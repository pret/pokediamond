//============================================================================================
/**
 * @file	comm_wifihistory.c
 * @bfief	�n���V�o�^����
 * @author	Akito Mori
 * @date	06.05.02
 */
//============================================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_wifihistory.h"

//==============================================================================
/**
 * $brief   �n���V����o�^
 *
 * @param   wifiHistory		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_WifiHistoryCheck( WIFI_HISTORY *wifiHistory )
{
	int i;
	int Nation,Area,region;
	MYSTATUS *status;
	int num = CommGetConnectNum();

	// �f�o�b�O�o�g���̎�����MYSTATUS�������Ă��Ȃ��̂œo�^�����͂��ׂĂƂ΂��悤�ɂ���
	if(CommInfoGetMyStatus(0)==NULL){
		return;
	}

	// �ڑ����Ă���l�����܂킷
	for(i=0;i<num;i++){
		if(CommGetCurrentID()!=i){
			Nation = CommInfoGetMyNation(i);
			Area   = CommInfoGetMyArea(i);
			status = CommInfoGetMyStatus( i );
			region = MyStatus_GetRegionCode( status );

			// ���E�n��R�[�h��o�^�i���������{�J�[�g���b�W��p�`�F�b�N����j
			Comm_WifiHistoryDataSet( wifiHistory, Nation, Area, region );
		}
	}
}

//==============================================================================
/**
 * @brief   ����̃J�[�g���b�W���[�W�����E���E�n��R�[�h����n���V����o�^����
 *
 * @param   wifiHistory		
 * @param   Nation		
 * @param   Area		
 * @param   langCode		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, int Nation, int Area, int langCode )
{
	
#if (PM_LANG == LANG_JAPAN)
	// ����̃J�[�g���b�W�����{�Ȃ̂�
	if(langCode==LANG_JAPAN){
		// �Ⴄ���̒n���V�R�[�h�����Ă�����o�^���Ȃ�
		if(Nation!=WIFI_NATION_JAPAN){
			return;
		}
	}
#endif
	
	// ���E�n���o�^
//	OS_Printf("no=%d\n", WIFIHISTORY_GetStat(wifiHistory, Nation, Area ));
	if(WIFIHISTORY_GetStat( wifiHistory, Nation, Area )==WIFIHIST_STAT_NODATA){
		WIFIHISTORY_SetStat( wifiHistory, Nation, Area, WIFIHIST_STAT_NEW );
	}
	

}