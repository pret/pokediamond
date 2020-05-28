//============================================================================================
/**
 * @file	pms_input.c
 * @bfief	簡易会話入力画面
 * @author	taya
 * @date	06.01.20
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\touchpanel.h"
#include "gflib\button_man.h"
#include "system\procsys.h"
#include "system\pms_data.h"

#include "pmsi_sound_def.h"
#include "pms_input_prv.h"
#include "pmsi_initial_data.h"


//------------------------------------------------------
/**
 * 定数定義
 */
//------------------------------------------------------
enum {
	HEAPSIZE_SYS = 0x8000,
	HEAPSIZE_VIEW = 0x28000,
};

enum {
	MAINSEQ_FADEIN = 0,
	MAINSEQ_SINGLE_MODE,
	MAINSEQ_DOUBLE_MODE,
	MAINSEQ_SENTENCE_MODE,
};


typedef enum {
	MENU_RESULT_NONE = -1,
	MENU_RESULT_CANCEL = -2,
	MENU_RESULT_MOVE = -3,
	MENU_RESULT_DISABLE_KEY = -4,

	MENU_RESULT_POS_YES = 0,
	MENU_RESULT_POS_NO,
	MENU_RESULT_POS_MAX = MENU_RESULT_POS_NO,

}MENU_RESULT;

enum {
	WORDWIN_RESULT_NONE,
	WORDWIN_RESULT_CURSOR_MOVE,
	WORDWIN_RESULT_SCROLL,
	WORDWIN_RESULT_SCROLL_AND_CURSOR_MOVE,
	WORDWIN_RESULT_INVALID,
};

enum {
	WORDWIN_CURSOR_X_MAX = 1,
	WORDWIN_CURSOR_Y_MAX = 4,
	WORDWIN_DISP_MAX = 10,

	WORDWIN_PAGE_LINES = WORDWIN_CURSOR_Y_MAX+1,
};

enum TOUCH_BUTTON {
	TOUCH_BUTTON_GROUP,
	TOUCH_BUTTON_INITIAL,
	TOUCH_BUTTON_UP,
	TOUCH_BUTTON_DOWN,

	TOUCH_BUTTON_NULL,
};


//------------------------------------------------------
/**
 * 関数型定義
 */
//------------------------------------------------------
typedef  void (*SubProc)(PMS_INPUT_WORK*, int*);
typedef  PROC_RESULT (*MainProc)(PMS_INPUT_WORK*, int*);

//------------------------------------------------------
/**
 * メニュー操作ワーク
 */
//------------------------------------------------------
typedef struct {
	u8   pos;
	u8   max;
}MENU_WORK;

typedef struct {
	u16   line;
	u16   line_max;
	u16   word_max;
	u8    cursor_x;
	u8    cursor_y;
	int   scroll_lines;

}WORDWIN_WORK;

typedef struct {
	s16  sentence_type;
	s8   sentence_id;
	s8   sentence_id_max;
}SENTENCE_WORK;


//------------------------------------------------------
/**
 * ワーク領域定義
 */
//------------------------------------------------------
struct _PMS_INPUT_WORK{

	PMSI_PARAM*   input_param;
	u32           input_mode;

	PMS_DATA      edit_pms;
	PMS_WORD      edit_word[ PMS_INPUT_WORD_MAX ];

	PMS_INPUT_VIEW*   vwk;
	PMS_INPUT_DATA*   dwk;

	int          main_seq;
	MainProc     main_proc;
	MainProc     next_proc;

	int          sub_seq;
	SubProc      sub_proc;




	u16           key_trg;
	u16           key_cont;
	u16           key_repeat;
	int           touch_button;
	int           hold_button;
	BUTTON_MAN*   bmn;
	BOOL          button_up_hold_flag;
	BOOL          button_down_hold_flag;

	u16        cmd_button_pos;
	u16        edit_pos;
	u16        category_pos;
	u16        category_pos_prv;

	WORDWIN_WORK   word_win;

	SENTENCE_WORK  sentence_wk;

	u8         sentence_edit_pos_max;
	u8         category_mode;


	MENU_WORK  menu;

};


//==============================================================
// Prototype
//==============================================================
static void BmnCallBack( u32 buttonID, u32 event, void* wk_ptr );
static PMS_INPUT_WORK* ConstructWork( PROC* proc );
static void setup_sentence_work( SENTENCE_WORK* s_wk, PMS_DATA* pms );
static void sentence_increment( SENTENCE_WORK* s_wk, PMS_DATA* pms );
static void sentence_decrement( SENTENCE_WORK* s_wk, PMS_DATA* pms );
static void DestructWork( PMS_INPUT_WORK* wk, PROC* proc );
static void ChangeMainProc( PMS_INPUT_WORK* wk, MainProc main_proc );
static void ChangeMainProc_ToCommandButtonArea( PMS_INPUT_WORK* wk );
static PROC_RESULT MainProc_EditArea( PMS_INPUT_WORK* wk, int* seq );
static PROC_RESULT mp_input_single( PMS_INPUT_WORK* wk, int* seq );
static PROC_RESULT mp_input_double( PMS_INPUT_WORK* wk, int* seq );
static PROC_RESULT mp_input_sentence( PMS_INPUT_WORK* wk, int* seq );
static PROC_RESULT MainProc_CommandButton( PMS_INPUT_WORK* wk, int* seq );
static PROC_RESULT MainProc_Category( PMS_INPUT_WORK* wk, int* seq );
static BOOL check_category_enable( PMS_INPUT_WORK* wk );
static BOOL check_category_cursor_move( PMS_INPUT_WORK* wk );
static BOOL keycheck_category_group_mode( PMS_INPUT_WORK* wk );
static BOOL keycheck_category_initial_mode( PMS_INPUT_WORK* wk );
static void setup_wordwin_params( WORDWIN_WORK* word_win, PMS_INPUT_WORK* wk );
static u32 get_wordwin_cursorpos( const WORDWIN_WORK* wordwin );
static u32 get_wordwin_pos( const WORDWIN_WORK* wordwin );
static int get_wordwin_scroll_vector( const WORDWIN_WORK* wordwin );
static int get_wordwin_linepos( const WORDWIN_WORK* wordwin );
static int get_wordwin_linemax( const WORDWIN_WORK* wordwin );
static PROC_RESULT MainProc_WordWin( PMS_INPUT_WORK* wk, int* seq );
static int check_wordwin_key( WORDWIN_WORK* wordwin, u16 key );
static int check_wordwin_scroll_up( WORDWIN_WORK* wordwin );
static int check_wordwin_scroll_down( WORDWIN_WORK* wordwin );
static BOOL set_select_word( PMS_INPUT_WORK* wk );
static PROC_RESULT MainProc_Quit( PMS_INPUT_WORK* wk, int* seq );
static void SetSubProc( PMS_INPUT_WORK* wk, SubProc sub_proc );
static void QuitSubProc( PMS_INPUT_WORK* wk );
static void SubProc_FadeIn( PMS_INPUT_WORK* wk, int* seq );
static void SubProc_CommandOK( PMS_INPUT_WORK* wk, int* seq );
static void SubProc_CommandCancel( PMS_INPUT_WORK* wk, int* seq );
static BOOL CheckModified( PMS_INPUT_WORK* wk );
static BOOL check_input_complete( PMS_INPUT_WORK* wk );
static void InitMenuState( MENU_WORK* menu, int max, int pos );
static MENU_RESULT  CtrlMenuState( MENU_WORK* menu , u16 key );
static u32 get_menu_cursor_pos( const MENU_WORK* menu );
static void SubProc_ChangeCategoryMode( PMS_INPUT_WORK* wk, int* seq );



//==============================================================
// PROC-DATA
//==============================================================
const PROC_DATA ProcData_PMSInput = {
	PMSInput_Init,
	PMSInput_Main,
	PMSInput_Quit,
	NO_OVERLAY_ID,
};



//------------------------------------------------------------------
/**
 * PROC初期化
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT PMSInput_Init( PROC * proc, int * seq )
{
	PMS_INPUT_WORK* wk;

	switch( *seq ){
	case 0:
		Snd_DataSetByScene( SND_SCENE_SUB_PMS, 0, 0 );	// サウンドデータロード(PMS)(BGM引継ぎ)

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_PMS_INPUT_SYSTEM, HEAPSIZE_SYS );
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_PMS_INPUT_VIEW, HEAPSIZE_VIEW );
		wk = ConstructWork( proc );
		PMSIView_SetCommand( wk->vwk, VCMD_INIT );
		(*seq)++;
		break;

	case 1:
		wk = PROC_GetWork( proc );
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			if( wk->input_mode == PMSI_MODE_SENTENCE )
			{
				wk->sentence_edit_pos_max = PMSIView_GetSentenceEditPosMax( wk->vwk );
			}
			else
			{
				wk->sentence_edit_pos_max = 0;
			}
			return PROC_RES_FINISH;
		}
		break;
	}

	return PROC_RES_CONTINUE;
}



//------------------------------------------------------------------
/**
 * PROC メイン
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT PMSInput_Main( PROC * proc, int * seq )
{
	PMS_INPUT_WORK* wk = PROC_GetWork( proc );

	wk->key_trg = sys.trg;
	wk->key_cont = sys.cont;
	wk->key_repeat = sys.repeat;

	BMN_Main( wk->bmn );

	if( wk->sub_proc != NULL )
	{
		wk->sub_proc( wk, &(wk->sub_seq) );
		return PROC_RES_CONTINUE;
	}
	else
	{
		return wk->main_proc( wk, &(wk->main_seq) );
	}

	return PROC_RES_CONTINUE;
}

//------------------------------------------------------------------
/**
 * ボタン管理マネージャコールバック
 *
 * @param   buttonID	
 * @param   event		
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
static void BmnCallBack( u32 buttonID, u32 event, void* wk_ptr )
{
	PMS_INPUT_WORK* wk = wk_ptr;

	switch( event ){
	case BMN_EVENT_TOUCH:
		wk->touch_button = buttonID;
		switch(buttonID){
		case TOUCH_BUTTON_UP:
			PMSIView_SetCommand( wk->vwk, VCMD_BUTTON_UP_HOLD );
			break;
		case TOUCH_BUTTON_DOWN:
			PMSIView_SetCommand( wk->vwk, VCMD_BUTTON_DOWN_HOLD );
			break;
		}
		break;

	case BMN_EVENT_RELEASE:
	case BMN_EVENT_SLIDEOUT:
		switch(buttonID){
		case TOUCH_BUTTON_UP:
			PMSIView_SetCommand( wk->vwk, VCMD_BUTTON_UP_RELEASE );
			break;
		case TOUCH_BUTTON_DOWN:
			PMSIView_SetCommand( wk->vwk, VCMD_BUTTON_DOWN_RELEASE );
			break;
		}
		wk->touch_button = TOUCH_BUTTON_NULL;
		break;

	case BMN_EVENT_HOLD:
		if(	(buttonID == TOUCH_BUTTON_UP)
		||	(buttonID == TOUCH_BUTTON_DOWN)
		){
			wk->touch_button = buttonID;
		}
		break;

	default:
		wk->touch_button = TOUCH_BUTTON_NULL;
		break;
	}
}

//------------------------------------------------------------------
/**
 * PROC 終了
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT PMSInput_Quit( PROC * proc, int * seq )
{
	DestructWork( PROC_GetWork(proc), proc );

	sys_DeleteHeap( HEAPID_PMS_INPUT_SYSTEM );
	sys_DeleteHeap( HEAPID_PMS_INPUT_VIEW );

	return PROC_RES_FINISH;
}
//------------------------------------------------------------------
/**
 * メインワーク構築
 *
 * @param   wk		
 * @param   proc		
 *
 */
//------------------------------------------------------------------
static PMS_INPUT_WORK* ConstructWork( PROC* proc )
{
	// enum TOUCH_BUTTON と一致させる
	static const TP_HIT_TBL hit_tbl[] = {
		{ BUTTON_GROUP_TOUCH_TOP, BUTTON_GROUP_TOUCH_BOTTOM, BUTTON_GROUP_TOUCH_LEFT, BUTTON_GROUP_TOUCH_RIGHT },
		{ BUTTON_INITIAL_TOUCH_TOP, BUTTON_INITIAL_TOUCH_BOTTOM, BUTTON_INITIAL_TOUCH_LEFT, BUTTON_INITIAL_TOUCH_RIGHT },
		{ BUTTON_UP_TOUCH_TOP, BUTTON_UP_TOUCH_BOTTOM, BUTTON_UP_TOUCH_LEFT, BUTTON_UP_TOUCH_RIGHT },
		{ BUTTON_DOWN_TOUCH_TOP, BUTTON_DOWN_TOUCH_BOTTOM, BUTTON_DOWN_TOUCH_LEFT, BUTTON_DOWN_TOUCH_RIGHT },
		{ TP_HIT_END, 0, 0, 0 },
	};

	PMS_INPUT_WORK* wk;

	wk = PROC_AllocWork( proc, sizeof(PMS_INPUT_WORK), HEAPID_PMS_INPUT_SYSTEM );
	wk->input_param = PROC_GetParentWork( proc );
	wk->input_mode = PMSI_PARAM_GetInputMode( wk->input_param );

	PMSI_PARAM_GetInitializeData( wk->input_param, wk->edit_word, &wk->edit_pms );

	if( wk->input_mode == PMSI_MODE_SENTENCE )
	{
		setup_sentence_work( &wk->sentence_wk, &wk->edit_pms );
	}


	wk->dwk = PMSI_DATA_Create( HEAPID_PMS_INPUT_SYSTEM, wk->input_param );
	wk->vwk = PMSIView_Create(wk, wk->dwk);
	wk->bmn = BMN_Create( hit_tbl, NELEMS(hit_tbl), BmnCallBack, wk, HEAPID_PMS_INPUT_SYSTEM );
	wk->button_up_hold_flag = FALSE;
	wk->button_down_hold_flag = FALSE;

	wk->category_mode = CATEGORY_MODE_GROUP;
	wk->sub_proc = NULL;
	wk->sub_seq = 0;
	wk->main_proc = MainProc_EditArea;
	wk->main_seq = 0;

	wk->edit_pos = 0;

	SetSubProc( wk, SubProc_FadeIn );

	return wk;
}

static void setup_sentence_work( SENTENCE_WORK* s_wk, PMS_DATA* pms )
{
	s_wk->sentence_type = PMSDAT_GetSentenceType(pms);
	s_wk->sentence_id_max = PMSDAT_GetSentenceIdMax(s_wk->sentence_type);
	s_wk->sentence_id = PMSDAT_GetSentenceID(pms);
}

static void sentence_increment( SENTENCE_WORK* s_wk, PMS_DATA* pms )
{
	s_wk->sentence_id++;
	if( s_wk->sentence_id >= s_wk->sentence_id_max )
	{
		s_wk->sentence_id = 0;
		s_wk->sentence_type++;
		if( s_wk->sentence_type >= PMS_TYPE_MAX )
		{
			s_wk->sentence_type = 0;
		}
		s_wk->sentence_id_max = PMSDAT_GetSentenceIdMax( s_wk->sentence_type );
	}

	PMSDAT_SetSentence( pms, s_wk->sentence_type, s_wk->sentence_id );
}

static void sentence_decrement( SENTENCE_WORK* s_wk, PMS_DATA* pms )
{
	s_wk->sentence_id--;
	if( s_wk->sentence_id < 0 )
	{
		s_wk->sentence_type--;
		if( s_wk->sentence_type < 0 )
		{
			s_wk->sentence_type = (PMS_TYPE_MAX - 1);
		}
		s_wk->sentence_id_max = PMSDAT_GetSentenceIdMax( s_wk->sentence_type );
		s_wk->sentence_id = (s_wk->sentence_id_max - 1);
	}

	PMSDAT_SetSentence( pms, s_wk->sentence_type, s_wk->sentence_id );
}



//------------------------------------------------------------------
/**
 * メインワーク破棄
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void DestructWork( PMS_INPUT_WORK* wk, PROC* proc )
{
	BMN_Delete( wk->bmn );
	PMSIView_Delete( wk->vwk );
	PMSI_DATA_Delete( wk->dwk );
	PROC_FreeWork( proc );
}




static void ChangeMainProc( PMS_INPUT_WORK* wk, MainProc main_proc )
{
	wk->main_proc = main_proc;
	wk->main_seq = 0;
}
static void ChangeMainProc_ToCommandButtonArea( PMS_INPUT_WORK* wk )
{
	ChangeMainProc( wk, MainProc_CommandButton );
}


//----------------------------------------------------------------------------------------------
/**
 * メインプロセス：入力欄での動作
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//----------------------------------------------------------------------------------------------
static PROC_RESULT MainProc_EditArea( PMS_INPUT_WORK* wk, int* seq )
{
	static const MainProc proc_tbl[] = {
		mp_input_single,
		mp_input_double,
		mp_input_sentence,
	};

	return proc_tbl[ wk->input_mode ]( wk, seq );
}

//------------------------------------------------------------------
/**
 * 単語１つ入力モード
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT mp_input_single( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_TO_COMMAND_BUTTON,
		SEQ_TO_SELECT_CATEGORY,
	};

	switch( *seq ){
	case SEQ_KEYWAIT:
		if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
		||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
		||	(wk->key_trg & PAD_BUTTON_SELECT)
		){
			SetSubProc( wk, SubProc_ChangeCategoryMode );
			break;
		}
		if( wk->key_trg & (PAD_KEY_DOWN | PAD_BUTTON_START))
		{
			Snd_SePlay(SOUND_MOVE_CURSOR);

			wk->cmd_button_pos = BUTTON_POS_DECIDE;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_BUTTON );
			(*seq) = SEQ_TO_COMMAND_BUTTON;
			break;
		}
		if( wk->key_trg & PAD_BUTTON_B )
		{
			Snd_SePlay(SOUND_CANCEL);

			SetSubProc( wk, SubProc_CommandCancel );
			break;
		}
		if( wk->key_trg & PAD_BUTTON_A )
		{
			Snd_SePlay(SOUND_DECIDE);

			wk->category_pos = 0;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_CATEGORY );
			(*seq) = SEQ_TO_SELECT_CATEGORY;
			break;
		}
		break;

	case SEQ_TO_COMMAND_BUTTON:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_CommandButton );
		}
		break;

	case SEQ_TO_SELECT_CATEGORY:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_Category );
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//------------------------------------------------------------------
/**
 * 単語２つ入力モード
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT mp_input_double( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_TO_COMMAND_BUTTON,
		SEQ_TO_SELECT_CATEGORY,
	};

	switch( *seq ){
	case SEQ_KEYWAIT:
		if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
		||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
		||	(wk->key_trg & PAD_BUTTON_SELECT)
		){
			SetSubProc( wk, SubProc_ChangeCategoryMode );
			break;
		}
		if( wk->key_trg & (PAD_KEY_DOWN|PAD_BUTTON_START) )
		{
			Snd_SePlay(SOUND_MOVE_CURSOR);

			wk->cmd_button_pos = BUTTON_POS_DECIDE;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_BUTTON );
			(*seq) = SEQ_TO_COMMAND_BUTTON;
			break;
		}
		if( wk->key_trg & PAD_KEY_LEFT )
		{
			if( wk->edit_pos != 0 )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);
				wk->edit_pos = 0;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_EDITAREA_CURSOR );
			}
			break;
		}
		if( wk->key_trg & PAD_KEY_RIGHT )
		{
			if( wk->edit_pos == 0 )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);
				wk->edit_pos = 1;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_EDITAREA_CURSOR );
			}
			break;
		}
		if( wk->key_trg & PAD_BUTTON_B )
		{
			Snd_SePlay(SOUND_CANCEL);

			SetSubProc( wk, SubProc_CommandCancel );
			break;
		}
		if( wk->key_trg & PAD_BUTTON_A )
		{
			Snd_SePlay(SOUND_DECIDE);

			wk->category_pos = 0;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_CATEGORY );
			(*seq) = SEQ_TO_SELECT_CATEGORY;
			break;
		}
		break;

	case SEQ_TO_COMMAND_BUTTON:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_CommandButton );
		}
		break;

	case SEQ_TO_SELECT_CATEGORY:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_Category );
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//------------------------------------------------------------------
/**
 * 文章入力モード
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT mp_input_sentence( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_INIT,
		SEQ_KEYWAIT,
		SEQ_WAIT_EDITAREA_UPDATE,
		SEQ_TO_COMMAND_BUTTON,
		SEQ_TO_SELECT_CATEGORY,
		
	};

	switch( *seq ){
	case SEQ_INIT:
		wk->sentence_edit_pos_max = PMSIView_GetSentenceEditPosMax( wk->vwk );
		(*seq) = SEQ_KEYWAIT;

		/* fallthru */


	case SEQ_KEYWAIT:
		if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
		||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
		||	(wk->key_trg & PAD_BUTTON_SELECT)
		){
			SetSubProc( wk, SubProc_ChangeCategoryMode );
			break;
		}
		if( wk->key_trg & PAD_KEY_UP )
		{
			if( (wk->sentence_edit_pos_max) && (wk->edit_pos != 0) )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);
				wk->edit_pos--;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_EDITAREA_CURSOR );
			}
			break;
		}
		if( wk->key_trg & PAD_KEY_DOWN )
		{
			Snd_SePlay(SOUND_MOVE_CURSOR);

			if( (wk->sentence_edit_pos_max) && (wk->edit_pos < (wk->sentence_edit_pos_max-1)) )
			{
				wk->edit_pos++;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_EDITAREA_CURSOR );
			}
			else
			{
				wk->cmd_button_pos = BUTTON_POS_DECIDE;
				PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_BUTTON );
				(*seq) = SEQ_TO_COMMAND_BUTTON;
				break;
			}
		}
		if( (wk->key_trg & PAD_BUTTON_START)
		||	( (wk->key_trg & PAD_BUTTON_A) && (wk->sentence_edit_pos_max==0) )
		){
			Snd_SePlay(SOUND_MOVE_CURSOR);

			wk->cmd_button_pos = BUTTON_POS_DECIDE;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_BUTTON );
			(*seq) = SEQ_TO_COMMAND_BUTTON;
			break;
		}
		if( wk->key_repeat & PAD_KEY_LEFT )
		{
			Snd_SePlay(SOUND_CHANGE_SENTENCE);

			wk->edit_pos = 0;
			sentence_decrement( &wk->sentence_wk, &wk->edit_pms );
			PMSIView_SetCommand( wk->vwk, VCMD_UPDATE_EDITAREA );
			(*seq) = SEQ_WAIT_EDITAREA_UPDATE;
			break;
		}
		if( wk->key_repeat & PAD_KEY_RIGHT )
		{
			Snd_SePlay(SOUND_CHANGE_SENTENCE);

			wk->edit_pos = 0;
			sentence_increment( &wk->sentence_wk, &wk->edit_pms );
			PMSIView_SetCommand( wk->vwk, VCMD_UPDATE_EDITAREA );
			(*seq) = SEQ_WAIT_EDITAREA_UPDATE;
			break;
		}

		if( wk->key_trg & PAD_BUTTON_B )
		{
			Snd_SePlay(SOUND_CANCEL);
			SetSubProc( wk, SubProc_CommandCancel );
			break;
		}
		if( wk->key_trg & PAD_BUTTON_A )
		{
			Snd_SePlay(SOUND_DECIDE);

			wk->category_pos = 0;
			PMSIView_SetCommand( wk->vwk, VCMD_EDITAREA_TO_CATEGORY );
			(*seq) = SEQ_TO_SELECT_CATEGORY;
			break;
		}
		break;

	case SEQ_WAIT_EDITAREA_UPDATE:
		if( PMSIView_WaitCommand( wk->vwk, VCMD_UPDATE_EDITAREA ) )
		{
			(*seq) = SEQ_INIT;
		}
		break;

	case SEQ_TO_COMMAND_BUTTON:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_CommandButton );
		}
		break;

	case SEQ_TO_SELECT_CATEGORY:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_Category );
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//----------------------------------------------------------------------------------------------
/**
 * メインプロセス：コマンドボタン（けってい・やめる）での動作
 *
 * @param   wk		
 * @param   seq		
 *
 */
//----------------------------------------------------------------------------------------------
static PROC_RESULT MainProc_CommandButton( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_TO_SUBPROC_OK,
		SEQ_TO_SUBPROC_CANCEL,
		SEQ_RETURN_SUBPROC_OK,
		SEQ_RETURN_SUBPROC_CANCEL,
		SEQ_TO_INPUT_AREA,
	};

	switch( *seq ){
	case SEQ_KEYWAIT:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{

			if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
			||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
			||	(wk->key_trg & PAD_BUTTON_SELECT)
			){
				SetSubProc( wk, SubProc_ChangeCategoryMode );
				break;
			}

			if( wk->key_trg & (PAD_KEY_LEFT | PAD_KEY_RIGHT) )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);

				wk->cmd_button_pos ^= 1;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_BUTTON_CURSOR );
				break;
			}

			if( wk->key_trg & PAD_BUTTON_START )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);
				wk->cmd_button_pos = BUTTON_POS_DECIDE;
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_BUTTON_CURSOR );
				break;
			}

			if( wk->key_trg & PAD_KEY_UP )
			{
				Snd_SePlay(SOUND_MOVE_CURSOR);

				PMSIView_SetCommand( wk->vwk, VCMD_BUTTON_TO_EDITAREA );
				(*seq) = SEQ_TO_INPUT_AREA;
				break;
			}

			if( wk->key_trg & PAD_BUTTON_A )
			{
				Snd_SePlay(SOUND_DECIDE);

				if( wk->cmd_button_pos == BUTTON_POS_DECIDE )
				{
					(*seq) = SEQ_TO_SUBPROC_OK;
					break;
				}
				else
				{
					(*seq) = SEQ_TO_SUBPROC_CANCEL;
					break;
				}
			}

			if( wk->key_trg & PAD_BUTTON_B )
			{
				Snd_SePlay(SOUND_DECIDE);
				(*seq) = SEQ_TO_SUBPROC_CANCEL;
				break;
			}
		}
		break;

	case SEQ_TO_SUBPROC_OK:
		(*seq) = SEQ_RETURN_SUBPROC_OK;
		SetSubProc( wk, SubProc_CommandOK );
		break;

	case SEQ_TO_SUBPROC_CANCEL:
		(*seq) = SEQ_RETURN_SUBPROC_CANCEL;
		SetSubProc( wk, SubProc_CommandCancel );
		break;

	case SEQ_RETURN_SUBPROC_OK:
	case SEQ_RETURN_SUBPROC_CANCEL:
		(*seq) = SEQ_KEYWAIT;
		break;

	case SEQ_TO_INPUT_AREA:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, MainProc_EditArea );
		}
		break;
	}


	return PROC_RES_CONTINUE;
}
//----------------------------------------------------------------------------------------------
/**
 * メインプロセス：カテゴリ選択
 *
 * @param   wk
 * @param   seq		
 *
 */
//----------------------------------------------------------------------------------------------
static PROC_RESULT MainProc_Category( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_NEXTPROC,
		SEQ_WAIT_MODE_CHANGE,
	};

	switch( *seq ){
	case SEQ_KEYWAIT:
		if (PMSIView_WaitCommand( wk->vwk, VCMD_MOVE_WORDWIN_CURSOR) == FALSE )
		{
			break;
		}

		if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
		||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
		||	(wk->key_trg & PAD_BUTTON_SELECT)
		){
			Snd_SePlay(SOUND_CHANGE_CATEGORY);
			wk->category_mode ^= 1;
			wk->category_pos = 0;
			PMSIView_SetCommand( wk->vwk, VCMD_CHANGE_CATEGORY_MODE_ENABLE );
			(*seq) = SEQ_WAIT_MODE_CHANGE;
			break;
		}

		if( wk->key_trg & PAD_BUTTON_B )
		{
			Snd_SePlay(SOUND_CANCEL);

			PMSIView_SetCommand( wk->vwk, VCMD_CATEGORY_TO_EDITAREA );
			wk->next_proc = MainProc_EditArea;
			*seq = SEQ_NEXTPROC;
			break;
		}
		if( wk->key_trg & PAD_BUTTON_A )
		{
			if( wk->category_pos == CATEGORY_POS_BACK )
			{
				Snd_SePlay(SOUND_CANCEL);

				PMSIView_SetCommand( wk->vwk, VCMD_CATEGORY_TO_EDITAREA );
				wk->next_proc = MainProc_EditArea;
				*seq = SEQ_NEXTPROC;
			}
			else if( check_category_enable( wk ) )
			{
				Snd_SePlay(SOUND_DECIDE);

				setup_wordwin_params( &wk->word_win, wk );
				wk->next_proc = MainProc_WordWin;
				PMSIView_SetCommand( wk->vwk, VCMD_CATEGORY_TO_WORDWIN );
				*seq = SEQ_NEXTPROC;
			}
			else
			{
				Snd_SePlay( SOUND_DISABLE_CATEGORY );
			}
			break;
		}
		if( check_category_cursor_move( wk ) )
		{
			Snd_SePlay(SOUND_MOVE_CURSOR);
			PMSIView_SetCommand( wk->vwk, VCMD_MOVE_CATEGORY_CURSOR );
			break;
		}
		break;

	case SEQ_NEXTPROC:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc( wk, wk->next_proc );
		}
		break;

	case SEQ_WAIT_MODE_CHANGE:
		if( PMSIView_WaitCommand( wk->vwk, VCMD_CHANGE_CATEGORY_MODE_ENABLE ) )
		{
			(*seq) = SEQ_KEYWAIT;
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//------------------------------------------------------------------
/**
 * 選択しているカテゴリに使用可能な単語が含まれているかチェック
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで含まれている
 */
//------------------------------------------------------------------
static BOOL check_category_enable( PMS_INPUT_WORK* wk )
{
	if( wk->category_mode == CATEGORY_MODE_GROUP )
	{
		return (PMSI_DATA_GetGroupEnableWordCount( wk->dwk, wk->category_pos ) != 0);
	}
	else
	{
		return (PMSI_DATA_GetInitialEnableWordCount( wk->dwk, wk->category_pos ) != 0 );
	}
	
}

//------------------------------------------------------------------
/**
 * カテゴリ選択時のカーソル移動チェック
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEでカーソル移動した
 */
//------------------------------------------------------------------
static BOOL check_category_cursor_move( PMS_INPUT_WORK* wk )
{
	static BOOL (* const func_tbl[])(PMS_INPUT_WORK*) = {
		keycheck_category_group_mode,
		keycheck_category_initial_mode,
	};

	return func_tbl[wk->category_mode]( wk );
}
//----------------------------------------------
// グループモード
//----------------------------------------------
static BOOL keycheck_category_group_mode( PMS_INPUT_WORK* wk )
{
	static const struct {
		u8   up_pos;
		u8   down_pos;
		u8   left_pos;
		u8   right_pos;
	}next_pos_tbl[] = {
		{ CATEGORY_POS_BACK,		CATEGORY_GROUP_SKILL2,	CATEGORY_GROUP_SKILL,	CATEGORY_GROUP_POKEMON2 },	// ポケモン
		{ CATEGORY_POS_BACK,		CATEGORY_GROUP_STATUS,	CATEGORY_GROUP_POKEMON,	CATEGORY_GROUP_SKILL },		// ポケモン２
		{ CATEGORY_POS_BACK,		CATEGORY_GROUP_TRAINER,	CATEGORY_GROUP_POKEMON2,CATEGORY_GROUP_POKEMON },	// わざ
		{ CATEGORY_GROUP_POKEMON,	CATEGORY_GROUP_PERSON,	CATEGORY_GROUP_TRAINER,	CATEGORY_GROUP_STATUS },	// わざ２
		{ CATEGORY_GROUP_POKEMON2,	CATEGORY_GROUP_GREET,	CATEGORY_GROUP_SKILL2,	CATEGORY_GROUP_TRAINER },	// ステータス
		{ CATEGORY_GROUP_SKILL,		CATEGORY_GROUP_LIFE,	CATEGORY_GROUP_STATUS,	CATEGORY_GROUP_SKILL2 },	// トレーナー
		{ CATEGORY_GROUP_SKILL2,	CATEGORY_GROUP_MIND,	CATEGORY_GROUP_LIFE,	CATEGORY_GROUP_GREET },		// ひと
		{ CATEGORY_GROUP_STATUS,	CATEGORY_GROUP_NANKAI,	CATEGORY_GROUP_PERSON,	CATEGORY_GROUP_LIFE },		// あいさつ
		{ CATEGORY_GROUP_TRAINER,	CATEGORY_GROUP_UNION,	CATEGORY_GROUP_GREET,	CATEGORY_GROUP_PERSON },	// せいかつ
		{ CATEGORY_GROUP_PERSON,	CATEGORY_POS_BACK,		CATEGORY_GROUP_UNION,	CATEGORY_GROUP_NANKAI },	// きもち
		{ CATEGORY_GROUP_GREET,		CATEGORY_POS_BACK,		CATEGORY_GROUP_MIND,	CATEGORY_GROUP_UNION },		// なんかいことば
		{ CATEGORY_GROUP_LIFE,		CATEGORY_POS_BACK,		CATEGORY_GROUP_NANKAI,	CATEGORY_GROUP_MIND },		// ユニオン
		{ CATEGORY_GROUP_MIND,		CATEGORY_GROUP_POKEMON,	CATEGORY_POS_BACK,		CATEGORY_POS_BACK },		// もどる
	};

	u32  pos = wk->category_pos;
	if( pos == CATEGORY_POS_BACK )
	{
		// テーブルを引くように
		pos = CATEGORY_GROUP_MAX;
	}

	if( wk->category_pos != CATEGORY_POS_BACK )
	{
		wk->category_pos_prv = wk->category_pos;

		if( wk->key_repeat & PAD_KEY_UP )
		{
			wk->category_pos = next_pos_tbl[ pos ].up_pos;
			return TRUE;
		}
		if( wk->key_repeat & PAD_KEY_DOWN )
		{
			wk->category_pos = next_pos_tbl[ pos ].down_pos;
			return TRUE;
		}
		if( wk->key_repeat & PAD_KEY_LEFT )
		{
			wk->category_pos = next_pos_tbl[ pos ].left_pos;
			return TRUE;
		}
		if( wk->key_repeat & PAD_KEY_RIGHT )
		{
			wk->category_pos = next_pos_tbl[ pos ].right_pos;
			return TRUE;
		}
	}
	else
	{
		if( wk->key_repeat & (PAD_KEY_UP) )
		{
			wk->category_pos = next_pos_tbl[CATEGORY_GROUP_MAX].up_pos + (wk->category_pos_prv % 3);
			return TRUE;
		}

		if( wk->key_repeat & (PAD_KEY_DOWN) )
		{
			wk->category_pos = next_pos_tbl[CATEGORY_GROUP_MAX].down_pos + (wk->category_pos_prv % 3);
			return TRUE;
		}

	}
	return FALSE;
}
//----------------------------------------------
// イニシャルモード
//----------------------------------------------
static BOOL keycheck_category_initial_mode( PMS_INPUT_WORK* wk )
{
	if( wk->category_pos != CATEGORY_POS_BACK )
	{
		int  next_pos = CATEGORY_POS_DISABLE;

		do
		{
			if( wk->key_repeat & PAD_KEY_UP )
			{
				next_pos = PMSI_INITIAL_DAT_GetUpCode( wk->category_pos );
				break;
			}
			if( wk->key_repeat & PAD_KEY_DOWN )
			{
				next_pos = PMSI_INITIAL_DAT_GetDownCode( wk->category_pos );
				break;
			}
			if( wk->key_repeat & PAD_KEY_RIGHT )
			{
				next_pos = PMSI_INITIAL_DAT_GetRightCode( wk->category_pos );
				break;
			}
			if( wk->key_repeat & PAD_KEY_LEFT )
			{
				next_pos = PMSI_INITIAL_DAT_GetLeftCode( wk->category_pos );
				break;
			}

		}while(0);

		if( next_pos != CATEGORY_POS_DISABLE )
		{
			wk->category_pos_prv = wk->category_pos;
			wk->category_pos = next_pos;
			return TRUE;
		}
	}
	else
	{
		if( wk->key_repeat & PAD_KEY_UP )
		{
			wk->category_pos = PMSI_INITIAL_DAT_GetColBottomCode( wk->category_pos_prv );
			return TRUE;
		}
		if( wk->key_repeat & PAD_KEY_DOWN )
		{
			wk->category_pos = PMSI_INITIAL_DAT_GetColTopCode( wk->category_pos_prv );
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * 単語ウィンドウパラメータ初期化
 *
 * @param   word_win		
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_wordwin_params( WORDWIN_WORK* word_win, PMS_INPUT_WORK* wk )
{
	word_win->line = 0;
	word_win->cursor_x = 0;
	word_win->cursor_y = 0;
	word_win->word_max = PMSI_GetCategoryWordMax(wk);
	word_win->scroll_lines = 0;

	if( word_win->word_max > WORDWIN_DISP_MAX )
	{
		word_win->line_max = ((word_win->word_max - WORDWIN_DISP_MAX) / 2) + (word_win->word_max & 1);
	}
	else
	{
		word_win->line_max = 0;
	}

}

static u32 get_wordwin_cursorpos( const WORDWIN_WORK* wordwin )
{
	return (wordwin->cursor_y * 2) + wordwin->cursor_x;
}
static u32 get_wordwin_pos( const WORDWIN_WORK* wordwin )
{
	return (wordwin->line * 2) + get_wordwin_cursorpos( wordwin );
}
static int get_wordwin_scroll_vector( const WORDWIN_WORK* wordwin )
{
	return wordwin->scroll_lines;
}
static int get_wordwin_linepos( const WORDWIN_WORK* wordwin )
{
	return wordwin->line;
}
static int get_wordwin_linemax( const WORDWIN_WORK* wordwin )
{
	return wordwin->line_max;
}


//----------------------------------------------------------------------------------------------
/**
 * メインプロセス：単語選択
 *
 * @param   wk
 * @param   seq		
 *
 */
//----------------------------------------------------------------------------------------------
static PROC_RESULT MainProc_WordWin( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_SCROLL_WAIT,
		SEQ_SCROLL_WAIT_AND_CURSOR_MOVE,
		SEQ_CHANGE_NEXTPROC,
	};

	switch(*seq ) {
	case SEQ_KEYWAIT:

		if(	(wk->touch_button == TOUCH_BUTTON_GROUP) && (wk->category_mode != CATEGORY_MODE_GROUP)
		||	(wk->touch_button == TOUCH_BUTTON_INITIAL) && (wk->category_mode !=CATEGORY_MODE_INITIAL)
		||	(wk->key_trg & PAD_BUTTON_SELECT)
		){
			Snd_SePlay(SOUND_CHANGE_CATEGORY);
			wk->category_pos = 0;
			wk->category_mode ^= 1;
			PMSIView_SetCommand( wk->vwk, VCMD_WORDWIN_TO_CATEGORY );
			wk->next_proc = MainProc_Category;
			*seq = SEQ_CHANGE_NEXTPROC;
			break;
		}

		{
			int result;

			if( wk->touch_button == TOUCH_BUTTON_UP )
			{
				result = check_wordwin_scroll_up( &(wk->word_win) );
			}
			else if( wk->touch_button == TOUCH_BUTTON_DOWN )
			{
				result = check_wordwin_scroll_down( &(wk->word_win) );
			}
			else
			{
				result = check_wordwin_key( &(wk->word_win), wk->key_repeat );
			}

			switch( result ){
			case WORDWIN_RESULT_CURSOR_MOVE:
				Snd_SePlay(SOUND_MOVE_CURSOR);
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_WORDWIN_CURSOR );
				return PROC_RES_CONTINUE;

			case WORDWIN_RESULT_SCROLL:
				Snd_SePlay(SOUND_MOVE_CURSOR);
				PMSIView_SetCommand( wk->vwk, VCMD_SCROLL_WORDWIN );
				(*seq) = SEQ_SCROLL_WAIT;
				return PROC_RES_CONTINUE;

			case WORDWIN_RESULT_SCROLL_AND_CURSOR_MOVE:
				Snd_SePlay(SOUND_MOVE_CURSOR);
				PMSIView_SetCommand( wk->vwk, VCMD_SCROLL_WORDWIN );
				(*seq) = SEQ_SCROLL_WAIT_AND_CURSOR_MOVE;
				return PROC_RES_CONTINUE;
			}
		}

		if( wk->key_trg & PAD_BUTTON_B )
		{
			Snd_SePlay(SOUND_CANCEL);

			PMSIView_SetCommand( wk->vwk, VCMD_WORDWIN_TO_CATEGORY );
			wk->next_proc = MainProc_Category;
			*seq = SEQ_CHANGE_NEXTPROC;
			break;
		}
		if( wk->key_trg & PAD_BUTTON_A )
		{
			Snd_SePlay(SOUND_DECIDE);

			set_select_word( wk );
			wk->next_proc = MainProc_EditArea;
			PMSIView_SetCommand( wk->vwk, VCMD_WORDTIN_TO_EDITAREA );
			(*seq) = SEQ_CHANGE_NEXTPROC;
			break;
		}
		break;

	case SEQ_SCROLL_WAIT:
		if( PMSIView_WaitCommand( wk->vwk, VCMD_SCROLL_WORDWIN ) )
		{
			(*seq) = SEQ_KEYWAIT;
		}
		break;

	case SEQ_SCROLL_WAIT_AND_CURSOR_MOVE:
		if( PMSIView_WaitCommand( wk->vwk, VCMD_SCROLL_WORDWIN ) )
		{
			PMSIView_SetCommand( wk->vwk, VCMD_MOVE_WORDWIN_CURSOR );
			(*seq) = SEQ_KEYWAIT;
		}
		break;

	case SEQ_CHANGE_NEXTPROC:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			ChangeMainProc(wk, wk->next_proc );
			(*seq) = SEQ_KEYWAIT;
		}
		break;
	}


	return PROC_RES_CONTINUE;
}

static int check_wordwin_key( WORDWIN_WORK* wordwin, u16 key )
{
	if( key & PAD_KEY_DOWN )
	{
		if( wordwin->cursor_y < WORDWIN_CURSOR_Y_MAX )
		{
			u32  pos;

			wordwin->cursor_y++;
			pos = get_wordwin_pos( wordwin );

			if( pos < wordwin->word_max )
			{
				return WORDWIN_RESULT_CURSOR_MOVE;
			}
			if( pos == wordwin->word_max )
			{
				if( pos & 1 )
				{
					wordwin->cursor_x = 0;
					return WORDWIN_RESULT_CURSOR_MOVE;
				}
			}
			wordwin->cursor_y--;
			return WORDWIN_RESULT_INVALID;
		}
		else if( wordwin->line < wordwin->line_max )
		{
			wordwin->scroll_lines = 1;
			wordwin->line++;
			
			if( get_wordwin_pos( wordwin ) < wordwin->word_max )
			{
				return WORDWIN_RESULT_SCROLL;
			}
			else
			{
				wordwin->cursor_x = 0;
				return WORDWIN_RESULT_SCROLL_AND_CURSOR_MOVE;
			}
		}
		return WORDWIN_RESULT_INVALID;
	}

	if( key & PAD_KEY_UP )
	{
		if( wordwin->cursor_y )
		{
			wordwin->cursor_y--;
			return WORDWIN_RESULT_CURSOR_MOVE;
		}
		else if( wordwin->line )
		{
			wordwin->scroll_lines = -1;
			wordwin->line--;
			return WORDWIN_RESULT_SCROLL;
		}
		return WORDWIN_RESULT_INVALID;
	}

	if( key & (PAD_KEY_LEFT | PAD_KEY_RIGHT ) )
	{
		wordwin->cursor_x ^= 1;
		if( get_wordwin_pos( wordwin ) < wordwin->word_max )
		{
			return WORDWIN_RESULT_CURSOR_MOVE;
		}
		wordwin->cursor_x ^= 1;
		return WORDWIN_RESULT_INVALID;
	}

	if( key & PAD_BUTTON_L )
	{
		return check_wordwin_scroll_up( wordwin );
	}

	if( key & PAD_BUTTON_R )
	{
		return check_wordwin_scroll_down( wordwin );
	}


	return WORDWIN_RESULT_NONE;
}
static int check_wordwin_scroll_up( WORDWIN_WORK* wordwin )
{
	
	if( wordwin->line )
	{
		if( wordwin->line >= WORDWIN_PAGE_LINES )
		{
			wordwin->line -= WORDWIN_PAGE_LINES;
			wordwin->scroll_lines = -WORDWIN_PAGE_LINES;
		}
		else
		{
			wordwin->scroll_lines = -(wordwin->line);
			wordwin->line = 0;
		}
		return WORDWIN_RESULT_SCROLL;
	}
	return WORDWIN_RESULT_INVALID;
}

static int check_wordwin_scroll_down( WORDWIN_WORK* wordwin )
{
	if( wordwin->line < wordwin->line_max )
	{
		if( (wordwin->line + WORDWIN_PAGE_LINES) <= wordwin->line_max )
		{
			wordwin->scroll_lines = WORDWIN_PAGE_LINES;
			wordwin->line += WORDWIN_PAGE_LINES;
		}
		else
		{
			wordwin->scroll_lines = wordwin->line_max - wordwin->line;
			wordwin->line = wordwin->line_max;
		}

		if( get_wordwin_pos( wordwin ) < wordwin->word_max )
		{
			return WORDWIN_RESULT_SCROLL;
		}
		else
		{
			wordwin->cursor_x = 0;
			return WORDWIN_RESULT_SCROLL_AND_CURSOR_MOVE;
		}


	}
	return WORDWIN_RESULT_INVALID;
}


//------------------------------------------------------------------
/**
 * 選択された単語をデータに反映する
 *
 * @param   wk		
 *
 * @retval  BOOL	入力できる欄を全て埋めたらTRUEが返る
 */
//------------------------------------------------------------------
static BOOL set_select_word( PMS_INPUT_WORK* wk )
{
	u32  word_idx;
	PMS_WORD  word;

	word_idx = get_wordwin_pos( &wk->word_win );
	if( wk->category_mode == CATEGORY_MODE_GROUP )
	{
		word = PMSI_DATA_GetGroupEnableWordCode( wk->dwk, wk->category_pos, word_idx );
	}
	else
	{
		word = PMSI_DATA_GetInitialEnableWordCode( wk->dwk, wk->category_pos, word_idx );
	}

	switch( wk->input_mode ){
	case PMSI_MODE_SINGLE:
		wk->edit_word[0] = word;
		break;

	case PMSI_MODE_DOUBLE:
		wk->edit_word[ wk->edit_pos ] = word;
		break;

	case PMSI_MODE_SENTENCE:
		PMSDAT_SetWord( &wk->edit_pms, wk->edit_pos, word );
		break;
	}

	return check_input_complete( wk );
}

//----------------------------------------------------------------------------------------------
/**
 * メインプロセス：フェードアウト～終了
 *
 * @param   wk
 * @param   seq		
 *
 */
//----------------------------------------------------------------------------------------------
static PROC_RESULT MainProc_Quit( PMS_INPUT_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		PMSIView_SetCommand( wk->vwk, VCMD_QUIT );
		(*seq)++;
		break;

	case 1:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			return PROC_RES_FINISH;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}








//------------------------------------------------------------------
/**
 * サブプロセススタート（メイン・サブ両方から呼んで良い）
 *
 * @param   wk		
 * @param   sub_proc
 *
 */
//------------------------------------------------------------------
static void SetSubProc( PMS_INPUT_WORK* wk, SubProc sub_proc )
{
	wk->sub_proc = sub_proc;
	wk->sub_seq = 0;
}

//------------------------------------------------------------------
/**
 * サブプロセス終了（実行中のサブプロセスからのみ呼び出す）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void QuitSubProc( PMS_INPUT_WORK* wk )
{
	wk->sub_proc = NULL;
}




//------------------------------------------------------------------
/**
 * サブプロセス：フェードイン
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubProc_FadeIn( PMS_INPUT_WORK* wk, int* seq )
{
	switch(*seq){
	case 0:
		PMSIView_SetCommand( wk->vwk, VCMD_FADEIN );
		(*seq)++;
		break;
	case 1:
		if(PMSIView_WaitCommandAll( wk->vwk ))
		{
			QuitSubProc( wk );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブプロセス：「けってい」コマンド
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubProc_CommandOK( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_INIT,
		SEQ_MENU_CTRL,
		SEQ_WAIT_ANYKEY,
		SEQ_RETURN,
	};

	switch(*seq){
	case SEQ_INIT:
		if( CheckModified( wk ) || PMSI_PARAM_GetNotEditEgnoreFlag(wk->input_param) )
		{
			if( check_input_complete( wk ) )
			{
				InitMenuState( &wk->menu, MENU_RESULT_POS_MAX, MENU_RESULT_POS_YES );
				PMSIView_SetCommand( wk->vwk, VCMD_DISP_MESSAGE_OK );
				(*seq) = SEQ_MENU_CTRL;
			}
			else
			{
				PMSIView_SetCommand( wk->vwk, VCMD_DISP_MESSAGE_WARN );
				(*seq) = SEQ_WAIT_ANYKEY;
			}
		}
		else
		{
			SetSubProc( wk, SubProc_CommandCancel );
		}
		break;

	case SEQ_MENU_CTRL:
		if( PMSIView_WaitCommand(wk->vwk, VCMD_MOVE_MENU_CURSOR) )
		{
			switch( CtrlMenuState(&(wk->menu), wk->key_trg) ){
			case MENU_RESULT_MOVE:
				Snd_SePlay(SOUND_MOVE_CURSOR);

				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_MENU_CURSOR );
				break;

			case MENU_RESULT_POS_NO:
			case MENU_RESULT_CANCEL:
				Snd_SePlay(SOUND_CANCEL);

				PMSIView_SetCommand( wk->vwk, VCMD_ERASE_MENU );
				(*seq) = SEQ_RETURN;
				break;

			case MENU_RESULT_POS_YES:
				Snd_SePlay(SOUND_DECIDE);
				if( wk->input_mode == PMSI_MODE_SENTENCE )
				{
					PMSDAT_ClearUnnecessaryWord( &(wk->edit_pms) );
				}
				PMSI_PARAM_WriteBackData( wk->input_param, wk->edit_word, &wk->edit_pms );
				ChangeMainProc( wk, MainProc_Quit );
				(*seq) = SEQ_RETURN;
				break;
			}
		}
		break;

	case SEQ_WAIT_ANYKEY:
		if( wk->key_trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_PLUS_KEY_MASK) )
		{
			PMSIView_SetCommand( wk->vwk, VCMD_DISP_MESSAGE_DEFAULT );
			(*seq) = SEQ_RETURN;
		}
		break;

	case SEQ_RETURN:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			QuitSubProc( wk );
		}
		break;
	}
}
//--------------------------------------------------------------------------------------
/**
 * サブプロセス：「やめる」コマンド
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//--------------------------------------------------------------------------------------
static void SubProc_CommandCancel( PMS_INPUT_WORK* wk, int* seq )
{
	enum {
		SEQ_INIT,
		SEQ_MENU_CTRL,
		SEQ_RETURN,
	};

	switch(*seq){
	case SEQ_INIT:
		InitMenuState( &wk->menu, MENU_RESULT_POS_MAX, MENU_RESULT_POS_NO );
		PMSIView_SetCommand( wk->vwk, VCMD_DISP_MESSAGE_CANCEL );
		(*seq) = SEQ_MENU_CTRL;
		break;

	case SEQ_MENU_CTRL:
		if( PMSIView_WaitCommand(wk->vwk, VCMD_MOVE_MENU_CURSOR) )
		{
			switch( CtrlMenuState(&(wk->menu), wk->key_trg) ){
			case MENU_RESULT_MOVE:
				Snd_SePlay(SOUND_MOVE_CURSOR);
				PMSIView_SetCommand( wk->vwk, VCMD_MOVE_MENU_CURSOR );
				break;

			case MENU_RESULT_POS_NO:
			case MENU_RESULT_CANCEL:
				Snd_SePlay(SOUND_CANCEL);

				PMSIView_SetCommand( wk->vwk, VCMD_ERASE_MENU );
				(*seq) = SEQ_RETURN;
				break;

			case MENU_RESULT_POS_YES:
				Snd_SePlay(SOUND_DECIDE);

				ChangeMainProc( wk, MainProc_Quit );
				(*seq) = SEQ_RETURN;
				break;
			}
		}
		break;

	case SEQ_RETURN:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			QuitSubProc( wk );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * 入力欄が初期状態と比べて変更されているかチェック
 *
 * @param   wk			
 *
 * @retval  BOOL		更新されていたらTRUEを返す
 */
//------------------------------------------------------------------
static BOOL CheckModified( PMS_INPUT_WORK* wk )
{
	return (PMSI_PARAM_CheckModifiedByEditDatas( wk->input_param, wk->edit_word, &wk->edit_pms ) == FALSE);
}

static BOOL check_input_complete( PMS_INPUT_WORK* wk )
{
	switch( wk->input_mode ){
	case PMSI_MODE_SINGLE:
		return (wk->edit_word[0] != PMS_WORD_NULL);

	case PMSI_MODE_DOUBLE:
		return ( (wk->edit_word[0] != PMS_WORD_NULL) && (wk->edit_word[1] != PMS_WORD_NULL) );

	case PMSI_MODE_SENTENCE:
		return PMSDAT_IsComplete( &wk->edit_pms );
	}

	return FALSE;
}


//------------------------------------------------------------------
/**
 * メニューコントロール初期化
 *
 * @param   menu		
 * @param   max		
 * @param   pos		
 *
 */
//------------------------------------------------------------------
static void InitMenuState( MENU_WORK* menu, int max, int pos )
{
	menu->pos = pos;
	menu->max = max;
}

//------------------------------------------------------------------
/**
 * メニューコントロール更新
 *
 * @param   menu		
 * @param   key		
 *
 * @retval  MENU_RESULT		
 */
//------------------------------------------------------------------
static MENU_RESULT  CtrlMenuState( MENU_WORK* menu , u16 key )
{
	if( key & PAD_KEY_UP )
	{
		if( menu->pos == 0 )
		{
			return MENU_RESULT_DISABLE_KEY;
		}
		else
		{
			menu->pos--;
			return MENU_RESULT_MOVE;
		}
	}
	if( key & PAD_KEY_DOWN )
	{
		if( menu->pos == menu->max )
		{
			return MENU_RESULT_DISABLE_KEY;
		}
		else
		{
			menu->pos++;
			return MENU_RESULT_MOVE;
		}
	}
	if( key & PAD_BUTTON_A )
	{
		return menu->pos;
	}
	if( key & PAD_BUTTON_B )
	{
		return MENU_RESULT_CANCEL;
	}
	return MENU_RESULT_NONE;
}

static u32 get_menu_cursor_pos( const MENU_WORK* menu )
{
	return menu->pos;
}

//--------------------------------------------------------------------------------------
/**
 * サブプロセス： カテゴリモード変更（編集・ボタン操作時のみ）
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//--------------------------------------------------------------------------------------
static void SubProc_ChangeCategoryMode( PMS_INPUT_WORK* wk, int* seq )
{
	switch(*seq ){

	case 0:
		Snd_SePlay(SOUND_CHANGE_CATEGORY);
		wk->category_mode ^= 1;
		PMSIView_SetCommand( wk->vwk, VCMD_CHANGE_CATEGORY_MODE_DISABLE );
		(*seq) = 1;
		break;

	case 1:
		if( PMSIView_WaitCommandAll( wk->vwk ) )
		{
			QuitSubProc( wk );
		}
		break;

	}
}


//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * 入力モード取得
 *
 * @param   wk		ワークポインタ
 *
 * @retval  u32		入力モード（enum PMSI_MODE)
 */
//------------------------------------------------------------------
u32 PMSI_GetInputMode( const PMS_INPUT_WORK* wk )
{
	return wk->input_mode;
}

//------------------------------------------------------------------
/**
 * 説明文字列タイプ取得
 *
 * @param   wk		ワークポインタ
 *
 * @retval  u32		説明文字列タイプ（enum PMSI_GUIDANCE)
 */
//------------------------------------------------------------------
u32 PMSI_GetGuidanceType( const PMS_INPUT_WORK* wk )
{
	return PMSI_PARAM_GetGuidanceType( wk->input_param );
}

//------------------------------------------------------------------
/**
 * カテゴリモード取得
 *
 * @param   wk		ワークポインタ
 *
 * @retval  u32		カテゴリモード
 */
//------------------------------------------------------------------
u32 PMSI_GetCategoryMode( const PMS_INPUT_WORK* wk )
{
	return wk->category_mode;
}

//------------------------------------------------------------------
/**
 * 表示中の文章タイプを取得
 *
 * @param   wk		ワークポインタ
 *
 * @retval  u32		文章タイプ（enum PMS_TYPE）
 */
//------------------------------------------------------------------
u32 PMSI_GetSentenceType( const PMS_INPUT_WORK* wk )
{
	return PMSDAT_GetSentenceType( &wk->edit_pms );
}

//------------------------------------------------------------------
/**
 * 編集中の単語ナンバーを返す
 *
 * @param   wk			ワークポインタ
 * @param   pos			何番目の単語？
 *
 * @retval  PMS_WORD	簡易会話単語ナンバー
 */
//------------------------------------------------------------------
PMS_WORD  PMSI_GetEditWord( const PMS_INPUT_WORK* wk, int pos )
{
	if( wk->input_mode == PMSI_MODE_SENTENCE )
	{
		return PMSDAT_GetWordNumber( &wk->edit_pms, pos );
	}
	else
	{
		return wk->edit_word[ pos ];
	}
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk			
 * @param   heapID		
 *
 * @retval  STRBUF*		
 */
//------------------------------------------------------------------
STRBUF* PMSI_GetEditSourceString( const PMS_INPUT_WORK* wk, u32 heapID )
{
	return PMSDAT_GetSourceString( &(wk->edit_pms), heapID );
}

//------------------------------------------------------------------
/**
 * 編集エリアのカーソル位置を返す
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_GetEditAreaCursorPos( const PMS_INPUT_WORK* wk )
{
	return wk->edit_pos;
}

//------------------------------------------------------------------
/**
 * ボタンカーソル位置取得
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_GetButtonCursorPos( const PMS_INPUT_WORK* wk )
{
	return wk->cmd_button_pos;
}

//------------------------------------------------------------------
/**
 * カテゴリカーソル位置取得
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_GetCategoryCursorPos( const PMS_INPUT_WORK* wk )
{
	return wk->category_pos;
}



//------------------------------------------------------------------
/**
 * カテゴリ内の有効単語総数を返す
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_GetCategoryWordMax( const PMS_INPUT_WORK* wk )
{
	if( wk->category_mode == CATEGORY_MODE_GROUP )
	{
		return PMSI_DATA_GetGroupEnableWordCount( wk->dwk, wk->category_pos );
	}
	else
	{
		return PMSI_DATA_GetInitialEnableWordCount( wk->dwk, wk->category_pos );
	}
}

//------------------------------------------------------------------
/**
 * カテゴリ内の有効単語の内、指定インデックスの単語をバッファにコピーする
 *
 * @param   wk		
 * @param   word_num		
 * @param   buf		
 *
 */
//------------------------------------------------------------------
void PMSI_GetCategoryWord( const PMS_INPUT_WORK* wk, u32 word_num, STRBUF* buf )
{
	if( wk->category_mode == CATEGORY_MODE_GROUP )
	{
		PMSI_DATA_GetGroupEnableWord( wk->dwk, wk->category_pos, word_num, buf );
	}
	else
	{
		PMSI_DATA_GetInitialEnableWord( wk->dwk, wk->category_pos, word_num, buf );
	}
}

u32 PMSI_GetWordWinCursorPos( const PMS_INPUT_WORK* wk )
{
	return get_wordwin_cursorpos( &(wk->word_win) );
}

int PMSI_GetWordWinScrollVector( const PMS_INPUT_WORK* wk )
{
	return get_wordwin_scroll_vector( &(wk->word_win) );
}
BOOL PMSI_GetWordWinUpArrowVisibleFlag( const PMS_INPUT_WORK* wk )
{
	return (get_wordwin_linepos(&(wk->word_win)) != 0);
}
BOOL PMSI_GetWordWinDownArrowVisibleFlag( const PMS_INPUT_WORK* wk )
{
	int  line, line_max;

	line = get_wordwin_linepos(&(wk->word_win));
	line_max = get_wordwin_linemax(&(wk->word_win));

	return ( line < line_max );
}

int PMSI_GetTalkWindowType( const PMS_INPUT_WORK* wk )
{
	return PMSI_PARAM_GetWindowType( wk->input_param );
}

//------------------------------------------------------------------
/**
 * メニューカーソルの位置を返す
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSI_GetMenuCursorPos( const PMS_INPUT_WORK* wk )
{
	return get_menu_cursor_pos( &wk->menu );
}
