//=============================================================================
/**
 * @file	comm_wifihistory.h
 * @brief	�n���V�f�[�^�̓o�^
 * @author	Akito Mori
 * @date    2006.05.02
 */
//=============================================================================


#ifndef _COMM_WIFIHISTORY_H_
#define _COMM_WIFIHISTORY_H_

#include "savedata/wifihistory.h"
//==============================================================================
// extern�錾
//==============================================================================

extern void Comm_WifiHistoryCheck( WIFI_HISTORY *wifiHistory );
extern void Comm_WifiHistoryDataSet( WIFI_HISTORY *wifiHistory, int Nation, int Area, int langCode );



#endif //_COMM_WIFIHISTORY_H_
