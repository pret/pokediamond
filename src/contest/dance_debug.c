//==============================================================================
/**
 * @file	dance_debug.c
 * @brief	ダンス部門で使用するデバッグソース
 * @author	matsuda
 * @date	2006.05.05(金)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "msgdata/msg.naix"

#include "dance.h"
#include "dance_tool.h"
#include "con_tool.h"
#include "dance_id.h"
#include "dance_tcb_pri.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg_cmsg_dance.h"
#include "system/fontoam.h"

#include "adv_tool.h"
#include "system/window.h"
#include "savedata/config.h"

#include "system/particle.h"
#include "../particledata/particledata.h"
#include "../particledata/particledata.naix"




#ifdef PM_DEBUG		//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


typedef struct{
	DANCE_PROC_WORK *dpw;
	s32 x;
	s32 y;
	s32 z;
	s32 gen_num;
	s32 emit_no;
	s32 seq;
}TEST_PARTICLE_DANCE;

static void TestParticleDanceMain(TCB_PTR tcb, void *work);

//--------------------------------------------------------------
/**
 * @brief   パーティクル座標合わせチェック用タスク生成
 *
 * @param   dpw		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
void TestParticleDance(DANCE_PROC_WORK *dpw)
{
	TEST_PARTICLE_DANCE *tpd;
	
	tpd = sys_AllocMemory(HEAPID_DANCE, sizeof(TEST_PARTICLE_DANCE));
	MI_CpuClear8(tpd, sizeof(TEST_PARTICLE_DANCE));
	
	tpd->dpw = dpw;
	tpd->z = DANCE_PARTICLE_DEFAULT_Z;
	tpd->gen_num = FX32_ONE;
	TCB_Add(TestParticleDanceMain, tpd, 500);
}

static void TestParticleDanceMain(TCB_PTR tcb, void *work)
{
	TEST_PARTICLE_DANCE *tpd = work;
	
	switch(tpd->seq){
	case 0:
		DT_EmitterCreate(tpd->dpw, tpd->emit_no, 
			tpd->x, tpd->y, tpd->z, tpd->gen_num);
		tpd->seq++;
		break;
	case 1:
		if(Particle_GetEmitterNum(tpd->dpw->ptc) == 0){
			tpd->seq--;
		}
		break;
	}
	
	if(sys.trg & PAD_BUTTON_A){
		tpd->emit_no++;
		if(tpd->emit_no >= CON_DANCE_SPAMAX){
			tpd->emit_no = 0;
		}
	}
	if(sys.trg & PAD_BUTTON_B){
		tpd->emit_no--;
		if(tpd->emit_no < 0){
			tpd->emit_no = CON_DANCE_SPAMAX - 1;
		}
	}
	
	if(sys.cont & PAD_KEY_LEFT){
		tpd->x -= 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.cont & PAD_KEY_RIGHT){
		tpd->x += 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.cont & PAD_KEY_DOWN){
		tpd->y -= 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.cont & PAD_KEY_UP){
		tpd->y += 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.cont & PAD_BUTTON_START){
		tpd->z -= 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.cont & PAD_BUTTON_SELECT){
		tpd->z += 100;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	
	if(sys.trg & PAD_BUTTON_X){
		tpd->gen_num += FX32_ONE / 5;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
	if(sys.trg & PAD_BUTTON_Y){
		tpd->gen_num -= FX32_ONE / 5;
		OS_TPrintf("tpd->x = %d, tpd->y = %d, tpd->z = %d, tpd->gen_num = %d\n", tpd->x, tpd->y, tpd->z, tpd->gen_num);
	}
}



#endif	//PM_DEBUG	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


