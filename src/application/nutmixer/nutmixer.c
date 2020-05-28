/**
 *	@file	nutmixer.c
 *	@brief	木の実まぜまぜ料理
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"

#include "nmix_mseq.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_porutogame1.h"


//プロトタイプ宣言　ローカル
//================================================================
///オーバーレイプロセス
static PROC_RESULT NutMixerProc_Init( PROC *proc,int *seq);
static PROC_RESULT NutMixerProc_Main( PROC *proc,int *seq);
static PROC_RESULT NutMixerProc_End( PROC *proc,int *seq);

const PROC_DATA NutMixerProcData = {
	NutMixerProc_Init,
	NutMixerProc_Main,
	NutMixerProc_End,
	NO_OVERLAY_ID,
};



//------------------------------------------------------------------
/**
 * @brief	サブプロセス呼び出し処理
 * @param	proc	サブプロセスポインタを保持するワークへのポインタ
 */
//------------------------------------------------------------------
BOOL NutMixerProcCall(PROC ** proc)
{
	if (*proc) {
		if (ProcMain(*proc)) {
			PROC_Delete(*proc);
			*proc = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 *	@brief	ナッツミキサー　プロセス初期化
 */
static PROC_RESULT	NutMixerProc_Init(PROC* proc,int *seq)
{
	NUTMIXER_WORK* wk = NULL;
	NUTMIXER_PARAM* pp = (NUTMIXER_PARAM*)PROC_GetParentWork(proc);
	
	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_NUT_MIXER,0x4000);
	wk = PROC_AllocWork(proc,sizeof(NUTMIXER_WORK),HEAPID_NUT_MIXER);
	MI_CpuClear8(wk,sizeof(NUTMIXER_WORK));

	wk->heapID = HEAPID_NUT_MIXER;

	//引継ぎパラメータ
	wk->param = pp;
	

	// バッグカーソル位置記憶領域初期化
	wk->bag_cursor = MyItem_BagCursorAlloc( wk->heapID );

	//動作モード取得
	if(pp->sys_mode == 1){
		wk->comm_f = TRUE;
	}

	return PROC_RES_FINISH;
}

/**
 *	@brief	ナッツミキサー　プロセスメイン
 */
static PROC_RESULT	NutMixerProc_Main(PROC* proc,int *seq)
{
	int	old_seq;
	NUTMIXER_WORK* wk = PROC_GetWork(proc);
	NUTMIXER_PARAM* pp = (NUTMIXER_PARAM*)PROC_GetParentWork(proc);

	old_seq = *seq;
	switch(*seq){
	case NMSEQ_BAG_MAIN:
		*seq =  NMixMainSeq_Bag(wk,&(wk->m_seq));
		break;
	case NMSEQ_GAME_CALL:
		*seq = NMixMainSeq_GameCall(wk,&(wk->m_seq));
		break;
	case NMSEQ_GAME_WAIT:
		*seq = NMixMainSeq_GameWait(wk,&(wk->m_seq));
		break;
	case NMSEQ_GAME_END:
		*seq = NMixMainSeq_GameEnd(wk,&(wk->m_seq));
		break;
	case NMSEQ_MAIN_END:
		return PROC_RES_FINISH;
	}

	if(old_seq != *seq){
		wk->m_seq = 0;
	}

	return PROC_RES_CONTINUE;
}

/**
 *	@brief	ナッツミキサー　プロセス終了
 */
static PROC_RESULT NutMixerProc_End(PROC* proc,int *seq)
{
	int	heapID = 0;
	NUTMIXER_WORK* wk = PROC_GetWork(proc);
	NUTMIXER_PARAM* pp = (NUTMIXER_PARAM*)PROC_GetParentWork(proc);


	//ワークエリア解放
	heapID = wk->heapID;

	// バッグカーソル位置記憶領域破棄
	sys_FreeMemoryEz( wk->bag_cursor );

	MI_CpuClear8(wk,sizeof(NUTMIXER_WORK));
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(heapID);

	sys_DeleteHeap(heapID);
	return PROC_RES_FINISH;
}

//====================================================================
//ローカルサブ関数
//====================================================================

