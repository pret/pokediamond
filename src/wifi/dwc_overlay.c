//=============================================================================
/**
 * @file	dwc_rapstart.c
 * @bfief	DWC�̃I�[�o�[���C���Ǘ�  ������풓�ɔz�u
 * @author	k.ohno
 * @date	06/02/23
 */
//=============================================================================

#include "common.h"
#include "system/pm_overlay.h"
#include "wifi/dwc_rap.h"
#include "wifi/dwc_test.h"
#include "communication/communication.h"

FS_EXTERN_OVERLAY(ol_wifi);
FS_EXTERN_OVERLAY(ol_wifiutil);
FS_EXTERN_OVERLAY( title_debug );
FS_EXTERN_OVERLAY(dpw_common);


//==============================================================================
/**
 * $brief   NitroDwc���ł܂��Ă���I�[�o�[���C�̈�����[�h����
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DwcOverlayStart(void)
{
	Overlay_Load( FS_OVERLAY_ID( ol_wifi ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
}

//==============================================================================
/**
 * $brief   NitroDwc���ł܂��Ă���I�[�o�[���C�̈�����
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DwcOverlayEnd(void)
{
    Overlay_UnloadID( FS_OVERLAY_ID( ol_wifi ) );
}

//==============================================================================
/**
 * $brief   Wifi�ݒ�A�v�����Ăяo�����߂̗̈�����[�h
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DwcUtilOverlayStart(void)
{
	Overlay_Load( FS_OVERLAY_ID( ol_wifiutil ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
}

//==============================================================================
/**
 * $brief   Wifi�ݒ�A�v�����Ăяo�����߂̗̈�����
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DwcUtilOverlayEnd(void)
{
    Overlay_UnloadID( FS_OVERLAY_ID( ol_wifiutil ) );
}

//==============================================================================
/**
 * $brief   Wifi�A�v���Ăяo��
 *
 * @param   savedata		
 * @param   HeapID		
 *
 * @retval  none		
 */
//==============================================================================
void DwcUtilOverlayCall(SAVEDATA *savedata,int HeapID)
{
#if 0
    Overlay_UnloadID( FS_OVERLAY_ID( title_debug ) );
#endif
    DwcOverlayStart();
    DwcUtilOverlayStart();
    mydwc_callUtility(HeapID);
    DwcUtilOverlayEnd();
    DwcOverlayEnd();
	OS_ResetSystem(0); 
}

//==============================================================================
/**
 * $brief   
 *
 * @param   savedata		
 * @param   HeapID		
 *
 * @retval  none		
 */
//==============================================================================
void DwcTestOverlayStart(SAVEDATA *savedata ,int HeapID)
{
    Overlay_UnloadID( FS_OVERLAY_ID( title_debug ) );
	CommVRAMDInitialize();
    DwcOverlayStart();
    DwcUtilOverlayStart();
	
	dwctest_init( HEAPID_WIFIMENU );

}


//==============================================================================
/**
 * $brief   
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DwcTestOverlayEnd(void)
{
    DwcUtilOverlayEnd();
    DwcOverlayEnd();
}

//==============================================================================
/**
 * $brief   ���E�����E�o�g���^���[�I�[�o�[���C���ʗ̈惍�[�h
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DpwCommonOverlayStart(void)
{
	// �T�[�o�[�A�N�Z�X���C�u�������ʃI�[�o�[���C�̈�ǂݍ���
	Overlay_Load(FS_OVERLAY_ID(dpw_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);
}

//==============================================================================
/**
 * $brief    ���E�����E�o�g���^���[�I�[�o�[���C���ʗ̈���
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DpwCommonOverlayEnd(void)
{
	// �T�[�o�[�A�N�Z�X���ʃI�[�o�[���C���
	Overlay_UnloadID(FS_OVERLAY_ID(dpw_common));
}



//==============================================================================
//
//	
//
//==============================================================================
#include "system/procsys.h"
#include "system/main.h"

//------------------------------------------------------------------
/**
 * @brief	�X�^�[�g���j���[����Ăяo�����Wi-Fi�ݒ���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static PROC_RESULT StartMenuWifiProc_Init(PROC * proc, int * seq)
{
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFIMENU, 0x41000);
  DwcUtilOverlayCall(((MAINWORK *)PROC_GetParentWork(proc))->savedata, HEAPID_WIFIMENU);
  sys_DeleteHeap(HEAPID_WIFIMENU);
  OS_ResetSystem(0); 
  return PROC_RES_FINISH;
}
const PROC_DATA StartMenuWifiProcData = {
  StartMenuWifiProc_Init,
  NULL,
  NULL,
  NO_OVERLAY_ID,
};

