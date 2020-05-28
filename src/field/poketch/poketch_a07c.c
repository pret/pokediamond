//============================================================================================
/**
 * @file	poketch_a07c.c
 * @bfief	�|�P�b�`�i�A�v��Noa07�F�Ȃ��x�`�F�b�J�[�j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"
#include "system\savedata.h"
#include "poketool\pokeicon.h"
#include "poketool\pokeparty.h"

#include "poketch_a07.h"
#include "poketch_prv.h"

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
static BOOL Poketch_A07_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static u32 calc_natsuki_level( u32 point );
static void CleanupWork( APPWORK *wk );
static void Poketch_A07_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A07_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A07_Init, Poketch_A07_Quit);
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
static BOOL Poketch_A07_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A07_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	if( Poketch_A07_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->conwk = conwk;

		{
			POKEPARTY* party = SaveData_GetTemotiPokemon( SaveData_GetPointer() );
			POKEMON_PARAM* pp;
			int i;
			int n;
			int count;

			count = 0;
			wk->vpara.poke_count = PokeParty_GetPokeCount(party);
			for(i=0; i<wk->vpara.poke_count; i++)
			{
				pp = PokeParty_GetMemberPointer(party, i);
				if( PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == FALSE )
				{
					wk->vpara.poke_param[count].monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
					wk->vpara.poke_param[count].form = PokeParaGet(pp, ID_PARA_form_no, NULL);
					wk->vpara.poke_param[count].imgArcIdx = PokeIconCgxArcIndexGet((const POKEMON_PASO_PARAM*)pp);
					n = calc_natsuki_level(PokeParaGet(pp, ID_PARA_friend, NULL));
					switch( n ){
					case 0:
					case 1:
					case 2:
						wk->vpara.poke_param[count].reaction_type = REACTION_HATE;
						wk->vpara.poke_param[count].reaction_level = 3 - n;	// 1~3
						break;
					case 3:
					default:
						wk->vpara.poke_param[count].reaction_type = REACTION_NEUTRAL;
						wk->vpara.poke_param[count].reaction_level = 0;
						break;
					case 4:
					case 5:
					case 6:
						wk->vpara.poke_param[count].reaction_type = REACTION_LIKE;
						wk->vpara.poke_param[count].reaction_level = -(3-n);	// 1~3
						break;

					}
					count++;
				}
			}
			wk->vpara.poke_count = count;

			wk->vpara.tp_cont = FALSE;
			wk->vpara.tp_trg = FALSE;
			wk->vpara.tp_x = 0;
			wk->vpara.tp_y = 0;
		}

		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * �Ȃ��x���x���v�Z
 *
 * @param   point		�|�P�����X�e�[�^�X�̂Ȃ��x�i0�`255�j
 *
 * @retval  u32		�Ȃ��x���x���i�Ȃ��x�`�F�b�J�[�Ǝ��j
 */
//------------------------------------------------------------------
static u32 calc_natsuki_level( u32 point )
{
	static const u8 border[] = {
		1, 35, 70, 150, 200, 255,
	};
	u32 i;

	for(i=0; i<NELEMS(border); i++)
	{
		if( point < border[i] )
		{
			return i;
		}
	}
	return NELEMS(border);
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
	Poketch_A07_DeleteViewWork( wk->vwk );
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
static void Poketch_A07_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A07_Quit(void *wk_adrs)
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
		Poketch_A07_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A07_WaitViewCommand( wk->vwk, CMD_INIT ))
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

	wk->vpara.tp_cont = PoketchGetTPCont(&wk->vpara.tp_x, &wk->vpara.tp_y);
	if( wk->vpara.tp_cont )
	{
		if( ((u32)(wk->vpara.tp_x - POKETCH_MONITOR_DOT_XORG) < (u32)(POKETCH_MONITOR_DOT_XEND - POKETCH_MONITOR_DOT_XORG))
		&	((u32)(wk->vpara.tp_y - POKETCH_MONITOR_DOT_YORG) < (u32)(POKETCH_MONITOR_DOT_YEND - POKETCH_MONITOR_DOT_YORG))
		){
			wk->vpara.tp_trg = GF_TP_GetTrg();
			return FALSE;
		}
		wk->vpara.tp_cont = FALSE;
	}

	wk->vpara.tp_x = 0;
	wk->vpara.tp_y = 0;
	wk->vpara.tp_trg = FALSE;

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
		Poketch_A07_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A07_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
