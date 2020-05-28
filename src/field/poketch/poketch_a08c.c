//============================================================================================
/**
 * @file	poketch_a08c.c
 * @bfief	�|�P�b�`�i�A�v��Noa08�F�_�E�W���O�}�V���j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"


#include "poketch_a08.h"
#include "poketch_prv.h"
#include "poketch_sound.h"



//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;

	u8        quit_req_flag;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	HIDE_ITEM_LIST*  item_list;

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
static BOOL Poketch_A08_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A08_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A08_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL check_touch_monitor( APPWORK* wk, u32* x, u32* y );
static void check_item_find( APPWORK* wk, int touch_x, int touch_y );
static void calc_glid_to_lcd_pos( int glid_x, int glid_y, int* lcd_x, int* lcd_y );
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A08_Init, Poketch_A08_Quit);
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
static BOOL Poketch_A08_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A08_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	if( Poketch_A08_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->item_list = NULL;

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
	if( wk->item_list )
	{
		sys_FreeMemoryEz( wk->item_list );
	}
	Poketch_A08_DeleteViewWork( wk->vwk );
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
static void Poketch_A08_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A08_Quit(void *wk_adrs)
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
		Poketch_A08_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A08_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * �V�[�P���X�F���͑҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	enum {
		SEQ_1ST_TOUCH_WAIT,
		SEQ_2ND_TOUCH_WAIT,
		SEQ_STOP_ANM,
		SEQ_UPDATE_ANM,
	};
	u32 x, y;

	if(wk->quit_req_flag)
	{
		Poketch_A08_StopRippleAnm( wk->vwk );
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case SEQ_1ST_TOUCH_WAIT:
		if( check_touch_monitor( wk, &x, &y ) )
		{
			check_item_find( wk, x, y );
			PoketchSePlay(POKETCH_SE_DOWSING_TOUCH);
			Poketch_A08_SetViewCommand( wk->vwk, CMD_RIPPLE_START );
			wk->seq = SEQ_2ND_TOUCH_WAIT;
		}
		break;

	case SEQ_2ND_TOUCH_WAIT:
		if( Poketch_A08_WaitViewCommand( wk->vwk, CMD_RIPPLE_START ) )
		{
			wk->seq = SEQ_1ST_TOUCH_WAIT;
			break;
		}
		if( (PoketchGetPlayerMoveTrg( wk->conwk ) == TRUE)
		||	(PoketchIsSleepMode( wk->conwk ) )
		){
			Poketch_A08_StopRippleAnm( wk->vwk );
			wk->seq = SEQ_STOP_ANM;
			break;
		}
		if( check_touch_monitor( wk, &x, &y ) )
		{
			check_item_find( wk, x, y );
			Poketch_A08_StopRippleAnm( wk->vwk );
			wk->seq = SEQ_UPDATE_ANM;
			break;
		}
		break;

	case SEQ_STOP_ANM:
		if( Poketch_A08_WaitViewCommand( wk->vwk, CMD_RIPPLE_START ) )
		{
			wk->seq = SEQ_1ST_TOUCH_WAIT;
		}
		break;

	case SEQ_UPDATE_ANM:
		if( Poketch_A08_WaitViewCommand( wk->vwk, CMD_RIPPLE_START ) )
		{
			PoketchSePlay(POKETCH_SE_DOWSING_TOUCH);
			Poketch_A08_SetViewCommand( wk->vwk, CMD_RIPPLE_START );
			wk->seq = SEQ_2ND_TOUCH_WAIT;
		}
		break;
	}

	return FALSE;
}


//------------------------------------------------------------------
/**
 * �L���͈͓����^�b�`���ꂽ���`�F�b�N
 *
 * @param   x		�^�b�`���ꂽ����X���W�B����ĂȂ��ƕs��B
 * @param   y		������Y���W
 *
 * @retval  BOOL	TRUE���ƃ^�b�`���ꂽ
 */
//------------------------------------------------------------------
static BOOL check_touch_monitor( APPWORK* wk, u32* x, u32* y )
{
	if( PoketchIsSleepMode(wk->conwk) == FALSE )
	{
		if( GF_TP_GetPointTrg( x, y ) )
		{
			if( ((u32)( (*x) - TOUCH_RANGE_LEFT) < (u32)(TOUCH_RANGE_RIGHT - TOUCH_RANGE_LEFT))
			&	((u32)( (*y) - TOUCH_RANGE_TOP) < (u32)(TOUCH_RANGE_BOTTOM - TOUCH_RANGE_TOP))
			){
				return TRUE;
			}
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 * @param   touch_x		�^�b�`�p�l���w
 * @param   touch_y		�^�b�`�p�l���x
 *
 */
//------------------------------------------------------------------
static void check_item_find( APPWORK* wk, int touch_x, int touch_y )
{
	static const fx32 hit_range_tbl[] = {
		 8 << FX32_SHIFT,
		24 << FX32_SHIFT,
		48 << FX32_SHIFT,
	};

	HIDE_ITEM_LIST* list = HideItem_CreateList( PoketchGetFieldSysWork(wk->conwk), HEAPID_POKETCH_APP );
	VIEWPARAM* vpara = &(wk->vpara);

	vpara->find_pattern = FIND_PATTERN_NONE;
	vpara->touch_x = touch_x;
	vpara->touch_y = touch_y;
	vpara->find_pos_count = 0;


	if( list )
	{
		int item_x, item_y;
		int i;
		fx32 range;
		for(i=0; list[i].response != HIDE_LIST_RESPONSE_NONE; i++)
		{

			calc_glid_to_lcd_pos( list[i].gx, list[i].gz, &item_x, &item_y );

			range = FX_Sqrt( ((item_x-touch_x)*(item_x-touch_x) + (item_y-touch_y)*(item_y-touch_y)) << FX32_SHIFT );

			if( range <= hit_range_tbl[ list[i].response ] )
			{
				if( vpara->find_pos_count < FIND_POS_MAX )
				{
					vpara->find_pos[ vpara->find_pos_count ].x = item_x;
					vpara->find_pos[ vpara->find_pos_count ].y = item_y;
					vpara->find_pos[ vpara->find_pos_count ].lv = list[i].response;
					OS_TPrintf("find [%d]  x=%d, y=%d->%d, lv=%d\n", vpara->find_pos_count, list[i].gx, list[i].gz, item_y, list[i].response);
					vpara->find_pos_count++;
					vpara->find_pattern = FIND_PATTERN_POS;
				}
			}
			else if( range <= hit_range_tbl[ (NELEMS(hit_range_tbl)-1) ] )
			{
				if( vpara->find_pattern == FIND_PATTERN_NONE )
				{
					vpara->find_pattern = FIND_PATTERN_EXIST;
				}
			}
		}
		sys_FreeMemoryEz( list );
	}

}
//------------------------------------------------------------------
/**
 * �O���b�h���W��LCD���W�ɕϊ�
 *
 * @param   glid_x		
 * @param   glid_y		
 * @param   lcd_x		
 * @param   lcd_y		
 *
 */
//------------------------------------------------------------------
static void calc_glid_to_lcd_pos( int glid_x, int glid_y, int* lcd_x, int* lcd_y )
{
	fx32  uni_x, uni_y;
	fx32  fx_lcd_x, fx_lcd_y;

	glid_x -= HIDE_LIST_SX;
	glid_y -= HIDE_LIST_TOP;

	*lcd_x = TOUCH_RANGE_CENTER_X + (glid_x * ITEM_ICON_DIFF_X);
	*lcd_y = TOUCH_RANGE_CENTER_Y + (glid_y * ITEM_ICON_DIFF_Y);

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
		Poketch_A08_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A08_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}




//==============================================================================
//==============================================================================

