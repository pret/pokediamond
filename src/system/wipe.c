//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe.c
 *@brief	DP��ʐ؂�ւ��V�X�e��
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <string.h>
#include "system.h"
#include "tcb.h"
#include "assert.h"
#include "system/lib_pack.h"
#include "system/wipe_wnd.h"
#include "include/system/brightness.h"
#include "include/gflib/sdkdef.h"

#define	__WIPE_H_GLOBAL
#include "system/wipe.h"
#define __WIPE_DEF_H_GLOBAL
#define __WIPE_DEF_H_GLOBAL_VAL
#include "system/wipe_def.h"
#include "system/wipe_sub.h"




//-------------------------------------
//	
//	Vblank���ɓo�^����f�[�^
//	
//=====================================
typedef struct {
	WIPE_HBLANK* p_wipehb;
	void*	work;
	pHBFunc	func;
	int		disp;
} WIPE_V_HBLANK;

//-------------------------------------
//	
//	vblank���ɔj������f�[�^
//	
//=====================================
typedef struct {
	WIPE_HBLANK* p_wipehb;
	int disp;
} WIPE_V_DELHBLANK;


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// ��ʐ؂�ւ��p�^�[���萔
enum{
	WIPE_THE_SAME_TIME = 0,		// ����
	WIPE_START_MAIN,			// ���C���J�n
	WIPE_START_SUB,				// �T�u�J�n
};


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	��ʐ؂�ւ��p�^�[���e�[�u��
//	
//=====================================
typedef struct {
	// ��ʐ؂�ւ��p�^�[���t���O
	int wipe_pattern;
	
	// ���C���T�u�̃��C�v�̑��݁A�񑶍݃t���O
	BOOL wipe_exist_m;	// ���C�v���I��������FALSE�ɂȂ��Ă��܂�	���C�v�I���������`�F�b�N�p
	BOOL wipe_exist_s;	// ���C�v���I��������FALSE�ɂȂ��Ă��܂�	���C�v�I�������������p

	BOOL wipe_exist_m_check;	// ���C�v���I�����Ă�TRUE�̂܂܂ł��B	���C�v���݃`�F�b�N�p
	BOOL wipe_exist_s_check;	// ���C�v���I�����Ă�TRUE�̂܂܂ł��B	���C�v���݃`�F�b�N�p
} WIPE_SYS_PATTERN_DATA;


//-------------------------------------
//	
//	�t�F�[�h�V�X�e���f�[�^
//	
//=====================================
typedef struct _WIPE_SYS_DATA{
	// �t�F�[�h�p�^�[���f�[�^
	WIPE_SYS_PATTERN_DATA	wipe_pattern_data;

	// ���C�v�f�[�^
	WIPE_SYS_WIPE_WORK	wipe_m;
	WIPE_SYS_WIPE_WORK	wipe_s;

	// HBlank���[�N
	WIPE_HBLANK			wipehb;

	// wndsys���[�N
	WNDP_SYS	wnd_sys;

	// ����t���O
	u16 move_flg;	
	u8 effect_flg_m;	// ��ʂɉ����e�����������Ă��邩
	u8 effect_flg_s;	// ��ʂɉ����e�����������Ă��邩

	// �t�F�[�h�A�E�g�J���[
	u16 fade_color;

} WIPE_SYS_DATA;	// size		316byte

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

static void endWipe(WIPE_SYS_DATA* scchg);
static void cleanWipeData( WIPE_SYS_DATA* p_wipe_data );

static void scchg_HBlankWorkSet( WIPE_HBLANK* p_wipehb );
static void scchg_HBlankFunc(void * work);
static void scchg_v_HBlankInit(TCB_PTR tcb, void* work);
static void scchg_v_HBlankDelete(TCB_PTR tcb, void* work);
static BOOL screenChangeSub(WIPE_SYS_PATTERN_DATA* pattern, WIPE_SYS_WIPE_WORK* wipe_m, WIPE_SYS_WIPE_WORK* wipe_s);

static void wipeFuncPack(BOOL* exist, WIPE_SYS_WIPE_WORK* wipe);
static BOOL wipeFunc(WIPE_SYS_WIPE_WORK* wipe);

static void setScreenChangePattern(int no, WIPE_SYS_PATTERN_DATA* pattern);
static void setWipeWork(WIPE_SYS_WIPE_WORK* wipe_w, int wipe_no, int division, int piece_sync, int sequence, void* work, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb,  int heap, u16 color);
static void patternDataSet(WIPE_SYS_PATTERN_DATA* pattern_data, int pattern, BOOL exist_m, BOOL exist_s);

static void setBackDropColor( u16 color );

static u16 getSetColor( WIPE_SYS_DATA* p_data, u16 color );
static u16 getSaveWiepColor( const WIPE_SYS_DATA* cp_data );
static void chgWnd_MstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data );
static void resetMstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data );


static BOOL WipeFadeInCheck( u32 wipe_type );

static void resetMstBrightnessVblank( TCB_PTR tcb, void* work );


//-----------------------------------------------------------------------------
/**
 *					�O���[�o���錾�錾
*/
//-----------------------------------------------------------------------------
const static pWIPEFunc WipeFunc[] = {
	WipeFunc00,
	WipeFunc01,
	WipeFunc02,
	WipeFunc03,
	WipeFunc04,
	WipeFunc05,
	WipeFunc06,
	WipeFunc07,
	WipeFunc08,
	WipeFunc09,
	WipeFunc10,
	WipeFunc11,
	WipeFunc12,
	WipeFunc13,
	WipeFunc14,
	WipeFunc15,
	WipeFunc16,
	WipeFunc17,
	WipeFunc18,
	WipeFunc19,
	WipeFunc20,
	WipeFunc21,
	WipeFunc22,
	WipeFunc23,
	WipeFunc24,
	WipeFunc25,
	WipeFunc26,
	WipeFunc27,
	WipeFunc28,
	WipeFunc29,
	WipeFunc30,
	WipeFunc31,
	WipeFunc32,
	WipeFunc33,
	WipeFunc34,
	WipeFunc35,
	WipeFunc36,
	WipeFunc37,
	WipeFunc38,
	WipeFunc39,
	WipeFunc40,
	WipeFunc41,
};

//-------------------------------------
//
//	���C�v�V�X�e�����[�N
//	316byte
//	
//	��̂̉�ʂŎg�p����V�X�e���̂���
//	�O���[�o���Ƀ��[�N�������Ƃɂ��܂���
//=====================================
static WIPE_SYS_DATA WipeSysWork;

//----------------------------------------------------------------------------
/**
 *@brief	��ʐ؂�ւ����C�v���J�n
 *
 *@param	pattern		�؂�ւ��p�^�[���ԍ�
 *@param	wipe_m		���C�v�@�@���C����ʃ��C�v�ԍ�
 *@param	wipe_s		���C�v�@�@�T�u��ʃ��C�v�ԍ�
 *@param	color		���C�v�̐F
 *@param	division	�e���C�v�����̕�����
 *@param	piece_sync	�e���C�v�̏����𕪊������P�Ђ̃V���N��
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_Start(int pattern, int wipe_m, int wipe_s, u16 color, int division, int piece_sync, int heap)
{
	WIPE_SYS_DATA* scw;
	u16 set_color;
	
	//"division �O�����ł�"
	GF_ASSERT(division);
	//"piece_sync �O�����ł�"
	GF_ASSERT(piece_sync);
	// ���쒆�Ȃ�Ƃ߂�
	GF_ASSERT( WipeSysWork.move_flg == FALSE );

	// ���[�N�|�C���^�ݒ�
	scw = &WipeSysWork;
	// ���[�N������
	cleanWipeData( scw );

	// �؂�ւ��p�^�[���f�[�^�쐬
	setScreenChangePattern(pattern, &scw->wipe_pattern_data);

	// HBlank���[�N�̏����ݒ�
	scchg_HBlankWorkSet( &scw->wipehb );

	// �ݒ�J���[�擾
	set_color = getSetColor( scw, color );
	
	// ���C�v���[�N�̍쐬
	setWipeWork(&scw->wipe_m, wipe_m, division, piece_sync, 0, NULL, WIPE_DISP_MAIN, &scw->wnd_sys, &scw->wipehb, heap, set_color);
	setWipeWork(&scw->wipe_s, wipe_s, division, piece_sync, 0, NULL, WIPE_DISP_SUB, &scw->wnd_sys, &scw->wipehb, heap, set_color);

	scw->move_flg	= TRUE;			// ���쒆�ɂ���	

	// �������֐������s
	// �P��ڂ̓���͏������ɂȂ��Ă���
	// ����������ŁA��ʂ̐ݒ�i�E�B���h�E�}�X�N�ō���������A�u���C�g�l�X�̏����ݒ�������Ȃ�����j
	// ������̂ł����ŌĂ�
	wipeFuncPack(&scw->wipe_pattern_data.wipe_exist_m, &scw->wipe_m);
	wipeFuncPack(&scw->wipe_pattern_data.wipe_exist_s, &scw->wipe_s);
		
	// �����t�F�[�h�C���̎��@�����@�����̂Ƃ��@�����@�E�B���h�E���g�p�������C�v
	// �Ȃ�΁A��ײ�Ƚ�ݒ��OFF����
	if( scw->wipe_pattern_data.wipe_exist_m_check ){
		resetMstBrightnessCheck_Do( &scw->wipe_m );
		scw->effect_flg_m = TRUE;
	}
	if( scw->wipe_pattern_data.wipe_exist_s_check ){
		resetMstBrightnessCheck_Do( &scw->wipe_s );
		scw->effect_flg_s = TRUE;
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	��ʐ؂�ւ����C�v���C���֐�
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_Main( void )
{
	WIPE_SYS_DATA* scw = &WipeSysWork;
	BOOL	ret;

	// ����t���O�������Ă���Ƃ��̂ݓ���
	if( scw->move_flg  ){
		ret = screenChangeSub(&scw->wipe_pattern_data, &scw->wipe_m, &scw->wipe_s);
		if(ret == TRUE){
			// ���C�v�I��
			endWipe( scw );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��ʐ؂�ւ����C�v�@�I���`�F�b�N
 *
 *	@param	none
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL WIPE_SYS_EndCheck( void )
{
	if( WipeSysWork.move_flg ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�̋����I��
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_ExeEnd( void )
{
	// HBLANK������
	WIPE_HBlankDelete( &WipeSysWork.wipehb, WIPE_DISP_MAIN );
	WIPE_HBlankDelete( &WipeSysWork.wipehb, WIPE_DISP_SUB );
	// WND���[�N�j��
	if( WipeSysWork.wipe_pattern_data.wipe_exist_m ){
		WipeSysWork.wipe_m.sequence = WIPE_END;	
	}
	if( WipeSysWork.wipe_pattern_data.wipe_exist_s ){
		WipeSysWork.wipe_s.sequence = WIPE_END;	
	}
	wipeFuncPack(&WipeSysWork.wipe_pattern_data.wipe_exist_m,
			&WipeSysWork.wipe_m);
	wipeFuncPack(&WipeSysWork.wipe_pattern_data.wipe_exist_s,
			&WipeSysWork.wipe_s);
	// ���C�v�I��
	WipeSysWork.move_flg = FALSE;	// ����OFF
	WipeSysWork.effect_flg_m = FALSE;
	WipeSysWork.effect_flg_s = FALSE;
	// ���[�N�̃N���A
	cleanWipeData( &WipeSysWork );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v����ʂɉe����^���Ă��邩�`�F�b�N
 *
 *	@retval	TRUE	���C�v��ԃN���A���Ă���
 *	@retval	FALSE	���C�v��ԃN���A����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL WIPE_SYS_EffectCheck( void )
{
	if( (WipeSysWork.effect_flg_m == TRUE) ||
		(WipeSysWork.effect_flg_s == TRUE) ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C�v��Ԃ���������
 *
 *	@param	disp	�������������
 *	@param	heap	�g�p����q�[�v
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 */
//-----------------------------------------------------------------------------
void WIPE_Reset( int disp )
{
	WIPE_ResetWndMask( disp );
	WIPE_ResetBrightness( disp );

	if( disp == WIPE_DISP_MAIN ){
		WipeSysWork.effect_flg_m = FALSE;
	}else{
		WipeSysWork.effect_flg_s = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�B���h�E�}�X�N��Ԃ���������
 *
 *	@param	disp	�������������
 *
 *	@return
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 * �����̊֐���
 *	 �n�[�h�E�F�A�E�B���h�E���g�p�������C�v����
 * �@�u���C�g�l�X���g�p�������C�v�Ɉڍs���鎞�ɁA
 * �@�n�[�h�E�F�A�E�B���h�E�̐ݒ����������ׂɎg�p���܂��B
 * 
 */
//-----------------------------------------------------------------------------
void WIPE_ResetWndMask( int disp )
{
	// �E�B���h�E�}�X�N����
	WNDP_SetVisibleWnd(GX_WNDMASK_NONE, disp);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�u���C�g�l�X��Ԃ�����
 *
 *	@param	disp	�������������
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��
 *
 * �����̊֐���
 *	 �u���C�g�l�X���g�p�������C�v����
 * �@�n�[�h�E�F�A�E�B���h�E���g�p�������C�v�Ɉڍs���鎞�ɁA
 * �@�u���C�g�l�X�̐ݒ����������ׂɎg�p���܂��B
 */
//-----------------------------------------------------------------------------
void WIPE_ResetBrightness( int disp )
{
	// �u���C�g�l�X����
	WIPE_SetMstBrightness( disp, BRIGHTNESS_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�u���C�g�l�X��Ԃ�ݒ�
 *
 *	@param	disp	�ݒ肷����
 *	@param	color	�u���C�g�l�X�J���[
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
			#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
 */
//-----------------------------------------------------------------------------
void WIPE_SetBrightness( int disp, u16 color )
{
	int color_msk;

	if( color == WIPE_FADE_WHITE ){
		color_msk = BRIGHTNESS_WHITE;
	}else{
		color_msk = BRIGHTNESS_BLACK;
	}
	
	WIPE_SetMstBrightness( disp, color_msk);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�E�B���h�E�}�X�N��Ԃ�ݒ�
 *
 *	@param	disp		�ݒ肷����
 *	@param	color		�J���[
 *
 * disp
	WIPE_DISP_MAIN,		// ���C����
	WIPE_DISP_SUB		// �T�u��

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// �z���C�g�C���E�A�E�g
			#define WIPE_FADE_BLACK		(0x0000)	// �u���b�N�C���E�A�E�g
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1�O�̃t�F�[�h�A�E�g�J���[�ŃC���E�A�E�g
 *
 *	���̊֐��́A
 *		�^�b�`�y���g�p��ʂ̏ꍇ�ɁA�t�F�[�h�C���O�Ƀ^�b�`�y����
 *		�o���ȂǁA��O����������܂��B���̂Ƃ��p�̊֐��ł�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetWndMask( int disp, u16 color )
{
	// �o�b�N�h���b�vcolor�̎w��
	if( disp == WIPE_DISP_MAIN ){
		GX_LoadBGPltt((void*)&color, 0, sizeof(short));
	}else{
		GXS_LoadBGPltt((void*)&color, 0, sizeof(short));
	}
	
	// �E�B���h�E�O�ʂŉ�ʂ𕢂�
	WNDP_V_SetVisibleWnd(&WipeSysWork.wnd_sys, GX_WNDMASK_W0, disp);
	WNDP_V_SetWndInsidePlane(&WipeSysWork.wnd_sys, GX_BLEND_ALL, FALSE, 0, disp);
	WNDP_V_SetWndPosition(&WipeSysWork.wnd_sys, 0,0,0,0,0, disp);	
	WNDP_V_SetWndOutsidePlane(&WipeSysWork.wnd_sys, GX_BLEND_PLANEMASK_BD, FALSE, disp);	
}




//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ʃp���b�g�F��ݒ�
 *
 *	@param	color	�J���[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetBackDropColor( u16 color )
{
	// �o�b�N�h���b�vcolor�̎w��
	GX_LoadBGPltt((void*)&color, 0, sizeof(short));
	GXS_LoadBGPltt((void*)&color, 0, sizeof(short));
}

//----------------------------------------------------------------------------
/**
 *	@brief	�u���C�g�l�X�l�ݒ�֐�
 *
 *	@param	disp	���
 *	@param	no		�ݒ�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetMstBrightness( int disp, int no )
{
	// �u���C�g�l�X����
	if( disp == WIPE_DISP_MAIN ){
		GX_SetMasterBrightness(no);
	}else{
		GXS_SetMasterBrightness(no);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��ʐ؂�ւ��t�F�[�h���I������
 *
 *@param	scchg	��ʐ؂�ւ��f�[�^
 *
 *@return	none
 *
 *
 * �I�����ɕK���ĂԕK�v������܂��B
 *
 */
//-----------------------------------------------------------------------------
static void endWipe(WIPE_SYS_DATA* scchg)
{
	scchg->move_flg = FALSE;	// ����OFF
	
	// ���C�v�J���[�̕ۑ�
	scchg->fade_color = getSaveWiepColor( scchg );

	// �����t�F�[�h�A�E�g�̎��@�����@�����̂Ƃ��@�����@�E�B���h�E���g�p�������C�v
	// �Ȃ�΁AϽ����ײ�Ƚ��ݒ肵�ăE�B���h�E�j��
	if( scchg->wipe_pattern_data.wipe_exist_m_check ){
		chgWnd_MstBrightnessCheck_Do( &scchg->wipe_m );

		// �t�F�[�h�C���Ȃ�effect_flg��j��
		if( scchg->wipe_m.fade_inout == WIPE_FADE_IN ){
			WipeSysWork.effect_flg_m = FALSE;
		}
	}
	if( scchg->wipe_pattern_data.wipe_exist_s_check ){
		chgWnd_MstBrightnessCheck_Do( &scchg->wipe_s );

		// �t�F�[�h�C���Ȃ�effect_flg��j��
		if( scchg->wipe_m.fade_inout == WIPE_FADE_IN ){
			WipeSysWork.effect_flg_s = FALSE;
		}
	}

	// ���[�N�̃N���A
	cleanWipeData( scchg );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	��ʐ؂�ւ��T�u�֐�
 *
 *@param	pattern		�؂�ւ��p�^�[��
 *@param	wipe_m		���C�v���C��
 *@param	wipe_s		���C�v�T�u
 *
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL screenChangeSub(WIPE_SYS_PATTERN_DATA* pattern, WIPE_SYS_WIPE_WORK* wipe_m, WIPE_SYS_WIPE_WORK* wipe_s)
{	
	switch(pattern->wipe_pattern){
	case WIPE_THE_SAME_TIME:	// ����
		wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		break;	
		
	case WIPE_START_MAIN:		// ���C������
		if(pattern->wipe_exist_m){
			wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		}else{
			wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		}
		break;	
	case WIPE_START_SUB:		// �T�u����
		if(pattern->wipe_exist_s){
			wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		}else{
			wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		}	
		break;	
	}
	
	// �����̃��C�v�̑��݃t���O��FALSE�ɂȂ�����I��
	if((pattern->wipe_exist_m == FALSE) &&
		(pattern->wipe_exist_s == FALSE)){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�v����֐����p�b�N�����֐�
 *	
 *@param	exist	���݃t���O�iWIPE_SYS_PATTERN_DATA���j
 *@param	wipe	���C�v���[�N
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void wipeFuncPack(BOOL* exist, WIPE_SYS_WIPE_WORK* wipe)
{
	int ret;
	
	if(*exist){

		ret = wipeFunc(wipe);	

		if(ret == TRUE){
			*exist = FALSE;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�v�֐������s
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL wipeFunc(WIPE_SYS_WIPE_WORK* wipe)
{
	return WipeFunc[wipe->wipe_no](wipe);	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��ʕύX�p�^�[���f�[�^���쐬
 *
 *@param	no			�p�^�[���i���o�[
 *@param	pattern_m	���C���̃p�^�[���f�[�^�i�[�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setScreenChangePattern(int no, WIPE_SYS_PATTERN_DATA* pattern)
{
	switch(no){
	case WIPE_PATTERN_WMS:
		patternDataSet(pattern, WIPE_THE_SAME_TIME, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_FMAS:
		patternDataSet(pattern, WIPE_START_MAIN, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_FSAM:
		patternDataSet(pattern, WIPE_START_SUB, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_M:
		patternDataSet(pattern, WIPE_START_MAIN, TRUE, FALSE);
		break;
		
	case WIPE_PATTERN_S:
		patternDataSet(pattern, WIPE_START_SUB, FALSE, TRUE);
		break;
	};
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p�^�[���f�[�^��ݒ�
 *
 *@param	pattern_data	�p�^�[���f�[�^�ݒ��
 *@param	pattern			�p�^�[��
 *@param	exist_m			���C�����C�v���݃t���O
 *@param	exist_s			�T�u���C�v���݃t���O
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void patternDataSet(WIPE_SYS_PATTERN_DATA* pattern_data, int pattern, BOOL exist_m, BOOL exist_s)
{
	pattern_data->wipe_pattern = pattern;
	pattern_data->wipe_exist_m = exist_m;
	pattern_data->wipe_exist_s = exist_s;
	pattern_data->wipe_exist_m_check = exist_m;
	pattern_data->wipe_exist_s_check = exist_s;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�v���[�N�f�[�^��ݒ�
 *
 *@param	wipe_w		�ݒ��
 *@param	wipe_no		���C�v�i���o�[
 *@param	division	����������
 *@param	piece_sync	�����P�Ђ̃V���N��
 *@param	sequence	�V�[�P���X
 *@param	work		���[�N�̈�
 *@param	disp		��
 *@param	wnd_sys		�E�B���h�E�V�X�e���|�C���^
 *@param	heap		�g�p����q�[�v
 *@param	color		�F
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void setWipeWork(WIPE_SYS_WIPE_WORK* wipe_w, int wipe_no, int division, int piece_sync, int sequence, void* work, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb,  int heap, u16 color)
{
	wipe_w->wipe_no		= wipe_no;
	wipe_w->division	= division;
	wipe_w->piece_sync	= piece_sync;
	wipe_w->sequence	= sequence;
	wipe_w->wipe_work	= work;
	wipe_w->disp		= disp;
	wipe_w->wnd_sys		= wnd_sys;
	wipe_w->p_wipehb	= p_wipehb;
	wipe_w->heap		= heap;
	wipe_w->color		= color;
}




//----------------------------------------------------------------------------
//
//
//	�G�t�F�N�g�pH�u�����N�֐��S
//
//
//============================================================================

//----------------------------------------------------------------------------
/**
 *
 *	@brief	H�u�����N���[�N�̏������l��ݒ�
 *
 *	@param	p_wipehb	���C�vH�u�����N���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_HBlankWorkSet( WIPE_HBLANK* p_wipehb )
{
	int i;
	for( i=0; i<2; i++ ){
		p_wipehb->work[ i ] = NULL;
		p_wipehb->func[ i ] = defaultHFunc;
		p_wipehb->flg[ i ]	= 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	HBlank�֐�
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_HBlankFunc(void * work)
{
	int i;		// ���[�v�p
	WIPE_HBLANK* p_wipehb = work;

	for(i=0;i<2;i++){
		p_wipehb->func[i](p_wipehb->work[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	H�u�����N�֐���ݒ�
 *
 *@param	p_wipehb	���C�v�V�X�e����H�u�����N���[�N�\����
 *@param	work		���[�N
 *@param	func		H�u�����N�֐�
 *@param	disp		�\���ʁi���C���T�u�j
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp)
{
	u8	result=TRUE;
	GF_ASSERT((p_wipehb->flg[disp] == 0));
	GF_ASSERT( p_wipehb->func[disp] != NULL );	// NULL���Ƃ�������

	if((p_wipehb->flg[0] == 0) &&
		(p_wipehb->flg[1] == 0)){
		result = sys_HBlankIntrSet(scchg_HBlankFunc, p_wipehb);		// �֐��ݒ�
	}
	GF_ASSERT(result == TRUE);

	
	p_wipehb->work[disp] = work;
	if(func){
		p_wipehb->func[disp] = func;
	}else{
		p_wipehb->func[disp] = defaultHFunc;
	}
	p_wipehb->flg[disp] = WIPE_HBLANK_DO;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	H�u�����N�j��
 *
 *@param	p_wipehb	���C�v��H�u�����N���[�N
 *@param	disp		�\����	���C���E�T�u
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp)
{
	p_wipehb->flg[disp] = WIPE_HBLANK_NONE;

	if((p_wipehb->flg[0] == 0) &&
		(p_wipehb->flg[1] == 0)){
		sys_HBlankIntrStop();		//HBlank���荞�ݒ�~
	}
	
	p_wipehb->func[disp] = defaultHFunc;
	p_wipehb->work[disp] = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	V�u�����N���Ԓ���H�u�����N�֐���ݒ�
 *
 *@param	work		���[�N
 *@param	func		H�u�����N�֐�
 *@param	disp		�\����
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_V_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp, int heap)
{
	WIPE_V_HBLANK* data = sys_AllocMemoryLo(heap, sizeof(WIPE_V_HBLANK));
	
	data->p_wipehb = p_wipehb;
	data->work = work;
	data->func = func;
	data->disp = disp;
	VWaitTCB_Add( scchg_v_HBlankInit, data, WIPE_HBLANK_INIT_TCB);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	H�u�����N�j��
 *
 *@param	disp		�\����	���C���E�T�u
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_V_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp, int heap)
{
	WIPE_V_DELHBLANK* p_delhb = sys_AllocMemoryLo(heap, sizeof(WIPE_V_DELHBLANK));
	p_delhb->p_wipehb	= p_wipehb;
	p_delhb->disp		= disp;
	VWaitTCB_Add( scchg_v_HBlankDelete, p_delhb, WIPE_HBLANK_DELETE_TCB);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank���Ԓ���Hblank������������^�X�N
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	work	�������f�[�^	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_HBlankInit(TCB_PTR tcb, void* work)
{
	WIPE_V_HBLANK*	data = (WIPE_V_HBLANK*)work;
	
	WIPE_HBlankInit(data->p_wipehb, data->work, data->func, data->disp);

	TCB_Delete( tcb );
	sys_FreeMemoryEz( work );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank���Ԓ���Hblank��j������֐�
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	work	�j���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_HBlankDelete(TCB_PTR tcb, void* work)
{
	WIPE_V_DELHBLANK* p_delhb = (WIPE_V_DELHBLANK*)work;
	
	WIPE_HBlankDelete(p_delhb->p_wipehb, p_delhb->disp);
	
	TCB_Delete( tcb );
	sys_FreeMemoryEz( work );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	H�u�����N�֐�	NULL���n���ꂽ��ݒ肳���֐�
 *
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void defaultHFunc( void* work )
{
}


//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�J���[�擾
 *
 *	@param	p_data	���C�v�f�[�^
 *	@param	color	�J���[�p�����[�^
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
static u16 getSetColor( WIPE_SYS_DATA* p_data, u16 color )
{
	if( color == WIPE_FADE_OUTCOLOR ){
		return p_data->fade_color;
	}
	return color;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����̃��C�v�f�[�^�̕ۑ�
 *
 *	@param	cp_data	���[�N
 *
 *	@return	�ۑ�����J���[
 */
//-----------------------------------------------------------------------------
static u16 getSaveWiepColor( const WIPE_SYS_DATA* cp_data )
{
	const WIPE_SYS_WIPE_WORK* cp_wipe_w;
	
	// ���C�v�ł̃t�F�[�h�A�E�g���̏ꍇ
	// �F��ۑ�
	if( cp_data->wipe_pattern_data.wipe_exist_m_check == TRUE ){
		cp_wipe_w = &cp_data->wipe_m;
	}else{
		cp_wipe_w = &cp_data->wipe_s;
	}

	// ���C�v�F�ۑ�
	if( cp_wipe_w->fade_inout == WIPE_FADE_OUT ){
		return cp_wipe_w->color;
	}
	return cp_data->fade_color;	// ���̂܂�
}

//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����NϽ���P�x���Z�b�gTCB
 */
//-----------------------------------------------------------------------------
static void resetMstBrightnessVblank( TCB_PTR tcb, void* work )
{
	WIPE_SYS_WIPE_WORK* p_data = work;
	WIPE_SetMstBrightness( p_data->disp, 0 );	
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�X�^�[��ײ�Ƚ��Ԃ����Z�b�g����
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
static void resetMstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data )
{
	// �����t�F�[�h�C���̎��@�����@�����̂Ƃ��@�����@�E�B���h�E���g�p�������C�v
	// �Ȃ�΁A��ײ�Ƚ�ݒ��OFF����
	if( (p_data->fade_inout == WIPE_FADE_IN) &&
		((p_data->color == WIPE_FADE_WHITE) || (p_data->color == WIPE_FADE_BLACK)) &&
		(p_data->wnd_br == WIPE_USE_WND) ){

		VWaitTCB_Add( resetMstBrightnessVblank, p_data, WIPE_VBLANK_BR_RESET_TCB );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�A�E�g�ŃE�B���h�E�ݒ莞�ɔ����̂Ƃ��́AϽ��[��ײ�Ƚ�ɂ���
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void chgWnd_MstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data )
{
	// �����t�F�[�h�A�E�g�̎��@�����@�����̂Ƃ��@�����@�E�B���h�E���g�p�������C�v
	// �Ȃ�΁AϽ����ײ�Ƚ��ݒ肵�ăE�B���h�E�j��
	if( (p_data->fade_inout == WIPE_FADE_OUT) &&
		((p_data->color == WIPE_FADE_WHITE) || (p_data->color == WIPE_FADE_BLACK)) &&
		(p_data->wnd_br == WIPE_USE_WND) ){

		// ��ײ�Ƚ�ݒ�
		WIPE_SetBrightness( p_data->disp, p_data->color );

		// �E�B���h�E�j��
		WIPE_ResetWndMask( p_data->disp);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�v�f�[�^����ɂ���
 *
 *	@param	p_wipe_data		���C�v�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void cleanWipeData( WIPE_SYS_DATA* p_wipe_data )
{
	memset( &p_wipe_data->wipe_pattern_data, 0, sizeof(WIPE_SYS_PATTERN_DATA) );
	memset( &p_wipe_data->wipe_m, 0, sizeof(WIPE_SYS_WIPE_WORK) );
	memset( &p_wipe_data->wipe_s, 0, sizeof(WIPE_SYS_WIPE_WORK) );
	memset( &p_wipe_data->wipehb, 0, sizeof(WIPE_HBLANK) );
	memset( &p_wipe_data->wnd_sys, 0, sizeof(WNDP_SYS) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�C������
 *
 *	@param	wipe_type	���C�v����
 *
 *	@retval	TRUE	�t�F�[�h�C��
 *	@retval	FALSE	�t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
static BOOL WipeFadeInCheck( u32 wipe_type )
{
	// �z�[���A�E�g�C�����������߂́A����t�F�[�h�C��
	if( (wipe_type % 2) ){
		return TRUE;
	}
	return FALSE;
}

