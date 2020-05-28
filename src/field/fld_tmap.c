/**
 *	@file	fld_tmap.c
 *	@brief	タウンマップ用　フィールド常駐関数群
 *	@author	Miyuki Iwasawa
 *	@date	06.04.05
 */

#include "common.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "field_subproc.h"
#include "field/field.h"
#include "field/townmap_footmark.h"
#include "field/situation_local.h"
#include "field/script.h"
#include "field/syswork.h"
#include "fieldmap.h"
#include "zonedata.h"
#include "system/mystatus.h"
#include "application/townmap.h"

///セーブフラグ引継ぎデータ構造体
typedef struct {
	u8	fk01;	///<フラグ種別フラグ
	u8	fidx01;	///<フラグ参照インデックス
	u8	fk02;	///<フラグ種別フラグ
	u8	fidx02;	///<フラグ参照インデックス
}TMAP_FLAGS_DATA;

///タウンマップ　到着フラグチェック
static const u8 arrive_id[TMAP_ARRIVEDATA_MAX] = {
 FLAG_ARRIVE_T01,
 FLAG_ARRIVE_T02,
 FLAG_ARRIVE_T03,
 FLAG_ARRIVE_T04,
 FLAG_ARRIVE_T05,
 FLAG_ARRIVE_T06,
 FLAG_ARRIVE_T07,
 FLAG_ARRIVE_C01,
 FLAG_ARRIVE_C02,
 FLAG_ARRIVE_C03,
 FLAG_ARRIVE_C04,
 FLAG_ARRIVE_C05,
 FLAG_ARRIVE_C06,
 FLAG_ARRIVE_C07,
 FLAG_ARRIVE_C08,
 FLAG_ARRIVE_C09,
 FLAG_ARRIVE_C11,
 FLAG_ARRIVE_R221R0101,
 FLAG_ARRIVE_C10,
 FLAG_ARRIVE_CHAMPLEAGUE,
};

static void tmap_FlagGet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,const char* path);

/**
 *	@brief	フィールド タウンマップモジュールデータセット
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:データを格納する構造体型へのポインタ
 *	@param	mode	u8:呼び出しモード(enum TMAP_MODE)
 */
void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode)
{
    MYSTATUS* pMyStatus;
	int i = 0,pos = 0,ret = 0;
	int x,z,zoneID;
	TOWN_MAP_FOOTMARK * fmark;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);

	memset(tp,0,sizeof(TOWNMAP_PARAM));

	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	zoneID = World_GetZoneIDFromMatrixXZ(fsys->World,x/BLOCK_GRID_W,z/BLOCK_GRID_W);
	if(ZoneData_IsSinouField(zoneID)){
		tp->player_x = x;
		tp->player_z = z;
	}else{
		tp->player_x = escape->grid_x;
		tp->player_z = escape->grid_z;
	}
//	tp->zone_id = GetNowZoneID(fsys);

	//自機の性別
    pMyStatus = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
	tp->player_sex = MyStatus_GetMySex(pMyStatus); 

	//自機の移動ログ取得
	fmark= Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
	
	pos = (fmark->NowPoint-2+FOOTMARK_NUM)%FOOTMARK_NUM;
	for(i = 0;i < TMAP_FVIEW_MAX;i++){
		tp->foot[i].x = fmark->Param[pos].BlockX;
		tp->foot[i].z = fmark->Param[pos].BlockZ;
		tp->foot[i].valid = fmark->Param[pos].Valied;
		if(fmark->Param[pos].Dir > 3){
			tp->foot[i].dir = DIR_RIGHT+1;
		}else{
			tp->foot[i].dir = fmark->Param[pos].Dir;
		}
		pos = (pos-1+FOOTMARK_NUM)%FOOTMARK_NUM;

		if(tp->foot[i].valid){
			ret++;
		}
	}

	//隠しマップ出現フラグ取得
	for(i = 0;i < 4;i++){
		if(SysWork_HideMapWorkCheck( ev, i)){
			tp->view_f |= (0x01 << i);
		}
	}
	//到着フラグ取得
	for(i = 0;i < TMAP_ARRIVEDATA_MAX;i++){
		tp->arrive[i] = SysFlag_ArriveGet( ev,arrive_id[i]);
	}

	//各種フラグ取得
	tmap_FlagGet(fsys,tp,"data/tmap_flags.dat");
	
	tp->mode = mode;
}

/**
 *	@brief	フラグ取得
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:データを格納する構造体型へのポインタ
 *	@param	mode	u8:呼び出しモード(enum TMAP_MODE)
 */
static void tmap_FlagGet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,const char* path)
{
	FSFile fp;
	int ret,i;
	int dat_num;
	TMAP_FLAGS_DATA *src;
	TMAP_FLAGS* wp;
	EVENTWORK* event = SaveData_GetEventWork(fsys->savedata);

	FS_InitFile(&fp);
	if(!FS_OpenFile(&fp,path)){
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
		GF_ASSERT(0);
		return;
	}
	//データ数取得
	ret = FS_ReadFile(&fp,&dat_num,4);
	GF_ASSERT(ret >= 0 && "ERROR:tmap flags data num can't read");
	
	//テンポラリメモリ確保
	src = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(TMAP_FLAGS_DATA));
	MI_CpuClear8(src,sizeof(TMAP_FLAGS_DATA));

	tp->flag_num = dat_num;	//数を保存

	for(i = 0;i < dat_num;i++){
		wp = &(tp->flags[i]);
		ret = FS_ReadFile(&fp,src,sizeof(TMAP_FLAGS_DATA));

		//フラグ取得
		switch(src->fk01){
		case 1:	//到着フラグ
			wp->ex01 = SysFlag_ArriveGet(event,src->fidx01);
			wp->ex01_f = 1;
			break;
		case 2:	//スクリプトフラグ
			wp->ex01 = CheckEventFlag(fsys,src->fidx01);
			wp->ex01_f = 1;
			break;
		}
		switch(src->fk02){
		case 1:	//到着フラグ
			wp->ex02 = SysFlag_ArriveGet(event,src->fidx02);
			wp->ex02_f = 1;
			break;
		case 2:	//スクリプトフラグ
			wp->ex02 = CheckEventFlag(fsys,src->fidx02);
			wp->ex02_f = 1;
			break;
		}
	}
	(void)FS_CloseFile(&fp);
	sys_FreeMemoryEz(src);	//テンポラリ解放
	return;
}

