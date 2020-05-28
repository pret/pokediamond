//============================================================================================
/**
 * @file	boxv_button.c
 * @brief	�{�b�N�X�����ʁ@�`�扺�����i��ʉ����{�^���֘A�j
 * @author	taya
 * @date	2005.09.21
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\fontproc.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


//---------------------------------------------
// �A�j�����
//---------------------------------------------
enum {
	ANM_NORMAL,
	ANM_PARTYBUTTON_PUSH,
	ANM_CLOSEBUTTON_PUSH,
};

//------------------------------------------------------------------
/**
 * ����������
 *
 * @param   wk			���[�N�|�C���^
 * @param   vwk			�`�惁�C�����[�N
 * @param   vpara		�`��p�����[�^
 * @param   bgl			BGL���C�u�����w�b�_�|�C���^
 * @param   actsys		�A�N�^�[�V�X�e���w�b�_�|�C���^
 *
 * @retval  BOOL		TRUE�Ő���
 */
//------------------------------------------------------------------
BOOL BoxAppView_ButtonInit( BUTTON_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys )
{
	wk->vwk = vwk;
	wk->actSys = actsys;
	wk->vpara = vpara;
	wk->actsys = actsys;
	wk->act = NULL;

	wk->cellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_m_button_lz_ncer, TRUE, &(wk->cellBank), HEAPID_BOX_VIEW);
	wk->anmBuf = ArcUtil_AnimBankDataGet(ARC_BOX_GRA, NARC_box_m_button_lz_nanr, TRUE, &(wk->anmBank), HEAPID_BOX_VIEW);

	if( wk->cellBuf == NULL || wk->anmBuf == NULL ){
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------
/**
 * �n�a�i�Z�b�g�A�b�v����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_ButtonActSet( BUTTON_VIEW_WORK* wk )
{
	CLACT_HEADER  header;

	NNS_G2dInitImageProxy( &(wk->imgProxy) );
	ArcUtil_CharSysLoad( ARC_BOX_GRA, NARC_box_m_button_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, OBJCHAR_MAIN_BUTTON_POS*0x20, HEAPID_BOX_VIEW, &(wk->imgProxy) );

	BoxAppView_SetActHeader( &header, &(wk->imgProxy), BoxAppView_GetObjPlttProxy( wk->vwk ), wk->cellBank, wk->anmBank, BGPRI_MAIN_BUTTON );
	wk->act = BoxAppView_AddActor( wk->actsys, &header, MAINBUTTON_XPOS+BoxAppView_GetTrayScrollOfs(wk->vwk), MAINBUTTON_YPOS, ACTPRI_MAIN_BUTTON, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_PaletteNoChg( wk->act, OBJPAL_MAINBUTTON );
}

//------------------------------------------------------------------
/**
 * �I������
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_ButtonQuit( BUTTON_VIEW_WORK* wk )
{
	if( wk->cellBuf != NULL )
	{
		sys_FreeMemoryEz( wk->cellBuf );
		wk->cellBuf = NULL;
	}
	if( wk->anmBuf != NULL )
	{
		sys_FreeMemoryEz( wk->anmBuf );
		wk->anmBuf = NULL;
	}
}


//------------------------------------------------------------------
/**
 * �{�^����ԕύX
 *
 * @param   wk			���[�N�|�C���^
 * @param   state		���
 *
 */
//------------------------------------------------------------------
void BoxAppView_ButtonStateChange( BUTTON_VIEW_WORK* wk, BOXAPPVIEW_BUTTON_STATE state )
{
	switch( state ){
	case BUTTON_STATE_INIT:
		CLACT_AnmChg(wk->act, ANM_NORMAL);
		break;
	case BUTTON_STATE_PARTY_PUSH:
		CLACT_AnmChg(wk->act, ANM_PARTYBUTTON_PUSH);
		break;
	case BUTTON_STATE_CLOSE_PUSH:
		CLACT_AnmChg(wk->act, ANM_CLOSEBUTTON_PUSH);
		break;
	}
}

