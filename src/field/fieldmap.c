//============================================================================================
/**
 * @file	fieldmap.c
 * @bfief	フィールドマップ
 * @author	GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/pm_rtc.h"
#include "talk_msg.h"
#include "vram_transfer_manager.h"
#include "vram_transfer_anm.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "sxy.h"
#include "fld_debug.h"
#include "worldmap.h"
#include "mapresource.h"
#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "div_map.h"
#include "system/pm_overlay.h"

#include "camera_move_test.h"
#include "field_light.h"
#include "field_anime.h"
#include "field_glb_state.h"
#include "field_event.h"
#include "fieldobj.h"
#include "weather_sys.h"

#include "player.h"
#include "field_anime.h"
#include "effect_uground.h"

#include "system/render_oam.h"
#include "system/arc_util.h"

#include "debug_saito.h"

#include "fieldmap.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "eventdata.h"

#include "field_3d_anime.h"
#include "place_name.h"	//地名表示

#include "field_effect.h"

#include "script.h"

#include "field_subscreen.h"

#include "situation_local.h"	//Situation_GetTMFootMark
#include "townmap_footmark.h"	//TMFootMark_Update
#include "honey_tree_enc.h"		//HTE_SetHoneyTreeAnimeCallBack

#include "field_camera.h"
#include "ev_time.h"
#include "ev_mapchange.h"		//MapChg_UpdateGameData

#include "fieldmap_func.h"
#include "field_gimmick.h"
#include "field_poketch.h"

#include "system/wipe.h"		//for wipe

#include "ug_base_layout.h"
#include "mapdata_weather.h"
#include "comm_player.h"    //メニューから復帰した時のFIELDOBJ位置

#include "quick_sand.h"

#include "system/pm_debug_wifi.h"

#ifdef PM_DEBUG
#include "debug_3d_draw_count.h"
#endif


// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN

extern WIFI_DEBUG_BATTLE_WK WIFI_DEBUG_BATTLE_Work;
#endif	//_WIFI_DEBUG_TUUSHIN

//============================================================================================
//	定数定義
//============================================================================================

#define	BG_CLEAR_COLOR		( 0x0000 )

#define	SET_FIELD_ANIME		( 1 )
#define	SET_DIVMAP_LOAD		( 2 )
#define	SET_MAP3D_WRITE		( 4 )
#define	SET_FIELD_3D_ANIME	( 8 )

#define	SET_FUNC_CHECK(p,flg)	( p & flg )

//** Vram転送マネージャータスク数 **//
#define VRAM_TRANFER_TASK_NUM	(128)

//** CharManager PlttManager用 **//
#define FLD_CHAR_CONT_NUM				(20)
#define FLD_CHAR_VRAMTRANS_MAIN_SIZE	(0x4000)
#define FLD_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)
#define FLD_PLTT_CONT_NUM				(20)

//分割マップデータの地形用メモリと高さデータ用メモリのサイズ定義
#define GROUND_MEM_SIZE			(0xf000)
#define HEIGHT_MEM_SIZE			(0x9000)
#define UNDER_GROUND_MEM_SIZE	(0xa800)
#define UNDER_HEIGHT_MEM_SIZE	(0x0)

//プロジェクションマトリクスを操作する際のＺオフセット
#define	PRO_MAT_Z_OFS	(4)

//拡張高さの個数
#define EX_HEIGHT_NUM	(8)

//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void bg_set( GF_BGL_INI * ini );
static void bg_exit( GF_BGL_INI * ini );
static void join_clact_oam_init(void);				// セルアクター用共有OAMマネージャの初期化
static void clact_delete(void);		// セルアクターの破棄

static void field_glb_state_init(GLST_DATA_PTR glb);		// デフォルトのグローバルステートの設定

static void	Map3Dwrite(FIELDSYS_WORK * repw);



static void vram_bank_set(void);
static void debug_vram_bank_set(void);
static void char_pltt_manager_init(void);		// キャラクタ・パレットマネージャーの初期化
static void char_pltt_manager_delete(void);		// キャラクタ・パレットマネージャーの破棄


static void FieldMapLoadSeq( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqDivMap( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqFeMoveObj( FIELDSYS_WORK * repw );
static void FieldMapLoadSeqRest( FIELDSYS_WORK * repw );

static PROC_RESULT FieldMapProc_Init(PROC * proc, int * seq);
static PROC_RESULT FieldMapProc_Main(PROC * proc, int * seq);
static PROC_RESULT FieldMapProc_End(PROC * proc, int * seq);

static BOOL FieldMap_ZoneChange(FIELDSYS_WORK * fsys);
static void FieldMap_Update(FIELDSYS_WORK * fsys, u8 flag);
static BOOL WatchPlayerPosition(FIELDSYS_WORK * fsys);

static void vBlankFunc(void * work);
static void UpdateFootMark(FIELDSYS_WORK * fsys);



//#define	OSP_HEAP_SIZE

#ifdef PM_DEBUG
void DebugDispTexBank(const u8 inNo);
#endif

//------------------------------------------------------------------
//	動作モデルリスト制御関連
//------------------------------------------------------------------
static MMDL_WORK * MMDL_Create(int heapID, int area_id);
static const int * MMDL_GetList(const MMDL_WORK * mmdl);
static const int MMDL_GetListSize(const MMDL_WORK * mmdl);
static void MMDL_Delete(MMDL_WORK * mmdl);

FS_EXTERN_OVERLAY(fieldmap_sub);

//============================================================================================
//	グローバル変数
//============================================================================================


//============================================================================================
//
//
//				関数
//
//
//============================================================================================

//----------------------------------------------------------------------------
/**
 *	@brief	フィールドオブジェ用ビルボードアクターVブランク処理
 */
//-----------------------------------------------------------------------------
static inline void fldobj_BlactVblank( FIELDSYS_WORK * fsys )
{
	FIELD_OBJ_BLACT_CONT *conot = FieldOBJSys_BlActContGet( fsys->fldobjsys );
	BLACT_SET_PTR blactset = FieldOBJ_BlActCont_SetPtrGet( conot );
	BLACT_VBlankFunc( blactset );
}

//------------------------------------------------------------------
/**
 * @brief	フィールド用VBLANK関数
 * @param	work
 */
//------------------------------------------------------------------
static void vBlankFunc(void * work)
{
	FIELDSYS_WORK * fsys = work;

	// BG書き換え
	GF_BGL_VBlankFunc( fsys->bgl );

	// Vram転送マネージャー実行
	DoVramTransferManager();

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	

	// 破棄ポリゴンの完全描画破棄
	// を通知
	fldobj_BlactVblank( fsys );
}

//============================================================================================
//
//
//		プロセス関数
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	プロセス関数：初期化：フィールドマップ
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_Init(PROC * proc, int * seq)
{
	u16 bgm_no;
	FIELDSYS_WORK * fsys;
	PROC_RESULT pr = PROC_RES_CONTINUE;
	
	fsys = PROC_GetParentWork(proc);

	switch (*seq) {
	case 0:
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank割り込み停止
		G2_BlendNone();//特殊効果無効化
		G2S_BlendNone();//特殊効果無効化

// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 1;
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = TRUE;
#endif	//_WIFI_DEBUG_TUUSHIN

		//ワイプウィンドウマスクリセット
		WIPE_ResetWndMask( WIPE_DISP_MAIN );
		WIPE_ResetWndMask( WIPE_DISP_SUB );

		//画面設定
		MapChg_Set3DDisplay(fsys);
		
		if (fsys->MapModeData->UseOverlayFlag) {
		//フィールドサブオーバーレイ領域を読み込み
			Overlay_Load(FS_OVERLAY_ID(fieldmap_sub), OVERLAY_LOAD_NOT_SYNCHRONIZE);
		}
		//フィールドヒープ作成
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_FIELD, fsys->MapModeData->HeapSize );
		GF_ASSERT(fsys->fldmap == NULL);
		fsys->fldmap = sys_AllocMemory(HEAPID_FIELD, sizeof(FIELDMAP_WORK));
		MI_CpuClear8(fsys->fldmap, sizeof(FIELDMAP_WORK));
		fsys->fldmap->fmapfunc_sys = FLDMAPFUNC_Sys_Create(fsys, HEAPID_FIELD, 8);

		vram_bank_set();				// ＶＲＡＭバンク設定
		initVramTransferManagerHeap( VRAM_TRANFER_TASK_NUM, HEAPID_FIELD );// ＶＲＡＭ転送マネージャーを初期化
		BLACT_InitSys(FIELDSYS_BLACTSET_NUM, HEAPID_FIELD);	// ビルボードアクターシステム初期化
		simple_3DBGInit(HEAPID_FIELD);
		char_pltt_manager_init();		// キャラクタ・パレットマネージャーの初期化
		join_clact_oam_init();// フィールド用セルアクター初期化

		GF_Disp_DispSelect();

		fsys->bgl = GF_BGL_BglIniAlloc( HEAPID_FIELD );
		bg_set( fsys->bgl );			// ＢＧ設定 
		FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );

		SpScriptSearch(fsys, SP_SCRID_INIT_CHANGE);

		DEBUG_ENTRY_STRESSPRINT_TASK(fsys);
		break;


	case 1:
		FieldMapLoadSeq( fsys );

		//FieldMapLoadSeqの後に（fsys->MapResourceのメモリ確保が済んでから）呼ぶ
		SetupMapResource(fsys->MapResource);
		//拡張配置モデル
		fsys->Map3DObjExp = M3DO_AllocMap3DObjList(HEAPID_FIELD);

		//地下秘密基地グッズ配置(地上にいるときはスルーします)
		BaseLayout_SetupUGBaseGoodsObj(fsys);	
		FieldMapLoadSeqDivMap( fsys );
		FieldMapLoadSeqFeMoveObj( fsys );
		FieldMapLoadSeqRest( fsys );

		{
			u16 weather = Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata));
			WEATHER_Set(fsys->fldmap->weather_data, weather);
		}

		//フィールド初期化：サウンドデータセット(シーンが変更されない時は何もしない)
		Snd_FieldMapInitBgmPlay( fsys, fsys->location->zone_id );

		//特殊スクリプトによるOBJ制御
		SpScriptSearch(fsys, SP_SCRID_OBJ_CHANGE);
		// フィールド内ｴﾌｪｸﾄHBLANKワークの作成と
		// HBLANK割り込みの実行	tomoya takahashi 
		fsys->fldmap->hblanksys = FLDHBLANK_SYS_Init( HEAPID_FIELD );
		FLDHBLANK_SYS_Start( fsys->fldmap->hblanksys );
		// 毒ｴﾌｪｸﾄ
		fsys->fldmap->poisoneffect = POISON_EFFE_Init( HEAPID_FIELD, fsys->fldmap->hblanksys );
		break;


	case 2:
		FieldSubScreen_Init(fsys);					//サブ画面開始処理リクエスト
		break;


	case 3:
		if (FieldSubScreen_WaitInit(fsys)) {		//サブ画面開始処理待ち
			fsys->main_mode_flag = TRUE;
			pr = PROC_RES_FINISH;
		}
		break;
	}

	(*seq)++;
	return pr;
}

//------------------------------------------------------------------
/**
 * @brief	プロセス関数：メイン：フィールドマップ
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_Main(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys;
	fsys = PROC_GetParentWork(proc);

	//この部分は自機の動作状態でなくカメラ移動などと同じく座標だけで制御可能にしたい。
	//（今はゾーン切替が自機動作に依存しすぎているため）
	//if ( Player_MoveStateGet(fsys->player) == OBJ_MOVE_STATE_START ) {
	//
	//…ということで自機座標チェックに移行してみた。2005.12.22	tamada
	if ( WatchPlayerPosition(fsys)) {
		SeedSys_CheckInScreen(fsys);
		UpdateFootMark(fsys);
		Field_SendPoketchInfo(fsys, POKETCH_SEND_MOVE_PLAYER, TRUE);
		if (FieldMap_ZoneChange(fsys)) {
			//SwayGrass_InitSwayGrass(fsys->SwayGrass);	//揺れ草クリア
		}
	}

	FieldMap_Update(fsys, SET_FIELD_3D_ANIME | SET_FIELD_ANIME | SET_DIVMAP_LOAD | SET_MAP3D_WRITE );

	if (fsys->main_mode_flag) {
		return PROC_RES_CONTINUE;
	} else {
		return PROC_RES_FINISH;
	}
}


//------------------------------------------------------------------
/**
 * @brief	プロセス関数：終了：フィールドマップ
 */
//------------------------------------------------------------------
static PROC_RESULT FieldMapProc_End(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys;

	fsys = PROC_GetParentWork(proc);
	DivMapLoadMain(fsys, fsys->map_cont_dat);				//マップロードメイン関数
	switch(*seq){
	case 0:
		//ギミック終了
		FLDGMK_EndFieldGimmick(fsys);
		//バインド対象をはがす
		DivMapPurgeTarget(fsys->map_cont_dat);
		//自機現在座標の退避
		fsys->location->grid_x = Player_NowGPosXGet( fsys->player );
		fsys->location->grid_z = Player_NowGPosZGet( fsys->player );
		fsys->location->dir = Player_DirGet( fsys->player );
		//拡張高さデータ領域解放
		EXH_FreeExHeightList(fsys->ExHeightList);
		
		{
			GF_ASSERT(fsys->field_3d_anime!=0);
			DivMapLoad_FreeMap(fsys->map_cont_dat);
		}
		
		RereaseFld3DAnimeAll(fsys->field_3d_anime);
		FreeFld3DAnimeManager(fsys->field_3d_anime);
		F3DASub_FreeAnimeContManager(&fsys->AnimeContMng);

		FieldAnimeAllRelease(fsys->fldmap->field_trans_anime);
		ReleaseFieldAnime(fsys->fldmap->field_trans_anime);
		fsys->fldmap->field_trans_anime = NULL;

		FieldOBJ_DrawProcPushAll( fsys->fldobjsys );			//描画処理退避
		FieldOBJSys_DrawDelete( fsys->fldobjsys );				//描画処理削除
		FieldOBJSys_MoveStopAll( fsys->fldobjsys );
		FE_Delete( fsys->fes );	//フィールドエフェクト削除
		
		MMDL_Delete(fsys->mmdl);					// 動作モデルリスト解放
		fsys->mmdl = NULL;

		M3DO_FreeMap3DObjList(fsys->Map3DObjExp);

		(*seq)++;
		break;
	case 1:
		if(WaitMapFree(fsys->map_cont_dat) == TRUE){
			ReleaseMapResource(&fsys->MapResource);		// マップリソース解放
			FreeDivMapCont(fsys->map_cont_dat);

			HTE_FreeHoneyTreeDat(&fsys->HoneyTreePtr);//蜜木データ解放

			FieldCameraEnd(fsys);					//フィールドカメラ終了
			
			DellLightCont(&fsys->light_cont_data);	// ライト破棄
			BoardWorkDelete( fsys->board );			// 看板ワーク解放
			FreePlaceNameCont(fsys->fldmap->place_name_cont);	//地名表示構造体解放
			WEATHER_Delete(fsys->fldmap->weather_data);	// 天気破棄
			POISON_EFFE_Delete( fsys->fldmap->poisoneffect );// 毒ｴﾌｪｸﾄ
			FLDHBLANK_SYS_Delete( fsys->fldmap->hblanksys );// Hブランク
			SeedSys_Finish(fsys->fldmap->seedsys);
			FogSys_Delete(&fsys->fog_data);			// フォグデータ
			GLST_Delete(&fsys->glst_data);			// グローバルステートデータ 
			
			clact_delete();							// セルアクターデータ
			
//			FieldMessageWinDel(fsys->bgl);		// メッセージウィンドウ開放
			bg_exit(fsys->bgl);					// BGL開放

			FieldSubScreen_Quit(fsys);			//サブ画面終了処理リクエスト
			(*seq) ++;
		}
		break;

	case 2:
		if (FieldSubScreen_WaitQuit(fsys)) {	//サブ画面終了処理待ち
			char_pltt_manager_delete();	// キャラクタ・パレットマネージャーの破棄
			BLACT_DestSys();		// ビルボードアクターシステムを破棄
			DellVramTransferManager();
			simple_3DBGExit();
			FLDMAPFUNC_Sys_Delete(fsys->fldmap->fmapfunc_sys);
			sys_VBlankFuncChange(NULL, NULL);
			sys_FreeMemoryEz( fsys->bgl );
			sys_FreeMemoryEz( fsys->fldmap );
			fsys->fldmap = NULL;

// WIFI　対戦AUTOﾓｰﾄﾞデバック
#ifdef _WIFI_DEBUG_TUUSHIN
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 0;
#endif	//_WIFI_DEBUG_TUUSHIN

			//フィールドヒープ解放
			sys_DeleteHeap( HEAPID_FIELD );

			if (fsys->MapModeData->UseOverlayFlag) {
			//フィールドサブオーバーレイ領域をアンロード
				Overlay_UnloadID(FS_OVERLAY_ID(fieldmap_sub));
			}

			return PROC_RES_FINISH;
		}
		break;

	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * @brief	プロセス定義データ：フィールド
 */
//------------------------------------------------------------------
const PROC_DATA FieldProcData = {
	FieldMapProc_Init,
	FieldMapProc_Main,
	FieldMapProc_End,
	NO_OVERLAY_ID,
};



//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	自機座標更新の監視
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
static BOOL WatchPlayerPosition(FIELDSYS_WORK * fsys)
{
	int x,z;
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	if (x != fsys->location->grid_x || z != fsys->location->grid_z) {
		fsys->location->grid_x = x;
		fsys->location->grid_z = z;
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	フィールド歩きでのゾーン切替
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	BOOL	TRUEのとき、ゾーンが切り替わった
 */
//------------------------------------------------------------------
static BOOL FieldMap_ZoneChange(FIELDSYS_WORK * fsys)
{
	u32 new_zone_id;
	u32 old_zone_id;
	int x,z;
	SITUATION * sit;

	x = Player_NowGPosXGet( fsys->player ) / BLOCK_GRID_W;
	z = Player_NowGPosZGet( fsys->player ) / BLOCK_GRID_H;
	new_zone_id = World_GetZoneIDFromMatrixXZ(fsys->World, x, z);
	old_zone_id = fsys->location->zone_id;
	//直前のゾーンと次のゾーンが同じ場合は何もしない
	if (new_zone_id == old_zone_id) {
		return FALSE;
	}
	
	//++++++++++++++	ゾーン更新処理			++++++++++++
	sit = SaveData_GetSituation(fsys->savedata);
	{
		//ロケーション更新（地続きの変移のため、ゾーンＩＤのみの更新となる。）
		fsys->location->zone_id = new_zone_id;
		//ゾーン別データの読み込み
		EventData_LoadZoneData(fsys, new_zone_id);
		
		//マップ遷移時のデータ更新処理
		MapChg_UpdateGameData(fsys, TRUE);
	}
	
	//++++++++++++++	旧ゾーン動作モデル削除処理	++++++++++++
	{
		int max = EventData_GetNpcCount( fsys );
		const FIELD_OBJ_H *head = EventData_GetNpcData( fsys );
		FieldOBJSys_ZoneUpdateDelete( fsys->fldobjsys, old_zone_id, new_zone_id, max, head );
	}

	//++++++++++++++	新ゾーンデータ追加処理	++++++++++++
	{
		SwayGrass_InitSwayGrass(fsys->SwayGrass);	//揺れ草クリア
			
		//フェードアウト → 追加波形読み込み → BGM再生
		Snd_FadeOutNextPlayCall( fsys, Snd_FieldBgmNoGet(fsys,fsys->location->zone_id), 
									BGM_FADE_FIELD_MODE );

		;//OBJ登録
		EventData_SetFieldOBJ(fsys);

		//天候リクエスト
		WEATHER_ChengeReq(fsys->fldmap->weather_data, Situation_GetWeatherID(sit));
	}

	//地名表示リクエスト
	{
		int place_id_old,place_id_new;
		place_id_old = ZoneData_GetPlaceNameID(old_zone_id);
		place_id_new = ZoneData_GetPlaceNameID(new_zone_id);
		if (place_id_old != place_id_new){
			PlaceNameRequest(fsys->fldmap->place_name_cont, place_id_new);//地名表示
		}
	}
	
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドマップ更新処理
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
static void FieldMap_Update(FIELDSYS_WORK * fsys, u8 flag)
{

	if (FieldEvent_Check(fsys) == FALSE) {
		EVTIME_Update(fsys);
	}

	MainLightCont(fsys->light_cont_data);		// ライトメイン

	//チャンネルフェードシステム(昼と夜で曲のチャンネル操作)
	//Snd_TrackFadeCall( fsys,Snd_FieldBgmNoGet(fsys,fsys->location->zone_id) );


	BoardMain( fsys );		// 看板制御

	DEBUG_INIT_TICK();
	DEBUG_STORE_TICK(0);
	if( SET_FUNC_CHECK( flag, SET_FIELD_ANIME ) != 0 ){
		FieldAnimeMain(fsys->fldmap->field_trans_anime);	// フィールド転送アニメ
	}
	if( SET_FUNC_CHECK( flag, SET_FIELD_3D_ANIME ) != 0 ){	//フィールド3Ｄアニメ
		F3DA_Main(fsys->field_3d_anime);
	}
	DEBUG_STORE_TICK(1);
	if( SET_FUNC_CHECK( flag, SET_DIVMAP_LOAD ) != 0 ){
		DivMapLoadMain(fsys, fsys->map_cont_dat);				//マップロードメイン関数
	}
	DEBUG_STORE_TICK(2);
	if( SET_FUNC_CHECK( flag, SET_MAP3D_WRITE ) != 0 ){
		Map3Dwrite( fsys );						// 描画エンジン
	}
	DEBUG_STORE_TICK(3);

	if (sys.trg & PAD_BUTTON_X){
		DEBUG_CLEAR_TICK();
	}

}


//------------------------------------------------------------------
/**
 * @brief	タウンマップ足跡情報のアップデート
 * @param	fsys	フィールド制御ワークへのポインタ
 * 
 * townmap_footmark.cに移動するかもしれない。
 */
//------------------------------------------------------------------
static void UpdateFootMark(FIELDSYS_WORK * fsys)
{
	TOWN_MAP_FOOTMARK * footmark;
	int x, z, dir;

	if (ZoneData_IsSinouField(fsys->location->zone_id) == FALSE) {
		//フィールド以外では足跡の更新はない！
		return;
	}
	footmark = Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
	x = Player_NowGPosXGet(fsys->player) / BLOCK_GRID_W;
	z = Player_NowGPosZGet(fsys->player) / BLOCK_GRID_H;
	dir = Player_DirGet(fsys->player);
	TMFootMark_Update(footmark, x, z, dir);
}


//============================================================================================
//============================================================================================
//===========================================================================
/**
 * 
 * ＶＲＡＭバンク設定
 *
 */
//===========================================================================
static void vram_bank_set(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

static void debug_vram_bank_set(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//===========================================================================
/**
 * 
 * ＢＧ設定 
 *
 */
//===========================================================================
// 外部公開用関数
void Fieldmap_BgSet( GF_BGL_INI * ini )
{
	bg_set( ini );
}
void Fieldmap_BgExit( GF_BGL_INI * ini )
{
	bg_exit( ini );
}

// 内部関数
static void bg_set( GF_BGL_INI * ini )
{
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	{	// MAIN DISP（エフェクト１）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT1, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT1, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT1 );
	}

	{	// MAIN DISP（エフェクト２）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_EFFECT2, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_EFFECT2, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_EFFECT2 );
	}
	{	// MAIN DISP（メッセージ）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, FLD_MBGFRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( ini, FLD_MBGFRM_FONT );
	}

//	OS_Printf(
//		"BGL_Alloc!! 1st appHeap = %ld\n", sys_GetHeapFreeSize(HEAPID_FIELD) );

	{
		u16	pal = BG_CLEAR_COLOR;
		DC_FlushRange( (void*)pal, 2 );
		GX_LoadBGPltt( &pal, 0, 2 );
	}

}


// BGL開放
static void bg_exit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, FLD_MBGFRM_EFFECT1 );
	GF_BGL_BGControlExit( ini, FLD_MBGFRM_EFFECT2 );
	GF_BGL_BGControlExit( ini, FLD_MBGFRM_FONT );
}

// セルアクター用共有OAMマネージャの初期化
static void join_clact_oam_init(void)
{
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 124,		// メイン画面OAM管理領域
			0, 31,		// メイン画面アフィン管理領域
			0, 124,		// サブ画面OAM管理領域
			0, 31,		// サブ画面アフィン管理領域
			HEAPID_FIELD);
	
}

// セルアクター初期化
static void clact_delete(void)
{
	// レンダラー共有OAMマネージャ破棄
	REND_OAM_Delete();
}


// デフォルトのグローバルステートの状態を設定
static void field_glb_state_init(GLST_DATA_PTR glb)
{
	GLST_MdlPolyMode(glb, GX_POLYGONMODE_MODULATE, FALSE);
	GLST_MdlCullMode(glb, GX_CULL_BACK, FALSE);
	GLST_MdlAlpha(glb, 31, FALSE);
	GLST_MdlMisc(glb, GX_POLYGON_ATTR_MISC_FOG, TRUE, FALSE);

	GLST_Reflect(glb, GLST_ALL);		// 設定
}

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			FLD_CHAR_CONT_NUM,
			FLD_CHAR_VRAMTRANS_MAIN_SIZE,
			FLD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_FIELD
		};
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// パレットマネージャー初期化
	InitPlttManager(FLD_PLTT_CONT_NUM, HEAPID_FIELD);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

	// 通信アイコン領域を予約する
}

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの破棄
//
//=====================================
void char_pltt_manager_delete(void)
{
	// キャラクタデータ破棄
	DeleteCharManager();
	// パレットデータ破棄
	DeletePlttManager();
}

//===========================================================================
/**
 * 
 * 描画
 *
 */
//===========================================================================
static void Map3Dwrite(FIELDSYS_WORK * repw)
{
	MtxFx44 org_pm,pm;

	//３Ｄ描画開始
	GF_G3X_Reset();

	GFC_CameraLookAt();

	//揺れ草範囲外チェック
	SwayGrass_CheckIO(repw);
	
	DrawAroundBlock(repw->map_cont_dat,repw->glst_data);
		
	M3DO_DrawMap3DObjExp(repw->Map3DObjExp, repw->MapResource);
	//プロジェクションマトリクスの変換
	{
		const MtxFx44 *m;
		m = NNS_G3dGlbGetProjectionMtx();
/**		
		OS_Printf("%x,%x,%x,%x\n%x,%x,%x,%x\n%x,%x,%x,%x\n%x,%x,%x,%x\n",
				m->_00,m->_01,m->_02,m->_03,
				m->_10,m->_11,m->_12,m->_13,
				m->_20,m->_21,m->_22,m->_23,
				m->_30,m->_31,m->_32,m->_33);
*/				
		org_pm = *m;
		pm = org_pm;
		pm._32 += FX_Mul(pm._22,PRO_MAT_Z_OFS*FX32_ONE);
		NNS_G3dGlbSetProjectionMtx(&pm);
		NNS_G3dGlbFlush();		//　ジオメトリコマンドを転送
	}

	//フィールドエフェクト描画
	FE_Draw( repw->fes );
	
	// ビルボードアクターシステム描画
	BLACT_DrawSys();
	//プロジェクションマトリクスを元に戻す
	{
		NNS_G3dGlbSetProjectionMtx(&org_pm);
		NNS_G3dGlbFlush();		//　ジオメトリコマンドを転送
	}

	///<fieldmap_func描画処理
	FLDMAPFUNC_Sys_Draw3D( repw->fldmap->fmapfunc_sys );

	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, SwapBuffMode);
#ifdef DEBUG_3DDRAW_COUNT	
	D_3D_DC_DrawPolygonCountUp();
#endif
}

//===========================================================================
/**
 *
 * フィールド用ワイプシステムを使用した輝度フェード
 *
 */
//===========================================================================
void FieldFadeWipeSet(const u8 flg)
{
	if( flg == FLD_DISP_BRIGHT_BLACKIN ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD  );
	}else if (flg == FLD_DISP_BRIGHT_BLACKOUT){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}else{
		GF_ASSERT(0&&"フェード指定ミス");
	}
}

static void FieldMapLoadSeq( FIELDSYS_WORK * repw )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );	// BG0を非表示

	// ジオメトリ＆レンダリングエンジン関連メモリのスワップ
	// 表示データを完全に消して、ロード時のちらつきを防ぎます。
	G3_SwapBuffers( GX_SORTMODE_AUTO, SwapBuffMode );

	//ロケーション情報から読み込むマップを識別
	//
	repw->field_3d_anime = F3DA_Field3DAnimeInit();	//フィールド3Ｄアニメメモリ確保
	repw->AnimeContMng = F3DASub_InitField3DAnimeCont();

//SetUpWorldMatrix( repw->location->zone_id, repw->World ); <<20060116 move
	{
		u16 area_id, mml_id;
		area_id = ZoneData_GetAreaID(repw->location->zone_id);
		repw->MapResource = AllocMapResource(	area_id,
												repw->field_3d_anime	);
		
		mml_id = ZoneData_GetMoveModelID(repw->location->zone_id);
		GF_ASSERT(repw->mmdl == NULL);
		repw->mmdl = MMDL_Create(HEAPID_FIELD, mml_id);
		
	}
}

static void FieldMapLoadSeqDivMap(FIELDSYS_WORK * repw)
{
	// マップ管理データ確保
	repw->map_cont_dat = InitDivMap(repw->World,
									repw->MapResource,
									repw->field_3d_anime,
									repw->DivMapMode);		
	
	//拡張高さデータ領域確保
	repw->ExHeightList = EXH_AllocExHeightList(EX_HEIGHT_NUM, HEAPID_FIELD);

	repw->HoneyTreePtr = HTE_AllocHoneyTreeDat();	//蜜塗り木用データ確保(地下では使いませんが、確保しちゃいます)
	if (repw->MapMode == MAP_MODE_GROUND){
		//DIVに蜜塗り用のコールバックを設定
		DIVM_SetLoadCallBack( repw->map_cont_dat, HTE_SetHoneyTreeAnimeCallBack, repw );
	}

	LoadDivMap( repw->map_cont_dat,
				repw->location->grid_x,
				repw->location->grid_z);
}

static void FieldMapLoadSeqFeMoveObj(FIELDSYS_WORK * repw)
{
	//フィールドエフェクト初期化
	repw->fes = FE_Init( repw, FE_EFFECT_MAX, HEAPID_FIELD, FE_HEAP_SIZE );
	FE_ParamInit_EOA( repw->fes, FE_EOA_MAX );
	FE_ParamInit_BlAct( repw->fes, HEAPID_FIELD, FE_BLACT_MAX,
		FE_BLACT_MDL_MAX, FE_BLACT_ANM_MAX, FE_BLACT_TEX_MAX,
		FE_BLACT_MDL_HEAP_SIZE, FE_BLACT_ANM_HEAP_SIZE, FE_BLACT_TEX_HEAP_SIZE );
	
	//地下かユニオンであればフィールドOBJに影を付けない
	if( repw->MapMode == MAP_MODE_UNDER || repw->MapMode == MAP_MODE_UNION ){
		FieldOBJSys_ShadowJoinSet( repw->fldobjsys, FALSE );
	}

	//地下とそれ以外で登録するエフェクトデータを変える
	if( repw->MapMode == MAP_MODE_UNDER ){
        FE_EffectRegistMore( repw->fes, DATA_FE_UnderProcRegistTbl );
	}
    else{
        FE_EffectRegistMore( repw->fes, DATA_FE_GroundProcRegistTbl );
    }
	
	//フィールドOBJ描画処理初期化
	FieldOBJSys_DrawInit( repw->fldobjsys,
			FLDOBJ_RESM_MAX_TEX,		//登録最大数
			MMDL_GetListSize(repw->mmdl) + FLDOBJ_RESM_REG_ALWAYS_NUM,	//常駐登録最大数（システム用４つ）
			MMDL_GetList(repw->mmdl) );

	Player_DrawInit( repw->player );	//自機描画初期化
	FieldOBJ_DrawProcPopAll( repw->fldobjsys );			//発生している全OBJの描画処理復帰
    CommPlayerSetForcePos();  // 通信している場合FLDOBJの現在位置への移動
    FieldOBJSys_MoveStopAllClear( repw->fldobjsys );
	DivMapBindTarget(
			Player_VecPosPtrGet(repw->player), repw->map_cont_dat);//地形バインド

	repw->fldmap->seedsys = SeedSys_Init(repw, HEAPID_FIELD);
}

static void FieldMapLoadSeqRest(FIELDSYS_WORK * repw)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );	// BG0を表示

	GF_Disp_DispOn();		// ディスプレイオン

	repw->glst_data = GLST_Init();			// ライト・マテリアル・ポリゴン設定の状態を保存するシステム作成
	field_glb_state_init(repw->glst_data);	// デフォルトの状態を保存

	repw->fog_data = FogSys_Init();			// フォグの状態を保存するシステムを作成
	//カメラの設定
	{
///		BOOL cycling_flg;
		int camera_id = Situation_GetCameraID(SaveData_GetSituation(repw->savedata));
///		cycling_flg = Player_MoveBitCheck_CyclingRoad( repw->player );
		FieldCameraInit( Player_VecPosPtrGet(repw->player), repw, camera_id, TRUE );
	}
	
	repw->light_cont_data = InitLightCont(repw->glst_data,
											MAPRES_GetLightIndex(repw->MapResource));
	repw->fldmap->weather_data = WEATHER_Init(repw);	// 天気システム初期化
	repw->fldmap->place_name_cont = AllocPlaceNameCont(repw->bgl);//地名表示構造体確保
	repw->board = BoardWorkAlloc( HEAPID_FIELD );		// 看板ワーク確保
	
	// フィールド転送アニメ処理初期化
	repw->fldmap->field_trans_anime = InitFieldAnime();
	FieldAnimeSets(repw->fldmap->field_trans_anime, GetMapResourceTexturePTR(repw->MapResource));

	//フィールドギミックセットアップ
	FLDGMK_SetUpFieldGimmick(repw);

	//流砂チェックタスク追加
	QuickSand_CheckTask(repw);
	
	//Vブランク関数セット
	sys_VBlankFuncChange(vBlankFunc, repw);
}





//============================================================================================
//
//
//				エリア別動作モデルリスト関連
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	動作モデルリストの上限
 */
//------------------------------------------------------------------
#define	MMDL_MAX	(FLDOBJ_RESM_REG_MAX_TEX)

//------------------------------------------------------------------
/**
 * @brief	動作モデルリスト制御ワーク定義
 */
//------------------------------------------------------------------
struct MMDL_WORK{
	u16 count;				///<動作モデルリストの定義数
	int id[MMDL_MAX];		///<動作モデルリスト
};
//------------------------------------------------------------------
/**
 * @brief	動作モデルリスト：初期化処理
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	area_id	セットするエリアの指定
 */
//------------------------------------------------------------------
static MMDL_WORK * MMDL_Create(int heapID, int area_id)
{
	int i;
	u16 * arc;
	MMDL_WORK * mmdl;

	mmdl = sys_AllocMemory(heapID, sizeof(MMDL_WORK));
	arc = ArchiveDataLoadMallocLo(ARC_MMODEL_LIST, area_id, heapID);
	//arc = ArchiveDataLoadMallocLo(ARC_MMDL, area_id, heapID);
	for (i = 0; i < MMDL_MAX; i++) {
		mmdl->id[i] = OBJCODEMAX;
	}
	for (i = 0; i < MMDL_MAX; i++) {
		mmdl->id[i] = arc[i];
		if (arc[i] == OBJCODEMAX) {
			break;
		}
	}
	mmdl->count = i;
	sys_FreeMemoryEz(arc);
	return mmdl;
}

//------------------------------------------------------------------
/**
 * @brief	動作モデルリスト：リストを取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	u16		動作モデルリストへのポインタ
 */
//------------------------------------------------------------------
static const int * MMDL_GetList(const MMDL_WORK * mmdl)
{
	return mmdl->id;
}
//------------------------------------------------------------------
/**
 * @brief	動作モデルリスト：リストの定義数を取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	u16		動作モデルリスト上の定義数
 */
//------------------------------------------------------------------
static const int MMDL_GetListSize(const MMDL_WORK * mmdl)
{
	return mmdl->count;
}

//------------------------------------------------------------------
/**
 * @brief	動作モデルリスト：終了処理
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
static void MMDL_Delete(MMDL_WORK * mmdl)
{
	sys_FreeMemoryEz(mmdl);
}

#ifdef PM_DEBUG
void DebugDispTexBank(const u8 inNo)
{
	GXVRamTex tex_bank;
	tex_bank = GX_GetBankForTex();
	if (tex_bank==0){
		OS_Printf("%d:disp_tex_bank=%d\n",inNo,tex_bank);
	}
	GF_ASSERT(tex_bank!=0&&"テクスチャバンク破壊発生");
/*	
	if (tex_bank==0){
		OS_Printf("テクスチャバンク破壊発生");
	}
*/	
}
#endif

