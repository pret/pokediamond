
//===========================================================================
/**
 *
 *@file		ug_radar.c
 *@brief	炭鉱レーダー処理（サブ画面）
 *@author	Akito Mori
 *@data		2005.09.23
 *
 */
//===========================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/pm_str.h"

#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "talk_msg.h"

#include "communication/communication.h"
#include "underground/ug_manager.h"
#include "underground/ug_trap.naix"
#include "comm_player.h"
#include "underg_radar.naix"
#include "ug_radar.h"

//========================================================================================
// 定数宣言
//========================================================================================

#define UG_RADAR_RESOURCE_ID	(   1000 ) 	// 下画面のリソースＩＤを衝突しないようにするために1000とする
#define UG_TALK_SPLIT_WORD_MAX	( 20*2*2 )	// 改行が入っているログ会話の最大文字数
#define UG_MESSAGE_LINE_NUM     (      2 )  // 会話ウインドウは２行しかないよ

// pos・view配列の添え字定義
#define POS_XZ 		(2)
#define POS_XZ_TIME (3)
#define POS_XZ_INFO	(4)
#define POS_X  		(0)
#define POS_Z  		(1)
#define POS_TIME  	(2)
#define POS_INFO	(2)
#define POS_OLDINFO (3)


// 炭坑レーダー最大OBJ登録数
#define UG_RADAR_CLACT_MAX ( COMM_MACHINE_MAX + TRAP_NUM_SINGLE_MAX + 1) //32+1個のはず


// レーダー表示位置指定用定義
#define RADAR_MIN_X		(7*8+4)
#define RADAR_MIN_Y		(    8+1)
#define RADAR_MAX_X		(RADAR_MIN_X+8*17+2)
#define RADAR_MAX_Y		(RADAR_MIN_Y+8*16)

// マップがブロックデータの右下になったらしいので矯正用データ

// +--------------+
// |              |
// | +------------+
// | |            |
// | |   ここ     |
// | |            |
// | |            |
// +-+------------+
#define MAP_START_OFFSET_X	( 32 )
#define MAP_START_OFFSET_Y	( 64 )

// グリッド数値最大定義
#define RADAR_GRID_MAX_X (32*14)
#define RADAR_GRID_MAX_Z (32*13)


// CellActorに処理させるリソースマネージャの数（＝マルチセル・マルチセルアニメは使用しない）
#define CELL_ANIME_RESOURCE_NUM	(4)

// 炭鉱レーダーのタスクの優先順位（通信よりは下にいる必要とかあると思うので）
#define UNDER_GROUND_RADAR_TCB_PRIORITY		(4)


#define MESSAGE_NONE		( 0 )
#define MESSAGE_WAIT		( 1 )
#define MESSAGE_END			( 2 )

#define RADAR_TALK_WAIT 	( 8 )

#define UG_MES_FIFO_MAX		( 32 )

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ

// -----炭鉱レーダー処理のシーケンス定義---------
enum{
	UG_INIT_BG = 0,
	UG_INIT_ACTOR,
	UG_START_FADE,
	UG_LCD_ON,
	UG_WAIT_FADE,
	UG_MAIN,
	UG_END_READY,
	UG_END,
	UG_END_FADE,
};

typedef struct{
    STRBUF* TalkBuf[UG_MES_FIFO_MAX];
    STRBUF* tempBuf;
	STRBUF* splitbuf[UG_MESSAGE_LINE_NUM];
	int top;
	int bottom;
	STRCODE codework[UG_TALK_SPLIT_WORD_MAX];
}UG_MESSAGE_FIFO;



//========================================================================================
// 構造体宣言
//========================================================================================
struct UG_RADAR_WORK{
	int           mode;												// レーダー遷移
	int           pos[COMM_MACHINE_MAX][POS_XZ];					// 全員分の座標
	int           view[COMM_MACHINE_MAX][POS_XZ_TIME];				// 表示用の座標＋生存時間(2秒)
	int		      trappos[TRAP_NUM_SINGLE_MAX+1][POS_XZ_INFO];		// 
	

	FIELDSYS_WORK *fsys;											// フィールドから引き継ぐシステムポインタ
	GF_BGL_INI    *bgl;												// フィールドから引き継ぐＢＧシステムポインタ

	CLACT_SET_PTR clactSet;											// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CELL_ANIME_RESOURCE_NUM];		// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[CELL_ANIME_RESOURCE_NUM];		// リソースオブジェテーブル
	CLACT_HEADER			clActHeader;							// セルアクターヘッダー

	CLACT_WORK_PTR			clActWork[COMM_MACHINE_MAX];			// セルアクターワークポインタ配列(主人公）
	CLACT_WORK_PTR			TrapActWork[TRAP_NUM_SINGLE_MAX+1];		// セルアクターワークポインタ配列（罠）
	GF_BGL_BMPWIN 			talkWin;								// レーダー画面メッセージウインドウ
	int						MesIndex;								// メッセージインデックス
	int						TalkMode;
	int						Wait;
	UG_MESSAGE_FIFO			UgMesFifo;
//    u16                   talkBuff[32][50*GLOBAL_MSGLEN];			

	
};

int debugpos[COMM_MACHINE_MAX][POS_XZ];


//========================================================================================
// プロトタイプ宣言
//========================================================================================
static void initBG(GF_BGL_INI *bgl,GF_BGL_BMPWIN *talkWin);
static void InitCellActor(UG_RADAR_WORK *urw);
static void HeroPosGet(const PLAYER_STATE_PTR jiki,int pos[][POS_XZ], int view[][POS_XZ_TIME]);
static void InitWork(int pos[][POS_XZ], int view[][POS_XZ_TIME]);
static void HeroRadarPosSet(int view[][POS_XZ_TIME], CLACT_WORK_PTR clActWork[]);
static void initBG(GF_BGL_INI* bgl, GF_BGL_BMPWIN *talkWin);
static void destBG(GF_BGL_INI* bgl);


extern void FieldMsgPrintInitSub(void);
extern void FldTalkBmpAddSub( GF_BGL_INI * ini, GF_BGL_BMPWIN * win );

static void RadarActionMessageFunc(GF_BGL_INI *bgl, GF_BGL_BMPWIN *talkWin, int *MesIndex, int *talkmode, int *wait, UG_MESSAGE_FIFO *MesFifo);


static void     MessageFifoInit(UG_MESSAGE_FIFO *fifo);
static void     MessageFifoFinalize(UG_MESSAGE_FIFO *fifo);
static int      MessageFifoIn(UG_MESSAGE_FIFO *fifo, STRBUF *src);
static STRBUF*  MessageFifoOut(UG_MESSAGE_FIFO *fifo);
static int      MessageFifoCheck(UG_MESSAGE_FIFO *fifo);
static void HeroTrapActSet( int pos[][POS_XZ_INFO],  CLACT_WORK_PTR TrapActWork[]);
static void HeroTrapPosGet( int pos[][POS_XZ_INFO] );

static UG_RADAR_WORK *debug_ug_radar;

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
static void UnderGround_RadarFunc(TCB_PTR tcb, void *wk)
{
	UG_RADAR_WORK *urw = wk;
	GF_BGL_INI    *bgl = urw->bgl;
	int i;

	debug_ug_radar = urw;
	switch(urw->mode){
	case UG_INIT_BG:
		// BG初期化・VRAM転送
		OS_Printf("start underground = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
		OS_Printf("underground  work= %ld\n",sizeof(UG_RADAR_WORK));

		initBG(bgl,&urw->talkWin);

		// レーダー用配列初期化
		InitWork(urw->pos,urw->view);
		MessageFifoInit(&urw->UgMesFifo);
		urw->mode++;
		break;
	case UG_INIT_ACTOR:

		InitCellActor(urw);

		// セルアクターヘッダ作成
		CLACT_U_MakeHeader(&urw->clActHeader, 
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
							0, 0,
							urw->resMan[CLACT_U_CHAR_RES],
							urw->resMan[CLACT_U_PLTT_RES],
							urw->resMan[CLACT_U_CELL_RES],
							urw->resMan[CLACT_U_CELLANM_RES],
							NULL,NULL);

		{
			//登録情報格納
			CLACT_ADD add;

			add.ClActSet	= urw->clactSet;
			add.ClActHeader	= &urw->clActHeader;

			add.mat.x		= FX32_CONST(32) ;
			add.mat.y		= FX32_CONST(96) + SUB_SURFACE_Y;		//画面は上下連続している（MAINが上、SUBが下）
			add.mat.z		= 0;
			add.sca.x		= FX32_ONE;
			add.sca.y		= FX32_ONE;
			add.sca.z		= FX32_ONE;
			add.rot			= 0;
			add.pri			= 0;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			add.heap		= HEAPID_FIELD;

			//セルアクター表示開始

			// 主人公登録
			for(i=0;i<COMM_MACHINE_MAX;i++){
				urw->clActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(urw->clActWork[i],1);
				CLACT_SetDrawFlag(urw->clActWork[i], 0);	//非表示に
				if(i==0){			//一旦自分は０ということにする
					CLACT_AnmChg( urw->clActWork[i], 1 );		//青色に
				}
			}
			
			// 罠登録
			for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){
				urw->TrapActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(urw->TrapActWork[i],1);
				CLACT_SetDrawFlag(urw->TrapActWork[i], 0);	//非表示に
				CLACT_AnmChg( urw->TrapActWork[i], 2 );		//罠アニメにチェンジ
			}
			
		}	
		


		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ
		
		urw->mode++;
		break;
	case UG_START_FADE:
		// 輝度フェード開始
//		ChangeBrightnessRequest(30,BRIGHTNESS_NORMAL,BRIGHTNESS_BLACK,
//			PLANEMASK_BG0|PLANEMASK_BG3|PLANEMASK_OBJ,MASK_SUB_DISPLAY);
		urw->mode++;
		break;
	case UG_LCD_ON:
		// サブ画面表示ＯＮ
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );
		urw->mode++;
		break;
	case UG_WAIT_FADE:
//		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){		//フェード終了待ち
			urw->mode++;
//		}
		break;
		
	// メインシーケンス
	case UG_MAIN:
		HeroPosGet(urw->fsys->player,urw->pos,urw->view);				// 通信関数から主人公の位置を取得する
		HeroRadarPosSet(urw->view, urw->clActWork);						// レーダー用の座標に変換して登録する
		HeroTrapPosGet( urw->trappos);									// 自分で設置した罠の位置を取得する
		HeroTrapActSet( urw->trappos, urw->TrapActWork);
		

		RadarActionMessageFunc(urw->bgl,
                               &urw->talkWin,&urw->MesIndex,
                               &urw->TalkMode,&urw->Wait,&urw->UgMesFifo);	// 行動内容をメッセージに反映

		CLACT_Draw( urw->clactSet );									// セルアクター常駐関数
		break;

	// 終了シーケンス
	case UG_END_READY:
		if(FldTalkMsgEndCheck( urw->MesIndex )){					//メッセージ表示終了を待たないとふっとぶ
			urw->mode++;
		}
		break;

	case UG_END:
		// キャラ転送マネージャー破棄
		CLACT_U_CharManagerDelete(urw->resObjTbl[CLACT_U_CHAR_RES]);

		// パレット転送マネージャー破棄
		CLACT_U_PlttManagerDelete(urw->resObjTbl[CLACT_U_PLTT_RES]);
		
		// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
		for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){
			CLACT_U_ResManagerDelete(urw->resMan[i]);
		}
		// セルアクターセット破棄
		CLACT_DestSet(urw->clactSet);

		BmpTalkWinClear( &urw->talkWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &urw->talkWin );						//BmpWin解放

		GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_S);				//会話ウインドウ用バッファ解放
		destBG(bgl);											// BG0,BG1用バッファ解放
        MessageFifoFinalize(&urw->UgMesFifo);

		// 輝度フェード開始
//		ChangeBrightnessRequest(30,BRIGHTNESS_BLACK,BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_SUB_DISPLAY);
		urw->mode++;
		break;

	case UG_END_FADE:
//		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){
			urw->fsys->UnderGroundRadar = NULL;
			PMDS_taskDel(tcb);	//タスク削除
			OS_Printf("end underground = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
//		}


		break;
		

	}

}

//------------------------------------------------------------------
/**
 * レーダー表示用座標初期化
 *
 * @param   pos[][POS_XZ]			
 * @param   view[][POS_XZ_TIME]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(int pos[][POS_XZ], int view[][POS_XZ_TIME])
{
	int i;
	for(i=0;i<COMM_MACHINE_MAX;i++){
		pos[i][POS_X]     = 0;
		pos[i][POS_Z]     = 0;
		view[i][POS_X]    = 0;
		view[i][POS_Z]    = 0;
		view[i][POS_TIME] = 0;
		
		debugpos[i][POS_X]   = gf_rand()%500+50;
		debugpos[i][POS_Z]   = gf_rand()%500+50;

	}
}

#if 0
int debugposmovex(int no, int flag)
{
	debugpos[no][flag] += gf_rand()%4 -2;

	return debugpos[no][flag];
}

#endif
//------------------------------------------------------------------
/**
 * 現在の主人公の座標を取得する（通信関数からか、フィールド関数からかは判断）
 *
 * @param   jiki					fieldsysのplayer構造体のポインタ
 * @param   pos[][POS_XZ]			主人公の座標
 * @param   view[][POS_XZ_TIME]		レーダー表示用の座標配列のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroPosGet(const PLAYER_STATE_PTR jiki,int pos[][POS_XZ], int view[][POS_XZ_TIME])
{
	int i;
	
	//通信関数から主人公の位置を取得
	for(i=0;i<COMM_MACHINE_MAX;i++){
		pos[i][POS_X] = CommPlayerGetPosX(i);
		pos[i][POS_Z] = CommPlayerGetPosZ(i);
	}

	//通信していないときはフィールド上の座標を取得

	if(CommIsInitialize()){
		if(CommIsConnect(CommGetCurrentID())==0){
			pos[0][POS_X] = Player_NowGPosXGet( jiki );	
			pos[0][POS_Z] = Player_NowGPosZGet( jiki );
		}else{
            // 自分が青くなるように位置を交換
            int gx = pos[0][POS_X];
            int gz = pos[0][POS_Z];
			pos[0][POS_X] = pos[CommGetCurrentID()][POS_X];
			pos[0][POS_Z] = pos[CommGetCurrentID()][POS_Z];
			pos[CommGetCurrentID()][POS_X] = gx;
			pos[CommGetCurrentID()][POS_Z] = gz;
		}
	}
	//取得値を表示座標に格納する
	for(i=0;i<COMM_MACHINE_MAX;i++){
        if(!UgSecretBaseIsSecretBasePlace(pos[i][POS_X],pos[i][POS_Z])){
            view[i][POS_X]    = pos[i][POS_X] - MAP_START_OFFSET_X;
			view[i][POS_Z]    = pos[i][POS_Z] - MAP_START_OFFSET_Y;
			view[i][POS_TIME] = 60; //RADAR_LIFE_TIME;
//			OS_Printf("comm= %d, X= %ld,Y= %ld\n",CommIsConnect(CommGetCurrentID()),pos[i][POS_X],pos[i][POS_Z]);
		}else{
			if(view[i][POS_TIME]!=0){
				if(view[i][POS_X]>=0){		//一度生存していた
					view[i][POS_TIME]--;
				}
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * レーダー用の座標に変換して登録する(表示・非表示の制御も行う）
 *
 * @param   view[][POS_XZ_TIME]		表示用座標格納配列
 * @param   clActWork[]				セルアクターワークのポインタ配列
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroRadarPosSet(int view[][POS_XZ_TIME], CLACT_WORK_PTR clActWork[])
{
	int i;

	for(i=0;i<COMM_MACHINE_MAX;i++){
		if(view[i][POS_TIME]!=0){
			VecFx32 pos;

			pos.x = (RADAR_MIN_X + ((RADAR_MAX_X-RADAR_MIN_X)*view[i][POS_X])/RADAR_GRID_MAX_X)*FX32_ONE;
			pos.y = (RADAR_MIN_Y + ((RADAR_MAX_Y-RADAR_MIN_Y)*view[i][POS_Z])/RADAR_GRID_MAX_Z)*FX32_ONE+ SUB_SURFACE_Y;
			pos.z = FX32_ONE;
			CLACT_SetMatrix(clActWork[i], &pos);
			CLACT_SetDrawFlag(clActWork[i], 1);	//存在しているなら表示に

		}else{
			CLACT_SetDrawFlag(clActWork[i], 0);	//０以外は非表示に
		}
	}
}


//------------------------------------------------------------------
/**
 * 自分の罠のグリッド位置を取得（自分のなので通信は関係ない）
 *     光らせたいものを返すように内部関数変更しました  k.ohno 06.03.22
 * @param   pos[][POS_XZ]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroTrapPosGet( int pos[][POS_XZ_INFO] )
{
	int i, x, z,info;
	for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){

		x    = UgMgrGetDispPointX(i);
    	z    = UgMgrGetDispPointZ(i);
		info = UgMgrGetDispPointInfo(i);

        if(!UgSecretBaseIsSecretBasePlace(x, z)){
            pos[i][POS_X] = x - MAP_START_OFFSET_X;
            pos[i][POS_Z] = z - MAP_START_OFFSET_Y;
			pos[i][POS_INFO] = info;
        }
        else{
            pos[i][POS_X] = 0;
            pos[i][POS_Z] = 0;
			pos[i][POS_INFO] = 0;
        }
	}
}



//------------------------------------------------------------------
/**
 * 自分の罠の表示
 *
 * @param   pos[][POS_XZ]		
 *
 * @retval  staitc void		
 */
//------------------------------------------------------------------
static void HeroTrapActSet( int pos[][POS_XZ_INFO],  CLACT_WORK_PTR TrapActWork[])
{
	int i;
	for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){
		if(pos[i][POS_X]!=0 ){
			VecFx32 vec;
			vec.x = (RADAR_MIN_X + ((RADAR_MAX_X-RADAR_MIN_X)*pos[i][POS_X])/RADAR_GRID_MAX_X)*FX32_ONE;
			vec.y = (RADAR_MIN_Y + ((RADAR_MAX_Y-RADAR_MIN_Y)*pos[i][POS_Z])/RADAR_GRID_MAX_Z)*FX32_ONE +SUB_SURFACE_Y;
			vec.z = FX32_ONE;
			CLACT_SetMatrix(TrapActWork[i], &vec);

			// 前回と表示情報が変わっている場合は見た目変更
			if(pos[i][POS_INFO]!=pos[i][POS_OLDINFO]){
				if(pos[i][POS_INFO]!=RADAR_TYPE_NONE){
					CLACT_AnmChg( TrapActWork[i], pos[i][POS_INFO] );
					CLACT_SetDrawFlag(TrapActWork[i], 1);
				}else{
					CLACT_SetDrawFlag(TrapActWork[i], 0);	//０以外は非表示に
				}
			}
		}else{
			CLACT_SetDrawFlag(TrapActWork[i], 0);	//０以外は非表示に
		}

		// 表示情報を更新
        pos[i][POS_OLDINFO] = pos[i][POS_INFO];

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
UG_RADAR_WORK *UnderGround_RadarInit( FIELDSYS_WORK *fsys )
{
	UG_RADAR_WORK *urw;
	TCB_PTR       tcb;

	//炭鉱レーダータスクを追加
	tcb = PMDS_taskAdd(UnderGround_RadarFunc, sizeof(UG_RADAR_WORK), UNDER_GROUND_RADAR_TCB_PRIORITY, HEAPID_FIELD);
	urw = TCB_GetWork(tcb);
	urw->fsys = fsys;
	urw->bgl  = fsys->bgl;

	return urw;
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
void UnderGround_RadarEnd(UG_RADAR_WORK *urw)
{
	// レーダーのシーケンス定義を終了に変更
	if(urw->mode==UG_MAIN){
		urw->mode = UG_END_READY;
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
static void initBG(GF_BGL_INI* bgl, GF_BGL_BMPWIN *talkWin)
{
	// 今までの破棄
	destBG(bgl);

	// サブ面BG０，１,3のコントロールを設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	}
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME3_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME3_S );
	}


	// パレット転送
	ArcUtil_PalSet(    ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NCLR, PALTYPE_SUB_BG, 0, 0x20*2,  HEAPID_FIELD);



	// キャラ転送( 32*9*0x20まではいける）
	ArcUtil_BgCharSet( ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NCGR, bgl, GF_BGL_FRAME0_S, 0, 32*5*0x20, 0, HEAPID_FIELD);
																					

	// スクリーン転送
	ArcUtil_ScrnSet(   ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 0, HEAPID_FIELD);

	FieldMsgPrintInit( PALTYPE_SUB_BG, MSG_PRINT_NO_INIT );				// サブ画面VRAMにフォントとパレットを転送

	
	GF_BGL_ClearCharSet( FLD_SBGFRM_FONT, 32, 0, HEAPID_FIELD );
    FldTalkBmpAdd( bgl, talkWin, FLD_SBGFRM_FONT);	// サブ画面メッセージウインドウ確保
	GF_BGL_BmpWinDataFill( talkWin, 0 );

	ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_SUB_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);

//    FldTalkWinPut( talkWin );			// サブ画面メッセージウインドウ表示開始
//    _pInfo->msgIndex = FldTalkMsgStart(&_pInfo->talkWin, pMsg, 1);

}



//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   urw		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(UG_RADAR_WORK *urw)
{
	int i;
	// セルアクター初期化
	urw->clactSet = CLACT_U_SetEasyInit( UG_RADAR_CLACT_MAX, &urw->renddata, HEAPID_FIELD );
	
	//リソースマネージャー初期化
	for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){		//リソースマネージャー作成
		urw->resMan[i] = CLACT_U_ResManagerInit( 1, i, HEAPID_FIELD );
	}

	
	//chara読み込み
	urw->resObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(urw->resMan[CLACT_U_CHAR_RES], 
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCGR, 0, UG_RADAR_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_FIELD);

	//pal読み込み
	urw->resObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(urw->resMan[CLACT_U_PLTT_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCLR, 0, UG_RADAR_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, 2, HEAPID_FIELD);

	//cell読み込み
	urw->resObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(urw->resMan[CLACT_U_CELL_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCER, 0, UG_RADAR_RESOURCE_ID, CLACT_U_CELL_RES,HEAPID_FIELD);

	//同じ関数でanim読み込み
	urw->resObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(urw->resMan[CLACT_U_CELLANM_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NANR, 0, UG_RADAR_RESOURCE_ID, CLACT_U_CELLANM_RES,HEAPID_FIELD);

	// Chara転送
	CLACT_U_CharManagerSetAreaCont( urw->resObjTbl[CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSetCleanArea( urw->resObjTbl[CLACT_U_PLTT_RES] );

}




//------------------------------------------------------------------
/**
 * 炭坑レーダー会話ウインドウ画面制御
 *
 * @param  bgl 		GF_BGL_INI*
 * @param  talkWin	GF_BGL_BMPWIN*
 * @param  MesIndex	文字表示待ちフラグ
 * @param  talkmode 文字表示状態（動作なし、表示待ち、スクロール中）
 * @param  wait		文字表示内で使用するウェイトカウンタ
 * @param  MesFifo	通信主人公行動ログFIFO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RadarActionMessageFunc(
	GF_BGL_INI *bgl, 
	GF_BGL_BMPWIN *talkWin, 
	int *MesIndex, 
	int *talkmode, 
	int *wait,  
	UG_MESSAGE_FIFO *MesFifo)
{
    STRBUF* strbuf;
    
    while(CommUnderGetActionMessage(MesFifo->tempBuf)){  // 今の状況を引き出しFIFOに詰める
		MessageFifoIn(MesFifo,MesFifo->tempBuf);
    }

	switch(*talkmode){
	// 文章表示開始
	case MESSAGE_NONE:
		if((strbuf=MessageFifoOut(MesFifo))!=NULL){
			*MesIndex = GF_STR_PrintSimple(
				talkWin, FONT_TALK, strbuf, 0, 2+16, 1,	NULL );
	        *talkmode = MESSAGE_WAIT;
		}
        break;
	// 表示終了待ち
	case MESSAGE_WAIT:
		if(FldTalkMsgEndCheck( *MesIndex )){
			*talkmode = MESSAGE_END;
			*wait = 0;
		}
		break;

	// スクロール
	case MESSAGE_END:
		if(MessageFifoCheck(MesFifo)==0){
			GF_BGL_BmpWinShift( talkWin, GF_BGL_BMPWIN_SHIFT_U, 2,  0x00);
			GF_BGL_BmpWinOn( talkWin );
			if(++(*wait) > RADAR_TALK_WAIT){
				*wait = 0;
//				BmpTalkWinClear( talkWin, WINDOW_TRANS_OFF );
				*talkmode = MESSAGE_NONE;
			}
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * メッセージFIFO初期化
 *
 * @param   fifo	UG_MESSAGE_FIFO構造体のポインタ
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void MessageFifoInit(UG_MESSAGE_FIFO *fifo)
{
	int i;
	for(i=0;i<UG_MES_FIFO_MAX;i++){
        fifo->TalkBuf[i] = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    }
	fifo->top    = 0;
	fifo->bottom = 0;
    fifo->tempBuf = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	for(i=0;i<UG_MESSAGE_LINE_NUM;i++){
		fifo->splitbuf[i] = STRBUF_Create( UG_TALK_SPLIT_WORD_MAX, HEAPID_FIELD );
	}
}

//------------------------------------------------------------------
/**
 * メッセージFIFO終了
 *
 * @param   fifo	UG_MESSAGE_FIFO構造体のポインタ
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void MessageFifoFinalize(UG_MESSAGE_FIFO *fifo)
{
	int i;
	for(i=0;i<UG_MES_FIFO_MAX;i++){
        STRBUF_Delete(fifo->TalkBuf[i]);
    }
    STRBUF_Delete(fifo->tempBuf);
	for(i=0;i<UG_MESSAGE_LINE_NUM;i++){
		STRBUF_Delete( fifo->splitbuf[i] );
	}

}

//------------------------------------------------------------------
/**
 * $brief   改行こみの配列なら分割して１行ずつにわける
 *
 * @param   fifo	
 * @param   src		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int UgMessageCheck( UG_MESSAGE_FIFO* fifo, STRBUF *src )
{
	int i,num,pos;
	// STRCODEに戻す
	STRBUF_GetStringCode( src, fifo->codework, UG_TALK_SPLIT_WORD_MAX );

	// 改行コードがあるか探す
	num = 0;
	i   = 0;
	while(fifo->codework[i]!=EOM_){
		if(fifo->codework[i]==CR_){
			num++;
			pos = i;
		}
		i++;
	}
	GF_ASSERT(num<2 && "炭坑レーダーメッセージに改行が２つ入っている");

	// 改行コードはなかった
	if(num==0){
		// 普通にコピーして終了
		STRBUF_Copy(fifo->splitbuf[0],src);
		return 1;
	}else{
	// 改行コードがあった場合は２つのSTRBUFに分けて保存する
		fifo->codework[pos] = EOM_;
		STRBUF_SetStringCode( fifo->splitbuf[0], fifo->codework );
		STRBUF_SetStringCode( fifo->splitbuf[1], &fifo->codework[pos+1] );
	}

	return 2;
}
//------------------------------------------------------------------
/**
 * メッセージFIFOに追加
 *
 * @param   fifo	UG_MESSAGE_FIFO構造体のポインタ
 * @param   src		コピー元の文字列
 *
 * @retval  int		格納したら1,しなかったら0
 */
//------------------------------------------------------------------
static int MessageFifoIn(UG_MESSAGE_FIFO *fifo, STRBUF *src)
{
	int top,i,linenum;

	// ２行にまたがったSTRBUFかチェック
	linenum = UgMessageCheck( fifo, src );

	// FIFO登録前チェック
	top = fifo->top;
	for(i=0;i<linenum;i++){
		if(++top==UG_MES_FIFO_MAX){
			top = 0;
		}
		if(top==fifo->bottom){			// bottomに追いついていないかチェック
			return 0;					// 登録するとおいついてしまう場合は終了
		}
	}

	// 登録できる
	for(i=0;i<linenum;i++){
   		STRBUF_Copy(fifo->TalkBuf[fifo->top],fifo->splitbuf[i]);
		fifo->top++;
		if(fifo->top==UG_MES_FIFO_MAX){
			fifo->top = 0;
		}
	}
	return 1;
}

//------------------------------------------------------------------
/**
 * メッセージFIFOから取り出し
 *
 * @param   fifo		UG_MESSAGE_FIFO構造体のポインタ
 *
 * @retval  STRCODE*	取り出した文字列のポインタ
 */
//------------------------------------------------------------------
static STRBUF* MessageFifoOut(UG_MESSAGE_FIFO *fifo)
{
	int result;
	if(fifo->top!=fifo->bottom){	// FIFOを解消しきっていないかチェック
		result = fifo->bottom;
		if(++fifo->bottom==UG_MES_FIFO_MAX){
			fifo->bottom = 0;
		}

		return fifo->TalkBuf[result];
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * FIFOが解消しきっているかチェック
 *
 * @param   fifo	UG_MESSAGE_FIFO構造体のポインタ
 *
 * @retval  int		解消しきっていたら1,違ったら0
 */
//------------------------------------------------------------------
static int MessageFifoCheck(UG_MESSAGE_FIFO *fifo)
{
	if(fifo->top!=fifo->bottom){	// FIFOを解消しきっていないかチェック
		return 0;
	}
	return 1;
}