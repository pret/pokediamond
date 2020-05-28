//============================================================================================
/**
 * @file	field_subscreen.c
 * @brief	フィールドでのサブ画面制御
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================
#ifndef __FIELD_SUBSCREEN_H__
#define __FIELD_SUBSCREEN_H__

//============================================================================================
//============================================================================================
extern void FieldSubScreen_Init(FIELDSYS_WORK * fsys);
extern BOOL FieldSubScreen_WaitInit(FIELDSYS_WORK * fsys);
extern void FieldSubScreen_Quit(FIELDSYS_WORK * fsys);
extern BOOL FieldSubScreen_WaitQuit(FIELDSYS_WORK * fsys);

#endif /* __FIELD_SUBSCREEN_H__ */
