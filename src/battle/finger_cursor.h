//==============================================================================
/**
 * @file	finger_cursor.h
 * @brief	戦闘指カーソル
 * @author	matsuda
 * @date	2006.06.13(火)
 */
//==============================================================================
#ifndef __FINGER_CURSOR_H__
#define __FINGER_CURSOR_H__


//==============================================================================
//	型定義
//==============================================================================
///FINGER_WORKの不定形ポインタ
typedef struct _FINGER_WORK * FINGER_PTR;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void FINGER_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern void FINGER_ResourceFree(
	CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern FINGER_PTR FINGER_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
extern void FINGER_ActorDelete(FINGER_PTR finger);
extern void FINGER_PosSetON_Surface(FINGER_PTR finger, int x, int y, fx32 surface_y);
extern void FINGER_PosSetON(FINGER_PTR finger, int x, int y);
extern void FINGER_OFF(FINGER_PTR finger);
extern void FINGER_TouchReq(FINGER_PTR finger, int wait);
extern BOOL FINGER_TouchAnimeCheck(FINGER_PTR finger);


#endif	//__FINGER_CURSOR_H__

