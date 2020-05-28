//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		scr_nagisa_scope.h
 *	@brief		ナギサシティ　灯台望遠鏡
 *	@author		tomoya takahashi
 *	@data		2006.07.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __SCR_NAGISA_SCOPE_H__
#define __SCR_NAGISA_SCOPE_H__

#include "field_common.h"

#undef GLOBAL
#ifdef	__SCR_NAGISA_SCOPE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

GLOBAL void CallNagisaScopeEvent(FIELDSYS_WORK * fsys);


#undef	GLOBAL
#endif		// __SCR_NAGISA_SCOPE_H__

