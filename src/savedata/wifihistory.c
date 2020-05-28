//============================================================================================
/**
 * @file	wifihistory_local.h
 * @brief
 * @date	2006.03.25
 */
//============================================================================================


#include "savedata/savedata.h"
#include "savedata/wifihistory.h"
#include "wifihistory_local.h"

#include "gflib/assert.h"

//============================================================================================
//============================================================================================


//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi�ʐM�������[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int WIFIHISTORY_GetWorkSize(void)
{
	return sizeof(WIFI_HISTORY);
}

//----------------------------------------------------------
/**
 * @brief	WiFi�ʐM�������[�N�̏�����
 * @param	hist
 * @return	WIFI_HISTORY	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void WIFIHISTORY_Init(WIFI_HISTORY * hist)
{
	MI_CpuClear32(hist, sizeof(WIFI_HISTORY));
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi�ʐM�����Z�[�u�f�[�^�̎擾
 * @param	sv		�Z�[�u�f�[�^�ւ̃|�C���^
 * @return	WIFI_HISTORY�f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
WIFI_HISTORY * SaveData_GetWifiHistory(SAVEDATA * sv)
{
	return (WIFI_HISTORY*)SaveData_Get(sv, GMDATA_ID_WIFIHISTORY);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�����̍��A�n����Z�b�g
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @param	nation		���w��R�[�h
 * @param	area		�n��w��R�[�h
 */
//----------------------------------------------------------
void WIFIHISTORY_SetMyNationArea(WIFI_HISTORY * wh, int nation, int area)
{
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);
	wh->my_nation = nation;
	wh->my_area = area;
	WIFIHISTORY_SetStat(wh, nation, area, WIFIHIST_STAT_MINE);
}

//----------------------------------------------------------
/**
 * @brief	�����̍��R�[�h���擾
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @return	int			���w��R�[�h
 */
//----------------------------------------------------------
int WIFIHISTORY_GetMyNation(const WIFI_HISTORY * wh)
{
	return wh->my_nation;
}

//----------------------------------------------------------
/**
 * @brief	�����̒n��R�[�h���擾
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @return	int			�n��w��R�[�h
 */
//----------------------------------------------------------
int WIFIHISTORY_GetMyArea(const WIFI_HISTORY * wh)
{
	return wh->my_area;
}

//----------------------------------------------------------
/**
 * @brief	��ԃR�[�h�̎擾
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @param	nation		���w��R�[�h
 * @param	area		�n��w��R�[�h
 * @return	WIFIHIST_STAT	��Ԏw��ID
 */
//----------------------------------------------------------
WIFIHIST_STAT WIFIHISTORY_GetStat(const WIFI_HISTORY * wh, int nation, int area)
{
	WIFIHIST_STAT stat;
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);

	if (nation == 0) {
		return WIFIHIST_STAT_NODATA;
	}
	stat = (wh->data[(nation - 1) * NATION_DATA_SIZE + area / 4] >> ((area % 4) * 2)) & 3;

	return stat;
}

//----------------------------------------------------------
/**
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @param	nation		���w��R�[�h
 * @param	area		�n��w��R�[�h
 * @param	stat		��Ԏw��ID
 */
//----------------------------------------------------------
void WIFIHISTORY_SetStat(WIFI_HISTORY * wh, int nation, int area, WIFIHIST_STAT stat)
{
	u8 * p;
	u8 mask = 3;
	u8 data;

	GF_ASSERT(stat < WIFIHIST_STAT_MAX);
	GF_ASSERT(nation < WIFI_NATION_MAX);
	GF_ASSERT(area < WIFI_AREA_MAX);

	if (nation == 0) {
		return;
	}
	p = &wh->data[(nation - 1) * NATION_DATA_SIZE + area / 4];

	*p &= ((mask << ((area % 4) * 2))^0xff);
	*p |= stat << ((area % 4) * 2);
	
	if (nation != WIFI_NATION_JAPAN) {
		WIFIHISTORY_SetWorldFlag(wh, TRUE);
	}
}


//----------------------------------------------------------
/**
 * @brief	���E���[�h���ǂ����̃t���O�擾
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @return	BOOL		TRUE�̂Ƃ��A���E���[�h
 */
//----------------------------------------------------------
BOOL WIFIHISTORY_GetWorldFlag(const WIFI_HISTORY * wh)
{
	return wh->world_flag;
}


//----------------------------------------------------------
/**
 * @brief	���E���[�h�̃t���O�Z�b�g
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 * @param	flag		�ݒ肷��l�iTRUE/FALSE�j
 */
//----------------------------------------------------------
void WIFIHISTORY_SetWorldFlag(WIFI_HISTORY * wh, BOOL flag)
{
	wh->world_flag = flag;
}


//----------------------------------------------------------
/**
 * @brief	���t�X�V�œ��e�X�V
 * @param	wh			WIFI�����f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
void WIFIHISTORY_Update(WIFI_HISTORY * wh)
{
	int i, j;
	u8 data;
	for (i = 0; i < (WIFI_NATION_MAX - 1) * NATION_DATA_SIZE; i++) {
		data = wh->data[i];
		for (j = 0; j < 8; j+=2) {
			if (((data >> j) & 3) == WIFIHIST_STAT_NEW) {
				data &= ((3 << j)^0xff);
				data |= (WIFIHIST_STAT_EXIST << j);
			}
		}
		wh->data[i] = data;
	}
}


