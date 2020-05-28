//=============================================================================
/**
 * @file	fld_lift.c
 * @bfief	リフト操作(ジム除く)
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/snd_tool.h"
#include "include/savedata/gimmickwork.h"
#include "../fielddata/build_model/build_model_id.h"
#include "fielddata/maptable/zone_id.h"

#include "field_gimmick_def.h"

#include "fld_lift.h"

#define FLD_LIFT_DATA_HRIGHT_ID	(0)		//拡張高さインデックス

#define NORM_LIFT_DIF	(FX32_ONE)		//高さ変動値
#define REAGE_LIFT_DIF	(FX32_ONE*2)		//高さ変動値
#define LIFT_BOTTOM	(0)
#define LIFT_TOP	(1)

#define MINE_LIFT_START_Z_D24R0103	(26)
#define MINE_LIFT_START_Z_D24R0105	(32*1+16)
#define MINE_LIFT_START_Z_D24R0106	(15)
#define MINE_LIFT_START_Z_C10R0102	(15)
#define MINE_LIFT_START_Z_C10R0104	(15)
#define MINE_LIFT_START_Z_C10R0106	(15)
#define MINE_LIFT_START_Z_C10R0108	(15)
#define MINE_LIFT_START_Z_C10R0110	(23)
#define MINE_LIFT_START_Z_C10R0111	(18)

#define MINE_R0103_EX_HEIGHT_X	(10)
#define MINE_R0103_EX_HEIGHT_Z	(23)

#define MINE_R0105_EX_HEIGHT_X	(18)
#define MINE_R0105_EX_HEIGHT_Z	(32*1+12)

#define MINE_R0106_EX_HEIGHT_X	(8)
#define MINE_R0106_EX_HEIGHT_Z	(11)

#define REAGE_EX_HEIGHT_X	(3)
#define REAGE_EX_HEIGHT_Z	(11)

#define CHAMP_EX_HEIGHT_X	(3)
#define CHAMP_EX_HEIGHT_Z	(19)

#define CHAMP_ROOM_EX_HEIGHT_X	(7)
#define CHAMP_ROOM_EX_HEIGHT_Z	(8)

#define LIFT_W	(3)
#define LIFT_H	(2)

#define MINE_LIFT_LV1		(FX32_ONE*16*1)		//鉱山下フロア
#define MINE_LIFT_LV2		(FX32_ONE*16*9)		//鉱山上フロア
#define REAGE01_LIFT_LV1	(0)					//四天王1下フロア
#define REAGE01_LIFT_LV2	(FX32_ONE*16*10)	//四天王1上フロア
#define REAGE02_LIFT_LV1	(0)					//四天王2下フロア
#define REAGE02_LIFT_LV2	(FX32_ONE*16*5)		//四天王2上フロア
#define REAGE03_LIFT_LV1	(0)					//四天王3下フロア
#define REAGE03_LIFT_LV2	(FX32_ONE*16*5)		//四天王3上フロア
#define REAGE04_LIFT_LV1	(0)					//四天王4下フロア
#define REAGE04_LIFT_LV2	(FX32_ONE*16*5)		//四天王4上フロア
#define CHAMP_LIFT_LV1		(0)					//チャンピオン通路下フロア
#define CHAMP_LIFT_LV2		(FX32_ONE*16*5)		//チャンピオン通路上フロア
#define CHAMP_ROOM_LIFT_LV1	(0)					//チャンピオン部屋下フロア
#define CHAMP_ROOM_LIFT_LV2	(FX32_ONE*16*15)	//チャンピオン部屋上フロア

#define EX_LIFT_POS_X	( FX32_ONE*(16*19+8) )
#define EX_LIFT_POS_Y	( FX32_ONE*16 )
#define EX_LIFT_POS_Z	( FX32_ONE*(16*(32+12)+8) )


typedef enum {
	LIFT_MINE01 = 0,
	LIFT_MINE02,
	LIFT_MINE03,
	LIFT_REAGE01,
	LIFT_REAGE02,
	LIFT_REAGE03,
	LIFT_REAGE04,
	LIFT_CHAMP,
	LIFT_CHAMP_ROOM,
	LIFT_MAX,
}LIFT_LOCATION;

typedef enum {
	TYPE_NORMAL,
	TYPE_REAGE,
};

typedef struct LIFT_DATA_tag
{
	fx32	BottomTop[2];
	int		X;
	int		Z;
	BOOL	Stop;	//上にあがったら、反応しなくなるかどうか　TRUE：反応しない
	BOOL	ExpObj;	//拡張ＯＢＪかどうか　TRUE:拡張ＯＢＪ
}LIFT_DATA;

typedef struct LIFT_WORK_tag
{
	u16		Lift;		//リフトの位置（上か下か）
	u16		Location;
	BOOL	LiftValid;	//リフト反応するか？	TRUE:反応する
	int		Type;		//ＳＥ	TYPE_NORMAL:通常リフト　TYPE_REAGE:リーグリフト 
	//Typeはセーブする必要はないけど、イベントに引き継ぐためここに確保する
}LIFT_WORK;

typedef struct {
	int seq;	///<シーケンス保持ワーク
	fx32 DstHeight;	//目的高さ
	BOOL Exp;	//拡張ＯＢＪかどうか　TRUE:拡張ＯＢＪ
	int Type;	//	LIFT_WORKのTypeを引き継ぐ
}EVENT_FLIFT_WORK;


static BOOL GMEVENT_MoveUpLift(GMEVENT_CONTROL * event);
static BOOL GMEVENT_MoveDownLift(GMEVENT_CONTROL * event);
static void FldLiftSePlay(const int inType);
static void FldLiftSeStop(const int inType);


static const LIFT_DATA LiftData[LIFT_MAX] = 
{
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0103_EX_HEIGHT_X, MINE_R0103_EX_HEIGHT_Z, FALSE, FALSE },
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0105_EX_HEIGHT_X, MINE_R0105_EX_HEIGHT_Z, FALSE, TRUE },
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0106_EX_HEIGHT_X, MINE_R0106_EX_HEIGHT_Z, FALSE, FALSE },
	{ {REAGE01_LIFT_LV1, REAGE01_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE02_LIFT_LV1, REAGE02_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE03_LIFT_LV1, REAGE03_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE04_LIFT_LV1, REAGE04_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {CHAMP_LIFT_LV1, CHAMP_LIFT_LV2}, CHAMP_EX_HEIGHT_X, CHAMP_EX_HEIGHT_Z, TRUE, FALSE },
	{ {CHAMP_ROOM_LIFT_LV1, CHAMP_ROOM_LIFT_LV2}, CHAMP_ROOM_EX_HEIGHT_X, CHAMP_ROOM_EX_HEIGHT_Z, TRUE, FALSE },
};

//---------------------------------------------------------------------------
/**
 * @brief	リフト:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLIFT_Setup(FIELDSYS_WORK *fsys)
{
	BOOL rc;
	M3DO_PTR ptr;
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	const LIFT_DATA *lift_data;
	fx32 height;

	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	lift_data = &LiftData[ lift_work->Location ];
	height = lift_data->BottomTop[lift_work->Lift];

	if(lift_data->ExpObj){
		//リフトの作成
		VecFx32 vec = {EX_LIFT_POS_X, 0,EX_LIFT_POS_Z};
		vec.y = height;
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_LIFT_BASE01,
							&vec, NULL,
							fsys->field_3d_anime );//<リフト
		ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
	}else{
		//リフト探す
		const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
		rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
		GF_ASSERT(rc);
	}
	
	//モデルのy座標変更
	{
		VecFx32 vec;
		vec = M3DO_GetGlobalVec(ptr);
		vec.y = height;
		M3DO_SetGlobalVec(ptr, &vec);
	}
	//
	//高さデータ作成
	EXH_SetUpExHeightData(	FLD_LIFT_DATA_HRIGHT_ID,
							lift_data->X, lift_data->Z, LIFT_W, LIFT_H,
							height,
							fsys->ExHeightList );
	
}

//---------------------------------------------------------------------------
/**
 * @brief	リフト:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLIFT_Init(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_FLD_LIFT);

	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	lift_work->LiftValid = TRUE;
	lift_work->Type = TYPE_NORMAL;

	//入ってきた場所のZ座標で、リフトの位置を決定（することにする）
	//※地形に依存した判定なので、地形が変わった場合は注意が必要
	switch(fsys->location->zone_id){
	case ZONE_ID_D24R0103:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0103){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE01;
		break;
	case ZONE_ID_D24R0105:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0105){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE02;
		break;
	case ZONE_ID_D24R0106:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0106){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE03;
		break;
	case ZONE_ID_C10R0102:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0102){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_REAGE01;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0104:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0104){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_REAGE02;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0106:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0106){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_REAGE03;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0108:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0108){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_REAGE04;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0110:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0110){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_CHAMP;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0111:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0111){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//リフト無反応
		}
		lift_work->Location = LIFT_CHAMP_ROOM;
		lift_work->Type = TYPE_REAGE;
		break;
	default:
		GF_ASSERT(0);
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	リフトの有効性チェック
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	u8		0:リフト無効	1:リフト有効
 */
//---------------------------------------------------------------------------
u8 FLIFT_CheckValid(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	if (lift_work->LiftValid){
		return 1;
	}else{
		return 0;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	リフト:移動
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	u8		0：イベントコールしない	1：イベントコールする
 */
//---------------------------------------------------------------------------
void FLIFT_MoveLift(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	EVENT_FLIFT_WORK * eflw;

	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	//一方通行リフトかをチェック(リフトが上にある場合は反応しなくなる)
	if ( (LiftData[lift_work->Location].Stop)&&(lift_work->Lift == LIFT_TOP) ){
		return;
	}
	
	//イベントコール
	eflw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_FLIFT_WORK));
	eflw->seq = 0;

	{
		eflw->Exp = LiftData[ lift_work->Location ].ExpObj;
		eflw->Type = lift_work->Type;
		if (lift_work->Lift == LIFT_BOTTOM){		//上に行く
			eflw->DstHeight = LiftData[lift_work->Location].BottomTop[LIFT_TOP];
			FieldEvent_Call(fsys->event, GMEVENT_MoveUpLift, eflw);
			lift_work->Lift = LIFT_TOP;
		}else{											//下に行く
			eflw->DstHeight = LiftData[lift_work->Location].BottomTop[LIFT_BOTTOM];
			FieldEvent_Call(fsys->event, GMEVENT_MoveDownLift, eflw);
			lift_work->Lift = LIFT_BOTTOM;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	リフトを上げる
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveUpLift(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_FLIFT_WORK * eflw = FieldEvent_GetSpecialWork(event);

	switch (eflw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//自機の高さ自動取得をオフ

		//リフト音再生
		FldLiftSePlay(eflw->Type);
		(eflw->seq) ++;
		break;
	case 1:	//リフトを上昇
		{
			if (eflw->Exp){
				//リフトOBJを取得
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			}else{
				const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
				BOOL rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
				GF_ASSERT(rc);
			}
			//y座標変更
			{
				fx32 dif;
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				if (eflw->Type == TYPE_NORMAL){
					dif = NORM_LIFT_DIF;
				}else{
					dif = REAGE_LIFT_DIF;
				}
				vec.y += dif;

				if (vec.y >= eflw->DstHeight){	//セット終了
					vec.y = eflw->DstHeight;
					//リフト音停止
					FldLiftSeStop(eflw->Type);
					(eflw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//自機高さ変更
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( FLD_LIFT_DATA_HRIGHT_ID, eflw->DstHeight, fsys->ExHeightList );
		//自機の高さ自動取得をオン
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );
		//リフト移動終了音
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(eflw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(eflw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	リフトを下げる
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveDownLift(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_FLIFT_WORK * eflw = FieldEvent_GetSpecialWork(event);

	switch (eflw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//自機の高さ自動取得をオフ

		//リフト音再生
		FldLiftSePlay(eflw->Type);
		(eflw->seq)	++;
		break;
	case 1:	//リフトを下降
		{
			if (eflw->Exp){
				//リフトOBJを取得
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			}else{
				const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
				BOOL rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
				GF_ASSERT(rc);
			}
			//y座標変更
			{
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				vec.y -= NORM_LIFT_DIF;
				
				if (vec.y <= eflw->DstHeight){	//セット終了
					vec.y = eflw->DstHeight;
					//リフト音停止
					FldLiftSeStop(eflw->Type);
					(eflw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//自機高さ変更
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( FLD_LIFT_DATA_HRIGHT_ID, eflw->DstHeight, fsys->ExHeightList );
		//自機の高さ自動取得をオン
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );
		//リフト移動終了音
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(eflw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(eflw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	リフト音
 * 
 * @param	inType		リフトタイプ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void FldLiftSePlay(const int inType)
{
	if (inType == TYPE_NORMAL){
		Snd_SePlay( SEQ_SE_DP_ELEBETA );
	}else{
		Snd_SePlay( SE_C10_LIFT );
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	リフ音停止
 * 
 * @param	inType		リフトタイプ 
 *
 * @return	none
 */
//---------------------------------------------------------------------------
static void FldLiftSeStop(const int inType)
{
	if (inType == TYPE_NORMAL){
		Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
	}else{
		Snd_SeStopBySeqNo( SE_C10_LIFT, 0 );
	}
}



