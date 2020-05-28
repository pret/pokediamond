//============================================================================================
/**
 * @file	map_jump.c
 * @brief	マップジャンプ制御
 * @date	2006.02.07
 * @author	Nozomu Saito
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field/location.h"
#include "ev_mapchange.h"
#include "field_3d_anime_ev.h"
#include "system/snd_tool.h"		//これがないと、fld_bgm.hでエラーが出る
#include "system/wipe.h"
#include "fld_bgm.h"

#include "map_jump_def.h"
#include "map_jump.h"

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_attr.h"		//for attribute

#include "fieldmap_work.h"	//for hblamk wipe
#include "field_hblank.h"	//for hblank wipe

#include "zonedata.h"

#include "fld_flg_init.h"

static BOOL MJUMPEVT_Wipe(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapChangeParent(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapFadeOutMat(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDoor(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutEsca(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutStairs(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDunIn(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeOutDunOut(GMEVENT_CONTROL * event);

static BOOL MJUMPEVT_MapFadeInDoor(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInBlack(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInEsca(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInStairs(GMEVENT_CONTROL * event);
static BOOL MJUMPEVT_MapFadeInDunOut(GMEVENT_CONTROL * event);

static void SetEscalatorIOPos(FIELDSYS_WORK *fsys);
static void SetStairsIOPos(FIELDSYS_WORK *fsys);
//フェードアウトエフェクトリスト
		//階段
static const MAP_JUMP_FUNC MapJumpFadeOutFuncTbl[MAP_JUMP_TYPE_MAX] = {
	MJUMPEVT_MapFadeOutMat,		//室内→外
	MJUMPEVT_MapFadeOutDoor,	//ドア（外）→室内
	MJUMPEVT_MapFadeOutEsca,	//エスカレーター
	MJUMPEVT_MapFadeOutStairs,	//階段
	MJUMPEVT_MapFadeOutDunIn,	//ダンジョン入る
	MJUMPEVT_MapFadeOutDunOut,	//ダンジョンホワイトアウト
	MJUMPEVT_MapFadeOutMat,		//外マット→屋内
};

//フェードインエフェクトリスト
		//階段
static const MAP_JUMP_FUNC MapJumpFadeInFuncTbl[MAP_JUMP_TYPE_MAX] = {
	MJUMPEVT_MapFadeInDoor,		//室内→外
	MJUMPEVT_MapFadeInBlack,	//ドア（外）→室内
	MJUMPEVT_MapFadeInEsca,		//エスカレーター
	MJUMPEVT_MapFadeInStairs,	//階段
	MJUMPEVT_MapFadeInBlack,	//ダンジョン入る
	MJUMPEVT_MapFadeInDunOut,	//ダンジョンホワイトイン
	MJUMPEVT_MapFadeInBlack,	//外マット→屋内
};

//マップジャンプ別表示位置補正関数群
static const MAP_JUMP_POS_SET MapJumpPosSetFuncTbl[MAP_JUMP_TYPE_MAX] = {
	NULL,						//室内→外
	NULL,						//ドア（外）→室内
	SetEscalatorIOPos,			//エスカレーター
	SetStairsIOPos,				//階段
	NULL,						//ダンジョン入る
	NULL,						//ダンジョン出る
	NULL,						//外マット→屋内
};

typedef struct {
	int seq;							///<シーケンス保持ワーク
	int call_seq;						///<コール先シーケンスワーク
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
	///FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
	void	*JumpEffectWork;
	int JumpType;
}EVENT_MAPCHG_WORK;


typedef struct WIPE_PARAM_tag
{
	int Seq;
	int Pattern;
	int Main;
	int Sub;
	u16 Col;
	int Div;
	int Sync;
	int Heap;
}WIPE_PARAM;

//-----------------------------------------------------------------------------
/**
 * @brief	ワイプイベントコール(ラスタとかを使うワイプのとき)
 * 内部でHブランク割り込みを停止させ、ワイプ終了で、ブランク処理を再スタートさせます
 * @param	event		イベントポインタ
 * @param	inPattern	切り替えパターン番号
 * @param	inMain		ワイプ　メイン画面ワイプパターン
 * @param	inSub		ワイプ　サブ画面ワイプパターン
 * @param	inCol		ワイプの色	
 * @param	inDiv		各ワイプ処理の分割数	(1.2.3.4.....)
 * @param	inSync		各ワイプの処理を分割した１片のシンク数	(1.2.3.4.....)
 * @param	inHeap		使用するヒープ
 *
 * @return none
 */
//-----------------------------------------------------------------------------
void MJUMP_RequestWipe(	GMEVENT_CONTROL * event,
						int inPattern, int inMain,
						int inSub, u16 inCol,
						int inDiv, int inSync,
						int inHeap)
{
	WIPE_PARAM *wp = sys_AllocMemory(inHeap, sizeof(WIPE_PARAM));
	wp->Pattern = inPattern;
	wp->Main = inMain;
	wp->Sub = inSub;
	wp->Col = inCol;
	wp->Div = inDiv;
	wp->Sync = inSync;
	wp->Heap = inHeap;
	wp->Seq = 0;

	FieldEvent_Call(event, MJUMPEVT_Wipe, wp);
}

//-----------------------------------------------------------------------------
/**
 * @brief	ワイプイベント
 * @param	event	イベントポインタ
 * 
 * @return  BOOL	TRUE:終了　FALSE:継続
 */
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_Wipe(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	WIPE_PARAM *wp = FieldEvent_GetSpecialWork(event);
	switch (wp->Seq) {
	case 0:
		FLDHBLANK_SYS_Stop( fsys->fldmap->hblanksys );
		//ワイプスタート
		WIPE_SYS_Start(	wp->Pattern, wp->Main, wp->Sub,
				wp->Col,wp->Div,wp->Sync,wp->Heap );
		wp->Seq++;
		break;
	case 1:
		if ( WIPE_SYS_EndCheck() ){
			FLDHBLANK_SYS_Start(fsys->fldmap->hblanksys);
			sys_FreeMemoryEz(wp);
			return TRUE;
		}
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントセット(ドアアニメつき)
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	inX			遷移先マップでのXグリッド位置
 * @param	inZ			遷移先マップでのYグリッド位置
 * @param	inDir		遷移先マップでの初期方向
 * @param	inType		ジャンプタイプ
 *
 * 遷移先マップのどこに出現するかの情報は次のマップを読み込むまではわからないはずなので
 * 本当は座標指定は無駄かもしれないけど、念のため。またエリアとゾーンの関係は再考されるので
 * エリア指定もいらなくなる可能性がある。
 */
//-----------------------------------------------------------------------------
void MJUMP_ChangeMap(FIELDSYS_WORK * fsys, const int zone, const int door_id,
						const int inX, const int inZ, const int inDir, const int inType )
{
	EVENT_MAPCHG_WORK * emw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	emw->seq = 0;
	emw->call_seq = 0;
	//ロケーションデータ作成
	SetLocation(&emw->next, zone, door_id, inX, inZ, inDir);

	//ジャンプタイプをセット
	emw->JumpType = inType;

	//マップジャンプイベントを作成
	FieldEvent_Set(fsys, MJUMPEVT_MapChangeParent, emw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントセット(マップタイプを参照する)
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	inX			遷移先マップでのXグリッド位置
 * @param	inZ			遷移先マップでのYグリッド位置
 * @param	inDir			遷移先マップでの初期方向
 *
 * 遷移先マップのどこに出現するかの情報は次のマップを読み込むまではわからないはずなので
 * 本当は座標指定は無駄かもしれないけど、念のため。またエリアとゾーンの関係は再考されるので
 * エリア指定もいらなくなる可能性がある。
 */
//-----------------------------------------------------------------------------
void MJUMP_ChangeMapByLocation(FIELDSYS_WORK * fsys, const int zone, const int door_id,
						const int inX, const int inZ, const int inDir)
{
	int now_zone;
	int type;
	EVENT_MAPCHG_WORK * emw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	
	emw->seq = 0;
	emw->call_seq = 0;
	//ロケーションデータ作成
	SetLocation(&emw->next, zone, door_id, inX, inZ, inDir);

	//現在マップ種類を調べる
	now_zone = fsys->location->zone_id;
	type = 0;
	if (ZoneData_IsDungeon(now_zone)){		//現在ダンジョン
		//飛び先を調べる
		if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_MATIN;			//ダンジョン間移動(部屋に入るのと同じ)
		}else if (ZoneData_IsOutDoor(zone)){
			type = M_JUMP_DUNOUT;			//ダンジョン外へ
		}else if (ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//部屋の中へ
		}else{
			GF_ASSERT(0);
		}
	}else if (ZoneData_IsOutDoor(now_zone)){//現在屋外
		//飛び先を調べる
		if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_DUNIN;			//ダンジョンの中へ
		}else if (ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//部屋の中へ
		}else{
			GF_ASSERT(0);
		}
	}else if (ZoneData_IsRoom(now_zone)){	//現在室内
		//飛び先を調べる
		if (ZoneData_IsOutDoor(zone)){
			type = M_JUMP_MATOUT;			//屋外へ
		}else if(ZoneData_IsRoom(zone)){
			type = M_JUMP_MATIN;			//部屋内の移動（部屋に入るのと同じ）
		}else if (ZoneData_IsDungeon(zone)){
			type = M_JUMP_MATOUT;			//ダンジョンへ（屋外へでるのと同じ)
		}else{
			GF_ASSERT(0);
		}
	}else{
		GF_ASSERT(0);
	}

	//ジャンプタイプをセット
	emw->JumpType = type;

	//マップジャンプイベントを作成
	FieldEvent_Set(fsys, MJUMPEVT_MapChangeParent, emw);
}

//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapChangeParent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &emw->next;

	switch (emw->seq) {
	case 0:		//ジャンプタイプ別にフェードアウトのイベントをコール
		emw->call_seq = 0;

		//フィールドBGMフェードアウト
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );

		FieldEvent_Call(event, MapJumpFadeOutFuncTbl[emw->JumpType], emw);
		(emw->seq) ++;
		break;
	case 1:	//フィールドプロセスを終了
		EventCmd_FinishFieldMap(event);
		(emw->seq) ++;
		break;
	case 2:	//実際にデータを新マップに書き換える
		EventCmd_MapChangeByLocation(event, &emw->next);
		(emw->seq) ++;
		break;
	case 3:	//フィールドプロセス開始
#if 0
		//移動ポケモン隣接移動
		MP_MovePokemonNeighboring(EncDataSave_GetSaveDataPtr(fsys->savedata));
#endif
		EventCmd_StartFieldMap(event);
		(emw->seq) ++;
		break;
	case 4:
		//ジャンプタイプ別に、自機の初期表示座標にオフセットをつける
		if (MapJumpPosSetFuncTbl[emw->JumpType] != NULL){
			MapJumpPosSetFuncTbl[emw->JumpType](fsys);
		}
		(emw->seq) ++;
		break;
	case 5:	//ジャンプタイプ別にフェードインのイベントをコール
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生

		//地名表示リクエスト
		PlaceNameRequestByFsys(fsys);

		emw->call_seq = 0;
		FieldEvent_Call(event, MapJumpFadeInFuncTbl[emw->JumpType], emw);
		(emw->seq) ++;
		break;
	case 6:	//終了処理
		sys_FreeMemoryEz(emw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	0:マットフェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutMat(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);

	switch (emw->call_seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
/**
		//"マップ遷移専用"フェードアウト → BGM再生
		{
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
*/		
		EventCmd_FieldFadeOut(event);
		(emw->call_seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
// @brief	1:ドアフェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDoor(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//ドアアニメワーク確保
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq) ++;
		break;
	case 1:	//ドアアニメ
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventDoorInAnime(fsys, anime_work) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//ドアアニメワーク解放
			(emw->call_seq) ++;
		}
		break;		
	case 2:
/**		
		//"マップ遷移専用"フェードアウト → BGM再生
		{
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
*/		
		EventCmd_FieldFadeOut(event);
		(emw->call_seq) ++;
		break;
	case 3:		//終了処理
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	2:エスカレーターフェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutEsca(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//アニメワーク確保
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq)++;
		break;
	case 1:	//エスカレーターアニメ　乗る
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventEscalatorInAnime(fsys, anime_work,Player_DirGet( fsys->player )) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//アニメワーク解放
			(emw->call_seq)++;
		}
		break;		
	case 2:		//終了処理	
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	3:階段フェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutStairs(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR fop;
	switch (emw->call_seq) {
	case 0:	//自機移動
		{
			int dir = Player_DirGet( fsys->player );
			fop = Player_FieldOBJGet( fsys->player );
		
			if (dir == DIR_LEFT){	//左向き
				FieldOBJ_AcmdSet(fop,AC_WALK_L_16F);
			}else if (dir == DIR_RIGHT){	//右向き
				FieldOBJ_AcmdSet(fop,AC_WALK_R_16F);
			}else{
				GF_ASSERT(0&&"自機の向きが不正");
			}
		}
		(emw->call_seq) ++;
		break;
	case 1:
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了	
			(emw->call_seq) ++;
		}
		break;
	case 2:
		//入る音
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		//フェードアウト開始
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
		
		(emw->call_seq) ++;
		break;
	case 3:	
		if (WIPE_SYS_EndCheck()) {
/**			
			//"マップ遷移専用"フェードアウト → BGM再生
			{
				LOCATION_WORK* location = &emw->next;
				Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
			}
			(emw->call_seq) ++;
*/			
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	4:ダンジョン入るフェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDunIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeOutHole, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	5:ダンジョン出るフェードアウトマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeOutDunOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeOutWhite, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
	}
/**	
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	switch (emw->call_seq) {
	case 0:
		//ズーム初期化
		//カメラズーム
		(emw->call_seq) ++;
		break;
	case 1:	//カメラズーム待ち
		if(1){
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			//主人公消す
			FieldOBJ_StatusBitSet_Vanish( fop, TRUE );
			//入る音
			Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
			//ワイプスタート	ホワイトアウト
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
			(emw->call_seq) ++;
		}
		break;
	case 2:	//ワイプ終了待ち
		if ( WIPE_SYS_EndCheck() ){
			//"マップ遷移専用"フェードアウト → BGM再生
			LOCATION_WORK* location = &emw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
			(emw->call_seq) ++;
		}
		break;
	case 3:		//終了処理
		return TRUE;
	}
*/	
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	0:外に出たときフェードインマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInDoor(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:
		{
			u8 attr;
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			attr = GetAttributeLSB( fsys,
									Player_NowGPosXGet( fsys->player ),
									Player_NowGPosZGet( fsys->player ) );
			if (MATR_IsDoor(attr)){
				//自機を非表示
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				(emw->call_seq) = 1;
			}else{
				FMJ_WORK_PTR work;
				work = MapJump_AllocWork();
				FieldEvent_Call(event, MapJump_EventFadeInShutSlide, work);
				(emw->call_seq) = 3;
			}
		}
		break;
	case 1:
		//ドアアニメワーク確保
		emw->JumpEffectWork = (FLD_3D_ANIME_WORK_PTR)Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq) ++;
		break;
	case 2:			//ドアアニメ
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventDoorOutAnime(fsys, anime_work) ){
			Fld3DAnm_FreeEvent3DAnimeWork(anime_work);	//ドアアニメワーク解放
			{
				FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
				//自機を表示
				FieldOBJ_StatusBitSet_Vanish( player, FALSE );
			}
			return TRUE;		//終了
		}
		break;
	case 3:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	1,4:室内、ダンジョン入ったときブラックインマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInBlack(GMEVENT_CONTROL * event)
{
	FIELD_OBJ_PTR fop;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:
		{
			//室内にドアがあったりするので特殊処理する
			u8 attr;
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			attr = GetAttributeLSB( fsys,
									Player_NowGPosXGet( fsys->player ),
									Player_NowGPosZGet( fsys->player ) );
			if (MATR_IsDoor(attr)){	//ドアがあったら
				//自機を非表示
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				emw->call_seq = 1;		//コール先のイベントシーケンス1からスタート
				FieldEvent_Change(event,MJUMPEVT_MapFadeInDoor,emw);
			}else{					//ドアなし
				FMJ_WORK_PTR work;
				//フェードイン開始
				work = MapJump_AllocWork();
				FieldEvent_Call(event, MapJump_EventFadeInBlack, work);
				(emw->call_seq) ++;
			}
		}
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	2:エスカレーターフェードインマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInEsca(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FLD_3D_ANIME_WORK_PTR	anime_work;
	switch (emw->call_seq) {
	case 0:	//アニメワーク確保
		emw->JumpEffectWork = Fld3DAnm_AllocEvent3DAnimeWork();
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		Fld3DAnm_EventSetGrid(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								anime_work	);
		(emw->call_seq)++;
		break;
	case 1:	//エスカレーターアニメ	降りる
		anime_work = (FLD_3D_ANIME_WORK_PTR)emw->JumpEffectWork;
		if ( Fld3DAnm_EventEscalatorOutAnime(fsys, anime_work,Player_DirGet( fsys->player )) ){
			Fld3DAnm_FreeEvent3DAnimeWork(emw->JumpEffectWork);	//アニメワーク解放
			(emw->call_seq)++;
		}
		break;
	case 2:			//終了処理
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	3:階段フェードインマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInStairs(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR fop;
	switch (emw->call_seq) {
	case 0:	//自機移動
		//フェードイン開始
		FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKIN);
		fop = Player_FieldOBJGet( fsys->player );
		
		if( /*FieldOBJ_AcmdSetCheck(fop) == TRUE*/1 ){	//アニメセットできるか?
			int dir;
			dir = Player_DirGet( fsys->player );
			if (dir == DIR_LEFT){	//左向き
				FieldOBJ_AcmdSet(fop,AC_WALK_L_16F);	//出来る。任意のアニメセット
			}else if (dir == DIR_RIGHT){	//右向き
				FieldOBJ_AcmdSet(fop,AC_WALK_R_16F);	//出来る。任意のアニメセット
			}else{
				GF_ASSERT(0&&"自機の向きが不正");
			}
		}else{
			GF_ASSERT(0&&"アニメ登録できなかった");
		}
		(emw->call_seq) ++;
		break;
	case 1:	
		fop = Player_FieldOBJGet( fsys->player );
		if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
			FieldOBJ_AcmdEnd(fop); //アニメ終了	
			(emw->call_seq) ++;
		}
		break;
	case 2:	
		if (WIPE_SYS_EndCheck()) {
			(emw->call_seq) ++;
		}
		break;
	case 3:		//終了処理
		return TRUE;
	}
	return FALSE;

}

//-----------------------------------------------------------------------------
// @brief	5:ダンジョン出るフェードインマップ遷移イベント(イベントコール)
//-----------------------------------------------------------------------------
static BOOL MJUMPEVT_MapFadeInDunOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * emw = FieldEvent_GetSpecialWork(event);
	FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
	switch (emw->call_seq) {
	case 0:
		{
			FMJ_WORK_PTR work;
			work = MapJump_AllocWork();
			FieldEvent_Call(event, MapJump_EventFadeInWhite, work);
			emw->call_seq++;
		}
		break;
	case 1:
		return TRUE;
/**		
		//自機を非表示
		FieldOBJ_StatusBitSet_Vanish( player, TRUE );
		(emw->call_seq)++;
		break;
	case 1:
		//ワイプスタート	ホワイトイン
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
						WIPE_TYPE_FADEIN,0x7fff,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		(emw->call_seq) ++;
		break;
	case 2:	//自機を表示して、方向別に1歩前進
		FieldOBJ_StatusBitSet_Vanish( player, FALSE );
		(emw->call_seq) ++;
		break;
	case 3:
		{
			FIELD_OBJ_PTR fop;
			fop = Player_FieldOBJGet( fsys->player );
			if( FieldOBJ_AcmdEndCheck(fop) == TRUE ){	//アニメ終了チェック
				FieldOBJ_AcmdEnd(fop); //アニメ終了	
				(emw->call_seq) ++;
			}
		}
		break;
	case 4:
		if (WIPE_SYS_EndCheck()) {
			return TRUE;
		}
*/		
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief 2:ジャンプ後、エスカレーターアニメーションを考え、自機の初期位置を変更する
//-----------------------------------------------------------------------------
static void SetEscalatorIOPos(FIELDSYS_WORK *fsys)
{
	int dir;
	VecFx32 vec;
	
	//マップ出現位置から左右１グリッドの場所に自機を出す
	//自機の座標,方向を取得
	dir = Player_DirGet( fsys->player );
	Player_VecPosGet( fsys->player, &vec );
	if (dir == DIR_RIGHT){
		vec.x -= (FX32_ONE*16);
	}else{	//(dir == DIR_LEFT)
		vec.x += (FX32_ONE*16);
	}
	//高さ取得
	vec.y = GetHeightPack(	fsys, vec.y, vec.x, vec.z, NULL);

	//座標セット
	Player_VecPosInit( fsys->player, &vec, dir );
	//自機座標を移動したのでバインドしなおし
	GFC_ReSetCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
	GFC_BindCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
}

//-----------------------------------------------------------------------------
// @brief 3:ジャンプ後、階段アニメーションを考え、自機の初期位置を変更する
//-----------------------------------------------------------------------------
static void SetStairsIOPos(FIELDSYS_WORK *fsys)
{
	int x,z,dir;
	VecFx32 vec;
	u8 attr;
	//自機の向きをみて、マップ出現位置から左右１グリッド離れた場所に自機を出す
	//自機の座標,方向を取得
	dir = Player_DirGet( fsys->player );
	Player_VecPosGet( fsys->player, &vec );
	
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	
	attr = GetAttributeLSB( fsys, x, z );
	if (MATR_IsRightStairs(attr)){//右階段の場合
		vec.x += (FX32_ONE*16);	//右へ１グリッド
		dir = DIR_LEFT;
	}else if(MATR_IsLeftStairs(attr)){	//左階段の場合
		vec.x -= (FX32_ONE*16);	//左へ１グリッド
		dir = DIR_RIGHT;
	}else{
		//GF_ASSERT(0&&"階段アトリビュートがはられていません");
		OS_Printf("階段アトリビュートがはられていません\n");
	}
	
	//高さ取得
	vec.y = GetHeightPack(	fsys, vec.y, vec.x, vec.z, NULL);
	//座標セット
	Player_VecPosInit( fsys->player, &vec, dir );
	//自機座標を移動したのでバインドしなおし
	GFC_ReSetCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
	GFC_BindCameraTarget(Player_VecPosPtrGet(fsys->player), fsys->camera_ptr);
}

