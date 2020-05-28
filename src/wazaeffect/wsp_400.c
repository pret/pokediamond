//==============================================================================
/**
 * @file	wsp_400.c
 * @brief	400�ԑ�̋Z�G�t�F�N�g
 * @author	goto
 * @date	2006.03.09
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"				///< �K�{
#include "system/lib_pack.h"	///< �K�{
#include "west_sp.h"			///< �K�{
#include "wsp.h"				///< xxx.c�ɑ΂���xxx.h�͕K�{

#include "wazatool.h"			///< �Z�G�t�F�N�g�x���֐��S
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"	///< �A�[�J�C�u�p
#include "system/arc_util.h"	///< �A�[�J�C�u�p

#include "we_def.h"

///< 425
typedef struct {

	TWE_TOOL_SYS		ts;		///< �Z�G�t�F�N�g�ėp�\����
	TWE_POKE_SYS		poke;	///< �|�P�����ėp�\����
	
	WAZATOOL_CALCMOVE	cm;		///< �ėp���[�N
	
} TWE_425_SYS;

static void We425_TCB(TCB_PTR tcb, void* work)
{
	TWE_425_SYS* wk = (TWE_425_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		break;
	
	default:
		///< �������
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
}

void WestSp_WE_425(WE_SYS_PTR we_sys)
{
	TWE_425_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_425_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We425_TCB, wk);
}
