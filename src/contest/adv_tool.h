//==============================================================================
/**
 * @file	adv_tool.h
 * @brief	コンテスト全部門共通ツールのヘッダ
 * @author	matsuda
 * @date	2006.02.02(木)
 */
//==============================================================================
#ifndef __ADV_TOOL_H__
#define __ADV_TOOL_H__

#include "system/fontoam.h"
#include "contest_type.h"


//==============================================================================
//	定数定義
//==============================================================================
///カメラのフラッシュ：ループ無限
#define ADV_FLASH_EFF_LOOP_ETERNITY		(0xff)


//==============================================================================
//	構造体定義
//==============================================================================
///フォントOAM用の構造体定義
typedef struct{
	FONTOAM_OBJ_PTR fontoam;		///<フォントOAM
	CHAR_MANAGER_ALLOCDATA cma;		///<フォントOAMキャラ領域データ
	u16 len;						///<フォントのドット長
}ADV_FONTACT;


///フラッシュエフェクト制御ワーク
typedef struct{
	TCB_PTR tcb;		///<フラッシュエフェクト動作タスクのポインタ
	PALETTE_FADE_PTR pfd;	///<
	s32 timer;			///<タイマーカウント
	const u16 *tbl;		///<フラッシュのウェイトが入っているテーブルへのポインタ
	u8 tbl_num;			///<tblの配列要素数
	u8 tbl_pos;			///<現在のテーブル参照位置
	u8 loop;			///<ループ回数
}ADV_FLASH_EFF_WORK;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void ADV_FontOamCreate(int heap_id, GF_BGL_INI *bgl, CATS_RES_PTR crp, 
	FONTOAM_SYS_PTR fontoam_sys, ADV_FONTACT *fontact, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, int bg_pri, int soft_pri);
extern void ADV_FontOamDelete(ADV_FONTACT *fontact);
extern void ADV_FontOamPosSet(ADV_FONTACT *fontact, int x, int y, int pos_center);
extern STRBUF * ADV_MSGDAT_GetJudgeName(u32 judge_name_id, u32 heap_id);
extern void ADV_ClipScoreCalc(CONTEST_SYSTEM *consys, int heap_id);
extern void ADV_BPScoreCalc(CONTEST_SYSTEM *consys);
extern void ADV_FlowerResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int char_id, int pltt_id, int cell_id, int anm_id);
extern void ADV_FlowerResourceFree(CATS_RES_PTR crp, 
	int char_id, int pltt_id, int cell_id, int anm_id);
extern void ADV_FlowerActorAddAll(FLOWER_WORK *flower, CATS_SYS_PTR csp, CATS_RES_PTR crp,	
	int char_id, int pltt_id, int cell_id, int anm_id, 
	int pal_offset, int soft_pri, int bg_pri, u32 tcb_pri);
extern void ADV_FlowerActorDelAll(FLOWER_WORK *flower);
extern GF_G3DMAN * ADV_Contest_3D_Init(int heap_id);
extern void ADV_Contest_3D_Exit(GF_G3DMAN *g3Dman);
extern ADV_FLASH_EFF_WORK * ADV_FlashEffectTaskSet(int heap_id, PALETTE_FADE_PTR pfd, 
	const u16 *tbl, int tbl_num, int loop, u32 tcb_pri);
extern void ADV_FlashEffectTaskDel(ADV_FLASH_EFF_WORK *flash);
extern BOOL ADV_FlashEffectCheck(void);


#endif	//__ADV_TOOL_H__
