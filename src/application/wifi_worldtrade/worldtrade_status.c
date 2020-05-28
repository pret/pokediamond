//============================================================================================
/**
 * @file	worldtrade_status.c
 * @bfief	���E�����|�P�����X�e�[�^�X��ʌĂяo���E���A
 * @author	Akito Mori
 * @date	06.05.10
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/touchpanel.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "savedata/sp_ribbon.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"
#include "itemtool/itemsym.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "libdpw/dpw_tr.h"




//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
//static void InitWork( WORLDTRADE_WORK *wk );
//static void FreeWork( WORLDTRADE_WORK *wk );



// �X�e�[�^�X��ʂŕ\������t���O�̗�i�r�b�g�e�[�u���ɂ���΂����̂Ɂc�j
static const u8 StatusPageTable[]={
	PST_PAGE_INFO,			// �u�|�P�������傤�ق��v
	PST_PAGE_MEMO,			// �u�g���[�i�[�����v
	PST_PAGE_PARAM,			// �u�|�P�����̂���傭�v
	PST_PAGE_CONDITION,		// �u�R���f�B�V�����v
	PST_PAGE_B_SKILL,		// �u���������킴�v
	PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
	PST_PAGE_RIBBON,		// �u���˂񃊃{���v
	PST_PAGE_RET,			// �u���ǂ�v
	PST_PAGE_MAX

};

//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

//==============================================================================
/**
 * $brief   ���E�����������ʏ�����
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
//	InitWork( wk );
	
	
	wk->statusParam.ppd  = WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos);
	wk->statusParam.ppt  = PST_PP_TYPE_POKEPASO;
	wk->statusParam.max  = 1;
	wk->statusParam.pos  = 0;
	wk->statusParam.mode = PST_MODE_NO_WAZACHG;	// �Z����ւ��֎~�ɂ���
	wk->statusParam.waza = 0;
	wk->statusParam.ev_contest = PokeStatus_ContestFlagGet(wk->param->savedata);
	wk->statusParam.zukan_mode = wk->param->zukanmode;
	wk->statusParam.cfg        = wk->param->config;
	wk->statusParam.ribbon     = SaveData_GetSpRibbon(wk->param->savedata);
	PokeStatus_PageSet( &wk->statusParam, StatusPageTable );
	PokeStatus_PlayerSet( &wk->statusParam, wk->param->mystatus );
	
	wk->proc = PROC_Create( &PokeStatusProcData, &wk->statusParam, HEAPID_WORLDTRADE );

	wk->subprocflag = 1;

	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   ���E�����������ʃ��C��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret=SEQ_MAIN;

		if( ProcMain( wk->proc ) ){

			PROC_Delete( wk->proc );

			WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, wk->sub_process_mode );
			
			ret = SEQ_FADEOUT;
		}

	return ret;
}


//==============================================================================
/**
 * $brief   ���E�����������ʏI��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_End(WORLDTRADE_WORK *wk, int seq)
{
//	FreeWork( wk );

	// �{�b�N�X��ʂɖ߂�
	WorldTrade_SubProcessUpdate( wk );

	return SEQ_INIT;
}
