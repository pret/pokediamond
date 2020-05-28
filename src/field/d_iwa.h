/**
 *	@file	d_iwa.h
 *	@brief	デバッグ岩澤ヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.06.01
 */

#ifndef __H_D_IWA_H__
#define __H_D_IWA_H__

//=============================
///	デバッグシステム制御用構造体
//=============================
typedef struct _DebugIwaWork{
	u8	ct;
	u8	work;
	u8	page;
	u8	task_id;
	int		wipe_f;
	void	*UserFunc;
	void	*RetFunc;
	void*	subWork;
	FIELDSYS_WORK	*fsys;

	u8		seq;
	u8		func_mode;
	u16		List;
	u16		Cursor;
	int		ret_x;
	int		ret_z;
	int		ret_zone;
	int		ret_val;
	BMPLIST_HEADER	bmplist_h;
	BMPLIST_WORK* blistWk; 
	BMPLIST_DATA* menulist; 

	GF_BGL_INI* pBglIni;
	GF_BGL_BMPWIN bmpwin;
}_DebugIwaWork;

extern void DebugMiyukiViewInit(_DebugIwaWork* wp,void* fsys,u8 list,u8 cursor);
extern void DebugMiyukiViewEnd(_DebugIwaWork* wp);
extern void DebugMiyukiFuncCall(TCB_PTR tcb,void* work);
extern void DebugMiyukiMain(TCB_PTR tcb,void* work);
extern void DebugMiyukiSubMenuWait(TCB_PTR tcb,void* work);

enum{
	DMSEQ_FADEOUT = 0,
	DMSEQ_FADEOUTWAIT,
	DMSEQ_FUNC,
	DMSEQ_FADEIN,
	DMSEQ_FADEINWAIT,
	DMSEQ_JUMPIN,
	DMSEQ_JUMPWAIT,
};

#endif	//__H_D_IWA_H__
