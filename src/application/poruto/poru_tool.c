/**
 *	@file	poru_tool.c
 *	@brief	ポルトケース＆デモコントローラ(常駐)
 *	@date	06.03.01
 *	@author	Miyuki Iwasawa
 */

#include "common.h"
#include "system/procsys.h"
#include "system/msgdata.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/window.h"
#include "gflib/number_str.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"

#include "application/poru_tool.h"
#include "savedata/poruto_util.h"
#include "porusys.h"
#include "porudemo.h"

//データ定義
#include "porudata.dat"

#define BUFSIZ_PLVMSG	(10)

typedef enum{
 SEQ_CASE_INIT,
 SEQ_CASE_WAIT,
 SEQ_PSEL_WAIT,
 SEQ_PST_WAIT,
 SEQ_DEMO_CALL,
 SEQ_DEMO_WAIT,
 SEQ_COND_CALL,
 SEQ_COND_WAIT,
 SEQ_FINISH,
};

///ポルトコントローラメインワーク
typedef struct _PORUTO_MAIN_DAT{
	int heapID;	///<ヒープID
	int seq;	///<シーケンス制御
	
	u8	pokePos;
	u8	pokePara;
	u16	pokeNo;
	PORUTO_PARAM* param;

	void *app_work;	///<サブプロセス用ワーク
	PROC*	proc;	///<サブプロセスワーク
}PORUTO_MAIN_DAT;

///オーバーレイプロセス定義
static PROC_RESULT PoruSys_Init(PROC* proc,int* seq);
static PROC_RESULT PoruSys_Main(PROC* proc,int* seq);
static PROC_RESULT PoruSys_End(PROC* proc,int* seq);

const PROC_DATA PorutoSysProcData = {
	PoruSys_Init,
	PoruSys_Main,
	PoruSys_End,
	NO_OVERLAY_ID,
};

static void PoruSys_SaveDataPut(PORUTO_MAIN_DAT* wk);
//==============================================================
//サブシーケンスプロトタイプ
static int seq_CaseInit(PORUTO_MAIN_DAT* wk);
static int seq_CaseWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeListWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeStatusWait(PORUTO_MAIN_DAT* wk);
static int seq_PoruDemoCall(PORUTO_MAIN_DAT* wk);
static int seq_PoruDemoWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeConditionCall(PORUTO_MAIN_DAT* wk);
static int seq_PokeConditionWait(PORUTO_MAIN_DAT* wk);

/**
 *	@brief	ポルトシステム呼び出しワークデータ作成
 *
 *	＊必ず PorutoSys_ReleaseCallWork()関数で解放すること！
 */
PORUTO_PARAM* PorutoSys_CreateCallWork(SAVEDATA* savedata,int heapID)
{
	PORUTO_PARAM* wk;
	PORUTO_DATA* dat;
	PORU_LIST* pl;
	WORDSET* wset;
//	STRBUF	*lvbuf;
	u8	param[PORUTO_PARAID_NUM];
	u8 i = 0,ct = 0,j = 0;
	u8	flags = 0;
	
	wk = sys_AllocMemory(heapID,sizeof(PORUTO_PARAM));
	MI_CpuClear8(wk,sizeof(PORUTO_PARAM));

	//セーブデータブロック取得
	wk->poruSave = SaveData_GetPorutoBlock(savedata);
	wk->mySave = SaveData_GetMyStatus(savedata);
	wk->ppSave = SaveData_GetTemotiPokemon(savedata);
	wk->itemSave = SaveData_GetMyItem(savedata);
	wk->configSave = SaveData_GetConfig(savedata);

#if 0
	{
		MSGDATA_MANAGER* msgman;
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
				NARC_msg_poruto_select_dat,heapID);
		lvbuf = MSGMAN_AllocString(msgman,mes_p_select_04_01);
		MSGMAN_Delete(msgman);
	}
#endif
	dat = PorutoData_AllocWork(heapID);
	wset = WORDSET_CreateEx(1,WORDSET_DEFAULT_BUFLEN,heapID);	


	//ポルトデータ取得
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PORUTO_GetData(wk->poruSave,i,dat);

		if(!PorutoData_IsEnable(dat)){
			continue;
		}
		PorutoData_GetParamArray(dat,param);

		//各種データ取得
		pl = &(wk->list[ct]);
		
		pl->id = i;
		pl->level = PorutoData_GetLevel(dat);
		pl->flavor = param[PORUTO_PARAID_FLAVOR];
		pl->taste = param[PORUTO_PARAID_TASTE];

#if 0
		pl->lvbuf = STRBUF_Create(BUFSIZ_PLVMSG,heapID);

		//ポルトレベル文字列展開
		WORDSET_RegisterNumber(wset,0,pl->level,2,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr(wset,pl->lvbuf,lvbuf);
#endif
		flags = 1;
		for(j = 0;j < 5;j++){
			if(param[j+PORUTO_PARAID_SPICY]){
				pl->flags |= flags;
			}
			flags <<= 1;
		}
		pl->valid = pl->view = 1;
		pl->myid = ct++;
		pl->next = pl->prev = 0xFF;
	}

	//ワーク解放
	WORDSET_Delete(wset);
	sys_FreeMemoryEz(dat);
//	STRBUF_Delete(lvbuf);
	
	wk->porunum = ct;	//ポルト初期数取得
	wk->ret_view = 5;	//ポルトケース初期ソートモード(ぜんぶ)
	return wk;
}

/**
 *	@brief	ポルトケース呼び出しワークを解放する
 */
void PorutoSys_ReleaseCallWork(PORUTO_PARAM* pp)
{
	int i;

#if 0
	for(i = 0;i < pp->porunum;i++){
		if(pp->list[i].lvbuf != NULL){
			STRBUF_Delete(pp->list[i].lvbuf);
		}
	}
#endif
	sys_FreeMemoryEz(pp);
}

//------------------------------------------------------
/**
 *	@brief	サブプロセス呼び出し処理
 *	@param	proc	サブプロセスポインタ
 */
//------------------------------------------------------
static BOOL PorutoSysProcCall(PROC** proc)
{
	if(*proc){
		if(ProcMain(*proc)){
			PROC_Delete(*proc);
			*proc = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 *	@brief	ポルトシステム呼び出し
 **/
static PROC_RESULT PoruSys_Init(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = NULL;
	void* pp = PROC_GetParentWork(proc);

	//ワークエリア取得
	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_PORUTO,0x1000);
	
	wk = PROC_AllocWork(proc,sizeof(PORUTO_MAIN_DAT),HEAPID_PORUTO);
	MI_CpuClear8(wk,sizeof(PORUTO_MAIN_DAT));

	//
	wk->heapID = HEAPID_PORUTO;
	//上位ワークポインタ保存
	wk->param = pp;

	return PROC_RES_FINISH;
}

/**
 *	@brief	ポルトコントローラメイン
 */
static PROC_RESULT PoruSys_Main(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = (PORUTO_MAIN_DAT*)PROC_GetWork(proc);

	switch(*seq){
	case SEQ_CASE_INIT:
		*seq = seq_CaseInit(wk);
		break;
	case SEQ_CASE_WAIT:
		*seq = seq_CaseWait(wk);
		break;
	case SEQ_PSEL_WAIT:
		*seq = seq_PokeListWait(wk);
		break;
	case SEQ_PST_WAIT:
		*seq = seq_PokeStatusWait(wk);
		break;
	case SEQ_DEMO_CALL:
		*seq = seq_PoruDemoCall(wk);
		break;
	case SEQ_DEMO_WAIT:
		*seq = seq_PoruDemoWait(wk);
		break;
	case SEQ_COND_CALL:
		*seq = seq_PokeConditionCall(wk);
		break;
	case SEQ_COND_WAIT:
		*seq = seq_PokeConditionWait(wk);
		break;
	case SEQ_FINISH:
		return PROC_RES_FINISH;
	}
	
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	ポルトコントローラ終了
 */
static PROC_RESULT	PoruSys_End(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = (PORUTO_MAIN_DAT*)PROC_GetWork(proc);

	//セーブデータ反映
	PoruSys_SaveDataPut(wk);

	//ワーク解放
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	sys_DeleteHeap(wk->heapID);
	return PROC_RES_FINISH;
}

/**
 *	@brief	ポルトセーブデータ書き出し
 */
static void PoruSys_SaveDataPut(PORUTO_MAIN_DAT* wk)
{
	u8 i = 0,flag = 0;
	PORU_LIST* pl;
	
	for(i = 0;i < wk->param->porunum;i++){
		pl = &wk->param->list[i];
		
		if(pl->del){	//データ削除
			PORUTO_DelData(wk->param->poruSave,pl->id);
			flag = 1;
		}
	}
	if(!flag){
		return;
	}
	//データ整理
	PORUTO_DataAdjust(wk->param->poruSave);
}

//============================================================
//サブシーケンス

/**
 *	@brief	ポルトケース初期化
 */
static int seq_CaseInit(PORUTO_MAIN_DAT* wk)
{
	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(porutocase);

	static const PROC_DATA CaseProcData = {
		PoruCase_Init,
		PoruCase_Main,
		PoruCase_End,
		FS_OVERLAY_ID(porutocase),
//		NO_OVERLAY_ID,
	};
	
	wk->proc = PROC_Create(&CaseProcData,wk->param,wk->heapID);
	return SEQ_CASE_WAIT;	
}

/**
 *	@brief	ポルトケース終了待ち
 */
static int seq_CaseWait(PORUTO_MAIN_DAT* wk)
{
	PLIST_DATA* pld;
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_CASE_WAIT;
	}
	//終了分岐
	if(wk->param->ret_mode == PCASE_RET_CANCEL){
		return SEQ_FINISH;
	}
	//リターンモードを一旦クリア
	wk->param->ret_mode = 0;

	//ポケモンリスト呼び出し
	pld = sys_AllocMemory( wk->heapID, sizeof(PLIST_DATA) );
	MI_CpuClear8( pld,sizeof(PLIST_DATA) );
	pld->pp = wk->param->ppSave;
	pld->myitem = wk->param->itemSave;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_PORUTO;
	pld->cfg = wk->param->configSave;

	wk->proc = PROC_Create(&PokeListProcData,pld,wk->heapID);
	wk->app_work = (void*)pld;

	return SEQ_PSEL_WAIT;
}

/**
 *	@brief	ポケモンリスト終了待ち
 */
static int seq_PokeListWait(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PLIST_DATA *pld;
	PSTATUS_DATA* psd;
	static const u8 PST_PageTbl[] = {
		PST_PAGE_CONDITION,	// 「コンディション」
		PST_PAGE_RET,			// 「もどる」
		PST_PAGE_MAX
	};
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_PSEL_WAIT;
	}
	
	//戻り値チェック
	pld = (PLIST_DATA*)wk->app_work;
	pos = pld->ret_sel;
	wk->pokePos = pos;	///手持ちナンバー保存
	sys_FreeMemoryEz(wk->app_work);
	
	if(pos == PL_SEL_POS_EXIT){
		return SEQ_CASE_INIT;	//ポルトケースに戻る
	}

	//ポケモンステータスを呼び出す
	//
	psd = sys_AllocMemory( wk->heapID, sizeof(PSTATUS_DATA) );

	psd->ppd  = wk->param->ppSave;
	psd->cfg = wk->param->configSave;
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = pos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = PST_MODE_PORUTO;
	psd->ev_contest = 1;
	psd->perap = NULL;
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet(psd,wk->param->mySave);

	wk->proc = PROC_Create(&PokeStatusProcData,pld,wk->heapID);
	
	wk->app_work = (void*)psd;
	return SEQ_PST_WAIT;
}

/**
 *	@brief	ポケモンステータス終了待ち
 */
static int seq_PokeStatusWait(PORUTO_MAIN_DAT* wk)
{
	PSTATUS_DATA* psd;
	u8	ret;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_PST_WAIT;
	}
	
	//戻り値チェック
	psd = (PSTATUS_DATA*)wk->app_work;
	ret = psd->ret_mode;
	
	//ポケモンが切り替えられたのをチェックする
	wk->pokePos = psd->pos;	///手持ちナンバー保存
	
	sys_FreeMemoryEz(wk->app_work);
	
	if(ret == PST_RET_CANCEL){
		return SEQ_CASE_INIT;	//ポルトケースに戻る
	}

	//選択されたポルトを消費する
	wk->param->list[wk->param->selID].del = 1;
	//リターンモードに1を格納
	wk->param->ret_mode = 1;
	//ポルトを与えるデモを呼び出す
	//
	return SEQ_DEMO_CALL;
}

/**
 *	@brief	ポルトデモ呼び出し
 */
static int seq_PoruDemoCall(PORUTO_MAIN_DAT* wk)
{
	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(porutocase);
	static const PROC_DATA DemoProcData = {
		PoruDemo_Init,
		PoruDemo_Main,
		PoruDemo_End,
		FS_OVERLAY_ID(porutocase),
//		NO_OVERLAY_ID,
	};
	PORUDEMO_PARAM* prm;
	
	prm = sys_AllocMemory(wk->heapID,sizeof(PORUDEMO_PARAM));
	MI_CpuClear8(prm,sizeof(PORUDEMO_PARAM));
	
	//引渡しパラメータ取得
	prm->flavor = wk->param->list[wk->param->selID].flavor;
	prm->poruto = PORUTO_GetDataAlloc(wk->param->poruSave,
		wk->param->list[wk->param->selID].id,wk->heapID);
	prm->pp = PokeParty_GetMemberPointer(wk->param->ppSave,wk->pokePos);
	prm->msg_spd = CONFIG_GetMsgPrintSpeed(wk->param->configSave);
	prm->win_type = CONFIG_GetWindowType(wk->param->configSave);

	//プロセスコール
	wk->proc = PROC_Create(&DemoProcData,prm,wk->heapID);
	wk->app_work = prm;

	return SEQ_DEMO_WAIT;
}

/**
 *	@brief	ポルトデモ終了待ち
 */
static int seq_PoruDemoWait(PORUTO_MAIN_DAT* wk)
{
	PORUDEMO_PARAM* prm;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_DEMO_WAIT;
	}
	//ワーク解放
	prm = (PORUDEMO_PARAM*)wk->app_work;
	sys_FreeMemoryEz(prm->poruto);
	sys_FreeMemoryEz(prm);
	return SEQ_COND_CALL;
}

/**
 *	@brief	コンディション呼び出し
 */
static int seq_PokeConditionCall(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PSTATUS_DATA* psd;
	PORUTO_DATA*	dat;

	static const u8 PST_PageTbl[] = {
		PST_PAGE_CONDITION,	// 「コンディション」
		PST_PAGE_MAX
	};
	
	//ポケモンステータスを呼び出す(コンディション変化)
	//
	psd = sys_AllocMemory( wk->heapID, sizeof(PSTATUS_DATA) );
	//ポルトパラメータをポケモンに反映
	dat = PORUTO_GetDataAlloc(wk->param->poruSave,
			wk->param->list[wk->param->selID].id,wk->heapID);

	psd->ppd  = wk->param->ppSave;
	psd->cfg = wk->param->configSave;
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = wk->pokePos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = PST_MODE_CONDITION;
	psd->poruto  = dat;
	psd->ev_contest = 1;
	psd->perap = NULL;
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet(psd,wk->param->mySave);

	wk->proc = PROC_Create(&PokeStatusProcData,psd,wk->heapID);
	
	wk->app_work = (void*)psd;
	return SEQ_COND_WAIT;
}

/**
 *	@brief	コンディション表示終了待ち
 */
static int seq_PokeConditionWait(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PSTATUS_DATA* psd;
	PORUTO_DATA*	dat;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_COND_WAIT;
	}
	psd = (PSTATUS_DATA*)wk->app_work;
	sys_FreeMemoryEz(psd->poruto);
	sys_FreeMemoryEz(wk->app_work);

#if 0
	//ポルトパラメータをポケモンに反映
	dat = PORUTO_GetDataAlloc(wk->param->poruSave,
			wk->param->list[wk->param->selID].id,wk->heapID);
	PoruSys_PoruPara2Poke(dat,
		PokeParty_GetMemberPointer(wk->param->ppSave,wk->pokePos));
	sys_FreeMemoryEz(dat);
#endif

	//ポルトリストへ戻る
	return SEQ_CASE_INIT;
}

//======================================================
//外部公開関数
//======================================================

/**
 *	@brief	ポルトデータと性格からそのポルトを好きか嫌いか返す
 */
PORU_FAVOLITE PoruSys_IsFavolite(PORUTO_DATA *dat,u8 seikaku)
{
	u8 prm[PORUTO_PARAID_NUM];
	u8	flavor,suki,kirai;
	u8	sid,kid;
	
	sid = poruto_f2char[seikaku][0];
	kid = poruto_f2char[seikaku][1];

	if(sid == PORUTO_FTYPE_MIX){
		//好き嫌いなし
		return PORU_FAVOLITE_NRM;
	}

	//ポルトパラメータ取得
	PorutoData_GetParamArray(dat,prm);
	flavor = prm[PORUTO_PARAID_FLAVOR];

	suki = prm[sid+PORUTO_PARAID_SPICY];
	kirai = prm[kid+PORUTO_PARAID_SPICY];

	if(suki == kirai){
		return PORU_FAVOLITE_NRM;
	}
	if(suki > kirai){
		return PORU_FAVOLITE_SUKI;
	}else{
		return PORU_FAVOLITE_KIRAI;
	}
}

/**
 *	@brief	性格からどの味が好きか嫌いか返す
 *
 *	@param	ポケモンの性格No
 *	@param	mode	PORU_FAVOLITE_SUKI:好きな味タイプを返す
 *					PORU_FAVOLITE_KIRAI:キライな味タイプを返す
 *
 *	@retval	PORUTO_FTYPE_SPICY	辛い
 *	@retval	PORUTO_FTYPE_ASTR	しぶい
 *	@retval	PORUTO_FTYPE_SWEET	あまい
 *	@retval	PORUTO_FTYPE_BITTER	苦い
 *	@retval	PORUTO_FTYPE_SOUR	すっぱい
 *	@retval	PORUTO_FTYPE_MIX	好き嫌いがない
 */
u8	PoruSys_GetFavolite(u8 seikaku,PORU_FAVOLITE mode)
{
	if(mode == PORU_FAVOLITE_SUKI){
		return poruto_f2char[seikaku][0];
	}else{
		return poruto_f2char[seikaku][1];
	}
	return PORUTO_FTYPE_MIX;
}

/**
 *	@brief	ポルトパラメータをポケモンパラメータにPushする
 */
void PoruSys_PoruPara2Poke(PORUTO_DATA* dat,POKEMON_PARAM* poke)
{
	u8 i,ct;
	u8 seikaku,friend;
	u8	sid,kid;
	float ftmp;
	int	pokeprm[6];
	u8	prm[PORUTO_PARAID_NUM];
	u8	up[PORUTO_PARAID_NUM];
	
	//性格No取得
	seikaku = PokeSeikakuGet(poke);
	sid = poruto_f2char[seikaku][0];
	kid = poruto_f2char[seikaku][1];

	//現在値取得
	PorutoData_GetParamArray(dat,prm);
	
	for(i = 0;i<6;i++){
		pokeprm[i] = PokeParaGet(poke,ID_PARA_style+i,NULL);
	}
	/*
	ID_PARA_style,				//かっこよさ
	ID_PARA_beautiful,			//うつくしさ
	ID_PARA_cute,				//かわいさ
	ID_PARA_clever,				//かしこさ
	ID_PARA_strong,				//たくましさ
	ID_PARA_fur,				//毛艶
	*/
	//上昇値取得
	ct = 0;
	for(i = PORUTO_PARAID_SPICY;i <= PORUTO_PARAID_TASTE;i++){
		up[ct++] = prm[i];	
	}
	//好き嫌いパラメータ補正
	if(sid != PORUTO_FTYPE_MIX){
		ftmp = (float)up[sid]*1.1f;
		up[sid] = (u8)ftmp;	
		ftmp = (float)up[kid]*0.9f;
		up[kid] = (u8)ftmp;
	}
	//パラメータ加算
	for(i = 0;i < 6;i++){
		pokeprm[i] += up[i];
		if(pokeprm[i] > 255){
			pokeprm[i] = 255;
		}
		PokeParaPut(poke,ID_PARA_style+i,&pokeprm[i]);
	}
	//懐き度上昇(一律1+)
	friend = PokeParaGet(poke,ID_PARA_friend,NULL);	
	if(friend < 255){
		++friend;
		PokeParaPut(poke,ID_PARA_friend,&friend);
	}
}
