//============================================================================================
/**
 * @file	record_corner.c
 * @bfief	レコードコーナー画面処理
 * @author	Akito Mori
 * @date	06.03.26
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
#include "msgdata/msg_record.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "system/bmp_menu.h"
#include "application/record_corner.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/comm_save.h"
#include "communication/wm_icon.h"
#include "field/fld_bmp.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "field/union_beacon_tool.h"
#include "field/fieldobj_code.h"

#include "record_corner_local.h"

#include "comm_command_record.h"


#include "msgdata/msg_ev_win.h"

// SE用定義
#define RECORD_MOVE_SE		(SEQ_SE_DP_SELECT)
#define RECORD_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define RECORD_BS_SE		(SEQ_SE_DP_SELECT)

#define FIELDOBJ_PAL_START	( 7 )

#define RECORD_1SEC_WAIT	( 45 )

#include "record.naix"			// グラフィックアーカイブ定義
#include "../wifi_worldtrade/worldtrade.naix"
#include "../../field/poketch/poketch_arc.h"

#include "communication/wh.h"

//============================================================================================
//	定数定義
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_LEAVE,
	SEQ_OUT,
};

enum{
	LIMIT_MODE_NONE,	///<制限なし
	LIMIT_MODE_TRUE,	///<制限発生中
	LIMIT_MODE_ONLY,	///<制限発生中(一人のみ)
};



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

/*** 関数プロトタイプ ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( RECORD_WORK *wk );
static void FreeWork( RECORD_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( RECORD_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(RECORD_WORK *wk);
static void SetCellActor(RECORD_WORK *wk);
static void BmpWinInit(RECORD_WORK *wk, PROC* proc);
static void BmpWinDelete( RECORD_WORK *wk );
static void CursorAppearUpDate(RECORD_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void EndSequenceCommonFunc( RECORD_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static BOOL NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, RECORD_WORK *wk );
static int  ConnectCheck( RECORD_WORK *wk );
static BOOL  MyStatusCheck( RECORD_WORK *wk );
static void RecordMessagePrint( RECORD_WORK *wk, int msgno, int all_put );
static int  EndMessageWait( int msg_index );
static void EndMessageWindowOff( RECORD_WORK *wk );
static int  OnlyParentCheck( void );
static int  MyStatusGetNum( void );
static void RecordDataSendRecv( RECORD_WORK *wk );
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait);
static void SequenceChange_MesWait( RECORD_WORK *wk, int next );
static void TrainerObjFunc( RECORD_WORK *wk );
static void LoadFieldObjData( RECORD_WORK *wk );
static void FreeFieldObjData( RECORD_WORK *wk );
static void TransFieldObjData( NNSG2dCharacterData *CharaData[2], NNSG2dPaletteData *PalData[2], int id, int view, int sex );
static void TransPal( TCB_PTR tcb, void *work );
static int GetTalkSpeed( RECORD_WORK *wk );
static void ChangeConnectMax( RECORD_WORK *wk, int plus );
static int  RecordCorner_BeaconControl( RECORD_WORK *wk, int plus );
static void PadControl( RECORD_WORK *wk );


// FuncTableからシーケンス遷移で呼ばれる関数
static int Record_MainInit( RECORD_WORK *wk, int seq );
static int Record_MainNormal( RECORD_WORK *wk, int seq );
static int Record_StartRecordCommand( RECORD_WORK *wk, int seq );
static int Record_RecordSendData( RECORD_WORK *wk, int seq );
static int Record_RecordMixData( RECORD_WORK *wk, int seq );
static int Record_StartSelectWait( RECORD_WORK *wk, int seq );
static int Record_StartSelect( RECORD_WORK *wk, int seq );
static int Record_EndSelectPutString( RECORD_WORK *wk, int seq );
static int Record_EndSelectWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerOK( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerNG( RECORD_WORK *wk, int seq );
static int Record_EndChild( RECORD_WORK *wk, int seq );
static int Record_EndChildWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectParent( RECORD_WORK *wk, int seq );
static int Record_EndSelectParentWait( RECORD_WORK *wk, int seq );
static int Record_ForceEnd( RECORD_WORK *wk, int seq );
static int Record_ForceEndWait( RECORD_WORK *wk, int seq );
static int Record_ForceEndSynchronize( RECORD_WORK *wk, int seq );
static int Record_EndParentOnly( RECORD_WORK *wk, int seq );
static int Record_EndParentOnlyWait( RECORD_WORK *wk, int seq );
static int Record_MessageWaitSeq( RECORD_WORK *wk, int seq );
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq );
static int Record_LogoutChildClose( RECORD_WORK *wk, int seq );
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq );
static int Record_NewMember( RECORD_WORK *wk, int seq );
static int Record_NewMemberEnd( RECORD_WORK *wk, int seq );
static int Record_CommSaveStart( RECORD_WORK *wk, int seq );
static int Record_CommSave( RECORD_WORK *wk, int seq ) ;
static int Record_EndMessageWait( RECORD_WORK *wk, int seq );
static int Record_FroceEndMesWait( RECORD_WORK *wk, int seq );



// レコードコーナーメインシーケンス用関数配列定義
static int (*FuncTable[])(RECORD_WORK *wk, int seq)={
	Record_MainInit,				// 	RECORD_MODE_INIT  = 0, 
	Record_NewMember, 		        // 	RECORD_MODE_NEWMEMBER,
	Record_NewMemberEnd,            // 	RECORD_MODE_NEWMEMBER_END,
	Record_MainNormal,              // 	RECORD_MODE,
	Record_EndSelectPutString,      // 	RECORD_MODE_END_SELECT,
	Record_EndSelectWait,			// 	RECORD_MODE_END_SELECT_WAIT,
	Record_EndSelectAnswerWait,		//	RECORD_MODE_END_SELECT_ANSWER_WAIT
	Record_EndSelectAnswerOK,		//	RECORD_MODE_END_SELECT_ANSWER_OK
	Record_EndSelectAnswerNG,		//	RECORD_MODE_END_SELECT_ANSWER_NG
	Record_EndChild,				//  RECORD_MODE_END_CHILD,
	Record_EndChildWait,			//  RECORD_MODE_END_CHILD_WAIT,
	Record_EndSelectParent,			// 	RECORD_MODE_END_SELECT_PARENT,
	Record_EndSelectParentWait,		//  RECORD_MODE_END_SELECT_PARENT_WAIT,
	Record_ForceEnd,				//	RECORD_MODE_FORCE_END,
	Record_FroceEndMesWait,			//  RECORD_MODE_FORCE_END_MES_WAIT,
	Record_ForceEndWait,			//  RECORD_MODE_FORCE_END_WAIT,
	Record_ForceEndSynchronize,		//  RECORD_MODE_FORCE_END_SYNCHRONIZE,
	Record_EndParentOnly,			// 	RECORD_MODE_END_PARENT_ONLY,
	Record_EndParentOnlyWait,		// 	RECORD_MODE_END_PARENT_ONLY_WAIT,
	Record_LogoutChildMes,			// 	RECORD_MODE_LOGOUT_CHILD,
	Record_LogoutChildMesWait,		//  RECORD_MODE_LOGOUT_CHILD_WAIT,
	Record_LogoutChildClose,		//  RECORD_MODE_LOGOUT_CHILD_CLOSE,
	Record_StartSelect,				// 	RECORD_MODE_START_SELECT,
	Record_StartSelectWait,         // 	RECORD_MODE_START_SELECT_WAIT
	Record_StartRecordCommand,		//  RECORD_MODE_START_RECORD_COMMAND
	Record_RecordSendData,			//	RECORD_MODE_RECORD_SEND_DATA ここがレコードデータ受信チェック

	// ここらへんに混ぜる処理を書いたり
	// セーブするシーケンスを書いたりしよう

	Record_RecordMixData,			//	RECORD_MODE_RECORD_MIX_DATA	まぜるシーケンス
	
	Record_CommSaveStart,			//  RECORD_MODE_COMM_SAVE_START
	Record_CommSave,				//  RECORD_MODE_COMM_SAVE
	Record_EndMessageWait,			//  RECORD_MODE_END_MES_WAIT
	

	Record_MessageWaitSeq,			//  RECORD_MODE_MESSAGE_WAIT,
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
PROC_RESULT RecordCornerProc_Init( PROC * proc, int * seq )
{
	RECORD_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		// レコードコーナー用ヒープ作成
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_RECORD, 0x41000 );

		wk = PROC_AllocWork( proc, sizeof(RECORD_WORK), HEAPID_RECORD );
		memset( wk, 0, sizeof(RECORD_WORK) );
		wk->bgl   = GF_BGL_BglIniAlloc( HEAPID_RECORD );
		wk->param = (RECORD_INPUT_PARAM*)PROC_GetParentWork( proc );
		wk->savedata = wk->param->sv;
		
		// 文字列マネージャー生成
		wk->WordSet    = WORDSET_Create( HEAPID_RECORD );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_record_dat, HEAPID_RECORD );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM バンク設定
		VramBankSet();
		
		// BGLレジスタ設定
		BgInit( wk->bgl );					

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

		// ワイプフェード開始
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD );
		

		//BGグラフィックセット
		BgGraphicSet( wk );

//		InitTPSystem();						// タッチパネルシステム初期化
//		InitTPNoBuff(2);
  
		// VBlank関数セット
		sys_VBlankFuncChange( VBlankFunc, wk );	
  

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
//		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

		// 通信コマンドを交換リスト用に変更
		CommCommandRecordInitialize( wk );

		// レコードコーナーモードに変更
		CommStateUnionRecordCornerChange();

        // 3台まで接続可能に書き換え
        CommStateSetLimitNum(3);

		// 親だったら「レコード通信募集中」にビーコン書き換え
		if(CommGetCurrentID()==0){
			Union_BeaconChange( UNION_PARENT_MODE_RECORD_FREE );
		}


		WirelessIconEasy();

		MakeSendData(wk->savedata, &wk->send_data);

		wk->trans_tcb = VIntrTCB_Add( TransPal, wk, 5 );


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

static int debug_pal_no = 0;
static int debug_obj_no = 0;


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

PROC_RESULT RecordCornerProc_Main( PROC * proc, int * seq )
{
	RECORD_WORK * wk  = PROC_GetWork( proc );

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		wk->ridatu_bit &= WH_GetBitmap();
	}
	
	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ワイプ処理待ち
			*seq = SEQ_MAIN;

			// 自分が子機で接続台数が２台以上だった場合はもう絵が描かれている
			if(CommGetCurrentID()!=0){
				if(MyStatusGetNum()>2){
					// 子機乱入リクエスト
					CommSendData(CR_RECORD_CHILD_JOIN, NULL, 0);
				}
			}

		}
		break;

	case SEQ_MAIN:
		// カーソル移動

		// シーケンス毎の動作
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}
		if(wk->record_execute == FALSE){	//レコード混ぜ中の時は更新しない
			NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(1, 3, 0), wk );
		}
		TrainerObjFunc(wk);

		// 変化した人数に応じてビーコンを変える
		if(CommGetCurrentID()==0){
			int temp = RecordCorner_BeaconControl( wk, 1 );
			if(*seq==SEQ_MAIN){
				// 終了シーケンスなどに流れていなければ変更する
				*seq = temp;
			}
		}

		break;
	case SEQ_LEAVE:
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}
		break;
	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
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
PROC_RESULT RecordCornerProc_End( PROC * proc, int * seq )
{
	RECORD_WORK  *wk    = PROC_GetWork( proc );
	int i;

	// パレット転送タスク終了
	TCB_Delete( wk->trans_tcb );

	// セルアクターリソース解放

	// キャラ転送マネージャー破棄
//	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES]);
		
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

	// 通信終了
//	CommStateExitUnion();
    CommStateSetLimitNum(2);
	CommStateUnionBconCollectionRestart();
	UnionRoomView_ObjInit( wk->param->union_view );

	// タッチパネルシステム終了
//	StopTP();							


	// メッセージマネージャー・ワードセットマネージャー解放
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ワーク解放
	FreeWork( wk );


	PROC_FreeWork( proc );				// PROCワーク開放

	// 入れ替わっていた上下画面出力を元に戻す
	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	// ビーコン書き換え
	Union_BeaconChange( UNION_PARENT_MODE_FREE );

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_RECORD );

	return PROC_RES_FINISH;
}

static const u8 palanimetable[][2]={
	{ 8,2,},
	{ 8,3,},
	{ 8,4,},
	{24,0,},
	{ 0,0xff,},
};



//------------------------------------------------------------------
/**
 * @brief   パレット転送タスク
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPal( TCB_PTR tcb, void *work )
{
	RECORD_WORK     *wk  = (RECORD_WORK *)work;
	VTRANS_PAL_WORK *pal = &wk->palwork;
	
	// パレットアニメ
	if(pal->sw){
		if(pal->wait>palanimetable[pal->seq][0]){
			u16 *src;
			pal->wait=0;
			pal->seq++;
			if(palanimetable[pal->seq][1]==0xff){
				pal->seq = 0;
			}
			src = (u16*)pal->palbuf->pRawData;
			GX_LoadOBJPltt(&src[16*palanimetable[pal->seq][1]], 0, 32);
//			OS_Printf("パレット転送 seq = %d \n",pal->seq);
		}else{
			wk->palwork.wait++;
		}
		
		CursorColTrans(&wk->CursorPal);
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
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );


	}

	// メイン画面1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_S );
	}

	// メイン画面背景
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_S );
	}


	// サブ画面テキスト面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	// サブ画面背景面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_RECORD );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_RECORD );

}


#define TALK_MESSAGE_BUF_NUM	( 90*2 )
#define TITLE_MESSAGE_BUF_NUM	( 20*2 )

//------------------------------------------------------------------
/**
 * お絵かきワーク初期化
 *
 * @param   wk		RECORD_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( RECORD_WORK *wk )
{
	int i;

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_RECORD );
		wk->TrainerStatus[i][0] = NULL;
		wk->TrainerStatus[i][1] = NULL;
		wk->TrainerReq[i]       = RECORD_EXIST_NO;

	}
	// 文字列バッファ作成
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_RECORD );
	wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_RECORD );

	wk->seq = RECORD_MODE_INIT;
	
	// レコードこうかんぼしゅう中！文字列取得
	MSGMAN_GetString(  wk->MsgManager, msg_union_record_title_01, wk->TitleString );

	// フィールドOBJ画像読み込み
	LoadFieldObjData( wk );

	wk->ObjPaletteTable = UnionView_PalleteTableAlloc( HEAPID_RECORD );


	// パレットアニメ用ワーク初期化
	wk->palwork.sw       = 0;
	wk->palwork.wait     = 0;
	wk->palwork.seq      = 0;
	wk->palwork.paldata  = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_record_s_obj_nclr, &wk->palwork.palbuf, HEAPID_RECORD );
	wk->connectBackup    = 0;
	wk->YesNoMenuWork    = NULL;
	wk->shareNum		 = 2;
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
static void FreeWork( RECORD_WORK *wk )
{
	int i;

	// フィールドOBJ画像解放
	FreeFieldObjData( wk );

	// 機械のパレットアニメ用データ解放
	sys_FreeMemoryEz(wk->palwork.paldata);

	// ユニオンOBJのパレットデータ解放
	sys_FreeMemoryEz(wk->ObjPaletteTable);

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TitleString ); 
	STRBUF_Delete( wk->TalkString ); 

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

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
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
static void BgGraphicSet( RECORD_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet( ARC_RECORD_GRA,  NARC_record_record_s_nclr, PALTYPE_MAIN_BG, 0, 16*16*2, HEAPID_RECORD );
	ArcUtil_PalSet( ARC_POKETCH_IMG, NARC_poketch_before_nclr,  PALTYPE_SUB_BG,  0, 16*2,   HEAPID_RECORD );
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_RECORD );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_RECORD );




	// メイン画面BG2キャラ転送
//	ArcUtil_BgCharSet( ARC_RECORD_GRA, NARC_record_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_S, 0, 32*8*0x20, 1, HEAPID_RECORD);

	// メイン画面BG2スクリーン転送
//	ArcUtil_ScrnSet(   ARC_RECORD_GRA, NARC_record_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 32*24*2, 1, HEAPID_RECORD);



	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr, bgl, GF_BGL_FRAME2_S, 0, 0, 1, HEAPID_RECORD);
	ArcUtil_ScrnSet(   ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 0, 1, HEAPID_RECORD);

	// サブ画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_RECORD_GRA, NARC_record_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 32*8*0x20, 1, HEAPID_RECORD);

	// サブ画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_RECORD_GRA, NARC_record_subbg_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_RECORD);

	// サブ画面会話ウインドウグラフィック転送
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_RECORD );

	MenuWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1+TALK_WIN_CGX_SIZ, FLD_MENUFRAME_PAL, 0, HEAPID_RECORD );

}


//** CharManager PlttManager用 **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)

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
			RECORD_CHAR_CONT_NUM,
			RECORD_CHAR_VRAMTRANS_MAIN_SIZE,
			RECORD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_RECORD
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(RECORD_PLTT_CONT_NUM, HEAPID_RECORD);

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
static void InitCellActor(RECORD_WORK *wk)
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
			HEAPID_RECORD);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 30, &wk->renddata, HEAPID_RECORD );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(3, i, HEAPID_RECORD);
	}


	//---------上画面用-------------------
#if 0
	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_RECORD_GRA, NARC_record_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_RECORD);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_RECORD_GRA, NARC_record_record_m_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_RECORD);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_RECORD_GRA, NARC_record_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_RECORD);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_RECORD_GRA, NARC_record_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_RECORD);
#endif

	//---------上画面人物OBJ読み込み-------------------

	//chara読み込み
	wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_RECORD_GRA, NARC_record_obj_s_lz_ncgr, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_RECORD);

	//pal読み込み
	wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_RECORD_GRA, NARC_record_record_s_obj_nclr, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 15, HEAPID_RECORD);

	//cell読み込み
	wk->resObjTbl[CHARA_RES][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_RECORD_GRA, NARC_record_obj_s_lz_ncer, 1, 2, CLACT_U_CELL_RES,HEAPID_RECORD);

	//同じ関数でanim読み込み
	wk->resObjTbl[CHARA_RES][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_RECORD_GRA, NARC_record_obj_s_lz_nanr, 1, 2, CLACT_U_CELLANM_RES,HEAPID_RECORD);


	//---------下画面用-------------------



	//chara読み込み
//	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
//							ARC_RECORD_GRA, NARC_record_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_RECORD);

	//pal読み込み
//	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
//							ARC_RECORD_GRA, NARC_record_record_m_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_RECORD);

	//cell読み込み
//	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
//							ARC_RECORD_GRA, NARC_record_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_RECORD);

	//同じ関数でanim読み込み
//	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
//							ARC_RECORD_GRA, NARC_record_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_RECORD);

	// リソースマネージャーから転送

	// Chara転送
//	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
//	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES] );

	// パレット転送
//	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
//	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  2 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

static const u16 obj_pos_tbl[][2]={
	{ 204,  84   },
	{ 204,  61-8 },
	{ 233,  80-8 },
	{ 223, 111-8 },
	{ 184, 111-8 },
	{ 174,  80-8 },
};

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			RECORD_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(RECORD_WORK *wk)
{
	int i;
#if 0
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
#endif

	CLACT_U_MakeHeader(&wk->clActHeader_friend, 2, 2, 2, 2, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 1,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);


	{
		//登録情報格納
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_friend;

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_RECORD;

		//セルアクター表示開始

		// 真ん中の機械だけは表示
		add.mat.x = FX32_ONE *   obj_pos_tbl[0][0];
		add.mat.y = FX32_ONE *   obj_pos_tbl[0][1];
		wk->MainActWork[0] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->MainActWork[0],1);
//		CLACT_AnmChg( wk->MainActWork[0], 0 );
		CLACT_SetDrawFlag( wk->MainActWork[0], 1 );

		// メイン画面用(人物の登録）
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   obj_pos_tbl[i+1][0];
			add.mat.y = FX32_ONE *   obj_pos_tbl[i+1][1];
			wk->MainActWork[i+1] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->MainActWork[i+1],1);
			CLACT_AnmChg( wk->MainActWork[i+1], 27+(i-1)*2 );
			CLACT_SetDrawFlag( wk->MainActWork[i+1], 0 );
		}


		//セルアクター表示開始
		// サブ画面用(矢印の登録）
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
//			wk->SubActWork[i] = CLACT_Add(&add);
//			CLACT_SetAnmFlag(wk->SubActWork[i],1);
//			CLACT_AnmChg( wk->SubActWork[i], i );
//			CLACT_DrawPriorityChg(wk->SubActWork[i], 1);	// それぞれのアクターのプライオリティ設定
//			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
			
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
#define RECORD_NAME_BMP_W	 ( 16 )
#define RECORD_NAME_BMP_H	 ( 11 )
#define RECORD_NAME_BMP_SIZE (RECORD_NAME_BMP_W * RECORD_NAME_BMP_H)


// 「やめる」文字列BMP（下画面）
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 20 )
#define OEKAKI_END_BMP_W	( 6  )
#define OEKAKI_END_BMP_H	( 2  )


// 会話ウインドウ表示位置定義
#define RECORD_TALK_X		(  2 )
#define RECORD_TALK_Y		(  19 )

#define RECORD_TITLE_X		(   3  )
#define RECORD_TITLE_Y		(   1  )
#define RECORD_TITLE_W		(  26  )
#define RECORD_TITLE_H		(   2  )


#define RECORD_MSG_WIN_OFFSET 		(1 + TALK_WIN_CGX_SIZ     + MENU_WIN_CGX_SIZ)
#define RECORD_TITLE_WIN_OFFSET		( RECORD_MSG_WIN_OFFSET   + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define RECORD_NAME_WIN_OFFSET		( RECORD_TITLE_WIN_OFFSET + RECORD_TITLE_W*RECORD_TITLE_H )
#define RECORD_YESNO_WIN_OFFSET		( RECORD_NAME_WIN_OFFSET  + RECORD_NAME_BMP_SIZE )

//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit(RECORD_WORK *wk, PROC* proc)
{
	// ---------- メイン画面 ------------------

	// BG1面BMP（やめる）ウインドウ確保・描画
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_S,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 13,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );

	// ----------- サブ画面名前表示BMP確保 ------------------
	// BG0面BMP（会話ウインドウ）確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		RECORD_TALK_X, RECORD_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  RECORD_MSG_WIN_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG0面BMP（タイトルウインドウ）確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
		RECORD_TITLE_X, RECORD_TITLE_Y, RECORD_TITLE_W, RECORD_TITLE_H, 15,  RECORD_TITLE_WIN_OFFSET );
	CenteringPrint(&wk->TitleWin, wk->TitleString, MSG_ALLPUT);

	// 名前表示ウインドウ
	{
		int i;
			GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[0], GF_BGL_FRAME0_M,	
				TRAINER_NAME_WIN_X, TRAINER1_NAME_WIN_Y, RECORD_NAME_BMP_W, RECORD_NAME_BMP_H, 15,  RECORD_NAME_WIN_OFFSET);

			GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[0], 0 );

		//最初に見えている面なので文字パネル描画と転送も行う
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(1, 3, 0), wk );


	}

	OS_Printf("YESNO win offset = %d\n",RECORD_YESNO_WIN_OFFSET);

/*
3713 2D4A 5694 089D 5EBF 7DC0 76EF 0000
0000 0000 0000 7FFF 62FF 6F7B 7F52 7FFF

*/



}	

//------------------------------------------------------------------
/**
 * $brief   センタリングしてプリント
 *
 * @param   win		GF_BGL_BMPWIN
 * @param   strbuf	
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait)
{
	int length = FontProc_GetPrintStrWidth( FONT_TALK, strbuf, 0 );
	int x      = (RECORD_TITLE_W*8-length)/2;
	
	GF_BGL_BmpWinDataFill( win, 0x0000 );

	GF_STR_PrintColor(	win, FONT_TALK, strbuf, x, 1, wait,	GF_PRINTCOLOR_MAKE(1, 4, 0),NULL);

}


// はい・いいえBMP（下画面）
#define YESNO_WIN_FRAME_CHAR	( 1 + TALK_WIN_CGX_SIZ )
#define YESNO_CHARA_OFFSET		( 1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define YESNO_WINDOW_X			( 22 )
#define YESNO_WINDOW_Y1			(  7 )
#define YESNO_WINDOW_Y2			( 13 )
#define YESNO_CHARA_W			(  8 )
#define YESNO_CHARA_H			(  4 )


//------------------------------------------------------------------
/**
 * $brief   確保したBMPWINを解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( RECORD_WORK *wk )
{
	int i;
	
//	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[0] );
//	}
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->MsgWin );


}





//------------------------------------------------------------------
/**
 * 移動の結果カーソルの形状がどのように変わるかを決定する
 * 文字の上であれば、正方形のカーソル、ボタンの上であれば長方形のカーソル
 * 文字の更新が行われることで、サブ画面の中のフォントの更新も行われる
 *
 * @param   wk			RECORD_WORK*
 * @param   arrow		移動方向
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(RECORD_WORK *wk, int arrow)
{
	VecFx32 tmpVex;

//	tmpVex.x = FX32_ONE*(MAIN_CURSOR_POSX+wk->Cursor.x*12);
//	tmpVex.y = FX32_ONE*(MAIN_CURSOR_POSY+(wk->Cursor.y-1)*16);
//	CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);


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
	mat.y = FX32_CONST( y );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}





//------------------------------------------------------------------
/**
 * $brief   開始時のメッセージ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Record_MainInit( RECORD_WORK *wk, int seq )
{
	
    CommStateSetErrorCheck(FALSE,TRUE); // 子機の出入りが確定するまではエラー扱いしない
	// 親の時はAボタンで開始メッセージ。子機は開始待ちメッセージ
	if(CommGetCurrentID()==0){
		RecordMessagePrint(wk, msg_union_record_01_01, 0 );
	}else{
		RecordMessagePrint(wk, msg_union_record_01_07, 0 );
	}
	SequenceChange_MesWait(wk, RECORD_MODE);

//	wk->seq = RECORD_MODE;

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   レコードコーナー通常処理
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_MainNormal( RECORD_WORK *wk, int seq )
{
	// 全体操作禁止でなければキー入力
	PadControl( wk );

	//TrainerObjFunc(wk);

	
	if(CommGetCurrentID()==0){				// 親機の時
		if(OnlyParentCheck()!=1){			// 一人じゃないか？
			RecordDataSendRecv( wk );
		}
	}else{
			RecordDataSendRecv( wk );
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * @brief   キー入力管理
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void PadControl( RECORD_WORK *wk )
{
	// レコード交換を開始しますか？（親のみ）
	if(sys.trg&PAD_BUTTON_A){
		if(CommGetCurrentID()==0){
			if(MyStatusGetNum()==wk->shareNum && wk->ridatu_bit == 0){
				u8 flag = RECORD_BAN_ON;
				RecordMessagePrint( wk, msg_union_record_01_02, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_START_SELECT);

				// 離脱禁止通達
				CommSendData( CR_RECORD_BAN, &flag, 1 );
				
				// 接続人数制限ON
				ChangeConnectMax( wk, 0 );
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}

	}else if(sys.trg&PAD_BUTTON_B){
		// やめますか？
		if(CommGetCurrentID()){
			// 子機は親機から禁止が来ている場合は終了できない
			if(wk->banFlag==0){
				RecordMessagePrint( wk, msg_union_record_01_03, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_END_SELECT);
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}else{
//			if( MyStatusGetNum()==wk->shareNum ){
			if( CommGetConnectNum()==wk->shareNum && wk->ridatu_bit == 0){
				u8 flag = RECORD_BAN_ON;
				// 親機は終了メニューへ
				RecordMessagePrint( wk, msg_union_record_01_03, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_END_SELECT);
				// 離脱禁止通達
				CommSendData( CR_RECORD_BAN, &flag, 1 );

				// 接続人数制限ON
				ChangeConnectMax( wk, 0 );
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}
	}
	else{
		if(wk->beacon_flag == RECORD_BAN_NONE){
			if(CommGetCurrentID() == 0 && CommGetConnectNum()==wk->shareNum){
				u8 flag = RECORD_BAN_NONE;
				// 離脱禁止解除通達
				CommSendData( CR_RECORD_BAN, &flag, 1 );
			}
		}
	}

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
static void EndSequenceCommonFunc( RECORD_WORK *wk )
{
	
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
static int Record_NewMember( RECORD_WORK *wk, int seq )
{
	// ●●●さんがはいってきました
//	RecordMessagePrint(wk, msg_oekaki_01);
//	wk->seq = RECORD_MODE_NEWMEMBER_WAIT;
	SequenceChange_MesWait(wk, RECORD_MODE_NEWMEMBER_END );

	// 画像転送状態になったら輝度ダウン
//	G2_SetBlendBrightness(  GX_BLEND_PLANEMASK_BG1|
//							GX_BLEND_PLANEMASK_BG2|
//							GX_BLEND_PLANEMASK_BG3|
//							GX_BLEND_PLANEMASK_OBJ
//								,  -6);

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   メッセージ終了を待って次のシーケンスに行く関数
 *
 * @param   wk		
 * @param   next		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SequenceChange_MesWait( RECORD_WORK *wk, int next )
{
	wk->seq     = RECORD_MODE_MESSAGE_WAIT;
	wk->nextseq = next;
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
static int Record_MessageWaitSeq( RECORD_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = wk->nextseq;
	}
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
static int Record_NewMemberEnd( RECORD_WORK *wk, int seq )
{
	// 輝度ダウン解除
//	G2_BlendNone();

	if(CommGetCurrentID()==0){
		int flag = RECORD_BAN_NONE;
		// 離脱禁止解除通達
		CommSendData( CR_RECORD_BAN, &flag, 1 );
	}

	wk->seq = RECORD_MODE;
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}


// はい・いいえ
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( 13 )
#define	BMP_YESNO_CGX	( RECORD_YESNO_WIN_OFFSET )


// はい・いいえ
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME0_M, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, BMP_YESNO_CGX
};

//------------------------------------------------------------------
/**
 * $brief   レコードコーナー「やめる」を選択した時
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectPutString( RECORD_WORK *wk, int seq )
{
	// はい・いいえ表示
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_END_SELECT_WAIT;
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
static int Record_EndSelectWait( RECORD_WORK *wk, int seq )
{
	int result;
	u32 ret;
	
	// 子機は親機から操作禁止がきている場合は操作できない
	if(CommGetCurrentID()){
		if(wk->banFlag){
			if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
			EndSequenceCommonFunc( wk );		//終了選択時の共通処理
			return seq;
		}
	}
	else{	//親の場合
		if(wk->ridatu_bit != 0){			//離脱しようとしている子がいるなら許可しない
			if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
			EndSequenceCommonFunc( wk );		//終了選択時の共通処理
			return seq;
		}
	}

//	if(wk->shareNum != MyStatusGetNum()){	//一致していないなら「やめる」許可しない
	if(MyStatusGetNum() != CommGetConnectNum()){
		//一致していないなら「やめる」許可しない(子も通るここは親しか更新されないshareNumは見ない)
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}

	// メニュー入力
	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			if(CommGetCurrentID()==0){
				int flag = RECORD_BAN_NONE;
				// 離脱禁止解除通達
				CommSendData( CR_RECORD_BAN, &flag, 1 );

				// 接続人数制限OFF
				ChangeConnectMax( wk, 1 );
			}
			
			SequenceChange_MesWait( wk, RECORD_MODE_INIT );
		}else{
			if(CommGetCurrentID()==0){		
				SequenceChange_MesWait( wk, RECORD_MODE_END_SELECT_PARENT );
				RecordMessagePrint( wk, msg_union_record_01_13, 0 );		// リーダーがやめると…
			}else{
				COMM_RECORD_END_CHILD_WORK crec;
				
				MI_CpuClear8(&crec, sizeof(COMM_RECORD_END_CHILD_WORK));
				crec.request = CREC_REQ_RIDATU_CHECK;
				crec.ridatu_id = CommGetCurrentID();
				
				wk->status_end = TRUE;
				wk->ridatu_wait = 0;
				//wk->seq = RECORD_MODE_END_CHILD;
				wk->seq = RECORD_MODE_END_SELECT_ANSWER_WAIT;
				CommSendData( CR_RECORD_END_CHILD, &crec, sizeof(COMM_RECORD_END_CHILD_WORK) );
			}
		}
		wk->YesNoMenuWork = NULL;
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
static int Record_EndSelectAnswerWait( RECORD_WORK *wk, int seq )
{
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
static int Record_EndSelectAnswerOK( RECORD_WORK *wk, int seq )
{
	if((wk->oya_share_num != CommGetConnectNum())
			|| (wk->oya_share_num != MyStatusGetNum())){
		OS_TPrintf("share_nuM = %d, Comm = %d, My = %d, Bit = %d\n", wk->oya_share_num, CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		wk->ridatu_wait = 0;
		wk->seq = RECORD_MODE_END_SELECT_ANSWER_NG;
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}
	
	wk->ridatu_wait++;
	OS_TPrintf("ridatu_wait = %d\n", wk->ridatu_wait);
	if(wk->ridatu_wait > 30){
		COMM_RECORD_END_CHILD_WORK crec;
		
		MI_CpuClear8(&crec, sizeof(COMM_RECORD_END_CHILD_WORK));
		crec.request = CREC_REQ_RIDATU_EXE;
		crec.ridatu_id = CommGetCurrentID();

		CommSendData( CR_RECORD_END_CHILD, &crec, sizeof(COMM_RECORD_END_CHILD_WORK) );

		wk->ridatu_wait = 0;
		wk->seq = RECORD_MODE_END_CHILD;
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
static int Record_EndSelectAnswerNG( RECORD_WORK *wk, int seq )
{
	wk->status_end = FALSE;
	SequenceChange_MesWait( wk, RECORD_MODE_INIT );
	
	OS_TPrintf("==========離脱強制キャンセル！===========\n");

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
	
}


//------------------------------------------------------------------
/**
 * $brief   このメンバーでレコードを開始しますか？
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartSelect( RECORD_WORK *wk, int seq )
{
	// はい・いいえ表示
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_START_SELECT_WAIT;
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「開始しますか？」はい・いいえ選択待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartSelectWait( RECORD_WORK *wk, int seq )
{
	int result;
	u32 ret;

	if(MyStatusGetNum() != wk->shareNum 		//一致していないなら許可しない
			|| wk->ridatu_bit != 0){			//離脱しようとしている子がいるなら許可しない
		if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
			Snd_SePlay(SEQ_SE_DP_CUSTOM06);
		}
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}
		
	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			int flag = RECORD_BAN_NONE;
			// 離脱禁止解除通達
			CommSendData( CR_RECORD_BAN, &flag, 1 );

			// ビーコン状態変更
			
			ChangeConnectMax( wk, 1 );
			SequenceChange_MesWait( wk, RECORD_MODE_INIT );


		}else{
			// 絶対ここにくるのは親だけど
			if(CommGetCurrentID()==0){		
//				SequenceChange_MesWait( wk, RECORD_MODE_STAET_RECORD_COMMAND );
//				RecordMessagePrint( wk, msg_union_record_01_11, 1 );		// まぜています
                // 接続禁止に書き換え
				wk->seq = RECORD_MODE_START_RECORD_COMMAND;
				wk->start_num = MyStatusGetNum();
			}else{
				GF_ASSERT(0);
			}
		}
		wk->YesNoMenuWork = NULL;
	}


	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	return seq;
}


//------------------------------------------------------------------
/**
 * $brief   親機が
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartRecordCommand( RECORD_WORK *wk, int seq )
{
	if(wk->record_send == 0){
		if(CommSendData( CR_RECORD_START, NULL, 0 ) == TRUE){
			wk->record_send = TRUE;
		}
	}
	
//	SequenceChange_MesWait( wk, RECORD_MODE_RECORD_SEND_DATA );
//	RecordMessagePrint( wk, msg_union_record_01_11, 1 );		// まぜています

	return seq;

}

//==============================================================================
/**
 * $brief   タイトルメッセージを変える「こうかんちゅう！」
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void RecordCornerTitleChange( RECORD_WORK *wk )
{
	// レコードこうかんぼしゅう中！文字列取得
	MSGMAN_GetString(  wk->MsgManager, msg_union_record_title_02, wk->TitleString );

	CenteringPrint(&wk->TitleWin, wk->TitleString, MSG_ALLPUT);
	
	// 機械をアニメさせる
	CLACT_AnmChg( wk->MainActWork[0], 37 );

	// VBLANKパレットアニメ開始
	wk->palwork.sw = 1;
}

//------------------------------------------------------------------
/**
 * $brief   データ送信・受信待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_RecordSendData( RECORD_WORK *wk, int seq )
{
	int i,result;

	result = 0;
//	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
//		result += CommIsSpritDataRecv(i);
//	}

	if( CommGetCurrentID() == 0 && CommGetConnectNum() != wk->start_num){
		//開始した時の人数と現在の人数が変わっているなら通信エラーにする
//		OS_TPrintf("人数が変わっているので強制的に通信エラーにします　開始時＝%d, 現在＝%d\n", wk->start_num, CommGetConnectNum());
//		CommStateSetError();
	}
	
	// 受信が終了した人数と接続人数が同じになったら終了
	if( CommGetConnectNum()==wk->recv_count ){

		// データ混ぜる処理へ
		wk->seq = RECORD_MODE_RECORD_MIX_DATA;

		for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
			OS_TPrintf("受信データ id=%d, seed=%d, xor=%08x\n",i,wk->recv_data[i].seed, wk->recv_data[i]._xor);
		}
	}

	return seq;
}
//------------------------------------------------------------------
/**
 * @brief	まぜる処理
 *
 * @param	wk
 * @param	seq
 *
 * @return	int
 */
//------------------------------------------------------------------
static int Record_RecordMixData( RECORD_WORK *wk, int seq )
{
	// データを混ぜる処理
	MixReceiveData(wk->savedata, wk->recv_data);

	wk->seq = RECORD_MODE_COMM_SAVE_START;

	return seq;
}




//------------------------------------------------------------------
/**
 * @brief   レコード交換終了セーブ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_CommSaveStart( RECORD_WORK *wk, int seq )
{
	void *FnoteWork;

	// ソフトリセット不可能にする
	sys.DontSoftReset = 1;

	// 冒険ノート処理
	FnoteWork = FNOTE_SioRecordDataMake( HEAPID_RECORD );
	FNOTE_DataSave( wk->param->fnote, FnoteWork, FNOTE_TYPE_SIO );

	// スコアを加算
	RECORD_Score_Add( wk->param->record, SCORE_ID_COMM_RECORD_CORNER );

	// 通信同期セーブ処理初期化
	CommSyncronizeSaveInit( &wk->saveseq_work );
	wk->seq = RECORD_MODE_COMM_SAVE;
	OS_Printf("同期セーブ開始\n");
	return seq;
}


//==============================================================================
/**
 * @brief   レコード交換通信同期セーブ終了待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  stati int		
 */
//==============================================================================
static int Record_CommSave( RECORD_WORK *wk, int seq ) 
{
	if( CommGetCurrentID() == 0 && CommGetConnectNum() != wk->start_num){
		//開始した時の人数と現在の人数が変わっているなら通信エラーにする
//		OS_TPrintf("人数が変わっているので強制的に通信エラーにします　開始時＝%d, 現在＝%d\n", wk->start_num, CommGetConnectNum());
//		CommStateSetError();
	}

	// 通信同期セーブ終了待ち
	if(CommSyncronizeSave(wk->param->sv, SVBLK_ID_MAX, &wk->saveseq_work)){

		// SE終了
		Snd_SeStopBySeqNo( SEQ_SE_DP_F209, 8 );


		// 「レコード交換が終了しました！」
		RecordMessagePrint( wk, msg_union_record_01_12, 0 );
		SequenceChange_MesWait( wk, RECORD_MODE_END_MES_WAIT );

		// 機械のアニメ元に戻す
		CLACT_AnmChg( wk->MainActWork[0], 0 );

		// VBLANKパレットアニメ終了
		wk->palwork.sw = 0;

		wk->wait = 0;
		OS_Printf("同期セーブ終了\n");

		// ソフトリセット可能にする
		sys.DontSoftReset = 0;

		wk->record_execute = FALSE;
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * @brief   正常終了(メッセージ表示から１秒まって終了）
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndMessageWait( RECORD_WORK *wk, int seq )
{
	if(wk->wait++ > 60){
		// 終了用通信同期
//		CommTimingSyncStart(RECORD_SYNCHRONIZE_END);
		wk->seq = RECORD_MODE_FORCE_END_WAIT;
	}
	return seq;
}


// RECORD_MODE_END_CHILD
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
static int 	Record_EndChild( RECORD_WORK *wk, int seq )
{
	u8 temp;
	
	// レコードコーナーをぬけました
	RecordMessagePrint( wk, msg_union_record_01_04, 0 );	

	// 終了通達
	temp = 0;
//	CommSendData( CR_RECORD_END_CHILD, &temp, 1 );

	SequenceChange_MesWait( wk, RECORD_MODE_END_CHILD_WAIT );

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}
				

// RECORD_MODE_END_CHILD_WAIT
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
static int 	Record_EndChildWait( RECORD_WORK *wk, int seq )
{			
	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT ){
		// ワイプフェード開始
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD );
		seq = SEQ_OUT;						//終了シーケンスへ
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
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
static int Record_EndSelectParent( RECORD_WORK *wk, int seq )
{

	// はい・いいえ表示
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_END_SELECT_PARENT_WAIT;

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
static int Record_EndSelectParentWait( RECORD_WORK *wk, int seq )
{
	int ret;

	if(wk->shareNum != MyStatusGetNum()			//一致していないなら「やめる」許可しない
			|| wk->ridatu_bit != 0){			//離脱しようとしている子がいるなら許可しない
		if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
			Snd_SePlay(SEQ_SE_DP_CUSTOM06);
		}
		EndSequenceCommonFunc( wk );		//終了選択時の共通処理
		return seq;
	}

	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			int flag = RECORD_BAN_NONE;
			
			wk->seq = RECORD_MODE_INIT;

			// 離脱禁止解除通達
			CommSendData( CR_RECORD_BAN, &flag, 1 );

			// 接続人数制限OFF
			ChangeConnectMax( wk, 1 );

		}else{
			wk->seq = RECORD_MODE_FORCE_END;
			CommSendData( CR_RECORD_END, NULL, 0 );						//終了通知
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// 親機（自分）の名前をWORDSET
		}
		wk->YesNoMenuWork = NULL;
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
static int Record_ForceEnd( RECORD_WORK *wk, int seq )
{
	if(CommGetCurrentID()==0){
		// それでは　レコード通信をちゅうし　します
		RecordMessagePrint( wk, msg_union_record_01_04, 0 );
	}else{
		// つごうがわるくなったメンバーがいるのでかいさんします
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// 親機（自分）の名前をWORDSET
		RecordMessagePrint( wk, msg_union_record_01_15, 0 );
	}
	SequenceChange_MesWait(wk,RECORD_MODE_FORCE_END_MES_WAIT);
	wk->wait = 0;

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}


//------------------------------------------------------------------
/**
 * @brief   強制終了メッセージ１秒待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_FroceEndMesWait( RECORD_WORK *wk, int seq )
{
	wk->wait++;
	if(wk->wait > RECORD_1SEC_WAIT){
		wk->seq = RECORD_MODE_FORCE_END_WAIT;
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
static int Record_ForceEndWait( RECORD_WORK *wk, int seq )
{
	// 通信同期待ち
	CommTimingSyncStart(RECORD_SYNCHRONIZE_END);
	wk->seq = RECORD_MODE_FORCE_END_SYNCHRONIZE;

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
static int Record_ForceEndSynchronize( RECORD_WORK *wk, int seq )
{
	if(CommIsTimingSync(RECORD_SYNCHRONIZE_END)){
	    CommStateSetErrorCheck(FALSE, FALSE); // 終了処理に入ったので切断はもう無視

		OS_Printf("終了時同期成功\n");
		// ワイプフェード開始
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD);

		seq = SEQ_OUT;						//終了シーケンスへ
	}
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
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
static int Record_EndParentOnly( RECORD_WORK *wk, int seq )
{
	RecordMessagePrint( wk, msg_union_record_01_08, 0 );	// リーダーが抜けたので解散します。
	wk->seq = RECORD_MODE_END_PARENT_ONLY_WAIT;

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
static int Record_EndParentOnlyWait( RECORD_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = RECORD_MODE_END_CHILD_WAIT;
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
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq )
{
	// ●●●さんがかえりました
	if( wk->MsgIndex != 0xff && EndMessageWait( wk->MsgIndex ) == 0){
		//表示中のメッセージがある場合は強制停止
		GF_STR_PrintForceStop(wk->MsgIndex);
	}
	RecordMessagePrint(wk, msg_union_record_01_14, 1 );
	wk->seq = RECORD_MODE_LOGOUT_CHILD_WAIT;

	// 接続可能人数を一旦現在の接続人数に落とす
	if(CommGetCurrentID()==0){
		ChangeConnectMax( wk, 0 );
	}


	OS_TPrintf("人数チェック＝logout child %d\n", CommGetConnectNum());
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
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq )
{
	// 接続人数が１減るかチェック
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	wk->seq  = RECORD_MODE_LOGOUT_CHILD_CLOSE;
	wk->wait = 0;

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
static int 	Record_LogoutChildClose( RECORD_WORK *wk, int seq )
{			

	// 接続人数が１減るまでは待つ
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}
	
	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT && wk->err_num == 0){
		wk->seq = RECORD_MODE_INIT;//RECORD_MODE;				//終了シーケンスへ

		// 離脱者がいなくなったので、＋１状態で一人は入れるようにする
		if(CommGetCurrentID()==0){
			ChangeConnectMax( wk, 1 );
		}
	}

	EndSequenceCommonFunc( wk );			//終了選択時の共通処理
	return seq;
	
}

#if 0
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
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq )
{
	// ●●●さんがかえりました
	wk->seq = RECORD_MODE_LOGOUT_CHILD_WAIT;

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
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq )
{
		wk->seq  = RECORD_MODE_LOGOUT_CHILD_CLOSE;
		wk->wait = 0;

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
static int 	Record_LogoutChildClose( RECORD_WORK *wk, int seq )
{			

	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT ){
		wk->seq = RECORD_MODE;				//終了シーケンスへ
	}

	EndSequenceCommonFunc( wk );			//終了選択時の共通処理
	return seq;
	
}

#endif


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
void RecordCorner_MainSeqForceChange( RECORD_WORK *wk, int seq, u8 id  )
{
	switch(seq){
	case RECORD_MODE_NEWMEMBER_END:
		EndMessageWindowOff( wk );
		break;
	case RECORD_MODE_FORCE_END:
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		break;
	case RECORD_MODE_RECORD_SEND_DATA:
		if(EndMessageWait(wk->MsgIndex) == 0){
			//表示中のメッセージがある場合は強制停止
			GF_STR_PrintForceStop(wk->MsgIndex);
		}
		RecordMessagePrint( wk, msg_union_record_01_11, 0 );		// 「まぜています」表示
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		break;
	case RECORD_MODE_LOGOUT_CHILD:
		if(wk->status_end == TRUE){
			return;	//自分自身が離脱処理中
		}
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		if(id==CommGetCurrentID()){
			// 自分が離脱する子機だった場合は「子機がいなくなたよ」とは言わない
			return;
		}
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		if(CommGetCurrentID() == 0){
			wk->ridatu_bit &= 0xffff ^ id;
		}
		break;
	case RECORD_MODE_END_SELECT_ANSWER_OK:
		break;
	case RECORD_MODE_END_SELECT_ANSWER_NG:
		break;
	default:
		GF_ASSERT( "指定以外のシーケンスチェンジが来た" );
		return;
	}
	wk->seq = seq;

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
void RecordCorner_MainSeqCheckChange( RECORD_WORK *wk, int seq, u8 id  )
{
	// 通常状態なら
	if(wk->seq == RECORD_MODE){
		OS_Printf("子機%dの名前を登録\n",id);
		switch(seq){
		case RECORD_MODE_NEWMEMBER:	
			// 指定の子機の名前をWORDSETに登録（離脱・乱入時)
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			ChangeConnectMax( wk, 1 );
			wk->seq      = seq;
			wk->shareNum = CommGetConnectNum();
			wk->ridatu_bit = 0;
			if(CommGetCurrentID()==0){
				int flag = RECORD_BAN_ON;//NONE;
				// 離脱禁止解除通達
				CommSendData( CR_RECORD_BAN, &flag, 1 );
				
			}
			break;
			// ↓↓↓ 
		case RECORD_MODE_LOGOUT_CHILD:
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			if(id==CommGetCurrentID()){
				// 自分が離脱する子機だった場合は「子機がいなくなたよ」とは言わない
				return;
			}
			if(CommGetCurrentID() == 0){
				wk->ridatu_bit &= 0xffff ^ id;
			}
			wk->seq = seq;
			break;
		default:
			GF_ASSERT( 0&&"指定以外のシーケンスチェンジが来た" );
			return;
		}


	}
	else if(seq == RECORD_MODE_NEWMEMBER){
		wk->ridatu_bit = 0;
		wk->shareNum = CommGetConnectNum();
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













//------------------------------------------------------------------
/**
 * 機械のパレット変更（点滅）
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

	*CursorCol+=10;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, ( 5    )*2, 2);
	GX_LoadOBJPltt((u16*)&tmp, ( 5+16 )*2, 2);
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
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return result;
}

#define NAME_PRINT_HABA	( 18 )
#define ID_STRING_NUM	(2+1+5+1)
//------------------------------------------------------------------
/**
 * $brief   オンライン状況を確認して上画面に名前とIDを表示する
 *
 * @param   win		
 * @param   frame		
 * @param   color		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static BOOL NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, RECORD_WORK *wk )
{
	int i,id = CommGetCurrentID();
	STRBUF *id_str = NULL;


	// 名前取得の状況に変化が無い場合は書き換えない
	if(!MyStatusCheck(wk)){
		return FALSE;
	}


	// それぞれの文字パネルの背景色でクリア
	GF_BGL_BmpWinDataFill(&win[0],0x0000);

	// 描画
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][0]!=NULL){
			// トレーナーIDの取得
			u16 tid = MyStatus_GetID_Low( wk->TrainerStatus[i][0] );

			// 自分の名前取得
			MyStatus_CopyNameString( wk->TrainerStatus[i][0], wk->TrainerName[i] );

			// トレーナーIDを埋め込んだ文字列「ID 12345」を取得
			WORDSET_RegisterNumber( wk->WordSet, 0, tid, 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_HANKAKU );
			id_str = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, msg_union_record_name_02, HEAPID_RECORD );
			
			if(id==i){	// 自分の名前の時は赤色で名前とIDを描画
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, wk->TrainerName[i], 5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(2,3,0),NULL);
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, id_str, 5+13*5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(2,3,0),NULL);
			}else{
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, wk->TrainerName[i], 5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, color,NULL);
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, id_str, 5+13*5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, color,NULL);
			}
			// ID文字列を解放
			STRBUF_Delete(id_str);
		}
	}
	GF_BGL_BmpWinOn( &win[0] );

	return TRUE;
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
static int ConnectCheck( RECORD_WORK *wk )
{
	int i,result=0;
	MYSTATUS *status;
	STRCODE  *namecode;

	// 接続チェック
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->ConnectCheck[i][0] = wk->ConnectCheck[i][1];

		wk->ConnectCheck[i][0] = CommIsConnect(i);

	}

	// 接続がいたら名前を反映させる
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->ConnectCheck[i][0]){				// 接続しているか？
			// 接続している

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
static void RecordDataSendRecv( RECORD_WORK *wk )
{
	
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
	for(result=0,i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
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
int RecordCorner_MyStatusGetNum(void)
{
	return MyStatusGetNum();
}


//	RECORD_EXIST_NO=0,
//	RECORD_EXIST_APPEAR_REQ,
//	RECORD_EXIST_APPEAR,
//	RECORD_EXIST_BYE_REQ,


//------------------------------------------------------------------
/**
 * $brief   MYSTATUSの取得状況に変化があったか？
 *
 * @param   wk		
 *
 * @retval  int		あったら1,  無い場合は0
 */
//------------------------------------------------------------------
static BOOL MyStatusCheck( RECORD_WORK *wk )
{
	int i,result=FALSE;
	// 接続がいたら名前を反映させる
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->TrainerStatus[i][1] = wk->TrainerStatus[i][0];
		wk->TrainerStatus[i][0] = CommInfoGetMyStatus(i);
	}

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][1] != wk->TrainerStatus[i][0]){

			// 変化あり
			result = TRUE;

			// 登場・さよならリクエストの発行
			if(wk->TrainerStatus[i][0]==NULL){
				wk->TrainerReq[i] = RECORD_EXIST_BYE_REQ;
			}else{
				wk->TrainerReq[i] = RECORD_EXIST_APPEAR_REQ;
			}
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
static void RecordMessagePrint( RECORD_WORK *wk, int msgno, int all_put )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	tempbuf = STRBUF_Create(TALK_MESSAGE_BUF_NUM,HEAPID_RECORD);
	MSGMAN_GetString(  wk->MsgManager, msgno, tempbuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	STRBUF_Delete(tempbuf);

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, 1, FLD_MESFRAME_PAL );

	// 文字列描画開始
	if(all_put == 0){
		wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, GetTalkSpeed(wk), NULL);
	}
	else{
		//一括表示の場合はMsgIndexが0xffになるので注意！
		GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, MSG_ALLPUT, NULL);
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
static void EndMessageWindowOff( RECORD_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}


//------------------------------------------------------------------
/**
 * @brief   トレーナーOBJの表示制御
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TrainerObjFunc( RECORD_WORK *wk )
{
	int i,seflag=0;
	
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		switch(wk->TrainerReq[i]){
		case RECORD_EXIST_NO:
			break;
		case RECORD_EXIST_APPEAR_REQ:
			{
				int view,sex;
				GF_ASSERT(wk->TrainerStatus[i][0]!=NULL);
				
				sex = MyStatus_GetMySex( wk->TrainerStatus[i][0] );
				view  = MyStatus_GetTrainerView( wk->TrainerStatus[i][0] );
				if(CommGetCurrentID()==i){
					// 主人公OBJ用のアニメ
					CLACT_AnmChg( wk->MainActWork[i+1], 38+sex*2 );
				}else{
					// フィールドOBJ用のアニメ
					TransFieldObjData( wk->FieldObjCharaData, wk->FieldObjPalData,  i, view, sex );
					CLACT_AnmChg( wk->MainActWork[i+1], 27+i*2 );
				}

			}
			CLACT_SetDrawFlag(wk->MainActWork[i+1], 1);
			wk->TrainerReq[i] = RECORD_EXIST_APPEAR;
			seflag = 1;
			break;
		case RECORD_EXIST_APPEAR:
			break;
		case RECORD_EXIST_BYE_REQ:
//			CLACT_SetDrawFlag(wk->MainActWork[i+1], 0);
			if(CommGetCurrentID()==i){
				int sex = MyStatus_GetMySex( wk->TrainerStatus[i][0] );
				CLACT_AnmChg( wk->MainActWork[i+1], 38+sex*2+1 );
			}else{
				CLACT_AnmChg( wk->MainActWork[i+1], 27+i*2+1 );
			}
			wk->TrainerReq[i] = RECORD_EXIST_NO;
			break;
		}
	}
	
	// 登場SEが必要な場合は鳴らす
	if(seflag){
		Snd_SePlay( SE_GTC_APPEAR );
	}
}


//------------------------------------------------------------------
/**
 * @brief   フィールドOBJ画像読み込み（ユニオンと自機）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadFieldObjData( RECORD_WORK *wk )
{
	// パレット読み込み
	wk->FieldObjPalBuf[0] = ArcUtil_PalDataGet( ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_nclr, &(wk->FieldObjPalData[0]), HEAPID_RECORD );
	wk->FieldObjPalBuf[1] = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &(wk->FieldObjPalData[1]), HEAPID_RECORD );

	// 画像読み込み
	wk->FieldObjCharaBuf[0] = ArcUtil_CharDataGet( ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_lz_ncgr, 1, &(wk->FieldObjCharaData[0]), HEAPID_RECORD );
	wk->FieldObjCharaBuf[1] = ArcUtil_CharDataGet( ARC_RECORD_GRA, NARC_record_union_chara_lz_ncgr,  1, &(wk->FieldObjCharaData[1]), HEAPID_RECORD );

}

#define OBJ_TRANS_SIZE	( 3 * 4*4 )
static const u16 obj_offset[]={
	( 13                    )*0x20,
	( 13 + OBJ_TRANS_SIZE*1 )*0x20,
	( 13 + OBJ_TRANS_SIZE*2 )*0x20,
	( 13 + OBJ_TRANS_SIZE*3 )*0x20,
	( 13 + OBJ_TRANS_SIZE*4 )*0x20,
};


static int _obj_no = 0;
static int _pal_no = 0;

//------------------------------------------------------------------
/**
 * @brief   渡されたユニオン見た目コードからフィールドOBJのキャラを転送する
 *
 * @param   id		
 * @param   view		
 * @param   sex		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransFieldObjData( NNSG2dCharacterData *CharaData[2], NNSG2dPaletteData *PalData[2], int id, int view, int sex )
{
	int pos;
	u8 *chara, *pal;
	
	// ユニオンキャラを転送

	pos   = UnionView_GetCharaNo( sex, view );

	chara = (u8*)CharaData[1]->pRawData;
	pal   = (u8*)PalData[1]->pRawData;

	GX_LoadOBJ( &chara[OBJ_TRANS_SIZE*pos*0x20], obj_offset[id], OBJ_TRANS_SIZE*0x20 );
	GX_LoadOBJPltt( &pal[pos*32], (id+FIELDOBJ_PAL_START)*32, 32 );

	OS_Printf("ID=%d のユニオン見た目は %d アイコン番号は %d\n", id, view, pos);

	
	
}

//------------------------------------------------------------------
/**
 * @brief   フィールドOBJ画像解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeFieldObjData( RECORD_WORK *wk )
{

	sys_FreeMemoryEz( wk->FieldObjPalBuf[0]  );
	sys_FreeMemoryEz( wk->FieldObjPalBuf[1]  );
                      
	sys_FreeMemoryEz( wk->FieldObjCharaBuf[0] );
	sys_FreeMemoryEz( wk->FieldObjCharaBuf[1] );
}

//------------------------------------------------------------------
/**
 * @brief   会話スピードを取得
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetTalkSpeed( RECORD_WORK *wk )
{
	return 1;
//	return CONFIG_GetMsgPrintSpeed(wk->param->config);
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
static void ChangeConnectMax( RECORD_WORK *wk, int plus )
{
	if(CommGetCurrentID()==0){
		if(plus == -1){
			CommStateSetLimitNum(1);
			OS_Printf("接続人数を強制的に1人に変更\n");
		}
		else{
			int num = CommGetConnectNum()+plus;
			if(num>5){
				num = 5;
			}
			CommStateSetLimitNum(num);
			OS_Printf("接続人数を %d人に変更\n",num);
		}
		
		if(plus == -1){
			wk->limit_mode = LIMIT_MODE_ONLY;
		}
		else if(plus == 0){
			wk->limit_mode = LIMIT_MODE_TRUE;
		}
		else{
			wk->limit_mode = LIMIT_MODE_NONE;
		}
	}

}


//------------------------------------------------------------------
/**
 * @brief   募集人数とビーコン情報を設定する
 *
 * @param   wk		
 * @param   plus	1なら募集したい時、0なら締め切りたいとき
 *
 * @retval  none
 */
//------------------------------------------------------------------
static int RecordCorner_BeaconControl( RECORD_WORK *wk, int plus )
{
	int num;
	// ビーコンを書き換える
	num = MyStatusGetNum();

	if(num>wk->shareNum){
		u8 flag = RECORD_BAN_ON;
		// 離脱禁止解除通達
		CommSendData( CR_RECORD_BAN, &flag, 1 );
		wk->beacon_flag = RECORD_BAN_ON;
	}
	else{
		wk->beacon_flag = RECORD_BAN_NONE;
	}

	// 接続人数とレコード交換可能人数が一致するまでは操作禁止
	if(num==wk->connectBackup){
		return SEQ_MAIN;
	}

	OS_TPrintf("人数が変わった\n");

	// 上限じゃない、かつ締め切りでもないなら募集続行
	switch(num){
	case 1:
		// ひとりになったので終了
		OS_TPrintf("ONLY!! Comm = %d, My = %d, Bit = %d\n", CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		if(CommGetConnectNum() > 1 || WH_GetBitmap() > 1){
			return SEQ_MAIN;	//完全に一人にはなっていないのでまだ何もしない
		}
		wk->seq = RECORD_MODE_END_PARENT_ONLY;
		ChangeConnectMax( wk, -1 );
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		return SEQ_LEAVE;
		break;
	case 2:	case 3:case 4:
		// まだ入れるよ
		Union_BeaconChange( UNION_PARENT_MODE_RECORD_FREE );

		// 接続人数が減った場合は接続最大人数も減らす
		if(num<wk->connectBackup){
			switch(wk->limit_mode){
			case LIMIT_MODE_NONE:
				ChangeConnectMax( wk, plus );
				break;
			case LIMIT_MODE_TRUE:
				ChangeConnectMax(wk, 0);
				break;
			}
			wk->shareNum = CommGetConnectNum();
		}
		break;
	case 5:
		// いっぱいです
		Union_BeaconChange( UNION_PARENT_MODE_RECORDNOW );
		ChangeConnectMax( wk, plus );
		break;
	}

	
	// 接続人数を保存
	wk->connectBackup = MyStatusGetNum();

	return SEQ_MAIN;
}