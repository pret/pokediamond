//============================================================================================
/**
 * @file	ev_gameover.c
 * @brief	�Q�[���N���A����
 * @date	2006.05.09
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"


#include "field_subproc.h"		//Field_DendouDemo_SetProc
#include "sysflag.h"
#include "syswork.h"
#include "situation_local.h"
#include "application/dendou_pc.h"
#include "savedata/dendou_data.h"
#include "savedata/record.h"
#include "savedata/mystatus.h"
#include "field/eventflag.h"		//EVENTWORK
#include "ev_mapchange.h"			//EventCmd_MapChangeByLocation
#include "system/pm_rtc.h"
#include "ev_time.h"				//EVTIME_SetGameClearDateTime
#include "ev_pokemon.h"				//EvPoke_SetChampionRibbon
#include "fieldmap.h"
#include "system\msgdata_util.h"
#include "system\window.h"
#include "system\wipe.h"
#include "system\snd_tool.h"
#include "talk_msg.h"
#include "fld_bmp.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_common_scr.h"
#include "system\main.h"
#include "poketool\status_rcv.h"

#include "report.h"				//Field_Save

//==============================================================================================
//==============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	BOOL	already_clear_flag;
	DEMO_DENDOU_PARAM ddp;
	ENDING_PROC_PARAM edp;

	GF_BGL_BMPWIN     bmpWin;
	STRBUF*           str;
	void*             iconWork;
	int               msgIndex;
	int               wait;
}GAMECLEAR_WORK;




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void SetupMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw );
static void StartReportMessage( FIELDSYS_WORK* fsys,  GAMECLEAR_WORK* gcw );
static void StartReportFinishMessage( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw, int save_result );
static void DeleteReportMessageResources( GAMECLEAR_WORK* gcw );
static void DeleteAllMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw );

static BOOL WaitMessage( GAMECLEAR_WORK* gcw );


//-----------------------------------------------------------------------------
/**
 * @brief	�a������f�[�^�̃Z�[�u
 */
//-----------------------------------------------------------------------------
static void SaveDendouData(FIELDSYS_WORK * fsys, BOOL already_clear_flag)
{
	DENDOU_SAVEDATA*  dd;
	POKEPARTY* party;
	RTCDate	date;
	LOAD_RESULT result;

	dd = SaveData_Extra_LoadDendouData(fsys->savedata, HEAPID_WORLD, &result);
	if (result != LOAD_RESULT_OK || !already_clear_flag) {
		//�f�[�^�����Ă���ꍇ�A���邢�͏���N���A�̏ꍇ�͏���������
		DendouData_Init(dd);
	}
	party = SaveData_GetTemotiPokemon(fsys->savedata);
	GF_RTC_GetDate(&date);
	DendouData_AddRecord( dd, party, &date );
	SaveData_Extra_SaveDendouData(fsys->savedata, dd);
	sys_FreeMemoryEz(dd);
}

//==============================================================================================
//==============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�Q�[���N���A����
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_GameClear(GMEVENT_CONTROL * event)
{
	LOCATION_WORK * sp;
	EVENTWORK * ev;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	GAMECLEAR_WORK * gcw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	DEMO_DENDOU_PARAM * ddp = &gcw->ddp;

	switch (*seq) {
	case 0:
		/* �a������f���Ăяo�� */
		Field_DendouDemo_SetProc( fsys, ddp );
		(*seq) ++;
		break;

	case 1:
		if( !FieldEvent_Cmd_WaitSubProcEnd(fsys) ){		//�T�u�v���Z�X�I���҂�
			sys_CreateHeap( HEAPID_BASE_APP, HEAPID_FIELD, 0x20000 );
			SetupMessageResources( fsys, gcw );
			WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
				WIPE_FADE_BLACK, 8, 1, HEAPID_EVENT );
			(*seq) ++;
		}
		break;

	case 2:
		if( WIPE_SYS_EndCheck() )
		{
			if( SaveData_IsOverwritingOtherData(fsys->savedata) == FALSE )
			{
				StartReportMessage( fsys, gcw );
				(*seq)++;
			}
			else
			{
				(*seq) = 7;
			}
		}
		break;

	case 3:
		if( WaitMessage( gcw ) )
		{
			(*seq)++;
		}
		break;

	case 4:
		/* �Z�[�u */
		{
			int result;

			//�����I�ɑS�̃Z�[�u�ƂȂ�悤�ɂ��Ă���

			PokeParty_RecoverAll( SaveData_GetTemotiPokemon(fsys->savedata) );
			SaveData_RequestTotalSave();

			result = SaveData_Save(fsys->savedata);
			SaveDendouData(fsys, gcw->already_clear_flag);

			/* �Z�[�u�����̃��b�Z�[�W�\�� */
			DeleteReportMessageResources( gcw );
			StartReportFinishMessage( fsys, gcw, result );
			(*seq) ++;
		}
		break;

	case 5:
		if( WaitMessage( gcw ) )
		{
			Snd_SePlay( SEQ_SE_DP_SAVE );
			gcw->wait = 18;
			(*seq)++;
		}
		break;

	case 6:
		if( gcw->wait )
		{
			gcw->wait--;
		}
		else
		{
			(*seq)++;
		}
		break;

	case 7:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK, 8, 1, HEAPID_EVENT );
		(*seq)++;
		break;

	case 8:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteAllMessageResources( fsys, gcw );

			/* �G���f�B���O�f���Ăяo�� */
			Field_EndingDemo_SetProc( fsys, &(gcw->edp) );
			(*seq) ++;
		}
		break;

	case 9:
		if( !FieldEvent_Cmd_WaitSubProcEnd(fsys) )
		{
			sys_FreeMemoryEz(gcw);
			sys_DeleteHeap( HEAPID_FIELD );
			OS_ResetSystem( _SOFT_RESET_NORMAL );
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief		�C�x���g�R�}���h�֐��F�Q�[���N���A
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventCmd_GameClear(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	LOCATION_WORK * sp,* ep;
	EVENTWORK * ev;
	MYSTATUS  * my;
	GAMECLEAR_WORK * gcw;
	RECORD * rec;
	POKEPARTY * party;
	fsys = FieldEvent_GetFieldSysWork(event);
	gcw = sys_AllocMemory(HEAPID_EVENT, sizeof(GAMECLEAR_WORK));

	ev = SaveData_GetEventWork(fsys->savedata);
	my = SaveData_GetMyStatus( fsys->savedata );
	sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	ep = Situation_GetEscapeLocation(SaveData_GetSituation(fsys->savedata));

	gcw->already_clear_flag = SysFlag_GameClearCheck(ev);
	gcw->ddp.player	= SaveData_GetMyStatus(fsys->savedata);
	gcw->ddp.party		= SaveData_GetTemotiPokemon(fsys->savedata);
	gcw->ddp.playTime	= SaveData_GetPlayTime(fsys->savedata);

	gcw->edp.playerSex = MyStatus_GetMySex( SaveData_GetMyStatus(fsys->savedata) );
	gcw->edp.clearFlag = SysFlag_GameClearCheck(ev);
	gcw->edp.zukanWork = SaveData_GetZukanWork(fsys->savedata);

	if (SysFlag_GameClearCheck(ev) == FALSE) {
		EVTIME_SetGameClearDateTime(fsys);	// ���߂Ă̓a������̎��Ԃ��L�^����
	}
	party = SaveData_GetTemotiPokemon(fsys->savedata);
	EvPoke_SetChampionRibbon(party);		// �`�����s�I�����{�����Z�b�g
	LOCATION_SetFirstPos(sp);				// ����ڑ���������2�K�ɃZ�b�g
	LOCATION_SetFirstEscapePos(ep);			// �G�X�P�[�v�������̊O�ɃZ�b�g
	SysFlag_CommCounterSet(ev);				// �R���e�B�j���[���ɓ���ڑ��悩��J�n����t���O���Z�b�g
	SysFlag_GameClearSet(ev);				// �Q�[���N���A�t���O���Z�b�g
	MyStatus_SetDpClearFlag( my );			// MYSTATUS���̃Q�[���N���A�t���O�����Ă�


//	SysWork_HideMapWorkSet(ev, HIDEMAP_ID_L04);	// L04���o��������悤�Ɂ@�X�N���v�g����open�ɕύX 06.07.13 iwasawa
	rec = SaveData_GetRecord(fsys->savedata);
	RECORD_Inc(rec, RECID_DENDOU_CNT);		// �a������J�E���g�A�b�v

	FieldEvent_Call(event, GMEVENT_GameClear, gcw);
}




//------------------------------------------------------------------
/**
 * 
 *
 * @param   fsys		
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void SetupMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
		GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		0, 0,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	gcw->str = NULL;
	gcw->iconWork = NULL;
	GF_BGL_BmpWinInit( &gcw->bmpWin );

	GF_Disp_SetBank( &SetBankData );
	GX_SetDispSelect( GX_DISP_SELECT_MAIN_SUB );
	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BackGroundColorSet( FLD_MBGFRM_FONT, 0x0000 );

	GF_BGL_BGControlSet( fsys->bgl, FLD_MBGFRM_FONT, &header, GF_BGL_MODE_TEXT );
	GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 0x20, 0, HEAPID_EVENT );
	GF_BGL_ScrFill( fsys->bgl, FLD_MBGFRM_FONT, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );

	GF_BGL_LoadScreenReq( fsys->bgl, FLD_MBGFRM_FONT );
}

//------------------------------------------------------------------
/**
 * �u���|�[�g�ɂ�������ł��܂��v���b�Z�[�W�̕\���J�n
 *
 * @param   fsys		
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void StartReportMessage( FIELDSYS_WORK* fsys,  GAMECLEAR_WORK* gcw )
{
	CONFIG* config = SaveData_GetConfig(fsys->savedata);

	gcw->str = MSGDAT_GetStrDirectAlloc( ARC_MSG, NARC_msg_common_scr_dat, msg_common_report_03, HEAPID_EVENT );

    FldTalkBmpAdd( fsys->bgl, &gcw->bmpWin, FLD_MBGFRM_FONT );
	FieldTalkWinPut( &gcw->bmpWin, config );

	gcw->msgIndex = FieldTalkMsgStart( &gcw->bmpWin, gcw->str, config, 1 );
	gcw->iconWork = TimeWaitIconAdd( &gcw->bmpWin, TALK_WIN_CGX_NUM );
}

//------------------------------------------------------------------
/**
 * �u���|�[�g�ɂ�������ł��܂��v���b�Z�[�W�̕\���I���҂�
 *
 * @param   gcw		
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
static BOOL WaitMessage( GAMECLEAR_WORK* gcw )
{
	return FldTalkMsgEndCheck( gcw->msgIndex );
}

//------------------------------------------------------------------
/**
 * �u���|�[�g�ɂ�������ł��܂��v���b�Z�[�W�\���̂��߂̃��\�[�X�j��
 *
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void DeleteReportMessageResources( GAMECLEAR_WORK* gcw )
{
	STRBUF_Delete( gcw->str );
	TimeWaitIconDel( gcw->iconWork );

	// BitmapWindow�͓��e���N���A���邾���Ŕj�����Ȃ��i���̃��b�Z�[�W�Ŏg���񂷁j
	FieldTalkWinClear( &gcw->bmpWin );
}


static void StartReportFinishMessage( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw, int save_result )
{
	MSGDATA_MANAGER* mm = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, HEAPID_FIELD );

	if( save_result == SAVE_RESULT_OK )
	{
		WORDSET* wordset;

		wordset = WORDSET_Create( HEAPID_FIELD );
		WORDSET_RegisterPlayerName( wordset, 0, SaveData_GetMyStatus(fsys->savedata) );

		gcw->str = MSGDAT_UTIL_AllocExpandString( wordset, mm, msg_common_report_04, HEAPID_FIELD );

		WORDSET_Delete( wordset );
	}
	else
	{
		gcw->str = MSGMAN_AllocString( mm, msg_common_report_06 );
	}
	MSGMAN_Delete( mm );

	gcw->msgIndex = FieldTalkMsgStart( &gcw->bmpWin, gcw->str, SaveData_GetConfig(fsys->savedata), 1 );
}


static void DeleteAllMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw )
{
	if( gcw->str )
	{
		STRBUF_Delete( gcw->str );
	}

	if( GF_BGL_BmpWinAddCheck(&gcw->bmpWin) )
	{
		GF_BGL_BmpWinDel( &gcw->bmpWin );
	}

	GF_BGL_BGControlExit( fsys->bgl, FLD_MBGFRM_FONT );
}
