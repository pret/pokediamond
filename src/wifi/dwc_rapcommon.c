//=============================================================================
/**
 * @file	dwc_rapcommon.c
 * @bfief	DWC���b�p�[�B�풓���W���[���ɒu������
 * @author	kazuki yoshihara  -> k.ohno����
 * @date	06/02/23
 */
//=============================================================================

#include "common.h"
#include <dwc.h>
#include "wifi/dwc_rap.h"

//==============================================================================
/**
 * DWC���C�u����������
 * @param   WIFI_LIST  ���[�U�[�f�[�^���Ȃ��ꍇ�쐬
 * @retval  DS�{�̂ɕۑ����郆�[�UID�̃`�F�b�N�E�쐬���ʁB
 */
//==============================================================================
int mydwc_init(int heapID)
{
	int ret;
    u8* pWork;
    u8* pTemp;

    pWork = sys_AllocMemory(heapID, DWC_INIT_WORK_SIZE+32);
    pTemp = (u8 *)( ((u32)pWork + 31) / 32 * 32 );
    // DWC���C�u����������
    ret = DWC_Init( pTemp );
    sys_FreeMemoryEz(pWork);

	return ret;
}


//==============================================================================
/**
 * DWC  UserData�����
 * @param   WIFI_LIST  ���[�U�[�f�[�^���Ȃ��ꍇ�쐬
 * @retval  DS�{�̂ɕۑ����郆�[�UID�̃`�F�b�N�E�쐬���ʁB
 */
//==============================================================================
void mydwc_createUserData( WIFI_LIST *pWifiList )
{
    // ���[�U�f�[�^�쐬������B    
    DWCUserData *userdata = WifiList_GetMyUserInfo(pWifiList);
    if( !DWC_CheckUserData( userdata ) ){
        DWC_CreateUserData( userdata, 'ADAJ' );
        DWC_ClearDirtyFlag( userdata );
        OS_TPrintf("WIFI���[�U�f�[�^���쐬\n");
    }
}

//==============================================================================
/**
 * ������GSID���擾����
 * @param   WIFI_LIST  
 * @retval  �O�Ɓ|�P�͎��s   ���̒l�͐���
 */
//==============================================================================

int mydwc_getMyGSID(WIFI_LIST *pWifiList)
{
    DWCUserData *userdata = WifiList_GetMyUserInfo(pWifiList);
    DWCFriendData friendData;

    DWC_CreateExchangeToken(userdata,&friendData);
    return DWC_GetGsProfileId( userdata,&friendData);
}

//==============================================================================
/**
 * ������GSID���������̂���������
 * @param   WIFI_LIST  
 * @retval  TRUE������
 */
//==============================================================================

BOOL mydwc_checkMyGSID(SAVEDATA *pSV)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(pSV);
    DWCUserData *userdata = WifiList_GetMyUserInfo(pList);

    if( DWC_CheckHasProfile( userdata )
       && DWC_CheckValidConsole( userdata ) ){
       return TRUE;
   }
   return FALSE;
}

