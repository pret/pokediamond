//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_wnd.h
 *@brief	�E�B���h�E����̊֐����p�b�N�����֐��S
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
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���C����ʂ��@�T�u��ʂ�
//	
//=====================================
enum {
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
} ;

//-------------------------------------
//	
//	�E�B���h�E�i���o�[
//	
//=====================================
enum {
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
} ;


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	Vblank�֐��p�̈���
//	
//=====================================
//-------------------------------------
//	
//	�\���E�B���h�E�̐ݒ�
//	
//=====================================
typedef struct {
	int wnd;		// �\��������E�B���h�E
	int disp;		// �\���ʁi���C���E�T�u�j
} WNDP_VISIBLE_PARAM;

//-------------------------------------
//	
//	�E�B���h�E����BG�EOBJ�̐ݒ�
//	
//=====================================
typedef struct {
	int wnd;		// �E�B���h�E���ɕ\��������BG�EOBJ�̃}�X�N
	BOOL effect;	// �G�t�F�N�g�̗L��
	int wnd_no;		// �E�B���h�E�i���o�[
	int disp;		// �\���ʁi���C���E�T�u�j
} WNDP_INSIDE_PARAM;

//-------------------------------------
//	
//	�I�u�W�F�E�B���h�E���̐ݒ�
//	
//=====================================
typedef struct {
	int wnd;		// �E�B���h�E���ɕ\��������BG�EOBJ�̃}�X�N
	BOOL effect;	// �G�t�F�N�g�̗L��
	int disp;		// �\���ʁi���C���E�T�u�j
} WNDP_OBJINSIDE_PARAM;

//-------------------------------------
//	
//	�E�B���h�E�O��BG�EOBJ�̐ݒ�
//	
//=====================================
typedef struct {
	int wnd;		// �E�B���h�E���ɕ\��������BG�EOBJ�̃}�X�N
	BOOL effect;	// �G�t�F�N�g�̗L��
	int disp;		// �\���ʁi���C���E�T�u�j
} WNDP_OUTSIDE_PARAM;

//-------------------------------------
//	
//	�E�B���h�E�̑傫���`�̐ݒ�
//	
//=====================================
typedef struct {
	short x1;		// ���WX(0->255)
	short y1;		// ���WY(0->192)
	short x2;		// ���WX(0->255)
	short y2;		// ���WY(0->192)
	int wnd_no;		// �E�B���h�E���ɕ\��������BG�EOBJ�̃}�X�N
	int disp;		// �\���ʁi���C���E�T�u�j
} WNDP_POSITION_PARAM;

//-------------------------------------
//	
//	�E�B���h�EVblank�V�X�e���f�[�^
//	Vblank�^�X�N�p�̃��[�N���ɗp��
//	���Ă���
//	
//=====================================
typedef struct _WNDP_SYS{
	WNDP_VISIBLE_PARAM		visible[2];		// �\����\���ݒ�i���C���E�T�u�j
	WNDP_INSIDE_PARAM		in_wnd[2][2];	// �E�B���h�E���̐ݒ�(���C���E�T�u�y�E�B���h�E�O�E�E�B���h�E�P�z)
	WNDP_OBJINSIDE_PARAM	obj_in_wnd[2];	// �I�u�W�F�E�B���h�E���̐ݒ�i���C���E�T�u�j
	WNDP_OUTSIDE_PARAM		out_wnd[2];		// �E�B���h�E�O�̐ݒ�i���C���E�T�u�j
	WNDP_POSITION_PARAM		position[2][2];	// �|�W�V�����̐ݒ�i���C���E�T�u�j
} WNDP_SYS;

//-------------------------------------
//	
//	�E�B���h�EVBlank�V�X�e���|�C���^
//	Vblank���̃E�B���h�E�f�[�^�̐ݒ莞
//	�ɂ̂ݕK�v�ȃ��[�N�f�[�^�ł��B
//	
//=====================================
typedef struct _WNDP_SYS* WNDP_SYS_PTR;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
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
 * window
	GX_WNDMASK_NONE = 0x00,		�Ȃ�
    GX_WNDMASK_W0 = 0x01,		�E�B���h�E�O
    GX_WNDMASK_W1 = 0x02,		�E�B���h�E�P
    GX_WNDMASK_OW = 0x04		�I�u�W�F�E�B���h�E
 * 
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetVisibleWnd(int window, int disp); 

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
 * window
	GX_WNDMASK_NONE = 0x00,		�Ȃ�
    GX_WNDMASK_W0 = 0x01,		�E�B���h�E�O
    GX_WNDMASK_W1 = 0x02,		�E�B���h�E�P
    GX_WNDMASK_OW = 0x04		�I�u�W�F�E�B���h�E
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetVisibleWnd(WNDP_SYS_PTR sys, int window, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̕\���E��\�����擾
 *
 *@param	disp	�\����
 *
 *@return	���ݒ肳��Ă���E�B���h�E�}�X�N�̃t���O
 *
 * return
	GX_WNDMASK_NONE = 0x00,		�Ȃ�
    GX_WNDMASK_W0 = 0x01,		�E�B���h�E�O
    GX_WNDMASK_W1 = 0x02,		�E�B���h�E�P
    GX_WNDMASK_OW = 0x04		�I�u�W�F�E�B���h�E
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int WNDP_GetVisibleWnd(int disp);  

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * wnd_no
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndInsidePlane(int wnd, BOOL effect, int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̓����ɓ���BG	Vblank�ōs��
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�����ɓ���BG
 *@param	effect	������BG�ɃG�t�F�N�g�����邩
 *@param	wnd_no	�E�B���h�E�i���o�[
 *@param	disp	�\����
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * wnd_no
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int wnd_no, int disp);

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndOutsidePlane(int wnd, BOOL effect, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̊O���ɗ���BG�̐ݒ�	VBlank�ōs��
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�O���ɗ���BG
 *@param	effect	�O���ɗ���BG�ɃG�t�F�N�g���������Ă��邩
 *@param	disp	�\����
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndOutsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp);

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
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * wnd_no
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndInsidePlane(int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̊O����BG���擾
 *
 *@param	disp	�\����
 *
 *@return	GXWndPlane
 *
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndOutsidePlane(int disp);

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
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndOBJInsidePlane(int wnd, BOOL effect, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	obj�E�B���h�E�̓����ɗ���BG��ݒ�	VBlank�ōs��
 *
 *@param	sys		Vblank�p�V�X�e���f�[�^
 *@param	wnd		�����ɗ���BG
 *@param	effect	�����ɗ���BG�ɃG�t�F�N�g�������邩
 *@param	disp	�\����
 *
 *@return	none
 *
 * wnd
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 * 
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndOBJInsidePlane(WNDP_SYS_PTR sys, int wnd, BOOL effect, int disp); 

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�E�B���h�E�̓�����BG���擾
 *
 *@param	disp	�\����
 *
 *@return	GXWndPlane
 *
 * return
	GX_WND_PLANEMASK_NONE = 0x0000,		�Ȃ�
    GX_WND_PLANEMASK_BG0 = 0x0001,		BG0
    GX_WND_PLANEMASK_BG1 = 0x0002,		BG1
    GX_WND_PLANEMASK_BG2 = 0x0004,		BG2
    GX_WND_PLANEMASK_BG3 = 0x0008,		BG3
    GX_WND_PLANEMASK_OBJ = 0x0010		OBJ
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXWndPlane WNDP_GetWndOBJInsidePlane(int disp);

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
 * wnd_no
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_SetWndPosition(int x1, int y1, int x2, int y2, int wnd_no, int disp);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̕\���ʒu�ƃT�C�Y��ݒ�	Vblank�ōs��
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
 * wnd_no
	WNDP_WND_0,		// �E�B���h�E�O
	WNDP_WND_1		// �E�B���h�E�P
 *
 * disp
	WNDP_DISP_MAIN,		// ���C����
	WNDP_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WNDP_V_SetWndPosition(WNDP_SYS_PTR sys, int x1, int y1, int x2, int y2, int wnd_no, int disp);


#undef	GLOBAL
#endif		// __WIPE_WND_H__

