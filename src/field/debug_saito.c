#ifdef PM_DEBUG

#include "common.h"
#include "system/pm_str.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/arc_util.h"
#include "system/bmp_cursor.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "field_common.h"
#include "system/fontproc.h"

#include "debug_saito.h"

#include "system/brightness.h"

#include "camera_move_test.h"

#include "fieldsys.h"

#include "field_event.h"
#include "mapdefine.h"
#include "worldmap.h"
//#include "effect_uground.h"
#include "player.h"
#include "zonedata.h"

//#include "under_tp.h"
#include "comm_field_state.h"  // 地下通信用

#include "ev_mapchange.h"
#include "eventdata.h"		//ゾーン毎のイベントデータ参照のため

//↓ポケモン関連
#include "system/buflen.h"

#include "system/msgdata_util.h"

#include "sway_grass_enc.h"

#include "msgdata/msg_debug_saito.h"
#include "msgdata/msg.naix"

#include "encount_set.h"

#include "savedata/encount.h"
#include "move_pokemon_def.h"

#include "move_pokemon.h"
#include "field/field_place_name.h"
#include "system/snd_tool.h"

#include "generate_zone.h"

#include "encount_define.h"
#include "arc/encdata_ex.naix"
#include "system/zukanwork.h"

#include "sp_fishing_enc.h"
#include "safari_enc.h"

#define	FDBG_DEBUG_PL		(FLD_SYSFONT_PAL)	//パレットナンバー

#define DISP_LINE_MAX	(9)

#define HEAPID_D_SAITO	(HEAPID_BASE_APP)



//----------------------------------------------------------------------------
//	構造体定義
//----------------------------------------------------------------------------
typedef struct _DEBUG_WINDOW_DATA{
//	u8	work;
	
	u16 debug_list;
	u16 debug_cursor;

	GF_BGL_BMPWIN	win;
	BMPLIST_WORK* lw;		// BMPメニューワーク
	struct _FIELDSYS_WORK * fsys;
	BMP_MENULIST_DATA 	*ld;
}DEBUG_WINDOW_DATA;

typedef struct _DEBUG_WORK_DATA{
	struct _FIELDSYS_WORK * fsys;
	GF_CAMERA_PTR camera;
	STRBUF	*StrBuf;
	u8 camera_tbl_no;
	
	GF_BGL_BMPWIN	win;
	s8	rod;
	u8	MovePokeInfoNo;	//0～2
	s8	zone_idx;
	u8	SafariArea;
}DEBUG_WORK_DATA;

typedef void (*DRAW_FUNC)( DEBUG_WORK_DATA* );

static const GF_CAMERA_PARAM TestOrgCamera[] =
{
	{
		/*0x30aec1*/0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		0	//dummy
	},								//0
	{
		0x189647,
		{
			-0x2ffe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x09c1,
		0	//dummy
	},								//1
	{
		0x23e93f,
		{
			-0x2cfe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x06c1,
		0	//dummy
	},								//2
	{
		0x1b8152,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x08c1,
		0	//dummy
	},								//3
	{
		0x3346fe,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x04c1,
		0	//dummy
	},								//4
	{
		0x298ec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		0	//dummy
	},								//5
	{
		0x14aec0,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0B01,
		0	//dummy
	},								//6
	{
		0x411726,
		{
			-0x23be,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x03c1,
		1	//near_far
	},								//7
	{
		0x61b89b,
		{
			-0x239e,0,0
		},
		GF_CAMERA_ORTHO,
		0x0281,
		2	//near_far
	},								//8
};

//------------------------------------------------------------------------------
//	global
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	extern
//------------------------------------------------------------------------------
extern u8 HC_DebugCheckHeight(const fx32 inX, const fx32 inZ, MHI_CONST_PTR inMap3DInfo, const BOOL inDetail);
//---------------------------------------------------------------------------
//	static 変数
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	static 関数
//---------------------------------------------------------------------------
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp);
static void DebugListFree(TCB_PTR tcb,void* work);
static void DebugWindowExit(TCB_PTR tcb,void* work);
static void DebugListControlTask(TCB_PTR tcb,void* work);

static void ChangeStressFlg(TCB_PTR tcb,void *work);
static void DebugWinSwayGrass(TCB_PTR tcb,void *work);
static void DispSwayGrassRec(TCB_PTR tcb,void *work);

static void MBMapSetExit(TCB_PTR tcb,void* work);


static void SetCameraDebugWindow(TCB_PTR tcb,void *work);
static void SetupCameraInfoWindow(TCB_PTR tcb,void *work);
static void SetupCameraListWindow(TCB_PTR tcb,void *work);

static void SetCamera(TCB_PTR tcb,void *work);
static void SetSwayGrass(TCB_PTR tcb,void *work);
///static void SetupPokeAnmWindow(TCB_PTR tcb,void *work);
static void DebugWinFishing(TCB_PTR tcb,void *work);
static void DebugWinMovePoke(TCB_PTR tcb,void *work);

static void SetupFishingRod(TCB_PTR tcb,void *work);
static void SetupFishingProb(TCB_PTR tcb,void *work);
static void SetupSpFishingPoint(TCB_PTR tcb,void *work);

static void SetupSwayGrassChain(TCB_PTR tcb,void *work);
static void DispSwayGrassInfo(TCB_PTR tcb,void *work);

static void SetupMovePokeInfo(TCB_PTR tcb,void *work);
static void DebugWinMovePokeName(TCB_PTR tcb,void *work);
static void SetupEntryMovePoke(TCB_PTR tcb,void *work);
static void SetupMovePokeZoneChgWin(TCB_PTR tcb,void *work);

//高さ変更
static void SetPlayerHeightChangeTask(TCB_PTR tcb,void *work);

//高さデバッグ
static void DebugCheckHeightGrid(TCB_PTR tcb,void *work);
static void DebugCheckHeightBlock(TCB_PTR tcb,void *work);

//大量発生
static void DebugGenerate(TCB_PTR tcb,void *work);
static void DebugStartGenerate(TCB_PTR tcb,void *work);
static void SetupGeneZoneInfoWin(TCB_PTR tcb,void *work);

//サファリ
static void DebugSafari(TCB_PTR tcb,void *work);

//AGB
static void DebugSetAgbVer(TCB_PTR tcb,void *work);
static void DebugAgbVer(TCB_PTR tcb,void *work);

//----------------------------------------------------------------------------
//	リスト項目名
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	項目と実行関数のリスト
//--------------------------------------------------------------------------
typedef struct ID_PARAM_tag
{
	u32  str_id;
	u32  param;
}ID_PARAM;

static const ID_PARAM DebugMenuMainList[] = {
	{ D_SAITO_MSG01, (u32)SetCamera },
	{ D_SAITO_MSG02, (u32)DebugWinSwayGrass, },
    { D_SAITO_MSG03, (u32)DebugCheckHeightBlock },
    { D_SAITO_MSG04, (u32)DebugCheckHeightGrid },
    { D_SAITO_MSG05, (u32)SetCameraDebugWindow },
    { D_SAITO_MSG06, (u32)SetPlayerHeightChangeTask },
///	{ D_SAITO_MSG09, (u32)SetupPokeAnmWindow },
	{ D_SAITO_MSG10, (u32)DebugWinFishing },
	{ D_SAITO_MSG11, (u32)DebugWinMovePoke },
	{ D_SAITO_MSG12, (u32)DebugGenerate },
	{ D_SAITO_MSG13, (u32)DebugSafari},
	{ D_SAITO_MSG14, (u32)DebugSetAgbVer },
};

static const ID_PARAM DebugCameraMenuList[] = {
	{ D_SAITO_MSG07, (u32)SetupCameraInfoWindow },
	{ D_SAITO_MSG08, (u32)SetupCameraListWindow },
};

static const ID_PARAM DebugSwayGrassMenuList[] = {
	{ D_SAITO_SWAY01, (u32)SetSwayGrass },
	{ D_SAITO_SWAY02, (u32)SetupSwayGrassChain },
	{ D_SAITO_SWAY03, (u32)DispSwayGrassInfo },
	{ D_SAITO_SWAY04, (u32)DispSwayGrassRec },
};

static const ID_PARAM DebugFishingMenuList[] = {
	{ D_SAITO_FISH01, (u32)SetupFishingRod },
	{ D_SAITO_FISH02, (u32)SetupFishingProb },
	{ D_SAITO_FISH03, (u32)SetupSpFishingPoint },
};

static const ID_PARAM DebugMovePokeMenuList[] = {
	{ D_SAITO_MP01, (u32)SetupMovePokeInfo },
	{ D_SAITO_MP02, (u32)DebugWinMovePokeName },
	{ D_SAITO_MP03, (u32)SetupEntryMovePoke },
};

static const ID_PARAM DebugMovePokeNameList[] = {
	{ D_SAITO_MP_AI, (u32)SetupMovePokeZoneChgWin },
	{ D_SAITO_MP_MUUBASU, (u32)SetupMovePokeZoneChgWin },
	{ D_SAITO_MP_DAAKU, (u32)SetupMovePokeZoneChgWin },
};

static const ID_PARAM DebugGeneMenuList[] = {
	{ D_SAITO_GENE01, (u32)DebugStartGenerate },
	{ D_SAITO_GENE02, (u32)SetupGeneZoneInfoWin },
};

static const ID_PARAM DebugAgbMenuList[] = {
	{ D_SAITO_AGB00, (u32)DebugAgbVer },
	{ D_SAITO_AGB01, (u32)DebugAgbVer },
	{ D_SAITO_AGB02, (u32)DebugAgbVer },
	{ D_SAITO_AGB03, (u32)DebugAgbVer },
	{ D_SAITO_AGB04, (u32)DebugAgbVer },
	{ D_SAITO_AGB05, (u32)DebugAgbVer },
};

//---------------------------------------------------------------------------
//  ウィンドウ設定
//---------------------------------------------------------------------------
//メインウィンドウ
static const BMPWIN_DAT	MainDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	14,21,
	FDBG_DEBUG_PL,8
};

//カメラウィンドウ
static const BMPWIN_DAT	CameraDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	14,5,
	FDBG_DEBUG_PL,8
};
//揺れ草
static const BMPWIN_DAT	SwayDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	8,10,
	FDBG_DEBUG_PL,8
};
//釣り
static const BMPWIN_DAT	FishingDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	16,7,
	FDBG_DEBUG_PL,8
};
//移動ポケモン
static const BMPWIN_DAT	MovePokeDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	12,7,
	FDBG_DEBUG_PL,8
};
//移動ポケモン名
static const BMPWIN_DAT	MovePokeNameDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	8,8,
	FDBG_DEBUG_PL,8
};
//大量発生
static const BMPWIN_DAT	GeneDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	10,6,
	FDBG_DEBUG_PL,8
};
//AGB
static const BMPWIN_DAT	AgbDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	10,14,
	FDBG_DEBUG_PL,8
};



//リスト作成
static void MakeBmpList(struct _FIELDSYS_WORK *fsys, const int inNum, ID_PARAM const *list, BMPWIN_DAT const * win_dat)
{
	TCB_PTR pTcb;
	DEBUG_WINDOW_DATA *wp;

	BMPLIST_HEADER bmplist_h = {
		//MainDebugList,		//表示文字データポインタ
		NULL,				//表示文字データポインタ
		NULL,				//カーソル移動ごとのコールバック関数
		NULL,		//１行ごとのコールバック関数
		NULL,		//GF_BGL_BMPWIN * 
		0,//リスト項目数
		0,//表示最大項目数
		2,					//ラベル表示Ｘ座標
		12,					//項目表示Ｘ座標
		1,					//カーソル表示Ｘ座標
		8,					//表示Ｙ座標
		FBMP_COL_WHITE,		//文字色
		FBMP_COL_BLACK,		//背景色
		FBMP_COL_BLK_SDW,	//文字影色
		0,					//文字間隔Ｘ
		1,					//文字間隔Ｙ
		BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
		FONT_SYSTEM,			//文字指定
		0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
		NULL,				//*work
	};
	
	wp = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WINDOW_DATA));
	if(wp == NULL){
		//ワークエリアが取得できなければ何もしない
		OS_Printf("map_num debug menu crate failed\n");
		return;
	}
	memset(wp,0,sizeof(DEBUG_WINDOW_DATA));

	wp->fsys = fsys;

	//デバッグメニュー用変数初期化
	InitDebugWindow(wp);

	//メイン処理タスク追加
	pTcb = TCB_Add(DebugListControlTask,wp,0);


	wp->ld = BMP_MENULIST_Create( inNum, HEAPID_D_SAITO );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
		for(i=0; i<inNum; i++)
		{
			BMP_MENULIST_AddArchiveString( wp->ld, msgman,
					list[i].str_id, list[i].param );
		}
		MSGMAN_Delete(msgman);
	}

	//BITMAPメニュー追加
	GF_BGL_BmpWinAddEx(fsys->bgl,&wp->win,win_dat);
	//BMPリスト設定
	bmplist_h.count = inNum;
	if (DISP_LINE_MAX < inNum){
		bmplist_h.line = DISP_LINE_MAX;
	}else{
		bmplist_h.line = inNum;
	}
	OS_Printf("disp=%d\n",inNum);
	bmplist_h.list = wp->ld;
	bmplist_h.win = &wp->win;
	wp->lw = BmpListSet(&bmplist_h,0,0,HEAPID_D_SAITO);
	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//ウィンドウ構築
static void SetWindow(	struct _FIELDSYS_WORK * fsys, TCB_FUNC t_func, DRAW_FUNC d_func,
						u8 posx, u8 posy, u8 sizx, u8 sizy 	)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);

	//メイン処理タスク追加
	pTcb = TCB_Add(t_func,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, posx, posy, sizx, sizy, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//確率フラグ表示
	d_func(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//===============================================================================
//	ウィンドウ共通
//===============================================================================
//初期化
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp)
{
	wp->debug_list = 0;
	wp->debug_cursor = 0;
}
//リストの開放処理
static void DebugListFree(TCB_PTR tcb,void* work)
{
	DEBUG_WINDOW_DATA	*wp;

	wp = (DEBUG_WINDOW_DATA*)work;

	//BMPウィンドウOFF
	GF_BGL_BmpWinOff(&wp->win);

	//BMPリスト破棄
	BmpListExit( wp->lw,&wp->debug_list,&wp->debug_cursor );
	//BMPWindow消去
	GF_BGL_BmpWinDel( &wp->win );
	return;
}
//デバッグウィンドウを解放
static void FreeDebugWindow(TCB_PTR tcb,void* work)
{
	//リストの開放処理
	DebugListFree(tcb,work);
	//ワークメモリ開放
	sys_FreeMemoryEz(work);
}

//デバッグウィンドウを解放(メモリ解放無し)
static void FreeDebugWindowNoFreeMem(TCB_PTR tcb,void* work)
{
	//リストの開放処理
	DebugListFree(tcb,work);
}
//デバッグウィンドウ終了
static void DebugWindowExit(TCB_PTR tcb,void* work)
{
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//タスク消去
	TCB_Delete(tcb);
	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
	return;
}
//リストコントロール
static void DebugListControlTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	DEBUG_WINDOW_DATA	*wp;
	
	wp = (DEBUG_WINDOW_DATA*)work;

	ret_code = BmpListMain(wp->lw);
	//キー操作判定
	if(sys.trg & PAD_BUTTON_A){
		if(ret_code){
			BMP_MENULIST_Delete( wp->ld );	//とりあえず
			func = (TCB_FUNC)ret_code;
			func(tcb,work);
		}
		return;
	}
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		BMP_MENULIST_Delete( wp->ld );	//とりあえず
		DebugWindowExit(tcb,work);
		return;
	}
}

//================================================================================
//	カメラ情報
//================================================================================
static void DrawCameraInfo(GF_CAMERA_PTR camera_ptr,GF_BGL_BMPWIN	*win, const u8 inNo)
{	
	u16 buff[10];
	CAMERA_ANGLE angle;
	u16 angle_x;
	STRBUF *str;
	STRBUF *msg_buf;
	MSGDATA_MANAGER* man;

	GF_BGL_BmpWinDataFill( win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = STRBUF_Create(10, HEAPID_D_SAITO);
	msg_buf = STRBUF_Create(16,HEAPID_D_SAITO);
	
	MSGMAN_GetString(man, D_SAITO_CAM_INFO01 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 0, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO02 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 1*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO03 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 2*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO04 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 3*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO05 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 4*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO06 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 5*16, MSG_ALLPUT, NULL );

	STRBUF_SetHexNumber(	str, GFC_GetCameraDistance(camera_ptr), 8,
							NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 7*8, 0, MSG_ALLPUT, NULL );
	
	angle = GFC_GetCameraAngle(camera_ptr);
	//仰角⇒地面からの傾きに変換
	angle_x = -angle.x;

	STRBUF_SetHexNumber(str, angle.x, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 1*16, MSG_ALLPUT, NULL );
	STRBUF_SetHexNumber(str, angle.y, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 2*16, MSG_ALLPUT, NULL );
	STRBUF_SetHexNumber(str, angle.z, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 3*16, MSG_ALLPUT, NULL );

	STRBUF_SetHexNumber(str, GFC_GetCameraPerspWay(camera_ptr), 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 4*16, MSG_ALLPUT, NULL );

	if (GFC_GetCameraView(camera_ptr) == GF_CAMERA_PERSPECTIV){
		MSGMAN_GetString(man, D_SAITO_CAM_INFO07 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 8*8, 5*16, MSG_ALLPUT, NULL );
	}else{
		MSGMAN_GetString(man, D_SAITO_CAM_INFO08 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 8*8, 5*16, MSG_ALLPUT, NULL );
	}
	
	{
		//ニア・ファー
		int near,far;
		near = GFC_GetCameraNear(camera_ptr)/FX32_ONE;
		far = GFC_GetCameraFar(camera_ptr)/FX32_ONE;
		
		MSGMAN_GetString(man, D_SAITO_CAM_INFO09 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 6*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO10 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 7*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, near, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 6*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, far, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 7*16, MSG_ALLPUT, NULL );
	}
	{
		//注視点
		VecFx32 look_at = GFC_GetLookTarget(camera_ptr);
		MSGMAN_GetString(man, D_SAITO_CAM_INFO11 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 8*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO12 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 9*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO13 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 10*16, MSG_ALLPUT, NULL );
		
		STRBUF_SetHexNumber(str, look_at.x, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 8*16, MSG_ALLPUT, NULL );
		STRBUF_SetHexNumber(str, look_at.y, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 9*16, MSG_ALLPUT, NULL );
		STRBUF_SetHexNumber(str, look_at.z, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 10*16, MSG_ALLPUT, NULL );
	}

	{
		//カメラテーブル番号
		STRBUF_SetNumber(str, inNo, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 11*16, MSG_ALLPUT, NULL );
	}
	
	STRBUF_Delete( msg_buf );
	STRBUF_Delete( str );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( win );
	
}

//カメラ用ウィンドウセット
static void SetCameraDebugWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//カメラウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugCameraMenuList),DebugCameraMenuList, &CameraDebugListWindowData);
	
}
//カメラリストウィンドウ表示中タスク
static void CameraListDispTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->camera_tbl_no == NELEMS(TestOrgCamera)-1){
			d_work->camera_tbl_no=0;
		}else{
			d_work->camera_tbl_no++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->camera_tbl_no == 0){
			d_work->camera_tbl_no = NELEMS(TestOrgCamera)-1;
		}else{
			d_work->camera_tbl_no--;
		}
	}
	
	if (flg == TRUE){
		//カメラパラメータ変更
		//カメラセット
		{
			GFC_InitCameraTDA(
				Player_VecPosPtrGet(d_work->fsys->player),
				TestOrgCamera[d_work->camera_tbl_no].Distance,		// 距離
				&TestOrgCamera[d_work->camera_tbl_no].Angle,		//
				TestOrgCamera[d_work->camera_tbl_no].PerspWay,		// 投射栄の角度
				TestOrgCamera[d_work->camera_tbl_no].View,
				TRUE,
				d_work->camera);
			if (TestOrgCamera[d_work->camera_tbl_no].dummy==1){
				GFC_SetCameraClip(FX32_ONE*150, FX32_ONE*1160,d_work->camera);
			}else if(TestOrgCamera[d_work->camera_tbl_no].dummy==2){
				GFC_SetCameraClip(FX32_ONE*150, FX32_ONE*1735,d_work->camera);
			}
			GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
		}
		//カメラ情報表示
		DrawCameraInfo(d_work->camera,&d_work->win,d_work->camera_tbl_no);
	}

	if (sys.trg & PAD_BUTTON_B){
		//カメラ反映
		GFC_CopyCamera(d_work->camera,d_work->fsys->camera_ptr);
		//カメラ削除
		GFC_FreeCamera(d_work->camera);
		//カメラアタッチ
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

//カメラ情報ウィンドウ表示中タスク
static void CameraInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		//カメラ削除
		GFC_FreeCamera(d_work->camera);
		//カメラアタッチ
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

//カメラ情報用ウィンドウ構築
static void SetCameraInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->camera_tbl_no = 0;
	
	d_work->fsys = fsys;
	//カメラ生成
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	GFC_CopyCamera(d_work->fsys->camera_ptr, d_work->camera);
	GFC_AttachCamera(d_work->camera);
	//メイン処理タスク追加
	pTcb = TCB_Add(CameraInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 24, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//カメラ情報表示
	DrawCameraInfo(d_work->camera,&d_work->win, d_work->camera_tbl_no);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//カメラリスト用ウィンドウ構築
static void SetCameraListWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->camera_tbl_no = 0;
	
	d_work->fsys = fsys;
	//カメラ生成
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	{
		GFC_InitCameraTDA(
				Player_VecPosPtrGet(fsys->player),
				TestOrgCamera[0].Distance,		// 距離
				&TestOrgCamera[0].Angle,		//
				TestOrgCamera[0].PerspWay,		// 投射栄の角度
				TestOrgCamera[0].View,
				TRUE,
				d_work->camera);
		GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
	}
	GFC_AttachCamera(d_work->camera);
	//メイン処理タスク追加
	pTcb = TCB_Add(CameraListDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 24, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//カメラ情報表示
	DrawCameraInfo(d_work->camera,&d_work->win, d_work->camera_tbl_no);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//カメラ情報用ウィンドウセット
static void SetupCameraInfoWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//カメラ情報ウィンドウ構築
	SetCameraInfoWindow(fsys);
}

//カメラリスト用ウィンドウセット
static void SetupCameraListWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//カメラ情報ウィンドウ構築
	SetCameraListWindow(fsys);
}

//揺れ草レコード表示
static void DrawSwayGrassRec(struct _FIELDSYS_WORK * fsys, GF_BGL_BMPWIN	*win)
{
	int i;
	GF_BGL_BmpWinDataFill( win, 0x0f );

	for (i=0;i<3;i++){
		SWAY_GRASS_HIST * hist;
		int chain;
		int monsno;
		hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
		chain = hist->SwayGrassRec[i].Chain;
		monsno = hist->SwayGrassRec[i].MonsNo;
		{
			//ポケモン名取得のため、ポケモン生成
			STRBUF *name_buf;
			name_buf = MSGDAT_UTIL_GetMonsName( monsno, HEAPID_D_SAITO );

			GF_STR_PrintSimple( win, FONT_SYSTEM, name_buf, 0, 16*i, MSG_ALLPUT, NULL );
			{
				STRBUF* str = STRBUF_Create(10, HEAPID_D_SAITO);
				STRBUF_SetNumber( str, chain, 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
				GF_STR_PrintSimple(win, FONT_SYSTEM, str, 10*8, 16*i, MSG_ALLPUT, NULL );
				STRBUF_Delete(str);
			}
			STRBUF_Delete(name_buf);
		}
	}
	
	GF_BGL_BmpWinOn( win );
	
}

//揺れ草レコード・情報ウィンドウ表示中タスク
static void SwayGrassInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

//揺れ草レコード用ウィンドウ構築
static void SetSwayGrassRecWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = fsys;
	//メイン処理タスク追加
	pTcb = TCB_Add(SwayGrassInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 6, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//揺れ草レコード表示
	DrawSwayGrassRec(fsys, &d_work->win);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//揺れ草レコード表示
static void DispSwayGrassRec(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//揺れ草情報ウィンドウ構築
	SetSwayGrassRecWindow(fsys);

}

static void CameraControlTask(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;
	(void)CameraInput(d_work->camera);


	if ( (sys.cont & PAD_BUTTON_B) && (sys.trg & PAD_BUTTON_X) ){

		//カメラセット
		{
			GFC_InitCameraTDA(
				Player_VecPosPtrGet(d_work->fsys->player),
				TestOrgCamera[0].Distance,		// 距離
				&TestOrgCamera[0].Angle,		//
				TestOrgCamera[0].PerspWay,		// 投射栄の角度
				TestOrgCamera[0].View,
				TRUE,
				d_work->camera);

			GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
		}
	}

	if (sys.cont & PAD_BUTTON_L){
		//カメラ反映
		GFC_CopyCamera(d_work->camera,d_work->fsys->camera_ptr);
		//カメラ削除
		GFC_FreeCamera(d_work->camera);
		//カメラアタッチ
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		//ワークメモリ開放
		sys_FreeMemoryEz(d_work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

static void SetCamera(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;

	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = wp->fsys;
	//カメラ生成
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	GFC_CopyCamera(d_work->fsys->camera_ptr, d_work->camera);
	GFC_AttachCamera(d_work->camera);
	
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ解放
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//タスクセット
	TCB_Add(CameraControlTask,d_work,0);

}

//-----------------------------------------------------------------------------
//	アクセス関数
//-----------------------------------------------------------------------------
//デバッグメインウィンドウ構築関数
void DBGSAI_MapNumDebugListSet(struct _FIELDSYS_WORK * fsys)
{
	MakeBmpList(fsys, NELEMS(DebugMenuMainList), DebugMenuMainList, &MainDebugListWindowData);
}

static int DebugPlayerHeightOfs = 0;

//高さを変える
static void HeightChangeTask(TCB_PTR tcb,void* work)
{
	VecFx32 *ofs;
	const VecFx32 *vec;
	
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;
	
	ofs = Player_VecDrawOffsPtrGet( d_work->fsys->player );
	vec = Player_VecPosPtrGet(d_work->fsys->player);
//	BLACT_WORK* bl_w;
//	bl_w = BLACT_WorkGet(FldBlActIdx, map3Ddata->actor[0].actorno);
	
	if (sys.trg & PAD_KEY_UP){
		OS_Printf("デバッグ：高さUP\n");
		DebugPlayerHeightOfs++;
		ofs->y += (FX32_ONE/4);
//		bl_w->Matrix.y+= (FX32_ONE/4);
	}else if (sys.trg & PAD_KEY_DOWN){
		OS_Printf("デバッグ：高さDOWN\n");
		DebugPlayerHeightOfs--;
		ofs->y -= (FX32_ONE/4);
//		bl_w->Matrix.y-= (FX32_ONE/4);
	}

	if (sys.trg & PAD_BUTTON_X){
		//リセット
		OS_Printf("デバッグ：高さリセット\n");
		DebugPlayerHeightOfs = 0;
		ofs->y = vec->y;
		ofs->y += (FX32_ONE*16);

//		bl_w->Matrix.y = map3Ddata->actor[0].global.y;
//		bl_w->Matrix.y+=(FX32_ONE*16);
	}
	
	if (sys.trg & PAD_BUTTON_B){
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

//高さ変更タスクセット
static void SetPlayerHeightChangeTask(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = wp->fsys;	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//タスクセット
	TCB_Add(HeightChangeTask,d_work,0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#define ATTR_DISP_W_NUM	(3)
#define ATTR_DISP_H_NUM	(3)
#define ATTR_ONE_DISP_SIZE (5)
typedef struct {
	GF_BGL_BMPWIN	win;//BMP
	GF_BGL_BMPWIN	win2;//BMP
	FIELDSYS_WORK * fsys;
}ATTR_CONT;

//アトリビュート情報表示
static void DispAttrInfo(ATTR_CONT *work)
{	
	GF_BGL_BmpWinDataFill( &work->win, 0x0f );
	GF_BGL_BmpWinDataFill( &work->win2, 0x0f );
	
	//自機の位置のアトリビュートを表示
	{
		int grid_x,grid_z,height;
		int base_x,base_z;
		int x,z;
		u8 i,j;
		u8 disp_ofs_x;
		BOOL rc;
		u8 attr;
		
		MSGDATA_MANAGER* man;
		STRBUF *msg_buf;
		STRBUF* str;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
		msg_buf = STRBUF_Create(16,HEAPID_D_SAITO);
		str = STRBUF_Create(4, HEAPID_D_SAITO);

		//自機グリッド座標を取得
		grid_x = Player_NowGPosXGet( work->fsys->player );
		grid_z = Player_NowGPosZGet( work->fsys->player );
		{
			VecFx32 vec;
			Player_VecPosGet( work->fsys->player, &vec );
			height = vec.y/(FX32_ONE*16);
		}

		base_x = grid_x-1;
		base_z = grid_z-1;
		
		for (i=0;i<3;i++){
			z = base_z+i;
			for(j=0;j<3;j++){
				disp_ofs_x = ATTR_ONE_DISP_SIZE*j*8;
				x = base_x+j;
				//アトリビュート取得
				rc = GetHitAttr(work->fsys, x, z);

				if (rc){
					MSGMAN_GetString(man, D_SAITO_ATTR01 ,msg_buf);
					GF_STR_PrintSimple(&work->win, FONT_SYSTEM, msg_buf, disp_ofs_x, i*16, MSG_ALLPUT, NULL );
				}else{
					MSGMAN_GetString(man, D_SAITO_ATTR02 ,msg_buf);
					GF_STR_PrintSimple(&work->win, FONT_SYSTEM, msg_buf, disp_ofs_x, i*16, MSG_ALLPUT, NULL );
				}
				
				attr = GetAttributeLSB(work->fsys, x, z);
				STRBUF_SetHexNumber( str, attr, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
				GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str, disp_ofs_x+2*8, i*16, MSG_ALLPUT, NULL );
			}
		}
			
		//自機グリッドから、ブロック座標、ブロック内ローカル座標を計算
		{
			int block_x,block_z;
			u8 local_x,local_z;
			u8 ofs = 6*8;
			u8 item_ofs = 3*8;
			block_x = grid_x/32;
			block_z = grid_z/32;
			local_x = grid_x%32;
			local_z = grid_z%32;
			
			MSGMAN_GetString(man, D_SAITO_ATTR03 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 0, MSG_ALLPUT, NULL );
			MSGMAN_GetString(man, D_SAITO_ATTR04 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 16, MSG_ALLPUT, NULL );
			MSGMAN_GetString(man, D_SAITO_ATTR05 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 32, MSG_ALLPUT, NULL );

			STRBUF_SetNumber( str, block_x, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 0, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, block_z, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+item_ofs, 0, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, local_x, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 16, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, local_z, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+item_ofs, 16, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, height, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 32, MSG_ALLPUT, NULL );
			
		}
		STRBUF_Delete(str);
		STRBUF_Delete( msg_buf );
		MSGMAN_Delete( man );
	}
	
	GF_BGL_BmpWinOn( &work->win );
	GF_BGL_BmpWinOn( &work->win2 );
}

//アトリビュート確認コントロール
static void DebugCheckAttrControlTask(TCB_PTR tcb,void* work)
{
	ATTR_CONT	*wp;
	wp = (ATTR_CONT*)work;
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		GF_BGL_BmpWinOff( &wp->win2 );
		GF_BGL_BmpWinDel( &wp->win2 );
		//ワークメモリ開放
		sys_FreeMemoryEz(work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}

//アトリビュート確認
void DBGSAI_CheckAttribute(struct _FIELDSYS_WORK * fsys)
{
	ATTR_CONT *d_work;
	int size_w,size_h;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(ATTR_CONT));
	d_work->fsys = fsys;
	
	size_w = ATTR_ONE_DISP_SIZE*ATTR_DISP_W_NUM;
	size_h =  2*ATTR_DISP_H_NUM;
	
	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0,
			size_w,size_h, 1, 1 );

	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win2,GF_BGL_FRAME3_M, 0, 18,
			6+3*2, 3*2, 1, 1+size_w*size_h );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//メイン処理タスク追加
	TCB_Add(DebugCheckAttrControlTask,d_work,0);
	//情報表示
	DispAttrInfo(d_work);
}

static BOOL DebugCheckHeightGridIn(	struct _FIELDSYS_WORK * fsys,
									const int inGridX,
									const int inGridZ,
									const BOOL inRoop,
									const BOOL inDetail)
{
	u8 idx;
	u8 rc;
	int i,j;
	fx32 base_x,x,base_z,z;
	MHI_CONST_PTR  height_info;
	fx32 x_ofs,z_ofs;
	int count;
	BOOL block_result;
	int non_height_count;
	
	//グリッドをfx32に
	base_x = inGridX*16*FX32_ONE;
	base_z = inGridZ*16*FX32_ONE;

	idx = GetNowLocalIndex(fsys->map_cont_dat);
	height_info = GetDivMapHeightInfo(fsys->map_cont_dat,idx);
	
	{
		//ブロックオフセット分を減算
		x_ofs = (((inGridX/32)*BLOCK_GRID_W)+(BLOCK_GRID_W/2))*16*FX32_ONE;
		z_ofs = (((inGridZ/32)*BLOCK_GRID_H)+(BLOCK_GRID_H/2))*16*FX32_ONE;
		base_x -= x_ofs;
		base_z -= z_ofs;
	}

	count = 0;
	block_result = FALSE;
	non_height_count = 0;
	for(i=0;i<16;i++){
		x = base_x+(i*FX32_ONE);
		for(j=0;j<16;j++){
			z = base_z+(j*FX32_ONE);
			rc = HC_DebugCheckHeight(x, z, height_info, inDetail);
			if (rc==1){
				if (inRoop == FALSE){
					//return TRUE;
					block_result = TRUE;
				}else{
					OS_Printf("ユニット内座標%d,%dは複数の高さを持っています\n",i,j);
					count++;
				}
			}else if(rc==2){
				if (inRoop == FALSE){
					if (block_result != TRUE){
						//return FALSE;
						block_result = FALSE;
					}
				}else{
					OS_Printf("ユニット内座標%d,%dは同じ高さを複数持っています\n",i,j);
				}

			}else if(rc==3){
				non_height_count++;
				if (inRoop == FALSE){
					if (block_result != TRUE){
						//return FALSE;
						block_result = FALSE;
					}
				}else{
					OS_Printf("ユニット内座標%d,%dは高さを持っていません\n",i,j);
				}
			}
		}
	}
	if (inRoop == FALSE){
		if (non_height_count!=256){//１グリッド全て高さが無かったとき以外
			OS_Printf("グリッド内に高さのない場所があります\n");
		}
		return block_result;
	}

	if (inDetail){
		OS_Printf("グリッド内には、複数の高さを持つユニットが%d箇所存在します\n",count);
	}
	
	if (count>0){
		return TRUE;
	}else{
		return FALSE;
	}
}

static void DebugCheckHeightGrid(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp = (DEBUG_WINDOW_DATA *)work;
	//高さデバッグ
	{
		u8 idx;
		int i,j;
		int grid_x,grid_z;
		VecFx32 base,vec;
		fx32 x_ofs,z_ofs;
		MHI_CONST_PTR  height_info;
		BOOL rc;
		
		Player_VecPosGet(wp->fsys->player, &base);

		//基点
		base.x-=(8*FX32_ONE);
		base.z-=(8*FX32_ONE);

		grid_x = Player_NowGPosXGet( wp->fsys->player );
		grid_z = Player_NowGPosZGet( wp->fsys->player );
		{
			int local_x,local_z;
			local_x = grid_x%32;
			local_z = grid_z%32;

			OS_Printf("\n//ブロック内グリッド座標%d,%dの高さをチェック\n",local_x,local_z);
		}

		DebugCheckHeightGridIn(wp->fsys,
				grid_x,
				grid_z,
				TRUE, TRUE);
		
	}
	DebugWindowExit(tcb,work);
}

static void DebugCheckHeightBlock(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp = (DEBUG_WINDOW_DATA *)work;
	//高さデバッグ
	{
		int i,j;
		int block_x,block_z;
		int base_grid_x,base_grid_z;
		BOOL rc;
		int count;
		block_x = Player_NowGPosXGet( wp->fsys->player )/BLOCK_GRID_W;
		block_z = Player_NowGPosZGet( wp->fsys->player )/BLOCK_GRID_H;

		OS_Printf("\n//ブロック%d,%dの高さをチェック\n",block_x,block_z);

		count = 0;
		for(i=0;i<32;i++){
			base_grid_x = block_x*32+i;
			for(j=0;j<32;j++){
				base_grid_z = block_z*32+j;
				rc = DebugCheckHeightGridIn(wp->fsys, base_grid_x, base_grid_z, FALSE, FALSE);
				if (rc){
					OS_Printf("高さ２層以上のグリッド：%d,%d\n",i,j);
					count++;
				}
			}
		}
		OS_Printf("２層以上の高さを持つグリッドを%d個発見\n",count);
	}

	DebugWindowExit(tcb,work);
}

static void SetSwayGrass(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	{
		u8 *charge;
		charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
		(*charge)=POKESEARCHER_CHARGE_MAX;
	}
	
	//揺れ草セット
	SwayGrass_Setup(wp->fsys);
	
	DebugWindowExit(tcb,work);
}

/////////////////////////////////////////////揺れ草関連//////////////////////////////////////////

//揺れ草メイン
static void DebugWinSwayGrass(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugSwayGrassMenuList), DebugSwayGrassMenuList, &SwayDebugListWindowData);
}

//アニメナンバー表示
static void DrawChain(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, SwayGrass_GetChain(d_work->fsys), 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//揺れ草チェーン表示中タスク
static void ChainDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		SwayGrass_DebugIncChain(d_work->fsys,1);
	}else if(sys.repeat & PAD_KEY_DOWN){
		SwayGrass_DebugIncChain(d_work->fsys,-1);
	}else if (sys.repeat & PAD_KEY_RIGHT){
		SwayGrass_DebugIncChain(d_work->fsys,10);
	}else if(sys.repeat & PAD_KEY_LEFT){
		SwayGrass_DebugIncChain(d_work->fsys,-10);
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawChain(d_work);
	}
	
	if ((sys.trg & PAD_BUTTON_B)||(sys.trg & PAD_BUTTON_A)){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}
}

//チェーン用ウィンドウ構築
static void SetChainWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(10, HEAPID_D_SAITO);
	//メイン処理タスク追加
	pTcb = TCB_Add(ChainDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 4, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//チェーン表示
	DrawChain(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//チェーン指定ウィンドウセット
static void SetupSwayGrassChain(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetChainWindow(fsys);
}

//揺れ草情報表示
static void DrawSwayGrassInfo(struct _FIELDSYS_WORK * fsys, GF_BGL_BMPWIN	*win)
{
	int i;
	GF_BGL_BmpWinDataFill( win, 0x0f );

	for (i=0;i<4;i++){
		int x,z;
		u8 tbl;
		BOOL valid,chain,rare;
		
		SwayGrass_GetGrassInfo(fsys, i,
							&x, &z, &tbl,&valid, &chain, &rare);

		{
			STRBUF* str = STRBUF_Create(10, HEAPID_D_SAITO);
			STRBUF_SetNumber( str, x%32, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 0*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, z%32, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 4*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, tbl, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, valid, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 10*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, chain, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 12*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, rare, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 14*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_Delete(str);
		}
	}
	
	GF_BGL_BmpWinOn( win );
	
}

//揺れ草情報用ウィンドウ構築
static void SetSwayGrassInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = fsys;
	//メイン処理タスク追加
	pTcb = TCB_Add(SwayGrassInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 16, 8, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//揺れ草レコード表示
	DrawSwayGrassInfo(fsys, &d_work->win);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//揺れ草情報表示
static void DispSwayGrassInfo(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//揺れ草情報ウィンドウ構築
	SetSwayGrassInfoWindow(fsys);

}

/////////////////////釣り
extern u8 DebugFishProbFlg;
static void DrawSpFishingPoint(DEBUG_WORK_DATA *d_work);
//釣りメイン
static void DebugWinFishing(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
}

//釣竿ナンバー表示
static void DrawFishingRod(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, d_work->rod, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//ロッド表示中タスク
static void RodDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		d_work->rod++;
		if (d_work->rod>2){
			d_work->rod = 0;
		}
	}else if(sys.repeat & PAD_KEY_DOWN){
		d_work->rod--;
		if (d_work->rod<0){
			d_work->rod = 2;
		}
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawFishingRod(d_work);
	}

	if (sys.trg & PAD_BUTTON_A){
		BOOL rc;

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
		rc = DebugSetFishingEncount( d_work->fsys, d_work->rod );
		OS_Printf("fishing = %d\n",rc);
		
		sys_FreeMemoryEz((void *)work);	
	}else if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//釣り用ウィンドウ構築
static void SetFishingRodWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);
	d_work->rod = 0;
	//メイン処理タスク追加
	pTcb = TCB_Add(RodDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 2, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//ロッド表示
	DrawFishingRod(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}
//釣り竿指定ウィンドウセット
static void SetupFishingRod(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetFishingRodWindow(fsys);
}

//釣り確率フラグ表示
static void DrawFishingProb(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, DebugFishProbFlg, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//確率フラグ表示中タスク
static void FishProbDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if ( (sys.trg & PAD_KEY_UP) ||
			(sys.trg & PAD_KEY_DOWN)){
		DebugFishProbFlg = (DebugFishProbFlg+1)%2;
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawFishingProb(d_work);
	}

	if ( (sys.trg & PAD_BUTTON_A) ||
			(sys.trg & PAD_BUTTON_B) ){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//釣り用ウィンドウ構築
static void SetFishingProbWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);

	//メイン処理タスク追加
	pTcb = TCB_Add(FishProbDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 2, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//確率フラグ表示
	DrawFishingProb(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//釣り確率フラグ指定ウィンドウセット
static void SetupFishingProb(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetFishingProbWindow(fsys);
}

//特殊釣りポイント表示中タスク
static void SpFishPointDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if ( sys.trg & PAD_BUTTON_B) {
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//特殊釣りポイントウィンドウ構築
static void SetSpFishingPointWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);

	//メイン処理タスク追加
	pTcb = TCB_Add(SpFishPointDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 8, 10, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//ポイント表示
	DrawSpFishingPoint(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}
//特殊釣りポイントウィンドウセット
static void SetupSpFishingPoint(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetSpFishingPointWindow(fsys);
}

//特殊釣りポイント表示
static void DrawSpFishingPoint(DEBUG_WORK_DATA *d_work)
{
	int pos[8];
	u32 rnd;
	STRBUF *str;
	MSGDATA_MANAGER* man;
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;

	{

		DEBUGSpFishing_GetPoint(d_work->fsys, pos, &rnd);
		STRBUF_SetHexNumber(str, rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 0*16, MSG_ALLPUT, NULL );
		
		STRBUF_SetNumber(str, pos[0], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[1], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 1*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[2], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[3], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 2*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[4], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 3*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[5], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 3*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[6], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 4*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[7], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 4*16, MSG_ALLPUT, NULL );
	}

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}


/////////////////////////////////////////////////////////////////////////////////////////
//移動ポケモン
static void SetMovePokeInfoWindow(struct _FIELDSYS_WORK * fsys);
static void DrawMovePokeInfo(DEBUG_WORK_DATA *d_work);
static void MovePokeInfoDispTask(TCB_PTR tcb,void* work);

static void SetEntryMovePokeWindow(struct _FIELDSYS_WORK * fsys);
static void DrawMovePokeName(DEBUG_WORK_DATA *d_work);
static void EntryMovePokeTask(TCB_PTR tcb,void* work);

static void SetMovePokeZoneChgWin(struct _FIELDSYS_WORK * fsys, const u16 inPos);
static void DrawMovePokeZone(DEBUG_WORK_DATA *d_work);
static void MovePokeZoneDispTask(TCB_PTR tcb,void* work);

//メイン
static void DebugWinMovePoke(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
}

//情報表示ウィンドウセット
static void SetupMovePokeInfo(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetMovePokeInfoWindow(fsys);
}

//移動ポケモン情報ウィンドウ構築
static void SetMovePokeInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	//メイン処理タスク追加
	pTcb = TCB_Add(MovePokeInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 16, 18, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//情報表示
	DrawMovePokeInfo(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//移動ポケモン情報表示
static void DrawMovePokeInfo(DEBUG_WORK_DATA *d_work)
{
	STRBUF *str;
	STRBUF *msg_buf;
	MSGDATA_MANAGER* man;
	MPD_PTR mpd;
	ENC_SV_PTR data;
	
	int poke_name_list[MOVE_POKE_MAX] = {	D_SAITO_MP_AI,
											D_SAITO_MP_MUUBASU,
											D_SAITO_MP_DAAKU	};	//アイ、ムーバス、ダーク
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;
	msg_buf = d_work->StrBuf;

	//セーブデータ取得
	data = EncDataSave_GetSaveDataPtr(d_work->fsys->savedata);
	mpd = EncDataSave_GetMovePokeDataPtr(data, d_work->MovePokeInfoNo);


	{
		int zone_id = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_ZONE_ID);
		int monsno = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO);
		u32 pow_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_POW_RND);
		u32 per_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_PER_RND);
		u8 hp = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_HP);
		u8 lv = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV);
		u8 cond = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_COND);
		u8 enc = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_ENC);

		//ポケモン名
		MSGMAN_GetString(man, poke_name_list[d_work->MovePokeInfoNo] ,msg_buf);		
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, msg_buf, 1*8, 0, MSG_ALLPUT, NULL );
		//モンスターナンバー
		STRBUF_SetNumber(str, monsno, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );
		//レベル
		STRBUF_SetNumber(str, lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );
		//HP
		STRBUF_SetNumber(str, hp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 3*16, MSG_ALLPUT, NULL );
		//パワー乱数
		STRBUF_SetHexNumber(str, pow_rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 4*16, MSG_ALLPUT, NULL );
		//個性乱数
		STRBUF_SetHexNumber(str, per_rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 5*16, MSG_ALLPUT, NULL );
		//状態
		STRBUF_SetNumber(str, cond, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 6*16, MSG_ALLPUT, NULL );
		//場所
		STRBUF_SetNumber(str, zone_id, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 7*16, MSG_ALLPUT, NULL );
		PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, msg_buf);
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, msg_buf, 4*8, 7*16, MSG_ALLPUT, NULL );
		//エンカウントフラグ
		STRBUF_SetNumber(str, enc, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 8*16, MSG_ALLPUT, NULL );

		OS_Printf("pow=%u\n",pow_rnd);
		OS_Printf("per=%u\n",per_rnd);
	}
	
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//移動ポケモン情報表示タスク
static void MovePokeInfoDispTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == MOVE_POKE_MAX-1){
			d_work->MovePokeInfoNo = 0;
		}else{
			d_work->MovePokeInfoNo++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == 0){
			d_work->MovePokeInfoNo = MOVE_POKE_MAX-1;
		}else{
			d_work->MovePokeInfoNo--;
		}
	}
	
	if (flg == TRUE){
		//移動ポケモン情報表示
		DrawMovePokeInfo(d_work);
	}

	if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//移動ポケモンメニューメインへ
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

static void SetupEntryMovePoke(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetEntryMovePokeWindow(fsys);
}

//移動ポケモンエントリウィンドウ構築
static void SetEntryMovePokeWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(16, HEAPID_D_SAITO); //移動ポケモン名を表示
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	//メイン処理タスク追加
	pTcb = TCB_Add(EntryMovePokeTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 6, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//情報表示
	DrawMovePokeName(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//移動ポケモン名表示
static void DrawMovePokeName(DEBUG_WORK_DATA *d_work)
{
	MSGDATA_MANAGER* man;
	
	int poke_name_list[MOVE_POKE_MAX] = {	D_SAITO_MP_AI,
											D_SAITO_MP_MUUBASU,
											D_SAITO_MP_DAAKU	};	//アイ、ムーバス、ダーク
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);

	//ポケモン名
	MSGMAN_GetString(man, poke_name_list[d_work->MovePokeInfoNo] ,d_work->StrBuf);		
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 1*8, 0, MSG_ALLPUT, NULL );
	
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//エントリ移動ポケモン選択タスク
static void EntryMovePokeTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == MOVE_POKE_MAX-1){
			d_work->MovePokeInfoNo = 0;
		}else{
			d_work->MovePokeInfoNo++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == 0){
			d_work->MovePokeInfoNo = MOVE_POKE_MAX-1;
		}else{
			d_work->MovePokeInfoNo--;
		}
	}
	
	if (flg == TRUE){
		//移動ポケモン情報表示
		DrawMovePokeName(d_work);
	}
	
	if (sys.trg & PAD_BUTTON_A){
		//エントリ
		MP_AddMovePoke(d_work->fsys->savedata, d_work->MovePokeInfoNo);
		Snd_SePlay( SEQ_SE_DP_SELECT );		//登録したら鳴らしとく
		
	}else if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//移動ポケモンメニューメインへ
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

//移動ポケモン名メイン
static void DebugWinMovePokeName(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugMovePokeNameList), DebugMovePokeNameList, &MovePokeNameDebugListWindowData);
}

//ゾーン変更ウィンドウセット
static void SetupMovePokeZoneChgWin(TCB_PTR tcb,void *work)
{
	u16 pos;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す(ワークは残す)
	FreeDebugWindowNoFreeMem(tcb,work);
	pos = wp->debug_cursor;
	//ワークメモリ開放
	sys_FreeMemoryEz(work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetMovePokeZoneChgWin(fsys,pos);
}

//移動ポケモンゾーンウィンドウ構築
static void SetMovePokeZoneChgWin(struct _FIELDSYS_WORK * fsys, const u16 inPos)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->MovePokeInfoNo = inPos;
	{
		ENC_SV_PTR data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		if ( EncDataSave_IsMovePokeValid(data, d_work->MovePokeInfoNo) ){
			d_work->zone_idx = EncDataSave_GetMovePokeZoneIdx(data, d_work->MovePokeInfoNo);
		}else{
			d_work->zone_idx = LOCATION_MAX;
		}
	}
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO); //ゾーン名を表示
	//メイン処理タスク追加
	pTcb = TCB_Add(MovePokeZoneDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 18, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//情報表示
	DrawMovePokeZone(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//移動ポケモンゾーン表示
static void DrawMovePokeZone(DEBUG_WORK_DATA *d_work)
{
	int zone_id;
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	
	//ゾーン名取得
	if ((d_work->zone_idx>=0)&&(d_work->zone_idx<LOCATION_MAX)){
		zone_id = MP_GetMovePokeZone(d_work->zone_idx);
	}else{
		zone_id = 0;
	}
	PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, d_work->StrBuf);
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//移動ポケモンゾーン表示中タスク
static void MovePokeZoneDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		d_work->zone_idx++;
		if (d_work->zone_idx>=LOCATION_MAX){
			d_work->zone_idx = 0;
		}
	}else if(sys.repeat & PAD_KEY_DOWN){
		d_work->zone_idx--;
		if (d_work->zone_idx<0){
			d_work->zone_idx = LOCATION_MAX-1;
		}
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawMovePokeZone(d_work);
	}

	if ( sys.trg & PAD_BUTTON_A ){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		Snd_SePlay( SEQ_SE_DP_SELECT );		//場所変更したら鳴らしとく
		//場所変更
		MP_DebugUpdateData( EncDataSave_GetSaveDataPtr(fsys->savedata),
							d_work->MovePokeInfoNo, d_work->zone_idx);

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//タスク消去
		TCB_Delete(tcb);
		sys_FreeMemoryEz((void *)work);
		//移動ポケモンメニューメインへ
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}else if(sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//タスク消去
		TCB_Delete(tcb);
		sys_FreeMemoryEz((void *)work);
		//移動ポケモンメニューメインへ
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

//////////////////////////////////////////////////////////////////////////////
static void SetGeneZoneInfoWin(struct _FIELDSYS_WORK * fsys);
static void DrawGeneZone(DEBUG_WORK_DATA *d_work);
static void GeneInfoDispTask(TCB_PTR tcb,void* work);
//大量発生
static void DebugGenerate(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugGeneMenuList), DebugGeneMenuList, &GeneDebugListWindowData);	
}

//大量発生情報表示セットアップ
static void SetupGeneZoneInfoWin(TCB_PTR tcb,void *work)
{
	u16 pos;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//ウィンドウ構築
	SetGeneZoneInfoWin(fsys);
}

//大量発生開始
static void DebugStartGenerate(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
	//大量発生開始
	EncDataSave_StartGenerate( fsys->savedata );
	Snd_SePlay( SEQ_SE_DP_SELECT );		//発生させたら鳴らしとく
}

//大量発生情報表示セットアップ
static void SetGeneZoneInfoWin(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO); //ゾーン名を表示
	//メイン処理タスク追加
	pTcb = TCB_Add(GeneInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 18, 4, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//情報表示
	DrawGeneZone(d_work);

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}

//大量発生場所表示
static void DrawGeneZone(DEBUG_WORK_DATA *d_work)
{
	ENC_SV_PTR data;
	MSGDATA_MANAGER* man;

	int zone_id;
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);

	data = EncDataSave_GetSaveDataPtr(d_work->fsys->savedata);
	
	//ゾーン名取得
	zone_id = GenerateZone_GetZone( EncDataSave_GetRandSeed(data,  ENC_RND_SEED_GENERATE) );
	PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, d_work->StrBuf);
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
	if(EncDataSave_IsGenerate( data )){
		MSGMAN_GetString(man, D_SAITO_GENE_ON ,d_work->StrBuf);		
	}else{
		MSGMAN_GetString(man, D_SAITO_GENE_OFF ,d_work->StrBuf);
	}
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 16, MSG_ALLPUT, NULL );
	MSGMAN_Delete( man );
}

//発生場所表示中タスク
static void GeneInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//大量発生メイン
		MakeBmpList(d_work->fsys, NELEMS(DebugGeneMenuList), DebugGeneMenuList, &GeneDebugListWindowData);
	}
}

////////////////////////////////////////////////////////////////////
static void DrawSafariInfo(DEBUG_WORK_DATA *d_work);
static void SetSafariInfoWindow(struct _FIELDSYS_WORK * fsys);
static void SafariInfoDispTask(TCB_PTR tcb,void* work);

static void DebugSafari(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();

	
	//ウィンドウ構築
	SetSafariInfoWindow(fsys);
}

//サファリ情報ウィンドウ構築
static void SetSafariInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	d_work->SafariArea = 0;
	//メイン処理タスク追加
	pTcb = TCB_Add(SafariInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 10, 6, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//情報表示
	DrawSafariInfo(d_work);

	return;
}

//サファリ情報表示タスク
static void SafariInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = work;

	BOOL draw = FALSE;
	if (sys.trg & PAD_KEY_UP){
		draw = TRUE;
		d_work->SafariArea = (d_work->SafariArea+1)%6;
	}else if (sys.trg & PAD_KEY_DOWN){
		draw = TRUE;
		if (d_work->SafariArea != 0){
			d_work->SafariArea--;
		}else {
			d_work->SafariArea = 5;
		}
	}

	if (draw){
		DrawSafariInfo(d_work);
	}

	
	if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//タスク消去
		TCB_Delete(tcb);
		//OBJ等の動作停止解除
		FieldSystemProc_SeqHoldEnd();
	}

}

//サファリ情報表示
static void DrawSafariInfo(DEBUG_WORK_DATA *d_work)
{
	STRBUF *str;
	MSGDATA_MANAGER* man;
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;

	{
		u32 seed;
		int idx1;
		int mons1;
		
		seed = EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(d_work->fsys->savedata),ENC_RND_SEED_SAFARI);
		//サファリ乱数
		STRBUF_SetHexNumber(str, seed, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 0*16, MSG_ALLPUT, NULL );
		
		//エントリテーブルインデックス表示
		SafariEnc_DebugGetSafariTbl(seed,
									ZukanWork_GetZenkokuZukanFlag(
										SaveData_GetZukanWork(GameSystem_GetSaveData(d_work->fsys))),
									d_work->SafariArea,
									&idx1, &mons1);
		STRBUF_SetNumber(str, d_work->SafariArea, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, idx1, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, mons1, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 2*16, MSG_ALLPUT, NULL );
	
	}

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//AGB
static void DebugSetAgbVer(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//メインウィンドウを消す
	FreeDebugWindow(tcb,work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//イベントフック
	FieldSystemProc_SeqHold();
	//ウィンドウ構築
	MakeBmpList(fsys, NELEMS(DebugAgbMenuList), DebugAgbMenuList, &AgbDebugListWindowData);
}

//ＡＧＢスロットバージョン変更
static void DebugAgbVer(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp;
	//メインウィンドウを消す(ワークは残す)
	FreeDebugWindowNoFreeMem(tcb,work);
	
	wp = (DEBUG_WINDOW_DATA *)work;

	switch(wp->debug_cursor){
	case 0:
		sys.AgbCasetteVersion = 0;
		break;
	case 1:
		sys.AgbCasetteVersion = VERSION_SAPPHIRE;
		break;
	case 2:
		sys.AgbCasetteVersion = VERSION_RUBY;
		break;
	case 3:
		sys.AgbCasetteVersion = VERSION_EMERALD;
		break;
	case 4:
		sys.AgbCasetteVersion = VERSION_RED;
		break;
	case 5:
		sys.AgbCasetteVersion = VERSION_GREEN;
		break;
	}

	OS_Printf("ver:%d\n",sys.AgbCasetteVersion);

	Snd_SePlay( SEQ_SE_DP_SELECT );		//発生させたら鳴らしとく

	//ワークメモリ開放
	sys_FreeMemoryEz(work);
	//メインウィンドウタスク消去
	TCB_Delete(tcb);
	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
}

#endif	//#ifdef PM_DEBUG
