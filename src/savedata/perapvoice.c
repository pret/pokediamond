//============================================================================================
/**
 * @file	perapvoice.c
 * @brief
 * @date	2006.04.06
 */
//============================================================================================


#include "savedata/savedata.h"
#include "savedata/perapvoice.h"
#include "perapvoice_local.h"

#include "gflib/assert.h"
#include "gflib/heapsys.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�I�E���|�P�����̐��f�[�^�Z�[�u���[�N�̒�`
 */
//----------------------------------------------------------
struct PERAPVOICE {
	BOOL exist_flag;
	s8 voicedata[PERAPVOICE_LENGTH];
};

//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�؃��b�v�̐����[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int PERAPVOICE_GetWorkSize(void)
{
	return sizeof(PERAPVOICE);
}

//----------------------------------------------------------
/**
 * @brief	�؃��b�v�̐����[�N�̏�����
 * @param	pv		PERAPVOICE�f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
void PERAPVOICE_Init(PERAPVOICE * pv)
{
	MI_CpuClear32(pv, sizeof(PERAPVOICE));
	pv->exist_flag = FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�؃��b�v�̐����[�N�̏�����
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	PERAPVOICE	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
PERAPVOICE * PERAPVOICE_AllocWork(int heapID)
{
	PERAPVOICE *pv = sys_AllocMemory(heapID, sizeof(PERAPVOICE));
	PERAPVOICE_Init(pv);
	return pv;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�؃��b�v�̐��Z�[�u�f�[�^�̎擾
 * @param	sv		�Z�[�u�f�[�^�ւ̃|�C���^
 * @return	PERAPVOICE�f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
PERAPVOICE * SaveData_GetPerapVoice(SAVEDATA * sv)
{
	return (PERAPVOICE*)SaveData_Get(sv, GMDATA_ID_PERAPVOICE);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���f�[�^�����݂��邩�ǂ����̃`�F�b�N
 * @param	pv		���f�[�^�ւ̃|�C���^
 * @return	BOOL	TRUE�F���݂���AFALSE�F���݂��Ȃ�
 */
//----------------------------------------------------------
BOOL PERAPVOICE_GetExistFlag(const PERAPVOICE * pv)
{
	return pv->exist_flag;
}

//==============================================================================
/**
 * @brief   ���f�[�^�̑��݃t���O�𗎂Ƃ�
 *
 * @param   pv		���f�[�^�ւ̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void PERAPVOICE_ClearExistFlag( PERAPVOICE * pv )
{
	pv->exist_flag = 0;
}

//----------------------------------------------------------
/**
 * @brief	���f�[�^�̎擾
 * @param	pv		���f�[�^�ւ̃|�C���^
 * @return	���f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
const void * PERAPVOICE_GetVoiceData(const PERAPVOICE * pv)
{
	return pv->voicedata;
}

//==============================================================================
/**
 * $brief   ���f�[�^�̓W�J
 *
 * @param   des		�W�J��
 * @param   src		�y���b�v�{�C�X�̃|�C���^
 *
 * @retval  none		
 *
 * 06/04/15���_�ł̓y���b�v�{�C�X��4bit,2khz,1�b�T���v�����O=1k
 * ���̃f�[�^��8bit�ɐL�΂���2k�ɂ��Ċi�[����
 */
//==============================================================================
void PERAPVOICE_ExpandVoiceData( s8 *des, const s8 *src )
{
	int i,count=0;
	s8 tmp;
	u8 dat;

	// 4bit1kbyte��8bit2kbyte�ɐL�΂�
	for(i=0;i<PERAPVOICE_LENGTH;i++){
		dat = src[i]&0x0f;
		tmp = dat-8;
		
		des[count]   = tmp*16;

		dat = src[i]>>4;
		tmp = dat-8;
		des[count+1]   = tmp*16;


//		des[count  ] = src[i];
//		des[count+1] = src[i]>>4;
		count += 2;
	}
}

//----------------------------------------------------------
/**
 * @brief	���f�[�^�̃Z�b�g
 * @param	pv		���f�[�^�ւ̃|�C���^
 * @param	src		�Z�b�g����f�[�^�ւ̃|�C���^
 *
 * 06/04/15���_�ł̓y���b�v�{�C�X��8bit,2khz,1�b�T���v�����O=2k
 * ���̃f�[�^��4bit�ɏk�߂�1k�ɂ��Ċi�[����
 *
 */
//----------------------------------------------------------
void PERAPVOICE_SetVoiceData(PERAPVOICE * pv, const s8 * src)
{
	int i,count;
	s8 tmp;
	u8 dat;

	// �i�[�t���O�𗧂Ă�
	pv->exist_flag = TRUE;

	// 2khz8bit��4bit�ɂ��Ċi�[
	count = 0;
	for(i=0;i<PERAPVOICE_LENGTH*2;i+=2){
		tmp = (src[i]/16);
		dat = tmp+8;
		pv->voicedata[count]   = dat;
//		pv->voicedata[count]  =  src[i];

		tmp = (src[i+1]/16);
		dat = tmp+8;

		pv->voicedata[count] |= (dat<<4);
//		pv->voicedata[count] |= (src[i+1]<<4);
		count++;
	}

//	MI_CpuCopy32(src, (void *)pv->voicedata, PERAPVOICE_LENGTH);
}

//==============================================================================
/**
 * $brief   ���f�[�^�̃R�s�[
 *
 * @param   des		�R�s�[�携�f�[�^�̃|�C���^
 * @param   src		�R�s�[�����f�[�^�̃|�C���^
 *
 * @retval  none	
 */
//==============================================================================
void PERAPVOICE_CopyData(PERAPVOICE * des, const PERAPVOICE * src)
{
	MI_CpuCopyFast(src, des,  sizeof(PERAPVOICE));
}
