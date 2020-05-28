//==============================================================================
/**
 * @file	egg.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.05.20(土)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"

#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"
#include "field/sodateya.h"

#include "system/wipe.h"
#include "include/poketool/poke_memo.h"
#include "include/savedata/mystatus.h"
#include "src/field/zonedata.h"

#include "demo/egg/egg.h"
#include "pokeanime/p_anm_sys.h"
#include "savedata/zukanwork.h"
#include "savedata/get_poke.h"

#include "include/itemtool/itemsym.h"

static PROC_RESULT	EGG_ProcInit(PROC* proc, int* seq);
static PROC_RESULT	EGG_ProcMain(PROC* proc, int* seq);
static PROC_RESULT	EGG_ProcExit(PROC* proc, int* seq);


// =============================================================================
//
//
//	■ プロック
//
//
// =============================================================================
//FS_EXTERN_OVERLAY(overlay_egg);

const PROC_DATA	EGG_ProcData = {
	EGG_ProcInit,
	EGG_ProcMain,
	EGG_ProcExit,	
	NO_OVERLAY_ID,	
//	FS_OVERLAY_ID(overlay_egg),
};

//--------------------------------------------------------------
/**
 * @brief	プロック初期化
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static PROC_RESULT	EGG_ProcInit(PROC* proc, int* seq)
{
	EGG_PROC_WORK*	epwk;
	EGG_MAIN_WORK*	emwk;
	
	sys_VBlankFuncChange(NULL, NULL);			///< VBlankセット
	sys_HBlankIntrStop();						///< HBlank割り込み停止
	
	
	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_EGG_DEMO, EGG_DEMO_HEAP_SIZE);
		
	emwk = PROC_AllocWork(proc, sizeof(EGG_MAIN_WORK), HEAPID_EGG_DEMO);
	memset(emwk, 0, sizeof(EGG_MAIN_WORK));
	
	epwk = PROC_GetParentWork(proc);
	
	emwk->epwk = epwk;
	
	emwk->sys.msg_speed = CONFIG_GetMsgPrintSpeed(emwk->epwk->param.cfg);
	emwk->sys.win_type  = CONFIG_GetWindowType(emwk->epwk->param.cfg);
	
	emwk->sys.g3Dman = EggDisp_3D_Init();
	emwk->sys.ssm_p	 = SoftSpriteInit(HEAPID_EGG_DEMO);
	
	emwk->sys.bgl	 = GF_BGL_BglIniAlloc(HEAPID_EGG_DEMO);
	initVramTransferManagerHeap(EGG_DEMO_VRAM_TRANSFER_TASK_NUM, HEAPID_EGG_DEMO);
	
	emwk->sys.pas	 = PokeAnm_AllocMemory(HEAPID_EGG_DEMO, 1, 0);
	
	emwk->sys.pfd	 = PaletteFadeInit(HEAPID_EGG_DEMO);
	PaletteTrans_AutoSet(emwk->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(emwk->sys.pfd, FADE_MAIN_BG,  0x200, HEAPID_EGG_DEMO);
	PaletteFadeWorkAllocSet(emwk->sys.pfd, FADE_MAIN_OBJ, 0x200, HEAPID_EGG_DEMO);
	PaletteFadeWorkAllocSet(emwk->sys.pfd, FADE_SUB_BG,   0x200, HEAPID_EGG_DEMO);
	PaletteFadeWorkAllocSet(emwk->sys.pfd, FADE_SUB_OBJ,  0x200, HEAPID_EGG_DEMO);
	
	EggDisp_SystemInit();						///< システム初期化
	EggDisp_DefaultBlendSet();					///< Blend設定
	EggDisp_3DVramInit();						///< 3D設定
	
	EggDisp_VramBankSet(emwk->sys.bgl);			///< Bank設定
	
	EggOAM_CatsInit(&emwk->sys);

//	OS_Printf("ssm_p = %8X\n", emwk->epwk);
//	SodateTamagoHuka( emwk->epwk->param.pp, HEAPID_EGG_DEMO );
//	OS_Printf("ssm_p = %8X\n", emwk->epwk);
	
	Snd_Stop();									///< サウンド全停止
	sys_VBlankFuncChange(EggDisp_VBlank, emwk);	///< VBlankセット		

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	プロックメイン
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static PROC_RESULT	EGG_ProcMain(PROC* proc, int* seq)
{
	EGG_MAIN_WORK*	emwk;
	
	emwk = PROC_GetWork(proc);
	
	switch(*seq){
	case 0:
		if (WIPE_SYS_EndCheck() == TRUE){
			(*seq)++;
		}
		{
			int monsno;
			
			monsno = PokeParaGet(emwk->epwk->param.pp, ID_PARA_monsno, NULL);
			
			if (monsno == MONSNO_MANAFI){
				emwk->mode = EDM_MODE_SPECIAL;
			}
			else {
				emwk->mode = EDM_MODE_NORMAL;
			}
		}
		break;
	
	case 1:
		{
			BOOL active;
			
			active = EggMain_Executed(emwk);
			
			if (active == FALSE){
				(*seq)++;
				break;
			}
			
			SoftSpriteMain(emwk->sys.ssm_p);
			EggDisp_ParticleMain();
		}
		break;
	
	default:
		if (WIPE_SYS_EndCheck() == TRUE){
			return PROC_RES_FINISH;
		}
		break;
	}
	return PROC_RES_CONTINUE;	
}


//--------------------------------------------------------------
/**
 * @brief	プロック終了
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static PROC_RESULT	EGG_ProcExit(PROC* proc, int* seq)
{
	EGG_MAIN_WORK*	emwk;
	
	emwk = PROC_GetWork(proc);
	
	GF_G3D_Exit(emwk->sys.g3Dman);
	
	GF_Disp_GX_VisibleControl(GF_BGL_FRAME1_M,  VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GF_BGL_FRAME2_M,  VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GF_BGL_FRAME3_M,  VISIBLE_OFF);
	GF_Disp_GXS_VisibleControl(GF_BGL_FRAME0_S, VISIBLE_OFF);
	
	PaletteFadeWorkAllocFree(emwk->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(emwk->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(emwk->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(emwk->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(emwk->sys.pfd);
		
	GF_BGL_BGControlExit(emwk->sys.bgl, GF_BGL_FRAME1_M);
	GF_BGL_BGControlExit(emwk->sys.bgl, GF_BGL_FRAME2_M);
	GF_BGL_BGControlExit(emwk->sys.bgl, GF_BGL_FRAME3_M);
	GF_BGL_BGControlExit(emwk->sys.bgl, GF_BGL_FRAME0_S);
	
	sys_FreeMemoryEz(emwk->sys.bgl);
	DellVramTransferManager();
	
	SoftSpriteEnd(emwk->sys.ssm_p);
	
	PokeAnm_FreeMemory(emwk->sys.pas);

	EggOAM_CatsDelete(&emwk->sys);

	PROC_FreeWork(proc);
		
	sys_DeleteHeap(HEAPID_EGG_DEMO);
	
	
	//Overlay_UnloadID(FS_OVERLAY_ID(bc_common));

	return PROC_RES_FINISH;
}







// =============================================================================
//
//
//	■ イベントコマンド側
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	デモ監視メイン
 *
 * @param	event	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL EGG_Demo_Main( GMEVENT_CONTROL * event )
{
	EGG_PROC_WORK* epwk = FieldEvent_GetSpecialWork(event);
	
	switch(epwk->seq){
	
	case EDMS_INIT:
		SodateTamagoHuka( epwk->param.pp, HEAPID_WORLD );
		EventCmd_FinishFieldMap(event);
		epwk->seq++;
		break;
	
	case EDMS_MAIN:
		EventCmd_CallSubProc(event, &EGG_ProcData, epwk);
		epwk->seq++;
		break;
	
	case EDMS_NAME_IN_INIT:
		{
			FIELDSYS_WORK*	fsys = FieldEvent_GetFieldSysWork(event);
			
			///< 孵化情報設定
			{
				POKEMON_PARAM* pp	= epwk->param.pp;
				MYSTATUS* my		= SaveData_GetMyStatus( GameSystem_GetSaveData(fsys) );
				TRMEMO_SETID setID  = TRMEMO_EGGBIRTH_PLACESET;
				int placeID			= ZoneData_GetPlaceNameID(fsys->location->zone_id);
				int heapID			= HEAPID_WORLD;
				int para = 0;
				
				PokeParaPut(pp, ID_PARA_tamago_flag, &para);
				TrainerMemoSetPP(pp, my, setID, placeID, heapID);
				
				PokeParaPut(pp, ID_PARA_default_name, NULL);
			}
			
			///< 図鑑登録
			{
				SaveData_GetPokeRegister( GameSystem_GetSaveData(fsys), epwk->param.pp );
			}
			
		
			if (epwk->is_name_set == TRUE){			
				epwk->seq = EDMS_NAME_IN_MAIN;
			}
			else {
				epwk->seq = EDMS_EXIT;
			}
		}
		break;
	
	case EDMS_NAME_IN_MAIN:
		{
			FIELDSYS_WORK*	fsys = FieldEvent_GetFieldSysWork(event);
			int mons_no;
			
			mons_no = PokeParaGet(epwk->param.pp, ID_PARA_monsno, 0);
			
			epwk->namein = NameIn_ParamAllocMake(HEAPID_WORLD, NAMEIN_POKEMON, mons_no, 
													NAMEIN_POKEMON_LENGTH, SaveData_GetConfig(GameSystem_GetSaveData(fsys)));
			epwk->namein->sex  = PokeParaGet(epwk->param.pp, ID_PARA_sex, NULL);
			epwk->namein->form = PokeParaGet(epwk->param.pp, ID_PARA_form_no, NULL);
			EventCmd_CallSubProc(event, &NameInProcData, epwk->namein);
			epwk->seq++;
		}
		break;
	
	case EDMS_NAME_IN_EXIT:
		if (epwk->namein->cancel == 0){
			PokeParaPut(epwk->param.pp, ID_PARA_nickname_buf_flag, epwk->namein->strbuf);
		}
		NameIn_ParamDelete(epwk->namein);
		epwk->seq++;
		break;
	
	case EDMS_EXIT:
		EventCmd_StartFieldMap(event);
		epwk->seq++;
		break;
	
	case EDMS_FREE:
		sys_FreeMemoryEz(epwk);
		return TRUE;
	
	}		
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	デモ監視呼び出し
 *
 * @param	event	
 * @param	param	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EventCmd_EGGProc(GMEVENT_CONTROL * event, void* param)
{
	EGG_PROC_WORK*	epwk;
	EGG_CALL_PARAM*	call_param;
	
	epwk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EGG_PROC_WORK));
	memset(epwk, 0, sizeof(EGG_PROC_WORK));
	
	call_param = (EGG_CALL_PARAM*)param;
	
	epwk->param = *call_param;
		
	FieldEvent_Call(event, EGG_Demo_Main, epwk);
}



// =============================================================================
//
//
//	■ デバッグ用
//
//
// =============================================================================
typedef struct {
	
	int seq;
	int monsno;
	
} DEBUG_EGG_DEMO;
//--------------------------------------------------------------
/**
 * @brief	デモ呼び出し用デバッグ
 *
 * @param	event	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL DebugEGG_GMEVENT_EggDemo(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK*	fsys = FieldEvent_GetFieldSysWork(event);
	int*			seq  = FieldEvent_GetSpecialWork(event);
	
	switch(*seq){
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq)++;
		break;
	case 1:
		{
			EGG_CALL_PARAM param;
			
			POKEPARTY* ppty;
			
			ppty = SaveData_GetTemotiPokemon(fsys->savedata);
			
			param.pp	= PokeParty_GetMemberPointer(ppty ,0);
			param.cfg	= SaveData_GetConfig(fsys->savedata);
			param.my	= SaveData_GetMyStatus(fsys->savedata);
			param.bgmno	= Snd_NowBgmNoGet();	///< 今のBGMナンバーを保存
			
			EventCmd_EGGProc(event, &param);
		}
		(*seq)++;
		break;
	case 2:
		EventCmd_FieldFadeIn(event);
		(*seq)++;
		break;
	case 3:
		sys_FreeMemoryEz(seq);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

static BOOL DebugEGG_GMEVENT_EggDemoMana(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK*	fsys = FieldEvent_GetFieldSysWork(event);
	DEBUG_EGG_DEMO* wk   = FieldEvent_GetSpecialWork(event);
	
	int* seq = &(wk->seq);
	
	switch(*seq){
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq)++;
		break;
	case 1:
		{
			int monsno;
			EGG_CALL_PARAM param;
			
			POKEPARTY* ppty;
			
			ppty = SaveData_GetTemotiPokemon(fsys->savedata);
			
			param.pp	= PokeParty_GetMemberPointer(ppty ,0);
			
			wk->monsno = PokeParaGet(param.pp, ID_PARA_monsno, NULL);
			
			OS_Printf("monsno = %3d\n", wk->monsno);
			
			monsno = MONSNO_MANAFI;
			PokeParaPut(param.pp, ID_PARA_monsno, &monsno);
			
			param.cfg	= SaveData_GetConfig(fsys->savedata);
			param.my	= SaveData_GetMyStatus(fsys->savedata);
			param.bgmno	= Snd_NowBgmNoGet();	///< 今のBGMナンバーを保存
			
			EventCmd_EGGProc(event, &param);
		}
		(*seq)++;
		break;
	case 2:
		{
			int monsno;
			EGG_CALL_PARAM param;
			
			POKEPARTY* ppty;
			
			ppty = SaveData_GetTemotiPokemon(fsys->savedata);
			
			param.pp	= PokeParty_GetMemberPointer(ppty ,0);
			OS_Printf("monsno = %3d\n", wk->monsno);
			
			PokeParaPut(param.pp, ID_PARA_monsno, &wk->monsno);
		}
		EventCmd_FieldFadeIn(event);
		(*seq)++;
		break;
	case 3:
		sys_FreeMemoryEz(wk);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	デバッグ呼び出し
 *
 * @param	fsys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DebugEGG_DemoStart(FIELDSYS_WORK *fsys)
{
	int* seq;
	
	seq = sys_AllocMemoryLo( HEAPID_WORLD, sizeof(int) );
	
	*seq = 0;
		
	FieldEvent_Set(fsys, DebugEGG_GMEVENT_EggDemo, seq);
}


void DebugEGG_DemoStartMana(FIELDSYS_WORK *fsys)
{
	int* seq;
	
	DEBUG_EGG_DEMO* wk;
	
	wk = sys_AllocMemoryLo( HEAPID_WORLD, sizeof(DEBUG_EGG_DEMO) );
	
	wk->monsno = 0;
	wk->seq = 0;
	
	FieldEvent_Set(fsys, DebugEGG_GMEVENT_EggDemoMana, wk);	
}





