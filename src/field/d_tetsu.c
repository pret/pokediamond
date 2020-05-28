//============================================================================================
/**
 *	デバッグメニュー渡辺
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
#include "system/wipe.h"
#include "application/wifi_earth.h"
#include "savedata/wifihistory.h"

//============================================================================================
//	ＰＲＯＣ定義データ
//============================================================================================
FS_EXTERN_OVERLAY(wifiearth);

const PROC_DATA Earth_Demo_proc_data = {
	Earth_Demo_Init,
	Earth_Demo_Main,
	Earth_Demo_Exit,
	FS_OVERLAY_ID(wifiearth),
};

FS_EXTERN_OVERLAY(opening);
extern PROC_RESULT Intro_Init( PROC * proc, int * seq );
extern PROC_RESULT Intro_Main( PROC * proc, int * seq );
extern PROC_RESULT Intro_Exit( PROC * proc, int * seq );

static const PROC_DATA Intro_proc_data = {
	Intro_Init,
	Intro_Main,
	Intro_Exit,
	FS_OVERLAY_ID(opening),
};

#include "demo/syoujyou.h"
static const PROC_DATA Syoujyou_proc_data = {
	Syoujyou_Init,
	Syoujyou_Main,
	Syoujyou_Exit,
	FS_OVERLAY_ID(syoujyou),
};

extern PROC_RESULT IntroTV_Init( PROC * proc, int * seq );
extern PROC_RESULT IntroTV_Main( PROC * proc, int * seq );
extern PROC_RESULT IntroTV_Exit( PROC * proc, int * seq );

static const PROC_DATA IntroTVProcData = {
	IntroTV_Init,
	IntroTV_Main,
	IntroTV_Exit,
	FS_OVERLAY_ID(opening),
};

//============================================================================================
//	メイン
//============================================================================================
#define	TCB_WK_SIZE		( 4*16 )
#define	DEBUG_WK_SIZE	( 32 )

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
	u32	bmp_work[WK_MAX];
	u32	work[DEBUG_WK_SIZE];
	BOOL	fade_end_flag;
	int	seq;

	SYOUJYOU_INI ini;

}D_WATANABE_PARAM;

typedef void (*pHNfunc)(void *);

//--------------------------------------------------------------------------------------------
extern void	WIFI_RegistratonInitDebug(SAVEDATA* savedata);
//--------------------------------------------------------------------------------------------
void DebugWatanabeMenuInit( void * fsys );
static void DebugProcMain( TCB_PTR _tcb, void * work );
static void	WIFI_RegistratonInitDebug(SAVEDATA* savedata);
//--------------------------------------------------------------------------------------------

void DebugWatanabeMenuInit( void * fsys )
{
	D_WATANABE_PARAM * wk;

	wk = (D_WATANABE_PARAM *)TCB_GetWork
				(PMDS_taskAdd(DebugProcMain,sizeof(D_WATANABE_PARAM),0,HEAPID_BASE_DEBUG));

	wk->fsys = fsys;
	wk->seq = 0;
}

static void DebugProcMain( TCB_PTR _tcb, void * work )
{
	D_WATANABE_PARAM * wk = (D_WATANABE_PARAM *)work;
	FIELDSYS_WORK* fsys = (FIELDSYS_WORK*)wk->fsys;

	switch(wk->seq){
	case 0:
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEOUT,WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK,
						WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_BASE_DEBUG);
		wk->seq++;
		break;
	case 1:
		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			GameSystem_FinishFieldProc(fsys);
			wk->seq++;
		}
		break;
	case 2:
		if (!GameSystem_CheckFieldProcExists(fsys)) {
			{
				WIFI_RegistratonInitDebug(fsys->savedata);

				GameSystem_StartSubProc(fsys, &Earth_Demo_proc_data, fsys->savedata);
				//GameSystem_StartSubProc(fsys, &Intro_proc_data, fsys->savedata);
				#if 0
				if( sys.cont & PAD_BUTTON_L ){
					wk->ini.type = 1;
				} else {
					wk->ini.type = 0;
				}
				wk->ini.savedata = fsys->savedata;

				GameSystem_StartSubProc(fsys, &Syoujyou_proc_data, &wk->ini);
				#endif
				//GameSystem_StartSubProc(fsys, &IntroTVProcData, fsys->savedata);
			}
			wk->seq++;
		}
		break;
	case 3:
		if(GameSystem_CheckSubProcExists(fsys) == FALSE){
			FieldEvent_Cmd_SetMapProc(fsys);
			wk->seq++;
		}
		break;
	case 4:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,WIPE_FADE_BLACK,
							WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_BASE_DEBUG);
			wk->seq++;
		}
		break;
	case 5:
		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			PMDS_taskDel( _tcb );
		}
		break;
	}
}


//------------------------------------------------------------------------
static void	WIFI_RegistratonInitDebug(SAVEDATA* savedata)
{
	WIFI_HISTORY* wh = SaveData_GetWifiHistory(savedata);
	int nationID,areaID;

	for(nationID=0;nationID<256;nationID++){
		for(areaID=0;areaID<64;areaID++){
			WIFIHISTORY_SetStat(wh,nationID,areaID,WIFIHIST_STAT_EXIST);
		}
	}
	WIFIHISTORY_SetWorldFlag(wh,FALSE);
}


