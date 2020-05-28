//==============================================================================
/**
 * @file	contest_cursor.h
 * @brief	�R���e�X�g����ʗp�J�[�\���̃w�b�_
 * @author	matsuda
 * @date	2006.03.27(��)
 */
//==============================================================================
#ifndef __CONTEST_CURSOR_H__
#define __CONTEST_CURSOR_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�퓬�J�[�\���̃A�j���^�C�v
typedef enum{
	CCURSOR_ANMTYPE_LU,		///<����J�[�\��
	CCURSOR_ANMTYPE_RU,		///<�E��J�[�\��
	CCURSOR_ANMTYPE_LD,		///<�����J�[�\��
	CCURSOR_ANMTYPE_RD,		///<�E���J�[�\��
}CCURSOR_ANMTYPE;

//==============================================================================
//	�^��`
//==============================================================================
///CCURSOR_WORK�̕s��`�|�C���^
typedef struct _CCURSOR_WORK * CCURSOR_PTR;

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void CCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern void CCURSOR_ResourceFree(CATS_RES_PTR crp, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
extern CCURSOR_PTR CCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
extern void CCURSOR_ActorDelete(CCURSOR_PTR cursor);
extern void CCURSOR_PosSetON(CCURSOR_PTR cursor, int left, int right, int top, int bottom);
extern void CCURSOR_ExPosSetON(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type);
extern void CCURSOR_OFF(CCURSOR_PTR cursor);
extern void CCURSOR_ExOFF(CCURSOR_PTR cursor);
extern void CCURSOR_IndividualPosSetON(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y);
extern void CCURSOR_IndividualPosSetON_Surface(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, 
	int ru_y, int ld_x, int ld_y, int rd_x, int rd_y, fx32 surface_y);
extern void CCURSOR_ExPosSetON_Surface(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type,
	fx32 surface_y);
extern void CCURSOR_PosSetON_Surface(CCURSOR_PTR cursor, int left, int right, int top, int bottom,
	fx32 surface_y);


#endif	//__CONTEST_CURSOR_H__

