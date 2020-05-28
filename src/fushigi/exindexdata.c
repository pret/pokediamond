//============================================================================================
/**
 * @file	exindexdata.c
 * @bfief	外部参照ファイルの作成
 * @author	Satoshi Mitsuhara
 * @date	06.07.30
 *
 * $Id: exindexdata.c,v 1.3 2006/08/02 12:08:42 mitsuhara Exp $
 */
//============================================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/system_data.h"

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "../field/sysflag_def.h"

#include "field/location.h"
#include "field/situation.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"

#include "itemtool/myitem.h"

#ifdef CREATE_INDEX

void CreateIndexData(int heapid);

typedef struct {
  // セーブデータの構造体はsrc/savedata/saveload_system.cにあるので参照する事
  // 主にSAVEDATA.SAVEWORKの構造を定義

  // SAVEDATAからの各セーブ項目のオフセット
  // ※ただし各構造体の内容は固定が保障されていないため、ここで得られたポインタを
  // 　元に構造体を直接アクセスする時には互換性に注意をしてください！
  u32 savework_offset[GMDATA_ID_MAX];

  // ■■■↓ずかん用ワーク参照用(GMDATA_ID_ZUKANWORKからのオフセット)
  // ずかんを持っているかフラグのオフセット
  u32 zukan_get_offset;
  // ぜんこくずかんモードかのフラグのオフセット
  u32 zenkoku_flag_offset;
  // ずかん：捕まえたフラグ用ワークのオフセット
  u32 get_flag_offset;
  // ずかん：見つけたフラグ用ワークのオフセット
  u32 see_flag_offset;
  // ずかん：オスメスフラグ用ワークのオフセット
  u32 sex_flag_offset;

  // ■■■↓ゲームの進行状況参照用(GMDATA_ID_EVENT_WORKからのオフセット)
  // ゲームフラグ参照用
  u32 game_flag_offset;
  // ゲームクリアフラグの番号(u8 game_flag_offset[game_clear_flag / 8])
  u32 game_clear_flag;
  // バッグを入手したかフラグ
  u32 game_bag_flag;

  // ■■■↓ポケモンセンターでセーブしてるかを得るための布石
  // ポケモンセンターでセーブしているかを調べる方法
  // 下記のsituation_offsetからセーブしたLOCATION_WORK構造体へのポインタを得る
  // その中にあるzone_idがセーブした際のマップ管理IDになります。
  // zone_idがZONE_ID_???PC0101～ZONE_ID_???PC0103ならばポケモンセンターです。
  // 全部で51マップと比較する必要があります。
  // ※参照ファイル
  // src/field/situation.cのLOCATION_WORK nowメンバ
  // src/fielddata/maptable/zone_id.h
  // ※「grep PC src/fielddata/maptable/zone_id.h」
  u32 situation_now_offset;

  // ■■■↓自分情報
  // MYSTATUSへのオフセット
  //  u32 mystatus_offset; ← これはsavework_offset[GMDATA_ID_PLAYER_DATA]と同等
  // プレイヤーの名前へのオフセット
  u32 mystatus_name_offset;
  // プレイヤーのID
  u32 mystatus_id_offset;
  // プレイヤーの性別
  u32 mystatus_sex_offset;
  
  // ■■■↓手持ちポケモン関連
  // 手持ちポケモンはPOKEPARTY構造体で管理されている
  // u32 pokeparty_offset; ← これはsavework_offset[GMDATA_ID_TEMOTI_POKE]と同等
  // 手持ちのポケモン数
  u32 pokecount_offset;
  // 手持ちポケモンへのオフセット(POKEMON_PARAMがTEMOTI_POKEMAX分)
  u32 pokemon_member_offset;
  // sizeof(POKEMON_PARAM) ※多分変更ないと思うけど念のため
  u32 sizeof_pokemon_param;

  // ■手持ちアイテム関連
  // u32 myitem_offset; ← これはsavework_offset[GMDATA_ID_TEMOTI_ITEM]と同等
  // sizeof(MINEITEM)
  u32 sizeof_mineitem;
  // 道具ポケット最大数
  u32 bag_normal_item_max;
  // 大切な物ポケット最大数
  u32 bag_event_item_max;
  // 技マシンポケット最大数
  u32 bag_waza_item_max;
  // シールポケット最大数
  u32 bag_seal_item_max;
  // 薬ポケット最大数
  u32 bag_drug_item_max;
  // 木の実ポケット最大数
  u32 bag_nuts_item_max;
  // モンスターボールポケット最大数
  u32 bag_ball_item_max;
  // 戦闘用アイテムポケット最大数
  u32 bag_battle_item_max;
  // 道具ポケットへのオフセット
  u32 bag_normal_item_offset;
  // 大切な物ポケットへのオフセット
  u32 bag_event_item_offset;
  // 技マシンポケットへのオフセット
  u32 bag_waza_item_offset;
  // シールポケットへのオフセット
  u32 bag_seal_item_offset;
  // 薬ポケットへのオフセット
  u32 bag_drug_item_offset;
  // 木の実ポケットへのオフセット
  u32 bag_nuts_item_offset;
  // モンスターボールポケットへのオフセット
  u32 bag_ball_item_offset;
  // 戦闘用アイテムポケットへのオフセット
  u32 bag_battle_item_offset;
  
  // ■■■↓ボックス関連
  // パソコンに預けてあるポケモンはPOKEMON_PASO_PARAMで管理されている(多分変わらないけど念のため)
  // u32 box_data_offset; ← これはsavework_offset[GMDATA_ID_BOXDATA]と同等
  // ボックスのトレイ数
  u32 box_data_tray_max;
  // ボックス情報の先頭へのオフセット
  u32 box_data_offset;
  // sizeof(POKEMON_PASO_PARAM) ※多分変更ないと思うけど念のため
  u32 sizeof_pokemon_paso_param;

  // ■■■↓Wi-Fi関連
  // ログイン用GameSpyIDが入っている場所
  // もしも外部ソフトで同一のIDを利用したい場合に参照する可能性があります
  // なお、書き換えは絶対に不可！決定的な"READ-ONLY"です
  // u32 system_data_offset; ← これはsavework_offset[GMDATA_ID_SYSTEM_DATA]と同等
  // GTS・Wifiバトルタワーログイン用GameSpyID（初めて取得したGameSpyIdを保存する）
  u32 profile_id_offset;
  
} EXINDEX;


// 外部関数定義
extern LOCATION_WORK * Situation_GetNowLocation(SITUATION * st);


//------------------------------------------------------------------
/**
 * @brief	他ゲーム用インデックス情報を作成する関数
 * @param	NONE
 * @return	NONE
 * ※ 呼び出された後は無限ループにて停止
 */
//------------------------------------------------------------------
void CreateIndexData(int heapid)
{
  u32 uval1;
  void *up1, *up2;
  int i, ival1;

  SAVEDATA *sv;
  EXINDEX *ex;

  ex = sys_AllocMemory(heapid, sizeof(EXINDEX));

  sv = SaveData_GetPointer();

  // 各セーブ項目へのオフセットをセット
  up2 = SaveData_Get(sv, 0);
  for(i = 0; i < GMDATA_ID_MAX; i++){
    up1 = SaveData_Get(sv, i);	// up1 = absolute address
    ex->savework_offset[i] = (u32)up1 - (u32)up2;
  }

  // ずかんを持っているかのフラグ位置
  up1 = SaveData_Get(sv, GMDATA_ID_ZUKANWORK);
  ex->zukan_get_offset = (u32)Index_Get_Zukan_Offset(up1) - (u32)up1;
  ex->zenkoku_flag_offset = (u32)Index_Get_Zenkoku_Zukan_Offset(up1) - (u32)up1;
  ex->get_flag_offset = (u32)Index_Get_Get_Flag_Offset(up1) - (u32)up1;
  ex->see_flag_offset = (u32)Index_Get_See_Flag_Offset(up1) - (u32)up1;
  ex->sex_flag_offset = (u32)Index_Get_Sex_Flag_Offset(up1) - (u32)up1;

  // ゲームフラグ関連
  up1 = SaveData_Get(sv, GMDATA_ID_EVENT_WORK);
  ex->game_flag_offset = (u32)EventWork_GetEventFlagAdrs(up1, 1) - (u32)up1;
  ex->game_clear_flag = SYS_FLAG_GAME_CLEAR;
  ex->game_bag_flag = SYS_FLAG_BAG_GET;

  // セーブした場所を得る(ポケモンセンターでセーブしたかの比較用)
  up1 = SaveData_Get(sv, GMDATA_ID_SITUATION);
  ex->situation_now_offset = (u32)Situation_GetNowLocation(up1) - (u32)up1;

  // MYSTATUS関連
  up1 = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
  ex->mystatus_name_offset = (u32)Index_Get_Mystatus_Name_Offset(up1) - (u32)up1;
  ex->mystatus_id_offset = (u32)Index_Get_Mystatus_Id_Offset(up1) - (u32)up1;
  ex->mystatus_sex_offset = (u32)Index_Get_Mystatus_Sex_Offset(up1) - (u32)up1;

  // 手持ちポケモン関連
  up1 = SaveData_Get(sv, GMDATA_ID_TEMOTI_POKE);
  ex->pokecount_offset = (u32)Index_Get_PokeCount_Offset(up1) - (u32)up1;
  ex->pokemon_member_offset = (u32)PokeParty_GetMemberPointer(up1, 0) - (u32)up1;
  ex->sizeof_pokemon_param = PokemonParam_GetWorkSize();

  // アイテム関連
  up1 = SaveData_Get(sv, GMDATA_ID_TEMOTI_ITEM);
  ex->sizeof_mineitem = sizeof(MINEITEM);
  ex->bag_normal_item_max = BAG_NORMAL_ITEM_MAX;
  ex->bag_event_item_max = BAG_EVENT_ITEM_MAX;
  ex->bag_waza_item_max = BAG_WAZA_ITEM_MAX;
  ex->bag_seal_item_max = BAG_SEAL_ITEM_MAX;
  ex->bag_drug_item_max = BAG_DRUG_ITEM_MAX;
  ex->bag_nuts_item_max = BAG_NUTS_ITEM_MAX;
  ex->bag_ball_item_max = BAG_BALL_ITEM_MAX;
  ex->bag_battle_item_max = BAG_BATTLE_ITEM_MAX;
  ex->bag_normal_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_NORMAL) - (u32)up1;
  ex->bag_event_item_offset =  (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_EVENT) - (u32)up1;
  ex->bag_waza_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_WAZA) - (u32)up1;
  ex->bag_seal_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_SEAL) - (u32)up1;
  ex->bag_drug_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_DRUG) - (u32)up1;
  ex->bag_nuts_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_NUTS) - (u32)up1;
  ex->bag_ball_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_BALL) - (u32)up1;
  ex->bag_battle_item_offset = (u32)Index_Get_Myitem_Offset(up1, BAG_POKE_BATTLE) - (u32)up1;

  // ボックス関連
  up1 = SaveData_Get(sv, GMDATA_ID_BOXDATA);
  ex->box_data_tray_max = BOX_MAX_TRAY;
  ex->box_data_offset = (u32)BOXDAT_GetPokeDataAddress(up1, 0, 0) - (u32)up1;
  ex->sizeof_pokemon_paso_param = PokemonPasoParamSizeGet();

  // Wi-Fi関連
  up1 = SaveData_Get(sv, GMDATA_ID_SYSTEM_DATA);
  ex->profile_id_offset = (u32)Index_Get_Profile_Offset(up1) - (u32)up1;
  
  OS_TPrintf("外部Index: %08X - %08X\n", ex, (u32)ex + sizeof(EXINDEX));
  OS_TPrintf("zukan_get_offset = %08X\n", &ex->zukan_get_offset);
  OS_TPrintf("game_flag_offset = %08X\n", &ex->game_flag_offset);
  OS_TPrintf("mystatus_name_offset = %08X\n", &ex->mystatus_name_offset);
  OS_TPrintf("pokecount_offset = %08X\n", &ex->pokecount_offset);
  OS_TPrintf("sizeof_mineitem = %08X\n", &ex->sizeof_mineitem);
  OS_TPrintf("box_data_tray_max = %08X\n", &ex->box_data_tray_max);
  OS_TPrintf("profile_id_offset = %08X\n", &ex->profile_id_offset);
  
  // 処理終了
  OS_Terminate();
}

/*  */

#endif	// CREATE_INDEX
