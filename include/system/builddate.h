//=============================================================================
/**
 * @file	builddate.h
 * @brief	�\�[�X�t�@�C���S�ʂɕύX���������make������悤�ɂ��Ă���
 * @author	Katsumi Ohno
 * @date    2005.10.03
 */
//=============================================================================

#ifndef __BUILDDATE_H__
#define __BUILDDATE_H__

//#include "system/pm_str.h"

#include "system/wordset.h"

extern char BuildDate[];
extern char BuildTime[];
extern void DebugBuildTimeDisp(void);
extern void WORDSET_DebugBuildTime(WORDSET * ws);
//extern void DebugGetBuildTime(STRCODE* buf);


#endif //__BUILDDATE_H__

