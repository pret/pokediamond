//=============================================================================================
/**
 * @file	scr_boxpwd.h
 * @brief	�{�b�N�X�p�X���[�h�ǎ��֘A����
 * @author	taya
 * @date	2006/06/01
 */
//=============================================================================================
#ifndef __SCR_BOXPWD_H__
#define __SCR_BOXPWD_H__

#define BOXPWD_RESULT_ERROR 	-1

//------------------------------------------------------------------
/**
 * �ǎ��p�X���[�h�����`�F�b�N
 *
 * @param   mystatus		
 * @param   word1		
 * @param   word2		
 * @param   word3		
 * @param   word4		
 *
 * @retval  int			�����̏ꍇ�A�ǎ��i���o�[(0�`7) / �s�����Ȃ� BOXPWD_RESULT_ERROR
 */
//------------------------------------------------------------------
extern int  BOXPWD_HitCheck( const MYSTATUS* mystatus, PMS_WORD word1, PMS_WORD word2, PMS_WORD word3, PMS_WORD word4 );

#endif
