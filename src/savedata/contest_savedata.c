//==============================================================================
/**
 * @file	contest_savedata.c
 * @brief	�R���e�X�g�Z�[�u�f�[�^����
 * @author	matsuda
 * @date	2006.06.03(�y)
 */
//==============================================================================
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"
#include "savedata/contest_savedata.h"
#include "contest/contest_def.h"
#include "contest_savedata_local.h"
#include "gflib/assert.h"



//==============================================================================
//	�萔��`
//==============================================================================
///�ΐ퐬�ыL�^�ő吔
#define CON_RECORD_COUNT_MAX		(9999)



//--------------------------------------------------------------
/**
 * @brief	�J�X�^���{�[���̃T�C�Y���擾
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CONDATA_GetWorkSize(void)
{
	return sizeof(CONTEST_DATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	�R���e�X�g�Z�[�u�f�[�^�̏���������
 * @param	condata		�R���e�X�g�Z�[�u�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
void CONDATA_Init(CONTEST_DATA * condata)
{
	int ranking, type;
	
	for(type = 0; type < CONTYPE_MAX; type++){
		for(ranking = 0; ranking < BREEDER_MAX; ranking++){
			condata->TuushinRecord[type][ranking] = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ΐ퐬�т��Z�b�g����
 *
 * @param   condata		�R���e�X�g�f�[�^�ւ̃|�C���^
 * @param   type		CONTYPE_???
 * @param   ranking		����(0origin)
 */
//--------------------------------------------------------------
void CONDATA_RecordAdd(SAVEDATA *sv, int type, int ranking)
{
	CONTEST_DATA *condata;
	
	condata = SaveData_Get(sv, GMDATA_ID_CONTEST);
	if(condata->TuushinRecord[type][ranking] < CON_RECORD_COUNT_MAX){
		condata->TuushinRecord[type][ranking]++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ΐ퐬�т��擾����
 *
 * @param   condata		�R���e�X�g�f�[�^�ւ̃|�C���^
 * @param   type		CONTYPE_???
 * @param   ranking		�擾���鏇��(0origin)
 *
 * @retval  �ΐ퐬��
 */
//--------------------------------------------------------------
u16 CONDATA_GetValue(SAVEDATA *sv, int type, int ranking)
{
	CONTEST_DATA *condata;
	
	condata = SaveData_Get(sv, GMDATA_ID_CONTEST);
	return condata->TuushinRecord[type][ranking];
}

