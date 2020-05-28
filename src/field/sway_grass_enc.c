//============================================================================================
/**
 * @file	sway_grass_enc.c
 * @brief	揺れ草エンカウント
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================

#include "sway_grass_enc.h"
#include "field_effect.h"
#include "map_tool.h"

#include "fieldsys.h"	//for savedata

#include "bounding_box.h"

#include "battle/battle_common.h"	//for FIGHT_WIN, FIGHT_POKE_GET

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "savedata/encount.h"

#include "itemtool/itemsym.h"
#include "encount_define.h"

#include "script.h"		//for GetEvScriptWorkMemberAdrs
#include "fielddata/script/pokesearcher_def.h"
#include "sway_grass_hist.h"

#define ISMIN(rc,a,b) { \
	(a<b)? (rc=TRUE):(rc=FALSE); \
}

#define SEARCH_AROUND		(4)
#define SEARCH_WIDTH_MAX	(9)
#define SEARCH_OFFS			(SEARCH_WIDTH_MAX/2)
#define SERCH_NUM_ROUND1	(32)	//外周外側
#define SERCH_NUM_ROUND2	(24)	//↓
#define SERCH_NUM_ROUND3	(16)	//↓
#define SERCH_NUM_ROUND4	(8)		//外周内側

#define RARE_POKE_PROP_MAX	(8200)	//分母最大8200
#define RARE_POKE_PROP_MIN	(200)	//分母最小200
#define SUB_PROP			(200)	//差し引く確率

enum {
	SEQ_SWAY_SEARCH,
	SEQ_SWAY_BGM_START,
	SEQ_SWAY_WAIT,
	SEQ_SWAY_NG,
	SEQ_SWAY_END
};

typedef struct SWAY_GRASS_INFO_tag
{
	int GridX;
	int GridZ;
	int EncTblCode;	//エンカウントするテーブルコード
	BOOL	SwayGrassFlg;
	BOOL	ChainFlg;	//連鎖フラグ
	BOOL	IsRare;
	EOA_PTR	GrassAnime;
	VecFx32 GrassPos;
}SWAY_GRASS_INFO;

typedef struct SWAY_GRASS_tag{
	int EncTblCode;			//エンカウントしたテーブルコード
	int Chain;				//連鎖回数
	int EncMonsNo;			//揺れ草エンカウントしたモンスターナンバー
	int EncMonsLv;				//揺れ草エンカウントしたモンスターレベル
	BOOL Valid;		//揺れ草中かどうか
	BOOL FirstEnc;			//初揺れ草エンカウントか
	BOOL SwayEncReturn;	//ゆれ草戦闘として復帰したか
	SWAY_GRASS_INFO GrassInfo[SEARCH_AROUND];
	BOUNDING_BOX	BoundingBox;
	u8 RewritePos;			//チェーンレコード書き換え位置
}SWAY_GRASS;

static BOOL SetSwayGrassInfo(	FIELDSYS_WORK * fsys,
							const fx32 inPlayerHeight,
							const int inX, const int inZ,
							const u8 inSearchX, const u8 inSearchZ,
							SWAY_GRASS_INFO *outInfo	);
static BOOL CheckSwayGrass(	const SWAY_GRASS_PTR inSwayGrass,
							const int inX, const int inZ,
							u8 *outRound);
static void UpdateSwayGrassHist(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR ioSwayGrass);
static u8 GetSwayGrassMinRecordPos(FIELDSYS_WORK * fsys);
static BOOL GetChainFlg(const u8 inRound, const int inBattleResult);
static BOOL SwayGrassSetupEvent(GMEVENT_CONTROL * event);
static BOOL CheckRare(const int inChain);
static void IncChain(int *outChain);

//-----------------------------------------------------------------------------
/**
 * @brief	メモリ確保関数
 * @param	inHeapID	ヒープID
 * 
 * @retval	ptr			ゆれ草構造体へのポインタ
 *
 */
//-----------------------------------------------------------------------------
SWAY_GRASS_PTR SwayGrass_AllocSwayGrass(const int inHeapID)
{
	SWAY_GRASS_PTR ptr;
	ptr = sys_AllocMemory(inHeapID, sizeof(SWAY_GRASS) );
	//バウンディングボックス作成(幅１グリッド分、高さ半グリッド分、奥行き１グリッド分)
	BB_MakeBoundingBox(FX32_ONE*16,FX32_ONE*8,FX32_ONE*16,&ptr->BoundingBox);
	return ptr;
}

//-----------------------------------------------------------------------------
/**
 * @brief	メモリ解放関数	(ゲーム始めに確保して、そのままなので解放しないかも)
 * @param	outSwayGrass		ゆれ草構造体へのポインタ
 * 
 * @retval	
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_FreeSwayGrass(SWAY_GRASS_PTR outSwayGrass)
{
	sys_FreeMemoryEz(outSwayGrass);
}

//-----------------------------------------------------------------------------
/**
 * @brief	初期化
 * @param	outSwayGrass		ゆれ草構造体へのポインタ
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_InitSwayGrass(SWAY_GRASS_PTR outSwayGrass)
{
	u8 i;
	outSwayGrass->Chain = 0;
	outSwayGrass->EncTblCode = SWAY_GRASS_ENC_NORMAL;
	outSwayGrass->EncMonsNo = 0;
	outSwayGrass->EncMonsLv = 0;
	outSwayGrass->Valid = FALSE;
	outSwayGrass->RewritePos = 0;
	outSwayGrass->FirstEnc = TRUE;
	outSwayGrass->SwayEncReturn = FALSE;
	
	MI_CpuClear8(&(outSwayGrass->GrassInfo[0]), sizeof(SWAY_GRASS_INFO)*SEARCH_AROUND);
	for(i=0;i<SEARCH_AROUND;i++){
		outSwayGrass->GrassInfo[i].SwayGrassFlg = FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	揺れ草捜索
 * @param	fsys			フィールドシステムポインタ
 * @param	inX				検索中心X座標
 * @param	inZ				検索中心Z座標
 * @param	ioSwayGrass	揺れ草構造体へのポインタ
 * 
 * @retval	BOOL		TRUE:揺れ草有効　FALSE:揺れ草無効
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_SearchSwayGrass(	FIELDSYS_WORK * fsys,
								const int inX, const int inZ,
								SWAY_GRASS_PTR ioSwayGrass)
{
	u8 i;				//外周カウンタ
	u8 size_x,size_z;	//外周縦横サイズ
	u8 num;				//決定番号
	u8 t_num;			//計算テンポラリ
	int x,z;			//座標
///	BOOL chain_flg;		//連鎖フラグ
	u8 valid_num;		//揺れ草数

	const VecFx32 *player_vec;

	u8	rand_list[SEARCH_AROUND] = {	//ランダムテーブル（各外周毎のランダム最大値）
		SERCH_NUM_ROUND1,	//一番外側
		SERCH_NUM_ROUND2,
		SERCH_NUM_ROUND3,
		SERCH_NUM_ROUND4	//一番内側
	};

	//自機高さ取得
	player_vec = Player_VecPosPtrGet( fsys->player );

	valid_num = 0;
	for(i=0;i<SEARCH_AROUND;i++){
		BOOL rc;
		//対象座標をランダムで決定
		num = gf_p_rand(rand_list[i]);
		//OS_Printf("num%d\n",num);
		//横幅設定
		size_x = SEARCH_WIDTH_MAX-(i*2);
		//縦幅設定
		size_z = SEARCH_WIDTH_MAX-(i*2);

		//決定した番号を幅で割る
		t_num = num/size_x;
		//商が0なら外周上、1なら下
		//上、下にヒットした場合、余りでｘ座標を決定（ｚは商で）
		if (t_num == 0){
			x = i+num%size_x;
			z = i;
		}else if(t_num == 1){
			x = i+num%size_x;
			z = i+size_z-1;
		}else{
			//	//ヒットしなかった場合、決定した番号-幅*2する
			GF_ASSERT( num>=(size_x*2) );
			t_num = num-(size_x*2);
			//加工した番号を2で割る
			//商+1でzが分かる（ｘは左側か、右側かなので、幅で判断）
			z = i+(t_num/2)+1;
			if (t_num%2 == 0){	//外周左側面
				x = i;
			}else{				//外周右側面
				x = i+size_x-1;
			}
		}
#if 0		
		//連鎖するかどうかを決定
		chain_flg = GetChainFlg(i,inBattleResult);
#endif
		//OS_Printf("grass_anime%d,%d\n",x,z);

		//決定した座標の情報をセット
		rc = SetSwayGrassInfo(	fsys, player_vec->y, inX, inZ, x, z,
								&ioSwayGrass->GrassInfo[i]);
		if (rc){
			valid_num++;
		}
	}

	if (valid_num == 0){
		SwayGrass_InitSwayGrass(ioSwayGrass);
		//曲終わらせる
		Snd_FadeOutNextPlayCall(fsys,
								Snd_FieldBgmNoGet(fsys,fsys->location->zone_id),
								BGM_FADE_FIELD_MODE );
	}else{
		ioSwayGrass->Valid = TRUE;
	}

	return ioSwayGrass->Valid;
}

//-----------------------------------------------------------------------------
/**
 * @brief	連鎖設定
 * @param	fsys			フィールドシステムポインタ
 * @param	inBattleResult	戦闘結果	 FIGHT_WIN	FIGHT_POKE_GET
 * @param	ioSwayGrass	揺れ草構造体へのポインタ
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void	SwayGrass_SetChain(	FIELDSYS_WORK * fsys,
								const int inBattleResult,
								SWAY_GRASS_PTR ioSwayGrass)
{
	u8 i;				//外周カウンタ
	for(i=0;i<SEARCH_AROUND;i++){
		if ( ioSwayGrass->GrassInfo[i].SwayGrassFlg){
			//連鎖するかどうかを決定
			ioSwayGrass->GrassInfo[i].ChainFlg = GetChainFlg(i,inBattleResult);//連鎖フラグセット
			//次回エンカウントするテーブルをセット
			if (!ioSwayGrass->GrassInfo[i].ChainFlg){
				//連鎖しないのでテーブルの抽選(確率は1/2)
				if(gf_p_rand(100) < 50){	//ノーマル
					ioSwayGrass->GrassInfo[i].EncTblCode = SWAY_GRASS_ENC_NORMAL;
				}else{		//テーブル変更
					ioSwayGrass->GrassInfo[i].EncTblCode = SWAY_GRASS_ENC_SP;
				}
				ioSwayGrass->GrassInfo[i].IsRare = FALSE;
			}else{
				//連鎖する場合は前回のテーブルを引き継ぐ
				ioSwayGrass->GrassInfo[i].EncTblCode = ioSwayGrass->EncTblCode;
				//レアポケモン抽選
				ioSwayGrass->GrassInfo[i].IsRare = CheckRare(fsys->SwayGrass->Chain);
			}
		}
	}
}


//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草アニメセット
 * @param	fsys		フィールドシステムポインタ
 * @param	outSwayGrass		ゆれ草構造体へのポインタ
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_SetSwayGrassAnime(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR outSwayGrass)
{
	u8 i;
	for(i=0;i<SEARCH_AROUND;i++){
		if (outSwayGrass->GrassInfo[i].SwayGrassFlg){
			int x = outSwayGrass->GrassInfo[i].GridX;
			int z = outSwayGrass->GrassInfo[i].GridZ;
			//レアフラグが成立しているかでアニメ分岐
			if (outSwayGrass->GrassInfo[i].IsRare){
				//レアポケモンエンカウント用アニメセット
				outSwayGrass->GrassInfo[i].GrassAnime =
					FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_KIRAKIRA );
			}else{
				//セットされているテーブルコードでアニメを分岐
				if (outSwayGrass->GrassInfo[i].EncTblCode == SWAY_GRASS_ENC_NORMAL){
					//通常テーブル
					outSwayGrass->GrassInfo[i].GrassAnime =
						FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_SMALL );
				}else{
					//揺れ草専用テーブル
					outSwayGrass->GrassInfo[i].GrassAnime =
						FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_BIG );
				}
			}
		}else{
			outSwayGrass->GrassInfo[i].GrassAnime = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草アニメ終了待ち
 * @param	ioSwayGrass		ゆれ草構造体へのポインタ
 * 
 * @retval	BOOL	TRUE:アニメ終了	FALSE:アニメ継続
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckSwayGrassAnimeEnd(SWAY_GRASS_PTR ioSwayGrass)
{
	u8 count;
	u8 i;
	count = 0;
	for(i=0;i<SEARCH_AROUND;i++){
		if (ioSwayGrass->GrassInfo[i].GrassAnime != NULL){
			
			if (FE_EncGrass_AnimeCheck( ioSwayGrass->GrassInfo[i].GrassAnime )){
				EOA_Delete( ioSwayGrass->GrassInfo[i].GrassAnime );
				ioSwayGrass->GrassInfo[i].GrassAnime = NULL;
				count++;
			}
		}else{
			count++;
		}
	}
	if(count >= SEARCH_AROUND){
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草チェック
 * @param	fsys		フィールドシステムポインタ
 * @param	ioSwayGrass		ゆれ草構造体へのポインタ
 * @param	outUseEncTable	使用するエンカウントテーブルコード
 * @param	outMonsDeside	エンカウントするポケモンが決定しているかを見るフラグ
 * 
 * @retval	BOOL	TRUE:揺れ草エンカウント成立　FALSE:揺れ草エンカウント不成立
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckSpEncount(	const int inX, const int inZ,
								FIELDSYS_WORK * fsys,
								SWAY_GRASS_PTR ioSwayGrass,
								int *outUseEncTable,
								BOOL *outMonsDeside,
								BOOL *outRare)
{
	u8 round;
	BOOL chain_flg;
	int tbl_code;
	
	*outMonsDeside = FALSE;
	*outRare = FALSE;
	//ゆれ草エンカウントかどうかをチェック
	if ( !CheckSwayGrass(ioSwayGrass, inX, inZ, &round) ){
		//踏んだ座標が揺れ草ではない
		return FALSE;//SWAY_GRASS_ENC_NO_ENC;
	}
	
	ioSwayGrass->SwayEncReturn = TRUE;	//戦闘後はゆれ草
	
	chain_flg = ioSwayGrass->GrassInfo[round].ChainFlg;
	tbl_code = ioSwayGrass->GrassInfo[round].EncTblCode;
	//初めてエンカウントかをチェック	
	if(ioSwayGrass->FirstEnc == FALSE){ //初めてではない
		if(chain_flg){			//連鎖成立なら、同じポケモン
			IncChain(&(ioSwayGrass->Chain));		//連鎖回数+1
			//*outUseEncTable = ioSwayGrass->EncTblCode;//保存しといたコード
			*outUseEncTable = tbl_code;	//SwayGrassのメンバから直に取ることも可能だけれども、Infoから取る
			*outMonsDeside = TRUE;
			//揺れ草エンカウント履歴チェックと更新
			UpdateSwayGrassHist(fsys, ioSwayGrass);
			//ioSwayGrass->SwayGrassEnc = TRUE;	//揺れ草エンカウント中フラグオン
			
			(*outRare) = ioSwayGrass->GrassInfo[round].IsRare;	//レアフラグセット
			
			return TRUE;//SWAY_GRASS_ENC_KEEP_MONSTER;
		}else{		//違うポケモン
			*outUseEncTable = tbl_code;	//エンカウントテーブルコードセット
		}
	}else{	//初めて揺れ草
		*outUseEncTable = tbl_code;
		ioSwayGrass->FirstEnc = FALSE;
		//書き換え対象となる揺れ草エンカウント履歴を取得する
		//(3つの履歴の中で一番連鎖数が少ないレコードの場所を取得する)
		ioSwayGrass->RewritePos = GetSwayGrassMinRecordPos(fsys);
	}
	
	//どっちのテーブルを適用したかを保存
	ioSwayGrass->EncTblCode = *outUseEncTable;

	//ioSwayGrass->SwayGrassEnc = TRUE;	//揺れ草エンカウント中フラグオン
	
	return TRUE;//SWAY_GRASS_ENC_START;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草エンカウントポケモンを記憶(ナンバー、レベル)
 * @param	outSwayGrass		ゆれ草構造体へのポインタ
 * @param	inMonsNo			エンカウントモンスターナンバー
 * @param	inMonsLv			エンカウントモンスターレベル
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_SetEncMonsNoLv(SWAY_GRASS_PTR outSwayGrass, const int inMonsNo, const int inMonsLv)
{
	GF_ASSERT(inMonsNo != 0);
	outSwayGrass->EncMonsNo = inMonsNo;
	outSwayGrass->EncMonsLv = inMonsLv;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草エンカウントポケモンを取得（ナンバー、レベル）
 * @param	inSwayGrass		ゆれ草構造体へのポインタ
 * @param	outMonsNo		エンカウントモンスターナンバー格納先
 * @param	outMonsLv		エンカウントモンスターレベル格納先
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_GetEncMonsNoLv(SWAY_GRASS_PTR inSwayGrass,  int *outMonsNo, int *outMonsLv)
{
	(*outMonsNo) = inSwayGrass->EncMonsNo;
	(*outMonsLv) = inSwayGrass->EncMonsLv;

}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草エンカウント復帰かを調べる
 * @param	inSwayGrass		ゆれ草構造体へのポインタ
 * @retval	BOOL		TRUE:揺れ草エンカウント復帰		FALSE:通常エンカウント復帰				
 *
 */
//-----------------------------------------------------------------------------
const BOOL SwayGrass_IsSwayEncRetern(const SWAY_GRASS_PTR inSwayGrass)
{
	return inSwayGrass->SwayEncReturn;
}

//-----------------------------------------------------------------------------
/**
 * @brief	画面内外チェック
 * @param	fsys			フィールドシステムポインタ
 * @param	inX				検索中心X座標
 * @param	inZ				検索中心Z座標
 * @param	inSearchX		検索X座標（相対）
 * @param	inSearchZ		検索Z座標（相対）
 * @param	inChainFlg		連鎖フラグ
 * @param	inEncTblCode	現在のエンカウントテーブルコード
 * @param	outInfo			ゆれ草情報構造体へのポインタ
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_CheckIO(FIELDSYS_WORK * fsys)
{
	BOOL rc;
	SWAY_GRASS_INFO *info;
	
	int i;

	if ((!fsys->SwayGrass->Valid)||(fsys->event!=NULL)){
		return;
	}
	
	//画面内外チェック
	for(i=0;i<SEARCH_AROUND;i++){
		info = &(fsys->SwayGrass->GrassInfo[i]);
		rc = BB_CullingCheck3DModelNonResQuick( &(info->GrassPos),
											 &(fsys->SwayGrass->BoundingBox) );
		if ((info->SwayGrassFlg)&&(!rc)){
			//無効にする
			info->SwayGrassFlg = FALSE;
		}
	}
	//全部無効かをチェック
	{
		int count;
		count = 0;
		for(i=0;i<SEARCH_AROUND;i++){
			info = &(fsys->SwayGrass->GrassInfo[i]);
			if (info->SwayGrassFlg == FALSE){
				count++;
			}
		}
		if (count == SEARCH_AROUND){
			///OS_Printf("揺れ草は無効になりました\n");
			SwayGrass_InitSwayGrass(fsys->SwayGrass);			
			//曲終わらせる
			Snd_FadeOutNextPlayCall(fsys,
									Snd_FieldBgmNoGet(fsys,fsys->location->zone_id),
									BGM_FADE_FIELD_MODE );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草有効チェック
 * @param	inSwayGrass	揺れ草構造体へのポインタ
 *
 * @retval	BOOL	TRUE:揺れ草有効		FALSE:揺れ草無効
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckValid( const SWAY_GRASS_PTR inSwayGrass )
{
	return inSwayGrass->Valid;
}


//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草情報セット
 * @param	fsys			フィールドシステムポインタ
 * @param	inPlayerHeight	自機高さ
 * @param	inX				検索中心X座標
 * @param	inZ				検索中心Z座標
 * @param	inSearchX		検索X座標（相対）
 * @param	inSearchZ		検索Z座標（相対）
 * @param	outInfo			ゆれ草情報構造体へのポインタ
 * 
 * @retval	BOOL			TRUE:揺れ草有効		FALSE:揺れ草無効
 *
 */
//-----------------------------------------------------------------------------
static BOOL SetSwayGrassInfo(	FIELDSYS_WORK * fsys,
								const fx32 inPlayerHeight,
								const int inX, const int inZ,
								const u8 inSearchX, const u8 inSearchZ,
								SWAY_GRASS_INFO *outInfo	)
{
	int x,z;
	MATR attr;
	x = (inX-SEARCH_OFFS)+inSearchX;
	z = (inZ-SEARCH_OFFS)+inSearchZ;
	//座標保存
	outInfo->GridX = x;
	outInfo->GridZ = z;
	//アトリビュート捜査
	attr = GetAttributeLSB(fsys, x, z);
	
	if (  MATR_IsGrass(attr) ){
		HEIGHT_TYPE code;
		//fx32型の座標を取得
		outInfo->GrassPos.x = FX32_ONE*16*x;
		outInfo->GrassPos.z = FX32_ONE*16*z;
		outInfo->GrassPos.y = GetHeightPack(fsys,
											0, outInfo->GrassPos.x, outInfo->GrassPos.z,
											&code);
		//高さを取得して、自機の高さと比較する
		if (inPlayerHeight != outInfo->GrassPos.y){
			//高さが同一ではないので、はねる
			outInfo->SwayGrassFlg = 0;
			OS_Printf("高さが違うので、揺れ草とみなさい\n");
			return FALSE;
		}
		//ゾーンＩＤが違う場合は、はねる
		{
			int zone_id;
			int block_x,block_z;
			block_x = x/BLOCK_GRID_W;
			block_z = z/BLOCK_GRID_H;
			zone_id = World_GetZoneIDFromMatrixXZ(fsys->World, block_x, block_z);
			if (fsys->location->zone_id != zone_id){
				outInfo->SwayGrassFlg = 0;
				OS_Printf("ゾーンＩＤ違うので、揺れ草とみなさい\n");
				return FALSE;
			}
		}
		

		//草ならゆれ草フラグを立てる
		outInfo->SwayGrassFlg = 1;
		
		return TRUE;
	}else{
		//草ではないのでフラグオフ
		outInfo->SwayGrassFlg = 0;
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草チェック
 * @param	inSwayGrass	揺れ草構造体へのポインタ
 * @param	inX			X座標
 * @param	inZ			Z座標
 * @param	outRound	ヒットした周回
 *
 * @retval	BOOL	TRUE:揺れ草ヒット		FALSE:揺れ草ヒットしてない
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckSwayGrass(	const SWAY_GRASS_PTR inSwayGrass,
							const int inX, const int inZ,
							u8 *outRound)
{
	u8 i;
	for(i=0;i<SEARCH_AROUND;i++){
		if (inSwayGrass->GrassInfo[i].SwayGrassFlg){
			if ( (inSwayGrass->GrassInfo[i].GridX == inX) &&
					(inSwayGrass->GrassInfo[i].GridZ == inZ) ){
				*outRound = i;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゆれ草履歴チェックと更新
 * @param	fsys		フィールドシステムポインタ	
 * @param	inSwayGrass	ゆれ草構造体へのポインタ	
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
static void UpdateSwayGrassHist(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR ioSwayGrass)
{
	SWAY_GRASS_HIST * hist;
	int chain;
	int i;
	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	chain = hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain;
	if (chain < ioSwayGrass->Chain){//記録を上回ったか？
		//更新
		hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain = ioSwayGrass->Chain;
		hist->SwayGrassRec[ioSwayGrass->RewritePos].MonsNo = ioSwayGrass->EncMonsNo;
		//ソート
		SwayGrassHist_SortHistData(hist);
		//書き換え位置の捜索
		if (hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain <= ioSwayGrass->Chain){
			//書き換え位置がずれたので捜索
			for(i=0;i<3;i++){
				if ( hist->SwayGrassRec[(2-i)].Chain == ioSwayGrass->Chain){
					ioSwayGrass->RewritePos = (2-i);
					return;
				}	
			}
			//ここにはこないはず。きてしまった場合は従来の書き換え位置を持続する(書き換え位置変更しない)
			GF_ASSERT(0);
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	揺れ草レコード内の書き換え位置を取得
 *
 * @param	fsys	フィールドシステムポインタ	
 *
 * @retval	u8		書き換え位置
 *
 */
//-----------------------------------------------------------------------------
static u8 GetSwayGrassMinRecordPos(FIELDSYS_WORK *fsys)
{
	SWAY_GRASS_HIST * hist;
	u8 pos;
	BOOL rc;

	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );

	//ランキングがされていないときの位置取得
	for(pos=0;pos<3;pos++){
		if (hist->SwayGrassRec[pos].MonsNo == 0){
			return pos;
		}
	}

	//ランキングが埋まっているときの位置取得
	ISMIN(rc,hist->SwayGrassRec[0].Chain,hist->SwayGrassRec[1].Chain);
	if (rc){
		pos = 0;
	}else{
		pos = 1;
	}
	ISMIN(rc,hist->SwayGrassRec[pos].Chain,hist->SwayGrassRec[2].Chain);
	if (!rc){
		pos = 2;
	}

	return pos;
}

//-----------------------------------------------------------------------------
/**
 * @brief	連鎖フラグの決定
 *
 * @param	inRound			外周
 * @param	inBattleResult	戦闘結果 FIGHT_WIN	FIGHT_POKE_GET
 * 
 * @retval	BOOL		連鎖フラグ	TURE:連鎖する	FALSE:連鎖しない	
 *
 */
//-----------------------------------------------------------------------------
static BOOL GetChainFlg(const u8 inRound, const int inBattleResult)
{
	//同じポケモンを出すかを確率で決める
	u8 *tbl;
	u8 table1[SEARCH_AROUND] = {88,68,48,28};
	u8 table2[SEARCH_AROUND] = {98,78,58,38};
	//前回、捕獲して戦闘を終了したかでテーブルを変更
	if (inBattleResult == FIGHT_WIN){
		tbl = table1;
	}else if(inBattleResult == FIGHT_POKE_GET){
		tbl = table2;
	}
	if(gf_p_rand(100)<tbl[inRound]){			//連鎖する
		return TRUE;
	}else{		//連鎖しない
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	初回揺れ草起動
 *
 * @param	*fsys		フィールドシステムポインタ
 * 
 * @retval	none	
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_Setup(FIELDSYS_WORK * fsys)
{
	int *seq;
	seq = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(int));
	(*seq) = 0;
	//イベントセット
	FieldEvent_Set(fsys, SwayGrass_SetupEvent, seq);
}

//-----------------------------------------------------------------------------
/**
 * @brief	初回揺れ草セットイベント
 * 
 * @param	*event		イベントポインタ
 * 
 * @retval	BOOL	TRUE:終了	FALSE:継続
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_SetupEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int *seq = FieldEvent_GetSpecialWork(event);
	
	switch (*seq) {
	case SEQ_SWAY_SEARCH:
		{
			u8 *charge;
			//ＯＢＪポーズ
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			//ポケサーチャー使用可能チェック(充電完了しているか？)
			//セーブデータ取得
			charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
			if ( (*charge)<POKESEARCHER_CHARGE_MAX ){
				EventCall_Script(event, SCRID_POKE_SEARCHER, NULL, NULL);
				*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM0)) = POKESEARCHER_CHARGE_MAX-(*charge);
				(*seq) = SEQ_SWAY_END;
			}else{
				int x,z;
				//ポケサーチャー充電クリア
				(*charge) = 0;
				//自機の位置取得
				x = Player_NowGPosXGet(fsys->player);
				z = Player_NowGPosZGet(fsys->player);
				//草サーチ
				SwayGrass_SearchSwayGrass(fsys, x, z,fsys->SwayGrass);
				if (fsys->SwayGrass->Valid){
					SwayGrass_SetChain(fsys, FIGHT_WIN, fsys->SwayGrass);	//初回テーブルは戦闘勝利で固定
					//草アニメセット
					SwayGrass_SetSwayGrassAnime(fsys, fsys->SwayGrass);
					(*seq) = SEQ_SWAY_BGM_START;
				}else{
					(*seq) = SEQ_SWAY_NG;
				}
			}
		}
		break;
	case SEQ_SWAY_BGM_START:
		//曲開始
		//Snd_FadeOutNextPlayCall( fsys, SEQ_KUSAGASA, BGM_FADE_FIELD_MODE );
		Snd_BgmPlay( SEQ_KUSAGASA );											//06.05.18
		(*seq) = SEQ_SWAY_WAIT;
		break;
	case SEQ_SWAY_WAIT:
		//アニメ終了待ち
		if (SwayGrass_CheckSwayGrassAnimeEnd(fsys->SwayGrass)){
			(*seq) = SEQ_SWAY_END;
		}
		break;
	case SEQ_SWAY_END:
		//終了
		sys_FreeMemoryEz(seq);
		//OBJポーズクリア
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;
		break;
		
	case SEQ_SWAY_NG:
		// メッセージ表示
		EventCall_Script( event, SCRID_POKE_SEARCHER_NG, NULL, NULL );
		(*seq) = SEQ_SWAY_END;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	レアチェック
 * 
 * @param	inChain		連鎖回数
 * 
 * @retval	BOOL	TRUE:レア	FALSE:ノーマル
 *
 */
//-----------------------------------------------------------------------------
#if 0
static BOOL CheckRare(const int inChain)
{
	int prop;
	if (inChain == 0){
		return FALSE;
	}
	
	prop = RARE_POKE_PROP_MAX - (inChain*SUB_PROP);
	if (prop < 0){
		prop = 1;
	}

	if ( gf_rand()%prop == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}
#else
static BOOL CheckRare(const int inChain)
{
	int prop;
	if (inChain == 0){
		return FALSE;
	}
	
	prop = RARE_POKE_PROP_MAX - (inChain*SUB_PROP);
	if (prop < RARE_POKE_PROP_MIN){
		prop = RARE_POKE_PROP_MIN;
	}

	if ( gf_p_rand(prop) == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}
#endif

//-----------------------------------------------------------------------------
/**
 * @brief	連鎖数更新（ハズレ引いたけど同じポケモンとエンカウントしたとき用）
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_UpDateChain(FIELDSYS_WORK * fsys)
{
	IncChain(&(fsys->SwayGrass->Chain));	//連鎖回数+1
	//揺れ草エンカウント履歴チェックと更新
	UpdateSwayGrassHist(fsys, fsys->SwayGrass);
}

#if 0
//-----------------------------------------------------------------------------
/**
 * @brief	履歴書き換え位置更新
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_ChangeHistRewritePos(FIELDSYS_WORK * fsys)
{
	fsys->SwayGrass->RewritePos = GetSwayGrassMinRecordPos(fsys);
}
#endif

//-----------------------------------------------------------------------------
/**
 * @brief	チェーン数取得
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @retval	int		チェーン数
 *
 */
//-----------------------------------------------------------------------------
int SwayGrass_GetChain(FIELDSYS_WORK * fsys)
{
	return fsys->SwayGrass->Chain;
}

//==============================================================================
/**
 * ポケサーチャーチャージ<<名前がポケトレになったらしい。まぎらわしい。
 *
 * @param	fsys			フィールドシステムポインタ
 *
 * @return	none
 */
//==============================================================================
void SwayGrass_ChargePokeSearcher(FIELDSYS_WORK *fsys)
{
	u8 *charge;
	//ポケサーチャーを持っているかチェック
	if( MyItem_CheckItem( SaveData_GetMyItem(fsys->savedata),
							ITEM_POKETORE,1,HEAPID_FIELD) == TRUE ){
		//セーブデータ取得
		charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
		if ( (*charge)<POKESEARCHER_CHARGE_MAX ){
			(*charge)++;
		}
	}
}

//==============================================================================
/**
 * 連鎖数の加算
 *
 * @param	outChain		連鎖数へのポインタ
 *
 * @return	none
 */
//==============================================================================
static void IncChain(int *outChain)
{
	(*outChain)++;
	if ( (*outChain) > SWAY_GRASS_CHAIN_MAX ){
		(*outChain) = SWAY_GRASS_CHAIN_MAX;
	}
}

#ifdef PM_DEBUG
//-----------------------------------------------------------------------------
/**
 * @brief	チェーン数変更
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	n		数
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_DebugIncChain(FIELDSYS_WORK * fsys, int n)
{
	if (fsys->SwayGrass->Chain + n > SWAY_GRASS_CHAIN_MAX){
		fsys->SwayGrass->Chain = SWAY_GRASS_CHAIN_MAX;
	}else{
		fsys->SwayGrass->Chain += n;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	チェーン数セット
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	n		数
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_DebugSetChain(FIELDSYS_WORK * fsys, int n)
{
	if (n > SWAY_GRASS_CHAIN_MAX){
		fsys->SwayGrass->Chain = SWAY_GRASS_CHAIN_MAX;
	}else{
		fsys->SwayGrass->Chain = n;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	草情報取得
 * 
 * @param	fsys	フィールドシステムポインタ
 * @param	inIdx	情報構造体インデックス	0～3
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_GetGrassInfo(FIELDSYS_WORK * fsys, const u8 inIdx,
							int *outX, int *outZ, u8 *outTbl,
							BOOL *outValid, BOOL *outChainFlg, BOOL *outRare)
{
	SWAY_GRASS_INFO *info;
	GF_ASSERT(inIdx<SEARCH_AROUND);

	info = &fsys->SwayGrass->GrassInfo[inIdx];

	(*outX) = info->GridX;
	(*outZ) = info->GridZ;
	(*outTbl) = info->EncTblCode;
	(*outValid) = info->SwayGrassFlg;
	(*outChainFlg) = info->ChainFlg;
	(*outRare) = info->IsRare;


}

#endif
