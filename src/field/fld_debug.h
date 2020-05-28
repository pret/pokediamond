//===========================================================================
/**
 *	@file	fld_debug.h
 *	@brief	�t�B�[���h�f�o�b�O���j���[���X�g�ݒ�
 *
 */
//===========================================================================

#ifndef _FLD_DEBUG_H_
#define _FLD_DEBUG_H_


#include "field/field.h"

#ifdef	PM_DEBUG
#define DEBUG_BG1_PRINT		// �t�B�[���h��ʂ�BG1�ʂɃf�o�b�O�������`��
#endif


//===========================================================================
/**
 *	@brief	�t�B�[���h�f�o�b�O���j���[���X�g�ݒ�
 *
 *	@param	none
 *	@retval	none
 */
//===========================================================================
extern void FieldDebugListSet(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
///	�f�o�b�O���j���[����RTC����Ăяo��
//------------------------------------------------------------------
extern void EventSet_DebugRtcCotrol(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
///	�f�o�b�O���j���[����e���r���e�\���Ăяo��
//------------------------------------------------------------------
extern void EventSet_TVDebugInfo(FIELDSYS_WORK * fsys);

//===========================================================================
//===========================================================================

#ifndef DEBUG_BG1_PRINT

#define	DEBUG_INIT_TICK()		/* �������Ȃ� */
#define	DEBUG_STORE_TICK(n)		/* �������Ȃ� */
#define DEBUG_CLEAR_TICK()		/* �������Ȃ� */

#define	DEBUG_VIEW_HOOK(n)		/* �������Ȃ� */

#define	DEBUG_ENTRY_STRESSPRINT_TASK(fsys)		/* �������Ȃ� */

#else

#define	DEBUG_INIT_TICK()		DEBUG_InitTick()
#define	DEBUG_STORE_TICK(n)		DEBUG_StoreTick(n)
#define DEBUG_CLEAR_TICK()		DEBUG_ClearMaxTick()

#define	DEBUG_VIEW_HOOK(n)		DebugStressDispHookSet(n)

#define	DEBUG_ENTRY_STRESSPRINT_TASK(fsys)	Debug_Entry_StressPrintTask(fsys)

extern void DebugBgPrint(GF_BGL_INI *ini,FIELDSYS_WORK *fsys);

extern void DEBUG_InitTick(void);
extern void DEBUG_StoreTick(int id);
extern void DEBUG_ClearMaxTick(void);
extern void DEBUG_PrintTickResult(GF_BGL_INI *ini,char * str, int x, int y);
extern void DebugStressDispHookSet(BOOL flag);

extern void DebugStressDispSet(const BOOL inFlg);

extern void Debug_EventSet_Tamada(FIELDSYS_WORK * fsys, int id);

extern void Debug_Entry_StressPrintTask(FIELDSYS_WORK * fsys);

extern void DEBUG_StoreTick2(int id);
extern void DEBUG_OS_PrintTick(void);

extern void DebugIchiCheckOn(FIELDSYS_WORK* fsys);

#endif	//DEBUG_BG1_PRINT


#endif	//_FLD_DEBUG_H_

