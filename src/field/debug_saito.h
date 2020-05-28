#ifndef __DEBUG_SAITO_H__
#define __DEBUG_SAITO_H__

#ifdef	DEBUG_ONLY_FOR_saitou
#define	OS_Printf_saitou(...)	OS_Printf(__VA_ARGS__);
#else
#define	OS_Printf_saitou(...)	/* DO NOTHING! */
#endif

#ifdef PM_DEBUG
#define	HERO_HEIGHT_CHANGE

extern void DBGSAI_MapNumDebugListSet(struct _FIELDSYS_WORK * fsys);
///extern void MotionBlurTest(void);
///extern BOOL IsMotionBlur(void);
///extern void DBGSAI_JumpMapControl(struct _FIELDSYS_WORK * fsys);
extern void DBGSAI_CheckAttribute(struct _FIELDSYS_WORK * fsys);

#endif	//PM_DEBUG

#endif //__DEBUG_SAITO_H__
