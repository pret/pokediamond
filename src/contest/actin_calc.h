//==============================================================================
/**
 * @file	actin_calc.h
 * @brief	���Z�͕���F�Z���ʌv�Z�Ȃǂ̃w�b�_
 * @author	matsuda
 * @date	2005.12.07(��)
 */
//==============================================================================
#ifndef __ACTIN_CALC_H__
#define __ACTIN_CALC_H__


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern int ACALC_BaseAppealGet(int wazano);
extern int ACALC_JudgeSufferCheck(ACTIN_GAME_PARAM *a_game, int check_breeder);
extern int ACALC_JudgeSufferPointCheck(int suffer_num);
extern int ACALC_VoltageUpDownCheck(int contest_type, int wazano, int judge_no, 
	int special_judge_no);
extern void ACALC_BreederSort(ACTIN_GAME_PARAM *a_game);


#endif	//__ACTIN_CALC_H__

