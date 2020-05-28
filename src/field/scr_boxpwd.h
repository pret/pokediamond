//=============================================================================================
/**
 * @file	scr_boxpwd.h
 * @brief	ボックスパスワード壁紙関連処理
 * @author	taya
 * @date	2006/06/01
 */
//=============================================================================================
#ifndef __SCR_BOXPWD_H__
#define __SCR_BOXPWD_H__

#define BOXPWD_RESULT_ERROR 	-1

//------------------------------------------------------------------
/**
 * 壁紙パスワード正解チェック
 *
 * @param   mystatus		
 * @param   word1		
 * @param   word2		
 * @param   word3		
 * @param   word4		
 *
 * @retval  int			正解の場合、壁紙ナンバー(0～7) / 不正解なら BOXPWD_RESULT_ERROR
 */
//------------------------------------------------------------------
extern int  BOXPWD_HitCheck( const MYSTATUS* mystatus, PMS_WORD word1, PMS_WORD word2, PMS_WORD word3, PMS_WORD word4 );

#endif
