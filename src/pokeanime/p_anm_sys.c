#include "pokeanime/p_anm_sys.h"
#include "system/softsprite.h"
#include "system/arc_tool.h"
#include "poketool/poke_tool.h"		//for PokePersonalParaGet
#include "tcb.h"

#include "past_def.h"


#define REQUEST_MAX	(256)
#define ANM_WORK_MAX	(8)
#define MOVE_FUNC_WORK_MAX	(8)
#define MOVE_FUNC_ENTRY_MAX	(4)

#define ANM_CMD_MAX	(34)

// ----------------------------------------
//
//	指定サイズ分アドレスを進めるマクロ
//		進めるアドレスの型に依存する
//
// -----------------------------------------
#define ADRS_CMD(n, m)			((n) += (m))

// -----------------------------------------
//
//	型サイズ分アドレスを進めるマクロ
//		最小単位でアドレスが進む
//		ADRS_CMD を利用するので型に依存する
//
// -----------------------------------------
#define ADRS_SHIFT(n)			(ADRS_CMD(n, 1))

typedef int	TAP;
typedef struct POKE_ANIME_tag *POKE_ANM_PTR;
typedef struct MOVE_FUNC_DATA_tag *MOVE_FUNC_DATA_PTR;
typedef void (*pAnmFunc)( POKE_ANM_PTR );
typedef void (*MoveFunc)( MOVE_FUNC_DATA_PTR, POKE_ANM_PTR);

static TAP  GetAdrsParamEx(u32* adrs, u8 s_byte, u8 byte);	///< データ取得
static TAP  GetAdrsParam(u32* adrs, u8 byte);					///< データ取得
static TAP  GetSeqAdrs(u32* adrs);

typedef struct MOVE_FUNC_DATA_tag
{
	BOOL Valid;		//関数有効フラグ
	int Work[MOVE_FUNC_WORK_MAX];	//ワーク
	int *Target;			//動作関数データ内の変更対象元
	int *ApplyTarget;		//アニメデータ内の変更対象先
	
	u8	ApplyType;		//値をセットするか、今の値に値を上乗せするかのフラグ

	u8	Wait;			//動作関数実行までのウェイト
	int StartVal;		//APPLY_ADD時の基準となる値
	int TransX;			//Ｘ移動値
	int TransY;			//Ｙ移動値
	int dx;				//Ｘ移動値（オフセット）
	int dy;				//Ｙ移動値（オフセット）
	int rx;				//拡縮Ｘ
	int ry;				//拡縮Ｙ
	int Rot;			//回転
	MoveFunc	Func;	//動作関数
}MOVE_FUNC_DATA;

typedef struct POKE_ANIME_tag
{
	SOFT_SPRITE *SoftSprite;	//ソフトウェアスプライトへのポインタ
	TCB_PTR Task;		//登録タスク（アニメ中断時解放用）
	void *ArcData;		//アーカイブデータ
	u32 *SeqAdrs;		//データシーケンスアドレス

	BOOL Valid;			//データ有効フラグ
//	int MonsNo;	//モンスターナンバー	（いらないかも）
	int AnimeNo;	//アニメナンバー(いらないかも)
	int Request;		//アニメ反映フラグ
	int End;			//アニメコマンド終了フラグ
	BOOL EndComp;		//アニメ終了フラグ
	int Work[ANM_WORK_MAX];	//ワーク
	int ReqCount;		//
	
	int LoopMax;			//ループ回数
	int LoopCount;			//現在ループ回数
	u32 *LoopStartAdrs;		//ループ開始アドレス

	int Wait;			//アニメ開始までのウェイト

	int OrgX;			//スプライトＸ座標
	int OrgY;			//スプライトＹ座標
	int TransX;			//Ｘ移動値
	int TransY;			//Ｙ移動値
	int dx;				//Ｘ移動値（オフセット）
	int dy;				//Ｙ移動値（オフセット）
	int rx;				//拡縮Ｘ
	int ry;				//拡縮Ｙ
	int Rot;			//回転

	MOVE_FUNC_DATA			MoveFuncData[MOVE_FUNC_ENTRY_MAX];

	u8 PokeReverse;	//ポケモンごとの反転フラグ(ポケモンによっては反転しない)　0：反転しない　1：反転する
	u8 CommandHold;	//動作関数起動中ホールドフラグ
	u8 CorrectDy;	//dy補正有効フラグ
	u8 PalFadeWaitFlg;	//パレットフェード終了待ちフラグ

}POKE_ANIME;

typedef struct POKE_ANIME_SYS_tag
{
	POKE_ANIME *PokeAnime;
	int HeapID;		//ヒープＩＤ
	u8 Reverse;		//アニメを反転するかどうかのフラグ　0：反転しない	1：反転する
	u8 AnimeNum;
}POKE_ANIME_SYS;

typedef struct MOVE_FUNC_P_DATA_tag
{
	MoveFunc	Func;	//動作関数
	int ParamNum;		//パラメータ数
	int TargetWorkIdx;	//変更対象を格納したワークのインデックス
}MOVE_FUNC_P_DATA;

static void CallMoveFuc(POKE_ANIME *pAnm, const int inMoveFuncNo);
static void	PokemonAnimeTask(TCB_PTR tcb, void *work);
static void ExecutePokeAnime(POKE_ANIME *pAnm);

static void	PAnm_End(POKE_ANIME *pAnm);
static void	PAnm_SetRequest(POKE_ANIME *pAnm);
static void PAnm_SetDefault(POKE_ANIME *pAnm);
static void PAnm_SetIfWorkVal(POKE_ANIME *pAnm);
static void PAnm_SetWorkVal(POKE_ANIME *pAnm);
static void PAnm_CopyWorkVal(POKE_ANIME *pAnm);
static void PAnm_AddWorkVal(POKE_ANIME *pAnm);
static void PAnm_MulWorkVal(POKE_ANIME *pAnm);
static void PAnm_SubWorkVal(POKE_ANIME *pAnm);
static void PAnm_DivWorkVal(POKE_ANIME *pAnm);
static void PAnm_ModWorkVal(POKE_ANIME *pAnm);
static void	PAnm_StartLoop(POKE_ANIME *pAnm);
static void	PAnm_EndLoop(POKE_ANIME *pAnm);
static void	PAnm_SetVal(POKE_ANIME *pAnm);		//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
static void	PAnm_AddVal(POKE_ANIME *pAnm);		//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
static void PAnm_SetAddVal(POKE_ANIME *pAnm);
static void PAnm_SetWorkValSin(POKE_ANIME *pAnm);
static void PAnm_SetWorkValCos(POKE_ANIME *pAnm);
static void PAnm_SetTrans(POKE_ANIME *pAnm);	//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
static void PAnm_AddTrans(POKE_ANIME *pAnm);	//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
static void PAnm_SetAddParam(POKE_ANIME *pAnm);
static void PAnm_ApplyTrans(POKE_ANIME *pAnm);
static void PAnm_ApplyAffine(POKE_ANIME *pAnm);
static void PAnm_SetD(POKE_ANIME *pAnm);
static void PAnm_SetWait(POKE_ANIME *pAnm);
static void PAnm_PaletteFade(POKE_ANIME *pAnm);
static void PAnm_WaitPaletteFade(POKE_ANIME *pAnm);

static void PAnm_HoldAnmCommand(POKE_ANIME *pAnm);
static void PAnm_SetDyCorrect(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncCurve(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncCurveDivTime(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLine(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLineDivTime(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLineDst(POKE_ANIME *pAnm);

static void PMove_Curve(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_CurveDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_Line(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_LineDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_LineDst(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);

#define CHARA_MAX	(25)
//性格別アニメハッシュテーブル（0：派手な動き　1：普通　2：控えめな動き）
static const u8 PesrsonalityTbl[CHARA_MAX] = {
	0,	//がんばりや
	2,	//さみしがり
	0,	//ゆうかん
	0,	//いじっぱり
	0,	//やんちゃ
	1,	//ずぶとい
	1,	//すなお
	1,	//のんき
	0,	//わんぱく
	1,	//のうてんき
	2,	//おくびょう
	0,	//せっかち
	1,	//まじめ
	0,	//ようき
	0,	//むじゃき
	2,	//ひかえめ
	2,	//おっとり
	2,	//れいせい
	2,	//てれや
	1,	//うっかりや
	1,	//おだやか
	2,	//おとなしい
	1,	//なまいき
	2,	//しんちょう
	1,	//きまぐれ
};

static const pAnmFunc PokeAnmCmdList[ANM_CMD_MAX] = {
	PAnm_End,				//0
	PAnm_SetRequest,
	PAnm_SetDefault,
	PAnm_SetIfWorkVal,
	PAnm_SetWorkVal,
	PAnm_CopyWorkVal,
	PAnm_AddWorkVal,
	PAnm_MulWorkVal,
	PAnm_SubWorkVal,
	PAnm_DivWorkVal,
	PAnm_ModWorkVal,
	PAnm_StartLoop,
	PAnm_EndLoop,
	PAnm_SetVal,		//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
	PAnm_AddVal,		//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
	PAnm_SetAddVal,
	PAnm_SetWorkValSin,
	PAnm_SetWorkValCos,
	PAnm_SetTrans,	//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
	PAnm_AddTrans,	//＜別のコマンドを使うように(時期的に考えてコマンドは消しません) 20060801
	PAnm_SetAddParam,
	PAnm_ApplyTrans,
	PAnm_ApplyAffine,
	PAnm_SetD,

	PAnm_HoldAnmCommand,
	PAnm_SetDyCorrect,
	PAnm_CallMoveFuncCurve,
	PAnm_CallMoveFuncCurveDivTime,
	PAnm_CallMoveFuncLine,
	PAnm_CallMoveFuncLineDivTime,
	PAnm_CallMoveFuncLineDst,	
	
	PAnm_SetWait,
	PAnm_PaletteFade,
	PAnm_WaitPaletteFade,
};

enum{
	MOVE_CURVE,
	MOVE_CURVE_DIVTIME,
	MOVE_LINE,
	MOVE_LINE_DIVTIME,
	MOVE_LINE_DST,
};

#define F_PARAM_NUM_CURVE			(6)	//カーブタイプ、対象、振幅、加算角度、位相、計算回数	計6
#define F_PARAM_NUM_CURVE_DIVTIME	(6)	//カーブタイプ、対象、振幅、角度、位相、計算回数	計6
#define F_PARAM_NUM_LINE			(4)	//対象、初速度、加速度、計算回数	計4
#define F_PARAM_NUM_LINE_DIVTIME	(3)	//対象、移動値、計算回数	計3
#define F_PARAM_NUM_LINE_DST		(4)	//対象、初速度、加速度、目的値	計4

static const MOVE_FUNC_P_DATA MoveFuncTbl[] = {
	{PMove_Curve, F_PARAM_NUM_CURVE, 1},
	{PMove_CurveDivTime, F_PARAM_NUM_CURVE_DIVTIME,1},
	{PMove_Line,F_PARAM_NUM_LINE, 0},
	{PMove_LineDivTime,F_PARAM_NUM_LINE_DIVTIME,0},
	{PMove_LineDst,F_PARAM_NUM_LINE_DST,0}
};

//--------------------------------------------------------------
/**
 * ポケモンアニメーションセッティングパラメータの作成
 *
 * @param	inMonsNo	モンスターナンバー
 * @param	outParam	パラメータ格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_CreateSettingParam(const int inMonsNo, P_ANM_SETTING_PARAM *outParam)
{
	GF_ASSERT(outParam!=NULL&&"ERROR:paramater is NULL");
	
	outParam->AnimeNo = 0;	//0をセット
	outParam->Wait = 0;		//0をセット
	outParam->Reverse = PokePersonalParaGet(inMonsNo, ID_PER_reverse);	//パーソナルから反転フラグを取得
	outParam->Reverse ^= 1;
}


//--------------------------------------------------------------
/**
 * ポケモンアニメーション用管理メモリの確保
 *
 * @param	inHeapID	ヒープID
 * @param	inAllocNum	アニメ確保数
 * @param	inReverse	反転許可フラグ
 *
 * @retval	POKE_ANM_S_PTR	確保したポケモンアニメ管理領域へのポインタ
 */
//--------------------------------------------------------------
POKE_ANM_SYS_PTR PokeAnm_AllocMemory(const int inHeapID, const int inAllocNum, const u8 inReverse)
{
	POKE_ANM_SYS_PTR ptr;
	ptr = sys_AllocMemory(inHeapID, sizeof(POKE_ANIME_SYS));
	ptr->Reverse = inReverse;
	ptr->AnimeNum = inAllocNum;
	ptr->HeapID = inHeapID;
	ptr->PokeAnime = sys_AllocMemory(inHeapID, sizeof(POKE_ANIME)*inAllocNum);
	//クリア
	MI_CpuClear8(ptr->PokeAnime,sizeof(POKE_ANIME)*inAllocNum);
	
	return  ptr;
}

//--------------------------------------------------------------
/**
 * ポケモンアニメーション用管理メモリ解放
 *
 * @param	ptr				ポケモンアニメ領域へのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_FreeMemory(POKE_ANM_SYS_PTR ptr)
{
	sys_FreeMemoryEz(ptr->PokeAnime);
	sys_FreeMemoryEz(ptr);
}
//--------------------------------------------------------------
/**
 * 性格から背面ポケモンアニメのスロット番号を返す（0～2）
 *
 * @param	inChar			ポケモンの性格
 *
 * @retval	u8			採用するスロット番号（0～2）
 */
//--------------------------------------------------------------
u8 PokeAnm_GetBackAnmSlotNo(	const u8 inChar )
{
	u8 slot_no;
	GF_ASSERT(inChar < CHARA_MAX);
	slot_no = PesrsonalityTbl[inChar];
	
	return slot_no;
}

//--------------------------------------------------------------
/**
 * ソフトウェアスプライトとポケモンナンバーをセットする
 *
 * @param	ptr				ポケモンアニメ領域へのポインタ
 * @param	ss				ソフトウェアスプライトへのポインタ
 * @param	inParam			アニメセッティングパラメータ
 * @param	inEntryIndex	登録インデックス
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_SetPokeAnime(	POKE_ANM_SYS_PTR ptr, SOFT_SPRITE *ss,
							const P_ANM_SETTING_PARAM *inParam,
							const u8 inEntryIndex)
{
	u8 idx = inEntryIndex;
	int anime_no = inParam->AnimeNo;
	int wait = inParam->Wait;
	
	GF_ASSERT((idx<ptr->AnimeNum)&&"ERROR:IndexOver");
	GF_ASSERT(ptr->PokeAnime[idx].Valid==FALSE&&"ERROR:PokeAnime Entry already");

	//クリア
	MI_CpuClear8(&ptr->PokeAnime[idx],sizeof(POKE_ANIME));

	//データ有効
	ptr->PokeAnime[idx].Valid = TRUE;

	//スプライトセット
	ptr->PokeAnime[idx].SoftSprite = ss;
#ifdef PM_DEBUG	
	//拡縮率をチェック
	{
		int aff_x,aff_y;
		aff_x = SoftSpriteParaGet(ss, SS_PARA_AFF_X);
		aff_y = SoftSpriteParaGet(ss, SS_PARA_AFF_Y);
		GF_ASSERT( (aff_x==0x100)&&(aff_y==0x100) );
	}
#endif	
	//アニメナンバー範囲外対処
	if (anime_no >= POKE_ANIME_MAX){
		anime_no = 0;
		wait = 0;
	}
	
	//モンスターナンバーからアニメーションを特定
	ptr->PokeAnime[idx].AnimeNo = anime_no;

	//反転フラグセット
	if (ptr->Reverse){
		//モンスターごとに反転を見る
		ptr->PokeAnime[idx].PokeReverse = inParam->Reverse;
	}else{
		ptr->PokeAnime[idx].PokeReverse = 0;
	}

	//アニメアーカイブデータセット
	ptr->PokeAnime[idx].ArcData =
		ArchiveDataLoadMallocLo(ARC_POKE_ANM, ptr->PokeAnime[idx].AnimeNo, ptr->HeapID );
	ptr->PokeAnime[idx].SeqAdrs = (u32*)ptr->PokeAnime[idx].ArcData;
	
	//アニメ終了フラグオフ
	ptr->PokeAnime[idx].End = 0;
	ptr->PokeAnime[idx].EndComp = FALSE;
	//ホールドクリア
	ptr->PokeAnime[idx].CommandHold = 0;
	//dy補正無効
	ptr->PokeAnime[idx].CorrectDy = CORRECT_OFF;
	//パレット待ち状態クリア
	ptr->PokeAnime[idx].PalFadeWaitFlg = 0;
	//アニメ登録（タスク登録）とタスク記憶
	ptr->PokeAnime[idx].Task = TCB_Add(PokemonAnimeTask, &ptr->PokeAnime[idx], 0);

	//アニメ開始ウェイトをセット
	ptr->PokeAnime[idx].Wait = wait;		

	ptr->PokeAnime[idx].OrgX = SoftSpriteParaGet(ss,SS_PARA_POS_X);
	ptr->PokeAnime[idx].OrgY = SoftSpriteParaGet(ss,SS_PARA_POS_Y);
	ptr->PokeAnime[idx].TransX = 0;
	ptr->PokeAnime[idx].TransY = 0;
	ptr->PokeAnime[idx].dx = 0;
	ptr->PokeAnime[idx].dy = 0;
	ptr->PokeAnime[idx].rx = 0;
	ptr->PokeAnime[idx].ry = 0;
	ptr->PokeAnime[idx].Rot = 0;

///	OS_Printf("anime_struct_size = %d\n",sizeof(POKE_ANIME));
}

//--------------------------------------------------------------
/**
 * アニメーション終了を検出
 *
 * @param	ptr				ポケモンアニメ領域へのポインタ
 * @param	inEntryIndex	０～３までの登録インデックス
 *
 * @retval	BOOL	TRUE:終了		FALSE:継続
 */
//--------------------------------------------------------------
BOOL PokeAnm_IsFinished(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex)
{
	GF_ASSERT((inEntryIndex<ptr->AnimeNum)&&"ERROR:IndexOver");

	return ptr->PokeAnime[inEntryIndex].EndComp;
}

//--------------------------------------------------------------
/**
 * アニメーション強制終了(タスク削除)
 *
 * @param	ptr				ポケモンアニメ領域へのポインタ
 * @param	inEntryIndex	０～３までの登録インデックス
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_EndAnimeForce(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex)
{
	if ( ptr->PokeAnime[inEntryIndex].Task != NULL ){
		TCB_Delete(ptr->PokeAnime[inEntryIndex].Task);
		ptr->PokeAnime[inEntryIndex].Task = NULL;
		ptr->PokeAnime[inEntryIndex].EndComp = TRUE;
		ptr->PokeAnime[inEntryIndex].Valid = FALSE;		//アニメ無効
		//アニメデータ解放
		sys_FreeMemoryEz(ptr->PokeAnime[inEntryIndex].ArcData);
	}
}

//--------------------------------------------------------------
/**
 * ポケモンアニメーションタスク
 *
 * @param	tcb		タスクのポインタ
 * @param	work	タスクワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void	PokemonAnimeTask(TCB_PTR tcb, void *work)
{
	POKE_ANIME *anime = (POKE_ANIME*)(work);
	if (anime->Wait == 0){
		ExecutePokeAnime(anime);
	}else{
		anime->Wait--;
	}
	
	if (anime->End){
		anime->EndComp = TRUE;
		anime->Valid = FALSE;		//アニメ無効
		//タスク破棄
		TCB_Delete(tcb);
		anime->Task = NULL;
		//アニメデータ解放
		sys_FreeMemoryEz(anime->ArcData);
	}
}

//--------------------------------------------------------------
/**
 * コマンド実行関数
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ExecutePokeAnime(POKE_ANIME *pAnm)
{
	pAnmFunc func;
	pAnm->Request = 0;
	pAnm->ReqCount = 0;

	{
		u8 i;
		u8 invalid;
		MOVE_FUNC_DATA_PTR mfd_ptr;
		//動作関数処理
		invalid = 0;
		for(i=0;i<MOVE_FUNC_ENTRY_MAX;i++){
			mfd_ptr = &(pAnm->MoveFuncData[i]);
			if (mfd_ptr->Valid){
				if (mfd_ptr->Wait == 0){
					///動作関数実行
					mfd_ptr->Func(mfd_ptr,pAnm);
				}else{
					mfd_ptr->Wait--;
				}
			}else{
				invalid++;
			}
		}
		if (invalid == MOVE_FUNC_ENTRY_MAX){	//動作関数が全て終了しているならば
			//コマンド解釈ホールドを解除
			pAnm->CommandHold = 0;
		}
	}

	if (pAnm->CommandHold){	//動作関数によりコマンド解釈をホールドしているならば
		//現在までの計算結果をスプライトに反映させて、アニメーションを実行
		PAnm_ApplyTrans(pAnm);
		PAnm_ApplyAffine(pAnm);
		return;
	}

	//パレットフェード終了待ち状態なら
	if (pAnm->PalFadeWaitFlg){
		//終わるまで次のコマンドを実行しない
		if( !SoftSpritePalFadeExist(pAnm->SoftSprite) ){//フェードの状況をみる
			pAnm->PalFadeWaitFlg = 0;//フェード終了
		}else{
			return ;//フェード継続してるので、返す
		}
	}

	while(1) {	//アニメ反映リクエストがかかるまで実行
///		OS_Printf("val=%d\n",(u32)(*pAnm->SeqAdrs));
		pAnm->ReqCount++;
		//実行関数
		GF_ASSERT((u32)*(pAnm->SeqAdrs)<ANM_CMD_MAX&&"ERROR:AnimeCmdOver");
		func = PokeAnmCmdList[(u32)*(pAnm->SeqAdrs)];
		func(pAnm);

		if (pAnm->End){
			break;
		}else{
			ADRS_SHIFT(pAnm->SeqAdrs);
			if (pAnm->Request){
///				OS_Printf("pos = %d\n",SoftSpriteParaGet(pAnm->SoftSprite,SS_PARA_POS_Y));
				break;
			}else if(pAnm->CommandHold){
				//動作関数初回変化を反映
				PAnm_ApplyTrans(pAnm);
				PAnm_ApplyAffine(pAnm);
				break;
			}
		}

		//無限ループ回避
		if (pAnm->ReqCount >= REQUEST_MAX)
		{
			GF_ASSERT(0&&"Request too long");
			//ポケモンの位置戻しとく？
			pAnm->End = 1;
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	指定バイト数データを取得
 *
 * @param	adrs	取得する対象アドレス
 * @param	s_byte	開始するバイト位置
 * @param	byte	取得するバイト数
 *
 * @retval	TAP	値
 *
 */
//--------------------------------------------------------------
static TAP GetAdrsParamEx(u32* adrs, u8 s_byte, u8 byte)
{
	TAP val = adrs[s_byte];
	
	if (byte != 1){
		GF_ASSERT(0);
	}
	return val;
}

//--------------------------------------------------------------
/**
 * @brief	指定バイト数データを取得
 *
 * @param	adrs	取得する対象アドレス
 * @param	byte	取得するバイト数
 *
 * @retval	TAP		値
 *
 */
//--------------------------------------------------------------
static TAP GetAdrsParam(u32* adrs, u8 byte)
{
	TAP val;

	val = GetAdrsParamEx(adrs, 0, byte);

	return val;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスアドレスを取得
 *
 * @param	adrs	取得する対象アドレス
 *
 * @retval	TAP		値
 *
 */
//--------------------------------------------------------------
static TAP GetSeqAdrs(u32* adrs)
{
	return GetAdrsParam(adrs, 1);
}

//--------------------------------------------------------------
/**
 * 動作関数のセット
 *
 * @param	pAnm			アニメポインタ
 * @param	inMoveFuncNo	動作関数番号(256は超えないと思う)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static MOVE_FUNC_DATA_PTR SetMoveFunc(POKE_ANIME *pAnm, const u8 inMoveFuncNo)
{
	MOVE_FUNC_DATA_PTR ptr;
	u8 i;
	//空いているところを探す
	for(i=0;i<MOVE_FUNC_ENTRY_MAX;i++){
		ptr = &(pAnm->MoveFuncData[i]);
		if (ptr->Valid == FALSE){
			//クリア
			MI_CpuClear8(ptr,sizeof(MOVE_FUNC_DATA));	
			//セット
			ptr->Valid = TRUE;
			ptr->Func = MoveFuncTbl[inMoveFuncNo].Func;
			return ptr;
		}
	}
	GF_ASSERT(0&&"ERROR:MOVE_FUNC_ENTRY_FAILED!!");
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
/**
 * int型値を取得
 *
 * @param	pAnm			アニメポインタ
 * @param	outVal			格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetInt(POKE_ANIME *pAnm, int *outVal)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outVal) =  (int)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * u8型値を取得
 *
 * @param	pAnm			アニメポインタ
 * @param	outVal			格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetU8(POKE_ANIME *pAnm, u8 *outVal)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outVal) =  (u8)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * ワークインデックス取得
 *
 * @param	pAnm			アニメポインタ
 * @param	outIdx			取得インデックス格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetIdx(POKE_ANIME *pAnm, u8 *outIdx)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outIdx) =  (u8)GetSeqAdrs(pAnm->SeqAdrs);
	GF_ASSERT((*outIdx)<ANM_WORK_MAX&&"ERROR:WorkOver");
}

//--------------------------------------------------------------
/**
 * ワークインデックス取得(インデックスが2つ連続してるとき)
 *
 * @param	pAnm			アニメポインタ
 * @param	outIdx1			1つめ取得インデックス格納バッファ
 * @param	outIdx2			2つめ取得インデックス格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetTwoIdx(POKE_ANIME *pAnm, u8 *outIdx1, u8 *outIdx2)
{
	GetIdx(pAnm, outIdx1);
	GetIdx(pAnm, outIdx2);
}

//--------------------------------------------------------------
/**
 * 加算・乗算共通処理
 *
 * @param	pAnm			アニメポインタ
 * @param	outDstIdx		格納先ワークインデックス
 * @param	outVal1			1つめ値格納バッファ
 * @param	outVal2			2つめ値格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CalcCommonAddMul(POKE_ANIME *pAnm, u8 *outDstIdx, int *outVal1, int *outVal2)
{
	u8 idx1,idx2;
	u8 calc;
	
	//格納先ワークインデックス取得
	GetIdx(pAnm,outDstIdx);
	//計算タイプ取得
	GetU8(pAnm,&calc);
	
	if (calc == CALC_VAL){
		//ワークと直値の計算
		GetIdx(pAnm,&idx1);
		(*outVal1) = pAnm->Work[idx1];
		GetInt(pAnm,outVal2);
	}else if (calc == CALC_WORK){
		//ワーク同士の計算
		GetTwoIdx(pAnm, &idx1, &idx2);
		(*outVal1) = pAnm->Work[idx1];
		(*outVal2) = pAnm->Work[idx2];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * 減算・除算・余り計算共通処理
 *
 * @param	pAnm			アニメポインタ
 * @param	outDstIdx		格納先ワークインデックス
 * @param	outVal1			1つめ値格納バッファ
 * @param	outVal2			2つめ値格納バッファ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CalcCommonSubDivMod(POKE_ANIME *pAnm, u8 *outDstIdx, int *outVal1, int *outVal2)
{
	u8 idx1,idx2;
	u8 calc1,calc2;
	//格納先ワークインデックス取得
	GetIdx(pAnm,outDstIdx);
	//計算タイプ取得
	GetU8(pAnm,&calc1);
	GetU8(pAnm,&calc2);
	
	if (calc1 == CALC_VAL){
		//直値
		GetInt(pAnm,outVal1);
	}else if(calc1 == CALC_WORK){
		//ワーク
		GetIdx(pAnm,&idx1);
		(*outVal1) = pAnm->Work[idx1];
	}else{
		GF_ASSERT(0);
	}

	if (calc2 == CALC_VAL){
		//直値
		GetInt(pAnm,outVal2);
	}else if(calc2 == CALC_WORK){
		//ワーク
		GetIdx(pAnm,&idx2);
		(*outVal2) = pAnm->Work[idx2];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * サイン・コサイン共通
 *
 * @param	pAnm			アニメポインタ
 * @param	outDstIdx		格納先ワークインデックス
 * @param	outRad			ラジアン値格納バッファ
 * @param	outL			振幅値格納バッファ
 * 
 * @retval	COMP_MINUS:小さい　COMP_PULS:大きい　COMP_EQUAL	同じ
 */
//--------------------------------------------------------------
static void CalcCommonSinCos(POKE_ANIME *pAnm, u8 *outDstIdx, int *outRad, int *outL)
{
	u8 rad_idx,l_idx,ofs_idx;
	int rad;
	int ofs;
	u8 use;
	
	//ワークインデックス取得
	//ラジアン取得
	GetTwoIdx(pAnm, outDstIdx, &rad_idx);
	
	rad = pAnm->Work[rad_idx];

	//振幅取得
	GetU8(pAnm,&use);
	if (use == USE_VAL){
		GetInt(pAnm,outL);
	}else if(use == USE_WORK){
		GetIdx(pAnm,&l_idx);
		(*outL) = pAnm->Work[l_idx];
	}else{
		GF_ASSERT(0);
	}

	//位相取得
	GetU8(pAnm,&use);
	if (use == USE_VAL){
		GetInt(pAnm,&ofs);
	}else if(use == USE_WORK){
		GetIdx(pAnm,&ofs_idx);
		ofs = pAnm->Work[ofs_idx];
	}else{
		GF_ASSERT(0);
	}
	
	(*outRad) = rad+ofs;
	(*outRad) %= 0x10000;

}

//--------------------------------------------------------------
/**
 * 値比較	２つ目の値に対して１つ目の値がどんな値であるかを返す
 *
 * @param	inVal1		値１つ目
 * @param	inVal2		値２つ目
 *
 * @retval	COMP_MINUS:小さい　COMP_PULS:大きい　COMP_EQUAL	同じ
 */
//--------------------------------------------------------------
static u8 CompVal(const int *inVal1, const int *inVal2)
{
	int val;
	val = 	(*inVal1)-(*inVal2);
	if (val<0){
		return COMP_MINUS;
	}else if (val>0){
		return COMP_PLUS;
	}else{
		return COMP_EQUAL;
	}
}

//--------------------------------------------------------------
/**
 * 拡縮によるＤＹ補正
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CorrectDy(POKE_ANIME *pAnm)
{
	int correct;
	correct = (-pAnm->ry)/8;
	SoftSpriteParaCalc(pAnm->SoftSprite, SS_PARA_POS_Y, correct);
}

/////////////////////////////////////////////////////////////////////////////////////////
//コマンド

//--------------------------------------------------------------
/**
 * アニメ終了
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_End(POKE_ANIME *pAnm)
{
	//スプライトを元の位置へ
	PAnm_SetDefault(pAnm);
	
	pAnm->Request = 1;
	pAnm->End = 1;
}

//--------------------------------------------------------------
/**
 * アニメ反映	(今まで行った計算結果を描画に反映する)
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetRequest(POKE_ANIME *pAnm)
{
	pAnm->Request = 1;
}

//--------------------------------------------------------------
/**
 * スプライトをアニメ前の状態に戻す（回転、拡縮に対しては、無回転、倍率1をセット）
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetDefault(POKE_ANIME *pAnm)
{
	//位置、回転、拡縮を元に戻す
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_Y, pAnm->OrgY);

	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_Z, 0);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_CX, 0);

	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_X, 0x100);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_Y, 0x100);
}

//--------------------------------------------------------------
/**
 * ワーク間の値のコピー	
 * 1つ目のインデックスで指定されるワークに、2つ目のインデックスで指定されるワークをコピー
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CopyWorkVal(POKE_ANIME *pAnm)
{
	u8 idx1,idx2;
	GetTwoIdx(pAnm, &idx1, &idx2);

	pAnm->Work[idx1] = pAnm->Work[idx2];
}

//--------------------------------------------------------------
/**
 * ワークの加算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonAddMul(pAnm, &dst_idx, &val1, &val2);
	
	pAnm->Work[dst_idx] = val1 + val2;
}

//--------------------------------------------------------------
/**
 * ワークの乗算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_MulWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;
	
	CalcCommonAddMul(pAnm, &dst_idx, &val1, &val2);

	pAnm->Work[dst_idx] = val1 * val2;
//	OS_Printf("mul=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ワークの減算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SubWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 - val2;
//	OS_Printf("sub=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ワークの除算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_DivWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 / val2;
//	OS_Printf("div=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ワークの余りをを計算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ModWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 % val2;
}

//--------------------------------------------------------------
/**
 * 値比較後にワークセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetIfWorkVal(POKE_ANIME *pAnm)
{
	u8 idx1,idx2;
	u8 comp, comp_result;
	u8 use;
	
	{
		int val1,val2;
		GetU8(pAnm,&use);  
		if (use == USE_VAL){
			GetIdx(pAnm,&idx1);
			val1 = pAnm->Work[idx1];
			GetInt(pAnm,&val2);
		}else if(use == USE_WORK){
			GetTwoIdx(pAnm, &idx1, &idx2);
			val1 = pAnm->Work[idx1];
			val2 = pAnm->Work[idx2];
		}else{
			GF_ASSERT(0);
		}
	
		GetU8(pAnm,&comp);
	
		GF_ASSERT((comp<=COMP_EQUAL)&&"ERROR:COMP_ERROR");
		//比較
		comp_result = CompVal(&val1, &val2);
	}
	
	{
		int val;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetIdx(pAnm,&idx1);
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetTwoIdx(pAnm, &idx1, &idx2);
			val = pAnm->Work[idx2];
		}else{
			GF_ASSERT(0);
		}

		if (comp == comp_result){	
			pAnm->Work[idx1] = val;
		}
	}
}

//--------------------------------------------------------------
/**
 * ワークに値をセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkVal(POKE_ANIME *pAnm)
{
	u8 idx;
	GetIdx(pAnm, &idx);
	
	ADRS_SHIFT(pAnm->SeqAdrs);
	pAnm->Work[idx] = (int)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * ループ開始
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_StartLoop(POKE_ANIME *pAnm)
{
	GF_ASSERT(pAnm->LoopStartAdrs==NULL&&"ERROR:Loop is moving");
	
	ADRS_SHIFT(pAnm->SeqAdrs);
	//ループ開始アドレスを保存
	pAnm->LoopStartAdrs = pAnm->SeqAdrs;
	//最大ループ回数保存
	pAnm->LoopMax = (int)GetSeqAdrs(pAnm->SeqAdrs);
	pAnm->LoopCount = 0;
}

//--------------------------------------------------------------
/**
 * ループ終了
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_EndLoop(POKE_ANIME *pAnm)
{
	pAnm->LoopCount++;
	if (pAnm->LoopCount >= pAnm->LoopMax){
		//ループ終了
		pAnm->LoopStartAdrs = NULL;
		pAnm->LoopCount = 0;
		pAnm->LoopMax = 0;
	}else{
		//ループ継続
		pAnm->SeqAdrs = pAnm->LoopStartAdrs;	//アドレスを戻す
	}
}

//--------------------------------------------------------------
/**
 * スプライトに値をセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetVal(POKE_ANIME *pAnm)
{
	u8 idx;
	int ss_param;
	//変更パラメータ取得
	GetInt(pAnm,&ss_param);
/**
	GetInt(pAnm,&use);
	if (use == USE_VAL){
		;
	}else if(use == USE_WAORK){
		;
	}else{
		GF_ASSERT(0);
	}
*/	
	GetIdx(pAnm, &idx);
	
	//セット
	SoftSpriteParaSet(pAnm->SoftSprite, ss_param, pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * スプライトに値をアッド
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddVal(POKE_ANIME *pAnm)
{
	u8 idx;
	int ss_param;
	//変更パラメータ取得
	GetInt(pAnm,&ss_param);
	
	GetIdx(pAnm, &idx);
	
	//アッド
	SoftSpriteParaCalc(pAnm->SoftSprite, ss_param, pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * スプライトに値をセット・アッドする
 *
 * @param	pAnm			アニメポインタ
 * @param	
 * @param	
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetAddVal(POKE_ANIME *pAnm)
{
	int ss_param;
	int val;
	
	//変更パラメータ取得
	GetInt(pAnm,&ss_param);
	{
		u8 idx;
		u8 use;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetIdx(pAnm,&idx);
			val = pAnm->Work[idx];
		}else{
			GF_ASSERT(0);
		}
	}

	{
		u8 ss_calc;
		GetU8(pAnm,&ss_calc);
		if (ss_calc == PARAM_SET){
			SoftSpriteParaSet(pAnm->SoftSprite, ss_param, val);
		}else if (ss_calc == PARAM_ADD){
			SoftSpriteParaCalc(pAnm->SoftSprite, ss_param, val);
		}else{
			GF_ASSERT(0);
		}
	}
}

//--------------------------------------------------------------
/**
 * サイン計算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkValSin(POKE_ANIME *pAnm)
{
	u8 idx;
	int dst_rad;
	int l;

	CalcCommonSinCos(pAnm,&idx,&dst_rad,&l);
	
	pAnm->Work[idx] = FX_Whole( FX_SinIdx(dst_rad)*l );
//	OS_Printf("sin=%d\n",pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * コサイン計算
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkValCos(POKE_ANIME *pAnm)
{
	u8 idx;
	int dst_rad;
	int l;

	CalcCommonSinCos(pAnm,&idx,&dst_rad,&l);

	pAnm->Work[idx] = FX_Whole( FX_CosIdx(dst_rad)*l );
}

//--------------------------------------------------------------
/**
 * 移動値をアニメデータ内トランス値にセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetTrans(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//ワークインデックス取得
	GetIdx(pAnm, &idx);

	//変更対象取得
	GetU8(pAnm,&trans);

	if (trans == PARAM_X){
		pAnm->TransX = pAnm->Work[idx];
	}else if (trans == PARAM_Y){
		pAnm->TransY = pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * 移動値をアニメデータ内トランス値にアッド
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddTrans(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//ワークインデックス取得
	GetIdx(pAnm, &idx);

	//変更対象取得
	GetU8(pAnm,&trans);

	if (trans == PARAM_X){
		pAnm->TransX += pAnm->Work[idx];
	}else if (trans == PARAM_Y){
		pAnm->TransY += pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * 値をアニメデータ内値にセット・アッド
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetAddParam(POKE_ANIME *pAnm)
{
	int *target;
	int val;

	{
		u8 param;

		//変更パラメータ取得
		GetU8(pAnm,&param);
		if (param == PARAM_X){
			target = &pAnm->TransX; 
		}else if (param == PARAM_Y){
			target = &pAnm->TransY;
		}else if (param == PARAM_DX){
			target = &pAnm->dx;
		}else if (param == PARAM_DY){
			target = &pAnm->dy;
		}else if (param == PARAM_RX){
			target = &pAnm->rx;
		}else if (param == PARAM_RY){
			target = &pAnm->ry;
		}else if (param == PARAM_ROT){
			target = &pAnm->Rot;
		}else{
			GF_ASSERT(0);
		}
	}
	
	{
		u8 idx;
		u8 use;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetIdx(pAnm,&idx);
			val = pAnm->Work[idx];
		}else{
			GF_ASSERT(0);
		}
	}

	{
		u8 calc;
		GetU8(pAnm,&calc);
		if (calc == PARAM_SET){
			(*target) = val;
		}else if (calc == PARAM_ADD){
			(*target) += val;
		}else{
			GF_ASSERT(0);
		}
	}

}

//--------------------------------------------------------------
/**
 * アニメデータ内トランス値をスプライトに反映
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ApplyTrans(POKE_ANIME *pAnm)
{
	if (pAnm->PokeReverse){
		SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX-(pAnm->TransX+pAnm->dx));
	}else{
		SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX+pAnm->TransX+pAnm->dx);
	}
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_Y, pAnm->OrgY+pAnm->TransY+pAnm->dy);
//	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_OX, pAnm->dx);
//	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_OY, pAnm->dy);
///	OS_Printf("pos_x = %d\n",SoftSpriteParaGet(pAnm->SoftSprite,SS_PARA_POS_X));
}

//--------------------------------------------------------------
/**
 * アニメデータ内回転、拡縮値をスプライトに反映
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ApplyAffine(POKE_ANIME *pAnm)
{
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_X, 0x100+pAnm->rx);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_Y, 0x100+pAnm->ry);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_Z, (u16)pAnm->Rot);

	{
		int correct;
		//dｙ補正するか？
		if (pAnm->CorrectDy == CORRECT_ON_MINUS){
			//拡縮率がマイナスのときに補正する
			if (pAnm->ry < 0){
				CorrectDy(pAnm);
			}
		}else if (pAnm->CorrectDy == CORRECT_ON_NOT_EQ){
			//拡縮率が当倍ではないときに補正する
			if (pAnm->ry != 0){
				CorrectDy(pAnm);
			}
		}else if(pAnm->CorrectDy == CORRECT_OFF){
			return;
		}else{
			GF_ASSERT(0);
		}
	}
}

//--------------------------------------------------------------
/**
 * 移動値(dx.dy)をアニメデータ内D値にセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetD(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//ワークインデックス取得
	GetIdx(pAnm, &idx);
	
	//変更対象取得
	ADRS_SHIFT(pAnm->SeqAdrs);
	trans =  (int)GetSeqAdrs(pAnm->SeqAdrs);
	if ((trans == PARAM_X)||(trans == PARAM_DX)){
		pAnm->dx = pAnm->Work[idx];
	}else if ((trans == PARAM_Y)||(trans == PARAM_DY)){
		pAnm->dy = pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * ウェイトにセット
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWait(POKE_ANIME *pAnm)
{
	//ワークインデックス取得
	GetInt(pAnm, &pAnm->Wait);
	pAnm->Request = 1;
}

//--------------------------------------------------------------
/**
 *　パレットフェード
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_PaletteFade(POKE_ANIME *pAnm)
{
	u8 start,end,wait;
	int rgb;
	
	GetU8(pAnm,&start);
	GetU8(pAnm,&end);
	GetU8(pAnm,&wait);
	GetInt(pAnm,&rgb);

	SoftSpritePalFadeSet(pAnm->SoftSprite, start, end, wait, rgb);
	
}

//--------------------------------------------------------------
/**
 *　パレットフェードウェイト
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_WaitPaletteFade(POKE_ANIME *pAnm)
{
	u8 start,end,wait;

	if( SoftSpritePalFadeExist(pAnm->SoftSprite) ){//フェードの状況をみる
		//フェード継続
		pAnm->PalFadeWaitFlg = 1;
		pAnm->Request = 1;
	}
}


////////////////////////////////////////////////////////////////////////////////
//動作関数セットコマンド

//--------------------------------------------------------------
/**
 * コマンド解釈ホールド
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_HoldAnmCommand(POKE_ANIME *pAnm)
{
	pAnm->CommandHold = 1;
}

//--------------------------------------------------------------
/**
 * DY補正有効フラグコントロール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetDyCorrect(POKE_ANIME *pAnm)
{
	GetU8(pAnm,&pAnm->CorrectDy);
	GF_ASSERT(	(pAnm->CorrectDy==CORRECT_ON_MINUS)||
				(pAnm->CorrectDy==CORRECT_ON_NOT_EQ)||
				(pAnm->CorrectDy==CORRECT_OFF)
			&&"ERROR:Correct Unknown");
}

//--------------------------------------------------------------
/**
 * カーブ関数をコール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncCurve(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_CURVE);
}

//--------------------------------------------------------------
/**
 *　カーブ回数分割関数をコール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncCurveDivTime(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_CURVE_DIVTIME);
}

//--------------------------------------------------------------
/**
 * ライン関数をコール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLine(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE);
}

//--------------------------------------------------------------
/**
 *　ライン回数分割関数をコール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLineDivTime(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE_DIVTIME);
}

//--------------------------------------------------------------
/**
 *　ライン目的値指定関数をコール
 *
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLineDst(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE_DST);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//アニメ動作関数関連

//--------------------------------------------------------------
/**
 * アニメデータ内動作変数に動作関数内動作値を反映
 *
 * @param	inType			適用方法
 * @param	inApplyVal		適用値
 * @param	outTarget		適用対象
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ApplyMoveVal(const u8 inType, const int *inStartVal, const int *inApplyVal, int *outTarget )
{
	if (inType == APPLY_SET){			//セット
		(*outTarget) = (*inApplyVal);
	}else if(inType == APPLY_ADD){		//開始値に加算
		(*outTarget) = (*inStartVal) + (*inApplyVal);
	}else if(inType == APPLY_SYNTHE){	//現在値に加算(合成)
		(*outTarget) += (*inApplyVal);
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 *	変更対象取得
 *
 * @param	inTarget		適用対象
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメデータポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetTarget(	const u8 inTarget, MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm )
{
	switch(inTarget){
	case TARGET_DX:
		pMFD->Target = &pMFD->dx;
		pMFD->ApplyTarget = &pAnm->dx;
		pMFD->StartVal = pAnm->dx;
		break;
	case TARGET_DY:
		pMFD->Target = &pMFD->dy;
		pMFD->ApplyTarget = &pAnm->dy;
		pMFD->StartVal = pAnm->dy;
		break;
	case TARGET_RX:
		pMFD->Target = &pMFD->rx;
		pMFD->ApplyTarget = &pAnm->rx;
		pMFD->StartVal = pAnm->rx;
		break;
	case TARGET_RY:
		pMFD->Target = &pMFD->ry;
		pMFD->ApplyTarget = &pAnm->ry;
		pMFD->StartVal = pAnm->ry;
		break;
	case TARGET_ROT:
		pMFD->Target = &pMFD->Rot;
		pMFD->ApplyTarget = &pAnm->Rot;
		pMFD->StartVal = pAnm->Rot;
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownTarget!");
	}
}

//--------------------------------------------------------------
/**
 * 動作関数コール
 * 動作関数のワークはつめて使うこと
 *
 * @param	pAnm				アニメポインタ
 * @param	inMoveFuncNo		動作関数番号
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CallMoveFuc(POKE_ANIME *pAnm, const int inMoveFuncNo)
{
	u8 i;
	MOVE_FUNC_DATA_PTR ptr;	
	//空いている管理場所に動作関数をセット
	ptr = SetMoveFunc(pAnm,inMoveFuncNo);

	//計算結果適用方法をセット
	GetU8(pAnm,&ptr->ApplyType);

	//関数実行待機時間セット
	GetU8(pAnm,&ptr->Wait);
	
	//動作に必要なパラメータのセット
	for(i=0;i<MoveFuncTbl[inMoveFuncNo].ParamNum;i++){
		GetInt(pAnm,&ptr->Work[i]);
///		OS_Printf("param=%d\n",ptr->Work[i]);
	}

	{
		int idx;
		idx = MoveFuncTbl[inMoveFuncNo].TargetWorkIdx;

///		OS_Printf("workidx = %d:%d\n",idx,ptr->Work[idx]);
		//変更対象の取得
		GetTarget(ptr->Work[idx], ptr, pAnm);
	}

	if (ptr->Wait == 0){
		//初回実行
		ptr->Func(ptr,pAnm);
	}else{
		ptr->Wait--;
	}
}

//--------------------------------------------------------------
/**
 * カーブ移動
 * work0:カーブタイプ（セット済）
 * work1:対象  (セット済)
 * work2:振幅（セット済）
 * work3:加算角度（セット済）
 * work4:位相（セット済）
 * work5:計算回数（セット済）
 * work6:回数のカウント
 *
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_Curve(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	u16 rad;
	
	int *work;
	
	work = pMFD->Work;

	rad = (work[3]*(work[6]+1))+work[4];

	switch(work[0]){
	case CURVE_SIN:
		(*pMFD->Target) = FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS:
		(*pMFD->Target) = FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	case CURVE_SIN_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownCurveType!");
	}
	
	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[6]++;

	if (work[6] >= work[5]){
		//終了
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * カーブ移動	回数分割(決められた実行回数内で、指定値分の移動をする　当然等速)
 * work0:カーブタイプ（セット済）
 * work1:対象 (セット済)
 * work2:振幅（セット済）
 * work3:角度（セット済）
 * work4:位相（セット済）
 * work5:計算回数（セット済）
 * work6:回数のカウント
 *
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_CurveDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	u16 rad;
	
	int *work;
	
	work = pMFD->Work;

	rad = ( (work[3]*(work[6]+1))/work[5] )+work[4];

	switch(work[0]){
	case CURVE_SIN:
		(*pMFD->Target) = FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS:
		(*pMFD->Target) = FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	case CURVE_SIN_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownCurveType!");
	}
	
	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[6]++;

	if (work[6] >= work[5]){
		//終了
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * 直線移動
 * work0:対象  (セット済)
 * work1:初速度（セット済）
 * work2:加速度（セット済）
 * work3:計算回数（セット済）
 * work4:回数のカウント
 *
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_Line(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = work[1]+(work[2]*work[4]);

	(*pMFD->Target)+=move;

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

///	OS_Printf("trans=%d\n",pAnm->TransX);

	work[4]++;

	if (work[4] >= work[3]){
		//終了
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * 直線移動　回数分割(決められた実行回数内で、指定値分の移動をする　当然等速)
 * work0:対象 (セット済)
 * work1:移動値（セット済）
 * work2:計算回数（セット済）
 * work3:回数のカウント
 *
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_LineDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = ( (work[3]+1)*work[1] )/work[2];

	(*pMFD->Target) = move;

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[3]++;

	if (work[3] >= work[2]){
		//終了
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * 直線移動目的値指定
 * work0:対象  (セット済)
 * work1:初速度（セット済）
 * work2:加速度（セット済）
 * work3:目的値（セット済）
 * work4:回数のカウント
 *
 * @param	pMFD			動作関数データポインタ
 * @param	pAnm			アニメポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_LineDst(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = work[1]+(work[2]*work[4]);

	(*pMFD->Target)+=move;

	if ( (pMFD->ApplyType == APPLY_SET) ||
		 (pMFD->ApplyType == APPLY_SYNTHE) ){			//セット
		if (move < 0){		//足しこんだ値がマイナスの場合
			if ((*pMFD->Target) <= work[3]){	//現在値のほうが目的値より小さければ終了
				(*pMFD->Target) = work[3];	//目的値セット
				pMFD->Valid = FALSE;
			}
		}else{				//足しこんだ値がプラスの場合
			if ((*pMFD->Target) >= work[3]){	//現在値のほうが目的値より大きければ終了
				(*pMFD->Target) = work[3];	//目的値セット
				pMFD->Valid = FALSE;
			}
		}
	}else if(pMFD->ApplyType == APPLY_ADD){		//開始値に加算
		int val = pMFD->StartVal+(*pMFD->Target);
		if (move < 0){		//足しこんだ値がマイナスの場合
			if (val <= work[3]){	//現在値のほうが目的値より小さければ終了
				(*pMFD->Target) += (work[3]- val);	//目的値セット
				pMFD->Valid = FALSE;
			}
		}else{				//足しこんだ値がプラスの場合
			if (val >= work[3]){	//現在値のほうが目的値より大きければ終了
				(*pMFD->Target) -= (val - work[3]);	//目的値セット
				pMFD->Valid = FALSE;
			}
		}
	}else{
		GF_ASSERT(0);
	}

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

///	OS_Printf("trans=%d\n",pAnm->TransX);

	work[4]++;
}


