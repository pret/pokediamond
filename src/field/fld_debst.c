//============================================================================================
/**
 *	@file	fld_debst.c
 *	@brief	フィールドデバッグメニュー　常駐領域
 *	@author	Miyuki Iwasawa
 *	@date	06.03.16
 *
 *	フィールドデバッグメニューソースで常駐して欲しいものはここ
 */
//============================================================================================

#ifdef PM_DEBUG
#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "system/fontproc.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "ev_mapchange.h"
#include "fld_debug.h"
#include "zonedata.h"
#include "system/builddate.h"
#include "system/window.h"
#include "system/wipe.h"
#include "mapdefine.h"
#include "system/snd_tool.h"
#include "field/field.h"
#include "field/field_matrix.h"

#include "application/townmap.h"

#include "system/bmp_cursor.h"
#include "system/arc_util.h"


//有効にするとデバッグメニュー「そらをとぶ」にカットインが入る 060505 kaga
//#define DEBUG_SKYJUMP_CUTIN_ON

#ifdef DEBUG_SKYJUMP_CUTIN_ON
#include "field_cutin.h"
#endif

//SkyJump
#ifdef DEBUG_SKYJUMP_CUTIN_ON
typedef struct _DEB_SKYJUMP{
	FIELDSYS_WORK* fsys;
	void* pWork;
	TCB_PTR tcb_cutin;
	int	seq;
	int	wipe_f;
}DEB_SKYJUMP;
#else	//DEBUG_SKYJUMP_CUTIN_ON off
typedef struct _DEB_SKYJUMP{
	FIELDSYS_WORK* fsys;
	void* pWork;
	int	seq;
	int	wipe_f;
}DEB_SKYJUMP;
#endif

//プロトタイプ
void DebugSkyJump_CreateTask(FIELDSYS_WORK* fsys);
void DBJump_JumpMapControl(struct _FIELDSYS_WORK * fsys);

/**
 *	@brief	デバッグ空を飛ぶコントロールタスク
 */

extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

#ifdef DEBUG_SKYJUMP_CUTIN_ON
static void DebugSkyjumpTask(TCB_PTR tcb,void* work)
{
	DEB_SKYJUMP	*wp = (DEB_SKYJUMP*)work;
	TOWNMAP_PARAM* twork;
	
	switch(wp->seq){
	case 0:
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//タウンマップ　空を飛ぶモード呼び出し
		wp->pWork = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(TOWNMAP_PARAM));
		FieldTMap_CallDataSet(wp->fsys,wp->pWork,TMAP_MJUMP);
		//デバッグモードフラグON
		twork = (TOWNMAP_PARAM*)wp->pWork;
		twork->debug_f = TRUE;
		FieldTMap_SetProc(wp->fsys,wp->pWork);
		break;
	case 2:
		//タウンマッププロセス終了待ち
		if(FieldEvent_Cmd_WaitSubProcEnd(wp->fsys)){
			return;
		}
		//フィールドプロセス復帰
		FieldEvent_Cmd_SetMapProc(wp->fsys);
		break;
	case 3:
		//フィールドプロセス開始終了待ち
		if(!FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			return;
		}
		
		//ブラックインリクエスト
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 4:
		//フェードイン待ち
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		
		//パラメータ取得
		twork = (TOWNMAP_PARAM*)wp->pWork;
		if(!twork->retval){
			wp->seq = 6;
			return;
		}
		
		//カットインリクエスト
		{
			POKEMON_PARAM *param =
				PokeParty_GetMemberPointer(
					SaveData_GetTemotiPokemon(wp->fsys->savedata), 0 );
			
			wp->tcb_cutin = FieldCutIn_Init(
				wp->fsys, CUTIN_TYPE_SKY,
				param, Player_SexGet(wp->fsys->player) );
		}
		
		break;
	case 5:
		
		//カットイン終了待ち
		if( FieldCutIn_EndCheck(wp->tcb_cutin) == FALSE ){
			return;
		}
		FieldCutIn_End( wp->tcb_cutin );
		
		twork = (TOWNMAP_PARAM*)wp->pWork;
		
		//ジャンプ
		EventSet_MapChangeBySky(wp->fsys,
			twork->ret_zone,DOOR_ID_JUMP_CODE,
			twork->ret_x*32+16,twork->ret_z*32+16, DIR_DOWN);
		break;
	case 6:
		sys_FreeMemoryEz(wp->pWork);
		sys_FreeMemoryEz(wp);
		TCB_Delete(tcb);
		return;
	}
	wp->seq++;
}
#else	//DEBUG_SKYJUMP_CUTIN_ON off
static void DebugSkyjumpTask(TCB_PTR tcb,void* work)
{
	DEB_SKYJUMP	*wp = (DEB_SKYJUMP*)work;
	TOWNMAP_PARAM* twork;
	
	switch(wp->seq){
	case 0:
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//タウンマップ　空を飛ぶモード呼び出し
		wp->pWork = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(TOWNMAP_PARAM));
		FieldTMap_CallDataSet(wp->fsys,wp->pWork,TMAP_MJUMP);
		//デバッグモードフラグON
		twork = (TOWNMAP_PARAM*)wp->pWork;
		twork->debug_f = TRUE;
		FieldTMap_SetProc(wp->fsys,wp->pWork);
		break;
	case 2:
		//タウンマッププロセス終了待ち
		if(FieldEvent_Cmd_WaitSubProcEnd(wp->fsys)){
			return;
		}
		//フィールドプロセス復帰
		FieldEvent_Cmd_SetMapProc(wp->fsys);
		break;
	case 3:
		//フィールドプロセス開始終了待ち
		if(!FieldEvent_Cmd_WaitMapProcStart(wp->fsys)){
			return;
		}
		//ブラックインリクエスト
		wp->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,HEAPID_BASE_DEBUG
				);
		break;
	case 4:
		//フェードイン待ち
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//パラメータ取得
		twork = (TOWNMAP_PARAM*)wp->pWork;
		if(!twork->retval){
			break;
		}
	
		//ジャンプ
		EventSet_EasyMapChange(wp->fsys,
			twork->ret_zone,DOOR_ID_JUMP_CODE,
			twork->ret_x*32+16,twork->ret_z*32+16, DIR_DOWN);
		break;
	case 5:
		sys_FreeMemoryEz(wp->pWork);
		sys_FreeMemoryEz(wp);
		TCB_Delete(tcb);
		return;
	}
	wp->seq++;
}
#endif

/**
 *	@brief	デバッグ空を飛ぶ　タスク登録
 */
void DebugSkyJump_CreateTask(FIELDSYS_WORK* fsys)
{
	DEB_SKYJUMP *wp;

	//空を飛ぶタスク作成
	wp = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(DEB_SKYJUMP));
	MI_CpuClear8(wp,sizeof(DEB_SKYJUMP));

	wp->fsys = fsys;
	TCB_Add(DebugSkyjumpTask,wp,0);
}

typedef struct {
	int seq;
	int subseq;
	int next_zone_id;
	int next_door_id;
	int next_x;
	int next_z;
	BOOL brightness;
}EVENT_UGCHG_WORK;

typedef struct {
	GF_BGL_BMPWIN	win;//BMP
	u8 cur_pos;
	int grid_val[2];	// 0=x、1=Z
	FIELDSYS_WORK * fsys;
	BMPCURSOR *Cursor;
}JUMP_CONT;

/**
 *	@brief	座標指定ジャンプフェードアウト
 */
static BOOL Sub_FadeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

	switch (mcw->subseq) {
		case 0:	
		GameSystem_FinishFieldProc(fsys);
		(mcw->subseq) ++;
		break;
	case 1:
		if (!GameSystem_CheckFieldProcExists(fsys)) {
			mcw->subseq = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

/**
 *	@brief	座標指定ジャンプフェードイン
 */
static BOOL Sub_FadeIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

	switch (mcw->subseq) {
	case 0:
		GameSystem_CreateFieldProc(fsys);
		(mcw->subseq) ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			mcw->subseq = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}


/**
 *	@brief	座標指定ジャンプ描画
 */
static void DrawJumpCont(JUMP_CONT *work)
{
	u16 buff[10];
	
	GF_BGL_BmpWinDataFill( &work->win, 0x0f );
	
	BMPCURSOR_Print( work->Cursor, &work->win, 0, work->cur_pos*16 );
	
	{
		STRBUF* str1 = STRBUF_Create(3, HEAPID_BASE_DEBUG);
		STRBUF* str2 = STRBUF_Create(3, HEAPID_BASE_DEBUG);
		STRBUF_SetNumber( str1, work->grid_val[0], 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str1, 2*8, 0, MSG_ALLPUT, NULL );
		STRBUF_SetNumber( str2, work->grid_val[1], 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str2, 2*8, 16, MSG_ALLPUT, NULL );
		STRBUF_Delete(str2);
		STRBUF_Delete(str1);
	}
	
	GF_BGL_BmpWinOn( &work->win );
}

/**
 *	@brief	座標指定ジャンプイベント
 */
static BOOL GMEVENT_JumpMap(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
		
	switch (mcw->seq) {
	case 0:
		if(Sub_FadeOut(event)){		// プロックChange
			(mcw->seq) ++;
		}
		break;
	case 1:
		EventCmd_MapChange(event, mcw->next_zone_id, mcw->next_door_id,
				mcw->next_x, mcw->next_z, DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 2:
		if(Sub_FadeIn(event)){		// プロックChange
			(mcw->seq) ++;
		}
		break;
	case 3:
		///PlaceNameRequest(fsys->place_name_cont,0);//地名表示
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	座標指定ジャンプコントロール
 */
static void DebugJumpControlTask(TCB_PTR tcb,void* work)
{
	JUMP_CONT	*wp;
	BOOL write;
	
	wp = (JUMP_CONT*)work;

	write = FALSE;
	//キー操作判定
	if ( (sys.trg & PAD_KEY_DOWN) ||
			(sys.trg & PAD_KEY_UP) ){
		//カーソルを消す
		//カーソル移動
		wp->cur_pos = (wp->cur_pos+1)%2;
		//カーソルを描く
		write = TRUE;
	}else if(sys.trg & PAD_KEY_LEFT){
		//値を減らす
		if (wp->grid_val[wp->cur_pos]-1<0){
			wp->grid_val[wp->cur_pos] = 29;
		}else{
			wp->grid_val[wp->cur_pos]--;
		}
		write = TRUE;
	}else if(sys.trg & PAD_KEY_RIGHT){
		//値を増やす
		wp->grid_val[wp->cur_pos] = (wp->grid_val[wp->cur_pos]+1)%30;
		write = TRUE;
	}

	if (write){
		DrawJumpCont(wp);
	}


	if(sys.trg & PAD_BUTTON_A){
		//ジャンプ
		EVENT_UGCHG_WORK * mcw;

		//イベント生成
		mcw = sys_AllocMemoryLo(HEAPID_BASE_DEBUG, sizeof(EVENT_UGCHG_WORK));
		mcw->seq = 0;
		mcw->subseq = 0;

		{
			int x,z;
			x = wp->grid_val[0];
			z = wp->grid_val[1];
			
			mcw->next_door_id = DOOR_ID_JUMP_CODE;
			mcw->next_x = x*32+16;
			mcw->next_z = z*32+16;
			//mcw->next_dir = DIR_DOWN;
		
			if (wp->fsys->location->zone_id == ZONE_ID_UG){//今地下
				mcw->next_zone_id = ZONE_ID_UG;
				///FieldEvent_Set(wp->fsys, GMEVENT_JumpMapForUG, mcw);
				JumpUnderGroundDirect(wp->fsys,x,z);
			}else{											//今地上
				mcw->next_zone_id = GetZoneIDFromMatrixID(	wp->fsys->World,
															MATRIX_ID_SINOU,
															wp->grid_val[0],
															wp->grid_val[1],
															30);
				FieldEvent_Set(wp->fsys, GMEVENT_JumpMap, mcw);
			}
		}
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		//ワークメモリ開放
		BMPCURSOR_Delete(  wp->Cursor );
		sys_FreeMemoryEz(work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
		return;
	}
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		//ワークメモリ開放
		BMPCURSOR_Delete(  wp->Cursor );
		sys_FreeMemoryEz(work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}

/**
 *	@brief	座標指定ジャンプ
 */
void DBJump_JumpMapControl(struct _FIELDSYS_WORK * fsys)
{
	JUMP_CONT *d_work;

	//地上以外は無視
	if ( (ZoneData_GetMatrixID(fsys->location->zone_id) != MATRIX_ID_FIELD)&&
			(ZoneData_GetMatrixID(fsys->location->zone_id) != MATRIX_ID_UNDER_GROUND) ){
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
		return;
	}

	d_work = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(JUMP_CONT));
	d_work->fsys = fsys;
	//カーソル初期化
	d_work->cur_pos = 0;
	d_work->Cursor = BMPCURSOR_Create(HEAPID_BASE_DEBUG);
	//現在ブロック取得
	d_work->grid_val[0] = Player_NowGPosXGet( fsys->player ) / 32;
	d_work->grid_val[1] = Player_NowGPosZGet( fsys->player ) / 32;
	//メイン処理タスク追加
	TCB_Add(DebugJumpControlTask,d_work,0);

	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 6, 4, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_BASE_DEBUG );
	//現在ブロック、カーソル表示
	DrawJumpCont(d_work);

	return;
}

//============================================================================================
//
//
//		RTC操作呼び出し
//
//
//============================================================================================
#include "debug/d_rtcmenu.h"

FS_EXTERN_OVERLAY(title_debug);

static const PROC_DATA DebugRtcProcData = {
	DebugRtcMenuProc_Init,
	DebugRtcMenuProc_Main,
	DebugRtcMenuProc_End,
	FS_OVERLAY_ID(title_debug),
};

//------------------------------------------------------------------
//------------------------------------------------------------------
static BOOL GMEVENT_DebugRtcControl(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int *seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		GameSystem_StartSubProc(fsys, &DebugRtcProcData, NULL);
		(*seq) ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys) == FALSE) {
			FieldEvent_Cmd_SetMapProc(fsys);
			(*seq) ++;
		}
		break;
	case 2:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys) == FALSE) {
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief
 */
//------------------------------------------------------------------
void EventSet_DebugRtcCotrol(FIELDSYS_WORK * fsys)
{
	FieldEvent_Set(fsys, GMEVENT_DebugRtcControl, NULL);
}




#endif	//PM_DEBUG
