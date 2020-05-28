//============================================================================================
/**
 * @brief	system_data.h
 * @brief	システムセーブデータ用ヘッダ
 * @date	2006.06.01
 * @author	tamada
 *
 */
//============================================================================================

#ifndef	__SYSTEM_DATA_H__
#define	__SYSTEM_DATA_H__

#include "savedata/savedata_def.h"
//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	システムセーブデータの不完全型定義
 */
//---------------------------------------------------------------------------
typedef struct SYSTEMDATA SYSTEMDATA;


//============================================================================================
//============================================================================================

//セーブデータシステムが参照する関数
extern int SYSTEMDATA_GetWorkSize(void);
extern void SYSTEMDATA_Init(SYSTEMDATA * sysdt);

extern SYSTEMDATA * SaveData_GetSystemData(SAVEDATA * sv);

//============================================================================================
//============================================================================================
extern void SYSTEMDATA_Update(SYSTEMDATA * sysdt);
extern BOOL SYSTEMDATA_IdentifyMACAddress(const SYSTEMDATA * sysdt);
extern BOOL SYSTEMDATA_IdentifyRTCOffset(const SYSTEMDATA * sysdt);
extern const u8 * SYSTEMDATA_GetMacAddress(const SYSTEMDATA * sysdt);
extern u8 SYSTEMDATA_GetBirthMonth(const SYSTEMDATA * sysdt);
extern u8 SYSTEMDATA_GetBirthDay(const SYSTEMDATA * sysdt);

extern BOOL SYSTEMDATA_GetBeaconMPOpenFlag(const SYSTEMDATA * sysdt);
extern void SYSTEMDATA_SetBeaconMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag);
extern BOOL SYSTEMDATA_GetWifiMPOpenFlag(const SYSTEMDATA * sysdt);
extern void SYSTEMDATA_SetWifiMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag);
extern void SYSTEMDATA_SetDpwInfo( SYSTEMDATA * sysdt, s32 profileId );
extern s32 SYSTEMDATA_GetDpwInfo( const SYSTEMDATA * sysdt );


#ifdef CREATE_INDEX
extern void *Index_Get_Profile_Offset(SYSTEMDATA *sys);
#endif

#endif	__SYSTEM_DATA_H__
