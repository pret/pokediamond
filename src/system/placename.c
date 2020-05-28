//============================================================================================
/**
 * @file	placename.c
 * @brief	�n���f�[�^��舵��
 * @author	taya
 * @date	2006.05.20
 */
//============================================================================================
#include "common.h"


#include "system\placename.h"


//--------------------------------------------------------------
/**
 *	�ߊl�ꏊ�^�C�v���Ƃ̊J�n�l
 */
//--------------------------------------------------------------
enum {
	MAP_START_NUMBER = 0,
	GAME_EVENT_START_NUMBER = 2000,
	EXT_EVENT_START_NUMBER = 3000,
};

static const u16  TypeStartNumber[] = {
	MAP_START_NUMBER,
	GAME_EVENT_START_NUMBER,
	EXT_EVENT_START_NUMBER,
};

//------------------------------------------------------------------
/**
 * �ߊl�ꏊ�i���o�[����ߊl�ꏊ�^�C�v���擾
 *
 * @param   number		�ߊl�ꏊ�i���o�[�i�|�P�����p�����[�^�Ƃ��ăZ�b�g����Ă���l�j
 *
 * @retval  PLACENAME_TYPE		�ߊl�ꏊ�^�C�v
 */
//------------------------------------------------------------------
PLACENAME_TYPE  PlaceName_GetType( u32 number )
{
	int i;

	for(i=0; i<(PLACENAME_TYPE_MAX-1); i++)
	{
		if( number < TypeStartNumber[i+1] )
		{
			return i;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * �ߊl�ꏊ�i���o�[����A�e�ߊl�ꏊ�^�C�v���Ƃ̃C���f�b�N�X�l��Ԃ�
 * ���߂�l��gmm���當����擾����ۂ̃C���f�b�N�X�Ƃ��Ďg����
 *
 * @param   number		�ߊl�ꏊ�i���o�[�i�|�P�����p�����[�^�Ƃ��ăZ�b�g����Ă���l�j
 *
 * @retval  int		�ߊl�ꏊ�^�C�v���Ƃ̃C���f�b�N�X
 */
//------------------------------------------------------------------
int PlaceName_GetIndex( u32 number )
{
	int type = PlaceName_GetType( number );
	return number - TypeStartNumber[type];
}


//------------------------------------------------------------------
/**
 * �ߊl�ꏊ�^�C�v���C���f�b�N�X����A�|�P�����p�����[�^�Ƃ��ăZ�b�g���邽�߂̒l���쐬
 *
 * @param   type		�ߊl�ꏊ�^�C�v
 * @param   index		�^�C�v���Ƃ̃C���f�b�N�X
 *
 * @retval  int			�|�P�����p�����[�^�Ƃ��ăZ�b�g���邽�߂̒l
 */
//------------------------------------------------------------------
int PlaceName_IndexToParamNumber( PLACENAME_TYPE type, int index )
{
	GF_ASSERT(type<PLACENAME_TYPE_MAX);
	return TypeStartNumber[type] + index;
}

