//==============================================================================
/**
 * @file	we_tool.h
 * @brief	�Z�G�t�F�N�g�֌W�̃c�[���̃w�b�_
 * @author	matsuda
 * @date	2005.07.29(��)
 */
//==============================================================================
#ifndef __WE_TOOL_H__
#define __WE_TOOL_H__

#include "we_sys.h"


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	�p�[�e�B�N�����o�����̃|�P�����ʒu���̃f�t�H���gZ�l
//--------------------------------------------------------------
#define WET_PARTICLE_Z_AA	(0x40)
#define WET_PARTICLE_Z_BB	(-5248)
#define WET_PARTICLE_Z_A	(WET_PARTICLE_Z_AA)
#define WET_PARTICLE_Z_B	(WET_PARTICLE_Z_BB)
#define WET_PARTICLE_Z_C	(-0x400)
#define WET_PARTICLE_Z_D	(-0x1cb0)

// �u�����h�ݒ�
#define WET_DEFAULT_BLEND	(0xffffffff)		///< �f�t�H���g�ŏ���������
#define WET_ALPHA_OAM		(26)				///< OAM�Ɋ|���郿�l	�f�t�H���g
#define WET_ALPHA_BG		(5)					///< BG�Ɋ|���郿�l		�f�t�H���g


// -----------------------------------------
//
//	���W����
//
// -----------------------------------------
typedef struct {
	s16 x;
	s16 y;
} WT_POINT;

typedef struct {
	
	s16	top;
	s16	left;
	s16	buttom;
	s16	right;
	
} WT_RECT;

extern void WT_SSP_PointGet(SOFT_SPRITE* ssp, WT_POINT* p);
extern void WT_CAP_PointGet(CATS_ACT_PTR cap, WT_POINT* p);


// -----------------------------------------
//
//	����������֘A
//
// -----------------------------------------
extern void* WazaEffect_AllocMemory(WE_SYS_PTR wsp, int size);
extern void  WazaEffect_FreeMemory(void* wk);


// -----------------------------------------
//
//	�������m�ۗp�}�N��
//
//	n = we_sys
//	m = �\���̖�
//
// -----------------------------------------
#define WET_ALLOC_MEMORY(mem, siz)	(WazaEffect_AllocMemory((mem), sizeof(siz)))

#define WET_SAFE_RELEASE(mem)		\
	{								\
		WazaEffect_FreeMemory(mem);	\
		(mem) = NULL;				\
	}

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern int	WET_ClientTypeGet(WE_SYS_PTR wsp, int client_no);
extern int	WET_SideCheck(WE_SYS_PTR wsp, int client_no);
extern int	WET_AllySideClientNoGet(WE_SYS_PTR wsp, int client_no);
extern int	WET_DiagonalClientTypeGet(WE_SYS_PTR wsp, int client_no);
extern int	WazaTool_DiagonalClientTypeGet_ClientType(int client_type);

///< �ʏ�
extern void WET_PokeParticlePosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_type);
extern void WET_PokeParticlePosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);
extern void WET_PokeParticlePosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type);

///< ���[�U�[
extern void WET_PokeParticleLaserPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaserPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);
extern void WET_PokeParticleLaserPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type);

///< ���[�U�[�Q
extern void WET_PokeParticleLaser2PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser2PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

///< ���[�U�[�R
extern void WET_PokeParticleLaser3PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser3PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);


///< ���[�U�[�R
extern void WET_PokeParticleLaser095PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser095PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

extern void WET_PokeParticleLaser161PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser161PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

extern void WET_PokeParticleLaser308PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser308PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

extern void WET_PokeParticleLaser304PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser304PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

extern void WET_PokeParticleLaser320PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser320PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

extern void WET_PokeParticleLaser406PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLaser406PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);

///< �����_
extern void WET_PokeParticleLookAtPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleLookAtPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);
extern void WET_PokeParticleLookAtPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type);
extern void WET_PokeParticleDispOutTopGet(VecFx32 *ret);

///< �����O
extern void WET_PokeParticleRingPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode);
extern void WET_PokeParticleRingPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret);
extern void WET_PokeParticleRingPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type);

extern void WET_AttackCameraEyeGet(int attack, VecFx32 *eye);
extern void WET_AttackCameraUpGet(int attack, VecFx32 *v_up);

extern void WET_DefaultBlendSet(WE_SYS_PTR we_sys, int obj_ba, int bg_ba);
extern void WET_BGSelectBlendSet(WE_SYS_PTR we_sys, int bg_msk, int obj_ba, int bg_ba);

extern void WET_DefaultBGEffectBlendSet( WE_SYS_PTR we_sys, int effe_ba, int bg_ba );
// wndmsk�ݒ�
enum{
	WET_WNDMSK_0,
	WET_WNDMSK_1,
};
extern void WET_DefaultWndMskSet( WE_SYS_PTR we_sys, int wnd_no, BOOL effect );
extern void WET_PokeDefaultPosGet_ClientType(int client_type, int contest_flag, WT_POINT* p);
extern void WET_PokeDefaultPosGet_ClientNo(WE_SYS_PTR wsp, int client_no, WT_POINT* p);

extern int WET_CheckClientNo(WE_SYS_PTR wsp, int type);

// =============================================================================
//
//
//	���ǂ��g������
//
//
// =============================================================================
// �ǂ��g�����̍\����
typedef struct {
	
	u8	seq;
	u8	cnt;
	u8	step;
	u8	wait;
	
	WE_SYS_PTR			wsp;
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		poke_crp;
	CATS_RES_PTR		oam_crp;
	GF_BGL_INI*			bgl;
	PALETTE_FADE_PTR	pfd;
	
} TWE_TOOL_SYS;

// �|�P�����ł悭�g�����̍\����
typedef struct {
	
	WT_POINT			base_p;
	WT_POINT			p;
	SOFT_SPRITE*		ssp;
	CATS_ACT_PTR		cap;
	
	int					client_no;
	
} TWE_POKE_SYS;

// �h�炵�p�\����
typedef struct {

	s16		x;
	s16		y;
	s16		w;
	s16		n;
	int		mode;

} TWE_SHAKE_TOOL;

///< Bit�`�F�b�N TRUE = ON
static inline BOOL IsBitCheck(int bit, int flag)
{	
	if ((bit & flag) == flag){
		return TRUE;
	}
	
	return FALSE;
}

extern void WT_ToolSysInit(WE_SYS_PTR we_sys, TWE_TOOL_SYS* wts);
extern void WT_SSPointerGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num);
extern void WT_CAPointerGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num);
extern void WT_PokeBasePointGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num);

#include "we_def.h"
//--------------------------------------------------------------
/**
 * @brief	LCD ���W����A�p�[�e�B�N��LCD���W���擾����
 *
 * @param	lcd_x			lcd x
 * @param	lcd_y			lcd y
 * @param	plcd_x			plcd x
 * @param	plcd_y			plcd y
 *
 * @retval	inline void	
 *
 */
//--------------------------------------------------------------
static inline void LCD_To_PTLCD_PosGet(s16 lcd_x, s16 lcd_y, int* plcd_x, int* plcd_y)
{
	*plcd_x = PT_LCD_L - (lcd_x * PT_LCD_DOT);
	*plcd_y = PT_LCD_T - (lcd_y * PT_LCD_DOT);
	
	*plcd_x = (lcd_x * PT_LCD_DOT) - (120 * PT_LCD_DOT);
	*plcd_y = (lcd_y * PT_LCD_DOT) + ( 96 * PT_LCD_DOT);
}


//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N��LCD ���W����ALCD���W���擾����
 *
 * @param	plcd_x			plcd x
 * @param	plcd_y			plcd y
 * @param	lcd_x			lcd x
 * @param	lcd_y			lcd y
 *
 * @retval	inline void	
 *
 *		�p�[�e�B�N�����́A��܂��ȍ��W�ň����̂ŕϊ����͐؂�̂Čv�Z�ł��B
 *
 */
//--------------------------------------------------------------
static inline void PTLCD_To_LCD_PosGet(int plcd_x, int plcd_y, s16* lcd_x, s16* lcd_y)
{
	*lcd_x = (plcd_x +  PT_LCD_L) / PT_LCD_DOT;
	*lcd_y = (plcd_y +  PT_LCD_T) / PT_LCD_DOT;
}

#endif	//__WE_TOOL_H__

