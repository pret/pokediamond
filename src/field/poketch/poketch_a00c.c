//============================================================================================
/**
 * @file	poketch_a00c.c
 * @bfief	�|�P�b�`�i�A�v��No00 = �f�W�^�����v�j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "system\pm_rtc.h"

#include "poketch_button.h"
#include "poketch_a00.h"
#include "poketch_prv.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;

	u8        rtc_callback_end_flag;
	u8        rtc_update_flag;
	u8        rtc_prev_minute;

	u8        backlight_update_flag;

	u32       rtc_wait_time;
	u32       rtc_wait_cnt;

	POKETCH_BUTTON_MAN*	button_man;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

}APPWORK;

//==============================================================
// �萔
//==============================================================
enum {
	RTC_WAIT_MARGIN_TIME = 30,	// �������ς��n�Y�̃t���[�����炱�̃t���[�����O�̎��_�Ń`�F�b�N���n�߂�
};



//==============================================================
// �V�[�P���X
//==============================================================
enum {
	SEQ_INIT,
	SEQ_IDLE,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A00_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A00_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A00_Quit(void *wk_adrs);
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs );
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);


//==============================================================
// �{�^���ʒu�ienum BUTTON_ID �ɑΉ��j
//==============================================================
#define ORGP(c)		((c)*8)
#define ENDP(c)		((c)*8+7)

static const TP_HIT_TBL ButtonRectData[] = {
	{  ORGP(2), ENDP(21),  ORGP(2), ENDP(25),  },
};


//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A00_Init, Poketch_A00_Quit);
}

//------------------------------------------------------------------
/**
 * �A�v���������֐�
 *
 * @param   wk_ptr		���[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 * @param   conwk		�A�v�����{�̂�������擾����ۂɕK�v�ƂȂ郏�[�N�i�A�v���ւ͔���J�j
 * @param   bgl			BGL���W���[���w�b�_
 * @param   param		�J���[�E���m�N���ȂǓ���^�C�v�i�A�v���ˑ��j
 */
//------------------------------------------------------------------
static BOOL Poketch_A00_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A00_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				return TRUE;
			}
		}
		sys_FreeMemoryEz( wk );
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
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param )
{
	if( Poketch_A00_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->rtc_callback_end_flag = TRUE;
		wk->backlight_update_flag = FALSE;

		wk->vpara.backlight = 0;

	// ���Ԏ擾�B�w���Ȓl�������Ă������̂��߂Ɋۂ߂Ă���
		GF_RTC_GetTime( &(wk->vpara.time) );
		if( wk->vpara.time.hour >= 24 ){
			wk->vpara.time.hour %= 24;
		}
		if( wk->vpara.time.minute >= 60 ){
			wk->vpara.time.hour %= 60;
		}
		wk->rtc_prev_minute = wk->vpara.time.minute;


		wk->button_man = PBTN_Create( ButtonRectData, NELEMS(ButtonRectData),
					BmnCallback, wk, POKETCH_APP_CTRL_HEAPID );
		if(wk->button_man == NULL)
		{
			return FALSE;
		}

		wk->conwk = conwk;
		return TRUE;
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
	Poketch_A00_DeleteViewWork( wk->vwk );
	PBTN_Delete( wk->button_man );
	sys_FreeMemoryEz( wk );
}
//------------------------------------------------------------------
/**
 * �A�v�����C���֐�
 *
 * @param   wk_adrs		���[�N�A�h���X
 *
 */
//------------------------------------------------------------------
static void Poketch_A00_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;


	if( wk->main_seq < NELEMS(seqtbl) )
	{
		PoketchButtonMainCall( wk->conwk, wk->button_man );

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
static void Poketch_A00_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * �{�^���}�l�[�W���R�[���o�b�N�֐�
 *
 * @param   btn_idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs )
{
	APPWORK* wk = (APPWORK*)wk_adrs;

	switch( touch_event ){
	case BMN_TOUCH_ON:
		wk->vpara.backlight = 1;
		wk->backlight_update_flag = TRUE;
		break;

	case BMN_TOUCH_OFF:
		wk->vpara.backlight = 0;
		wk->backlight_update_flag = TRUE;
		break;
	}
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
	if(wk->quit_req_flag == FALSE)
	{
		wk->main_seq = seq;
	}
	else
	{
		wk->main_seq = SEQ_QUIT;
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
		Poketch_A00_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A00_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_IDLE );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�Ȃ�����Ȃ�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( wk->backlight_update_flag )
	{
		wk->backlight_update_flag = FALSE;
		Poketch_A00_SetViewCommand( wk->vwk, CMD_BACKLIGHT_UPDATE );
	}

	if(Poketch_A00_WaitViewCommand( wk->vwk, CMD_TIME_UPDATE ))
	{
		wk->rtc_prev_minute = wk->vpara.time.minute;
		GF_RTC_GetTime( &(wk->vpara.time) );
		if( wk->rtc_prev_minute != wk->vpara.time.minute )
		{
			Poketch_A00_SetViewCommand( wk->vwk, CMD_TIME_UPDATE );
		}
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
		Poketch_A00_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A00_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}


