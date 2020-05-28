//============================================================================================
/**
 * @file	button_man.c
 * @bfief	�{�^����ԊǗ��}�l�[�W��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "gflib\touchpanel.h"

#define __POKETCH_BUTTON_MAN_GLOBAL__
#include "poketch_button.h"



//====================================================
// �萔
//====================================================
#define EVENT_TIME_MAX	(2)			// �P�̃{�^�������������鎞�ԃC�x���g�̍ő吔

//====================================================
// �ʃ{�^����ԊǗ��\����
//====================================================
typedef struct {
	u8  state;
	u8  touch_flag;
	u8  prev_touch_flag;
	u8  action_event;

	u16 timer;
	u16 doubletap_time;

	u16 event_time[ EVENT_TIME_MAX ];
	u16 repeat_time;

}BUTTON;

//====================================================
// �{�^���S�̊Ǘ�
//====================================================
struct _POKETCH_BUTTON_MAN {
	const TP_HIT_TBL*	hit_tbl;
	pBmnCallBack		callback;
	u32					heap_type;
	u32					btn_cnt;
	void*				callback_param;

	BUTTON *btn;

};

//====================================================
// �{�^�����
//====================================================
enum {
	STATE_FREE = 0,
	STATE_HOLD,
	STATE_DOUBLETAP_CHECK,
	STATE_DOUBLETAP,
	STATE_RESET,
};

//====================================================
// �萔
//====================================================
#define TIMER_MAX	(0xffff)		// �z�[���h��Ԃ̃^�C�}�[�ő�l

//==============================================================
// Prototype
//==============================================================
static void ButtonStateInit( BUTTON* btn );
static void ButtonStateChange( BUTTON *btn, u32 state );
static void ButtonStateChange( BUTTON *btn, u32 state );
static void ButtonTimerInc( BUTTON *btn );
static u32 TimeEventCheck( BUTTON* btn );
static u32 StateFree( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateHold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateDoubleTapCheck( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateDoubleTap( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateReset( BUTTON *btn, BOOL tp_cont,  BOOL tp_trg );


//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W���쐬
 *
 * @param   hit_tbl			�����蔻��Ɏg��TP_HIT_TBL�e�[�u��
 * @param   btn_cnt			RECT_HIT�e�[�u���̗v�f���iNELEMS�Łj
 * @param   callback		�{�^���̏�ԍX�V���ɌĂяo�����R�[���o�b�N�֐�
 * @param   callback_param	�R�[���o�b�N�֐��ɓn���C�Ӄ|�C���^
 * @param   heap_type		���W���[���̃��[�N�m�ۂɎg���q�[�v�^�C�v
 *
 * @retval  BOOL		����I���Ȃ�m�ۂ����}�l�[�W���̃A�h���X�C
 *						�m�ێ��s������NULL
 */
//------------------------------------------------------------------
POKETCH_BUTTON_MAN* PBTN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBack callback, void *callback_param, u32 heap_type )
{
	POKETCH_BUTTON_MAN *bmn;

	GF_ASSERT( btn_cnt > 0 );

	bmn = sys_AllocMemory( heap_type, sizeof(POKETCH_BUTTON_MAN) );
	if(bmn)
	{
		bmn->heap_type = heap_type;
		bmn->callback = callback;
		bmn->hit_tbl = hit_tbl;
		bmn->btn_cnt = btn_cnt;
		bmn->callback_param = callback_param;

		bmn->btn = sys_AllocMemory( heap_type, sizeof(BUTTON) * btn_cnt );
		if(bmn->btn)
		{
			u32 i;

			for(i = 0; i < btn_cnt; i++)
			{
				ButtonStateInit( &bmn->btn[i] );
			}
		}
		else
		{
			sys_FreeMemory( heap_type, bmn );
			bmn = NULL;
		}
	}
	return bmn;
}
//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W������
 *
* @param   bmn		PBTN_Create�Ŋm�ۂ����}�l�[�W���̃A�h���X
 *
 */
//------------------------------------------------------------------
void PBTN_Delete( POKETCH_BUTTON_MAN *bmn )
{
	GF_ASSERT( bmn );
	sys_FreeMemory( bmn->heap_type, bmn->btn );
	sys_FreeMemory( bmn->heap_type, bmn );
}

//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W�����C���i���t���[���Ăяo���j
 *
 * @param   bmn		
 *
 */
//------------------------------------------------------------------
void PBTN_Main( POKETCH_BUTTON_MAN *bmn )
{
	static u32 (* const ButtonProc[])(BUTTON*, BOOL, BOOL ) = {
		StateFree,
		StateHold,
		StateDoubleTapCheck,
		StateDoubleTap,
		StateReset,
	};

	BOOL tp_cont, tp_trg;
	u32 i, ev, touch_ev;

	tp_cont = GF_TP_GetCont();
	if( tp_cont )
	{
		tp_trg = GF_TP_GetTrg();

		for(i = 0; i < bmn->btn_cnt; i++)
		{
			bmn->btn[i].prev_touch_flag = bmn->btn[i].touch_flag;
			if(bmn->btn[i].touch_flag){
				bmn->btn[i].touch_flag = GF_TP_SingleHitCont( &bmn->hit_tbl[i] );
			}else{
				bmn->btn[i].touch_flag = GF_TP_SingleHitTrg( &bmn->hit_tbl[i] );
			}
		}
	}
	else
	{
		tp_trg = FALSE;

		for(i = 0; i < bmn->btn_cnt; i++)
		{
			bmn->btn[i].prev_touch_flag = bmn->btn[i].touch_flag;
			bmn->btn[i].touch_flag = FALSE;
		}
	}


	for(i = 0; i < bmn->btn_cnt; i++)
	{
		ev = ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
		if(bmn->btn[i].touch_flag != bmn->btn[i].prev_touch_flag){
			touch_ev = bmn->btn[i].touch_flag;
		}else{
			touch_ev = BMN_TOUCH_CONT;
		}
		if(	(ev != BMN_EVENT_NULL)
		||	(touch_ev != BMN_TOUCH_CONT)
		){
			bmn->callback( i, ev, touch_ev, bmn->callback_param );
			break;
		}
	}

	for(i++ ; i < bmn->btn_cnt; i++)
	{
		ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
	}
}


//------------------------------------------------------------------
/**
 * ����{�^���Ƀ_�u���^�b�v���m�̋@�\����������
 *
 * @param   bmn		�}�l�[�W�����[�N
 * @param   idx		�{�^���C���f�b�N�X
 * @param   time	�_�u���^�b�v���m�t���[����
 *
 */
//------------------------------------------------------------------
void PBTN_SetDoubleTapTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time )
{
	bmn->btn[idx].doubletap_time = time;
}
//------------------------------------------------------------------
/**
 * ����{�^���Ɉ�莞�ԃz�[���h�ŃC�x���g�����̋@�\����������
 *
 * @param   bmn		�}�l�[�W�����[�N
 * @param   idx		�{�^���C���f�b�N�X
 * @param   event_num		�C�x���g�i���o�[
 * @param   time		�C�x���g��������z�[���h���ԁi�t���[���j
 *
 */
//------------------------------------------------------------------
void PBTN_SetEventTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u32 event_num, u16 time )
{
	bmn->btn[idx].event_time[event_num] = time;
}
//------------------------------------------------------------------
/**
 * ����{�^���Ƀ��s�[�g�Ԋu���Z�b�g
 *
 * @param   bmn		
 * @param   idx		
 * @param   time		
 *
 */
//------------------------------------------------------------------
void PBTN_SetRepeatTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time )
{
	bmn->btn[idx].repeat_time = time;
}

//------------------------------------------------------------------
/**
 * �{�^����Ԃ��������Z�b�g
 *
 * @param   bmn		�}�l�[�W�����[�N
 * @param   idx		�{�^���C���f�b�N�X
 *
 */
//------------------------------------------------------------------
void PBTN_ResetState( POKETCH_BUTTON_MAN* bmn, u32 idx )
{
	bmn->btn[idx].timer = 0;
	bmn->btn[idx].state = STATE_RESET;
}

//------------------------------------------------------------------
/**
 * �{�^�����[�N������
 *
 * @param   btn		�{�^�����[�N
 *
 */
//------------------------------------------------------------------
static void ButtonStateInit( BUTTON* btn )
{
	u32 i;

	btn->state = STATE_FREE;
	btn->touch_flag = FALSE;
	btn->prev_touch_flag = FALSE;
	btn->timer = 0;
	btn->doubletap_time = 0;	// �f�t�H���g�ł͂O�i�_�u���^�b�v�Ȃ��j

	for(i = 0; i < EVENT_TIME_MAX; i++)
	{
		btn->event_time[i] = 0;
	}

	btn->repeat_time = 0;
}
//------------------------------------------------------------------
/**
 * �{�^���X�e�[�^�X�ύX
 *
 * @param   btn			�{�^�����[�N
 * @param   state		�X�e�[�^�X
 *
 */
//------------------------------------------------------------------
static void ButtonStateChange( BUTTON *btn, u32 state )
{
	btn->state = state;
	btn->timer = 0;
}
//------------------------------------------------------------------
/**
 * �^�C�}�[�ێ������܂܃X�e�[�^�X�ύX
 *
 * @param   btn		
 * @param   state		
 *
 */
//------------------------------------------------------------------
static void ButtonStateChangeNoReset( BUTTON *btn, u32 state )
{
	btn->state = state;
}
//------------------------------------------------------------------
/**
 * �{�^���ʃ^�C�}�[�C���N�������g�B
 *
 * @param   btn		�{�^�����[�N
 *
 * @retval	BOOL	TRUE�ŃC�x���g����
 */
//------------------------------------------------------------------
static void ButtonTimerInc( BUTTON *btn )
{
	if( btn->timer < TIMER_MAX ){
		btn->timer++;
	}
}

//------------------------------------------------------------------
/**
 * �^�C�}�[�C�x���g�����Ȃ�ID��n��
 *
 * @param   btn		�{�^�����[�N
 *
 * @retval  u32		�C�x���gID�i�������Ȃ���� BUTTON_EVENT_NULL�j
 */
//------------------------------------------------------------------
static u32 TimeEventCheck( BUTTON* btn )
{
	u32 i;

	for(i = 0; i < EVENT_TIME_MAX; i++)
	{
		if(btn->event_time[i] == btn->timer)
		{
			return BMN_EVENT_TIMER0 + i;
		}
	}


	return BMN_EVENT_NULL;
}


//------------------------------------------------------------------
/**
 * �{�^����ԁF�������
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 StateFree( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	if(btn->touch_flag){
		if(tp_trg){
			ButtonStateChange( btn, STATE_HOLD );
			return BMN_EVENT_TOUCH;
		}
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * �{�^����ԁF������Ă���
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 StateHold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	ButtonTimerInc( btn );

	// �{�^����������
	if( btn->touch_flag ){
		u32 event_idx;

		event_idx = TimeEventCheck( btn );

		if( event_idx != BMN_EVENT_NULL )
		{
			return event_idx;
		}

		if( btn->repeat_time != 0 && btn->timer >= btn->repeat_time )
		{
			btn->timer = 0;
			return BMN_EVENT_REPEAT;
		}

	}
	// �X�N���[���ɂ͐G���Ă邯�ǃ{�^�������ĂȂ�
	else if(tp_cont){
		ButtonStateChange( btn, STATE_FREE );
		return BMN_EVENT_OUT;
	}
	// �X�N���[���ɐG���ĂȂ�
	else{
		if(btn->doubletap_time){
			ButtonStateChangeNoReset( btn, STATE_DOUBLETAP_CHECK );
		}else{
			ButtonStateChange( btn, STATE_FREE );
			return BMN_EVENT_TAP;
		}
	}

	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * �{�^����ԁF������āA�_�u���^�b�v�����邩�`�F�b�N
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 StateDoubleTapCheck( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	ButtonTimerInc( btn );

	if( btn->timer > btn->doubletap_time ){
		ButtonStateChange( btn, STATE_FREE );
		return BMN_EVENT_TAP;
	}

	if( btn->touch_flag && tp_trg )
	{
		ButtonStateChange( btn, STATE_DOUBLETAP );
		return BMN_EVENT_DOUBLETAP;
	}

	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * �_�u���^�b�v�m���
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 StateDoubleTap( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	// �{�^����������
	if( btn->touch_flag ){

		ButtonTimerInc( btn );

	}else{
		ButtonStateChange( btn, STATE_FREE );
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * �������Z�b�g��
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 StateReset( BUTTON *btn, BOOL tp_cont,  BOOL tp_trg )
{
	if( btn->touch_flag == FALSE )
	{
		ButtonStateChange( btn, STATE_FREE );
	}
	return BMN_EVENT_NULL;
}

