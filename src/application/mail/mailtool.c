/**
 *	@file	mail.c
 *	@brief	メールシステム
 *	@author	Miyuki Iwasaw
 *	@date	06.02.07
 */

#include "common.h"
#include "poketool/poke_tool.h"
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

#include "savedata/mail_util.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "application/mail/mail_param.h"
#include "application/mail/mailview.h"
#include "application/pms_input.h"
#include "mail_snd_def.h"

enum{
	MAILCASE_INIT,
	MAILCASE_WAIT,
	MAILCASE_END,
	WORDCASE_INIT,
	WORDCASE_WAIT,
	WORDCASE_END,
};

//メールシステムメインワーク
typedef struct _MAIL_MAIN_DAT{
	int	heapID;	///<ヒープID
	u16	ret_val;	///<リターン値
	u16	ret_no;		///<リターン編集NO

	void	*app_wk;	///<簡易会話モジュールワークの保存
	PROC*	proc;		///<サブプロセスワーク
	MAIL_TMP_DATA *dat;	///<メールデータテンポラリ

	PMS_DATA	tmpPms;	//<簡易会話テンポラリ
}MAIL_MAIN_DAT;

//プロトタイプ宣言　ローカル
//================================================================
///オーバーレイプロセス
static PROC_RESULT MailSysProc_Init( PROC *proc,int *seq);
static PROC_RESULT MailSysProc_Main( PROC *proc,int *seq);
static PROC_RESULT MailSysProc_End( PROC *proc,int *seq);

//================================================================
///データ定義エリア
//================================================================
///オーバーレイプロセス定義データ
const PROC_DATA MailSysProcData = {
	MailSysProc_Init,
	MailSysProc_Main,
	MailSysProc_End,
	NO_OVERLAY_ID,
};

MAIL_PARAM* MailSys_GetWorkCreate(SAVEDATA* savedata,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID);
MAIL_PARAM* MailSys_GetWorkView(SAVEDATA* savedata,MAILBLOCK_ID blockID,u16 dataID,int heapID);
MAIL_PARAM* MailSys_GetWorkViewPoke(SAVEDATA* savedata,POKEMON_PARAM* poke,int heapID);
MAIL_PARAM* MailSys_GetWorkViewPrev(SAVEDATA* savedata,u8 designNo,int heapID);
BOOL MailSys_IsDataCreate(MAIL_PARAM* wk);
int MailSys_PushDataToSave(MAIL_PARAM* wk,MAILBLOCK_ID blockID,u8 dataID);
int MailSys_PushDataToSavePoke(MAIL_PARAM* wk,POKEMON_PARAM* poke);
void MailSys_ReleaseCallWork(MAIL_PARAM* wk);
int	MailSys_MoveMailPoke2Paso(MAIL_BLOCK* block,POKEMON_PARAM* poke,int heapID);
int	MailSys_MoveMailPaso2Poke(MAIL_BLOCK* block,u16 id,POKEMON_PARAM* poke,int heapID);


MAIL_TMP_DATA* MailSys_AllocTmpData(const MAIL_DATA* org,int heapID);
void MailSys_ReleaseTmpData(MAIL_TMP_DATA* tmp);
void MailSys_SetTmpData(MAIL_DATA* org,MAIL_TMP_DATA* tmp);




/**
 *	@brief	メール画面呼び出しワーク作成(Create)
 *
 *	@retval	NULL	新規作成領域がない
 *	@retval ワークポインタ	メール作成画面呼び出し
 */
MAIL_PARAM* MailSys_GetWorkCreate(SAVEDATA* savedata,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID)
{
	MAIL_PARAM* wk;
	MAIL_BLOCK* pBlock;
	int id;
	
	//メールセーブデータブロック取得
	pBlock = SaveData_GetMailBlock(savedata); 

	//モジュール呼び出し用のワークを作成
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));

	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	wk->designNo = design;
	wk->poke_pos = poke_pos;
	wk->pBlock = pBlock;

	//呼び出しモード設定
	wk->mode = MAIL_MODE_CREATE;
	wk->blockID = blockID;	//データブロックID取得
	wk->dataID = 0;	//IDは0初期化
	wk->savedata = savedata;

	//データテンポラリ作成
	wk->pDat = MailData_CreateWork(heapID);
	MailData_Clear(wk->pDat);

	//初期データ格納(デザインNoは無効にして呼び出す)
	MailData_CreateFromSaveData(wk->pDat,MAIL_DESIGN_NULL,poke_pos,savedata);
	return wk;
}

/**
 *	@brief	メール画面呼び出しワーク作成(View)
 *
 *	@retval	NULL	新規作成領域がない
 *	@retval ワークポインタ	メール描画画面呼び出し
 */
MAIL_PARAM* MailSys_GetWorkView(SAVEDATA* savedata,MAILBLOCK_ID blockID,u16 dataID,int heapID)
{
	MAIL_PARAM* wk;
	MAIL_BLOCK* pBlock;

	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));

	//呼び出しモード設定
	wk->mode = MAIL_MODE_VIEW;
	wk->blockID = blockID;
	wk->dataID = dataID;
	wk->savedata = savedata;
	
	//メールセーブデータブロック取得
	pBlock = SaveData_GetMailBlock(savedata); 
	wk->pBlock = pBlock;
	
	//セーブデータ取得
	wk->pDat = MAIL_AllocMailData(pBlock,blockID,dataID,heapID);
	return wk;
}

/**
 *	@brief	メール画面呼び出しワーク作成(View/POKEMON_PARAM)
 */
MAIL_PARAM* MailSys_GetWorkViewPoke(SAVEDATA* savedata,POKEMON_PARAM* poke,int heapID)
{
	MAIL_PARAM* wk;
	
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	
	//呼び出しモード設定
	wk->mode = MAIL_MODE_VIEW;
	wk->savedata = savedata;
	
	//ワークを取得
	wk->pDat = MailData_CreateWork(heapID);
	//メールデータ取得
	PokeParaGet(poke,ID_PARA_mail_data,wk->pDat);
	return wk;
}

/**
 *	@brief	メール画面呼び出しワーク作成(View/空メールプレビュー)
 */
MAIL_PARAM* MailSys_GetWorkViewPrev(SAVEDATA* savedata,u8 designNo,int heapID)
{
	MAIL_PARAM* wk;
	
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	
	//呼び出しモード設定
	wk->mode = MAIL_MODE_VIEW;
	wk->savedata = savedata;

	//ワークを取得
	wk->pDat = MailData_CreateWork(heapID);

	//デザインNoのみ設定
	MailData_SetDesignNo(wk->pDat,designNo);	
	return wk;
}

/**
 *	@brief	直前のモジュール呼び出しでデータが作成されたかどうか？
 */
BOOL MailSys_IsDataCreate(MAIL_PARAM* wk)
{
	return wk->ret_val;
}

/**
 *	@brief	直前のモジュール呼び出しで作成されたデータをセーブデータに反映
 */
int MailSys_PushDataToSave(MAIL_PARAM* wk,MAILBLOCK_ID blockID,u8 dataID)
{
	if(!MailSys_IsDataCreate(wk)){
		return 0;	//作成されていない
	}
	MAIL_AddMailFormWork(wk->pBlock,blockID,dataID,wk->pDat);
	return 1;
}

/**
 *	@brief	直前のモジュール呼び出しで作成されたデータをセーブデータに反映(Poke)
 */
int MailSys_PushDataToSavePoke(MAIL_PARAM* wk,POKEMON_PARAM* poke)
{
	if(!MailSys_IsDataCreate(wk)){
		return 0;	//作成されていない
	}
	PokeParaPut(poke,ID_PARA_mail_data,wk->pDat);
	return 1;
}

/**
 *	@brief	メールモジュール呼び出しワークを解放
 */
void MailSys_ReleaseCallWork(MAIL_PARAM* wk)
{
	//データテンポラリを確保していた場合は解放
	if(wk->pDat != NULL){
		sys_FreeMemoryEz(wk->pDat);
	}
	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	ポケモンメールをパソメールに移動
 *
 *	@retval	MAILDATA_NULLID	空きがないので転送できない
 *	@retval	"その他"　転送したデータID
 */
int	MailSys_MoveMailPoke2Paso(MAIL_BLOCK* block,POKEMON_PARAM* poke,int heapID)
{
	int id;
	int itemno = ITEM_DUMMY_DATA;
	MAIL_DATA* src = NULL;

	//空き領域検索
	id = MAIL_SearchNullID(block,MAILBLOCK_PASOCOM);
	if(id == MAILDATA_NULLID){
		return MAILDATA_NULLID;
	}
	//ワーク作成
	src = MailData_CreateWork(heapID);

	//ポケモンからメールを取得
	PokeParaGet(poke,ID_PARA_mail_data,src);

	//パソコン領域にデータコピー
	MAIL_AddMailFormWork(block,MAILBLOCK_PASOCOM,id,src);

	//ポケモンからメールを外す
	MailData_Clear(src);
	PokeParaPut(poke,ID_PARA_mail_data,src);
	PokeParaPut(poke,ID_PARA_item,&itemno);

	//領域解放
	sys_FreeMemoryEz(src);

	return id;
}

/**
 *	@brief	パソメールをポケモンに移動
 *
 *	@retval	MAILDATA_NULLID IDが不正なのでなにもしなかった
 *	@retval	"その他"　転送したデータID
 */
int	MailSys_MoveMailPaso2Poke(MAIL_BLOCK* block,u16 id,POKEMON_PARAM* poke,int heapID)
{
	int itemno = ITEM_DUMMY_DATA;
	MAIL_DATA* src = NULL;

	//メールデータを取得
	src = MAIL_AllocMailData(block,MAILBLOCK_PASOCOM,id,heapID);
	if(src == NULL){
		return MAILDATA_NULLID;
	}
	//メールのデザインNoからアイテムNoに復元
	itemno = MailItemNumGet(MailData_GetDesignNo(src));
	//ポケモンにメールを移す
	PokeParaPut(poke,ID_PARA_mail_data,src);
	PokeParaPut(poke,ID_PARA_item,&itemno);

	//パソコン領域のデータを消す
	MAIL_DelMailData(block,MAILBLOCK_PASOCOM,id);

	//領域解放
	sys_FreeMemoryEz(src);
	return id;
}


/**
 *	@brief	メールデータ　テンポラリ作成
 *
 *	＊内部でメモリをアロケートするので必ず呼び出し側が
 *	　MailSys_ReleaseTmpData()で解放すること
 */
MAIL_TMP_DATA* MailSys_AllocTmpData(const MAIL_DATA* org,int heapID)
{
	u16	i;
	MAIL_TMP_DATA* tmp;

	tmp = sys_AllocMemory(heapID,sizeof(MAIL_TMP_DATA));
	MI_CpuClear8(tmp,sizeof(MAIL_TMP_DATA));
	
	tmp->val = 0;

	tmp->writerID = MailData_GetWriterID(org);
	tmp->name = STRBUF_Create(BUFLEN_PERSON_NAME,heapID);
	STRBUF_SetStringCode(tmp->name,MailData_GetWriterName((MAIL_DATA*)org));
	tmp->design = MailData_GetDesignNo(org);
	tmp->lang = MailData_GetCountryCode(org);
	tmp->ver = MailData_GetCasetteVersion(org);

	for(i = 0;i < MAILDAT_ICONMAX;i++){
		tmp->icon[i].dat = MailData_GetIconParamByIndex(org,i,MAIL_ICONPRM_ALL);
	}
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		PMSDAT_Copy(&tmp->msg[i],MailData_GetMsgByIndex((MAIL_DATA*)org,i));
	}
	return tmp;
}

/**
 *	@brief	メールデータ　テンポラリ解放
 *
 *	＊MailSys_AllocTmpData()で確保したメモリ領域を開放する
 */
void MailSys_ReleaseTmpData(MAIL_TMP_DATA* tmp)
{
	if(tmp->name != NULL){
		STRBUF_Delete(tmp->name);
	}
	sys_FreeMemoryEz(tmp);
}

/**
 *	@brief	メールデータ　テンポラリデータ書き出し
 */
void MailSys_SetTmpData(MAIL_DATA* org,MAIL_TMP_DATA* tmp)
{
	u16	i;

	//簡易文コピー
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		MailData_SetMsgByIndex(org,&tmp->msg[i],i);
	}

	//データを有効化するためにデザインNOを設定
	MailData_SetDesignNo(org,tmp->design);
}

//------------------------------------------------------------------
/**
 * @brief	サブプロセス呼び出し処理
 * @param	proc	サブプロセスポインタを保持するワークへのポインタ
 */
//------------------------------------------------------------------
static BOOL MailSysProcCall(PROC ** proc)
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
 *	@brief	メール作成呼び出し　初期化
 */
static PROC_RESULT MailSysProc_Init(PROC* proc,int* seq)
{
	MAIL_MAIN_DAT* wk = NULL;
	MAIL_PARAM* pp = (MAIL_PARAM*)PROC_GetParentWork(proc);
	
	//ワークエリア取得
	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_MAILSYS,0x1000);
	wk = PROC_AllocWork(proc,sizeof(MAIL_MAIN_DAT),HEAPID_MAILSYS);
	MI_CpuClear8(wk,sizeof(MAIL_MAIN_DAT));

	//ヒープID保存
	wk->heapID = HEAPID_MAILSYS;

	//データテンポラリ作成
	wk->dat = MailSys_AllocTmpData(pp->pDat,wk->heapID);
	wk->dat->configSave = SaveData_GetConfig(pp->savedata);

	if(pp->mode == MAIL_MODE_CREATE){
		//無効ナンバーが格納されているので、上位ワークから取得する
		wk->dat->design = pp->designNo;	//デザインNo適用
	}
	if(wk->dat->design >= MAIL_DESIGN_MAX){
		wk->dat->design = 0;
	}
	wk->dat->val = pp->mode;

	return PROC_RES_FINISH;
}

/**
 *	@brief	メール作成メイン
 */
static PROC_RESULT MailSysProc_Main(PROC *proc,int* seq)
{
	MAIL_MAIN_DAT* wk = PROC_GetWork(proc);
	MAIL_PARAM* pp = (MAIL_PARAM*)PROC_GetParentWork(proc);

	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(mailview);
	FS_EXTERN_OVERLAY(overlay_pmsi);
	
	// プロセス定義データ
	static const PROC_DATA MailViewProcData = {
		MailViewProc_Init,
		MailViewProc_Main,
		MailViewProc_End,
		FS_OVERLAY_ID(mailview),
	};
	static const PROC_DATA PMSProcData = {
		PMSInput_Init,
		PMSInput_Main,
		PMSInput_Quit,
		FS_OVERLAY_ID(overlay_pmsi),
	};

	switch(*seq){
	case MAILCASE_INIT:
		wk->dat->val = pp->mode;	//動作モード値復帰
		wk->proc = PROC_Create(&MailViewProcData,wk->dat,wk->heapID);
		*seq = MAILCASE_WAIT;
		break;
	case MAILCASE_WAIT:
		if(!MailSysProcCall(&wk->proc)){
			break;
		}
		switch(wk->dat->val){
		case VIEW_END_CANCEL:
			*seq = MAILCASE_END;
			break;
		case VIEW_END_DECIDE:
			*seq = MAILCASE_END;
			break;
		default:
			*seq = WORDCASE_INIT;	
			break;
		}
		break;
	case MAILCASE_END:
		//データ取得
		if(	pp->mode == MAIL_MODE_CREATE){
			if(	wk->dat->val == VIEW_END_DECIDE){
				MailSys_SetTmpData(pp->pDat,wk->dat);	//メールデータを書き換え
				//スコア加算処理
				RECORD_Score_Add(SaveData_GetRecord(pp->savedata),SCORE_ID_WRITE_MAIL);
				pp->ret_val = 1;	//戻り値設定
			}else{
				pp->ret_val = 0;	//戻り値設定
			}
		}
		return PROC_RES_FINISH;
	case WORDCASE_INIT:
		wk->app_wk = PMSI_PARAM_Create( PMSI_MODE_SENTENCE,
				PMSI_GUIDANCE_DEFAULT,pp->savedata, wk->heapID);

		//初期データセット
		if(PMSDAT_IsEnabled(&(wk->dat->msg[wk->dat->cntNo]))){
			//既に入力文がある
			PMSDAT_Copy(&(wk->tmpPms),&(wk->dat->msg[wk->dat->cntNo]));
		}else{
			//まだ空
			PMSDAT_Init(&(wk->tmpPms),PMS_TYPE_MAIL);	
		}
		PMSI_PARAM_SetInitializeDataSentence(wk->app_wk,&(wk->tmpPms));
		
		wk->proc = PROC_Create(&PMSProcData,wk->app_wk,wk->heapID);
		*seq = WORDCASE_WAIT;
		break;
	case WORDCASE_WAIT:
		if(!MailSysProcCall(&wk->proc)){
			break;
		}
		// 簡易会話取得
		if(	PMSI_PARAM_CheckCanceled(wk->app_wk) == FALSE)
//			&& PMSI_PARAM_CheckModified(wk->app_wk) == TRUE)
		{
			//変更があれば書き戻し
			PMSI_PARAM_GetInputDataSentence( wk->app_wk,  &(wk->dat->msg[wk->dat->cntNo]));
		}
		PMSI_PARAM_Delete(wk->app_wk);
		*seq = MAILCASE_INIT;	
		break;
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	メール作成終了
 */
static PROC_RESULT MailSysProc_End(PROC *proc,int* seq)
{
	MAIL_MAIN_DAT	*wk = PROC_GetWork(proc);

	//メールデータテンポラリ領域解放
	MailSys_ReleaseTmpData(wk->dat);

	//ワークエリア解放
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);

	sys_DeleteHeap(wk->heapID);

	return PROC_RES_FINISH;
}

//===========================================================================
//デバッグ用ルーチン
//===========================================================================
