//=============================================================================
/**
 * @file	honey_tree_enc.c
 * @bfief	蜜塗りエンカウント
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "honey_tree_enc.h"
#include "map_tool.h"
#include "player.h"
#include "fieldsys.h"
#include "..\fielddata\script\common_scr_def.h"		//for SCRID_HONEY_TREE
#include "honey_tree_def.h"
#include "..\fielddata\maptable\zone_id.h"

#include "../fielddata/build_model/build_model_id.h"

#include "savedata/encount.h"
#include "arc/encdata_ex.naix"

#define START_TIME	(24*60)		//蜜を塗った直後の時間 24ｘ60分

#define ENC_START_TIME	(18*60)	//エンカウント可能な時間　18ｘ60分

typedef enum{
	TH_ENC_TBL_NORM,
	TH_ENC_TBL_RARE,
	TH_ENC_TBL_G_RARE,
}HT_ENC_TBL;

typedef enum{
	SWAY_LV_NONE,		//揺れない
	SWAY_LV_NORMAL,		//通常揺れ
	SWAY_LV_GRATE,		//すごく揺れる
	SWAY_LV_G_GRATE,	//ものごっつ揺れる
}SWAY_LV;

enum{
	HTE_NONE,
	HTE_NORMAL,
	HTE_RARE,
	HTE_GRATE_RARE,
};

typedef struct HONEY_DATA_ANM_tag
{
	u8 AnimeNo;
	BOOL AnimeFlg;
}HONEY_DATA_ANM;

typedef struct HONEY_TREE_DAT_tag
{
	HONEY_DATA_ANM HoneyData[HONEY_TREE_MAX];
	int ZoneList[HONEY_TREE_MAX];
}HONEY_TREE_DAT;

//揺れる木のゾーンリスト(ゾーンをまたいだときに参照するので、アーカイブにしないで、固定で持ちます)
static const int HoneyTreeZoneList[HONEY_TREE_MAX] = {
	ZONE_ID_R205A,
	ZONE_ID_R205B,
	ZONE_ID_R206,
	ZONE_ID_R207,
	ZONE_ID_R208,
	ZONE_ID_R209,
	ZONE_ID_R210A,
	ZONE_ID_R210B,
	ZONE_ID_R211B,
	ZONE_ID_R212A,
	ZONE_ID_R212B,
	ZONE_ID_R213,
	ZONE_ID_R214,
	ZONE_ID_R215,
	ZONE_ID_R218,
	ZONE_ID_R221,
	ZONE_ID_R222,
	ZONE_ID_D02,
	ZONE_ID_D03,
	ZONE_ID_D04,
	ZONE_ID_D13R0101,
};

//エンカウントポケモンアーカイブインデックステーブル
//ダイヤ
static const int HoneyEncArcTbl_Dia[] = {
	NARC_encdata_ex_honey_dia_nrm_bin,		//通常
	NARC_encdata_ex_honey_dia_rare_bin,		//レア
	NARC_encdata_ex_honey_dia_s_rare_bin,	//激レア
};

//パール
static const int HoneyEncArcTbl_Perl[] = {
	NARC_encdata_ex_honey_perl_nrm_bin,		//通常
	NARC_encdata_ex_honey_perl_rare_bin,		//レア
	NARC_encdata_ex_honey_perl_s_rare_bin,	//激レア
};

static void SetRareLv(const BOOL inHit, u8 *outRare);
static void SetHoneyTreeTblMonsNo(u8 *outTblMonsNo);
static void SetHoneyTreeAnimation(FIELDSYS_WORK *fsys, M3DOL_PTR inMap3DObjList, const int inBlockIdx);
static u8 GetTreeNoFromZoneID(const int inZoneID);
static const int SetHoneyTreeEncTbl(const u8 inRareLv);
static const int SetSwayLv(const u8 inRareLv);
static const BOOL GetAnimeNoForHoneyTree(const int inSwayLv, u8 *outAnimeNo);
static const BOOL CheckHoneyTreeEncTime(const int inTime);
static BOOL CheckRareFlg(const u32 inTrainerID, const u8 inIndex);

//==============================================================================
/**
 * 蜜木データの確保と初期化
 *
 * 
 * @retval	HTD_PTR			蜜木データポインタ		
 * 
 */
//==============================================================================
HTD_PTR HTE_AllocHoneyTreeDat(void)
{
	u8 i;
	HTD_PTR htd_p;
	htd_p = sys_AllocMemory(HEAPID_FIELD, sizeof(HONEY_TREE_DAT));
	for(i=0;i<HONEY_TREE_MAX;i++){
		htd_p->HoneyData[i].AnimeNo = 0;
		htd_p->HoneyData[i].AnimeFlg = FALSE;
	}
	return htd_p;
}

//==============================================================================
/**
 * 解放処理
 *
 * @param	outHoneyTree	蜜木データポインタ	
 * 
 * @retval  none		
 */
//==============================================================================
void HTE_FreeHoneyTreeDat(HTD_PTR *outHoneyTree)
{
	sys_FreeMemoryEz(*outHoneyTree);
	*outHoneyTree = NULL;
}

//==============================================================================
/**
 * 蜜塗り木の接触チェック
 *
 * @param	fsys		フィールドシステムポインタ
 * @param	outScrID	スクリプトID格納アドレス
 *
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
 */
//==============================================================================
BOOL HTE_CheckHoneyTree(FIELDSYS_WORK *fsys, int *outScrID)
{
	TARGET_RECT rect;
	int x,z;
	BOOL rc;
	int dir;

	*outScrID = SCRID_HONEY_TREE;
	//自機座標取得(グリッド)
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	//自機方向取得
	dir = Player_DirGet( fsys->player );
	if (dir == DIR_UP){
		//自機方向の前方1グリッドの矩形を作成
		MPTL_MakeTargetRect( x, z, 0, -1, 1, 1, &rect);

		rc = MPTL_CheckMap3DObjInRect(	fsys,
										BMID_TREEEFF,			//揺れる木
										&rect,
										NULL);
	}else{
		rc = FALSE;
	}
	return rc;
}

//==============================================================================
/**
 * 現在いるゾーンの蜜塗り木のステート取得
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	u16			木のステート
 */
//==============================================================================
u16 HTE_GetNowLocHoneyTreeState(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	HT_PTR ptr;
	HONEY_DATA *data;
	//現在のゾーンIDを取得
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"蜜塗り木が登録されていません" );

	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///	ptr = HTSave_GetHoneyTree(fsys->savedata);
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	if ( CheckHoneyTreeEncTime(data->Time) ){
		return HONEY_SPREAD_ENCOUNT;//エンカウント可
	}else{
		if (data->Time != 0){
			//蜜を塗って時間経過が開始されている場合
			return HONEY_SPREAD_ALREADY;	//蜜塗り可（すでに塗ってある状態）
		}else{
			return HONEY_SPREAD_OK;	//蜜塗り可
		}
	}
}

//==============================================================================
/**
 * 現在いるゾーンの蜜塗り木のセットアップ
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 */
//==============================================================================
void HTE_SetupNowLocHoneyTree(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	HT_PTR ptr;
	HONEY_DATA *data;
	BOOL rare_flg;
	//現在のゾーンIDを取得
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"蜜塗り木が登録されていません" );
	
	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	
	data->Time = START_TIME;
	{
		MYSTATUS *my_st = SaveData_GetMyStatus(fsys->savedata);
		//トレーナーIDから、当たり番号を決定
		rare_flg = CheckRareFlg(MyStatus_GetID(my_st), tree_no);
	}
	//前回の木と比較。同じ木なら、前回のポケモンとのエンカウント率が高くなる>テーブルのみ同じに変更 20060619
	if (HTSave_GetBeforeTreeNo(ptr) == tree_no){
		if ( (gf_p_rand(100) ) <90){	//同じポケモンとエンカウント(9割りで同じ)
			SetHoneyTreeTblMonsNo(&data->TblMonsNo);
			//木の揺れ方を決定
			data->SwayLv = SetSwayLv(data->RareLv);
			return;
		}
	}
	{	//再抽選
		SetRareLv(rare_flg, &data->RareLv);
		//ハズレ以外なら
		if (data->RareLv != HTE_NONE){
			SetHoneyTreeTblMonsNo(&data->TblMonsNo);
			//テーブル決定
			data->TblNo = SetHoneyTreeEncTbl( data->RareLv );
		}else{	//ハズレのときは、テーブルをノーマルにする
			data->TblNo = TH_ENC_TBL_NORM;
			data->TblMonsNo = 0;
			//ハズレなので、時間を初期化
			data->Time = 0;
		}
		//木の揺れ方を決定
		data->SwayLv = SetSwayLv(data->RareLv);
	}
	//木の番号を記憶
	HTSave_SetBeforeTreeNo(tree_no, ptr);
}

//==============================================================================
/**
 * 蜜塗り木の戦闘後処理
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 */
//==============================================================================
void HTE_SetHoneyTreeInfoAfterBtl(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"蜜塗り木が登録されていません" );
	//アニメストップ
	if (fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg){
		u8 idx;
		M3DO_PTR obj_ptr;
		M3DOL_PTR obj_list;
		NNSG3dRenderObj *render_obj;
		//ローカルインデックスを取得
		idx = GetNowLocalIndex(fsys->map_cont_dat);
		//ＯＢＪリストを取得
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_list);
		obj_ptr = M3DO_GetMap3DObjDataFromID(obj_list, BMID_TREEEFF);
		render_obj = M3DO_GetRenderObj(obj_ptr);
		if (obj_ptr != NULL){
			F3DA_RemoveFld3DAnime(	fsys->field_3d_anime,
									render_obj,
									BMID_TREEEFF,
									fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo);
		}
		fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = FALSE;
///		OS_Printf("揺れ草アニメストップ\n");
	}
	//モンスターテーブル番号は消さないこと!!
}

//==============================================================================
/**
 * 蜜塗り木のレア度を決定
 *
 * @param	inHit		当たりフラグ
 * @param	outRare		レア度を格納するバッファ		
 * 
 * @return	none
 */
//==============================================================================
static void SetRareLv(const BOOL inHit, u8 *outRare)
{
	int rand;
	rand = gf_p_rand(100);
	if (inHit){
		if(rand<1){			//1%
			*outRare = HTE_GRATE_RARE;	//激レア
		}else if(rand<10){	//9%
			*outRare = HTE_NONE;		//ハズレ
		}else if(rand<30){	//20%
			*outRare = HTE_NORMAL;	//通常
		}else{				//70%
			*outRare = HTE_RARE;	//レア
		}
	}else{
		if(rand<10){	//10%
			*outRare = HTE_NONE;		//ハズレ
		}else if(rand<30){	//20%
			*outRare = HTE_RARE;	//レア
		}else{				//70%
			*outRare = HTE_NORMAL;	//通常
		}
	}
}

//==============================================================================
/**
 * 蜜塗り木のエンカウントモンスターテーブルナンバーを決定
 *
 * @param	outTblMonsNo		モンスターテーブルナンバーを格納するバッファ
 *
 * @return	none
 */
//==============================================================================
static void SetHoneyTreeTblMonsNo(u8 *outTblMonsNo)
{
	int rand;
	rand = gf_p_rand(100);
	if(rand<5){			//5%
		*outTblMonsNo = 5;
	}else if(rand<10){	//5%
		*outTblMonsNo = 4;
	}else if(rand<20){	//10%
		*outTblMonsNo = 3;
	}else if(rand<40){	//20%
		*outTblMonsNo = 2;
	}else if(rand<60){	//20%
		*outTblMonsNo = 1;
	}else{				//40%
		*outTblMonsNo = 0;
	}
}

//==============================================================================
/**
 * 蜜塗りエンカウントテーブル決定
 *
 * @param	inRareLv		レア度
 *
 * @return	int				テーブル番号
 */
//==============================================================================
static const int SetHoneyTreeEncTbl(const u8 inRareLv)
{
	int tbl_no;
	if (inRareLv == HTE_GRATE_RARE){	//超レア
		tbl_no = TH_ENC_TBL_G_RARE;
	}else if(inRareLv == HTE_RARE){		//レア
		tbl_no = TH_ENC_TBL_RARE;
	}else{								//ノーマル
		tbl_no = TH_ENC_TBL_NORM;
	}
	return tbl_no;
}

//==============================================================================
/**
 * 揺れ具合をセット
 *
 * @param	inRareLv		レア度
 *
 * @return	int				揺れ具合
 */
//==============================================================================
static const int SetSwayLv(const u8 inRareLv)
{
	int sway_lv;
	int rand;
	rand = gf_p_rand(100);
	
	if (inRareLv == HTE_GRATE_RARE){	//超レア
		if (rand<5){		//5%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<6){	//1%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<7){	//1%
			sway_lv = SWAY_LV_NONE;
		}else{				//93%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else if(inRareLv == HTE_RARE){		//レア
		if (rand<75){		//75%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<95){	//20%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<96){	//1%
			sway_lv = SWAY_LV_NONE;
		}else{				//4%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else if(inRareLv == HTE_NORMAL){	//ノーマル
		if (rand<19){		//19%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<79){	//60%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<99){	//20%
			sway_lv = SWAY_LV_NONE;
		}else{				//1%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}else{								//ハズレ
		if (rand<1){		//1%
			sway_lv = SWAY_LV_GRATE;
		}else if(rand<19){	//18%
			sway_lv = SWAY_LV_NORMAL;
		}else if(rand<99){	//80%
			sway_lv = SWAY_LV_NONE;
		}else{				//1%
			sway_lv = SWAY_LV_G_GRATE;
		}
	}
	return sway_lv;
}

//==============================================================================
/**
 * 揺れアニメナンバーのセット
 * アニメナンバーは、field_3d_anime.c内のアニメテーブルに依存します
 *
 * @param	inRareLv		揺れ具合
 * @oaram	outAnimeNo		アニメナンバー　0：ノーマル　1すごく揺れる　2：ものごっつ揺れる
 *
 * @return	BOOL			TRUE：アニメする	FALSE：アニメしない
 */
//==============================================================================
static const BOOL GetAnimeNoForHoneyTree(const int inSwayLv, u8 *outAnimeNo)
{
	u8 anime_no;	//アニメナンバー
	BOOL rc;
	rc = TRUE;
	if (inSwayLv == SWAY_LV_G_GRATE){
		*outAnimeNo = 2;
	}else if (inSwayLv == SWAY_LV_GRATE){
		*outAnimeNo = 1;
	}else if (inSwayLv == SWAY_LV_NORMAL){
		*outAnimeNo = 0;
	}else{
		rc = FALSE;
	}
	return rc;
}

//==============================================================================
/**
 * 蜜塗り木のアニメーションセットメイン
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inMap3DObjList	マップ3DOBJリスト
 * @param	inBlockIdx		ブロックインデックス
 *
 * @return	none
 */
//==============================================================================
static void SetHoneyTreeAnimation(FIELDSYS_WORK *fsys, M3DOL_PTR inMap3DObjList, const int inBlockIdx)
{
	u16 zone_id;
	u8 tree_no;
	
	//ブロックのゾーンIDを取得
	zone_id = World_GetZoneIDFromBlockIdx(fsys->World, inBlockIdx);
	//取得したゾーンＩＤは蜜塗りする場所かを調べる
	tree_no = GetTreeNoFromZoneID(zone_id);

	if (tree_no != HONEY_TREE_MAX){
		HT_PTR ptr;
		HONEY_DATA *data;
		M3DO_PTR obj_ptr;

		ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///		ptr = HTSave_GetHoneyTree(fsys->savedata);
		data = HTSave_GetHoneyDataPtr(tree_no, ptr);	
		
		//蜜塗りする場所の場合、その場所の、蜜塗り木の状況を取得
		if ( CheckHoneyTreeEncTime(data->Time) ){
			BOOL rc;
			u8 anime_no;
			//ゆれ方を分岐
			rc = GetAnimeNoForHoneyTree(data->SwayLv, &anime_no);
			
			if(!rc){
				return;
			}
			
			//アニメーションセット（アニメそのものは、ブラックアウト時に済ませておく）
			obj_ptr = M3DO_GetMap3DObjDataFromID(inMap3DObjList, BMID_TREEEFF);
			if (obj_ptr != NULL){
				NNSG3dRenderObj *render_obj;
				render_obj = M3DO_GetRenderObj(obj_ptr);
				//すでにアニメしてるかもしれないので、ここで、アニメをオフにする
				F3DA_RemoveFld3DAnime(	fsys->field_3d_anime,
										render_obj,
										BMID_TREEEFF,
										fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo);

				fsys->HoneyTreePtr->HoneyData[tree_no].AnimeNo = anime_no;
				fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = rc;
				
				F3DA_SetFld3DAnime(	BMID_TREEEFF, anime_no, TRUE,
									render_obj,
									fsys->field_3d_anime	);
			}
		}
	}
}

//==============================================================================
/**
 * ゾーンIDから蜜塗り木のナンバーを取得
 *
 * @param	inZoneID		ゾーンID
 *
 * @return	u8				木ナンバー
 */
//==============================================================================
static u8 GetTreeNoFromZoneID(const int inZoneID)
{
	u8 i;
	for(i=0;i<HONEY_TREE_MAX;i++){
		if (inZoneID == HoneyTreeZoneList[i]){
			return i;
		}
	}
	return i;
}

//==============================================================================
/**
 * エンカウントできる時間かをチェック
 *
 * @param	inTime		時間
 *
 * @return  BOOL	TRUE:エンカウント可		FALSE：エンカウント不可
 */
//==============================================================================
static const BOOL CheckHoneyTreeEncTime(const int inTime)
{
///	OS_Printf("time%d\n",inTime);
	if ( (0<inTime)&&(inTime<=ENC_START_TIME) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * トレーナーＩＤをキーにして当たりを割り出す
 *
 * @param	inTrainerID		トレーナーＩＤ
 * @param	inIndex			現在の木インデックス
 *
 * @return	BOOL		TRUE:当たり		FALSE:ハズレ
 */
//==============================================================================
static BOOL CheckRareFlg(const u32 inTrainerID, const u8 inIndex)
{
	u8 i,j;
	u8 temp[4];
	//4つに分割
	temp[0] = (inTrainerID >> 24) & 0xff;
	temp[1] = (inTrainerID >> 16) & 0xff;
	temp[2] = (inTrainerID >> 8) & 0xff;
	temp[3] = inTrainerID & 0xff;

	temp[0] %= HONEY_TREE_MAX;
	temp[1] %= HONEY_TREE_MAX;
	temp[2] %= HONEY_TREE_MAX;
	temp[3] %= HONEY_TREE_MAX;

	for(i=1;i<4;i++){
		for(j=0;j<i;j++){
			if (temp[j] == temp[i]){
				temp[i]++;
				if (temp[i]>=HONEY_TREE_MAX){
					temp[i] = 0;
				}
			}
		}
	}

	OS_Printf("honey_rare_hit:%d,%d,%d,%d\n",temp[0],temp[1],temp[2],temp[3]);

	for(i=0;i<4;i++){
		if (inIndex == temp[i]){
			return TRUE;	//当たり
		}
	}

	return FALSE;		//ハズレ
}

//==============================================================================
/**
 * 蜜塗り木のエンカウントポケモンを取得
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	int			モンスターナンバー
 */
//==============================================================================
int HTE_GetHoneyTreeMonster(FIELDSYS_WORK *fsys)
{
	u8 tree_no;
	//現在のゾーンIDを取得
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"蜜塗り木が登録されていません" );
	{
		int *tbl;
		int monsno;
		HT_PTR ptr;
		HONEY_DATA *data;

		ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
///		ptr = HTSave_GetHoneyTree(fsys->savedata);
		data = HTSave_GetHoneyDataPtr(tree_no, ptr);
		if( PM_VERSION == VERSION_DIAMOND ){		//ダイヤ
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, HoneyEncArcTbl_Dia[data->TblNo], HEAPID_FIELD);
		}else{										//パール
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, HoneyEncArcTbl_Perl[data->TblNo], HEAPID_FIELD);
		}
#ifdef PM_DEBUG		
		{
			int i;
			OS_Printf("テーブル検証\n");
			for(i=0;i<5;i++){
				OS_Printf("%d,",tbl[i]);
			}
			OS_Printf("\n");
		}
#endif
		monsno = tbl[data->TblMonsNo];
		sys_FreeMemoryEz(tbl);
		return monsno;
	}
}

//==============================================================================
/**
 * アニメセットコールバック
 *
 * @param	work			ワーク
 * @param	inBlockIndex	ブロックインデックス
 * @param	inObjList		OBJリスト
 *
 * @return	none
 */
//==============================================================================
void HTE_SetHoneyTreeAnimeCallBack(void* work, const int inBlockIndex, const M3DOL_PTR inObjList)
{
	FIELDSYS_WORK *fsys;
	u8 tree_no;
	if (inBlockIndex<0){
		return;
	}

	fsys = (FIELDSYS_WORK *)work;
	SetHoneyTreeAnimation(fsys, inObjList, inBlockIndex);
}

//==============================================================================
/**
 * 現在いるゾーンの蜜木アニメフラグを落とす
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 */
//==============================================================================
void HTE_ResetAnimeFlg(FIELDSYS_WORK *fsys)
{
	HT_PTR ptr;
	HONEY_DATA *data;
	u8 tree_no;
	//現在のゾーンIDを取得
	tree_no = GetTreeNoFromZoneID(fsys->location->zone_id);
	GF_ASSERT(tree_no!=HONEY_TREE_MAX&&"蜜塗り木が登録されていません" );
	fsys->HoneyTreePtr->HoneyData[tree_no].AnimeFlg = FALSE;
	
	ptr = EncDataSave_GetHoneyTree(EncDataSave_GetSaveDataPtr(fsys->savedata));
	data = HTSave_GetHoneyDataPtr(tree_no, ptr);
	//蜜データの時間を0にする
	data->Time = 0;
}
