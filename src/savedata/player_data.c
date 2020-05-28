//============================================================================================
/**
 * @file	player_data.c
 * @date	2006.06.01
 * @author	tamada
 * @brief	�v���C���[�֘A�Z�[�u�f�[�^
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/playerdata_local.h"

#include "gflib/assert.h"

#include "gflib/msg_print.h"
#include "system/buflen.h"

#include "savedata/mystatus.h"
#include "mystatus_local.h"
#include "config_local.h"
#include "savedata/config.h"
#include "mystatus_local.h"
#include "savedata/mystatus.h"
#include "coin_local.h"
#include "savedata/coin.h"
#include "playtime_local.h"
#include "savedata/playtime.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�v���C���[�Z�[�u�f�[�^�̒�`
 */
//------------------------------------------------------------------
struct PLAYER_DATA {
	CONFIG config;
	MYSTATUS mystatus;
	COIN mycoin;
	PLAYTIME playtime;
};

//============================================================================================
//
//		��ɃZ�[�u�V�X�e������Ă΂��֐�
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^�T�C�Y�̎擾
 * @return	int		�v���C���[�Z�[�u�f�[�^�̃T�C�Y
 */
//------------------------------------------------------------------
int PLAYERDATA_GetWorkSize(void)
{
	return sizeof(PLAYER_DATA);
}

//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^������
 * @param	pd		�v���C���[�Z�[�u�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void PLAYERDATA_Init(PLAYER_DATA * pd)
{
	MI_CpuClearFast(pd, sizeof(PLAYER_DATA));
	/* �ȉ��Ɍʕ����̏��������������� */
	CONFIG_Init(&pd->config);
	MyStatus_Init(&pd->mystatus);
	COIN_Init(&pd->mycoin);
	PLAYTIME_Init(&pd->playtime);
}

//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	������ԃf�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	MYSTATUS	������ԕێ����[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
MYSTATUS * SaveData_GetMyStatus(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->mystatus;
}

//---------------------------------------------------------------------------
/**
 * @brief	�ݒ���f�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	CONFIG		�ݒ���ێ����[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
CONFIG * SaveData_GetConfig(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->config;
}

//---------------------------------------------------------------------------
/**
 * @brief	�R�C���f�[�^�ւ̃|�C���^���擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	coin	�R�C���f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
COIN * SaveData_GetMyCoin(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->mycoin;
}

//---------------------------------------------------------------------------
/**
 * @brief	�v���C���ԃf�[�^�ւ̃|�C���^���擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	playtime	�v���C���ԃf�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
PLAYTIME * SaveData_GetPlayTime(SAVEDATA * sv)
{
	PLAYER_DATA * pd;
	pd = SaveData_Get(sv, GMDATA_ID_PLAYER_DATA);
	return &pd->playtime;
}

