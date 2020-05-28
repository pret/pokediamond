//============================================================================================
/**
 *	@file	fld_debug.c
 *	@brief	フィールドデバッグメニュー用ソース
 *
 *	@date	04/12/17
 *	@author	Game Freak Inc.
 */
//============================================================================================

#ifdef	PM_DEBUG


#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "system/fontproc.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/debug_flag.h"
#include "debug_saito.h"
#include "d_tomoya.h"
#include "d_taya.h"

#include "ev_mapchange.h"
#include "fld_debug.h"
#include "zonedata.h"
#include "div_map.h"
#include <ctype.h>
#include "system/builddate.h"
#include "system/window.h"

#include "mapdefine.h"

#include "system/snd_tool.h"
#include "field/field.h"
#include "poketool/poke_tool.h"
#include "poketool/status_rcv.h"
#include "poketool/pokeparty.h"
#include "itemtool/myitem.h"
#include "itemtool/itemsym.h"

#include "tv_topic.h"
#include "system/pm_rtc.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "field/field_matrix.h"
#include "battle/battle_common.h"
#include "savedata/savedata.h"
#include "savedata/tv_work.h"
#include "savedata/record.h"
#include "savedata/b_tower.h"
#include "savedata/pokepark_data.h"
#include "savedata/gametime.h"
#include "savedata/system_data.h"
#include "savedata/randomgroup.h"	//RANDOM_GROUP
#include "savedata/contest_savedata.h"
#include "situation_local.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "field/union_beacon_tool.h"
#include "syswork.h"
#include "communication/communication.h"
#include "comm_union_beacon.h"
#include "report.h"
#include "fielddata/script/saveflag.h"

#include "fieldmap_work.h"			//FIELDMAP_WORK
#include "fieldmap_func.h"			//FLDMAPFUNC_～

#include "msgdata/msg_debug_fldmenu.h"
#include "msgdata/msg_debug_tamada.h"
#include "msgdata/msg_debug_flag.h"
#include "msgdata/msg_debug_numinput.h"
#include "msgdata/msg_debug_tv.h"
#include "battle/battle_common.h"
#include "field/tvtopic_extern.h"

#include "sway_grass_enc.h"

#ifdef	PM_DEBUG
#include "debug_3d_draw_count.h"
#endif

typedef enum {
	DEBUG_VIEW_OFF = 0,
	DEBUG_VIEW_STRESS,
	DEBUG_VIEW_POS,
	DEBUG_VIEW_UNIONBEACON,
}DEBUG_VIEW_MODE;
/********************************************************************/
/*                                                                  */
/*	グローバル定義													*/
/*                                                                  */
/********************************************************************/
//pFunc	DebugUserfunc	= {0};
//u8		DebugUserWindow = {0};
static  int DebugStressFlg= DEBUG_VIEW_OFF;
static	BOOL DebugViewHookFlag = FALSE;

typedef struct _FLD_DEB_DAT{
	u8	work;
	u16 DebugList;
	u16 DebugCursor;
	BMPLIST_WORK *blistWk;
	FIELDSYS_WORK * fsys;
	GF_BGL_BMPWIN* pBmpwin;
	BMPLIST_DATA * menulist;
	void (*finish_func)(FIELDSYS_WORK *);
}FLD_DEB_DAT;

///gmmからメニュー文字列を取るとき用のリスト定義構造体
typedef struct _GMM_MENU_PARAM{
	u32	str_id;	///<メッセージID
	u32	param;	///<パラメータ
}GMM_MENU_PARAM;

///汎用数値入力インターフェースリスト定義
typedef void (*DEBUG_NUMINPUT_FUNC)(SAVEDATA* sv,u32 param,u32 value);
typedef u32 (*DEBUG_NUMGET_FUNC)(SAVEDATA* sv,u32 param);
typedef struct{
	u32	min;
	u32	max;
	u32	param;
	DEBUG_NUMINPUT_FUNC set_func;
	DEBUG_NUMGET_FUNC get_func;
}DEBUG_NUMINPUT_LIST;

typedef struct{
	FIELDSYS_WORK* fsys;
	FLD_DEB_DAT * pFdd;	//フィールドメニューワーク
	GF_BGL_BMPWIN win;	//BMPウィンドウ
	const DEBUG_NUMINPUT_LIST*	pList;
	const GMM_MENU_PARAM*		pMenu;
	int						list_num;
	u8			seq;
	u8			now;
	u8			sel;
	u8			n_keta;
	u32			n_max;
	u32			n_min;
	u32			value;
	STRBUF*		nbuf[10];
}DEBUG_NUMINPUT_WORK;

/********************************************************************/
/*                                                                  */
/*	ローカル定義													*/
/*                                                                  */
/********************************************************************/
//●デバッグ項目ウインドウデータ
#define	FDBG_LIST_PX1		(0)		//Ｘ座標1
#define	FDBG_LIST_PY1		(1+4)		//Ｙ座標1
#define	FDBG_LIST_PX2		(20)	//Ｘ座標2
#define	FDBG_LIST_PY2		(4)		//Ｙ座標2
#define	FDBG_LIST_SX		(13)	//Ｘサイズ
#define	FDBG_LIST_SY		(18)	//Ｙサイズ
#define	FDBG_LIST_PL		(FLD_SYSFONT_PAL)	//パレットナンバー
#define	FDBG_LIST_CH		(8)

//●マップ情報ウインドウデータ
#define	FDBG_INFO_PX1		(0)		//Ｘ座標1
#define	FDBG_INFO_PY1		(17)	//Ｙ座標1
#define	FDBG_INFO_PX2		(0)		//Ｘ座標2
#define	FDBG_INFO_PY2		(0)		//Ｙ座標2
#define	FDBG_INFO_SX		(30)	//Ｘサイズ
#define	FDBG_INFO_SY		(3)		//Ｙサイズ
#define	FDBG_INFO_PL		(FLD_SYSFONT_PAL)	//パレットナンバー
#define	FDBG_INFO_CH		(FDBG_LIST_CH + FDBG_LIST_SX * FDBG_LIST_SY)

//●処理情報ウインドウデータ
#define	FDBG_RSLT_PX		(0)		//Ｘ座標
#define	FDBG_RSLT_PY		(16)	//Ｙ座標
#define	FDBG_RSLT_SX		(30)	//Ｘサイズ
#define	FDBG_RSLT_SY		(4)		//Ｙサイズ
#define	FDBG_RSLT_PL		(FLD_SYSFONT_PAL)	//パレットナンバー
#define	FDBG_RSLT_CH		(8)

//●共用ユーザーウインドウデータ
#define	FDBG_USER_PX		(5)		//Ｘ座標
#define	FDBG_USER_PY		(1)		//Ｙ座標
#define	FDBG_USER_SX		(20)	//Ｘサイズ
#define	FDBG_USER_SY		(16)	//Ｙサイズ
#define	FDBG_USER_PL		(FLD_SYSFONT_PAL)	//パレットナンバー
#define	FDBG_USER_CH		(8)

#define STRESS_INFO_PAL_OFFSET	(64)
#define	STRESS_INFO_PAL_SIZE	(32)

static void	FieldDebugListControlTask(TCB_PTR tcb,void* work);
static void	FieldDebugListExitTask(TCB_PTR tcb,void* work);

static void	FieldDebugExit(TCB_PTR tcb,void* work);
static void FieldDebugExitCall(TCB_PTR tcb, void * work);

static BMP_MENULIST_DATA * MakeFieldDebugMenu(int arcID, const GMM_MENU_PARAM * list, int count);
static BMP_MENULIST_DATA * MakeEveryWhereMenu(int count);
static FLD_DEB_DAT * FieldDebugListCreateGMM(
		FIELDSYS_WORK * fsys,int arcID,const GMM_MENU_PARAM * list, int count,TCB_FUNC func);
static void	FieldDebugListFree(void* work);

static void	InfoCallBack2(BMPLIST_WORK* lw,u32 param,u8 y);


static void FieldDebugTVListSet(FIELDSYS_WORK * fsys);
static void FieldDebugTamadaListSet(FIELDSYS_WORK * fsys);
static void FieldDebugMapChangeList(FIELDSYS_WORK * fsys);
static void FieldDebugRTCListSet(FIELDSYS_WORK * fsys);
static void FieldDebugG3XList(FIELDSYS_WORK * fsys);
static void FieldDebugSysFlagList(FIELDSYS_WORK * fsys);


void FieldBitMapWinCgxSet( GF_BGL_INI * ini);

extern void DebugMoriMenuInit(GF_BGL_INI *ini, FIELDSYS_WORK *fsys);
extern void DebugWatanabeMenuInit( void* fsys );
extern void DebugTomoInit(void);
extern void DebugNakamuraInit( void * fsys );
extern void DebugMiyukiInit(void* fsys);
extern void DebugGotoMenuInit(FIELDSYS_WORK* fsys);
extern void DebugNoharaMenuInit( FIELDSYS_WORK* fsys );
extern void DebugBgmMenuInit( FIELDSYS_WORK* fsys );
extern void DebugScriptMenuInit( FIELDSYS_WORK* fsys );
extern void DebugMatsudaInit(FIELDSYS_WORK *fsys);
extern void DebugKagayaMenuInit( FIELDSYS_WORK *fsys );

extern void DBJump_JumpMapControl(struct _FIELDSYS_WORK * fsys);

/********************************************************************/
/*                                                                  */
/*				メニュー関数										*/
/*                                                                  */
/********************************************************************/


//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「わたなべ」
//--------------------------------------------------------------------
static void Debug_staff_watanabe(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT* wk = (FLD_DEB_DAT*)work;
	void* fsys = (void*)wk->fsys;
	
	FieldDebugExitCall(tcb, work);

	DebugWatanabeMenuInit(fsys);
//	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「もり」
//--------------------------------------------------------------------
static void Debug_staff_mori(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	GF_BGL_INI *ini  = (GF_BGL_INI *)wk->fsys->bgl;

	FieldDebugExitCall(tcb, work);

	DebugMoriMenuInit(ini, wk->fsys);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「ともみち」
//--------------------------------------------------------------------
static void Debug_staff_tomomiti(TCB_PTR tcb,void* work)
{
	
	// 呼ぶと落ちてしまうので一旦終了するようにした
	FieldDebugExit(tcb,work);

#if 0
	FieldDebugExitCall(tcb, work);

	DebugTomoInit();
#endif
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「なかむら」
//--------------------------------------------------------------------
static void Debug_staff_nakahiro(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);

	DebugNakamuraInit( tmp );
}
//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「さいとう」
//--------------------------------------------------------------------
static void Debug_staff_saitou(TCB_PTR tcb,void* work)
{
	FIELDSYS_WORK * fsys;
	FLD_DEB_DAT	*wp;
	wp = (FLD_DEB_DAT*)work;
	fsys = wp->fsys;
	
	FieldDebugExitCall(tcb, work);

	DBGSAI_MapNumDebugListSet(fsys);
}
//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「ともや」
//--------------------------------------------------------------------
static void Debug_staff_tomoya(TCB_PTR tcb,void* work)
{
	FieldDebugExitCall(tcb, work);

	DebugListSetOfTomoya(((FLD_DEB_DAT *)work)->fsys);
//	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「いわさわ」
//--------------------------------------------------------------------
static void Debug_staff_miyuki(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);

	DebugMiyukiInit(tmp);
}


//--------------------------------------------------------------------
//メニュー項目：空を飛ぶ
//--------------------------------------------------------------------
extern void DebugSkyJump_CreateTask(FIELDSYS_WORK* fsys);
static void Debug_skyjump(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;

	//空を飛ぶタスク作成
	DebugSkyJump_CreateTask(wk->fsys);	
	FieldDebugExitCall(tcb, work);
}

//--------------------------------------------------------------------
///メニュー項目：GTS
//--------------------------------------------------------------------
static void Debug_gts_jump(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FieldDebugExit(tcb,work);
	EventSet_EasyMapChange(wk->fsys, ZONE_ID_C01, DOOR_ID_JUMP_CODE, 149, 780, DIR_DOWN);
}

//--------------------------------------------------------------------
///メニュー項目：バトルタワー
//--------------------------------------------------------------------
static void Debug_btower_jump(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FieldDebugExit(tcb,work);
	EventSet_EasyMapChange(wk->fsys, ZONE_ID_D31, DOOR_ID_JUMP_CODE, 24, 13, DIR_DOWN);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「そがべ」
//--------------------------------------------------------------------
static void Debug_staff_sogabe(TCB_PTR tcb,void* work)
{
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「たまだ」
//--------------------------------------------------------------------
static void Debug_staff_tamada(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugTamadaListSet(fsys);
}


//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「まつだ」
//--------------------------------------------------------------------
static void Debug_staff_matsuda(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT *fdd = work;
	
	FieldDebugExitCall(tcb, work);

	DebugMatsudaInit(fdd->fsys);
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「かがや」
//--------------------------------------------------------------------
static void Debug_staff_kagaya(TCB_PTR tcb,void* work)
{
#if 0
	FieldDebugExit(tcb,work);
#else
	FLD_DEB_DAT *fdd = work;
	FieldDebugExitCall(tcb, work);
	DebugKagayaMenuInit(fdd->fsys);
#endif
}


//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「のはら」
//--------------------------------------------------------------------
static void Debug_staff_nohara(TCB_PTR tcb,void* work)
{
	FieldDebugExitCall(tcb, work);
	DebugNoharaMenuInit( ((FLD_DEB_DAT *)work)->fsys );
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「たや」
//--------------------------------------------------------------------
static void Debug_staff_taya(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;

	FieldDebugExitCall(tcb, work);
	DebugTayaMenuInit( (void*)(wk->fsys) );
}

//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「ごとう」
//--------------------------------------------------------------------
static void Debug_staff_gotou(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT* wk = (FLD_DEB_DAT*)work;
	void* fsys = (void*)wk->fsys;
	
	FieldDebugExitCall(tcb, work);
	DebugGotoMenuInit(fsys);
#if 0
	FieldDebugExit(tcb,work);
#endif
}


extern void DebugCommMenuInit(void* pFSys);  // d_ohno.c
//--------------------------------------------------------------------
///メニュー項目:「スタッフよう」→「おおの」
//--------------------------------------------------------------------
static void Debug_staff_ohno(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);

	DebugCommMenuInit(tmp);  // フィールドシステムを渡す
//	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
/*
 *	@brief	メニュー項目:テスト
 */
//--------------------------------------------------------------------
static void Debug_test_func(void)
{
	if(sys.trg & PAD_BUTTON_A){
//		DebugUserfunc = NULL;
	}
}

//負荷情報表示有無セット関数
void DebugStressDispSet(const BOOL inFlg)
{
	DebugStressFlg = inFlg;
	
	if (DebugStressFlg != DEBUG_VIEW_OFF){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	}else{
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}
}


//--------------------------------------------------------------------
///メニュー項目：ふかチェック用プリントを全部表示ON
//--------------------------------------------------------------------
static void Debug_huka_check_on(TCB_PTR tcb,void* work)
{
	if(DebugStressFlg==DEBUG_VIEW_OFF){
		DebugStressDispSet( DEBUG_VIEW_STRESS );
	}else{
		DebugStressDispSet( DEBUG_VIEW_OFF );
	}
	
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目：位置確認のためだけの表示ON
//--------------------------------------------------------------------
static void Debug_ichi_check_on(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wp = (FLD_DEB_DAT	*)work;

	GF_BGL_ScrClear( wp->fsys->bgl, FLD_MBGFRM_EFFECT1 );
	if(DebugStressFlg==DEBUG_VIEW_OFF){
		DebugStressDispSet(DEBUG_VIEW_POS);
	}else{
		DebugStressDispSet(DEBUG_VIEW_OFF);
	}
	
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
///メニュー項目：ユニオン用ビーコン表示ON
//--------------------------------------------------------------------
static void Debug_union_beacon_on(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wp = (FLD_DEB_DAT	*)work;

	GF_BGL_ScrClear( wp->fsys->bgl, FLD_MBGFRM_EFFECT1 );
	if(DebugStressFlg==DEBUG_VIEW_OFF){
		DebugStressDispSet(DEBUG_VIEW_UNIONBEACON);
	}else{
		DebugStressDispSet(DEBUG_VIEW_OFF);
	}
	
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///外部呼出し：位置確認のためだけの表示ON
//--------------------------------------------------------------------
void DebugIchiCheckOn(FIELDSYS_WORK* fsys)
{
	if(DebugStressFlg==DEBUG_VIEW_OFF){
		GF_BGL_ScrClear( fsys->bgl, FLD_MBGFRM_EFFECT1 );
		DebugStressDispSet( DEBUG_VIEW_POS );
	}
}

//--------------------------------------------------------------------
///メニュー項目：マップジャンプ(上下)
//--------------------------------------------------------------------
static void Debug_map_jump_up_down(TCB_PTR tcb,void* work)
{
	FIELDSYS_WORK * fsys;
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;	
	fsys = wk->fsys;

    // デバッグメニューからいく場合 同じ場所に下りるようにしました
    // 秘密基地に降りられるとまずい為です k.ohno
    Debug_ChangeUnderGroundDirect(fsys, 47, 384);
	FieldDebugExit(tcb,work);
	
}

//--------------------------------------------------------------------
///メニュー項目：マップジャンプ
//--------------------------------------------------------------------
static void Debug_map_jump(TCB_PTR tcb,void* work)
{
	FIELDSYS_WORK * fsys;
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;	
	fsys = wk->fsys;

	FieldDebugExitCall(tcb, work);

	DBJump_JumpMapControl(fsys);

}

//--------------------------------------------------------------------
///メニュー項目： ユニオンルーム
//--------------------------------------------------------------------
static void Debug_map_jump_union(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FieldDebugExit(tcb,work);

	EventSet_UnionRoomMapChange(wk->fsys);
}


//--------------------------------------------------------------------
///メニュー項目：地上フィールド Town01に強制ジャンプ(室内ハマリの回避用)
//--------------------------------------------------------------------
static void Debug_map_jump_t01(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT* wk = (FLD_DEB_DAT *)work;
	FieldDebugExit(tcb,work);

	EventSet_EasyMapChange(wk->fsys, ZONE_ID_T01, DOOR_ID_JUMP_CODE, 3*32+16, 27*32+16, DIR_DOWN);
}

//--------------------------------------------------------------------
///メニュー項目： ノモセ水ジムジャンプ
//--------------------------------------------------------------------
static void Debug_map_jump_gym01_00_00(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FieldDebugExit(tcb,work);

	EventSet_EasyMapChange(wk->fsys, ZONE_ID_C06GYM0101, DOOR_ID_JUMP_CODE, 16, 16, DIR_DOWN);
}

//--------------------------------------------------------------------
///メニュー項目：リスト/どこでもジャンプメニューコントローラ
//--------------------------------------------------------------------
//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグジャンプ用メイン制御タスク
 *
 *	@param	tcb		TCB_PTR:呼び出し元タスクブロックへのポインタ
 *	@param	work	void*:呼び出し元タスクブロックワークへのポインタ
 */
//------------------------------------------------------------------
static void FieldDebugListJumpMenuTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	FLD_DEB_DAT	*wp;
	u16 x,z;

	wp = (FLD_DEB_DAT*)work;

	ret_code = BmpListMain(wp->blistWk);
	//キー操作判定
	if(sys.trg & PAD_BUTTON_A){
		if(ret_code){
			x = z = 0;
			GetBlockPosFromZoneID(ret_code,&x,&z);
			EventSet_EasyMapChange(wp->fsys,
					ret_code, DOOR_ID_JUMP_CODE, x*32+16, z*32+16, DIR_DOWN);
		}
		FieldDebugExit(tcb,work);
		return;
	}
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		if (wp->finish_func != NULL) {
			FIELDSYS_WORK * fsys = wp->fsys;
			void (*func)(FIELDSYS_WORK*) = wp->finish_func;
			FieldDebugExitCall(tcb,work);
			func(wp->fsys);
		} else {
			FieldDebugExit(tcb,work);
		}
		return;
	}
}
//--------------------------------------------------------------------
///メニュー項目：リストジャンプメニュー項目定義
//--------------------------------------------------------------------
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_list_jump.h"

static const GMM_MENU_PARAM FieldDebugListJumpMenu1[] = {
	{ msg_label_listjump1,	BMPLIST_RABEL},			//ラベル01
	{ msg_buil01_00_00,	ZONE_ID_C03R0101},	//
	{ msg_buil02_00_00,	ZONE_ID_C04R0202},	//
	{ msg_buil03_00_00,	ZONE_ID_C04R0203},	//
	{ msg_buil04_00_00,	ZONE_ID_C04R0302},	//
	{ msg_buil05_00_00,	ZONE_ID_C03R0102},	//
	{ msg_buil06_00_00,	ZONE_ID_C03R0104},	//
	{ msg_buil07_00_00,	ZONE_ID_C05R0101},	//
	{ msg_buil08_00_00,	ZONE_ID_C05R0102},	//
	{ msg_love01_00_00,	ZONE_ID_C05R0201},	//
	{ msg_grow01_00_00,	ZONE_ID_T04R0101},	//
	{ msg_bike01_00_00,	ZONE_ID_C04R0101},	//
	{ msg_scho01_00_00,	ZONE_ID_C01R0701},	//
	{ msg_gate01_00_00,	ZONE_ID_R206R0201},	//
	{ msg_gate02_00_00,	ZONE_ID_R218R0101},	//
	{ msg_gate03_00_00,	ZONE_ID_C04R0401},	//
	{ msg_d12r0101,		ZONE_ID_D12R0101},	//
	{ msg_t04r0101,		ZONE_ID_T04R0101},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};
static const GMM_MENU_PARAM FieldDebugListJumpMenu2[] = {
	{ msg_label_listjump2,	BMPLIST_RABEL},			//ラベル01
	{ msg_libra01_00_00,ZONE_ID_C02R0101},	//
	{ msg_libra02_00_00,ZONE_ID_C02R0102},	//
	{ msg_libra03_00_00,ZONE_ID_C02R0103},	//
	{ msg_wise01_00_00,	ZONE_ID_T05R0101},	//
	{ msg_muse01_00_00,	ZONE_ID_C03R0401},	//
	{ msg_comp01_00_00,	ZONE_ID_C01R0101},	//
	{ msg_comp02_00_00,	ZONE_ID_C01R0102},	//
	{ msg_comp03_00_00,	ZONE_ID_C01R0103},	//
	{ msg_shouse01_00_00,ZONE_ID_C07R0101},	//
	{ msg_phouse01_00_00,ZONE_ID_D02R0101},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};
static const GMM_MENU_PARAM FieldDebugListJumpMenu3[] = {
	{ msg_label_listjump3,	BMPLIST_RABEL},			//ラベル01
	{ msg_hotel01_00_00,	ZONE_ID_R213R0301},	//
	{ msg_hotel02_00_00,	ZONE_ID_R213R0401},	//
	{ msg_hotel03_00_00,	ZONE_ID_L02R0101},	//
	{ msg_depart01_00_00,	ZONE_ID_C07R0201},	//
	{ msg_depart02_00_00,	ZONE_ID_C07R0202},	//
	{ msg_depart03_00_00,	ZONE_ID_C07R0203},	//
	{ msg_depart04_00_00,	ZONE_ID_C07R0204},	//
	{ msg_depart05_00_00,	ZONE_ID_C07R0205},	//
	{ msg_cont01_00_00,		ZONE_ID_C05R1101},	//
	{ msg_cont02_00_00,		ZONE_ID_C05R1102},	//
	{ msg_dun2601_00_00,	ZONE_ID_D26R0101},	//
	{ msg_dun2602_00_00,	ZONE_ID_D26R0102},	//
	{ msg_dun2603_00_00,	ZONE_ID_D26R0103},	//
	{ msg_dun2604_00_00,	ZONE_ID_D26R0104},	//
	{ msg_dun2605_00_00,	ZONE_ID_D26R0105},	//
	{ msg_dun2606_00_00,	ZONE_ID_D26R0106},	//
	{ msg_tv01_00_00,		ZONE_ID_C01R0201},	//
	{ msg_tv02_00_00,		ZONE_ID_C01R0202},	//
	{ msg_tv03_00_00,		ZONE_ID_C01R0203},	//
	{ msg_tv04_00_00,		ZONE_ID_C01R0204},	//
	{ msg_tv05_00_00,		ZONE_ID_C01R0205},	//
	{ msg_tv06_00_00,		ZONE_ID_C01R0206},	//
	{ msg_fhouse01_00_00,	ZONE_ID_T03R0101},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};

static const GMM_MENU_PARAM FieldDebugListJumpMenu4[] = {
	{ msg_label_listjump4,	BMPLIST_RABEL},			//ラベル01
	{ msg_tower01_00_00,	ZONE_ID_D31R0201},	//
	{ msg_tower02_00_00,	ZONE_ID_D31R0202},	//
	{ msg_tower03_00_00,	ZONE_ID_D31R0203},	//
	{ msg_tower04_00_00,	ZONE_ID_D31R0204},	//
	{ msg_tower05_00_00,	ZONE_ID_D31R0205},	//
	{ msg_tower06_00_00,	ZONE_ID_D31R0206},	//
	{ msg_tower07_00_00,	ZONE_ID_D31R0207},	//
	{ msg_fac01_00_00,		ZONE_ID_D31R0101},	//
	{ msg_fac02_00_00,		ZONE_ID_D31R0102},	//
	{ msg_fac03_00_00,		ZONE_ID_D31R0103},	//
	{ msg_dun3101_00_00,	ZONE_ID_D31},		//
	{ msg_wifi01_00_00,		ZONE_ID_C01R0601},	//
	{ msg_dun1101_00_00,	ZONE_ID_D11R0101},	//
	{ msg_dun0601_00_00,	ZONE_ID_D06R0101},	//
	{ msg_view01_00_00,		ZONE_ID_C06R0101},	//
	{ msg_view02_00_00,		ZONE_ID_C06R0102},	//
	{ msg_dun0514_00_00,	ZONE_ID_D05R0114},	//
	{ msg_dun0515_00_00,	ZONE_ID_D05R0115},	//
	{ msg_game01_00_00,		ZONE_ID_C07R0101},	//
	{ msg_gift01_00_00,		ZONE_ID_C07R0401},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};

static const GMM_MENU_PARAM FieldDebugListJumpMenu5[] = {
	{ msg_label_listjump5,	BMPLIST_RABEL},			//ラベル01
	{ msg_dun0901_00_00,	ZONE_ID_D09R0101},	//
	{ msg_dun0902_00_00,	ZONE_ID_D09R0102},	//
	{ msg_dun0903_00_00,	ZONE_ID_D09R0103},	//
	{ msg_dun0904_00_00,	ZONE_ID_D09R0104},	//
	{ msg_dun0905_00_00,	ZONE_ID_D09R0105},	//
	{ msg_dun0906_00_00,	ZONE_ID_D09R0106},	//
	{ msg_leag01_00_00,		ZONE_ID_C10R0101},	//
	{ msg_siten01_00_00,	ZONE_ID_C10R0103},	//
	{ msg_siten02_00_00,	ZONE_ID_C10R0105},	//
	{ msg_siten03_00_00,	ZONE_ID_C10R0107},	//
	{ msg_siten04_00_00,	ZONE_ID_C10R0109},	//
	{ msg_siten05_00_00,	ZONE_ID_C10R0102},	//
	{ msg_siten06_00_00,	ZONE_ID_C10R0104},	//
	{ msg_siten07_00_00,	ZONE_ID_C10R0110},	//
	{ msg_champ01_00_00,	ZONE_ID_C10R0111},	//
	{ msg_dendou01_00_00,	ZONE_ID_C10R0112},	//
	{ msg_dendou02_00_00,	ZONE_ID_C10R0113},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};
static const GMM_MENU_PARAM FieldDebugListJumpMenu6[] = {
	{ msg_label_listjump6,	BMPLIST_RABEL},			//ラベル01
	{ msg_gate07_00_00,	ZONE_ID_R206R0101},	//
	{ msg_gate05_00_00,	ZONE_ID_R221R0101},	//
	{ msg_view01_00_00,ZONE_ID_C06R0101},	//
	{ msg_view02_00_00,ZONE_ID_C06R0102},	//
	{ msg_dun1601_00_00,ZONE_ID_D16R0101},	//
	{ msg_dun1602_00_00,ZONE_ID_D16R0102},	//
	{ msg_dun1603_00_00,ZONE_ID_D16R0103},	//
	{ msg_dun0504_00_00,ZONE_ID_D05R0104},	//
	{ msg_dun0505_00_00,ZONE_ID_D05R0105},	//
	{ msg_dun2401_00_00,ZONE_ID_D24R0101},	//
	{ msg_dun2402_00_00,ZONE_ID_D24R0102},	//
	{ msg_dun2403_00_00,ZONE_ID_D24R0103},	//
	{ msg_dun2404_00_00,ZONE_ID_D24R0104},	//
	{ msg_dun2405_00_00,ZONE_ID_D24R0105},	//
	{ msg_dun2406_00_00,ZONE_ID_D24R0106},	//
	{ msg_rich01_00_00,ZONE_ID_R212AR0101},	//
	{ msg_rich02_00_00,ZONE_ID_R212AR0102},	//
	{ msg_dun2301_00_00,ZONE_ID_D23R0101},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};

static const GMM_MENU_PARAM FieldDebugListJumpMenuAn[] = {
	{ msg_label_listjump_an,BMPLIST_RABEL},			//ラベル01
	{ msg_dun0701_00_00,	ZONE_ID_D07R0101},	//
	{ msg_dun0702_00_00,	ZONE_ID_D07R0102},	//
	{ msg_dun0703_00_00,	ZONE_ID_D07R0103},	//
	{ msg_dun0704_00_00,	ZONE_ID_D07R0104},	//
	{ msg_dun0705_00_00,	ZONE_ID_D07R0105},	//
	{ msg_dun0706_00_00,	ZONE_ID_D07R0106},	//
	{ msg_dun0707_00_00,	ZONE_ID_D07R0107},	//
	{ msg_dun0708_00_00,	ZONE_ID_D07R0108},	//
	{ msg_dun0709_00_00,	ZONE_ID_D07R0109},	//
	{ msg_dun0710_00_00,	ZONE_ID_D07R0110},	//
	{ msg_dun0711_00_00,	ZONE_ID_D07R0111},	//
	{ msg_dun0712_00_00,	ZONE_ID_D07R0112},	//
	{ msg_dun0713_00_00,	ZONE_ID_D07R0113},	//
	{ msg_dun0714_00_00,	ZONE_ID_D07R0114},	//
	{ msg_dun0715_00_00,	ZONE_ID_D07R0115},	//
	{ msg_dun0716_00_00,	ZONE_ID_D07R0116},	//
	{ msg_dun0717_00_00,	ZONE_ID_D07R0117},	//
	{ msg_dun0718_00_00,	ZONE_ID_D07R0118},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};
static const GMM_MENU_PARAM FieldDebugListJumpMenuGym[] = {
	{ msg_label_listjump_gym,	BMPLIST_RABEL},			//ラベル01
	{ msg_gym01_00_00,	ZONE_ID_C06GYM0101},	//
	{ msg_gym02_00_00,	ZONE_ID_C02GYM0101},	//
	{ msg_gym03_00_00,	ZONE_ID_C03GYM0101},	//
	{ msg_gym0401_00_00,	ZONE_ID_C04GYM0101},	//
	{ msg_gym0402_00_00,	ZONE_ID_C04GYM0102},	//
	{ msg_gym0501_00_00,	ZONE_ID_C05GYM0101},	//
	{ msg_gym0502_00_00,	ZONE_ID_C05GYM0102},	//
	{ msg_gym0503_00_00,	ZONE_ID_C05GYM0103},	//
	{ msg_gym0504_00_00,	ZONE_ID_C05GYM0104},	//
	{ msg_gym06_00_00,	ZONE_ID_C09GYM0101},	//
	{ msg_gym07_00_00,	ZONE_ID_C07GYM0101},	//
	{ msg_gym0801_00_00,	ZONE_ID_C08GYM0101},	//
	{ msg_gym0802_00_00,	ZONE_ID_C08GYM0102},	//
	{ msg_gym0803_00_00,	ZONE_ID_C08GYM0103},	//
	{ msg_exit_listjump,		 0x00000000},		//00:閉じる
};
//--------------------------------------------------------------------
///メニュー項目：ジムジャンプ
//--------------------------------------------------------------------
static void Debug_map_jump_list_gym(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenuGym, NELEMS(FieldDebugListJumpMenuGym),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}
//--------------------------------------------------------------------
///メニュー項目：リストジャンプ1
//--------------------------------------------------------------------
static void Debug_map_jump_list(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu1, NELEMS(FieldDebugListJumpMenu1),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ2
//--------------------------------------------------------------------
static void Debug_map_jump_list2(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu2, NELEMS(FieldDebugListJumpMenu2),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ3
//--------------------------------------------------------------------
static void Debug_map_jump_list3(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu3, NELEMS(FieldDebugListJumpMenu3),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ4
//--------------------------------------------------------------------
static void Debug_map_jump_list4(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu4, NELEMS(FieldDebugListJumpMenu4),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ5
//--------------------------------------------------------------------
static void Debug_map_jump_list5(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu5, NELEMS(FieldDebugListJumpMenu5),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ6
//--------------------------------------------------------------------
static void Debug_map_jump_list6(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenu6, NELEMS(FieldDebugListJumpMenu6),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：リストジャンプ アンノーンダンジョン
//--------------------------------------------------------------------
static void Debug_map_jump_list_an(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_list_jump_dat,
			FieldDebugListJumpMenuAn, NELEMS(FieldDebugListJumpMenuAn),FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//--------------------------------------------------------------------
///メニュー項目：どこでもジャンプ
//--------------------------------------------------------------------
static void Debug_map_jump_flex(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT * wp = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wp->fsys;
	FieldDebugExitCall(tcb, work);
	
	wp = FieldDebugListCreateGMM(fsys, 0,
			NULL, ZONE_ID_MAX-2,FieldDebugListJumpMenuTask);
	wp->finish_func = FieldDebugListSet;
}

//--------------------------------------------------------------------
///メニュー項目：アウトレンジ表示
//--------------------------------------------------------------------
static void Debug_out_range_disp(TCB_PTR tcb,void* work)
{
	FIELDSYS_WORK * fsys;
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;	
	fsys = wk->fsys;

	SetDebugOutRangeFlg();
	FieldDebugExit(tcb,work);
	
}

extern void DebugItemMakeInit( void * fsys );
//--------------------------------------------------------------------
///メニュー項目： データさくせい・アイテム
//--------------------------------------------------------------------
static void Debug_itemmake(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);

	DebugItemMakeInit( tmp );
}

extern void DebugPokemonMakeInit( void * fsys );
//--------------------------------------------------------------------
///メニュー項目： データさくせい・ポケモンさくせい
//--------------------------------------------------------------------
static void Debug_pokemonmake(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);
	DebugPokemonMakeInit( tmp );
}

extern void DebugPokemonChangeInit( void * fsys );
//--------------------------------------------------------------------
///メニュー項目： データさくせい・ポケモンかきかえ
//--------------------------------------------------------------------
static void Debug_pokemonchg(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);
	DebugPokemonChangeInit( tmp );
}

extern void DebugDameTamagoSet( void * fsys );
//--------------------------------------------------------------------
///メニュー項目： データさくせい・ダメタマゴ
//--------------------------------------------------------------------
static void Debug_dametamago(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);
	DebugDameTamagoSet( tmp );
}


//--------------------------------------------------------------------
///メニュー項目：その他のマップ切替
//--------------------------------------------------------------------
static void Debug_jump_other(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugMapChangeList(fsys);
}
//--------------------------------------------------------------------
/**
 * @brief	メニュー項目：タイトルに戻る
 *
 * リークしているかどうかのチェック用？
 */

//--------------------------------------------------------------------
static void Debug_return_title(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * fsys = (void *)wk->fsys;

	EventSet_ReturnToTitle(fsys);
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目：アトリビュート確認
//--------------------------------------------------------------------
static void Debug_check_attribute(TCB_PTR tcb,void* work)
{
	FIELDSYS_WORK * fsys;
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;	
	fsys = wk->fsys;

	FieldDebugExitCall(tcb, work);
	DBGSAI_CheckAttribute(fsys);
}

//--------------------------------------------------------------------
///メニュー項目:「とけい」
//--------------------------------------------------------------------
static void Debug_control_time(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugRTCListSet(fsys);
}
//--------------------------------------------------------------------
///メニュー項目:「3Dせってい」
//--------------------------------------------------------------------
static void Debug_g3x_setting(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugG3XList(fsys);
}

//--------------------------------------------------------------------
///メニュー項目:「♂♀きりかえ」
//--------------------------------------------------------------------
static void Debug_sex_change(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);

	//性別を逆転する
	if (MyStatus_GetMySex(my) == PM_MALE) {
		MyStatus_SetMySex(my, PM_FEMALE);
	} else {
		MyStatus_SetMySex(my, PM_MALE);
	}

	// ユニオンルームの見た目番号も変更する
	{
		u8 view;
		view = UnionView_GetTrainerType( MyStatus_GetID(my), MyStatus_GetMySex(my), 0 );
		MyStatus_SetTrainerView( my, view );
	}


	FieldDebugExit(tcb, work);
	
	//現在地へ飛びなおす
	EventSet_EasyMapChange(fsys, fsys->location->zone_id, DOOR_ID_JUMP_CODE,
			Player_NowGPosXGet(fsys->player), Player_NowGPosZGet(fsys->player), DIR_DOWN);
	
}
//--------------------------------------------------------------------
///メニュー項目:「ゲームフラグ」
//--------------------------------------------------------------------
static void Debug_sysflag(TCB_PTR tcb, void *work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugSysFlagList(fsys);
}

extern void DebugEncountSetInit( void * fsys );
//--------------------------------------------------------------------
///メニュー項目： システム・エンカウント
//--------------------------------------------------------------------
static void Debug_encountset(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	void * tmp = (void *)wk->fsys;

	FieldDebugExitCall(tcb, work);

	DebugEncountSetInit( tmp );
}

//--------------------------------------------------------------------
///メニュー項目：	システム・はいたついん
//--------------------------------------------------------------------
static void Debug_postman(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	if (!DebugFlagData.postman_status) {
		DebugFlagData.postman_status = 1;
		Snd_SePlay(SEQ_SE_DP_SELECT);
	} else {
		DebugFlagData.postman_status = 0;
		Snd_SePlay(SEQ_SE_DP_WALL_HIT);
	}
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);
	FieldDebugTVListSet(fsys);
}

//--------------------------------------------------------------------
///メニュー項目： システム・BGM
//--------------------------------------------------------------------
static void Debug_bgm(TCB_PTR tcb,void* work)
{
	FieldDebugExitCall(tcb, work);
	DebugBgmMenuInit( ((FLD_DEB_DAT *)work)->fsys );
}

//--------------------------------------------------------------------
///メニュー項目： システム・SCRIPT
//--------------------------------------------------------------------
static void Debug_script(TCB_PTR tcb,void* work)
{
	FieldDebugExitCall(tcb, work);
	DebugScriptMenuInit( ((FLD_DEB_DAT *)work)->fsys );
}

//--------------------------------------------------------------------
///メニュー項目： システム・ふしぎなおくりもの
//--------------------------------------------------------------------
static void Debug_WiFiHusigi(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;

	FIELDSYS_WORK * fsys	= wk->fsys;
	SYSTEMDATA * sysdt;
	u8 f;
	sysdt = SaveData_GetSystemData(fsys->savedata);

	f = SYSTEMDATA_GetWifiMPOpenFlag(sysdt);
	OS_Printf("WiFi不思議フラグ 元[%d]\n",f);

	SYSTEMDATA_SetWifiMPOpenFlag(sysdt,1);

	f = SYSTEMDATA_GetWifiMPOpenFlag(sysdt);
	OS_Printf("WiFi不思議フラグ 後[%d]\n",f);

	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_save01(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	SaveData_RequestTotalSave();
	Field_Save(wk->fsys);
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_save02(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	Field_Save(wk->fsys);
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
///カウントストップ直前・でんどういり
//--------------------------------------------------------------------
static void Debug_cntstop_dendou(TCB_PTR tcb, void * work)
{
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
///カウントストップ・テレビ
//--------------------------------------------------------------------
static void Debug_cntstop_tv(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	FIELDSYS_WORK * fsys = wk->fsys;
	SAVEDATA * sv = fsys->savedata;
	POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);

	//スロット上限チェック用トピックセット
	TVTOPIC_Entry_Record_Slot(fsys, 3, 50000, 65566 * 65536 - 1);
	//サファリ上限チェック用トピックセット
	{
		int count;
		TV_WORK * tvwk = SaveData_GetTvWork(sv);
		TVTOPIC_SafariTemp_Init(tvwk);
		for (count = 0; count < 40; count ++) {
			TVTOPIC_SafariTemp_Set(tvwk, PokeParty_GetMemberPointer(party, 0));
		}
		TVTOPIC_Entry_Watch_Safari(fsys);
	}
	//捕獲上限チェック用トピックセット
	{
		TVWATCH_BATTLE_WORK * tvwbw = TVWatchBattleWork_Create(HEAPID_FIELD);

		TVBATTLE_StoreResult(tvwbw, PokeParty_GetMemberPointer(party, 0),
				FIGHT_WIN, 999 * 14, HEAPID_FIELD);
		TVTOPIC_Entry_Watch_Capture(fsys, tvwbw, FIGHT_WIN);

		TVBATTLE_StoreResult(tvwbw, PokeParty_GetMemberPointer(party, 0),
				FIGHT_POKE_GET, 999 * 14, HEAPID_FIELD);
		TVTOPIC_Entry_Watch_Capture(fsys, tvwbw, FIGHT_POKE_GET);

		TVWatchBattleWork_Delete(tvwbw);
	}
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
///カウントストップ直前・つうしんコンテスト
//--------------------------------------------------------------------
static void Debug_cntstop_contest(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	FIELDSYS_WORK * fsys = wk->fsys;
	SAVEDATA * sv = fsys->savedata;

	{
		int now, i, ranking, loop_max, type;
		
		for(ranking = 0; ranking < 4; ranking++){
			for(type = 0; type < 5; type++){
				now = CONDATA_GetValue(sv, type, ranking);
				loop_max = 9998 - now;
				for(i = 0; i < loop_max; i++){
					CONDATA_RecordAdd(sv, type, ranking);
				}
			}
		}
	}

	//つうしんコンテスト成績
	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///カウントストップ直前・その他
//--------------------------------------------------------------------
static void Debug_cntstop_etc(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	FIELDSYS_WORK * fsys = wk->fsys;
	SAVEDATA * sv = fsys->savedata;
	//おこづかい
	{
		MYSTATUS * my = SaveData_GetMyStatus(sv);
		MyStatus_SetGold(my, 999999 - 1);
	}
	//プレイ時間
	{
		PLAYTIME * ptime = SaveData_GetPlayTime(sv);
		PLAYTIME_Set(ptime, 999, 58, 0);
	}
	//揺れ草連鎖数
	{
		SwayGrass_DebugSetChain(fsys, SWAY_GRASS_CHAIN_MAX-1);
	}
	//スコア
	{
		RECORD * rec = SaveData_GetRecord(sv);
		RECORD_Score_DebugSet(rec, SCORE_MAX-1);
	}

	FieldDebugExit(tcb,work);
}

//--------------------------------------------------------------------
///メニュー項目:「すうちにゅうりょく」
//--------------------------------------------------------------------
static void FieldDebugNumInputList(FIELDSYS_WORK * fsys,
	const DEBUG_NUMINPUT_LIST* pList,const GMM_MENU_PARAM* pMenu,int num);

static u32 DNumInput_RecordGet(SAVEDATA* sv,u32 param);
static void DNumInput_RecordSet(SAVEDATA* sv,u32 param,u32 value);
static u32 DNumInput_TowerStageGet(SAVEDATA* sv,u32 param);
static void DNumInput_TowerStageSet(SAVEDATA* sv,u32 param,u32 value);
static u32 DNumInput_TowerChallengeGet(SAVEDATA* sv,u32 param);
static void DNumInput_TowerChallengeSet(SAVEDATA* sv,u32 param,u32 value);
static u32 DNumInput_TowerWifiRankGet(SAVEDATA* sv,u32 param);
static void DNumInput_TowerWifiRankSet(SAVEDATA* sv,u32 param,u32 value);

#include "fld_numinput.dat"
static void Debug_numinput_tower(TCB_PTR tcb, void *work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);

	FieldDebugNumInputList(fsys,
		Debug_NumInputL_Tower,Debug_NumInputG_Tower,NELEMS(Debug_NumInputG_Tower));
}
static void Debug_numinput_sysflag(TCB_PTR tcb, void *work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);

	FieldDebugNumInputList(fsys,
		Debug_NumInputL_SysFlag,Debug_NumInputG_SysFlag,NELEMS(Debug_NumInputG_SysFlag));
}
static void Debug_numinput_record(TCB_PTR tcb, void *work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	FIELDSYS_WORK * fsys = wk->fsys;
	FieldDebugExitCall(tcb, work);

	FieldDebugNumInputList(fsys,
		Debug_NumInputL_Record,Debug_NumInputG_Record,NELEMS(Debug_NumInputG_Record));
}

//==============================================================================
//
//
//
//==============================================================================

static const GMM_MENU_PARAM FieldDebugListTop[] = {
	{DF_LABEL03,BMPLIST_RABEL},
	{DF_JUMP01,(u32)Debug_skyjump},
	{DF_GTS,(u32)Debug_gts_jump},
	{DF_BTOWER,(u32)Debug_btower_jump},
	{DF_JUMP02,(u32)Debug_map_jump_list_gym},
	{DF_JUMP03_00,(u32)Debug_map_jump_list},
	{DF_JUMP03_01,(u32)Debug_map_jump_list2},
	{DF_JUMP03_02,(u32)Debug_map_jump_list3},
	{DF_JUMP03_03,(u32)Debug_map_jump_list4},
	{DF_JUMP03_04,(u32)Debug_map_jump_list5},
	{DF_JUMP03_05,(u32)Debug_map_jump_list6},
	{DF_JUMP03_AN,(u32)Debug_map_jump_list_an},
	{DF_JUMP04,(u32)Debug_map_jump_flex},
	{DF_JUMP07,(u32)Debug_jump_other},
	{DF_LABEL01,BMPLIST_RABEL},
	{DF_CHECK00,(u32)Debug_huka_check_on},
	{DF_CHECK01,(u32)Debug_ichi_check_on},
	{DF_CHECK02,(u32)Debug_check_attribute},
	{DF_UNIONBEACON, (u32)Debug_union_beacon_on},
	{DF_LABEL08,BMPLIST_RABEL},
	{DF_BOX_SAVE,(u32)Debug_save01},
	{DF_MY_SAVE,(u32)Debug_save02},
	{DF_LABEL06,BMPLIST_RABEL},
	{DF_TIME00, (u32)Debug_control_time},
	{DF_G3X,	(u32)Debug_g3x_setting},
	{DF_SEX_CHG,(u32)Debug_sex_change},
	{DF_SYSFLAG,(u32)Debug_sysflag},
	{DF_ENCOUNT,(u32)Debug_encountset},
	{DF_DEBUG_POSTMAN, (u32)Debug_postman},
	{DF_DEBUG_TV,	(u32)Debug_tv},
	{DF_DEBUG_BGM,(u32)Debug_bgm},
	{DF_DEBUG_SCRIPT,(u32)Debug_script},
	{DF_WIFI_HUSHIGI,(u32)Debug_WiFiHusigi},
	{DF_LABEL07,BMPLIST_RABEL},
	{DF_NI_TOWER,	(u32)Debug_numinput_tower},
	{DF_NI_SYSFLAG,	(u32)Debug_numinput_sysflag},
	{DF_NI_RECORD,	(u32)Debug_numinput_record},
	{DF_LABEL04,BMPLIST_RABEL},
	{DF_CHANGE00,(u32)Debug_out_range_disp},
	{DF_LABEL05,BMPLIST_RABEL},
	{DF_POKEMON00,(u32)Debug_pokemonmake},
	{DF_POKEMON01,(u32)Debug_pokemonchg},
	{DF_POKEMON02,(u32)Debug_dametamago},
	{DF_ITEM00,(u32)Debug_itemmake},
	{DF_LABEL09,BMPLIST_RABEL},
	//{DF_CNTSTOP_DENDOU,(u32)Debug_cntstop_dendou},
	{DF_CNTSTOP_TV,(u32)Debug_cntstop_tv},
	{DF_CNTSTOP_CONTEST,(u32)Debug_cntstop_contest},
	{DF_CNTSTOP_ETC,(u32)Debug_cntstop_etc},
	{DF_LABEL02,BMPLIST_RABEL},
	{DF_NAME01,(u32)Debug_staff_watanabe},
	{DF_NAME09,(u32)Debug_staff_tamada},
	{DF_NAME08,(u32)Debug_staff_sogabe},
	{DF_NAME02,(u32)Debug_staff_mori},
	{DF_NAME04,(u32)Debug_staff_tomomiti},
	{DF_NAME10,(u32)Debug_staff_matsuda},
	{DF_NAME11,(u32)Debug_staff_kagaya},
	{DF_NAME03,(u32)Debug_staff_nakahiro},
	{DF_NAME12,(u32)Debug_staff_nohara},
	{DF_NAME13,(u32)Debug_staff_taya},
	{DF_NAME07,(u32)Debug_staff_miyuki},
	{DF_NAME05,(u32)Debug_staff_saitou},
	{DF_NAME14,(u32)Debug_staff_gotou},
	{DF_NAME06,(u32)Debug_staff_tomoya},
	{DF_NAME15,(u32)Debug_staff_ohno},
};

/********************************************************************/
/*                                                                  */
/*	フィールドデバッグメニューリスト設定							*/
/*                                                                  */
/********************************************************************/
//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグメニューリスト設定
 *
 *	@param	fsys
 */
//------------------------------------------------------------------
void FieldDebugListSet(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_fldmenu_dat,
			FieldDebugListTop, NELEMS(FieldDebugListTop), NULL);
	wp->finish_func = NULL;

	//イベントフック
	FieldSystemProc_SeqHold();
	return;
}


//============================================================================================
//============================================================================================

static const GMM_MENU_PARAM FieldDebugJumpListGMM[] = {
	{DF_JUMP08,(u32)Debug_map_jump_up_down},
	{DF_JUMP09,(u32)Debug_map_jump},
	{DF_JUMP10,(u32)Debug_map_jump_union},
	{DF_JUMP11,(u32)Debug_map_jump_t01},
	{DF_JUMP13,(u32)Debug_map_jump_gym01_00_00},
	{DF_JUMP12,(u32)Debug_return_title},
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugMapChangeList(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_fldmenu_dat,
			FieldDebugJumpListGMM, NELEMS(FieldDebugJumpListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//============================================================================================
//
//		フィールドデバッグメニュー：3D設定用サブメニュー
//
//============================================================================================
//--------------------------------------------------------------------
///	エッジマーキング有効
//--------------------------------------------------------------------
static void Debug_edgemarking_on(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	G3X_EdgeMarking(TRUE);
}
//--------------------------------------------------------------------
///	エッジマーキング無効
//--------------------------------------------------------------------
static void Debug_edgemarking_off(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	G3X_EdgeMarking(FALSE);
}
//--------------------------------------------------------------------
///	アンチエイリアス有効
//--------------------------------------------------------------------
static void Debug_antialias_on(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	G3X_AntiAlias(TRUE);
}
//--------------------------------------------------------------------
///	アンチエイリアス無効
//--------------------------------------------------------------------
static void Debug_antialias_off(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	G3X_AntiAlias(FALSE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_edgecolor_change(int color)
{
	static GXRgb tbl[8];
	int i;
	tbl[0] = GX_RGB(0,0,0);
	for (i = 1; i < 8; i++) {
		tbl[i] = GX_RGB(color,color,color);
	}
	G3X_SetEdgeColorTable(tbl);
	G3X_EdgeMarking(TRUE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_edgecolor_4(TCB_PTR tcb, void * work)
{
	Debug_edgecolor_change(4);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_edgecolor_10(TCB_PTR tcb, void * work)
{
	Debug_edgecolor_change(10);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_edgecolor_16(TCB_PTR tcb, void * work)
{
	Debug_edgecolor_change(16);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_edgecolor_20(TCB_PTR tcb, void * work)
{
	Debug_edgecolor_change(20);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const GMM_MENU_PARAM FieldDebugG3XListGMM[] = {
	{DF_G3X_EDGE_ON,		(u32)Debug_edgemarking_on},
	{DF_G3X_EDGE_OFF,		(u32)Debug_edgemarking_off},
	{DF_G3X_ANTIALIAS_ON,	(u32)Debug_antialias_on},
	{DF_G3X_ANTIALIAS_OFF,	(u32)Debug_antialias_off},
	{DF_G3X_EDGE1,			(u32)Debug_edgecolor_4},
	{DF_G3X_EDGE2,			(u32)Debug_edgecolor_10},
	{DF_G3X_EDGE3,			(u32)Debug_edgecolor_16},
	{DF_G3X_EDGE4,			(u32)Debug_edgecolor_20},
};
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugG3XList(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_fldmenu_dat,
			FieldDebugG3XListGMM, NELEMS(FieldDebugG3XListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//============================================================================================
//
//		サブメニュー：たまだ専用
//
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_01(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT * wk = work;
	u16 item;

	item = ITEM_SUKUSUKUKOYASI;
	do {
		if (MyItem_CheckItem(SaveData_GetMyItem(wk->fsys->savedata), item, 1, HEAPID_FIELD)) {
			item ++;
		} else {
			MyItem_AddItem(SaveData_GetMyItem(wk->fsys->savedata), item, 1, HEAPID_FIELD);
			Snd_SePlay(SEQ_SE_DP_SELECT);
			break;
		}
	}while (item <= ITEM_NEBANEBAKOYASI);

	//FieldDebugListSet(((FLD_DEB_DAT*)work)->fsys);
	//FieldDebugExitCall(tcb,work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_02(TCB_PTR tcb, void* work)
{
	FLD_DEB_DAT * wk = work;
	u16 item;
	item = ITEM_KURABONOMI;
	do {
		if (MyItem_CheckItem(SaveData_GetMyItem(wk->fsys->savedata), item, 1, HEAPID_FIELD)) {
			item ++;
		} else {
			MyItem_AddItem(SaveData_GetMyItem(wk->fsys->savedata), item, 1, HEAPID_FIELD);
			Snd_SePlay(SEQ_SE_DP_SELECT);
			break;
		}
	}while (item <= ITEM_RENBUNOMI);

	//FieldDebugListSet(((FLD_DEB_DAT*)work)->fsys);
	//FieldDebugExitCall(tcb,work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_03(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;

	if (!MyItem_CheckItem(SaveData_GetMyItem(wk->fsys->savedata), 
				ITEM_KODAKKUZYOURO, 1, HEAPID_FIELD)) {
		MyItem_AddItem(SaveData_GetMyItem(wk->fsys->savedata),
				ITEM_KODAKKUZYOURO, 1, HEAPID_FIELD);
		Snd_SePlay(SEQ_SE_DP_SELECT);
	}
}


static BOOL EdgeFlag = TRUE;
static BOOL AntiAliasFlag = TRUE;

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_test01(TCB_PTR tcb, void * work)
{
	//ポケモンのHP=4,毒状態にする
	u32 buf;
	FLD_DEB_DAT * wk = work;
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(wk->fsys->savedata), 0);
	buf = CONDITION_DOKU;
	PokeParaPut(pp, ID_PARA_condition, &buf);
	buf = PokeParaGet(pp, ID_PARA_hp, NULL);
	buf = 4;
	PokeParaPut(pp, ID_PARA_hp, &buf);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_test02(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	EventSet_EasyMapChange(wk->fsys, ZONE_ID_D05R0114, DOOR_ID_JUMP_CODE,31,53,DIR_DOWN);
	FieldDebugExit(tcb, work);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_test03(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	FIELDSYS_WORK * fsys = wk->fsys;
	POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
	TVTOPIC_Entry_Record_RemoveTrap(fsys, 1, 11);
	TVTOPIC_Entry_Record_GetFlag(fsys, 7);
	TVTOPIC_Entry_Record_Slot(fsys, 100, 10000, 99);
	TVTOPIC_Entry_Record_BTower(fsys, 99, PokeParty_GetMemberPointer(party, 0), TRUE);
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
///ポケパークデータ追加１
//--------------------------------------------------------------------
static void Debug_tamada_ppdata1(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	POKEPARK_DATA * ppd = SaveData_GetPokeParkData(wk->fsys->savedata);
	POKEPARKDATA_Debug_SetData(ppd, 0, MONSNO_RIZAADON, 50, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 1, MONSNO_ZENIGAME, 15, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 2, MONSNO_KAMEERU, 30, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 3, MONSNO_SANDO, 15, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 4, MONSNO_KYATAPII, 7, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 5, MONSNO_MENOKURAGE, 15, 0, 0, gf_mtRand());
}

//--------------------------------------------------------------------
///ポケパークデータ追加２
//--------------------------------------------------------------------
static void Debug_tamada_ppdata2(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	POKEPARK_DATA * ppd = SaveData_GetPokeParkData(wk->fsys->savedata);
	POKEPARKDATA_Debug_SetData(ppd, 0, MONSNO_HAKURYUU, 40, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 1, MONSNO_HUSIGIDANE, 15, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 2, MONSNO_PIPPI, 30, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 3, MONSNO_SANDO, 15, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 4, MONSNO_KENTAROSU, 30, 0, 0, gf_mtRand());
	POKEPARKDATA_Debug_SetData(ppd, 5, MONSNO_SUPIAA, 15, 0, 0, gf_mtRand());
	FieldDebugExit(tcb, work);
}
//--------------------------------------------------------------------
///ＲＴＣペナルティ状態チェック
//--------------------------------------------------------------------
static void Debug_tamada_rtc_check(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	if (GMTIME_IsPenaltyMode(SaveData_GetGameTime(wk->fsys->savedata))) {
		Snd_SePlay(SEQ_SE_DP_BOWA);
		OS_PutString("PENALTY ON\n");
	} else {
		Snd_SePlay(SEQ_SE_DP_SELECT);
		OS_PutString("PENALTY OFF\n");
	}
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tamada_add_usa_group(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	FIELDSYS_WORK * fsys = wk->fsys;
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	STRBUF * groupname;
	STRBUF * myname = MyStatus_CreateNameString(my, HEAPID_FIELD);
	
	groupname = MSGDAT_GetStrDirectAlloc(ARC_MSG, NARC_msg_debug_tamada_dat,
			DF_TAMADA_USA_GROUP_NAME, HEAPID_FIELD);

	RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_LEADER, myname);
	RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_GROUP, groupname);
	RandomGroup_SetSex(rg, RANDOMGROUP_MINE, MyStatus_GetMySex(my));
	RandomGroup_SetRegionCode(rg, RANDOMGROUP_MINE, PM_LANG);
	RandomGroup_SetRandomSeed(rg, RANDOMGROUP_MINE, gf_mtRand());
	RandomGroup_Copy(rg, RANDOMGROUP_MINE, RANDOMGROUP_MYUSE);

	STRBUF_Delete(groupname);
	STRBUF_Delete(myname);
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const GMM_MENU_PARAM FieldDebugTamadaListGMM[] = {
	{DF_LABEL_TAMADA, BMPLIST_RABEL},
	{DF_TAMADA01, (u32)Debug_tamada_01},
	{DF_TAMADA02, (u32)Debug_tamada_02},
	{DF_TAMADA03, (u32)Debug_tamada_03},
	{DF_TAMADA_TEST01, (u32)Debug_tamada_test01},
	{DF_TAMADA_TEST02, (u32)Debug_tamada_test02},
	{DF_TAMADA_TEST03, (u32)Debug_tamada_test03},
	{DF_TAMADA_PPDATA1,	(u32)Debug_tamada_ppdata1},
	{DF_TAMADA_PPDATA2,	(u32)Debug_tamada_ppdata2},
	{DF_TAMADA_RTC_CHECK, (u32)Debug_tamada_rtc_check},
	{DF_TAMADA_ADD_USA_GROUP, (u32)Debug_tamada_add_usa_group},
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugTamadaListSet(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_tamada_dat,
			FieldDebugTamadaListGMM, NELEMS(FieldDebugTamadaListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//============================================================================================
//
//		サブメニュー：テレビ
//
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TVRefresh(TCB_PTR tcb, void * work, int id)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	TVWORK_StartProgram(SaveData_GetTvWork(wk->fsys->savedata));
	DebugFlagData.tv_program_id = id;
	FieldDebugExit(tcb, work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv0(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,0);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv1(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,1);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv2(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,2);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv3(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,3);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv4(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,4);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv5(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,5);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv6(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,6);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv7(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,7);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv8(TCB_PTR tcb, void * work)
{
	TVRefresh(tcb,work,8);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv_clear_mine(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	TV_WORK * tvwk = SaveData_GetTvWork(wk->fsys->savedata);

	TVWORK_ClearMyTopic(tvwk);
	TVRefresh(tcb,work,0);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv_clear_other(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	TV_WORK * tvwk = SaveData_GetTvWork(wk->fsys->savedata);

	TVWORK_ClearOtherTopic(tvwk);
	TVRefresh(tcb,work,0);
}

extern void EventSet_TVDebugInfo(FIELDSYS_WORK * fsys);
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_tv_watch_data(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT * wk = work;
	EventSet_TVDebugInfo(wk->fsys);
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugTVListSet(FIELDSYS_WORK * fsys)
{
	static const GMM_MENU_PARAM FieldDebugTVListGMM[] = {
		{DF_TV_TITLE,			BMPLIST_RABEL},
		{DF_TV_CHANNEL0,		(u32)Debug_tv0},
		{DF_TV_CHANNEL1,		(u32)Debug_tv1},
		{DF_TV_CHANNEL2,		(u32)Debug_tv2},
		{DF_TV_CHANNEL3,		(u32)Debug_tv3},
		{DF_TV_CHANNEL4,		(u32)Debug_tv4},
		{DF_TV_CHANNEL5,		(u32)Debug_tv5},
		{DF_TV_CHANNEL6,		(u32)Debug_tv6},
		{DF_TV_CHANNEL7,		(u32)Debug_tv7},
		{DF_TV_CHANNEL8,		(u32)Debug_tv8},
		{DF_TV_CLEAR_MINE,		(u32)Debug_tv_clear_mine},
		{DF_TV_CLEAR_OTHER,		(u32)Debug_tv_clear_other},
		{DF_TV_CHECK_DATA,		(u32)Debug_tv_watch_data},
	};

	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_tv_dat,
			FieldDebugTVListGMM, NELEMS(FieldDebugTVListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}


//============================================================================================
//
//		サブメニュー：時間
//
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Normal(TCB_PTR tcb, void * work)
{
	DEBUG_StopFakeTime();
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Fix08_00(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeFixTime(8, 0);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Fix12_00(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeFixTime(12, 0);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Fix18_00(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeFixTime(18, 0);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Fix22_00(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeFixTime(22, 0);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_Fix02_00(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeFixTime(2, 0);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_x600(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeTime(600);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_x60(TCB_PTR tcb, void * work)
{
	DEBUG_StartFakeTime(60);
	Snd_SePlay(SEQ_SE_DP_SELECT);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_RTC_control(TCB_PTR tcb, void * work)
{
	FLD_DEB_DAT	* wk = (FLD_DEB_DAT *)work;
	EventSet_DebugRtcCotrol(wk->fsys);
	FieldDebugExit(tcb,work);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------

static const GMM_MENU_PARAM FieldDebugRTCListGMM[] = {
	{DF_LABEL_TIME, BMPLIST_RABEL},
	{DF_TIME0, (u32)Debug_RTC_Normal},
	{DF_TIME1, (u32)Debug_RTC_Fix08_00},
	{DF_TIME2, (u32)Debug_RTC_Fix12_00},
	{DF_TIME3, (u32)Debug_RTC_Fix18_00},
	{DF_TIME4, (u32)Debug_RTC_Fix22_00},
	{DF_TIME5, (u32)Debug_RTC_Fix02_00},
	{DF_TIME6,	 (u32)Debug_RTC_x60},
	{DF_TIME7,	(u32)Debug_RTC_x600},
	{DF_TIME8,	(u32)Debug_RTC_control},
};
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugRTCListSet(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_fldmenu_dat,
			FieldDebugRTCListGMM, NELEMS(FieldDebugRTCListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

//============================================================================================
//
//		サブメニュー：システムフラグ
//
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_bag_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_BagSet(SaveData_GetEventWork(fsys->savedata));
}
#if 0
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_bag_off(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_Bag(SaveData_GetEventWork(fsys->savedata));
}
#endif
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_gameclear_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_GameClearSet(SaveData_GetEventWork(fsys->savedata));
	MyStatus_SetDpClearFlag( SaveData_GetMyStatus(fsys->savedata) );
	
}

#if 0
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_gameclear_off(TCB_PTR tcb, void * work)
{
}
#endif
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_fnote_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_FNoteSet(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_fnote_off(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_FNoteReset(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_spsave_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_CommCounterSet(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_spsave_off(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_CommCounterReset(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_kairiki_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_KairikiSet(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_kairiki_off(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_KairikiReset(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_safari_on(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_SafariSet(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_safari_off(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	SysFlag_SafariReset(SaveData_GetEventWork(fsys->savedata));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_dash(TCB_PTR tcb, void * work)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	PLAYER_SAVE_DATA *psv = Situation_GetPlayerSaveData(SaveData_GetSituation(fsys->savedata));
	Player_SaveDataDashSet(psv, !Player_SaveDataDashCheck(psv));
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void DebugHideMapControl(void * work, int hidemap_id, BOOL set_flag)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	if (set_flag) {
		SysWork_HideMapWorkSet(ev, hidemap_id);
	} else {
		SysWork_HideMapWorkClear(ev, hidemap_id);
	}
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D15_on(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D15, TRUE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D15_off(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D15, FALSE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D30_on(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D30, TRUE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D30_off(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D30, FALSE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_L04_on(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_L04, TRUE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_L04_off(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_L04, FALSE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D18_on(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D18, TRUE);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_D18_off(TCB_PTR tcb, void * work)
{
	DebugHideMapControl(work, HIDEMAP_ID_D18, FALSE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void HaihuOnCommon(void * work, int haihu_id, u16 itemno)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	MYITEM * myitem = SaveData_GetMyItem(fsys->savedata);
	SysWork_HaihuEventWorkSet(ev, haihu_id);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void HaihuOffCommon(void * work, int haihu_id, u16 itemno)
{
	FIELDSYS_WORK * fsys = ((FLD_DEB_DAT *)work)->fsys;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	SysWork_HaihuEventWorkClear(ev, haihu_id);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu01_on(TCB_PTR tcb, void * work)
{
	HaihuOnCommon(work, HAIHUEVENT_ID_D30, 0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu01_off(TCB_PTR tcb, void * work)
{
	HaihuOffCommon(work, HAIHUEVENT_ID_D30, 0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu02_on(TCB_PTR tcb, void * work)
{
	HaihuOnCommon(work, HAIHUEVENT_ID_D18, 0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu02_off(TCB_PTR tcb, void * work)
{
	HaihuOffCommon(work, HAIHUEVENT_ID_D18, 0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu03_on(TCB_PTR tcb, void * work)
{
	HaihuOnCommon(work, HAIHUEVENT_ID_D05, 0);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Debug_flag_haihu03_off(TCB_PTR tcb, void * work)
{
	HaihuOffCommon(work, HAIHUEVENT_ID_D05, 0);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const GMM_MENU_PARAM FieldDebugSysFlagListGMM[] = {
	{DF_FLAG_BAG_ON,	(u32)Debug_flag_bag_on},
//	{DF_FLAG_BAG_OFF,	(u32)Debug_flag_bag_off},
	{DF_FLAG_GAMECLEAR_ON,	(u32)Debug_flag_gameclear_on},
//	{DF_FLAG_GAMECLEAR_OFF,	(u32)Debug_flag_gameclear_off},
	{DF_FLAG_FNOTE_ON,		(u32)Debug_flag_fnote_on},
	{DF_FLAG_FNOTE_OFF,		(u32)Debug_flag_fnote_off},
	{DF_FLAG_SPSAVE_ON,		(u32)Debug_flag_spsave_on},
	{DF_FLAG_SPSAVE_OFF,	(u32)Debug_flag_spsave_off},
	{DF_FLAG_KAIRIKI_ON,	(u32)Debug_flag_kairiki_on},
	{DF_FLAG_KAIRIKI_OFF,	(u32)Debug_flag_kairiki_off},
	{DF_FLAG_SAFARI_ON,		(u32)Debug_flag_safari_on},
	{DF_FLAG_SAFARI_OFF,	(u32)Debug_flag_safari_off},
	{DF_FLAG_DASH,			(u32)Debug_flag_dash},
	{DF_FLAG_D15_ON,		(u32)Debug_flag_D15_on},
	{DF_FLAG_D15_OFF,		(u32)Debug_flag_D15_off},
	{DF_FLAG_D30_ON,		(u32)Debug_flag_D30_on},
	{DF_FLAG_D30_OFF,		(u32)Debug_flag_D30_off},
	{DF_FLAG_L04_ON,		(u32)Debug_flag_L04_on},
	{DF_FLAG_L04_OFF,		(u32)Debug_flag_L04_off},
	{DF_FLAG_D18_ON,		(u32)Debug_flag_D18_on},
	{DF_FLAG_D18_OFF,		(u32)Debug_flag_D18_off},
	{DF_FLAG_HAIHU01_ON,	(u32)Debug_flag_haihu01_on},
	{DF_FLAG_HAIHU01_OFF,	(u32)Debug_flag_haihu01_off},
	{DF_FLAG_HAIHU02_ON,	(u32)Debug_flag_haihu02_on},
	{DF_FLAG_HAIHU02_OFF,	(u32)Debug_flag_haihu02_off},
	{DF_FLAG_HAIHU03_ON,	(u32)Debug_flag_haihu03_on},
	{DF_FLAG_HAIHU03_OFF,	(u32)Debug_flag_haihu03_off},
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void FieldDebugSysFlagList(FIELDSYS_WORK * fsys)
{
	FLD_DEB_DAT * wp;
	wp = FieldDebugListCreateGMM(fsys, NARC_msg_debug_flag_dat,
			FieldDebugSysFlagListGMM, NELEMS(FieldDebugSysFlagListGMM), NULL);
	wp->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}



//============================================================================================
//
//
//		フィールドデバッグメニュー共通処理
//
//
//============================================================================================
/********************************************************************/
/*                                                                  */
/*				データ郡											*/
/*                                                                  */
/********************************************************************/
//------------------------------------------------------------------
//	ビットマップシステム用データ
//------------------------------------------------------------------
static const u8 FieldDebugListPos[][4] = {
	{FDBG_LIST_PX1,FDBG_LIST_PY1,FDBG_INFO_PX1,FDBG_INFO_PY1},
	{FDBG_LIST_PX2,FDBG_LIST_PY2,FDBG_INFO_PX2,FDBG_INFO_PY2},
};

static const BMPWIN_DAT	FieldDebugListWindowData = {
	GF_BGL_FRAME3_M,
	FDBG_LIST_PX1,FDBG_LIST_PY1,
	FDBG_LIST_SX,FDBG_LIST_SY,FDBG_LIST_PL,FDBG_LIST_CH
};

static const BMPWIN_DAT	FieldDebugInfoWindowData = {
	GF_BGL_FRAME3_M,
	FDBG_INFO_PX1,FDBG_INFO_PY1,
	FDBG_INFO_SX,FDBG_INFO_SY,FDBG_INFO_PL,FDBG_INFO_CH
};

static const BMPWIN_DAT	FieldDebugRsltWindowData = {
	GF_BGL_FRAME3_M,
	FDBG_RSLT_PX,FDBG_RSLT_PY,
	FDBG_RSLT_SX,FDBG_RSLT_SY,FDBG_RSLT_PL,FDBG_RSLT_CH
};

static const BMPWIN_DAT	FieldDebugUserWindowData = {
	GF_BGL_FRAME3_M,
	FDBG_USER_PX,FDBG_USER_PY,
	FDBG_USER_SX,FDBG_USER_SY,FDBG_USER_PL,FDBG_USER_CH
};

//------------------------------------------------------------------
//	項目リストデータ
//------------------------------------------------------------------
static const BMPLIST_HEADER FieldDebugListHeader = {
	NULL,				//表示文字データポインタ
	NULL,				//カーソル移動ごとのコールバック関数
	InfoCallBack2,		//１行ごとのコールバック関数
	NULL,				//GF_BGL_BMPWIN構造体データへのポインタ
	0,					//リスト項目数
	8,					//表示最大項目数
	2,					//ラベル表示Ｘ座標
	12,					//項目表示Ｘ座標
	1,					//カーソル表示Ｘ座標
	8,					//表示Ｙ座標
	FBMP_COL_WHITE,		//文字色
	FBMP_COL_BLACK,		//背景色
	FBMP_COL_BLK_SDW,	//文字影色
	0,					//文字間隔Ｘ
	0,					//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
	POKE_SYS,			//文字指定
	0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	NULL,				//ワークポインタ
};

//------------------------------------------------------------------
//	リストシステムからのコールバック※一行表示ごと
//------------------------------------------------------------------
static void	InfoCallBack2(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if(param == BMPLIST_RABEL){
		BmpListTmpColorChange(lw,FBMP_COL_RED_SDW,FBMP_COL_BLACK,FBMP_COL_RED);
	}else{
		BmpListTmpColorChange(lw,FBMP_COL_WHITE,FBMP_COL_BLACK,FBMP_COL_BLK_SDW);
	}
}


///暫定的にここに作成(FLD用Windowキャラクタが揃ったら移動)

//------------------------------------------------------------------
/**
 *	@brief	ユーザー指定のウィンドウキャラクタとパレットをVRAMにセットする
 *
 *	@param	none
 *	@return none
 */
//------------------------------------------------------------------
void FieldBitMapWinCgxSet( GF_BGL_INI * ini )
{
	MenuWinGraphicSet( ini, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
}

/********************************************************************/
/*                                                                  */
/*	デバッグリスト設定												*/
/*                                                                  */
/********************************************************************/
static void		FieldDebugListInit(FLD_DEB_DAT* wp, const GMM_MENU_PARAM * list)
{
	if((wp->DebugList == 0)&&(wp->DebugCursor == 0)){
		//一行目がラベルだったらそこは避ける
		if (list != NULL &&list[wp->DebugList].param == BMPLIST_RABEL) {
			wp->DebugList	= 0;
			wp->DebugCursor	= 1;
		}
	}
}

//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグメニュータスク破棄タスク
 *
 *	ワークエリアの開放を行っているので、デバッグメニュー開放時に必ず呼んで下さい
 *
 *	@param	tcb		TCB_PTR:フィールドデバッグメニューメインタスクへのポインタ
 *	@param	work	void*:FLD_DEB_DAT型ワークへのポインタ
 */
//------------------------------------------------------------------
static void FieldDebugListExitTask(TCB_PTR tcb,void* work)
{
	//ワークメモリ開放
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);

	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
	return;
}

//------------------------------------------------------------------
//BMPリスト設定
//------------------------------------------------------------------
static BMP_MENULIST_DATA * MakeFieldDebugMenu(int arcID, const GMM_MENU_PARAM * list, int count)
{
	int i;
	MSGDATA_MANAGER* msgman;
	BMP_MENULIST_DATA * menulist = BMP_MENULIST_Create(count,HEAPID_FIELD);

	msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,arcID,HEAPID_FIELD);

	for(i = 0;i < count;i++){
		BMP_MENULIST_AddArchiveString(menulist,
			msgman, list[i].str_id, list[i].param );
	}
	MSGMAN_Delete(msgman);

	return menulist;
}

//------------------------------------------------------------------
//BMPリスト設定（どこでもジャンプ用）
//------------------------------------------------------------------
static BMP_MENULIST_DATA * MakeEveryWhereMenu(int count)
{
	//どこでもジャンプ用の特別処理
	int i;
	STRCODE	tmpbuf[128];
	STRBUF	*mstr = STRBUF_Create(128,HEAPID_BASE_DEBUG);
	BMP_MENULIST_DATA * menulist = BMP_MENULIST_Create(count,HEAPID_FIELD);

	for(i = 0;i < count;i++){
		PM_strclear(tmpbuf,EOM_,128);
		STRBUF_Clear(mstr);
		
		//ゾーン名取得
		if(ASCIIcode2DSuni(0,(u8*)ZoneData_GetZoneName(i+2),tmpbuf)){
			tmpbuf[0] = EOM_;
		}
		STRBUF_SetStringCode(mstr,tmpbuf);
		BMP_MENULIST_AddString(menulist,mstr,i+2);
	}
	STRBUF_Delete(mstr);
	return menulist;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドデバッグメニューリストの生成(gmmから文字列取得版)
 * @param	fsys
 * @param	arcID	gmmのアーカイブID
 * @param	list	メニューリスト
 * @param	count	メニューリストの要素数
 * @param	func	メインコントローラのポインタ(NULL=FieldDebugListControlTask)
 *
 * 解放は FieldDebugListFree(void* work)を共有してよい
 */
//------------------------------------------------------------------
static FLD_DEB_DAT * FieldDebugListCreateGMM(FIELDSYS_WORK * fsys,
		int arcID,const GMM_MENU_PARAM * list, int count,TCB_FUNC func)
{
	BMPLIST_HEADER bmplist_h;
	TCB_PTR	pTcb = NULL;
	FLD_DEB_DAT *wp = NULL;
	int i;

	wp = sys_AllocMemory(HEAPID_FIELD,sizeof(FLD_DEB_DAT));
	if(wp == NULL){
		//ワークエリアが取得できなければ何もしない
		OS_Printf("field debug menu crate failed\n");
		return NULL;
	}
	MI_CpuClear8(wp,sizeof(FLD_DEB_DAT));

	wp->fsys = fsys;

	//メイン処理タスク追加
	if(func == NULL){
		pTcb = TCB_Add(FieldDebugListControlTask,wp,0);
	}else{
		pTcb = TCB_Add(func,wp,0);
	}

	//デバッグメニュー用変数初期化
	FieldDebugListInit(wp, list);

	//デバッグメニュー用ウィンドウキャラクタ&パレットセット
	FieldBitMapWinCgxSet( wp->fsys->bgl );

	//BITMAP追加
	wp->pBmpwin = GF_BGL_BmpWinAllocGet(HEAPID_FIELD,1);
	GF_BGL_BmpWinAddEx(wp->fsys->bgl,wp->pBmpwin,&FieldDebugListWindowData);

	//BMPリスト設定
	if (list != NULL) {
		wp->menulist = MakeFieldDebugMenu(arcID, list, count);
	} else {
		wp->menulist = MakeEveryWhereMenu(count);
	}

	bmplist_h = FieldDebugListHeader;
	bmplist_h.list = wp->menulist;
	bmplist_h.win = wp->pBmpwin;
	bmplist_h.count = count;
	wp->blistWk = BmpListSet(&(bmplist_h),wp->DebugList,wp->DebugCursor,HEAPID_FIELD);

	return wp;
}

//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグメニューリストの破棄
 *
 *	@param	work	void*:
 */
//------------------------------------------------------------------
static void FieldDebugListFree(void* work)
{
	FLD_DEB_DAT	*wp;

	wp = (FLD_DEB_DAT*)work;

	//BMPウィンドウOFF
	GF_BGL_BmpWinOff(wp->pBmpwin);

	//BMPリスト破棄
	BMP_MENULIST_Delete(wp->menulist);
	BmpListExit(wp->blistWk,&(wp->DebugList),&(wp->DebugCursor));

	//BMPWindow消去
	GF_BGL_BmpWinDel(wp->pBmpwin);

	//ワーク解放
	sys_FreeMemoryEz(wp->pBmpwin);
	return;
}


//------------------------------------------------------------------
/**
 *	@brief	デバッグメニュー終了メッセージ表示Wait
 *
 *	@param	tcb		TCB_PTR:呼び出し元タスクブロックへのポインタ
 *	@param	work	void*:呼び出し元タスクブロックワークへのポインタ
 */
//------------------------------------------------------------------
static void	FieldDebugListExitMsgWait(TCB_PTR tcb,void* work)
{
	FLD_DEB_DAT	*wp;

	wp = (FLD_DEB_DAT*)work;

	if(sys.trg & PAD_BUTTON_A){
		GF_BGL_BmpWinOff(wp->pBmpwin);
		GF_BGL_BmpWinDel(wp->pBmpwin);

		TCB_ChangeFunc(tcb,FieldDebugListExitTask);
	}
}

//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグの終了へ遷移
 *
 *	デバッグメニュー用ワークとリストの破棄を行う
 *	@param	tcb		TCB_PTR:呼び出し元タスクブロックへのポインタ
 *	@param	work	void*:呼び出し元タスクブロックワークへのポインタ
 */
//------------------------------------------------------------------
static void FieldDebugExit(TCB_PTR tcb,void* work)
{
	//リストの開放処理
	FieldDebugListFree(work);
	//フィールドデバッグタスク共通終了処理へ
	TCB_ChangeFunc(tcb,FieldDebugListExitTask);
	return;
}
//------------------------------------------------------------------
/**
 * @brief	フィールドデバッグメニュー終了処理
 */
//------------------------------------------------------------------
static void FieldDebugExitCall(TCB_PTR tcb,void* work)
{
	//リストの開放処理
	FieldDebugListFree(work);

	//ワークメモリ開放
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);

	//OBJ等の動作停止解除
	//FieldSystemProc_SeqHoldEnd();
	return;
}

//------------------------------------------------------------------
/**
 *	@brief	フィールドデバッグメイン制御タスク
 *
 *	@param	tcb		TCB_PTR:呼び出し元タスクブロックへのポインタ
 *	@param	work	void*:呼び出し元タスクブロックワークへのポインタ
 */
//------------------------------------------------------------------
static void FieldDebugListControlTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	FLD_DEB_DAT	*wp;
	
	wp = (FLD_DEB_DAT*)work;

	ret_code = BmpListMain(wp->blistWk);

	//キー操作判定
	if(sys.trg & PAD_BUTTON_A){
		if(ret_code){
			func = (TCB_FUNC)ret_code;
			func(tcb,work);
		}
		return;
	}
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		if (wp->finish_func != NULL) {
			FIELDSYS_WORK * fsys = wp->fsys;
			void (*func)(FIELDSYS_WORK*) = wp->finish_func;
			FieldDebugExitCall(tcb,work);
			func(wp->fsys);
		} else {
			FieldDebugExit(tcb,work);
		}
		return;
	}
}

//レコード記録の現在値を取得する関数
static u32 DNumInput_RecordGet(SAVEDATA* sv,u32 param)
{
	return RECORD_Get(SaveData_GetRecord(sv),param);
}
//レコード記録に値をセットする関数
static void DNumInput_RecordSet(SAVEDATA* sv,u32 param,u32 value)
{
	RECORD_Set(SaveData_GetRecord(sv),param,value);
}
//タワーの周回数をゲットする関数
static u32 DNumInput_TowerStageGet(SAVEDATA* sv,u32 param)
{
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	return TowerScoreData_SetStage(score,param,BTWR_DATA_get);
}
//タワーの周回数をセットする関数
static void DNumInput_TowerStageSet(SAVEDATA* sv,u32 param,u32 value)
{
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	TowerScoreData_DebugSetStageValue(score,param,value);
}
//タワーに挑戦中のフラグをON/Offする
static u32 DNumInput_TowerChallengeGet(SAVEDATA* sv,u32 param)
{
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	return TowerScoreData_SetFlags(score,param,BTWR_DATA_get);
}
//タワーに挑戦中のフラグをON/Offする
static void DNumInput_TowerChallengeSet(SAVEDATA* sv,u32 param,u32 value)
{
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	if(value){
		TowerScoreData_SetFlags(score,param,BTWR_DATA_set);
	}else{
		TowerScoreData_SetFlags(score,param,BTWR_DATA_reset);
	}
}
//タワーwifiランクを取得
static u32 DNumInput_TowerWifiRankGet(SAVEDATA* sv,u32 param)
{
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	return TowerScoreData_SetWifiRank(score,BTWR_DATA_get);
}
//タワーwifiランクをセット
static void DNumInput_TowerWifiRankSet(SAVEDATA* sv,u32 param,u32 value)
{
	u32 i;
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	
	TowerScoreData_SetWifiRank(score,BTWR_DATA_reset);

	for(i = 0;i < value-1;i++){
		TowerScoreData_SetWifiRank(score,BTWR_DATA_inc);
	}
}
//============================================================================================
//
//
//		フィールドデバッグメニュー 共通数値インプット処理
//
//
//============================================================================================
/**
 *	数値入力用の見出し文字列指定、paramは0からの連番
 *	Debug_NumInput_Listと並びをそろえておく必要あり！
 */
#include "application/app_tool.h"
#if 0
static const GMM_MENU_PARAM Debug_NumInput_Gmm[] = {
 {dni_rec_renshou_max01,	0},	
 {dni_rec_renshou_now01,	1},	
 {dni_tower_try01,		2},	
 {dni_tower_stage01,	3},	
 {dni_rec_renshou_max02,	4},	
 {dni_rec_renshou_now02,	5},	
 {dni_tower_try02,		6},	
 {dni_tower_stage02,	7},	
 {dni_rec_renshou_max03,	8},	
 {dni_rec_renshou_now03,	9},	
 {dni_tower_try03,		10},	
 {dni_tower_stage03,	11},	
 {dni_rec_renshou_max04,	12},	
 {dni_rec_renshou_now04,	13},	
 {dni_tower_try04,		14},	
 {dni_tower_stage04,	15},	
 {dni_rec_renshou_max05,	16},	
 {dni_rec_renshou_now05,	17},	
 {dni_tower_try05,		18},	
 {dni_tower_stage05,	19},	
 {dni_rec_tower_entry,		20},	
 {dni_rec_tower_win,		21},	
 //↑ここまでバトルタワー
 
};	
static const DEBUG_NUMINPUT_LIST Debug_NumInput_List[] = {
 {0,9999,	RECID_RENSHOU_SINGLE,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,9999,	RECID_RENSHOU_SINGLE_CNT,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,1,		BTWR_SFLAG_SINGLE_RECORD,DNumInput_TowerChallengeSet,DNumInput_TowerChallengeGet},
 {0,9999,	0,DNumInput_TowerStageSet,DNumInput_TowerStageGet},
 {0,9999,	RECID_RENSHOU_DOUBLE,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,9999,	RECID_RENSHOU_DOUBLE_CNT,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,1,		BTWR_SFLAG_DOUBLE_RECORD,DNumInput_TowerChallengeSet,DNumInput_TowerChallengeGet},
 {0,9999,	1,DNumInput_TowerStageSet,DNumInput_TowerStageGet},
 {0,9999,	RECID_RENSHOU_MULTI,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,9999,	RECID_RENSHOU_MULTI_CNT,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,1,		BTWR_SFLAG_MULTI_RECORD,DNumInput_TowerChallengeSet,DNumInput_TowerChallengeGet},
 {0,9999,	2,DNumInput_TowerStageSet,DNumInput_TowerStageGet},
 {0,9999,	RECID_RENSHOU_COMM_MULTI,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,9999,	RECID_RENSHOU_COMM_MULTI_CNT,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,1,		BTWR_SFLAG_CMULTI_RECORD,DNumInput_TowerChallengeSet,DNumInput_TowerChallengeGet},
 {0,9999,	3,DNumInput_TowerStageSet,DNumInput_TowerStageGet},
 {0,9999,	RECID_RENSHOU_WIFI,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,9999,	RECID_RENSHOU_WIFI_CNT,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,1,		BTWR_SFLAG_WIFI_RECORD,DNumInput_TowerChallengeSet,DNumInput_TowerChallengeGet},
 {0,9999,	4,DNumInput_TowerStageSet,DNumInput_TowerStageGet},
 {0,99999,RECID_BTOWER_CHALLENGE,DNumInput_RecordSet,DNumInput_RecordGet},
 {0,99999,RECID_BTOWER_WIN,DNumInput_RecordSet,DNumInput_RecordGet},
 //↑ここまでバトルタワー
};
#endif

static void DebugNumInputControlTask(TCB_PTR tcb,void* work);

/**
 *	@brief	汎用デバッグ数値入力インターフェース
 */
static void FieldDebugNumInputList(FIELDSYS_WORK * fsys,
	const DEBUG_NUMINPUT_LIST* pList,const GMM_MENU_PARAM* pMenu,int num)
{
	u32 i,count;
	BMPLIST_HEADER bmplist_h;
	TCB_PTR	pTcb = NULL;
	DEBUG_NUMINPUT_WORK* wk;
	GMM_MENU_PARAM* list;
	WORDSET	*wset;
	MSGDATA_MANAGER* pMan;
	STRBUF*			tmp;

	wk = sys_AllocMemory(HEAPID_FIELD,sizeof(DEBUG_NUMINPUT_WORK));
	MI_CpuClear8(wk,sizeof(DEBUG_NUMINPUT_WORK));
	
	wk->pFdd = sys_AllocMemory(HEAPID_FIELD,sizeof(FLD_DEB_DAT));
	MI_CpuClear8(wk->pFdd,sizeof(FLD_DEB_DAT));
	
	wk->fsys = fsys;
	wk->pFdd->fsys = fsys;
	wk->pList = pList;
	wk->pMenu = pMenu;
	wk->list_num = num;

	//数字列描画用bmpウィンドウを追加
	GF_BGL_BmpWinAdd( fsys->bgl, &wk->win, FLD_MBGFRM_FONT, 16, 1, 12, 2,
			FDBG_LIST_PL,FDBG_LIST_CH+(FDBG_LIST_SX*FDBG_LIST_SY));
	GF_BGL_BmpWinDataFill(&wk->win,APP_WINCLR_COL(FBMP_COL_WHITE));
	GF_BGL_BmpWinOn(&wk->win);

	//文字セット追加
	wset = WORDSET_CreateEx(1,2,HEAPID_FIELD);
	pMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_debug_numinput_dat,HEAPID_FIELD);
	tmp = MSGMAN_AllocString(pMan,dni_num_print);
	
	for(i = 0;i < 10;i++){
		wk->nbuf[i] = STRBUF_Create(2,HEAPID_FIELD);
		WORDSET_RegisterNumber(wset,0,i,1,
					NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);	
		WORDSET_ExpandStr(wset,wk->nbuf[i],tmp);
	}
	STRBUF_Delete(tmp);
	MSGMAN_Delete(pMan);
	WORDSET_Delete(wset);

	//メイン処理タスク追加
	pTcb = TCB_Add(DebugNumInputControlTask,wk,0);

	//デバッグメニュー用変数初期化
	FieldDebugListInit(wk->pFdd,wk->pMenu);

	//デバッグメニュー用ウィンドウキャラクタ&パレットセット
	FieldBitMapWinCgxSet( fsys->bgl );

	//BITMAP追加
	wk->pFdd->pBmpwin = GF_BGL_BmpWinAllocGet(HEAPID_FIELD,1);
	GF_BGL_BmpWinAddEx(fsys->bgl,wk->pFdd->pBmpwin,&FieldDebugListWindowData);

	//BMPリスト設定
	wk->pFdd->menulist = MakeFieldDebugMenu(NARC_msg_debug_numinput_dat,
//			Debug_NumInput_Gmm,NELEMS(Debug_NumInput_Gmm));
			wk->pMenu,wk->list_num);

	bmplist_h = FieldDebugListHeader;
	bmplist_h.list = wk->pFdd->menulist;
	bmplist_h.win = wk->pFdd->pBmpwin;
	bmplist_h.count = wk->list_num;//NELEMS(Debug_NumInput_Gmm);
	wk->pFdd->blistWk = BmpListSet(&(bmplist_h),wk->pFdd->DebugList,wk->pFdd->DebugCursor,HEAPID_FIELD);

	wk->pFdd->finish_func = FieldDebugListSet;

	//イベントフック
	FieldSystemProc_SeqHold();
}

#define FCOLS_BLACK	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define FCOLS_GREEN	(GF_PRINTCOLOR_MAKE(FBMP_COL_GREEN,FBMP_COL_GRN_SDW,FBMP_COL_WHITE))

static void ninput_print(DEBUG_NUMINPUT_WORK* wk)
{
	u32 i,val,tmp,ofs,now;

	tmp = 1;
	val = 0;
	ofs = 12*8;
	GF_BGL_BmpWinDataFill(&wk->win,APP_WINCLR_COL(FBMP_COL_WHITE));

	now = wk->value;
	for(i = 0;i < (wk->n_keta-1);i++){
		tmp *= 10;
	}
	for(i = wk->n_keta;i > 0;i--){
		val = now/tmp;
		if(val != 0){
			now -= val*tmp;
		}
		if((i-1) == wk->sel){
			GF_STR_PrintColor(&wk->win,FONT_SYSTEM,
				wk->nbuf[val],ofs-9*i,0,MSG_NO_PUT,FCOLS_GREEN,NULL);
		}else{
			GF_STR_PrintColor(&wk->win,FONT_SYSTEM,
				wk->nbuf[val],ofs-9*i,0,MSG_NO_PUT,FCOLS_BLACK,NULL);
		}
		tmp /= 10;
	}
	GF_BGL_BmpWinOn(&wk->win);
}

static int ninput_updown(DEBUG_NUMINPUT_WORK* wk,int mode)
{
	static const u32 ninput_incdec[] = {
	1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000
	};
	if(mode == 0){	//add
		if((wk->value+ninput_incdec[wk->sel] > wk->n_max)||
			(s64)(wk->value)+ninput_incdec[wk->sel]>0xFFFFFFFF){
			wk->value = wk->n_min;
		}else{
			wk->value += ninput_incdec[wk->sel];
		}
	}else{
		if((s64)(wk->value)-ninput_incdec[wk->sel] < wk->n_min){
			wk->value = wk->n_max;
		}else{
			wk->value -= ninput_incdec[wk->sel];
		}
	}
	return 1;
}
static int ninput_side(DEBUG_NUMINPUT_WORK* wk,int mode)
{
	if(mode == 0){	//left
		if(wk->sel < wk->n_keta){
			wk->sel++;
			return 1;
		}
	}else{
		if(wk->sel > 0){	
			wk->sel--;
			return 1;
		}
	}
	return 0;
}

/**
 *	@brief	数値入力コントロール
 */
static void DebugNumInputControlTask(TCB_PTR tcb,void* work)
{
	u32 i,value,flag;
	s32	ret_code;
	DEBUG_NUMINPUT_WORK* wk = (DEBUG_NUMINPUT_WORK*)work;

	switch(wk->seq){
	case 0:
		ret_code = BmpListMain(wk->pFdd->blistWk);

		if(sys.trg & PAD_BUTTON_CANCEL){
			FieldDebugExitCall(tcb,wk->pFdd);
			FieldDebugListSet(wk->fsys);
			GF_BGL_BmpWinOff(&wk->win);
			GF_BGL_BmpWinDel(&wk->win);
			for(i = 0;i < 10;i++){
				STRBUF_Delete(wk->nbuf[i]);
			}
			sys_FreeMemoryEz(work);
			return;
		}
		if(!(sys.trg & PAD_BUTTON_DECIDE)){
			return;
		}
		wk->sel = 0;
		wk->now = ret_code;
		wk->n_min = wk->pList[wk->now].min;
		wk->n_max = wk->pList[wk->now].max;

		if((wk->pList[wk->now].get_func)!=NULL){
			wk->value = 
				(wk->pList[wk->now].get_func)(
					wk->fsys->savedata,wk->pList[wk->now].param);
		}else{
			wk->value = wk->n_min;
		}

		//4294967295
		if(wk->n_max>=1000000000){
			wk->n_keta = 10;
		}else{
			value = 10;
			for(i = 1;i < 10;i++){
				if((wk->n_max/value)==0){
					wk->n_keta = i;
					break;
				}
				value *= 10;
			}
		}
		ninput_print(wk);
		wk->seq++;
		break;
	case 1:	//数値入力
		if(sys.trg & PAD_BUTTON_CANCEL){
			wk->seq++;
			return;
		}else if(sys.trg & PAD_BUTTON_DECIDE){
			//数値適用
			(wk->pList[wk->now].set_func)(
				wk->fsys->savedata,wk->pList[wk->now].param,wk->value);
			wk->seq++;
			return;
		}
		flag = 0;
		if(sys.trg & PAD_KEY_DOWN){
			flag = ninput_updown(wk,1);	
		}else if(sys.trg & PAD_KEY_UP){
			flag = ninput_updown(wk,0);	
		}else if(sys.trg & PAD_KEY_LEFT){
			flag = ninput_side(wk,0);	
		}else if(sys.trg & PAD_KEY_RIGHT){
			flag = ninput_side(wk,1);	
		}
		//描画更新
		if(flag){
			ninput_print(wk);
		}
		break;
	case 2:
		GF_BGL_BmpWinDataFill(&wk->win,APP_WINCLR_COL(FBMP_COL_WHITE));
		GF_BGL_BmpWinOn(&wk->win);
		wk->seq = 0;
		break;
	}
}


//============================================================================================
//
//
//		デバッグ用情報表示関連
//
//
//============================================================================================

#ifdef DEBUG_BG1_PRINT

#define SCREEN_CHARA_W		(32)
#define	DEBUG_TICK_MAX	(4)
#define	DEBUG_TICK_MAX2	(10)
static u32 store_ticks[DEBUG_TICK_MAX];
static u16 store_max_ticks[DEBUG_TICK_MAX];
static char *palwork;
static NNSG2dPaletteData *pal;
static u32 store_ticks2[DEBUG_TICK_MAX2];
//------------------------------------------------------------------
/**
 * @brief	デバッグ用表示フック処理
 * @param	flag	BOOL	フックするかどうか
 */
//------------------------------------------------------------------
void DebugStressDispHookSet(BOOL flag)
{
	DebugViewHookFlag = flag;
}

//------------------------------------------------------------------
/**
 * 
 * DEBUG 1文字スクリーン反映
 * 
 **/
//------------------------------------------------------------------
static void DebugCharPut(u16 *screen, char c, int x, int y)
{
	if(c==0x20){
		c = 0x29;
	}
	if(c=='='){
		c = 0x30+10;
	}
	if(c=='-'){   // マイナス表示が出ていなかったのでMに置換
		c = 'M';
	}
	screen[x+y*SCREEN_CHARA_W] = 0x2000+(c-0x2F);
}

//------------------------------------------------------------------
/**
 * 
 * DEBUG 文字列スクリーン反映
 * 
 **/
//------------------------------------------------------------------
static void DebugStrPut(GF_BGL_INI *ini, char *str,int x, int y)
{
	int  n=0;
	u16  *screen;
	screen = GF_BGL_ScreenAdrsGet( ini, FLD_MBGFRM_EFFECT1 );

	while(str[n]!=0){
		DebugCharPut(screen,str[n],x+n,y);
		n++;
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void DebugClearScreen(GF_BGL_INI * ini)
{
	u16  *screen;
	screen = GF_BGL_ScreenAdrsGet( ini, FLD_MBGFRM_EFFECT1 );
	MI_CpuClearFast(screen, sizeof(u16) * 32 * 24);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void DebugBgPrint_Position( GF_BGL_INI * ini, FIELDSYS_WORK * fsys, char * str )
{
	VecFx32 pos;
	Player_VecPosGet(fsys->player,&pos);
	sprintf(str,"X = %05d, Y = %05d, Z = %05d  ",FX_Whole(pos.x),FX_Whole(pos.y),FX_Whole(pos.z));
	DebugStrPut(ini, str,1,2);

	if(CommMPIsInitialize()){
		int id = CommGetCurrentID();
		int cannel = CommMPGetChannel();
		sprintf(str,"ID = %d CHANNEL = %d",id,cannel);
		DebugStrPut(ini, str,1,3);
	}
}

//------------------------------------------------------------------
/**
 * @brief	3D描画情報表示
 */
//------------------------------------------------------------------
static void DebugBgPrint_Stress( GF_BGL_INI * ini, FIELDSYS_WORK * fsys, char * str )
{
	//ジオメトリエンジンが受け取ったポリゴン数
	sprintf(str,"REG POLY LIST = %04d",G3X_GetPolygonListRamCount());
	DebugStrPut(ini,str,1,2);

	//NitroSystemに渡したポリゴン数
	sprintf(str,"MDL POLY LIST = %04d",D_3D_DC_DrawPolygonGet());
	DebugStrPut(ini,str,1,3);

	//ジオメトリエンジンが受け取った頂点数
	sprintf(str,"REG VTX COUNT = %04d",G3X_GetVtxListRamCount());
	DebugStrPut(ini,str,1,4);

	//NitroSystemに渡した頂点数
	sprintf(str,"MDL VTX COUNT = %04d",D_3D_DC_DrawVertexGet());
	DebugStrPut(ini,str,1,5);

	//NitroSystemでポリゴン描画を呼び出した回数
	sprintf(str,"DRAW COUNT    = %04d",D_3D_DC_DrawNumGet());
	DebugStrPut(ini,str,1,6);

	//テクスチャVRAMに転送しているテクスチャの量
	sprintf(str,"VRAM TEX    = %06d",D_3D_DC_VramTexSizeGet());
	DebugStrPut(ini,str,1,7);	

	//パレットVRAMに転送しているパレットの量
	sprintf(str,"PAL  TEX    = %06d",D_3D_DC_VramPalSizeGet());
	DebugStrPut(ini,str,1,8);


	//各処理の負荷をタイマーで取得
	DEBUG_PrintTickResult(ini, str, 1, 9);

    // makeした日時を表示
	sprintf(str,"BUILD %s %s", BuildDate, BuildTime);
    {
        int i;
        for(i=0;str[i]!=0;i++){
            str[i] = toupper(str[i]);
        }
        DebugStrPut(ini,str, 1, 12);
    }

    {
        u8 macAddress[WM_SIZE_MACADDR];

        OS_GetMacAddress(macAddress);
        sprintf(str, "MAC %02X%02X%02X%02X%02X%02X\n",
                    macAddress[0],macAddress[1],macAddress[2],
                    macAddress[3],macAddress[4],macAddress[5]);
        DebugStrPut(ini,str,1,13);
    }

}

//------------------------------------------------------------------
/**
 * @brief	個別ビーコン情報表示ルーチン
 */
//------------------------------------------------------------------
static void DebugBeaconPut( GF_BGL_INI * ini, const _GF_BSS_DATA_INFO * gfdata, char * str, int y)
{
	UNION_BEACON_STATE *beaconState;
	MYSTATUS * my;

	beaconState = (UNION_BEACON_STATE*)gfdata->regulationBuff;

	sprintf(str, "%-5d ", gfdata->pokeID & 0xffff);
	DebugStrPut(ini, str, 1, y);

	sprintf(str, "%02X %02X %02X ", gfdata->serviceNo, gfdata->regulationNo,
			gfdata->connectNum, gfdata->soloDebugNo);
	DebugStrPut(ini, str, 1 + 6, y);

	my = (MYSTATUS *)(gfdata->myStatusBuff);
	if (MyStatus_GetMySex(my) == PM_MALE) {
		DebugStrPut(ini, "M", 1 + 6 + 9, y);
	} else {
		DebugStrPut(ini, "F", 1 + 6 + 9, y);
	}
	sprintf(str, "%02X %02X%02X%02X%02X", beaconState->mode,
			beaconState->c_face[0],
			beaconState->c_face[1],
			beaconState->c_face[2],
			beaconState->c_face[3]
		   );
	DebugStrPut(ini, str, 1 + 6 + 9 + 1, y);
}

//------------------------------------------------------------------
/**
 * @brief	個別ビーコン情報表示ルーチン
 */
//------------------------------------------------------------------
static void DebugBeaconPut2( GF_BGL_INI * ini, const _GF_BSS_DATA_INFO * gfdata, char * str, int y)
{
	UNION_BEACON_STATE *beaconState;
	MYSTATUS * my;
	char * sex_str;

	beaconState = (UNION_BEACON_STATE*)gfdata->regulationBuff;
	
	my = (MYSTATUS *)(gfdata->myStatusBuff);
	if (MyStatus_GetMySex(my) == PM_MALE) {
		sex_str = "M";
	} else {
		sex_str = "F";
	}

	sprintf(str, "%s%-5d %02X %X %02X ",
			sex_str,
			gfdata->pokeID & 0xffff,
			gfdata->serviceNo,
			gfdata->connectNum,
			beaconState->mode);
	DebugStrPut(ini, str, 1, y);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void MakeMACAddressStr(char * str, const u8 * mac)
{
	sprintf(str,"%02X%02X%02X%02X%02X%02X ", mac[0],mac[1],mac[2], mac[3],mac[4],mac[5]);
}

//------------------------------------------------------------------
/**
 * @brief	ビーコン情報表示
 */
//------------------------------------------------------------------
static void DebugBgPrint_CommBeacon( GF_BGL_INI * ini, FIELDSYS_WORK * fsys, char * str )
{
	WMBssDesc* desc;
	_GF_BSS_DATA_INFO * gfdata;
	int i;

	DebugClearScreen( ini );

	//DebugStrPut(ini, "ID    SV RG CN  MD CHILDS", 1, 1);
	DebugStrPut(ini, " ID    SV C MD MACADRS", 1, 1);
	gfdata = CommMPGetMyGFBss();
	if (gfdata != NULL) {
		SYSTEMDATA * sysdt = SaveData_GetSystemData(fsys->savedata);
		const u8 * mac = SYSTEMDATA_GetMacAddress(sysdt);
		DebugBeaconPut2(ini, gfdata, str, 2);
		MakeMACAddressStr(str, mac);
		DebugStrPut(ini, str, 1 + 15, 2);
		//DebugBeaconPut(ini, gfdata, str, 2);
	}

	for (i = 0; i < SCAN_PARENT_COUNT_MAX; i++) {
		desc = CommMPGetWMBssDesc(i);
		if (desc == NULL) {
			DebugStrPut(ini, "NO DATA", 1, 4 + i);
			continue;
		}
		gfdata = (_GF_BSS_DATA_INFO *)desc->gameInfo.userGameInfo;
		DebugBeaconPut2(ini, gfdata, str, 4 + i);
		MakeMACAddressStr(str, desc->bssid);
		DebugStrPut(ini, str, 1 + 15, 4 + i);
		//DebugBeaconPut(ini, gfdata, str, 4 + i);
		sprintf(str, " %02X", CommMPGetBConUncacheTime(i));
		DebugStrPut(ini, str, 1 + 15 + 13, 4 + i);
		//DebugStrPut(ini, str, 1 + 6 + 9 + 1 + 11, 4 + i);

	}
}

//------------------------------------------------------------------
/**
 * 
 * DEBUG 文字列描画(フィールド専用、BG1面に描画）
 * 
 * 改行なし、「０～９、ＡＢＣ（大文字のみ）、＝、スペース」を表示
 * 
 * 
 **/
//------------------------------------------------------------------
void DebugBgPrint(GF_BGL_INI *ini, FIELDSYS_WORK *fsys)
{

#ifdef DEBUG_3DDRAW_COUNT	
	s32 result;
	char str[100];
	

	if(DebugViewHookFlag){
		return;
	}

	if(DebugStressFlg == DEBUG_VIEW_OFF){
		return;
	}

	//主人公座標
	sprintf(str,"GRIDX = %03d, GRIDZ = %03d  ",Player_NowGPosXGet(fsys->player),Player_NowGPosZGet(fsys->player));
	DebugStrPut(ini, str,1,1);


	switch (DebugStressFlg) {
	default:
	case DEBUG_VIEW_OFF:
		break;

	case DEBUG_VIEW_POS:
		DebugBgPrint_Position( ini, fsys, str );
		break;

	case DEBUG_VIEW_STRESS:
		DebugBgPrint_Stress( ini, fsys, str );
		break;

	case DEBUG_VIEW_UNIONBEACON:
		DebugBgPrint_CommBeacon( ini, fsys, str );
		break;
	}
	GF_BGL_LoadScreenReq( ini,FLD_MBGFRM_EFFECT1 );	//デバッグ文字列面のスクリーンを転送
#endif	
}

//--------------------------------------------------------------------
// デバッグ表示のためにPAL・ｷｬﾗ転送
//--------------------------------------------------------------------
static void DebugBgCharPalSet(GF_BGL_INI *ini)
{
	pal = GF_BGL_NTRCHR_PalLoad( (void*)&palwork, HEAPID_FIELD,"data/nfont.NCLR");
	GF_BGL_NTRCHR_CharLoad( ini, FLD_MBGFRM_EFFECT1, "data/nfont.NCGR", 0);
	GX_LoadBGPltt( pal->pRawData, STRESS_INFO_PAL_OFFSET, STRESS_INFO_PAL_SIZE);

}
//--------------------------------------------------------------------
//	パレット用ワークを開放
//--------------------------------------------------------------------
static void DebugBgCharPalFree(void)
{
	// DEBUG文字列用のパレット領域を解放
	sys_FreeMemoryEz(palwork);
}


//--------------------------------------------------------------------
/**
 * @brief	フィールド制御タスク：デバッグ負荷表示定義データ
 * @param	fwk		フィールド制御タスクのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param	work	汎用ワークへのポインタ（未使用）
 */
//--------------------------------------------------------------------
static void DebugBgPrint_Create(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	GF_BGL_PrioritySet(FLD_MBGFRM_EFFECT1, 0);
	//デフォルトは非表示にしとく
	DebugStressDispSet(DEBUG_VIEW_OFF);
	//デバッグ文字表示用キャラクタ・パレット転送
	DebugBgCharPalSet(fsys->bgl);
}

//--------------------------------------------------------------------
/**
 * @brief	フィールド制御タスク：デバッグ負荷表示定義データ
 * @param	fwk		フィールド制御タスクのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param	work	汎用ワークへのポインタ（未使用）
 */
//--------------------------------------------------------------------
static void DebugBgPrint_Delete(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	DebugBgCharPalFree();
}

//--------------------------------------------------------------------
/**
 * @brief	フィールド制御タスク：デバッグ負荷表示定義データ
 * @param	fwk		フィールド制御タスクのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param	work	汎用ワークへのポインタ（未使用）
 */
//--------------------------------------------------------------------
static void DebugBgPrint_Update(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	DebugBgPrint(fsys->bgl,fsys);
}

//--------------------------------------------------------------------
/**
 * @brief	フィールド制御タスク：デバッグ負荷表示定義データ
 */
//--------------------------------------------------------------------
static const FLDMAPFUNC_DATA DebugBgPrtData = {
	FLDMAP_PRI_DEBUGPRINT,
	0,
	DebugBgPrint_Create,
	DebugBgPrint_Delete,
	DebugBgPrint_Update,
	NULL
};

//--------------------------------------------------------------------
/**
 * @brief	フィールド制御タスク：デバッグ負荷表示の追加
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//--------------------------------------------------------------------
void Debug_Entry_StressPrintTask(FIELDSYS_WORK * fsys)
{
	FLDMAPFUNC_Create(fsys->fldmap->fmapfunc_sys, &DebugBgPrtData);
}


//============================================================================================
//
//
//			デバッグ用処理負荷チェック関連
//
//
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	デバッグ用処理負荷簡易モニタ、初期化
 */
//--------------------------------------------------------------------
void DEBUG_InitTick(void)
{
	OS_SetTick(0);
}

//--------------------------------------------------------------------
/**
 * @brief	デバッグ用処理負荷簡易モニタ、コストの取得
 * @param	id	保持ワークのID指定
 */
//--------------------------------------------------------------------
void DEBUG_StoreTick(int id)
{
	SDK_ASSERT(0 <= id && id < DEBUG_TICK_MAX);
	store_ticks[id] = OS_TicksToMicroSeconds(OS_GetTick());
	if (store_ticks[id] > store_max_ticks[id]) {
		store_max_ticks[id] = store_ticks[id];
	}
	OS_SetTick(0);
}

//--------------------------------------------------------------------
/**
 * @brief	デバッグ用処理負荷最大値のクリア
 */
//--------------------------------------------------------------------
void DEBUG_ClearMaxTick(void)
{
	int i;
	for (i = 0; i < DEBUG_TICK_MAX; i++) {
		store_max_ticks[i] = 0;
	}
}
//--------------------------------------------------------------------
/**
 * @brief
 * @param	x, y
 */
//--------------------------------------------------------------------
void DEBUG_PrintTickResult(GF_BGL_INI *ini, char * str, int x, int y)
{
	int i;
	int result= 0;

	//各関数の間に埋め込んだTick数の表示
	DebugStrPut(ini,"TICKS ", x, y);	
	for (i = 0; i < DEBUG_TICK_MAX; i++) {
		sprintf(str, "-%05d", store_ticks[i]);
		DebugStrPut(ini,str, x + 6 + 6 * i, y);
		sprintf(str, " %05d", store_max_ticks[i]);
		DebugStrPut(ini,str, x + 6 + 6 * i, y + 1);
	}

	//メインループ期間に対してのパーセンテージ
	for(i=0;i<DEBUG_TICK_MAX;i++){
		result += store_ticks[i];
	}
									// １００パーセントで、1Syncのクロック数を(1Sync+次のSyncのVblank期間まで)を262ラインで割る
	sprintf(str,"MAINSTRESS = %d  ",(100*result)/(16700 * (192+262)/262));
	DebugStrPut(ini,str, x, y+2);

}

//--------------------------------------------------------------------
/**
 * @brief	デバッグ用処理負荷簡易モニタ、コストの取得
 * @param	id	保持ワークのID指定
 */
//--------------------------------------------------------------------
void DEBUG_StoreTick2(int id)
{
	SDK_ASSERT(0 <= id && id < DEBUG_TICK_MAX2);
	store_ticks2[id] = OS_TicksToMicroSeconds(OS_GetTick());
	OS_SetTick(0);
}

//--------------------------------------------------------------------
/**
 * @brief
 * @param	x, y
 */
//--------------------------------------------------------------------
void DEBUG_OS_PrintTick(void)
{
	int i;
	int result= 0;

	//各関数の間に埋め込んだTick数の表示
	for (i = 0; i < DEBUG_TICK_MAX2; i++) {
		OS_Printf("%d:-%d\n", i,store_ticks2[i]);
	}
}



#endif //DEBUG_BG1_PRINT


#endif	//PM_DEBUG
