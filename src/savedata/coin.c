//============================================================================================
/**
 * @brief	coin.c
 * @brief	�R�C������
 * @date	2006.03.09
 * @author	tamada
 */
//============================================================================================

#include "savedata/coin.h"
#include "coin_local.h"
#include "gflib/assert.h"

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�R�C���f�[�^�̏���������
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
void COIN_Init(COIN * coin)
{
	coin->value = 0;
}
//---------------------------------------------------------------------------
/**
 * @brief	�R�C���̐����Z�b�g����
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 * @param	setvalue	�Z�b�g����l
 */
//---------------------------------------------------------------------------
void COIN_Set(COIN * coin, u32 setvalue)
{
	GF_ASSERT(setvalue <= COIN_MAX);
	coin->value = setvalue;
}

//---------------------------------------------------------------------------
/**
 * @brief	�R�C���̐����擾����
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 * @retval	int			�R�C���̐�
 */
//---------------------------------------------------------------------------
u32 COIN_GetValue(const COIN * coin)
{
	return coin->value;
}

//---------------------------------------------------------------------------
/**
 * @brief	�R�C���𑝂₷
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 * @param	addvalue	���₷�l
 * @retval	TRUE		��������
 * @retval	FALSE		���s����
 */
//---------------------------------------------------------------------------
BOOL COIN_Add(COIN * coin, u32 addvalue)
{
//	GF_ASSERT(addvalue > COIN_MAX);
	if (coin->value >= COIN_MAX) {
		return FALSE;
	}
	coin->value += addvalue;
	if (coin->value > COIN_MAX) {
		coin->value = COIN_MAX;
	}
	return TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	�R�C���𑝂₹�邩�ǂ������`�F�b�N
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 * @param	addvalue	���₷�l
 * @retval	TRUE		�R�C���𑝂₷�̂ɐ�������
 * @retval	FALSE		�R�C���𑝂₷�̂Ɏ��s�����i�ő�l�𒴂����j
 */
//---------------------------------------------------------------------------
BOOL COIN_AddCheck(const COIN * coin, u32 addvalue)
{
	if (addvalue + (u32)coin->value <= COIN_MAX) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�R�C�������炷
 * @param	coin		�R�C���f�[�^�ւ̃|�C���^
 * @param	subvalue	���炷�l
 * @retval	TRUE		��������
 * @retval	FALSE		���s����
 */
//---------------------------------------------------------------------------
BOOL COIN_Sub(COIN * coin, u32 subvalue)
{
//	GF_ASSERT(subvalue > COIN_MAX);
	if (coin->value < subvalue) {
		return FALSE;
	}
	coin->value -= subvalue;
	return TRUE;
}

