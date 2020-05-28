//============================================================================================
/**
 * @file	worldtrade_data.c
 * @brief	���E�����Z�[�u�f�[�^
 * @author	mori GAME FREAK inc.
 * @date	2006.04.30
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"

#include "savedata/worldtrade_data.h"

#define POKEMON_DATA_SIZE		(236)

//============================================================================================
//============================================================================================

struct WORLDTRADE_DATA{
	u8 PokemonData[POKEMON_DATA_SIZE];	// �a�����|�P�����̃f�[�^
	u16 		flag;					// �a���Ă��邩�t���O
	u16 		toBox;					// �{�b�N�X�m�n�i�莝���̏ꍇ��RETURN_POSITION_TEMOTI�j
	GF_DATE		lastExchangeDate;		// �ŏI�������t
};



//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
WORLDTRADE_DATA * SaveData_GetWorldTradeData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_WORLDTRADEDATA);
}


//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int WorldTradeData_GetWorkSize(void)
{
	return sizeof(WORLDTRADE_DATA);
}

//==============================================================================
/**
 * $brief   ���E������ԕۑ��f�[�^�̊m��
 *
 * @param   heapID		
 *
 * @retval  WORLDTRADE_DATA *		
 */
//==============================================================================
WORLDTRADE_DATA * WorldTradeData_AllocWork(u32 heapID)
{
	WORLDTRADE_DATA * WorldTradeData;
	WorldTradeData = sys_AllocMemory(heapID, sizeof(WORLDTRADE_DATA));
	
	WorldTradeData_Init( WorldTradeData );

	return WorldTradeData;
	
}

//==============================================================================
/**
 * $brief   �f�[�^������
 *
 * @param   randomgroup		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTradeData_Init(WORLDTRADE_DATA * WorldTradeData )
{
	
	MI_CpuClearFast(WorldTradeData, sizeof(WORLDTRADE_DATA));
	
}


//==============================================================================
/**
 * $brief   �a���Ă��邩�H
 *
 * @param   WorldTradeData		
 *
 * @retval  int		0:�a���Ă��Ȃ�	1:�a���Ă���
 */
//==============================================================================
int  WorldTradeData_GetFlag( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->flag;
}
//==============================================================================
/**
 * $brief   �a���Ă���t���O�̑���
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
void  WorldTradeData_SetFlag( WORLDTRADE_DATA* WorldTradeData, int flag )
{
	WorldTradeData->flag = flag;
}


//==============================================================================
/**
 * $brief   �|�P�����f�[�^�����o��
 *
 * @param   WorldTradeData		
 * @param   poke		
 *
 * @retval  none		
 */
//==============================================================================
void  WorldTradeData_GetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke )
{
	MI_CpuCopyFast( WorldTradeData->PokemonData, (void*)poke, POKEMON_DATA_SIZE );
}

//==============================================================================
/**
 * $brief   �|�P������a�����̂ŁA�R�s�[��ۑ����Ă���
 *
 * @param   WorldTradeData		
 * @param   poke		
 *
 * @retval  none		
 */
//==============================================================================
void  WorldTradeData_SetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke, int boxno )
{
	MI_CpuCopyFast( (void*)poke, WorldTradeData->PokemonData, POKEMON_DATA_SIZE );
}


//==============================================================================
/**
 * $brief   ���������������Ō�̓��𓾂�
 *
 * @param   WorldTradeData		
 *
 * @retval  int		0:�a���Ă��Ȃ�	1:�a���Ă���
 */
//==============================================================================
GF_DATE  WorldTradeData_GetLastDate( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->lastExchangeDate;
}
//==============================================================================
/**
 * $brief   ���������������Ō�̓����L�^����
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
void  WorldTradeData_SetLastDate( WORLDTRADE_DATA* WorldTradeData, GF_DATE date )
{
	WorldTradeData->lastExchangeDate = date;
}

//==============================================================================
/**
 * @brief   �|�P�������a�����Ă���BOXNO�i�Ă�����RETURN_POSITION_TEMOTI�j�擾
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTradeData_GetBoxNo( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->toBox;
}

