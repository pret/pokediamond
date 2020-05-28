//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		effect_warppoint.c
 *@brief	ワープポイント
 *@author	k.ohno
 *@data		2006.06.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"


#include "system/bmp_menu.h"
#include "worldmap.h"
#include "fieldobj.h"
#include "fieldobj_code.h" //AC_WALK...等 アニメーションコードがまとめてあります。
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "system/pm_str.h"
#include "player.h"
#include "system/snd_tool.h"
#include "field_effect.h"
#include "syswork.h"
#include "system/clact_tool.h"
#include "field_clact.h"
#include "fld_comact.h"
#include "eventdata.h"
#include "system/wipe.h"

#include "effect_warppoint.h"

#define _TCB_PRIORITY_NORMAL (100)


typedef struct{
    FIELDSYS_WORK* pFSys;
    BOOL* pBEnd;
    int seq;
    int timer;
    int dir;
} WARP_EVENT_WORK;


#define _UP_TIME (20)
#define _UP_HEIGHT  (FX32_ONE * 2.2)
#define _UP_ACCEL (FX32_ONE / 2)

//--------------------------------------------------------------
/**
 * 次の回転方向をセットする
 * @param	dir
 * @retval	dir
 */
//--------------------------------------------------------------

static void _nextDirSet(WARP_EVENT_WORK* wk)
{
    switch(wk->dir){
      case DIR_UP:
        wk->dir = DIR_LEFT;
        break;
      case DIR_LEFT:
        wk->dir = DIR_DOWN;
        break;
      case DIR_DOWN:
        wk->dir = DIR_RIGHT;
        break;
      case DIR_RIGHT:
        wk->dir = DIR_UP;
        break;
    }
    Player_DirSet(wk->pFSys->player, wk->dir);
}


static void _upPlayer(TCB_PTR tcb, void* work)
{
    WARP_EVENT_WORK* wk = work;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( wk->pFSys->player );
    VecFx32 vec;

    enum{
        _START,
        _UPING,
    };

    switch(wk->seq){
      case _START:
/*        if((wk->timer % 4)==3){
            _nextDirSet(wk);
        }
        wk->timer++;
        if(wk->timer == 8){
            wk->seq = _UPING;
            wk->timer = 0;
            Snd_SePlay(SE_AZITO_WARP);
        }
        break;  */
        wk->seq = _UPING;
        Snd_SePlay(SE_AZITO_WARP);
      case _UPING:
        if(wk->timer % 2){
            _nextDirSet(wk);
        }
        FieldOBJ_VecDrawOffsOutSideGet(fldobj, &vec);
        vec.y = (_UP_HEIGHT + (_UP_ACCEL * wk->timer)) * wk->timer;
        FieldOBJ_VecDrawOffsOutSideSet(fldobj, &vec);
        wk->timer++;
        if(wk->timer == _UP_TIME){
            WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                           WIPE_TYPE_FADEOUT,WIPE_TYPE_FADEOUT,
                           WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                           1,HEAPID_FIELD);
        }
        else if((wk->timer > _UP_TIME) && WIPE_SYS_EndCheck()){         //フィールドマッププロセス復帰
            *wk->pBEnd = TRUE;
            sys_FreeMemoryEz(wk);
            TCB_Delete(tcb);
        }
        else{
            break;
        }
    }
}

static void _downPlayer(TCB_PTR tcb, void* work)
{
    WARP_EVENT_WORK* wk = work;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( wk->pFSys->player );
    VecFx32 vec;
    int tim;
	
    enum{
        _FADE,
        _DOWNING,
        _END,
    };
	
    switch(wk->seq){
      case _FADE:
	    {	//060731 kaga
			FieldOBJ_MovePauseClear( fldobj ); 
        	FieldOBJ_VecDrawOffsOutSideGet(fldobj, &vec);
        	 tim = (_UP_TIME - wk->timer);
        	vec.y = (_UP_HEIGHT + (_UP_ACCEL * tim)) * tim;
        	FieldOBJ_VecDrawOffsOutSideSet(fldobj, &vec);
        	FieldOBJ_Draw( fldobj );
		}
		
		Snd_SePlay(SE_AZITO_WARP);
        wk->seq = _DOWNING;
      case _DOWNING:
        if(wk->timer % 2){
            _nextDirSet(wk);
        }
		
        FieldOBJ_VecDrawOffsOutSideGet(fldobj, &vec);
        tim = (_UP_TIME - wk->timer);
        vec.y = (_UP_HEIGHT + (_UP_ACCEL * tim)) * tim;
        FieldOBJ_VecDrawOffsOutSideSet(fldobj, &vec);
        wk->timer++;
        if(wk->timer == 2){
            WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                           WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
                           WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                           1,HEAPID_FIELD);
        }
	
        if(wk->timer > _UP_TIME){
            wk->seq = _END;
        }
        break;
      case _END:
        if(WIPE_SYS_EndCheck()){         //フィールドマッププロセス復帰
            Player_DirSet(wk->pFSys->player, DIR_DOWN);
            *wk->pBEnd = TRUE;
            sys_FreeMemoryEz(wk);
            TCB_Delete(tcb);
        }
        break;
    }
}


#if 0 //060731 kaag
static void _downPlayer(TCB_PTR tcb, void* work)
{
    WARP_EVENT_WORK* wk = work;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( wk->pFSys->player );
    VecFx32 vec;
    int tim;
	
    enum{
        _FADE,
        _DOWNING,
        _END,
    };
	
    switch(wk->seq){
      case _FADE:
        Snd_SePlay(SE_AZITO_WARP);
        wk->seq = _DOWNING;
      case _DOWNING:
        if(wk->timer % 2){
            _nextDirSet(wk);
        }
		
        FieldOBJ_VecDrawOffsOutSideGet(fldobj, &vec);
        tim = (_UP_TIME - wk->timer);
        vec.y = (_UP_HEIGHT + (_UP_ACCEL * tim)) * tim;
        FieldOBJ_VecDrawOffsOutSideSet(fldobj, &vec);
        wk->timer++;
        if(wk->timer == 2){
            WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                           WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
                           WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                           1,HEAPID_FIELD);
        }
	
        if(wk->timer > _UP_TIME){
            wk->seq = _END;
        }
        break;
      case _END:
        if(WIPE_SYS_EndCheck()){         //フィールドマッププロセス復帰
            Player_DirSet(wk->pFSys->player, DIR_DOWN);
            *wk->pBEnd = TRUE;
            sys_FreeMemoryEz(wk);
            TCB_Delete(tcb);
        }
        break;
    }
}
#endif

//----------------------------------------------------------------------------
/**
 *@brief	地下マップフェードエフェクト
 *@param	fsys	フィールドシステムワーク
 *@param	no		エフェクトナンバー
 *@param	end		終了チェックフラグ
 *@return	none
 */
//-----------------------------------------------------------------------------
void StartJumpPointEffect(FIELDSYS_WORK* fsys, BOOL bUp, BOOL* end)
{
    WARP_EVENT_WORK* wk = sys_AllocMemoryLo( HEAPID_FIELD, sizeof(WARP_EVENT_WORK) );

    /* オブジェクト作成 */
    MI_CpuClear8(wk,sizeof(WARP_EVENT_WORK));
    wk->pFSys = fsys;
    wk->pBEnd = end;
    wk->dir = Player_DirGet(fsys->player);
    if(bUp){
        TCB_Add(_upPlayer, wk, _TCB_PRIORITY_NORMAL);
    }
    else{
        TCB_Add(_downPlayer, wk, _TCB_PRIORITY_NORMAL);
    }
}


