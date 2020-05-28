//============================================================================================
/**
 * @file	savedata.c
 * @brief	セーブデータ管理
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.12
 *
 * @li		2006.04.17	セーブロードシステムをsaveload_system.cに分離
 */
//============================================================================================

#include "common.h"
#include "gflib/system.h"


#include "system/gamedata.h"

#include "savedata/savedata.h"
#include "savedata_local.h"


//セーブデータ内容を扱うのに必要な関数参照のためのヘッダ

#include "poketool/poke_tool.h"
#include "../poketool/poke_tool_def.h"

#include "savedata/system_data.h"
#include "playerdata_local.h"
#include "poketool/pokeparty.h"
#include "itemtool/myitem.h"
#include "field/eventflag.h"
#include "field/poketch_data.h"
#include "field/situation.h"
#include "savedata/zukanwork.h"
#include "savedata/sodateyadata.h"
#include "savedata/friendlist.h"
#include "savedata/undergrounddata.h"
#include "savedata/regulation.h"
#include "savedata/imageclip_data.h"
#include "savedata/honeytree_data.h"
#include "savedata/wifilist.h"
#include "savedata/randomgroup.h"
#include "savedata/fnote_mem.h"
#include "savedata/trainercard_data.h"
#include "savedata/wifihistory.h"

#include "savedata/mail_util.h"
#include "savedata/poruto_util.h"
#include "poketool/boxdata.h"
#include "savedata/record.h"
#include "savedata/guinness.h"

#include "savedata/custom_ball.h"
#include "savedata/contest_savedata.h"

#include "savedata/misc.h"
#include "misc_local.h"

#include "savedata/perapvoice.h"
#include "savedata/perapvoice_local.h"
#include "savedata/b_tower.h"
#include "savedata/b_tower_local.h"

#include "savedata/sp_ribbon.h"
#include "savedata/dendou_data.h"
#include "savedata/encount.h"
#include "savedata/fushigi_data.h"
#include "savedata/worldtrade_data.h"
#include "savedata/tv_work.h"
#include "savedata/pokepark_data.h"
#include "system/pms_word.h"


//=============================================================================
//=============================================================================

//============================================================================================
//
//
//		ロムデータ
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ内容定義
 */
//---------------------------------------------------------------------------
const SAVEDATA_TABLE SaveDataTable[] = {
//ノーマルデータグループ
	{	//システムデータ
		GMDATA_ID_SYSTEM_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SYSTEMDATA_GetWorkSize,
		(FUNC_INIT_WORK)SYSTEMDATA_Init,
	},
	{	//プレイヤーデータ
		GMDATA_ID_PLAYER_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PLAYERDATA_GetWorkSize,
		(FUNC_INIT_WORK)PLAYERDATA_Init,
	},
	{	//手持ちポケモン
		GMDATA_ID_TEMOTI_POKE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PokeParty_GetWorkSize,
		(FUNC_INIT_WORK)PokeParty_InitWork,
	},
	{	//手持ちどうぐ
		GMDATA_ID_TEMOTI_ITEM,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MyItem_GetWorkSize,
		(FUNC_INIT_WORK)MyItem_Init,
	},
	{	//イベントワーク
		GMDATA_ID_EVENT_WORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)EventWork_GetWorkSize,
		(FUNC_INIT_WORK)EventWork_Init,
	},
	{	//ポケッチデータ
		GMDATA_ID_POKETCH_DATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PoketchData_GetWorkSize,
		(FUNC_INIT_WORK)PoketchData_Init,
	},
	{	//状況データ
		GMDATA_ID_SITUATION,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)Situation_GetWorkSize,
		(FUNC_INIT_WORK)Situation_Init,
	},
	{	//ずかんデータ
		GMDATA_ID_ZUKANWORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)ZukanWork_GetWorkSize,
		(FUNC_INIT_WORK)ZukanWork_Init,
	},
	{	//育て屋データ
		GMDATA_ID_SODATEYA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SodateyaWork_GetWorkSize,
		(FUNC_INIT_WORK)SodateyaWork_Init,
	},
	{	//しりあいグループ
		GMDATA_ID_FRIEND,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FriendList_GetWorkSize,
		(FUNC_INIT_WORK)FriendList_Init,
	},
	{	//その他データ
		GMDATA_ID_MISC,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MISC_GetWorkSize,
		(FUNC_INIT_WORK)MISC_Init,
	},
	{	//フィールドOBJセーブ
		GMDATA_ID_FIELDOBJSV,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FieldObjSv_GetWorkSize,
		(FUNC_INIT_WORK)FieldObjSv_Init,
	},
	{	//地下アイテムデータ+秘密基地データ
		GMDATA_ID_UNDERGROUNDDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)UnderGroundData_GetWorkSize,
		(FUNC_INIT_WORK)UnderGroundData_Init,
	},
    {  // レギュレーションデータ
        GMDATA_ID_REGULATION,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RegulationData_GetWorkSize,
		(FUNC_INIT_WORK)RegulationData_Init,
    },
	{	//イメージクリップのデータ
		GMDATA_ID_IMAGECLIPDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)ImcSaveData_GetWorkSize,
		(FUNC_INIT_WORK)ImcSaveData_Init,
	},
	{	//メールのデータ
		GMDATA_ID_MAILDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)MAIL_GetBlockWorkSize,
		(FUNC_INIT_WORK)MAIL_Init,
	},
	{	//ポルトのデータ
		GMDATA_ID_PORUTODATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PORUTO_GetSaveWorkSize,
		(FUNC_INIT_WORK)PORUTO_Init,
	},
	{	// 乱数の種グループ
		GMDATA_ID_RANDOMGROUP,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RandomGroup_GetWorkSize,
		(FUNC_INIT_WORK)RandomGroup_Init,
	},
	{	//冒険ノートのデータ
		GMDATA_ID_FNOTE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FNOTE_GetWorkSize,
		(FUNC_INIT_WORK)FNOTE_InitAll,
	},
	{	//トレーナーカード
		GMDATA_ID_TRCARD,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TRCSave_GetSaveDataSize,
		(FUNC_INIT_WORK)TRCSave_InitSaveData,
	},
	{	//レコード用カウントアップデータ
		GMDATA_ID_RECORD,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)RECORD_GetWorkSize,
		(FUNC_INIT_WORK)RECORD_Init,
	},
	{	//カスタムボール
		GMDATA_ID_CUSTOM_BALL,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)CustomBall_GetWorkSize,
		(FUNC_INIT_WORK)CustomBall_Init,
	},
	{	//ぺラップ音声データ
		GMDATA_ID_PERAPVOICE,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PERAPVOICE_GetWorkSize,
		(FUNC_INIT_WORK)PERAPVOICE_Init,
	},
	{	//バトルタワーデータ
		GMDATA_ID_BTLTOWER,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TowerData_GetWorkSize,
		(FUNC_INIT_WORK)TowerData_Init,
	},
	{	//配布リボンデータ
		GMDATA_ID_SP_RIBBON,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)SP_RIBBON_GetWorkSize,
		(FUNC_INIT_WORK)SP_RIBBON_Init,
	},
	{
		// エンカウント関連データ
		GMDATA_ID_ENCOUNT,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)EncDataSave_GetWorkSize,
		(FUNC_INIT_WORK)EncDataSave_InitSaveData,
	},
	{	//世界交換データ
		GMDATA_ID_WORLDTRADEDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WorldTradeData_GetWorkSize,
		(FUNC_INIT_WORK)WorldTradeData_Init,
	},
	{	//TVデータ
		GMDATA_ID_TVWORK,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)TVWORK_GetWorkSize,
		(FUNC_INIT_WORK)TVWORK_Init,
	},
	{	//ギネスホールデータ
		GMDATA_ID_GUINNESS,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)GuinnessData_GetWorkSize,
		(FUNC_INIT_WORK)GuinnessData_Init,
	},
	{	// Wifi用、自分情報・友達情報
		GMDATA_ID_WIFILIST,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WifiList_GetWorkSize,
		(FUNC_INIT_WORK)WifiList_Init,
	},

	{	//WiFi通信履歴データ
		GMDATA_ID_WIFIHISTORY,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)WIFIHISTORY_GetWorkSize,
		(FUNC_INIT_WORK)WIFIHISTORY_Init,
	},
	{	//ふしぎな贈り物データ
		GMDATA_ID_FUSHIGIDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)FUSHIGIDATA_GetWorkSize,
		(FUNC_INIT_WORK)FUSHIGIDATA_Init,
	},
	{	//ポケパーク用ポケモンデータ
		GMDATA_ID_POKEPARKDATA,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)POKEPARKDATA_GetWorkSize,
		(FUNC_INIT_WORK)POKEPARKDATA_Init,
	},
	{	//コンテスト
		GMDATA_ID_CONTEST,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)CONDATA_GetWorkSize,
		(FUNC_INIT_WORK)CONDATA_Init,
	},
	{	// 簡易会話単語
		GMDATA_ID_PMS,
		SVBLK_ID_NORMAL,
		(FUNC_GET_SIZE)PMSW_GetSaveDataSize,
		(FUNC_INIT_WORK)PMSW_InitSaveData,
	},
//ボックスデータグループ
	{	//ポケモンボックスのデータ
		GMDATA_ID_BOXDATA,
		SVBLK_ID_BOX,
		(FUNC_GET_SIZE)BOXDAT_GetTotalSize,
		(FUNC_INIT_WORK)BOXDAT_Init,
	},

};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
const int SaveDataTableMax = NELEMS(SaveDataTable);



//============================================================================================
//
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	テレビデータのポインタ取得
 * @param	sv			セーブデータ構造へのポインタ
 * @return	BOX_DATA	テレビデータへのポインタ
 */
//---------------------------------------------------------------------------
TV_WORK * SaveData_GetTvWork(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_TVWORK);
}

//---------------------------------------------------------------------------
/**
 * @brief	ボックスデータのポインタ取得
 * @param	sv			セーブデータ構造へのポインタ
 * @return	BOX_DATA	ボックスデータへのポインタ
 */
//---------------------------------------------------------------------------
BOX_DATA * SaveData_GetBoxData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_BOXDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	ふしぎな贈り物用セーブデータへのポインタ取得
 * @param	sv				セーブデータ構造へのポインタ
 * @return	FUSHIGI_DATA	ふしぎな贈り物データへのポインタ
 */
//---------------------------------------------------------------------------
FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_FUSHIGIDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	ポケパーク用セーブデータへのポインタ取得
 * @param	sv				セーブデータ構造へのポインタ
 * @return	POKEPARK_DATA	ポケパーク用セーブデータへのポインタ
 */
//---------------------------------------------------------------------------
POKEPARK_DATA * SaveData_GetPokeParkData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_POKEPARKDATA);
}

//============================================================================================
//
//
//			特殊セーブデータ
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータの定義テーブル
 */
//---------------------------------------------------------------------------
const EXSAVEDATA_TABLE ExtraSaveDataTable[] = {
	{
		// 殿堂入りデータ
		EXDATA_ID_DENDOU,
		SAVE_PAGE_MAX + 0,
		(FUNC_GET_SIZE)DendouData_GetWorkSize,
		(FUNC_INIT_WORK)DendouData_Init,
	},

	{	//ふしぎ贈り物データ
		EXDATA_ID_FUSHIGIDATA,
		SAVE_PAGE_MAX + 3,
		(FUNC_GET_SIZE)FUSHIGIDATA_GetWorkSize,
		(FUNC_INIT_WORK)FUSHIGIDATA_Init,
	},

};
//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータのテーブル数
 */
//---------------------------------------------------------------------------
const int ExtraSaveDataTableMax = NELEMS(ExtraSaveDataTable);



//============================================================================================
//
//
//			個別の特殊セーブデータアクセス関数
//
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータロード：殿堂入りデータ
 * @param	sv			セーブデータ構造へのポインタ
 * @param	heap_id		ワークを取得するヒープのID
 * @param	result
 * @return	void *	取得したセーブデータを載せたワークへのポインタ
 */
//---------------------------------------------------------------------------
DENDOU_SAVEDATA * SaveData_Extra_LoadDendouData(SAVEDATA * sv, int heap_id, LOAD_RESULT * result)
{
	return SaveData_Extra_LoadAlloc(sv, heap_id, EXDATA_ID_DENDOU, result);
}

//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータセーブ：殿堂入りデータ
 * @param	sv			セーブデータ構造へのポインタ
 * @param	data		殿堂入りデータへのポインタ
 * @retval	SAVE_RESULT_OK		セーブ成功
 * @retval	SAVE_RESULT_NG		セーブ失敗
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Extra_SaveDendouData(SAVEDATA * sv, DENDOU_SAVEDATA * data)
{
	return SaveData_Extra_Save(sv, EXDATA_ID_DENDOU, data);
}


#if 0

通常セーブデータに含まれるようになったために削除

//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータロード：ふしぎなおくりもの
 * @param	sv			セーブデータ構造へのポインタ
 * @param	heap_id		ワークを取得するヒープのID
 * @param	result		ロード結果取得用のワーク
 * @return	void *	取得したセーブデータを載せたワークへのポインタ
 */
//---------------------------------------------------------------------------
FUSHIGI_DATA * SaveData_Extra_LoadFushigiData(SAVEDATA * sv, int heap_id, LOAD_RESULT * result)
{
	return SaveData_Extra_LoadAlloc(sv, heap_id, EXDATA_ID_FUSHIGIDATA, result);
}

//---------------------------------------------------------------------------
/**
 * @brief	特殊セーブデータセーブ：ふしぎなおくりもの
 * @param	sv			セーブデータ構造へのポインタ
 * @param	data		殿堂入りデータへのポインタ
 * @retval	SAVE_RESULT_OK		セーブ成功
 * @retval	SAVE_RESULT_NG		セーブ失敗
 */
//---------------------------------------------------------------------------
SAVE_RESULT SaveData_Extra_SaveFushigiData(SAVEDATA * sv, FUSHIGI_DATA * data)
{
	return SaveData_Extra_Save(sv, EXDATA_ID_FUSHIGIDATA, data);
}
#endif


