//============================================================================================
/**
 * @file	field_3d_anime_ev.c
 * @brief	イベント用3Dアニメ関連ファイル
 * @author	Nozomu Saito
 * @date	2006.01.26
 */
//============================================================================================
#include "common.h"
#include "system/wipe.h"
#include "field_3d_anime.h"
#include "fieldsys.h"
#include "field_event.h"

#include "map_tool.h"
#include "system/snd_tool.h"	//for SE

#include "field_3d_anime_ev.h"
#include "field_3d_anime_def.h"

#include "mapresource.h"		//for texture

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_jump.h"

#include "debug_saito.h"

#define DOOR_ANIME_ENTRY_ID	(1)
#define ESCA_ANIME_ENTRY_ID	(2)

#define ANM_CAM_ZOOM	(12)
#define ANM_CAM_ZOOM_OUT	(16)

#define	ZOOM_VAL	(96)

typedef struct FLD_3D_ANIME_WORK_tag{
	int seq;
	TARGET_RECT TargetRect;
	int GridX;
	int GridZ;
	u8 EntryID;
	u8 CameraZoomCount;
	u8 AnimeNum;
	BOOL CameraZoomStartFlg;
	u16 PerspWayWork;
}FLD_3D_ANIME_WORK;

static void AnimeCameraZoomIn(GF_CAMERA_PTR camera_ptr, u8 *ioCount);
static void AnimeCameraZoomOut(GF_CAMERA_PTR camera_ptr,  u8 *ioCount);
static BOOL IsAutoDoor(const int inObjID);
//==============================================================================
/**
 * イベント用3Dアニメ構造体メモリアロケーション
 * 
 * @param	none
 *
 * @retval  FLD_3D_ANIME_WORK_PTR	イベントアニメーションワークポインタ
 */
//==============================================================================
FLD_3D_ANIME_WORK_PTR	Fld3DAnm_AllocEvent3DAnimeWork(void)
{
	FLD_3D_ANIME_WORK_PTR anime_3d_work_ptr;
	anime_3d_work_ptr = sys_AllocMemoryLo( HEAPID_FIELD, sizeof(FLD_3D_ANIME_WORK) );
	anime_3d_work_ptr->seq = 0;
	return anime_3d_work_ptr;
}

//==============================================================================
/**
 * イベント用3Dアニメ構造体解放
 * 
 * @param	outAnime3DWorkPtr	イベントアニメーションワークポインタ
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_FreeEvent3DAnimeWork(FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr)
{
	sys_FreeMemoryEz(outAnime3DWorkPtr);
}

//==============================================================================
/**
 * イベント用3Dアニメ対象座標セット
 * 
 * @param	inGridX				ワールドグリッドX座標
 * @param	inGridZ				ワールドグリッドZ座標
 * @param	outAnime3DWorkPtr	イベントアニメーションワークポインタ
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_EventSetGrid(	const int inGridX, const int inGridZ,
							FLD_3D_ANIME_WORK_PTR outAnime3DWorkPtr)
{
	outAnime3DWorkPtr->GridX = inGridX;
	outAnime3DWorkPtr->GridZ = inGridZ;
}

//==============================================================================
/**
 * ドアアニメイベント(入る)
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	work	イベントアニメーションワークポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL Fld3DAnm_EventDoorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work)
{
	FIELD_OBJ_PTR fop;

	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {	BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
							BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
							BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
							BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
							BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1 };
			
			//カメラズーム初期化
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;
		
			MPTL_MakeTargetRect( work->GridX, work->GridZ, -1, -1, 3, 1, &rect );

			//登録コードを設定
			work->EntryID = DOOR_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				u8 anime_num;
				NNSG3dResTex *tex;

				anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
				work->AnimeNum = anime_num;
#if 0
				if (IsAutoDoor(obj_id)){	//自動ドアのとき
					anime_num = 2;			//セットするアニメ２つ（開く、閉じる）
				}else{						//それ以外
					anime_num = 4;			//セットするアニメ４つ（開く、閉じる、外出開く、外出閉じる）
				}
#endif				
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);

				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										DOOR_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex,anime_num,
										1,		//ループ1回
										FALSE);
			}else{
				OS_Printf_saitou("ドアないです\n");
				GF_ASSERT(0&&"No Door");
				return TRUE;	//ドアなし
			}//end if
			(work->seq) ++;
		}
		
		break;
	
	case 1:
		{
			int obj_id;
			int sound;
			int anime_no;
			obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//エレベーターの場合のみカメラズームさせない<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				//カメラバインドを解く
				GFC_PurgeCameraTarget(fsys->camera_ptr);
				//カメラズーム開始
				work->CameraZoomStartFlg = TRUE;
			}
			
			if ( IsAutoDoor(obj_id) ){
				//SEセット
				sound = SE_JIDO_DOOR_OPEN;	//自動ドア開く
			}else{
				//SEセット
				sound = SE_DOOR_OPEN;		//ドア開く
			}
			
			if (work->AnimeNum == 2){
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}else if(work->AnimeNum == 4){
				anime_no = ANIME_NO_DOOR_OPEN_IN;
			}else{
				GF_ASSERT(0);
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}
			
			F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//ドア開くアニメ
		}
		(work->seq) ++;
		break;
	case 2:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//開くアニメ終了待ち
			if (wait) {
				(work->seq) ++;
			}
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
#if 0		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_WALK_U_32F);	//出来る。任意のアニメセット
		}else{
			GF_ASSERT(0&&"アニメ登録できなかった");
		}
#else
		//ドアアニメの場合に限りアニメ登録チェックを行わなくてよい（ドアは壁になっていて、グリッドのズレが生じないため）
		FieldOBJ_AcmdSet(fop,AC_WALK_U_8F);	//アニメセット	
#endif
		(work->seq) ++;
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了

			//自機を消す
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			{
				int obj_id;
				int sound;
				int anime_no;
				obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
				if ( IsAutoDoor(obj_id) ){
					//SEセット
					sound = SE_JIDO_DOOR_CLOSE;	//自動ドア閉じる
				}else{
					//SEセット
					sound = SE_DOOR_CLOSE;		//ドア閉じる
				}

				if (work->AnimeNum == 2){
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}else if(work->AnimeNum == 4){
					anime_no = ANIME_NO_DOOR_CLOSE_IN;
				}else{
					GF_ASSERT(0);
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}
				F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//ドア閉じるアニメ
			}
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//閉じるアニメ終了待ち
			if (wait) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											DOOR_ANIME_ENTRY_ID	);
				return TRUE;
			}
		}
		break;
	}
	if (work->CameraZoomStartFlg){
		//カメラズームイン
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);
	}
	return FALSE;	
}

//==============================================================================
/**
 * ドアアニメイベント(出る)
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	work	イベントアニメーションワークポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL Fld3DAnm_EventDoorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work)
{
	FIELD_OBJ_PTR fop;

	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
							BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
							BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
							BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
							BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1};

			//カメラズーム初期化
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			
			MPTL_MakeTargetRect( work->GridX, work->GridZ, -1, 0, 3, 1, &rect );
			//登録コードを設定
			work->EntryID = DOOR_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				u8 anime_num;
				NNSG3dResTex *tex;
				anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
				work->AnimeNum = anime_num;
#if 0				
				if (IsAutoDoor(obj_id)){	//自動ドアのとき
					anime_num = 2;			//セットするアニメ２つ（開く、閉じる）
				}else{						//それ以外
					anime_num = 4;			//セットするアニメ４つ（開く、閉じる、外出開く、外出閉じる）
				}
#endif				
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										DOOR_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex,anime_num,
										1,		//ループ1回
										FALSE);
			}else{
				OS_Printf_saitou("ドアないです\n");
				GF_ASSERT(0&&"No Door");
				//フェードイン開始
				FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
				(work->seq)  = 6;
				return FALSE;
			}//end if

			//パースの保存
			work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);	
			
			//エレベーターの場合のみカメラズームさせない<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				//カメラのズームをセットしなおし
				//パース書き換え
				GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
			}
			(work->seq) ++;
		}
		break;
	case 1:
		//ワイプスタート	スプリットイン
		MJUMP_RequestWipe(	fsys->event, WIPE_PATTERN_WMS, WIPE_TYPE_SPLITIN_VCENTER,
							WIPE_TYPE_FADEIN,0x0000,6,1,HEAPID_WORLD );
		{
			int obj_id;
			int sound;
			int anime_no;
			obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);

			//エレベーターの場合のみカメラズームさせない<<20060704 add
			if (obj_id != BMID_ELE_DOOR1){
				work->CameraZoomStartFlg = TRUE;	//ズーム開始
			}
			
			if ( IsAutoDoor(obj_id) ){
				//SEセット
				sound = SE_JIDO_DOOR_OPEN;	//自動ドア開く
			}else{
				//SEセット
				sound = SE_DOOR_OPEN;		//ドア開く（外出）
			}

			if (work->AnimeNum == 2){
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}else if(work->AnimeNum == 4){
				anime_no = ANIME_NO_DOOR_OPEN_OUT;
			}else{
				GF_ASSERT(0);
				anime_no = ANIME_NO_DOOR_AUTO_OPEN;
			}
			
			F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//ドア開くアニメ
		}
		
		(work->seq) ++;
		break;
	case 2:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//開くアニメ終了待ち
			if (wait) {
				fop = Player_FieldOBJGet( fsys->player );
				//自機を表示
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) ++;
			}
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
#if 0			
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_WALK_D_32F);	//出来る。任意のアニメセット
		}else{
			GF_ASSERT(0&&"アニメ登録できなかった");
		}
#else
		//ドアアニメの場合に限りアニメ登録チェックを行わなくてよい（ドアは壁になっていて、グリッドのズレが生じないため）
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//アニメセット	
#endif
		(work->seq) ++;
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了
			{
				int obj_id;
				int sound;
				int anime_no;
				obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
				if ( IsAutoDoor(obj_id) ){
					//SEセット
					sound = SE_JIDO_DOOR_CLOSE;	//自動ドア閉じる
				}else{
					//SEセット
					sound = SE_DOOR_CLOSE;		//ドア閉じる(外出)
				}

				if (work->AnimeNum == 2){
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}else if(work->AnimeNum == 4){
					anime_no = ANIME_NO_DOOR_CLOSE_OUT;
				}else{
					GF_ASSERT(0);
					anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
				}
				F3DASub_StartAnimeSnd(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID, anime_no, sound);	//ドア閉じるアニメ
			}
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, DOOR_ANIME_ENTRY_ID);
			//閉じるアニメ終了、ブラックアウト終了、ズーム終了待ち
			if (wait&&WIPE_SYS_EndCheck()&&
					(work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr))) {
				
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											DOOR_ANIME_ENTRY_ID	);
				return TRUE;
			}
		}
		break;
	case 6:	//ドアがないとき用シーケンス
		if (WIPE_SYS_EndCheck()){
			return TRUE;
		}
		break;
	}
	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//ズームアウト
	}
	return FALSE;
}

//==============================================================================
/**
 * ドアアニメと連動するカメラ(ズームイン)
 * 
 * @param	camera_ptr		カメラポインタ
 * @param	ioCoint			カメラズームカウンタ
 *
 * @retval  none
 */
//==============================================================================
static void AnimeCameraZoomIn(GF_CAMERA_PTR camera_ptr, u8 *ioCount)
{
	u8 sp;
	u16 zoom;
	
	if ( (*ioCount)*ANM_CAM_ZOOM> ZOOM_VAL ){
		return;
	}
	
	zoom = (*ioCount)*ANM_CAM_ZOOM;

	if (zoom>ZOOM_VAL){
		sp = zoom-ZOOM_VAL;
	}else{
		sp = ANM_CAM_ZOOM;
	}

	{
		u16 persp_way;
		persp_way = GFC_GetCameraPerspWay(camera_ptr);
		if ((u16)(persp_way-sp)>0x0000){
			GFC_AddCameraPerspWay(-sp,camera_ptr);
		}
		(*ioCount)++;
	}
}

//==============================================================================
/**
 * ドアアニメと連動するカメラ(ズームアウト)
 * 
 * @param	camera_ptr		カメラポインタ
 * @param	ioCoint			カメラズームカウンタ
 *
 * @retval  none
 */
//==============================================================================
static void AnimeCameraZoomOut(GF_CAMERA_PTR camera_ptr, u8 *ioCount)
{
	u8 sp;
	u16 zoom;
	if ( (*ioCount)*ANM_CAM_ZOOM_OUT>= ZOOM_VAL ){
		return;
	}
	zoom = (*ioCount)*ANM_CAM_ZOOM_OUT;
	if (zoom>ZOOM_VAL){
		sp = zoom-ZOOM_VAL;
	}else{
		sp = ANM_CAM_ZOOM_OUT;
	}

	{
		u16 persp_way;
		persp_way = GFC_GetCameraPerspWay(camera_ptr);
		if ((u16)(persp_way+sp)>0x0000){
			GFC_AddCameraPerspWay(sp,camera_ptr);
		}
		(*ioCount)++;
	}
}

//==============================================================================
/**
 * 自動ドア判定
 * 
 * @param	inObjID		OBJID
 *
 * @retval  BOOL		TRUE:自動ドア	FALSE:自動ドアではない
 */
//==============================================================================
static BOOL IsAutoDoor(const int inObjID)
{
	return ( (inObjID == BMID_P_DOOR)||(inObjID == BMID_C5_DOOR_S)||
			 (inObjID == BMID_GYM_DOOR00)||(inObjID == BMID_DOOR_WI01)||
			 (inObjID == BMID_DOOR_PC01)||(inObjID == BMID_CARD_DOOR01)||
			 (inObjID == BMID_ELE_DOOR1)
			 /*||(inObjID == BMID_D3_DOOR1)||(inObjID == BMID_COUNTER_PC04)*/ );
}

//==============================================================================
/**
 * エスカレーター(上下左右関係無く、エスカレーター降りる)
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	work	イベントアニメーションワークポインタ
 * @param	inDir	自機方向
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL Fld3DAnm_EventEscalatorOutAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir)
{
	FIELD_OBJ_PTR fop;
	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_STAIR_PC_U01, BMID_STAIR_PC_D01, BMID_STAIR_PC_U02, BMID_STAIR_PC_D02};
			
			//自機方向によって検索範囲を分岐
			if (inDir == DIR_LEFT){
				MPTL_MakeTargetRect(work->GridX,work->GridZ,-1, 0, 2, 1, &rect );
			}else{	//(inDir == DIR_RIGHT)
				MPTL_MakeTargetRect(work->GridX,work->GridZ,0, 0, 2, 1, &rect );
			}
			//登録コードを設定
			work->EntryID = ESCA_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				NNSG3dResTex *tex;
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										ESCA_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex, 1, //セットするアニメ1つ
										1,		//ループ1回
										TRUE);	//逆再生
			}else{
				GF_ASSERT(0&&"エスカレーターがない");
				return TRUE;
			}//end if
			
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
				FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//出来る。動きをポーズ
			}else{
				GF_ASSERT(0&&"アニメ登録できなかった");
			}
			(work->seq) ++;
		}
		break;
	case 1:
		//フェードイン開始
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
		
		F3DASub_StartAnimeSnd(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID, ANIME_NO_ESCA, SEQ_SE_DP_ESUKA);	//エスカレーターアニメ
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			int code;
			if (inDir == DIR_RIGHT){
				code = AC_WALK_R_16F;
			}else{	//(inDir == DIR_LEFT)
				code = AC_WALK_L_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//出来る。任意のアニメセット
		}else{
			GF_ASSERT(0&&"アニメ登録できなかった");
		}
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//出来る。ポーズ解除
			(work->seq) ++;
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			int code;
			if (inDir == DIR_RIGHT){
				code = AC_WALK_R_16F;
			}else{	//(inDir == DIR_LEFT)
				code = AC_WALK_L_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//出来る。１歩左に歩く
			(work->seq) ++;
		}
		break;
	case 4:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了	
			(work->seq) ++;
		}
		break;
	case 5:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID);
			//エスカレーターアニメ終了、ブラックイン終了待ち
			if (wait&&WIPE_SYS_EndCheck()) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											ESCA_ANIME_ENTRY_ID	);
				//ＳＥストップ
				Snd_SeStopBySeqNo( SEQ_SE_DP_ESUKA, 0 );
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

//==============================================================================
/**
 * エスカレーター(上下左右関係無く、エスカレーターに乗る)
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	work	イベントアニメーションワークポインタ
 * @param	inDir	自機方向
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL Fld3DAnm_EventEscalatorInAnime(FIELDSYS_WORK * fsys, FLD_3D_ANIME_WORK_PTR work, const u8 inDir)
{
	FIELD_OBJ_PTR fop;
	switch (work->seq) {
	case 0:
		{
			BOOL rc;
			M3DO_PTR obj_ptr;
			TARGET_RECT rect;
			int obj_id;
			int list[] = {BMID_STAIR_PC_U01, BMID_STAIR_PC_D01, BMID_STAIR_PC_U02, BMID_STAIR_PC_D02};
			

			//自機方向によって検索範囲を分岐
			if (inDir == DIR_LEFT){
				MPTL_MakeTargetRect(work->GridX,work->GridZ,-1, 0, 2, 1, &rect );
			}else{	//(inDir == DIR_RIGHT)
				MPTL_MakeTargetRect(work->GridX,work->GridZ,0, 0, 2, 1, &rect );
			}
			//登録コードを設定
			work->EntryID = ESCA_ANIME_ENTRY_ID;
			
			rc = MPTL_CheckPluralMap3DObjInRect(fsys,
												list,
												NELEMS(list),
												&rect,
												&obj_ptr,
												&obj_id);

			if (rc){
				u8 no;
				NNSG3dResTex *tex;
				tex = GetMapResourceBmTexturePTR(fsys->MapResource);
				F3DASub_SetUpAnimation(	fsys->field_3d_anime,
										fsys->AnimeContMng,
										ESCA_ANIME_ENTRY_ID,
										obj_id,
										M3DO_GetRenderObj(obj_ptr),
										M3DO_GetObjModel(obj_ptr),
										tex, 1,	//セットするアニメ1つ
										1,		//ループ1回
										FALSE);
			}else{
				GF_ASSERT(0&&"エスカレーターがない");
				return TRUE;
			}//end if
			
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
				FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//出来る。動きをポーズ
			}else{
				GF_ASSERT(0&&"アニメ登録できなかった");
			}
			(work->seq) ++;
		}
		break;
	case 1:
		F3DASub_StartAnimeSnd(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID, ANIME_NO_ESCA, SEQ_SE_DP_ESUKA);	//エスカレーターアニメ
		fop = Player_FieldOBJGet( fsys->player );
		
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			int code;
			if (inDir == DIR_LEFT){
				code = AC_WALK_L_16F;
			}else{
				code = AC_WALK_R_16F;
			}
			FieldOBJ_AcmdSet(fop,code);	//出来る。任意のアニメセット
		}else{
			GF_ASSERT(0&&"アニメ登録できなかった");
		}
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//出来る。ポーズ解除
			//フェードアウト開始
			FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
			(work->seq) ++;
		}
		break;
	case 3:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了	
			(work->seq) ++;
		}
		break;
	case 4:
		{
			BOOL wait;
			wait = F3DASub_WaitAnimation(fsys->AnimeContMng, ESCA_ANIME_ENTRY_ID);
			//エスカレーターアニメ終了、ブラックアウト終了待ち
			if (wait&&WIPE_SYS_EndCheck()) {
				F3DASub_RereaseAnimation(	fsys->field_3d_anime,
											fsys->AnimeContMng,
											ESCA_ANIME_ENTRY_ID	);
				//ＳＥストップ
				Snd_SeStopBySeqNo( SEQ_SE_DP_ESUKA, 0 );
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}


//==============================================================================
//
//	↓スクリプト用関数群
//
//==============================================================================


//==============================================================================
/**
 * アニメ待ち
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
static BOOL WaitAnime(GMEVENT_CONTROL * event)
{
	BOOL wait;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	u8 *entry  = FieldEvent_GetSpecialWork(event);
	wait = F3DASub_WaitAnimation(fsys->AnimeContMng, *entry);
	//開くアニメ終了待ち
	if (wait) {
		sys_FreeMemoryEz(entry);
		return TRUE;
	}
	return FALSE;
}

//==============================================================================
/**
 * ドアアニメーションのセットアップ
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inEntryID	登録ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_Setup(FIELDSYS_WORK * fsys,
						const int inGridX, const int inGridZ, const u8 inEntryID)
{
	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {	BMID_DOOR01,BMID_T1_DOOR1,BMID_T2_DOOR1,BMID_T2_DOOR2,
					BMID_C1_DOOR1,BMID_P_DOOR, BMID_DOOR_PC01, BMID_DOOR_WI01,
					BMID_GYM_DOOR01,BMID_C3_DOOR1, BMID_C3_DOOR2,BMID_T3_DOOR1,
					BMID_C4_DOOR1,BMID_D3_DOOR1, BMID_C5_DOOR_S, BMID_GYM_DOOR00,
					BMID_CARD_DOOR01, BMID_COUNTER_PC04, BMID_L2_DOOR1, BMID_ELE_DOOR1 };

	MPTL_MakeTargetRect( inGridX, inGridZ, -1, 0, 3, 1, &rect );

	rc = MPTL_CheckPluralMap3DObjInRect(fsys,
										list,
										NELEMS(list),
										&rect,
										&obj_ptr,
										&obj_id);

	if (rc){
		u8 no;
		u8 anime_num;
		NNSG3dResTex *tex;
		anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
#if 0		
		if (IsAutoDoor(obj_id)){	//自動ドアのとき
			anime_num = 2;			//セットするアニメ２つ（開く、閉じる）
		}else{						//それ以外
			anime_num = 4;			//セットするアニメ４つ（開く、閉じる、外出開く、外出閉じる）
		}
#endif		
		tex = GetMapResourceBmTexturePTR(fsys->MapResource);
		F3DASub_SetUpAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID,
								obj_id,
								M3DO_GetRenderObj(obj_ptr),
								M3DO_GetObjModel(obj_ptr),
								tex,anime_num,
								1,		//ループ1回
								FALSE);
	}else{
		GF_ASSERT(0&&"ドアありません");
	}
}

//==============================================================================
/**
 * ドアアニメーション(オープン)
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_StartOpenDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID	)
{
	int obj_id;
	int sound;
	int anime_no;
	u8 anime_num;
	obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, inEntryID);
	anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
	if ( IsAutoDoor(obj_id) ){
		//SEセット
		sound = SE_JIDO_DOOR_OPEN;	//自動ドア開く
	}else{
		//SEセット
		sound = SE_DOOR_OPEN;		//ドア開く
	}

	if (anime_num == 2){
		anime_no = ANIME_NO_DOOR_AUTO_OPEN;
	}else if(anime_num ==4){
		anime_no = ANIME_NO_DOOR_OPEN_IN;
	}else{
		GF_ASSERT(0);
		anime_no = ANIME_NO_DOOR_AUTO_OPEN;
	}
	F3DASub_StartAnimeSnd(fsys->AnimeContMng, inEntryID, anime_no, sound);	//ドア開くアニメ
}

//==============================================================================
/**
 * ドアアニメーション(クローズ)
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_StartCloseDoorAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID	)
{
	int obj_id;
	int sound;
	int anime_no;
	u8 anime_num;
	obj_id = F3DASub_GetObjIDFromEntryID(fsys->AnimeContMng, inEntryID);
	anime_num = F3DA_GetAnimeNum(fsys->field_3d_anime, obj_id);
	if ( IsAutoDoor(obj_id) ){
		//SEセット
		sound = SE_JIDO_DOOR_CLOSE;	//自動ドア閉じる
	}else{
		//SEセット
		sound = SE_DOOR_CLOSE;		//ドア閉じる
	}

	if (anime_num == 2){
		anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
	}else if(anime_num == 4){
		anime_no = ANIME_NO_DOOR_CLOSE_IN;
	}else{
		GF_ASSERT(0);
		anime_no = ANIME_NO_DOOR_AUTO_CLOSE;
	}
	F3DASub_StartAnimeSnd(fsys->AnimeContMng, inEntryID, anime_no, sound);	//ドア閉じるアニメ
}

//==============================================================================
/**
 * アニメーション待ち
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_WaitAnime(FIELDSYS_WORK * fsys, const u8 inEntryID)
{
	u8 *entry = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(u8));
	*entry = inEntryID;
	FieldEvent_Call(fsys->event, WaitAnime, entry);
}

//==============================================================================
/**
 * ドアアニメーション解放
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ID
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_DOOR_FreeDoor(FIELDSYS_WORK * fsys, const u8 inEntryID)
{
	F3DASub_RereaseAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID	);
}

//==============================================================================
/**
 * 流砂アニメーションのスタート
 * 
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inAnmNo		アニメナンバー	0：流砂下　1：流砂上
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval  none
 */
//==============================================================================
void Fld3DAnm_StartQuickSandAnime(	const int inGridX,
									const int inGridZ,
									const int inAnmNo,
									FIELDSYS_WORK * fsys)
{

	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {BMID_CY_SLOPE, BMID_CY_SLOPE_DUN};
		
	//検索範囲作成
	MPTL_MakeTargetRect( inGridX, inGridZ, 0, -1, 1, 3, &rect );
	//流砂OBJ取得
/**
	rc = MPTL_CheckMap3DObjInRect(	fsys,
									BMID_CY_SLOPE,
									&rect,
									&obj_ptr);
*/									
	rc = MPTL_CheckPluralMap3DObjInRect(fsys,
										list,
										NELEMS(list),
										&rect,
										&obj_ptr,
										&obj_id);
	GF_ASSERT(rc&&"流砂見つからない");
	
	//アニメセット
	{
		NNSG3dRenderObj *render_obj;
		render_obj = M3DO_GetRenderObj(obj_ptr);
		rc =	F3DA_SetFld3DAnime(	obj_id, inAnmNo, TRUE,
									render_obj,
									fsys->field_3d_anime );
		GF_ASSERT(rc&&"流砂セット失敗");
	}
	{
		FLD_3D_ANM_DAT_PTR anime;
		//アニメ取得
		anime = F3DA_GetFld3DAnmPtr(obj_id, inAnmNo, fsys->field_3d_anime);
		//アニメ開始
		F3DA_SetStartFrame(anime);
		F3DA_SetStopFlg(anime, FALSE);
		F3DA_MoveAnime(anime);
	}
}

typedef struct FLD_MAP_JUMP_WORK_tag{
	int seq;
	u8 CameraZoomCount;
	BOOL CameraZoomStartFlg;
	u16 PerspWayWork;
}FLD_MAP_JUMP_WORK;

//メモリ確保
extern FMJ_WORK_PTR	MapJump_AllocWork(void)
{
	FMJ_WORK_PTR work_ptr;
	work_ptr = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(FLD_MAP_JUMP_WORK));
	work_ptr->seq = 0;
	return work_ptr;
}

//==============================================================================
/**
 * ホワイトイン
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL MapJump_EventFadeInWhite(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		fop = Player_FieldOBJGet( fsys->player );
		//下向きの場合は自機非表示
		if (Player_DirGet( fsys->player ) == DIR_DOWN){
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			(work->seq) = 1;
		}else{
			//自機表示
			FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
			(work->seq) = 3;

		}
		//カメラズーム初期化
		work->CameraZoomStartFlg = FALSE;
		work->CameraZoomCount = 0;	
			
		//カメラのズームをセットしなおし
		{
			//パースの保存
			work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);
			//パース書き換え
			GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
		}
		
		//ワイプスタート	ホワイトイン
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
						WIPE_TYPE_FADEIN,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		work->CameraZoomStartFlg = TRUE;	//ズームアウト開始
		
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//自機表示
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//アニメセット
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了
			(work->seq) ++;
		}
		break;
	case 3:
		//ワイプ終了、ズーム終了待ち
		if ( WIPE_SYS_EndCheck()&&
				( work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr) ) ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//ズームアウト
	}

	return FALSE;
}


//==============================================================================
/**
 * ホワイトアウト
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL MapJump_EventFadeOutWhite(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			//自機非表示
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			//カメラズーム初期化
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			//入る音
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//ワイプスタート	ホワイトアウト
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//ズームイン開始
			(work->seq) ++;
		}
		break;
	case 1:
		//ワイプ終了待ち
		if ( WIPE_SYS_EndCheck() ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);		//ズームイン
	}

	return FALSE;
}

//==============================================================================
/**
 * ホールアウト
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL MapJump_EventFadeOutHole(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			//カメラズーム初期化
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			//入る音
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//ワイプスタート	ホールアウト
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT,
								WIPE_TYPE_FADEOUT,0x0000,6,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//ズームイン開始
			(work->seq) ++;
		}
		break;
	case 1:
		//ワイプ終了待ち
		if ( WIPE_SYS_EndCheck() ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomIn(fsys->camera_ptr, &work->CameraZoomCount);		//ズームイン
	}

	return FALSE;
}

//==============================================================================
/**
 * シャット・スライドイン
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL MapJump_EventFadeInShutSlide(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			u8 dir;
			u8 main_wipe_type;
			fop = Player_FieldOBJGet( fsys->player );
			dir = Player_DirGet( fsys->player );
			//下向きの場合は自機非表示
			if ( dir == DIR_DOWN){
				FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
				(work->seq) = 1;
			}else{
				//自機表示
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) = 3;
		
			}
			//カメラズーム初期化
			work->CameraZoomStartFlg = FALSE;
			work->CameraZoomCount = 0;	
			
			//カメラのズームをセットしなおし
			{
				//パースの保存
				work->PerspWayWork = GFC_GetCameraPerspWay(fsys->camera_ptr);
				//パース書き換え
				GFC_AddCameraPerspWay(-(ZOOM_VAL),fsys->camera_ptr);	
			}

			//方向別にワイプの種類を分ける
			switch(dir){
			case DIR_UP:
				main_wipe_type = WIPE_TYPE_SHUTTERIN_DOWN;
				break;
			case DIR_DOWN:
				main_wipe_type = WIPE_TYPE_SHUTTERIN_UP;
				break;
			case DIR_LEFT:
				main_wipe_type = WIPE_TYPE_SLIDEIN;
				break;
			case DIR_RIGHT:
				main_wipe_type = WIPE_TYPE_SLIDEIN_LR;
				break;
			default:
				GF_ASSERT(0);
			}
			
			//ワイプスタート	シャット・スライドイン
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, main_wipe_type,
								WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			work->CameraZoomStartFlg = TRUE;	//ズームアウト開始
		}
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//自機表示
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//アニメセット
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了
			(work->seq) ++;
		}
		break;
	case 3:
		//ワイプ終了、ズーム終了待ち
		if ( WIPE_SYS_EndCheck()&&
				( work->PerspWayWork == GFC_GetCameraPerspWay(fsys->camera_ptr) ) ) {
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	if (work->CameraZoomStartFlg){
		AnimeCameraZoomOut(fsys->camera_ptr, &work->CameraZoomCount);		//ズームアウト
	}

	return FALSE;
}

//==============================================================================
/**
 * ブラックイン
 * 
 * @param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
BOOL MapJump_EventFadeInBlack(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FMJ_WORK_PTR work = FieldEvent_GetSpecialWork(event);
	switch (work->seq) {
	case 0:
		{
			u8 dir;
			u8 main_wipe_type;
			fop = Player_FieldOBJGet( fsys->player );
			dir = Player_DirGet( fsys->player );
			//下向きの場合は自機非表示
			if ( dir == DIR_DOWN){
				FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
				(work->seq) = 1;
			}else{
				//自機表示
				FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
				(work->seq) = 3;
		
			}
			
			MJUMP_RequestWipe(	event, WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		}
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		//自機表示
		FieldOBJ_StatusBitSet_Vanish( fop, FALSE );
		FieldOBJ_AcmdSet(fop,AC_WALK_D_8F);	//アニメセット
		(work->seq) ++;
		break;
	case 2:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了
			(work->seq) ++;
		}
		break;
	case 3:
		//ワイプ終了待ち
		if ( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz(work);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

