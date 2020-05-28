//============================================================================================
/**
 * @file	eventdata.c
 * @brief	ゾーン毎に読み込むイベントデータの処理
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.17
 */
//============================================================================================

#include "common.h"
#include "mapdefine.h"

#include "fieldsys.h"

#include "zonedata.h"

#include "fieldobj.h"

#include "system/arc_tool.h"

#include "eventdata.h"

#include "encount_dat.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゾーン毎のイベントデータ構造
 *
 * ゾーン毎に生成されて組み込まれるイベントデータバイナリを
 * 解析してこの構造体に値を入れる。
 */
//------------------------------------------------------------------
struct EVENT_DATA{
	u32 bg_count;
	u32 npc_count;
	u32 connect_count;
	u32 posevent_count;
	const BG_TALK_DATA * bg_data;
	const struct _TAG_FIELD_OBJ_H * npc_data;
	const CONNECT_DATA * connect_data;
	const POS_EVENT_DATA * posevent_data;
	u32 buffer[0x800 / sizeof(u32)];
	u32 sp_scr[0x100 / sizeof(u32)];
	ENCOUNT_DATA enc_work;
};


//------------------------------------------------------------------
//------------------------------------------------------------------

static void LoadEventData(EVENT_DATA * eventdata, int zone_id);
static void MakeEventData(EVENT_DATA * event_data);
static void LoadSpecialScriptData(EVENT_DATA * eventdata, int zone_id);
//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	イベントデータ：生成処理
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void EventData_Sys_Create(FIELDSYS_WORK * fsys, int heapID)
{
	EVENT_DATA * eventdata;
	GF_ASSERT(fsys->eventdata == NULL);
	fsys->eventdata = sys_AllocMemory(heapID, sizeof(EVENT_DATA));
}

//------------------------------------------------------------------
/**
 * @brief	イベントデータ：生成処理
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void EventData_Sys_Delete(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->eventdata != NULL);
	sys_FreeMemoryEz(fsys->eventdata);
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゾーンごとのイベントデータ読み込み
 * @param	zone_id		ゾーンIDの指定
 *
 * ゾーンごとのイベントデータバイナリを読み込んでイベントデータ構造体を
 * 生成する
 */
//------------------------------------------------------------------
void EventData_LoadZoneData(FIELDSYS_WORK * fsys, int zone_id)
{
	GF_ASSERT(fsys->eventdata != NULL);
	LoadEventData(fsys->eventdata, zone_id);
	MakeEventData(fsys->eventdata);
	EventData_LoadEncountData(&fsys->eventdata->enc_work, zone_id);
	LoadSpecialScriptData(fsys->eventdata, zone_id);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void LoadEventData(EVENT_DATA * eventdata, int zone_id)
{
	int index;
	index = ZoneData_GetEventID(zone_id);
	GF_ASSERT(ArchiveDataSizeGet(ARC_EVENTDATA, index) < sizeof(eventdata->buffer));
	ArchiveDataLoad(eventdata->buffer, ARC_EVENTDATA, index);
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	フィールドNPCのセット
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void EventData_SetFieldOBJ(FIELDSYS_WORK * fsys)
{
	int num = fsys->eventdata->npc_count;
	GF_ASSERT(fsys->eventdata != NULL);
	if (num != 0) {
		FieldOBJ_AddBin(fsys->fldobjsys, fsys->location->zone_id, num, fsys->eventdata->npc_data);
	}
}

//------------------------------------------------------------------
/**
 * @brief	BG話しかけイベントデータの取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	データ先頭へのポインタ
 */
//------------------------------------------------------------------
const BG_TALK_DATA * EventData_GetNowBgTalkData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->bg_data;
}
//------------------------------------------------------------------
/**
 * @brief	BG話しかけイベントデータ数の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	データ数
 */
//------------------------------------------------------------------
int EventData_GetNowBgTalkDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->bg_count;
}

//------------------------------------------------------------------
/**
 * @brief	マップ接続データ数の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	データ数
 */
//------------------------------------------------------------------
int EventData_GetNowConnectDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->connect_count;
}
//------------------------------------------------------------------
/**
 * @brief	マップ接続データの取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		出入り口ID
 * @retval	NULL以外	指定したデータへのポインタ
 * @retval	NULL		データが存在しない
 */
//------------------------------------------------------------------
const CONNECT_DATA * EventData_GetNowConnectDataByID(const FIELDSYS_WORK * fsys, int door_id)
{
	if (door_id >= fsys->eventdata->connect_count) {
		OS_Printf("door_id error\n");
		return NULL;
	}
	return &fsys->eventdata->connect_data[door_id];
}
//------------------------------------------------------------------
/**
 * @brief	マップ接続データIDの取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	x		探すX位置（グリッド単位）
 * @param	z		探すZ位置（グリッド単位）
 * @return	int	出入口ID
 * @return	-1	出入口が存在しなかった場合
 */
//------------------------------------------------------------------
int EventData_SearchNowConnectIDByXZ(const FIELDSYS_WORK * fsys, int x, int z)
{
	int door_id;

	for (door_id = 0; door_id < fsys->eventdata->connect_count; door_id ++) {
		if (fsys->eventdata->connect_data[door_id].x == x &&
			fsys->eventdata->connect_data[door_id].z == z) {
			return door_id;
		}
	}
	return -1;
}

//------------------------------------------------------------------
/**
 * @brief	POS発動イベントのデータ数取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	POS発動イベントのデータ数
 */
//------------------------------------------------------------------
int EventData_GetNowPosEventDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->posevent_count;
}
//------------------------------------------------------------------
/**
 * @brief	POS発動イベントのデータ取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	データ先頭へのポインタ
 */
//------------------------------------------------------------------
const POS_EVENT_DATA * EventData_GetNowPosEventData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->posevent_data;
}

//------------------------------------------------------------------
/**
 * @brief	npc_count取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	"npc_count"
 */
//------------------------------------------------------------------
u32 EventData_GetNpcCount(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->npc_count;
}

//------------------------------------------------------------------
/**
 * @brief	npc_data取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	"npc_data"
 */
//------------------------------------------------------------------
const FIELD_OBJ_H* EventData_GetNpcData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->npc_data;
}

//------------------------------------------------------------------
/**
 * @brief	npc_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	gx		グリッドX
 * @param	gz		グリッドZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataPosChange(FIELDSYS_WORK * fsys, int id, u16 gx, u16 gz )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//同じIDを検索
			p[i].gx = gx;
			p[i].gz = gz;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "同じIDが見つかりませんでした！" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	npc_dataの方向を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	dir		方向
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir );
BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//同じIDを検索
			p[i].dir = dir;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "同じIDが見つかりませんでした！" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	npc_dataの動作コードを書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	mv		動作コード
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv );
BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//同じIDを検索
			p[i].move_code =mv;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "同じIDが見つかりませんでした！" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	connect_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	x		セットするX
 * @param	z		セットするZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );
BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z )
{
	CONNECT_DATA* p	= (CONNECT_DATA*)fsys->eventdata->connect_data;
	//OS_Printf( "変更前 x = %d\n", p[id].x );
	//OS_Printf( "変更前 z = %d\n", p[id].z );
	p[id].x			= x;
	p[id].z			= z;
	//OS_Printf( "変更後 x = %d\n", p[id].x );
	//OS_Printf( "変更後 z = %d\n", p[id].z );
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	connect_dataの接続先ゾーンIDを書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	zone	セットするゾーン
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone );
BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone)
{
	CONNECT_DATA* p	= (CONNECT_DATA*)fsys->eventdata->connect_data;
	
	p[id].link_zone_id	= zone;
	return TRUE;
}
//------------------------------------------------------------------
/**
 * @brief	bg_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	x		セットするX
 * @param	z		セットするZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );
BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z )
{
	BG_TALK_DATA* p = (BG_TALK_DATA*)EventData_GetNowBgTalkData( fsys );

	//OS_Printf( "変更前 p = %d\n", p );
	//OS_Printf( "変更前 x = %d\n", p->gx );
	//OS_Printf( "変更前 x = %d\n", p->gz );
	(p)+=id;
	p->gx = x;
	p->gz = z;
	//OS_Printf( "変更後 p = %d\n", p );
	//OS_Printf( "変更後 x = %d\n", p->gx );
	//OS_Printf( "変更後 x = %d\n", p->gz );
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	イベントデータ生成処理
 * @param	event_data	EVENT_DATA構造体へのポインタ
 *
 * EVENT_DATA::bufferに読み込まれているバイナリデータを
 * 解析してEVENT_DATA構造体のほかのメンバーを生成する。
 */
//------------------------------------------------------------------
static void MakeEventData(EVENT_DATA * event_data)
{
	const u8 * buffer = (const u8 *)event_data->buffer;

	//BG話しかけイベントデータ読み込み
	event_data->bg_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->bg_count != 0) {
		event_data->bg_data = (const BG_TALK_DATA *)buffer;
	} else {
		event_data->bg_data = NULL;
	}
	buffer += sizeof(BG_TALK_DATA) * event_data->bg_count;

	//NPC配置データ読み込み
	event_data->npc_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->npc_count != 0) {
		event_data->npc_data = (const struct _TAG_FIELD_OBJ_H *)buffer;
	} else {
		event_data->npc_data = NULL;
	}
	buffer += sizeof(struct _TAG_FIELD_OBJ_H) * event_data->npc_count;

	//マップ接続データ読み込み
	event_data->connect_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->connect_count != 0) {
		event_data->connect_data = (const CONNECT_DATA *)buffer;
	} else {
		event_data->connect_data = NULL;
	}
	buffer += sizeof(CONNECT_DATA) * event_data->connect_count;

	//POS発動イベントデータ読み込み
	event_data->posevent_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->posevent_count != 0) {
		event_data->posevent_data = (const POS_EVENT_DATA *)buffer;
	} else {
		event_data->posevent_data = NULL;
	}
	buffer += sizeof(POS_EVENT_DATA) * event_data->posevent_count;

}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゾーン毎のエンカウントデータの読み込み
 * @param	zone_id		ゾーンIDの指定
 * @param	event_data	EVENT_DATA構造体へのポインタ
 */
//------------------------------------------------------------------
void EventData_LoadEncountData(ENCOUNT_DATA *enc_data, int zone_id)
{
	int arc_version;
	memset(enc_data, 0, sizeof(ENCOUNT_DATA));
	if (ZoneData_GetEncountFlag(zone_id)) {
		if (PM_VERSION == VERSION_DIAMOND){
			arc_version = ARC_D_ENCOUNT;
		}else{
			arc_version = ARC_P_ENCOUNT;
		}
		ArchiveDataLoad(enc_data, arc_version,
				ZoneData_GetEncountArchiveID(zone_id));
	}
}

//------------------------------------------------------------------
/**
 * @brief	エンカウントデータの取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	ENCOUNT_DATA * エンカウントデータの先頭アドレス
 *
 * 
 * 
 */
//------------------------------------------------------------------
const ENCOUNT_DATA * EventData_GetEncountData(const FIELDSYS_WORK * fsys)
{
	return &fsys->eventdata->enc_work;
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゾーン毎の特殊スクリプトデータの読み込み
 * @param	zone_id		ゾーンIDの指定
 * @param	event_data	EVENT_DATA構造体へのポインタ
 */
//------------------------------------------------------------------
static void LoadSpecialScriptData(EVENT_DATA * eventdata, int zone_id)
{
	int index;
	index = ZoneData_GetSpScriptArchiveID(zone_id);
	MI_CpuClearFast(eventdata->sp_scr, sizeof(eventdata->sp_scr));
	GF_ASSERT(ArchiveDataSizeGet(ARC_SCRIPT, index) < sizeof(eventdata->sp_scr));
	ArchiveDataLoad(eventdata->sp_scr, ARC_SCRIPT, index);
}

//------------------------------------------------------------------
/**
 * @brief	特殊スクリプトデータの取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	void * 特殊スクリプトデータの先頭アドレス
 *
 */
//------------------------------------------------------------------
void * EventData_GetSpecialScript(const FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->eventdata != NULL);
	return &fsys->eventdata->sp_scr;
}


//------------------------------------------------------------------
/**
 * 地下に潜ることが出来る座標かどうかをチェック
 *
 * @param   fsys		フィールド制御ワークへのポインタ
 * @param   gx			チェックするＸ座標
 * @param   gz			チェックするＺ座標
 *
 * @retval  BOOL		"TRUE=潜ることができる FALSE=できない"
 */
//------------------------------------------------------------------
BOOL EventData_CheckIntoUGPos( const FIELDSYS_WORK* fsys, u16 gx, u16 gz )
{
	const EVENT_DATA* eventdata = fsys->eventdata;
	u32 i;

	for(i=0; i<eventdata->npc_count; i++)
	{
		if( (eventdata->npc_data[i].gx == gx)
		&&	(eventdata->npc_data[i].gz == gz)
		){
			return FALSE;
		}
	}
	return TRUE;
}

