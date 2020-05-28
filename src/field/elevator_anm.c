//=============================================================================
/**
 * @file	elevator_anm.c
 * @bfief	エレベーターアニメ
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

#define ELE_ANM_CONT_CODE	(0x1)		//エレベータアニメ識別コード 値は適当
enum{
	SEQ_SETUP,
	SEQ_ANM_START,
	SEQ_ANM_WAIT,
	SEQ_SE_WAIT,
	SEQ_END
};

typedef struct ELEVATOR_ANM_tag
{
	u8 Loop;		//アニメループ数	
	u8 Dir;			//方向
	u8 Seq;			//シーケンサ
	u8 dummy;
}ELEVATOR_ANM;

static BOOL ElevatorAnimeEvent(GMEVENT_CONTROL * event);

//==============================================================================
/**
 * エスカレータアニメーションセット
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inDir		方向（上下）
 * @param	inLoop		アニメループ数
 * 
 * @return	none
 */
//==============================================================================
void ElevatorAnm_StartAnm(FIELDSYS_WORK * fsys, const u8 inDir, const u8 inLoop)
{
	BOOL rc;

	rc = MPTL_CheckMap3DObj(fsys, BMID_EV_O01, NULL, NULL);
			
	if (rc){
		//エレベーターあった
		//データ作成
		ELEVATOR_ANM *work = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(ELEVATOR_ANM));
		work->Loop = inLoop;
		work->Dir = inDir;
		work->Seq = 0;
		//アニメイベントコール
		FieldEvent_Call(fsys->event, ElevatorAnimeEvent, work);
	}else{
		GF_ASSERT(0&&"エレベーターありません");
	}
}

//==============================================================================
/**
 * エレベータアニメイベント
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL	TRUE:イベント終了　FALSE:イベント継続
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
			//アニメーションセットアップ
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									ELE_ANM_CONT_CODE,	//エレベーターアニメ識別コード
									BMID_EV_O01,
									render_obj,
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									2,				//アニメ数2
									work->Loop,		//ループ
									FALSE			//反転しない
									);
		}
		(work->Seq)++;
		break;
	case SEQ_ANM_START:
		GF_ASSERT( ((work->Dir==ELE_UP)||(work->Dir==ELE_DOWN))&&"方向が不正" );
		//アニメーションスタート
		F3DASub_StartAnimation(fsys->AnimeContMng, ELE_ANM_CONT_CODE, work->Dir);
		//エレベーター音
		if (work->Dir==ELE_UP){	
			Snd_SePlay( SE_ELEBETA_UP);
		}else{	//work->Dir==ELE_DOWN
			Snd_SePlay( SE_ELEBETA_DOWN );
		}
		(work->Seq)++;
		break;
	case SEQ_ANM_WAIT:
		//アニメ待ち
		if ( (F3DASub_WaitAnimation(fsys->AnimeContMng, ELE_ANM_CONT_CODE)) ){
			//音ストップ
			if (work->Dir==ELE_UP){
				Snd_SeStopBySeqNo( SE_ELEBETA_UP, 0 );
			}else{	//work->Dir==ELE_DOWN
				Snd_SeStopBySeqNo( SE_ELEBETA_DOWN, 0 );
			}

			//ピンポーン
			Snd_SePlay( SE_ELEBETA_ARRIVAL );
			
			//アニメ解放
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
		//終り
		sys_FreeMemoryEz(work);
		return TRUE;
	}

	return FALSE;
}
