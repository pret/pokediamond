#include "agbpoke_access.h"
#include "agbpoke_util.h"

static u16 agbpoke_font[] = L"�@�����������������������������������ĂƂȂɂʂ˂̂͂Ђӂւق܂݂ނ߂�������������񂟂����������傪�����������������������Âłǂ΂тԂׂڂς҂Ղ؂ۂ��A�C�E�G�I�J�L�N�P�R�T�V�X�Z�\�^�`�c�e�g�i�j�k�l�m�n�q�t�w�z�}�~�����������������������������@�B�D�F�H�������K�M�O�Q�S�U�W�Y�[�]�_�a�d�f�h�o�r�u�x�{�p�s�v�y�|�b0123456789!?�B�[�E�c�w�x�u�v�����~�D�~�^ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz��:";
#define EUFONT_START 0xf1
#define EOM_			0xff		/* �I���R�[�h */

static u16 eufont[] = 
{
	0x00c4, /* �E�����E�g�啶��A */
	0x00d6, /* �E�����E�g�啶��O */
	0x0055, /* �E�����E�g�啶��U */
	0x00e4, /* �E�����E�g������A */
	0x00f6, /* �E�����E�g������O */
	0x00fc /* �E�����E�g������U */
};
static u16 convPokecode(u8 code)
{
	if( code < EUFONT_START ) return agbpoke_font[code];
	return eufont[code - EUFONT_START];
	
}

void agbpoke_codeConv(u8 *src, u16 *dest, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		if( *(src + i) == EOM_ )
		{
			dest[i] = 0;
			return;
		}
		dest[i] = convPokecode(*(src + i));
	}
	dest[length] = 0;
}


//------------------------------------------------------------------
/**
 * @brief	�g���[�i�[�̂h�c�i���o�[��Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u32 agbpoke_GetTrainerID(void)
{
  SYS_SAVE_DATA *myd = agbpoke_GetMyDataPtr();	// MyData�ւ̃|�C���^��Ԃ�
  return myd->ID[3] << 24 | myd->ID[2] << 16 | myd->ID[1] << 8 | myd->ID[0];
}

//------------------------------------------------------------------
/**
 * @brief	�g���[�i�[����Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u8 *agbpoke_GetTrainerName(void)
{
  SYS_SAVE_DATA *myd = agbpoke_GetMyDataPtr();	// MyData�ւ̃|�C���^��Ԃ�
  return myd->my_name;
}


/*  */
