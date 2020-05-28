//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_wnd.c
 *@brief	ウィンドウ操作の関数をパックした関数郡
 *@author	tomoya takahashi 
 *@data		2005.08.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#define	__WIPE_WND_H_GLOBAL
#include "system/wipe_wnd.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void wndp_v_SetVisibleWnd(TCB_PTR tcb, void* data);
static void wndp_v_SetWndInsidePlane(TCB_PTR tcb, void* data);
static void wndp_v_SetWndOutsidePlane(TCB_PTR tcb, void* data);
static void wndp_v_SetWndOBJInsidePlane(TCB_PTR tcb, void* data);
static void wndp_v_SetWndPosition(TCB_PTR tcb, void* data);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示・非表示
 *
 *@param	window	表示させるウィンドウ
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_SetVisibleWnd(int window, int disp)
{
	if(disp == WNDP_DISP_MAIN){
		GX_SetVisibleWnd(window);
	}else{
		GXS_SetVisibleWnd(window);
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示・非表示を取得
 *
 *@param	disp	表示面
 *
 *@return	int
 *
 *
 */
//-----------------------------------------------------------------------------
int WNDP_GetVisibleWnd(int disp)
{
	int ret;
	if(disp == WNDP_DISP_MAIN){
		ret = GX_GetVisibleWnd();
	}else{
		ret = GXS_GetVisibleWnd();
	}
	return ret;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの内側に入るBG
 *
 *@param	wnd		内側に入るBG
 *@param	effect	内側のBGにエフェクトがあるか
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_SetWndInsidePlane(int wnd, BOOL effect, int wnd_no, int disp)
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			G2_SetWnd0InsidePlane(wnd, effect);
		}else{
			G2S_SetWnd0InsidePlane(wnd, effect);
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			G2_SetWnd1InsidePlane(wnd, effect);
		}else{
			G2S_SetWnd1InsidePlane(wnd, effect);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの外側に来るBGの設定
 *
 *@param	wnd		外側に来るBG
 *@param	effect	外側に来るBGにエフェクトがかかっているか
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_SetWndOutsidePlane(int wnd, BOOL effect, int disp)
{
	if(disp == WNDP_DISP_MAIN){
		G2_SetWndOutsidePlane(wnd, effect);
	}else{
		G2S_SetWndOutsidePlane(wnd, effect);
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの内側のBGを取得
 *
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	GXWndPlane
 *
 *
 */
//-----------------------------------------------------------------------------
GXWndPlane WNDP_GetWndInsidePlane(int wnd_no, int disp)
{
	GXWndPlane num;
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			num = G2_GetWnd0InsidePlane();
		}else{
			num = G2S_GetWnd0InsidePlane();
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			num = G2_GetWnd1InsidePlane();
		}else{
			num = G2S_GetWnd1InsidePlane();
		}
	}
	
	return num;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの外側のBGを取得
 *
 *@param	disp	表示面
 *
 *@return	GXWndPlane
 *
 *
 */
//-----------------------------------------------------------------------------
GXWndPlane WNDP_GetWndOutsidePlane(int disp)
{
	GXWndPlane num;
	if(disp == WNDP_DISP_MAIN){
		num = G2_GetWndOutsidePlane();
	}else{
		num = G2S_GetWndOutsidePlane();
	}
	return num;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	objウィンドウの内側に来るBGを設定
 *
 *@param	wnd		内側に来るBG
 *@param	effect	内側に来るBGにエフェクトがかかるか
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_SetWndOBJInsidePlane(int wnd, BOOL effect, int disp)
{
	if(disp == WNDP_DISP_MAIN){
		G2_SetWndOBJInsidePlane(wnd, effect);
	}else{
		G2S_SetWndOBJInsidePlane(wnd, effect);
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェウィンドウの内側のBGを取得
 *
 *@param	disp	表示面
 *
 *@return	GXWndPlane
 *
 *
 */
//-----------------------------------------------------------------------------
GXWndPlane WNDP_GetWndOBJInsidePlane(int disp)
{
	GXWndPlane num;
	if(disp == WNDP_DISP_MAIN){
		num = G2_GetWndOBJInsidePlane();
	}else{
		num = G2S_GetWndOBJInsidePlane();
	}
	return num;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示位置とサイズを設定
 *	
 *@param	x1	左位置
 *@param	y1	上位置
 *@param	x2	右位置
 *@param	y2	下位置
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_SetWndPosition(int x1, int y1, int x2, int y2, int wnd_no, int disp)
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			G2_SetWnd0Position(x1,y1,x2,y2);
		}else{
			G2S_SetWnd0Position(x1,y1,x2,y2);
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			G2_SetWnd1Position(x1,y1,x2,y2);
		}else{
			G2S_SetWnd1Position(x1,y1,x2,y2);
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示・非表示Vblankで行う
 *
 *@param	sys		Vblank用システムデータ
 *@param	window	表示させるウィンドウ
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_V_SetVisibleWnd(WNDP_SYS_PTR sys, int window, int disp)
{
	WNDP_VISIBLE_PARAM* wvp;
	wvp = &sys->visible[disp];
	wvp->wnd = window;
	wvp->disp = disp;
	VWaitTCB_Add(wndp_v_SetVisibleWnd,wvp,1);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの内側に入るBG
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		内側に入るBG
 *@param	effect	内側のBGにエフェクトがあるか
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_V_SetWndInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int wnd_no, int disp)
{
	WNDP_INSIDE_PARAM* wip;

	wip = &sys->in_wnd[disp][wnd_no];
	wip->wnd	= wnd;
	wip->effect = effect;
	wip->wnd_no	= wnd_no;
	wip->disp	= disp;
	VWaitTCB_Add( wndp_v_SetWndInsidePlane, wip, 1);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの外側に来るBGの設定
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		外側に来るBG
 *@param	effect	外側に来るBGにエフェクトがかかっているか
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_V_SetWndOutsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp)
{
	WNDP_OUTSIDE_PARAM* wop;

	wop = &sys->out_wnd[disp];
	wop->wnd	= wnd;
	wop->effect = effect;
	wop->disp	= disp;
	VWaitTCB_Add(wndp_v_SetWndOutsidePlane, wop, 1);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	objウィンドウの内側に来るBGを設定
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		内側に来るBG
 *@param	effect	内側に来るBGにエフェクトがかかるか
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_V_SetWndOBJInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp)
{
	WNDP_OBJINSIDE_PARAM* woip;

	woip = &sys->obj_in_wnd[disp];
	woip->wnd	= wnd;
	woip->effect = effect;
	woip->disp	= disp;
	VWaitTCB_Add(wndp_v_SetWndOBJInsidePlane, woip, 1);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示位置とサイズを設定
 *	
 *@param	sys		Vblank用システムデータ
 *@param	x1	左位置
 *@param	y1	上位置
 *@param	x2	右位置
 *@param	y2	下位置
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WNDP_V_SetWndPosition(WNDP_SYS_PTR sys, int x1, int y1, int x2, int y2, int wnd_no, int disp)
{
	WNDP_POSITION_PARAM* wpp;

	wpp = &sys->position[disp][wnd_no];
	wpp->x1		= x1;
	wpp->y1		= y1;
	wpp->x2		= x2;
	wpp->y2		= y2;
	wpp->wnd_no	= wnd_no;
	wpp->disp	= disp;
	VWaitTCB_Add(wndp_v_SetWndPosition, wpp, 1);
}






//----------------------------------------------------------------------------
/**
 *
 *@brief	表示ウィンドウの設定をVblankタスクで行う
 *
 *@param	tcb		タスクポインタ
 *@param	data	WNDP_VISIBLE_PARAM型のデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void wndp_v_SetVisibleWnd(TCB_PTR tcb, void* data)
{
	WNDP_VISIBLE_PARAM* wvp = (WNDP_VISIBLE_PARAM*)data;
	WNDP_SetVisibleWnd(wvp->wnd, wvp->disp);

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ内の設定をVblankタスクで行う
 *
 *@param	tcb		タスクポインタ
 *@param	data	WNDP_INSIDE_PARAM型のデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void wndp_v_SetWndInsidePlane(TCB_PTR tcb, void* data)
{
	WNDP_INSIDE_PARAM* wip = (WNDP_INSIDE_PARAM*)data;
	WNDP_SetWndInsidePlane(wip->wnd, wip->effect, wip->wnd_no, wip->disp);

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ外の設定をVblankタスクで行う
 *
 *@param	tcb		タスクポインタ
 *@param	data	WNDP_OUTSIDE_PARAM型のデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void wndp_v_SetWndOutsidePlane(TCB_PTR tcb, void* data)
{
	WNDP_OUTSIDE_PARAM* wop = (WNDP_OUTSIDE_PARAM*)data;
	WNDP_SetWndOutsidePlane(wop->wnd, wop->effect, wop->disp);

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ外の設定をVblankタスクで行う
 *
 *@param	data	WNDP_OBJINSIDE_PARAM型のデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void wndp_v_SetWndOBJInsidePlane(TCB_PTR tcb, void* data)
{
	WNDP_OBJINSIDE_PARAM* woip = (WNDP_OBJINSIDE_PARAM*)data;
	WNDP_SetWndOBJInsidePlane(woip->wnd, woip->effect, woip->disp);

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウポジションの設定をVblankタスクで行う
 *
 *@param	data	WNDP_POSITION_PARAM型のデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void wndp_v_SetWndPosition(TCB_PTR tcb, void* data)
{
	WNDP_POSITION_PARAM* wpp = (WNDP_POSITION_PARAM*)data;
	WNDP_SetWndPosition(wpp->x1,wpp->y1,wpp->x2,wpp->y2,wpp->wnd_no, wpp->disp);

	TCB_Delete( tcb );
}
