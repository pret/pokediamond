//============================================================================================
/**
 * @file	fd_shop.c
 * @brief	�t�����h���B�V���b�v �o�b�O����
 * @author	Hiroyuki Nakamura
 * @date	2006.07.12
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/wordset.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "application/bag.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "field_clact.h"
#include "syswork.h"

#include "fd_shop_sys.h"
#include "fd_shop.h"


//=================================================================================================
//	�v���g�^�C�v�錾
//=================================================================================================
static u8 ShopSaleWaitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk );
static void ShopSaleRetSeq( GMEVENT_CONTROL * event );


//--------------------------------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�C�x���g�F�V���b�v���p�����o�b�O����
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 * @retval	TRUE	�C�x���g�I��
 * @retval	FALSE	�C�x���g�p��
 */
//--------------------------------------------------------------------------------------------
BOOL GMEVENT_ShopSale( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case SHOP_SEQ_SALE_WAIT:		// �u����v�I���҂�
		wk->seq = ShopSaleWaitSeq( fsys, wk );
		break;

	case SHOP_SEQ_SALE_RET:			// �u����v�I�� -> �t�F�[�h�C��
		ShopSaleRetSeq( event );
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʏI���҂�
 *
 * @param	fsys	�t�B�[���h���[�N
 * @param	wk		�V���b�v���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 ShopSaleWaitSeq( FIELDSYS_WORK * fsys, SHOP_WORK * wk )
{
	// �T�u�v���Z�X�I���҂�
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return SHOP_SEQ_SALE_WAIT;
	}

	wk->fnote_sale_cnt = BagSysSaleCntGet( wk->bag_wk );

	sys_FreeMemoryEz( wk->bag_wk );

	FieldEvent_Cmd_SetMapProc( fsys );

	return SHOP_SEQ_SALE_RET;
}

//--------------------------------------------------------------------------------------------
/**
 * �V���b�v���A�҂�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static void ShopSaleRetSeq( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	SHOP_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	// �t�B�[���h�}�b�v�v���Z�X�J�n�҂�
	if( FieldEvent_Cmd_WaitMapProcStart(fsys) ){
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
		FieldEvent_Change( event, GMEVENT_Shop, wk );
		wk->seq = SHOP_SEQ_SALE_MENU_RET;
	}
}
