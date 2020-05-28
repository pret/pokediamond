//============================================================================================
/**
 * @file	trainer_card.c
 * @bfief	トレーナーカード
 * @author	Nozomu Saito
 * @date	05.11.15
 */
//============================================================================================
#include "trcard_sys.h"
#include "gflib/touchpanel.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/wipe.h"
#include "system/fontproc.h"

#include "system/snd_tool.h"
#include "trcard_snd_def.h"
#include "trcard_bmp.h"
#include "trcard_obj.h"
#include "trcard_cgx_def.h"
#include "application/app_tool.h"
#include "trainer_case.naix"

#include "msgdata/msg_trainerscard.h"
#include "msgdata/msg.naix"
#include "communication/wm_icon.h"

#define MIN_SCRUCH	(3)
#define MAX_SCRUCH	(40)
#define REV_SPEED	(FX32_SHIFT - wk->RevSpeed)

#define CGX_WIDE		(32)
#define BUTTON_CGX_POS	(4*CGX_WIDE)
#define	MAIN_BUTTON_CGX_SIZE	(4)
#define MAIN_BUTTON_POS_Y	(19)
#define MAIN_BUTTON_POS_X	(14)

#define NOBODY_CGX_POS	(5*CGX_WIDE+26)
#define	GYM_READER_CGX_SIZE	(5)
#define COVER_CGX_WIDTH	(16)

#define BADGE_BAD_PLTT_NO	(3)
#define UNI_TRAINER_PLTT_NO	(4)

#define TRC_BG_TRAINER		(GF_BGL_FRAME3_S)//(GF_BGL_FRAME0_S)
#define TRC_BG_FONT			(GF_BGL_FRAME3_S)
#define TRC_BG_SIGHN		(GF_BGL_FRAME3_S)
#define TRC_BG_CASE			(GF_BGL_FRAME1_S)
#define TRC_BG_CARD			(GF_BGL_FRAME2_S)
#define TRC_BG_UNDER_CASE	(GF_BGL_FRAME2_M)
#define TRC_BG_COVER		(GF_BGL_FRAME3_M)

#define CARD_SCALE_MIN	(0x24)

#define UNION_TR_MAX	(16)

enum {
	SEQ_IN,
	SEQ_MAIN,
	SEQ_OUT,
	SEQ_REV,
	SEQ_COVER,
};

typedef enum {
	TRC_KEY_REQ_NONE = 0,
	TRC_KEY_REQ_TP_BEAT,
	TRC_KEY_REQ_TP_BRUSH,
	TRC_KEY_REQ_REV_BUTTON,
	TRC_KEY_REQ_END_BUTTON,
}TRC_KEY_REQ;

typedef enum {
	COVER_CLOSE = 0,
	COVER_OPEN = 1,
}COVER_STATE;

enum {
	CASE_BUTTON,
	BADGE0,
	BADGE1,
	BADGE2,
	BADGE3,
	BADGE4,
	BADGE5,
	BADGE6,
	BADGE7,
};

enum {
	ANIME_NOTHING,
	ANIME_BUTTON_PUSH,
	ANIME_BUTTON_PULL
};

typedef struct {
	const RECT_HIT_TBL *const CoverTpRect[2];	//0:カバー閉じてるとき 1:カバー開けてるとき
}RECT_HIT_TBL_LIST;

//ここで指定した回数以上こすると、バッジを1回磨いたことになる(レベル毎)
static const u8 TempScruchMax[5] = {
	1,3,4,15,15
};

// 8バッジとケースボタンのタッチパネル判定テーブル
static const RECT_HIT_TBL TpRect1[] =
{
	//上	下		左		右
	{ 19*8, 23*8-1,	15*8,	19*8-1, },
	{ 5*8,  10*8-1,	3*8,	8*8-1,  },
	{ 5*8,  10*8-1,	10*8,	15*8-1, },
	{ 5*8,  10*8-1,	17*8,	21*8-1, },
	{ 5*8,  10*8-1,	24*8,	29*8-1, },
	{ 12*8, 17*8-1,	3*8,	8*8-1,  },
	{ 12*8, 17*8-1,	10*8,	15*8-1, },
	{ 12*8, 17*8-1,	17*8,	21*8-1, },
	{ 12*8, 17*8-1,	24*8,	29*8-1, },
	{ RECT_HIT_END, 0, 0, 0 }
};

//カバーが閉じているときのタッチパネル判定テーブル(ボタンのみ)
static const RECT_HIT_TBL TpRect2[] =
{
	//上	下		左		右
	{ 19*8, 23*8-1,	15*8,	19*8-1, },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL_LIST TpHit[] =	{
	{TpRect2,TpRect2},		// 通信時(TR_CARD_DATA::BrushValid == 0) カバーを開けても、バッジ磨きできない
	{TpRect2,TpRect1},		//通常時(TR_CARD_DATA::BrushValid == 1)	カバー開けたらバッジ磨ける
};

static const u8 ButtonAnimePush[] = {
	1,1,	//1フレーム、1番目
	0,2,	//終了、2番目
};
static const u8 ButtonAnimePull[] = {
	1,1,	//1フレーム、1番目
	0,0,	//終了、     0番目
};

static const u8 * const ButtonAnime[] = {
	ButtonAnimePush,
	ButtonAnimePull
};

//ユニオンルームトレーナー表示テーブル
static const int UniTrTable[UNION_TR_MAX] = 
{
	//男
	NARC_trainer_case_trdp_schoolb256_NCGR,
	NARC_trainer_case_trdp_mushi256_NCGR,
	NARC_trainer_case_trdp_elitem256_NCGR,
	NARC_trainer_case_trdp_heads256_NCGR,
	NARC_trainer_case_trdp_iseki256_NCGR,
	NARC_trainer_case_trdp_karate256_NCGR,
	NARC_trainer_case_trdp_prince256_NCGR,
	NARC_trainer_case_trdp_espm256_NCGR,
	//女
	NARC_trainer_case_trdp_mini256_NCGR,
	NARC_trainer_case_trdp_battleg256_NCGR,
	NARC_trainer_case_trdp_sister256_NCGR,
	NARC_trainer_case_trdp_elitew256_NCGR,
	NARC_trainer_case_trdp_idol256_NCGR,
	NARC_trainer_case_trdp_madam256_NCGR,
	NARC_trainer_case_trdp_cowgirl256_NCGR,
	NARC_trainer_case_trdp_princess256_NCGR,
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void AllocStrBuf( TR_CARD_WORK * wk );
static void FreeStrBuf( TR_CARD_WORK * wk );

static void SetTrCardVramBank(void);
static void SetTrCardBg( GF_BGL_INI * ini );
static void SetTrCardBgGraphic( TR_CARD_WORK * wk );

static void TrCardBgExit( GF_BGL_INI * ini );

static BOOL CardRev(TR_CARD_WORK * wk );
static BOOL CoverOpenClose(TR_CARD_WORK *wk);
static BOOL PushButton(TR_CARD_WORK *wk, const u8 *inAnime);
static int CheckKey(TR_CARD_WORK *wk);
static void BrushBadge(TR_CARD_WORK *wk);
static void SetCardPalette(const u8 inCardRank, const u8 inPokeBookHold);
static void SetCasePalette(const u8 inVersion);
static void SetUniTrainerPalette(const u8 inTrainerNo);

static void ChangeBgButton(TR_CARD_WORK *wk, const u8 inAnmNum);
static void ChangeBgGymReader(TR_CARD_WORK *wk, const u8 inNo);
static void VBlankFunc( void * work );
static void DispTrainer(TR_CARD_WORK *wk);
static void ClearTrainer(TR_CARD_WORK *wk);

static void BadgeLvUp(TR_CARD_WORK *wk, const u8 inBadgeNo);
static void ResetAffinePlane(void);
static void ButtonAnimeControl(TR_CARD_WORK *wk);
static const u8 GetBadgeLevel(const int inCount);

static void ClearScruchSndNow(TR_SCRUCH_SND *outScruchSnd);
static void ClearScruchSnd(TR_SCRUCH_SND *outScruchSnd);
static void PlayScruchSnd(TR_SCRUCH_SND *ioScruchSnd);
static void MakeSignData(const u8 *inRawData, u8 *outData);
static void TransSignData(GF_BGL_INI * bgl,const int inFrame, const u8 *inSignData);
static void PlayButtonAndCoverSnd(const COVER_STATE inIsOpen);
static void UpdatePlayTime(TR_CARD_WORK *wk, const u8 inUpdateFlg);
static int CheckTpBadgeTrg(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl);
static int CheckTpBadgeCont(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl);

//============================================================================================
//	グローバル変数
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_Init( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrSet( NULL,NULL );		// HBlankセット

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	sys_KeyRepeatSpeedSet( 4, 8 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_TR_CARD, 0x28000 );

	wk = PROC_AllocWork( proc, sizeof(TR_CARD_WORK), HEAPID_TR_CARD );
	memset( wk, 0, sizeof(TR_CARD_WORK) );

///	APP_WipeStart( APP_WIPE_IN, HEAPID_TR_CARD );	// 輝度変更セット
	
	wk->TrCardData = PROC_GetParentWork( proc );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_TR_CARD );
	
	AllocStrBuf(wk);
	
	SetTrCardVramBank();
	SetTrCardBg( wk->bgl );
	SetTrCardBgGraphic( wk );

	InitTPSystem();						// タッチパネルシステム初期化
	InitTPNoBuff(4);

	//音関連初期化
	Snd_DataSetByScene( SND_SCENE_SUB_TRCARD, 0, 0 ); //サウンドデータロード(BGM引継ぎ)
	Snd_BadgeWorkInit( &wk->SndBadgeWork );
	Snd_SePlay( SND_TRCARD_CALL );		//呼び出し音
	
	InitTRCardCellActor( &wk->ObjWork );
	
	{
		int i;
		u8 badge_disp[TR_BADGE_NUM_MAX];
		for(i=0;i<TR_BADGE_NUM_MAX;i++){
			if (wk->TrCardData->BadgeData[i].BadgeHold){
				badge_disp[i] = 1;
			}else{
				badge_disp[i] = 0;
			}
		}
		
		SetTrCardActor( &wk->ObjWork, badge_disp );
	}
	
	TRCBmp_AddTrCardBmp( wk->bgl, wk->win );

	{
		u8 no;
		for(no=0;no<TR_BADGE_NUM_MAX;no++){
			//マスク判定
			if ( (wk->TrCardData->GymReaderMask>>no)&0x01 ){
				ChangeBgGymReader(wk,no);
			}
		}
		GF_BGL_LoadScreenReq( wk->bgl, TRC_BG_COVER );
	}
	
	TRCBmp_WriteTrWinInfo( wk->win, wk->TrCardData );
	//コロン描く
	TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), TRUE, wk->SecBuf);
	
	wk->is_back = FALSE;		//表面からスタート
	wk->IsOpen = COVER_CLOSE;			//ケースは閉じた状態からスタート

	wk->touch = RECT_HIT_NONE;			//タッチパネルは押されていない

	wk->ButtonPushFlg = FALSE;			//ボタン押されてない
	wk->AnimeType = ANIME_NOTHING;		//ボタンアニメ無し
	//バッジレベルに合わせてパレットセット
	{
		u8 lv;
		u8 i;
		for(i=0;i<TR_BADGE_NUM_MAX;i++){
			wk->ScruchCounter[i] = 0;
			if (wk->TrCardData->BadgeData[i].BadgeHold){
				lv = GetBadgeLevel(wk->TrCardData->BadgeData[i].BadgeScruchCount);
				if (lv <= TR_CARD_BADGE_LV_MAX){
					if (lv == TR_CARD_BADGE_LV_MAX){	//バッジレベルが最高のときは、1段階下のレベルのパレットを使用
						SetBadgePalette(&wk->ObjWork, i, 0);
					}else{
						SetBadgePalette(&wk->ObjWork, i, BADGE_BAD_PLTT_NO-lv);
					}
				}
				//星アクター表示
				if (lv == TR_CARD_BADGE_LV_MAX-1){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+i], 1);	//表示
				}
				else if (lv == TR_CARD_BADGE_LV_MAX){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_GRATE_STAR_ACT_START+i], 1);	//表示
				}
			}
		}
	}

	//拡縮面をリセット
	ResetAffinePlane();
	

	sys_VBlankFuncChange(VBlankFunc, NULL );	// VBlankセット

	//通信アイコンセット
	// 受信強度アイコンを通信接続中なら表示するし、
	// ユニオンのように通信回路は動作しているが接続はしていない状態なら出さない
	// Change by Mori 2006/07/19
	WirelessIconEasyUnion();

	//BGMをしぼる
	//Snd_BgmFadeOut( BGM_VOL_TR_CASE, BGM_FADE_TR_CASE_TIME );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_TR_CASE );

	WIPE_SYS_Start(	WIPE_PATTERN_FSAM, WIPE_TYPE_SHUTTERIN_DOWN,
					WIPE_TYPE_SHUTTERIN_DOWN, WIPE_FADE_BLACK,
					WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_TR_CARD );

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_Main( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		{
			int req;
			req = CheckKey(wk);

			if (req == TRC_KEY_REQ_TP_BEAT){
				//タッチパネルテンプレートとタッチ座標を比較
				if (wk->touch == CASE_BUTTON){
					wk->ButtonPushFlg = TRUE;		//ボタン押した
					wk->AnimeType = ANIME_BUTTON_PUSH;	//ボタン押下アニメ
					//ボタンエフェクトアクター表示
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START], 1);	//表示
					CLACT_SetAnmFlag(wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START],1);
					CLACT_AnmChg( wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START], 10 );
					
					wk->sub_seq = 0;	//サブシーケンス初期化
					//ボタンアニメ初期化
					wk->AnmNum = 0;
					wk->ButtonAnmCount = 0;
					//シーケンス待ちフラグ初期化
					wk->rc_cover = FALSE;
					*seq = SEQ_COVER;	//カバーの開閉
				}else{
					u8 no = wk->touch-1;
					//バッジ所有判定
					if (wk->TrCardData->BadgeData[no].BadgeHold){
						u8 lv;
						lv = GetBadgeLevel(wk->TrCardData->BadgeData[no].BadgeScruchCount);
						//バッジ音がする
						Snd_BadgeWorkPlay( &wk->SndBadgeWork, no, lv );
					}
				}
			}else if (req == TRC_KEY_REQ_TP_BRUSH){
				if ( (wk->ButtonPushFlg)&&(wk->touch != CASE_BUTTON) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//ボタン戻しアニメ
				}
				//カバーが空いていれば、バッチ磨き
				BrushBadge(wk);//バッチ磨き
			}else{
				if ( (wk->ButtonPushFlg)&&(wk->AnimeType == ANIME_NOTHING) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//ボタン戻しアニメ
				}
				if (wk->TrCardData->BrushValid){
					ClearScruchSnd(&wk->ScruchSnd);
				}

				if (req == TRC_KEY_REQ_REV_BUTTON){
					//カードひっくり返す
					wk->sub_seq = 0;	//サブシーケンス初期化
					*seq = SEQ_REV;	//カード回転
				}else if (req == TRC_KEY_REQ_END_BUTTON){
					//終了
					Snd_SePlay( SND_TRCARD_END );		//終了音
///					APP_WipeStart( APP_WIPE_OUT, HEAPID_TR_CARD );	// 輝度変更セット
					WIPE_SYS_Start(	WIPE_PATTERN_FMAS, WIPE_TYPE_SHUTTEROUT_UP,
									WIPE_TYPE_SHUTTEROUT_UP, WIPE_FADE_BLACK,
									WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_TR_CARD );
					*seq = SEQ_OUT;
				}
			}
			UpdatePlayTime(wk, wk->TrCardData->TimeUpdate);
		}
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	
	case SEQ_REV:	//リバース処理
		if ( CardRev(wk) ){
			*seq = SEQ_MAIN;
		}
		break;
	case SEQ_COVER:
		if (wk->AnimeType == ANIME_NOTHING){
			int req;
			req = CheckKey(wk);

			if (req == TRC_KEY_REQ_TP_BEAT){
				if (wk->touch == CASE_BUTTON){
					wk->ButtonPushFlg = TRUE;		//ボタン押した
					wk->AnimeType = ANIME_BUTTON_PUSH;	//ボタン押下アニメ
					//ボタンアニメ初期化
					wk->AnmNum = 0;
					wk->ButtonAnmCount = 0;
				}
			}else if (req == TRC_KEY_REQ_TP_BRUSH){
				if ( (wk->ButtonPushFlg)&&(wk->touch != CASE_BUTTON) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//ボタン戻しアニメ
				}
			}else{
				if ( wk->ButtonPushFlg ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//ボタン戻しアニメ
				}
			}
		}
		//開閉
		if (wk->rc_cover == FALSE){
			wk->rc_cover = CoverOpenClose(wk);
		}

		if (wk->rc_cover){
			wk->rc_cover = FALSE;
			*seq = SEQ_MAIN;
		}
		break;
	}

	//ボタンアニメ
	ButtonAnimeControl(wk);
	

	CLACT_Draw( wk->ObjWork.ClactSet );									// セルアクター常駐関数

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_End( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk  = PROC_GetWork( proc );

	//使用した拡縮面を元に戻す
	ResetAffinePlane();
	
	FreeStrBuf( wk );					//文字列解放
	
	RereaseCellObject(&wk->ObjWork);		//2Dオブジェクト関連領域解放

	sys_FreeMemoryEz( wk->TrArcData );	//トレーナーキャラアーカイブデータ解放

	sys_FreeMemoryEz( wk->TrScrnArcData );//トレーナースクリーン解放

	TRCBmp_ExitTrCardBmpWin( wk->win );			// BMPウィンドウ開放
	TrCardBgExit( wk->bgl );			// BGL削除
	StopTP();							// タッチパネル終了

	PROC_FreeWork( proc );				// ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット
	sys_DeleteHeap( HEAPID_TR_CARD );

	//BGMを元の音量に戻す
	//Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_TR_CASE_TIME, BGM_FADEIN_START_VOL_NOW );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_MAX );

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列バッファの確保
 *
 * @param	wk		画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocStrBuf( TR_CARD_WORK * wk )
{
	wk->PlayTimeBuf = STRBUF_Create(TIME_H_DIGIT+1, HEAPID_TR_CARD);
	wk->SecBuf =	STRBUF_Create(5, HEAPID_TR_CARD);
	{
		MSGDATA_MANAGER* man;
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_trainerscard_dat, HEAPID_TR_CARD);
		MSGMAN_GetString(man, MSG_TCARD_12, wk->SecBuf);
		MSGMAN_Delete( man );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列バッファの解放
 *
 * @param	wk		画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeStrBuf( TR_CARD_WORK * wk )
{
	STRBUF_Delete( wk->PlayTimeBuf );
	STRBUF_Delete( wk->SecBuf );
}

//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardVramBank(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_64_E,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * カードパレット設定
 *
 * @param	inCardRank		カードランク
 * @param	inPokeBookHold	図鑑所持フラグ
 * 
 * @return	なし
 */
//--------------------------------------------------------------------------------------------
static void SetCardPalette(const u8 inCardRank, const u8 inPokeBookHold)
{
	{
		void *buf;
		NNSG2dPaletteData *dat;

		if (inPokeBookHold){
			switch(inCardRank){
			case 0:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_0_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 1:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_1_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 2:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_2_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 3:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_3_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 4:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_4_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 5:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_5_NCLR, &dat, HEAPID_TR_CARD );
				break;
			}
		}else{
			buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_6_NCLR, &dat, HEAPID_TR_CARD );
		}

		{
			u16 * adr;
			DC_FlushRange( dat->pRawData, 2*16*16 );	//16本分をフラッシュ
			adr = dat->pRawData;
			//16パレット１番目から3本分ロード
			GXS_LoadBGPltt( &adr[16], 2*16, 2*16*3 );
			//f番目のパレット１本をロード
			GXS_LoadBGPltt( &adr[16*15], 2*16*15, 2*16 );
			sys_FreeMemoryEz(buf);
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ケースパレットセット
 *
 * @param	inVersion	バージョン
 *
 * @return	なし
 */
//--------------------------------------------------------------------------------------------
static void SetCasePalette(const u8 inVersion)
{
	void *buf;
	NNSG2dPaletteData *dat;
	switch(inVersion){
	case VERSION_DIAMOND:		//ダイヤ
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_d_NCLR, &dat, HEAPID_TR_CARD );
		break;
	case VERSION_PEARL:		//パール
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_p_NCLR, &dat, HEAPID_TR_CARD );
		break;
	default:	//別バージョン
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_x_NCLR, &dat, HEAPID_TR_CARD );
		break;
	}
		
	DC_FlushRange( dat->pRawData, 2*16 );
	GX_LoadBGPltt( dat->pRawData, 0, 2*16 );
	GXS_LoadBGPltt( dat->pRawData, 0, 2*16 );
	sys_FreeMemoryEz(buf);
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオントレーナーパレットセット
 *
 * @param	inTrainerNo
 *
 * @return	なし
 */
//--------------------------------------------------------------------------------------------
static void SetUniTrainerPalette(const u8 inTrainerNo)
{
	void *buf;
	u8 *addr;
	NNSG2dPaletteData *dat;
	buf = ArcUtil_PalDataGet(
			ARC_TR_CASE_GRA, NARC_trainer_case_trdp_union_card_NCLR, &dat, HEAPID_TR_CARD );

	addr = (u8*)(dat->pRawData);
		
	DC_FlushRange(&addr[2*16*inTrainerNo] , 2*16 );
	GXS_LoadBGPltt( &addr[2*16*inTrainerNo], 2*16*UNI_TRAINER_PLTT_NO, 2*16 );
	sys_FreeMemoryEz(buf);
}

//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardBg( GF_BGL_INI * ini )
{

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_1, GX_BGMODE_4, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// FONT (BMP)
		GF_BGL_BGCNT_HEADER ExAffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_FONT, &ExAffineBgCntDat, GF_BGL_MODE_256X16 );
		GF_BGL_ScrClear( ini, TRC_BG_FONT );
	}

	{	// BG (CASE CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_CASE, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, TRC_BG_CASE );
	}

	{	// BG (CARD CHAR)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_CARD, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, TRC_BG_CARD );
	}

	{	// BG (UNDER_CASE CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_UNDER_CASE, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, TRC_BG_UNDER_CASE );
	}

	{	// BG (UNDER_CASE_COVER CHAR)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_COVER, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, TRC_BG_COVER );
	}

	
/*
	{	// BUTTON (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_POKELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_POKELIST );
*/	
}

//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardBgGraphic( TR_CARD_WORK * wk )
{
	// TRAINER_PALETTE(UP_DISPLAY)
	{
		void *buf;
		NNSG2dPaletteData *dat;
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_0_NCLR, &dat, HEAPID_TR_CARD );
		DC_FlushRange( dat->pRawData, 2*16*16 );
		GXS_LoadBGPltt( dat->pRawData, 0, 2*16*16 );
		sys_FreeMemoryEz(buf);
	}
	
	// CARD PALETTE
	SetCardPalette(wk->TrCardData->CardRank, wk->TrCardData->PokeBookFlg);
	
	// UNSER_CASE_COVER PALETTE(UNDER_DISPLAY)
	{
		void *buf;
		NNSG2dPaletteData *dat;
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NCLR, &dat, HEAPID_TR_CARD );
		DC_FlushRange( dat->pRawData, 16*2*16 );
		GX_LoadBGPltt( dat->pRawData, 0, 16*2*16 );
		sys_FreeMemoryEz(buf);
	}
	// CASE PALETTE
	SetCasePalette(wk->TrCardData->Version);

	//TRAINER
	if (wk->TrCardData->UnionTrNo == UNION_TR_NONE){
		{
			BOOL rc;
			//アーカイブデータ取得
			wk->TrArcData = ArcUtil_Load(	ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer_NCGR,
											FALSE, HEAPID_TR_CARD, ALLOC_TOP );
			GF_ASSERT(wk->TrArcData!=NULL);
			rc = NNS_G2dGetUnpackedBGCharacterData( wk->TrArcData, &wk->TrCharData);
			GF_ASSERT(rc);
		}
	
		if (wk->TrCardData->TrSex == PM_MALE){
			//男
			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer01_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
		}else{
			//女
			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer02_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
		}
	}else{
		//ユニオンルームで他の人のデータを見る時
		{
			BOOL rc;
			//アーカイブデータ取得
			wk->TrArcData = ArcUtil_Load(	ARC_TR_CASE_GRA, UniTrTable[wk->TrCardData->UnionTrNo],
											FALSE, HEAPID_TR_CARD, ALLOC_TOP );
			GF_ASSERT(wk->TrArcData!=NULL);
			rc = NNS_G2dGetUnpackedBGCharacterData( wk->TrArcData, &wk->TrCharData);
			GF_ASSERT(rc);

			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_test256_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
			//トレーナーパレット変更
			SetUniTrainerPalette(wk->TrCardData->UnionTrNo);
		}
	}
	DispTrainer(wk);

	//CARD
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_NCGR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_faca_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
	//CASE
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case_NCGR, wk->bgl, TRC_BG_CASE, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case_NSCR, wk->bgl, TRC_BG_CASE, 0, 0, 0, HEAPID_TR_CARD );

	//UNDER_CASE
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case2_NCGR, wk->bgl, TRC_BG_UNDER_CASE, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case2_NSCR, wk->bgl, TRC_BG_UNDER_CASE, 0, 0, 0, HEAPID_TR_CARD );
	//UNDER_CASE_COVER
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NCGR, wk->bgl, TRC_BG_COVER, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NSCR, wk->bgl, TRC_BG_COVER, 0, 0, 0, HEAPID_TR_CARD );

	//サイン展開
	MakeSignData(wk->TrCardData->SignRawData, wk->TrSignData);

}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TrCardBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, TRC_BG_FONT );
	GF_BGL_BGControlExit( ini, TRC_BG_CARD );
	GF_BGL_BGControlExit( ini, TRC_BG_CASE );
	GF_BGL_BGControlExit( ini, TRC_BG_UNDER_CASE );
	GF_BGL_BGControlExit( ini, TRC_BG_COVER );

	sys_FreeMemoryEz( ini );
}

#define FIRST_SPEED	(8)
//--------------------------------------------------------------------------------------------
/**
 * カードをひっくり返す
 *
 * @param	wk		画面のワーク
 *
 * @return	BOOL	TRUE:終了	FALSE：処理中
 */
//--------------------------------------------------------------------------------------------
static BOOL CardRev( TR_CARD_WORK *wk )
{
	BOOL rc;
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	rc = FALSE;
	switch(wk->sub_seq){
	case 0:
		wk->RevSpeed = FIRST_SPEED;	
		//情報を消す
		//ちょっと拡大して
		wk->CardScaleX = 1 << FX32_SHIFT;
		wk->CardScaleY = 1 << FX32_SHIFT;
		wk->CardScaleX += 2 << (FX32_SHIFT - 6);
		wk->CardScaleY += 2 << (FX32_SHIFT - 6);

		Snd_SePlay( SND_TRCARD_REV );		//ひっくり返す音

		wk->sub_seq++;
		break;
	case 1:
		//幅を縮める
		wk->CardScaleX -= 2 << (REV_SPEED);
		if (wk->CardScaleX <= 0){//カードスクリーン変更
			wk->CardScaleX = CARD_SCALE_MIN;	//バグ表示防止(値はカードの厚みを維持できる位の目分量)
			wk->sub_seq++;
		}

		wk->RevSpeed--;
		if (wk->RevSpeed <=1 ){
			wk->RevSpeed = 1;
		}
		break;
	case 2:
		if (wk->is_back == FALSE){
			wk->is_back = TRUE;
			ArcUtil_ScrnSet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_back_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
			//表面を消す
			TRCBmp_NonDispWinInfo(wk->win, TRC_BMPWIN_TR_ID, TRC_BMPWIN_START_TIME);
			//トレーナー消す
			ClearTrainer(wk);
			//スクリーンクリア
			GF_BGL_ScrClear( wk->bgl, TRC_BG_SIGHN );
			//裏面表示
			TRCBmp_WriteTrWinInfoRev( wk->win, wk->TrCardData );
			TransSignData(wk->bgl,TRC_BG_SIGHN, wk->TrSignData);
		}else{
			wk->is_back = FALSE;
			ArcUtil_ScrnSet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_faca_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
			//裏面を消す
			TRCBmp_NonDispWinInfo(wk->win, TRC_BMPWIN_CLEAR_TIME, TRC_BMPWIN_TRADE_INFO);
			//スクリーンクリア
			GF_BGL_ScrClear( wk->bgl, TRC_BG_TRAINER );
			//トレーナー表示
			DispTrainer(wk);
			//表面表示
			TRCBmp_WriteTrWinInfo( wk->win, wk->TrCardData );
		}
		wk->sub_seq++;
		break;
	case 3:
		//幅を広げる
		wk->RevSpeed++;
		if(wk->RevSpeed > FIRST_SPEED){
			wk->RevSpeed = FIRST_SPEED;
		}

		wk->CardScaleX += 2 << (REV_SPEED);
		if (wk->CardScaleX >= (1 << FX32_SHIFT)){
			wk->CardScaleX = 1 << FX32_SHIFT;
			//元のサイズへ
			wk->CardScaleX = 1 << FX32_SHIFT;
			wk->CardScaleY = 1 << FX32_SHIFT;

			//Snd_SePlay( SND_TRCARD_REV_AFTER );		//ひっくり返した後表示音
			rc = TRUE;
		}
		break;
	}

	rScale_x = FX_Inv(wk->CardScaleX);
	rScale_y = FX_Inv(wk->CardScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2S_SetBG2Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	G2S_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );

	return rc;
}

/**
static const fx32 CoverSpeed[] =
{
	2 << (FX32_SHIFT - 11),
	2 << (FX32_SHIFT - 11),
	2 << (FX32_SHIFT - 7),
	2 << (FX32_SHIFT - 7),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
};

#define COVER_MOVE	(16)
*/

static const fx32 CoverSpeed[] =
{
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
};

#define COVER_MOVE	(14)



//--------------------------------------------------------------------------------------------
/**
 * ケースカバーの開閉
 *
 * @param	wk		画面のワーク
 *
 * @return	BOOL	TRUE:終了	FALSE：処理中
 */
//--------------------------------------------------------------------------------------------

static BOOL CoverOpenClose(TR_CARD_WORK *wk)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;

	switch(wk->sub_seq){
	case 0:
		wk->Counter = 0;		
		if (wk->IsOpen == COVER_CLOSE){
			wk->CoverScaleY = 1 << FX32_SHIFT;
			wk->sub_seq = 1;
		}else{
			wk->sub_seq = 2;
		}
		PlayButtonAndCoverSnd(wk->IsOpen);
		break;
	case 1:		
		//開ける
		wk->CoverScaleY -= CoverSpeed[wk->Counter++];///2 << (FX32_SHIFT - 4);
		if (wk->Counter==COVER_MOVE){//カードスクリーン変更
			wk->IsOpen = COVER_OPEN;		//開いた状態
			wk->sub_seq = 3;
		}
		break;
	case 2:
		//閉める
		wk->CoverScaleY += CoverSpeed[(COVER_MOVE-1)-(wk->Counter++)];///2 << (FX32_SHIFT - 4);
		
		if (wk->Counter == COVER_MOVE){//カードスクリーン変更
			wk->IsOpen = COVER_CLOSE;		//閉じた状態
			wk->CoverScaleY = (1 << FX32_SHIFT);
			wk->sub_seq = 3;
		}
		break;
	case 3:	
		return TRUE;
	}

	rScale_x = FX_Inv(1 << FX32_SHIFT);
	rScale_y = FX_Inv(wk->CoverScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 0,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * キー判定
 *
 * @param	wk		画面のワーク
 *
 * @return	int		リクエスト
 */
//--------------------------------------------------------------------------------------------
static int CheckKey(TR_CARD_WORK *wk)
{
	int key_req;
	BOOL tp_key_flg;
	tp_key_flg = FALSE;
	key_req = TRC_KEY_REQ_NONE;

	wk->touch = RECT_HIT_NONE;

#ifdef PM_DEBUG
/**	
	if (sys.trg & PAD_BUTTON_R){
		if ( (wk->TrCardData->PokeBookFlg == 0)&&(wk->TrCardData->CardRank == 0) ){
			wk->TrCardData->PokeBookFlg = 1;
		}else{
			wk->TrCardData->CardRank = (wk->TrCardData->CardRank+1)%6;
			if (wk->TrCardData->CardRank == 0){
				wk->TrCardData->PokeBookFlg = 0;
			}
		}
		SetCardPalette(wk->TrCardData->CardRank, wk->TrCardData->PokeBookFlg);
		return key_req;
	}
	
	if (sys.trg & PAD_BUTTON_L){
		if (wk->TrCardData->Version == VERSION_DIAMOND){
			wk->TrCardData->Version = VERSION_PEARL;
		}else if(wk->TrCardData->Version == VERSION_PEARL){
			wk->TrCardData->Version = VERSION_DP_NEXT;
		}else{
			wk->TrCardData->Version = VERSION_DIAMOND;
		}
		SetCasePalette(wk->TrCardData->Version);
		return key_req;
	}
*/	
#endif
	if (sys.tp_trg){
///		OS_Printf("xy=%d,%d\n",sys.tp_x,sys.tp_y);
		wk->brushOK = TRUE;	//バッジ磨き可能
	}
	
///	wk->touch = GF_TP_RectHitTrg( TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
	wk->touch = CheckTpBadgeTrg( wk->bgl, TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
	//ヒット判定
	if (wk->touch != RECT_HIT_NONE){	//タッチパネルトリガー判定
///		OS_Printf("hit=%d\n",wk->touch);
		tp_key_flg = TRUE;	//タッチパネルリクエスト
		key_req = TRC_KEY_REQ_TP_BEAT;
	}else if (sys.tp_cont){	//タッチパネルベタ押し判定
///		wk->touch = GF_TP_RectHitCont( TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
		wk->touch = CheckTpBadgeCont( wk->bgl, TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
		if (wk->brushOK){
			tp_key_flg = TRUE;	//タッチパネルリクエスト
			key_req = TRC_KEY_REQ_TP_BRUSH;
		}
	}else{	//タッチパネル触っていない
		wk->brushOK = FALSE;	//バッジ磨き不可能
	}

	//タッチパネルキーが起動していなければボタン判定
	if (tp_key_flg == FALSE){
		if ( sys.trg & PAD_BUTTON_DECIDE ){
			key_req = TRC_KEY_REQ_REV_BUTTON;
		}else if ( sys.trg & PAD_BUTTON_CANCEL ){
			key_req = TRC_KEY_REQ_END_BUTTON;
		}
	}

	return key_req;
}

//--------------------------------------------------------------------------------------------
/**
 * バッジ磨き
 *
 * @param	wk		画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BrushBadge(TR_CARD_WORK *wk)
{
	BOOL scruch;
	int sub;
	scruch = FALSE;
	//保持座標とタッチ座標の差分を取る
	if( (sys.tp_x!=0xffff)&&(sys.tp_y!=0xffff)&&
			(wk->BeforeX!=0xffff)&&(wk->BeforeY!=0xffff) ){	//値有効か？
		//保持座標とタッチ座標が同じバッジ何にあるかを調べる
		if ( (wk->touch!=RECT_HIT_NONE)&&(wk->touch!=CASE_BUTTON) ){
			//バッジ所有判定
			if (wk->TrCardData->BadgeData[wk->touch-1].BadgeHold){
				//差分が規定値以上の場合は磨いたことにする
				if ( wk->BeforeX > sys.tp_x ){		//前回のほうが値が大きいか？
					sub = wk->BeforeX - sys.tp_x;
					wk->ScruchSnd.DirX = -1;
				}else{
					sub = sys.tp_x - wk->BeforeX;
					wk->ScruchSnd.DirX = 1;
				}
				if ( (sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH) ){
					if ( wk->BeforeY > sys.tp_y ){	//前回のほうが値が大きいか？
						sub = wk->BeforeY - sys.tp_y;
						wk->ScruchSnd.DirY = -1;
					}else{
						sub = sys.tp_y - wk->BeforeY;
						wk->ScruchSnd.DirY = 1;
					}
					if (sub<=MAX_SCRUCH){
						scruch = TRUE;			//こすった
						PlayScruchSnd(&wk->ScruchSnd);
					}else{
						ClearScruchSndNow(&wk->ScruchSnd);
					}
				}else if (sub<=MAX_SCRUCH){
					if ( wk->BeforeY > sys.tp_y ){		//前回のほうが値が大きいか？
						sub = wk->BeforeY - sys.tp_y;
						wk->ScruchSnd.DirY = -1;
					}else{
						sub = sys.tp_y - wk->BeforeY;
						wk->ScruchSnd.DirY = 1;
					}
					if ((sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH)){
						scruch = TRUE;		//こすった
						PlayScruchSnd(&wk->ScruchSnd);
					}else{
						ClearScruchSndNow(&wk->ScruchSnd);
					}
				}

				if (scruch){
///					OS_Printf("scruch_%d\n",wk->touch);
///					OS_Printf("sc=%d,%d-%d,%d\n",wk->BeforeX,wk->BeforeY,sys.tp_x,sys.tp_y);
					//磨いた時間更新
					//レベル更新
					BadgeLvUp(wk, wk->touch-1);
					OS_Printf("temp_scruch:%d\n",wk->ScruchCounter[wk->touch-1]);
					OS_Printf("brush=%d,%d\n",wk->touch,wk->TrCardData->BadgeData[wk->touch-1].BadgeScruchCount);
				}
			}
		}
	}
		//保持座標更新
	wk->BeforeX = sys.tp_x;
	wk->BeforeY = sys.tp_y;
}

//--------------------------------------------------------------------------------------------
/**
 * ボタン変更
 *
 * @param	wk			画面のワーク
 * @param	inAnmNum	アニメナンバー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ChangeBgButton(TR_CARD_WORK *wk, const u8 inAnmNum)
{
    u16 * buf;
    u16 start;
    u8  x, y;
    
    buf   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_UNDER_CASE );
	start = BUTTON_CGX_POS+(MAIN_BUTTON_CGX_SIZE*inAnmNum);

    for( y=0; y<MAIN_BUTTON_CGX_SIZE; y++ ){
        for( x=0; x<MAIN_BUTTON_CGX_SIZE; x++ ){
            buf[ (y+MAIN_BUTTON_POS_Y)*TRC_SCREEN_WIDTH + x+MAIN_BUTTON_POS_X ] = start+y*CGX_WIDE+x + (0<<12);
        }
    }
	GF_BGL_LoadScreenReq( wk->bgl, TRC_BG_UNDER_CASE );
}

#define GYM_READER_ST_SCR_POS_X	(3)		//スクリーン開始座標X(キャラ単位)
#define GYM_READER_ST_SCR_POS_Y	(4)		//スクリーン開始座標Y(キャラ単位)
#define GYM_READER_SCR_OFFSET	(7)		//ジムリーダー表示間隔(キャラ単位)
#define GYM_READER_SIDE_NUM		(4)		//ジムリーダー横表示人数

//--------------------------------------------------------------------------------------------
/**
 * ジムリーダー顔差し替え
 *
 * @param	wk		画面のワーク
 * @param	inNo	リーダーナンバー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ChangeBgGymReader(TR_CARD_WORK *wk, const u8 inNo)
{
    u8 * buf;
    u16 start;
    u8  x, y;
    
	u8 dst_start_x,pos_x;
	u8 dst_start_y,pos_y;

	dst_start_x = GYM_READER_ST_SCR_POS_X;
	dst_start_y = GYM_READER_ST_SCR_POS_Y;

	pos_x = inNo%GYM_READER_SIDE_NUM;
	pos_y = inNo/GYM_READER_SIDE_NUM;

	dst_start_x += (pos_x*GYM_READER_SCR_OFFSET);
	dst_start_y += (pos_y*GYM_READER_SCR_OFFSET);

    buf   = (u8 *)GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_COVER );
	start = NOBODY_CGX_POS;

    for( y=0; y<GYM_READER_CGX_SIZE; y++ ){
        for( x=0; x<GYM_READER_CGX_SIZE	; x++ ){
            buf[ (y+dst_start_y)*TRC_SCREEN_WIDTH + x+dst_start_x ] = start+y*COVER_CGX_WIDTH+x;
        }
    }
}


//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	// セルアクター
	// Vram転送マネージャー実行
	DoVramTransferManager();

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//--------------------------------------------------------------------------------------------
/**
 * バッジレベルアップ
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BadgeLvUp(TR_CARD_WORK *wk, const u8 inBadgeNo)
{
	int count;
	u8 lv, old_lv;
	
	count = (wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount)+1;

	if (count<COUNT_LV4){
		old_lv = GetBadgeLevel(wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount);

		wk->ScruchCounter[inBadgeNo]++;
		if (wk->ScruchCounter[inBadgeNo] >= TempScruchMax[old_lv]){
			wk->ScruchCounter[inBadgeNo] = 0;
			(wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount)++;
		
			lv = GetBadgeLevel(count);
			GF_ASSERT(old_lv<=lv&&"error");
			if (old_lv < lv){		//磨いて、レベルが上がった場合
				if (lv <= TR_CARD_BADGE_LV_MAX){
					if (lv == TR_CARD_BADGE_LV_MAX){	//バッジレベルが最高のときは、1段階下のレベルのパレットを使用
						SetBadgePalette(&wk->ObjWork, inBadgeNo, 0);
					}else{
						SetBadgePalette(&wk->ObjWork, inBadgeNo, BADGE_BAD_PLTT_NO-lv);
					}
				}
				//星アクター表示
				if (lv == TR_CARD_BADGE_LV_MAX-1){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+inBadgeNo], 1);	//表示
				}else if(lv == TR_CARD_BADGE_LV_MAX){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+inBadgeNo], 0);	//非表示
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_GRATE_STAR_ACT_START+inBadgeNo], 1);	//表示
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 拡縮面リセット
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ResetAffinePlane(void)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv((1 << FX32_SHIFT));
	rScale_y = FX_Inv((1 << FX32_SHIFT));
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2S_SetBG2Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	G2S_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 0,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
}


//--------------------------------------------------------------------------------------------
/**
 * ボタンアニメコントロール
 *
 * @param	wk			画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ButtonAnimeControl(TR_CARD_WORK *wk)
{
	if (wk->AnimeType == ANIME_BUTTON_PUSH){
		//ボタン押し込む
		if( PushButton(wk, ButtonAnime[0]) ){
			wk->AnimeType = ANIME_NOTHING;
		}
	}else if (wk->AnimeType == ANIME_BUTTON_PULL){
		//ボタン戻る
		if( PushButton(wk, ButtonAnime[1]) ){
			wk->AnimeType = ANIME_NOTHING;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ボタンアニメ
 *
 * @param	wk			画面のワーク
 * @param	inAnime		アニメテーブル
 *
 * @return	BOOL	TRUE:終了	FALSE：処理中
 */
//--------------------------------------------------------------------------------------------
static BOOL PushButton(TR_CARD_WORK *wk, const u8 *inAnime)
{
	u8 frame,num;
	frame = inAnime[wk->AnmNum*2];
	if (frame == 0){
		//終了
		wk->ButtonAnmCount = 0;
		wk->AnmNum = 0;
		return TRUE;
	}else if (wk->ButtonAnmCount>=frame){
		wk->ButtonAnmCount = 0;
		wk->AnmNum++;
	}
	
	num = inAnime[wk->AnmNum*2+1];
	if (wk->ButtonAnmCount == 0){
		ChangeBgButton(wk, num);
	}
	wk->ButtonAnmCount++;

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナースクリーン転送
 *
 * @param	wk			画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DispTrainer(TR_CARD_WORK *wk)
{
	u32 transSize;
	
	transSize = wk->ScrnData->szByte;
	
	//TRAINER
	GF_BGL_LoadCharacter(wk->bgl, TRC_BG_TRAINER, wk->TrCharData->pRawData, wk->TrCharData->szByte, 0);
	
	if( GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_TRAINER ) != NULL ){
		GF_BGL_ScreenBufSet( wk->bgl, TRC_BG_TRAINER, wk->ScrnData->rawData, transSize );
	}
	
	GF_BGL_LoadScreen( wk->bgl, TRC_BG_TRAINER, wk->ScrnData->rawData, transSize, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナースクリーンクリア
 *
 * @param	wk			画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearTrainer(TR_CARD_WORK *wk)
{
	GF_BGL_ScrFill(wk->bgl, TRC_BG_TRAINER, 0, 20, 6, 6, 9, GF_BGL_SCRWRT_PALNL);
}

//--------------------------------------------------------------------------------------------
/**
 * バッジレベル取得
 *
 * @param	inCount			磨き回数
 *
 * @return	u8				レベル
 */
//--------------------------------------------------------------------------------------------
static const u8 GetBadgeLevel(const int inCount)
{
	u8 lv;
	if ((0<=inCount)&&(inCount<COUNT_LV0)){
		lv = 0;
	}else if(inCount<COUNT_LV1){
		lv =1;
	}else if (inCount<COUNT_LV2){
		lv = 2;
	}else if (inCount<COUNT_LV3){
		lv = 3;
	}else if (inCount<COUNT_LV4){
		lv = 4;
	}else{
		GF_ASSERT(0&&"BadgeLevelOver");
		lv = 0;
	}
	return lv;
}

//--------------------------------------------------------------------------------------------
/**
 * バッジこすり音制御するための現在方向をクリア
 *
 * @param	*outScruchSnd	バッジこすり音構造体へのポインタ
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void ClearScruchSndNow(TR_SCRUCH_SND *outScruchSnd)
{
	outScruchSnd->DirX = 0;
	outScruchSnd->DirY = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * バッジこすり音制御するためのデータをクリア
 *
 * @param	*outScruchSnd	バッジこすり音構造体へのポインタ
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void ClearScruchSnd(TR_SCRUCH_SND *outScruchSnd)
{
	outScruchSnd->OldDirX = 0;
	outScruchSnd->OldDirY = 0;
	outScruchSnd->DirX = 0;
	outScruchSnd->DirY = 0;
	outScruchSnd->Snd = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * バッジこすり音再生
 *
 * @param	*ioScruchSnd	バッジこすり音構造体へのポインタ
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void PlayScruchSnd(TR_SCRUCH_SND *ioScruchSnd)
{
	int snd_list[2] = {
		SND_TRCARD_SCRUCH01,
		SND_TRCARD_SCRUCH02
	};
	//初回判定
	if ((ioScruchSnd->OldDirX == 0)&&(ioScruchSnd->OldDirY == 0)){
///		OS_Printf("初回\n");//初回音
		Snd_SePlay( SND_TRCARD_SCRUCH01 );
	}
	//前回の方向と今回の方向を比較
	if ((ioScruchSnd->OldDirX*ioScruchSnd->DirX<0) ||
			(ioScruchSnd->OldDirY*ioScruchSnd->DirY<0)){
///		OS_Printf("切り替え\n");//方向が変わったので音を切り替える
		ioScruchSnd->Snd = (ioScruchSnd->Snd+1)%2;
		Snd_SePlay( snd_list[ioScruchSnd->Snd] );
	}

	ioScruchSnd->OldDirX = ioScruchSnd->DirX;
	ioScruchSnd->OldDirY = ioScruchSnd->DirY;
	ioScruchSnd->DirX = 0;
	ioScruchSnd->DirY = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サインデータ作成
 *
 * @param	*inRawData	ビット単位で持っているサインデータ
 * @param	*outData	サインデータ格納場所
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void MakeSignData(const u8 *inRawData, u8 *outData)
{
	
	int dot,raw_dot;
	u8 raw_line;	//0～7
	u8 shift;		//0～7
	for(dot=0;dot<SIGN_SIZE_X*SIGN_SIZE_Y*64;dot++){
		raw_dot = dot/64;
		raw_line = (dot/8)%8;
		shift = (dot%8);
		outData[dot] = ( 0x01 & (inRawData[(raw_dot*8)+raw_line]>>shift) );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * サインデータ転送
 *
 * @param	bgl				bgl
 * @param	inFrame			対象フレーム
 * @param	inSignData		サインデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TransSignData(GF_BGL_INI * bgl,const int inFrame, const u8 *inSignData)
{
	u16 *buf;
	u8 x,y;
	u16 count;
	
	GF_BGL_LoadCharacter( bgl, inFrame, inSignData, SIGN_BYTE_SIZE, SIGN_CGX );
	
	buf   = (u16 *)GF_BGL_ScreenAdrsGet( bgl, inFrame );
	
	count = 0;
	for( y=0; y<SIGN_SY; y++ ){
        for( x=0; x<SIGN_SX; x++ ){
            buf[ (SIGN_PY+y)*TRC_SCREEN_WIDTH + x+SIGN_PX ] = (SIGN_CGX+count);
			count++;
        }
    }
	GF_BGL_LoadScreenReq( bgl, inFrame );
}

//--------------------------------------------------------------------------------------------
/**
 * ボタン押下とカバー開閉音
 *
 * @param	inIsOpen		カバーの状態
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PlayButtonAndCoverSnd(const COVER_STATE inIsOpen)
{
	//Snd_SePlay(SND_TRCARD_BUTTON);	//ボタン音
	if (inIsOpen == COVER_OPEN){	//カバー開いている	
		Snd_SePlay(SND_TRCARD_CASE_CL);//カバー閉める音
	}else{			//カバー閉じてる
		Snd_SePlay(SND_TRCARD_CASE_OP);	//カバー開ける音
	}
}

//--------------------------------------------------------------------------------------------
/**
 * プレイ時間更新
 *
 * @param	wk				画面のワーク
 * @param	inUpdateFlg		時間更新フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdatePlayTime(TR_CARD_WORK *wk, const u8 inUpdateFlg)
{
	//更新フラグがたっているかをチェック
	if (!inUpdateFlg){
		return;
	}
	
	if (!wk->is_back){	//表面の場合のみ描画
		if (wk->SecCount == 0){
			TRCBmp_WritePlayTime(wk->win, wk->TrCardData, wk->PlayTimeBuf);
			//コロン描く
			TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), TRUE, wk->SecBuf);
		}else if(wk->SecCount == 15){
			//コロン消す
			TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), FALSE, wk->SecBuf);
		}
	}
	//カウントアップ
	wk->SecCount = (wk->SecCount+1)%30;		//	1/30なので
}

//--------------------------------------------------------------------------------------------
/**
 * バッジヒット判定(トリガー)
 *
 * @param	bgl
 * @param	hitTbl		ヒット矩形
 *
 * @return	int			結果
 */
//--------------------------------------------------------------------------------------------
static int CheckTpBadgeTrg(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl)
{
	int	ret = GF_TP_RectHitTrg( hitTbl );

	if( ret != RECT_HIT_NONE ){
		if (ret != CASE_BUTTON){
			u16	pat = 0x40;
			if( GF_BGL_DotCheck( bgl, TRC_BG_UNDER_CASE, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
				return RECT_HIT_NONE;
			}
		}else{
			return ret;
		}
	}
	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * バッジヒット判定(ベタ)
 *
 * @param	bgl
 * @param	hitTbl		ヒット矩形
 *
 * @return	int			結果
 */
//--------------------------------------------------------------------------------------------
static int CheckTpBadgeCont(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl)
{
	int	ret = GF_TP_RectHitCont( hitTbl );

	if( ret != RECT_HIT_NONE ){
		if (ret != CASE_BUTTON){
			u16	pat = 0x40;
			if( GF_BGL_DotCheck( bgl, TRC_BG_UNDER_CASE, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
				return RECT_HIT_NONE;
			}
		}else{
			return ret;
		}
	}
	return ret;
}

