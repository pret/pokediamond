//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_wnd.c
 *@brief	�E�B���h�E����̊֐����p�b�N�����֐��S
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
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
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
 *@brief	�E�B���h�E�̕\���E��\��
 *
 *@param	window	�\��������E�B���h�E
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̕\���E��\�����擾
 *
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̓����ɓ���BG
 *
 *@param	wnd		�����ɓ���BG
 *@param	effect	������BG�ɃG�t�F�N�g�����邩
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̊O���ɗ���BG�̐ݒ�
 *
 *@param	wnd		�O���ɗ���BG
 *@param	effect	�O���ɗ���BG�ɃG�t�F�N�g���������Ă��邩
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̓�����BG���擾
 *
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̊O����BG���擾
 *
 *@param	disp	�\����
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
 *@brief	obj�E�B���h�E�̓����ɗ���BG��ݒ�
 *
 *@param	wnd		�����ɗ���BG
 *@param	effect	�����ɗ���BG�ɃG�t�F�N�g�������邩
 *@param	disp	�\����
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
 *@brief	�I�u�W�F�E�B���h�E�̓�����BG���擾
 *
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̕\���ʒu�ƃT�C�Y��ݒ�
 *	
 *@param	x1	���ʒu
 *@param	y1	��ʒu
 *@param	x2	�E�ʒu
 *@param	y2	���ʒu
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̕\���E��\��Vblank�ōs��
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	window	�\��������E�B���h�E
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̓����ɓ���BG
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�����ɓ���BG
 *@param	effect	������BG�ɃG�t�F�N�g�����邩
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̊O���ɗ���BG�̐ݒ�
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�O���ɗ���BG
 *@param	effect	�O���ɗ���BG�ɃG�t�F�N�g���������Ă��邩
 *@param	disp	�\����
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
 *@brief	obj�E�B���h�E�̓����ɗ���BG��ݒ�
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�����ɗ���BG
 *@param	effect	�����ɗ���BG�ɃG�t�F�N�g�������邩
 *@param	disp	�\����
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
 *@brief	�E�B���h�E�̕\���ʒu�ƃT�C�Y��ݒ�
 *	
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	x1	���ʒu
 *@param	y1	��ʒu
 *@param	x2	�E�ʒu
 *@param	y2	���ʒu
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
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
 *@brief	�\���E�B���h�E�̐ݒ��Vblank�^�X�N�ōs��
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	data	WNDP_VISIBLE_PARAM�^�̃f�[�^
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
 *@brief	�E�B���h�E���̐ݒ��Vblank�^�X�N�ōs��
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	data	WNDP_INSIDE_PARAM�^�̃f�[�^
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
 *@brief	�E�B���h�E�O�̐ݒ��Vblank�^�X�N�ōs��
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	data	WNDP_OUTSIDE_PARAM�^�̃f�[�^
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
 *@brief	�E�B���h�E�O�̐ݒ��Vblank�^�X�N�ōs��
 *
 *@param	data	WNDP_OBJINSIDE_PARAM�^�̃f�[�^
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
 *@brief	�E�B���h�E�|�W�V�����̐ݒ��Vblank�^�X�N�ōs��
 *
 *@param	data	WNDP_POSITION_PARAM�^�̃f�[�^
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
