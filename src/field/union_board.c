
//===========================================================================
/**
 *
 *@file		union_board.c
 *@brief	ユニオンルーム掲示板表示処理（サブ画面）
 *@author	Akito Mori
 *@data		2006.02.03
 *
 */
//===========================================================================

#ifdef PM_DEBUG
//#define UNIONBOARD_DEBUG
#endif

#include "common.h"
#include "gflib/touchpanel.h"


#include "system/lib_pack.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_overlay.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/pm_str.h"
#include "gflib/strbuf_family.h"

#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_word.h"
#include "system/wordset.h"
#include "system/msgdata.h"
#include "system/msgdata_util.h"

#include "savedata/friendlist.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_union.h"

#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "talk_msg.h"

#include "communication/communication.h"
#include "underground/ug_manager.h"
#include "comm_player.h"
#include "unionroom.naix"
#include "union_board.h"

#include "comm_union.h"
#include "comm_union_view.h"
#include "comm_union_view_def.h"
#include "comm_union_beacon.h"


FS_EXTERN_OVERLAY(unionroom_board);


struct _STRBUF {
	u16  size;			///< 配列サイズ
	u16  strlen;		///< 文字列長（EOMを含まない）
	u32  magicNumber;	///< 正常に初期化済みであることをチェックするためのナンバー

	STRCODE  buffer[1];	///< 配列本体
};

//========================================================================================
// 定数宣言
//========================================================================================

#define UNION_BOARD_RESOURCE_ID	( 999 ) // 下画面のリソースＩＤを衝突しないようにするために1000とする


// CellActorに処理させるリソースマネージャの数（＝マルチセル・マルチセルアニメは使用しない）
#define CELL_ANIME_RESOURCE_NUM		(4)

// ユニオンボードに表示するOBJの数
#define UNION_BOARD_OBJ_PARTS_NUM	(3)	

// 炭鉱レーダーのタスクの優先順位（通信よりは下にいる必要とかあると思うので）
#define UNION_BOARD_TCB_PRIORITY	(4)

// 下画面に表示する簡易会話の数
#define UNION_BOARD_CARD_NUM		( 3 )

#define UNION_BOARD_CLACT_MAX			( 10 )

#define MESSAGE_NONE		( 0 )
#define MESSAGE_WAIT		( 1 )
#define MESSAGE_END			( 2 )


#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ

// -----炭鉱レーダー処理のシーケンス定義---------
enum{
	UNIONBOARD_INIT_BG = 0,
	UNIONBOARD_INIT_ACTOR,
	UNIONBOARD_MAIN,
	UNIONBOARD_END,
};



//========================================================================================
// 構造体宣言
//========================================================================================
typedef struct{
	u16 max;
	u16 old_max;
	u16 now;
	u16 barflag;
}UNION_SCROLL;

typedef struct{
	GF_BGL_BMPWIN	bName;							// 名前描画ビットマップ
	GF_BGL_BMPWIN	bMessage;						// 簡易会話描画ビットマップ
	GF_BGL_BMPWIN	bFriend;						// しりあい告知ビットマップ
	int				sex;							// 貼り付けるカードの背景
	int				push;							// 押し込まれ状態
}UNION_BOARD_BMP;

struct UNION_BOARD_WORK{
	int           			mode;									//シーケンス遷移

	COMM_UNIONROOM_VIEW 	*cuv;
	COMM_UNIONROOM_WORK     *union_work;
	FIELDSYS_WORK 			*fsys;									// フィールドから引き継ぐシステムポインタ
	MYSTATUS				*mystatus;
	GF_BGL_INI    			*bgl;									// フィールドから引き継ぐＢＧシステムポインタ
	

	WORDSET					*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER 		*MsgManager;							// メッセージデータマネージャー

	u16			  	 		*Bg1ScrenData;							// BG1書き換え用スクリーンデータ実体
	NNSG2dScreenData 		*BoardScreen;							// BG1書き換え用スクリーンデータアドレス

	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CELL_ANIME_RESOURCE_NUM];		// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[CELL_ANIME_RESOURCE_NUM];		// リソースオブジェテーブル
	CLACT_HEADER			clActHeader;							// セルアクターヘッダー

	CLACT_WORK_PTR			clActWork[COMM_MACHINE_MAX];			// セルアクターワークポインタ配列(主人公）
	int						MesIndex;								// メッセージインデックス
	int						TalkMode;
	int						Wait;
	int						lastHitTrg;

	UNION_BOARD_BMP			UnionBmp[3];
	UNION_CHAT_RINGBUF		*UnionChatRingBuf;

	UNION_SCROLL			Scroll;
	int						old_scrollpoint;
	int						old_winanime;

	BOOL					BgTransReq;

	TCB_PTR					tcb;	
};


#ifdef PM_DEBUG
static UNION_BOARD_WORK *debug_ubw;
#endif

//========================================================================================
// プロトタイプ宣言
//========================================================================================
static void InitWork( UNION_BOARD_WORK *ubw );
static void destBG(GF_BGL_INI* bgl);
static void initBG( GF_BGL_INI *bgl );
static void InitCellActor(UNION_BOARD_WORK *ubw);
static void SetCellActor( UNION_BOARD_WORK *ubw );

static void BmpWinInit( GF_BGL_INI *bgl, UNION_BOARD_BMP *UnionBmp);
static void BmpWinDelete( UNION_BOARD_BMP *UnionBmp );

extern void FieldMsgPrintInitSub(void);
extern void FldTalkBmpAddSub( GF_BGL_INI * ini, GF_BGL_BMPWIN * win );


static void UnionChatInit( UNION_CHAT *chat);
static void UnionChatAllocInit( UNION_CHAT_RINGBUF *chatbuf);
static void UnionChatFree(UNION_CHAT *chat);
static void UnionChatAllFree( UNION_CHAT_RINGBUF *chatbuf);

static void BoardWriteFunc( UNION_BOARD_WORK *ubw );
static void UnionChat_Print( UNION_BOARD_WORK *ubw, int no,  UNION_CHAT *mes);
static void TouchPanelFunc( UNION_BOARD_WORK *ubw );
static void ScrollControl( UNION_BOARD_WORK *ubw );
static void SetScrollBar_PosY( CLACT_WORK_PTR act, int y );
static void GetUnionChat( UNION_BOARD_WORK *ubw );
static void AddUnionChatPmsData( UNION_BOARD_WORK *ubw, u32 id, PMS_DATA *pms, MYSTATUS *mystatus );
static int UnionChatRegisterCheck(UNION_BOARD_WORK *ubw, PMS_DATA *pms, int id);
static int AddUnionChatRingBufPos( UNION_CHAT_RINGBUF *chatbuf, int pos );
static int GetUnionBoardPrintPoint( int start, int now );
static int  TouchTrgFunc( UNION_BOARD_WORK *ubw );
static int  TouchContFunc( UNION_BOARD_WORK *ubw );



static void UnionBoardReWriteOn( UNION_BOARD_WORK *ubw);
static void UnionBoard_AddChatSub( UNION_BOARD_WORK *ubw, MYSTATUS *status, PMS_DATA *pms, u32 id );
static STRBUF *FriendLinkStringGet(FRIEND_LIST *friendlist, u32 id, WORDSET *wordset, MSGDATA_MANAGER *msgdata, MYSTATUS *my);
static void ChatButtonAnimation( GF_BGL_INI *bgl, NNSG2dScreenData *Screen, UNION_BOARD_BMP *Board, int button, int num, int *old);



//------------------------------------------------------------------
/**
 * 炭鉱レーダーメイン（タスク関数）
 *
 * @param   tcb		タスクポインタ
 * @param   wk		ワークポインタ(UG_RADAR_WORKとしてキャストして使う）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionRoom_BoardFunc(TCB_PTR tcb, void *wk)
{
	UNION_BOARD_WORK *ubw = wk;
	GF_BGL_INI       *bgl = ubw->bgl;
	int i;

	// ユニオンルームから主人公が飛んでいくとユニオン用のワークが消滅してしまうので予防線
	if(ubw->fsys->union_view==NULL){
		return;
	}

	switch(ubw->mode){
	case UNIONBOARD_INIT_BG:
		// BG初期化・VRAM転送
		OS_Printf("start unionboard = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
		OS_Printf("underground  work= %ld\n",sizeof(UNION_BOARD_WORK));

		initBG( bgl );

		// レーダー用配列初期化
		InitWork( ubw );
//		UnionChatAllocInit( &ubw->UnionChatRingBuf );

#ifdef PM_DEBUG
		debug_ubw = ubw;

#endif
	
		ubw->mode++;
		break;
	case UNIONBOARD_INIT_ACTOR:

		InitCellActor(ubw);
		SetCellActor(ubw);
		FontProc_LoadBitData(FONT_TALK, HEAPID_FIELD);


		BmpWinInit( ubw->bgl, ubw->UnionBmp );

		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		UnionBoardReWriteOn( ubw );
		ubw->mode++;
		break;
	// メインシーケンス
	case UNIONBOARD_MAIN:
		GetUnionChat( ubw );
		ScrollControl( ubw );
		TouchPanelFunc( ubw );

#ifdef UNIONBOARD_DEBUG
		if(sys.trg&PAD_BUTTON_Y){
			int r;
			for(i=0;i<ubw->UnionChatRingBuf->num;i++){
				OS_TPrintf("----chat no %d\n",i);
				OS_TPrintf("name ");
				for(r=0;r<6;r++){
					OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].name->buffer[r]);
				}
				OS_TPrintf("\nmessage ");
				for(r=0;r<6;r++){
					OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].message->buffer[r]);
				}
				OS_TPrintf("\nfriend ");
				if(ubw->UnionChatRingBuf->mes[i].friend!=NULL){
					for(r=0;r<6;r++){
						OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].friend->buffer[r]);
					}
				}else{
					OS_TPrintf("\n");
				}
				
				OS_TPrintf("\nid = %08x, sex = %d \n", ubw->UnionChatRingBuf->mes[i].id, ubw->UnionChatRingBuf->mes[i].sex);

				OS_TPrintf("PmsData ");
				OS_TPrintf("type %d, id %d, word0 %d, word1 %d\n", 
								ubw->UnionChatRingBuf->mes[i].PmsData.sentence_type,
								ubw->UnionChatRingBuf->mes[i].PmsData.sentence_id,
								ubw->UnionChatRingBuf->mes[i].PmsData.word[0],
								ubw->UnionChatRingBuf->mes[i].PmsData.word[1]
				);
			}
		}
		if(sys.trg & PAD_BUTTON_L){
			OS_TPrintf(" HEAPID_BASE_SYSTEM = %x\n",sys_GetHeapFreeSize( HEAPID_BASE_SYSTEM ));	
			OS_TPrintf(" HEAPID_BASE_APP = %x\n",   sys_GetHeapFreeSize( HEAPID_WORLD ));	
			OS_TPrintf(" HEAPID_WORLD = %x\n",   sys_GetHeapFreeSize( HEAPID_WORLD ));	
			OS_TPrintf(" HEAPID_UNIONBoARD = %x\n",   sys_GetHeapFreeSize( HEAPID_UNIONBOARD ));	
		}
		
		if(sys.trg & PAD_BUTTON_DEBUG){
			WMBssDesc         *beacon;
			_GF_BSS_DATA_INFO *gfinfo;
			int i;
			
			OS_TPrintf("now beacon =\n");
			for(i=0;i<10;i++){
				beacon = CommMPGetWMBssDesc(i);	
				if(beacon!=NULL){		// ビーコンが取れなかったらスルー
					gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
					OS_TPrintf( "%08x,  ", gfinfo->pokeID);
				}
			}
			OS_TPrintf("\n");
			Debug_FriendListAllPrint( SaveData_GetFriendList(ubw->fsys->savedata) );
		}

		if(sys.trg & PAD_BUTTON_SELECT){
			PMS_DATA pmsdata;
			PMSDAT_SetDebugRandom( &pmsdata );
			Union_SetMyPmsData( ubw->union_work, &pmsdata );		// ユニオンワークで保存しておき下画面に表示させる
		}

#endif
		BoardWriteFunc( ubw );

		CLACT_Draw( ubw->clactSet );									// セルアクター常駐関数
		break;

	case UNIONBOARD_END:
		break;

	}
}

// 名前表示ＢＭＰ定義
#define NAME_BMPWIN_W			(  8 )
#define NAME_BMPWIN_H			(  2 )

#define NAME_BMPWIN_POSX		(  1 )
#define NAME0_BMPWIN_POSY		(  1 )

// 簡易会話表示ＢＭＰ定義
#define MESSAGE_BMPWIN_W		( 27 )
#define MESSAGE_BMPWIN_H		(  5 )

#define MESSAGE_BMPWIN_POSX		(  2 )
#define MESSAGE0_BMPWIN_POSY	(  3 )

// しりあい告知ＢＭＰ定義
#define FRIEND_BMPWIN_W		( 15 )
#define FRIEND_BMPWIN_H		(  2 )

#define FRIEND_BMPWIN_POSX		( 12 )
#define FRIEND_BMPWIN_POSY		(  1 )




#define UNION_BOARD_BGCHAR_OFFSET	( 32*5 )
#define UNION_NAME_BMP_SIZE         ( NAME_BMPWIN_W*NAME_BMPWIN_H )
#define UNION_CHAT_BMP_SIZE  	    ( MESSAGE_BMPWIN_W * MESSAGE_BMPWIN_H )
#define UNION_FRIEND_BMP_SIZE   	( FRIEND_BMPWIN_W  * FRIEND_BMPWIN_H )

#define UNION_BOARD_NAMECHAR_OFFSET   ( UNION_BOARD_BGCHAR_OFFSET + UNION_NAME_BMP_SIZE*3 )
#define UNION_BOARD_FRIENDCHAR_OFFSET ( UNION_BOARD_NAMECHAR_OFFSET + UNION_CHAT_BMP_SIZE*3 )

//------------------------------------------------------------------
/**
 * ユニオンボードワーク初期化
 *
 * @param   pos[][POS_XZ]			
 * @param   view[][POS_XZ_TIME]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( UNION_BOARD_WORK *ubw )
{
	int i;
	ubw->BgTransReq = FALSE;

	ubw->Scroll.max     = 0;
	ubw->Scroll.old_max = 0;
	ubw->Scroll.now     = 0;
	ubw->Scroll.barflag = 0;


	// 文字列マネージャー初期化
	ubw->WordSet    = WORDSET_Create( HEAPID_FIELD );
	ubw->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_union_dat, HEAPID_FIELD );


	// 加工用BG1データ読み込み
	ubw->Bg1ScrenData = ArcUtil_ScrnDataGet(ARC_UNIONROOM_GRA, NARC_unionroom_unionbg1_lz_nscr, 1, &(ubw->BoardScreen), HEAPID_FIELD);
	OS_Printf( "bg1srcreen data adrs = %08x\n",ubw->BoardScreen);


}


//------------------------------------------------------------------
/**
 * $brief   BMPWIN確保
 *
 * @param   bgl		
 * @param   UnionBmp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( GF_BGL_INI *bgl, UNION_BOARD_BMP *UnionBmp)
{
	// 下画面ボタン用BMP確保
	int i;

	for(i=0;i<UNION_BOARD_CARD_NUM;i++){
		// 名前
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bName, GF_BGL_FRAME0_S+i,	
			NAME_BMPWIN_POSX, 
			NAME0_BMPWIN_POSY+i*8, 
			NAME_BMPWIN_W, 
			NAME_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_BGCHAR_OFFSET + i * UNION_NAME_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bName, 0x0000 );

		GF_BGL_BmpWinOn( &UnionBmp[i].bName );

		// 簡易会話
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bMessage, GF_BGL_FRAME0_S+i,	
			MESSAGE_BMPWIN_POSX, 
			MESSAGE0_BMPWIN_POSY+i*8, 
			MESSAGE_BMPWIN_W, 
			MESSAGE_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_NAMECHAR_OFFSET + i * UNION_CHAT_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bMessage, 0x0000 );
		GF_BGL_BmpWinOn( &UnionBmp[i].bMessage );

		// しりあい会話
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bFriend, GF_BGL_FRAME0_S+i,	
			FRIEND_BMPWIN_POSX, 
			FRIEND_BMPWIN_POSY+i*8, 
			FRIEND_BMPWIN_W, 
			FRIEND_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_FRIENDCHAR_OFFSET + i * UNION_FRIEND_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bFriend, 0x0000 );
		GF_BGL_BmpWinOn( &UnionBmp[i].bFriend );
		
	}

	OS_Printf(" CHAT_BOARD BMP End = %d\n ",UNION_BOARD_FRIENDCHAR_OFFSET + i * UNION_FRIEND_BMP_SIZE);
	OS_Printf("heap remain = %d\n",sys_GetHeapFreeSize( HEAPID_FIELD ));

}

//------------------------------------------------------------------
/**
 * $brief   BMPWIN解放
 *
 * @param   UnionBmp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( UNION_BOARD_BMP *UnionBmp )
{
	int i;
	for(i=0;i<UNION_BOARD_CARD_NUM;i++){
		GF_BGL_BmpWinDel( &UnionBmp[i].bMessage );
		GF_BGL_BmpWinDel( &UnionBmp[i].bName );
		GF_BGL_BmpWinDel( &UnionBmp[i].bFriend );
	}
}


//==============================================================================
/**
 * 炭鉱レーダー初期化関数（タスク登録）
 *
 * @param   fsys		FIELDSYS_WORKのポインタ
 *
 * @retval  none		
 */
//==============================================================================
UNION_BOARD_WORK *UnionRoom_BoardInit( FIELDSYS_WORK *fsys )
{
	UNION_BOARD_WORK *ubw;
	TCB_PTR       tcb;

	//炭鉱レーダータスクを追加
	tcb           = PMDS_taskAdd(UnionRoom_BoardFunc, sizeof(UNION_BOARD_WORK), UNION_BOARD_TCB_PRIORITY, HEAPID_FIELD);
	ubw           = TCB_GetWork(tcb);
	ubw->fsys     = fsys;
	ubw->bgl      = fsys->bgl;
	ubw->cuv      = fsys->union_view;
	ubw->union_work = fsys->union_work;
	ubw->mystatus = SaveData_GetMyStatus(fsys->savedata);
	ubw->mode     = 0;
	ubw->tcb      = tcb;

	
	ubw->UnionChatRingBuf = fsys->union_view->unionBoardChat;
//	ubw->UnionChatRingBuf = UnionBoard_ChatAllocInit( HEAPID_FIELD );
	

	return ubw;
}

//==============================================================================
/**
 * レーダー画面終了を通知
 *
 * @param   fsys		FieldSysのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void UnionRoom_BoardEnd(UNION_BOARD_WORK *ubw)
{
	// レーダーのシーケンス定義を終了に変更
	if(ubw->mode==UNIONBOARD_MAIN){
		GF_BGL_INI       *bgl = ubw->bgl;
		int i;

		ubw->mode = UNIONBOARD_END;

		FontProc_UnloadBitData( FONT_TALK );

		// キャラ転送マネージャー破棄
		CLACT_U_CharManagerDelete(ubw->resObjTbl[CLACT_U_CHAR_RES]);

		// パレット転送マネージャー破棄
		CLACT_U_PlttManagerDelete(ubw->resObjTbl[CLACT_U_PLTT_RES]);
		
		// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
		for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){
			CLACT_U_ResManagerDelete(ubw->resMan[i]);
		}
		// セルアクターセット破棄
		CLACT_DestSet(ubw->clactSet);

		// 文字列マネージャー破棄
		MSGMAN_Delete(  ubw->MsgManager );
		WORDSET_Delete( ubw->WordSet );

		//BmpWin解放
		BmpWinDelete( ubw->UnionBmp );				

		destBG(bgl);											// BG0,BG1用バッファ解放

//		UnionChatAllFree( ubw->UnionChatRingBuf);
//		UnionBoard_ChatDataDelete( ubw->UnionChatRingBuf );
		sys_FreeMemoryEz( ubw->Bg1ScrenData );

		PMDS_taskDel( ubw->tcb );

	}else{
		GF_ASSERT("レーダー初期化が終わらないうちに終了呼び出しされました");
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief 地下画面に突入するまでのサブ画面ＢＧのシステムを破棄
 *
 *@param	bgl		BGLシステム構造体のポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destBG(GF_BGL_INI* bgl)
{
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME1_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_S);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	BGコントロール設定
 *
 *@param	bgl	BGLシステムのポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBG( GF_BGL_INI* bgl )
{
	// 今までの破棄
	destBG(bgl);

	// サブ面BG設定
	// BG0面（テキスト0）
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME0_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	}
	// BG1面（テキスト1）
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME1_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}

	// BG2面（テキスト1）
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME2_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	}

	// BG3面（背景）
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME3_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	// パレット転送
	ArcUtil_PalSet(    ARC_UNIONROOM_GRA, NARC_unionroom_unionbg_nclr, PALTYPE_SUB_BG, 0, 0x20*3,  HEAPID_FIELD);

	// キャラ転送(転送キャラの指定がBGCHAR_OFFSETになっているのは、BGのVRAMから転送しているから）
	ArcUtil_BgCharSet( ARC_UNIONROOM_GRA, NARC_unionroom_unionbg_lz_ncgr, bgl, GF_BGL_FRAME3_S, 0, UNION_BOARD_BGCHAR_OFFSET*0x20, 1, HEAPID_FIELD);

	// スクリーン転送
	ArcUtil_ScrnSet(   ARC_UNIONROOM_GRA, NARC_unionroom_unionbg1_base_lz_nscr, bgl, GF_BGL_FRAME3_S, 0, 32*24*2, 1, HEAPID_FIELD);

	FieldMsgPrintInit(PALTYPE_SUB_BG, MSG_PRINT_NO_INIT);				// サブ画面VRAMにフォントとパレットを転送

}



//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   ubw		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(UNION_BOARD_WORK *ubw)
{
	int i;
	// セルアクター初期化
	ubw->clactSet = CLACT_U_SetEasyInit( UNION_BOARD_CLACT_MAX, &ubw->renddata, HEAPID_FIELD );
	
	//リソースマネージャー初期化
	for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){		//リソースマネージャー作成
		ubw->resMan[i] = CLACT_U_ResManagerInit(1, i, HEAPID_FIELD);
	}

	
	//chara読み込み
	ubw->resObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(ubw->resMan[CLACT_U_CHAR_RES], 
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_ncgr, 1, UNION_BOARD_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_FIELD);

	//pal読み込み
	ubw->resObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(ubw->resMan[CLACT_U_PLTT_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_nclr, 0, UNION_BOARD_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, 1, HEAPID_FIELD);

	//cell読み込み
	ubw->resObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(ubw->resMan[CLACT_U_CELL_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_ncer, 1, UNION_BOARD_RESOURCE_ID, CLACT_U_CELL_RES,HEAPID_FIELD);

	//同じ関数でanim読み込み
	ubw->resObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(ubw->resMan[CLACT_U_CELLANM_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_nanr, 1, UNION_BOARD_RESOURCE_ID, CLACT_U_CELLANM_RES,HEAPID_FIELD);

	// Chara転送
	CLACT_U_CharManagerSetAreaCont( ubw->resObjTbl[CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSetCleanArea( ubw->resObjTbl[CLACT_U_PLTT_RES] );

}

#define UNION_ARROW_X			(256-24)
#define UNION_ARROW_UP_Y		(     0)
#define UNION_ARROW_DOWN_Y		(192-8*4)
#define UNION_ARROW_SCROLL_Y	(192/2)

static const int obj_parts_table_y[]={
		UNION_ARROW_UP_Y	,
		UNION_ARROW_DOWN_Y	,
		UNION_ARROW_SCROLL_Y,
};


//------------------------------------------------------------------
/**
 * $brief   セルアクター配置
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor( UNION_BOARD_WORK *ubw )
{
	int i;
		// セルアクターヘッダ作成
		CLACT_U_MakeHeader(&ubw->clActHeader, 
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
							0, 0,
							ubw->resMan[CLACT_U_CHAR_RES],
							ubw->resMan[CLACT_U_PLTT_RES],
							ubw->resMan[CLACT_U_CELL_RES],
							ubw->resMan[CLACT_U_CELLANM_RES],
							NULL,NULL);

		{
			//登録情報格納
			CLACT_ADD add;

			add.ClActSet	= ubw->clactSet;
			add.ClActHeader	= &ubw->clActHeader;

			add.mat.z		= 0;
			add.sca.x		= FX32_ONE;
			add.sca.y		= FX32_ONE;
			add.sca.z		= FX32_ONE;
			add.rot			= 0;
			add.pri			= 0;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			add.heap		= HEAPID_FIELD;

			//セルアクター表示開始

			// 上下矢印スクロールバー登録
			for(i=0;i<UNION_BOARD_OBJ_PARTS_NUM;i++){
				add.mat.x		= FX32_CONST( UNION_ARROW_X ) ;
				add.mat.y		= FX32_CONST( obj_parts_table_y[i] ) + SUB_SURFACE_Y;		//画面は上下連続している（MAINが上、SUBが下）
				ubw->clActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(ubw->clActWork[i],1);
				CLACT_AnmChg( ubw->clActWork[i], i );	//各々の姿に
			}
//			CLACT_SetDrawFlag(ubw->clActWork[2], 0);	//スクロールバーは非表示に
			
		}	

}





//------------------------------------------------------------------
/**
 * $brief   リングバッファ内で参照点の足し算を行う
 *
 * @param   chatbuf		
 * @param   pos		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int AddUnionChatRingBufPos( UNION_CHAT_RINGBUF *chatbuf, int pos )
{
	pos++;
	if(pos==UNION_CHAT_MAX){
		pos = 0;
	}

	return pos;
}

//------------------------------------------------------------------
/**
 * $brief   リングバッファを考慮したチャット表示開始位置取得
 *
 * @param   start		
 * @param   now		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetUnionBoardPrintPoint( int start, int now )
{
	int result = start+now;
	if(result>=UNION_CHAT_MAX){
		result -= UNION_CHAT_MAX;
	}
	return result;
}
//------------------------------------------------------------------
/**
 * $brief   名前を簡易会話を描画
 *
 * @param   ubw		
 * @param   no		
 * @param   mes		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionChat_Print( UNION_BOARD_WORK *ubw, int no, UNION_CHAT *mes)
{

	// カード用に性別を保存
	ubw->UnionBmp[no].sex = mes->sex;

	OS_Printf("カード描画\n");

	// スクリーン加工転送(性別に対応して青か赤になる）
	GF_BGL_ScrWriteExpand(	ubw->bgl, GF_BGL_FRAME3_S, 0, no*8, 32, 8,
			ubw->BoardScreen->rawData, 0, 24*ubw->UnionBmp[no].sex, 32, 48 );

	// BMP用バッファクリア
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bName,    0x0000 );
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bMessage, 0x0000 );
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bFriend,  0x0000 );
	
	// 文字列描画
	GF_STR_PrintColor( &ubw->UnionBmp[no].bName,    FONT_TALK, mes->name,    0, 2, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );
	GF_STR_PrintColor( &ubw->UnionBmp[no].bMessage, FONT_TALK, mes->message, 0, 6, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );

	// VRAMにvBlank中に転送
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bName    );
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bMessage );

	if(mes->friend){
		GF_STR_PrintColor( &ubw->UnionBmp[no].bFriend, FONT_TALK, mes->friend, 0, 2, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );
	}
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bFriend );
}

//------------------------------------------------------------------
/**
 * $brief   ユニオンボード描画常駐関数
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BoardWriteFunc( UNION_BOARD_WORK *ubw )
{
	int i,r;
	int pos = GetUnionBoardPrintPoint( ubw->UnionChatRingBuf->start, ubw->Scroll.now );
	int max = ubw->UnionChatRingBuf->num;
	
	if(max>3){
		max = 3;
	}

	// スクロールバーの位置が動いていた場合は再描画
	if(ubw->Scroll.now!=ubw->old_scrollpoint){
		UnionBoardReWriteOn( ubw );
		ubw->old_scrollpoint = ubw->Scroll.now;
	}

	// 簡易会話描画
	if(ubw->BgTransReq==TRUE){
//		OS_Printf( "pos=%d, bufnum=%d bufstart=%d now=%d",pos, ubw->UnionChatRingBuf.num, ubw->UnionChatRingBuf.start, ubw->Scroll.now);

		
		// 簡易会話描画
		for(i=0;i<max;i++){
			UnionChat_Print(ubw, i, &ubw->UnionChatRingBuf->mes[pos]);
			pos = AddUnionChatRingBufPos(ubw->UnionChatRingBuf,pos);
		}
		DC_FlushRange((void*)GF_BGL_ScreenAdrsGet( ubw->bgl, GF_BGL_FRAME3_S ), 32*24*2);
		GF_BGL_LoadScreen(	ubw->bgl, GF_BGL_FRAME3_S, GF_BGL_ScreenAdrsGet( ubw->bgl, GF_BGL_FRAME3_S ), 32*24*2, 0 );

		ubw->BgTransReq = FALSE;

	}

}

// 下画面用ボタン位置定義
#define SUB_BUTTON1_POSX		( 256-24   )
#define SUB_BUTTON1_POSY		( 0        )
#define SUB_BUTTON2_POSX		( 256-24   )
#define SUB_BUTTON2_POSY		( 192-8*4  )
#define SUB_BUTTON_W			( 8*2 )
#define SUB_BUTTON_H			( 8*4 )
#define SUB_SCROLLBAR_POSX		( 256-24   )
#define SUB_SCROLLBAR_POSY		( 8*4+16  )
#define SUB_SCROLLBAR_W			( 24  )
#define SUB_SCROLLBAR_H			( 192-8*8-16*2  )

#define SUB_CHAT_POSX			(  0 )
#define SUB_CHAT1_POSY			(  0 )
#define SUB_CHAT2_POSY			( 8*8)
#define SUB_CHAT3_POSY			(16*8)
#define SUB_CHAT_W				(29*8)
#define SUB_CHAT_H				( 8*8)


static const RECT_HIT_TBL sub_button_hittbl[]={
	{SUB_BUTTON1_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON1_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
	{SUB_BUTTON2_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON2_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
	{SUB_CHAT1_POSY, SUB_CHAT1_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT2_POSY, SUB_CHAT2_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT3_POSY, SUB_CHAT3_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_SCROLLBAR_POSY, SUB_SCROLLBAR_POSY+SUB_SCROLLBAR_H, SUB_SCROLLBAR_POSX, SUB_SCROLLBAR_POSX+SUB_SCROLLBAR_W},
	{RECT_HIT_END,0,0,0},		// 終了データ
};

static const RECT_HIT_TBL sub_scroll_hittbl[]={
	{SUB_SCROLLBAR_POSY, SUB_SCROLLBAR_POSY+SUB_SCROLLBAR_H, SUB_SCROLLBAR_POSX, SUB_SCROLLBAR_POSX+SUB_SCROLLBAR_W},
	{SUB_CHAT1_POSY, SUB_CHAT1_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT2_POSY, SUB_CHAT2_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT3_POSY, SUB_CHAT3_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{RECT_HIT_END,0,0,0},		// 終了データ
};

//------------------------------------------------------------------
/**
 * $brief   スクロールバーの座標を設定する
 *
 * @param   act		アクターのポインタ
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetScrollBar_PosY( CLACT_WORK_PTR act, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( SUB_SCROLLBAR_POSX );
	mat.y = FX32_CONST( y ) + SUB_SURFACE_Y;
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}

//------------------------------------------------------------------
/**
 * $brief   スクロールバー周りの処理
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ScrollControl( UNION_BOARD_WORK *ubw )
{

	ubw->Scroll.max = ubw->UnionChatRingBuf->num;

	// 項目数が４以上になったらスクロールバーを表示する(減る事はないだろうけど）
	if(ubw->Scroll.max > 3 && ubw->Scroll.old_max<=3){
		ubw->Scroll.barflag = 1;
		ubw->Scroll.now            = 0;
	}
	CLACT_SetDrawFlag(ubw->clActWork[2], ubw->Scroll.barflag);	//スクロールバー表示制御
	
	if( ubw->Scroll.barflag ){
		if(!GF_TP_GetCont()){
			int haba,y;
			y    = SUB_SCROLLBAR_POSY + (ubw->Scroll.now * SUB_SCROLLBAR_H) / (ubw->Scroll.max-3);
			SetScrollBar_PosY( ubw->clActWork[2],y );
//			OS_Printf("y=%d, haba=%d, now=%d max=%d\n",y,haba,ubw->Scroll.now, ubw->Scroll.max);
		}
	}
	ubw->Scroll.old_max = ubw->Scroll.max;
}	

//------------------------------------------------------------------
/**
 * @brief   タッチパネルのトリガー処理
 *
 * @param   ubw		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TouchTrgFunc( UNION_BOARD_WORK *ubw )
{
	int button,i,listpos;
	WMBssDesc         *beacon;
	_GF_BSS_DATA_INFO *gfinfo;

	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		switch(button){
		// 上矢印（上にウインドウを１つスクロール）
		case 0:
			CLACT_AnmChg( ubw->clActWork[button], button+4 );	//各々の姿に
			if(ubw->Scroll.now!=0){
				Snd_SePlay(SEQ_SE_DP_BUTTON3);
				ubw->Scroll.now--;
			}
			break;
		// 下矢印（下にウインドウを１つスクロール）
		case 1:
			CLACT_AnmChg( ubw->clActWork[button], button+4 );	//各々の姿に
			if(ubw->Scroll.now<ubw->Scroll.max-3){
				Snd_SePlay(SEQ_SE_DP_BUTTON3);
				ubw->Scroll.now++;
			}
			break;
		// スクロールバー
		case 5:
			break;

		// 上画面メンバーサーチ処理（ウインドウを触ると上で赤い枠）
		// 簡易会話ウインドウを押した
//		case 2:	case 3:	case 4:
		default:
			if(ubw->UnionChatRingBuf->num >= (button-1)){	// 受け取っている会話よりもボタンが大きいときは無視する

				listpos = GetUnionBoardPrintPoint( ubw->UnionChatRingBuf->start, ubw->Scroll.now )+button-2;

				// ビーコンのIDが一致して、かつ既に地面に立っているならばエフェクトON
			
				// １０人分の親機ビーコンを検索する
				for(i=0;i<10;i++){
					beacon = CommMPGetWMBssDesc(i);	
					if(beacon!=NULL){		// ビーコンが取れなかったらスルー
						gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
						// ビーコンのIDが一致して、かつ既に地面に立っているならばエフェクトON
//						OS_Printf("appear=%d, pokeID=%d, RingBufID=%d\n",ubw->cuv->objwork[i].appear,gfinfo->pokeID,ubw->UnionChatRingBuf.mes[listpos].id);
						if((ubw->cuv->objwork[i].appear==OBJ_OK) && (gfinfo->pokeID == ubw->UnionChatRingBuf->mes[listpos].id)){
							Snd_SePlay(SEQ_SE_DP_BUTTON3);
							ubw->cuv->objwork[i].effect = 1;
							break;
						}
					}
				}
				// 自分のチャット？
				{
					MYSTATUS *my = CommMPGetMyStatus();
					
					if(ubw->UnionChatRingBuf->mes[listpos].id == MyStatus_GetID(my)){
						Snd_SePlay(SEQ_SE_DP_BUTTON3);
						ubw->cuv->objwork[UNION_EFFECT_HERO_NO].effect = 1;
					}
				
				}

			}
			break;
		}
		ubw->lastHitTrg = button-2;
	}

	return button;
}

//------------------------------------------------------------------
/**
 * @brief   タッチパネルをドラッグするときの処理
 *
 * @param   ubw		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TouchContFunc( UNION_BOARD_WORK *ubw )
{
	int button;

	// スライドバー処理
	button=GF_TP_RectHitCont( sub_scroll_hittbl );
	if( button != RECT_HIT_NONE ){
		u32 x, y;
		switch(button){
		case 0:

			// タッチしている座標にスライドバーを座標設定
			GF_TP_GetPointCont( &x, &y );
			SetScrollBar_PosY( ubw->clActWork[2],y );
		
			// 一番近いメッセージ数分割位置のアタリも取得しておく
			if(ubw->Scroll.max>3){
				int haba,i;

				haba = SUB_SCROLLBAR_H / (ubw->Scroll.max-2);
				for(i=0;i<ubw->Scroll.max-2;i++){
					if( (y >= SUB_SCROLLBAR_POSY+haba*i) && (y < SUB_SCROLLBAR_POSY+haba*(i+1))){
						ubw->Scroll.now =i;
						break;
					}
				}
			}
			break;
		// 簡易会話ウインドウ
//		case 1: case 2: case 3:
		default:
			if(ubw->UnionChatRingBuf->num>=button){	// 受け取っている会話よりもボタンが大きいときは無視する

				// 押してなかったまたは同じボタンを押し続けているなら反応する
				if(ubw->lastHitTrg==(button-1)){	
					if(ubw->UnionBmp[button-1].push<2*2+1){
						ubw->UnionBmp[button-1].push++;
					}
				}
			}
			break;
		}
	}

	return button;
}


//------------------------------------------------------------------
/**
 * @brief   ＬＲボタンでチャットウインドウを動かす事ができる
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LR_ButtonFunc( UNION_BOARD_WORK *ubw )
{
	if(sys.trg & PAD_BUTTON_L){
		// 上矢印（下にウインドウを１つスクロール）と同じ機能
		CLACT_AnmChg( ubw->clActWork[0], 0+4 );
		if(ubw->Scroll.now!=0){
			ubw->Scroll.now--;
			Snd_SePlay(SEQ_SE_DP_BUTTON3);
		}
	}else if(sys.trg & PAD_BUTTON_R){
		// 下矢印（下にウインドウを１つスクロール）と同じ機能
		CLACT_AnmChg( ubw->clActWork[1], 1+4 );
		if(ubw->Scroll.now<ubw->Scroll.max-3){
			ubw->Scroll.now++;
			Snd_SePlay(SEQ_SE_DP_BUTTON3);
		}
	}

}
//------------------------------------------------------------------
/**
 * $brief   タッチパネル処理
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchPanelFunc( UNION_BOARD_WORK *ubw )
{
	int button=RECT_HIT_NONE;

	// イベント中でなければタッチパネルに反応する
	if(!FieldEvent_Check(ubw->fsys)){
		int check;
		check  = TouchTrgFunc( ubw );
		button = TouchContFunc( ubw );

		// タッチパネルにまったく触っていないならＬＲボタンの処理も呼び出す
		if(check==RECT_HIT_NONE && button == RECT_HIT_NONE){
			LR_ButtonFunc(ubw);
		}
	}
	

	// 簡易会話ウインドウボタンのアニメ処理（押されたらへこむ・離すと戻る）
	ChatButtonAnimation( ubw->bgl, ubw->BoardScreen, ubw->UnionBmp, button-1, ubw->UnionChatRingBuf->num, &ubw->old_winanime);
}


static const bg_src_anime_offset[]={0,3,5};

//------------------------------------------------------------------
/**
 * @brief   簡易会話ウインドウアニメ処理
 *
 * @param   bgl		
 * @param   Screen		
 * @param   Board		
 * @param   button		
 * @param   num		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChatButtonAnimation( GF_BGL_INI *bgl, NNSG2dScreenData *Screen, UNION_BOARD_BMP *Board, int button, int num, int *old)
{
	int i,tmp=0;
	if(num>3){
		num = 3;
	}
	
	for(i=0;i<num;i++){
		if(button!=i){
			if(Board[i].push!=0){
				Board[i].push--;
			}
		}
		tmp += Board[i].push;
//		OS_Printf("button %d = %d   ", i, Board[i].push);
	}
//	OS_Printf("\n");

	// 全部０だったら転送の必要はない(全部０だった次のフレームも転送する）
	if(tmp==0 && *old==0){
		*old = tmp;
		return;
	}
	// 前回のフレームのバックアップ
	*old = tmp;

	for(i=0;i<num;i++){
		int page = Board[i].push/2;

		// スクリーン加工転送
		GF_BGL_ScrWriteExpand( bgl, GF_BGL_FRAME3_S, 0, i*8, 32, 8,
			Screen->rawData, 0, 24*Board[i].sex+8*page, 32, 48 );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_Y_SET, bg_src_anime_offset[page] );

	}
	DC_FlushRange((void*)GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME3_S ), 32*24*2);

	GF_BGL_LoadScreen(	bgl, GF_BGL_FRAME3_S, GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME3_S ), 32*24*2, 0 );


//	OS_Printf("転送してる\n");

}

//------------------------------------------------------------------
/**
 * $brief   しりあいなら「○○○のともだち」という文字列をセット
 *
 * @param   fr		
 * @param   id		
 * @param   wordset		
 * @param   msgdata		
 *
 * @retval  STRBUF *		
 */
//------------------------------------------------------------------
static STRBUF *FriendLinkStringGet(FRIEND_LIST *friendlist, u32 id, WORDSET *wordset, MSGDATA_MANAGER *msgdata, MYSTATUS *my)
{
	STRBUF *string = NULL;
	STRBUF *name;
	int ret = 0;

	// しりあいか、しりあいのしりあいか検索
	if(id != MyStatus_GetID(my)){
		ret = FriendList_IdFullCheck( friendlist, id );
	}
	
	if(ret>0){
		if(ret==DIRECT_FRIEND){
			// 自分のしりあいだったら自分の名前を
			WORDSET_RegisterPlayerName( wordset, 0, my );
		}else if(ret>=INDIRECT_FRIEND){
			// 友達の知り合いだったらその友達の名前を
			int index = ret-INDIRECT_FRIEND;
			name = STRBUF_Create(10,HEAPID_UNIONBOARD);
			STRBUF_SetStringCode( name, FriendList_GetName(friendlist, index));
			WORDSET_RegisterWord( wordset, 0, name, 0, 0, FriendList_GetGroupListRegion( friendlist, index ) );
			STRBUF_Delete(name);
		}
		// 「○○○のともだち」
		string = MSGDAT_UTIL_AllocExpandString( wordset, msgdata, msg_union_friend_name01, HEAPID_UNIONBOARD );
	}
	return string;
}


//------------------------------------------------------------------
/**
 * $brief   UnionChat構造体に新しいデータを登録する
 *
 * @param   union_mes		
 * @param   id		
 * @param   pms		
 * @param   mystatus		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AddUnionChatPmsData( UNION_BOARD_WORK *ubw,	u32 id, PMS_DATA *pms, MYSTATUS *mystatus )
{
	UNION_CHAT_RINGBUF *chatbuf = ubw->UnionChatRingBuf;
	FRIEND_LIST *friendlist 	= ubw->cuv->friendlist;
	int *pos;

	OS_Printf("書き込み前 chat->num %d, chat->start %d\n", chatbuf->num, chatbuf->start);

	// チャットリングバッファの最大数まできている場合はスタート位置をずらしていく（リングバッファ処理）
	if(chatbuf->num==UNION_CHAT_MAX){	// MAX=30個
		pos = &chatbuf->start;
	}else{
		pos = &chatbuf->num;
	}
	
	// 既に簡易会話の文字列バッファを確保している場合は解放する
	if(chatbuf->mes[*pos].message!=NULL){
		STRBUF_Delete(chatbuf->mes[*pos].message);
	}
	// 既にしりあい告知の文字列バッファを確保している場合は解放する
	if(chatbuf->mes[*pos].friend!=NULL){
		STRBUF_Delete(chatbuf->mes[*pos].friend);
	}
	
	// 名前・ID・簡易会話・簡易会話文字列の登録
	STRBUF_SetStringCode( chatbuf->mes[*pos].name, MyStatus_GetMyName(mystatus));
	chatbuf->mes[*pos].PmsData = *pms;
	chatbuf->mes[*pos].id      = id;
	chatbuf->mes[*pos].sex     = MyStatus_GetMySex(mystatus);
	chatbuf->mes[*pos].message = PMSDAT_ToString( pms, HEAPID_UNIONBOARD );
	chatbuf->mes[*pos].friend  = FriendLinkStringGet(friendlist, id, ubw->WordSet, ubw->MsgManager, ubw->mystatus);
	
	// 次の登録位置にずらす
	(*pos)++;

	// スタート位置が最大まできた場合は最初に戻す
	if(chatbuf->start==UNION_CHAT_MAX){
		chatbuf->start = 0;
	}

	OS_Printf("書き込み後 chat->num %d, chat->start %d\n", chatbuf->num, chatbuf->start);

}


//------------------------------------------------------------------
/**
 * $brief   チャットデータが登録するかどうかチェック
 *
 * @param   ubw		
 * @param   pms		
 * @param   id		
 *
 * @retval  int		0は登録済み 1なら登録されてない新メンバー 
 */
//------------------------------------------------------------------
static int UnionChatRegisterCheck(UNION_BOARD_WORK *ubw, PMS_DATA *pms, int id)
{
	int r,index;


	// 簡易会話は有効な内容か？
	if(!PMSDAT_IsEnabled(pms)){
		return 0;
	}

	// 既に表示済みの内容かチェック
	for(r=0;r<ubw->UnionChatRingBuf->num;r++){
		if( id==ubw->UnionChatRingBuf->mes[r].id ){
			if(PMSDAT_Compare( pms, &ubw->UnionChatRingBuf->mes[r].PmsData)){
				break;
			}
		}
	}

	// 既に登録済みか？( 登録数０の時は絶対登録)
	if(r!=ubw->UnionChatRingBuf->num && ubw->UnionChatRingBuf->num!=0){
		return 0;
	}

	if( id==ubw->UnionChatRingBuf->mes[r].id ){
		OS_Printf("IDが違ったので登録 %08x , %08x\n", id,ubw->UnionChatRingBuf->mes[r].id);
	}else if(PMSDAT_Compare( pms, &ubw->UnionChatRingBuf->mes[r].PmsData)){
		OS_Printf("簡易会話が違ったので登録 %08x , %08x\n", id,ubw->UnionChatRingBuf->mes[r].id);
	}

	return 1;
	
}



//------------------------------------------------------------------
/**
 * $brief   新規簡易会話登録（他人・自分両方対応）
 *
 * @param   ubw		
 * @param   mystatus		
 * @param   pms		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBoard_AddChatSub( UNION_BOARD_WORK *ubw, MYSTATUS *status, PMS_DATA *pms, u32 id )
{
	int flag=0;

	// スクロールバーの一番下に位置しているか
	if(ubw->Scroll.now==ubw->Scroll.max-3){
		flag = 1;
	}
	OS_Printf("scroll.now=%d scroll_max = %d\n", ubw->Scroll.now, ubw->Scroll.max);

	// チャットがバッファと一致しなかったので登録
	AddUnionChatPmsData( ubw, id, pms, status );

	// スクロールバーが一番下にある時は下にいつづけるように＋１する
	if(ubw->Scroll.barflag){
		if(flag){
			ubw->Scroll.now = ubw->UnionChatRingBuf->num-3;
		}
		OS_Printf("scrol.now=%d, chat->num=%d, chat->start=%d\n", ubw->Scroll.now,ubw->UnionChatRingBuf->num,ubw->UnionChatRingBuf->start);
	}
	UnionBoardReWriteOn( ubw );

}


static _GF_BSS_DATA_INFO* d_gfinfo;
static PMS_DATA* d_pms;

//------------------------------------------------------------------
/**
 * $brief   ビーコンデータから新しいチャットデータを取得する
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void GetUnionChat( UNION_BOARD_WORK *ubw )
{
//	GetWMBssDesc_toPmsData(ubw->UnionChat);
	int i,r;
	WMBssDesc 			*beacon;
	_GF_BSS_DATA_INFO   *gfinfo;
	PMS_DATA			*pms;
	MYSTATUS			*status;
	PMS_DATA			debugpms;

	// 話し掛け中はチャット更新をしない
	if(FieldEvent_Check(ubw->fsys)){
		return;
	}

	status = MyStatus_AllocWork(HEAPID_FIELD);
	
	for(i=0;i<16;i++){
		beacon = CommMPGetWMBssDesc(i);
		
		// ビーコンが存在している＝ユニオンルームの人がいる
		if(beacon!=NULL){

			gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
			pms    = (PMS_DATA*)&gfinfo->pmsData;
			d_gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
			d_pms    = (PMS_DATA*)&gfinfo->pmsData;
			MyStatus_Copy((MYSTATUS*)gfinfo->myStatusBuff, status);

			// チャットデータは登録済み？
			if(UnionChatRegisterCheck(ubw, pms, gfinfo->pokeID)){
				// 一致しなかったので登録
				UnionBoard_AddChatSub( ubw, status, pms, gfinfo->pokeID );	// 簡易会話登録
			}
		}
	}

	// 自分のデータが掲載リクエストを受けていないか？
	if((pms=Union_GetMyPmsData( ubw->union_work ))!=NULL){
		u32 id = MyStatus_GetID( ubw->mystatus );
		UnionBoard_AddChatSub( ubw, ubw->mystatus, pms, id  );	// 簡易会話登録
	}
	
	sys_FreeMemoryEz(status);
}


//------------------------------------------------------------------
/**
 * $brief   BMP面の再描画リクエスト発行
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBoardReWriteOn( UNION_BOARD_WORK *ubw)
{
	ubw->BgTransReq = TRUE;

}
