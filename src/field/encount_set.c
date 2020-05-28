//============================================================================================
/**
 * @file	encount_set.c
 * @brief	エンカウント関連

 * @author	saitou
 *
 * 2005.12.18	field_encount.cからエンカウント判定部分を移動
 */
//============================================================================================
#include "encount_set.h"
#include "syswork.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "eventdata.h"
#include "honey_tree_enc.h"

#include "field_encount.h"
#include "battle/tokusyu_def.h"

#include "system/pm_rtc.h"
#include "system/timezone.h"
#include "sysflag.h"
#include "system/zukanwork.h"
#include "debug_saito.h"

#include "situation_local.h"

#include "enc_tbl_change_def.h"
#include "arc/encdata_ex.naix"

#include "savedata/encount.h"
#include "move_pokemon_def.h"
#include "move_pokemon.h"
#include "encount_define.h"

#include "generate_zone.h"
#include "calendar_enc.h"
#include "sp_fishing_enc.h"

#include "weather_sys.h"
#include "fieldmap_work.h"
#include "field_fishing.h"
#include "ev_time.h"

#include "zonedata.h"

#include "battle/battle_server.h"	//for	FormChange
#include "ev_pokemon.h"
#include "itemtool/itemsym.h"		//for ITEM_KIYOMENOOHUDA・ITEM_KIYOMENOOKOU
#include "savedata/vidro_type.h"

#include "safari_enc.h"
#include "agb_slot_enc.h"

#include "poketool/tr_tool.h"
#include "battle/trno_def.h"		//BTFIVEの代入のための暫定なはず by soga

//============================================================================================
//============================================================================================


#define	WALK_COUNT_GLOBAL	( 8 )		// エンカウントしない歩数の基本値
#define	WALK_NEXT_PERCENT	( 5 )		// 歩数カウント失敗で次の処理に進む確率
#define	NEXT_PERCENT	( 40 )		// エンカウント処理に移行する基本確率
#define CYCLE_PERCENT		( 30 )	//自転車に乗っているときの加算確率
#define LONG_GRASS_PERCENT		( 30 )	//長い草の中にいるときの加算確率

#define	CALC_SHIFT			( 8 )		// 計算シフト値

#define ENC_MONS_NUM_MAX	ENC_MONS_NUM_NORMAL

#define ROD_TYPE_NONE	(0xff)		//確率テーブル指定無し
#define WEATHER_NONE	(0xff)		//天気指定無し

#ifdef PM_DEBUG

u8 DebugFishProbFlg = 0;

#endif

typedef struct SWAY_ENC_INFO_tag
{
	int Table;
	BOOL Decide;
	BOOL Rare;
	BOOL Enc;
}SWAY_ENC_INFO;

typedef struct ENC_COMMON_DATA_tag
{
	int MonsNo;
	u16 LvMax;
	u16 LvMin;
}ENC_COMMON_DATA;

typedef struct ENC_FLD_SPA_tag
{
	u32 TrainerID;			//トレーナーＩＤ
	BOOL SprayCheck;		//スプレーチェックするかのフラグ	TRUE:チェックする
	BOOL EncCancelSpInvalid;//戦闘回避特性無効	TRUE:無効	FALSE:有効		(現状では、あまいかおり・あまいミツ用)
	u8	 SpMyLv;			//スプレーチェックに使うレベル
	u8	 Egg;				//タマゴフラグ
	u8	 Spa;				//特性
	u8   FormProb[2];		//シーウシ・シードルゴ用フォルム変更確率　0：シーウシ　1：シードルゴ
	u8	 AnnoonTblType;		//アンノーンテーブルタイプ
}ENC_FLD_SPA;

static BOOL MapEncountCheck( FIELDSYS_WORK * fsys, const u32 map_encount, const u8 attr );
static u8 EncountAttributeCheck( FIELDSYS_WORK * fsys, u8 attr, u8 *outEncLocation );
static BOOL	EncountWalkCheck( FIELDSYS_WORK * fsys, u32 per );
static BOOL EncountCheckMain( FIELDSYS_WORK * fsys, u32 per );

static BOOL CheckFixTypeEcnt(	POKEMON_PARAM *inPokeParam,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 inListNum,
							const u8 type, const u8 tokusei,u8 * outNo);
static BOOL CheckEcntCancelByLv( const ENC_FLD_SPA *inFldSpa, POKEMON_PARAM *inMyPokeParam, const u8 inEneLv);
static int GetEncountProbGround(FIELDSYS_WORK * fsys);
static int GetEncountProbWater(FIELDSYS_WORK * fsys);
static int GetEncountProbFishing(FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType);
static BOOL WildEncSingle(FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENCOUNT_DATA *data,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa,
							const SWAY_ENC_INFO *inSwayEncInfo );
static BOOL WildEncDouble(	FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa );
static BOOL WildWaterEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * param,
								ENC_COMMON_DATA *enc_data,
								const ENC_FLD_SPA *inFldSpa );
static BOOL FishingEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * battle_param,
								ENC_COMMON_DATA *inData,
								const ENC_FLD_SPA *inFldSpa,
								const FISHINGROD_TYPE inRodType );
static BOOL SetEncountData(	POKEMON_PARAM *param,
							const FISHINGROD_TYPE inRodType,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 location,
							const int inTarget,
							BATTLE_PARAM *outBattleParam);
static BOOL SetSwayEncountData(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *param,
								const ENC_FLD_SPA *inFldSpa,
								const ENC_COMMON_DATA *inData,
								const int inTarget,
								BATTLE_PARAM *outBattleParam,
								const int inMonsNo, const int inLv);
static BOOL SetEncountDataDecideMons(	const int inMonsNo, const int inLv,
										const int inTarget,
										const BOOL inRare,
										const u32 inTrainerID,
										const ENC_FLD_SPA *inSpa,
										POKEMON_PARAM *param,
										BATTLE_PARAM *outBattleParam);

static u8 ChangeEncProb(	const BOOL IsFishing,
							const u8 inProb,
							const ENC_FLD_SPA *inFldSpa,
							const u32 inWeatherCode,
							POKEMON_PARAM *inPokeParam	);

static void SetFieldBattleParam(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, BATTLE_PARAM **param);
static void SetSfariMonster(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, const BOOL inBookGet, ENC_COMMON_DATA *enc_data);

static BOOL CheckSpray(const u8 inEneLv, const ENC_FLD_SPA *inSpa);
static void SetMovePokemon(const u32 inTrainerID, MPD_PTR mpd, BATTLE_PARAM *outBattleParam);
static BOOL CheckMovePokeEnc(FIELDSYS_WORK * fsys, MPD_PTR *outMpd);
static BOOL AddPokemonParam(const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *ioPokeParam, BATTLE_PARAM *ioBattleParam );
static u8 GetMaxLvMonsTblNo(const ENC_COMMON_DATA *inEncCommonData, const ENC_FLD_SPA *inFldSpa, const u8 inTblNo);
static void SetSpaStruct(FIELDSYS_WORK *fsys, POKEMON_PARAM *inPokeParam, ENCOUNT_DATA* inData, ENC_FLD_SPA *outSpa  );
static void ChangeEncProbByEquipItem( POKEMON_PARAM *inMyPokeParam, u8 *ioPer );
static void ChangeEncProbByVidro( FIELDSYS_WORK *fsys, u8 *ioPer );

typedef struct ANNOON_TABLE_tag
{
	int Num;
	const u8 *Tbl;
}ANNOON_TABLE;

static const u8 Tbl1[] = {
	UNK_A, UNK_B, UNK_C, UNK_G, UNK_H,
	UNK_J, UNK_K, UNK_L, UNK_M, UNK_O,
	UNK_P, UNK_Q, UNK_S, UNK_T, UNK_U,
	UNK_V, UNK_W, UNK_X, UNK_Y, UNK_Z,
};

static const u8 Tbl2[] = {
	UNK_F, 
};

static const u8 Tbl3[] = {
	UNK_R, 
};

static const u8 Tbl4[] = {
	UNK_I, 
};

static const u8 Tbl5[] = {
	UNK_N, 
};

static const u8 Tbl6[] = {
	UNK_E, 
};

static const u8 Tbl7[] = {
	UNK_D, 
};

static const u8 Tbl8[] = {
	UNK_ENC, UNK_QUE, 
};

static const ANNOON_TABLE ANNOON_Table[] = {
	{ 20, Tbl1 },
	{ 1 , Tbl2 },
	{ 1 , Tbl3 },
	{ 1 , Tbl4 },
	{ 1 , Tbl5 },
	{ 1 , Tbl6 },
	{ 1 , Tbl7 },
	{ 2 , Tbl8 },
};

//-----------------------------------------------------------------------------
/**
 * 時間帯エンカウントテーブル差し替え
 *
 * @param	inEncData			エンカウントデータポインタ
 * @param	*outTZEncMonsNo1	エンカウントポケモン1体目
 * @param	*outTZEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void EncSet_SetTimeZoneEnc(const ENCOUNT_DATA *inEncData, int *outTZEncMonsNo1, int *outTZEncMonsNo2)
{
	int time_zone;
	time_zone = GF_RTC_GetTimeZone();
	if ( (time_zone == TIMEZONE_NOON)||(time_zone == TIMEZONE_EVENING) ){
		(*outTZEncMonsNo1) = inEncData->NoonEnc[0];
		(*outTZEncMonsNo2) = inEncData->NoonEnc[1];
	}else if( (time_zone == TIMEZONE_NIGHT)||(time_zone == TIMEZONE_MIDNIGHT) ){
		(*outTZEncMonsNo1) = inEncData->NightEnc[0];
		(*outTZEncMonsNo2) = inEncData->NightEnc[1];
	}
}
#if 0
//-----------------------------------------------------------------------------
/**
 * サファリエンカウントテーブル差し替え
 *
 * @param	inRandomSeed		ランダムの種
 * @param	inBookComp			全国図鑑完成フラグ
 * @param	*outSafEncMonsNo1	エンカウントポケモン1体目
 * @param	*outSafEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void EncSet_SetSafariEnc(	const int inRandomSeed, const BOOL inBookComp,
							int *outSafEncMonsNo1, int *outSafEncMonsNo2	)
{
	int *tbl;
	int arc_idx;
	u16 tblno1,tblno2;
	
	//全国図鑑完成かどうかで、テーブルを変える
	if(inBookComp){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//サファリエンカウントテーブル取得
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//ランダムの種を元にサファリエンカウントテーブルから2体選出
	
	/* ---選出方法--- */
	/*サファリランダムの種の上位2バイトと下位2バイトを*/
	/*サファリ特殊テーブル数で割った余りを選出ポケモンテーブル番号とする*/
	/*その結果、2つの値が同じ場合は、値に1を加えた値を2つ目のテーブル番号とする*/
	/*選出した2つの番号がテーブルの最後の番号だった場合、片方は、テーブルの始めの番号となる*/
	
	tblno1 = ( (inRandomSeed >> 16) & 0xffff );
	tblno2 = ( inRandomSeed & 0xffff );

	tblno1 %= SAFARI_TBL_MAX;
	tblno2 %= SAFARI_TBL_MAX;

	if (tblno1 == tblno2){
		tblno2 = (tblno2+1)%SAFARI_TBL_MAX;
	}
	
	(*outSafEncMonsNo1) = tbl[tblno1];
	(*outSafEncMonsNo2) = tbl[tblno2];

	sys_FreeMemoryEz(tbl);
}
#endif

//-----------------------------------------------------------------------------
/**
 * 大量発生エンカウントテーブル差し替え
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	inEncData			エンカウントデータポインタ
 * @param	*outGeneEncMonsNo1	エンカウントポケモン1体目
 * @param	*outGeneEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncSet_SetGeneEnc(	FIELDSYS_WORK * fsys,
								const ENCOUNT_DATA *inEncData,
								int *outGeneEncMonsNo1, int *outGeneEncMonsNo2)
{
	u32 rnd_seed;
	ENC_SV_PTR data;
	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	
	//大量発生発動中？
	if ( EncDataSave_IsGenerate( data ) ){
		//ランダムの種を元に大量発生する場所を割り出し2体差し替え
		rnd_seed = EncDataSave_GetRandSeed(data, ENC_RND_SEED_GENERATE);
		if ( fsys->location->zone_id == GenerateZone_GetZone(rnd_seed)){
			(*outGeneEncMonsNo1) = inEncData->GenerateEnc[0];
			(*outGeneEncMonsNo2) = inEncData->GenerateEnc[1];
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * 裏山エンカウントテーブル差し替え
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	inBookGet			全国図鑑入手フラグ
 * @param	*outHillEncMonsNo1	エンカウントポケモン1体目
 * @param	*outHillEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncSet_SetHillBackEnc(	FIELDSYS_WORK * fsys, const BOOL inBookGet,
									int *outHillEncMonsNo1, int *outHillEncMonsNo2)
{
	int *tbl;
	u16 idx1,idx2;
	
	//裏山？
	if ( ZoneData_IsHillBackZone( fsys->location->zone_id ) ){
		EncDataSave_GetHillBackPokeIdx(fsys->savedata, &idx1, &idx2);
		//全国図鑑入手してるか？
		if ( inBookGet ){
			//裏山エンカウントテーブル取得
			tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
		
			//2体差し替え
			if (idx1 != HILL_BACK_POKE_NONE){
				(*outHillEncMonsNo1) = tbl[idx1];
			}
			if (idx2 != HILL_BACK_POKE_NONE){
				(*outHillEncMonsNo2) = tbl[idx2];
			}
			sys_FreeMemoryEz(tbl);
		}
	}
}
//============================================================================================
//
//
//					エンカウント判定処理
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * ２対２野生戦のときは揺れ草エンカウントはない仕様だが、チェックは通してます
 *
 * @param	fsys				フィールドシステムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
BOOL FieldEncount_Check(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM * param;
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//エンカウントする地形（地上か水上か）
	BOOL rc;
	BOOL result;
	BOOL companion;
	BOOL safari_flg;	//サファリフラグ

	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	
	ENC_FLD_SPA f_spa;
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = (u8)GetAttributeLSB( fsys, x, z );

	{
		u8	prob;
		// エンカウントアトリビュートチェック
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//エンカウントするアトリビュートではない もしくは確率が0
		}

		//手持ちパーティ取得
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		
		data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得
		
		SetSpaStruct(fsys, poke_param, data, &f_spa  );

		{
			//スプレー使用中ならばスプレーチェックする
			if ( !EncDataSave_CanUseSpray( EncDataSave_GetSaveDataPtr(fsys->savedata) ) ){
				POKEMON_PARAM *spray_poke_param;
				OS_Printf("supure-chekku\n");
				spray_poke_param = EvPoke_GetLivingPokemonTop(my_party);
				//スプレーチェックする
				f_spa.SprayCheck = TRUE;
				//スプレーチェックに使うレベルを取得
				f_spa.SpMyLv = PokeParaGet(spray_poke_param, ID_PARA_level, NULL);
			}
		}
		
		//特性によってエンカウント確率変更
		prob = ChangeEncProb(	FALSE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//ビードロによる確率変更
		ChangeEncProbByVidro( fsys, &prob );
		
		//装備アイテム（きよめのおふだ）による確率変動
		ChangeEncProbByEquipItem( poke_param, &prob );
		
		if( MapEncountCheck( fsys, prob, attr ) == FALSE ){
			rc = FALSE;
		}else{
			rc = TRUE;
		}
	}

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );

	//ゆれ草エンカウントチェック
	//ゆれ草にヒットしたら、事前チェックで、エンカウントしなかったっとしてもエンカウントする
	if ( !SwayGrass_CheckSpEncount(x, z, fsys, fsys->SwayGrass,
									&sway_enc_info.Table,
									&sway_enc_info.Decide,
									&sway_enc_info.Rare) ){
		sway_enc_info.Enc = FALSE;		//ゆれ草エンカウント不成立
	}else{
		sway_enc_info.Enc = TRUE;		//ゆれ草エンカウント成立
		rc = TRUE;
	}

	if (rc == FALSE){
		return FALSE;
	}

	//連れ歩き判定
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//通常
		companion = FALSE;
	}else{	//連れ歩き
		//バトルパラメータのアロケーションとポケモンパーティの初期化
		companion = TRUE;
	}

	//移動ポケモンチェック(連れ歩き時、揺れ草エンカウント成立時はチェックしない)
	if ( (!companion)&&(sway_enc_info.Enc==FALSE) ){
		MPD_PTR mpd;
		//移動ポケモンエンカウントチェック
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//スプレーチェック
			if ( !CheckSpray( EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV),  &f_spa ) ){
				//バトルパラム作成
				param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//ファイトタイプは移動ポケモン専用
				//手持ちポケモンなどセット
				BattleParam_SetParamByGameData(param, fsys);
				//パラメータセット
				SetMovePokemon(f_spa.TrainerID, mpd, param);
				//エンカウントした場合は、ゆれ草情報をクリア
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
				FieldEncount_Set(fsys, param);		//移動ポケモンとエンカウント
				return TRUE;
			}else{
				return FALSE;		//スプレーで戦闘回避(バトルパラム作成前なので解放しなくてＯＫ)
			}
		}
	}

	//バトルパラムの作成
	if (!companion){
		//サファリフラグを取得
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, &param);
	}else{
		param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//ファイトタイプは固定
	}
	
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(param, fsys);
	
	//地上水上分岐
	if (enc_location == GROUND_ENCOUNT){			//地上
		//共通エンカウントデータ作成
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//全国図鑑入手フラグ取得
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));
		
		//昼夜テーブル書き換え
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//大量発生テーブル書き換え
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//裏山テーブル書き換え
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGBスロットテーブル書き換え
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);

		if (!companion){
			//サファリ特殊枠のセット
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//シングル戦セット
			result = WildEncSingle(	fsys, poke_param, param, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			//相方ポケモンセット
			{
				//本来は連れ歩いている五人衆のIDを代入 by soga 2006.06.20
				param->trainer_id[CLIENT_NO_MINE2] =
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01
				TT_EncountTrainerDataMake(param,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, param, enc_data, &f_spa );
		}
	}else if(enc_location == WATER_ENCOUNT){		//水上
		//共通エンカウントデータ作成
		int i;
		for(i=0;i<ENC_MONS_NUM_SEA;i++){
			enc_data[i].MonsNo = data->EncSea[i].MonsterNo;
			enc_data[i].LvMax = data->EncSea[i].MaxLevel;
			enc_data[i].LvMin = data->EncSea[i].MinLevel;
		}
		result = WildWaterEncSingle(	fsys, poke_param, param, enc_data, &f_spa);
	}else{
		GF_ASSERT(0&&"エンカウントロケーション不明");
		BattleParam_Delete(param);	//バトルパラム解放
		return FALSE;
	}

	if (result){
		FieldEncount_Set(fsys, param);
	}else{
		rc = FALSE;
	}

	GF_ASSERT( sys_CheckHeapSafe( HEAPID_FIELD ) );
	GF_ASSERT( sys_CheckHeapSafe( HEAPID_WORLD ) );

	if (rc == FALSE){
		BattleParam_Delete(param);	//バトルパラム解放
	}
	//歩きカウントクリアする
	fsys->encount.walk_count = 0;
	
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * 釣りエンカウント
 * ※サファリにいたとしても、釣では特殊枠が無いので、サファリモンスターのセットは行わない
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	inRodtype			釣り竿
 * @param	outBattleParam		バトルパラメータのポインタのポインタ
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL SetFishingEncount( FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType, BATTLE_PARAM **outBattleParam )
{
	POKEMON_PARAM *poke_param;
	POKEPARTY *my_party;
	BOOL safari_flg;		//サファリフラグ

	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//特殊能力

	{
		u8 prob;
#ifdef PM_DEBUG
		if (DebugFishProbFlg){
			prob = 100;
		}else{
			// エンカウント率
			prob = GetEncountProbFishing(fsys, inRodType);
		}
#else
		// エンカウント率
		prob = GetEncountProbFishing(fsys, inRodType);
#endif
		if(  prob == 0 ){
			return FALSE;		//確率が0
		}

		//手持ちポケパーティ取得
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得	
		SetSpaStruct(fsys, poke_param, NULL, &f_spa);

		//特性によってエンカウント率変更
		prob = ChangeEncProb(	TRUE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//確率でエンカウント
		if (gf_p_rand(100) >= prob){
			return FALSE;		//エンカウントしない
		}
	}
	//サファリフラグを取得
	safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));

	//バトルパラメータセット
	SetFieldBattleParam(fsys, safari_flg, outBattleParam);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(*outBattleParam, fsys);
	//つり用の設定
	BattleParam_SetFisingParam(*outBattleParam);


	if ( (ZoneData_IsSpFishingZone(fsys->location->zone_id))&&
			 SpFishing_CheckPoint(fsys) ){
		//特殊釣りデータ作成
		u8 i;
		int monsno;
		u8 max,min;
		SpFishing_GetMaxMinLv(&max, &min);
		SpFishing_GetMonsNo(&monsno);
		
		for(i=0;i<ENC_MONS_NUM_FISH;i++){
			enc_data[i].MonsNo = monsno;
			enc_data[i].LvMax = max;
			enc_data[i].LvMin = min;
		}
	}else{
		//共通エンカウントデータ作成
		{
			NON_GROUND_ENC_MONSTER_DAT *enc_fish;
			u8 i;
			ENCOUNT_DATA *data;

			data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
			//シーウシ・シードルゴフォルム変更確率セット<<釣りでは出ないのでセット不要

			//釣り竿別にデータ作成
			switch(inRodType){
			case FISHINGROD_BAD:		//ボロ
				enc_fish = data->EncFish1;
				break;
			case FISHINGROD_GOOD:		//いい
				enc_fish = data->EncFish2;
				break;
			case FISHINGROD_GREAT:		//すごい
				enc_fish = data->EncFish3;
				break;
			}
		
			for(i=0;i<ENC_MONS_NUM_FISH;i++){
				enc_data[i].MonsNo = enc_fish[i].MonsterNo;
				enc_data[i].LvMax = enc_fish[i].MaxLevel;
				enc_data[i].LvMin = enc_fish[i].MinLevel;
			}	
		}
	}

	//釣りエンカウント
	{
		BOOL rc;
		rc = FishingEncSingle( fsys, poke_param, *outBattleParam, enc_data, &f_spa, inRodType );
		if (!rc){
			return FALSE;
		}
	}
	
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * 甘い蜜・甘い香りエンカウント
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	event			イベントポインタ
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL SetSweetEncount(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event)
{
	BATTLE_PARAM * param;
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//エンカウントする地形（地上か水上か）
	BOOL companion;
	BOOL safari_flg;	//サファリフラグ
	BOOL result;
	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//特殊能力

	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );

	
	attr = (u8)GetAttributeLSB( fsys, x, z );
	
	{
		u8	prob;
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//エンカウントするアトリビュートではない もしくは確率が0
		}
	}
	
	//手持ちパーティ取得
	my_party = SaveData_GetTemotiPokemon(fsys->savedata);

	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	poke_param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得
	SetSpaStruct(fsys, poke_param, data, &f_spa);
	//スプレーチェックしない
	f_spa.SprayCheck = FALSE;
	//エンカウント回避特性をキャンセルする
	f_spa.EncCancelSpInvalid = TRUE;

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );
	
	//連れ歩き判定
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//通常
		companion = FALSE;
	}else{	//連れ歩き
		companion = TRUE;
	}

	//移動ポケモンチェック(連れ歩き時はチェックしない。あまいかおりで揺れ草は無いので、チェックは省く)
	if (!companion){
		MPD_PTR mpd;
		//移動ポケモンエンカウントチェック
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//香りでエンカウントなのでスプレーチェックなし
			//バトルパラム作成
			param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//ファイトタイプは移動ポケモン専用
			//手持ちポケモンなどセット
			BattleParam_SetParamByGameData(param, fsys);
			//パラメータセット
			SetMovePokemon(f_spa.TrainerID,mpd, param);
			//エンカウントした場合は、ゆれ草情報をクリア
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
			FieldEncount_Change(fsys, event, param);		//移動ポケモンとエンカウント
			return TRUE;
		}
	}

	//バトルパラムの作成
	if (!companion){
		//サファリフラグを取得
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, &param);
	}else{
		param = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//ファイトタイプは固定
	}
	
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(param, fsys);

	//地上水上分岐
	if (enc_location == GROUND_ENCOUNT){			//地上
		//共通エンカウントデータ作成
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//全国図鑑入手フラグ取得
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));

		//昼夜テーブル書き換え
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//大量発生テーブル書き換え
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//裏山テーブル書き換え
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGBスロットテーブル書き換え
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);
		
		if (!companion){
			//サファリ特殊枠のセット
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//シングル戦セット
			result = WildEncSingle(	fsys, poke_param, param, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			//相方ポケモンセット
			{
				//本来は連れ歩いている五人衆のIDを代入 by soga 2006.06.20
				param->trainer_id[CLIENT_NO_MINE2] = 
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01;
				TT_EncountTrainerDataMake(param,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, param, enc_data, &f_spa );
		}
	}else if(enc_location == WATER_ENCOUNT){		//水上
		//共通エンカウントデータ作成
		int i;
		for(i=0;i<ENC_MONS_NUM_SEA;i++){
			enc_data[i].MonsNo = data->EncSea[i].MonsterNo;
			enc_data[i].LvMax = data->EncSea[i].MaxLevel;
			enc_data[i].LvMin = data->EncSea[i].MinLevel;
		}
		result = WildWaterEncSingle(	fsys, poke_param, param, enc_data, &f_spa);
	}else{
		GF_ASSERT(0&&"エンカウントロケーション不明");
		return FALSE;
	}

	if (result){
		FieldEncount_Change(fsys, event, param);
	}else{
		GF_ASSERT(0);
	}
	//歩きカウントクリアする
	fsys->encount.walk_count = 0;
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * レバガチャエンカウント
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	outBattleParam		バトルパラメータのポインタのポインタ
 *
 * @return	BOOL		TRUE:エンカウント成立	FALSE:エンカウント不成立
 */
//-----------------------------------------------------------------------------
BOOL SetKeyRandEncount( FIELDSYS_WORK * fsys, BATTLE_PARAM **outBattleParam )
{
	POKEMON_PARAM *poke_param;
	int x, z;
	u8	attr;
	u8 enc_location;	//エンカウントする地形（地上か水上か）
	BOOL rc;
	BOOL result;
	BOOL companion;
	BOOL safari_flg;	//サファリフラグ

	SWAY_ENC_INFO sway_enc_info;
	
	POKEPARTY *my_party;
	ENCOUNT_DATA *data;
	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	
	ENC_FLD_SPA f_spa;

	*outBattleParam = NULL;
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = (u8)GetAttributeLSB( fsys, x, z );

	{
		u8	prob;
		// エンカウントアトリビュートチェック
		prob = EncountAttributeCheck( fsys, attr, &enc_location );
		if( prob == 0 ){
			return FALSE;		//エンカウントするアトリビュートではない もしくは確率が0
		}

		//手持ちパーティ取得
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		
		data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得
		
		SetSpaStruct(fsys, poke_param, data, &f_spa  );

		{
			//スプレー使用中ならばスプレーチェックする
			if ( !EncDataSave_CanUseSpray( EncDataSave_GetSaveDataPtr(fsys->savedata) ) ){
				POKEMON_PARAM *spray_poke_param;
				OS_Printf("supure-chekku\n");
				spray_poke_param = EvPoke_GetLivingPokemonTop(my_party);
				//スプレーチェックする
				f_spa.SprayCheck = TRUE;
				//スプレーチェックに使うレベルを取得
				f_spa.SpMyLv = PokeParaGet(spray_poke_param, ID_PARA_level, NULL);
			}
		}
		
		//特性によってエンカウント確率変更
		prob = ChangeEncProb(	FALSE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//ビードロによる確率変更
		ChangeEncProbByVidro( fsys, &prob );
		
		//装備アイテム（きよめのおふだ）による確率変動
		ChangeEncProbByEquipItem( poke_param, &prob );
		
		if( MapEncountCheck( fsys, prob, attr ) == FALSE ){
			rc = FALSE;
		}else{
			rc = TRUE;
		}
	}

	memset( &sway_enc_info, 0, sizeof(SWAY_ENC_INFO) );
	sway_enc_info.Enc = FALSE;		//ゆれ草エンカウント確実に不成立
	
	//連れ歩き判定
	if (!SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){	//通常
		companion = FALSE;
	}else{	//連れ歩き
		//バトルパラメータのアロケーションとポケモンパーティの初期化
		companion = TRUE;
	}

	//移動ポケモンチェック(連れ歩き時はチェックしない。レバガチャで揺れ草はないので、チェックは省く)
	if (!companion){
		MPD_PTR mpd;
		//移動ポケモンエンカウントチェック
		if ( CheckMovePokeEnc(fsys, &mpd) ){
			//スプレーチェック
			if ( !CheckSpray( EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV),  &f_spa ) ){
				//バトルパラム作成
				*outBattleParam = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_MOVE);	//ファイトタイプは移動ポケモン専用
				//手持ちポケモンなどセット
				BattleParam_SetParamByGameData(*outBattleParam, fsys);
				//パラメータセット
				SetMovePokemon(f_spa.TrainerID,mpd, *outBattleParam);
				//エンカウントした場合は、ゆれ草情報をクリア
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
				return TRUE;
			}else{
				return FALSE;		//スプレーで戦闘回避(バトルパラム作成前なので解放しなくてＯＫ)
			}
		}
	}

	//バトルパラムの作成
	if (!companion){
		//サファリフラグを取得
		safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));
		SetFieldBattleParam(fsys, safari_flg, outBattleParam);
	}else{
		*outBattleParam = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_YASEI);	//ファイトタイプは固定
	}
	
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(*outBattleParam, fsys);
	
	//地上水上分岐	水上レバガチャは無いだろう。多分
	if (enc_location == GROUND_ENCOUNT){			//地上
		//共通エンカウントデータ作成
		int i;
		BOOL book_get;
		for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
			enc_data[i].MonsNo = data->NormalEnc[i].MonsterNo;
			enc_data[i].LvMax = data->NormalEnc[i].Level;
			enc_data[i].LvMin = data->NormalEnc[i].Level;
		}

		//全国図鑑入手フラグ取得
		book_get = ZukanWork_GetZenkokuZukanFlag(
								SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));
		
		//昼夜テーブル書き換え
		EncSet_SetTimeZoneEnc( data, &enc_data[TIME_ENC_1].MonsNo, &enc_data[TIME_ENC_2].MonsNo);
		//大量発生テーブル書き換え
		EncSet_SetGeneEnc(fsys, data, &enc_data[GENE_ENC_1].MonsNo, &enc_data[GENE_ENC_2].MonsNo);
		//裏山テーブル書き換え
		EncSet_SetHillBackEnc(	fsys, book_get, &enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
		//AGBスロットテーブル書き換え
		AgbSlotEnc_SetAgbSlotEnc(data, book_get, &enc_data[AGB_ENC_1].MonsNo, &enc_data[AGB_ENC_2].MonsNo);

		if (!companion){
			//サファリ特殊枠のセット
			SetSfariMonster(fsys, safari_flg, book_get, enc_data);
			//シングル戦セット
			result = WildEncSingle(	fsys, poke_param, *outBattleParam, data, enc_data, &f_spa,
							&sway_enc_info );
		}else{
			{
				//本来は連れ歩いている五人衆のIDを代入 by soga 2006.06.20
				(*outBattleParam)->trainer_id[CLIENT_NO_MINE2] =
					SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) ); //BTFIVE1_01
				TT_EncountTrainerDataMake(*outBattleParam,fsys->savedata,HEAPID_WORLD);
			}
			result = WildEncDouble(	fsys, poke_param, *outBattleParam, enc_data, &f_spa );
		}
	}else{
		GF_ASSERT(0&&"エンカウントロケーション不明");
		BattleParam_Delete(*outBattleParam);	//バトルパラム解放
		return FALSE;
	}

	if (!result){
		rc = FALSE;
	}

	GF_ASSERT( sys_CheckHeapSafe( HEAPID_FIELD ) );
	GF_ASSERT( sys_CheckHeapSafe( HEAPID_WORLD ) );

	if (rc == FALSE){
		BattleParam_Delete(*outBattleParam);	//バトルパラム解放
	}else{
		//歩きカウントクリアする
		fsys->encount.walk_count = 0;
	}
	return rc;
}


//-----------------------------------------------------------------------------
/**
 * 野生シングル戦セットアップ
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	poke_param			ポケモンパラム
 * @param	param				バトルパラム
 * @param	data				エンカウントデータ
 * @param	enc_data			共通エンカウントデータテーブル
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inSwayEncInfo		揺れ草情報データへのポインタ
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL WildEncSingle(FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENCOUNT_DATA *data,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa,
							const SWAY_ENC_INFO *inSwayEncInfo )
{
	BOOL rc;
	//揺れ草かどうかで分岐
	if (inSwayEncInfo->Enc){	//揺れ草エンカウント
		int monsno,lv;
		//ゆれ草専用テーブルに書き換え
		if (inSwayEncInfo->Table == SWAY_GRASS_ENC_SP){
			enc_data[SWAY_ENC_1].MonsNo = data->SwayEnc[0];
			enc_data[SWAY_ENC_2].MonsNo = data->SwayEnc[1];
			enc_data[SWAY_ENC_3].MonsNo = data->SwayEnc[2];
			enc_data[SWAY_ENC_4].MonsNo = data->SwayEnc[3];
		}

		//揺れ草前回ポケモン情報を取得（初回時は、0が入ってる）
		SwayGrass_GetEncMonsNoLv(fsys->SwayGrass, &monsno, &lv);
		//エンカウントするモンスターが決定している場合
		if (inSwayEncInfo->Decide == TRUE)	{
			MYSTATUS *my_st;
			//トレーナーＩＤ取得
			my_st = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
			//指定ポケモンと100％エンカウント
			rc = SetEncountDataDecideMons(	monsno, lv,
											POKEPARTY_ENEMY,
											inSwayEncInfo->Rare,
											MyStatus_GetID(my_st),//トレーナーＩＤ
											inFldSpa,
											poke_param,
											param );
		}else{	//決定していない場合、もしくは初回
			//エンカウントデータをセット
			rc = SetSwayEncountData(fsys, poke_param, inFldSpa, enc_data, POKEPARTY_ENEMY,
									param,  monsno, lv);
		}
		
		if (rc){
			//次回揺れ草場所を決定
			{
				int x,z;
				//自機の位置取得
				x = Player_NowGPosXGet(fsys->player);
				z = Player_NowGPosZGet(fsys->player);
				SwayGrass_SearchSwayGrass(fsys, x, z, fsys->SwayGrass);
			}
		}
	}else{			//通常
		rc = SetEncountData(poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
							GROUND_ENCOUNT, POKEPARTY_ENEMY,
							param);
		if (rc){
			//通常エンカウントした場合は、ゆれ草情報等をクリア
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * 野生ダブル戦セットアップ
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	poke_param			ポケモンパラム
 * @param	param				バトルパラム
 * @param	enc_data			共通エンカウントデータテーブル
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL WildEncDouble(	FIELDSYS_WORK * fsys,
							POKEMON_PARAM *poke_param,
							BATTLE_PARAM * param,
							ENC_COMMON_DATA *enc_data,
							const ENC_FLD_SPA *inFldSpa )
{
	BOOL rc;
	{
		{
			//エンカウントデータをセット
			rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
									GROUND_ENCOUNT, POKEPARTY_ENEMY,
									param );
			if (!rc){
				return FALSE;
			}
			
			rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
									GROUND_ENCOUNT, POKEPARTY_ENEMY_PAIR,
									param );
		}
		
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * 野生水上シングル戦セットアップ
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	poke_param			ポケモンパラム
 * @param	param				バトルパラム
 * @param	enc_data			共通エンカウントデータテーブル
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL WildWaterEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * param,
								ENC_COMMON_DATA *enc_data,
								const ENC_FLD_SPA *inFldSpa )
{
	BOOL rc;

	{
		//エンカウントデータをセット
		rc = SetEncountData(	poke_param, ROD_TYPE_NONE, inFldSpa, enc_data,
								WATER_ENCOUNT, POKEPARTY_ENEMY,
								param );
	}
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * 釣り
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	poke_param			ポケモンパラム
 * @param	battle_param		バトルパラム
 * @param	inData				エンカウントデータ
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inRodType			釣竿
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL FishingEncSingle(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *poke_param,
								BATTLE_PARAM * battle_param,
								ENC_COMMON_DATA *inData,
								const ENC_FLD_SPA *inFldSpa,
								const FISHINGROD_TYPE inRodType )
{
	BOOL rc;
	rc = SetEncountData(poke_param, inRodType, inFldSpa, inData,
						FISHING_ENCOUNT, POKEPARTY_ENEMY,
						battle_param );
	return rc;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントチェック（歩数関連）
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	map_encount			エンカウント確率
 * @param	attr				アトリビュート
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL MapEncountCheck( FIELDSYS_WORK * fsys, const u32 per, const u8 attr )
{
	u8 next_base;
	u32 map_encount;
	
	//100%が上限
	if (per>100){
		map_encount = 100;
	}
	map_encount = per << CALC_SHIFT;

	// エンカウントする歩数
	if( EncountWalkCheck( fsys, map_encount ) == FALSE ){
		fsys->encount.walk_count++;			// 歩数カウント＋
		// 5%で次の処理へ
		if( ( gf_p_rand(100) ) >= WALK_NEXT_PERCENT ){
			return FALSE;
		}
	}

	next_base = NEXT_PERCENT;	//基本40％

	//長い草の場合は+30％
	if ( MATR_IsLongGrass(attr) ){
		next_base += LONG_GRASS_PERCENT;
	}else{
		//自転車に乗っているなら+30％
		if ( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){
			next_base += CYCLE_PERCENT;
		}
	}
	//日付による確率変動
	next_base = CalEnc_GetProb(next_base, EVTIME_IsPenaltyMode(fsys));

	//100%が上限
	if (next_base>100){
		next_base = 100;
	}

	// next_base%で次の処理（基本は60%で処理を打ち切り)
	if( ( gf_p_rand(100) ) < next_base  ){
		// メイン
		if( EncountCheckMain( fsys, per ) ){
			return TRUE;
		}	
	}
	return FALSE;
	
}

//-----------------------------------------------------------------------------
/**
 * 確率を返す
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	attr				アトリビュート
 * @param	outEncLocation		エンカウント場所を格納するバッファ
 *
 * @return	u8					確率
 */
//-----------------------------------------------------------------------------
static u8 EncountAttributeCheck( FIELDSYS_WORK * fsys, u8 attr, u8 *outEncLocation  )
{
	if (MATR_IsEncount(attr)){
		if (MATR_IsWater(attr)){			//水
			(*outEncLocation) = WATER_ENCOUNT;
			return GetEncountProbWater( fsys );
		}else{								//陸
			(*outEncLocation) = GROUND_ENCOUNT;
			return GetEncountProbGround( fsys );
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
/**
 * 徒歩チェック
 *
 * @param	fsys	フィールドシステムポインタ
 * @param	per		確率
 *
 * @return	BOOL	
 */
//-----------------------------------------------------------------------------
static BOOL	EncountWalkCheck( FIELDSYS_WORK * fsys, u32 per )
{
	per = (per/10)>>CALC_SHIFT;
	if (per > WALK_COUNT_GLOBAL) {
		per = WALK_COUNT_GLOBAL;
	}
	per = WALK_COUNT_GLOBAL - ( per );

	if( fsys->encount.walk_count >= per ){
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントチェック
 *
 * @param	fsys	フィールドシステムポインタ
 * @param	per		確率
 *
 * @return	BOOL	TRUE:エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL EncountCheckMain( FIELDSYS_WORK * fsys, u32 per )
{
	if ( gf_p_rand(100) >= per ){
		return FALSE;
	}else{
		return TRUE;
	}
}

//-----------------------------------------------------------------------------
/**
 * ランダムポケモンセット（草むら/砂漠/洞窟）
 *
 * @return	u8 エンカウントデータのテーブル番号
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSet(void)
{
	u8	i;

	i = gf_p_rand(100);

	if( i < 20 )			return	0;		// 20%
	if( i >= 20 && i < 40 )	return	1;		// 20%
	if( i >= 40 && i < 50 )	return	2;		// 10%
	if( i >= 50 && i < 60 )	return	3;		// 10%
	if( i >= 60 && i < 70 )	return	4;		// 10%
	if( i >= 70 && i < 80 )	return	5;		// 10%
	if( i >= 80 && i < 85 )	return	6;		//  5%
	if( i >= 85 && i < 90 )	return	7;		//  5%
	if( i >= 90 && i < 94 )	return	8;		//  4%
	if( i >= 94 && i < 98 )	return	9;		//  4%
	if( i == 98 )			return	10;		//  1%
	return	11;								//  1%
}

//-----------------------------------------------------------------------------
/**
 * ランダムポケモンセット（水上）
 *
 * @return	u8 エンカウントデータのテーブル番号
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSetNoGround(void)
{
	u8	i;

	i = gf_p_rand(100);

	if( i < 60 )			return	0;		// 60%
	if( i >= 60 && i < 90 )	return	1;		// 30%
	if( i >= 90 && i < 95 )	return	2;		//  5%
	if( i >= 95 && i < 99 )	return	3;		//  4%
	return	4;								//  1%
}

//-----------------------------------------------------------------------------
/**
 * ランダムポケモンセット（釣り）
 *
 * @param	inFishingRod		釣竿
 *
 * @return	u8		エンカウントデータのテーブル番号		
 */
//-----------------------------------------------------------------------------
static u8 RandamPokeSetFishing( const FISHINGROD_TYPE inFishingRod )
{
	u8	i;
	u8	p = 0;

	i = gf_p_rand(100);

	switch( inFishingRod ){
	case FISHINGROD_BAD:		// ボロの釣竿
		if		( i < 60 )	p = 0;	// 60%
		else if ( i < 90 )	p = 1;	// 30%
		else if ( i < 95 )	p = 2;	// 5%
		else if ( i < 99 )	p = 3;	// 4%	
		else				p = 4;	// 1%
		break;
	case FISHINGROD_GOOD:		// 良い釣竿
		if		( i < 40 )	p = 0;	// 40%
		else if ( i < 80 )	p = 1;	// 40%
		else if ( i < 95 )	p = 2;	// 15%
		else if ( i < 99 )	p = 3;	// 4%
		else				p = 4;	// 1%
		break;
	case FISHINGROD_GREAT:		// 凄い釣竿
		if		( i < 40 )	p = 0;	// 40%
		else if ( i < 80 )	p = 1;	// 40%
		else if ( i < 95 )	p = 2;	// 15%
		else if ( i < 99 )	p = 3;	// 4%
		else				p = 4;	// 1%
		break;
	default:
		GF_ASSERT(0&&"unknown fishing rod");
	}

	return	p;
}

//-----------------------------------------------------------------------------
/**
 * 装備アイテムによるエンカウント率変化
 *
 * @param	inMyPokeParam	手持ち先頭ポケモン
 * @param	ioPer			確率
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void ChangeEncProbByEquipItem( POKEMON_PARAM *inMyPokeParam, u8 *ioPer )
{
	u16 item;
	item = PokeParaGet( inMyPokeParam, ID_PARA_item, NULL );
	// 先頭のポケモンが「きよめのおふだ」・「きよめのおこう」を装備している場合、2/3
	if( (item == ITEM_KIYOMENOOHUDA)||
		(item == ITEM_KIYOMENOOKOU) ){
		(*ioPer) = ( (*ioPer) * 2 ) / 3;
	}
}

//-----------------------------------------------------------------------------
/**
 * ビードロよるエンカウント率変化
 *
 * @param	fsys		フィールドシステムポインタ
 * @param	ioPer		確率
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void ChangeEncProbByVidro( FIELDSYS_WORK *fsys, u8 *ioPer )
{
	u8 type;
	//セーブデータからビードロタイプを取得
	type = EncDataSave_GetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	if( type == VIDRO_BLACK ){			//「くろいビードロ」を使用している場合、1/2倍
		(*ioPer)/=2;
//		OS_Printf("黒使用中%d\n",(*ioPer));
	}else if (type == VIDRO_WHITE){		//「しろいビードロ」を使用している場合、1.5倍
		(*ioPer) = (*ioPer) + ((*ioPer)/2);
//		OS_Printf("白使用中%d\n",(*ioPer));
	}
}

//-----------------------------------------------------------------------------
/**
 * 性格設定
 *
 * @param	inPokeParam			ポケモンパラム
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 *
 * @return	u8					性格
 */
//-----------------------------------------------------------------------------
static u8 GetEncountChar(POKEMON_PARAM *inPokeParam, const ENC_FLD_SPA *inFldSpa)
{
	u32	type;

	//シンクロの特性によりエンカウントポケモンの性格を同じになりやすくする
	// 先頭のポケモンがタマゴでない
	if( inFldSpa->Egg == 0 ){
		if( inFldSpa->Spa == TOKUSYU_SINKURO ){	//シンクロ
			if ( gf_p_rand(2) == 0 ){//特性適用　確率1/2
				type = (u32)PokeParaGet( inPokeParam, ID_PARA_personal_rnd, NULL );
				type = type % 25;
				return (u8)type;
			}
		}
	}
	
	return gf_p_rand(25);	// ランダムで決定
	
}

//-----------------------------------------------------------------------------
/**
 * レベル設定
 *
 * @param	inData			共通エンカウントデータテーブル
 * @param	inFldSpa		特性チェック・フォルム変更用構造体へのポインタ
 *
 * @return	u8				レベル
 */
//-----------------------------------------------------------------------------
static u8 SetEncountPokeLv( const ENC_COMMON_DATA *inData, const ENC_FLD_SPA *inFldSpa )
{
	u8	size;
	u8	plus;
	u8	min, max;
	u8	spa;

	// Max Lv が Min Lv より小さい場合の修正処理
	if( inData->LvMax >= inData->LvMin ){
		min = inData->LvMin;
		max = inData->LvMax;
	}else{
		min = inData->LvMax;
		max = inData->LvMin;
	}

	size = max - min + 1;		// 補正サイズ
	plus = gf_rand() % size;	// 補正値

	//「やるき」「プレッシャー」「はりきり」の特性発動チェックレベルの高いポケモンと５割でエンカウント
	// 先頭のポケモンがタマゴでない
	if( inFldSpa->Egg == 0 ){
		if( (inFldSpa->Spa == TOKUSYU_HARIKIRI)||
			(inFldSpa->Spa == TOKUSYU_YARUKI)||
			(inFldSpa->Spa == TOKUSYU_PURESSYAA) ){
			// 1/2で特性発動
			if( gf_p_rand(2) == 0 ){
				return 	( min + plus );		// 特性未発動
			}
			return	( max );	//特性発動。レベルをmaxにする
		}
	}

	return	( min + plus );		// エンカウントレベル
}

//-----------------------------------------------------------------------------
/**
 * エンカウントポケモンセット（レア）
 *
 * @param	poke				モンスターナンバー
 * @param	lv					レベル
 * @param	inTarget			追加対象
 * @param	inTrainerID			トレーナーＩＤ
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inPokeParam			ポケモンパラム（自分）
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncountParamSetRare(	const u16 poke, const u8 lv, const int inTarget,
									const u32 inTrainerID, const ENC_FLD_SPA *inFldSpa,
									POKEMON_PARAM *inPokeParam, BATTLE_PARAM *outBattleParam )
{
	BOOL rc;
	u32 rnd_val;
	BOOL sp_use;	//特性適用するか？
	u8 my_poke_sex;
	u8 my_poke_chr;
	
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);

	sp_use = FALSE;

	//特性チェック	レアとなるＩＤは崩さずに、特性を反映
	//チェックする特性は、メロメロボディとシンクロ
	if (inFldSpa->Egg == 0){
		if (inFldSpa->Spa == TOKUSYU_MEROMEROBODHI){
			//エンカウントするポケモンの性別ベクトルを調べる
			u32 sex_vec;
			sex_vec = PokePersonalParaGet( poke, ID_PER_sex );
			switch(sex_vec){
			case    MONS_MALE:
			case    MONS_FEMALE:
			case    MONS_UNKNOWN:
					break;		//性別無しもしくは、固定の場合は、特性発動しない
			default:
				// 2/3で特性発動
				if( gf_p_rand(3) > 0 ){
					my_poke_sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(inPokeParam);
					sp_use = TRUE;
				}
			}
		}else if (inFldSpa->Spa == TOKUSYU_SINKURO){
			if ( gf_p_rand(2) == 0 ){//特性適用　確率1/2
				my_poke_chr = PokeSeikakuGet(inPokeParam);
				sp_use = TRUE;
			}
		}
	}

	//レア個性乱数取得
	rnd_val = PokeRareRndGet(inTrainerID);

	if (sp_use){//特性を適用する場合
		u8 sex,chr;
		do{
			if (inFldSpa->Spa == TOKUSYU_MEROMEROBODHI){
				//相手の性別を取得（性別無しは上で弾いてるので必ず雌雄が分かるはず）
				sex = PokeSexGetMonsNo(poke, rnd_val);
				GF_ASSERT(sex!=PARA_UNK&&"ERROR:ENCOUNT_SEX_ERROR");
				//自分の性別と比較（メロメロボディを持っているポケモンは必ず性別があることを前提とする）
				if (sex != my_poke_sex){
					break;	//異性なので終了
				}else{
					rnd_val = PokeRareRndGet(inTrainerID);	//レア個性乱数再取得
				}
			}else if (inFldSpa->Spa == TOKUSYU_SINKURO){
				//相手の性格を取得
				chr = PokeSeikakuGetRnd(rnd_val);
				//自分の性格と比較
				if (chr == my_poke_chr){
					break;	//同じ性格なので終了
				}else{
					rnd_val = PokeRareRndGet(inTrainerID);	//レア個性乱数再取得
				}
				

			}
		}while(1);
	}
	
	PokeParaSet(poke_param, poke, lv, POW_RND, RND_SET, rnd_val, ID_SET, inFldSpa->TrainerID);
	rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
	GF_ASSERT(rc&&"ポケモンの追加に失敗");
	sys_FreeMemoryEz(poke_param);

	OS_Printf("RARE_POKEMON_ENCOUNT!!!!!\n");
}

//-----------------------------------------------------------------------------
/**
 * エンカウントポケモンセット
 *
 * @param	poke				モンスターナンバー
 * @param	lv					レベル
 * @param	inTarget			追加対象
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inPokeParam			ポケモンパラム（自分）
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void EncountParamSet(u16 poke, u8 lv, const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *inPokeParam, BATTLE_PARAM *outBattleParam )
{
	u8 valid_flg;	//特性有効チェックフラグ
	u8 sex;
	BOOL rc;
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);

	valid_flg = 1;

	//エンカウントするポケモンの性別ベクトルを調べる
	{
		u32 sex_vec;
		sex_vec = PokePersonalParaGet( poke, ID_PER_sex );
		switch(sex_vec){
        case    MONS_MALE:
        case    MONS_FEMALE:
        case    MONS_UNKNOWN:
			valid_flg = 0;
		}
	}

	if (valid_flg){//選出したポケモンが性別なし、もしくは、固定の場合は、特性チェックなし
		//先頭ポケモンの特性がメロメロボディのときは異性が出やすくなる
		// 先頭のポケモンがタマゴでない
		if( inFldSpa->Egg == 0 ){
			if( inFldSpa->Spa == TOKUSYU_MEROMEROBODHI ){
				// 2/3で特性発動
				if( gf_p_rand(3) > 0 ){
					sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(inPokeParam);
					//異性を発生させる
					if (sex == PARA_FEMALE){
						sex = PARA_MALE;
						OS_Printf("メスなのでオスセット\n");
					}else if (sex == PARA_MALE){
						sex = PARA_FEMALE;
						OS_Printf("オスなのでメスセット\n");
					}else{			GF_ASSERT(0&&"性別不明");
					}
					PokeParaSetSexChr(poke_param, poke, lv, POW_RND, sex, GetEncountChar(inPokeParam, inFldSpa), 0);
					PokeParaPut(poke_param, ID_PARA_id_no, &inFldSpa->TrainerID);
#if 0	//デバッグ用
					{
						u8 d_sex;
						d_sex = PokeParaGet(inPokeParam, ID_PARA_sex, NULL);//PokeSexGet(poke_param);
						if (d_sex == PARA_FEMALE){
							OS_Printf("メス\n");
						}else if (d_sex == PARA_MALE){
							OS_Printf("オス\n");
						}else{
							GF_ASSERT(0&&"セットした性別不明");
						}
					}
#endif				
					rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
					GF_ASSERT(rc&&"ポケモンの追加に失敗");
					sys_FreeMemoryEz(poke_param);
					return;
				}
			}
		}
	}

	PokeParaSetChr( poke_param, poke, lv, POW_RND, GetEncountChar(inPokeParam, inFldSpa) );
	PokeParaPut(poke_param, ID_PARA_id_no, &inFldSpa->TrainerID);
	rc = AddPokemonParam(inTarget, inFldSpa, poke_param, outBattleParam);
	GF_ASSERT(rc&&"ポケモンの追加に失敗");
	sys_FreeMemoryEz(poke_param);
}

#ifdef PM_DEBUG
//----------------------------------------------------
//	デバッグエンカウントポケモンセット
//	引数 : u16 poke = ポケモンID
//		   u8 lv    = エンカウントLv
//----------------------------------------------------
static void DebugEncountParamSet(	u16 poke, u8 lv, const int inTarget,
									BATTLE_PARAM *outBattleParam )
{
	u16 monsno;
	u32 rnd;
	u8 sex;
	u8 spa;
	BOOL rc;
	POKEMON_PARAM *poke_param;
	poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
	PokeParaInit(poke_param);
	
	PokeParaSetChr( poke_param, poke, lv, POW_RND, (gf_p_rand(25)) );
	rc = PokeParty_Add(outBattleParam->poke_party[inTarget], poke_param);
	GF_ASSERT(rc&&"ポケモンの追加に失敗");
	sys_FreeMemoryEz(poke_param);
}
#endif

//-----------------------------------------------------------------------------
/**
 * エンカウントデータセット
 *
 * @param	param				モンスターナンバー
 * @param	inRodType					レベル
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inData				共通エンカウントデータテーブル
 * @param	location			場所
 * @param	intarget			追加対象
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetEncountData(	POKEMON_PARAM *param,
							const FISHINGROD_TYPE inRodType,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 location,
							const int inTarget,
							BATTLE_PARAM *outBattleParam)
{
	BOOL result;
	u8	no = 0;
	u8	lv = 0;
	
	// エンカウントポケモン決定
	switch( location ){
	case GROUND_ENCOUNT:	// 陸地
		//じりょく特性による、はがねタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_NORMAL, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		if (result == FALSE){
			//せいでんき特性による、でんきタイプのエンカウント率の向上
			result = CheckFixTypeEcnt(	param, inFldSpa, inData,
										ENC_MONS_NUM_NORMAL, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
			if (result == FALSE){
				//特性による指定タイプとのエンカウントに失敗。通常のエンカウント
				no = RandamPokeSet();
				//OS_Printf("enc_random = %d\n",no);				
			}
		}
		//隠し特性による最大レベルポケモン選出(地上)
		no = GetMaxLvMonsTblNo(inData, inFldSpa, no);
		lv = inData[no].LvMax;
		break;
	case WATER_ENCOUNT:		// 水上
		//じりょく特性による、はがねタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_SEA, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		//せいでんき特性による、でんきタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_SEA, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//特性による指定タイプとのエンカウントに失敗。通常のエンカウント
			no = RandamPokeSetNoGround();
		}
		//レベルセット
		lv = SetEncountPokeLv( &inData[no], inFldSpa );
		break;
	case FISHING_ENCOUNT:	//釣り
		//じりょく特性による、はがねタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_FISH, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
		//せいでんき特性による、でんきタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_FISH, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//特性による指定タイプとのエンカウントに失敗。通常のエンカウント
			no = RandamPokeSetFishing(inRodType);
		}
		//レベルセット
		lv = SetEncountPokeLv( &inData[no], inFldSpa );
		break;
	default:
		GF_ASSERT(0);
	}

	//特性によるレベル差戦闘回避
	if( CheckEcntCancelByLv( inFldSpa, param, lv )){
		return FALSE;
	}

	// スプレーチェック Lvの低いポケモンはエンカウントしない
	if( CheckSpray(lv, inFldSpa) == TRUE ){
		return FALSE;		//スプレーで戦闘回避
	}
	
	// エンカウントポケモンセット
	EncountParamSet( inData[no].MonsNo, lv, inTarget, inFldSpa, param, outBattleParam );
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントデータセット（ポケモン指定）
 *
 * @param	inMonsNo			モンスターナンバー
 * @param	inLv				レベル
 * @param	inTarget			追加対象
 * @param	inRare				レアフラグ
 * @param	inTrainerID			トレーナーＩＤ
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	param				ポケモンパラム（自分）
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetEncountDataDecideMons(	const int inMonsNo, const int inLv,
										const int inTarget,
										const BOOL inRare,
										const u32 inTrainerID,
										const ENC_FLD_SPA *inFldSpa,
										POKEMON_PARAM *param,
										BATTLE_PARAM *outBattleParam)
{
	u8	lv = 0;

	GF_ASSERT(inMonsNo != 0);
	
	//エンカウントするポケモンがすでに決まっているので、じりょく、せいでんき特性は無視する
	//やるき、はりきり、プレッシャーによる、レベル変動も行わない
	lv = inLv;

	//スプレーチェック無し
	
	// エンカウントポケモンセット
	if (inRare){
		EncountParamSetRare(inMonsNo, lv, inTarget, inTrainerID,
							inFldSpa, param, outBattleParam );
	}else{
		EncountParamSet( inMonsNo, lv, inTarget, inFldSpa, param, outBattleParam );
	}
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントデータセット（揺れ草）
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	param				ポケモンパラム
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inData				共通エンカウンデータテーブル
 * @param	inTartget			追加対象
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static BOOL SetSwayEncountData(	FIELDSYS_WORK * fsys,
								POKEMON_PARAM *param,
								const ENC_FLD_SPA *inFldSpa,
								const ENC_COMMON_DATA *inData,
								const int inTarget,
								BATTLE_PARAM *outBattleParam,
								const int inMonsNo, const int inLv)
{
	u8 result;
	u8	no = 0;
	u8	lv = 0;

	int monsno;
	
	// エンカウントポケモン決定
	//じりょく特性による、はがねタイプのエンカウント率の向上
	result = CheckFixTypeEcnt(	param, inFldSpa, inData,
								ENC_MONS_NUM_NORMAL, METAL_TYPE,TOKUSYU_ZIRYOKU, &no);
	if (result == FALSE){
		//せいでんき特性による、でんきタイプのエンカウント率の向上
		result = CheckFixTypeEcnt(	param, inFldSpa, inData,
									ENC_MONS_NUM_NORMAL, ELECTRIC_TYPE,TOKUSYU_SEIDENKI, &no);
		if (result == FALSE){
			//特性による指定タイプとのエンカウントに失敗。通常のエンカウント
			no = RandamPokeSet();
		}
	}
	lv = inData[no].LvMax;
	monsno = inData[no].MonsNo;

	//初回か？
	if (inMonsNo == 0){	//初回
		//初回ゆれ草エンカウントとして、エンカウントした場合は、セットしたポケモンを記憶する
		SwayGrass_SetEncMonsNoLv(fsys->SwayGrass, monsno, lv);
		//連鎖数の更新<<仕様変更 2006/0519 add　初回から更新する（厳密には連鎖数ではなくて戦闘数になる）
		SwayGrass_UpDateChain(fsys);
	}else{			//初回じゃない
		//揺れ草ハズレ引いたけど同じポケモンの場合は連鎖を復活させる
		if (monsno == inMonsNo ){
			monsno = inMonsNo;
			lv = inLv;
			//連鎖数の更新
			SwayGrass_UpDateChain(fsys);
		}else{
			//ハズレなので揺れ草終わり
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
	}

	//スプレーチェック無し
	
	// エンカウントポケモンセット
	EncountParamSet( monsno, lv, inTarget, inFldSpa, param, outBattleParam );
	return	TRUE;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントデータセット（蜜塗り）
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SetHoneyTreeEncountData(FIELDSYS_WORK *fsys, BATTLE_PARAM *outBattleParam)
{
	POKEMON_PARAM *param;
	int monsno;
	ENC_FLD_SPA f_spa;		//特殊能力
	u8 lv;
	
	monsno = HTE_GetHoneyTreeMonster(fsys);
	//先頭ポケモンのタマゴチェック
	{	
		POKEPARTY *my_party;
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得
		SetSpaStruct(fsys, param, NULL, &f_spa );
	}

	//レベル設定（5～15）
	{
		u8 plus = HONEY_TREE_LV_MAX-HONEY_TREE_LV_MIN+1;
		lv = HONEY_TREE_LV_MIN + gf_p_rand(plus);

		//「やるき」「プレッシャー」「はりきり」の特性発動チェックレベルの高いポケモンと５割でエンカウント
		// 先頭のポケモンがタマゴでない
		if( f_spa.Egg == 0 ){
			if( (f_spa.Spa == TOKUSYU_HARIKIRI)||
				(f_spa.Spa == TOKUSYU_YARUKI)||
				(f_spa.Spa == TOKUSYU_PURESSYAA) ){
				// 1/2で特性発動
				if( gf_p_rand(2) == 0 ){
					;		// 特性未発動
				}else{
					lv = HONEY_TREE_LV_MAX;	//特性発動。レベルをmaxにする
				}
			}
		}
	}

	//スプレーチェック無し
	
	//蜜木アニメフラグオフ
	HTE_ResetAnimeFlg(fsys);
	outBattleParam->battle_status_flag |= BATTLE_STATUS_FLAG_MITSUNURI_BATTLE;
	
	EncountParamSet( monsno, lv, POKEPARTY_ENEMY, &f_spa, param, outBattleParam );
	return;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントデータセット（イベント）
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	monsno				モンスターナンバー
 * @param	level				レベル
 * @param	outBattleParam		バトルパラムポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SetWildEncountData(FIELDSYS_WORK *fsys, u16 monsno, u8 level,BATTLE_PARAM *outBattleParam)
{
	POKEMON_PARAM *param;
	ENC_FLD_SPA f_spa;		//特殊能力
	//先頭ポケモンのタマゴチェック
	{	
		POKEPARTY *my_party;
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得

		SetSpaStruct(fsys, param, NULL, &f_spa );
	}
	
	/*-隠し特性の発動-*/
	/*-イベントから呼ばれる野生戦は、-*/
	/*-メロメロボディー、シンクロ、ふくがん-*/
	/*-の3つが機能する-*/
	EncountParamSet( monsno, level, POKEPARTY_ENEMY, &f_spa, param, outBattleParam );
	return;
}

//-----------------------------------------------------------------------------
/**
 * エンカウントするかどうかを返す（ゾーンのエンカウントフラグは判定しない）
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	attr				アトリビュート
 *
 * @return	BOOL				TRUE: エンカウントする	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
BOOL EncSet_CheckEncount( FIELDSYS_WORK * fsys, u8 attr  )
{
	int prob = 0;
	
	if (MATR_IsEncount(attr)){
		if (MATR_IsWater(attr)){			//水
			prob = GetEncountProbWater( fsys );
		}else{								//陸
			prob = GetEncountProbGround( fsys );
		}
	}
	
	if (prob){
		return TRUE;
	}else{
		return FALSE;
	}
}

#ifdef PM_DEBUG
//----------------------------------------------------
//	ノーマル
//	引数   : ENCOUNT_DATA * inData = エンカウントデータ
//			 u8 id             = エンカウント地形
//			 u8 sp_check       = 特殊チェック
//	戻り値 : TRUE = ENCOUNT　FALSE = NOT ENCOUNT
//----------------------------------------------------
BOOL DebugSetEncountData(	const ENCOUNT_DATA * inData,
							const u8 id,
							BATTLE_PARAM *outBattleParam)
{
	DebugEncountParamSet( 1, 10, POKEPARTY_ENEMY, outBattleParam );//先頭はタマゴではないとする

	return	TRUE;
}
#endif

//-----------------------------------------------------------------------------
/**
 * 地上エンカウント率を返す
 *
 * @param	fsys				フィールドシステムポインタ
 *
 * @return	int					確率
 */
//-----------------------------------------------------------------------------
static int GetEncountProbGround(FIELDSYS_WORK * fsys)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	return data->EncProbGround;
}

//-----------------------------------------------------------------------------
/**
 * 水上エンカウント率を返す
 *
 * @param	fsys				フィールドシステムポインタ
 *
 * @return	int					確率
 */
//-----------------------------------------------------------------------------
static int GetEncountProbWater(FIELDSYS_WORK * fsys)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	return data->EncProbSea;
}

//-----------------------------------------------------------------------------
/**
 * 釣りエンカウント率を返す
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	inRodType			釣竿
 *
 * @return	int					確率
 */
//-----------------------------------------------------------------------------
static int GetEncountProbFishing(FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType)
{
	ENCOUNT_DATA *data;
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);
	switch(inRodType){
	case FISHINGROD_BAD:				//ボロ釣竿
		return data->EncProbFish1;
	case FISHINGROD_GOOD:				//いい釣竿
		return data->EncProbFish2;
	case FISHINGROD_GREAT:				//すごい釣竿
		return data->EncProbFish3;
	default:
		GF_ASSERT(0);
		return 0;
	}
}

//-----------------------------------------------------------------------------
/**
 * 指定タイプのポケモンとエンカウントさせる
 *
 * @param	inData			共通エンカウントデータテーブル
 * @param	inListNum		リスト数
 * @param	type			タイプ
 * @param	outNo			テーブル番号格納バッファ
 *
 * @return	BOOL		TRUE:成功	FALSE:失敗
 */
//-----------------------------------------------------------------------------
static BOOL FixPokeSet(const ENC_COMMON_DATA *inData, const u8 inListNum, const u8 type, u8 * outNo)
{
	u8 same_type[ENC_MONS_NUM_MAX];	//指定したタイプと同じタイプのポケモンのエンカウントリスト
	u8 cnt;				//エントリーした数
	u8 i;
	u8 type1,type2;
	//初期化
	for (i=0;i<ENC_MONS_NUM_MAX;i++){
		same_type[i] = 0;
	}
	cnt = 0;
	
	//指定タイプとエンカウントリスト内のポケモンのタイプを比較する
	for (i=0;i<inListNum;i++){
		type1 = PokePersonalParaGet( inData[i].MonsNo, ID_PER_type1 );
		type2 = PokePersonalParaGet( inData[i].MonsNo, ID_PER_type2 );
		if ( (type1 == type)||(type2 == type) ){
			//同じタイプならリストにエントリー
			same_type[cnt++] = i; 
		}
	}
	//エンカウントリスト内に指定タイプがいない、もしくは、リスト内は全て指定タイプなら普通にエンカウントさせる
	if ( (cnt == 0)||(cnt==inListNum) ){
		return FALSE;
	}
	*outNo = same_type[gf_rand()%cnt];//指定タイプのポケモンを出現させる(確率一定)
	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * 指定タイプのポケモンとエンカウントさせる
 *
 * @param	inPokeParam		ポケモンパラム
 * @param	inFldSpa		特性チェック・フォルム変更用構造体へのポインタ
 * @param	inData			共通エンカウントデータテーブル
 * @param	inListNum		リスト数
 * @param	type			タイプ
 * @param	tokusei			特性
 * @param	outNo			テーブル番号格納バッファ
 *
 * @return	BOOL		TRUE:成功	FALSE:失敗
 */
//-----------------------------------------------------------------------------
static BOOL CheckFixTypeEcnt(	POKEMON_PARAM *inPokeParam,
							const ENC_FLD_SPA *inFldSpa,
							const ENC_COMMON_DATA *inData,
							const u8 inListNum,
							const u8 type, const u8 tokusei,u8 * outNo)
{
	// 先頭のポケモンがタマゴでない
	if( inFldSpa->Egg == 0 ){
		if( inFldSpa->Spa == tokusei ){
			// 1/2で特性発動
			if( gf_p_rand(2) == 0 ){
				return FixPokeSet(inData, inListNum, type, outNo);
			}
		}
	}
	//特性発動しない
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * エンカウント率変更
 *
 * @param	IsFishing		釣りかどうか
 * @param	inProb			確率
 * @param	inFldSpa		特性チェック・フォルム変更用構造体へのポインタ
 * @param	inWeatherCode	天気
 * @param	inPokeParam		ポケモンパラム
 *
 * @return	u8				確率
 */
//-----------------------------------------------------------------------------
static u8 ChangeEncProb(	const BOOL inIsFishing,
							const u8 inProb,
							const ENC_FLD_SPA *inFldSpa,
							const u32 inWeatherCode,
							POKEMON_PARAM *inPokeParam	)
{
	int prob;

	prob = inProb;
	// 先頭のポケモンがタマゴでない
	if( inFldSpa->Egg == 0 ){
		if (inIsFishing){		//釣り
			//きゅうばん、ねんちゃくならエンカウント率2倍
			if( (inFldSpa->Spa == TOKUSYU_NENTYAKU)||(inFldSpa->Spa == TOKUSYU_KYUUBAN) ){
				prob*2;
			}
		}else{					//釣り以外
			//ありじごく、ノーガードならエンカウント率2倍
			//砂嵐中、すながくれなら1/2
			//吹雪中、ゆきがくれなら1/2
			//しろいきりなら1/2
			//はやあしなら1/2
			if( (inFldSpa->Spa == TOKUSYU_ARIZIGOKU)||
				(inFldSpa->Spa == TOKUSYU_NOOGAADO)||
				(inFldSpa->Spa == TOKUSYU_HAKKOU) ){	//発光は隠し特性ではありません
				prob*=2;
			}else if(inFldSpa->Spa == TOKUSYU_SUNAGAKURE){
				//天候チェック(砂嵐)
				if(inWeatherCode == WEATHER_SYS_SANDSTORM){
					prob/=2;
				}
			}else if(inFldSpa->Spa == TOKUSYU_YUKIGAKURE){
				//天候チェック（雪、吹雪、猛吹雪）
				if ( (inWeatherCode == WEATHER_SYS_SNOW)||
					 (inWeatherCode == WEATHER_SYS_SNOWSTORM)||
					 (inWeatherCode == WEATHER_SYS_SNOWSTORM_H) ){
					prob/=2;
				}
			}else if( (inFldSpa->Spa == TOKUSYU_SIROIKEMURI)||
					  (inFldSpa->Spa == TOKUSYU_HAYAASI)||
					  (inFldSpa->Spa == TOKUSYU_AKUSYUU) ){		//悪臭は隠し特性ではありません
				prob/=2;
			}
		}

		if (prob>100){		//100%こえたら　100%にする
			prob = 100;
		}
	}
	
	return prob;
}

//-----------------------------------------------------------------------------
/**
 * レベル差による戦闘回避（隠し特性）
 *
 * @param	inFldSpa		特性チェック・フォルム変更用構造体へのポインタ
 * @param	inMyPokeParam	ポケモンパラム
 * @param	inEneLv			相手のレベル
 *
 * @return	BOOL	TRUE:回避成功	FALSE:回避失敗
 */
//-----------------------------------------------------------------------------
static BOOL CheckEcntCancelByLv( const ENC_FLD_SPA *inFldSpa, POKEMON_PARAM *inMyPokeParam, const u8 inEneLv)
{
	u8 my_poke_lv;
	//キャンセルする場合は回避しない
	if ( inFldSpa->EncCancelSpInvalid ){
		return FALSE;
	}
	
	if (inFldSpa->Egg == 0){
		if( (inFldSpa->Spa == TOKUSYU_SURUDOIME)||(inFldSpa->Spa == TOKUSYU_IKAKU) ){//するどいめ、いかく
			//手持ちのレベルを取得
			my_poke_lv = PokeParaGet(inMyPokeParam, ID_PARA_level, NULL);
			//手持ちがレベル５以下のときは特性無効
			if (my_poke_lv<=5){
				return FALSE;		//戦闘回避しない
			}
			// 相手LV＜＝手持ちLV-５
			if( inEneLv <= my_poke_lv-5 ){
				// 1/2でエンカウント回避
				if (gf_p_rand(2) == 0){
					return TRUE;		//戦闘回避
				}
			}
		}
	}

	return FALSE;		//戦闘回避しない
}

//-----------------------------------------------------------------------------
/**
 * ファイトタイプの決定
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inSafariFlg		サファリフラグ
 * @param	param			バトルパラム
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void SetFieldBattleParam(FIELDSYS_WORK * fsys, const BOOL inSatafiFlg, BATTLE_PARAM **param)
{
	if (!inSatafiFlg){
		//バトルパラメータのアロケーションとポケモンパーティの初期化(野生戦)
		(*param) = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);
	}else {		//サファリフラグ成立なら
		//バトルパラメータのアロケーションとポケモンパーティの初期化(サファリ)
		u16 * ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));
		(*param) = BattleParam_CreateForSafari(HEAPID_WORLD, *ball);
	}
}

//-----------------------------------------------------------------------------
/**
 * サファリ特殊枠モンスターのセット
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inSafariFlg		サファリフラグ
 * @param	inBookGet		全国図鑑入手フラグ
 * @param	enc_data		共通エンカウントデータテーブル
 *
 * @return	none
 */
//-----------------------------------------------------------------------------

static void SetSfariMonster(FIELDSYS_WORK * fsys, const BOOL inSafariFlg, const BOOL inBookGet, ENC_COMMON_DATA *enc_data)
{
	if (inSafariFlg){	//サファリフラグ成立なら
		//サファリ特殊枠のポケモンセット
		SafariEnc_SetSafariEnc(	EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(fsys->savedata), ENC_RND_SEED_SAFARI),
								inBookGet,
								fsys->location->zone_id,
								&enc_data[SP_ENC_1].MonsNo, &enc_data[SP_ENC_2].MonsNo);
	}
}

//-----------------------------------------------------------------------------
/**
 * スプレーチェック
 *
 * @param	
 *
 * @return	BOOL	TRUE:スプレー発動	FALSE:スプレー不発
 */
//-----------------------------------------------------------------------------
static BOOL CheckSpray(const u8 inEneLv, const ENC_FLD_SPA *inSpa)
{
	if (inSpa->SprayCheck){
		//レベル比較
		if (inSpa->SpMyLv > inEneLv){
			OS_Printf("スプレー効果発揮\n");
			return TRUE;
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * 移動ポケモンエンセット
 *
 * @param	
 *
 * @return	BOOL	TRUE:エンカウント	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static void SetMovePokemon(const u32 inTrainerID, MPD_PTR mpd, BATTLE_PARAM *outBattleParam)
{
	int monsno;
	u8 lv;
	u32 pow_rnd;
	u32 per_rnd;
	u32 cond;
	u16 hp;
	
	BOOL rc;
	POKEMON_PARAM *poke_param;
	
	poke_param = PokemonParam_AllocWork(HEAPID_FIELD);
	
	monsno = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO);
	lv = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV);
	pow_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_POW_RND);
	per_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_PER_RND);
	cond = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_COND);
	hp = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_HP);

	PokeParaSetPowRnd( poke_param, monsno, lv, pow_rnd, per_rnd );
	
	PokeParaPut( poke_param, ID_PARA_id_no, &inTrainerID );		// ＩＤ
	PokeParaPut( poke_param, ID_PARA_condition, &cond );		// コンディション
	PokeParaPut( poke_param, ID_PARA_hp,        &hp );		// HP

	//アイテムを所持していないので、直接アッドする
	rc = PokeParty_Add(outBattleParam->poke_party[POKEPARTY_ENEMY], poke_param);
	GF_ASSERT(rc&&"ポケモンの追加に失敗");
	sys_FreeMemoryEz(poke_param);
}

//-----------------------------------------------------------------------------
/**
 * 移動ポケモンエンカウントチェック
 *
 * @param	
 *
 * @return	BOOL	TRUE:エンカウント	FALSE:エンカウントしない
 */
//-----------------------------------------------------------------------------
static BOOL CheckMovePokeEnc(FIELDSYS_WORK * fsys, MPD_PTR *outMpd)
{
	ENC_SV_PTR data;
	MPD_PTR temp[MOVE_POKE_MAX];
	u8 enc_count;
	u8 i;
	int zone;

	//同じ場所にいる移動ポケモンを取得
	enc_count = 0;
	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	for(i=0;i<MOVE_POKE_MAX;i++){
		zone = MP_GetMovePokeZone(EncDataSave_GetMovePokeZoneIdx(data,i));
		if( EncDataSave_IsMovePokeValid(data,i)&&
				(zone == fsys->location->zone_id) ){
			temp[enc_count] = EncDataSave_GetMovePokeDataPtr(data, i);
			enc_count++;
		}
	}

	if (enc_count == 0){
		return FALSE;			//移動ポケモンいない
	}else{
		//いる場合、5割でエンカウント
		if ( gf_p_rand(2) == 0 ){
			return FALSE;
		}
	}
	
	if (enc_count>1){
		//ランダムで選出
		(*outMpd)  = temp[ gf_p_rand(enc_count) ];
	}else{
		//1匹しかいないので確定
		(*outMpd)  = temp[0];
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 * 戦闘するポケモンをバトルパラムに追加
 *
 * @param	inTarget			追加対象
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	ioPokeParam			ポケモンパラム
 * @param	ioBattleParam		バトルパラム
 *
 * @return	BOOL		ポケパーティ追加結果
 */
//-----------------------------------------------------------------------------
static BOOL AddPokemonParam(const int inTarget, const ENC_FLD_SPA *inFldSpa,
							POKEMON_PARAM *ioPokeParam, BATTLE_PARAM *ioBattleParam )
{
	int range = ITEM_RANGE_NORMAL;
	//特性ふぐがんチェック
	if (inFldSpa->Egg == 0){
		if (inFldSpa->Spa == TOKUSYU_HUKUGAN){
			range = ITEM_RANGE_HUKUGAN;
		}
	}
	
	PokeItemSet(ioPokeParam, ioBattleParam->fight_type , range);

	//フォルム変更
	{
		u8 change_flg;
		u8 form_no;
		int monsno;
		change_flg = 0;
		monsno = PokeParaGet( ioPokeParam, ID_PARA_monsno, NULL );
		//フォルム変更データは確率で入っているが、現状、変化するかしないかの２択なので、0でなければ、変更する
		if (monsno == MONSNO_SIIUSI ){
			change_flg = 1;
			if (!inFldSpa->FormProb[0]){
				form_no = FORMNO_SII_WEST;	//西側デフォルト
				OS_Printf("西\n");
			}else{
				form_no = FORMNO_SII_EAST;	//東側フォルム変更
				OS_Printf("東\n");
			}
		}else if(monsno == MONSNO_SIIDORUGO){
			change_flg = 1;
			if (!inFldSpa->FormProb[1]){
				form_no = FORMNO_SII_WEST;	//西側デフォルト
			}else{
				form_no = FORMNO_SII_EAST;	//東側フォルム変更
			}
		}else if(monsno == MONSNO_ANNOON){
			u8 num;
			change_flg = 1;
			//出現タイプを取得
			num = ANNOON_Table[ inFldSpa->AnnoonTblType ].Num;
			form_no = ANNOON_Table[ inFldSpa->AnnoonTblType ].Tbl[ gf_rand()%num ];
		}

		if (change_flg){
			PokeParaPut(ioPokeParam,ID_PARA_form_no,(u8 *)&form_no);
		}

	}
	return PokeParty_Add(ioBattleParam->poke_party[inTarget], ioPokeParam);
}

//地上戦処理：指定したテーブル番号の示すポケモンの中で一番レベルの高いテーブル番号を返す(隠し特性処理)
//-----------------------------------------------------------------------------
/**
 * 地上戦処理：指定したテーブル番号の示すポケモンの中で一番レベルの高いテーブル番号を返す(隠し特性処理)

 *
 * @param	inEncCommonData		共通エンカウントデータテーブル
 * @param	inFldSpa			特性チェック・フォルム変更用構造体へのポインタ
 * @param	inTblNo				テーブルナンバー
 *
 * @return	u8					変更後テーブルナンバー
 */
//-----------------------------------------------------------------------------
static u8 GetMaxLvMonsTblNo(const ENC_COMMON_DATA *inEncCommonData, const ENC_FLD_SPA *inFldSpa, const u8 inTblNo)
{
	u8 tbl_no;
	u8 i;
	if (inFldSpa->Egg == 0){
		//やるき、はりきり、プレッシャー 特性発動チェックレベルの高いポケモンと５割でエンカウント
		if ( (inFldSpa->Spa == TOKUSYU_YARUKI)||
			 (inFldSpa->Spa == TOKUSYU_HARIKIRI)||
			 (inFldSpa->Spa == TOKUSYU_PURESSYAA) ){
			
			//5割で発動
			if (gf_p_rand(2) == 0){
				return inTblNo;			//特性未発動
			}
			
			//テーブル番号保存
			tbl_no = inTblNo;
			//同じモンスターナンバーのテーブルを検索
			for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
				if (inEncCommonData[i].MonsNo == inEncCommonData[tbl_no].MonsNo){ //同じモンスターナンバーか？
					//レベル比較
					if (inEncCommonData[i].LvMax > inEncCommonData[tbl_no].LvMax){
						//テーブル番号の更新
						tbl_no = i;
					}
				}
			}
			return tbl_no;
		}
	}

	return inTblNo;
}

//-----------------------------------------------------------------------------
/**
 * 特性、スプレーチェックなどの情報を集計して構造体にセット

 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inPokeParam		自分のポケモンパラム
 * @param	inData			エンカウントデータ
 * @param	outSpa			情報構造体ポインタ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void SetSpaStruct(FIELDSYS_WORK *fsys, POKEMON_PARAM *inPokeParam, ENCOUNT_DATA* inData, ENC_FLD_SPA *outSpa  )
{
	//先頭ポケモンのタマゴチェック
	if( PokeParaGet( inPokeParam, ID_PARA_tamago_flag, NULL ) == 0 ){
		// 先頭のポケモンがタマゴでない
		outSpa->Egg = 0;
		outSpa->Spa = PokeParaGet(inPokeParam, ID_PARA_speabino, NULL);	// 特殊能力取得
	}else{
		// 先頭のポケモンがタマゴ
		outSpa->Egg = 1;
		outSpa->Spa = TOKUSYU_MAX;
	}

	outSpa->SpMyLv = 0;
	outSpa->SprayCheck = FALSE;
	outSpa->EncCancelSpInvalid = FALSE;
	
	if (inData != NULL){
		//シーウシ・シードルゴフォルム変更確率セット
		outSpa->FormProb[0] = inData->FormProb[0];	//シーウシ
		outSpa->FormProb[1] = inData->FormProb[1];	//シードルゴ
		//アンノーン
		if (inData->AnnoonTable != 0){
			GF_ASSERT(inData->AnnoonTable<=8&&"annoon_table_over");
			//アンノーンテーブルタイプセット
			outSpa->AnnoonTblType = inData->AnnoonTable-1;
		}else{
			outSpa->AnnoonTblType = 0;
		}
	}
	//トレーナーＩＤのセット
	outSpa->TrainerID = MyStatus_GetID( SaveData_GetMyStatus(fsys->savedata) );
	
}

#ifdef PM_DEBUG

//-----------------------------------------------------------------------------
/**
 * 釣りエンカウント
 * ※サファリにいたとしても、釣では特殊枠が無いので、サファリモンスターのセットは行わない
 *
 * @param	fsys				フィールドシステムポインタ
 * @param	inRodtype			釣り竿
 *
 * @return	BOOL
 */
//-----------------------------------------------------------------------------
BOOL DebugSetFishingEncount( FIELDSYS_WORK * fsys, const u8 inRodType )
{
	BATTLE_PARAM * battle_param;
	POKEMON_PARAM *poke_param;
	POKEPARTY *my_party;
	BOOL safari_flg;		//サファリフラグ

	ENC_COMMON_DATA enc_data[ENC_MONS_NUM_MAX];
	ENC_FLD_SPA f_spa;		//特殊能力

	{
		u8 prob;
#ifdef PM_DEBUG
		if (DebugFishProbFlg){
			prob = 100;
		}else{
			// エンカウント率
			prob = GetEncountProbFishing(fsys, inRodType);
		}
#else
		// エンカウント率
		prob = GetEncountProbFishing(fsys, inRodType);
#endif
		if(  prob == 0 ){
			return FALSE;		//確率が0
		}

		//手持ちポケパーティ取得
		my_party = SaveData_GetTemotiPokemon(fsys->savedata);
		poke_param = PokeParty_GetMemberPointer(my_party, 0);	//先頭ポケモン取得
		SetSpaStruct(fsys, poke_param, NULL, &f_spa );
	
		//釣りでは、スプレーチェックをしない
	
		//特性によってエンカウント率変更
		prob = ChangeEncProb(	TRUE, prob, &f_spa,
								Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata)),
								poke_param	);
		//確率でエンカウント
		if (gf_p_rand(100) >= prob){
			return FALSE;		//エンカウントしない
		}
	}
	//サファリフラグを取得
	safari_flg = SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata));

	//バトルパラメータセット
	SetFieldBattleParam(fsys, safari_flg, &battle_param);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(battle_param, fsys);


	if ( (ZoneData_IsSpFishingZone(fsys->location->zone_id))&&
			 SpFishing_CheckPoint(fsys) ){
		//特殊釣りデータ作成
		u8 i;
		int monsno;
		u8 max,min;
		SpFishing_GetMaxMinLv(&max, &min);
		SpFishing_GetMonsNo(&monsno);
		
		for(i=0;i<ENC_MONS_NUM_FISH;i++){
			enc_data[i].MonsNo = monsno;
			enc_data[i].LvMax = max;
			enc_data[i].LvMin = min;
		}
	}else{
		//共通エンカウントデータ作成
		{
			NON_GROUND_ENC_MONSTER_DAT *enc_fish;
			u8 i;
			ENCOUNT_DATA *data;

			data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);	
		
			//釣り竿別にデータ作成
			switch(inRodType){
			case FISHINGROD_BAD:		//ボロ
				enc_fish = data->EncFish1;
				break;
			case FISHINGROD_GOOD:		//いい
				enc_fish = data->EncFish2;
				break;
			case FISHINGROD_GREAT:		//すごい
				enc_fish = data->EncFish3;
				break;
			}
		
			for(i=0;i<ENC_MONS_NUM_FISH;i++){
				enc_data[i].MonsNo = enc_fish[i].MonsterNo;
				enc_data[i].LvMax = enc_fish[i].MaxLevel;
				enc_data[i].LvMin = enc_fish[i].MinLevel;
			}	
		}
	}

	//釣りエンカウント
	{
		BOOL rc;
		rc = FishingEncSingle( fsys, poke_param, battle_param, enc_data, &f_spa, inRodType );
		if (!rc){
			return FALSE;
		}
	}
	
	return TRUE;
}

#endif


