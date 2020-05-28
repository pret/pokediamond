//==============================================================================
/**
 * @file	cb_sys.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.04.03(月)
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

#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"

#include "include/poketool/pokeicon.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"


#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"

#include "include/application/cb_sys.h"
#include "battle/battle_common.h"
#include "system/wipe.h"

#include "battle/graphic/batt_bg_def.h"

#include "data/cb_data_def.h"

#include "system/pm_overlay.h"


#include "wazaeffect/ball_effect_tool.h"

#include "cb_snd_def.h"
#include "pokeanime/p_anm_sys.h"

#include "include/field/tvtopic_extern.h"
#include "include/savedata/tv_work.h"

FS_EXTERN_OVERLAY(bc_common);



static PROC_RESULT	CB_ProcInit(PROC* proc, int* seq);
static PROC_RESULT	CB_ProcMain(PROC* proc, int* seq);
static PROC_RESULT	CB_ProcEnd(PROC* proc, int* seq);

FS_EXTERN_OVERLAY(custom_ball);
const PROC_DATA CustomBallProcData = {			///< プロセス定義データ

	CB_ProcInit,
	CB_ProcMain,
	CB_ProcEnd,	

	FS_OVERLAY_ID(custom_ball),
};



//--------------------------------------------------------------
/**
 * @brief	プロック初期化
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static PROC_RESULT	
 *
 */
//--------------------------------------------------------------
static PROC_RESULT CB_ProcInit(PROC* proc, int* seq)
{
	CB_MAIN_WORK* cbmw;
	CB_PROC_WORK* cbpw;

	///< ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_CUSTOM_BALL, CB_DEF_HEAP_SIZE);
	
	///< 基本初期化
	CB_Tool_SystemInit(HEAPID_CUSTOM_BALL);
	
	///< ブレンド
	CB_Tool_DefaultBlendSet();

	///< ワーク作成
	cbmw = PROC_AllocWork(proc, sizeof(CB_MAIN_WORK), HEAPID_CUSTOM_BALL);
	memset(cbmw, 0, sizeof(CB_MAIN_WORK));
	
	cbmw->sys.g3Dman = CB_3D_Init();
	
	cbpw = PROC_GetParentWork(proc);	
	cbmw->cb_pw = cbpw;
	
	///< ダミー領域に、タマゴ以外の先頭ポケモン配置
	cbmw->test_pp = PokemonParam_AllocWork(HEAPID_CUSTOM_BALL);
//	CB_Tool_TestPokemonCreate(cbmw);
	
	cbmw->sys.hold	= 0xFF;
	cbmw->page.no	= 0;
	cbmw->page.max	= (CB_Tool_SealCllectionGet(cbmw->cb_pw->save_data) / CB_DEF_PAGE_ITEMS) + 1;
	
	if (cbmw->page.max > CB_DEF_PAGE_MAX){
		cbmw->page.max = CB_DEF_PAGE_MAX;
	}
	
	cbmw->select[0] = CBProc_SelectPosGet(cbmw->cb_pw);
	cbmw->select[1] = CBProc_SelectPosGet(cbmw->cb_pw);
	
	///< セーブデータ引継ぎ
	{
		int i;
		int cb_id;		
		CB_CORE* core;
		
		///< アイテムデータ
		cbmw->cb_item_data = CB_SaveData_ItemDataGet(cbmw->cb_pw->save_data);
		
		///< コアデータ取得
		for (i = 0; i < CB_DEF_CORE_MAX; i++){
			core = CB_SaveData_CoreDataGet(cbmw->cb_pw->save_data, i);
			cbmw->cb_edit_data[i].poke_idx	= CB_DEF_POKE_NOT_INDEX;
			cbmw->cb_edit_data[i].core	 	= core;
		}
		
		///< 手持ちポケモンがカプセルを持っているか検索
		for (i = 0; i < TEMOTI_POKEMAX; i++){
			if (cbmw->cb_pw->poke_para[i] == NULL){ continue; }
			
			cb_id = PokeParaGet(cbmw->cb_pw->poke_para[i], ID_PARA_cb_id, 0);
			
			if (cb_id != 0){
				///< 1 オリジンなので
				cbmw->cb_edit_data[ cb_id - 1 ].poke_idx = i;
			}
		}
	}

	///< 初期化
	cbmw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_CUSTOM_BALL);
	initVramTransferManagerHeap(CB_DEF_VRAM_TRANSFER_TASK_NUM, HEAPID_CUSTOM_BALL);
	
	cbmw->sys.pfd = PaletteFadeInit(HEAPID_CUSTOM_BALL);
	PaletteTrans_AutoSet(cbmw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(cbmw->sys.pfd, FADE_MAIN_BG,  0x200, HEAPID_CUSTOM_BALL);
	PaletteFadeWorkAllocSet(cbmw->sys.pfd, FADE_SUB_BG,	  0x200, HEAPID_CUSTOM_BALL);
	PaletteFadeWorkAllocSet(cbmw->sys.pfd, FADE_MAIN_OBJ, 0x200, HEAPID_CUSTOM_BALL);
	PaletteFadeWorkAllocSet(cbmw->sys.pfd, FADE_SUB_OBJ,  0x200, HEAPID_CUSTOM_BALL);	
	
	CB_Tool_Battle_VramBankSet(cbmw->sys.bgl);
	
	CB_Particle_Init();
	
	///< ソフトスプライト
	cbmw->sys.ssm_p = SoftSpriteInit(HEAPID_CUSTOM_BALL);
//	CB_Test_PokemonSSP_Add(cbmw);
//	CB_Test_PokemonSSP_Vanish(cbmw, 1);
	
	///< アニメ
	cbmw->sys.pas = PokeAnm_AllocMemory(HEAPID_CUSTOM_BALL, 1, 0);

	///< ウィンドウ
	{
		int win_type;
		
		win_type = CONFIG_GetWindowType(cbmw->cb_pw->cfg);
		CB_BMP_WindowResLoad(cbmw->sys.bgl, cbmw->sys.pfd, win_type);
		CB_BMP_WindowResLoad_Sub(cbmw->sys.bgl, cbmw->sys.pfd, win_type);
	}
	
	///< OBJ
	CB_Tool_CatsInit(&cbmw->sys);
	
	///< タッチパネル
	{
		u32 active;
		InitTPSystem();
		active = InitTPNoBuff( 4 );
		if(active != TP_OK){
			OS_Printf("custom ball != TP_OK\n");
		}
	}
	
	///< ボタンシステム
	CB_Tool_ButtonInit(cbmw);

	sys_VBlankFuncChange(CB_Tool_VBlank, cbmw);
	
	///< --- font oam
	FontOam_SysInit(cbmw);
	
	///< サウンドデータロード(カスタムボール)(BGM引継ぎ)
	Snd_DataSetByScene( SND_SCENE_SUB_CUSTOM, 0, 0 );

	OS_Printf("□ custom ball init\n");
	
	return PROC_RES_FINISH;
}


//--------------------------------------------------------------
/**
 * @brief	プロックメイン
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static PROC_RESULT	
 *
 */
//--------------------------------------------------------------
enum {
	CB_SEQ_IN = 0,
	CB_SEQ_MAIN,
	CB_SEQ_OUT,
};
static PROC_RESULT CB_ProcMain(PROC* proc, int* seq)
{
	CB_MAIN_WORK* cbmw;
	
	cbmw = PROC_GetWork(proc);
#if 0
#ifdef CUSTOM_BALL_DOSNT_EXECUTED

	return PROC_RES_FINISH;

#endif
#endif
	switch(*seq){
	case CB_SEQ_IN:
		if (WIPE_SYS_EndCheck() == TRUE){
			*seq = CB_SEQ_MAIN;
		}
		break;
		
	case CB_SEQ_MAIN:
		{
			BOOL active = CustomMain_Executed(cbmw);
			
			if (active == FALSE){
				*seq = CB_SEQ_OUT;
				break;
			}
			
			SoftSpriteMain(cbmw->sys.ssm_p);
			CB_Particle_Main();
		}
		break;
	
	case CB_SEQ_OUT:
		if (WIPE_SYS_EndCheck() == TRUE){
			return PROC_RES_FINISH;
		}
		break;
	}

//	OS_Printf("□ custom ball main\n");

	return PROC_RES_CONTINUE;
}


//--------------------------------------------------------------
/**
 * @brief	プロック終了
 *
 * @param	proc	
 * @param	seq	
 *
 * @retval	static PROC_RESULT	
 *
 */
//--------------------------------------------------------------
static PROC_RESULT CB_ProcEnd(PROC* proc, int* seq)
{
	CB_MAIN_WORK* cbmw;
	
	cbmw = PROC_GetWork(proc);
	
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0,  VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1,  VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2,  VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3,  VISIBLE_OFF);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME1_M);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME2_M);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME3_M);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME0_S);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME1_S);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit(cbmw->sys.bgl, GF_BGL_FRAME3_S);
	

	sys_FreeMemoryEz(cbmw->sys.bgl);
	
	PaletteFadeWorkAllocFree(cbmw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(cbmw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(cbmw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(cbmw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(cbmw->sys.pfd);
	
	CBProc_SelectPosSet(cbmw->cb_pw, cbmw->select[0]);

	sys_FreeMemoryEz(cbmw->test_pp);
	CBS_Delete(cbmw);
	BMN_Delete(cbmw->sys.btn);
	
	///< soft sprite
	SoftSpriteEnd(cbmw->sys.ssm_p);
	PokeAnm_FreeMemory(cbmw->sys.pas);
	
	///< font oam
	FontOam_SysDelete(cbmw);
	
	CB_Tool_CatsDelete(&cbmw->sys);
		
	DellVramTransferManager();
	
	
	GF_G3D_Exit(cbmw->sys.g3Dman);
	
	CB_Tool_SystemDelete( HEAPID_CUSTOM_BALL );
		
	PROC_FreeWork(proc);	///< cbmw free
	
	///< タッチパネル
	{
		u32 active;
		active = StopTP();
		if(active != TP_OK){
			OS_Printf("custom ball != TP_OK\n");
		}
	}
	
	sys_DeleteHeap( HEAPID_CUSTOM_BALL );
	
	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	
	OS_Printf("□ custom ball end\n");
	
	return PROC_RES_FINISH;
}

// =============================================================================
//
//
//	■ PROCワークへのアクセス関数
//
//
// =============================================================================
///< ポケモンパラメータ
POKEMON_PARAM* CBProc_PokeParaGet(CB_PROC_WORK* pw, int no)
{
	int idx = no;

	if (pw->poke_cnt < idx){
		GF_ASSERT(0);
		idx = 0;
	}

	return pw->poke_para[ idx ];
}

///< 最後に選択していたカーソル位置
u8 CBProc_SelectPosGet(CB_PROC_WORK* pw)
{
	return pw->select_pos;
}

void CBProc_SelectPosSet(CB_PROC_WORK* pw, u8 pos)
{
	pw->select_pos = pos;
}


///< プロックの次のシーケンス
u8 CBProc_NextModeGet(CB_PROC_WORK* pw)
{
	return pw->proc_next_mode;
}

void CBProc_NextModeSet(CB_PROC_WORK* pw, u8 mode)
{
	pw->proc_next_mode = mode;
}

/*

	

 */
#include "application/pokelist.h"
typedef struct {
	
	int seq;
	
} CB_EDIT_WORK;

typedef struct {
	
	CB_MAIN_WORK*	mw;
	CB_EDIT_WORK*	edit;	
	CB_PROC_WORK*	p_wk;
	PLIST_DATA*		pld;
	SAVEDATA*		save;
	
	int seq;
	
} CB_SUB_EDIT_WORK;

enum {
	CBPS_INIT = 0,
	CBPS_MAIN,
	CBPS_MAIN_END_CHECK,
	CBPS_LIST,
	CBPS_LIST_END_CHECK,
	CBPS_EXIT,
	CBPS_FREE,
};


static BOOL GMEVENT_Sub_CBEdit(GMEVENT_CONTROL * event)
{
	CB_SUB_EDIT_WORK*	sub_edit = FieldEvent_GetSpecialWork(event);
	CB_PROC_WORK*		p_wk	 = sub_edit->p_wk;
	FIELDSYS_WORK*		fsys	 = FieldEvent_GetFieldSysWork(event);
	
	switch(sub_edit->seq){
	case CBPS_INIT:
		///< 初期化
		EventCmd_FinishFieldMap(event);
		p_wk->save_data = CB_SaveData_AllDataGet(sub_edit->save);
		CBProc_SelectPosSet(p_wk, 0);

		{		
			int i;
			int poke_cnt;
			p_wk->pparty = SaveData_GetTemotiPokemon(sub_edit->save);
			poke_cnt = PokeParty_GetPokeCount(p_wk->pparty);
			p_wk->poke_cnt = poke_cnt;
			for (i = 0; i < poke_cnt; i++){
				p_wk->poke_para[i] = PokeParty_GetMemberPointer(p_wk->pparty, i);
			}
			for ( ; i < TEMOTI_POKEMAX; i++){
				p_wk->poke_para[i] = NULL;
			}
		}
		sub_edit->seq = CBPS_MAIN;
		break;
	
	case CBPS_MAIN:
		///< カプセル画面
		EventCmd_CallSubProc(event, &CustomBallProcData, p_wk);
		sub_edit->seq = CBPS_MAIN_END_CHECK;
		break;
	
	case CBPS_MAIN_END_CHECK:
		///< リストへ行くかの分岐
		{
			u8 mode;
			
			mode = CBProc_NextModeGet(sub_edit->p_wk);
			
			switch(mode){
			default:
				GF_ASSERT(0);
			case CB_PROC_NEXT_MODE_END:
				sub_edit->seq = CBPS_EXIT;		///< 終了
				break;
		
			case CB_PROC_NEXT_MODE_LIST:
				sub_edit->seq = CBPS_LIST;		///< リスト
				break;
			}
		}
		break;
		
	case CBPS_LIST:
		///< リスト処理
		{
			PLIST_DATA* pld	= sub_edit->pld;
			pld->pp			= p_wk->pparty;
			pld->myitem		= SaveData_GetMyItem(sub_edit->save);
			pld->mailblock	= SaveData_GetMailBlock(sub_edit->save);
			pld->ret_sel	= 0;
			pld->type		= PL_TYPE_SINGLE;
			pld->mode		= PL_MODE_KAPSEL_SET;
			pld->cfg		= p_wk->cfg;
			
			EventCmd_CallSubProc(event, &PokeListProcData, pld);
			sub_edit->seq = CBPS_LIST_END_CHECK;
		}
		break;
	
	case CBPS_LIST_END_CHECK:
		///< カプセルへ戻る準備
		{
			PLIST_DATA* pld	= sub_edit->pld;
			POKEMON_PARAM* pp;
			CB_CORE* core;
			CB_SEAL* seal;
			TV_WORK* tvwk;
			int tv_id;
			int cb_id;
			
			cb_id = CBProc_SelectPosGet(sub_edit->p_wk) + 1;
			
			if (pld->ret_sel != PL_SEL_POS_EXIT){
				
				pp = CBProc_PokeParaGet(sub_edit->p_wk, pld->ret_sel);
				
				PokeParaPut(pp, ID_PARA_cb_id, (u8*)&cb_id);
				PokeParaPut(pp,
							ID_PARA_cb_core,
							CB_SaveData_CoreDataGet(p_wk->save_data, cb_id - 1));							
					
				///< TV用データ ０番目は必ずシールが貼られているので０番目で
				core  = CB_SaveData_CoreDataGet(p_wk->save_data, cb_id - 1);
				seal  = CB_SaveData_SealDataGet(core, 0);
				tv_id = CB_SaveData_SealIDGet(seal);
				tv_id = Seal_NameGet(tv_id);					///< seal id から 名前ＩＤへ変換
				tvwk  = SaveData_GetTvWork(fsys->savedata);
				
				TVTOPIC_Entry_Watch_CustomBall(tvwk, pp, tv_id);
			}
		}
		sub_edit->seq = CBPS_MAIN;
		break;
	
	case CBPS_EXIT:
		///< 終了処理
		EventCmd_StartFieldMap(event);
		sub_edit->seq = CBPS_FREE;
		break;

	case CBPS_FREE:
		///< 解放処理
		sys_FreeMemoryEz(sub_edit->pld);
		sys_FreeMemoryEz(sub_edit->p_wk);
		sys_FreeMemoryEz(sub_edit);
		return TRUE;
	}
	return FALSE;
}

void EventCmd_CustomBallEditProc(GMEVENT_CONTROL * event, SAVEDATA* save)
{
	CB_SUB_EDIT_WORK* sub_edit = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(CB_SUB_EDIT_WORK));
	memset(sub_edit, 0, sizeof(CB_SUB_EDIT_WORK));

	sub_edit->save	= save;

	///< プロックワーク
	sub_edit->p_wk	= sys_AllocMemory(HEAPID_WORLD, sizeof(CB_PROC_WORK));
	memset(sub_edit->p_wk, 0, sizeof(CB_PROC_WORK));
	sub_edit->p_wk->cfg = SaveData_GetConfig(save);
	sub_edit->p_wk->save = save;

	///< ポケモンリスト
	sub_edit->pld	= sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
	memset(sub_edit->pld, 0, sizeof(PLIST_DATA));

	FieldEvent_Call(event, GMEVENT_Sub_CBEdit, sub_edit);
}

///< デバッグから呼ばれる
static BOOL GMEVENT_CBEdit(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK*	fsys = FieldEvent_GetFieldSysWork(event);
	CB_EDIT_WORK*	edit = FieldEvent_GetSpecialWork(event);
	
	switch(edit->seq){
	case 0:
		EventCmd_FieldFadeOut(event);
		edit->seq++;
		break;
	case 1:
		EventCmd_CustomBallEditProc(event, fsys->savedata);
		edit->seq++;
		break;
	case 2:
		EventCmd_FieldFadeIn(event);
		edit->seq++;
		break;
	case 3:
		sys_FreeMemoryEz(edit);
		return TRUE;
	}

	return FALSE;
}

void CustomBallEdit_Start(FIELDSYS_WORK *fsys)
{
	CB_EDIT_WORK* edit;
	
	edit = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(CB_EDIT_WORK));
	
	edit->seq = 0;
	
	FieldEvent_Set(fsys, GMEVENT_CBEdit, edit);
}


// =============================================================================
//
//
//	■内部参照
//
//
// =============================================================================

typedef struct {
	u16	id;					///< 登録用ID 0 = データ無 
	u8	name;				///< 名前
	u8	pal_id;				///< パレット
	u8	pt_id;				///< パーティクルの番号
	u8	type;				///< A or B
	u16	price;				///< 値段
	u8	comment_id;			///< コメント
} TCB_SEAL_DATA;

static const TCB_SEAL_DATA Seal_Data[ CB_DEF_ITEM_DATA_NUM ];

#define CB_SEAL_DATA_MAX	(sizeof(Seal_Data))

/*
	データ　いずれアーカイブする
*/
static const TCB_SEAL_DATA Seal_Data[ CB_DEF_ITEM_DATA_NUM ] = {
	{ CB__SEAL_00_NCGR_BIN, SEAL_NAME_000, CB_SEAL_NCLR, SPA_P_CB_HART01, 	 CB_SEAL_TYPE_A, 999, seal_01 },	///< ダミー
	
	{ CB__SEAL_01_NCGR_BIN, SEAL_NAME_001,	 CB_SEAL_NCLR, SPA_P_CB_HART01, 	 CB_SEAL_TYPE_A,  50, seal_01 },
	{ CB__SEAL_02_NCGR_BIN, SEAL_NAME_002,	 CB_SEAL_NCLR, SPA_P_CB_HART02, 	 CB_SEAL_TYPE_A,  50, seal_02 },
	{ CB__SEAL_03_NCGR_BIN, SEAL_NAME_003,	 CB_SEAL_NCLR, SPA_P_CB_HART03, 	 CB_SEAL_TYPE_A,  50, seal_03 },
	{ CB__SEAL_04_NCGR_BIN, SEAL_NAME_004,	 CB_SEAL_NCLR, SPA_P_CB_HART04, 	 CB_SEAL_TYPE_A,  50, seal_04 },
	{ CB__SEAL_05_NCGR_BIN, SEAL_NAME_005,	 CB_SEAL_NCLR, SPA_P_CB_HART05, 	 CB_SEAL_TYPE_A, 100, seal_05 },
	{ CB__SEAL_06_NCGR_BIN, SEAL_NAME_006,	 CB_SEAL_NCLR, SPA_P_CB_HART06, 	 CB_SEAL_TYPE_A, 100, seal_06 },
	
	{ CB__SEAL_08_NCGR_BIN, SEAL_NAME_007,	 CB_SEAL_NCLR, SPA_P_CB_STAR01, 	 CB_SEAL_TYPE_A,  50, seal_07 },
	{ CB__SEAL_07_NCGR_BIN, SEAL_NAME_008,	 CB_SEAL_NCLR, SPA_P_CB_STAR02, 	 CB_SEAL_TYPE_A,  50, seal_08 },
	{ CB__SEAL_10_NCGR_BIN, SEAL_NAME_009,	 CB_SEAL_NCLR, SPA_P_CB_STAR03, 	 CB_SEAL_TYPE_A,  50, seal_09 },
	{ CB__SEAL_09_NCGR_BIN, SEAL_NAME_010,	 CB_SEAL_NCLR, SPA_P_CB_STAR04, 	 CB_SEAL_TYPE_A,  50, seal_10 },
	{ CB__SEAL_12_NCGR_BIN, SEAL_NAME_011,	 CB_SEAL_NCLR, SPA_P_CB_STAR05, 	 CB_SEAL_TYPE_A, 100, seal_11 },
	{ CB__SEAL_11_NCGR_BIN, SEAL_NAME_012,	 CB_SEAL_NCLR, SPA_P_CB_STAR06, 	 CB_SEAL_TYPE_A, 100, seal_12 },
	
	{ CB__SEAL_13_NCGR_BIN, SEAL_NAME_013,	 CB_SEAL_NCLR, SPA_P_CB_LINE01, 	 CB_SEAL_TYPE_A, 100, seal_13 },
	{ CB__SEAL_14_NCGR_BIN, SEAL_NAME_014,	 CB_SEAL_NCLR, SPA_P_CB_LINE02,	 CB_SEAL_TYPE_A, 100, seal_14 },
	{ CB__SEAL_15_NCGR_BIN, SEAL_NAME_015,	 CB_SEAL_NCLR, SPA_P_CB_LINE03,	 CB_SEAL_TYPE_A, 100, seal_15 },
	{ CB__SEAL_15_2_NCGR_BIN, SEAL_NAME_015_2, CB_SEAL_NCLR, SPA_P_CB_LINE04,	 CB_SEAL_TYPE_A, 100, seal_15_02 },
	
	{ CB__SEAL_16_NCGR_BIN, SEAL_NAME_016,	 CB_SEAL_NCLR, SPA_P_CB_KEMURI01,  CB_SEAL_TYPE_A, 100, seal_16 },
	{ CB__SEAL_17_NCGR_BIN, SEAL_NAME_017,	 CB_SEAL_NCLR, SPA_P_CB_KEMURI02,  CB_SEAL_TYPE_A, 100, seal_17 },
	{ CB__SEAL_18_NCGR_BIN, SEAL_NAME_018,	 CB_SEAL_NCLR, SPA_P_CB_KEMURI03,  CB_SEAL_TYPE_A, 100, seal_18 },
	{ CB__SEAL_19_NCGR_BIN, SEAL_NAME_019,	 CB_SEAL_NCLR, SPA_P_CB_KEMURI04,  CB_SEAL_TYPE_A, 100, seal_19 },
	
	{ CB__SEAL_20_NCGR_BIN, SEAL_NAME_020,	 CB_SEAL_NCLR, SPA_P_CB_TUNDER01,  CB_SEAL_TYPE_A, 100, seal_20 },
	{ CB__SEAL_21_NCGR_BIN, SEAL_NAME_021,	 CB_SEAL_NCLR, SPA_P_CB_TUNDER02,  CB_SEAL_TYPE_A, 100, seal_21 },
	{ CB__SEAL_22_NCGR_BIN, SEAL_NAME_022,	 CB_SEAL_NCLR, SPA_P_CB_TUNDER03,  CB_SEAL_TYPE_A, 100, seal_22 },
	{ CB__SEAL_23_NCGR_BIN, SEAL_NAME_023,	 CB_SEAL_NCLR, SPA_P_CB_TUNDER04,  CB_SEAL_TYPE_A, 100, seal_23 },
	
	{ CB__SEAL_24_NCGR_BIN, SEAL_NAME_024,	 CB_SEAL_NCLR, SPA_P_CB_BALL01, 	 CB_SEAL_TYPE_A,  50, seal_24 },
	{ CB__SEAL_25_NCGR_BIN, SEAL_NAME_025,	 CB_SEAL_NCLR, SPA_P_CB_BALL02, 	 CB_SEAL_TYPE_A,  50, seal_25 },
	{ CB__SEAL_26_NCGR_BIN, SEAL_NAME_026,	 CB_SEAL_NCLR, SPA_P_CB_BALL03, 	 CB_SEAL_TYPE_A,  50, seal_26 },
	{ CB__SEAL_27_NCGR_BIN, SEAL_NAME_027,	 CB_SEAL_NCLR, SPA_P_CB_BALL04, 	 CB_SEAL_TYPE_A,  50, seal_27 },
	
	{ CB__SEAL_29_NCGR_BIN, SEAL_NAME_028,	 CB_SEAL_NCLR, SPA_P_CB_FIRE01, 	 CB_SEAL_TYPE_A,  50, seal_28 },
	{ CB__SEAL_28_NCGR_BIN, SEAL_NAME_029,	 CB_SEAL_NCLR, SPA_P_CB_FIRE02, 	 CB_SEAL_TYPE_A,  50, seal_29 },
	{ CB__SEAL_31_NCGR_BIN, SEAL_NAME_030,	 CB_SEAL_NCLR, SPA_P_CB_FIRE03, 	 CB_SEAL_TYPE_A,  50, seal_30 },
	{ CB__SEAL_30_NCGR_BIN, SEAL_NAME_031,	 CB_SEAL_NCLR, SPA_P_CB_FIRE04, 	 CB_SEAL_TYPE_A,  50, seal_31 },
	
	{ CB__SEAL_32_NCGR_BIN, SEAL_NAME_032,	 CB_SEAL_NCLR, SPA_P_CB_PAPER01,	 CB_SEAL_TYPE_A,  50, seal_32 },
	{ CB__SEAL_33_NCGR_BIN, SEAL_NAME_033,	 CB_SEAL_NCLR, SPA_P_CB_PAPER02,	 CB_SEAL_TYPE_A,  50, seal_33 },
	{ CB__SEAL_34_NCGR_BIN, SEAL_NAME_034,	 CB_SEAL_NCLR, SPA_P_CB_PAPER03,	 CB_SEAL_TYPE_A, 100, seal_34 },
	{ CB__SEAL_35_NCGR_BIN, SEAL_NAME_035,	 CB_SEAL_NCLR, SPA_P_CB_PAPER04,	 CB_SEAL_TYPE_A, 100, seal_35 },
	
	{ CB__SEAL_36_NCGR_BIN, SEAL_NAME_036,	 CB_SEAL_NCLR, SPA_P_CB_HANA01, 	 CB_SEAL_TYPE_A,  50, seal_36 },
	{ CB__SEAL_37_NCGR_BIN, SEAL_NAME_037,	 CB_SEAL_NCLR, SPA_P_CB_HANA02, 	 CB_SEAL_TYPE_A,  50, seal_37 },
	{ CB__SEAL_38_NCGR_BIN, SEAL_NAME_038,	 CB_SEAL_NCLR, SPA_P_CB_HANA03, 	 CB_SEAL_TYPE_A,  50, seal_38 },
	{ CB__SEAL_39_NCGR_BIN, SEAL_NAME_039,	 CB_SEAL_NCLR, SPA_P_CB_HANA04, 	 CB_SEAL_TYPE_A,  50, seal_39 },
	{ CB__SEAL_40_NCGR_BIN, SEAL_NAME_040,	 CB_SEAL_NCLR, SPA_P_CB_HANA05, 	 CB_SEAL_TYPE_A,  50, seal_40 },
	{ CB__SEAL_41_NCGR_BIN, SEAL_NAME_041,	 CB_SEAL_NCLR, SPA_P_CB_HANA06, 	 CB_SEAL_TYPE_A,  50, seal_41 },
	
	{ CB__SEAL_42_NCGR_BIN, SEAL_NAME_042,	 CB_SEAL_NCLR, SPA_P_CB_ONPU01, 	 CB_SEAL_TYPE_A,  50, seal_42 },
	{ CB__SEAL_43_NCGR_BIN, SEAL_NAME_043,	 CB_SEAL_NCLR, SPA_P_CB_ONPU02, 	 CB_SEAL_TYPE_A,  50, seal_43 },
	{ CB__SEAL_44_NCGR_BIN, SEAL_NAME_044,	 CB_SEAL_NCLR, SPA_P_CB_ONPU03, 	 CB_SEAL_TYPE_A,  50, seal_44 },
	{ CB__SEAL_45_NCGR_BIN, SEAL_NAME_045,	 CB_SEAL_NCLR, SPA_P_CB_ONPU04, 	 CB_SEAL_TYPE_A,  50, seal_45 },
	{ CB__SEAL_46_NCGR_BIN, SEAL_NAME_046,	 CB_SEAL_NCLR, SPA_P_CB_ONPU05, 	 CB_SEAL_TYPE_A,  50, seal_46 },
	{ CB__SEAL_47_NCGR_BIN, SEAL_NAME_047,	 CB_SEAL_NCLR, SPA_P_CB_ONPU06, 	 CB_SEAL_TYPE_A,  50, seal_47 },
	{ CB__SEAL_48_NCGR_BIN, SEAL_NAME_048,	 CB_SEAL_NCLR, SPA_P_CB_ONPU07, 	 CB_SEAL_TYPE_A,  50, seal_48 },
	
	{ CB__SEAL_49_NCGR_BIN, SEAL_NAME_049,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_A,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_50_NCGR_BIN, SEAL_NAME_050,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_B,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_51_NCGR_BIN, SEAL_NAME_051,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_C,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_52_NCGR_BIN, SEAL_NAME_052,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_D,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_53_NCGR_BIN, SEAL_NAME_053,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_E,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_54_NCGR_BIN, SEAL_NAME_054,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_F,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_55_NCGR_BIN, SEAL_NAME_055,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_G,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_56_NCGR_BIN, SEAL_NAME_056,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_H,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_57_NCGR_BIN, SEAL_NAME_057,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_I,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_58_NCGR_BIN, SEAL_NAME_058,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_J,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_59_NCGR_BIN, SEAL_NAME_059,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_K,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_60_NCGR_BIN, SEAL_NAME_060,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_L,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_61_NCGR_BIN, SEAL_NAME_061,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_M,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_62_NCGR_BIN, SEAL_NAME_062,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_N,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_63_NCGR_BIN, SEAL_NAME_063,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_O,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_64_NCGR_BIN, SEAL_NAME_064,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_P,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_65_NCGR_BIN, SEAL_NAME_065,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_Q,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_66_NCGR_BIN, SEAL_NAME_066,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_R,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_67_NCGR_BIN, SEAL_NAME_067,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_S,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_68_NCGR_BIN, SEAL_NAME_068,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_T,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_69_NCGR_BIN, SEAL_NAME_069,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_U,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_70_NCGR_BIN, SEAL_NAME_070,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_V,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_71_NCGR_BIN, SEAL_NAME_071,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_W,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_72_NCGR_BIN, SEAL_NAME_072,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_X,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_73_NCGR_BIN, SEAL_NAME_073,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_Y,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_74_NCGR_BIN, SEAL_NAME_074,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_Z,	 CB_SEAL_TYPE_B,   0, seal_01 },
	{ CB__SEAL_75_NCGR_BIN, SEAL_NAME_075,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_MARK01, CB_SEAL_TYPE_B, 0, seal_01 },
	{ CB__SEAL_76_NCGR_BIN, SEAL_NAME_076,	 CB_SEAL_NCLR, SPA_P_CB_ALPHA_MARK02, CB_SEAL_TYPE_B, 0, seal_01 },
	
	{ CB__SEAL_77_NCGR_BIN, SEAL_NAME_077,	 CB_SEAL_NCLR, SPA_P_CB_SP_01,		CB_SEAL_TYPE_A, 0, seal_77 },	
	{ CB__SEAL_78_NCGR_BIN, SEAL_NAME_078,	 CB_SEAL_NCLR, SPA_P_CB_SP_02,		CB_SEAL_TYPE_A, 0, seal_78 },	
	{ CB__SEAL_79_NCGR_BIN, SEAL_NAME_079,	 CB_SEAL_NCLR, SPA_P_CB_SP_03,		CB_SEAL_TYPE_A, 0, seal_79 },
};


//--------------------------------------------------------------
/**
 * @brief	キャラ２
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_Li_CharArcGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);
	
	return Seal_Data[id].id;
}


//--------------------------------------------------------------
/**
 * @brief	キャラ
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_CharArcGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);

	return Seal_Data[id].id;
}


//--------------------------------------------------------------
/**
 * @brief	なまえ
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_NameGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);
	
	return Seal_Data[id].name;
}


//--------------------------------------------------------------
/**
 * @brief	パーティクル
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_EffectGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);

	return Seal_Data[id].pt_id;
}


//--------------------------------------------------------------
/**
 * @brief	タイプ
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_TypeGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);

	return Seal_Data[id].type;
}


//--------------------------------------------------------------
/**
 * @brief	値段
 *
 * @param	id	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	Seal_PriceGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);

	return Seal_Data[id].price;
}


//--------------------------------------------------------------
/**
 * @brief	コメント
 *
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int Seal_CommentGet(u8 id)
{
	GF_ASSERT(id < CB_SEAL_DATA_MAX);

	return Seal_Data[id].comment_id;	
}

