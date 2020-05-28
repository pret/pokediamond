//============================================================================================
/**
 * @file	poketch_a29.h
 * @bfief	�|�P�b�`�i�A�v��No29:�|�P�����q�X�g���[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A29_H_
#define _POKETCH_A29_H_

#include "field\poketch_data.h"
#include "poketch_prv.h"

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
};

//====================================================
// �A�C�R���z�u
//====================================================
enum {
	ICONPOS_XORG = POKETCH_MONITOR_DOT_XORG + 32,
	ICONPOS_YORG = POKETCH_MONITOR_DOT_YORG + 32,
	ICONPOS_XDIFF = 40,
	ICONPOS_YDIFF = 48,

	ICON_TOUCH_WIDTH = 48,
	ICON_TOUCH_HEIGHT = 36,
};

#define TOUCH_TOP(y)	( (ICONPOS_YORG + ICONPOS_YDIFF*(y)) - (ICON_TOUCH_HEIGHT/2) )
#define TOUCH_BOTTOM(y)	( (ICONPOS_YORG + ICONPOS_YDIFF*(y)) + (ICON_TOUCH_HEIGHT/2) )
#define TOUCH_LEFT(x)	( (ICONPOS_XORG + ICONPOS_XDIFF*(x)) - (ICON_TOUCH_WIDTH/2) )
#define TOUCH_RIGHT(x)	( (ICONPOS_XORG + ICONPOS_XDIFF*(x)) + (ICON_TOUCH_WIDTH/2) )


//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	struct {
		int  monsno;
		int  iconPattern;
	}poke_param[ POKETCH_POKE_HISTORY_COUNT_MAX ];

	u32   pokeCount;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A29_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A29_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A29_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A29_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A29_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A29_DeleteViewWork(VIEWWORK* wk);

#endif
