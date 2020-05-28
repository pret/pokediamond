//============================================================================================
/**
 * @file	wifi_country.h
 * @brief	WI-FI地球画面で使用する文字列等のデータを外部公開するための仕組み
 * @author	taya
 * @date	2006.04.22
 */
//============================================================================================
#ifndef __WIFI_COUNTRY_H__
#define __WIFI_COUNTRY_H__


extern u32 WIFI_COUNTRY_GetDataLen( void );
extern u32 WIFI_COUNTRY_CountryCodeToDataIndex( u32 countryCode );
extern u32 WIFI_COUNTRY_CountryCodeToPlaceMsgDataID( u32 countryCode );
extern u32 WIFI_COUNTRY_DataIndexToPlaceMsgDataID( u32 dataIndex );
extern u32 WIFI_COUNTRY_DataIndexToCountryCode( u32 dataIndex );
extern u32 WIFI_COUNTRY_DataIndexToPlaceDataID( u32 dataIndex );


#endif
