//=============================================================================
/**
 * @file	dwc_raputility.c
 * @bfief	DWC���b�p�[�B�o�g���I�[�o�[���C�Q�w�ɕ���  06.03.25
 * @author	kazuki yoshihara  -> k.ohno
 * @date	06/03/25
 */
//=============================================================================

#include "common.h"
#include "wifi/dwc_rap.h"
#include "communication/communication.h"

//==============================================================================
/**
 * WiFi�ڑ����[�e�B���e�B���Ăяo��
 * @param   none
 * @retval  none
 */
//==============================================================================
void mydwc_callUtility( int HeapID )
{
	OSIntrMode old;
	void *work;

	CommVRAMDInitialize(); // 
	// �A���[���V�X�e�������������Ă����Ȃ���DWC_StartUtility�ďo�����Panic����������
	OS_InitTick();
	OS_InitAlarm();


	// ���荞�ݏ�������U�֎~��
	old = OS_DisableInterrupts();

	// WiFi�ݒ胁�j���[�Ăяo���i�I���܂ŋA���Ă��Ȃ�)
	work = sys_AllocMemory( HeapID, DWC_UTILITY_WORK_SIZE );
	(void)DWC_StartUtility( work, DWC_LANGUAGE_JAPANESE, DWC_UTILITY_TOP_MENU_FOR_JPN );
	sys_FreeMemoryEz( work );

	// �֎~�������荞�ݏ����𕜋A
	OS_RestoreInterrupts( old );

	//�}�X�^�[���荞�ݏ�����L����
	OS_EnableIrq( ); 


}