//============================================================================================
/**
 * @file	zonedata.c
 * @brief	ゾーン固有の管理データ
 * @author	tamada
 * @date	2005.08.05
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "zonedata.h"

#include "mapdefine.h"
#include "maptype.h"


#include "../fielddata/script/scr_seq.naix"

#include "../msgdata/msg.naix"

#include "../data/sound/sound_data.sadl"

#include "../fielddata/eventdata/zone_event.naix"

#include "../fielddata/encountdata/enc_data.naix"

#include "msgdata/msg_place_name.h"

#include "weather_sys.h"
#include "mapdata_weather_def.h"

#include "battle/attr_def.h"

#include "../fielddata/mm_list/mmlist_def.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゾーン毎に持つデータの構成
 */
//------------------------------------------------------------------
typedef struct{
	u8 area_id;							///<AREA_IDの指定
	u8 movemodel_id;					///<動作モデルの指定
	u16 matrix_id;						///<マップマトリックスの指定
	u16 script_id;						///<スクリプトファイルのアーカイブID
	u16 sp_script_id;					///<特殊スクリプトファイルのアーカイブID
	u16 msg_id;							///<メッセージファイルのアーカイブID
	u16 bgm_day_id;						///<BGM指定（昼）のID
	u16 bgm_night_id;					///<BGM指定（夜）のID
	u16 enc_data_id;					///<エンカウント指定
	u16 event_data_id;					///<イベントデータファイルのアーカイブID
	u16 placename_id;					///<地名メッセージのＩＤ
	u8 weather_id;						///<天候指定のID
	u8 camera_id;						///<カメラ指定のID
	u8 maptype;							///<マップタイプの指定(MAPTYPE定義参照）
	u8 battle_bg_type:4;				///<戦闘背景の指定
	u8 bicycle_flag:1;					///<自転車に乗れるかどうか
	u8 dash_flag:1;						///<ダッシュできるかどうか
	u8 escape_flag:1;					///<あなぬけできるかどうか
	u8 fly_flag:1;
}ZONE_DATA;
//------------------------------------------------------------------
//------------------------------------------------------------------

enum {
	sp_scr_dummy = NARC_scr_seq_sp_dummy_bin,
	scr_dummy = NARC_scr_seq_dummy_bin,
	//sp_scr_dummy = NARC_scr_seq_sp_c01_bin,
	//scr_dummy = NARC_scr_seq_c01_bin,
	msg_dummy = NARC_msg_c01_dat,
	enc_dummy = 0xffff,
};

#include "../fielddata/maptable/maptable.dat"

static int ZoneData_GetMapType(int zone_id);
//===========================================================================
//===========================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int ZoneData_CheckRange(int zone_id)
{
	if (zone_id >= NELEMS(ZoneData)) {
		GF_ASSERT_MSG(0, "%d/%d:zone_id error\n",zone_id,NELEMS(ZoneData)-1);
		return ZONE_ID_C01;
	}
	return zone_id;
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	エリアIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u16			エリア指定
 */
//------------------------------------------------------------------
const u16 ZoneData_GetAreaID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].area_id;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
const u16 ZoneData_GetMoveModelID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].movemodel_id;
}

//------------------------------------------------------------------
/**
 * @brief	マップマトリックスIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u16			マップマトリックス指定
 */
//------------------------------------------------------------------
const u16 ZoneData_GetMatrixID(int zone_id)
{
	u16 mtx_id;
	zone_id = ZoneData_CheckRange(zone_id);
	mtx_id = ZoneData[zone_id].matrix_id;
	if (mtx_id == MATRIX_ID_DUN0514){
		if (CasetteVersion == VERSION_PEARL) {
			mtx_id = MATRIX_ID_DUN0515;
		}
	}
	return mtx_id;
}
//------------------------------------------------------------------
/**
 * @brief	メッセージアーカイブIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			メッセージアーカイブID
 */
//------------------------------------------------------------------
u32 ZoneData_GetMsgArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].msg_id;
}

//------------------------------------------------------------------
/**
 * @brief	スクリプトアーカイブIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			スクリプトアーカイブID
 */
//------------------------------------------------------------------
u32 ZoneData_GetScriptArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].script_id;
}
//------------------------------------------------------------------
/**
 * @brief	スクリプトアーカイブIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			スクリプトアーカイブID
 */
//------------------------------------------------------------------
u32 ZoneData_GetSpScriptArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].sp_script_id;
}


//------------------------------------------------------------------
/**
 * @brief	BGM指定の取得
 * @param	zone_id		ゾーン指定
 * @return	u16			BGM指定
 */
//------------------------------------------------------------------
u16 ZoneData_GetDayBGMID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bgm_day_id;
}

//------------------------------------------------------------------
/**
 * @brief	BGM指定の取得
 * @param	zone_id		ゾーン指定
 * @return	u16			BGM指定
 */
//------------------------------------------------------------------
u16 ZoneData_GetNightBGMID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bgm_night_id;
}

//------------------------------------------------------------------
/**
 * @brief	エンカウントフラグの取得
 * @param	zone_id		ゾーン指定
 * @return	TRUE：エンカウントデータあり、FALSE:エンカウントデータなし
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEncountFlag (int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return (ZoneData[zone_id].enc_data_id != enc_dummy);
}

//------------------------------------------------------------------
/**
 * @brief	エンカウントアーカイブIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32	アーカイブID指定
 */
//------------------------------------------------------------------
u32 ZoneData_GetEncountArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].enc_data_id;
}

//------------------------------------------------------------------
/**
 * @brief	イベントデータアーカイブIDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			イベントデータアーカイブID
 */
//------------------------------------------------------------------
u32 ZoneData_GetEventID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].event_data_id;
}

//------------------------------------------------------------------
/**
 * @brief	地名メッセージ指定IDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			地名メッセージ指定ＩＤ
 */
//------------------------------------------------------------------
u32 ZoneData_GetPlaceNameID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].placename_id;
}

//------------------------------------------------------------------
/**
 * @brief	天候指定IDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			天候指定のID
 */
//------------------------------------------------------------------
u32 ZoneData_GetWeatherID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].weather_id;
}

//------------------------------------------------------------------
/**
 * @brief	カメラ指定IDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			カメラ指定のID
 */
//------------------------------------------------------------------
u32 ZoneData_GetCameraID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].camera_id;
}

//------------------------------------------------------------------
/**
 * @brief	カメラ指定IDの取得
 * @param	zone_id		ゾーン指定
 * @return	u32			戦闘背景指定のID
 */
//------------------------------------------------------------------
u32 ZoneData_GetBattleBGID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].battle_bg_type;
}
//------------------------------------------------------------------
/**
 * @brief	あなぬけができるかどうかのフラグ取得
 * @param	zone_id		ゾーン指定
 * @return	BOOL		できるかどうか
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableEscapeFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].escape_flag;
}
//------------------------------------------------------------------
/**
 * @brief	そらをとぶ・テレポートができるかどうかのフラグ取得
 * @param	zone_id		ゾーン指定
 * @return	BOOL		できるかどうか
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableFlyFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].fly_flag;
}

//------------------------------------------------------------------
/**
 * @brief	ダッシュができるかどうかのフラグ取得
 * @param	zone_id		ゾーン指定
 * @return	BOOL		できるかどうか
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableDashFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].dash_flag;
}
//------------------------------------------------------------------
/**
 * @brief	じてんしゃをつかえるかどうかのフラグ取得
 * @param	zone_id		ゾーン指定
 * @return	BOOL		できるかどうか
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableBicycleFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bicycle_flag;
}
//------------------------------------------------------------------
/**
 * @brief	マップタイプの取得
 * @param	zone_id		ゾーン指定
 * @return	int			マップタイプ指定ID
 *
 * マップタイプを使用した判定は分散させると後々のタイプ追加などが
 * 大変になるのでこの関数は外部公開していない
 */
//------------------------------------------------------------------
static int ZoneData_GetMapType(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].maptype;
}
//============================================================================================
//
//
//	ゾーンIDによる各種判定ロジック
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	テレポートを使えるかどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、テレポートを使える
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableTeleportFlag(int zone_id)
{
	if (ZoneData_GetEnableFlyFlag(zone_id) == FALSE) {
		return FALSE;
	}
	return (ZoneData_GetMapType(zone_id) != MAPTYPE_TOWN);
}

//------------------------------------------------------------------
/**
 * @brief	フィールドかどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、フィールド（部屋でもダンジョンでもない）
 */
//------------------------------------------------------------------
BOOL ZoneData_IsSinouField(int zone_id)
{
	return (ZoneData_GetMatrixID(zone_id) == MATRIX_ID_FIELD);
}

//------------------------------------------------------------------
/**
 * @brief	ポケセンかどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、ポケセン
 */
//------------------------------------------------------------------
BOOL ZoneData_IsPokecen(int zone_id)
{
	return (ZoneData_GetMapType(zone_id) == MAPTYPE_POKECEN);
}

//------------------------------------------------------------------
/**
 * @brief	ダンジョンかどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、ダンジョン
 */
//------------------------------------------------------------------
BOOL ZoneData_IsDungeon(int zone_id)
{
	return (ZoneData_GetMapType(zone_id) == MAPTYPE_CAVE);
}

//------------------------------------------------------------------
/**
 * @brief	屋内かどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、屋内
 */
//------------------------------------------------------------------
BOOL ZoneData_IsRoom(int zone_id)
{
	return ( (ZoneData_GetMapType(zone_id) == MAPTYPE_ROOM) ||
			 (ZoneData_GetMapType(zone_id) == MAPTYPE_POKECEN) );
}

//------------------------------------------------------------------
/**
 * @brief	屋外かどうかのチェック
 * @param	zone_id		ゾーン指定
 * @retval	BOOL	TRUEのとき、屋外
 */
//------------------------------------------------------------------
BOOL ZoneData_IsOutDoor(int zone_id)
{
	return ( (ZoneData_GetMapType(zone_id) == MAPTYPE_TOWN) ||
			 (ZoneData_GetMapType(zone_id) == MAPTYPE_ROAD) );
}

//------------------------------------------------------------------
/**
 * @brief	通信を利用する可能性のあるゾーンかどうかチェック
 *
 * @param   zone_id		ゾーン指定
 *
 * @retval  BOOL		TRUEのとき、通信を利用するかも
 */
//------------------------------------------------------------------
BOOL ZoneData_IsCommPlayableZone(int zone_id)
{
	if( ZoneData_IsPokecen(zone_id) )
	{
		return TRUE;
	}


	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	ユニオンルームかどうかのチェック
 * @param   zone_id		ゾーン指定
 * @return	BOOL	TRUEのとき、ユニオンルーム
 */
//------------------------------------------------------------------
BOOL ZoneData_IsUnionRoom(const int zone_id)
{
	return (zone_id == ZONE_ID_UNION);
}

//------------------------------------------------------------------
/**
 * @brief	特殊釣りエンカウントするゾーンかどうかチェック
 *
 * @param   zone_id		ゾーン指定
 *
 * @retval  BOOL		TRUEのとき、特殊釣りエンカウントゾーン
 */
//------------------------------------------------------------------
BOOL ZoneData_IsSpFishingZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D05R0113);
}

//------------------------------------------------------------------
/**
 * @brief	裏山エンカウントするゾーンかどうかチェック
 *
 * @param   zone_id		ゾーン指定
 *
 * @retval  BOOL		TRUEのとき、裏山エンカウントゾーン
 */
//------------------------------------------------------------------
BOOL ZoneData_IsHillBackZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D23R0101);
}

//------------------------------------------------------------------
/**
 * @brief	自然公園かどうかのチェック
 * @param   zone_id		ゾーン指定
 * @retval	BOOL		TRUEのとき、自然公園
 */
//------------------------------------------------------------------
BOOL ZoneData_IsNaturalPark(const int zone_id)
{
	return (zone_id == ZONE_ID_D11R0101);
}

//------------------------------------------------------------------
/**
 * @brief	てんかいのふえが使えるゾーンかどうかチェック
 *
 * @param   zone_id		ゾーン指定
 *
 * @retval  BOOL		TRUEのとき、使えるゾーン
 */
//------------------------------------------------------------------
BOOL ZoneData_IsUseTenkainofueZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D05R0114);
}

//------------------------------------------------------------------
/**
 * @brief	ポケセン２Fにいるかどうかのチェック
 * @param   zone_id		ゾーン指定
 */
//------------------------------------------------------------------
BOOL ZoneData_IsPokecen2F(const int zone_id)
{
	static const u16 pc2f[] = {
		ZONE_ID_T02PC0102,
		ZONE_ID_T03PC0102,
		ZONE_ID_T04PC0102,
		ZONE_ID_T05PC0102,
		ZONE_ID_T06PC0102,
		ZONE_ID_T07PC0102,
		ZONE_ID_C01PC0102,
		ZONE_ID_C02PC0102,
		ZONE_ID_C03PC0102,
		ZONE_ID_C03PC0102,
		ZONE_ID_C04PC0102,
		ZONE_ID_C05PC0102,
		ZONE_ID_C06PC0102,
		ZONE_ID_C07PC0102,
		ZONE_ID_C08PC0102,
		ZONE_ID_C09PC0102,
		ZONE_ID_C10PC0102,
		ZONE_ID_C11PC0102,
	};

	int index;
	for (index = 0; index < NELEMS(pc2f); index++ ) {
		if (zone_id == pc2f[index]) {
			return TRUE;
		}
	}
	return FALSE;

}

//============================================================================================
//
//
//
//	マップごとの個別データ取得
//
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	場所進化の情報を返す
 * @param	zone_id		ゾーン指定ID
 * @retval	SHINKA_NONE
 * @retval	SHINKA_PLACE_TENGANZAN
 * @retval	SHINKA_PLACE_KOKE
 * @retval	SHINKA_PLACE_ICE
 */
//-----------------------------------------------------------------------------
int ZoneData_GetShinkaPlaceID(int zone_id)
{
	static const u16 tbl[] = {
		ZONE_ID_R217,		SHINKA_PLACE_ICE,
		ZONE_ID_D03R0101,	SHINKA_PLACE_KOKE,
		ZONE_ID_D05R0101,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0102,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0103,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0104,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0105,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0106,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0107,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0108,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0109,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0110,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0111,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0112,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0113,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0114,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0115,	SHINKA_PLACE_TENGANZAN,
	};
	int i;
	for (i = 0; i < NELEMS(tbl); i += 2) {
		if (tbl[i] == zone_id) {
			return tbl[i + 1];
		}
	}
	return SHINKA_NONE;
}

