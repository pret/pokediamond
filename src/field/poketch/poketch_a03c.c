//============================================================================================
/**
 * @file	poketch_a03c.c
 * @bfief	�|�P�b�`�i�A�v��No03�F�������j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_button.h"
#include "poketch_a03.h"
#include "poketch_prv.h"


//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;

	u8        quit_req_flag;
	u8        prevFrameWriteFlag;

	u32       appNumber;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	POKETCH_BUTTON_MAN*	button_man;

}APPWORK;


//==============================================================
// �{�^���z�u
//==============================================================
static const TP_HIT_TBL ButtonRectData[] = {
	{  24,  88,  180, 204, },
	{ 104, 168,  180, 204, },
};

enum BUTTON_ID {
	BUTTON_ERASER,
	BUTTON_PEN,
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
static BOOL Poketch_A03_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A03_Main(TCB_PTR tcb, void *wk_adrs);
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs );
static void Poketch_A03_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL CheckOverWrite( APPWORK* wk );
static BOOL CheckWriteCont( APPWORK* wk );
static void InterpolateCommandSet( APPWORK* wk, u32 sx, u32 sy, u32 ex, u32 ey );
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A03_Init, Poketch_A03_Quit);
}

//------------------------------------------------------------------
/**
 * �A�v���������֐�
 *
 * @param   wk_ptr		���[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 * @param   conwk		�A�v�����{�̂�������擾����ۂɕK�v�ƂȂ郏�[�N�i�A�v���ւ͔���J�j
 * @param   bgl			BGL���W���[���w�b�_
 * @param   app_number	�A�v���i���o�[
 */
//------------------------------------------------------------------
static BOOL Poketch_A03_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 app_number)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, app_number ))
		{
			if( TCB_Add(Poketch_A03_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber )
{
	wk->vpara.appNumber = appNumber;
	wk->vpara.touch_mode = TOUCHMODE_PEN;

	if( Poketch_A03_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		int x, y;
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->prevFrameWriteFlag = FALSE;

		wk->button_man = PBTN_Create( ButtonRectData, NELEMS(ButtonRectData), BmnCallback, wk, POKETCH_APP_CTRL_HEAPID );

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
	PBTN_Delete( wk->button_man );
	Poketch_A03_DeleteViewWork( wk->vwk );
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
static void Poketch_A03_Main(TCB_PTR tcb, void *wk_adrs)
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
	if( touch_event == BMN_TOUCH_ON )
	{
		if( (wk->vpara.touch_mode == TOUCHMODE_PEN    && btn_idx == BUTTON_ERASER)
		||	(wk->vpara.touch_mode == TOUCHMODE_ERASER && btn_idx == BUTTON_PEN)
		)
		{
			wk->vpara.touch_mode ^= 1;
			Poketch_A03_SetViewCommand( wk->vwk, CMD_BUTTON_UPDATE );
		}
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
static void Poketch_A03_Quit(void *wk_adrs)
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
		Poketch_A03_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A03_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * �V�[�P���X�F���C������
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	extern void Poketch_A03_SetViewCommandVintr(VIEWWORK* wk, u32 cmd);

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
	}

	switch( wk->seq ){
	case 0:
		if( PoketchIsSleepMode( wk->conwk ) )
		{
			break;
		}
		if( wk->prevFrameWriteFlag )
		{
			u32  prev_x, prev_y;

			prev_x = wk->vpara.pixel_update_x;
			prev_y = wk->vpara.pixel_update_y;
			if( CheckWriteCont( wk ) )
			{
				InterpolateCommandSet( wk, prev_x, prev_y, wk->vpara.pixel_update_x, wk->vpara.pixel_update_y );
//				Poketch_A03_SetViewCommand( wk->vwk, CMD_PIXEL_SET_END );
			}
			else
			{
				wk->prevFrameWriteFlag = FALSE;
			}
		}
		else
		{
			if( CheckOverWrite( wk ) )
			{
				Poketch_A03_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				wk->prevFrameWriteFlag = TRUE;
			}
		}
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * ���݂̃s�N�Z���ƈقȂ��Ԃɏ㏑������悤�Ƃ��Ă��邩�`�F�b�N
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL CheckOverWrite( APPWORK* wk )
{
	u32 x, y;

	// �^�b�`�p�l���ɐG��Ă�
	if( PoketchGetTPCont( &x, &y ) )
	{
		// �������L���͈͂ł���
		if( ((u32)( x - AREA_START_X) < (u32)(AREA_END_X - AREA_START_X))
		&	((u32)( y - AREA_START_Y) < (u32)(AREA_END_Y - AREA_START_Y))
		){
			// DS�̃h�b�g�P�ʂ���|�P�b�`�s�N�Z���P�ʂ�
			x = (x - AREA_START_X) >> 1;
			y = (y - AREA_START_Y) >> 1;
			// ���݂̃s�N�Z���ƈႤ��Ԃ��������܂�悤�Ƃ��Ă���Ȃ�`��p�����[�^�Z�b�g
			if( wk->vpara.pixel[x][y] != wk->vpara.touch_mode )
			{
				wk->vpara.pixel[x][y] = wk->vpara.touch_mode;
				wk->vpara.pixel_update_x = x;
				wk->vpara.pixel_update_y = y;
				return TRUE;
			}
		}
	}
	return FALSE;
}

static BOOL CheckWriteCont( APPWORK* wk )
{
	u32 x, y;
	// �^�b�`�p�l���ɐG��Ă�
	if( PoketchGetTPCont( &x, &y ) )
	{
		// �������L���͈͂ł���
		if( ((u32)( x - AREA_START_X) < (u32)(AREA_END_X - AREA_START_X))
		&	((u32)( y - AREA_START_Y) < (u32)(AREA_END_Y - AREA_START_Y))
		){
			x = (x - AREA_START_X) >> 1;
			y = (y - AREA_START_Y) >> 1;
			wk->vpara.pixel_update_x = x;
			wk->vpara.pixel_update_y = y;
			return TRUE;
		}
	}
	return FALSE;
}

static void InterpolateCommandSet( APPWORK* wk, u32 sx, u32 sy, u32 ex, u32 ey )
{
	extern void Poketch_A03_SetViewCommandVintr(VIEWWORK* wk, u32 cmd);

	u32   diffX, diffY, add, intVal;
	fx32  fxval, fxadd;

	if( (sy == ey) && (sx == ex ) ){
		return;
	}

	diffX = (ex > sx)? (ex - sx) : (sx - ex);
	diffY = (ey > sy)? (ey - sy) : (sy - ey);

	if( diffX > diffY )
	{
		add = (ex > sx)? 1 : -1;
		if( diffX ){
			fxadd = ((ey-sy) * FX32_ONE);
			fxadd /= (s32)(diffX);
		}else{
			fxadd = 0;
		}

		fxval = (sy << FX32_SHIFT) + fxadd;
		sx += add;

		while( sx != ex )
		{
			intVal = fxval >> FX32_SHIFT;

			if( sx < PIXEL_H_MAX && intVal < PIXEL_V_MAX )
			{
				if(wk->vpara.pixel[sx][intVal] != wk->vpara.touch_mode)
				{
					wk->vpara.pixel[sx][intVal] = wk->vpara.touch_mode;
					wk->vpara.pixel_update_x = sx;
					wk->vpara.pixel_update_y = intVal;
					Poketch_A03_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				}
			}
			sx += add;
			fxval += fxadd;
		}
	}
	else
	{
		add = (ey > sy)? 1 : -1;
		if( diffY ){
			fxadd = (ex-sx) * FX32_ONE;
			fxadd /= (s32)diffY;
		}else{
			fxadd = 0;
		}
		fxval = (sx << FX32_SHIFT) + fxadd;
		sy += add;

		while( sy != ey )
		{
			intVal = fxval >> FX32_SHIFT;
			if( sy < PIXEL_V_MAX && intVal < PIXEL_H_MAX )
			{
				if(wk->vpara.pixel[intVal][sy] != wk->vpara.touch_mode)
				{
					wk->vpara.pixel[intVal][sy] = wk->vpara.touch_mode;
					wk->vpara.pixel_update_x = intVal;
					wk->vpara.pixel_update_y = sy;
					Poketch_A03_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				}
			}
			sy += add;
			fxval += fxadd;
		}
	}

	if( ey < PIXEL_V_MAX && ex < PIXEL_H_MAX )
	{
		wk->vpara.pixel_update_x = ex;
		wk->vpara.pixel_update_y = ey;
		Poketch_A03_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
	}
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
		Poketch_A03_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A03_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
