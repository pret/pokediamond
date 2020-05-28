//============================================================================================
/**
 * @file	poketch_a24c.c
 * @bfief	�|�P�b�`�i�A�v��Noa24�F�J���[�`�F���W���[�j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"

#include "poketch_a24.h"
#include "poketch_prv.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;

	u8        prev_bar_pos;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	POKETCH_DATA*  savedata;

}APPWORK;

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
static BOOL Poketch_A24_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A24_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A24_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL check_update_bar_pos( APPWORK* wk );
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A24_Init, Poketch_A24_Quit);
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
static BOOL Poketch_A24_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A24_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	wk->savedata = PoketchGetSaveData(conwk);
	wk->vpara.bar_pos = PoketchData_GetColorType(wk->savedata);
	wk->prev_bar_pos = wk->vpara.bar_pos;
	if( Poketch_A24_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

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
	Poketch_A24_DeleteViewWork( wk->vwk );
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
static void Poketch_A24_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
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
static void Poketch_A24_Quit(void *wk_adrs)
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
		Poketch_A24_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A24_WaitViewCommand( wk->vwk, CMD_INIT ))
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

	switch( wk->seq ){
	case 0:
		if( check_update_bar_pos( wk ) )
		{
			Poketch_A24_SetViewCommand( wk->vwk, CMD_UPDATE_BARPOS );
			wk->seq++;
		}
		break;

	case 1:
		if( Poketch_A24_WaitViewCommand( wk->vwk, CMD_UPDATE_BARPOS ) )
		{
			wk->seq = 0;
		}
		break;
	}


	return FALSE;
}

static BOOL check_update_bar_pos( APPWORK* wk )
{
	enum {
		TOUCH_V_RANGE = 12,
		TOUCH_H_RANGE = 8,

		TOUCH_RANGE_TOP = BAR_YPOS-TOUCH_V_RANGE,
		TOUCH_RANGE_BOTTOM = BAR_YPOS + TOUCH_V_RANGE,
		TOUCH_RANGE_LEFT = BAR_XORG - TOUCH_H_RANGE,
		TOUCH_RANGE_RIGHT = (BAR_XORG+(POKETCH_COLOR_TYPE_MAX-1)*BAR_MOVE_DIFF)+BAR_MOVE_DIFF,
	};

	if( PoketchIsSleepMode(wk->conwk) == FALSE )
	{
		u32 x, y;
		if( GF_TP_GetPointCont(&x,&y) )
		{
			if(	(TOUCH_RANGE_TOP<=y)  && (y<TOUCH_RANGE_BOTTOM) 
			&&	(TOUCH_RANGE_LEFT<=x) && (x<TOUCH_RANGE_RIGHT)
			){

				u32 p = (x - TOUCH_RANGE_LEFT) / BAR_MOVE_DIFF;
				if(p>=POKETCH_COLOR_TYPE_MAX)
				{
					// �O�̂���
					p = POKETCH_COLOR_TYPE_MAX-1;
				}
				if( p != wk->prev_bar_pos )
				{
					wk->vpara.bar_pos = p;
					wk->prev_bar_pos = p;
					PoketchData_SetColorType( wk->savedata, p );
					return TRUE;
				}
			}
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
		Poketch_A24_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A24_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
