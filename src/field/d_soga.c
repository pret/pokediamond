//============================================================================================
/**
 *	デバッグメニュー「曽我部」の処理
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "field/field.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "fld_bmp.h"
#include "system/pm_str.h"
#include "vm.h"
#include "script.h"
#include "scrcmd.h"
#include "sxytype.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "battle/battle_common.h"
#include "..\fielddata\script\connect_def.h"

//============================================================================================
//	メイン
//============================================================================================
#define	TCB_WK_SIZE		( 4*16 )

enum {
	WK_SEQ = 0,
//	WK_WIN_INDEX,
//	WK_LIST_ID,
	WK_LIST_RET,

	WK_MAX
};

typedef struct {
	void * fsys;
	GF_BGL_BMPWIN	win;
	BMPLIST_WORK * lw;
	u32	work[WK_MAX];
}D_SOGABE_PARAM;

typedef void (*pHNfunc)(void *);


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void DebugSogabeMenuInit( void * fsys );
static void DS_MenuMain( TCB_PTR _tcb, void * work );
static void DS_MenuExit( D_SOGABE_PARAM * wk );

static void DebugBattle1vs1(FIELDSYS_WORK * fsys);
static void DebugBattle2vs2(FIELDSYS_WORK * fsys);
static void DebugBattleTrainer1vs1(FIELDSYS_WORK * fsys);
static void DebugBattleSIO(FIELDSYS_WORK * fsys);

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static const STRCODE menu_msg01[] = { n1_,v__,s__,n1_,BA_,TO_,RU_,EOM_ };
static const STRCODE menu_msg02[] = { n2_,v__,s__,n2_,BA_,TO_,RU_,EOM_ };
static const STRCODE menu_msg03[] = { TO_,RE_,bou_,NA_,bou_,BA_,TO_,RU_,EOM_ };
static const STRCODE menu_msg04[] = { tu_,u_,si_,n_,EOM_ };

static const BMPLIST_DATA d_menu_list[] =
{
	{ (const void *)menu_msg01, (u32)DebugBattle1vs1		},
	{ (const void *)menu_msg02, (u32)DebugBattle2vs2		},
	{ (const void *)menu_msg03, (u32)DebugBattleTrainer1vs1 },
	{ (const void *)menu_msg04, (u32)DebugBattleSIO },
};

static const BMPLIST_HEADER d_menu_list_h = {
	d_menu_list,			// 表示文字データポインタ
	NULL,					// カーソル移動ごとのコールバック関数
	NULL,					// 一列表示ごとのコールバック関数
	NULL,
	NELEMS(d_menu_list),	// リスト項目数
	11,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	12,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	FONT_SYSTEM,			// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};



void DebugSogabeMenuInit( void * fsys )
{
	D_SOGABE_PARAM * wk;
	GF_BGL_INI * bgl;
	BMPLIST_HEADER	list_h;

	bgl = FieldBglIniGet( fsys );

	wk = (D_SOGABE_PARAM *)TCB_GetWork(
					PMDS_taskAdd( DS_MenuMain, sizeof(D_SOGABE_PARAM), 0, HEAPID_BASE_DEBUG ) );

	wk->fsys = fsys;
	wk->work[ WK_SEQ ] = 0;
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 1, 10, 12, 13, 1 );

	list_h = d_menu_list_h;
	list_h.win = &wk->win;
	wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->win );
}

static void DS_MenuMain( TCB_PTR _tcb, void * work )
{
	D_SOGABE_PARAM * wk = (D_SOGABE_PARAM *)work;
	GF_BGL_INI * bgl;
	u32	ret;

	switch( wk->work[ WK_SEQ ] ){
	case 0:
		ret = BmpListMain( wk->lw );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			DS_MenuExit( wk );
			PMDS_taskDel( _tcb );
			FieldSystemProc_SeqHoldEnd();
			break;
		default:
			wk->work[WK_LIST_RET] = ret;
			wk->work[WK_SEQ]++;
		}
		break;
	case 1:
		{
			pHNfunc func = (pHNfunc)wk->work[WK_LIST_RET];
			void * fsys = wk->fsys;

			DS_MenuExit( wk );
			PMDS_taskDel( _tcb );
			func( fsys );
		}
	}
}

static void DS_MenuExit( D_SOGABE_PARAM * wk )
{
	BmpListExit( wk->lw, NULL, NULL );

	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win );
}

extern	BOOL DebugFieldEncount(FIELDSYS_WORK * fsys);
extern	BOOL DebugFieldEncount2vs2(FIELDSYS_WORK * fsys);
extern	BOOL DebugFieldTrainerEncount(FIELDSYS_WORK * fsys);

static void DebugBattle1vs1(FIELDSYS_WORK * fsys)
{
	DebugFieldEncount(fsys);
}

static void DebugBattle2vs2(FIELDSYS_WORK * fsys)
{
	DebugFieldEncount2vs2(fsys);
}

static void DebugBattleTrainer1vs1(FIELDSYS_WORK * fsys)
{
	DebugFieldTrainerEncount(fsys);
}

static void DebugBattleSIO(FIELDSYS_WORK * fsys)
{
	EventSet_Script(fsys, SCRID_CONNECT_COLOSSEUM, NULL );
}

