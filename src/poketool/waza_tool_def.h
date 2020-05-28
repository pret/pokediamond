
//============================================================================================
/**
 * @file	waza_tool_def.h
 * @bfief	技パラメータツール郡
 * @author	HisashiSogabe
 * @date	05.08.25
 */
//============================================================================================

#include "contest/contest.h"

struct waza_table_data
{
	u16				battleeffect;
	u8				kind;
	u8				damage;

	u8				wazatype;
	u8				hitprobability;
	u8				pp;
	u8				addeffect;

	u16				attackrange;
	s8				attackpri;
	u8				flag;

	CONWAZA_DATA	condata;
};

