/**
 *	@file	tmap_nrm.c
 *	@brief	タウンマップ　ノーマルモード制御
 *	@date	05.11.02
 *	@author	Miyuki Iwasawa
 */
#include "common.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "field/syswork.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/brightness.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "gflib/touchpanel.h"
#include "application/townmap.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_townmap.h"
#include "msgdata/msg_place_name.h"
#include "tmap.h"
#include "tmap_act.h"
#include "tmap_snd_def.h"
#include "tmap_nrm.dat"
#include "fielddata/maptable/zone_id.h"

//実体はplace_name_core.c
extern void PNC_GetPlaceNameFromZoneID(	const int inZoneID,
										const u32 inHeapID,
										STRBUF *outName);

///足跡表示構造体
#define DIR_NOT			(-1)	///<向きがない場合
#define DIR_UP			(0)		///<上向き
#define DIR_DOWN		(1)		///<下向き
#define DIR_LEFT		(2)		///<左向き
#define DIR_RIGHT		(3)		///<右向き
#define DIR_ROT_UP		(0)
#define DIR_ROT_LEFT	(1)
#define DIR_ROT_DOWN	(2)
#define DIR_ROT_RIGHT	(3)

typedef struct _TMAP_FVIEW{
	int	x;
	int	z;
	u16	dir;	//方向
	u8	idx;
	u8	valid;
	
	CLACT_WORK_PTR	pAct;	///<アクターワーク
}TMAP_FVIEW;
typedef struct _TMAP_FOOTVIEW{
	int	num;	//有効データ数
	TCB_PTR	tcb;	///アニメタスク
	u16	anmct;	///<アニメカウンタ
	u8	now;
	u8	old;
	TMAP_FVIEW	foot[TMAP_FVIEW_MAX];
}TMAP_FOOTVIEW;

typedef struct _TMAP_MODE_NORMAL{
	int	seq;		///<シーク制御
	int	sub_seq;	///<シーク制御
	int	sub_ct;	///<シーク制御
	int	main_ct;	///<シーク制御
	u8	forcus;	///<上下画面どちらに制御がいるか？
	u8	key_f;	///<キーフラグ
	u8	view_f;	///<ビュー更新フラグ
	u8	cmove_f;	///<カーソルが移動中かどうか？
	u8	tp_f;	///<タッチパネルコントロールフラグ
	u8	guide_f:4;	///<ガイド更新フラグ	
	u8	board_f:4;	///<ボードタイプ識別フラグ	
	u16	repeat_f;	///<リピート
	int cposX;		///<現在のカーソル位置(ブロック)
	int cposZ;		///<現在のカーソル位置(ブロック)
	int	czoneID;	///<現在のゾーンID
	int	ozoneID;	///<古いゾーンID
	
	GF_BGL_BMPWIN	win[WIN_MAX];	///<BMPウィンドウデータ
	GF_BGL_BMPWIN*	pBoardWin;	///<ボード用ウィンドウ

	TMAP_SCROLLPRM	scrBGM0;	///<スクロールパラメータ
	TMAP_SCROLLPRM	scrBGS0;	///<スクロールパラメータ

	TMAP_VIEW_DAT*	pTView;	///<タウンViewデータ
	TMAP_GDAT*		pBlock;	///<ブロックデータ

	TMAP_FOOTVIEW	fView;	///<足跡描画

	CLACT_WORK_PTR	pCAW_btn;	///<アクターワーク
	CLACT_WORK_PTR	pCAW_cur;	///<アクターワーク
	CLACT_WORK_PTR	pCAW_hero;	///<アクターワーク

	TCB_PTR			tcb;	//タスクポインタ
}TMAP_MODE_NORMAL;

///プロトタイプ
int	TMapNormal_Init(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Build(TMAP_MAIN_DAT* pMain);
int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Main(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Draw(TMAP_MAIN_DAT* pMain);
int TMapNormal_Release(TMAP_MAIN_DAT *pMain);
int TMapNormal_VBlank(TMAP_MAIN_DAT *pMain);
int TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain);
int TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain);
int TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain);
int TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain);


static void TMap_BoardMsgSet(TMAP_MAIN_DAT* pMain,TMAP_GDAT* pBlock,int zoneID);
static void TMap_BoardGraphicOff(TMAP_MAIN_DAT* pMain);
static void TMap_GuideTagSet(TMAP_MAIN_DAT* pMain,GF_BGL_BMPWIN* win);
static void TMapN_BmpWinSet(TMAP_MAIN_DAT* pMain);
static void TMapN_BmpWinExit(TMAP_MAIN_DAT* pMain);
static void TMapN_SubButtonSet(TMAP_MAIN_DAT* pMain,u8 frm,u8 mode);
static void TMapN_2DGrapDefSet(TMAP_MAIN_DAT* pMain);
static void TMapN_2DGrapClear(TMAP_MAIN_DAT* pMain);
static void TMapN_CellActSet(TMAP_MAIN_DAT* pMain);
static void TMapN_FootViewInit(TMAP_MAIN_DAT* pMain);
static void TMapN_FootViewTask(TCB_PTR tcb,void* work);
static void TMapN_FootViewRelease(TMAP_MAIN_DAT* pMain);

static void TMapN_CheckKeyCursor(TMAP_MAIN_DAT* pMain,int key);
static void TMapN_ZoneNameGet(TMAP_MAIN_DAT *pMain,int zoneID,int x,int z);
static void TMapN_ZoneNameWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,int zoneID,int x,int z);
static void TMapN_BlockExpWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,TMAP_GDAT* pBlock);
static void TMapN_BlockChange(TMAP_MAIN_DAT* pMain);
static void TMapN_BlockReset(TMAP_MAIN_DAT* pMain);
static void TMapN_CursorDrawUp(TMAP_MAIN_DAT* pMain);
static void TMapN_SubScrollSet(TMAP_MAIN_DAT* pMain,int x,int y);


static void TMapNS_AddSVForcusTask(TMAP_MAIN_DAT* pMain,int mode);
static void TMapNS_SVForcusInTask(TCB_PTR tcb,void* work);
static void TMapNS_SVForcusOutTask(TCB_PTR tcb,void* work);

static int TMapJ_CheckJumpPos(TMAP_MAIN_DAT* pMain);

/**
 *	@brief	ノーマルモード初期化
 */
int	TMapNormal_Init(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk;

	pMain->pSwork = sys_AllocMemory(pMain->heapID,sizeof(TMAP_MODE_NORMAL));
	wk = (TMAP_MODE_NORMAL*)pMain->pSwork;
	memset(wk,0,sizeof(TMAP_MODE_NORMAL));

	return TMAP_SEQ_FINISH;	
}

/**
 *	@brief	ノーマルモード解放
 */
int TMapNormal_Release(TMAP_MAIN_DAT *pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//ビュークリア
	TMapN_2DGrapClear(pMain);
	if(pMain->mode != TMAP_MBG){
		TMapN_FootViewRelease(pMain);
	}
	TownViewDataRelease(wk->pTView);
	TMapN_BmpWinExit(pMain);
	sys_FreeMemoryEz(wk);
	return TMAP_SEQ_FINISH;	
}

/**
 *	@brief	ノーマルモードデータ構築
 */
int	TMapNormal_Build(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	switch(wk->seq){
	case 0:
		//メインからのデータ引継ぎ
		wk->cposX = pMain->cposX;
		wk->cposZ = pMain->cposZ;
		wk->czoneID = -1;	//ダミー値
		//サブ画面カーソル位置描画
		wk->scrBGS0.scrX = (wk->cposX*TMAP_SBLOCK_UNIT+8)	- 128+16;
		wk->scrBGS0.scrY = (wk->cposZ*TMAP_SBLOCK_UNIT)	- 96;

		TMapN_SubScrollSet(pMain,wk->scrBGS0.scrX,wk->scrBGS0.scrY);

		//Bmpウィンドウ初期化
		TMapN_BmpWinSet(pMain);
		
		//足跡マーク
		if(pMain->mode != TMAP_MBG){
			TMapN_FootViewInit(pMain);
		}
		break;
	case 1:
		//2DGrapSet
		TMapN_2DGrapDefSet(pMain);

		//セルアクター追加
		TMapN_CellActSet(pMain);
		
		//タウンView作成
		wk->pTView = TownViewDataCreate(pMain->pCActSys,pMain->pCActRes,
				pMain->param->arrive,TOWN_VIEW_MAX,pMain->heapID);
	
		TMapN_BlockReset(pMain);
		TMapN_BlockChange(pMain);
		wk->seq = 0;
		return TMAP_SEQ_FINISH;
	}
	wk->seq++;
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	ノーマルモード　フェードイン
 */
int TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_FMAS,
			WIPE_TYPE_HOLEIN,
			WIPE_TYPE_TUNNELIN_TOP,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MOPEN);

	WIPE_ResetBrightness(WIPE_DISP_MAIN);
	WIPE_ResetBrightness(WIPE_DISP_SUB);
	//ブレンド設定
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,GX_BLEND_PLANEMASK_BG3,28,4);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	ノーマルモード　フェードアウト
 */
int TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_FSAM,
			WIPE_TYPE_HOLEOUT,
			WIPE_TYPE_TUNNELOUT_TOP,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MCLOSE);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	BGモード　フェードイン
 */
int TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_M,
			WIPE_TYPE_HOLEIN,
			WIPE_TYPE_HOLEIN,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MOPEN);

	WIPE_ResetBrightness(WIPE_DISP_MAIN);
//	WIPE_ResetBrightness(WIPE_DISP_SUB);
	//ブレンド設定
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,GX_BLEND_PLANEMASK_BG3,28,4);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	BGモード　フェードアウト
 */
int TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_M,
			WIPE_TYPE_HOLEOUT,
			WIPE_TYPE_HOLEOUT,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MCLOSE);
//	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	ノーマルモードキー取得
 */
int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(	wk->tp_f <= 1 &&
		sys.trg & PAD_BUTTON_CANCEL){
		Snd_SePlay(SND_TMAP_CANCEL);
		return TMAP_SEQ_FINISH;	
	}
	if(wk->tp_f > 1){
		//サブ画面切り替え中はキー検知しない
		return TMAP_SEQ_CONTINUE;
	}
	TMapN_CheckKeyCursor(pMain,sys.cont);

	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	ジャンプモードキー取得	キーウェイトモード
 */
int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(wk->tp_f <= 1){	//タッチパネルタスクが動いているときは終了しない
		if(sys.trg & PAD_BUTTON_DECIDE){
			if(TMapJ_CheckJumpPos(pMain)){
				Snd_SePlay(SND_TMAP_DECIDE);
				return TMAP_SEQ_FINISH;
			}
			return TMAP_SEQ_CONTINUE;
		}else if(sys.trg & PAD_BUTTON_CANCEL){
			Snd_SePlay(SND_TMAP_CANCEL);
			return TMAP_SEQ_FINISH;
		}
	}
	if(wk->tp_f > 1){
		//サブ画面切り替え中はキー検知しない
		return TMAP_SEQ_CONTINUE;
	}

	TMapN_CheckKeyCursor(pMain,sys.cont);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	BGモードキー取得
 */
int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(	sys.trg & (PAD_BUTTON_CANCEL)){
		Snd_SePlay(SND_TMAP_CANCEL);
		return TMAP_SEQ_FINISH;	
	}

	TMapN_CheckKeyCursor(pMain,sys.cont);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	ノーマルモード　メインコントロール
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
int TMapNormal_Main(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(wk->view_f & VIEW_UP){
		//ブロック更新
		if(wk->guide_f >= 2){
			TMapN_BlockChange(pMain);
			wk->view_f = VIEW_CLEAR;
			wk->repeat_f = 0;
			wk->guide_f = 0;
		}
	}else if(wk->forcus == TMAPN_FORCUS_SUB && wk->repeat_f == 1){
		TMap_BoardMsgSet(pMain,NULL,wk->czoneID);		
	}

	TMapN_CursorDrawUp(pMain);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	ノーマルモード　Drawシーケンス
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
int TMapNormal_Draw(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FVIEW *wp;
	int i;

	//足跡描画
	for(i = 0;i < wk->fView.num;i++){
		wp = &(wk->fView.foot[i]);
	}

	TownViewDataDraw(wk->pTView,pMain->mode);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	看板フレーム VBlank転送
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
int TMapNormal_VBlank(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	GF_BGL_BMPWIN* win;
	TMAP_GDAT* pBlock = pMain->vb_block;
	int	zoneID = pMain->vb_zoneID;

	u32	siz;
	GF_PRINTCOLOR col;
	STRCODE name[BUFLEN_PLACE_NAME];

	if(!pMain->vb_trans){
		return TMAP_SEQ_CONTINUE;
	}
	//フラグOff
	pMain->vb_trans = 0;

	//処理
	if(pBlock == NULL){
		//ブロックデータ無し
		TMapN_BlockExpWrite(pMain,&(wk->win[WIN_BLOCK]),NULL);
		TMap_BoardGraphicOff(pMain);
		return TMAP_SEQ_CONTINUE;
	}
	TMapN_BlockExpWrite(pMain,&(wk->win[WIN_BLOCK]),pBlock);
	
	//ボードメッセージ描画
	STRBUF_Clear(pMain->placeName);
	TMapN_ZoneNameGet(pMain,zoneID,wk->cposX,wk->cposZ);
	
	BoardWinGraphicSet(	pMain->bgl,
			BMPL_BOARD_FRM,BMPW_BOARD_CGX,BMPL_BOARD_PAL,
			pBlock->kType, pBlock->kIdx,pMain->heapID);

	if(pBlock->kType == BOARD_TYPE_TOWN || pBlock->kType == BOARD_TYPE_ROAD){
		win = &wk->win[WIN_BOARD0];
	}else{
		win = &wk->win[WIN_BOARD1];
	}
	//これから描くウィンドウを憶えておく
	wk->pBoardWin = win;
	wk->board_f = pBlock->kType;
	
	BmpBoardWinWrite(win, WINDOW_TRANS_OFF,
			BMPW_BOARD_CGX,BMPL_BOARD_PAL,/*BOARD_TYPE_TOWN*/pBlock->kType);
	
	GF_BGL_BmpWinDataFill(win,FBMP_COL_WHITE);
	GF_STR_PrintSimple(	win,
					FONT_TALK,
					pMain->placeName,
					0,0,
					MSG_NO_PUT,
					NULL );

	GF_BGL_BmpWinOn(win);
	GF_BGL_BmpWinOn(&wk->win[WIN_BLOCK]);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	タッチパネルチェック
 */
static int TMapNS_TPCheck(TMAP_MAIN_DAT* pMain,int mode)
{
	int ret;
	u16 pat;
	static const RECT_HIT_TBL TMapN_TpRect[] = {
		{0,191,0,255},
		{TMSCR_DSWMB_DPY*8,TMSCR_DSWMB_DEY*8,TMSCR_DSWMB_DPX*8,TMSCR_DSWMB_DEX*8},
		{RECT_HIT_END,0,0,0}
	};
	
	ret = GF_TP_RectHitTrg(&(TMapN_TpRect[1-mode]));
	if(ret == RECT_HIT_NONE || mode == TMAPN_FORCUS_SUB){
		return ret;
	}
	pat = 0x0012;	//0000 0011 1111 1111	無効パレットbit(onになっている色Noは反応させない)
	if(GF_BGL_DotCheck(pMain->bgl,GF_BGL_FRAME1_S,sys.tp_x,sys.tp_y,&pat) == FALSE){
		return ret;
	}
	return RECT_HIT_NONE;
}

/**
 *	@brief	タッチパネルチェック
 */
static BOOL TMapNS_TPCheckCall(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(pMain->param->mode == TMAP_MBG){
		return FALSE;	//BGモードはタッチパネルチェック無し
	}
	if(GF_TP_GetCont()){
		if(wk->tp_f == 0 && TMapNS_TPCheck(pMain,wk->forcus) != RECT_HIT_NONE){
			TMapNS_AddSVForcusTask(pMain,wk->forcus);
			wk->tp_f = 3;
			return TRUE;
		}
	}else if(wk->tp_f == 3 || wk->tp_f == 1){
		wk->tp_f--;
	}
	return FALSE;
}

/**
 *	@brief	カーソル移動キーチェック
 */
static void TMapN_CheckKeyCursor(TMAP_MAIN_DAT* pMain,int key)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(wk->key_f){
		if(!(key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_RIGHT|PAD_KEY_LEFT))){
			if(wk->guide_f == 1){	//押しっぱなしチェック
				++wk->guide_f;
			}
		}
		return;	//カーソル移動中
	}

	//タッチパネルチェック
	if(TMapNS_TPCheckCall(pMain)){
		return;
	}

	if(!(key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_RIGHT|PAD_KEY_LEFT))){
		if(wk->guide_f == 1){
			++wk->guide_f;
		}
		return;
	}
	if(key & PAD_KEY_UP){
		if(wk->cposZ >= CMOVE_MINZ){
			wk->cposZ -= 1;
			wk->key_f |= KEYS_CMOVE_MZ;
		}
	}
	if(key & PAD_KEY_DOWN){
		if(wk->cposZ <= CMOVE_MAXZ){
			wk->cposZ += 1;
			wk->key_f |= KEYS_CMOVE_PZ;
		}
	}
	if(key & PAD_KEY_RIGHT){
		if(wk->cposX <= CMOVE_MAXX){
			wk->cposX += 1;
			wk->key_f |= KEYS_CMOVE_PX;
		}
	}
	if(key & PAD_KEY_LEFT){
		if(wk->cposX >= CMOVE_MINX){
			wk->cposX -= 1;
			wk->key_f |= KEYS_CMOVE_MX;
		}
	}
	wk->cmove_f = CMOVE_COUNT;
	wk->key_f |= KEYS_FREEZE;	//キーフック

	if(wk->view_f != 0){
		wk->repeat_f++;
	}else{
		wk->repeat_f = 0;
	}
	wk->view_f = 0;
	wk->guide_f = 1;
	return;
}

/**
 *	@brief	カーソル移動ブロック切り替え
 */
static void TMapN_BlockChange(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	//地名表示書き換え
	TMapN_ZoneNameWrite(
		pMain,&(wk->win[WIN_M01]),wk->czoneID,wk->cposX,wk->cposZ);
	
	//空を飛ぶポジションチェック
	TownViewDataSelectPos(wk->pTView,wk->czoneID,wk->cposX,wk->cposZ);
	
	if(wk->forcus == TMAPN_FORCUS_SUB){
		//ブロック説明書き換え
		TMap_BoardMsgSet(pMain,wk->pBlock,wk->czoneID);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	}
}

/**
 *	@brief	カーソル移動ブロック切り替え
 */
static void TMapN_BlockReset(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	//現在のゾーンを取得
	wk->ozoneID = wk->czoneID;
	wk->czoneID = GetFieldMatrixZoneID((FMZ_CONST_PTR)pMain->pZone,wk->cposX,wk->cposZ);

	//現在のブロックデータを取得
	wk->pBlock = TMapBlockDataGet(pMain->pBDat,wk->cposX,wk->cposZ,pMain->mapView);
}

typedef struct _SP_ZONE_NAME{
	u16	x;
	u16	z;
	int	zoneID;
}SP_ZONE_NAME;

/**
 *	@brief	フィールドマトリクスゾーンIDとx,z座標から、表示する地名文字列を決める
 */
static void TMapN_ZoneNameGet(TMAP_MAIN_DAT *pMain,int zoneID,int x,int z)
{
	int i;
	
	static const SP_ZONE_NAME spZone[] = {
		{11,19,ZONE_ID_D05R0101},
		{11,20,ZONE_ID_D05R0101},
		{11,21,ZONE_ID_D05R0101},
		{11,22,ZONE_ID_D05R0101},
		{12,12,ZONE_ID_D05R0101},
		{12,13,ZONE_ID_D05R0101},
		{12,14,ZONE_ID_D05R0101},
		{12,15,ZONE_ID_D05R0101},
		{12,16,ZONE_ID_D05R0101},
		{12,17,ZONE_ID_D05R0101},
		{12,18,ZONE_ID_D05R0101},
		{12,19,ZONE_ID_D05R0101},
		{20,12,ZONE_ID_D31},
	};
	if(zoneID != 0)	{
		//フィールドマトリクスゾーンIDから取得
		PNC_GetPlaceNameFromZoneID(zoneID,pMain->heapID,pMain->placeName);
		return;
	}
	//フィールドマトリクス上にないゾーン名を座標から取得する
	for(i = 0;i < NELEMS(spZone);i++){
		if(spZone[i].x !=  x || spZone[i].z != z){
			continue;
		}
		//該当場所見つかった
		PNC_GetPlaceNameFromZoneID(spZone[i].zoneID,pMain->heapID,pMain->placeName);
		return;	
	}
	//名前のない場所用の文字列を表示
	PNC_GetPlaceNameFromZoneID(0,pMain->heapID,pMain->placeName);
	return;
}

/**
 *	@brief	ゾーン名の表示関数
 *
 */
static void TMapN_ZoneNameWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,int zoneID,int x,int z)
{
	u32	siz;
	GF_PRINTCOLOR col;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	STRBUF_Clear(pMain->placeName);
	
	GF_BGL_BmpWinDataFill(win,0);
	col = GF_PRINTCOLOR_MAKE(1,2,0);
//	if(zoneID > 0 && wk->pBlock != NULL){
	if(wk->pBlock != NULL){
//		GetPlaceNameFromZoneID(zoneID,pMain->heapID,pMain->placeName);
		TMapN_ZoneNameGet(pMain,zoneID,x,z);

		if(pMain->mode == TMAP_MJUMP){
			siz = BMPL_M01_NSX;
		}else{
			siz = (BMPL_M01_SX*8)-FontProc_GetPrintStrWidth(FONT_SYSTEM,pMain->placeName,0);
			siz/=2;
		}
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							pMain->placeName,
							siz,BMPL_M01_WINY,
							MSG_NO_PUT,
							col,
							NULL );
	}

	//どこへ飛びますか？
	if(pMain->mode == TMAP_MJUMP){
		STRBUF* buf_q = MSGMAN_AllocString(pMain->pMsgTMap,mes_townmap_01_01);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							buf_q,
							0,BMPL_M01_WINY,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(buf_q);
	}

	GF_BGL_BmpWinOn(win);
}

/**
 *	@brief	ブロック説明の表示関数
 *
 */
static void TMapN_BlockExpWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,TMAP_GDAT* pBlock)
{
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *ex1;
	STRBUF *ex2;
	
	if(pBlock == NULL){
		//ウィンドウクリア
#if	S2410_060815_FIX
		/*マスター後バグfix 説明テキストチラつき不具合解消*/
		GF_BGL_BmpWinDataFill(win,0);
		GF_BGL_BmpWinOn(win);
#endif
		GF_BGL_BmpWinOff(win);
		return;
	}
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_BGL_BmpWinDataFill(win,0);

	if(	(pBlock->gmes01 != 0xFFFF) &&
		(pMain->param->flags[pBlock->id].ex01_f == 0 ||
		 pMain->param->flags[pBlock->id].ex01)){
		ex1 = MSGMAN_AllocString(pMain->pMsgTMap,pBlock->gmes01);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							ex1,
							pBlock->gmes01_ox,pBlock->gmes01_oy,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(ex1);
	}
	if(	(pBlock->gmes02 != 0xFFFF) &&
		(pMain->param->flags[pBlock->id].ex02_f == 0 ||
		 pMain->param->flags[pBlock->id].ex02)){
		ex2 = MSGMAN_AllocString(pMain->pMsgTMap,pBlock->gmes02);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							ex2,
							pBlock->gmes02_ox,pBlock->gmes02_oy,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(ex2);
	}
}
/**
 *	@brief	カーソルの描画場所更新
 */
static void TMapN_CursorDrawUp(TMAP_MAIN_DAT* pMain)
{
	int	dif = SUBSCR_MOVE_UNIT;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(!wk->cmove_f){
		return;
	}
	if(wk->cmove_f-- == CMOVE_COUNT){
		//カーソル移動
		CATS_ObjectPosSet(wk->pCAW_cur,
				wk->cposX*CMOVE_UNIT+CMOVE_OFSX,
				wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);
		CLACT_AnmFrameChg(wk->pCAW_cur,FX32_ONE);	//アニメパターンリセット

		//ブロックデータリセット
		TMapN_BlockReset(pMain);

		//上画面ゾーン名表示リライト
		TMapN_ZoneNameWrite(
			pMain,&(wk->win[WIN_M01]),
			GetFieldMatrixZoneID((FMZ_CONST_PTR)pMain->pZone,wk->cposX,wk->cposZ),wk->cposX,wk->cposZ);
		dif += 1;
	}
	
	if(wk->key_f & KEYS_CMOVE_MZ){
		wk->scrBGS0.scrY -= dif;
	}
	if(wk->key_f & KEYS_CMOVE_PZ){
		wk->scrBGS0.scrY += dif;
	}
	if(wk->key_f & KEYS_CMOVE_PX){
		wk->scrBGS0.scrX += dif;
	}
	if(wk->key_f & KEYS_CMOVE_MX){
		wk->scrBGS0.scrX -= dif;
	}
	TMapN_SubScrollSet(pMain,wk->scrBGS0.scrX,wk->scrBGS0.scrY);

	if(wk->cmove_f > 0){
		return;
	}
	wk->view_f = VIEW_UP;	//view更新
	wk->key_f = 0;	//キーフック解除

	if(wk->ozoneID != wk->czoneID){
		TownViewDataSelectPos(wk->pTView,-1,0,0);
	}
}

/**
 *	@brief	看板フレームメッセージ表示
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static void TMap_BoardMsgSet(TMAP_MAIN_DAT* pMain,TMAP_GDAT* pBlock,int zoneID)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *name;

	//パラメータ保存(実際の更新はVBlank中に行う)
	pMain->vb_zoneID = zoneID;
	pMain->vb_block = pBlock;
	pMain->vb_trans = 1;
	return;
}

/**
 *	@brief	看板フレーム表示Off
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static void TMap_BoardGraphicOff(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	GF_BGL_BMPWIN	*win;
	
	win = wk->pBoardWin;
	wk->pBoardWin = NULL;
	if(win == NULL){
		return;
	}

	GF_BGL_BmpWinDataFill(win,FBMP_COL_NULL);
	GF_BGL_BmpWinOff(win);
	
	BmpBoardWinClear(win,wk->board_f,WINDOW_TRANS_ON);
	GF_BGL_LoadScreenV_Req(pMain->bgl,BMPL_BOARD_FRM);
}


/**
 *	@brief	ガイドタグ表示
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static void TMap_GuideTagSet(TMAP_MAIN_DAT* pMain,GF_BGL_BMPWIN* win)
{
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *buf;

	//BG描画
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME1_S,
			TMSCR_DSWMG_DPX,TMSCR_DSWMG_DPY,TMSCR_DSWMG_DSX,TMSCR_DSWMG_DSY,
			pMain->pScr02_dswm->rawData,
			TMSCR_DSWMG_SPX,TMSCR_DSWMG_SPY,
			pMain->pScr02_dswm->screenWidth/8,pMain->pScr02_dswm->screenHeight/8);

	//メッセージ描画
	buf = MSGMAN_AllocString(pMain->pMsgTMap,mes_townmap_02_01);

	siz = BMPL_GUIDE_NSX-FontProc_GetPrintStrWidth( FONT_SYSTEM,buf, 0 );
	siz/=2;
	
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_BGL_BmpWinDataFill(win,FBMP_COL_NULL);
	GF_STR_PrintColor(	win,
						FONT_SYSTEM,
						buf,
						siz,0,
						MSG_NO_PUT,
						col,
						NULL );
	GF_BGL_BmpWinOn(win);

	STRBUF_Delete(buf);
}

/**
 *	@brief	BmpWindow初期化
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static void TMapN_BmpWinSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_M01], BMPL_M01_FRM,
		BMPL_M01_PX, BMPL_M01_PY, BMPL_M01_SX, BMPL_M01_SY, BMPL_M01_PAL, BMPL_M01_CGX );
	
	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BOARD0], BMPL_BOARD_FRM,
		BMPL_BOARD0_PX, BMPL_BOARD0_PY, BMPL_BOARD0_SX, BMPL_BOARD0_SY, BMPL_BOARD_PAL, BMPL_BOARD0_CGX );
	
	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BOARD1], BMPL_BOARD_FRM,
		BMPL_BOARD1_PX, BMPL_BOARD1_PY, BMPL_BOARD1_SX, BMPL_BOARD1_SY, BMPL_BOARD_PAL, BMPL_BOARD1_CGX );

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BLOCK], BMPL_BLOCK_FRM,
		BMPL_BLOCK_PX, BMPL_BLOCK_PY, BMPL_BLOCK_SX, BMPL_BLOCK_SY, BMPL_BLOCK_PAL, BMPL_BLOCK_CGX );

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_GUIDE], BMPL_GUIDE_FRM,
		BMPL_GUIDE_PX, BMPL_GUIDE_PY, BMPL_GUIDE_SX, BMPL_GUIDE_SY, BMPL_GUIDE_PAL, BMPL_GUIDE_CGX );

	//ウィンドウクリア
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_M01]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BOARD0]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BOARD1]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BLOCK]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_GUIDE]),0);
	GF_BGL_BmpWinOn(&wk->win[WIN_M01]);

	GF_BGL_BmpWinOff(&wk->win[WIN_BOARD0]);
	GF_BGL_BmpWinOff(&wk->win[WIN_BOARD1]);
	GF_BGL_BmpWinOff(&wk->win[WIN_BLOCK]);
	GF_BGL_BmpWinOff(&wk->win[WIN_GUIDE]);

}

/**
 *	@brief	BmpWindow解放
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static void TMapN_BmpWinExit(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	u16	i;
	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinDel(&wk->win[i]);
	}
}

/**
 *	@brief	ボタンスクリーン描画
 *
 *	@param	pMain	TMAP_MAIN_DAT*
 *	@param	frm		アニメフレームNo
 *	@param	mode	バックを書き込むかどうかのフラグ(書き込むときはOn)
 */
static void TMapN_SubButtonSet(TMAP_MAIN_DAT* pMain,u8 frm,u8 mode)
{
	if(mode){
		GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME1_S,
			0,0,32,24,
			pMain->pScr02_sw->rawData,
			0,0,
			pMain->pScr02_sw->screenWidth/8,pMain->pScr02_sw->screenHeight/8);
	}
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME1_S,
		TMSCR_DSWMB_DPX,TMSCR_DSWMB_DPY,TMSCR_DSWMB_DSX,TMSCR_DSWMB_DSY,
		pMain->pScr02_dswm->rawData,
		frm*TMSCR_DSWMB_DSX+TMSCR_DSWMB_SPX,TMSCR_DSWMB_SPY,
		pMain->pScr02_dswm->screenWidth/8,pMain->pScr02_dswm->screenHeight/8);
}

/**
 *	@brief	配布マップ描画　サブルーチン
 *	
 */
	typedef struct _HMAP{
		u8	dpx,dpy;
		u8	px,py;
		u8	sx,sy;
	}HMAP;
	
static void TMap_HaifuMapSet(TMAP_MAIN_DAT* pMain,int mode)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	static const HMAP hmap[] = {
		{HMAP01_MB_DPX,HMAP01_MB_DPY,HMAP01_MB_PX,HMAP01_MB_PY,HMAP01_MB_SX,HMAP01_MB_SY},
		{HMAP01_ML_DPX,HMAP01_ML_DPY,HMAP01_ML_PX,HMAP01_ML_PY,HMAP01_ML_SX,HMAP01_ML_SY},
		{HMAP01_SB_DPX,HMAP01_SB_DPY,HMAP01_SB_PX,HMAP01_SB_PY,HMAP01_SB_SX,HMAP01_SB_SY},
		{HMAP01_SL_DPX,HMAP01_SL_DPY,HMAP01_SL_PX,HMAP01_SL_PY,HMAP01_SL_SX,HMAP01_SL_SY},
		
		{HMAP02_MB_DPX,HMAP02_MB_DPY,HMAP02_MB_PX,HMAP02_MB_PY,HMAP02_MB_SX,HMAP02_MB_SY},
		{HMAP02_ML_DPX,HMAP02_ML_DPY,HMAP02_ML_PX,HMAP02_ML_PY,HMAP02_ML_SX,HMAP02_ML_SY},
		{HMAP02_SB_DPX,HMAP02_SB_DPY,HMAP02_SB_PX,HMAP02_SB_PY,HMAP02_SB_SX,HMAP02_SB_SY},
		{HMAP02_SL_DPX,HMAP02_SL_DPY,HMAP02_SL_PX,HMAP02_SL_PY,HMAP02_SL_SX,HMAP02_SL_SY},
		
		{0,0,0,0,0,0},
		{HMAP03_ML_DPX,HMAP03_ML_DPY,HMAP03_ML_PX,HMAP03_ML_PY,HMAP03_ML_SX,HMAP03_ML_SY},
		{0,0,0,0,0,0},
		{HMAP03_SL_DPX,HMAP03_SL_DPY,HMAP03_SL_PX,HMAP03_SL_PY,HMAP03_SL_SX,HMAP03_SL_SY},
		
		{HMAP04_MB_DPX,HMAP04_MB_DPY,HMAP04_MB_PX,HMAP04_MB_PY,HMAP04_MB_SX,HMAP04_MB_SY},
		{HMAP04_ML_DPX,HMAP04_ML_DPY,HMAP04_ML_PX,HMAP04_ML_PY,HMAP04_ML_SX,HMAP04_ML_SY},
		{HMAP04_SB_DPX,HMAP04_SB_DPY,HMAP04_SB_PX,HMAP04_SB_PY,HMAP04_SB_SX,HMAP04_SB_SY},
		{HMAP04_SL_DPX,HMAP04_SL_DPY,HMAP04_SL_PX,HMAP04_SL_PY,HMAP04_SL_SX,HMAP04_SL_SY},
	};
	HMAP* mback,*mload,*sback,*sload;

	mback = (HMAP*)&(hmap[mode*4+0]);
	mload = (HMAP*)&(hmap[mode*4+1]);
	sback = (HMAP*)&(hmap[mode*4+2]);
	sload = (HMAP*)&(hmap[mode*4+3]);

	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME2_M,
			mload->px,mload->py,mload->sx,mload->sy,
			pMain->pScr01_dis->rawData,
			mload->dpx,mload->dpy,SCWS_GET(pMain->pScr01_dis),SCHS_GET(pMain->pScr01_dis));	

	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME2_S,
			sload->px,sload->py,sload->sx,sload->sy,pMain->pScr02_dis->rawData,
			sload->dpx,sload->dpy,SCWS_GET(pMain->pScr02_dis),SCHS_GET(pMain->pScr02_dis));
	
	if(mode == HIDEMAP_ID_L04){
		return;
	}
	//背景マップ
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
			mback->px,mback->py,mback->sx,mback->sy,
			pMain->pScr01_dis->rawData,
			mback->dpx,mback->dpy,SCWS_GET(pMain->pScr01_dis),SCHS_GET(pMain->pScr01_dis));	

	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME3_S,
			sback->px,sback->py,sback->sx,sback->sy,pMain->pScr02_dis->rawData,
			sback->dpx,sback->dpy,SCWS_GET(pMain->pScr02_dis),SCHS_GET(pMain->pScr02_dis));
}

/**
 *	@brief ノーマルモード　BGデータセット
 */
static void TMapN_2DGrapDefSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	int sp = 0;
	
	//ロード
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME2_M,
			0,0,32,24,
			pMain->pScr01->rawData,
			0,0,SCWS_GET(pMain->pScr01),SCHS_GET(pMain->pScr01));	

	//背景マップ
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
			0,0,32,24,
			pMain->pScr01_back->rawData,
			0,0,SCWS_GET(pMain->pScr01_back),SCHS_GET(pMain->pScr01_back));	
	
	if(pMain->mode != TMAP_MJUMP){
		sp = ZONEN_BG_SY;
		GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
				ZONEN_BG_PX,ZONEN_BG_PY,ZONEN_BG_SX,ZONEN_BG_SY,
				pMain->pScr01_back->rawData,
				0,ZONEN_BG_PY,SCWS_GET(pMain->pScr01_back),SCHS_GET(pMain->pScr01_back));	
	}
	
	//サブ
	TMapN_SubButtonSet(pMain,0,1);
	
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME2_S,0,0,64,64,pMain->pScr02_dr->rawData,
			0,0,pMain->pScr02_dr->screenWidth/8,pMain->pScr02_dr->screenHeight/8);
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME3_S,0,0,64,64,pMain->pScr02_dm->rawData,
			0,0,pMain->pScr02_dm->screenWidth/8,pMain->pScr02_dm->screenHeight/8);

	//配布マップの描画
//	pMain->mapView = 0x0F;
	if(pMain->mapView & 0x0001){	//配布マップ1 D15
		TMap_HaifuMapSet(pMain,0);
	}
	if(pMain->mapView & 0x0002){	//配布マップ2 D30
		TMap_HaifuMapSet(pMain,1);
	}
	if(pMain->mapView & 0x0004){	//配布マップ3 L4
		TMap_HaifuMapSet(pMain,2);
	}
	if(pMain->mapView & 0x0008){	//配布マップ4 D18
		TMap_HaifuMapSet(pMain,3);
	}
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_S);
}

static void TMapN_2DGrapClear(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//スクロールリセット
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,0);
	
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME2_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME3_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME2_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME3_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_M);
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_S);
}

/**
 *	@brief ノーマルモード　アクターセット
 */
static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
{
	{	// ボタンエフェクト
		0,	//ID
		0, 0, 0,	//x,y,z
		0, TMAP_SPRI_BTN, 0, NNS_G2D_VRAM_TYPE_2DSUB,	//anmNO,pri,pal,d_area
		0, 0, 0, 0	//prm1,prm2,prm3,prm4
	},
	{	// メインカーソル 
		1,
		0, 0, 0,
		0, TMAP_SPRI_CUR, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{	// メイン自機 
		2,
		0, 0, 0,
		0, TMAP_SPRI_HERO, 1, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
};

static void TMapN_CellActSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//サブ画面用ボタン
	wk->pCAW_btn =	CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[0] );

	CLACT_SetDrawFlag(wk->pCAW_btn, 0 );
	CLACT_SetAnmFrame(wk->pCAW_btn,FX32_ONE);
	CATS_ObjectPosSet(wk->pCAW_btn,128,108);

	//メインカーソル
	wk->pCAW_cur =	CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[1] );

	CLACT_SetDrawFlag(wk->pCAW_cur, 1 );
	CLACT_SetAnmFrame(wk->pCAW_cur,FX32_CONST(2));
	CLACT_SetAnmFlag(wk->pCAW_cur,1);
	CATS_ObjectPosSet(wk->pCAW_cur,
			wk->cposX*CMOVE_UNIT+CMOVE_OFSX,wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);

	//メイン自機
	wk->pCAW_hero = CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[2]);

	CLACT_SetDrawFlag(wk->pCAW_hero,1);
	CLACT_AnmFrameSet(wk->pCAW_hero,pMain->param->player_sex);
	CATS_ObjectPosSet(wk->pCAW_hero,
			wk->cposX*CMOVE_UNIT+CMOVE_OFSX,wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);
}

/**
 *	@brief	ノーマルモードサブ画面スクロール値セット	
 */
static void TMapN_SubScrollSet(TMAP_MAIN_DAT* pMain,int x,int y)
{
	if(x < TMAPN_BGS0X_MIN){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MIN);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MIN);
	}else if(x > TMAPN_BGS0X_MAX){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MAX);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MAX);
	}else{
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,x);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,x);
	}
	
	if(y < TMAPN_BGS0Y_MIN){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MIN);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MIN);
	}else if(y > TMAPN_BGS0Y_MAX){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MAX);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MAX);
	}else{
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,y);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,y);
	}
}

/**
 *	@brief ノーマルモード　足跡データ初期化
 */
static int TMapNS_IsFootMarkHit(TMAP_FOOTVIEW* pv,int x,int z)
{
	int i = 0;
	
	for(i = 0;i < pv->num;i++){
		if(pv->foot[i].x == x && pv->foot[i].z == z){
			return i;
		}
	}
	return -1;
}

/**
 *	@brief	ノーマルモード　足跡マークリソース作成
 */
static void TMapN_FootViewInit(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FOOT	*wp;
	TMAP_FVIEW	*dest;
	int i = 0,ret,idx;

	//上,下,右,左
	static const u16 dirTable[4] = {DIR_ROT_UP,DIR_ROT_DOWN,DIR_ROT_RIGHT,DIR_ROT_LEFT};
	static const TCATS_OBJECT_ADD_PARAM	ActAddParam =
	{
		TMAP_ACTID_FOOT,	//ID
		0, 0, 0,	//x,y,z
		0, TMAP_SPRI_FOOT, TMAP_APAL_FOOT, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
		0, 0, 0, 0	//prm1,prm2,prm3,prm4
	};

	//データ解析
	MI_CpuClear8(&(wk->fView),sizeof(TMAP_FOOTVIEW));
	for(i = 0;i < TMAP_FVIEW_MAX;i++){
		wp = &(pMain->param->foot[i]);
		if(wp->valid == 0){
			break;
		}
		if(wp->x == pMain->gx && wp->z == pMain->gz){
			continue;	//現在の自機位置はスルー
		}
		ret = TMapNS_IsFootMarkHit(&(wk->fView),wp->x,wp->z);
		if(ret < 0){
			dest = &(wk->fView.foot[wk->fView.num++]);
		}else{
			dest = &(wk->fView.foot[ret]);
		}
		dest->x = wp->x;
		dest->z = wp->z;
		if(wp->dir > DIR_RIGHT){
			dest->dir = 0;
			idx = 5;
		}else{
			dest->dir = dirTable[wp->dir];
			idx = 0;
		}
		dest->idx = i;//(TMAP_FVIEW_MAX-1)-i;
		dest->valid = 1;

		dest->pAct = CATS_ObjectAdd(pMain->pCActSys,
				pMain->pCActRes,&(ActAddParam));

		CATS_ObjectPosSet(dest->pAct,
				dest->x*TMAP_MDOT_UNIT+TMAP_MDOT_OFSX,
				dest->z*TMAP_MDOT_UNIT+TMAP_MDOT_OFSZ);
//		CLACT_AnmFrameChg(dest->pAct,FX32_CONST(idx+dest->idx));
//		CLACT_SetRotationAffine(dest->pAct,16384*dest->dir,CLACT_AFFINE_NORMAL);
		CLACT_DrawPriorityChg(dest->pAct,2);
		CLACT_SetDrawFlag(dest->pAct,FALSE);
	}
	if(wk->fView.num == 0){
		return;
	}
	//アニメタスク登録
	wk->fView.now = wk->fView.num-1;
	wk->fView.tcb = TCB_Add(TMapN_FootViewTask,&wk->fView,1);
}

static void TMapN_FootViewTask(TCB_PTR tcb,void* work)
{
	TMAP_FOOTVIEW* wk = (TMAP_FOOTVIEW*)work;

	if(wk->anmct++ % 26 > 0){
		return;
	}

	//古い位置を消して新しい位置を出す
	CLACT_SetDrawFlag(wk->foot[wk->old].pAct,FALSE);
	CLACT_SetDrawFlag(wk->foot[wk->now].pAct,TRUE);

	wk->old = wk->now;
	wk->now = (wk->now+(wk->num-1))%wk->num;

	if(wk->anmct > 26*10){
		wk->anmct = 1;
	}
}

/**
 *	@brief	ノーマルモード　足跡マークリソース解放
 */
static void TMapN_FootViewRelease(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FVIEW	*dest;
	int i = 0,ret;

	if(wk->fView.tcb != NULL){
		TCB_Delete(wk->fView.tcb);
	}
	for(i = 0;i < wk->fView.num;i++){
		dest = &(wk->fView.foot[i]);
		CATS_ObjectDel(dest->pAct);
	}
}

/**
 *	@brief	サブ画面フォーカスタスク登録
 */
static void TMapNS_AddSVForcusTask(TMAP_MAIN_DAT* pMain,int mode)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	wk->sub_seq = 0;
	wk->sub_ct = 0;
	if(mode == 0){
		wk->tcb = TCB_Add(TMapNS_SVForcusInTask,pMain,0);
	}else{
		wk->tcb = TCB_Add(TMapNS_SVForcusOutTask,pMain,0);
	}
}

/**
 *	@brief	サブ画面フォーカスInタスク
 */
static void TMapNS_SVForcusInTask(TCB_PTR tcb,void* work)
{
	TMAP_MAIN_DAT* pMain = (TMAP_MAIN_DAT*)work;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	static const u8 btnAnmTbl[] = {1,2,1,0};

	switch(wk->sub_seq){
	case 0:
		CLACT_SetDrawFlag(wk->pCAW_btn, 1 );
		CLACT_SetAnmFlag(wk->pCAW_btn,1);	//オートアニメセット
		CLACT_AnmFrameSet(wk->pCAW_btn,1);	//アニメスタートフレームセット

		Snd_SePlay(SND_TMAP_SOPEN);
		wk->sub_seq++;
		break;
	case 1:
		//ボタンアニメ
		if(wk->sub_ct % 2){
			TMapN_SubButtonSet(pMain,btnAnmTbl[wk->sub_ct/2],0);
			GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
		}
		if(wk->sub_ct++ > 7){
			wk->sub_seq++;
		}
		break;
	case 2:
		CLACT_SetDrawFlag(wk->pCAW_btn, 0);
		CLACT_SetAnmFlag(wk->pCAW_btn,0);	//オートアニメを止める
		//フェードアウト処理
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTEROUT_DOWN,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 3:
		//フェード待ち
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//画面書き換え
		wk->forcus = TMAPN_FORCUS_SUB;
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		
		TMap_GuideTagSet(pMain,&(wk->win[WIN_GUIDE]));
		TMapN_BlockReset(pMain);
		TMapN_BlockChange(pMain);

		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTERIN_UP,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 4:
		if(!WIPE_SYS_EndCheck()){
			return; 
		}
		wk->sub_ct = 0;
		wk->sub_seq = 0;
		wk->tp_f -= 2;
		TCB_Delete(tcb);
		wk->tcb = NULL;
		break;
	}
}

/**
 *	@brief	サブ画面フォーカスアウトタスク
 */
static void TMapNS_SVForcusOutTask(TCB_PTR tcb,void* work)
{
	TMAP_MAIN_DAT* pMain = (TMAP_MAIN_DAT*)work;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	switch(wk->sub_seq){
	case 0:
		//フェードアウト処理
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTEROUT_DOWN,0x0000,8,1,pMain->heapID
				);
		Snd_SePlay(SND_TMAP_SCLOSE);
		wk->sub_seq++;
		break;
	case 1:
		//フェード待ち
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		TMapN_SubButtonSet(pMain,0,1);
	
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTERIN_UP,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 2:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		wk->forcus = TMAPN_FORCUS_MAIN;
		wk->sub_seq = 0;
		wk->sub_ct = 0;
		wk->tp_f -= 2;
		TCB_Delete(tcb);
		wk->tcb = NULL;
		return;
	}
	return;
}

/**
 *	@brief	ジャンプモード、A決定チェック
 *	@param	pMain TMAP_MAIN_DATへのポインタ
 */
static int TMapJ_CheckJumpPos(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_VIEW_OBJ *pd = NULL;
	u8	jump_f = 1;

	if(wk->pBlock == NULL){
		return 0;	//空を飛ぶで飛べない場所
	}
	pd = TownViewDataSearchPos(wk->pTView,wk->czoneID,wk->cposX,wk->cposZ);

#ifdef PM_DEBUG
	if(pd == NULL || pd->flag == 0){
		if(pMain->param->debug_f == 0){
			return 0;	//まだ飛べない
		}
	}
#else	//ifdef PM_DEBUG
	if(pd == NULL || pd->flag == 0){
		return 0;	//まだ飛べない
	}
#endif	//ifdef PM_DEBUG
	
	pMain->param->retval = 1;
	pMain->param->ret_x = wk->cposX;
	pMain->param->ret_z = wk->cposZ;
	pMain->param->ret_zone = wk->czoneID;
	return 1;
}
