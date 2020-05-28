//============================================================================================
/**
 * @file	poketch_a22c.c
 * @bfief	�|�P�b�`�i�A�v��Noa22�F�}�[�L���O�}�b�v�j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "field\fieldsys.h"
#include "field\eventflag.h"
#include "savedata\encount.h"
#include "..\field_townmap.h"
#include "..\syswork.h"


#include "poketch_a22.h"
#include "poketch_prv.h"

//==============================================================
// �ړ��|�P�������̍X�V�p�x��
//==============================================================
enum {
	MOVEPOKE_WALKCOUNT_SHOW = 5,	///< ��\�����\���ɐ؂�ւ������
	MOVEPOKE_SHOW_PERCENTAGE = 50,	///< ��\�����\���؂�ւ����̐����m���i100�����j
};










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

	POKETCH_DATA*  savedata;
	MPD_PTR        movePoke[ MOVE_POKE_MAX ];

	u8			markPriority[ POKETCH_MAP_MARK_MAX ];
	u8			movepokeWalkCount;

}APPWORK;

//==============================================================
// �V�[�P���X
//==============================================================
enum {
	SEQ_INIT,
	SEQ_WAIT_TOUCH,
	SEQ_DRAG,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A22_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A22_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A22_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqWaitTouch(APPWORK *wk);
static BOOL SeqDrag(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static void replace_priority( APPWORK* wk, int top_id );
static BOOL check_update_player_location( APPWORK* wk );



//------------------------------------------------------------------
/**
 * �A�v���̐���֐��A�h���X�����C���R���g���[���ɓn��
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A22_Init, Poketch_A22_Quit);
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
static BOOL Poketch_A22_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A22_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	int i;

	wk->savedata = PoketchGetSaveData( conwk );

	for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
	{
		wk->vpara.markpos[i].point_flag = TRUE;
		wk->vpara.markpos[i].pri = i;
		PoketchData_MarkMap_GetMarkPos( wk->savedata, i, &(wk->vpara.markpos[i].x), &(wk->vpara.markpos[i].y) );
		wk->vpara.markpos[i].x += POKETCH_MONITOR_DOT_XORG;
		wk->vpara.markpos[i].y += POKETCH_MONITOR_DOT_YORG;
		wk->vpara.markpos[i].point_flag = FALSE;

		wk->markPriority[i] = i;
	}
	wk->vpara.dragMarkID = 0;
	wk->vpara.updateFlag = FALSE;
	wk->vpara.player_updateFlag = FALSE;

	{
		EVENTWORK* ev = SaveData_GetEventWork( PoketchGetSystemSaveData(conwk) );
		for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
		{
			wk->vpara.hidemap_flag[i] = SysWork_HideMapWorkCheck( ev, i );
		}
	}

	{
		ENC_SV_PTR  enc = EncDataSave_GetSaveDataPtr( PoketchGetSystemSaveData(conwk) );
		for(i=0; i<MOVE_POKE_MAX; i++)
		{
			wk->movePoke[i] = EncDataSave_GetMovePokeDataPtr( enc, i );
			wk->vpara.move_poke[i].flag = EncDataSave_GetMovePokeDataParam( wk->movePoke[i], MP_PARAM_ENC );
			wk->movepokeWalkCount = 0;
		}
	}



	FLDTOWNMAP_GetBlockXZ( PoketchGetFieldSysWork(conwk), &(wk->vpara.player_x), &(wk->vpara.player_y) );

	if( Poketch_A22_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
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
	int i;
	for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
	{
		PoketchData_MarkMap_SetMarkPos( wk->savedata, i,
			(wk->vpara.markpos[i].x - POKETCH_MONITOR_DOT_XORG),
			(wk->vpara.markpos[i].y - POKETCH_MONITOR_DOT_YORG) );
	}
	Poketch_A22_DeleteViewWork( wk->vwk );
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
static void Poketch_A22_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqWaitTouch,
		SeqDrag,
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
static void Poketch_A22_Quit(void *wk_adrs)
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
		Poketch_A22_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A22_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_WAIT_TOUCH );
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
static BOOL SeqWaitTouch(APPWORK *wk)
{
	enum {
		MARK_HIT_RANGE = 8,		// ���S�_����㉺���E�ɂ��ꂾ���i�h�b�g�j��������
	};

	u32 x, y;

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	wk->vpara.player_updateFlag = check_update_player_location( wk );

	wk->vpara.updateFlag = FALSE;
	if(PoketchGetTPTrg(&x, &y))
	{
		int i, id, dx, dy;

		for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
		{
			id = wk->markPriority[i];

			dx = (int)(wk->vpara.markpos[id].x) - (int)x;
			if( (dx >= -MARK_HIT_RANGE) && (dx <= MARK_HIT_RANGE) )
			{
				dy = (int)(wk->vpara.markpos[id].y) - (int)(y);
				if( (dy >= -MARK_HIT_RANGE) && (dy <= MARK_HIT_RANGE) )
				{
					replace_priority( wk, id );
					wk->vpara.markpos[id].x = x;
					wk->vpara.markpos[id].y = y;
					wk->vpara.markpos[id].point_flag = TRUE;
					wk->vpara.dragMarkID = id;
					wk->vpara.updateFlag = TRUE;
					ChangeSeq( wk, SEQ_DRAG );
					break;
				}
			}
		}
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�h���b�O��
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŃA�v���I��
 */
//------------------------------------------------------------------
static BOOL SeqDrag(APPWORK *wk)
{
	u32 x, y;

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	wk->vpara.player_updateFlag = check_update_player_location( wk );

	if(PoketchGetTPCont(&x, &y))
	{
		wk->vpara.markpos[wk->vpara.dragMarkID].x = x;
		wk->vpara.markpos[wk->vpara.dragMarkID].y = y;
	}
	else
	{
		wk->vpara.markpos[wk->vpara.dragMarkID].point_flag = FALSE;
		ChangeSeq( wk, SEQ_WAIT_TOUCH );
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
		Poketch_A22_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A22_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}





//------------------------------------------------------------------
/**
 * �}�[�N�̃v���C�I���e�B����ג���
 *
 * @param   wk		
 * @param   top_id		
 *
 */
//------------------------------------------------------------------
static void replace_priority( APPWORK* wk, int top_id )
{
	if( wk->markPriority[0] != top_id )
	{
		int i, id;

		for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
		{
			if( wk->markPriority[i] == top_id )
			{
				break;
			}
		}
		while(i)
		{
			wk->markPriority[i] = wk->markPriority[i-1];
			i--;
		}
		wk->markPriority[0] = top_id;

		for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
		{
			id = wk->markPriority[i];
			wk->vpara.markpos[id].pri = i;
		}
	}
}
//------------------------------------------------------------------
/**
 * �v���C���[�̈ʒu�i�^�E���}�b�v���W�j�X�V�`�F�b�N
 * �X�V���ꂽ��vpara�̓��e������������
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUE�ōX�V���ꂽ
 */
//------------------------------------------------------------------
static BOOL check_update_player_location( APPWORK* wk )
{
	BOOL ret = FALSE;

	if(PoketchGetPlayerMoveTrg(wk->conwk))
	{
		// ���@�̃O���b�h�i�}�b�v��j���ς������X�V
		int x, y;
		FLDTOWNMAP_GetBlockXZ( PoketchGetFieldSysWork(wk->conwk), &x, &y );
		if( (x != wk->vpara.player_x) || (y != wk->vpara.player_y) )
		{
			wk->vpara.player_x = x;
			wk->vpara.player_y = y;
			ret = TRUE;
		}

		// �ړ��|�P�����̏�Ԃɂ���Ă��X�V
		if( ++(wk->movepokeWalkCount) >= MOVEPOKE_WALKCOUNT_SHOW )
		{
			int i;

			for(i=0; i<MOVE_POKE_MAX; i++)
			{
				if( wk->vpara.move_poke[i].flag == FALSE )
				{
					wk->vpara.move_poke[i].flag = EncDataSave_GetMovePokeDataParam( wk->movePoke[i], MP_PARAM_ENC );
					if( wk->vpara.move_poke[i].flag )
					{
						ret = TRUE;
					}
				}
				if( wk->vpara.move_poke[i].flag )
				{
					wk->vpara.move_poke[i].zone_id = EncDataSave_GetMovePokeDataParam( wk->movePoke[i], MP_PARAM_ZONE_ID );
					ret = TRUE;
				}
			}
		}
	}

	return ret;
}
