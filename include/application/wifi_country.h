//============================================================================================
/**
 * @file	wifi_country.h
 * @brief	WI-FI�n����ʂŎg�p���镶���񓙂̃f�[�^���O�����J���邽�߂̎d�g��
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
