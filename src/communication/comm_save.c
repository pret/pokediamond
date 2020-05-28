//=============================================================================
/**
 * @file	comm_save.c
 * @brief	�ʐM���g�����ėp�֐�
 * @author	Katsumi Ohno
 * @date    2006.03.14
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "savedata/savedata.h"
#include "communication/comm_save.h"

//==============================================================================
// �ʐM�����p��`
//==============================================================================
#define COMM_SAVE_SYNCHRO_NO1	( 111 )
#define COMM_SAVE_SYNCHRO_NO2	( 112 )
#define COMM_SAVE_SYNCHRO_NO3	( 113 )


//==============================================================================
// �V�[�P���X��`
//==============================================================================
enum{
	COMMSAVE_SEQ_START=0,
	COMMSAVE_SEQ_SYNCRO1,
	COMMSAVE_SEQ_SAVE,
	COMMSAVE_SEQ_SYNCRO2,
	COMMSAVE_SEQ_SAVE_FINISH,
	COMMSAVE_SEQ_SYNCRO3,
	COMMSAVE_SEQ_END,
};
//==============================================================================
/**
 * @brief   �ʐM�����Z�[�u����������
 *
 * @param   savedata		
 * @param   BlockID		
 *
 * @retval  none		
 */
//==============================================================================
void CommSyncronizeSaveInit( int *seq )
{
	*seq = COMMSAVE_SEQ_START;
}


//==============================================================================
/**
 * @brief   �ʐM�����Z�[�u�V�[�P���X
 *
 * @param   savedata	�Z�[�u�f�[�^�\���̂ւ̃|�C���^
 * @param   seq			�V�[�P���X�Ǘ��p��[���̃|�C���^
 *
 * @retval  int			0:������	1:�I��
 */
//==============================================================================
int CommSyncronizeSave( SAVEDATA *savedata, int BlockID, int *seq )
{
	SAVE_RESULT result;
	switch(*seq){
	// 1��ڂ̓����J�n
	case COMMSAVE_SEQ_START:
		CommTimingSyncStart( COMM_SAVE_SYNCHRO_NO1 );
		*seq = COMMSAVE_SEQ_SYNCRO1;
		break;

	// �����I���{�Z�[�u������
	case COMMSAVE_SEQ_SYNCRO1:
		if(CommIsTimingSync(COMM_SAVE_SYNCHRO_NO1)){
			SaveData_DivSave_Init(savedata, BlockID);
			*seq = COMMSAVE_SEQ_SAVE;
			OS_Printf("�����P���\n");
		}
		break;
	// �Z�[�u
	case COMMSAVE_SEQ_SAVE:
		result = SaveData_DivSave_Main(savedata);
		GF_ASSERT(result != SAVE_RESULT_OK);
		GF_ASSERT(result != SAVE_RESULT_NG);
		if (result == SAVE_RESULT_LAST){
			*seq = COMMSAVE_SEQ_SYNCRO2;
			CommTimingSyncStart( COMM_SAVE_SYNCHRO_NO2 );
			OS_Printf("�Z�[�u�O���I��\n");
		}
		break;
	// 2��ڂ̓���
	case COMMSAVE_SEQ_SYNCRO2:
		if(CommIsTimingSync(COMM_SAVE_SYNCHRO_NO2)){
			*seq = COMMSAVE_SEQ_SAVE_FINISH;
			OS_Printf("�����Q���\n");
		}
		break;
	// �Z�[�u�c��Z�N�^�������ݏ���
	case COMMSAVE_SEQ_SAVE_FINISH:
		result = SaveData_DivSave_Main(savedata);
		GF_ASSERT(result != SAVE_RESULT_NG);
		GF_ASSERT(result != SAVE_RESULT_LAST);
		if (result == SAVE_RESULT_OK) {
			OS_Printf("�Z�[�u�㔼�I��\n");
			*seq = COMMSAVE_SEQ_SYNCRO3;
		}
		break;
	// �I������
	case COMMSAVE_SEQ_SYNCRO3:
			*seq = COMMSAVE_SEQ_END;
		break;
	// �I��
	case COMMSAVE_SEQ_END:
		return 1;
		break;
	}
	
	return 0;
}
