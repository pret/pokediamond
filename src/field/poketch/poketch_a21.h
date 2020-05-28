//============================================================================================
/**
 * @file	poketch_a21.h
 * @bfief	�|�P�b�`�i�A�v��No21:�L�b�`���^�C�}�[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A21_H_
#define _POKETCH_A21_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_CHANGE_INPUT,
	CMD_CHANGE_COUNTDOWN,
	CMD_UPDATE_BUTTON,
	CMD_UPDATE_NUM,
	CMD_START_ALARM,
	CMD_STOP_ALARM,
};

enum {
	BUTTON_RANGE_X = 64,
	BUTTON_RANGE_Y = 32,
	ARROW_RANGE_X = 16,
	ARROW_RANGE_Y = 16,


	START_XPOS = 48,
	START_YPOS = 160,
	STOP_XPOS  = 112,
	STOP_YPOS  = 160,
	RESET_XPOS = 176,
	RESET_YPOS = 160,


	ARROW_UP_BASE_YPOS = 88,
	ARROW_DOWN_BASE_YPOS = 136,

	MIN10_UP_XPOS = 80,
	MIN10_UP_YPOS = ARROW_UP_BASE_YPOS,
	MIN1_UP_XPOS  = MIN10_UP_XPOS+16,
	MIN1_UP_YPOS  = ARROW_UP_BASE_YPOS,
	MIN10_DOWN_XPOS = MIN10_UP_XPOS,
	MIN10_DOWN_YPOS = ARROW_DOWN_BASE_YPOS,
	MIN1_DOWN_XPOS  = MIN1_UP_XPOS,
	MIN1_DOWN_YPOS  = ARROW_DOWN_BASE_YPOS,


	SEC10_UP_XPOS = 128,
	SEC10_UP_YPOS = ARROW_UP_BASE_YPOS,
	SEC1_UP_XPOS  = SEC10_UP_XPOS+16,
	SEC1_UP_YPOS  = ARROW_UP_BASE_YPOS,
	SEC10_DOWN_XPOS = 128,
	SEC10_DOWN_YPOS = ARROW_DOWN_BASE_YPOS,
	SEC1_DOWN_XPOS  = SEC10_DOWN_XPOS+16,
	SEC1_DOWN_YPOS  = ARROW_DOWN_BASE_YPOS,




	START_TOUCH_TOP    = START_YPOS - (BUTTON_RANGE_Y/2),
	START_TOUCH_BOTTOM = START_YPOS + (BUTTON_RANGE_Y/2),
	START_TOUCH_LEFT   = START_XPOS - (BUTTON_RANGE_X/2),
	START_TOUCH_RIGHT  = START_XPOS + (BUTTON_RANGE_X/2),
	STOP_TOUCH_TOP     = STOP_YPOS  - (BUTTON_RANGE_Y/2),
	STOP_TOUCH_BOTTOM  = STOP_YPOS  + (BUTTON_RANGE_Y/2),
	STOP_TOUCH_LEFT    = STOP_XPOS  - (BUTTON_RANGE_X/2),
	STOP_TOUCH_RIGHT   = STOP_XPOS  + (BUTTON_RANGE_X/2),
	RESET_TOUCH_TOP    = RESET_YPOS - (BUTTON_RANGE_Y/2),
	RESET_TOUCH_BOTTOM = RESET_YPOS + (BUTTON_RANGE_Y/2),
	RESET_TOUCH_LEFT   = RESET_XPOS - (BUTTON_RANGE_X/2),
	RESET_TOUCH_RIGHT  = RESET_XPOS + (BUTTON_RANGE_X/2),

	MIN10_UP_TOP    = MIN10_UP_YPOS - (ARROW_RANGE_Y/2),
	MIN10_UP_BOTTOM = MIN10_UP_YPOS + (ARROW_RANGE_Y/2),
	MIN10_UP_LEFT   = MIN10_UP_XPOS - (ARROW_RANGE_X/2),
	MIN10_UP_RIGHT  = MIN10_UP_XPOS + (ARROW_RANGE_X/2),
	MIN1_UP_TOP     = MIN1_UP_YPOS - (ARROW_RANGE_Y/2),
	MIN1_UP_BOTTOM  = MIN1_UP_YPOS + (ARROW_RANGE_Y/2),
	MIN1_UP_LEFT    = MIN1_UP_XPOS - (ARROW_RANGE_X/2),
	MIN1_UP_RIGHT   = MIN1_UP_XPOS + (ARROW_RANGE_X/2),
	MIN10_DOWN_TOP    = MIN10_DOWN_YPOS - (ARROW_RANGE_Y/2),
	MIN10_DOWN_BOTTOM = MIN10_DOWN_YPOS + (ARROW_RANGE_Y/2),
	MIN10_DOWN_LEFT   = MIN10_DOWN_XPOS - (ARROW_RANGE_X/2),
	MIN10_DOWN_RIGHT  = MIN10_DOWN_XPOS + (ARROW_RANGE_X/2),
	MIN1_DOWN_TOP     = MIN1_DOWN_YPOS - (ARROW_RANGE_Y/2),
	MIN1_DOWN_BOTTOM  = MIN1_DOWN_YPOS + (ARROW_RANGE_Y/2),
	MIN1_DOWN_LEFT    = MIN1_DOWN_XPOS - (ARROW_RANGE_X/2),
	MIN1_DOWN_RIGHT   = MIN1_DOWN_XPOS + (ARROW_RANGE_X/2),


	SEC10_UP_TOP    = SEC10_UP_YPOS - (ARROW_RANGE_Y/2),
	SEC10_UP_BOTTOM = SEC10_UP_YPOS + (ARROW_RANGE_Y/2),
	SEC10_UP_LEFT   = SEC10_UP_XPOS - (ARROW_RANGE_X/2),
	SEC10_UP_RIGHT  = SEC10_UP_XPOS + (ARROW_RANGE_X/2),
	SEC1_UP_TOP     = SEC1_UP_YPOS - (ARROW_RANGE_Y/2),
	SEC1_UP_BOTTOM  = SEC1_UP_YPOS + (ARROW_RANGE_Y/2),
	SEC1_UP_LEFT    = SEC1_UP_XPOS - (ARROW_RANGE_X/2),
	SEC1_UP_RIGHT   = SEC1_UP_XPOS + (ARROW_RANGE_X/2),

	SEC10_DOWN_TOP    = SEC10_DOWN_YPOS - (ARROW_RANGE_Y/2),
	SEC10_DOWN_BOTTOM = SEC10_DOWN_YPOS + (ARROW_RANGE_Y/2),
	SEC10_DOWN_LEFT   = SEC10_DOWN_XPOS - (ARROW_RANGE_X/2),
	SEC10_DOWN_RIGHT  = SEC10_DOWN_XPOS + (ARROW_RANGE_X/2),
	SEC1_DOWN_TOP     = SEC1_DOWN_YPOS - (ARROW_RANGE_Y/2),
	SEC1_DOWN_BOTTOM  = SEC1_DOWN_YPOS + (ARROW_RANGE_Y/2),
	SEC1_DOWN_LEFT    = SEC1_DOWN_XPOS - (ARROW_RANGE_X/2),
	SEC1_DOWN_RIGHT   = SEC1_DOWN_XPOS + (ARROW_RANGE_X/2),


};


enum {
	KITCHEN_MODE_INPUT = 0,
	KITCHEN_MODE_COUNTDOWN,
};

enum {
	BUTTON_OFF = 0,
	BUTTON_ON,
};

enum {
	PUSH_BUTTON_MAX = 3,	// BTN_START�`BTN_RESET
};

enum {
	ALARM_STATE_STOP,
	ALARM_STATE_COUNTDOWN,
	ALARM_STATE_ACT,
	ALARM_STATE_ACT_PAUSE,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	s8   min10;
	s8   min1;
	s8   sec10;
	s8   sec1;

	u8   button[PUSH_BUTTON_MAX];

	BOOL arrow_disp_flag;
	u32  alarm_state;
	u32  alarm_pause_anim;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A21_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A21_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A21_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A21_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A21_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A21_DeleteViewWork(VIEWWORK* wk);
extern u32 Poketch_A21_GetAlarmAnimState( VIEWWORK* wk );

#endif
