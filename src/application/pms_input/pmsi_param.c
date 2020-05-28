

#include "common.h"
#include "system\pms_data.h"
#include "system\pms_word.h"
#include "savedata\zukanwork.h"
#include "savedata\config.h"

#include "field\sysflag.h"

#include "pms_input_prv.h"

//==================================================================================
//==================================================================================
enum {
	PMS_TYPE_DEFAULT = PMS_TYPE_MAIL,
};

//==================================================================================
//==================================================================================

struct _PMSI_PARAM {
	u8   input_mode;
	u8   guidance_type;			///< �������^�C�v�ienum PMS_INPUT_GUIDANCE�j

	// [out]
	u8  cancel_flag;			///< �u��߂�v�ŃL�����Z�����ꂽ�t���O
	u8  modified_flag;			///< �L�����Z�����ꂸ�A�����e���X�V���ꂽ���t���O

	u8  game_clear_flag;
	u8  notedit_egnore_flag;	///< ON�ɂ���ƕҏW����Ă��Ȃ��Ă����ʂɏI��邱�Ƃ��o����

	WINTYPE		win_type;

	const ZUKAN_WORK*     zukan_savedata;
	const PMSW_SAVEDATA*  pmsw_savedata;

	PMS_DATA   pms;		// ���̓��[�h�p
	PMS_WORD   word[PMS_INPUT_WORD_MAX];	// �P�ꃂ�[�h�p

	// �{�b�N�X�ǎ��p�X���[�h�Ƃ��Ă̒l�i�P��Q���[�h���̂ݗL���j
	u16        boxpwd_id[ PMS_INPUT_WORD_MAX ];
};


//==============================================================
// Prototype
//==============================================================








//==============================================================================================
//	���͉�ʂ��Ăяo��������̃p�����[�^����
//==============================================================================================

//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʃp�����[�^�쐬
 *
 * @param   input_mode			���̓��[�h�ienum PMSI_MODE�j
 * @param   guidance_type		�������^�C�v�ienum PMSI_GUIDANCE�j
 * @param   savedata			�Z�[�u�f�[�^�|�C���^
 * @param   heapID				�쐬�p�q�[�vID
 *
 * @retval  PMSI_PARAM*			�쐬���ꂽ�p�����[�^�I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
PMSI_PARAM*  PMSI_PARAM_Create( u32 input_mode, u32 guidance_type, SAVEDATA* savedata, u32 heapID )
{
	PMSI_PARAM* p = sys_AllocMemory( heapID, sizeof(PMSI_PARAM));

	p->input_mode = input_mode;
	p->guidance_type = guidance_type;
	p->zukan_savedata = SaveData_GetZukanWork(savedata);
	p->pmsw_savedata = SaveData_GetPMSW(savedata);
	p->game_clear_flag = SysFlag_GameClearCheck( SaveData_GetEventWork(savedata) );
	p->notedit_egnore_flag = FALSE;

	p->cancel_flag = TRUE;
	p->modified_flag = FALSE;
	p->win_type = CONFIG_GetWindowType( SaveData_GetConfig(savedata) );

	if(input_mode == PMSI_MODE_SENTENCE)
	{
		PMSDAT_Init( &p->pms, PMS_TYPE_DEFAULT );
	}
	else
	{
		int i;
		for(i=0; i<PMS_INPUT_WORD_MAX; i++)
		{
			p->word[i] = PMS_WORD_NULL;
		}
	}

	return p;
}
//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʃp�����[�^�j��
 *
 * @param   p		�p�����[�^�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_Delete( PMSI_PARAM* p )
{
	sys_FreeMemoryEz(p);
}



//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʂ̏�����ԂɎg�p����p�����[�^�Z�b�g�i�P��P���[�h�p�j
 *
 * @param   p			�p�����[�^�I�u�W�F�N�g
 * @param   word		�Z�b�g����ȈՉ�b�P��R�[�h
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_SetInitializeDataSingle( PMSI_PARAM* p, PMS_WORD word )
{
	p->word[0] = word;
}
//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʂ̏�����ԂɎg�p����p�����[�^�Z�b�g�i�P��Q���[�h�p�j
 *
 * @param   p			�p�����[�^�I�u�W�F�N�g
 * @param   word0		�Z�b�g����ȈՉ�b�P��R�[�h�P
 * @param   word1		�Z�b�g����ȈՉ�b�P��R�[�h�Q
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_SetInitializeDataDouble( PMSI_PARAM* p, PMS_WORD word0, PMS_WORD word1 )
{
	p->word[0] = word0;
	p->word[1] = word1;
}
//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʂ̏�����ԂɎg�p����p�����[�^�Z�b�g�i���̓��[�h�p�j
 *
 * @param   p		�p�����[�^�I�u�W�F�N�g
 * @param   pms		�Z�b�g����ȈՉ�b�f�[�^�|�C���^
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_SetInitializeDataSentence( PMSI_PARAM* p, const PMS_DATA* pms )
{
	p->pms = *pms;
}

//------------------------------------------------------------------
/**
 * ��x���ʂ��󂯎������A�����P�x�A���͉�ʗp�p�����[�^�Ƃ��Ďg����悤�ɂ���
 *
 * @param   p		�p�����[�^�I�u�W�F�N�g
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_SetReuseState( PMSI_PARAM* p )
{
	p->cancel_flag = TRUE;
	p->modified_flag = FALSE;
}


//------------------------------------------------------------------
/**
 * �ҏW���Ȃ��Ă����ʂɏI���t���O�����Ă�
 *
 * @param   p		
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_SetNotEditEgnore( PMSI_PARAM* p )
{
	p->notedit_egnore_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʂŁA���͂��L�����Z�����ꂽ���ǂ�������
 *
 * @param   p			�p�����[�^�I�u�W�F�N�g
 *
 * @retval  BOOL		TRUE�ŃL�����Z�����ꂽ
 */
//------------------------------------------------------------------
BOOL PMSI_PARAM_CheckCanceled( const PMSI_PARAM* p )
{
	return p->cancel_flag;
}
//------------------------------------------------------------------
/**
 * �ȈՉ�b���͉�ʂ̏I����A������Ԃ���ύX���Ȃ��ꂽ���`�F�b�N
 *
 * @param   p			�p�����[�^�I�u�W�F�N�g
 *
 * @retval  BOOL		TRUE�ŕύX���ꂽ
 */
//------------------------------------------------------------------
BOOL PMSI_PARAM_CheckModified( const PMSI_PARAM* p )
{
	return p->modified_flag;
}


//------------------------------------------------------------------
/**
 * ���͉�ʂœ��͂��ꂽ�f�[�^���擾�i�P��P���[�h�j
 *
 * @param   p			�p�����[�^�I�u�W�F�N�g
 *
 * @retval  PMS_WORD		���̓f�[�^�i�P��R�[�h�j
 */
//------------------------------------------------------------------
PMS_WORD  PMSI_PARAM_GetInputDataSingle( const PMSI_PARAM* p )
{
	return p->word[0];
}

//------------------------------------------------------------------
/**
 * ���͉�ʂœ��͂��ꂽ�f�[�^���擾�i�P��Q���[�h�j
 *
 * @param   p		�p�����[�^�I�u�W�F�N�g
 * @param   dst		���͂��ꂽ�f�[�^���󂯎��o�b�t�@
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_GetInputDataDouble( const PMSI_PARAM* p,  PMS_WORD* dst )
{
	dst[0] = p->word[0];
	dst[1] = p->word[1];
}

//------------------------------------------------------------------
/**
 * ���͉�ʂœ��͂��ꂽ�f�[�^���擾�i���̓��[�h�j
 *
 * @param   p		�p�����[�^�I�u�W�F�N�g
 * @param   pms		���͂��ꂽ�f�[�^���󂯎��\���̃A�h���X
 *
 */
//------------------------------------------------------------------
void PMSI_PARAM_GetInputDataSentence( const PMSI_PARAM* p, PMS_DATA* pms )
{
	PMSDAT_Copy( pms, &(p->pms) );
}







//==============================================================================================
//	���͉�ʓ�������̃p�����[�^����
//==============================================================================================

u32 PMSI_PARAM_GetInputMode( const PMSI_PARAM* p )
{
	return p->input_mode;
}
u32 PMSI_PARAM_GetGuidanceType( const PMSI_PARAM* p )
{
	return p->guidance_type;
}

int PMSI_PARAM_GetWindowType( const PMSI_PARAM* p )
{
	return p->win_type;
}

const ZUKAN_WORK*  PMSI_PARAM_GetZukanSaveData( const PMSI_PARAM* p )
{
	return p->zukan_savedata;
}

const PMSW_SAVEDATA* PMSI_PARAM_GetPMSW_SaveData( const PMSI_PARAM* p )
{
	return p->pmsw_savedata;
}

BOOL PMSI_PARAM_GetGameClearFlag( const PMSI_PARAM* p )
{
	return p->game_clear_flag;
}

BOOL PMSI_PARAM_GetNotEditEgnoreFlag( const PMSI_PARAM* p )
{
	return p->notedit_egnore_flag;
}

void PMSI_PARAM_GetInitializeData( const PMSI_PARAM* p, PMS_WORD* word, PMS_DATA* pms )
{
	switch( p->input_mode ){
	case PMSI_MODE_SINGLE:
		word[0] = p->word[0];
		break;
	case PMSI_MODE_DOUBLE:
		word[0] = p->word[0];
		word[1] = p->word[1];
		break;
	case PMSI_MODE_SENTENCE:
		*pms = p->pms;
		break;
	}
}

BOOL PMSI_PARAM_CheckModifiedByEditDatas( const PMSI_PARAM* p, const PMS_WORD* word, const PMS_DATA* pms )
{
	switch( p->input_mode ){
	case PMSI_MODE_SINGLE:
		return word[0] == p->word[0];

	case PMSI_MODE_DOUBLE:
		return ((word[0] == p->word[0]) && (word[1] == p->word[1]));

	case PMSI_MODE_SENTENCE:
	default:
		return PMSDAT_Compare( &p->pms, pms );
	}

}

void PMSI_PARAM_WriteBackData( PMSI_PARAM* p, const PMS_WORD* word, const PMS_DATA* pms )
{
	int i;

	p->modified_flag = (PMSI_PARAM_CheckModifiedByEditDatas(p, word, pms) == FALSE);
	p->cancel_flag = FALSE;

	for(i=0; i<PMS_INPUT_WORD_MAX; i++)
	{
		p->word[i] = word[i];
	}
	p->pms = *pms;
}
