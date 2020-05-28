//============================================================================================
/**
 * @file	pmsiv_tool.h
 * @bfief	簡易会話入力画面（描画下請け共有ツール）
 * @author	taya
 * @date	06.02.13
 */
//============================================================================================
#ifndef __PMSIV_TOOL_H__
#define __PMSIV_TOOL_H__

#include "gflib\bg_system.h"
#include "gflib\tcb.h"



//======================================================================
//======================================================================
typedef struct {
	int  plane1;
	int  plane2;

	int  ev;
	int  ev_end;
	int  ev_step;
	int  wait;

	int  seq;
	TCB_PTR  tcb;

}PMSIV_TOOL_BLEND_WORK;

enum {
	PMSIV_BLEND_MAX = 124,

	PMSIV_BLDY_MAX = 16,
};


//------------------------------------------------------------------
/**
 * 半透明フェードエフェクト開始
 *
 * @param   wk			ワークポインタ
 * @param   plane1		
 * @param   plane2		
 * @param   start		
 * @param   end		
 * @param   wait		
 *
 */
//------------------------------------------------------------------
extern void PMSIV_TOOL_SetupBlendWork( PMSIV_TOOL_BLEND_WORK* wk, int plane1, int plane2, int start, int end, int wait );
extern BOOL PMSIV_TOOL_WaitBlend( PMSIV_TOOL_BLEND_WORK* wk );

//------------------------------------------------------------------
/**
 * 輝度エフェクト開始
 *
 * @param   wk		
 * @param   bg_plane		
 * @param   start		
 * @param   end		
 * @param   wait		
 *
 * @retval  extern void		
 */
//------------------------------------------------------------------
extern void PMSIV_TOOL_SetupBrightWork( PMSIV_TOOL_BLEND_WORK* wk, int bg_plane, int start, int end, int wait );
extern BOOL PMSIV_TOOL_WaitBright( PMSIV_TOOL_BLEND_WORK* wk );



//======================================================================
//======================================================================
enum PMSIV_TOOL_SCROLL_DIRECTION {
	PMSIV_TOOL_SCROLL_DIRECTION_X,
	PMSIV_TOOL_SCROLL_DIRECTION_Y,
};


typedef struct {
	GF_BGL_INI*                bgl;

	u32   bg_frame;
	int   scroll_param;
	fx32  pos;
	fx32  end_pos;
	fx32  add_value;
	u16   timer;
	u16   seq;

	TCB_PTR  tcb;


}PMSIV_TOOL_SCROLL_WORK;

extern void PMSIV_TOOL_SetupScrollWork( PMSIV_TOOL_SCROLL_WORK* wk, GF_BGL_INI* bgl, u32 bg_frame, int direction, int vector, int wait );
extern BOOL PMSIV_TOOL_WaitScroll( PMSIV_TOOL_SCROLL_WORK* wk );




#endif

