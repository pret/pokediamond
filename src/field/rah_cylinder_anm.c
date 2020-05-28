//=============================================================================
/**
 * @file	rah_cylinder_anm.c
 * @bfief	レイ・アイ・ハイのシリンダーアニメ
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"
#include "fielddata/build_model/build_model_id.h"
#include "field\sysflag.h"

#include "rah_cylinder_anm.h"

static BOOL AnimeEvent(GMEVENT_CONTROL * event);

//--------------------------------------------------------------
/**
 * 初期化
 *
 * @param	fsys			フィールドシステムポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void RAH_CYL_ANM_Setup(FIELDSYS_WORK *fsys)
{
	FLD_3D_ANM_DAT_PTR anime;
	//救出イベントフラグによって分岐
	if ( !SysFlag_ReiAiHaiCheck( SaveData_GetEventWork(fsys->savedata) ) ){
		//救出前
		//1番アニメを開始フレームで停止 ループ数を1にセット
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetAnimeLoopMax(anime, 1);
		F3DA_SetStopFlg(anime, TRUE);
	}else{
		//救出後
		//0番アニメを停止　1番アニメを最終フレームで停止
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 0, fsys->field_3d_anime );
		F3DA_SetStopFlg(anime, TRUE);
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetLastFrame(anime);
		F3DA_SetStopFlg(anime, TRUE);
	}
}

//--------------------------------------------------------------
/**
 * シリンダー救出アニメ開始
 *
 * @param	fsys			フィールドシステムポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void RAH_CYL_ANM_StartFreeEvent(FIELDSYS_WORK *fsys)
{
	//アニメイベントコール
	FieldEvent_Call(fsys->event, AnimeEvent, NULL);
}

//--------------------------------------------------------------
/**
 * シリンダー救出アニメイベント
 *
 * @param	event	イベントポインタ
 *
 * @retval	BOOL	TRUE:イベント終了	FALSE:イベント継続
 */
//--------------------------------------------------------------
static BOOL AnimeEvent(GMEVENT_CONTROL * event)
{
	int *seq;
	FLD_3D_ANM_DAT_PTR anime;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	
	seq  = FieldEvent_GetSeqWork(event);
	switch(*seq){
	case 0: //0番アニメの最終フレーム待ち
		//アニメ検索
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 0, fsys->field_3d_anime );
		if ( F3DA_IsLastFrame(anime) ){
			F3DA_SetStopFlg(anime, TRUE);		//停止
			(*seq)++;
		}
		break;
	case 1: //1番アニメスタート
		//アニメ検索
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetStopFlg(anime, FALSE);		//再生
		(*seq)++;
		break;
	case 2:	//1番アニメ待ち
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		if ( F3DA_IsAnimeEnd(anime) ){
			return TRUE;
		}
		break;
	}
	return FALSE;
}
