//============================================================================================
/**
 * @file	demo_ending_list.h
 * @brief	エンディングデモ　スタッフリスト処理
 * @author	taya
 * @date	2006.05.22
 */
//============================================================================================
#ifndef __DEMO_ENDING_LIST_H__
#define __DEMO_ENDING_LIST_H__

#include "system\msgdata.h"



typedef struct _ENDING_LIST_WORK	ENDING_LIST_WORK;



extern ENDING_LIST_WORK* Ending_ListWork_Create( GF_BGL_INI* bgl, int startLine, int bgFrame, int palPos, MSGDATA_MANAGER* msgMan );
extern void Ending_ListWork_Delete( ENDING_LIST_WORK* wk );
extern BOOL Ending_ListWork_Scroll( ENDING_LIST_WORK* wk, int height );


extern void Ending_ListWork_WriteEndStr( ENDING_LIST_WORK* wk, BOOL fillFlag );
extern void Ending_ListWork_WriteCopyLights( ENDING_LIST_WORK* wk );

#endif  /* __DEMO_ENDING_LIST_H__ */
