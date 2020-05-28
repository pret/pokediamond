//============================================================================================
/**
 * @file	field_amaikaori.c
 * @brief	フィールド技：甘い香り
 * @author	Nozomu Saito
 * @date	2006.06.01
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "player.h"
#include "field_cutin.h"

#include "amaikaori_eff.h"

#include "field_skill_prm.h"

#include "field_amaikaori.h"

typedef struct AMAIKAORI_WORK_tag
{
	TCB_PTR TcbCutIn;
	EVENT_AMAIKAORI_EFF_WORK *EffWork;
}AMAIKAORI_WORK;

BOOL GMEVENT_Amakikaori( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	FLD_SKILL_PRM *work = FieldEvent_GetSpecialWork( event );
	int *seq = FieldEvent_GetSeqWork(event);
	AMAIKAORI_WORK *skill_work = work->Work;

	switch(*seq){
	case 0:
		//スキル固有メモリ確保
		work->Work = sys_AllocMemoryLo( HEAPID_WORLD, sizeof(AMAIKAORI_WORK) );
		(*seq)++;
		break;
	case 1:
		//甘い香りエフェクトイベント内で解放してくれるので、確保だけ
		{
			int size = FLDMAP_Amaikaori_WorkSize();
			skill_work->EffWork = sys_AllocMemoryLo( HEAPID_WORLD, size );
			memset( skill_work->EffWork, 0, size );
		}
		(*seq)++;
		break;
	case 2:		//カットイン
		{
			int sex = Player_SexGet( fsys->player );
			skill_work->TcbCutIn = FieldCutIn_Init( fsys, CUTIN_TYPE_HIDEN, work->PokeParam, sex );
		}
		(*seq)++;
		break;
	case 3:		//カットイン待ち
		if( FieldCutIn_EndCheck(skill_work->TcbCutIn) ){
			FieldCutIn_End( skill_work->TcbCutIn );	//カットイン終了
			(*seq)++;
		}
		break;
	case 4:		//エフェクトコール
		FieldEvent_Call(event, FLDMAP_AmaikaoriEvent, skill_work->EffWork);
		(*seq)++;
		break;	
	case 5:		//ワーク解放
		sys_FreeMemoryEz(work->Work);
		sys_FreeMemoryEz(work);
		return TRUE;
	}

	return FALSE;
}

