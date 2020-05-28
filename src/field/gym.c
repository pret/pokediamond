//=============================================================================
/**
 * @file	gym.c
 * @bfief	ジム仕掛けとか
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

#include "field_gimmick_def.h"
#include "sysflag_def.h" 

#include "gym_def.h"

#include "gym_local.h"
#include "gym_init.h"

#include "gym.h"

//ジム共通
#define ONE_GRID	(FX32_ONE*16)
#define ONE_HEIGHT	(FX32_ONE*16)

//水ジム-----------------
//水ジムの水位定義
#define WATER_LV1	(FX32_ONE*16*0)		//高さ１段階
#define WATER_LV2	(FX32_ONE*16*2)		//高さ２段階
#define WATER_LV3	(FX32_ONE*16*4)		//高さ３段階
#define MODEL_WATER_LV1	(FX32_ONE*0)	//モデル高さ１段階
#define MODEL_WATER_LV2	(FX32_ONE*16*2)	//モデル高さ２段階
#define MODEL_WATER_LV3	(FX32_ONE*16*4)	//モデル高さ３段階
#define WATER_DIF	(FX32_ONE)		//高さ変動値（モデル高さ用）

#define WTAER_GYM_DATA_HRIGHT_ID	(0)	//拡張高さ参照インデックス（水ジム水面用）

//アニメ制御コード
#define WATER_GYM_BTN_ANM1		(1)
#define WATER_GYM_BTN_ANM2		(2)
#define WATER_GYM_BTN_ANM3		(3)

#define WATER_GYM_EX_HEIGHT_X	(1)
#define WATER_GYM_EX_HEIGHT_Z	(2)
#define WATER_GYM_EX_HEIGHT_W	(25)
#define WATER_GYM_EX_HEIGHT_H	(38)


//ゴーストジム-----------------
//リフト位置定義
#define GHOST_LIFT_LV1	(FX32_ONE*16*0)		//高さ１段階
#define GHOST_LIFT_LV2	(FX32_ONE*16*10)		//高さ２段階
#define MODEL_GHOST_LIFT_LV1	(FX32_ONE*0)	//モデル高さ１段階
#define MODEL_GHOST_LIFT_LV2	(FX32_ONE*16*10)	//モデル高さ２段階
#define GHOST_LIFT_DIF	(FX32_ONE)		//高さ変動値（モデル高さ用）

#define GHOST_GYM_DATA_HRIGHT_ID	(0)	//拡張高さ参照インデックス（ゴーストジムリフト用）

#define GHOST_GYM_EX_HEIGHT_X	(8)
#define GHOST_GYM_EX_HEIGHT_Z	(13)
#define GHOST_GYM_EX_HEIGHT_W	(3)
#define GHOST_GYM_EX_HEIGHT_H	(2)

//鋼ジム-------------------
//フロア間距離
#define FLOOR_MARGIN	(10)
#define FLOOR_DISP_START_VAL	(9)
#define STEEL_UD_LIFT_DIF	(FX32_ONE*8)		//高さ変動値（モデル高さ用）
#define STEEL_FRLR_LIFT_DIF	(FX32_ONE*8)		//手前奥左右変動値（モデル高さ用）
#define STEEL_CENTER_OFS	(FX32_ONE*8)

#define STEEL_FOG_OFS	(0x76a0)
#define STEEL_FOG_MAX	(72)

//格闘ジム-------------------
#define COMBAT_WALL_POS_MAX	(15)
#define COMBAT_CENTER_OFS_X	(FX32_ONE*16*2)
#define COMBAT_CENTER_OFS_Z	(FX32_ONE*8)
enum{
	WALLNO_1 = 0,
	WALLNO_2,
	WALLNO_3,
	WALLNO_4,
	WALLNO_5,
	WALLNO_6,
	WALLNO_7,
	WALLNO_8,
	WALLNO_9,
	WALLNO_10,
	WALLNO_11,
	WALLNO_12,
};

//電気ジム------------------
#define ELEC_GEAR_NUM1_YROT	(3)
#define ELEC_GEAR_NUM2_YROT	(4)
#define ELEC_GEAR_NUM2_XROT	(2)
#define ELEC_GEAR_NUM3_YROT	(9)
#define ELEC_GEAR_NUM3_XROT	(4)

#define ELEC_GEAR_MAX1	(ELEC_GEAR_NUM1_YROT)
#define ELEC_GEAR_MAX2	(ELEC_GEAR_NUM2_YROT+ELEC_GEAR_NUM2_XROT)
#define ELEC_GEAR_MAX3	(ELEC_GEAR_NUM3_YROT+ELEC_GEAR_NUM3_XROT)
#define ELEC_GEAR_MAX	(ELEC_GEAR_MAX3)

#define ELEC_GEAR_CENTER_OFS_X	(FX32_ONE*8)
#define ELEC_GEAR_CENTER_OFS_Y	(FX32_ONE*8)
#define ELEC_GEAR_CENTER_OFS_Z	(FX32_ONE*8)


#define GEAR_ROT_DIR_LEFT	(0)		//回転が与えられたときその方向に回転する
#define GEAR_ROT_DIR_RIGHT	(1)		//回転が与えられたとき逆方向に回転する

#define GEAR_ROT_TYPE_Y	(0)			//Ｙ軸回転
#define GEAR_ROT_TYPE_X	(1)			//Ｘ軸回転

//下記3つの定義は、反時計回り回転を与えたとき、反時計回りをするギアの定義です
//2Dエディタを使用する際、
//指定回転方向と逆回転するギアの場合はROTATE_GEAR_PLUS90とROTATE_GEAR_MINUS90の使用方法を逆にします


#define GEAR_ROT_SPEED		(0x400)



typedef struct {
	int seq;							///<シーケンス保持ワーク
}EVENT_GYM_WORK;

static u8 GetBit(const u8 inBit, const int inData);

static void ChangeBit(const u8 inBit, int *outData);

//水ジム
static BOOL GMEVENT_SetGymWaterLv1(GMEVENT_CONTROL * event);
static BOOL GMEVENT_SetGymWaterLv2(GMEVENT_CONTROL * event);
static BOOL GMEVENT_SetGymWaterLv3(GMEVENT_CONTROL * event);

static void SetWaterGymButton(const u8 inWaterLv, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);

//ゴーストジム
static BOOL GMEVENT_MoveUpGymGhost(GMEVENT_CONTROL * event);
static BOOL GMEVENT_MoveDownGymGhost(GMEVENT_CONTROL * event);

//鋼ジム
static BOOL GMEVENT_MoveUDGymSteel(GMEVENT_CONTROL * event);
static BOOL GMEVENT_MoveLRGymSteel(GMEVENT_CONTROL * event);
static BOOL GMEVENT_MoveFRGymSteel(GMEVENT_CONTROL * event);

//格闘ジム
static BOOL GMEVENT_MoveWallGymCombat(GMEVENT_CONTROL * event);

//電気ジム
static BOOL GMEVENT_RotateElecGymGear(GMEVENT_CONTROL * event);

//---------------------------------------------------------------------------
/**
 * @brief	制御ビット取得
 * 
 * @param	inData			データ
 * @param	inBit			対象ビット
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static u8 GetBit(const u8 inBit, const int inData)
{
	u8 bit;
	bit = (inData>>inBit)&(0x01);
	return bit;
}

//---------------------------------------------------------------------------
/**
 * @brief	制御ビット変更
 * 
 * @param	inBit		対象ビット
 * @param	outData		データ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void ChangeBit(const u8 inBit, int *outData)
{
	(*outData)^=(0x1<<inBit);
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:ボタンチェック
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_CheckWaterGymButton(FIELDSYS_WORK *fsys)
{
	TARGET_RECT rect;
	int x,z;
	BOOL rc;
	int id;
	int list[] = {BMID_R04_B1,BMID_R04_B2,BMID_R04_B3};	//ボタン1、ボタン2、ボタン3

	//*outScrID = SCRID_HONEY_TREE;
	//自機座標取得(グリッド)
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	

	//自機のいるグリッドの矩形を作成
	MPTL_MakeTargetRect( x, z, 0, 0, 1, 1, &rect);

	rc = MPTL_CheckPluralMap3DObjInRect( fsys, list, NELEMS(list), &rect, NULL, &id);
	if(rc){
		EVENT_GYM_WORK * egw;
		GIMMICKWORK *work;
		WATER_GYM_WORK *water_gym_work;
		work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
		water_gym_work = (WATER_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_WATER_GYM);
		
		//イベントコール
		egw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GYM_WORK));
		egw->seq = 0;
		if (id == BMID_R04_B1){	//ボタン1
			FieldEvent_Call(fsys->event, GMEVENT_SetGymWaterLv3, egw);
			water_gym_work->Water = GYM_WATER_LV3;
		}else if(id == BMID_R04_B2){	//ボタン2
			FieldEvent_Call(fsys->event, GMEVENT_SetGymWaterLv2, egw);
			water_gym_work->Water = GYM_WATER_LV2;
		}else if(id == BMID_R04_B3){	//ボタン3
			FieldEvent_Call(fsys->event, GMEVENT_SetGymWaterLv1, egw);
			water_gym_work->Water = GYM_WATER_LV1;
		}else{
			GF_ASSERT(0&&"水面上昇下降エラー：OBJID不正");
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:高さ当たり判定
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inHeight	高さ
 * @param	outHit		判定結果	TRUE:ヒット	FALSE:ヒットしてない
 * 
 * @return	BOOL		TRUE:このあと通常当たり判定を行わない	FALSE:通常当たり判定を行う
 */
//---------------------------------------------------------------------------
BOOL GYM_HitCheckWaterGym(	FIELDSYS_WORK *fsys,
							const int inGridX, const int inGridZ,
							const fx32 inHeight, BOOL *outHit	)
{
	u8 attr;
	//アトリビュートを調べる
	attr = GetAttributeLSB(fsys, inGridX, inGridZ);
	if ( MATR_IsWaterHeightLv1(attr) ){
		if (inHeight != 0){
			(*outHit) = TRUE;
			return TRUE;
		}
	}else if ( MATR_IsWaterHeightLv2(attr) ){
		if (inHeight != FX32_ONE*16*2){
			(*outHit) = TRUE;
			return TRUE;
		}
	}else if ( MATR_IsWaterHeightLv3(attr) ){
		if (inHeight != FX32_ONE*16*4){
			(*outHit) = TRUE;
			return TRUE;
		}
	}
	(*outHit) = FALSE;
	return FALSE;	//通常当たり判定を実行
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:水位をLV1にする
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL	TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_SetGymWaterLv1(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);

	switch (egw->seq) {
	case 0:
		//ボタンアニメ（ボタン3を押下）
		SetWaterGymButton(GYM_WATER_LV1, fsys->field_3d_anime);
		(egw->seq) ++;
		break;
	case 1:			//水位を下降
		{
			FLD_3D_ANM_DAT_PTR anime1,anime2,anime3;
			anime1 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM1, fsys->field_3d_anime);
			anime2 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM2, fsys->field_3d_anime);
			anime3 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM3, fsys->field_3d_anime);
			if ( F3DA_IsAnimeEnd(anime1) &&
				 F3DA_IsAnimeEnd(anime2) &&
				 F3DA_IsAnimeEnd(anime3) ){
				//水面OBJを取得
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
				//y座標変更
				{
					VecFx32 vec;
					vec = M3DO_GetGlobalVec(ptr);
					vec.y -= WATER_DIF;	
					if (vec.y <= MODEL_WATER_LV1){	//セット終了
						vec.y = MODEL_WATER_LV1;
						(egw->seq) ++;
					}
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( WTAER_GYM_DATA_HRIGHT_ID, WATER_LV1, fsys->ExHeightList );
		//水位変更音停止
		Snd_SeStopBySeqNo( SE_NOMOSE_GYM_BUTTON, 0 );
		(egw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:水位をLV2にする
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL	TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_SetGymWaterLv2(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);

	switch (egw->seq) {
	case 0:	//上昇されるか、下降させるかを決定
		//ボタンアニメ（ボタン2を押下）
		SetWaterGymButton(GYM_WATER_LV2, fsys->field_3d_anime);
		(egw->seq) ++;
		break;
	case 1:
		{
			FLD_3D_ANM_DAT_PTR anime1,anime2,anime3;
			anime1 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM1, fsys->field_3d_anime);
			anime2 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM2, fsys->field_3d_anime);
			anime3 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM3, fsys->field_3d_anime);
			if ( F3DA_IsAnimeEnd(anime1) &&
				 F3DA_IsAnimeEnd(anime2) &&
				 F3DA_IsAnimeEnd(anime3) ){
				//現在の水位を取得
				//水面OBJを取得
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
				{
					VecFx32 vec;
					vec = M3DO_GetGlobalVec(ptr);
					if (vec.y == MODEL_WATER_LV1){
						(egw->seq) = 2;
					}else if(vec.y == MODEL_WATER_LV2){
						sys_FreeMemoryEz(egw);
						return TRUE;;
					}else if(vec.y == MODEL_WATER_LV3){
						(egw->seq) = 3;
					}else{
						GF_ASSERT(0);
					}
				}
			}
		}	
		break;
	case 2:			//水位を上昇
		//水面OBJを取得
		ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
		//y座標変更
		{
			VecFx32 vec;
			vec = M3DO_GetGlobalVec(ptr);
			vec.y += WATER_DIF;	
			if (vec.y >= MODEL_WATER_LV2){	//セット終了
				vec.y = MODEL_WATER_LV2;
				(egw->seq) = 4;
			}
			M3DO_SetGlobalVec(ptr, &vec);
		}
		break;
	case 3:		//水位を降下
		//水面OBJを取得
		ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
		//y座標変更
		{
			VecFx32 vec;
			vec = M3DO_GetGlobalVec(ptr);
			vec.y -= WATER_DIF;	
			if (vec.y <= MODEL_WATER_LV2){	//セット終了
				vec.y = MODEL_WATER_LV2;
				(egw->seq) = 4;
			}
			M3DO_SetGlobalVec(ptr, &vec);
		}
		break;
	case 4:	//高さセット
		EXH_SetExHeight( WTAER_GYM_DATA_HRIGHT_ID, WATER_LV2, fsys->ExHeightList );
		//水位変更音停止
		Snd_SeStopBySeqNo( SE_NOMOSE_GYM_BUTTON, 0 );
		(egw->seq) ++;
		break;
	case 5:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:水位をLV3にする
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL	TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_SetGymWaterLv3(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);

	switch (egw->seq) {
	case 0:
		//ボタンアニメ（ボタン1を押下）
		SetWaterGymButton(GYM_WATER_LV3, fsys->field_3d_anime);
		(egw->seq) ++;
		break;	
	case 1:			//水位を上昇
		{
			FLD_3D_ANM_DAT_PTR anime1,anime2,anime3;
			anime1 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM1, fsys->field_3d_anime);
			anime2 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM2, fsys->field_3d_anime);
			anime3 = F3DA_GetFld3DAnmPtrByCode(WATER_GYM_BTN_ANM3, fsys->field_3d_anime);
			if ( F3DA_IsAnimeEnd(anime1) &&
				 F3DA_IsAnimeEnd(anime2) &&
				 F3DA_IsAnimeEnd(anime3) ){
				//水面OBJを取得
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
				//y座標変更
				{
					VecFx32 vec;
					vec = M3DO_GetGlobalVec(ptr);
					vec.y += WATER_DIF;	
					if (vec.y >= MODEL_WATER_LV3){	//セット終了
						vec.y = MODEL_WATER_LV3;
						(egw->seq) ++;
					}
					M3DO_SetGlobalVec(ptr, &vec);
				}
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( WTAER_GYM_DATA_HRIGHT_ID, WATER_LV3, fsys->ExHeightList );
		//水位変更音停止
		Snd_SeStopBySeqNo( SE_NOMOSE_GYM_BUTTON, 0 );
		(egw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_SetupWaterGym(FIELDSYS_WORK *fsys)
{
	u8 water;
	M3DO_PTR ptr;
	fx32 model_water_height;
	fx32 data_height;
	BOOL reverse1,reverse2,reverse3;
	GIMMICKWORK *work;
	WATER_GYM_WORK *water_gym_work;
	
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	water_gym_work = (WATER_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_WATER_GYM);

	//水面の作成
	{
		VecFx32 vec = {FX32_ONE*16*16,0,FX32_ONE*16*16};
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_R04_W,
							&vec, NULL,
							fsys->field_3d_anime );//<水ジム水面
	}

	//拡張高さの作成
	EXH_SetUpExHeightData(	WTAER_GYM_DATA_HRIGHT_ID,
							WATER_GYM_EX_HEIGHT_X,
							WATER_GYM_EX_HEIGHT_Z,
							WATER_GYM_EX_HEIGHT_W,
							WATER_GYM_EX_HEIGHT_H,
							WATER_LV1,fsys->ExHeightList );

	//水位を取得
	water = water_gym_work->Water;
	//取得した水位を元に、
	//水の高さ、データの高さ、ボタンの押下状況をセット
	
	switch(water){
	case GYM_WATER_LV1:		//ボタン3が押されている(１段階)
		model_water_height = MODEL_WATER_LV1;
		data_height = WATER_LV1;
		reverse1 = TRUE;
		reverse2 = TRUE;
		reverse3 = FALSE;
		break;
	case GYM_WATER_LV2:		//ボタン2が押されている（２段階）
		model_water_height = MODEL_WATER_LV2;
		data_height = WATER_LV2;
		reverse1 = TRUE;
		reverse2 = FALSE;
		reverse3 = TRUE;
		break;
	case GYM_WATER_LV3:		//ボタン1が押されている（３段階）
		model_water_height = MODEL_WATER_LV3;
		data_height = WATER_LV3;
		reverse1 = FALSE;
		reverse2 = TRUE;
		reverse3 = TRUE;
		break;
	default:	//データが壊れている可能性がある（ボタン1が押されていることにしておく）
		GF_ASSERT(0&&"データが不正です");
		model_water_height = MODEL_WATER_LV1;
		data_height = WATER_LV1;
		reverse1 = TRUE;
		reverse2 = TRUE;
		reverse3 = FALSE;
	}
	
	//水面OBJを取得
	ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_R04_W);
	//モデルのy座標変更
	{
		VecFx32 vec;
		vec = M3DO_GetGlobalVec(ptr);
		vec.y = model_water_height;
		M3DO_SetGlobalVec(ptr, &vec);
	}
	//
	//高さデータの変更
	EXH_SetExHeight( WTAER_GYM_DATA_HRIGHT_ID, data_height, fsys->ExHeightList );
	
	//３種類のボタン状況セット
	{
		FLD_3D_ANM_DAT_PTR anime;
		//ボタン1
		//アニメ検索
		anime = F3DA_GetFld3DAnmPtr( BMID_R04_B1, 0, fsys->field_3d_anime );
		//制御コードセット
		F3DA_SetControlCode( anime, WATER_GYM_BTN_ANM1 );
		//リバースセット
		F3DA_SetAnimeReverseDirect( anime, reverse1 );
		//ループ回数セット
		F3DA_SetAnimeLoopMax( anime, 1 );
		//ストップフラグセット
		F3DA_SetStopFlg( anime, TRUE );	//停止
		//アニメ終端フレームにセット
		F3DA_SetLastFrame( anime );

		//ボタン2
		//アニメ検索
		anime = F3DA_GetFld3DAnmPtr( BMID_R04_B2, 0, fsys->field_3d_anime );
		//制御コードセット
		F3DA_SetControlCode( anime, WATER_GYM_BTN_ANM2 );
		//リバースセット
		F3DA_SetAnimeReverseDirect( anime, reverse2 );
		//ループ回数セット
		F3DA_SetAnimeLoopMax( anime, 1 );
		//ストップフラグセット
		F3DA_SetStopFlg( anime, TRUE );	//停止
		//アニメ終端フレームにセット
		F3DA_SetLastFrame( anime );

		//ボタン3
		//アニメ検索
		anime = F3DA_GetFld3DAnmPtr( BMID_R04_B3, 0, fsys->field_3d_anime );
		//制御コードセット
		F3DA_SetControlCode( anime, WATER_GYM_BTN_ANM3 );
		//リバースセット
		F3DA_SetAnimeReverseDirect( anime, reverse3 );
		//ループ回数セット
		F3DA_SetAnimeLoopMax( anime, 1 );
		//ストップフラグセット
		F3DA_SetStopFlg( anime, TRUE );	//停止
		//アニメ終端フレームにセット
		F3DA_SetLastFrame( anime );
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:ボタンアニメのセット
 * 
 * @param	inWaterLv			水位レベル
 * @param	field_3d_anime_ptr	アニメ管理ポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetWaterGymButton(const u8 inWaterLv, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR anime;
	int anime_a,anime_b,anime_c;
	
	if (inWaterLv == GYM_WATER_LV3){	//ボタン１
		anime_a = WATER_GYM_BTN_ANM1;
		anime_b = WATER_GYM_BTN_ANM2;
		anime_c = WATER_GYM_BTN_ANM3;
	}else if(inWaterLv == GYM_WATER_LV2){			//ボタン２
		anime_a = WATER_GYM_BTN_ANM2;
		anime_b = WATER_GYM_BTN_ANM1;
		anime_c = WATER_GYM_BTN_ANM3;
	}else if(inWaterLv == GYM_WATER_LV1){			//ボタン３
		anime_a = WATER_GYM_BTN_ANM3;
		anime_b = WATER_GYM_BTN_ANM1;
		anime_c = WATER_GYM_BTN_ANM2;
	}else{
		GF_ASSERT(0);
	}
	anime = F3DA_GetFld3DAnmPtrByCode(anime_a, field_3d_anime_ptr);
	F3DA_SetAnimeReverseDirect(anime, FALSE);
	F3DA_SetStartFrame(anime);
	F3DA_SetStopFlg(anime, FALSE);
	F3DA_MoveAnime(anime);
		
	anime = F3DA_GetFld3DAnmPtrByCode(anime_b, field_3d_anime_ptr);
	F3DA_SetAnimeReverseDirect(anime, TRUE);
	F3DA_SetStartFrame(anime);
	F3DA_SetStopFlg(anime, FALSE);
	F3DA_MoveAnime(anime);

	anime = F3DA_GetFld3DAnmPtrByCode(anime_c, field_3d_anime_ptr);
	F3DA_SetAnimeReverseDirect(anime, TRUE);
	F3DA_SetStartFrame(anime);
	F3DA_SetStopFlg(anime, FALSE);
	F3DA_MoveAnime(anime);

	//水量変更音
	Snd_SePlay( SE_NOMOSE_GYM_BUTTON );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//ゴーストジム

//---------------------------------------------------------------------------
/**
 * @brief	ゴーストジム:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_SetupGhostGym(FIELDSYS_WORK *fsys)
{
	u8 lift;
	M3DO_PTR ptr;
	fx32 model_lift_height;
	fx32 data_height;
	GIMMICKWORK *work;
	GHOST_GYM_WORK *ghost_gym_work;
	
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	ghost_gym_work = (GHOST_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_GHOST_GYM);

	//リフトの作成
	{
		VecFx32 vec = {FX32_ONE*(16*9+8),0,FX32_ONE*(16*13+8)};
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_LIFT_BASE01,
							&vec, NULL,
							fsys->field_3d_anime );//<リフト
	}
	
	//拡張高さの作成
	EXH_SetUpExHeightData(	GHOST_GYM_DATA_HRIGHT_ID,
							GHOST_GYM_EX_HEIGHT_X,
							GHOST_GYM_EX_HEIGHT_Z,
							GHOST_GYM_EX_HEIGHT_W,
							GHOST_GYM_EX_HEIGHT_H,
							GHOST_LIFT_LV1,fsys->ExHeightList );

	//リフトの位置を取得
	lift = ghost_gym_work->Lift;
	
	switch(lift){
	case GYM_GHOST_LIFT_LV1:		//下フロア
		model_lift_height = MODEL_GHOST_LIFT_LV1;
		data_height = GHOST_LIFT_LV1;
		break;
	case GYM_GHOST_LIFT_LV2:		//上フロア
		model_lift_height = MODEL_GHOST_LIFT_LV2;
		data_height = GHOST_LIFT_LV2;
		break;
	default:	//データが壊れている可能性がある
		GF_ASSERT(0 && "データが不正です");
		model_lift_height = MODEL_GHOST_LIFT_LV1;
		data_height = GHOST_LIFT_LV1;
	}
	
	//リフトOBJを取得
	ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
	//モデルのy座標変更
	{
		VecFx32 vec;
		vec = M3DO_GetGlobalVec(ptr);
		vec.y = model_lift_height;
		M3DO_SetGlobalVec(ptr, &vec);
	}
	//
	//高さデータの変更
	EXH_SetExHeight( GHOST_GYM_DATA_HRIGHT_ID, data_height, fsys->ExHeightList );
}

//---------------------------------------------------------------------------
/**
 * @brief	ゴーストジム:リフト移動
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_MoveGhostGymLift(FIELDSYS_WORK *fsys)
{
	EVENT_GYM_WORK * egw;
	
	//イベントコール
	egw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GYM_WORK));
	egw->seq = 0;

	//自機のy座標からコールするイベントを切り替える
	{
		VecFx32 vec;
		GIMMICKWORK *work;
		GHOST_GYM_WORK *ghost_gym_work;
		work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
		ghost_gym_work = (GHOST_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_GHOST_GYM);
		Player_VecPosGet( fsys->player, &vec );
		if (vec.y == GHOST_LIFT_LV1){
			FieldEvent_Call(fsys->event, GMEVENT_MoveUpGymGhost, egw);
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;
		}else{
			FieldEvent_Call(fsys->event, GMEVENT_MoveDownGymGhost, egw);
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV1;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	ゴーストジム:リフトを上げる
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveUpGymGhost(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);

	switch (egw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//自機の高さ自動取得をオフ

		//リフト音再生
		Snd_SePlay( SEQ_SE_DP_ELEBETA );
		(egw->seq) ++;
		break;
	case 1:	//リフトを上昇
		{
			//リフトOBJを取得
			ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			//y座標変更
			{
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				vec.y += GHOST_LIFT_DIF;

				if (vec.y >= MODEL_GHOST_LIFT_LV2){	//セット終了
					vec.y = MODEL_GHOST_LIFT_LV2;
					//リフト音停止
					Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
					(egw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//自機高さ変更
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( GHOST_GYM_DATA_HRIGHT_ID, GHOST_LIFT_LV2, fsys->ExHeightList );
		//自機の高さ自動取得をオン
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );

		//リフト移動終了音
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(egw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	ゴーストジム:リフトを下げる
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveDownGymGhost(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);

	switch (egw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//自機の高さ自動取得をオフ

		//リフト音再生
		Snd_SePlay( SEQ_SE_DP_ELEBETA );
		(egw->seq)	++;
		break;
	case 1:	//リフトを下降
		{
			//リフトOBJを取得
			ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			//y座標変更
			{
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				vec.y -= GHOST_LIFT_DIF;
				
				if (vec.y <= MODEL_GHOST_LIFT_LV1){	//セット終了
					vec.y = MODEL_GHOST_LIFT_LV1;
					//リフト音停止
					Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
					(egw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//自機高さ変更
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//高さセット
		EXH_SetExHeight( GHOST_GYM_DATA_HRIGHT_ID, GHOST_LIFT_LV1, fsys->ExHeightList );
		//自機の高さ自動取得をオン
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );

		//リフト移動終了音
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(egw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

//鋼ジム
static const u8 SteelGymHitTbl[4][1024] = 
{
	//#gym02_attr_01
	{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	},
	//#gym02_attr_02
	{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,
1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,
1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,
1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	},
	//#gym02_attr_03
	{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,
1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,0,0,0,1,
1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,0,0,0,1,
1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,0,0,0,1,
1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1,
1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,0,0,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,
1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	},
	//#gym02_attr_04
	{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,
1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,
1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	},
};

typedef enum {
	STEEL_FLOOR_1F = 0,
	STEEL_FLOOR_2F,
	STEEL_FLOOR_3F,
	STEEL_FLOOR_4F,
}STEEL_FLOOR;

typedef enum { 
	MOVE_DIR_UP,
	MOVE_DIR_DOWN,
	MOVE_DIR_REAR,
	MOVE_DIR_FRONT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_LEFT,
}MOVE_DIR;

typedef struct LIFT_POSITION_tag
{
	u8 GridX;
	u8 Height;
	u8 GridZ;
}LIFT_POSITION;

typedef struct STEEL_GYM_TEMP_WORK_tag
{
	FIELDSYS_WORK *fsys;
	int Floor2F;
	int Floor3F;
	int Floor4F;
	u8 LiftHeight[STEEL_LIFT_MAX];	//フロア識別用バッファ　0:1F 1:2F 2:3F 3:4F
	u8 LiftEntryIdx[STEEL_LIFT_MAX];		//拡張配置モデル登録インデックス
	LIFT_POSITION	LiftPos[STEEL_LIFT_MAX];
	int ObjID[STEEL_LIFT_MAX];
	u8 ListIdx;
	fx32 Dst;
	MOVE_DIR MoveDir;
}STEEL_GYM_TEMP_WORK;

typedef struct STEEL_LIFT_INFO_tag
{
	int ObjID;
	LIFT_POSITION	BeforePos;
	LIFT_POSITION	AffterPos;
	u8 BeforeHeight;
	u8 AffterHeight;
	u16 dummy;	
}STEEL_LIFT_INFO;

static const STEEL_LIFT_INFO LiftInfo[STEEL_LIFT_MAX] = {
	{ BMID_LIFT_BASE05, {16,  0,  9},{16, 30,  9}, STEEL_FLOOR_1F, STEEL_FLOOR_4F, 0 },
	{ BMID_LIFT_BASE04, {11,  0, 13},{11, 10, 13}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 0 },
	{ BMID_LIFT_BASE04, {15,  0, 13},{15, 10, 13}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 0 },
	{ BMID_LIFT_BASE04, {19,  0, 13},{19, 10, 13}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 0 },
	{ BMID_LIFT_BASE04, {24,  0, 13},{24, 10, 13}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 0 },
	{ BMID_LIFT_BASE04, {21,  0, 22},{21, 10, 22}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 0 },
	
	{ BMID_LIFT_BASE04, {25,  0,  9},{25, 10,  9}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 1 },
	{ BMID_LIFT_BASE04, {25,  0, 22},{25, 10, 22}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 1 },
	{ BMID_LIFT_BASE04, {29,  0, 22},{29, 10, 22}, STEEL_FLOOR_1F, STEEL_FLOOR_2F, 1 },
	{ BMID_LIFT_BASE04, { 5, 10, 26},{ 5, 20, 26}, STEEL_FLOOR_2F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE03, {11, 10, 22},{18, 10, 22}, STEEL_FLOOR_2F, STEEL_FLOOR_2F, 1 } ,
	
	{ BMID_LIFT_BASE04, {29, 10,  9},{29, 20,  9}, STEEL_FLOOR_2F, STEEL_FLOOR_3F, 1 },
	{ BMID_LIFT_BASE03, {10, 20,  4},{14, 20,  4}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE03, {19, 20,  4},{22, 20,  4}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE03, { 7, 20, 12},{22, 20, 12}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE03, { 9, 20, 26},{21, 20, 26}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE02, { 2, 20, 19},{ 2, 20, 22}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 1 },
	{ BMID_LIFT_BASE02, {26, 20, 16},{26, 20, 22}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 0 },
	{ BMID_LIFT_BASE02, {29, 20, 16},{29, 20, 22}, STEEL_FLOOR_3F, STEEL_FLOOR_3F, 1 },

	{ BMID_LIFT_BASE05, { 7,  0,  9},{ 7, 30,  9}, STEEL_FLOOR_1F, STEEL_FLOOR_4F, 1 },
	{ BMID_LIFT_BASE03, {19, 30,  4},{26, 30,  4}, STEEL_FLOOR_4F, STEEL_FLOOR_4F, 0 },
	{ BMID_LIFT_BASE03, { 5, 30, 26},{26, 30, 26}, STEEL_FLOOR_4F, STEEL_FLOOR_4F, 1 },
	{ BMID_LIFT_BASE02, {29, 30,  7},{29, 30, 23}, STEEL_FLOOR_4F, STEEL_FLOOR_4F, 0 },
	{ BMID_LIFT_BASE02, { 2, 30, 12},{ 2, 30, 23}, STEEL_FLOOR_4F, STEEL_FLOOR_4F, 1 },
};

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトのバニッシュ
 * 
 * @param	inSteelTemp		鋼ジムテンポラリワーク
 * @param	inInvisible			バニッシュフラグ
 * @param	inFloor				対象フロア
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void InvisibleLift(const STEEL_GYM_TEMP_WORK *inSteelTemp,
						const BOOL inInvisible,
						const STEEL_FLOOR inFloor)
{
	M3DO_PTR obj_ptr;
	int i;
	for(i=0;i<STEEL_LIFT_MAX;i++){
		if (inSteelTemp->LiftHeight[i] == inFloor){
			obj_ptr = M3DO_GetMap3DObjData(	inSteelTemp->fsys->Map3DObjExp,
											inSteelTemp->LiftEntryIdx[i] );
			M3DO_SetVanish(obj_ptr, inInvisible);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトヒット判定
 * 
 * @param	inSteelTemp		鋼ジムテンポラリワーク
 * 
 * @return	u8					ヒットしたリフトインデックス
 */
//---------------------------------------------------------------------------
static u8 CheckLiftHit(STEEL_GYM_TEMP_WORK *inSteelTemp)
{
	u8 i;
	u8 height;
	u8 grid_x;
	u8 grid_z;
	VecFx32 vec;
	Player_VecPosGet( inSteelTemp->fsys->player, &vec );
	//自機の高さ取得
	height = vec.y/ONE_HEIGHT;
	//自機のグリッド座標を取得
	grid_x = vec.x/ONE_GRID;
	grid_z = vec.z/ONE_GRID;
	
	for(i=0;i<STEEL_LIFT_MAX;i++){
		//高さ比較
		if (inSteelTemp->LiftPos[i].Height == height){
			//XZ比較
			if ( (inSteelTemp->LiftPos[i].GridX == grid_x) &&
					(inSteelTemp->LiftPos[i].GridZ == grid_z) ){
				return i;
			}
		}
	}
	return STEEL_LIFT_MAX;
}
#if 0
//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフト制御ビット取得
 * 
 * @param	inSteelGumWork		鋼ジムワーク
 * @param	inBit				対象ビット
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static u8 GetLiftPosBit(const STEEL_GYM_WORK *inSteelGymWork, const u8 inBit)
{
	u8 bit;
	bit = (inSteelGymWork->LiftPosBit>>inBit)&(0x01);
	return bit;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフト制御ビットセット
 * 
 * @param	outSteelGymWork		鋼ジムワーク
 * @param	inBit				対象ビット
 * @param	inVal				値
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetLiftPosBit(STEEL_GYM_WORK *outSteelGymWork, const u8 inBit, const u8 inVal)
{
	int u,m,d;
	GF_ASSERT((inVal<=1)&&"2以上の値がセットされています");
	
	u = outSteelGymWork->LiftPosBit & (0xffffffff<<(inBit+1));
	d = outSteelGymWork->LiftPosBit & (0xffffffff>>(32-inBit));
	m = inVal<<inBit;
	outSteelGymWork->LiftPosBit = (u|m|d);
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフト制御ビット変更
 * 
 * @param	outSteelGymWork		鋼ジムワーク
 * @param	inBit				対象ビット
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void ChangeLiftPosBit(STEEL_GYM_WORK *outSteelGymWork, const u8 inBit)
{
	outSteelGymWork->LiftPosBit^=(0x1<<inBit);
}
#endif
//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフト移動イベントコール
 * 
 * @param	ioSteelTemp		鋼ジムテンポラリワーク
 * @param	inIdx			リフトインデックス
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CallLiftMoveEvent(STEEL_GYM_TEMP_WORK *ioSteelTemp, const u8 inIdx)
{
	int lift_type;
	u8 bit;
	EVENT_GYM_WORK * egw;
	
	GIMMICKWORK *work;
	STEEL_GYM_WORK *steel_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(ioSteelTemp->fsys));
	steel_gym_work = (STEEL_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_STEEL_GYM);
	
	egw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GYM_WORK));
	egw->seq = 0;

	ioSteelTemp->ListIdx = inIdx;	
	
	//対象リフトのタイプを取得
	lift_type = ioSteelTemp->ObjID[inIdx];
	//対象リフトの位置を取得
	bit = GetBit(inIdx, steel_gym_work->LiftPosBit);
	///bit = GetLiftPosBit(steel_gym_work, inIdx);
	//位置更新
	///ChangeLiftPosBit(steel_gym_work, inIdx);
	ChangeBit(inIdx,&steel_gym_work->LiftPosBit);
	//移動イベントをコール
	if (lift_type == BMID_LIFT_BASE03){	//左右
		if (bit){		//左へ
			ioSteelTemp->MoveDir = MOVE_DIR_LEFT;
			ioSteelTemp->Dst = LiftInfo[inIdx].BeforePos.GridX*ONE_GRID+STEEL_CENTER_OFS;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].BeforePos;		
		}else{			//右へ
			ioSteelTemp->MoveDir = MOVE_DIR_RIGHT;
			ioSteelTemp->Dst = LiftInfo[inIdx].AffterPos.GridX*ONE_GRID+STEEL_CENTER_OFS;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].AffterPos;
		}
		FieldEvent_Set(ioSteelTemp->fsys, GMEVENT_MoveLRGymSteel, egw);
	}else if (lift_type == BMID_LIFT_BASE02) {			//手前奥
		if (bit){		//奥へ
			ioSteelTemp->MoveDir = MOVE_DIR_REAR;
			ioSteelTemp->Dst = LiftInfo[inIdx].BeforePos.GridZ*ONE_GRID+STEEL_CENTER_OFS;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].BeforePos;
		}else{			//手前へ
			ioSteelTemp->MoveDir = MOVE_DIR_FRONT;
			ioSteelTemp->Dst = LiftInfo[inIdx].AffterPos.GridZ*ONE_GRID+STEEL_CENTER_OFS;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].AffterPos;
		}
		FieldEvent_Set(ioSteelTemp->fsys, GMEVENT_MoveFRGymSteel, egw);
	}else{				//上下
		if (bit){		//下へ
			ioSteelTemp->MoveDir = MOVE_DIR_DOWN;
			ioSteelTemp->Dst = LiftInfo[inIdx].BeforePos.Height*ONE_HEIGHT;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].BeforePos;
			//高さコード更新	(下り時は先に行ってしまう)
			ioSteelTemp->LiftHeight[inIdx] =
							LiftInfo[inIdx].BeforeHeight;
		}else{			//上へ
			ioSteelTemp->MoveDir = MOVE_DIR_UP;
			ioSteelTemp->Dst = LiftInfo[inIdx].AffterPos.Height*ONE_HEIGHT;
			ioSteelTemp->LiftPos[inIdx] = LiftInfo[inIdx].AffterPos;
		}
		FieldEvent_Set(ioSteelTemp->fsys, GMEVENT_MoveUDGymSteel, egw);	
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:床のバニッシュ
 * 
 * @param	steel_temp		鋼ジムテンポラリワーク
 * @param	inHeight		高さ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetLiftFloorVanish(STEEL_GYM_TEMP_WORK *steel_temp, const fx32 inHeight)
{
	M3DO_PTR obj_ptr2F;
	M3DO_PTR obj_ptr3F;
	M3DO_PTR obj_ptr4F;
	
	//高さに応じて床をバニッシュ
	obj_ptr2F = M3DO_GetMap3DObjData(steel_temp->fsys->Map3DObjExp, steel_temp->Floor2F);
	obj_ptr3F = M3DO_GetMap3DObjData(steel_temp->fsys->Map3DObjExp, steel_temp->Floor3F);
	obj_ptr4F = M3DO_GetMap3DObjData(steel_temp->fsys->Map3DObjExp, steel_temp->Floor4F);

	if (inHeight>=ONE_HEIGHT*(FLOOR_MARGIN-FLOOR_DISP_START_VAL)){	//2F
		M3DO_SetVanish(obj_ptr2F, FALSE);//表示
		//STEEL_FLOOR_2Fのリフトを表示
		InvisibleLift(steel_temp, FALSE, STEEL_FLOOR_2F);
	}else{
		M3DO_SetVanish(obj_ptr2F, TRUE);//非表示
		//STEEL_FLOOR_2Fのリフトを非表示
		InvisibleLift(steel_temp, TRUE, STEEL_FLOOR_2F);
	}
	
	if (inHeight>=ONE_HEIGHT*(FLOOR_MARGIN*2-FLOOR_DISP_START_VAL)){	//3F
		M3DO_SetVanish(obj_ptr3F, FALSE);//表示
		//STEEL_FLOOR_3Fのリフトを表示
		InvisibleLift(steel_temp, FALSE, STEEL_FLOOR_3F);
	}else{
		M3DO_SetVanish(obj_ptr3F, TRUE);//非表示
		//STEEL_FLOOR_3Fのリフトを表示
		InvisibleLift(steel_temp, TRUE, STEEL_FLOOR_3F);
	}
	
	if (inHeight>=ONE_HEIGHT*(FLOOR_MARGIN*3-FLOOR_DISP_START_VAL)){	//4F
		M3DO_SetVanish(obj_ptr4F, FALSE);//表示
		//STEEL_FLOOR_4Fのリフトを表示
		InvisibleLift(steel_temp, FALSE, STEEL_FLOOR_4F);
	}else{
		M3DO_SetVanish(obj_ptr4F, TRUE);//非表示
		//STEEL_FLOOR_4Fのリフトを表示
		InvisibleLift(steel_temp, TRUE, STEEL_FLOOR_4F);
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトの上下移動
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveUDGymSteel(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);
	STEEL_GYM_TEMP_WORK *steel_temp;

	steel_temp = (STEEL_GYM_TEMP_WORK *)fsys->fldmap->Work;
	
	switch (egw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//自機の高さ自動取得をオフ

		//リフト音再生
		Snd_SePlay( SEQ_SE_DP_ELEBETA );
		(egw->seq)	++;
		break;
	case 1:	//リフトを移動
		{
			int entry;
			//リフトOBJを取得
			entry = steel_temp->LiftEntryIdx[steel_temp->ListIdx];
			ptr = M3DO_GetMap3DObjData(fsys->Map3DObjExp, entry);
			//y座標変更
			{
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				if (steel_temp->MoveDir == MOVE_DIR_UP){
					vec.y += STEEL_UD_LIFT_DIF;
					if (vec.y >= steel_temp->Dst){	//セット終了
						vec.y = steel_temp->Dst;
						//高さコード更新
						steel_temp->LiftHeight[steel_temp->ListIdx] =
							LiftInfo[steel_temp->ListIdx].AffterHeight;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}
				}else if (steel_temp->MoveDir == MOVE_DIR_DOWN){
					vec.y -= STEEL_UD_LIFT_DIF;
					if (vec.y <= steel_temp->Dst){	//セット終了
						vec.y = steel_temp->Dst;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}
				}else{
					GF_ASSERT(0&&"方向指定エラー");
				}
				
				Player_VecPosYSet( fsys->player, vec.y );	//自機高さ変更
				M3DO_SetGlobalVec(ptr, &vec);

				SetLiftFloorVanish(steel_temp, vec.y);
			}
		}
		break;
	case 2:
		//自機の高さ自動取得をオン
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );
		//リフト移動終了音
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(egw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトを左右に移動
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveLRGymSteel(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);
	STEEL_GYM_TEMP_WORK *steel_temp;

	steel_temp = (STEEL_GYM_TEMP_WORK *)fsys->fldmap->Work;
	fop = Player_FieldOBJGet( fsys->player );	
	switch (egw->seq) {
	case 0:
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//出来る。動きをポーズ
			//リフト音再生
			Snd_SePlay( SEQ_SE_DP_ELEBETA );
			(egw->seq)	++;
		}
		break;
	case 1:	//リフトを移動
		{
			int entry;
			//リフトOBJを取得
			entry = steel_temp->LiftEntryIdx[steel_temp->ListIdx];
			ptr = M3DO_GetMap3DObjData(fsys->Map3DObjExp, entry);
			//x座標変更
			{
				VecFx32 vec,player_vec;
				vec = M3DO_GetGlobalVec(ptr);
				Player_VecPosGet( fsys->player, &player_vec );
				vec.x = player_vec.x;
				if (steel_temp->MoveDir == MOVE_DIR_RIGHT){
					if (vec.x >= steel_temp->Dst){	//セット終了
						vec.x = steel_temp->Dst;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}else{
						if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
							FieldOBJ_AcmdSet(fop,AC_WALK_R_2F);	//自機右移動
						}
					}
				}else if (steel_temp->MoveDir == MOVE_DIR_LEFT){
					if (vec.x <= steel_temp->Dst){	//セット終了
						vec.x = steel_temp->Dst;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}else{
						if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
							FieldOBJ_AcmdSet(fop,AC_WALK_L_2F);	//自機左移動
						}
					}
				}else{
					GF_ASSERT(0&&"方向指定エラー");
				}
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//出来る。ポーズ解除
			(egw->seq) ++;
		}
	case 3:
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了
			//リフト移動終了音
			Snd_SePlay( SE_YOSUGA_GYM_LIFT );
			(egw->seq) ++;
		}
		break;
	case 4:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトを手前奥に移動
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveFRGymSteel(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);
	STEEL_GYM_TEMP_WORK *steel_temp;

	steel_temp = (STEEL_GYM_TEMP_WORK *)fsys->fldmap->Work;
	fop = Player_FieldOBJGet( fsys->player );	
	switch (egw->seq) {
	case 0:
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_ON);	//出来る。動きをポーズ
			//リフト音再生
			Snd_SePlay( SEQ_SE_DP_ELEBETA );
			(egw->seq)	++;
		}
		break;
	case 1:	//リフトを移動
		{
			int entry;
			//リフトOBJを取得
			entry = steel_temp->LiftEntryIdx[steel_temp->ListIdx];
			ptr = M3DO_GetMap3DObjData(fsys->Map3DObjExp, entry);
			//z座標変更
			{
				VecFx32 vec,player_vec;
				vec = M3DO_GetGlobalVec(ptr);
				Player_VecPosGet( fsys->player, &player_vec );
				vec.z = player_vec.z;
				if (steel_temp->MoveDir == MOVE_DIR_FRONT){
					if (vec.z >= steel_temp->Dst){	//セット終了
						vec.z = steel_temp->Dst;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}else{
						if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
							FieldOBJ_AcmdSet(fop,AC_WALK_D_2F);	//自機手前移動
						}
					}
				}else if (steel_temp->MoveDir == MOVE_DIR_REAR){
					if (vec.z <= steel_temp->Dst){	//セット終了
						vec.z = steel_temp->Dst;
						//リフト音停止
						Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
						(egw->seq) ++;
					}else{
						if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
							FieldOBJ_AcmdSet(fop,AC_WALK_U_2F);	//自機奥移動
						}
					}
				}else{
					GF_ASSERT(0&&"方向指定エラー");
				}
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:
		if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?
			FieldOBJ_AcmdSet(fop,AC_ANM_PAUSE_OFF);	//出来る。ポーズ解除
			(egw->seq) ++;
		}
		break;
	case 3:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
				FieldOBJ_AcmdEnd(fop); //アニメ終了
				//リフト移動終了音
				Snd_SePlay( SE_YOSUGA_GYM_LIFT );
				(egw->seq) ++;
			}
		}
		break;
	case 4:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_SetupSteelGym(FIELDSYS_WORK *fsys)
{
	STEEL_GYM_TEMP_WORK *steel_temp;
	GIMMICKWORK *work;
	STEEL_GYM_WORK *steel_gym_work;
	
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	steel_gym_work = (STEEL_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_STEEL_GYM);

	//鋼ジム専用ワークをアロケートして、フィールドマップ汎用ワークポインタにあてる
	fsys->fldmap->Work = sys_AllocMemory(HEAPID_FIELD, sizeof(STEEL_GYM_TEMP_WORK));
	steel_temp = fsys->fldmap->Work;

	steel_temp->fsys = fsys;
	//床（2F～4F）の作成
	{
		VecFx32 vec = {FX32_ONE*(16*16),0,FX32_ONE*(16*16)};
		vec.y = ONE_HEIGHT*FLOOR_MARGIN;
		steel_temp->Floor2F = M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_GYM02_2F,
							&vec,NULL,
							fsys->field_3d_anime );
		vec.y = ONE_HEIGHT*FLOOR_MARGIN*2;
		steel_temp->Floor3F = M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_GYM02_3F,
							&vec,NULL,
							fsys->field_3d_anime );
		vec.y = ONE_HEIGHT*FLOOR_MARGIN*3;
		steel_temp->Floor4F = M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_GYM02_4F,
							&vec,NULL,
							fsys->field_3d_anime );
	}
	//リフトの作成(24個)
	{
		VecFx32 vec;
		int i;
		for(i=0;i<STEEL_LIFT_MAX;i++){
			if (/*GetLiftPosBit(steel_gym_work,i)*/GetBit(i, steel_gym_work->LiftPosBit)){
				vec.x = ONE_GRID*LiftInfo[i].AffterPos.GridX;
				vec.y = ONE_HEIGHT*LiftInfo[i].AffterPos.Height;
				vec.z = ONE_GRID*LiftInfo[i].AffterPos.GridZ;
				steel_temp->LiftPos[i] = LiftInfo[i].AffterPos;
				steel_temp->LiftHeight[i] = LiftInfo[i].AffterHeight;
			}else{
				vec.x = ONE_GRID*LiftInfo[i].BeforePos.GridX;
				vec.y = ONE_HEIGHT*LiftInfo[i].BeforePos.Height;
				vec.z = ONE_GRID*LiftInfo[i].BeforePos.GridZ;
				steel_temp->LiftPos[i] = LiftInfo[i].BeforePos;
				steel_temp->LiftHeight[i] = LiftInfo[i].BeforeHeight;
			}
			vec.x+=STEEL_CENTER_OFS;
			vec.z+=STEEL_CENTER_OFS;
			steel_temp->LiftEntryIdx[i] = 
				M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
									fsys->MapResource,
									LiftInfo[i].ObjID,
									&vec, NULL,
									fsys->field_3d_anime );//<リフト

			steel_temp->ObjID[i] = LiftInfo[i].ObjID;
		}
	}

	//バニッシュセット
	{
		VecFx32 player_vec;
		//自機の高さを取得
		Player_VecPosGet( fsys->player, &player_vec );
		SetLiftFloorVanish(steel_temp, player_vec.y);
	}
	
	//クリップセット
	GFC_SetCameraClip(FX32_ONE * 100,FX32_ONE * 1700, fsys->camera_ptr);
	
	//フォグセット
	SetFogData(fsys->fog_data, FOG_SYS_ALL,
			TRUE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x0200, STEEL_FOG_OFS);
	
	SetFogColor(fsys->fog_data, FOG_SYS_ALL, GX_RGB(0,0,0), 0);
	{
		int i;
		char fog_tbl[32];
		for(i=0;i<32;i++){
			fog_tbl[i] = i*(STEEL_FOG_MAX/32);
		}
		SetFogTbl(fsys->fog_data, fog_tbl);
	}

}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:リフトチェック
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	BOOL	TRUE:リフトあり		FALSE:リフト無し
 */
//---------------------------------------------------------------------------
BOOL GYM_CheckSteelLift(FIELDSYS_WORK *fsys)
{
	//リフトヒットチェック
	u8 idx;
	STEEL_GYM_TEMP_WORK *steel_temp;

	//ギミックワークを見る
	{
		int id;
		GIMMICKWORK *work;
		
		//ギミックワーク取得
		work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
		//ギミックコードを取得
		id = GIMMICKWORK_GetAssignID(work);

		if (id != FLD_GIMMICK_STEEL_GYM){
			return FALSE;					//鋼ジムギミック無し
		}
	}

	steel_temp = (STEEL_GYM_TEMP_WORK *)fsys->fldmap->Work;
	if (steel_temp == NULL){
		return FALSE;
	}
	idx = CheckLiftHit(steel_temp);
	if (idx != STEEL_LIFT_MAX){
		//ヒットしたので処理
		//リフトの位置とリフトタイプで、イベント分岐
		CallLiftMoveEvent(steel_temp, idx);
		return TRUE;
	}
	
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:終了処理
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_EndSteelGym(FIELDSYS_WORK *fsys)
{
	STEEL_GYM_TEMP_WORK *steel_temp;
	steel_temp = (STEEL_GYM_TEMP_WORK *)fsys->fldmap->Work;
	sys_FreeMemoryEz(steel_temp);
	fsys->fldmap->Work = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:当たり判定
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inHeight	高さ
 * @param	outHit		判定結果	TRUE:ヒット	FALSE:ヒットしてない
 * 
 * @return	BOOL		TRUE:このあと通常当たり判定を行わない	FALSE:通常当たり判定を行う
 */
//---------------------------------------------------------------------------
BOOL GYM_HitCheckSteelGym(	FIELDSYS_WORK *fsys,
							const int inGridX, const int inGridZ,
							const fx32 inHeight, BOOL *outHit	)
{
	u8 floor;
	const u8 *tbl;
	int index;
	//階層を決定
	floor = (inHeight/ONE_HEIGHT)/FLOOR_MARGIN;
	GF_ASSERT(floor<=3&&"階層エラー");
	
	tbl = SteelGymHitTbl[floor];
	index = inGridX+inGridZ*32;
	GF_ASSERT(index<1024&&"インデックスエラー");
	(*outHit) = tbl[index];

	return TRUE;	//通常当たり判定は行わない
}

//////////////////////////////////////////////////////////////////////////////////////////

//格闘ジム
typedef struct COMBAT_HIT_RECT_tag
{
	u8 X;
	u8 W;
}COMBAT_HIT_RECT;

typedef struct COMBAT_GYM_TEMP_WORK_tag
{
	FIELDSYS_WORK *fsys;
	u8 WallEntryIdx[COMBAT_WALL_MAX];		//拡張配置モデル登録インデックス
///	int ObjID[COMBAT_WALL_MAX];
	u8 WallPos[COMBAT_WALL_MAX];
	u8 ListIdx;
	fx32 Dst;
	MOVE_DIR MoveDir;
	const COMBAT_HIT_RECT	* HitRect[COMBAT_WALL_MAX];
}COMBAT_GYM_TEMP_WORK;

typedef struct COMBAT_WALL_INFO_tag
{
	int ObjID;
	u8 BaseZ;		//配置されるZ座標
	u8 BeforeX;		//移動前X座標(左時)
	u8 AffterX;		//移動後X座標（右時）
	u8 dummy;	
}COMBAT_WALL_INFO;

typedef struct COMBAT_WALL_POS_INFO_tag
{
	u8 GridX;	//X座標
	u8 GridZ;	//Z座標
	u8 Bit;		//発動条件	0:左から押せる　1右から押せる
	u8 WallNo;	//しきり番号
}COMBAT_WALL_POS_INFO;

typedef struct COMBAT_WALL_HIT_tag
{
	COMBAT_HIT_RECT BeforeRect[2];
	COMBAT_HIT_RECT AffterRect[2];
}COMBAT_WALL_HIT;

//しきり情報
static const COMBAT_WALL_INFO WallInfo[COMBAT_WALL_MAX] = {
	{ BMID_GYM_WALL06,  9,  9, 10, 0 },
	{ BMID_GYM_WALL02, 10,  3,  4, 0 },
	{ BMID_GYM_WALL02, 10, 11, 12, 1 },
	{ BMID_GYM_WALL04, 10, 17, 18, 1 },
	{ BMID_GYM_WALL05, 12,  1,  5, 1 },
	{ BMID_GYM_WALL01, 13, 16, 20, 0 },
	{ BMID_GYM_WALL07, 14, 19, 20, 0 },
	{ BMID_GYM_WALL06, 16,  4,  7, 1 },
	{ BMID_GYM_WALL06, 16, 16, 17, 0 },
	{ BMID_GYM_WALL05, 18,  1,  5, 1 },
	{ BMID_GYM_WALL07, 19, 19, 20, 0 },
	{ BMID_GYM_WALL03, 20,  3,  8, 1 },
};

//しきり押し場所情報
static const COMBAT_WALL_POS_INFO WallPosInfo[COMBAT_WALL_POS_MAX] = {
	{12, 20, 1, WALLNO_12},
	{ 2, 20, 0, WALLNO_12},
	{18, 19, 0, WALLNO_11},
	{ 9, 18, 1, WALLNO_10},
	{21, 16, 1, WALLNO_9},
	{15, 16, 0, WALLNO_9},
	{11, 16, 1, WALLNO_8},
	{18, 14, 0, WALLNO_7},
	{15, 13, 0, WALLNO_6},
	{ 9, 12, 1, WALLNO_5},
	{22, 10, 1, WALLNO_4},
	{16, 10, 1, WALLNO_3},
	{ 2, 10, 0, WALLNO_2},
	{ 8,  9, 0, WALLNO_1},
};

//しきり当たり判定
static const COMBAT_WALL_HIT WallHitInfo[COMBAT_WALL_MAX] = {
	{ {{ 9, 2}, {12, 1}}, {{10, 2}, {13, 1}} },
	{ {{ 3, 1}, { 5, 2}}, {{ 4, 1}, { 6, 2}} },
	{ {{11, 1}, {13, 2}}, {{12, 1}, {14, 2}} },
	{ {{18, 1}, {20, 1}}, {{19, 1}, {21, 1}} },
	{ {{ 4, 1}, { 0, 0}}, {{ 5, 4}, { 0, 0}} },
	{ {{16, 4}, { 0, 0}}, {{20, 1}, { 0, 0}} },
	{ {{19, 4}, { 0, 0}}, {{22, 1}, { 0, 0}} },
	{ {{ 4, 2}, { 7, 1}}, {{ 7, 2}, {10, 1}} },
	{ {{16, 2}, {19, 1}}, {{17, 2}, {20, 1}} },
	{ {{ 4, 1}, { 0, 0}}, {{ 5, 4}, { 0, 0}} },
	{ {{19, 4}, { 0, 0}}, {{22, 1}, { 0, 0}} },
	{ {{ 3, 4}, { 0, 0}}, {{ 8, 4}, { 0, 0}} },
};

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:しきりプッシュ判定
 * 
 * @param	inCombatTemp		格闘ジムテンポラリワーク
 * 
 * @return	u8					ヒットしたリフトインデックス
 */
//---------------------------------------------------------------------------
static u8 CheckWallPush(COMBAT_GYM_TEMP_WORK *inCombatTemp, const u8 inDir)
{
	u8 i;
	u8 dir;
	u8 check_x;
	u8 grid_x;
	u8 grid_z;
	VecFx32 vec;
	Player_VecPosGet( inCombatTemp->fsys->player, &vec );
	//自機のグリッド座標を取得
	grid_x = vec.x/ONE_GRID;
	grid_z = vec.z/ONE_GRID;
	
	for(i=0;i<COMBAT_WALL_POS_MAX;i++){
		//XZ比較
		if ( (WallPosInfo[i].GridX == grid_x) &&
				(WallPosInfo[i].GridZ == grid_z) ){
			u8 no;
			no = WallPosInfo[i].WallNo;
			if (WallPosInfo[i].Bit){	//右にある
				check_x = WallInfo[no].AffterX;
				dir = DIR_LEFT;
			}else{						//左にある
				check_x = WallInfo[no].BeforeX;
				dir = DIR_RIGHT;
			}

			if ( (check_x == inCombatTemp->WallPos[no])&&
					(dir == inDir) ){
				return no;
			}
		}
	}
	return COMBAT_WALL_POS_MAX;
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:しきり移動イベントコール
 * 
 * @param	ioCombatTemp	格闘ジムテンポラリワーク
 * @param	inIdx			リフトインデックス
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CallWallMoveEvent(COMBAT_GYM_TEMP_WORK *ioCombatTemp, const u8 inIdx)
{
	int lift_type;
	u8 bit;
	EVENT_GYM_WORK * egw;
	
	GIMMICKWORK *work;
	COMBAT_GYM_WORK *combat_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(ioCombatTemp->fsys));
	combat_gym_work = (COMBAT_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_COMBAT_GYM);
	
	egw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GYM_WORK));
	egw->seq = 0;

	ioCombatTemp->ListIdx = inIdx;
	
	//対象リフトの位置を取得
	bit = GetBit(inIdx, combat_gym_work->WallPosBit);
	
	ChangeBit(inIdx,&combat_gym_work->WallPosBit);
	//移動イベントをコール
	
	if (bit){		//今右にある
		ioCombatTemp->MoveDir = MOVE_DIR_LEFT;
		ioCombatTemp->Dst = WallInfo[inIdx].BeforeX*ONE_GRID+COMBAT_CENTER_OFS_X;
		ioCombatTemp->WallPos[inIdx] = WallInfo[inIdx].BeforeX;
		ioCombatTemp->HitRect[inIdx] = &(WallHitInfo[inIdx].BeforeRect[0]);
	}else{			//今左にある
		ioCombatTemp->MoveDir = MOVE_DIR_RIGHT;
		ioCombatTemp->Dst = WallInfo[inIdx].AffterX*ONE_GRID+COMBAT_CENTER_OFS_X;
		ioCombatTemp->WallPos[inIdx] = WallInfo[inIdx].AffterX;
		ioCombatTemp->HitRect[inIdx] = &(WallHitInfo[inIdx].AffterRect[0]);
	}
	FieldEvent_Set(ioCombatTemp->fsys, GMEVENT_MoveWallGymCombat, egw);
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_SetupCombatGym(FIELDSYS_WORK *fsys)
{
	COMBAT_GYM_TEMP_WORK *combat_temp;
	GIMMICKWORK *work;
	COMBAT_GYM_WORK *combat_gym_work;
	
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	combat_gym_work = (COMBAT_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_COMBAT_GYM);

	//格闘ジム専用ワークをアロケートして、フィールドマップ汎用ワークポインタにあてる
	fsys->fldmap->Work = sys_AllocMemory(HEAPID_FIELD, sizeof(COMBAT_GYM_TEMP_WORK));
	combat_temp = fsys->fldmap->Work;

	combat_temp->fsys = fsys;
	
	//しきりの作成(12個)
	{
		VecFx32 vec;
		int i;
		for(i=0;i<COMBAT_WALL_MAX;i++){
			if (GetBit(i,combat_gym_work->WallPosBit)){
				vec.x = ONE_GRID*WallInfo[i].AffterX;
				vec.y = -ONE_GRID;
				vec.z = ONE_GRID*WallInfo[i].BaseZ;
				combat_temp->WallPos[i] = WallInfo[i].AffterX;
				combat_temp->HitRect[i] = &(WallHitInfo[i].AffterRect[0]);
			}else{
				vec.x = ONE_GRID*WallInfo[i].BeforeX;
				vec.y = -ONE_GRID;
				vec.z = ONE_GRID*WallInfo[i].BaseZ;
				combat_temp->WallPos[i] = WallInfo[i].BeforeX;
				combat_temp->HitRect[i] = &(WallHitInfo[i].BeforeRect[0]);
			}
			vec.x+=COMBAT_CENTER_OFS_X;
			vec.z+=COMBAT_CENTER_OFS_Z;
			combat_temp->WallEntryIdx[i] = 
				M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
									fsys->MapResource,
									WallInfo[i].ObjID,
									&vec, NULL,
									fsys->field_3d_anime );//<しきり

			///combat_temp->ObjID[i] = WallInfo[i].ObjID;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:終了処理
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_EndCombatGym(FIELDSYS_WORK *fsys)
{
	COMBAT_GYM_TEMP_WORK *combat_temp;
	combat_temp = (COMBAT_GYM_TEMP_WORK *)fsys->fldmap->Work;
	sys_FreeMemoryEz(combat_temp);
	fsys->fldmap->Work = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:しきりチェック
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	inDir	判定方向
 * 
 * @return	BOOL	TRUE:HIT		FALSE:NO_HIT
 */
//---------------------------------------------------------------------------
BOOL GYM_CheckCombatWall(FIELDSYS_WORK *fsys)
{
	u8 idx;
	u8 dir;
	COMBAT_GYM_TEMP_WORK *combat_temp;

	//ギミックワークを見る
	{
		int id;
		GIMMICKWORK *work;
		
		//ギミックワーク取得
		work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
		//ギミックコードを取得
		id = GIMMICKWORK_GetAssignID(work);

		if (id != FLD_GIMMICK_COMBAT_GYM){
			return FALSE;					//格闘ジムギミック無し
		}
	}

	combat_temp = (COMBAT_GYM_TEMP_WORK *)fsys->fldmap->Work;
	if (combat_temp == NULL){
		return FALSE;
	}
	dir = Player_DirGet(fsys->player);
	idx = CheckWallPush(combat_temp, dir);
	if (idx != COMBAT_WALL_POS_MAX){
		//ヒットしたので処理
		CallWallMoveEvent(combat_temp, idx);
		return TRUE;
	}
	
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:しきり当たり判定
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inHeight	高さ
 * @param	outHit		判定結果	TRUE:ヒット	FALSE:ヒットしてない
 * 
 * @return	BOOL		TRUE:このあと通常当たり判定を行わない	FALSE:通常当たり判定を行う
 */
//---------------------------------------------------------------------------
BOOL GYM_HitCheckCombatGym(	FIELDSYS_WORK *fsys,
							const int inGridX, const int inGridZ,
							const fx32 inHeight, BOOL *outHit	)
{
	int i,j;
	COMBAT_GYM_TEMP_WORK *combat_temp;
	const COMBAT_HIT_RECT	*rect;
	combat_temp = (COMBAT_GYM_TEMP_WORK *)fsys->fldmap->Work;
	for(i=0;i<COMBAT_WALL_MAX;i++){
		if (WallInfo[i].BaseZ == inGridZ){
			rect = combat_temp->HitRect[i];
			for(j=0;j<2;j++){
				if (rect[j].W == 0){
					break;
				}
				if ( (rect[j].X<=inGridX)&&
						(inGridX < (rect[j].X+rect[j].W)) ){
					(*outHit) = TRUE;
					return TRUE;	//HITしたので、通常当たり判定はパス
				}
			}
		}
	}
	return FALSE;	//通常当たり判定を実行
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:しきりの移動
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveWallGymCombat(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);
	COMBAT_GYM_TEMP_WORK *combat_temp;

	combat_temp = (COMBAT_GYM_TEMP_WORK *)fsys->fldmap->Work;
	fop = Player_FieldOBJGet( fsys->player );
	switch (egw->seq) {
	case 0:
		//しきりを押す音
		Snd_SePlay( SE_TOBARI_GYM_MOVE );
		//自機の移動(壁になっていて、グリッドのズレが生じないため、自機の移動アニメ終了を待たずにアニメ登録)
		if (combat_temp->MoveDir == MOVE_DIR_RIGHT){
			FieldOBJ_AcmdSet(fop,AC_WALK_R_8F);	//自機右移動
		}else{
			FieldOBJ_AcmdSet(fop,AC_WALK_L_8F);	//自機左移動
		}
		(egw->seq)	++;		
		break;
	case 1:	//しきりを移動
		{
			int entry;
			//リフトOBJを取得
			entry = combat_temp->WallEntryIdx[combat_temp->ListIdx];
			ptr = M3DO_GetMap3DObjData(fsys->Map3DObjExp, entry);
			//x座標変更
			{
				VecFx32 vec,player_vec;
				vec = M3DO_GetGlobalVec(ptr);
				
				if (combat_temp->MoveDir == MOVE_DIR_RIGHT){
					vec.x += (FX32_ONE*2);
					if (vec.x >= combat_temp->Dst){	//セット終了
						vec.x = combat_temp->Dst;
						(egw->seq) ++;
					}
				}else if (combat_temp->MoveDir == MOVE_DIR_LEFT){
					vec.x -= (FX32_ONE*2);
					if (vec.x <= combat_temp->Dst){	//セット終了
						vec.x = combat_temp->Dst;
						(egw->seq) ++;
					}
				}else{
					GF_ASSERT(0&&"方向指定エラー");
				}
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
				FieldOBJ_AcmdEnd(fop); //アニメ終了
				//しきり動く音止める
				Snd_SeStopBySeqNo( SE_TOBARI_GYM_MOVE, 0 );
				(egw->seq) ++;
			}
		}
		break;
	case 3:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

//電気ジム

typedef struct ELEC_GYM_TEMP_WORK_tag
{
	FIELDSYS_WORK *fsys;
	u8 ObjEntryIdx[ELEC_GEAR_MAX];
	u8 RoomNo;
	u8 GearNum;
	u8 RotateCode;
	
	u16 RotVal;			//回転度合いタイプ
	u16 NowRotate;		//現在回転値
	u16 DstRotate;		//目的回転値
}ELEC_GYM_TEMP_WORK;

typedef struct GEAR_tag
{
	int ObjID;		//ギアＯＢＪＩＤ
	u8 X;
	u8 Y;
	u8 Z;
	u8 RotateCode:2;	//回転状況
	u8 RotateDir:1;	//ギア回転方向
	u8 RotType:1;	//ギア回転タイプ
	u8 dummy:4;
}GEAR;

typedef struct GEAR_HIT_RECT_tag
{
	u8 X;
	u8 Z;
	u8 W;
	u8 H;
}GEAR_HIT_RECT;


static const GEAR	Room1Gear[ELEC_GEAR_MAX1] = 
{
	{ BMID_GYM_GEAR02,	  3,  0,  8, GEAR_ROT_ST_90,  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR02_2,  8,  0,  8, GEAR_ROT_ST_180, GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR02,   13,  0,  8, GEAR_ROT_ST_0,	  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
};

static const GEAR	Room2Gear[ELEC_GEAR_MAX2] = 
{
	{ BMID_GYM_GEAR02,	  6,  0,  8, GEAR_ROT_ST_90,  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR01_2, 11,  0,  8, GEAR_ROT_ST_270, GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR04,   15,  3,  8, GEAR_ROT_ST_90,  GEAR_ROT_DIR_RIGHT,GEAR_ROT_TYPE_X },
	{ BMID_GYM_GEAR04,	  2,  3, 13, GEAR_ROT_ST_90,  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_X },
	{ BMID_GYM_GEAR01_2,  6,  0, 13, GEAR_ROT_ST_180, GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03,   11,  0, 13, GEAR_ROT_ST_180, GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
};

static const GEAR	Room3Gear[ELEC_GEAR_MAX3] = 
{
	{ BMID_GYM_GEAR03,	  6,  6,  8, GEAR_ROT_ST_90,  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR02_2, 11,  6,  8, GEAR_ROT_ST_0,   GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03_2, 16,  6,  8, GEAR_ROT_ST_0,	  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR04,	  2,  3, 13, GEAR_ROT_ST_0,   GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_X },
	{ BMID_GYM_GEAR02_2,  6,  6, 13, GEAR_ROT_ST_90,  GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03,   11,  6, 13, GEAR_ROT_ST_270, GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03_2, 16,  6, 13, GEAR_ROT_ST_270, GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR04,   20,  3, 13, GEAR_ROT_ST_90,  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_X },
	{ BMID_GYM_GEAR04_2,  2,  3, 18, GEAR_ROT_ST_0,	  GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_X },
	{ BMID_GYM_GEAR02,	  6,  0, 18, GEAR_ROT_ST_90,  GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03_2, 11,  0, 18, GEAR_ROT_ST_270, GEAR_ROT_DIR_LEFT,  GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR03,   16,  0, 18, GEAR_ROT_ST_0,	  GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_Y },
	{ BMID_GYM_GEAR04_2, 20,  3, 18, GEAR_ROT_ST_90,  GEAR_ROT_DIR_RIGHT, GEAR_ROT_TYPE_X },
};

static const GEAR * const RoomGear[ELEC_ROOM_MAX] = {
	Room1Gear, Room2Gear, Room3Gear
};

static const GEAR_HIT_RECT Room1GearHit[4*ELEC_GEAR_NUM1_YROT] =
{
	{ 1,8,2,1}, { 3,6,1,2}, { 4,8,2,1}, { 3,9,1,2},	//左のギア
	{ 6,8,2,1}, { 8,6,1,2}, { 9,8,2,1}, { 8,9,1,2},	//真ん中のギア
	{11,8,2,1}, {13,6,1,2}, {14,8,2,1}, {13,9,1,2}	//右のギア
};
static const GEAR_HIT_RECT Room2GearHit[4*ELEC_GEAR_NUM2_YROT+ELEC_GEAR_NUM2_XROT] =
{
	{ 4, 8,2,1}, { 6, 6,1,2}, { 7, 8,2,1}, { 6, 9,1,2},	//奥左のギア
	{ 9, 8,2,1}, {11, 6,1,2}, {12, 8,2,1}, {11, 9,1,2},	//奥真ん中のギア
	{15, 6,1,5},										//奥右（縦）のギア
	{ 2,11,1,5},										//手前左（縦）のギア
	{ 4,13,2,1}, { 6,11,1,2}, { 7,13,2,1}, { 6,14,1,2},	//手前真ん中のギア
	{ 9,13,2,1}, {11,11,1,2}, {12,13,2,1}, {11,14,1,2}	//手前右のギア
};
static const GEAR_HIT_RECT Room3GearHit[4*ELEC_GEAR_NUM3_YROT+ELEC_GEAR_NUM3_XROT] =
{
	{ 4,8,2,1}, { 6, 6,1,2}, { 7,8,2,1}, { 6,9,1,2},	//上段奥左のギア
	{ 9,8,2,1}, {11, 6,1,2}, {12,8,2,1}, {11,9,1,2},	//上段奥真ん中のギア
	{14,8,2,1}, {16, 6,1,2}, {17,8,2,1}, {16,9,1,2},	//上段奥右のギア
	{ 2,11,1,5},
	{ 4,13,2,1}, { 6,11,1,2}, { 7,13,2,1}, { 6,14,1,2},	//上段手前左のギア
	{ 9,13,2,1}, {11,11,1,2}, {12,13,2,1}, {11,14,1,2},	//上段手前真ん中のギア
	{14,13,2,1}, {16,11,1,2}, {17,13,2,1}, {16,14,1,2},	//上段手前右のギア
	{20,11,1,5},
	{ 2,16,1,5},
	{ 4,18,2,1}, { 6,16,1,2}, { 7,18,2,1}, { 6,19,1,2},	//下段左のギア
	{ 9,18,2,1}, {11,16,1,2}, {12,18,2,1}, {11,19,1,2},	//下段真ん中のギア
	{14,18,2,1}, {16,16,1,2}, {17,18,2,1}, {16,19,1,2},	//下段右のギア
	{20,16,1,5},
};

static const GEAR_HIT_RECT * const RoomGearHit[ELEC_ROOM_MAX] = {
	Room1GearHit,Room2GearHit,Room3GearHit
};

//ギア当たり判定

//1部屋目
static const u8 Room1Rot0Hit[] = { 1,2,4,5,10,11 };
static const u8 Room1Rot90Hit[] = { 0,1,5,6, 9,10 };
static const u8 Room1Rot180Hit[] = { 0,3,6,7, 8, 9 };
static const u8 Room1Rot270Hit[] = {  2,3,4,7, 8,11 };
//2部屋目
static const u8 Room2Rot0Hit[] =  { 1,2,4,5,7,8,9,10,11,12,15 };
static const u8 Room2Rot90Hit[] = { 0,1,4,5,6,11,12,13,14,0,0 };//後ろ2つはダミー（すでにエントリされている番号で埋めとく）
static const u8 Room2Rot180Hit[] = { 0,3,5,6,7,8, 9,10,12,13,17 };
static const u8 Room2Rot270Hit[] = { 2,3,4,6,7,10,11,13,16,2,2 };//後ろ2つはダミー（すでにエントリされている番号で埋めとく）
//3部屋目
static const u8 Room3Rot0Hit[] =  { 2,6,7,11,14,15,17,21,25,28,29,31,38,39 };
static const u8 Room3Rot90Hit[] = { 1,4,7,10,12,15,16,20,22,26,29,30,34,35 };
static const u8 Room3Rot180Hit[] = { 0,4,5,9,13,16,19,23,25,27,30,33,36,39 };
static const u8 Room3Rot270Hit[] = { 3,5,6,8,12,13,14,18,24,26,27,28,32,37 };

typedef struct GEAR_HIT_INFO_tag
{
	int HitNum;	//当たり矩形数
	u8 const *HitList[4];	//0,90,180,270°のときの当たり判定テーブル
}GEAR_HIT_INFO;

GEAR_HIT_INFO GearHitInfo[ELEC_ROOM_MAX] = 
{
	{ 6,{Room1Rot0Hit, Room1Rot90Hit, Room1Rot180Hit, Room1Rot270Hit} },
	{ 11,{Room2Rot0Hit, Room2Rot90Hit, Room2Rot180Hit, Room2Rot270Hit} },
	{ 14,{Room3Rot0Hit, Room3Rot90Hit, Room3Rot180Hit, Room3Rot270Hit} },
};

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:部屋に応じたギア個数を返す
 * 
 * @param	inRoomNo	部屋ナンバー
 * 
 * @return	u8			ギア個数
 */
//---------------------------------------------------------------------------
static u8 GetGearNum(const u8 inRoomNo)
{
	u8 num;
	switch (inRoomNo){
	case ELEC_GYM_ROOM1:
		num = ELEC_GEAR_MAX1;
		break;
	case ELEC_GYM_ROOM2:
		num = ELEC_GEAR_MAX2;
		break;
	case ELEC_GYM_ROOM3:
		num = ELEC_GEAR_MAX3;
		break;
	default:
		GF_ASSERT(0);
		num = 0;
	}
	return num;
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:ギアの初期回転計算
 *
 * @param	inGear			ギアデータ
 * @param	inRoomRotate	ギミック発動による追加回転
 * @param	outRotate		回転ベクトル格納バッファ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void GetStartRotate(const GEAR *inGear , const u8 inRoomRotate, VecFx32 *outRotate)
{
	fx32 *target = NULL;
	fx16 rot,room_rot;

	//足しこみ対象決定
	switch (inGear->RotType){
	case GEAR_ROT_TYPE_Y:
		target = &(outRotate->y);
		break;
	case GEAR_ROT_TYPE_X:
		target = &(outRotate->x);
		break;
	default:
		GF_ASSERT(0&&"ERROR:RotType unknown");
	}

	rot = 0;

	//ギアごとの初期回転をベクトルに足しこむ
	GF_ASSERT(inGear->RotateCode<=GEAR_ROT_ST_270&&"ERROR:RotState unknown");
	rot += (0x4000*inGear->RotateCode);

	GF_ASSERT(inRoomRotate<=GEAR_ROT_ST_270&&"ERROR:RotState unknown");
	//ボタンによる回転をギアに足し込む(回転方向によっては差し引く)
	room_rot = 0x4000*inRoomRotate;
	if (inGear->RotateDir == GEAR_ROT_DIR_LEFT){
		rot += room_rot;
	}else if(inGear->RotateDir == GEAR_ROT_DIR_RIGHT){
		rot -= room_rot;
	}else{
		GF_ASSERT(0&&"ERROR:RotDir unknown");;
	}

	(*target) = rot;
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_SetupElecGym(FIELDSYS_WORK *fsys)
{
	ELEC_GYM_TEMP_WORK *elec_temp;
	GIMMICKWORK *work;
	ELEC_GYM_WORK *elec_gym_work;
	
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	elec_gym_work = (ELEC_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_ELEC_GYM);

	//電気ジム専用ワークをアロケートして、フィールドマップ汎用ワークポインタにあてる
	fsys->fldmap->Work = sys_AllocMemory(HEAPID_FIELD, sizeof(ELEC_GYM_TEMP_WORK));
	elec_temp = fsys->fldmap->Work;

	elec_temp->RoomNo = elec_gym_work->RoomNo;
	elec_temp->RotateCode = elec_gym_work->GearRotateCode;
///	elec_temp->fsys = fsys;
	
	//部屋ごとにギアを作成
	{
		VecFx32 vec;
		VecFx32 rotate;
		int i;
		u8 gear_num;

		gear_num = GetGearNum(elec_gym_work->RoomNo);

		for(i=0;i<gear_num;i++){
			const GEAR *room_gear;
			room_gear = RoomGear[elec_gym_work->RoomNo];
			vec.x = room_gear[i].X * ONE_GRID;
			vec.y = room_gear[i].Y * ONE_GRID;
			vec.z = room_gear[i].Z * ONE_GRID;
			
			vec.x+=ELEC_GEAR_CENTER_OFS_X;
			vec.z+=ELEC_GEAR_CENTER_OFS_Z;

			//Ｘ軸回転なら補正をかける
			if (room_gear[i].RotType == GEAR_ROT_TYPE_X){
				vec.y+=ELEC_GEAR_CENTER_OFS_Y;
			}
			
			//回転計算
			{
				rotate.x = 0;
				rotate.y = 0;
				rotate.z = 0;
				//初期回転を取得
				GetStartRotate(&(room_gear[i]), elec_gym_work->GearRotateCode, &rotate);
			}
			
			
			elec_temp->ObjEntryIdx[i] = 
				M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
									fsys->MapResource,
									room_gear[i].ObjID,
									&vec, &rotate,
									fsys->field_3d_anime );
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:終了処理
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_EndElecGym(FIELDSYS_WORK *fsys)
{
	ELEC_GYM_TEMP_WORK *elec_temp;
	elec_temp = (ELEC_GYM_TEMP_WORK *)fsys->fldmap->Work;
	sys_FreeMemoryEz(elec_temp);
	fsys->fldmap->Work = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:当たり判定
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inGridX		グリッドX座標
 * @param	inGridZ		グリッドZ座標
 * @param	inHeight	高さ
 * @param	outHit		判定結果	TRUE:ヒット	FALSE:ヒットしてない
 * 
 * @return	BOOL		TRUE:このあと通常当たり判定を行わない	FALSE:通常当たり判定を行う
 */
//---------------------------------------------------------------------------
BOOL GYM_HitCheckElecGym(	FIELDSYS_WORK *fsys,
							const int inGridX, const int inGridZ,
							const fx32 inHeight, BOOL *outHit	)
{
	
	int i, hit_num,rot;
	u8 const *hit_list;
	u8 idx;
	GEAR_HIT_RECT const *rect;
	ELEC_GYM_TEMP_WORK *elec_temp;
	elec_temp = (ELEC_GYM_TEMP_WORK *)fsys->fldmap->Work;
	
	hit_num = GearHitInfo[elec_temp->RoomNo].HitNum;
	rot = elec_temp->RotateCode;
	hit_list = GearHitInfo[elec_temp->RoomNo].HitList[rot];

	rect = RoomGearHit[elec_temp->RoomNo];

	for(i=0;i<hit_num;i++){
		idx = hit_list[i];
		if ( (rect[idx].X<=inGridX)&&(inGridX<rect[idx].X+rect[idx].W) &&
				(rect[idx].Z<=inGridZ)&&(inGridZ<rect[idx].Z+rect[idx].H) ){
			(*outHit) = TRUE;
			return TRUE;	//HITしたので、通常当たり判定はパス
		}
	}
		
	return FALSE;	//通常当たり判定を実行
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:ギア回転
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	inRotate	回転（0:+90°、1:-90°、2:180°）
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_RotateElecGymGear(FIELDSYS_WORK *fsys, const u8 inRotate)
{
	EVENT_GYM_WORK * egw;
	ELEC_GYM_TEMP_WORK *elec_temp;
	GIMMICKWORK *work;
	ELEC_GYM_WORK *elec_gym_work;
	
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	elec_gym_work = (ELEC_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_ELEC_GYM);
	
	elec_temp = (ELEC_GYM_TEMP_WORK *)fsys->fldmap->Work;
	
	//イベントコール
	egw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GYM_WORK));
	egw->seq = 0;

	{
		s8 rot_code;
		elec_temp->RotVal = inRotate;
		elec_temp->NowRotate = 0;
		elec_temp->GearNum = GetGearNum(elec_gym_work->RoomNo);
		rot_code = elec_gym_work->GearRotateCode;
		
		if ( inRotate == ROTATE_GEAR_PLUS90){
			elec_temp->DstRotate = 0x4000;
			rot_code = (rot_code+1)%GEAR_ROT_ST_MAX;
		}else if(inRotate == ROTATE_GEAR_MINUS90){
			elec_temp->DstRotate = 0x4000;
			rot_code--;
			if (rot_code<0){
				rot_code = GEAR_ROT_ST_270;
			}
		}else if (inRotate == ROTATE_GEAR_PLUS180){
			elec_temp->DstRotate = 0x8000;
			rot_code = (rot_code+2)%GEAR_ROT_ST_MAX;
		}else{
			GF_ASSERT(0&&"ERROR:GearRotate unknown");
			return;
		}

		elec_gym_work->GearRotateCode = rot_code;
		elec_temp->RotateCode = rot_code;

		//ギア回転音
		Snd_SePlay( SE_NAGISA_GYM_BUTTON );
		
		FieldEvent_Call(fsys->event, GMEVENT_RotateElecGymGear, egw);
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:ギアの回転
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_RotateElecGymGear(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GYM_WORK * egw = FieldEvent_GetSpecialWork(event);
	ELEC_GYM_TEMP_WORK *elec_temp;

	elec_temp = (ELEC_GYM_TEMP_WORK *)fsys->fldmap->Work;
	switch (egw->seq) {
	case 0:	//ギア回転
		{
			u8 i;
			u16 rot;
			u16 speed;
			//回転形式ごとに、変化量を足しこむ
			if (elec_temp->NowRotate + GEAR_ROT_SPEED <= elec_temp->DstRotate){
				speed = GEAR_ROT_SPEED;
			}else{
				speed = elec_temp->NowRotate + GEAR_ROT_SPEED - elec_temp->DstRotate;
			}
			elec_temp->NowRotate += speed;

			rot = speed;

			if (elec_temp->RotVal == ROTATE_GEAR_MINUS90){
				rot = -rot;
			}

			for(i=0;i<elec_temp->GearNum;i++){
				int entry;
				//ギアOBJを取得
				entry = elec_temp->ObjEntryIdx[i];
				ptr = M3DO_GetMap3DObjData(fsys->Map3DObjExp, entry);

				//回転
				{
					VecFx32 *rot_vec;
					rot_vec = M3DO_GetRotateVecPtr(ptr);

					//時計回り、反時計回りで足すか引くか分岐する
					{
						const GEAR *room_gear;
						fx32 *target;
						u16 temp,apply_rot;
						room_gear = RoomGear[elec_temp->RoomNo];
						if (room_gear[i].RotateDir == GEAR_ROT_DIR_RIGHT){
							apply_rot = -rot;
						}else{
							apply_rot = rot;
						}
						//回転軸対象の決定
						switch (room_gear[i].RotType){
						case GEAR_ROT_TYPE_Y:
							target = &(rot_vec->y);
							break;
						case GEAR_ROT_TYPE_X:
							target = &(rot_vec->x);
							break;
						default:
							GF_ASSERT(0&&"ERROR:RotType unknown");
						}
						temp = (*target);
						temp += apply_rot;
						(*target) = temp;
					}
				}
			}	//end for

			if (elec_temp->NowRotate >= elec_temp->DstRotate){
				(egw->seq) ++;
			}
		}
		break;
	case 1:
		sys_FreeMemoryEz(egw);
		return TRUE;
	}
	return FALSE;
}
