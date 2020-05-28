//==============================================================================
/**
 * @file	pm_overlay.c
 * @brief	オーバーレイ制御
 * @author	matsuda
 * @date	2005.06.16(木)
 */
//==============================================================================
#include <nitro.h>
#include <nitro/fs.h>
#include "common.h"
#include "pm_overlay.h"


#if 0
NitroStaticInitを使用するには
/*
 * NitroStaticInit() を static initializer に指定するには
 * このヘッダをインクルードします.
 */
#include <nitro/sinit.h>

#endif


//==============================================================================
//	定数定義
//==============================================================================
///各メモリエリアで、一度にオーバーレイ出来る数
#define AREA_WORK_MAX		(8)

//--------------------------------------------------------------
//	デバッグ用定義
//--------------------------------------------------------------
#ifdef PM_DEBUG
///定義が有効の場合はオーバーレイのアンロード実行時にアンロードした領域をクリアする
#define DEBUG_OVELAY_UNLOAD_CLEAR
#endif


//==============================================================================
//	構造体定義
//==============================================================================
typedef struct{
	FSOverlayID loaded_id;
	BOOL loaded;
}OVERLAY_WORK;

typedef struct{
	OVERLAY_WORK main[AREA_WORK_MAX];
	OVERLAY_WORK itcm[AREA_WORK_MAX];
	OVERLAY_WORK dtcm[AREA_WORK_MAX];
}OVERLAY_SYSTEM;

//==============================================================================
//	グローバル変数宣言
//==============================================================================
static OVERLAY_SYSTEM OverlaySys;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void Overlay_Unload(OVERLAY_WORK *ovwork);
static BOOL Overlay_CrossAreaCheck(const FSOverlayID id);
static OVERLAY_WORK * Overlay_AreaOverlayWorkPtrGet(int memory_area);
static BOOL Overlay_RamStartEndAdressGet(const FSOverlayID id, u32 *start, u32 *end);
static BOOL load_overlay_high(MIProcessor target, FSOverlayID id);
static BOOL load_overlay_middle(MIProcessor target, FSOverlayID id);
static BOOL load_overlay_low(MIProcessor target, FSOverlayID id);
void Overlay_SystemWorkInit(void);
void Overlay_Init(void);
void Overlay_UnloadID(const FSOverlayID id);
void Overlay_UnloadMain(void);
void Overlay_UnloadItcm(void);
void Overlay_UnloadDtcm(void);
void Overlay_UnloadAll(void);
int Overlay_MemoryAreaGet(const FSOverlayID id);
BOOL Overlay_Load(const FSOverlayID id, int load_type);
BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work);

//--------------------------------------------------------------
/**
 * @brief   オーバーレイ制御のシステムワークをクリアする
 */
//--------------------------------------------------------------
void Overlay_SystemWorkInit(void)
{
	MI_CpuClear32(&OverlaySys, sizeof(OVERLAY_SYSTEM));
}

//--------------------------------------------------------------
/**
 * @brief   現在読み込んでいる全てのオーバーレイをアンロードしてから、システムワークをクリアする
 */
//--------------------------------------------------------------
void Overlay_Init(void)
{
	Overlay_UnloadAll();
	Overlay_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief   オーバーレイをアンロードします
 * @param   ovwork		オーバーレイワークへのポインタ
 */
//--------------------------------------------------------------
static void Overlay_Unload(OVERLAY_WORK *ovwork)
{
	//現在読み込まれているオーバーレイモジュールをアンロードします
	BOOL ret;
#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	u32 start, end;
#endif

	GF_ASSERT(ovwork->loaded == TRUE);

#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	//アンロードしたオーバーレイ領域を0クリアするために解放する前にアドレス取得
	Overlay_RamStartEndAdressGet(ovwork->loaded_id, &start, &end);
#endif

	ret = FS_UnloadOverlay(MI_PROCESSOR_ARM9, ovwork->loaded_id);
	OS_Printf("overlay 解放しました id = 0x%08X(10進数：%d)\n", 
		ovwork->loaded_id, ovwork->loaded_id);
	GF_ASSERT(ret == TRUE);
	ovwork->loaded = FALSE;

#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	//アンロードしたオーバーレイ領域をクリアする
	OS_TPrintf("overlay unloade start address = 0x%08X\n", start);
	OS_TPrintf("overlay unloade end address = 0x%08X\n", end);
	//MI_CpuClear8((void*)start, end - start);
	MI_CpuFill8((void*)start, 0xff, end - start);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   指定したオーバーレイIDのオーバーレイをアンロードします
 *
 * @param   id		オーバーレイID
 *
 * ロードされていない場合は何もしません
 */
//--------------------------------------------------------------
void Overlay_UnloadID(const FSOverlayID id)
{
	OVERLAY_WORK *ovwork;
	int memory_area;
	int i;
	
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == TRUE && ovwork[i].loaded_id == id){
			//現在読み込まれているオーバーレイモジュールをアンロードします
			Overlay_Unload(&ovwork[i]);
			return;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインメモリに展開されているオーバーレイを全てアンロードします
 */
//--------------------------------------------------------------
void Overlay_UnloadMain(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.main[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.main[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ITCMに展開されているオーバーレイを全てアンロードします
 */
//--------------------------------------------------------------
void Overlay_UnloadItcm(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.itcm[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.itcm[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   DTCMに展開されているオーバーレイを全てアンロードします
 */
//--------------------------------------------------------------
void Overlay_UnloadDtcm(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.dtcm[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.dtcm[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   指定したオーバーレイIDと同じメモリエリアに展開されているオーバーレイ領域を
 *          全てアンロードします
 *
 * @param   id		オーバーレイID
 */
//--------------------------------------------------------------
void Overlay_UnloadSameArea(const FSOverlayID id)
{
	int memory_area;
	
	memory_area = Overlay_MemoryAreaGet(id);
	switch(memory_area){
	case OVERLAY_AREA_MAIN:
		Overlay_UnloadMain();
		break;
	case OVERLAY_AREA_ITCM:
		Overlay_UnloadItcm();
		break;
	case OVERLAY_AREA_DTCM:
		Overlay_UnloadDtcm();
		break;
	default:
		GF_ASSERT(0);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   現在読み込んでいるオーバーレイへのアンロードを、全ての領域に対して行う
 */
//--------------------------------------------------------------
void Overlay_UnloadAll(void)
{
	Overlay_UnloadMain();
	Overlay_UnloadItcm();
	Overlay_UnloadDtcm();
}

//--------------------------------------------------------------
/**
 * @brief   指定オーバーレイIDの展開先メモリエリアを取得する
 * @param   id		オーバーレイID
 * @retval  展開先メモリエリア(OVERLAY_AREA_???)
 */
//--------------------------------------------------------------
int Overlay_MemoryAreaGet(const FSOverlayID id)
{
	FSOverlayInfo info;
	BOOL ret;
	u32 ram_address;
	
	ret = FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id);
	GF_ASSERT(ret == TRUE);
	
	ram_address = (u32)FS_GetOverlayAddress(&info);
	if(ram_address <= HW_ITCM_END && ram_address >= HW_ITCM_IMAGE){
		return OVERLAY_AREA_ITCM;
	}
	else if(ram_address <= HW_DTCM_END && ram_address >= HW_DTCM){
		return OVERLAY_AREA_DTCM;
	}
	return OVERLAY_AREA_MAIN;
}

//--------------------------------------------------------------
/**
 * @brief   指定したオーバーレイをロードする
 *
 * @param   id				ロードするオーバーレイID
 * @param   load_type		ロードタイプ(OVERLAY_LOAD_???)
 *
 * @retval  TRUE:成功
 * @retval  FALSE:失敗
 *
 * 複数のオーバーレイを実行している時、領域が被った場合はオーバーレイは失敗します。
 * (デバッグ中はGF_ASSERTで停止します)
 *
 * ロードはFS_SetDefaultDMA(or FS_Init)で設定されている方法で行います。
 * 使用するDMA,CPUを変更したい場合は、この関数実行前にFS_SetDefaultDMAで設定を行ってください。
 * ITCM,DTCMへのロードは内部で一時的にCPUに変更してロードを行います。(ロード後は元の設定に戻します)
 */
//--------------------------------------------------------------
BOOL Overlay_Load(const FSOverlayID id, int load_type)
{
	BOOL ret;
	int memory_area;
	u32 dma_bak = FS_DMA_NOT_USE;
	OVERLAY_WORK *ovwork;
	int i;
	
//	Overlay_Unload(memory_area);	//同領域を使用しているオーバーレイをアンロード
	if(Overlay_CrossAreaCheck(id) == FALSE){
		return FALSE;
	}

	//空きワークサーチ
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == FALSE){
			ovwork = &ovwork[i];
			ovwork->loaded = TRUE;
			ovwork->loaded_id = id;
			break;
		}
	}
	if(i >= AREA_WORK_MAX){
		GF_ASSERT(0);	//同メモリエリア内にオーバーレイ出来る数を超えている
		return FALSE;
	}
	
	if(memory_area == OVERLAY_AREA_ITCM || memory_area == OVERLAY_AREA_DTCM){
		//TCMへの書き込みはDMAでは出来ないので一時的にCPUへ変更
		dma_bak = FS_SetDefaultDMA(FS_DMA_NOT_USE);
	}
	
	switch(load_type){
	case OVERLAY_LOAD_SYNCHRONIZE:
		ret = load_overlay_high(MI_PROCESSOR_ARM9, id);
		break;
	case OVERLAY_LOAD_SYNCHRONIZE_2:
		ret = load_overlay_middle(MI_PROCESSOR_ARM9, id);
		break;
	case OVERLAY_LOAD_NOT_SYNCHRONIZE:
		ret = load_overlay_low(MI_PROCESSOR_ARM9, id);
		break;
	default:		//不明なロードタイプ
		GF_ASSERT(0);
		return FALSE;
	}

	if(memory_area == OVERLAY_AREA_ITCM || memory_area == OVERLAY_AREA_DTCM){
		//一時的に変更したのを元に戻す
		FS_SetDefaultDMA(dma_bak);
	}

	if(ret == FALSE){	//ロード失敗
		OS_Printf("overlay 0x%08X is not available!\n", id);
		GF_ASSERT(0);
		return FALSE;
	}

	OS_Printf("overlay ロードしました id = 0x%08X(10進数:%d)\n", id, id);
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   指定したオーバーレイIDの領域が現在展開されているオーバーレイ領域とアドレスが
 *          被っていないかチェックする
 *
 * @param   id		オーバーレイID
 *
 * @retval  TRUE:被っていない。　FALSE:被っている(エラーの場合も有)
 */
//--------------------------------------------------------------
static BOOL Overlay_CrossAreaCheck(const FSOverlayID id)
{
	int memory_area;
	u32 start, end, c_start, c_end;
	BOOL ret;
	OVERLAY_WORK *ovwork;
	int i;
	
	ret = Overlay_RamStartEndAdressGet(id, &start, &end);
	if(ret == FALSE){
		return FALSE;
	}
	
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == TRUE){
			ret = Overlay_RamStartEndAdressGet(ovwork[i].loaded_id, &c_start, &c_end);
			if(ret == TRUE){
				if((start >= c_start && start < c_end) || (end > c_start && end <= c_end)
						|| (start <= c_start && end >= c_end)){
					OS_Printf("オーバーレイ領域に重複が発生しました！\n");
					OS_Printf("展開済みID=%d、新規に展開しようとしたID=%d\n", 
						ovwork[i].loaded_id, id);
					GF_ASSERT(0);
					return FALSE;
				}
			}
		}
	}
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   指定メモリエリアが参照するオーバーレイワークの先頭アドレスを取得する
 * @param   memory_area		メモリエリア(OVERLAY_AREA_???)
 * @retval  指定メモリに対応したオーバーレイワークの先頭アドレス
 */
//--------------------------------------------------------------
static OVERLAY_WORK * Overlay_AreaOverlayWorkPtrGet(int memory_area)
{
	OVERLAY_WORK *ovwork;
	
	switch(memory_area){
	case OVERLAY_AREA_MAIN:
	default:
		ovwork = OverlaySys.main;
		break;
	case OVERLAY_AREA_ITCM:
		ovwork = OverlaySys.itcm;
		break;
	case OVERLAY_AREA_DTCM:
		ovwork = OverlaySys.dtcm;
		break;
	}
	return ovwork;
}

//--------------------------------------------------------------
/**
 * @brief   指定オーバーレイIDのロード開始アドレスとロード終了アドレスを取得する
 *
 * @param   id			オーバーレイID
 * @param   start		取得したロード開始アドレス代入先
 * @param   end			取得したロード終了アドレス代入先
 *
 * @retval  TRUE:正常終了。　FALSE:失敗
 */
//--------------------------------------------------------------
static BOOL Overlay_RamStartEndAdressGet(const FSOverlayID id, u32 *start, u32 *end)
{
	FSOverlayInfo info;
	BOOL ret;
	
	ret = FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id);
	if(ret == FALSE){
		GF_ASSERT(0);
		return FALSE;
	}
	
	*start = (u32)FS_GetOverlayAddress(&info);
	*end = *start + FS_GetOverlayTotalSize(&info);
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   全てを同期的に実行
 *
 * @param   target		ロードする対象（ARM9プロセッサ/ARM7プロセッサ）
 * @param   id			オーバーレイID
 *
 * @retval  TRUE:成功
 * @retval  FALSE:失敗
 */
//--------------------------------------------------------------
static BOOL load_overlay_high(MIProcessor target, FSOverlayID id)
{
	return FS_LoadOverlay(target, id);
}

//--------------------------------------------------------------
/**
 * @brief   部分的に手作業で実行 (同期的)
 *
 * @param   target		ロードする対象（ARM9プロセッサ/ARM7プロセッサ）
 * @param   id			オーバーレイID
 *
 * @retval  TRUE:成功
 * @retval  FALSE:失敗
 */
//--------------------------------------------------------------
static BOOL load_overlay_middle(MIProcessor target, FSOverlayID id)
{
	FSOverlayInfo info;

	if(!FS_LoadOverlayInfo(&info, target, id)){
		return FALSE;
	}
	if(!FS_LoadOverlayImage(&info)){
		return FALSE;
	}
	FS_StartOverlay(&info);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   全てを手作業で実行 (非同期的)
 *
 * @param   target		ロードする対象（ARM9プロセッサ/ARM7プロセッサ）
 * @param   id			オーバーレイID
 *
 * @retval  TRUE:成功
 * @retval  FALSE:失敗
 */
//--------------------------------------------------------------
static BOOL load_overlay_low(MIProcessor target, FSOverlayID id)
{
	FSOverlayInfo info;
	
	//オーバーレイモジュールの情報をロードします
	if (!FS_LoadOverlayInfo(&info, target, id)){
		return FALSE;
	}
	
	{
		FSFile file;
		
		//FSFile構造体を初期化します
		FS_InitFile(&file);
		(void)FS_LoadOverlayImageAsync(&info, &file);
		(void)FS_WaitAsync(&file);
		(void)FS_CloseFile(&file);
	}
	FS_StartOverlay(&info);
	return TRUE;
}

//--------------------------------------------------------------
/**
 */
//--------------------------------------------------------------
BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work)
{
	if (!Overlay_Load(id, load_type)) {
		return FALSE;
	}
	func(work);

	Overlay_UnloadID(id);
	return TRUE;
}

