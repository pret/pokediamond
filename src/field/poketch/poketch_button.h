//============================================================================================
/**
 * @file	poketch_button.h
 * @bfief	�{�^����ԊǗ��}�l�[�W��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef __BUTTON_MAN_H__
#define __BUTTON_MAN_H__

#include "gflib/touchpanel.h"



enum BMN_EVENT {
	BMN_EVENT_NULL = 0,
	BMN_EVENT_TOUCH,		
	BMN_EVENT_OUT,			
	BMN_EVENT_TAP,			// �V���O���^�b�v�m��Ŕ���
	BMN_EVENT_DOUBLETAP,	// �_�u���^�b�v�m��Ŕ���
	BMN_EVENT_TIMER0,
	BMN_EVENT_TIMER1,
	BMN_EVENT_REPEAT,
};

enum  BMN_TOUCH {
	BMN_TOUCH_OFF,			// �O�t���[���G��ĂȂ������t���[���G�ꂽ
	BMN_TOUCH_ON,			// �O�t���[���G��Ă��������t���[���G��ĂȂ�
	BMN_TOUCH_CONT,			// �O�t���[���ƕς�炸
};


//---------------------------------------------------------------------
/**
 *	�{�^���}�l�[�W���^�錾
 */
//---------------------------------------------------------------------
typedef struct _POKETCH_BUTTON_MAN	POKETCH_BUTTON_MAN;


//---------------------------------------------------------------------
/**
 *	�{�^���}�l�[�W������̃R�[���o�b�N�֐��^�B�����̓��e�͈ȉ��̏��B
 *
 *	u32		�{�^���̃C���f�b�N�X
 *	u32		���������C�x���g�iBMN_EVENT�j
 *	u32		�ڐG�󋵂̍X�V�iBMN_TOUCH�j
*	void*	PBTN_Create�œn�������[�N�|�C���^
 *
 */
//---------------------------------------------------------------------
typedef void (*pBmnCallBack)(u32, u32, u32, void*);



extern POKETCH_BUTTON_MAN* PBTN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBack callback, void *callback_param, u32 heap_type );
extern void PBTN_Delete( POKETCH_BUTTON_MAN *bmn );
extern void PBTN_Main( POKETCH_BUTTON_MAN *bmn );
extern void PBTN_SetDoubleTapTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time );
extern void PBTN_SetEventTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u32 event_num, u16 time );
extern void PBTN_SetRepeatTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time );
extern void PBTN_ResetState( POKETCH_BUTTON_MAN* bmn, u32 idx );



#endif
