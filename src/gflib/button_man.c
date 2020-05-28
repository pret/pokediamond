//============================================================================================
/**
 * @file	button_man.c
 * @bfief	�{�^����ԊǗ��}�l�[�W��
 * @date	2005.11.08
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "gflib\button_man.h"




//==============================================================================
// �萔
//==============================================================================
//-----------------------------------------------
/**
 * �{�^�����
 */
//-----------------------------------------------
enum {
	STATE_FREE = 0,
	STATE_HOLD,
};

//-----------------------------------------------
/**
 * ���̂�
 */
//-----------------------------------------------
enum {
	BMN_EVENT_NULL = 0xffffffff,	///< �{�^���C�x���g�����l�i�����C�x���g���������Ă��Ȃ���Ԃ������j
	HOLD_TIMER_MAX = 0xffff,		///< �^�C�}�[�ő�l
};

//==============================================================================
// �\���̒�`
//==============================================================================

//----------------------------------------------
/**
 * �ʂ̃{�^�����
 */
//----------------------------------------------
typedef struct {
	u8  state;				///< ���
	u8  touch_flag;			///< �G���Ă���t���O
	u16 timer;
}BUTTON;

//----------------------------------------------
/**
 * �}�l�[�W���S�̂̃��[�N
 */
//----------------------------------------------
struct _BUTTON_MAN {
	const TP_HIT_TBL*	hit_tbl;
	u32					btn_cnt;
	pBmnCallBackFunc	callback_func;
	void*				callback_arg;

	BUTTON *btn;
};



//==============================================================================
// Prototype
//==============================================================================
static void button_state_init( BUTTON* btn );
static u32 button_proc_free( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 button_proc_hold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static void button_state_change( BUTTON *btn, u32 state );


//======================================================================================================
/**
 * �{�^���Ǘ��}�l�[�W���쐬
 *
 * @param   hit_tbl			[in]  �����蔻��e�[�u��
 * @param   btn_cnt			[in]  hit_tbl �̗v�f���i=���ꂪ�o�^����{�^���̐��Ƃ������Ɓj
 * @param   callback		[in]  �{�^���C�x���g�������ɌĂяo�����R�[���o�b�N�֐�
 * @param   callback_arg	[in]  callback �Ăяo�����Ɉ����Ƃ��ēn�����C�ӂ̃|�C���^
 * @param   heapID			[in]  �}�l�[�W���̈�쐬�p�q�[�vID
 *
 * @retval  BUTTON_MAN*		�}�l�[�W���|�C���^
 */
//======================================================================================================
BUTTON_MAN* BMN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBackFunc callback, void *callback_arg, u32 heapID )
{
	BUTTON_MAN *bmn;

	GF_ASSERT( btn_cnt > 0 );

	bmn = sys_AllocMemory( heapID, sizeof(BUTTON_MAN) );
	if(bmn)
	{
		bmn->hit_tbl = hit_tbl;
		bmn->btn_cnt = btn_cnt;
		bmn->callback_func = callback;
		bmn->callback_arg = callback_arg;

		bmn->btn = sys_AllocMemory( heapID, sizeof(BUTTON) * btn_cnt );
		if(bmn->btn)
		{
			u32 i;

			for(i=0; i<btn_cnt; i++)
			{
				button_state_init( &bmn->btn[i] );
			}
		}
		else
		{
			sys_FreeMemoryEz( bmn );
			bmn = NULL;
		}
	}
	return bmn;
}
//------------------------------------------------------------------
/**
 * �{�^�����[�N������
 *
 * @param   btn		�{�^�����[�N
 *
 */
//------------------------------------------------------------------
static void button_state_init( BUTTON* btn )
{
	btn->state = STATE_FREE;
	btn->touch_flag = FALSE;
	btn->timer = 0;
}


//======================================================================================================
/**
 * �{�^���Ǘ��}�l�[�W������
 *
 * @param   bmn		�}�l�[�W���|�C���^
 */
//======================================================================================================
void BMN_Delete( BUTTON_MAN *bmn )
{
	GF_ASSERT( bmn );
	sys_FreeMemoryEz( bmn->btn );
	sys_FreeMemoryEz( bmn );
}

//======================================================================================================
/**
 * �{�^���Ǘ��}�l�[�W�����C��
 *
 * �e�{�^����Ԃ̃`�F�b�N���X�V�A�C�x���g����������΃R�[���o�b�N�Ăяo�����s���B
 *
 * @param   bmn		�}�l�[�W���|�C���^
 *
 */
//======================================================================================================
void BMN_Main( BUTTON_MAN *bmn )
{
	static u32 (* const ButtonProc[])(BUTTON*, BOOL, BOOL ) = {
		button_proc_free,
		button_proc_hold,
	};

	BOOL tp_cont, tp_trg;
	u32 i, ev;

	tp_cont = GF_TP_GetCont();
	if( tp_cont )
	{
		tp_trg = GF_TP_GetTrg();

		for(i = 0; i < bmn->btn_cnt; i++)
		{
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
			bmn->btn[i].touch_flag = FALSE;
		}
	}


	for(i=0; i<bmn->btn_cnt; i++)
	{
		ev = ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
		if(ev != BMN_EVENT_NULL)
		{
			bmn->callback_func( i, ev, bmn->callback_arg );
		}
	}
/*
	for(i++ ; i < bmn->btn_cnt; i++)
	{
		ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
	}
*/

}
//------------------------------------------------------------------
/**
 * �{�^����ԁF�G���Ă��Ȃ�
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 button_proc_free( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	if(btn->touch_flag){
		if(tp_trg){
			button_state_change( btn, STATE_HOLD );
			return BMN_EVENT_TOUCH;
		}
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * �{�^����ԁF�G���Ă���
 *
 * @param   btn			�{�^�����[�N
 * @param   tp_cont		�^�b�`�p�l��Cont�t���O
 * @param   tp_trg		�^�b�`�p�l��Trg�t���O
 *
 * @retval  u32		���������C�x���g�^�C�v
 */
//------------------------------------------------------------------
static u32 button_proc_hold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	// �{�^����������
	if( btn->touch_flag )
	{
		if( btn->timer < HOLD_TIMER_MAX )
		{
			btn->timer++;
		}
		return BMN_EVENT_HOLD;
	}
	// �{�^�������ĂȂ����ǃX�N���[���ɂ͐G���Ă���
	else if(tp_cont)
	{
		button_state_change( btn, STATE_FREE );
		return BMN_EVENT_SLIDEOUT;
	}
	// �X�N���[���ɐG���ĂȂ�
	else
	{
		button_state_change( btn, STATE_FREE );
		return BMN_EVENT_RELEASE;
	}

	return BMN_EVENT_NULL;
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
static void button_state_change( BUTTON *btn, u32 state )
{
	btn->state = state;
	btn->timer = 0;
}



//======================================================================================================
/**
 * �{�^�����z�[���h��Ԃɂ��鎞�A���̃z�[���h���ԁi�t���[�����j��Ԃ�
 *
 * @param   bmn		�}�l�[�W�����[�N
 * @param   idx		�{�^���C���f�b�N�X
 *
 * @retval  u32		�z�[���h���Ȃ�z�[���h���ԁA�z�[���h���ȊO�Ȃ�O
 */
//======================================================================================================
u32 BMN_GetHoldFrameCount( BUTTON_MAN* bmn, u32 idx )
{
	BUTTON *btn = &bmn->btn[idx];

	if(btn->state == STATE_HOLD)
	{
		return btn->timer;
	}
	return 0;
}
