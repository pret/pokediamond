//============================================================================================
/**
 * @file	wifihistory.h
 * @brief
 * @date	2006.03.25
 */
//============================================================================================

#ifndef	__WIFIHISTORY_H__
#define	__WIFIHISTORY_H__

#include "savedata/savedata_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi�ʐM�����f�[�^�̕s���S�^�錾
 */
//----------------------------------------------------------
typedef struct _WIFI_HISTORY WIFI_HISTORY;

///WiFi�ʐM�������c�����̐�
#define	WIFI_NATION_MAX		(256)

///WiFi�ʐM�������c�����̂��ꂼ��̒n��R�[�h�̍ő吔
#define	WIFI_AREA_MAX		(64)


///���{�̒n���V��`(�{����country103�Ȃ񂾂��Q�Ƃł��Ȃ��̂Łj
#define WIFI_NATION_JAPAN	( 103 ) 


//----------------------------------------------------------
/**
 * @brief	WiFi�ʐM�����f�[�^�̏�Ԓ�`
 */
//----------------------------------------------------------
typedef enum {
	WIFIHIST_STAT_NODATA = 0,	///<�܂��ʐM�������Ƃ��Ȃ�
	WIFIHIST_STAT_NEW = 1,		///<�{�����߂ĒʐM����
	WIFIHIST_STAT_EXIST = 2,	///<�ʐM�������Ƃ�����
	WIFIHIST_STAT_MINE = 3,		///<�����̏ꏊ

	WIFIHIST_STAT_MAX,
}WIFIHIST_STAT;

//----------------------------------------------------------
//----------------------------------------------------------
//���[�N�T�C�Y�擾�i�Z�[�u�V�X�e������Ă΂��j
extern int WIFIHISTORY_GetWorkSize(void);
//�������i�Z�[�u�V�X�e������Ă΂��j
extern void WIFIHISTORY_Init(WIFI_HISTORY * hist);
//�Z�[�u�f�[�^�擾�i�g���ӏ��ŌĂԁj
extern WIFI_HISTORY * SaveData_GetWifiHistory(SAVEDATA * sv);

//������m�F���Ă��܂���B
extern void WIFIHISTORY_SetMyNationArea(WIFI_HISTORY * wh, int nation, int area);
extern int WIFIHISTORY_GetMyNation(const WIFI_HISTORY * wh);
extern int WIFIHISTORY_GetMyArea(const WIFI_HISTORY * wh);
extern void WIFIHISTORY_SetStat(WIFI_HISTORY * wh, int nation, int area, WIFIHIST_STAT stat);
extern WIFIHIST_STAT WIFIHISTORY_GetStat(const WIFI_HISTORY * wh, int nation, int area);

extern BOOL WIFIHISTORY_GetWorldFlag(const WIFI_HISTORY * wh);
extern void WIFIHISTORY_SetWorldFlag(WIFI_HISTORY * wh, BOOL flag);

//���t�ɂ��X�V����
extern void WIFIHISTORY_Update(WIFI_HISTORY * wh);

#endif	/* __WIFIHISTORY_H__ */

