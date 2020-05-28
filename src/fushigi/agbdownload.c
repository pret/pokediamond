//===================================================================
/**
 * @file	agbdownload.c
 * @bfief	AGB�J�Z�b�g����̂ӂ����f�[�^�_�E�����[�h
 * @author	Satoshi Mitsuhara
 * @date	06.06.09
 *
 * <pre>
 * �`�f�a�J�Z�b�g���̃������}�b�v
 *	0x08000000	�v���O�����{�f�[�^
 *	     |
 *	0x08100000	�]���f�[�^�̃T�C�Y(�S�o�C�g)
 *	0x08100010	�r�[�R�����
 *	0x08100100	�ӂ����Ȃ�������̃f�[�^�J�n
 *	     |
 *	0x081xxxxx	�I��
 * </pre>
 *
 * $Id: agbdownload.c,v 1.3 2006/07/15 08:47:20 mitsuhara Exp $
 */
//===================================================================

#include "agbdownload.h"

// �A�N�Z�X�\�J�[�g���b�W�̃Q�[���R�[�h
static u32 AgbCartridgeTable[] = {
#if 0
  // �����Ӂ�
  // �����̓_�C�������h�^�p�[���p�ɕύX����Ȃ���΂Ȃ�܂���I
  'ZP3J',  'ZP4J',  'ZP5J',  'ZP6J',  'ZP7J',
  'ZR3J',  'ZR4J',  'ZR5J',  'ZR6J',  'ZR7J',
#else
  'B5BJ', 'B5CJ', 'B5DJ', 'B5EJ', 'B5FJ',
  'B5GJ', 'B5HJ', 'B5IJ', 'B5JJ', 'B5KJ',
  'B5LJ', 'B5MJ', 'B5PJ', 'B5QJ', 'B5RJ',
  'B5SJ', 'B5TJ', 'B5UJ', 'B5VJ', 'B5WJ',
#endif
  0,
};


//------------------------------------------------------------------
/**
 * @brief	�ӂ����f�[�^���܂ރJ�Z�b�g����������
 * @param	NONE
 * @return	TRUE: �ӂ����J�Z�b�g   FALSE: �Ȃ�
 */
//------------------------------------------------------------------
static BOOL CheckAgbCartridgeInitialCode(void)
{
  int i;
  u32 init_code = CTRDG_GetAgbGameCode();
  // AgbCartridgeTable��u32�Ƃ��Ĉ����Ă��ă��g���G���f�B�A���ɂȂ��Ă��܂�����
  // ���̂��܂��킹��init_code���Ђ�����Ԃ�
  init_code = (((init_code >>  0) & 255) << 24 |
	       ((init_code >>  8) & 255) << 16 |
	       ((init_code >> 16) & 255) <<  8 |
	       ((init_code >> 24) & 255) <<  0);

  for(i = 0; i < AgbCartridgeTable[i]; i++){
    if(AgbCartridgeTable[i] == init_code){
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("AGB�z�z�J�Z�b�g��F�����܂��� [GAMECODE:%c%c%c%c]\n",
		 (init_code >> 24) & 255,
		 (init_code >> 16) & 255,
		 (init_code >>  8) & 255,
		 (init_code >>  0) & 255);
#endif
      return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�Z�b�g�̃A�N�Z�X�����������Ă��邩����
 * @param	NONE
 * @return	TRUE: �A�N�Z�X�\   FALSE: �Ȃ�
 */
//------------------------------------------------------------------
static BOOL IsExistAgbCartridge(void)
{
  // �`�f�a�J�[�g���b�W������(OS_Init�ŏ�������Ă���͂��H)
  CTRDG_Init();
  // �`�f�a�J�[�g���b�W�����݂��Ȃ����FALSE
  if(CTRDG_IsAgbCartridge() == FALSE)
    return FALSE;
  // �C�V���ȊO�̃J�Z�b�g�Ȃ��FALSE
  if(CTRDG_GetAgbMakerCode() != AGB_MAKER_CODE)
    return FALSE;
  // �w�肳�ꂽ�C�j�V�����R�[�h�ȊO��FALSE
  if(CheckAgbCartridgeInitialCode() == FALSE)
    return FALSE;
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�[�g���b�W���ɂ���f�[�^�̃T�C�Y��Ԃ�
 * @param	NONE
 * @return	�T�C�Y(0�Ȃ�΃J�[�g���b�W���h�����Ă��Ȃ�
 */
//------------------------------------------------------------------
int GetAgbCartridgeDataSize(void)
{
  u32 size;

  // �J�Z�b�g�̏������`�F�b�N
  if(IsExistAgbCartridge() == FALSE)
    return 0;

  CTRDG_Enable(TRUE);
  CTRDG_Read32((const u32 *)AGBMISSIONDATASIZE, &size);
  CTRDG_Enable(FALSE);
  
  return size;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�[�g���b�W���ɂ���r�[�R���f�[�^���R�s�[
 * @param	NONE
 * @return	TRUE: �R�s�[����  : FALSE: ���s
 */
//------------------------------------------------------------------
BOOL GetAgbCartridgeBeaconData(void *dist, int size)
{
  BOOL flag;

  // �J�Z�b�g�̏������`�F�b�N
  if(IsExistAgbCartridge() == FALSE)
    return FALSE;

  // �Q�[���f�[�^���w��̈�ɃR�s�[����
  if(size == 0)
    return FALSE;

  CTRDG_Enable(TRUE);
  flag = (BOOL)CTRDG_CpuCopy16((const void *)AGBBEACONDATAPTR, dist, size);
  CTRDG_Enable(FALSE);

  // �Ō�ɃJ�[�g���b�W����������s��
  if(CTRDG_IsExisting() == FALSE)
    return FALSE;

  return flag;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�[�g���b�W����f�[�^��ǂݏo��
 * @param	NONE
 * @return	TRUE: ����   FALSE: ���s
 */
//------------------------------------------------------------------
BOOL ReadAgbCartridgeData(void *dist, int size)
{
  BOOL flag;

  // �J�Z�b�g�̏������`�F�b�N
  if(IsExistAgbCartridge() == FALSE)
    return FALSE;

  // �Q�[���f�[�^���w��̈�ɃR�s�[����
  if(size == 0)
    size = GetAgbCartridgeDataSize();
  CTRDG_Enable(TRUE);
  flag = (BOOL)CTRDG_CpuCopy16((const void *)AGBMISSIONDATAPTR, dist, size);
  CTRDG_Enable(FALSE);

  OS_TPrintf("AGB�J�Z�b�g�ɓ����Ă�f�[�^�̃T�C�Y��%d [%08X\n", size, dist);

  
  // �Ō�ɃJ�[�g���b�W����������s��
  if(CTRDG_IsExisting() == FALSE)
    return FALSE;

  return flag;
}

/*  */
