//============================================================================================
/**
 * @file	poketch_a01_c.c
 * @bfief	�|�P�b�`�i�A�v��No01 �X�g�b�v�E�H�b�`�j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "gflib\apptimer.h"

#include "poketch_button.h"
#include "poketch_a01.h"
#include "poketch_prv.h"


//==============================================================
// backup 
//==============================================================
typedef struct {

	BOOL action_flag;

	u32  hour;
	u32  min;
	u32  sec;
	u32  msec;

	u64  start_tick;
	u64  stop_tick;

}BACKUP_WORK;

//==============================================================
// main Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;
	u8        prev_main_seq;

	u8        button_event;
	u16       time;

	u32       appNumber;

	u64       start_tick;
	u64       stop_tick;

	POKETCH_A01_VIEW_PARAM  vpara;
	BACKUP_WORK             backup;


	POKETCH_BUTTON_MAN*		button;
	POKETCH_A01_VIEWWORK*	vwk;
	CONTACT_WORK*			conwk;

}APPWORK;

//==============================================================
// �V�[�P���X
//==============================================================
enum {
	SEQ_INIT,
	SEQ_IDLE,
	SEQ_COUNT,
	SEQ_RESET1,
	SEQ_RESET2,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A01_Init(void **wk_ptr, CONTACT_WORK* contact_wk, GF_BGL_INI* bgl, u32 appNumber);
static BOOL SetupWork( APPWORK *wk, GF_BGL_INI* bgl, u32 appNumber );
static void CleanupWork( APPWORK *wk );
static void Poketch_A01_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A01_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqCount( APPWORK *wk );
static BOOL SeqReset1( APPWORK *wk );
static BOOL SeqReset2( APPWORK *wk );
static BOOL SeqQuit(APPWORK *wk);
static BOOL BmnSetup( APPWORK* wk );
static void BmnCleanup( APPWORK *wk );
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void CounterDataReset( APPWORK* wk );
static void CounterStart( APPWORK *wk );
static void CounterStop( APPWORK *wk );
static void CounterUpdate( APPWORK* wk, POKETCH_A01_VIEW_PARAM* vpara );



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A01_Init, Poketch_A01_Quit);
}

//------------------------------------------------------------------
/**
 * �A�v���������֐�
 *
 * @param   wk_ptr		���[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 */
//------------------------------------------------------------------
static BOOL Poketch_A01_Init(void **wk_ptr, CONTACT_WORK* contact_wk, GF_BGL_INI* bgl, u32 appNumber)
{
	APPWORK *wk = (APPWORK*)sys_AllocMemory(POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, bgl, appNumber ))
		{
			wk->conwk = contact_wk;
			if( TCB_Add(Poketch_A01_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				return TRUE;
			}
		}
		else
		{
			sys_FreeMemoryEz( wk );
			wk = NULL;
		}
	}

	return FALSE;


}
//------------------------------------------------------------------
/**
 * ���[�N�̃Z�b�g�A�b�v
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static BOOL SetupWork( APPWORK *wk, GF_BGL_INI* bgl, u32 appNumber )
{
	wk->appNumber = appNumber;

	if(PoketchWork_Load(appNumber, &(wk->backup), sizeof(wk->backup)))
	{
		wk->start_tick = wk->backup.start_tick;
		wk->stop_tick = wk->backup.stop_tick;
		wk->vpara.hour = wk->backup.hour;
		wk->vpara.min = wk->backup.min;
		wk->vpara.sec = wk->backup.sec;
		wk->vpara.msec = wk->backup.msec;

		wk->vpara.counter_action_flag = wk->backup.action_flag;
		if( wk->vpara.counter_action_flag )
		{
			wk->vpara.btn = BTN_STATE_COUNT;
		}
		else
		{
			wk->vpara.btn = BTN_STATE_FREE;
		}
	}
	else
	{
		CounterDataReset( wk );
		wk->vpara.btn = BTN_STATE_FREE;
	}

	if(Poketch_A01_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->prev_main_seq = wk->main_seq;
		wk->quit_req_flag = FALSE;

		if( BmnSetup( wk ) ){
			return TRUE;
		}
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ���[�N�̃N���[���A�b�v
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CleanupWork( APPWORK *wk )
{
	wk->backup.start_tick = wk->start_tick;
	wk->backup.stop_tick = wk->stop_tick;
	wk->backup.hour = wk->vpara.hour;
	wk->backup.min = wk->vpara.min;
	wk->backup.sec = wk->vpara.sec;
	wk->backup.msec = wk->vpara.msec;
	wk->backup.action_flag = wk->vpara.counter_action_flag;
	PoketchWork_Save( wk->appNumber, &(wk->backup), sizeof(wk->backup) );

	BmnCleanup( wk );
	Poketch_A01_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz(wk);
}
//------------------------------------------------------------------
/**
 * �A�v�����C���֐�
 *
 * @param   wk_adrs		���[�N�A�h���X
 *
 */
//------------------------------------------------------------------
static void Poketch_A01_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqCount,
		SeqReset1,
		SeqReset2,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		if(	wk->quit_req_flag && (wk->main_seq != SEQ_QUIT) )
		{
			ChangeSeq( wk, SEQ_QUIT );
			wk->quit_req_flag = FALSE;
		}

		PoketchButtonMainCall( wk->conwk, wk->button );
		CounterUpdate( wk, &(wk->vpara) );

		if( seqtbl[wk->main_seq](wk) )
		{
			CleanupWork( wk );
			TCB_Delete(tcb);
			PoketchNoticeAppEnd( wk->conwk );
		}
	}
	else
	{
		SDK_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �A�v���I���֐�
 *
 * @param   wk_adrs		���[�N�A�h���X
 *
 */
//------------------------------------------------------------------
static void Poketch_A01_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
}

//------------------------------------------------------------------
/**
 * �V�[�P���X�ύX
 *
 * @param   wk		���[�N�|�C���^
 * @param   seq		�ύX��̃V�[�P���X�i���o�[
 *
 */
//------------------------------------------------------------------
static void ChangeSeq(APPWORK *wk, u32 seq)
{
	wk->prev_main_seq = wk->main_seq;
	if(wk->quit_req_flag == FALSE)
	{
		wk->main_seq = seq;
	}
	else
	{
		wk->main_seq = SEQ_QUIT;
		wk->quit_req_flag = FALSE;
	}

	wk->seq = 0;
}


//------------------------------------------------------------------
/**
 * �V�[�P���X�F��ʍ\�z
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqInit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A01_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A01_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );

			if( wk->vpara.counter_action_flag )
			{
				ChangeSeq( wk, SEQ_COUNT );
			}
			else
			{
				ChangeSeq( wk, SEQ_IDLE );
			}
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�{�^��������҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			wk->vpara.btn = BTN_STATE_TOUCH;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			wk->seq++;
		}
		break;

	case 1:
		switch( wk->button_event ){
		case BMN_EVENT_OUT:
			wk->vpara.btn = BTN_STATE_FREE;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			wk->seq--;
			break;

		case BMN_EVENT_TAP:
			wk->vpara.btn = BTN_STATE_COUNT;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			CounterStart( wk );
			ChangeSeq( wk, SEQ_COUNT );
			break;

		case BMN_EVENT_TIMER0:
			wk->vpara.btn = BTN_STATE_RESET1;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_RESET1 );
			break;
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�J�E���g��
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqCount( APPWORK *wk )
{
	switch( wk->seq ){
	case 0:
		if(wk->button_event == BMN_EVENT_TOUCH){
			wk->vpara.btn = BTN_STATE_TOUCH;
			CounterStop( wk );
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			wk->seq++;
		}
		break;

	case 1:
		switch( wk->button_event ){
		case BMN_EVENT_OUT:
			wk->vpara.btn = BTN_STATE_FREE;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_IDLE );
			break;

		case BMN_EVENT_TAP:
			wk->vpara.btn = BTN_STATE_FREE;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_IDLE );
			break;

		case BMN_EVENT_TIMER0:
			wk->vpara.btn = BTN_STATE_RESET1;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_RESET1 );
			break;
		}
		break;
	}

	return FALSE;

}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F���Z�b�g�O�G�t�F�N�g�P
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqReset1( APPWORK *wk )
{
	switch( wk->button_event ) {
	case BMN_EVENT_TAP:
		if( wk->prev_main_seq == SEQ_IDLE )
		{
			CounterStart( wk );
			wk->vpara.btn = BTN_STATE_COUNT;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_COUNT );
			break;
		}
		/* fallthru */
	case BMN_EVENT_OUT:
		wk->vpara.btn = BTN_STATE_FREE;
		Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
		ChangeSeq( wk, SEQ_IDLE );
		break;


	case BMN_EVENT_TIMER1:
		wk->vpara.btn = BTN_STATE_RESET2;
		Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
		ChangeSeq( wk, SEQ_RESET2 );
		break;
	}

	return FALSE;

}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F���Z�b�g�O�G�t�F�N�g�Q
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqReset2( APPWORK *wk )
{
	enum {
		EFF_TIME =  90,
		BOMB_TIME = 60,
		BURN_TIME = 30,
	};

	switch(wk->seq){
	case 0:
		wk->time = 0;
		wk->seq++;
		/* fallthru */
	case 1:
		if(++(wk->time) >= EFF_TIME)
		{
			wk->vpara.btn = BTN_STATE_BOMB;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			wk->time = 0;
			wk->seq++;
		}
		break;

	case 2:
		if(++(wk->time) >= BOMB_TIME)
		{
			wk->vpara.btn = BTN_STATE_BURN;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			CounterDataReset( wk );
			wk->time = 0;
			wk->seq++;
		}
		break;

	case 3:
	// ���ꂾ���̓A�j���I���ŏI��������
		if( Poketch_A01_WaitViewCommand( wk->vwk, CMD_BTN_UPDATE) )
		{
			wk->vpara.btn = BTN_STATE_FREE;
			Poketch_A01_SetViewCommand( wk->vwk, CMD_BTN_UPDATE );
			ChangeSeq( wk, SEQ_IDLE );
		}
		break;
	}
	
	return FALSE;
}


//------------------------------------------------------------------
/**
 * �V�[�P���X�F�I������
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqQuit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		wk->vpara.btn = BTN_STATE_QUIT;
		Poketch_A01_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A01_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}








/*====================================================================================*/
/*                                                                                    */
/*  �{�^���Ǘ��}�l�[�W������                                                          */
/*                                                                                    */
/*====================================================================================*/

enum {
	BUTTON_TIMER_RESETEFF1 = 15,							// ���Z�b�g�G�t�F�N�g�n��
	BUTTON_TIMER_RESETEFF2 = BUTTON_TIMER_RESETEFF1 + 60,	// ���Z�b�g�G�t�F�N�g����
};



//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W���Z�b�g�A�b�v
 *
 * @param   wk			�A�v�����[�N
 *
 * @retval  BOOL		TRUE�Ő���
 */
//------------------------------------------------------------------
static BOOL BmnSetup( APPWORK* wk )
{
	static const TP_HIT_TBL ButtonHitData[] = {
		{ TP_USE_CIRCLE, 112, 112, 39 },
	};

	wk->button = PBTN_Create( ButtonHitData, NELEMS(ButtonHitData), BmnCallBack, wk, POKETCH_APP_CTRL_HEAPID );
	if( wk->button != NULL )
	{
		PBTN_SetEventTime( wk->button, 0, 0, BUTTON_TIMER_RESETEFF1 );
		PBTN_SetEventTime( wk->button, 0, 1, BUTTON_TIMER_RESETEFF2 );
		wk->button_event = BMN_EVENT_NULL;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W���N���[���A�b�v
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void BmnCleanup( APPWORK *wk )
{
	PBTN_Delete( wk->button );
}
//------------------------------------------------------------------
/**
 * �{�^���Ǘ��}�l�[�W������̃R�[���o�b�N�֐�
 *
 * @param   idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs )
{
	APPWORK *wk = (APPWORK*)wk_adrs;

	wk->button_event = event;
}


/*====================================================================================*/
/*                                                                                    */
/*  �J�E���^�[����Ǘ�                                                                */
/*                                                                                    */
/*====================================================================================*/

static void CounterDataReset( APPWORK* wk )
{
	wk->vpara.counter_action_flag = FALSE;
	wk->vpara.counter_reset_flag = TRUE;
	wk->vpara.msec = 0;
	wk->vpara.sec = 0;
	wk->vpara.min = 0;
	wk->vpara.hour = 0;
	wk->start_tick = 0;
	wk->stop_tick = 0;
}

static void CounterStart( APPWORK *wk )
{
	if( wk->start_tick )
	{
		wk->start_tick += ( APTM_GetData() - wk->stop_tick );
	}
	else
	{
		wk->start_tick = APTM_GetData();
	}
	wk->vpara.counter_action_flag = TRUE;
	wk->vpara.counter_reset_flag = FALSE;
}


static void CounterStop( APPWORK *wk )
{
	wk->stop_tick = APTM_GetData();
	wk->vpara.counter_action_flag = FALSE;
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void CounterUpdate( APPWORK* wk, POKETCH_A01_VIEW_PARAM* vpara )
{
	if( vpara->counter_action_flag )
	{
		u64  upper, lower, tick;

		tick = APTM_GetData() - wk->start_tick;

	// upper�ɕb�Alower�Ɏc��̃~���b������
		CP_SetDiv64_32( APTM_CalcMsec(tick), 1000 );
		upper = CP_GetDivResult64();
		lower = CP_GetDivRemainder64();
		CP_SetDiv64_32( lower, 10 );
		vpara->msec = CP_GetDivResult32();

	// �b��60�Ŋ����� upper �ɕ��A�]�肪�b
		CP_SetDiv64_32( upper, 60 );
		upper = CP_GetDivResult64();
		vpara->sec = CP_GetDivRemainder32();

	// ����60�Ŋ����� upper �Ɏ��A�]�肪��
		CP_SetDiv64_32( upper, 60 );
		upper = CP_GetDivResult64();
		vpara->min = CP_GetDivRemainder32();

		if( upper >= 24 )
		{
			CP_SetDiv64_32( upper, 24 );
			upper = CP_GetDivRemainder32();
		}

		vpara->hour = (u32)upper;

	}
}
