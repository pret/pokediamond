//=============================================================================
/**
 * @file	title.h
 * @brief
 * @author	GAME FREAK inc.
 */
//=============================================================================

#ifndef	__TITLE_H__
#define	__TITLE_H__

#include "system/procsys.h"

extern const PROC_DATA TitleProcData;
extern const PROC_DATA StartMenuProcData;		// system/startmenu.c

#ifdef	PM_DEBUG
//��p�̃w�b�_��p�ӂ���قǂł͂Ȃ��̂ŁA�Ԏ؂肵�Ă܂�
extern const PROC_DATA SoundTestProcData;		//debug/snd_test.c
extern const PROC_DATA PokeGraTestProcData;		//debug/poke_test.c
extern const PROC_DATA TrGraTestProcData;		//debug/tr_test.c
extern const PROC_DATA DebugTitleMenuProcData;	//debug/d_title.c
extern const PROC_DATA DebugStartMenuProcData;	//debug/d_startmenu.c
extern const PROC_DATA DebugFightProcData;		//debug/d_fight.c
extern const PROC_DATA DebugPersonMenuProcData;	//debug/d_person_menu.c
extern const PROC_DATA DebugRtcMenuProcData;	//debug/d_rtcmenu.c
#endif


#endif	//	__TITLE_H__
