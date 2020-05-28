//==============================================================================
/**
 * @file	gra_tool.h
 * @brief	�O���t�B�b�N�c�[��
 * @author	goto
 * @date	2005.11.16
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	_GRA_TOOL_H_
#define _GRA_TOOL_H_

#include "battle/graphic/batt_obj_def.h"						///< �A�[�J�C�u�f�[�^
#include "battle/graphic/batt_bg_def.h"						///< �A�[�J�C�u�f�[�^


//==============================================================================
//	�\���̒�`
//==============================================================================
///�|�P�����L�����W�J�p�����[�^
typedef struct
{
	u8	*exchr_buffer;		///<�|�P�����L�����f�[�^�W�J�o�b�t�@
	int	arcID;				///<�A�[�J�C�u���̃|�P�����O���t�B�b�N�A�[�J�C�u�i���o�[
	int	pal_index;			///<�A�[�J�C�u���̃|�P�����p���b�g�C���f�b�N�X�i���o�[
	int	height;				///<�|�P�����������
}EXCHR_PARAM;


// -----------------------------------------
//
//	���萔��`
//
// -----------------------------------------
// 2D��1D�ϊ��Ɏg�p
#define CHAR_DOT_X		(8/2)								///< 1�L�����̃o�C�g�T�C�Y
#define CHAR_DOT_Y		(8)									///< 1�L�����̃o�C�g�T�C�Y
#define CHAR_BYTE		(CHAR_DOT_X * CHAR_DOT_Y)			///< 1�L�����o�C�g��

// -----------------------------------------
//
//	���|�P�����p�萔��`
//		(�퓬�����Ȃ̂ňړ�����ꍇ������܂��B)
//
// -----------------------------------------
#define POKE_TEX_X		(0)									///< �|�P�����ϊ��p�e�N�X�`���؂���J�n�ʒuX
#define POKE_TEX_Y		(0)									///< �|�P�����ϊ��p�e�N�X�`���؂���J�n�ʒuY
#define POKE_TEX_W		(10)								///< �|�P�����ϊ��p�e�N�X�`���؂���I���ʒuX
#define POKE_TEX_H		(10)								///< �|�P�����ϊ��p�e�N�X�`���؂���I���ʒuY
#define POKE_TEX_SIZE	(POKE_TEX_W * POKE_TEX_H * CHAR_BYTE)

#define PO_CHAR_ID		(POKE_OAM_NCGR)		///< �_�~�[�f�[�^�̃A�[�J�C�uID
#define PO_PLTT_ID		(POKE_OAM_NCLR)
#define PO_CELL_ID		(POKE_OAM_NCER)
#define PO_CELLANM_ID	(POKE_OAM_NANR)

#define PB_N_SCREEN_ID		(POKE_SCREEN_N_NSCR);		///< �_�~�[�X�N���[���̃A�[�J�C�uID
#define PB_F_SCREEN_ID		(POKE_SCREEN_F_NSCR);
#define PB_N_512_SCREEN_ID	(POKE_SCREEN_N_512_NSCR);	///< �_�~�[�X�N���[���̃A�[�J�C�uID512x512
#define PB_F_512_SCREEN_ID	(POKE_SCREEN_F_512_NSCR);

// -----------------------------------------
//
//	���ϊ��p�̋�`�\����
//
// -----------------------------------------
typedef struct {
	
	int x;
	int y;
	int w;
	int h;
	
} CHANGES_INTO_DATA_RECT;

extern void	 ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void	 ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst);
extern void  ChangesInto_OAM_from_1D_RC(int sx, int sy, const CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst);

extern void  ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff);
extern void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id);

extern void* ChangesInto_BattlePokePalData_Alloc(int arc_id, int index_no, int heap_id);


/// �|�P�����̂Ԃ��Ή�Ver �g���Ă���̂������₵�܂����B
extern void  Ex_ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);
extern void  Ex_ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);

extern void  Ex_ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);
extern void* Ex_ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id, u32 rnd, BOOL animeFlag, int dir, int monsno);

#endif

