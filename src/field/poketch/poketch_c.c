//============================================================================================
/**
 * @file	poketch_c.c
 * @bfief	�|�P�b�`�i���C���j�@�R���g���[��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\lib_pack.h"
#include "system\pm_overlay.h"
#include "gflib\touchpanel.h"
#include "system\snd_tool.h"
#include "savedata\mystatus.h"
#include "..\field_event.h"

#include "field\poketch.h"
#include "poketch_sound.h"
#include "poketch_prv.h"
#include "poketch_main.h"
#include "poketch_button.h"


//#define POKETCH_PROC_PRINT_ENABLE

#ifdef POKETCH_PROC_PRINT_ENABLE
static void PoketchProcPrintf(const char* fmt, ...)
{
	va_list vlist;

	va_start( vlist, fmt );
	OS_TVPrintf( fmt, vlist );
	va_end(vlist);
}
#else
#define PoketchProcPrintf(...)	/* */
#endif


//====================================================
// �A�v���I�[�o�[���C���W���[���錾
//====================================================
FS_EXTERN_OVERLAY(poketch_app_dwatch);
FS_EXTERN_OVERLAY(poketch_app_awatch);
FS_EXTERN_OVERLAY(poketch_app_stopwatch);
FS_EXTERN_OVERLAY(poketch_app_calc);
FS_EXTERN_OVERLAY(poketch_app_memo);
FS_EXTERN_OVERLAY(poketch_app_dotart);
FS_EXTERN_OVERLAY(poketch_app_simple_pokelist);
FS_EXTERN_OVERLAY(poketch_app_dummy);
FS_EXTERN_OVERLAY(poketch_app_natsuki_checker);
FS_EXTERN_OVERLAY(poketch_app_dowsing);
FS_EXTERN_OVERLAY(poketch_app_counter);
FS_EXTERN_OVERLAY(poketch_app_pedometer);
FS_EXTERN_OVERLAY(poketch_app_cointoss);
FS_EXTERN_OVERLAY(poketch_app_trainer_launcher);
FS_EXTERN_OVERLAY(poketch_app_wazaeff);
FS_EXTERN_OVERLAY(poketch_app_color_changer);
FS_EXTERN_OVERLAY(poketch_app_sodateya_camera);
FS_EXTERN_OVERLAY(poketch_app_love_tester);
FS_EXTERN_OVERLAY(poketch_app_alarm);
FS_EXTERN_OVERLAY(poketch_app_roulette);
FS_EXTERN_OVERLAY(poketch_app_kitchen);
FS_EXTERN_OVERLAY(poketch_app_comm_search);
FS_EXTERN_OVERLAY(poketch_app_backlight);
FS_EXTERN_OVERLAY(poketch_app_dummy_monitor);
FS_EXTERN_OVERLAY(poketch_app_mark_map);
FS_EXTERN_OVERLAY(poketch_app_seed_map);
FS_EXTERN_OVERLAY(poketch_app_calendar);
FS_EXTERN_OVERLAY(poketch_app_pokemon_counter);
FS_EXTERN_OVERLAY(poketch_app_pokemon_history);

//====================================================
// �A�v���I�[�o�[���C�h�c�e�[�u��
//====================================================
static const struct {
	int          appID;
	FSOverlayID  overlayID;
}OverlayID[] = {

	{ POKETCH_APPID_DWATCH,				FS_OVERLAY_ID(poketch_app_dwatch) },			// 00: �f�W�^�����v
	{ POKETCH_APPID_STOPWATCH,			FS_OVERLAY_ID(poketch_app_stopwatch) },			// 01: �X�g�b�v�E�H�b�`
	{ POKETCH_APPID_CALC,				FS_OVERLAY_ID(poketch_app_calc) },				// 02: �d��
	{ POKETCH_APPID_MEMO,				FS_OVERLAY_ID(poketch_app_memo) }, 				// 03: ������
	{ POKETCH_APPID_AWATCH,				FS_OVERLAY_ID(poketch_app_awatch) },			// 04: �A�i���O���v
	{ POKETCH_APPID_DOTART,				FS_OVERLAY_ID(poketch_app_dotart) },			// 05: �h�b�g�A�[�g
	{ POKETCH_APPID_POKELIST,			FS_OVERLAY_ID(poketch_app_simple_pokelist) },	// 06: �ȈՃ|�P�������X�g
	{ POKETCH_APPID_NATSUKI_CHECK,		FS_OVERLAY_ID(poketch_app_natsuki_checker) },	// 07: �Ȃ��x�`�F�b�J�[
	{ POKETCH_APPID_DOWSING,			FS_OVERLAY_ID(poketch_app_dowsing) },			// 08: �_�E�W���O�}�V��
	{ POKETCH_APPID_COUNTER,			FS_OVERLAY_ID(poketch_app_counter) },			// 09: �J�E���^�[
	{ POKETCH_APPID_PEDOMETER,			FS_OVERLAY_ID(poketch_app_pedometer) },			// 10: �����v
	{ POKETCH_APPID_SODATEYA_CAMERA,	FS_OVERLAY_ID(poketch_app_sodateya_camera) },	// 15: �����Ă�J����
	{ POKETCH_APPID_ROULETTE,			FS_OVERLAY_ID(poketch_app_roulette) },			// 16: ���[���b�g
	{ POKETCH_APPID_COINTOSS,			FS_OVERLAY_ID(poketch_app_cointoss) },			// 17: �R�C���g�X
	{ POKETCH_APPID_WAZA_EFF_CHECK,		FS_OVERLAY_ID(poketch_app_wazaeff) },			// 18: �킴���ʃ`�F�b�J�[
	{ POKETCH_APPID_LOVETESTER,			FS_OVERLAY_ID(poketch_app_love_tester) },		// 19: ���u�e�X�^�[
	{ POKETCH_APPID_ALARM_WATCH,		FS_OVERLAY_ID(poketch_app_alarm) },				// 20: �A���[�����v
	{ POKETCH_APPID_KITCHEN_TIMER,		FS_OVERLAY_ID(poketch_app_kitchen) },			// 21: �L�b�`���^�C�}�[
	{ POKETCH_APPID_MAP_MARKING,		FS_OVERLAY_ID(poketch_app_mark_map) },			// 22: �}�[�L���O�}�b�v
	{ POKETCH_APPID_SEED_SEARCHER,		FS_OVERLAY_ID(poketch_app_seed_map) },			// 23: ���̂݃}�b�v
	{ POKETCH_APPID_COLOR_CHANGER,		FS_OVERLAY_ID(poketch_app_color_changer) },		// 24: �J���[�`�F���W���[
	{ POKETCH_APPID_CALENDER,			FS_OVERLAY_ID(poketch_app_calendar) },			// 25: �J�����_�[
	{ POKETCH_APPID_COMM_SEARCHER,		FS_OVERLAY_ID(poketch_app_comm_search) },		// 27: ������T�[�`���[
	{ POKETCH_APPID_POKEMON_COUNTER,	FS_OVERLAY_ID(poketch_app_pokemon_counter) },	// 28: �|�P�����J�E���^�[
	{ POKETCH_APPID_POKEMON_HISTORY,	FS_OVERLAY_ID(poketch_app_pokemon_history) },	// 29: �|�P�����q�X�g���[

};


//====================================================
// �V�[�P���X
//====================================================
enum {
	SEQ_INIT = 0,
	SEQ_APP_MAIN,
	SEQ_APPCHANGE_NORMAL,
	SEQ_CLEANUP,
	SEQ_QUIT,
};

// �X���[�v�ȍ~���̃V�[�P���X
enum {
	SLEEP_SEQ_NULL,	// �����Ȃ�
	SLEEP_SEQ_REQ,	// �X���[�v���N�G�X�g����
	SLEEP_SEQ_MAIN,	// �X���[�v���ł�
	SLEEP_SEQ_WAKE,	// �E�F�C�N���N�G�X�g����
};

// �A�v�����
enum {
	APP_STATE_CLEAN = 0,	///< ���������Ă��Ȃ����
	APP_STATE_INIT,			///< �������������s��
	APP_STATE_RUN,			///< ���쒆
	APP_STATE_QUIT,			///< �I���������s��
};

//====================================================
// �q�[�v�g�p�T�C�Y
//====================================================
enum {
	HEAPSIZE_MAIN = 0xc000,
	HEAPSIZE_APP = 0xc000,
};
//====================================================
// ���̂��萔
//====================================================
enum {
	APP_SKIP_TIMER = 30,
	APP_FIRST_SKIP_TIMER = 3,
};

//====================================================
// ���C�����[�N
//====================================================
struct _POKETCH_WORK {
	u8	main_seq;
	u8	seq;
	u8	app_state;

	u8	touch_flag;
	u8	player_move_flag;
	u8  app_changing_flag;
	u8  appchange_button_disable_flag;
	u8  pedometer_update_flag;

	u32  button_action;
	BOOL app_skip_flag;
	u32  app_skip_timer;
	int  load_app_id;
	FSOverlayID  load_app_overlay_id;

	POKETCH_VIEW_WORK	*view_wk;
	POKETCH_MAIN_VPARAM  vpara;
	void				*app_work;

	POKETCH_BUTTON_MAN*				button;
	u32						button_cmd_req;
	u32						button_prev_cmd;

	struct _POKETCH_WORK**  this_work_adrs;	// �������p�Ɏ����̃A�h���X������
	TCB_PTR                 tail_task;

	// �A�v���P�[�V�����̐���֐�
	pAppInitProc	app_init_proc;
	pAppQuitProc	app_quit_proc;
	pAppSaveProc	app_save_proc;
	void*			app_save_arg;

	GF_BGL_INI*						bgl;
	NNSG2dOamManagerInstance*		oamm;

	SAVEDATA*       savedata;
	POKETCH_DATA*   poketch_savedata;
	FIELDSYS_WORK*  fieldsys;
};

//==============================================================
// Prototype
//==============================================================
static void PoketchProcPrintf(const char* fmt, ...);
static POKETCH_WORK* GetMainWorkPtr(void);
static BOOL PoketchWorkSetup( POKETCH_WORK* wk );
static void PoketchWorkCleanup( POKETCH_WORK* wk );
static void PoketchMain(TCB_PTR tcb, void *wk_adrs);
static void PoketchTail( TCB_PTR tcb, void* wk_adrs );
static void ChangeSeq( POKETCH_WORK *wk, u32 seq );
static void SeqInit(POKETCH_WORK *wk);
static void SeqAppMain(POKETCH_WORK *wk);
static void SeqAppChange(POKETCH_WORK *wk);
static void SeqCleanUp( POKETCH_WORK *wk );
static void LoadApplication( POKETCH_WORK* wk, int appID);
static void UnloadApplication( POKETCH_WORK* wk );
static void InitApplication( POKETCH_WORK* wk, u32 app_no );
static BOOL WaitInitApplication( POKETCH_WORK* wk );
static void QuitApplication( POKETCH_WORK* wk );
static BOOL WaitQuitApplication( POKETCH_WORK* wk );
static BOOL BmnSetup( POKETCH_WORK* wk );
static void BmnCleanup( POKETCH_WORK *wk );
static void ButtonUpdate( POKETCH_WORK *wk );
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static BOOL ButtonViewReq( POKETCH_VIEW_WORK *vwk, u32 cmd );
static inline BOOL check_inside_poketch_screen( u32 x, u32 y );


extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);



//------------------------------------------------------------------
/**
 * ���C�����[�N�|�C���^��Ԃ�
 *
 * @retval  POKETCH_WORK*		���C�����[�N�|�C���^
 */
//------------------------------------------------------------------
static POKETCH_WORK* GetMainWorkPtr(void)
{
	#ifdef PM_DEBUG
	extern POKETCH_WORK* GetPoketchMainWorkPtrDebug(void);
	#endif

	return  GetPoketchMainWorkPtr();
}

//------------------------------------------------------------------
/**
 * �|�P�b�`�������J�n�i�t�B�[���h�J�n���ɂ̂݌Ă΂��j
 *
 * @param   wk_adrs		���[�N�A�h���X��ۑ�����ϐ��̃|�C���^
 * @param   savedata	�|�P�b�`�Z�[�u�f�[�^�|�C���^
 * @param   bgl			��ʍ\�z�Ɏg��BGL�V�X�e���|�C���^
 *
 */
//------------------------------------------------------------------
void PoketchInit( FIELDSYS_WORK* fsys, POKETCH_WORK **wk_adrs, SAVEDATA* savedata,  GF_BGL_INI* bgl, NNSG2dOamManagerInstance* oamm )
{
	POKETCH_WORK *wk;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKETCH_MAIN, HEAPSIZE_MAIN );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKETCH_APP,  HEAPSIZE_APP );

	wk = sys_AllocMemory(POKETCH_MAIN_CTRL_HEAPID, sizeof(POKETCH_WORK));

	if(wk != NULL)
	{
		*wk_adrs = wk;

		wk->fieldsys = fsys;
		wk->savedata = savedata;
		wk->poketch_savedata = SaveData_GetPoketchData( savedata );
		wk->bgl = bgl;
		wk->oamm = oamm;

		if( PoketchWorkSetup( wk ) )
		{
			InitTPSystem();			// �^�b�`�p�l���V�X�e��������
			InitTPNoBuff(4);

			wk->this_work_adrs = wk_adrs;
			wk->tail_task = TCB_Add( PoketchTail, wk, POKETCH_TAIL_TASKPRI );
			TCB_Add( PoketchMain, wk, POKETCH_MAIN_TASKPRI );
		}
	}
}

//------------------------------------------------------------------
/**
 * �|�P�b�`�I�������J�n
 *
 * @param   wk		�|�P�b�`���[�N�|�C���^�iPoketchInit�œn�������́j
 *
 */
//------------------------------------------------------------------
void PoketchQuitReq(POKETCH_WORK *wk)
{
	PoketchProcPrintf("�|�P�b�`�I���ʒm\n");
	if( (wk->main_seq != SEQ_CLEANUP) && (wk->main_seq != SEQ_QUIT) )
	{
		ChangeSeq( wk, SEQ_CLEANUP );
	}
}
//------------------------------------------------------------------
/**
 * �|�P�b�`�I���҂�
 *
 * @param   wk		�|�P�b�`���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL PoketchQuitWait( POKETCH_WORK *wk )
{
	return (wk == NULL);
}

//==============================================================================================
//
// �t�B�[���h�Ƃ̂��Ƃ�
//
//==============================================================================================

//------------------------------------------------------------------
/**
 * �t�B�[���h����|�P�b�`�֊e��󋵕ω��̒ʒm���󂯎��
 *
 * @param   wk		
 * @param   id		
 * @param   value		
 *
 */
//------------------------------------------------------------------
void Poketch_SendRequest( POKETCH_WORK* wk, FIELD_POKETCH_SEND_ID  id, u32 value )
{
	switch( id ){
	case POKETCH_SEND_SLEEP:
		break;

	case POKETCH_SEND_MOVE_PLAYER:
		wk->player_move_flag = TRUE;
		break;

	case POKETCH_SEND_PEDOMATER:
		{
			u32 count = PoketchData_GetPedometer( wk->poketch_savedata );
			if( ++count > 99999 )
			{
				count = 0;
			}
			PoketchData_SetPedometer( wk->poketch_savedata, count );
			wk->pedometer_update_flag = TRUE;
			
		}
		break;

	case POKETCH_SEND_SAVE:
		if( wk->app_state == APP_STATE_RUN )
		{
			if( wk->app_save_proc )
			{
				wk->app_save_proc( wk->app_save_arg );
			}
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * �t�B�[���h������Ăяo����A
 * �|�P�b�`�̃{�^���E�X�N���[�����^�b�`���Ă��邩�`�F�b�N
 *
 * @param   wk			�|�P�b�`���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�Ń^�b�`���Ă���
 */
//------------------------------------------------------------------
BOOL Poketch_CheckTouch( POKETCH_WORK* wk )
{
	return wk->touch_flag;
}

//------------------------------------------------------------------
/**
 * �|�P�b�`�Ō��݉ғ����̃A�v���i���o�[��Ԃ�
 *
 * @param   wk		�|�P�b�`���[�N�|�C���^
 *
 * @retval  int		�A�v���i���o�[
 */
//------------------------------------------------------------------
int Poketch_GetRunningApplication( POKETCH_WORK* wk )
{
	return wk->load_app_id;
}


//------------------------------------------------------------------
/**
 * ���C�����[�N�Z�b�g�A�b�v
 *
 * @param   wk		���[�N�|�C���^
 */
//------------------------------------------------------------------
static BOOL PoketchWorkSetup( POKETCH_WORK* wk )
{
	if(Poketch_MAIN_SetViewWork( &(wk->view_wk), &(wk->vpara), wk->oamm, wk ))
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;

		wk->touch_flag = FALSE;
		wk->player_move_flag = FALSE;
		wk->pedometer_update_flag = FALSE;
		wk->app_changing_flag = FALSE;
		wk->appchange_button_disable_flag = FALSE;
		wk->load_app_id = POKETCH_APP_NONE;
		wk->app_state = APP_STATE_CLEAN;

		wk->button_action = BMN_EVENT_NULL;

		if( BmnSetup( wk ) )
		{
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ���C�����[�N�N���[���A�b�v
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void PoketchWorkCleanup( POKETCH_WORK* wk )
{
	TCB_Delete( wk->tail_task );
	BmnCleanup( wk );
	UnloadApplication( wk );
	Poketch_MAIN_DeleteViewWork( wk->view_wk );
}

//------------------------------------------------------------------
/**
 * �|�P�b�`���C���^�X�N
 *8+
 * @param   tcb			TCB�|�C���^
 * @param   wk_adrs		���[�N�A�h���X
 */
//------------------------------------------------------------------
static void PoketchMain(TCB_PTR tcb, void *wk_adrs)
{
	static void (* const seq_tbl[])(POKETCH_WORK *) = {
		SeqInit,
		SeqAppMain,
		SeqAppChange,
		SeqCleanUp,
	};

	POKETCH_WORK *wk;

	wk = (POKETCH_WORK *)wk_adrs;

	if( wk->main_seq < NELEMS(seq_tbl) )
	{
		if( wk->main_seq != SEQ_INIT )
		{
			ButtonUpdate( wk );
		}
		seq_tbl[ wk->main_seq ]( wk );
	}
	else
	{
		GF_ASSERT( wk->main_seq == SEQ_QUIT );
		*(wk->this_work_adrs) = NULL;
		PoketchWorkCleanup( wk );
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );

		sys_DeleteHeap( HEAPID_POKETCH_MAIN );
		sys_DeleteHeap( HEAPID_POKETCH_APP );

	}
}

//------------------------------------------------------------------
/**
 * ���C���A�`�擙�A�S�Ă̏������I�������ɂP�����Ă���^�X�N
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PoketchTail( TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_WORK* wk = wk_adrs;

	wk->player_move_flag = FALSE;
	wk->pedometer_update_flag = FALSE;
}

//------------------------------------------------------------------
/**
 * �V�[�P���X�؂�ւ�
 *
 * @param   wk		���[�N�|�C���^
 * @param   seq		���̃V�[�P���X
 *
 */
//------------------------------------------------------------------
static void ChangeSeq( POKETCH_WORK *wk, u32 seq )
{
	wk->main_seq = seq;
	wk->seq = 0;
}


//------------------------------------------------------------------
/**
 * �V�[�P���X�F��ʍ\�z
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void SeqInit(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_MAIN_SetCommand(wk->view_wk, CMD_MAIN_INIT);
		wk->seq++;
		break;

	case 1:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_INIT))
		{
			u32 appID = PoketchData_GetNowApplication(wk->poketch_savedata);
			LoadApplication( wk, appID );
			InitApplication( wk, appID );
			wk->seq++;
		}
		break;

	case 2:
		if( WaitInitApplication(wk) == FALSE )
		{
			break;
		}
		Poketch_MAIN_SetCommand(wk->view_wk, CMD_MAIN_FIRSTOPEN);
		wk->seq++;
		/* fallthru */
	case 3:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_FIRSTOPEN))
		{
			ChangeSeq(wk, SEQ_APP_MAIN);
		}
	}
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�A�v�����C��
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SeqAppMain(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		if( PoketchIsSleepMode(wk) )
		{
			return;
		}

		switch( wk->button_action ){
		case BMN_EVENT_TAP:
		case BMN_EVENT_TIMER0:
			PoketchProcPrintf("�^�b�v���ꂽ\n");
			wk->app_skip_flag = FALSE;
			wk->app_changing_flag = TRUE;
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_EFFCLOSE );
			wk->seq++;
			break;
		}
		break;

	case 1:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			PoketchProcPrintf("�X�L�b�v�t���OON\n");
			wk->app_skip_flag = TRUE;
		}

		if(Poketch_MAIN_WaitCommandAll( wk->view_wk ))
		{
			wk->vpara.app_pos = PoketchData_SetApplicationPosNext( wk->poketch_savedata );
			if( wk->app_skip_flag )
			{
				Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_DISP );
				wk->app_skip_timer = APP_SKIP_TIMER;
				wk->app_skip_flag = FALSE;
				wk->seq = 4;
			}
			else
			{
				PoketchProcPrintf("�r�d�p�Q��\n");
				wk->app_skip_timer = APP_FIRST_SKIP_TIMER;
				wk->seq = 2;
			}
		}
		break;

	case 2:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_DISP );
			wk->app_skip_timer = APP_SKIP_TIMER;
			wk->app_skip_flag = FALSE;
			wk->seq = 4;
			break;
		}

		if( wk->app_skip_timer )
		{
			wk->app_skip_timer--;
		}
		else
		{
			QuitApplication( wk );
			wk->seq = 3;
		}
		break;

	case 3:
		if( WaitQuitApplication(wk) )
		{
			PoketchProcPrintf("�A�v���I������̂Ő؂�ւ��V�[�P���X��\n");
			UnloadApplication( wk );
			PoketchWork_Reset();
			ChangeSeq(wk, SEQ_APPCHANGE_NORMAL);
		}
		break;

	// �A�Ŏ�t�J�n
	case 4:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			wk->vpara.app_pos = PoketchData_SetApplicationPosNext( wk->poketch_savedata );
			wk->app_skip_timer = APP_SKIP_TIMER;
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_UPDATE );
			break;
		}

		if(wk->app_skip_timer)
		{
			wk->app_skip_timer--;
		}
		else
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_END );
			QuitApplication( wk );
			wk->seq = 3;
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�A�v���؂�ւ�
 *
 * @param   wk		
 */
//------------------------------------------------------------------
static void SeqAppChange(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		{
			u32 appID;
			wk->appchange_button_disable_flag = TRUE;

			appID = PoketchData_GetNowApplication( wk->poketch_savedata );
			LoadApplication( wk, appID );
			InitApplication( wk, appID );

			wk->seq++;
		}
		break;

	case 1:
		if( WaitInitApplication(wk) )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_EFFOPEN );
			wk->seq++;
		}
		break;

	case 2:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_EFFOPEN))
		{
			wk->app_changing_flag = FALSE;
			wk->appchange_button_disable_flag = FALSE;
			ChangeSeq(wk, SEQ_APP_MAIN);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �V�[�P���X�F�|�P�b�`�I��
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SeqCleanUp( POKETCH_WORK *wk )
{
	enum {
		SEQ_INIT = 0,
		SEQ_WAIT_APP_INIT,
		SEQ_WAIT_APP_QUIT,
		SEQ_WAIT_VIEW_QUIT,
	};

	switch( wk->seq ){
	case SEQ_INIT:
		switch( wk->app_state ){
		case APP_STATE_INIT:
			wk->seq = SEQ_WAIT_APP_INIT;
			break;
		case APP_STATE_RUN:
			QuitApplication( wk );
			wk->seq = SEQ_WAIT_APP_QUIT;
			break;
		case APP_STATE_QUIT:
		case APP_STATE_CLEAN:
			wk->seq = SEQ_WAIT_APP_QUIT;
			break;
		}
		break;

	case SEQ_WAIT_APP_INIT:
		if( WaitInitApplication(wk) )
		{
			QuitApplication( wk );
			wk->seq = SEQ_WAIT_APP_QUIT;
		}
		break;

	case SEQ_WAIT_APP_QUIT:
		if( WaitQuitApplication(wk) )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_QUIT );
			wk->seq = SEQ_WAIT_VIEW_QUIT;
		}
		break;

	case SEQ_WAIT_VIEW_QUIT:
		if( Poketch_MAIN_WaitCommandAll( wk->view_wk ) )
		{
			UnloadApplication( wk );
			StopTP();
			ChangeSeq( wk, SEQ_QUIT );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * �A�v���P�[�V�����̃I�[�o�[���C���W���[�������[�h
 *
 * @param   app_no		�A�v���P�[�V�����i���o�[
 *
 */
//------------------------------------------------------------------
static void LoadApplication( POKETCH_WORK* wk, int appID)
{
	GF_ASSERT( appID >= 0 && appID < NELEMS(OverlayID) );

	if( wk->load_app_id == POKETCH_APP_NONE )
	{
		int i;
		PoketchProcPrintf("�A�v�� Load ���܂�\n");

		for(i=0; i<NELEMS(OverlayID); i++)
		{
			if( OverlayID[i].appID == appID )
			{
				Overlay_Load( OverlayID[i].overlayID, OVERLAY_LOAD_NOT_SYNCHRONIZE);
				wk->load_app_id = appID;
				wk->load_app_overlay_id = OverlayID[i].overlayID;
				break;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * �A�v���P�[�V�����̃I�[�o�[���C���W���[�����A�����[�h
 *
 * @param   app_no		
 *
 */
//------------------------------------------------------------------
static void UnloadApplication( POKETCH_WORK* wk )
{
	if( wk->load_app_id != POKETCH_APP_NONE )
	{
		PoketchProcPrintf("�A�v�� Unload ���܂�\n");
		Overlay_UnloadID( wk->load_app_overlay_id );
		wk->load_app_id = POKETCH_APP_NONE;
	}
}


//------------------------------------------------------------------
/**
 * ���[�h�����A�v���̏������J�n
 *
 * @param   wk		
 * @param   app_no		
 *
 */
//------------------------------------------------------------------
static void InitApplication( POKETCH_WORK* wk, u32 app_no )
{
	GF_ASSERT(wk->app_state == APP_STATE_CLEAN);
	PoketchProcPrintf("�A�v���������J�n���܂�\n");
	wk->app_init_proc( &(wk->app_work), wk, wk->bgl, wk->load_app_id );
	wk->app_state = APP_STATE_INIT;
}
//------------------------------------------------------------------
/**
 * ���[�h�����A�v���̏������I���҂�
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL WaitInitApplication( POKETCH_WORK* wk )
{
	if( wk->app_state == APP_STATE_RUN )
	{
		PoketchProcPrintf("�A�v���������������܂���\n");
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * ���[�h�����A�v���̏I�������J�n
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void QuitApplication( POKETCH_WORK* wk )
{
	GF_ASSERT(wk->app_state == APP_STATE_RUN);
	PoketchProcPrintf("�A�v���I�������J�n���܂�\n");
	wk->app_quit_proc( wk->app_work );
	wk->app_state = APP_STATE_QUIT;
}
//------------------------------------------------------------------
/**
 * ���[�h�����A�v���̏I�������҂�
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL WaitQuitApplication( POKETCH_WORK* wk )
{
	if( wk->app_state == APP_STATE_CLEAN )
	{
		PoketchProcPrintf("�A�v���I�������������܂���\n");
		return TRUE;
	}
	return FALSE;
}

/*====================================================================================*/
/*                                                                                    */
/*  �e�A�v������ʒm���󂯎��֐��Q                                                  */
/*                                                                                    */
/*====================================================================================*/

//------------------------------------------------------------------
/**
 * �e�A�v�����W���[���̃��[�h��ANitroStaticInit�ɂ��Ăяo�����
 * �A�v���̊e�퐧��֐��A�h���X���󂯎��
 *
 * @param   initproc		�������֐�
 * @param   quitproc		�I���֐�
 *
 */
//------------------------------------------------------------------
void PoketchSetAppProc( pAppInitProc initproc, pAppQuitProc quitproc)
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	wk->app_init_proc = initproc;
	wk->app_quit_proc = quitproc;
	wk->app_save_proc = NULL;
}
//------------------------------------------------------------------
/**
 * �e�A�v������̏����������ʒm���󂯎��
 */
//------------------------------------------------------------------
void PoketchNoticeAppStart(CONTACT_WORK* wk)
{
	PoketchProcPrintf("�A�v���J�n�ʒm�����Ƃ�\n");

	GF_ASSERT(wk->app_state==APP_STATE_INIT);
	wk->app_state = APP_STATE_RUN;
}
//------------------------------------------------------------------
/**
 * �e�A�v������̏I���ʒm���󂯎��
 */
//------------------------------------------------------------------
void PoketchNoticeAppEnd(CONTACT_WORK* wk)
{
	PoketchProcPrintf("�A�v���I���ʒm�����Ƃ�\n");

	GF_ASSERT(wk->app_state==APP_STATE_QUIT);
	wk->app_state = APP_STATE_CLEAN;
}

//------------------------------------------------------------------
/**
 * �e�A�v���̃f�[�^�Z�[�u�p�֐��A�h���X���󂯎��
 *�i���|�[�g���ɃZ�[�u���K�v�ȃA�v���̂ݗ��p����j
 *
 * @param   saveproc	�Z�[�u�֐��A�h���X
 * @param   arg			�֐��Ăяo���ɕK�v�Ȉ���
 *
 */
//------------------------------------------------------------------
void PoketchSetAppSaveProc( pAppSaveProc saveproc, void* arg )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	wk->app_save_proc = saveproc;
	wk->app_save_arg = arg;
}


/*====================================================================================*/
/*                                                                                    */
/*  �{�^����ԃ��[�N����                                                              */
/*                                                                                    */
/*====================================================================================*/

// enum POKETCH_BUTTON_VIEW �̕��тƓ���
static const u32 ButtonViewCmd[] = {
	CMD_MAIN_BUTTONFREE,
	CMD_MAIN_BUTTONLOCK,
	CMD_MAIN_BUTTONPUSH,
};

enum {
	BUTTON_TIMER_TAP = 7,
	BUTTON_TIMER_DOUBLETAP = 8,		// �ŏ��̃^�b�v����_�u���^�b�v������s���t���[����
};

enum {
	BUTTON_ID_MAIN,		///< ���C���̃{�^��
	BUTTON_ID_SCREEN,	///< ��ʑS�̂��{�^���Ƃ��Ĉ����c
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
static BOOL BmnSetup( POKETCH_WORK* wk )
{
	// �{�^���ʒu�iview�Ɏ����������ǂ��̂��c?�j
	static const TP_HIT_TBL ButtonRectData[] = {
		{ 96, 172, 220, 244 },
		{ POKETCH_MONITOR_DOT_YORG, POKETCH_MONITOR_DOT_YEND, POKETCH_MONITOR_DOT_XORG, POKETCH_MONITOR_DOT_XEND },
	};

	wk->button = PBTN_Create( ButtonRectData, NELEMS(ButtonRectData), BmnCallBack, wk, POKETCH_MAIN_CTRL_HEAPID );
	if( wk->button != NULL )
	{
		PBTN_SetEventTime( wk->button, 0, 0, BUTTON_TIMER_TAP );
		wk->button_cmd_req = CMD_NULL;
		wk->button_prev_cmd = CMD_NULL;
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
static void BmnCleanup( POKETCH_WORK *wk )
{
	PBTN_Delete( wk->button );
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void ButtonUpdate( POKETCH_WORK *wk )
{
	wk->button_action = BMN_EVENT_NULL;
	PBTN_Main( wk->button );
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
	POKETCH_WORK *wk = (POKETCH_WORK*)wk_adrs;

	// �t�B�[���h���ɒʒm����u�|�P�b�`�G���Ă�t���O�v�̍X�V
	if( PoketchIsSleepMode(wk) == FALSE )
	{
		switch( touch_event ){
		case BMN_TOUCH_ON:
			wk->touch_flag = TRUE;
			break;
		case BMN_TOUCH_OFF:
			wk->touch_flag = FALSE;
			break;
		}
	}
	else
	{
		wk->touch_flag = FALSE;
	}

	// �X�N���[������G��ꂽ���̏���
	if( idx == BUTTON_ID_SCREEN )
	{
		if( PoketchIsSleepMode(wk) )
		{
			if(touch_event == BMN_TOUCH_ON)
			{
				Snd_SePlay( POKETCH_SE_BEEP );
			}
		}
	}
	// �{�^������G��ꂽ���̏���
	else
	{
		u32 v_cmd = CMD_NULL;

		switch(touch_event){
		case BMN_TOUCH_OFF:
			v_cmd = CMD_MAIN_BUTTONFREE;
			PoketchProcPrintf( "@@BTN  off\n");
			break;
		case BMN_TOUCH_ON:
			if( PoketchIsSleepMode(wk) || wk->appchange_button_disable_flag )
			{
				v_cmd = CMD_MAIN_BUTTONLOCK;
				event = BMN_EVENT_NULL;
				PoketchProcPrintf( "@@BTN  on, sleep\n");
			}
			else
			{
				v_cmd = CMD_MAIN_BUTTONPUSH;
				PoketchProcPrintf( "@@BTN  on, wake\n");
			}
			break;
		}

		if( wk->button_cmd_req != CMD_NULL )
		{
			u32 tmp = v_cmd;
			PoketchProcPrintf( "@@BTN  cmd_swap %d->%d\n", v_cmd, wk->button_cmd_req);
			v_cmd = wk->button_cmd_req;
			wk->button_cmd_req = tmp;
		}

		if(v_cmd != CMD_NULL)
		{
			PoketchProcPrintf( "@@BTN  vcmd:%d\n", v_cmd);
			if( ButtonViewReq( wk->view_wk, v_cmd ) )
			{
				if( v_cmd == CMD_MAIN_BUTTONLOCK || v_cmd == CMD_MAIN_BUTTONPUSH )
				{
					wk->button_prev_cmd = v_cmd;
				}
			}
		}

		switch( event ){
		case BMN_EVENT_TIMER0:
			PBTN_ResetState( wk->button, 0 );
			break;
		case BMN_EVENT_TAP:
			// �X���[�v���ɉ�������ă��b�N���^�b�v���̓X���[�v����Ȃ��̂Ń{�^���C�x���g�L��
			// �݂����Ȃ��Ƃ�h��
			if( wk->button_prev_cmd == CMD_MAIN_BUTTONLOCK )
			{
				event = BMN_EVENT_NULL;
			}
			break;
		case BMN_EVENT_OUT:
			// �������񂾂�����X���C�h�A�E�g�ł�����������
			if( wk->button_prev_cmd == CMD_MAIN_BUTTONPUSH )
			{
				event = BMN_EVENT_TAP;
			}
			break;
		}

		PoketchProcPrintf( "@@BTN  event=%d\n", event);
		wk->button_action = event;
	}
}
//------------------------------------------------------------------
/**
 * �{�^���\���X�V�R�}���h��view���ɓ`����
 *
 * @param   wk		�|�P�b�`���[�N
 * @param   cmd		�R�}���h
 *
 * @retval  TRUE�ŃR�}���h���s�����^FALSE���ƑO�̃R�}���h�������Ȃ̂Ŗ�������
 */
//------------------------------------------------------------------
static BOOL ButtonViewReq( POKETCH_VIEW_WORK *vwk, u32 cmd )
{
	u32 i;

	for(i = 0; i < NELEMS(ButtonViewCmd); i++)
	{
		if( Poketch_MAIN_WaitCommand( vwk, cmd ) == FALSE )
		{
			return FALSE;
		}
	}
	Poketch_MAIN_SetCommand( vwk, cmd );
	return TRUE;
}



/*====================================================================================*/
/*                                                                                    */
/*  �`����۰ّ�����Ăяo�����֐�                                                  */
/*                                                                                    */
/*====================================================================================*/

POKETCH_VIEW_WORK* PoketchGetMainViewWork( void )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	return wk->view_wk;
}


void PoketchSePlay( u32 se )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		Snd_SePlay( se );
	}
}

void PoketchVoicePlay( u32 pokeno )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		Snd_PMVoicePlay( pokeno );
	}
}
static inline BOOL check_inside_poketch_screen( u32 x, u32 y )
{
	if( ((u32)(x - POKETCH_MONITOR_DOT_XORG) < (u32)(POKETCH_MONITOR_DOT_XEND - POKETCH_MONITOR_DOT_XORG))
	&	((u32)(y - POKETCH_MONITOR_DOT_YORG) < (u32)(POKETCH_MONITOR_DOT_YEND - POKETCH_MONITOR_DOT_YORG))
	){
		return TRUE;
	}
	return FALSE;
}


BOOL PoketchGetTPCont( u32* x, u32 *y )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		if( GF_TP_GetPointCont(x, y) )
		{
			return check_inside_poketch_screen(*x, *y);
		}
	}
	return FALSE;
}

BOOL PoketchGetTPTrg( u32* x, u32 *y )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		if( GF_TP_GetPointTrg( x, y ) )
		{
			return check_inside_poketch_screen(*x, *y);
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * �X���[�v���[�h���ǂ����`�F�b�N
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PoketchIsSleepMode( const CONTACT_WORK* wk )
{
	return FieldEvent_Check( wk->fieldsys );
}

//------------------------------------------------------------------
/**
 * �{�^���}�l�[�W�������Ăяo��
 *
 * @param   man
 */
//------------------------------------------------------------------
void PoketchButtonMainCall( const CONTACT_WORK* wk, POKETCH_BUTTON_MAN* man )
{
	if(	(PoketchIsSleepMode(wk) ==  FALSE)
	&&	(wk->app_changing_flag == FALSE)
	){
		PBTN_Main( man );
	}
}

//------------------------------------------------------------------
/**
 * �v���C���[�ړ��t���O���擾
 *
 * @param   wk		
 *
 * @retval  BOOL	
 */
//------------------------------------------------------------------
BOOL PoketchGetPlayerMoveTrg( const CONTACT_WORK* wk )
{
	return wk->player_move_flag;;
}
//------------------------------------------------------------------
/**
 * �����v�X�V�t���O���擾
 *
 * @param   wk		
 *
 * @retval  BOOL	
 */
//------------------------------------------------------------------
BOOL PoketchGetPedometerUpdateFlag( const CONTACT_WORK* wk )
{
	return wk->pedometer_update_flag;
}

FIELDSYS_WORK* PoketchGetFieldSysWork( const CONTACT_WORK* wk )
{
	return wk->fieldsys;
}

POKETCH_DATA* PoketchGetSaveData( const CONTACT_WORK* wk )
{
	return (POKETCH_DATA*)(wk->poketch_savedata);
}

SAVEDATA* PoketchGetSystemSaveData( const CONTACT_WORK* wk )
{
	return (SAVEDATA*)(wk->savedata);
}

int PoketchGetBoardType( const CONTACT_WORK* wk )
{
	MYSTATUS* myst = SaveData_GetMyStatus( wk->savedata );

	if( MyStatus_GetMySex(myst) == PM_FEMALE )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

