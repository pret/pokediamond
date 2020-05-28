//==============================================================================
/**
 * @file	d_matsu.c
 * @brief	松田デバッグ用ファイル
 * @author	matsuda
 * @date	2005.06.20(月)
 */
//==============================================================================

#ifdef PM_DEBUG	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "common.h"
#include "system/pm_overlay.h"
#include "system/test_overlay.h"

#include "system/bmp_list.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "contest/contest.h"

#include "script.h"
#include "..\fielddata\script\connect_def.h"

#include "system/particle.h"
#include "particledata/particledata.h"
#include "particledata/particledata.naix"

#include "system/fontproc.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_matsu.h"

#include "field/sysflag.h"




//==============================================================================
//	オーバーレイIDのextern宣言
//==============================================================================
/* overlay id in *.lcf */
FS_EXTERN_OVERLAY(test_first);
FS_EXTERN_OVERLAY(test_second);
FS_EXTERN_OVERLAY(test_itcm);
FS_EXTERN_OVERLAY(test_second_abc);


//==============================================================================
//	構造体宣言
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   松田デバッグ用構造体
 */
//--------------------------------------------------------------
typedef struct{
	FIELDSYS_WORK *fsys;
	BMPLIST_WORK *lw;
	BMP_MENULIST_DATA *listmenu;
	GF_BGL_BMPWIN bmpwin;
	s16 wait;
	u8 main_seq;
}DMATSU_WORK;

//--------------------------------------------------------------
/**
 * @brief   松田デバッグ用構造体(グローバル変数)
 */
//--------------------------------------------------------------
typedef struct{
	u8 dance_rotation_off;		///<1:ダンスのローテーションなし
}DMATSU_GLOBAL_WORK;

//==============================================================================
//	グローバル変数宣言
//==============================================================================
///1:ローテーションなし。　0:ローテーションあり　2:ダンス回数制限なし
u8 DmatsuWork_DanceRotationOff = 0;

//==============================================================================
//	型宣言
//==============================================================================
typedef void (*pDMFunc)(DMATSU_WORK *);

//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void DM_MenuMain(TCB_PTR tcb, void *work);
static void DM_MenuExit(DMATSU_WORK *dm);
static void DM_ActingStart(DMATSU_WORK *dm);
static void DM_VisualStart(DMATSU_WORK *dm);
static void DM_ClipVisualStart(DMATSU_WORK *dm);
static void DM_DanceStart(DMATSU_WORK *dm);
static void DM_DanceNoneLimitStart(DMATSU_WORK *dm);
static void DM_DanceRotatinOn(DMATSU_WORK *dm);
static void DM_DanceRotationOff(DMATSU_WORK *dm);
static void DM_ContestSioStart(DMATSU_WORK *dm);
static void DM_ResultStart(DMATSU_WORK *dm);
static void TestOverlaySet(DMATSU_WORK *dm);
static void TestSet(DMATSU_WORK *dm);
static void FieldParticleTest(DMATSU_WORK *dm);
static void DM_SysFlagON_Style(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Style(DMATSU_WORK *dm);
static void DM_SysFlagON_Beautiful(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Beautiful(DMATSU_WORK *dm);
static void DM_SysFlagON_Cute(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Cute(DMATSU_WORK *dm);
static void DM_SysFlagON_Clever(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Clever(DMATSU_WORK *dm);
static void DM_SysFlagON_Strong(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Strong(DMATSU_WORK *dm);
void DebugMatsudaInit(FIELDSYS_WORK *fsys);

//==============================================================================
//	デバッグメニューリスト用データ等
//==============================================================================
///デバッグメニューの項目
static const struct {
	u32  str_id;
	u32  param;
}DebugMenuParamList[] = {
	{ DMMSG_ACTIN, (u32)DM_ActingStart },
	{ DMMSG_VISUAL, (u32)DM_VisualStart},
	{ DMMSG_CLIP_VISUAL, (u32)DM_ClipVisualStart},
	{ DMMSG_DANCE, (u32)DM_DanceStart},
	{ DMMSG_DANCE_NONE_LIMIT, (u32)DM_DanceNoneLimitStart},
	{ DMMSG_ROTE_ON, (u32)DM_DanceRotatinOn},
	{ DMMSG_ROTE_OFF, (u32)DM_DanceRotationOff},
	{ DMMSG_TUUSHIN, (u32)DM_ContestSioStart},
	{ DMMSG_RESULT, (u32)DM_ResultStart},
	{ DMMSG_PARTICLE, (u32)FieldParticleTest },
	{ DMMSG_OVERLAY, (u32)TestOverlaySet },
	{ DMMSG_SYSFLAG_ON_STYLE, (u32)DM_SysFlagON_Style },
	{ DMMSG_SYSFLAG_OFF_STYLE, (u32)DM_SysFlagOFF_Style },
	{ DMMSG_SYSFLAG_ON_BEAUTIFUL, (u32)DM_SysFlagON_Beautiful },
	{ DMMSG_SYSFLAG_OFF_BEAUTIFUL, (u32)DM_SysFlagOFF_Beautiful },
	{ DMMSG_SYSFLAG_ON_CUTE, (u32)DM_SysFlagON_Cute },
	{ DMMSG_SYSFLAG_OFF_CUTE, (u32)DM_SysFlagOFF_Cute },
	{ DMMSG_SYSFLAG_ON_CLEVER, (u32)DM_SysFlagON_Clever },
	{ DMMSG_SYSFLAG_OFF_CLEVER, (u32)DM_SysFlagOFF_Clever },
	{ DMMSG_SYSFLAG_ON_STRONG, (u32)DM_SysFlagON_Strong },
	{ DMMSG_SYSFLAG_OFF_STRONG, (u32)DM_SysFlagOFF_Strong },
};


#define LIST_MENU_MAX		(NELEMS(DebugMenuParamList))

///デバッグメニューのリスト
static const BMPLIST_HEADER DebugMenuListHeader = {
	NULL,			// 表示文字データポインタ
	NULL,					// カーソル移動ごとのコールバック関数
	NULL,					// 一列表示ごとのコールバック関数
	NULL,
	LIST_MENU_MAX,	// リスト項目数
	11,//LIST_MENU_MAX,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	8,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_WHITE,			// 文字色
	FBMP_COL_BLACK,			// 背景色
	FBMP_COL_BLK_SDW,		// 文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	FONT_SYSTEM,				// 文字指定
	0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};




//--------------------------------------------------------------
/**
 * @brief   オーバーレイテスト
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void TestOverlayStart(TCB_PTR tcb, void *work)
{
	DMATSU_WORK *dm = work;
	
	if(dm->wait == 0){
		dm->wait++;
		/* address of function is specified in main.lsf */
		OS_Printf("func_1() : addr = 0x%08X.\n", test_overlay_func_1);
		OS_Printf("func_2() : addr = 0x%08X.\n", test_overlay_func_2);
		OS_Printf("func_3() : addr = 0x%08X.\n", test_overlay_itcm);
		return;
	}
	
	//OS_PrintServer();

	//各十時キーによってオーバーレイ読み出し
	if(sys.trg & PAD_KEY_RIGHT){
		//まず同じ空間を使用しているオーバーレイを全てアンロード
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_first));
		//自分自身をオーバーレイ実行
		Overlay_Load(FS_OVERLAY_ID(test_first), OVERLAY_LOAD_NOT_SYNCHRONIZE);
	}
	else if(sys.trg & PAD_KEY_DOWN){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_second));
		Overlay_Load(FS_OVERLAY_ID(test_second), OVERLAY_LOAD_SYNCHRONIZE_2);
		Overlay_Load(FS_OVERLAY_ID(test_second_abc), OVERLAY_LOAD_SYNCHRONIZE_2);
	}
	else if(sys.trg & PAD_KEY_LEFT){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_itcm));
		Overlay_Load(FS_OVERLAY_ID(test_itcm), OVERLAY_LOAD_SYNCHRONIZE);
	}
	else if(sys.trg & PAD_KEY_UP){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_second_abc));
		Overlay_Load(FS_OVERLAY_ID(test_second_abc), OVERLAY_LOAD_SYNCHRONIZE_2);
	}

	//各ボタンによってオーバーレイされているファイル内の関数呼び出し
	if (sys.trg & PAD_BUTTON_A){
		test_overlay_func_1();
	}
	else if (sys.trg & PAD_BUTTON_B){
		test_overlay_func_2();
	}
	else if(sys.trg & PAD_BUTTON_Y){
		test_overlay_itcm();
	}
	else if(sys.trg & PAD_BUTTON_X){
		test_overlay_func_3();
	}
	
	if(sys.trg & PAD_BUTTON_START){
		sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
		TCB_Delete(tcb);
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief   松田デバッグ処理、呼び出し口
 */
//--------------------------------------------------------------
void DebugMatsudaInit(FIELDSYS_WORK *fsys)
{
	DMATSU_WORK *dm;
	BMPLIST_HEADER list_h;
	
	dm = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(DMATSU_WORK));
	memset(dm, 0, sizeof(DMATSU_WORK));
	
	//BMPウィンドウ生成
	GF_BGL_BmpWinAdd(fsys->bgl, &dm->bmpwin, 
		FLD_MBGFRM_FONT, 1, 1, 19, 22, 13, 1);
	dm->fsys = fsys;
	
	dm->listmenu = BMP_MENULIST_Create(LIST_MENU_MAX, HEAPID_BASE_DEBUG);

	//文字列リスト作成
	{
		MSGDATA_MANAGER *man;
		STRBUF * str_buf;
		int i;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
			NARC_msg_debug_matsu_dat, HEAPID_BASE_DEBUG);
		
		for(i = 0; i < LIST_MENU_MAX; i++){
			BMP_MENULIST_AddArchiveString(dm->listmenu, man, DebugMenuParamList[i].str_id, 
				DebugMenuParamList[i].param);
		}
		
		MSGMAN_Delete(man);
	}
	
	list_h = DebugMenuListHeader;
	list_h.win = &dm->bmpwin;
    list_h.list = dm->listmenu;
	dm->lw = BmpListSet(&list_h, 0, 0, HEAPID_BASE_DEBUG);
	
	GF_BGL_BmpWinOn(&dm->bmpwin);
	
	TCB_Add(DM_MenuMain, dm, 10);
}

//--------------------------------------------------------------
/**
 * @brief   松田用デバッグメニューリスト選択
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		デバッグ用松田ワークへのポインタ
 */
//--------------------------------------------------------------
static void DM_MenuMain(TCB_PTR tcb, void *work)
{
	DMATSU_WORK *dm = work;
	u32	ret;

	ret = BmpListMain(dm->lw);
	switch(dm->main_seq){
	case 0:
		dm->main_seq++;
		break;
	case 1:
		switch(ret){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			DM_MenuExit(dm);
			TCB_Delete(tcb);
			sys_FreeMemoryEz(dm);
			FieldSystemProc_SeqHoldEnd();
			return;
		default:
			{
				pDMFunc func = (pDMFunc)ret;

				DM_MenuExit(dm);
				TCB_Delete(tcb);
				func(dm);
				return;
			}
			break;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   松田用デバッグメニューリストを閉じる
 * @param   dm		デバッグ用松田ワークへのポインタ
 */
//--------------------------------------------------------------
static void DM_MenuExit(DMATSU_WORK *dm)
{
	BMP_MENULIST_Delete(dm->listmenu);
	BmpListExit(dm->lw, NULL, NULL);

	GF_BGL_BmpWinOff(&dm->bmpwin);
	GF_BGL_BmpWinDel(&dm->bmpwin);
}

static void TestOverlaySet(DMATSU_WORK *dm)
{
	TCB_Add(TestOverlayStart, dm, 20);
}

extern void BattleSystemProc(void);
static void TestSet(DMATSU_WORK *dm)
{
#if 0
	sys.mainSys_sequence = 5;//SEQ_EXIT;
	sys.pReturnProc = BattleSystemProc;
	//FieldSysWork.general_seqno = 0;
#else
//	if(sys.trg & START_BUTTON){
		sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
//		TCB_Delete(tcb);
		FieldSystemProc_SeqHoldEnd();
		return;
//	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：演技力部門開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ActingStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_ACTIN);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ビジュアル部門開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_VisualStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_VISUAL);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：イメージクリップ＞ビジュアル部門開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ClipVisualStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_CLIP_VISUAL);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ダンス部門開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 0;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ダンス部門開始(全ての四分音符でダンス)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceNoneLimitStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 2;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ダンス部門開始(ローテーションあり)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceRotatinOn(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ダンス部門開始(ローテーションなし)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceRotationOff(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 1;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：ダンス部門開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ContestSioStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 0;
	EventSet_Script(dm->fsys, SCRID_CONNECT_CONTEST, NULL );
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト：結果発表開始
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ResultStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_RESULT);
}

//--------------------------------------------------------------
/**
 * @brief   
 * @param   dm		
 */
//--------------------------------------------------------------
static void DM_SysFlagON_Style(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STYLE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Style(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STYLE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Beautiful(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_BEAUTIFUL);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Beautiful(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_BEAUTIFUL);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Cute(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CUTE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Cute(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CUTE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Clever(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CLEVER);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Clever(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CLEVER);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Strong(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STRONG);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Strong(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STRONG);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルテスト
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void FieldParticleTest(DMATSU_WORK *dm);
static void TestTCB_Particle(TCB_PTR tcb, void *work);
static int TestParticle_Main(void);
static u32 sAllocTex(u32 size, BOOL is4x4comp);
static u32 sAllocTexPalette(u32 size, BOOL is4pltt);

typedef struct{
	PTC_PTR ptc;
	u8 seq;
	
}TEST_PARTICLE_WORK;

///戦闘パーティクルのカメラニア設定
#define BP_NEAR			(FX32_ONE)
///戦闘パーティクルのカメラファー設定
#define BP_FAR			(FX32_ONE * 900)

static void FieldParticleTest(DMATSU_WORK *dm)
{
	sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
	FieldSystemProc_SeqHoldEnd();
	
	{
		TEST_PARTICLE_WORK *tpw;
		
		tpw = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(TEST_PARTICLE_WORK));
		MI_CpuClear8(tpw, sizeof(TEST_PARTICLE_WORK));
		TCB_Add(TestTCB_Particle, tpw, 20);
	}
}

static void TestTCB_Particle(TCB_PTR tcb, void *work)
{
	TEST_PARTICLE_WORK *tpw = work;
	int heap_id = HEAPID_BASE_DEBUG;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;
	
	switch(tpw->seq){
	case 0:		//初期化
		Particle_SystemWorkInit();	//パーティクルシステム初期化
		tpw->seq++;
		break;
	case 1:		//パーティクルシステム作成
		heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE);
		tpw->ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, 
			PARTICLE_LIB_HEAP_SIZE, TRUE, heap_id);
		camera_ptr = Particle_GetCameraPtr(tpw->ptc);
		GFC_SetCameraClip(BP_NEAR, BP_FAR, camera_ptr);

		tpw->seq++;
		break;
	case 2:		//リソース読み込み＆登録
		resource = Particle_ArcResourceLoad(
			ARC_PARTICLE_DATA, NARC_particledata_w_001_spa, heap_id);
		Particle_ResourceSet(tpw->ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
		
		tpw->seq++;
		break;
	case 3:		//パーティクル生成
		Particle_CreateEmitterCallback(tpw->ptc, 0, NULL, NULL);
		break;
	case 4:		//パーティクル実行
		if(TestParticle_Main() == FALSE){
			tpw->seq++;
		}
		break;
	case 5:		//パーティクルシステム破棄
		heap = Particle_HeapPtrGet(tpw->ptc);
		Particle_SystemExit(tpw->ptc);
		sys_FreeMemoryEz(heap);
		
		tpw->seq++;
		break;
	default:
		sys_FreeMemoryEz(tpw);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   戦闘用パーティクルシステム・メイン関数(計算・描画処理などを実行)
 *
 * @param   ptc		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
static int TestParticle_Main(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;
	
	GF_G3X_Reset();


	if(Particle_GetActionNum() == 0){
		return FALSE;
	}
	

	draw_num = Particle_DrawAll();	//パーティクル描画

	if(draw_num > 0){
		//パーティクルの描画が終了したので、再びソフトウェアスプライト用カメラに設定
		GF_G3X_Reset();
	}

	Particle_CalcAll();	//パーティクル計算

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   テクスチャVRAMアドレスを返すためのコールバック関数
 *
 * @param   size		テクスチャサイズ
 * @param   is4x4comp	4x4圧縮テクスチャであるかどうかのフラグ(TRUE=圧縮テクスチャ)
 *
 * @retval  読み込みを開始するVRAMのアドレス
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	GF_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	Particle_LnkTexKeySet(key);		//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}

//--------------------------------------------------------------
/**
 * @brief	テクスチャパレットVRAMアドレスを返すためのコールバック関数
 *
 * @param	size		テクスチャサイズ
 * @param	is4pltt		4色パレットであるかどうかのフラグ
 *
 * @retval	読み込みを開始するVRAMのアドレス
 *
 * direct形式のテクスチャの場合、SPL_LoadTexPlttByCallbackFunctionは
 * コールバック関数を呼び出しません。
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, NNS_GFD_ALLOC_FROM_LOW);
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "パーティクルでパレットの確保が出来ません！\n");
	}
	Particle_PlttLnkTexKeySet(key);	//リンクドリストを使用しているのでキー情報をセット
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}

#endif	// PM_DEBUG +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


