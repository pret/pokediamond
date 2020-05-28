//============================================================================================
/**
 * @file	oekaki.c
 * @bfief	お絵かきボード画面処理
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================
#define DEBUGPLAY_ONE	( 0 )


#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_oekaki.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wh.h"
#include "field/fld_bmp.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "savedata/fnote_mem.h"
#include "savedata/config.h"

#include "application/oekaki.h"

#include "oekaki_local.h"

#include "comm_command_oekaki.h"


//#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"

// SE用定義
#define OEKAKI_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define OEKAKI_BS_SE		(SEQ_SE_DP_CUSTOM06)


#include "oekaki.naix"			// グラフィックアーカイブ定義

//============================================================================================
//	定数定義
//============================================================================================

//============================================================================================
//	プロトタイプ宣言
//============================================================================================

/*** 関数プロトタイプ ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( OEKAKI_WORK *wk );
static void FreeWork( OEKAKI_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( OEKAKI_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(OEKAKI_WORK *wk);
static void SetCellActor(OEKAKI_WORK *wk);
static void BmpWinInit(OEKAKI_WORK *wk, PROC* proc);
static void BmpWinDelete( OEKAKI_WORK *wk );
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void NormalTouchFunc(OEKAKI_WORK *wk);
static int Oekaki_MainNormal( OEKAKI_WORK *wk, int seq );
static void EndSequenceCommonFunc( OEKAKI_WORK *wk );
static int Oekaki_EndSelectPutString( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerOK( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerNG( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChild( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChildWait( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChildWait2( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectParent( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectParentWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEnd( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEndWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEndSynchronize( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndParentOnly( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndParentOnlyWait( OEKAKI_WORK *wk, int seq );
static void DrawPoint_to_Line( 	GF_BGL_BMPWIN *win, 	const u8 *brush, 	int px, int py, int *sx, int *sy, 	int count, int flag );
static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock );
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw );
static void MoveCommCursor( OEKAKI_WORK *wk );
static void DebugTouchDataTrans( OEKAKI_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, OEKAKI_WORK *wk );
static int ConnectCheck( OEKAKI_WORK *wk );
static void LineDataSendRecv( OEKAKI_WORK *wk );
static int MyStatusCheck( OEKAKI_WORK *wk );
static void EndMessagePrint( OEKAKI_WORK *wk, int msgno, int wait );
static int EndMessageWait( int msg_index );
static void EndMessageWindowOff( OEKAKI_WORK *wk );
static int OnlyParentCheck( void );
static int Oekaki_LogoutChildMes( OEKAKI_WORK *wk, int seq );
static int Oekaki_LogoutChildClose( OEKAKI_WORK *wk, int seq );
static int Oekaki_LogoutChildMesWait( OEKAKI_WORK *wk, int seq );
static int MyStatusGetNum( void );
static int Oekaki_NewMemberWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_NewMember( OEKAKI_WORK *wk, int seq );
static int Oekaki_NewMemberEnd( OEKAKI_WORK *wk, int seq );
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no);
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag );
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy );
static void ChangeConnectMax( OEKAKI_WORK *wk, int plus );
static int ConnectNumControl( OEKAKI_WORK *wk );
static int Oekaki_ForceEndWaitNop( OEKAKI_WORK *wk, int seq );
static void SetNextSequence( OEKAKI_WORK *wk, int nextSequence );
static void OekakiSequenceControl( OEKAKI_WORK *wk, int proc_seq );

static BOOL OekakiInitYesNoWin(OEKAKI_WORK *wk, TOUCH_SW_PARAM *param);
static void OekakiResetYesNoWin(OEKAKI_WORK *wk);
static int FakeEndYesNoSelect( OEKAKI_WORK  *wk );
static void SetTouchpanelData( TOUCH_INFO *touchResult, TP_ONE_DATA *tpData, int brush_color, int brush );


typedef struct{
	int (*func)(OEKAKI_WORK *wk, int seq);
	int execOn_SeqLeave;
}OEKAKI_FUNC_TABLE;

static OEKAKI_FUNC_TABLE FuncTable[]={
	{NULL,						1,},	// OEKAKI_MODE_INIT  = 0, 
	{Oekaki_NewMember, 		    0,},    // OEKAKI_MODE_NEWMEMBER,
	{Oekaki_NewMemberWait,      0,},    // OEKAKI_MODE_NEWMEMBER_WAIT,
	{Oekaki_NewMemberEnd,       0,},    // OEKAKI_MODE_NEWMEMBER_END,
	{Oekaki_MainNormal,         0,},    // OEKAKI_MODE,
	{Oekaki_EndSelectPutString, 1,},    // OEKAKI_MODE_END_SELECT,
	{Oekaki_EndSelectWait,		1,},	// OEKAKI_MODE_END_SELECT_WAIT,
	{Oekaki_EndSelectAnswerWait,1,},	// OEKAKI_MODE_END_SELECT_ANSWER_WAIT
	{Oekaki_EndSelectAnswerOK,	1,},	// OEKAKI_MODE_END_SELECT_ANSWER_OK
	{Oekaki_EndSelectAnswerNG,	1,},	// OEKAKI_MODE_END_SELECT_ANSWER_NG
	{Oekaki_EndChild,			1,},	// OEKAKI_MODE_END_CHILD
	{Oekaki_EndChildWait,		1,},	// OEKAKI_MODE_END_CHILD_WAIT
	{Oekaki_EndChildWait2,		1,},	// OEKAKI_MODE_END_CHILD_WAIT2
	{Oekaki_EndSelectParent,	1,},	// OEKAKI_MODE_END_SELECT_PARENT
	{Oekaki_EndSelectParentWait,1,},	// OEKAKI_MODE_END_SELECT_PARENT_WAIT
	{Oekaki_ForceEnd,			1,},	// OEKAKI_MODE_FORCE_END
	{Oekaki_ForceEndWait,		1,},	// OEKAKI_MODE_FORCE_END_WAIT
	{Oekaki_ForceEndSynchronize,1,},	// OEKAKI_MODE_FORCE_END_SYNCHRONIZE
	{Oekaki_ForceEndWaitNop,	1,},	// OEKAKI_MODE_FORCE_END_WAIT_NOP
	{Oekaki_EndParentOnly,		1,},	// OEKAKI_MODE_END_PARENT_ONLY
	{Oekaki_EndParentOnlyWait,	1,},	// OEKAKI_MODE_END_PARENT_ONLY_WAIT
	{Oekaki_LogoutChildMes,		1,},	// OEKAKI_MODE_LOGOUT_CHILD
	{Oekaki_LogoutChildMesWait,	1,},	// OEKAKI_MODE_LOGOUT_CHILD_WAIT
	{Oekaki_LogoutChildClose,	1,},	// OEKAKI_MODE_LOGOUT_CHILD_CLOSE
};



//============================================================================================
//	プロセス関数
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
PROC_RESULT OekakiProc_Init( PROC * proc, int * seq )
{
	OEKAKI_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OEKAKI, 0x40000 );

		wk = PROC_AllocWork( proc, sizeof(OEKAKI_WORK), HEAPID_OEKAKI );
		memset( wk, 0, sizeof(OEKAKI_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OEKAKI );
		
		// 文字列マネージャー生成
		wk->WordSet    = WORDSET_Create( HEAPID_OEKAKI );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_oekaki_dat, HEAPID_OEKAKI );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM バンク設定
		VramBankSet();
		
		// BGLレジスタ設定
		BgInit( wk->bgl );					

		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

		// 輝度変更セット
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		
		// パラメータ取得
		{
			OEKAKI_PARAM *param = (OEKAKI_PARAM*)PROC_GetParentWork( proc );
			wk->param = param;
		}

		//BGグラフィックセット
		BgGraphicSet( wk );

		// タッチパネルシステム初期化
		InitTPSystem();						
		InitTPNoBuff(2);
  
		// VBlank関数セット
		sys_VBlankFuncChange( VBlankFunc, wk->bgl );	
  
		// ワーク初期化
		InitWork( wk );

		// OBJキャラ、パレットマネージャー初期化
		char_pltt_manager_init();

		// CellActorシステム初期化
		InitCellActor(wk);
		
		// CellActro表示登録
		SetCellActor(wk);

		// BMPWIN登録・描画
		BmpWinInit(wk,proc);

		// サウンドデータロード(名前入力)(BGM引継ぎ)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		// 画面出力を上下入れ替える
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

		// 通信コマンドを交換リスト用に変更
		CommCommandOekakiBoardInitialize( wk );
        // お絵かき時には接続切断でエラー扱いしない
        CommStateSetErrorCheck(FALSE,TRUE);
        
        // 3台まで接続可能に書き換え(開始した時は２人でここにくるのであと一人だけ入れるようにしておく）
		if(CommGetCurrentID()==0){
	        CommStateSetLimitNum(3);
		}

		
		WirelessIconEasy();

		// 親だったら「おえかき通信中」にビーコン書き換え
		if(CommGetCurrentID()==0){
			Union_BeaconChange( UNION_PARENT_MODE_OEKAKI_FREE );
			CommMPSetDisconnectOtherError(TRUE);
		}
		(*seq)++;
		break;
	case 1:
		wk = PROC_GetWork( proc );
		(*seq) = SEQ_IN;
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
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

PROC_RESULT OekakiProc_Main( PROC * proc, int * seq )
{
	OEKAKI_WORK * wk  = PROC_GetWork( proc );

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		wk->ridatu_bit &= WH_GetBitmap();
	}
	
	// ワークに現在のprocシーケンスを保存
	wk->proc_seq = *seq;

	// サブシーケンス遷移制御を行う
	OekakiSequenceControl( wk, *seq );
	
	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ワイプ処理待ち
//			*seq = SEQ_MAIN;

			// 自分が子機で接続台数が２台以上だった場合はもう絵が描かれている
			if(CommGetCurrentID()!=0){
				if( (MyStatusGetNum()>=2) ){
					// 子機乱入リクエスト
					CommSendData(CO_OEKAKI_CHILD_JOIN, NULL, 0);
					OS_Printf("乱入します\n");
					*seq = SEQ_MAIN;
				}
				break;
			}else{
				//親はメインへ
				*seq = SEQ_MAIN;
			}
		}
		break;

	case SEQ_MAIN:
		// カーソル移動

		// シーケンス毎の動作
		if(FuncTable[wk->seq].func!=NULL){
			*seq = FuncTable[wk->seq].func( wk, *seq );
		}
		// 接続人数を確認して上画面に名前を描画
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xd,0xf),wk);

		if(CommGetCurrentID()==0){				// 親は
			int temp = ConnectNumControl(wk);
			if(*seq == SEQ_MAIN){
				// 既に終了シーケンスなどに入っている場合は書き換えない
				*seq = temp;
			}
		}
		CursorColTrans(&wk->CursorPal);

		break;
	case SEQ_LEAVE:
		if(FuncTable[wk->seq].func!=NULL && FuncTable[wk->seq].execOn_SeqLeave){
			*seq = FuncTable[wk->seq].func( wk, *seq );
		}
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			OS_Printf("ワイプ終了確認\n");
			return PROC_RES_FINISH;
		}
		break;
	}
	CLACT_Draw( wk->clactSet );									// セルアクター常駐関数

	return PROC_RES_CONTINUE;
}

#define DEFAULT_NAME_MAX		18

// ダイヤ・パールで変わるんだろう
#define MALE_NAME_START			0
#define FEMALE_NAME_START		18

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
PROC_RESULT OekakiProc_End( PROC * proc, int * seq )
{
	OEKAKI_WORK  *wk    = PROC_GetWork( proc );
	OEKAKI_PARAM *param = (OEKAKI_PARAM*)PROC_GetParentWork( proc );
	int i;
	void *FnoteWork;

	switch(*seq){
	case 0:
		OS_Printf("おえかきワーク解放処理突入\n");
		// 冒険ノート用処理
		FnoteWork = FNOTE_SioUnionPictureDataMake( HEAPID_OEKAKI );
		FNOTE_DataSave( param->fnote, FnoteWork, FNOTE_TYPE_SIO );

		// Vblank期間中のBG転送終了
		sys_VBlankFuncChange( NULL, NULL);

		// セルアクターリソース解放

		// キャラ転送マネージャー破棄
		CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
		CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

		// パレット転送マネージャー破棄
		CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
		CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
		// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
		for(i=0;i<CLACT_RESOURCE_NUM;i++){
			CLACT_U_ResManagerDelete(wk->resMan[i]);
		}
		// セルアクターセット破棄
		CLACT_DestSet(wk->clactSet);

		//OAMレンダラー破棄
		REND_OAM_Delete();

		// リソース解放
		DeleteCharManager();
		DeletePlttManager();

		// BMPウィンドウ開放
		BmpWinDelete( wk );

		// BGL削除
		BgExit( wk->bgl );

		// タッチパネルシステム終了
		StopTP();							


		// メッセージマネージャー・ワードセットマネージャー解放
		MSGMAN_Delete( wk->MsgManager );
		WORDSET_Delete( wk->WordSet );

		(*seq)++;
		break;
	case 1:
		// 通信終了
	//	CommStateExitUnion();
		CommStateSetLimitNum(1);
		CommStateUnionBconCollectionRestart();
		UnionRoomView_ObjInit( param->view );

		// 入れ替わっていた上下画面出力を元に戻す
		GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

		// ビーコン書き換え
		Union_BeaconChange( UNION_PARENT_MODE_FREE );

		CommMPSetDisconnectOtherError(FALSE);
		(*seq)++;
		break;
	case 2:
		if (wk->ireagalJoin){
			OS_Printf("親機だけになるまで待機\n");	
			if (WH_GetBitmap() == 1){
				(*seq)++;
			}
		}else{
			(*seq)++;
		}
		break;
	case 3:
		CommStateSetLimitNum(2);
		// ワーク解放
		FreeWork( wk );

		sys_FreeMemoryEz( wk->param );

		PROC_FreeWork( proc );				// PROCワーク開放

		sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

		sys_DeleteHeap( HEAPID_OEKAKI );

		CommStateSetLimitNum(2);

		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
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
	
	GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
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
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
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
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// メイン画面文字版0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// メイン画面ラクガキ面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// メイン画面背景
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

#if 0
	// 背景 (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
#endif

	// サブ画面テキスト面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// サブ画面背景面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_OEKAKI );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_OEKAKI );

}


#define TALK_MESSAGE_BUF_NUM	( 40*2 )

//------------------------------------------------------------------
/**
 * お絵かきワーク初期化
 *
 * @param   wk		OEKAKI_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( OEKAKI_WORK *wk )
{
	int i;

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_OEKAKI );
		wk->AllTouchResult[i].size = 0;
		wk->OldTouch[i].size = 0;
		wk->TrainerStatus[i][0] = NULL;
		wk->TrainerStatus[i][1] = NULL;

	}
	// 「やめる」文字列バッファ作成
	wk->EndString  = STRBUF_Create( 10, HEAPID_OEKAKI );
	wk->TalkString = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_OEKAKI );

	// ブラシ初期化
	wk->brush_color  = 0;
	wk->brush        = MIDDLE_BRUSH;
	wk->banFlag      = OEKAKI_BAN_OFF;
	wk->yesno_flag   = 0;
	wk->shareNum     = 2;
	wk->shareBit     = WH_GetBitmap();
	wk->firstChild   = 0;
	wk->ireagalJoin  = 0;
	wk->seq          = 0;
	wk->bookJoin  = 0;
	wk->joinBit  = 0;

	// 親は通信で絵を受け取る必要が無い
	if( CommGetCurrentID()==0 ){
		SetNextSequence( wk, OEKAKI_MODE );
	}else{
		// 絵を受け取らないといけない
		SetNextSequence( wk, OEKAKI_MODE );
	}
	
	// 「やめる」取得
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_08, wk->EndString );

	// お絵かき画像圧縮データ領域
	wk->lz_buf = sys_AllocMemory( HEAPID_OEKAKI, 30*16*32 );

	// 下画面ウインドウシステム初期化
	wk->TouchSubWindowSys = TOUCH_SW_AllocWork( HEAPID_OEKAKI );

	// 接続人数監視用ワーク初期化
	wk->connectBackup = 0;
}

//------------------------------------------------------------------
/**
 * $brief   ワーク解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( OEKAKI_WORK *wk )
{
	int i;

	sys_FreeMemoryEz(  wk->lz_buf );
	TOUCH_SW_FreeWork( wk->TouchSubWindowSys );


	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->EndString  ); 

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
static void BgExit( GF_BGL_INI * ini )
{

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemoryEz( ini );
}


//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( OEKAKI_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, PALTYPE_MAIN_BG, 0, 16*2*2,  HEAPID_OEKAKI);
	ArcUtil_PalSet(    ARC_OEKAKI_GRA, NARC_oekaki_oekaki_s_nclr, PALTYPE_SUB_BG,  0, 16*2*2,  HEAPID_OEKAKI);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_OEKAKI );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_OEKAKI );




	// メイン画面BG2キャラ転送
	ArcUtil_BgCharSet( ARC_OEKAKI_GRA, NARC_oekaki_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// メイン画面BG2スクリーン転送
	ArcUtil_ScrnSet(   ARC_OEKAKI_GRA, NARC_oekaki_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_OEKAKI);



	// サブ画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_OEKAKI_GRA, NARC_oekaki_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// サブ画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_OEKAKI_GRA, NARC_oekaki_subbg_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_OEKAKI);

	// サブ画面会話ウインドウグラフィック転送
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_OEKAKI );

	MenuWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1+TALK_WIN_CGX_SIZ, FLD_MENUFRAME_PAL, 0, HEAPID_OEKAKI );

}


//** CharManager PlttManager用 **//
#define OEKAKI_CHAR_CONT_NUM				(20)
#define OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define OEKAKI_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define OEKAKI_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OEKAKI_CHAR_CONT_NUM,
			OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE,
			OEKAKI_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_OEKAKI
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(OEKAKI_PLTT_CONT_NUM, HEAPID_OEKAKI);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   wk		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(OEKAKI_WORK *wk)
{
	int i;
	
	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 126,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 126,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_OEKAKI);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 50+3, &wk->renddata, HEAPID_OEKAKI );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_OEKAKI);
	}


	//---------上画面用-------------------

	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OEKAKI);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_OEKAKI);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);


	//---------下画面用-------------------



	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_OEKAKI);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_OEKAKI);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);

	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

static const u16 pal_button_oam_table[][3]={
	{13     , 171, 5},		// 黒
	{13+24*1, 171, 7},		// 白
	{13+24*2, 171, 9},		// 赤
	{13+24*3, 171,11},		// 紫
	{13+24*4, 171,13},		// 青
	{13+24*5, 171,15},		// 水色
	{13+24*6, 171,17},		// 緑
	{13+24*7, 171,19},		// 黄色
	{13+24*8+20, 171,21},	// 「やめる」

	// ペン先アイコン
	{20,	  9,   29, },
	{36,      9,   32, },	// 初期値で決定状態になっている
	{52,      9,   33, },
};

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			OEKAKI_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(OEKAKI_WORK *wk)
{
	int i;
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	{
		//登録情報格納
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_m;

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_OEKAKI;

		//セルアクター表示開始

		// メイン画面用(矢印の登録）
		for(i=0;i<5;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  TRAINER_NAME_POS_X + i * 40);
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN );
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->MainActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->MainActWork[i],1);
			CLACT_AnmChg( wk->MainActWork[i], i );
			CLACT_SetDrawFlag( wk->MainActWork[i], 0 );

		}

		// メイン画面パレット・「やめる」ボタンの登録
		for(i=0;i<9+3;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  pal_button_oam_table[i][0]);
			add.mat.y = FX32_ONE * ( pal_button_oam_table[i][1] );
			wk->ButtonActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ButtonActWork[i],1);
			CLACT_AnmChg( wk->ButtonActWork[i], pal_button_oam_table[i][2] );
			if(i >= 8){
				CLACT_BGPriorityChg( wk->ButtonActWork[i], 2 );
			}
//			CLACT_SetDrawFlag( wk->ButtonActWork[i], 0 );
		}

		// 黒色パレットはへこませておく
		CLACT_AnmChg( wk->ButtonActWork[0], 6 );


		// サブ画面用(矢印の登録）
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
			wk->SubActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->SubActWork[i],1);
			CLACT_AnmChg( wk->SubActWork[i], i );
			CLACT_DrawPriorityChg(wk->SubActWork[i], 1);	// それぞれのアクターのプライオリティ設定
			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
			
		}
		
	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//サブ画面OBJ面ＯＮ
	
}

// おえかきボードBMP（下画面）
#define OEKAKI_BOARD_POSX	 ( 1 )
#define OEKAKI_BOARD_POSY	 ( 2 )
#define OEKAKI_BOARD_W	 ( 30 )
#define OEKAKI_BOARD_H	 ( 15 )


// 名前表示BMP（上画面）
#define OEKAKI_NAME_BMP_W	 ( 10 )
#define OEKAKI_NAME_BMP_H	 (  2 )
#define OEKAKI_NAME_BMP_SIZE (OEKAKI_NAME_BMP_W * OEKAKI_NAME_BMP_H)


// 「やめる」文字列BMP（下画面）
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 21 )
#define OEKAKI_END_BMP_W	( 6  )
#define OEKAKI_END_BMP_H	( 2  )


// 会話ウインドウ表示位置定義
#define OEKAKI_TALK_X		(  2 )
#define OEKAKI_TALK_Y		(  1 )
//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit(OEKAKI_WORK *wk, PROC* proc)
{
	// ---------- メイン画面 ------------------

	// BG0面BMP（会話ウインドウ）ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		OEKAKI_TALK_X, OEKAKI_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG1面用BMP（お絵かき画像）ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->OekakiBoard, GF_BGL_FRAME1_M,
		OEKAKI_BOARD_POSX, OEKAKI_BOARD_POSY, OEKAKI_BOARD_W, OEKAKI_BOARD_H, 0,  1 );
	GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );

	// BG1面BMP（やめる）ウインドウ確保・描画
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_M,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 13,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );
//	GF_STR_PrintSimple( &wk->EndWin, FONT_TALK, wk->EndString, 0, 0, MSG_ALLPUT, NULL);
	GF_STR_PrintColor( &wk->EndWin, FONT_TALK, wk->EndString, 0, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x7,0x1,0x0),NULL);

	// ----------- サブ画面名前表示BMP確保 ------------------
	{
		int i;
		for(i=0;i<OEKAKI_MEMBER_MAX;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[i], GF_BGL_FRAME0_S,	
				TRAINER_NAME_POS_X/8+2, TRAINER_NAME_POS_Y/8+i*4-1, 10, 2, 13,  1+i*OEKAKI_NAME_BMP_SIZE);
			GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[i], 0 );
		}

		//最初に見えている面なので文字パネル描画と転送も行う
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xd,0xf), wk );
	}

}	

// はい・いいえ用定義（下画面）
#define YESNO_CHARA_OFFSET	(1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY)
#define YESNO_CHARA_W		( 8 )
#define YESNO_CHARA_H		( 4 )





//------------------------------------------------------------------
/**
 * $brief   確保したBMPWINを解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( OEKAKI_WORK *wk )
{
	int i;
	
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->OekakiBoard );
	GF_BGL_BmpWinDel( &wk->MsgWin );


}








//------------------------------------------------------------------
/**
 * $brief   カーソル位置を変更する
 *
 * @param   act		アクターのポインタ
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y - 8 );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


// ---------------------------------------------------------
// 通常時タッチ検出テーブル
// ---------------------------------------------------------

#define PAL_BUTTON_X	(  0  )
#define PAL_BUTTON_Y	( 150 )
#define PAL_BUTTON_W	( 3*8 )
#define PAL_BUTTON_H	( 5*8 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define END_BUTTON_RECT ( 8*8 -1 )

#define PAL_BUTTON0_X	( PAL_BUTTON_X+PAL_BUTTON_W*0 )
#define PAL_BUTTON1_X	( PAL_BUTTON_X+PAL_BUTTON_W*1 )
#define PAL_BUTTON2_X	( PAL_BUTTON_X+PAL_BUTTON_W*2 )
#define PAL_BUTTON3_X	( PAL_BUTTON_X+PAL_BUTTON_W*3 )
#define PAL_BUTTON4_X	( PAL_BUTTON_X+PAL_BUTTON_W*4 )
#define PAL_BUTTON5_X	( PAL_BUTTON_X+PAL_BUTTON_W*5 )
#define PAL_BUTTON6_X	( PAL_BUTTON_X+PAL_BUTTON_W*6 )
#define PAL_BUTTON7_X	( PAL_BUTTON_X+PAL_BUTTON_W*7 )
#define END_BUTTON_X	( PAL_BUTTON_X+PAL_BUTTON_W*8 )

#define BRUSH_BUTTON0_X ( 14 ) // 16,5 23,12
#define BRUSH_BUTTON1_X ( 30 ) // 16,5 23,12
#define BRUSH_BUTTON2_X ( 46 ) // 16,5 23,12
#define BRUSH_BUTTON_Y  (  1 ) // 16,5 23,12
#define BRUSH_BUTTON_W  ( 12 ) // 16,5 23,12
#define BRUSH_BUTTON_H  ( 12 ) // 16,5 23,12


static const RECT_HIT_TBL sub_button_hittbl[]={

// パレット
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON0_X,PAL_BUTTON0_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON1_X,PAL_BUTTON1_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON2_X,PAL_BUTTON2_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON3_X,PAL_BUTTON3_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON4_X,PAL_BUTTON4_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON5_X,PAL_BUTTON5_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON6_X,PAL_BUTTON6_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON7_X,PAL_BUTTON7_X+PAL_BUTTON_RECT},

// 終了ボタン
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,END_BUTTON_X,END_BUTTON_X+END_BUTTON_RECT},

// ペン先ボタン
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON0_X,BRUSH_BUTTON0_X+BRUSH_BUTTON_W},
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON1_X,BRUSH_BUTTON1_X+BRUSH_BUTTON_W},
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON2_X,BRUSH_BUTTON2_X+BRUSH_BUTTON_W},

{RECT_HIT_END,0,0,0},		// 終了データ
};


// ---------------------------------------------------------
// 離脱選択禁止中の際のYESNOボタン検出テーブル
// ---------------------------------------------------------
#define OEKAKI_YESNO_BUTTON_X ( 25 )
#define OEKAKI_YESNO_BUTTON_Y ( 6  )

#define FAKE_YESNO_X	( OEKAKI_YESNO_BUTTON_X*8 )
#define FAKE_YESNO_Y	( OEKAKI_YESNO_BUTTON_Y*8 )
#define FAKE_YESNO_W	( 6*8 )
#define FAKE_YESNO_H	( 8*8 )

static const RECT_HIT_TBL fake_yesno_hittbl[]={
{FAKE_YESNO_Y, FAKE_YESNO_Y+FAKE_YESNO_H, FAKE_YESNO_X, FAKE_YESNO_X+FAKE_YESNO_W},
{RECT_HIT_END,0,0,0},
};

// ---------------------------------------------------------
// 描画領域検出用テーブル
// ---------------------------------------------------------
#define DRAW_AREA_X	(  8  )
#define DRAW_AREA_Y	( 16  )
#define DRAW_AREA_W	( OEKAKI_BOARD_W*8 )
#define DRAW_AREA_H	( OEKAKI_BOARD_H*8)

static const RECT_HIT_TBL sub_canvas_touchtbl[]={
	{DRAW_AREA_Y,DRAW_AREA_Y+DRAW_AREA_H,DRAW_AREA_X,DRAW_AREA_X+DRAW_AREA_W},
{RECT_HIT_END,0,0,0},		// 終了データ
};




//------------------------------------------------------------------
/**
 * タッチパネルで押したボタンがへこむ
 *
 * @param   wk		OEKAKI_WORKのポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NormalTouchFunc(OEKAKI_WORK *wk)
{
	int button=-1,touch;
	int decide = FALSE;
	
	// 入力処理

	// カラー切り替え
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		switch(button){
		case 0:	case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			// 色変更
			if(wk->brush_color!=button){
				wk->brush_color = button;
				PalButtonAppearChange( wk->ButtonActWork, button);
				Snd_SePlay(OEKAKI_DECIDE_SE);
			}
			break;
		case 8:
			// 「やめる」を押したらウインドウ描画開始
			if(wk->seq==OEKAKI_MODE){
				// 親機の場合は接続拒否
				if(CommGetCurrentID()==0){
					//コネクト数と表示人数が異なる場合は、やめるボタンを無反応にする
					if (wk->shareBit != WH_GetBitmap()){
						Snd_SePlay(OEKAKI_BS_SE);
						break;
					}
					CommStateSetLimitNum(CommGetConnectNum());
					wk->banFlag = OEKAKI_BAN_ON;
					// 「おえかきをやめますか？」
					EndMessagePrint( wk, msg_oekaki_02, 1 );
					SetNextSequence( wk, OEKAKI_MODE_END_SELECT );
					EndButtonAppearChange( wk->ButtonActWork, TRUE );
					decide = TRUE;
					Snd_SePlay(OEKAKI_DECIDE_SE);
				}else{
					if(wk->AllTouchResult[0].banFlag == OEKAKI_BAN_ON ){
						// 親機に禁止されているときはＳＥのみ
						Snd_SePlay(OEKAKI_BS_SE);
					}else{
						// 「おえかきをやめますか？」
						EndMessagePrint( wk, msg_oekaki_02, 1 );
						SetNextSequence( wk, OEKAKI_MODE_END_SELECT );
						EndButtonAppearChange( wk->ButtonActWork, TRUE );
						decide = TRUE;
						Snd_SePlay(OEKAKI_DECIDE_SE);
					}
				}

			}
			break;
		case 9:	case 10: case 11:
			// ペン先変更
			{
				int i;
				for(i=0;i<3;i++){
					if((button-9)==i){
						CLACT_AnmChg( wk->ButtonActWork[CELL_BRUSH_NO+i], 29+2*i+1 );		// ON
					}else{
						CLACT_AnmChg( wk->ButtonActWork[CELL_BRUSH_NO+i], 29+2*i );	// OFF
					}
				}
				if(wk->brush!=(SMALL_BRUSH + button-9)){
					wk->brush = SMALL_BRUSH + button-9;
					Snd_SePlay(SEQ_SE_DP_BUTTON3);
				}
			}
			break;
		}
	}

	// カーソル位置変更
	touch = GF_TP_RectHitCont( sub_canvas_touchtbl );

	CLACT_SetDrawFlag( wk->MainActWork[CommGetCurrentID()], 0 );
	if(touch!=RECT_HIT_NONE){
		// 自分のカーソルはタッチパネルの座標を反映させる
		SetCursor_Pos( wk->MainActWork[CommGetCurrentID()], sys.tp_x, sys.tp_y );
		CLACT_SetDrawFlag( wk->MainActWork[CommGetCurrentID()], 1 );
	}

	// サンプリング情報を取得して格納
	{
		TP_ONE_DATA	tpData;
		int i;
		if(MainTP( &tpData, TP_BUFFERING_JUST, 64 )==TP_OK){
			SetTouchpanelData( &wk->MyTouchResult, &tpData, wk->brush_color, wk->brush );

			if(decide == TRUE){
				wk->MyTouchResult.size = 0;
			}
		}
	}

	// 見た目の処理
//	button=GF_TP_RectHitCont( sub_button_hittbl );


}


//------------------------------------------------------------------
/**
 * $brief   パレットとやめるボタンのセルアクター制御
 *
 * @param   act		アクターのポインタ
 * @param   button		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no )
{
	int i;
	
	for(i=0;i<8;i++){
		// 押されたボタンはへこむ。ほかのボタンは戻る
		if(i==no){
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2]+1 );
		}else{
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2] );
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   やめるボタンのオン・オフ
 *
 * @param   act		アクターのポインタ
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag )
{
	if(flag==TRUE){
		CLACT_AnmChg( act[8], pal_button_oam_table[8][2]+1 );
	}else{
		CLACT_AnmChg( act[8], pal_button_oam_table[8][2] );
	}
}

//------------------------------------------------------------------
/**
 * $brief   お絵かきボード通常処理
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_MainNormal( OEKAKI_WORK *wk, int seq )
{
	NormalTouchFunc(wk);			//  タッチパネル処理


	
	if(CommGetCurrentID()==0){				// 親機の時
		if(OnlyParentCheck()!=1){			// 一人じゃないか？
			LineDataSendRecv( wk );
		}
	}else{
			LineDataSendRecv( wk );
	}
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 1 );

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   終了選択処理の共通処理関数(後ろで描画等）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndSequenceCommonFunc( OEKAKI_WORK *wk )
{
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 0 );
	
}


//------------------------------------------------------------------
/**
 * $brief   新しい子機がきたので親機が画像を送信しはじめる
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Oekaki_NewMember( OEKAKI_WORK *wk, int seq )
{
	// ●●●さんがはいってきました
	OS_Printf("newMemberは%d\n",wk->newMemberId);
	if(CommGetCurrentID()==wk->newMemberId){
		EndMessagePrint(wk, msg_oekaki_14, 0);
	}else{
		EndMessagePrint(wk, msg_oekaki_01, 0);
	}
	SetNextSequence( wk, OEKAKI_MODE_NEWMEMBER_WAIT );

	Snd_SePlay(SEQ_SE_DP_BUTTON9);

	// 画像転送状態になったら輝度ダウン
	G2_SetBlendBrightness(  GX_BLEND_PLANEMASK_BG1|
							GX_BLEND_PLANEMASK_BG2|
							GX_BLEND_PLANEMASK_BG3|
							GX_BLEND_PLANEMASK_OBJ
								,  -6);

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   新しい子機用の画像受信待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Oekaki_NewMemberWait( OEKAKI_WORK *wk, int seq )
{
//	if( EndMessageWait( wk->MsgIndex ) ){
//		// 会話ウインドウ表示待ちは行うが、画像データ受信の方がおそいはずなのでそっちがシーケンスをきりかえるはず
//	}
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   子機乱入受信終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_NewMemberEnd( OEKAKI_WORK *wk, int seq )
{
	// 輝度ダウン解除
	G2_BlendNone();

	ChangeConnectMax(wk, 1);

	SetNextSequence( wk, OEKAKI_MODE );
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	//乱入済み
	wk->bookJoin = 0;
	OS_Printf("乱入成功\n");
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   お絵かきボード「やめる」を選択した時
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectPutString( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;
		BOOL rc;

		// YES NO ウィンドウボタンの表示
		param.p_bgl		= wk->bgl;
		param.bg_frame	= GF_BGL_FRAME0_M;
		param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
		param.pltt_offs = 8;
		param.x			= OEKAKI_YESNO_BUTTON_X; /*25*/
		param.y			= OEKAKI_YESNO_BUTTON_Y; /* 6*/

		rc = OekakiInitYesNoWin(wk, &param);
		GF_ASSERT(rc);

		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_WAIT );
	}
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「やめますか？」はい・いいえ選択待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectWait( OEKAKI_WORK *wk, int seq )
{
	int result;

	// 誤送信を防ぐ
	wk->MyTouchResult.size = 0;

	if(wk->AllTouchResult[0].banFlag==OEKAKI_BAN_ON && CommGetCurrentID()!=0){
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理

		if(FakeEndYesNoSelect(wk)){
			// 親機に禁止されているときはＳＥのみ
			Snd_SePlay(OEKAKI_BS_SE);
		}

		return seq;
	}

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}
	
	if(MyStatusGetNum() != CommGetConnectNum()){
		//一致していないなら「やめる」許可しない(子も通るここは親しか更新されないshareNumは見ない)
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}

	result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//やめますか？
	case TOUCH_SW_RET_YES:						//はい
		if(CommGetCurrentID()==0){		
			SetNextSequence( wk, OEKAKI_MODE_END_SELECT_PARENT );
			EndMessagePrint( wk, msg_oekaki_05, 1 );		// リーダーがやめると…
		}else{
			COMM_OEKAKI_END_CHILD_WORK coec;
			
			MI_CpuClear8(&coec, sizeof(COMM_OEKAKI_END_CHILD_WORK));
			coec.request = COEC_REQ_RIDATU_CHECK;
			coec.ridatu_id = CommGetCurrentID();
			
			wk->status_end = TRUE;
			wk->ridatu_wait = 0;

//			SetNextSequence( wk, OEKAKI_MODE_END_CHILD );
			SetNextSequence( wk, OEKAKI_MODE_END_SELECT_ANSWER_WAIT );
			CommSendData( CO_OEKAKI_END_CHILD, &coec, sizeof(COMM_OEKAKI_END_CHILD_WORK) );
			BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		}
		OekakiResetYesNoWin(wk);

		//おえかき再描画
		GF_BGL_BmpWinOn( &wk->OekakiBoard );
	
		break;
	case TOUCH_SW_RET_NO:						//いいえ
		SetNextSequence( wk, OEKAKI_MODE );
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		OekakiResetYesNoWin(wk);

		//おえかき再描画
		GF_BGL_BmpWinOn( &wk->OekakiBoard );
		
		// 親機は接続拒否を解除
		if(CommGetCurrentID()==0){
//			CommStateSetEntryChildEnable(TRUE);
			CommStateSetLimitNum(CommGetConnectNum()+1);
			wk->banFlag = OEKAKI_BAN_OFF;
		}

		break;
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「やめますか？」＞「はい」、で親から離脱許可待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectAnswerWait( OEKAKI_WORK *wk, int seq )
{
	// 誤送信を防ぐ
	wk->MyTouchResult.size = 0;
	
	wk->ridatu_wait = 0;
	
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「やめますか？」＞「はい」、で親から離脱許可待ち＞OK!
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectAnswerOK( OEKAKI_WORK *wk, int seq )
{
	// 誤送信を防ぐ
	wk->MyTouchResult.size = 0;

	if((wk->oya_share_num != CommGetConnectNum())
			|| (wk->oya_share_num != MyStatusGetNum())){
		OS_TPrintf("share_nuM = %d, Comm = %d, My = %d, Bit = %d\n", wk->oya_share_num, CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		wk->ridatu_wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_ANSWER_NG );
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}
	
	wk->ridatu_wait++;
	OS_TPrintf("ridatu_wait = %d\n", wk->ridatu_wait);
	if(wk->ridatu_wait > 30){
		COMM_OEKAKI_END_CHILD_WORK coec;
		
		MI_CpuClear8(&coec, sizeof(COMM_OEKAKI_END_CHILD_WORK));
		coec.request = COEC_REQ_RIDATU_EXE;
		coec.ridatu_id = CommGetCurrentID();

		CommSendData( CO_OEKAKI_END_CHILD, &coec, sizeof(COMM_OEKAKI_END_CHILD_WORK) );

		wk->ridatu_wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD );
	}


	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「やめますか？」＞「はい」、で親から離脱許可待ち＞NG!
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectAnswerNG( OEKAKI_WORK *wk, int seq )
{
	// 誤送信を防ぐ
	wk->MyTouchResult.size = 0;

	wk->status_end = FALSE;
	SetNextSequence( wk, OEKAKI_MODE );
	EndButtonAppearChange( wk->ButtonActWork, FALSE );
	
	OS_TPrintf("==========離脱強制キャンセル！===========\n");
	
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

// OEKAKI_MODE_END_CHILD
//------------------------------------------------------------------
/**
 * $brief   子機終了メッセージ開始
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Oekaki_EndChild( OEKAKI_WORK *wk, int seq )
{
	u8 temp;
	
	// おえかきをやめました
	EndMessagePrint( wk, msg_oekaki_07, 1 );	

	// 終了通達
//	CommSendData( CO_OEKAKI_END_CHILD, &temp, 1 );

	SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT );

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}
				

// OEKAKI_MODE_END_CHILD_WAIT
//------------------------------------------------------------------
/**
 * $brief   子機終了メッセージ表示終了待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Oekaki_EndChildWait( OEKAKI_WORK *wk, int seq )
{			

	if( EndMessageWait( wk->MsgIndex ) ){
		wk->wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT2 );
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   メッセージ表示終了後少し待つ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Oekaki_EndChildWait2( OEKAKI_WORK *wk, int seq )
{			

	if( ++wk->wait > OEKAKI_MESSAGE_END_WAIT ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		seq = SEQ_OUT;						//終了シーケンスへ
	}

	EndSequenceCommonFunc( wk );			//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   親機が終了するときはもう一度「リーダーがやめると…」と質問する
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectParent( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;
		BOOL rc;

		// YES NO ウィンドウボタンの表示
		param.p_bgl		= wk->bgl;
		param.bg_frame	= GF_BGL_FRAME0_M;
		param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
		param.pltt_offs = 8;
		param.x			= 25;
		param.y			= 6;

		rc = OekakiInitYesNoWin(wk, &param);
		GF_ASSERT(rc);

		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_PARENT_WAIT );

	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   親機の２回目の「はい・いいえ」
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectParentWait( OEKAKI_WORK *wk, int seq )
{
	int result = TOUCH_SW_Main( wk->TouchSubWindowSys );

	if(wk->shareNum != MyStatusGetNum()	//一致していないなら「やめる」許可しない
			|| wk->ridatu_bit != 0){	//離脱しようとしている子がいるなら許可しない
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}

	switch(result){				//やめますか？
	case TOUCH_SW_RET_YES:						//はい
		SetNextSequence( wk, OEKAKI_MODE_FORCE_END );
		CommSendData_ServerSide( CO_OEKAKI_END, NULL, 0 );	//終了通知
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// 親機（自分）の名前をWORDSET
		seq = SEQ_LEAVE;
		OS_Printf("OEKAKI_MODE_FORCE_ENDにかきかえ\n");
		OekakiResetYesNoWin(wk);
		break;
	case TOUCH_SW_RET_NO:						//いいえ
		SetNextSequence( wk, OEKAKI_MODE );
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		OekakiResetYesNoWin(wk);

		// 親機は接続拒否を解除
		if(CommGetCurrentID()==0){
//			CommStateSetEntryChildEnable(TRUE);
			CommStateSetLimitNum(CommGetConnectNum()+1);
			wk->banFlag = OEKAKI_BAN_OFF;
		}
		break;
	}


	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   親機が終わりと言ったので終わる
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ForceEnd( OEKAKI_WORK *wk, int seq )
{
	WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// 親機（自分）の名前をWORDSET
	
	EndMessagePrint( wk, msg_oekaki_04, 1 );				// リーダーが抜けたので解散します。
	SetNextSequence( wk, OEKAKI_MODE_FORCE_END_WAIT );

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}


//------------------------------------------------------------------
/**
 * $brief   親機が終わりと言ったので終わる
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ForceEndWait( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_FORCE_END_SYNCHRONIZE );
		CommTimingSyncStart(OEKAKI_SYNCHRONIZE_END);
		OS_Printf("同期開始\n");
		
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   全員の通信同期を待つ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ForceEndSynchronize( OEKAKI_WORK *wk, int seq )
{
	if(CommIsTimingSync(OEKAKI_SYNCHRONIZE_END) || CommGetConnectNum() == 1){
		OS_Printf("終了時同期成功  seq = %d\n", seq);
		OS_Printf("コネクト人数%d\n",CommGetConnectNum());
//		wk->seq = OEKAKI_MODE_FORCE_END_WAIT_NOP;
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		seq = SEQ_OUT;						//終了シーケンスへ
	}
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}

//------------------------------------------------------------------
/**
 * @brief   何もしない
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ForceEndWaitNop( OEKAKI_WORK *wk, int seq )
{
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   親一人になったので終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndParentOnly( OEKAKI_WORK *wk, int seq )
{
	EndMessagePrint( wk, msg_oekaki_06, 1 );				// リーダーが抜けたので解散します。
	SetNextSequence( wk, OEKAKI_MODE_END_PARENT_ONLY_WAIT );

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   一人になった文章を表示して終了シーケンスへ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndParentOnlyWait( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT2 );
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   ●●●さんがかえりました
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_LogoutChildMes( OEKAKI_WORK *wk, int seq )
{
	// ●●●さんがかえりました
	if( wk->MsgIndex != 0xff && EndMessageWait( wk->MsgIndex ) == 0){
		//表示中のメッセージがある場合は強制停止
		GF_STR_PrintForceStop(wk->MsgIndex);
	}

	EndMessagePrint( wk, msg_oekaki_03, 1 );	
	SetNextSequence( wk, OEKAKI_MODE_LOGOUT_CHILD_WAIT );
	Snd_SePlay(SEQ_SE_DP_BUTTON9);

	// 接続可能人数を一旦現在の接続人数に落とす
	if(CommGetCurrentID()==0){
		ChangeConnectMax( wk, 0 );
	}
	wk->err_num = CommGetConnectNum();

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   子機か抜けた文章終了待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_LogoutChildMesWait( OEKAKI_WORK *wk, int seq )
{
	// 接続人数が１減るかチェック
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_LOGOUT_CHILD_CLOSE );
		wk->wait = 0;
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   表示終了ウェイト
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Oekaki_LogoutChildClose( OEKAKI_WORK *wk, int seq )
{			
	// 接続人数が１減るまでは待つ
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	if( ++wk->wait > OEKAKI_MESSAGE_END_WAIT && wk->err_num == 0 ){
		EndMessageWindowOff( wk );
		SetNextSequence( wk, OEKAKI_MODE );
		if(CommGetCurrentID() == 0){
			wk->banFlag = OEKAKI_BAN_OFF;
			ChangeConnectMax(wk, 1);
		}
	}

	EndSequenceCommonFunc( wk );			//終了選択時の共通処理
	return seq;
	
}




//==============================================================================
/**
 * $brief   どんな状態であっても強制的にメインシーケンスチェンジ
 *
 * @param   wk		
 * @param   seq		
 * @param   id		
 *
 * @retval  none		
 */
//==============================================================================
void OekakiBoard_MainSeqForceChange( OEKAKI_WORK *wk, int seq, u8 id  )
{
	switch(seq){
	case OEKAKI_MODE_NEWMEMBER:	
		if(wk->seq==OEKAKI_MODE_END_SELECT_WAIT || wk->seq==OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			OekakiResetYesNoWin(wk);
//			CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);
		}
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		// 指定の子機の名前をWORDSETに登録（離脱・乱入時)
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		wk->newMemberId = id;
		wk->ridatu_bit = 0;
		OS_Printf("新しい人のID %d\n",id);
		break;
	case OEKAKI_MODE_NEWMEMBER_END:
		EndMessageWindowOff( wk );
		break;
	case OEKAKI_MODE_LOGOUT_CHILD:
		if(wk->status_end == TRUE){
			return;	//自分自身が離脱処理中
		}
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		if(id==CommGetCurrentID()){
			// 自分が離脱する子機だった場合は「子機がいなくなたよ」とは言わない
			return;
		}

		if(CommGetCurrentID() == 0){
			wk->ridatu_bit &= 0xffff ^ id;
		}
		if(wk->seq==OEKAKI_MODE_END_SELECT_WAIT || wk->seq==OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			OekakiResetYesNoWin(wk);
//			CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);

			//おえかき再描画
			GF_BGL_BmpWinOn( &wk->OekakiBoard );
		}
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		break;
	case OEKAKI_MODE_FORCE_END:
		break;
	case OEKAKI_MODE_END_SELECT_ANSWER_OK:
		break;
	case OEKAKI_MODE_END_SELECT_ANSWER_NG:
		break;
	default:
		GF_ASSERT( "指定以外のシーケンスチェンジが来た" );
		return;
	}
	SetNextSequence( wk, seq );

}

//==============================================================================
/**
 * $brief   何か処理をしてからメインループ内シーケンスチェンジ(通常状態であること）
 *
 * @param   wk		
 * @param   seq		このメインシーケンスにチェンジしたい
 *
 * @retval  none		
 */
//==============================================================================
void OekakiBoard_MainSeqCheckChange( OEKAKI_WORK *wk, int seq, u8 id  )
{
	// 通常状態なら
	if(wk->seq == OEKAKI_MODE){
		OS_Printf("子機%dの名前を登録\n",id);
		switch(seq){
		case OEKAKI_MODE_LOGOUT_CHILD:
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			if(id==CommGetCurrentID()){
				// 自分が離脱する子機だった場合は「子機がいなくなたよ」とは言わない
				return;
			}
			if(CommGetCurrentID() == 0){
				wk->ridatu_bit &= 0xffff ^ id;
			}
			SetNextSequence( wk, seq );
			break;
		
		default:
			GF_ASSERT( 0&&"指定以外のシーケンスチェンジが来た" );
			return;
		}


	}


}



//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//11520
//---------------------------------------------------------
// ブラシパターン
//---------------------------------------------------------

// どうしてもパレットデータを3bitに縮めてしまいたいので、透明色を8にして
// 色指定自体は0-7に当てている。0は透明色だがBD面を黒にして黒く見えるようにしている

// BMPデータは最低横8dot分必要なので、4x4のドットデータを作りたい時は
// ２バイトごとに参照されないデータがもう２バイト必要
static const u8 oekaki_brush[3][8][24]={

{	/*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x11,  0x00,0x00,  0x00,0x11, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x22,  0x00,0x00,  0x00,0x22, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x33,  0x00,0x00,  0x00,0x33, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x44,  0x00,0x00,  0x00,0x44, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x55,  0x00,0x00,  0x00,0x55, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x66,  0x00,0x00,  0x00,0x66, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x77,  0x00,0x00,  0x00,0x77, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x88,  0x00,0x00,  0x00,0x88, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
},
{	/*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x00,0x00, 0x00,0x00, 0x00,0x11, 0x00,0x00,  0x10,0x11,  0x01,0x00,  0x10,0x11, 0x01,0x00,  0x00,0x11, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x22, 0x00,0x00,  0x20,0x22,  0x02,0x00,  0x20,0x22, 0x02,0x00,  0x00,0x22, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x33, 0x00,0x00,  0x30,0x33,  0x03,0x00,  0x30,0x33, 0x03,0x00,  0x00,0x33, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x44, 0x00,0x00,  0x40,0x44,  0x04,0x00,  0x40,0x44, 0x04,0x00,  0x00,0x44, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x55, 0x00,0x00,  0x50,0x55,  0x05,0x00,  0x50,0x55, 0x05,0x00,  0x00,0x55, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x66, 0x00,0x00,  0x60,0x66,  0x06,0x00,  0x60,0x66, 0x06,0x00,  0x00,0x66, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x77, 0x00,0x00,  0x70,0x77,  0x07,0x00,  0x70,0x77, 0x07,0x00,  0x00,0x77, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x88, 0x00,0x00,  0x80,0x88,  0x08,0x00,  0x80,0x88, 0x08,0x00,  0x00,0x88, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
},                                                                     
{   /*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x10,0x11, 0x01,0x00, 0x11,0x11, 0x11,0x00,  0x11,0x11,  0x11,0x00,  0x11,0x11, 0x11,0x00,  0x11,0x11, 0x11,0x00, 0x10,0x11, 0x01,0x00,},
	{0x20,0x22, 0x02,0x00, 0x22,0x22, 0x22,0x00,  0x22,0x22,  0x22,0x00,  0x22,0x22, 0x22,0x00,  0x22,0x22, 0x22,0x00, 0x20,0x22, 0x02,0x00,},
	{0x30,0x33, 0x03,0x00, 0x33,0x33, 0x33,0x00,  0x33,0x33,  0x33,0x00,  0x33,0x33, 0x33,0x00,  0x33,0x33, 0x33,0x00, 0x30,0x33, 0x03,0x00,},
	{0x40,0x44, 0x04,0x00, 0x44,0x44, 0x44,0x00,  0x44,0x44,  0x44,0x00,  0x44,0x44, 0x44,0x00,  0x44,0x44, 0x44,0x00, 0x40,0x44, 0x04,0x00,},
	{0x50,0x55, 0x05,0x00, 0x55,0x55, 0x55,0x00,  0x55,0x55,  0x55,0x00,  0x55,0x55, 0x55,0x00,  0x55,0x55, 0x55,0x00, 0x50,0x55, 0x05,0x00,},
	{0x60,0x66, 0x06,0x00, 0x66,0x66, 0x66,0x00,  0x66,0x66,  0x66,0x00,  0x66,0x66, 0x66,0x00,  0x66,0x66, 0x66,0x00, 0x60,0x66, 0x06,0x00,},
	{0x70,0x77, 0x07,0x00, 0x77,0x77, 0x77,0x00,  0x77,0x77,  0x77,0x00,  0x77,0x77, 0x77,0x00,  0x77,0x77, 0x77,0x00, 0x70,0x77, 0x07,0x00,},
	{0x80,0x88, 0x08,0x00, 0x88,0x88, 0x88,0x00,  0x88,0x88,  0x88,0x00,  0x88,0x88, 0x88,0x00,  0x88,0x88, 0x88,0x00, 0x80,0x88, 0x08,0x00,},
},
};

/*


















*/



//==============================================================================
/**
 * @brief   描画開始位置がマイナス方向にあっても描画できるBmpWinPrintラッパー
 * @retval  none		
 */
//==============================================================================
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy )
{
	// X描画開始ポイントがマイナスか
	if(win_x < 0){
		int diff;
		diff = win_x*-1;
		if(diff>win_dx){	// そのマイナス分は転送幅を超えてないか
			diff = win_dx;	// 超えてたら転送幅と同じにする
		}

		// 転送参照開始ポイントと、転送幅を引く
		win_x   = 0;
		src_x  += diff;
		src_dx -= diff;
		win_dx -= diff;
	}

	// Y描画開始ポイントがマイナスか
	if(win_y < 0){
		int diff;
		diff = win_y*-1;
		if(diff>win_dy){	// そのマイナス分は転送幅を超えてないか
			diff = win_dy;	// 超えてたら転送幅と同じにする
		}

		// 転送参照開始ポイントと、転送幅を引く
		win_y   = 0;
		src_y  += diff;
		src_dy -= diff;
		win_dy -= diff;
	}

	GF_BGL_BmpWinPrint( win, src,	src_x, src_y, src_dx, src_dy, win_x, win_y, win_dx, win_dy );
}


#define POINT_W	( 6 )
#define POINT_H	( 6 )
//------------------------------------------------------------------
/**
 * $brief   ライン描画
 *
 * @param   win		
 * @param   brush		
 * @param   px		
 * @param   py		
 * @param   sx		
 * @param   sy		
 * @param   count		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawPoint_to_Line( 
	GF_BGL_BMPWIN *win, 
	const u8 *brush, 
	int px, int py, int *sx, int *sy, 
	int count, int flag )
{
	int dx, dy, s, step;
	int x1 = *sx;
	int y1 = *sy;
	int x2 = px;
	int y2 = py;

	// 初回は原点保存のみ
	if(count==0 && flag == 0){
		*sx = px;		*sy = py;
		return;
	}
	

	dx = MATH_IAbs(x2 - x1);  dy = MATH_IAbs(y2 - y1);
	if (dx > dy) {
		if (x1 > x2) {
			step = (y1 > y2) ? 1 : -1;
			s = x1;  x1 = x2;  x2 = s;  y1 = y2;
		} else step = (y1 < y2) ? 1: -1;
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		s = dx >> 1;
		while (++x1 <= x2) {
			if ((s -= dy) < 0) {
				s += dx;  y1 += step;
			};
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		}
	} else {
		if (y1 > y2) {
			step = (x1 > x2) ? 1 : -1;
			s = y1;  y1 = y2;  y2 = s;  x1 = x2;
		} else step = (x1 < x2) ? 1 : -1;
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		s = dy >> 1;
		while (++y1 <= y2) {
			if ((s -= dx) < 0) {
				s += dy;  x1 += step;
			}
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		}
	}
	
	
	*sx = px;			*sy = py;

}

static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock )
{
	int i;
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		stock[i].size = all[i].size;
		if(all[i].size!=0){
			stock[i].x = all[i].x[all[i].size-1];
			stock[i].y = all[i].y[all[i].size-1];
		}
	}
}


static int debug_count;
//------------------------------------------------------------------
/**
 * $brief  通信で受信したタッチパネルの結果データを下に描画する
 *
 * @param   win		
 * @param   all		
 * @param   draw	メモリ上で行ったCGX変更を転送するか？(0:しない	1:する）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw )
{
	int px,py,i,r,flag=0, sx, sy;

//	OS_Printf("id0=%d,id1=%d,id2=%d,id3=%d,id4=%d\n",all[0].size,all[1].size,all[2].size,all[3].size,all[4].size);

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(all[i].size!=0){
			if(old[i].size){
				sx = old[i].x-9;
				sy = old[i].y-17;
			}
			for(r=0;r<all[i].size;r++){
				px = all[i].x[r] - 9;
				py = all[i].y[r] - 17;
				// BG1面用BMP（お絵かき画像）ウインドウ確保
//				GF_BGL_BmpWinPrint( win, (void*)oekaki_brush[all[i].brush],	0, 0, 4, 4, px, py, 4, 4 );
				DrawPoint_to_Line(win, oekaki_brush[all[i].brush][all[i].color], px, py, &sx, &sy, r, old[i].size);
				flag = 1;
			}
			
		}
	}
	if(flag && draw){
		
//		OS_Printf("write board %d times\n",debug_count++);
		GF_BGL_BmpWinOn( win );
	}
	
	// 今回の最終座標のバックアップを取る   
    Stock_OldTouch(all, old);
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		all[i].size = 0;		// 一度描画したら座標情報は捨てる
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   通信データからカーソル位置を移動させる
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MoveCommCursor( OEKAKI_WORK *wk )
{
	int i;
	TOUCH_INFO *all = wk->AllTouchResult;
	
	// 座標データが入っている時はカーソル座標を反映させる
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(i!=CommGetCurrentID()){		// 自分のカーソルはタッチパネルから直接とる
			if(all[i].size!=0 && CommInfoGetMyStatus(i)!=NULL){
				CLACT_SetDrawFlag( wk->MainActWork[i], 1 );
				SetCursor_Pos( wk->MainActWork[i], all[i].x[all[i].size-1],  all[i].y[all[i].size-1]);
			}else{
				CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
			}
		}
	}
	
}
//------------------------------------------------------------------
/**
 * $brief   デバッグ用に自分で取得した情報を受信バッファにコピーする
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void DebugTouchDataTrans( OEKAKI_WORK *wk )
{
	wk->AllTouchResult[0] = wk->MyTouchResult;
}


//------------------------------------------------------------------
/**
 * カーソルのパレット変更（点滅）
 *
 * @param   CursorCol	sinに渡すパラメータ（360まで）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorColTrans(u16 *CursorCol)
{
	fx32  sin;
	GXRgb tmp;
	int   r,g,b;

	*CursorCol+=20;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, ( 12 )*2, 2);
}

//------------------------------------------------------------------
/**
 * $brief   現在何人接続しているか？
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int OnlyParentCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return result;
}


//------------------------------------------------------------------
/**
 * $brief   オンライン状況を確認して上画面に名前を表示する
 *
 * @param   win		
 * @param   frame		
 * @param   color		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, OEKAKI_WORK *wk )
{
	int i,id = CommGetCurrentID();
	int num;

	// 名前取得の状況に変化が無い場合は書き換えない
	if(!MyStatusCheck(wk)){
		return;
	}

	// ログイン状況に応じて上画面の矢印をON・OFFする
	for(i=0;i<5;i++){
		if(wk->TrainerStatus[i][0]==NULL){
			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
		}else{
			CLACT_SetDrawFlag( wk->SubActWork[i], 1 );
		}
	}

	// それぞれの文字パネルの背景色でクリア
	for(i=0;i<5;i++){
		GF_BGL_BmpWinFill( &win[i], 0, 0, 0, OEKAKI_NAME_BMP_W*8, OEKAKI_NAME_BMP_H*8 );
	}

	// 描画
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][0]!=NULL){
			MyStatus_CopyNameString( wk->TrainerStatus[i][0], wk->TrainerName[i] );
			if(id==i){
				GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(FBMP_COL_RED,FBMP_COL_RED_SDW,15),NULL);
			}else{
				GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, color,NULL);
			}
		}
		GF_BGL_BmpWinOn( &win[i] );
	}
	OS_Printf("名前かきかえしますよ\n");

}









#define PLATE_CHARA_OFFSET1	( 12 )
#define PLATE_CHARA_OFFSET2	( 16 )

static const u8 plate_num[4]={2,2,3,2};
static const u8 plate_table[4][3]={
	{8*8,17*8,0,},
	{8*8,17*8,0,},
	{5*8,12*8,18*8,},
	{8*8,17*8,0,},

};
static const u8 plate_chara_no[][5]={
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
};

//------------------------------------------------------------------
/**
 * $brief   接続が確認された場合は名前を取得する
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int ConnectCheck( OEKAKI_WORK *wk )
{
	int i,result=0;
	MYSTATUS *status;
	STRCODE  *namecode;

	// 接続チェック
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->ConnectCheck[i][0] = wk->ConnectCheck[i][1];

		wk->ConnectCheck[i][0] = CommIsConnect(i);

	}

	// 接続がいたら名前を反映させる
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->ConnectCheck[i][0]){				// 接続しているか？

			status = CommInfoGetMyStatus(i);
			if(status!=NULL){					// MYSTATUSは取得できているか？
				namecode = (STRCODE*)MyStatus_GetMyName(status);
				STRBUF_SetStringCode( wk->TrainerName[i], namecode );
			}

		}
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   タッチパネル情報の送受信を行う
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LineDataSendRecv( OEKAKI_WORK *wk )
{
	if( CommGetCurrentID()==0 ){
		// 親機は自分のタッチパネル情報を追加して送信する
        if(CommIsEmptyQueue_ServerSize()){
			wk->MyTouchResult.banFlag    = wk->banFlag;
			wk->ParentTouchResult[0] = wk->MyTouchResult;
			CommSendData_ServerSide( CO_OEKAKI_LINEPOSSERVER, wk->ParentTouchResult, COMM_SEND_5TH_PACKET_MAX*OEKAKI_MEMBER_MAX );
		}
	}else{
        if(CommIsEmptyQueue()){
			// 子機は自分のタッチパネル情報を親機に送信する
			CommSendData( CO_OEKAKI_LINEPOS, &wk->MyTouchResult, COMM_SEND_5TH_PACKET_MAX );
		}
	}
}


//------------------------------------------------------------------
/**
 * $brief   現在のオンライン数を取得
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyStatusGetNum( void )
{
	int i,result;
	for(result=0,i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(CommInfoGetMyStatus(i)!=NULL){
			result++;
		}
	}
	return result;
}

//--------------------------------------------------------------
/**
 * @brief   現在のオンライン数を取得(グローバル関数版)
 *
 * @param   none		
 *
 * @retval  接続人数
 */
//--------------------------------------------------------------
int OekakiBoard_MyStatusGetNum(void)
{
	return MyStatusGetNum();
}

//------------------------------------------------------------------
/**
 * $brief   MYSTATUSの取得状況に変化があったか？
 *
 * @param   wk		
 *
 * @retval  int		あったら1,  無い場合は0
 */
//------------------------------------------------------------------
static int MyStatusCheck( OEKAKI_WORK *wk )
{
	int i,result=0;
	// 接続がいたら名前を反映させる
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerStatus[i][1] = wk->TrainerStatus[i][0];
		wk->TrainerStatus[i][0] = CommInfoGetMyStatus(i);
	}

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][1] != wk->TrainerStatus[i][0]){
			result = 1;
		}
	}

	return result;
}


//------------------------------------------------------------------
/**
 * $brief   会話ウインドウ表示
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessagePrint( OEKAKI_WORK *wk, int msgno, int wait )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	tempbuf = STRBUF_Create(TALK_MESSAGE_BUF_NUM,HEAPID_OEKAKI);
	MSGMAN_GetString(  wk->MsgManager, msgno, tempbuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	STRBUF_Delete(tempbuf);

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, 1, FLD_MESFRAME_PAL );


	// メッセージスピードを指定
	if(wait==0){
		wait = MSG_ALLPUT;
	}

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);
	if(wait == MSG_ALLPUT){
		wk->MsgIndex = 0xff;
	}

}

//------------------------------------------------------------------
/**
 * $brief   会話表示ウインドウ終了待ち
 *
 * @param   msg_index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int EndMessageWait( int msg_index )
{
	if(msg_index == 0xff){
		return 1;
	}
	
	if(GF_MSG_PrintEndCheck( msg_index )==0){
		
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessageWindowOff( OEKAKI_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}


//------------------------------------------------------------------
/**
 * @brief   接続人数がその時接続人数＋１になるように再設定する
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChangeConnectMax( OEKAKI_WORK *wk, int plus )
{
	if(CommGetCurrentID()==0){
		int num = CommGetConnectNum()+plus;
		if(num>5){
			num = 5;
		}
		CommStateSetLimitNum(num);
		OS_Printf("接続人数を %d人に変更\n",num);
	}

}

//------------------------------------------------------------------
/**
 * @brief  接続人数を監視して制御を変える 
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ConnectNumControl( OEKAKI_WORK *wk )
{
	int num;
	// ビーコンを書き換える
	num = MyStatusGetNum();

	switch(num){
	case 1:
		if(wk->seq<=OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			if (WH_GetBitmap() != 1){
				OS_Printf("一人ではなくなりました。\n");
				OS_Printf("bit:%d\n",WH_GetBitmap());
				wk->ireagalJoin = 1;
			}
			OS_Printf("OEKAKI_MODE_END_PARENT_ONLYにかきかえ\n");
//			wk->seq = OEKAKI_MODE_END_PARENT_ONLY;
			wk->next_seq = OEKAKI_MODE_END_PARENT_ONLY;	//予約
			OS_Printf("接続制限を１にする");
   	    	CommStateSetLimitNum(1);
			// やめる選択中だったら強制リセット
			if(wk->yesno_flag){
				OekakiResetYesNoWin(wk);
				CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);
			}
			return SEQ_LEAVE;
		}
		break;
	case 2:case 3:case 4:
		// まだ入れるよ
		Union_BeaconChange( UNION_PARENT_MODE_OEKAKI_FREE );

		// 接続人数が減った場合は接続最大人数も減らす
		if(num<wk->connectBackup){
			if(wk->banFlag==OEKAKI_BAN_ON){
				ChangeConnectMax( wk, 0 );
			}else{
				ChangeConnectMax( wk, 1 );
			}
		}
		break;
	case 5:
		// いっぱいです
		Union_BeaconChange( UNION_PARENT_MODE_OEKAKINOW );
		break;
	}

	// 画像共有人数が減ったときは更新
	if(num<wk->connectBackup){
		wk->shareNum = CommGetConnectNum();
		wk->shareBit = WH_GetBitmap();
		OS_TPrintf("接続人数が減ったのでshareNumを%d人に変更\n", CommGetConnectNum());
		/*乱入中フラグ成立している状態で、人数が減った*/
		if(wk->bookJoin){/*乱入予定ビットと比較し、それが落ちていた場合は、乱入者が電源を切ったとみなす*/
			if (!(wk->shareBit&wk->joinBit)){
				//リミット制限再設定
				ChangeConnectMax( wk, 1 );
				//離脱解除
				wk->banFlag = OEKAKI_BAN_OFF;
				//乱入予約キャンセル
				wk->bookJoin = 0;
				wk->joinBit = 0;
				OS_Printf("乱入キャンセルされました\n");
			}
		}
	}

	// 接続人数を保存
	wk->connectBackup = MyStatusGetNum();

	// 通信接続人数が画像共有人数よりも多くなった場合は離脱禁止フラグを立てる
	if(wk->shareNum < CommGetConnectNum()){
		OS_Printf("ban_flag_on:%d,%d\n",wk->shareNum, CommGetConnectNum());
		OS_Printf("乱入予定\n");
		wk->banFlag = OEKAKI_BAN_ON;
		//乱入を期待する
		wk->bookJoin = 1;
		//乱入しようとしている人のビットを取得
		wk->joinBit = wk->shareBit^WH_GetBitmap();
		GF_ASSERT( (wk->joinBit == 2)||
					(wk->joinBit == 4)||
					(wk->joinBit == 8)||
					(wk->joinBit == 16) );
		
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   次に移行させたいシーケンス番号を入れる
 *
 * @param   wk		
 * @param   nextSequence		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetNextSequence( OEKAKI_WORK *wk, int nextSequence )
{
	wk->next_seq = nextSequence;
}


//------------------------------------------------------------------
/**
 * @brief   wk->seqのコントロールを行う
 *
 * @param   wk		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void OekakiSequenceControl( OEKAKI_WORK *wk, int proc_seq )
{
	// シーケンスが違うなら
	if(wk->seq!=wk->next_seq){
		// 終了シーケンスじゃないことを確認して
		if(proc_seq!=SEQ_LEAVE){ 
			wk->seq = wk->next_seq;
		}else{
			// 一部実行制限のシーケンスじゃないことを確認して
			if(FuncTable[wk->next_seq].execOn_SeqLeave){
				OS_Printf("now_next:%d,%d\n",wk->seq,wk->next_seq);
				// シーケンス書き換え
				wk->seq = wk->next_seq;
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief   タッチパネルのはい・いいえウィンドウの作成関数
 *
 * @param   wk		
 *
 * @retval  BOOL		TRUE：成功	FALSE：失敗 			
 */
//------------------------------------------------------------------
static BOOL OekakiInitYesNoWin(OEKAKI_WORK *wk, TOUCH_SW_PARAM *param)
{
	if(!wk->yesno_flag){
		TOUCH_SW_Init( wk->TouchSubWindowSys, param );
		wk->yesno_flag = 1;
		return TRUE;
	}else{
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief   タッチパネルのはい・いいえウィンドウの消去関数
 *
 * @param   wk		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void OekakiResetYesNoWin(OEKAKI_WORK *wk)
{
	if(wk->yesno_flag){
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		wk->yesno_flag = 0;
	}
}


//------------------------------------------------------------------
/**
 * @brief   YESNOボタンを禁止している間、嘘の検出を行う
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int FakeEndYesNoSelect( OEKAKI_WORK  *wk )
{

	int button=GF_TP_RectHitTrg( fake_yesno_hittbl );
	if( button != RECT_HIT_NONE ){
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * @brief   タッチパネルデータの格納処理
 *
 * @param   touchResult		
 * @param   tpData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetTouchpanelData( TOUCH_INFO *touchResult, TP_ONE_DATA *tpData, int brush_color, int brush )
{
	int i,n;

	// 最初にサンプリングされた点を格納
	if(tpData->Size!=0){
		touchResult->x[0] = tpData->TPDataTbl[0].x;
		touchResult->y[0] = tpData->TPDataTbl[0].y;

		// 最後にサンプリングされた点を格納
		n = tpData->Size-1;
		touchResult->x[1] = tpData->TPDataTbl[n].x;
		touchResult->y[1] = tpData->TPDataTbl[n].y;
	}

	// 最大４回サンプリングされるはずだが、それでも送信データは２と格納する
	if(tpData->Size>=2){
		touchResult->size  = 2;
	}else{
		touchResult->size  = tpData->Size;
	}
	
	// 色・大きさ設定
	touchResult->color = brush_color;
	touchResult->brush = brush;

}