//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_wnd.h
 *@brief	ウィンドウ操作の関数をパックした関数郡
 *@author	tomoya takahashi
 *@data		2005.08.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WIPE_WND_H__
#define __WIPE_WND_H__

#undef GLOBAL
#ifdef	__WIPE_WND_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	メイン画面か　サブ画面か
//	
//=====================================
enum {
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
} ;

//-------------------------------------
//	
//	ウィンドウナンバー
//	
//=====================================
enum {
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
} ;


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	Vblank関数用の引数
//	
//=====================================
//-------------------------------------
//	
//	表示ウィンドウの設定
//	
//=====================================
typedef struct {
	int wnd;		// 表示させるウィンドウ
	int disp;		// 表示面（メイン・サブ）
} WNDP_VISIBLE_PARAM;

//-------------------------------------
//	
//	ウィンドウ内のBG・OBJの設定
//	
//=====================================
typedef struct {
	int wnd;		// ウィンドウ内に表示させるBG・OBJのマスク
	BOOL effect;	// エフェクトの有無
	int wnd_no;		// ウィンドウナンバー
	int disp;		// 表示面（メイン・サブ）
} WNDP_INSIDE_PARAM;

//-------------------------------------
//	
//	オブジェウィンドウ内の設定
//	
//=====================================
typedef struct {
	int wnd;		// ウィンドウ内に表示させるBG・OBJのマスク
	BOOL effect;	// エフェクトの有無
	int disp;		// 表示面（メイン・サブ）
} WNDP_OBJINSIDE_PARAM;

//-------------------------------------
//	
//	ウィンドウ外のBG・OBJの設定
//	
//=====================================
typedef struct {
	int wnd;		// ウィンドウ内に表示させるBG・OBJのマスク
	BOOL effect;	// エフェクトの有無
	int disp;		// 表示面（メイン・サブ）
} WNDP_OUTSIDE_PARAM;

//-------------------------------------
//	
//	ウィンドウの大きさ形の設定
//	
//=====================================
typedef struct {
	short x1;		// 座標X(0->255)
	short y1;		// 座標Y(0->192)
	short x2;		// 座標X(0->255)
	short y2;		// 座標Y(0->192)
	int wnd_no;		// ウィンドウ内に表示させるBG・OBJのマスク
	int disp;		// 表示面（メイン・サブ）
} WNDP_POSITION_PARAM;

//-------------------------------------
//	
//	ウィンドウVblankシステムデータ
//	Vblankタスク用のワークを先に用意
//	しておく
//	
//=====================================
typedef struct _WNDP_SYS{
	WNDP_VISIBLE_PARAM		visible[2];		// 表示非表示設定（メイン・サブ）
	WNDP_INSIDE_PARAM		in_wnd[2][2];	// ウィンドウ内の設定(メイン・サブ【ウィンドウ０・ウィンドウ１】)
	WNDP_OBJINSIDE_PARAM	obj_in_wnd[2];	// オブジェウィンドウ内の設定（メイン・サブ）
	WNDP_OUTSIDE_PARAM		out_wnd[2];		// ウィンドウ外の設定（メイン・サブ）
	WNDP_POSITION_PARAM		position[2][2];	// ポジションの設定（メイン・サブ）
} WNDP_SYS;

//-------------------------------------
//	
//	ウィンドウVBlankシステムポインタ
//	Vblank中のウィンドウデータの設定時
//	にのみ必要なワークデータです。
//	
//=====================================
typedef struct _WNDP_SYS* WNDP_SYS_PTR;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
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
 * window
	GX_WNDMASK_NONE = 0x00,		なし
    GX_WNDMASK_W0 = 0x01,		ウィンドウ０
    GX_WNDMASK_W1 = 0x02,		ウィンドウ１
    GX_WNDMASK_OW = 0x04		オブジェウィンドウ
 * 
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetVisibleWnd(int window, int disp); 

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
 * window
	GX_WNDMASK_NONE = 0x00,		なし
    GX_WNDMASK_W0 = 0x01,		ウィンドウ０
    GX_WNDMASK_W1 = 0x02,		ウィンドウ１
    GX_WNDMASK_OW = 0x04		オブジェウィンドウ
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetVisibleWnd(WNDP_SYS_PTR sys, int window, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示・非表示を取得
 *
 *@param	disp	表示面
 *
 *@return	今設定されているウィンドウマスクのフラグ
 *
 * return
	GX_WNDMASK_NONE = 0x00,		なし
    GX_WNDMASK_W0 = 0x01,		ウィンドウ０
    GX_WNDMASK_W1 = 0x02,		ウィンドウ１
    GX_WNDMASK_OW = 0x04		オブジェウィンドウ
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int WNDP_GetVisibleWnd(int disp);  

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * wnd_no
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndInsidePlane(int wnd, BOOL effect, int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの内側に入るBG	Vblankで行う
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		内側に入るBG
 *@param	effect	内側のBGにエフェクトがあるか
 *@param	wnd_no	ウィンドウナンバー
 *@param	disp	表示面
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * wnd_no
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int wnd_no, int disp);

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndOutsidePlane(int wnd, BOOL effect, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの外側に来るBGの設定	VBlankで行う
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		外側に来るBG
 *@param	effect	外側に来るBGにエフェクトがかかっているか
 *@param	disp	表示面
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndOutsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp);

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
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * wnd_no
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndInsidePlane(int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの外側のBGを取得
 *
 *@param	disp	表示面
 *
 *@return	GXWndPlane
 *
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndOutsidePlane(int disp);

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndOBJInsidePlane(int wnd, BOOL effect, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	objウィンドウの内側に来るBGを設定	VBlankで行う
 *
 *@param	sys		Vblank用システムデータ
 *@param	wnd		内側に来るBG
 *@param	effect	内側に来るBGにエフェクトがかかるか
 *@param	disp	表示面
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndOBJInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェウィンドウの内側のBGを取得
 *
 *@param	disp	表示面
 *
 *@return	GXWndPlane
 *
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		なし
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndOBJInsidePlane(int disp);

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
 * wnd_no
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndPosition(int x1, int y1, int x2, int y2, int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの表示位置とサイズを設定	Vblankで行う
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
 * wnd_no
	WNDP_WND_0,		// ウィンドウ０
	WNDP_WND_1		// ウィンドウ１
 *
 * disp
	WNDP_DISP_MAIN,		// メイン面
	WNDP_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndPosition(WNDP_SYS_PTR sys, int x1, int y1, int x2, int y2, int wnd_no, int disp);


#undef	GLOBAL
#endif		// __WIPE_WND_H__

