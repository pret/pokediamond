//=============================================================================
/**
 * @file	spray.c
 * @bfief	�X�v���[����
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================

#include "common.h"
#include "field_common.h"
#include "savedata/encount.h"
#include "savedata/savedata.h"
#include "script.h"
#include "fielddata/script/common_scr_def.h"

#include "spray.h"

//==============================================================================
/**
 * 1�����Ƃ̃X�v���[���ʌ��Z
 *
 * @param	sv		�Z�[�u�f�[�^�|�C���^
 * 
 * @retval	BOOL	TRUE:�X�v���[���ʐ؂�	FALSE:����ȊO
 * 
 */
//==============================================================================
BOOL Spray_DecSpray(SAVEDATA * sv, FIELDSYS_WORK * fsys)
{
	u8 *spray;
	//�Z�[�u�f�[�^�擾
	spray = EncDataSave_GetSprayCnt(EncDataSave_GetSaveDataPtr(sv));
	//0�łȂ���΁A���Z
	if ( (*spray) > 0 ){
		(*spray)--;
		//���Z��������0�ɂȂ�������ʐ؂ꃁ�b�Z�[�W
		if( (*spray)==0 ){
			OS_Printf("�X�v���[���ʐ؂�\n");
			EventSet_Script(fsys, SCRID_END_SPRAY, NULL);
			return TRUE;
		}
	}
	return FALSE;
}
