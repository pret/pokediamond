//===========================================================================
/**
 * @file	safari_scope.c
 * @brief	サファリ望遠鏡
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "map_jump.h"		//for wipe
#include "field/fld_flg_init.h"
#include "sysflag.h"

#include "fieldmap.h"		//for FieldFadeWipeSet

#include "map_attr.h"		//for attribute

#include "fieldmap_work.h"	//for hblamk wipe
#include "field_hblank.h"	//for hblank wipe

#include "safari_scope_common.h"
#include "safari_scope_obj.h"
#include "safari_scope_calc.h"
#include "safari_scope.h"

#define SCOPE_DISP_TIME	(60)

typedef struct SCOPE_EVENT_WORK_tag
{
	SSO_PTR SafScpObjPtr;
	SSC_SD_PTR ScpDatPtr;
	LOCATION_WORK *Next;
	u8 Seq;
	u8 Count;
	u8 Wait;
}SCOPE_EVENT_WORK;

enum {
	SS_START,	//初回フェードアウトコール
	SS_F_PROC_END,	//フィールドプロセスを終了
	SS_MAP_CHG,		//マップチェンジ
	SS_F_PROC_START,//フィールドプロセス開始
	SS_SCOPE_SET,	//望遠鏡セットアップ
	SS_SCOPE_VIEW,		//望遠鏡のぞいてる
	SS_SCOPE_RESET,	//次の望遠鏡の準備
	SS_TASK_WAIT,	//セルアクター終了待ち
	SS_END,		//望遠鏡終了
};

static BOOL GMEVENT_SafariScopeStart(GMEVENT_CONTROL * event);

//--------------------------------------------------------------------------------------------
/**
 * イベントコール
 *
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CallSafariScopeEvent(FIELDSYS_WORK * fsys)
{
	SCOPE_EVENT_WORK * sew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SCOPE_EVENT_WORK));
	sew->SafScpObjPtr = SSO_AllocMemory(HEAPID_WORLD);
	sew->ScpDatPtr = SSC_CreateScopePointList(HEAPID_WORLD, fsys);

	sew->Seq = SS_START;
	sew->Count = 0;
	
	//マップジャンプイベントを作成
	FieldEvent_Call(fsys->event, GMEVENT_SafariScopeStart, sew);
}

//--------------------------------------------------------------------------------------------
/**
 * 望遠鏡イベント
 *
 * @param	event		イベントポインタ
 *
 * @return	BOOL		TRUE:終了　FALSE:継続
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_SafariScopeStart(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SCOPE_EVENT_WORK * sew = FieldEvent_GetSpecialWork(event);

	switch (sew->Seq) {
	case SS_START:		//望遠鏡スタート
		//望遠鏡モードセット
		FldFlg_SetScopeMode(fsys, TRUE);
		//ロケーションデータ作成
		SSC_SetNextLocation(sew->Count, sew->ScpDatPtr);
		sew->Next = SSC_GetNextLocaton(sew->ScpDatPtr);
		
		EventCmd_FieldFadeOut(event);			//フェードアウト
		sew->Seq = SS_F_PROC_END;
		break;
	case SS_F_PROC_END:	//フィールドプロセスを終了
		EventCmd_FinishFieldMap(event);
		sew->Seq = SS_MAP_CHG;
		break;
	case SS_MAP_CHG:	//実際にデータを新マップに書き換える
		{
			EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
			if (sew->Count == 0){					//ポケッチをフック
				SysFlag_PoketchHookSet(ev);
///				OS_Printf("ポケッチをフック\n");
			}else if(sew->Count == SCOPE_DISP_CNT){	//ポケッチのフックを解除
				SysFlag_PoketchHookReset(ev);
///				OS_Printf("ポケッチのフックを解除\n");
			}
		}
		//SSC_JumpMap(event, sew->ScpDatPtr);
		EventCmd_MapChangeByLocation(event, sew->Next);
		sew->Seq = SS_F_PROC_START;
		break;
	case SS_F_PROC_START:	//フィールドプロセス開始
		EventCmd_StartFieldMap(event);
		sew->Seq = SS_SCOPE_SET;
		break;
	case SS_SCOPE_SET:
		{
			FIELD_OBJ_PTR player = Player_FieldOBJGet( fsys->player );
			sew->Count++;
			//5回未満なら自機非表示
			//エンカウントするポケモン表示
			//5回処理したら自機は表示（望遠鏡の位置に戻ってる）
			if (sew->Count<=SCOPE_DISP_CNT){
				int monsno;
				monsno = SSC_GetSafScpMons(fsys);
				//自機非表示
				FieldOBJ_StatusBitSet_Vanish( player, TRUE );
				
				SSO_SetupSafariScopeCLACT(sew->SafScpObjPtr,monsno);
				SSO_DrawStartCellAct(sew->SafScpObjPtr);
				sew->Wait = 0;
				Snd_SePlay( SEQ_SE_DP_KASYA );		//覗いたときの音
				MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEIN,
							0xffff,0x0000,6,1,HEAPID_WORLD);
				
				sew->Seq = SS_SCOPE_VIEW;
			}else{
				//自機表示
				FieldOBJ_StatusBitSet_Vanish( player, FALSE );
				EventCmd_FieldFadeIn(event);		//フェードイン
				sew->Seq = SS_END;
			}
		}
		break;
	case SS_SCOPE_VIEW:
		sew->Wait++;
		//ウェイト時間経過が決定ボタン押下で次のシーケンスへ
		if ((sew->Wait>=SCOPE_DISP_TIME)||(sys.trg & PAD_BUTTON_DECIDE)){
			//ロケーションデータ作成
			SSC_SetNextLocation(sew->Count, sew->ScpDatPtr);
			sew->Next = SSC_GetNextLocaton(sew->ScpDatPtr);
			Snd_SePlay( SEQ_SE_DP_KASYA );		//閉じたときの音
			MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT,
								0xffff,0x0000,6,1,HEAPID_WORLD);
	
			sew->Seq = SS_SCOPE_RESET;
		}
		break;
	case SS_SCOPE_RESET:
		SSO_DrawEndCellAct(sew->SafScpObjPtr);
		sew->Seq = SS_TASK_WAIT;
		break;
	case SS_TASK_WAIT:
		if (SSO_WaitDrawCellTask(sew->SafScpObjPtr)){
			//セルアクター解放
			SSO_RereaseSSCellObject(sew->SafScpObjPtr);
			sew->Seq = SS_F_PROC_END;
		}
		break;
	case SS_END:		//終了処理
		////望遠鏡モードリセット
		FldFlg_SetScopeMode(fsys, FALSE);
		
		SSC_RereaseScopePointList(sew->ScpDatPtr);
		SSO_FreeMemory(sew->SafScpObjPtr);
		sys_FreeMemoryEz(sew);
		return TRUE;
	}
	return FALSE;
}
