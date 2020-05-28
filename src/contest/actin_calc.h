//==============================================================================
/**
 * @file	actin_calc.h
 * @brief	‰‰‹Z—Í•”–åF‹ZŒø‰ÊŒvZ‚È‚Ç‚Ìƒwƒbƒ_
 * @author	matsuda
 * @date	2005.12.07(…)
 */
//==============================================================================
#ifndef __ACTIN_CALC_H__
#define __ACTIN_CALC_H__


//==============================================================================
//	ŠO•”ŠÖ”éŒ¾
//==============================================================================
extern int ACALC_BaseAppealGet(int wazano);
extern int ACALC_JudgeSufferCheck(ACTIN_GAME_PARAM *a_game, int check_breeder);
extern int ACALC_JudgeSufferPointCheck(int suffer_num);
extern int ACALC_VoltageUpDownCheck(int contest_type, int wazano, int judge_no, 
	int special_judge_no);
extern void ACALC_BreederSort(ACTIN_GAME_PARAM *a_game);


#endif	//__ACTIN_CALC_H__

