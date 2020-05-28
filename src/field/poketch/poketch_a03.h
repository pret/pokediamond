//============================================================================================
/**
 * @file	poketch_a03.h
 * @bfief	�|�P�b�`�i�A�v��No03�F�������j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A03_H_
#define _POKETCH_A03_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_BUTTON_UPDATE,
	CMD_PIXEL_UPDATE,
	CMD_PIXEL_SET,
	CMD_PIXEL_SET_END,
	CMD_QUIT,
};

//====================================================
// �萔
//====================================================
enum TOUCH_MODE {
	TOUCHMODE_ERASER,
	TOUCHMODE_PEN,
};

enum {
	AREA_START_X = 16,
	AREA_START_Y = 16,
	AREA_END_X = 172,
	AREA_END_Y = 166,

	AREA_H_RANGE = AREA_END_X - AREA_START_X,
	AREA_V_RANGE = AREA_END_Y - AREA_START_Y,

	PIXEL_H_MAX = (AREA_H_RANGE/2) + (AREA_H_RANGE&1),
	PIXEL_V_MAX = (AREA_V_RANGE/2) + (AREA_V_RANGE&1),
};


//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	u32 touch_mode;

	u32  pixel_update_x;
	u32  pixel_update_y;
	u8   pixel[PIXEL_H_MAX][PIXEL_V_MAX];

	u32  appNumber;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A03_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A03_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A03_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A03_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A03_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A03_DeleteViewWork(VIEWWORK* wk);

#endif
