//============================================================================================
/**
 * @file	ug_base_bmp.h
 * @brief	îÈñßäÓínBMPèàíu
 * @author	saito
 * @date	2006.02.28
 *
 */
//============================================================================================
#ifndef __UG_BASE_BMP_H__
#define __UG_BASE_BMP_H__

#include "common.h"
#include "../field_common.h"

#define LIST_CANCEL_CODE	(0xfffffffe)

typedef	struct UG_BASE_MENU_tag UG_BASE_MENU;
typedef	struct UG_BASE_LIST_tag UG_BASE_LIST;

extern UG_BASE_MENU * BMENU_AllocUgBaseMenu(void);
extern void BMENU_InitBaseMainMenu(	UG_BASE_MENU *menu, FIELDSYS_WORK * fsys,
									u16 *pStartLine,  u16 *pCurPos);
extern void BMENU_FreeUgBaseMenu(UG_BASE_MENU *menu);
extern const u32 BMENU_GetReturnIndex(UG_BASE_MENU *menu);
extern BOOL BMENU_EditMainMenuControl(UG_BASE_MENU *outMenu);

extern UG_BASE_LIST * BMENU_AllocUgBaseGoodsList(void);
extern void BMENU_InitBaseGoodsList(UG_BASE_LIST *list, FIELDSYS_WORK * fsys,
									u16 *pStartLine, u16 *pCurPos);
extern void BMENU_SetGoodsNumToList(UG_BASE_LIST *list, const u8 inNum, const u8 inLimit);
extern void BMENU_FreeUgBaseGoodsList(UG_BASE_LIST *list);
extern const u32 BMENU_GetReturnListIdx(UG_BASE_LIST *list);
extern BOOL BMENU_EditGoodsListControl(UG_BASE_LIST *outList);
#endif //__UG_BASE_BMP_H__
