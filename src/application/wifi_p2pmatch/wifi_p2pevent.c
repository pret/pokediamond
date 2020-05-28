//============================================================================================
/**
 * @file	wifi_p2pevent.c
 * @bfief	WIFIP2Pイベント制御
 * @author	k.ohno
 * @date	06.04.14
 */
//============================================================================================

#include "common.h"

#include "system/wipe.h"
#include "system/brightness.h"
#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"
#include "field/field_encount.h"
#include "field/sysflag.h"

#include "application/wifi_p2pmatch.h"

#include "wifi/dwc_rap.h"
#include "savedata/wifilist.h"

extern void DwcUtilOverlayStart(void);



FS_EXTERN_OVERLAY(wifi_p2pmatch);
// プロセス定義データ
static const PROC_DATA WifiP2PMatchProcData = {
	WifiP2PMatchProc_Init,
	WifiP2PMatchProc_Main,
	WifiP2PMatchProc_End,
	FS_OVERLAY_ID(wifi_p2pmatch),
};

typedef struct{
    WIFIP2PMATCH_PROC_PARAM* pMatchParam;
	int seq;
    u16* ret;
    u8 lvLimit;
    u8 bSingle;
}EV_P2PEVENT_WORK;

    enum{
        P2P_INIT,
        P2P_MATCH_BOARD_INIT,
		P2P_MATCH_BOARD,
		P2P_SELECT,
		P2P_BATTLE,
        P2P_BATTLE_END,
		P2P_TRADE,
        P2P_TRADE_END,
        P2P_UTIL,
		P2P_EXIT,
        P2P_FREE,
        P2P_SETEND,
        P2P_NOP
	};

static BOOL GMEVENT_Sub_P2PMatch(GMEVENT_CONTROL * event);

//==============================================================================
//	WIFI通信入り口
//==============================================================================
static BOOL GMEVENT_Sub_P2PMatch(GMEVENT_CONTROL * event)
{
	int len;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_P2PEVENT_WORK *ep2p = FieldEvent_GetSpecialWork(event);

		
    switch (ep2p->seq) {
      case P2P_INIT:
        ep2p->pMatchParam->pSaveData = fsys->savedata;
//		EventCmd_FinishFieldMap(event);
  //      ep2p->seq ++;
  //      break;
      case P2P_MATCH_BOARD_INIT:
        ep2p->seq++;
        if(ep2p->pMatchParam->seq == WIFI_P2PMATCH_DPW){
            if( mydwc_checkMyGSID(fsys->savedata) ){
                ep2p->seq = P2P_FREE;  //コード取得済みの場合なにもしない
                *(ep2p->ret) = 0;
            }
        }
		break;
      case P2P_MATCH_BOARD:
        EventCmd_CallSubProc(event, &WifiP2PMatchProcData, ep2p->pMatchParam);
        ep2p->seq ++;
		break;
      case P2P_SELECT:
        if( mydwc_checkMyGSID(fsys->savedata) ){  // コード取得に成功
            SysFlag_WifiUseSet(SaveData_GetEventWork(fsys->savedata));
        }
        switch(ep2p->pMatchParam->seq){
          case WIFI_P2PMATCH_SBATTLE_FREE:   // 通信対戦呼び出し
            ep2p->lvLimit = 0;
            ep2p->bSingle = TRUE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_SBATTLE50:   // 通信対戦呼び出し
            ep2p->lvLimit = 50;
            ep2p->bSingle = TRUE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_SBATTLE100:   // 通信対戦呼び出し
            ep2p->lvLimit = 100;
            ep2p->bSingle = TRUE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_DBATTLE_FREE:   // 通信対戦呼び出し
            ep2p->lvLimit = 0;
            ep2p->bSingle = FALSE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_DBATTLE50:   // 通信対戦呼び出し
            ep2p->lvLimit = 50;
            ep2p->bSingle = FALSE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_DBATTLE100:   // 通信対戦呼び出し
            ep2p->lvLimit = 100;
            ep2p->bSingle = FALSE;
            ep2p->seq = P2P_BATTLE;
            break;
          case WIFI_P2PMATCH_TRADE:   // ポケモントレード呼び出し
            ep2p->seq = P2P_TRADE;
            break;
          case WIFI_P2PMATCH_DPW_END:  //DPWへいく場合
            *(ep2p->ret) = 1;
            ep2p->seq = P2P_SETEND;
            break;
          case WIFI_P2PMATCH_END:  // 通信切断してます。終了します。
            ep2p->seq = P2P_EXIT;
            break;
          case WIFI_P2PMATCH_UTIL:  //WIFIUTILへ飛びます
            ep2p->seq = P2P_UTIL;
            break;
        }
		break;
	case P2P_BATTLE:
        EventCmd_WifiBattle(event, ep2p->pMatchParam->targetID, ep2p->lvLimit, ep2p->bSingle);
        ep2p->seq++;
        break;
	case P2P_BATTLE_END:
        ep2p->seq = P2P_MATCH_BOARD;
		break;
      case P2P_TRADE:
        EventCmd_UnionTrade(event);
        ep2p->seq++;
        break;
      case P2P_TRADE_END:
        ep2p->seq = P2P_MATCH_BOARD;
		break;
      case P2P_UTIL:
        sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFIP2PMATCH, DWC_UTILITY_WORK_SIZE+0x100 );
        DwcUtilOverlayStart();
        mydwc_callUtility(HEAPID_WIFIP2PMATCH);
        OS_ResetSystem(0); 
        break;
      case P2P_EXIT:
      case P2P_SETEND:
      case P2P_FREE:
        sys_FreeMemoryEz(ep2p->pMatchParam);
		sys_FreeMemoryEz(ep2p);
        ep2p->seq++;
		return TRUE;
      default:
		return TRUE;
	}
	return FALSE;
}


static EV_P2PEVENT_WORK* _createEvP2PWork(void)
{
    EV_P2PEVENT_WORK *ep2p = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_P2PEVENT_WORK));
    MI_CpuClear8(ep2p, sizeof(EV_P2PEVENT_WORK));
    ep2p->pMatchParam = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(WIFIP2PMATCH_PROC_PARAM));
	MI_CpuClear8(ep2p->pMatchParam, sizeof(WIFIP2PMATCH_PROC_PARAM));
    return ep2p;
}

void EventCmd_P2PMatchProc(GMEVENT_CONTROL * event)
{
	EV_P2PEVENT_WORK *ep2p = _createEvP2PWork();
    ep2p->pMatchParam->seq = WIFI_P2PMATCH_P2P;
	FieldEvent_Call(event, GMEVENT_Sub_P2PMatch, ep2p);
}

void EventCmd_DPWInitProc(GMEVENT_CONTROL * event)
{
	EV_P2PEVENT_WORK *ep2p = _createEvP2PWork();
    ep2p->pMatchParam->seq = WIFI_P2PMATCH_DPW;
	FieldEvent_Call(event, GMEVENT_Sub_P2PMatch, ep2p);
}

void EventCmd_DPWInitProc2(GMEVENT_CONTROL * event, u16* ret)
{
	EV_P2PEVENT_WORK *ep2p = _createEvP2PWork();
    ep2p->pMatchParam->seq = WIFI_P2PMATCH_DPW;
    ep2p->ret = ret;
	FieldEvent_Call(event, GMEVENT_Sub_P2PMatch, ep2p);
}


