//=============================================================================
/**
 * @file	get_text.c	
 * @bfief	���b�Z�[�W�G�f�B�^�R���o�[�^���o�͂����f�[�^����e�L�X�g�f�[�^���擾
 * @author	GAME FREAK inc.  taya
 */
//=============================================================================
#include "common.h"
#include "system/get_text.h"

//------------------------------------------------------------------
/**
 * ������ID���當����A�h���X��Ԃ�
 *
 * @param   msg_data		������f�[�^�擪�A�h���X
 * @param   msg_id			������ID
 *
 * @retval  const u8*		
 *
 *	������ msg_data �́A���b�Z�[�W�R���o�[�^���o�͂����o�C�i���t�@�C���̐擪�ł�
 *
 */
//------------------------------------------------------------------
const STRCODE* GetMessageData(const u8* msg_data, u32 msg_id)
{
	const u32 *ptr;
	u32  msg_max;

	ptr = (const u32*)msg_data;

	msg_max = *ptr++;
	if(msg_id >= msg_max)
	{
		SDK_ASSERT(0);
		return NULL;
	}

	ptr += msg_id;
	msg_data = (const u8*)ptr;
	msg_data += *ptr;

	return (STRCODE*)msg_data;
}
