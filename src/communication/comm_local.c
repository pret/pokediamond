//=============================================================================
/**
 * @file	comm_local.c
 * @brief	�ʐM�̒჌�x���Ȕėp�֐����W�߂�����
 * @author	Katsumi Ohno
 * @date    2005.09.12
 */
//=============================================================================


#include "common.h"
#include "wh.h"
#include "communication/communication.h"
#include "comm_local.h"
#include "comm_ring_buff.h"

//==============================================================================
/**
 * �T�[�r�X�ԍ��ɑΉ������q�@�ڑ�MAX�l�����擾
 * �T�[�r�X�ԍ��� include/communication/comm_def.h�ɂ���܂�
 * @param   serviceNo �T�[�r�X�ԍ�
 * @retval  �q�@�䐔
 */
//==============================================================================

u16 CommLocalGetServiceMaxEntry(u16 serviceNo)
{
    u8 maxBuff[]={
        COMM_MODE_TRADE_NUM_MAX,
        COMM_MODE_BATTLE_SINGLE_NUM_MAX,
        COMM_MODE_BATTLE_DOUBLE_NUM_MAX,
        COMM_MODE_BATTLE_MIX_1ON1_NUM_MAX,
        COMM_MODE_BATTLE_MULTI_NUM_MAX,
        COMM_MODE_BATTLE_MIX_2ON2_NUM_MAX,
        COMM_MODE_NUT_CRASH_NUM_MAX,
        COMM_MODE_RECORD_NUM_MAX,
        COMM_MODE_CONTEST_NUM_MAX,
        COMM_MODE_UNION_NUM_MAX,
        COMM_MODE_UNDERGROUND_NUM_MAX,
        COMM_MODE_POLLOCK4_NUM_MAX,
        COMM_MODE_POLLOCK16_NUM_MAX,
        COMM_MODE_PICTURE_NUM_MAX,
        COMM_MODE_POKETCH_NUM_MAX,
        COMM_MODE_MYSTERY_NUM_MAX,
        COMM_MODE_TOWER_MULTI_NUM_MAX,
        COMM_MODE_PARTY_NUM_MAX,
        COMM_MODE_UNION_APP_NUM_MAX,
        COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MAX,
        COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MAX,
        COMM_MODE_TRADE_WIFI_NUM_MAX,
        COMM_MODE_VCHAT_WIFI_NUM_MAX,
        COMM_MODE_LOGIN_WIFI_NUM_MAX,
        COMM_MODE_DPW_WIFI_NUM_MAX,
        COMM_MODE_FUSIGI_WIFI_NUM_MAX,
    };
    GF_ASSERT_RETURN(serviceNo < sizeof(maxBuff), COMM_MODE_TRADE_NUM_MAX);
    return maxBuff[serviceNo];
}


//==============================================================================
/**
 * �T�[�r�X�ԍ��ɑΉ������q�@�ڑ�MAX�l�����擾
 * �T�[�r�X�ԍ��� include/communication/comm_def.h�ɂ���܂�
 * @param   serviceNo �T�[�r�X�ԍ�
 * @retval  �q�@�䐔
 */
//==============================================================================

u16 CommLocalGetServiceMinEntry(u16 serviceNo)
{
    u8 minBuff[]={
        COMM_MODE_TRADE_NUM_MIN,
        COMM_MODE_BATTLE_SINGLE_NUM_MIN,
        COMM_MODE_BATTLE_DOUBLE_NUM_MIN,
        COMM_MODE_BATTLE_MIX_1ON1_NUM_MIN,
        COMM_MODE_BATTLE_MULTI_NUM_MIN,
        COMM_MODE_BATTLE_MIX_2ON2_NUM_MIN,
        COMM_MODE_NUT_CRASH_NUM_MIN,
        COMM_MODE_RECORD_NUM_MIN,
        COMM_MODE_CONTEST_NUM_MIN,
        COMM_MODE_UNION_NUM_MIN,
        COMM_MODE_UNDERGROUND_NUM_MIN,
        COMM_MODE_POLLOCK4_NUM_MIN,
        COMM_MODE_POLLOCK16_NUM_MIN,
        COMM_MODE_PICTURE_NUM_MIN,
        COMM_MODE_POKETCH_NUM_MIN,
        COMM_MODE_MYSTERY_NUM_MIN,
        COMM_MODE_TOWER_MULTI_NUM_MIN,
        COMM_MODE_PARTY_NUM_MIN,
        COMM_MODE_UNION_APP_NUM_MIN,
        COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MIN,
        COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MIN,
        COMM_MODE_TRADE_WIFI_NUM_MIN,
        COMM_MODE_VCHAT_WIFI_NUM_MIN,
        COMM_MODE_LOGIN_WIFI_NUM_MIN,
        COMM_MODE_DPW_WIFI_NUM_MIN,
        COMM_MODE_FUSIGI_WIFI_NUM_MIN,
    };
    GF_ASSERT_RETURN(serviceNo < sizeof(minBuff), COMM_MODE_TRADE_NUM_MIN);
    return minBuff[serviceNo];
}

//==============================================================================
/**
 * ���j�I���O���[�v���ʊ֐�
 * @param   serviceNo �T�[�r�X�ԍ�
 * @retval  yes=union
 */
//==============================================================================

BOOL CommLocalIsUnionGroup(int serviceNo)
{
    switch(serviceNo){
      case COMM_MODE_UNION_APP:
      case COMM_MODE_UNION:
      case COMM_MODE_PICTURE:
      case COMM_MODE_RECORD:
        return TRUE;
    }
    return FALSE;
}

