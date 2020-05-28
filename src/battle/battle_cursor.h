//==============================================================================
/**
 * @file	battle_cursor.h
 * @brief	�퓬����ʗp�J�[�\���̃w�b�_
 * @author	matsuda
 * @date	2006.03.27(��)
 */
//==============================================================================
#ifndef __BATTLE_CURSOR_H__
#define __BATTLE_CURSOR_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�퓬�J�[�\���̃A�j���^�C�v
typedef enum{
	BCURSOR_ANMTYPE_LU,		///<����J�[�\��
	BCURSOR_ANMTYPE_RU,		///<�E��J�[�\��
	BCURSOR_ANMTYPE_LD,		///<�����J�[�\��
	BCURSOR_ANMTYPE_RD,		///<�E���J�[�\��
}BCURSOR_ANMTYPE;

//==============================================================================
//	�^��`
//==============================================================================
///BCURSOR_WORK�̕s��`�|�C���^
typedef struct _BCURSOR_WORK * BCURSOR_PTR;

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void BCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern void BCURSOR_ResourceFree(CATS_RES_PTR crp, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern BCURSOR_PTR BCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
extern void BCURSOR_ActorDelete(BCURSOR_PTR cursor);
extern void BCURSOR_PosSetON(BCURSOR_PTR cursor, int left, int right, int top, int bottom);
extern void BCURSOR_ExPosSetON(BCURSOR_PTR cursor, int x, int y, BCURSOR_ANMTYPE anm_type);
extern void BCURSOR_OFF(BCURSOR_PTR cursor);
extern void BCURSOR_ExOFF(BCURSOR_PTR cursor);
extern void BCURSOR_IndividualPosSetON(BCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y);
extern void BCURSOR_IndividualPosSetON_Surface(BCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, 
	int ru_y, int ld_x, int ld_y, int rd_x, int rd_y, fx32 surface_y);
extern void BCURSOR_ExPosSetON_Surface(BCURSOR_PTR cursor, int x, int y, BCURSOR_ANMTYPE anm_type,
	fx32 surface_y);
extern void BCURSOR_PosSetON_Surface(BCURSOR_PTR cursor, int left, int right, int top, int bottom,
	fx32 surface_y);


#endif	//__BATTLE_CURSOR_H__

