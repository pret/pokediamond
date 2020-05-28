//==============================================================================
/**
 * @file	actin_param.h
 * @brief	演技力部門で企画側でいじりそうな定義を抜き出しておく為の場所
 * @author	matsuda
 * @date	2006.02.11(土)
 */
//==============================================================================
#ifndef __ACTIN_PARAM_H__
#define __ACTIN_PARAM_H__


///審判コメントレベル(数値以下だとそのレベルになる)
enum{
	JUDGE_COMMENT_LEVEL_0 = 0,		///<最も低い評価
	JUDGE_COMMENT_LEVEL_1 = 20,		
	JUDGE_COMMENT_LEVEL_2 = 50,
	JUDGE_COMMENT_LEVEL_3 = 90,
	JUDGE_COMMENT_LEVEL_4 = 30000,	///<最も高い評価
};


#endif	//__ACTIN_PARAM_H__

