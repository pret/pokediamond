//============================================================================================
/**
 * @file	box.c
 * @brief	ボックス操作画面　メイン
 * @author	taya
 * @date	2005.09.05
 */
//============================================================================================
#include "common.h"
#include "gflib\button_man.h"
#include "system\procsys.h"
#include "system\wordset.h"
#include "system\savedata.h"
#include "application\namein.h"
#include "application\p_status.h"
#include "application\bag.h"
#include "itemtool\myitem.h"
#include "application\box.h"
#include "poketool\poke_tool.h"
#include "poketool\boxdata.h"
#include "poketool\pokeparty.h"
#include "poketool\poke_number.h"
#include "src\system\pm_overlay.h"
#include "savedata\config.h"
#include "savedata\perapvoice.h"
#include "savedata\sp_ribbon.h"
#include "poketool\monsno.h"
#include "poketool\poke_number.h"
#include "battle\wazano_def.h"

#include "system\msgdata.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_boxmenu.h"
#include "msgdata\msg_chr.h"

#include  "box_common.h"
#include  "boxmenu.h"
#include  "box_reel.h"

//==============================================================
// 定数
//==============================================================
enum {
	HEAPSIZE_SYS = 0x4000,
	HEAPSIZE_VIEW = 0x3c000,

	SELECT_TRAY_CANCEL = -1,
};

enum {
	BUTTONID_LEFT,
	BUTTONID_RIGHT,
	BUTTONID_PAGE,


	BUTTONID_NONE = 0xffff,
};

enum {
	AREASELECT_RESULT_NONE,		///< 範囲選択中カーソル動作：なにもなし
	AREASELECT_RESULT_UPDATE,	///< 範囲選択中カーソル動作：位置更新
	AREASELECT_RESULT_OVER,		///< 範囲選択中カーソル動作：移動できない方向へのキー操作
	AREASELECT_RESULT_SCROLL_LEFT,		///< 範囲選択中カーソル動作：トレイ左スクロール
	AREASELECT_RESULT_SCROLL_RIGHT,		///< 範囲選択中カーソル動作：トレイ右スクロール
};


/// サブ画面操作を抜けるキー
#define SUBLCD_CTRL_ESCAPE_KEYMASK	(PAD_PLUS_KEY_MASK|PAD_BUTTON_A|PAD_BUTTON_B)

static const TP_HIT_TBL ButtonHitTbl[] = {
	{ TP_USE_CIRCLE,   0, 184, 40 },
	{ TP_USE_CIRCLE, 255, 184, 40 },
	{ TP_HIT_END,0,0,0},
};

static const TP_HIT_TBL CompareButtonHitTbl[] = {
	{ TP_USE_CIRCLE,   0, 184, 40 },
	{ TP_USE_CIRCLE, 255, 184, 40 },
	{ TP_USE_CIRCLE, 128, 178, 12 },
	{ TP_HIT_END,0,0,0},
};


static const TP_HIT_TBL IconHitTbl[] = {
	{ TP_USE_CIRCLE, 256 -104, 168, 16 },
	{ TP_USE_CIRCLE, 256 - 93, 134, 16 },
	{ TP_USE_CIRCLE, 256 - 72, 104, 16 },
	{ TP_USE_CIRCLE, 256 - 40,  84, 16 },
	{ TP_USE_CIRCLE, 256 - 16,  52, 16 },
	{ TP_USE_CIRCLE, 256 - 16,  16, 16 },
	{ TP_HIT_END,0,0,0},
};

//-----------------------------------------------
/**
 *	逃がす時にチェックするワザナンバー
 */
//-----------------------------------------------
static const u16 NigasuCheckWazaTable[] = {
	WAZANO_NAMINORI,
	WAZANO_ROKKUKURAIMU,
	WAZANO_TAKINOBORI,
};

#define NIGASU_CHECKWAZA_MAX		(NELEMS(NigasuCheckWazaTable))

//==============================================================
// Sub Work
//==============================================================
typedef struct {
	u32  seq;			///< シーケンスナンバー
	u8   continue_flag;	///< ウィンドウは開いた状態でキー処理から続けるフラグ
	s8   trayNumber;	///< 初期表示指定＆選択結果格納
	u16  msgID;			///< 選択時に表示するメッセージID
}SELECT_TRAY_WORK;

//------------------------------------------------
/*
 * 	逃がす時の技チェック用ワーク
 */
//------------------------------------------------
typedef struct {
	u8   done;		///< チェック完了した
	u8   ok;		///< 逃がすことが出来る

	u8   tray;
	u8   pos;

	u8   target_waza_flag[ NIGASU_CHECKWAZA_MAX ];
	u16  count[ NIGASU_CHECKWAZA_MAX ];

	POKEMON_PASO_PARAM* targetPoke;
	BOX_DATA*	boxData;
	POKEPARTY*	partyData;
	BOOL        pokeCatchFlag;

}RELEASE_WAZACHECK_WORK;

//==============================================================
// Main Work
//==============================================================
typedef struct _BOXAPP_WORK{
	BOXAPP_VPARAM		vpara;
	BOXAPP_VIEW_WORK*	vwk;
	BOX_PROC_PARAM*		procParam;
	SAVEDATA*			saveData;
	BOX_DATA*			boxData;
	POKEPARTY*			partyData;
	NAMEIN_PARAM*		nameinParam;
	PSTATUS_DATA		statusParam;
	RELEASE_WAZACHECK_WORK	wazaCheckWork;

	BUTTON_MAN*			bmn;
	BUTTON_MAN*         icon_bmn;
	u32					btn_id;
	u32					touch_icon_id;

	MSGDATA_MANAGER*	msgman_box;
	MSGDATA_MANAGER*	msgman_poke;
	MSGDATA_MANAGER*	msgman_poke_character;
	MSGDATA_MANAGER*	msgman_speabi;
	WORDSET*			wordset;
	POKEMON_PARAM*		partyPokeWork;
	CONFIG*				sysConfig;

	PROC_RESULT (*mainSeqFunc)( struct _BOXAPP_WORK* );
	void (*subSeqFunc)( struct _BOXAPP_WORK*, u32* seq );

	u32			seq;
	u32			subseq;
	s32			work;

	SELECT_TRAY_WORK		selectTrayWork;
	u32						azukeruTrayNumber;

	BOX_REEL_CTRL			reel;
	int						reel_pos;
	u32						reel_timer;
	BOOL					reel_move_flag;
	BOOL					reel_release_flag;
	int						reel_prev_slide;

	PROC*		subProc;
	void*		subProcWork;

	u32 itemno;
}BOXAPP_WORK;

typedef  PROC_RESULT (*seqFunc)( BOXAPP_WORK* );
typedef  void (*SubSeqFunc)( BOXAPP_WORK*, u32* );

//==============================================================
// Prototype
//==============================================================
static void MainSeqChange( BOXAPP_WORK* wk, seqFunc nextSeqFunc );
static void SubSeqSet( BOXAPP_WORK* wk, SubSeqFunc subseq );
static void SubSeqEnd( BOXAPP_WORK* wk );
static seqFunc GetNextMainSeqAdrsByCursorArea( BOXAPP_WORK* wk );
static void SetBoxModifiedFlag( BOXAPP_WORK* wk );
static void SubSeq_StartBox( BOXAPP_WORK* wk,  u32* seq );
static void SubSeq_RestartBox( BOXAPP_WORK* wk,  u32* seq );
static PROC_RESULT BoxMainSeq_Open( BOXAPP_WORK* wk );
static inline int MainSeq_ButtonCheckProc( BOXAPP_WORK* wk );
static PROC_RESULT BoxMainSeq_Tray( BOXAPP_WORK* wk );
static BOOL CheckStatusPokeUnleavable( BOXAPP_WORK* wk, int* msgID );
static PROC_RESULT BoxMainSeq_Party( BOXAPP_WORK* wk );
static PROC_RESULT BoxMainSeq_TrayTab( BOXAPP_WORK* wk );
static PROC_RESULT BoxMainSeq_ExitButton( BOXAPP_WORK* wk );
static PROC_RESULT BoxMainSeq_PartyButton( BOXAPP_WORK* wk );
static void SetPokemonStatusScheneParam( BOXAPP_WORK* wk );
static PROC_RESULT BoxMainSeq_Close( BOXAPP_WORK* wk );
static void  SubSeq_ExitButton( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_B_Exit( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_Pokemon( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_Item( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_Tray( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_Jump( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_WallPaper( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Menu_Marking( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_AreaSelect( BOXAPP_WORK* wk, u32* seq );
static BOOL Check_AreaSelectPokePut( const BOXAPP_VPARAM* vpara );
static void SubSeq_OP_Tukamu( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_OP_Oku( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_OP_Irekaeru( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_OP_Tureteiku( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_OP_Azukeru( BOXAPP_WORK* wk, u32* seq );
static BOOL CheckPointLastPartyPoke( BOXAPP_WORK* wk );
static BOOL CheckReleasable( BOXAPP_WORK* wk, int* msgID );
static void SubSeq_OP_Nigasu( BOXAPP_WORK* wk, u32* seq );
static void StartReleaseWazaCheck( BOXAPP_WORK* mainWk );
static void ReleaseWazaCheckTask( TCB_PTR tcb, void* wk_adrs );
static BOOL PokeHaveWaza( POKEMON_PASO_PARAM* ppp, u16 waza );
static void SubSeq_Connect_InputTrayName( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_Connect_PokemonStatus( BOXAPP_WORK* wk, u32* seq );
static void UpdateCursorPosByStatusScene( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk );
static void SubSeq_Connect_Bag( BOXAPP_WORK* wk, u32 *seq );
static void SubSeq_Restore_Item( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_ItemMode_Restore( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_ItemInfo( BOXAPP_WORK* wk, u32* seq );
static void SelectTrayCtrl_Init( BOXAPP_WORK* wk, u32 init_tray_num, u32 msg_id );
static void SelectTrayCtrl_Continue( BOXAPP_WORK* wk );
static BOOL SelectTrayCtrl_Main( BOXAPP_WORK* wk );
static int calc_reelmove_vector( int* next, int now, u32 max );
static void SubSeq_ChangeTray( BOXAPP_WORK* wk, u32* seq );
static void SubSeq_TrayMode( BOXAPP_WORK* wk,  u32* seq );
static void SubSeq_LimitMode( BOXAPP_WORK* wk,  u32* seq );
static BOOL CheckLimitModeIconTouch( BOXAPP_WORK* wk );
static void IconBmnCallBack( u32 btnID, u32 event, void* wk_adrs );
static void InitWork( BOXAPP_WORK* wk, BOX_PROC_PARAM* proc_param );
static void DeleteWork( BOXAPP_WORK* wk );
static void InitWork_system( BOXAPP_SYSTEM* system, int mode );
static void InitWork_cursor( BOXAPP_WORK* wk );
static void InitWork_catchpoke( BOXAPP_CATCH_POKE* catchPoke );
static void DeleteWork_catchpoke( BOXAPP_CATCH_POKE* catchPoke );
static void InitWork_tray( BOX_DATA* box, BOXAPP_TRAY* tray );
static void DeleteWork_tray( BOXAPP_TRAY* tray );
static void InitWork_statusPoke( BOXAPP_STATUS_POKE* statusPoke );
static void DeleteWork_statusPoke( BOXAPP_STATUS_POKE* statusPoke );
static void InitWork_Compare( BOXAPP_COMPARE* compare );
static void DeleteWork_Compare( BOXAPP_COMPARE* compare );
static void InitWork_SubLCD( BOXAPP_SUBLCD* sub );
static void SetTrayStatus( const BOX_DATA* box, BOXAPP_TRAY* tray );
static void TrayCurrentWallPaperUpdate( BOXAPP_VPARAM* vpara, BOX_DATA* box );
static BOOL CheckCursorMoveKeyInput( u32 keyflag, BOXAPP_WORK* wk );
static BOOL CursorPosMove( BOXAPP_VPARAM* vpara, int x, int y );
static int CheckCursorMoveKeyInput_AreaSelect( u32 keyflag, BOXAPP_WORK* wk );
static int CursorPosMove_AreaSelect( BOXAPP_VPARAM* vpara, int x, int y );
static void CursorPosSetForPartyBoxButtonOpen( BOXAPP_WORK* wk );
static void CursorPosSetForPartyBoxButtonClose( BOXAPP_WORK* wk );
static void CursorPointPokeUpdate( BOXAPP_WORK* wk );
static BOOL CheckButtonPush( BOXAPP_WORK* wk );
static void BmnCallBack( u32 btnID, u32 event, void* wk_adrs );
static void VParaSet_MessageID( BOXAPP_VPARAM* vpara, u32 msgID );
static void VParaSet_CursorTrayPos( BOXAPP_VPARAM* vpara, u32 x, u32 y );
static void VParaSet_PokeCatch( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_AreaSelectPokeCatch( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_StartAreaSelect( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_UpdateAreaSelect( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_PokePut( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_AreaSelectPokePut( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara );
static void VParaSet_PokeChange( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara);
static BOOL VParaSet_CatchPokeAzuke( BOXAPP_WORK* wk, u32 trayNum );
static BOOL VParaSet_PointPokeAzuke( BOXAPP_WORK* wk, u32 trayNum );
static void VParaSet_CatchPokeNigasu( BOXAPP_WORK* wk );
static void VParaSet_PointPokeNigasu( BOXAPP_WORK* wk );
static void VParaSet_StatusPoke( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk );
static void VParaSet_StatusPoke_Normal( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk );
static void VParaSet_StatusPoke_Compare( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk );
static void VParaSet_SwitchCompareSide( BOXAPP_VPARAM* vpara );
static void VParaSet_ChangeComparePage( BOXAPP_VPARAM* vpara );
static void VParaSet_SetComparePageButtonState( BOXAPP_VPARAM* vpara, BOOL on );
static void VParaSet_StatusPokeData( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp );
static void VParaSet_StatusPokeMark( BOXAPP_VPARAM* vpara );
static void VParaSet_StatusPokeItemNumber( BOXAPP_VPARAM* vpara, u16 itemno, BOXAPP_WORK* wk );
static void VParaSet_CurrentTrayInc( BOXAPP_VPARAM* vpara );
static void VParaSet_CurrentTrayDec( BOXAPP_VPARAM* vpara );
static void VParaSet_CurrentTrayNumberSet( BOXAPP_VPARAM* vpara, u32 number );
static void VParaSet_JumpWin( BOXAPP_VPARAM* vpara, u32 center_trayno );
static void VParaSet_WithDrawItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk );
static void VParaSet_ClearCatchItem( BOXAPP_VPARAM* vpara );
static void VParaSet_SetItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk );
static void VParaSet_SwapItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk );
static void VParaSet_SubLCDStae( BOXAPP_VPARAM* vpara, u32 state );
static void VParaSet_SubLCDPos( BOXAPP_VPARAM* vpara, u32 pos );
static void VParaSet_SubLCDLimitPos( BOXAPP_VPARAM* vpara, u32 pos );
static void VParaSet_SubLCDMove( BOXAPP_VPARAM* vpara, int move );
static void VParaSet_LimitModeBitFlag( BOXAPP_VPARAM* vpara, u32 iconID );
static void VParaSet_ExpertModeChange( BOXAPP_VPARAM* vpara );
static u32 GetStatusPokeParam( BOXAPP_VPARAM* vpara, int paramID, void* buf );
static u32 GetPointPokeParam( BOXAPP_VPARAM* vpara, int paramID, void* buf );


//------------------------------------------------------------------
/**
 * ボックスアプリPROC：Init
 *
 * @param   proc			
 * @param   seq				
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT BoxProc_Init( PROC * proc, int * seq )
{
	BOXAPP_WORK* wk;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BOX_SYSTEM, HEAPSIZE_SYS );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BOX_VIEW, HEAPSIZE_VIEW );

	wk = PROC_AllocWork( proc, sizeof(BOXAPP_WORK), HEAPID_BOX_SYSTEM );

	if( wk != NULL )
	{
		InitWork( wk, PROC_GetParentWork(proc) );
		BoxAppView_Init( &(wk->vwk), &wk->vpara, wk );

		wk->seq = 0;
		wk->mainSeqFunc = GetNextMainSeqAdrsByCursorArea( wk );

		SubSeqSet( wk, SubSeq_StartBox );
	}

	return PROC_RES_FINISH;
}
//------------------------------------------------------------------
/**
 * ボックスアプリPROC：Main
 *
 * @param   proc			
 * @param   seq				
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT BoxProc_Main( PROC* proc, int* seq )
{
	typedef PROC_RESULT (*BoxMainSeq)( BOXAPP_WORK* );

	BOXAPP_WORK* wk = PROC_GetWork(proc);

	if( wk->subSeqFunc != NULL )
	{
		wk->subSeqFunc( wk, &(wk->subseq) );
		return PROC_RES_CONTINUE;
	}
	else
	{
		if( wk->mainSeqFunc != NULL )
		{
			if( sys.trg & PAD_BUTTON_Y )
			{
				if( BoxAppView_WaitCommandAll(wk->vwk) == TRUE )
				{
					VParaSet_ExpertModeChange( &wk->vpara );
					BoxAppView_SetCommand( wk->vwk, CMD_CHANGE_EXPERTMODE );
					return PROC_RES_CONTINUE;
				}
			}
			return wk->mainSeqFunc( wk );
		}
	}

	GF_ASSERT(0);
	return PROC_RES_FINISH;
}
//------------------------------------------------------------------
/**
 * ボックスアプリPROC：End
 *
 * @param   proc			
 * @param   seq				
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT BoxProc_End( PROC* proc, int* seq )
{
	BOXAPP_WORK* wk = PROC_GetWork( proc );


	if( PokeParty_PokemonCheck( wk->partyData, MONSNO_PERAPPU ) ==  FALSE )
	{
		PERAPVOICE*  pv = SaveData_GetPerapVoice( wk->saveData );
		PERAPVOICE_ClearExistFlag( pv );
	}

	BoxAppView_End( wk->vwk );
	DeleteWork( wk );

	sys_DeleteHeap(  HEAPID_BOX_SYSTEM );
	sys_DeleteHeap(  HEAPID_BOX_VIEW );

	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * メインシーケンス変更
 *
 * @param   wk		
 * @param   nextSeqFunc
 *
 */
//------------------------------------------------------------------
static void MainSeqChange( BOXAPP_WORK* wk, seqFunc nextSeqFunc )
{
	wk->mainSeqFunc = nextSeqFunc;
	wk->seq = 0;
}
//------------------------------------------------------------------
/**
 * サブシーケンスへ動作切り替え
 *
 * @param   wk			ワークポインタ
 * @param   subSeqFunc	サブシーケンス関数ポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeqSet( BOXAPP_WORK* wk, SubSeqFunc subseq )
{
	wk->subSeqFunc = subseq;
	wk->subseq = 0;
}
//------------------------------------------------------------------
/**
 * サブシーケンス動作終了
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeqEnd( BOXAPP_WORK* wk )
{
	wk->subSeqFunc = NULL;
}

//------------------------------------------------------------------
/**
 * 現在のカーソル位置から対応したメインシーケンス関数アドレスを返す
 *
 * @param   wk		
 *
 * @retval  seqFunc		
 */
//------------------------------------------------------------------
static seqFunc GetNextMainSeqAdrsByCursorArea( BOXAPP_WORK* wk )
{
	switch( BoxAppVPara_GetCursorArea( &(wk->vpara) ) ){
	case CURSOR_AREA_TRAY:
	default:
		return BoxMainSeq_Tray;

	case CURSOR_AREA_PARTY:
		return BoxMainSeq_Party;

	case CURSOR_AREA_TRAY_TAB:
		return BoxMainSeq_TrayTab;

	case CURSOR_AREA_EXIT_BUTTON:
		return BoxMainSeq_ExitButton;

	case CURSOR_AREA_PARTY_BUTTON:
		return BoxMainSeq_PartyButton;
	}
}

//------------------------------------------------------------------
/**
 * ボックスデータ更新フラグをオンにする
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SetBoxModifiedFlag( BOXAPP_WORK* wk )
{
	wk->procParam->modifiedFlag = TRUE;
}



//------------------------------------------------------------------
/**
 * サブシーケンス：画面構築
 *
 * @param   wk		
 */
//------------------------------------------------------------------
static void SubSeq_StartBox( BOXAPP_WORK* wk,  u32* seq )
{
	switch( *seq ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_INIT );
		(*seq)++;
		break;

	case 1:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_INIT))
		{
			BoxAppView_SetCommand( wk->vwk, CMD_NORMAL_IN );
			(*seq)++;
		}
		break;

	case 2:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_NORMAL_IN ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：画面復帰
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SubSeq_RestartBox( BOXAPP_WORK* wk,  u32* seq )
{
	switch( *seq ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_INIT );
		(*seq)++;
		break;

	case 1:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_INIT))
		{
			BoxAppView_SetCommand( wk->vwk, CMD_FADEIN );
			(*seq)++;
		}
		break;

	case 2:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_FADEIN ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * メインシーケンス：画面イン
 *
 * @param   wk		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_Open( BOXAPP_WORK* wk )
{
	switch( wk->seq ) {
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_NORMAL_IN );
		wk->seq++;
		break;
	case 1:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_NORMAL_IN ) )
		{
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea(wk) );
		}
		break;
	}
	return PROC_RES_CONTINUE;
}

// ボタン押下で表示ポケモンを固定された時のパラメータ操作処理
static inline void update_compare_param_by_button( BOXAPP_WORK* wk )
{
	VParaSet_SwitchCompareSide( &wk->vpara );
	VParaSet_StatusPoke( &wk->vpara,  wk->vpara.cursor.point_poke, wk );
	BoxAppView_SetCommand( wk->vwk, CMD_SWITCH_COMPARE_SIDE_BY_BUTTON );
	BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
}

//------------------------------------------------------------------
/**
 * メインシーケンス共通のボタン押下チェック処理
 *
 * @param   wk		
 *
 * @retval  inline void		
 */
//------------------------------------------------------------------
static inline int MainSeq_ButtonCheckProc( BOXAPP_WORK* wk )
{
	if( CheckButtonPush( wk ) )
	{
		if( BoxAppVPara_GetBoxMode(&wk->vpara) != BOX_MODE_COMPARE )
		{
			switch( wk->btn_id ){
			case BUTTONID_LEFT:
				SubSeqSet( wk, SubSeq_TrayMode );
				break;

			case BUTTONID_RIGHT:
				if( BoxAppVPara_GetBoxMode(&wk->vpara) != BOX_MODE_ITEM )
				{
					SubSeqSet( wk, SubSeq_LimitMode );
				}
				else
				{
					Snd_SePlay( SOUND_DISABLE_BUTTON );
				}
				break;
			}
		}
		else
		{
			switch( wk->btn_id ){
			case BUTTONID_LEFT:
				if( (BoxAppVPara_GetCompareUpdateSide(&wk->vpara) == BOXAPP_COMPARE_SIDE_LEFT)
				&&	(BoxAppVPara_GetCursorPointPokeFlag(&wk->vpara) == TRUE )
				){
					Snd_SePlay( SOUND_DECIDE );
					update_compare_param_by_button( wk );
					return 1;
				}
				else
				{
					Snd_SePlay( SOUND_DISABLE_BUTTON );
				}
				break;

			case BUTTONID_RIGHT:
				if( (BoxAppVPara_GetCompareUpdateSide(&wk->vpara) == BOXAPP_COMPARE_SIDE_RIGHT)
				&&	(BoxAppVPara_GetCursorPointPokeFlag(&wk->vpara) == TRUE )
				){
					Snd_SePlay( SOUND_DECIDE );
					update_compare_param_by_button( wk );
					return 1;
				}
				else
				{
					Snd_SePlay( SOUND_DISABLE_BUTTON );
				}
				break;

			case BUTTONID_PAGE:
				Snd_SePlay( SOUND_DECIDE );
				VParaSet_ChangeComparePage( &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_CHANGE_COMPARE_PAGE );
				return 1;
			}
		}
	}

	return 0;
}



//------------------------------------------------------------------
/**
 * メインシーケンス：トレイ
 *
 * @param   wk		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_Tray( BOXAPP_WORK* wk )
{
	enum {
		SEQ_CHECK_KEY,
		SEQ_WAIT_CURSOR_MOVE,
		SEQ_WAIT_ANY_COMMAND,
	};

	switch( wk->seq ) {
	case SEQ_CHECK_KEY:
		if( sys.trg & PAD_BUTTON_A ){
			if( BoxAppVPara_GetCursorStatusEnableFlag( &wk->vpara ) )
			{
				if( BoxAppVPara_GetBoxMode( &wk->vpara ) != BOX_MODE_ITEM )
				{
					SubSeqSet( wk, SubSeq_Menu_Pokemon );
				}
				else
				{
					SubSeqSet( wk, SubSeq_Menu_Item );
				}
				break;
			}
		}
		if( sys.trg & PAD_BUTTON_B ){
			SubSeqSet( wk, SubSeq_B_Exit );
			break;
		}
		if( sys.cont & PAD_BUTTON_L ){
			VParaSet_CurrentTrayDec( &wk->vpara );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( sys.cont & PAD_BUTTON_R ){
			VParaSet_CurrentTrayInc( &(wk->vpara) );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( CheckCursorMoveKeyInput( sys.cont, wk ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq++;
			break;
		}

		if( MainSeq_ButtonCheckProc(wk) )
		{
			wk->seq = SEQ_WAIT_ANY_COMMAND;
		}

		break;

	case SEQ_WAIT_CURSOR_MOVE:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) ){
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea( wk ) );
		}
		break;

	case SEQ_WAIT_ANY_COMMAND:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			wk->seq = SEQ_CHECK_KEY;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}
//------------------------------------------------------------------
/**
 * 現在ステータス表示されているポケモンを、てもちトレイから
 * 外に連れ出すことが出来るかチェック
 *
 * @param   wk			ワークポインタ
 * @param   msgID		連れ出せないポケモンの場合、警告メッセージのID
 *
 * @retval  BOOL		TRUEで連れ出せない
 */
//------------------------------------------------------------------
static BOOL CheckStatusPokeUnleavable( BOXAPP_WORK* wk, int* msgID )
{
	if( ItemMailCheck(BoxAppVPara_GetStatusPokeItemNumber(&wk->vpara)) )
	{
		*msgID = msg_boxmes_01_32;
		return TRUE;
	}

	if( GetStatusPokeParam( &wk->vpara, ID_PARA_cb_id, NULL ) != 0 )
	{
		*msgID = msg_boxmes_01_31;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * メインシーケンス：てもちトレイ
 *
 * @param   wk		ワークポインタ
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_Party( BOXAPP_WORK* wk )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_CURSORMOVE_WAIT,
		SEQ_TRAYCLOSE,
		SEQ_TRAYCLOSE_WAIT,
		SEQ_TRAYCLOSE_CURSOR_WAIT,
		SEQ_MSG_KEYWAIT,
		SEQ_WAIT_ANY_COMMAND,
	};

	switch( wk->seq ){
	case SEQ_KEYWAIT:
		if( sys.trg & PAD_BUTTON_A )
		{
			// 閉じるボタンの処理
			if( BoxAppVPara_GetCursorPartyPos( &wk->vpara ) == CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
			{
				wk->seq = SEQ_TRAYCLOSE;
				break;
			}
			// それ以外の場所
			if( BoxAppVPara_GetCursorStatusEnableFlag( &wk->vpara ) )
			{
				if( BoxAppVPara_GetBoxMode( &wk->vpara ) != BOX_MODE_ITEM )
				{
					SubSeqSet( wk, SubSeq_Menu_Pokemon );
				}
				else
				{
					SubSeqSet( wk, SubSeq_Menu_Item );
				}
				break;
			}
			break;
		}
	// 手持ちトレイを閉じようとした
		if( (sys.trg & PAD_BUTTON_B)
		||	((sys.trg & PAD_KEY_RIGHT) && (BoxAppVPara_GetCursorPartyPos(&wk->vpara) & 1))
		||	((sys.trg & PAD_KEY_RIGHT) && (BoxAppVPara_GetCursorPartyPos(&wk->vpara) == CURSOR_PARTYTRAY_CLOSEBUTTON_POS))
		){
			wk->seq = SEQ_TRAYCLOSE;
			break;
		}
		if( CheckCursorMoveKeyInput( sys.cont, wk ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_CURSORMOVE_WAIT;
			break;
		}
		if( MainSeq_ButtonCheckProc(wk) )
		{
			wk->seq = SEQ_WAIT_ANY_COMMAND;
			break;
		}
		break;

	// カーソル移動待ち
	case SEQ_CURSORMOVE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) )
		{
			wk->seq = SEQ_KEYWAIT;
		}
		break;


	case SEQ_TRAYCLOSE:
		// あずけるモードならボックスを抜けようとするのと同じ処理
		if( BoxAppVPara_GetBoxMode( &wk->vpara ) == BOX_MODE_AZUKERU )
		{
			SubSeqSet( wk, SubSeq_B_Exit );
			wk->seq = SEQ_KEYWAIT;
		}
		else
		{
			int msgID;

			// 手持ちから外せないポケモンを掴んでいる場合は警告
			if(	(BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) != CURSOR_CATCH_NONE)
			&&	(CheckStatusPokeUnleavable( wk, &msgID ))
			){
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msgID );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				wk->seq = SEQ_MSG_KEYWAIT;
			}
			else
			{
				BoxAppView_SetCommand( wk->vwk, CMD_PARTYTRAY_CLOSE );
				wk->seq = SEQ_TRAYCLOSE_WAIT;
			}
		}
		break;

	// トレイ閉じ待ち
	case SEQ_TRAYCLOSE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_PARTYTRAY_CLOSE ) )
		{
			CursorPosSetForPartyBoxButtonClose( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_TRAYCLOSE_CURSOR_WAIT;
		}
		break;

	case SEQ_TRAYCLOSE_CURSOR_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) )
		{
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea( wk ) );
		}
		break;

	case SEQ_MSG_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			wk->seq = SEQ_KEYWAIT;
		}
		break;

	case SEQ_WAIT_ANY_COMMAND:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			wk->seq = SEQ_KEYWAIT;
		}
		break;

	}

	return PROC_RES_CONTINUE;
}
//------------------------------------------------------------------
/**
 * メインシーケンス：トレイタブ
 *
 * @param   wk		ワークポインタ
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_TrayTab( BOXAPP_WORK* wk )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_CURSORMOVE_WAIT,
	};

	switch( wk->seq ){
	case SEQ_KEYWAIT:
		if( sys.cont & (PAD_KEY_LEFT|PAD_BUTTON_L) ){
			VParaSet_CurrentTrayDec( &wk->vpara );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( sys.cont & (PAD_KEY_RIGHT|PAD_BUTTON_R) ){
			VParaSet_CurrentTrayInc( &(wk->vpara) );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( sys.trg & PAD_BUTTON_A ){
			SubSeqSet( wk, SubSeq_Menu_Tray );
			break;
		}
		if( sys.trg & PAD_BUTTON_B ){
			SubSeqSet( wk, SubSeq_B_Exit );
			break;
		}
		if( CheckCursorMoveKeyInput( sys.cont, wk ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_CURSORMOVE_WAIT;
			break;
		}

		MainSeq_ButtonCheckProc(wk);
		break;

	case SEQ_CURSORMOVE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) ){
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea( wk ) );
		}
		break;
	}
	return PROC_RES_CONTINUE;
}
//------------------------------------------------------------------
/**
 * メインシーケンス：『とじる』ボタン上
 *
 * @param   wk		ワークポインタ
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_ExitButton( BOXAPP_WORK* wk )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_TRAYCHANGE_WAIT,
		SEQ_CURSORMOVE_WAIT,
	};

	switch( wk->seq ){
	case SEQ_KEYWAIT:
		if( sys.trg & PAD_BUTTON_A ){
			SubSeqSet( wk, SubSeq_ExitButton );
			break;
		}
		if( sys.trg & PAD_BUTTON_B ){
			SubSeqSet( wk, SubSeq_B_Exit );
			break;
		}
		if( sys.cont & PAD_BUTTON_L ){
			VParaSet_CurrentTrayDec( &wk->vpara );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( sys.cont & PAD_BUTTON_R ){
			VParaSet_CurrentTrayInc( &(wk->vpara) );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( CheckCursorMoveKeyInput( sys.cont, wk ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_CURSORMOVE_WAIT;
			break;
		}
		MainSeq_ButtonCheckProc(wk);
		break;

	case SEQ_TRAYCHANGE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_TRAY_CHANGE ) ){
			wk->seq = SEQ_KEYWAIT;
		}
		break;

	case SEQ_CURSORMOVE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) ){
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea( wk ) );
		}
		break;
	}
	return PROC_RES_CONTINUE;
}
//------------------------------------------------------------------
/**
 * メインシーケンス：『てもちポケモン』ボタン上
 *
 * @param   wk		ワークポインタ
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_PartyButton( BOXAPP_WORK* wk )
{
	enum {
		SEQ_KEYWAIT,
		SEQ_BUTTONACTION_WAIT,
		SEQ_PARTYTRAY_OPEN_WAIT,
		SEQ_TRAYCHANGE_WAIT,
		SEQ_CURSORMOVE_WAIT,
		SEQ_WARN_MESSAGE_WAIT,
	};

	switch( wk->seq ){
	case SEQ_KEYWAIT:
		if( sys.trg & PAD_BUTTON_A )
		{
			if( BoxAppVPara_GetBoxMode(&wk->vpara) != BOX_MODE_TURETEIKU )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_BUTTON_PUSH_ACTION );
				wk->seq = SEQ_BUTTONACTION_WAIT;
			}
			else
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_19 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				wk->seq = SEQ_WARN_MESSAGE_WAIT;

			}
			break;
		}
		if( sys.trg & PAD_BUTTON_B )
		{
			SubSeqSet( wk, SubSeq_B_Exit );
			break;
		}
		if( sys.cont & PAD_BUTTON_L ){
			VParaSet_CurrentTrayDec( &wk->vpara );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( sys.cont & PAD_BUTTON_R ){
			VParaSet_CurrentTrayInc( &(wk->vpara) );
			SubSeqSet( wk, SubSeq_ChangeTray );
			break;
		}
		if( CheckCursorMoveKeyInput( sys.cont, wk ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_CURSORMOVE_WAIT;
			break;
		}

		MainSeq_ButtonCheckProc(wk);

		break;

	case SEQ_BUTTONACTION_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_BUTTON_PUSH_ACTION ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_PARTYTRAY_OPEN );
			wk->seq = SEQ_PARTYTRAY_OPEN_WAIT;
		}
		break;

	case SEQ_PARTYTRAY_OPEN_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_PARTYTRAY_OPEN ) )
		{
			CursorPosSetForPartyBoxButtonOpen( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			wk->seq = SEQ_CURSORMOVE_WAIT;
		}
		break;

	case SEQ_TRAYCHANGE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_TRAY_CHANGE ) ){
			wk->seq = SEQ_KEYWAIT;
		}
		break;

	case SEQ_CURSORMOVE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) ){
			MainSeqChange( wk, GetNextMainSeqAdrsByCursorArea( wk ) );
		}
		break;

	case SEQ_WARN_MESSAGE_WAIT:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B))
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			wk->seq = SEQ_KEYWAIT;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}
//------------------------------------------------------------------
/**
 * ポケモンステータス画面用パラメータセット
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SetPokemonStatusScheneParam( BOXAPP_WORK* wk )
{
	/*
		typedef struct {
			void * ppd;		// ポケモンデータ
			u8	ppt;		// パラメータタイプ
			u8	mode;		// モード
			u8	max;		// 最大数
			u8	pos;		// 何番目のデータか
			u8	ret_sel;
			u8	ret_mode;
			u8	dmy[3];
		}PSTATUS_DATA;
	*/
	static const u8	page_tbl[] = {
			PST_PAGE_INFO,			// 「ポケモンじょうほう」
			PST_PAGE_MEMO,			// 「トレーナーメモ」
			PST_PAGE_PARAM,			// 「ポケモンのうりょく」
			PST_PAGE_CONDITION,		// 「コンディション」
			PST_PAGE_B_SKILL,		// 「たたかうわざ」
			PST_PAGE_C_SKILL,		// 「コンテストわざ」
			PST_PAGE_RIBBON,		// 「きねんリボン」
			PST_PAGE_RET,			// 「もどる」
			PST_PAGE_MAX
	};

	if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_SINGLE )
	{
		BOXAPP_CATCH_POKE* catchPoke = &wk->vpara.catchPoke;

		wk->statusParam.ppd = wk->vpara.catchPoke.ppp;
		wk->statusParam.ppt = (catchPoke->fromPartyFlag)? PST_PP_TYPE_POKEPARAM : PST_PP_TYPE_POKEPASO;
		wk->statusParam.max = 1;
		wk->statusParam.pos = 0;
		wk->statusParam.mode = 0;
		wk->statusParam.waza = 0;
		wk->statusParam.cfg = wk->sysConfig;
	}
	else if( BoxAppVPara_GetCursorArea( &wk->vpara ) == CURSOR_AREA_TRAY )
	{
		wk->statusParam.ppd = BOXDAT_GetPokeDataAddress(wk->boxData, BOXDAT_GetCureentTrayNumber(wk->boxData), 0);
		wk->statusParam.ppt = PST_PP_TYPE_POKEPASO;
		wk->statusParam.max = BOX_MAX_POS;
		wk->statusParam.pos = BoxAppVPara_GetCursorTrayPos( &wk->vpara );
		wk->statusParam.mode = 0;
		wk->statusParam.waza = 0;
	}
	else
	{
		wk->statusParam.ppd = wk->partyData;
		wk->statusParam.ppt = PST_PP_TYPE_POKEPARTY;
		wk->statusParam.max = PokeParty_GetPokeCount( wk->partyData );
		wk->statusParam.pos = BoxAppVPara_GetCursorPartyPos( &wk->vpara );
		wk->statusParam.mode = 0;
		wk->statusParam.waza = 0;
	}

	wk->statusParam.perap = NULL;
	wk->statusParam.zukan_mode = PMNumber_GetMode( wk->saveData );
	wk->statusParam.ev_contest = PokeStatus_ContestFlagGet( wk->saveData );
	wk->statusParam.ribbon = SaveData_GetSpRibbon( wk->saveData );

	PokeStatus_PageSet( &(wk->statusParam), page_tbl );
	PokeStatus_PlayerSet( &(wk->statusParam), SaveData_GetMyStatus( wk->saveData ) );
}
//------------------------------------------------------------------
/**
 * メインシーケンス：ボックスを閉じる演出
 *
 * @param   wk		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
static PROC_RESULT BoxMainSeq_Close( BOXAPP_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_BOXCLOSE );
		wk->seq++;
		break;
	case 1:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			return PROC_RES_FINISH;
		}
	}
	return PROC_RES_CONTINUE;
}

//======================================================================================================
// サブシーケンス群
//======================================================================================================

//------------------------------------------------------------------
/**
 * サブシーケンス：「ボックスをとじる」ボタンを押した
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
static void  SubSeq_ExitButton( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_CATCH_CHECK,
		SEQ_BUTTONACTION_WAIT,
		SEQ_MENUWAIT,
		SEQ_MENU_VIEWWAIT,
		SEQ_WARN_VIEWWAIT,
		SEQ_WARN_KEYWAIT,
		SEQ_CLEAR_VIEWWAIT,
	};

	switch( (*seq) ){
	case SEQ_CATCH_CHECK:
		if( (BoxAppVPara_GetBoxMode( &(wk->vpara) ) == BOX_MODE_ITEM)
		&&	(BoxAppVPara_GetCatchItemNumber( &(wk->vpara) ) != ITEM_DUMMY_ID )
		){
			SubSeqSet( wk, SubSeq_ItemMode_Restore );
			break;
		}

		if( BoxAppVPara_GetCursorCatchPokeFlag( &(wk->vpara) ) != CURSOR_CATCH_NONE )
		{
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_18 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_WARN_VIEWWAIT;
			break;
		}
		else
		{
			BoxAppView_SetCommand( wk->vwk, CMD_BUTTON_PUSH_ACTION );
			(*seq) = SEQ_BUTTONACTION_WAIT;
		}
		break;

	case SEQ_BUTTONACTION_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_BUTTON_PUSH_ACTION ) )
		{
			Snd_SePlay( SOUND_DISP_MENU );
			// ボックスを終了しますか？ メッセージ表示
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_12 );
			BoxMenu_SetYesNoMenu( &(wk->vpara), 1 );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_MENUWAIT;
		}
		break;

	case SEQ_MENUWAIT:
		switch( BoxMenu_Ctrl( &(wk->vpara) ) ){
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;

		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_NO:
			Snd_SePlay( SOUND_CANCEL );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CLEAR_VIEWWAIT;
			break;

		case BOXMENU_YES:
			MainSeqChange( wk, BoxMainSeq_Close );
			SubSeqEnd(wk);
			break;
		}
		break;


	case SEQ_WARN_VIEWWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE)
		{
			break;
		}
		(*seq) = SEQ_WARN_KEYWAIT;
		/* fallthru */
	case SEQ_WARN_KEYWAIT:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CLEAR_VIEWWAIT;
		}
		break;
	case SEQ_CLEAR_VIEWWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			SubSeqEnd(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：Ｂボタンで抜けようとした
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_B_Exit( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_CATCH_CHECK,
		SEQ_TRAYCHANGE_WAIT,
		SEQ_WARN_VIEWWAIT,
		SEQ_WARN_KEYWAIT,
		SEQ_CLEAR_VIEWWAIT,
		SEQ_MENUWAIT,
		SEQ_MENU_VIEWWAIT,
	};

	switch( (*seq) ){
	case SEQ_CATCH_CHECK:
		if( BoxAppVPara_GetCursorCatchPokeFlag( &(wk->vpara) ) != CURSOR_CATCH_NONE )
		{
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_18 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_WARN_VIEWWAIT;
			break;
		}
		else if(
			(BoxAppVPara_GetBoxMode(&wk->vpara) == BOX_MODE_ITEM)
		&&	(BoxAppVPara_GetCatchItemNumber(&wk->vpara) != ITEM_DUMMY_ID)
		){
			SubSeqSet( wk, SubSeq_ItemMode_Restore );
			break;
		}
		else
		{
			Snd_SePlay( SOUND_DISP_MENU );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_13 );
			BoxMenu_SetYesNoMenu( &(wk->vpara), 0 );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_MENUWAIT;
		}
		break;

	case SEQ_MENUWAIT:
		switch( BoxMenu_Ctrl( &(wk->vpara) ) ){
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_NO:
			MainSeqChange( wk, BoxMainSeq_Close );
			SubSeqEnd(wk);
			break;

		case BOXMENU_YES:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CLEAR_VIEWWAIT;
			break;
		}
		break;


	case SEQ_WARN_VIEWWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE)
		{
			break;
		}
		(*seq) = SEQ_WARN_KEYWAIT;
		/* fallthru */
	case SEQ_WARN_KEYWAIT:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CLEAR_VIEWWAIT;
		}
		break;
	case SEQ_CLEAR_VIEWWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			SubSeqEnd(wk);
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモンメニュー
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_Pokemon( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_INIT_WAIT,
		SEQ_MENU_CTRL,
		SEQ_DECIDE_MENU,
		SEQ_CANCEL_WAIT,
		SEQ_CMD_WAIT,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		WORDSET_RegisterPokeNickName( wk->wordset, 0, BoxAppVPara_GetStatusPokePara( &wk->vpara ) );
		VParaSet_MessageID( &wk->vpara, msg_boxmes_01_01 );
		BoxMenu_SetPokeMenu( &wk->vpara );
		if( BoxAppVPara_GetExpertModeFlag( &wk->vpara ) )
		{
			wk->work = BoxMenu_GetFirstMenuID( &wk->vpara );
			(*seq) = SEQ_DECIDE_MENU;
		}
		else
		{
			Snd_SePlay( SOUND_DISP_MENU );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_INIT_WAIT;
		}
		break;
	case SEQ_INIT_WAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE){
			break;
		}
		(*seq) = SEQ_MENU_CTRL;
		/* fallthru */
	case SEQ_MENU_CTRL:
		wk->work = BoxMenu_Ctrl( &(wk->vpara) );
		switch( wk->work ){
		case BOXMENU_CTRL_LOOP:
			break;
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_POKEMENU_QUIT:
			Snd_SePlay( SOUND_CANCEL );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CANCEL_WAIT;
			break;

		default:
			(*seq) = SEQ_DECIDE_MENU;
			break;
		}
		break;

	case SEQ_DECIDE_MENU:
		switch( wk->work ){
		case BOXMENU_POKE_TUKAMU:
			if(	(BoxAppVPara_GetCursorArea(&wk->vpara) == CURSOR_AREA_TRAY)
			&&	(BoxAppVPara_GetExpertModeFlag(&wk->vpara) == TRUE )
			){
				SubSeqSet( wk, SubSeq_AreaSelect );
			}
			else
			{
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				SubSeqSet( wk, SubSeq_OP_Tukamu );
			}
			break;

		case BOXMENU_POKE_OKU:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			SubSeqSet( wk, SubSeq_OP_Oku );
			break;

		case BOXMENU_POKE_IREKAERU:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			SubSeqSet( wk, SubSeq_OP_Irekaeru );
			break;

		case BOXMENU_POKE_TURETEIKU:
			SubSeqSet( wk, SubSeq_OP_Tureteiku );
			break;

		case BOXMENU_POKE_AZUKERU:
			SubSeqSet( wk, SubSeq_OP_Azukeru );
			break;

		case BOXMENU_POKE_MARKING:
			SubSeqSet( wk, SubSeq_Menu_Marking );
			break;

		case BOXMENU_POKE_NIGASU:
			SubSeqSet( wk, SubSeq_OP_Nigasu );
			break;

		case BOXMENU_POKE_YOUSU:
			SubSeqSet( wk, SubSeq_Connect_PokemonStatus );
			break;

		case BOXMENU_POKE_MOTIMONO:
			{
				if( BoxAppVPara_GetStatusPokeItemNumber( &wk->vpara ) == ITEM_DUMMY_ID )
				{
					SubSeqSet( wk, SubSeq_Connect_Bag );
				}
				else
				{
					SubSeqSet( wk, SubSeq_Restore_Item );
				}
			}
			break;

		case BOXMENU_COMPARE_HOLD_LEFT:
		case BOXMENU_COMPARE_HOLD_RIGHT:
			VParaSet_SwitchCompareSide( &wk->vpara );
			VParaSet_StatusPoke( &wk->vpara,  wk->vpara.cursor.point_poke, wk );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			BoxAppView_SetCommand( wk->vwk, CMD_SWITCH_COMPARE_SIDE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			Snd_SePlay( SOUND_DECIDE );
			(*seq) = SEQ_CMD_WAIT;
			break;
		}
		break;

	case SEQ_CANCEL_WAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			SubSeqEnd(wk);
		}
		break;

	case SEQ_CMD_WAIT:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SubSeqEnd(wk);
		}
		break;

	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：アイテムメニュー
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_Item( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_WAIT_MENU_DISP,
		SEQ_MENU_CTRL,
		SEQ_DECIDE_MENU,
		SEQ_CANCEL_WAIT,
		SEQ_UPDATE_POKEICON,
		SEQ_CMD_WAIT,
		SEQ_KEYWAIT,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		{
			u32 itemno = BoxAppVPara_GetCatchItemNumber( &wk->vpara );
			if( itemno != ITEM_DUMMY_ID )
			{
				WORDSET_RegisterItemName( wk->wordset, 0, itemno );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_26 );
			}
			else
			{
				itemno = BoxAppVPara_GetStatusPokeItemNumber( &wk->vpara );
				if( itemno != ITEM_DUMMY_ID )
				{
					WORDSET_RegisterItemName( wk->wordset, 0, itemno );
					VParaSet_MessageID( &wk->vpara, msg_boxmes_01_26 );
				}
				else
				{
					VParaSet_MessageID( &wk->vpara, msg_boxmes_01_30 );
				}
			}
			BoxMenu_SetItemMenu( &wk->vpara );
		}
		if( BoxAppVPara_GetStatusPokeTamagoFlag( &wk->vpara ) )
		{
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_36 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_KEYWAIT;
		}
		else if( BoxAppVPara_GetExpertModeFlag( &wk->vpara ) )
		{
			wk->work = BoxMenu_GetFirstMenuID( &wk->vpara );
			(*seq) = SEQ_DECIDE_MENU;
		}
		else
		{
			Snd_SePlay( SOUND_DISP_MENU );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_WAIT_MENU_DISP;
		}
		break;

	case SEQ_WAIT_MENU_DISP:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE){
			break;
		}
		(*seq) = SEQ_MENU_CTRL;
		/* fallthru */
	case SEQ_MENU_CTRL:
		wk->work = BoxMenu_Ctrl( &(wk->vpara) );
		switch( wk->work ){
		case BOXMENU_CTRL_LOOP:
			break;
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_ITEM_QUIT:
			Snd_SePlay( SOUND_CANCEL );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CANCEL_WAIT;
			break;

		default:
			Snd_SePlay( SOUND_DECIDE );
			(*seq) = SEQ_DECIDE_MENU;
			break;
		}
		break;

	case SEQ_DECIDE_MENU:
		switch( wk->work ){
		case BOXMENU_ITEM_SET:		///< アイテム「もたせる」
			if( BoxAppVPara_GetCatchItemNumber( &wk->vpara ) != ITEM_DUMMY_ID )
			{
				VParaSet_SetItem( &wk->vpara, wk );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_ITEM_SET );
				Snd_SePlay( SOUND_ITEM_SET );
				(*seq) = SEQ_UPDATE_POKEICON;
			}
			else
			{
				SubSeqSet( wk, SubSeq_Connect_Bag );
			}
			break;

		case BOXMENU_ITEM_WITHDRAW:	///< アイテム「あずかる」
			if( ItemMailCheck( BoxAppVPara_GetStatusPokeItemNumber(&wk->vpara) ) )
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_25 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_KEYWAIT;
			}
			else
			{
				VParaSet_WithDrawItem( &wk->vpara, wk );
				SetBoxModifiedFlag( wk );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_ITEM_WITHDRAW );
				Snd_SePlay( SOUND_ITEM_WITHDRAW );
				(*seq) = SEQ_UPDATE_POKEICON;
			}
			break;

		case BOXMENU_ITEM_INFO:		///< アイテム「せつめい」
			SubSeqSet( wk, SubSeq_ItemInfo );
			break;

		case BOXMENU_ITEM_SWAP:		///< アイテム「とりかえる」
			if( ItemMailCheck( BoxAppVPara_GetStatusPokeItemNumber(&wk->vpara) ) )
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_25 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_KEYWAIT;
			}
			else
			{
				VParaSet_SwapItem( &wk->vpara, wk );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_ITEM_SWAP );
				Snd_SePlay( SOUND_ITEM_SWAP );
				(*seq) = SEQ_UPDATE_POKEICON;
			}
			break;

		case BOXMENU_ITEM_TO_BAG:	///< アイテム「バッグへ」
			SubSeqSet( wk, SubSeq_ItemMode_Restore );
			break;
		}
		break;

	case SEQ_CANCEL_WAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			SubSeqEnd(wk);
		}
		break;

	case SEQ_UPDATE_POKEICON:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			BoxAppView_SetCommand( wk->vwk, CMD_ITEM_POKE_UPDATE );
			*seq = SEQ_CMD_WAIT;
		}
		break;

	case SEQ_CMD_WAIT:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SubSeqEnd(wk);
		}
		break;

	case SEQ_KEYWAIT:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand(wk->vwk, CMD_MSG_CLEAR);
			(*seq) = SEQ_CMD_WAIT;
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：トレイメニュー
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_Tray( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_INIT_WAIT,
		SEQ_MENU_CTRL,
		SEQ_DECIDE_MENU,
		SEQ_CANCEL_WAIT,
		SEQ_CMD_WAIT,
		SEQ_CMD_WAIT_UPDATE,
		SEQ_GOTO_WALLPAPER_MENU,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		VParaSet_MessageID( &wk->vpara, msg_boxmes_01_08 );
		BoxMenu_SetTrayMenu( &wk->vpara );
		if( BoxAppVPara_GetExpertModeFlag( &wk->vpara ) )
		{
			Snd_SePlay( SOUND_DECIDE );
			wk->work = BoxMenu_GetFirstMenuID( &wk->vpara );
			(*seq) = SEQ_DECIDE_MENU;
		}
		else
		{
			Snd_SePlay( SOUND_DISP_MENU );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_INIT_WAIT;
		}
		break;
	case SEQ_INIT_WAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE){
			break;
		}
		(*seq) = SEQ_MENU_CTRL;
		/* fallthru */
	case SEQ_MENU_CTRL:
		wk->work = BoxMenu_Ctrl( &(wk->vpara) );
		switch( wk->work ){
		case BOXMENU_CTRL_LOOP:
			break;
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_TRAYMENU_QUIT:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CANCEL_WAIT;
			break;
		default:
			(*seq) = SEQ_DECIDE_MENU;
			break;
		}
		break;

	case SEQ_DECIDE_MENU:
		switch(wk->work){
		case BOXMENU_TRAY_JUMP:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			SubSeqSet( wk, SubSeq_Menu_Jump );
			break;

		case BOXMENU_TRAY_WALLPAPER:
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
			(*seq) = SEQ_GOTO_WALLPAPER_MENU;
			break;

		case BOXMENU_TRAY_NAME:
			SubSeqSet( wk, SubSeq_Connect_InputTrayName );
			break;
		}
		break;


	case SEQ_CANCEL_WAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			SubSeqEnd( wk );
		}
		break;

	case SEQ_GOTO_WALLPAPER_MENU:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SubSeqSet( wk, SubSeq_Menu_WallPaper );
		}
		break;

	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：ボックス切り替え
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_Jump( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_SUBSEQ_RET,
		SEQ_RETURN,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		SelectTrayCtrl_Init( wk, BoxAppVPara_GetTrayBoxNumber( &wk->vpara ), msg_boxmes_01_09 );
		(*seq) = SEQ_SUBSEQ_RET;
		break;

	case SEQ_SUBSEQ_RET:
		if( SelectTrayCtrl_Main(wk) == FALSE )
		{
			break;
		}
		// 今いるボックスを選んだらキャンセルと同じ扱い
		if( (wk->selectTrayWork.trayNumber == SELECT_TRAY_CANCEL)
		||	(wk->selectTrayWork.trayNumber == BoxAppVPara_GetTrayBoxNumber( &wk->vpara ))
		){
			(*seq) = SEQ_RETURN;
		}
		else
		{
			VParaSet_CurrentTrayNumberSet( &wk->vpara, wk->selectTrayWork.trayNumber );
			BOXDAT_SetCureentTrayNumber( wk->boxData, wk->selectTrayWork.trayNumber );
			BoxAppView_SetCommand( wk->vwk, CMD_TRAY_CHANGE );
			(*seq) = SEQ_RETURN;
		}
		BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
		BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_CLEAR );
		break;

	case SEQ_RETURN:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：壁紙メニュー
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_WallPaper( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_CATEGORY_INIT,
		SEQ_CATEGORY_DISPWAIT,
		SEQ_CATEGORY_MENUCTRL,
		SEQ_TYPE_DISPWAIT,
		SEQ_TYPE_MENUCTRL,
		SEQ_WPCHANGE_START,
		SEQ_VIEWWAIT_PREV,
		SEQ_VIEWWAIT_RETURN,
	};
	switch( (*seq) ){
	case SEQ_INIT:
		wk->work = BOXMENU_WP_CATEGORY1;
		(*seq) = SEQ_CATEGORY_INIT;
		/* fallthru */
	case SEQ_CATEGORY_INIT:
		VParaSet_MessageID( &wk->vpara, msg_boxmes_01_10 );
		BoxMenu_SetWallPaperCategoryMenu( &wk->vpara, wk->work );
		BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
		(*seq) = SEQ_CATEGORY_DISPWAIT;
		break;
	case SEQ_CATEGORY_DISPWAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE){
			break;
		}
		(*seq) = SEQ_CATEGORY_MENUCTRL;
		/* fallthru */
	case SEQ_CATEGORY_MENUCTRL:
		switch( BoxMenu_Ctrl(&(wk->vpara)) ){
		case BOXMENU_CTRL_LOOP:
			break;
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_TRAYMENU_QUIT:
		default:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_VIEWWAIT_RETURN;
			break;
		case BOXMENU_WP_CATEGORY1:
		case BOXMENU_WP_CATEGORY2:
		case BOXMENU_WP_CATEGORY3:
		case BOXMENU_WP_CATEGORY4:
		case BOXMENU_WP_CATEGORY_EX1:
		case BOXMENU_WP_CATEGORY_EX2:
			// 選択されたカテゴリを覚えておく
			wk->work = BoxMenu_GetSelectMenuID( &wk->vpara );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_11 );
			BoxMenu_SetWallPaperTypeMenu( &wk->vpara, wk->work );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_TYPE_DISPWAIT;
			break;
		}
		break;

	case SEQ_TYPE_DISPWAIT:
		if(BoxAppView_WaitCommand( wk->vwk, CMD_MENU_DISP ) == FALSE){
			break;
		}
		(*seq) = SEQ_TYPE_MENUCTRL;
		/* fallthru */
	case SEQ_TYPE_MENUCTRL:
		switch( BoxMenu_Ctrl(&(wk->vpara)) ){
		case BOXMENU_CTRL_LOOP:
			break;
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_TRAYMENU_QUIT:
			(*seq) = SEQ_CATEGORY_INIT;
			break;
		default:
			wk->work = BoxMenu_GetSelectMenuID( &wk->vpara );
			if( wk->work >= BOXMENU_WP_NAME1_1 && wk->work <= BOXMENU_WP_NAME_EX_8 )
			{
				BOXDAT_SetWallPaperNumber( wk->boxData, BOXDAT_TRAYNUM_CURRENT, ( wk->work - BOXMENU_WP_NAME1_1 ) );
				TrayCurrentWallPaperUpdate( &wk->vpara, wk->boxData );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq) = SEQ_WPCHANGE_START;
			}
			else
			{
				GF_ASSERT(0);
				(*seq) = SEQ_CATEGORY_INIT;
			}
		}
		break;

	case SEQ_WPCHANGE_START:
		BoxAppView_SetCommand( wk->vwk, CMD_WALLPAPER_CHANGE );
		(*seq) = SEQ_VIEWWAIT_RETURN;
		break;

	case SEQ_VIEWWAIT_PREV:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			(*seq) = SEQ_CATEGORY_INIT;
		}
		break;

	case SEQ_VIEWWAIT_RETURN:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SubSeqEnd(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：マーキングメニュー
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Menu_Marking( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_MENUCTRL,
		SEQ_RET,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		BoxMenu_SetMarkingMenu( &wk->vpara );
		VParaSet_MessageID( &wk->vpara, msg_boxmes_01_02 );
		BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
		(*seq) = SEQ_MENUCTRL;
		break;

	case SEQ_MENUCTRL:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE ){
			break;
		}else{
			u32 ctrl_result = BoxMenu_Ctrl(&(wk->vpara));
			switch( ctrl_result ){
			case BOXMENU_CTRL_LOOP:
				break;
			case BOXMENU_CTRL_MOVE:
				BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
				break;

			case BOXMENU_CTRL_CANCEL:
			case BOXMENU_MARKING_CANCEL:
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq) = SEQ_RET;
				break;

			case BOXMENU_MARKING_DECIDE:
				VParaSet_StatusPokeMark( &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_MARK_UPDATE );
				BoxAppView_SetCommand( wk->vwk, CMD_ICON_LIMITMODE_UPDATE );
				(*seq) = SEQ_RET;
				break;

			default:
				if( ctrl_result >= BOXMENU_MARK1 && ctrl_result <= BOXMENU_MARK6 )
				{
					ctrl_result -= BOXMENU_MARK1;
					BoxMenu_ReverseMarkingState( &wk->vpara, ctrl_result );
					BoxAppView_SetCommand( wk->vwk, CMD_MENUMARK_UPDATE );
				}
				break;
			}
		}
		break;

	case SEQ_RET:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * サブシーケンス：アイコンの範囲選択処理
 *
 * @param   wk				ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_AreaSelect( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_AREASELECT,
		SEQ_POSSELECT,
		SEQ_CURSORMOVE_AREASELECT,
		SEQ_POKEPUT_WAIT,
	};

	switch(*seq){
	case SEQ_INIT:
		if( sys.cont & PAD_BUTTON_A )
		{
			VParaSet_StartAreaSelect( wk, &wk->vpara );
			BoxAppView_SetCommand( wk->vwk, CMD_START_AREASELECT );
			Snd_SePlay( SOUND_MOVE_CURSOR );
			*seq = SEQ_AREASELECT;
		}
		else
		{
			SubSeqSet( wk, SubSeq_OP_Tukamu );
		}
		break;

	case SEQ_AREASELECT:
		if( sys.cont & PAD_BUTTON_A )
		{
			switch( CheckCursorMoveKeyInput_AreaSelect( sys.cont, wk ) ){
			case AREASELECT_RESULT_OVER:
				if( (sys.cont & PAD_PLUS_KEY_MASK) == (sys.trg & PAD_PLUS_KEY_MASK) )
				{
					Snd_SePlay( SOUND_WARNING );
				}
				break;

			case AREASELECT_RESULT_UPDATE:
				VParaSet_UpdateAreaSelect( wk, &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_UPDATE_AREASELECT );
				BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
				*seq = SEQ_CURSORMOVE_AREASELECT;
				break;
			}
		}
		else
		{
			if( BoxAppVPara_CheckAreaSelectSinglePoke(&wk->vpara) )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_END_AREASELECT );
				SubSeqSet( wk, SubSeq_OP_Tukamu );
			}
			else
			{
				VParaSet_AreaSelectPokeCatch( wk, &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_CATCH_AREASELECT_POKE );
				Snd_SePlay( SOUND_POKE_CATCH );
				*seq = SEQ_POSSELECT;
			}
		}
		break;


	case SEQ_POSSELECT:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		switch( CheckCursorMoveKeyInput_AreaSelect( sys.cont, wk ) ){
		case AREASELECT_RESULT_OVER:
			if( (sys.cont & PAD_PLUS_KEY_MASK) == (sys.trg & PAD_PLUS_KEY_MASK) )
			{
				Snd_SePlay( SOUND_WARNING );
			}
			break;

		case AREASELECT_RESULT_UPDATE:
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			if( (BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) & CUROSR_CATCH_STATUS_HOLD_MASK) == 0 )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			}
			break;

		case AREASELECT_RESULT_SCROLL_LEFT:
			VParaSet_CurrentTrayDec( &wk->vpara );
			BOXDAT_SetCureentTrayNumber( wk->boxData, BoxAppVPara_GetTrayBoxNumber(&wk->vpara) );
			BoxAppView_SetCommand( wk->vwk, CMD_TRAY_CHANGE );
			break;

		case AREASELECT_RESULT_SCROLL_RIGHT:
			VParaSet_CurrentTrayInc( &(wk->vpara) );
			BOXDAT_SetCureentTrayNumber( wk->boxData, BoxAppVPara_GetTrayBoxNumber(&wk->vpara) );
			BoxAppView_SetCommand( wk->vwk, CMD_TRAY_CHANGE );
			break;

		case AREASELECT_RESULT_NONE:
			if(sys.trg & PAD_BUTTON_A )
			{
				if(Check_AreaSelectPokePut(&wk->vpara))
				{
					VParaSet_AreaSelectPokePut( wk, &wk->vpara );
					BoxAppView_SetCommand( wk->vwk, CMD_POKE_PUT );
					Snd_SePlay( SOUND_POKE_PUT );
					*seq = SEQ_POKEPUT_WAIT;
				}
				else
				{
					Snd_SePlay( SOUND_WARNING );
				}
				break;
			}
			if( sys.trg & PAD_BUTTON_B )
			{
				Snd_SePlay( SOUND_WARNING );
			}
			break;
		}
		break;

	case SEQ_CURSORMOVE_AREASELECT:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			*seq = SEQ_AREASELECT;
		}
		break;

	case SEQ_POKEPUT_WAIT:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd(wk);
		}
		break;

	}
}
//------------------------------------------------------------------
/**
 * 範囲選択中のポケモンを現在位置に置けるかチェック
 *
 * @param   vpara		
 *
 * @retval  BOOL		TRUEで置ける
 */
//------------------------------------------------------------------
static BOOL Check_AreaSelectPokePut( const BOXAPP_VPARAM* vpara )
{
	POKEMON_PASO_PARAM* ppp;
	int i, catch_top_pos, put_top_pos, check_pos;
	const BOXAPP_CURSOR* cursor = &vpara->cursor;
	const BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;

	put_top_pos = BoxAppVPara_GetAreaSelectCursorTopPos(vpara);
	catch_top_pos = catchPoke->areaTopPos;

	for(i=0; i<catchPoke->areaPokeCount; i++)
	{
		check_pos = put_top_pos + (catchPoke->areaPokePos[i]-catch_top_pos);

		ppp = BOXDAT_GetPokeDataAddress( vpara->boxData, BOXDAT_TRAYNUM_CURRENT, check_pos );
		if( PokePasoParaGet( ppp, ID_PARA_poke_exist, NULL ) )
		{
			return FALSE;
		}
	}

	return TRUE;
}


//------------------------------------------------------------------
/**
 * サブシーケンス：つかむ動作実行
 *
 * @param   wk				ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Tukamu( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_CMD_WAIT_CLOSEUP,
		SEQ_LASTPOKE_WARN,
		SEQ_CMD_WAIT,
	};

	switch( *seq ){
	case SEQ_INIT:
		if( BoxAppVPara_GetCursorArea( &wk->vpara ) == CURSOR_AREA_PARTY )
		{
			if( CheckPointLastPartyPoke( wk ) == FALSE )
			{
				Snd_SePlay( SOUND_POKE_CATCH );
				VParaSet_PokeCatch( wk, &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_POKE_CATCH );
				(*seq) = SEQ_CMD_WAIT_CLOSEUP;
			}
			// 残り１匹ではつかめない
			else
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_07 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_LASTPOKE_WARN;
			}
		}
		else
		{
			Snd_SePlay( SOUND_POKE_CATCH );
			VParaSet_PokeCatch( wk, &wk->vpara );
			BoxAppView_SetCommand( wk->vwk, CMD_POKE_CATCH );
			(*seq) = SEQ_CMD_WAIT;
		}
		break;


	case SEQ_CMD_WAIT_CLOSEUP:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			CursorPointPokeUpdate( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_PARTYICON_CLOSEUP );
			(*seq) = SEQ_CMD_WAIT;
		}
		break;

	case SEQ_LASTPOKE_WARN:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_CMD_WAIT;
		}
		break;

	case SEQ_CMD_WAIT:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SubSeqEnd(wk);
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：おく動作実行
 *
 * @param   wk		
 * @param   seq		
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Oku( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT = 0,
		SEQ_WAIT_PARTYICON_MOVE,
		SEQ_WAIT_ALL,
	};

	switch( *seq ){
	case SEQ_INIT:
		VParaSet_PokePut( wk, &wk->vpara );
		BoxAppView_SetCommand( wk->vwk, CMD_POKE_PUT );
		Snd_SePlay( SOUND_POKE_PUT );

		if(	(BoxAppVPara_GetCursorArea(&wk->vpara) == CURSOR_AREA_PARTY) )
		{
			u32 cpos, pcnt;

			cpos = BoxAppVPara_GetCursorPartyPos(&wk->vpara);
			pcnt = PokeParty_GetPokeCount(wk->partyData);

			if( cpos != (pcnt-1))
			{
				// 手持ちトレイでアイコンを正規の位置におかなかった場合、
				// CMD_POKE_PUT 完了後に正規位置まで運ぶ＆ステータス更新する必要がある
				(*seq) = SEQ_WAIT_PARTYICON_MOVE;
				CursorPointPokeUpdate( wk );
				break;
			}
		}
		(*seq) = SEQ_WAIT_ALL;
		break;


	case SEQ_WAIT_PARTYICON_MOVE:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			CursorPointPokeUpdate( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_PARTYLASTICON_CLOSEUP );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_WAIT_ALL;
		}
		break;

	case SEQ_WAIT_ALL:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SetBoxModifiedFlag( wk );
			SubSeqEnd(wk);
		}
		break;

	}
}


//------------------------------------------------------------------
/**
 * いれかえてはいけないケースをチェック
 *
 * @param   wk		ワークポインタ
 * @param   msgID	入れ替えられない時、そのエラーメッセージID
 *
 * @retval  BOOL	TRUEならいれかえてはいけない
 */
//------------------------------------------------------------------
static BOOL CheckSwapNGCase( BOXAPP_WORK* wk, u32* msgID)
{
	// 手持ちで戦える最後の１体を指している場合...
	if( CheckPointLastPartyPoke(wk) )
	{
		// タマゴと入れ替えるのはNG
		if( GetStatusPokeParam(&wk->vpara, ID_PARA_tamago_exist, NULL) )
		{
			*msgID = msg_boxmes_01_07;
			return TRUE;
		}

		// 瀕死のポケモンと入れ替えるのはNG
		if( BoxAppVPara_GetCursorCatchPokeFromPartyFlag( &wk->vpara ) )
		{
			if( GetStatusPokeParam(&wk->vpara, ID_PARA_hp, NULL) == 0 )
			{
				*msgID = msg_boxmes_01_07;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * サブシーケンス：いれかえる動作実行
 *
 * @param   wk		
 * @param   seq		
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Irekaeru( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT = 0,
		SEQ_MSG_KEYWAIT,
		SEQ_RET,
	};

	switch( *seq ){
	case SEQ_INIT:
		{
			u32 msgID;

			if( CheckSwapNGCase(wk, &msgID) )
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msgID );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_MSG_KEYWAIT;
			}
			else
			{
				VParaSet_PokeChange( wk, &wk->vpara );
				Snd_SePlay( SOUND_POKE_SWAP );
				BoxAppView_SetCommand( wk->vwk, CMD_POKE_CHANGE );
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
				(*seq) = SEQ_RET;
			}
		}
		break;

	case SEQ_MSG_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
		}
		break;

	case SEQ_RET:
		if(BoxAppView_WaitCommandAll( wk->vwk ))
		{
			SetBoxModifiedFlag( wk );
			SubSeqEnd(wk);
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * サブシーケンス：つれていく動作実行
 *
 * @param   wk				ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Tureteiku( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_PARTY_COUNT_CHECK,
		SEQ_ICONCATCH_WAIT,
		SEQ_PARTYTRAY_OPEN_WAIT,
		SEQ_CURSOR_GO_WAIT,
		SEQ_ICONPUT_WAIT,
		SEQ_PARTYTRAY_CLOSE_WAIT,
		SEQ_CURSOR_RET_WAIT,
		SEQ_WARNMSG_KEYWAIT,
		SEQ_RETURN,
	};

	switch( (*seq) ){
	case SEQ_PARTY_COUNT_CHECK:
		if( PokeParty_GetPokeCount( wk->partyData ) != TEMOTI_POKEMAX )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_SINGLE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_PARTYTRAY_OPEN );
				(*seq) = SEQ_PARTYTRAY_OPEN_WAIT;
			}
			else
			{
				Snd_SePlay( SOUND_POKE_CATCH );
				VParaSet_PokeCatch( wk, &wk->vpara );
				BoxAppView_SetCommand( wk->vwk, CMD_POKE_CATCH );
				(*seq) = SEQ_ICONCATCH_WAIT;
			}
		}
		else
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_06 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_WARNMSG_KEYWAIT;
		}
		break;

	case SEQ_ICONCATCH_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_POKE_CATCH ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_PARTYTRAY_OPEN );
			(*seq) = SEQ_PARTYTRAY_OPEN_WAIT;
		}
		break;

	case SEQ_PARTYTRAY_OPEN_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_PARTYTRAY_OPEN ) )
		{
			CursorPosSetForPartyBoxButtonOpen( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			(*seq) = SEQ_CURSOR_GO_WAIT;
		}
		break;

	case SEQ_CURSOR_GO_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_CURSOR_MOVE ) )
		{
			VParaSet_PokePut( wk, &wk->vpara );
			SetBoxModifiedFlag( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_POKE_PUT );
			(*seq) = SEQ_ICONPUT_WAIT;
		}
		break;

	case SEQ_ICONPUT_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_POKE_PUT ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_PARTYTRAY_CLOSE );
			(*seq) = SEQ_PARTYTRAY_CLOSE_WAIT;
		}
		break;

	case SEQ_PARTYTRAY_CLOSE_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_PARTYTRAY_CLOSE ) )
		{
			CursorPosSetForPartyBoxButtonClose( wk );
			BoxAppView_SetCommand( wk->vwk, CMD_CURSOR_MOVE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_RETURN;
		}
		break;

	case SEQ_WARNMSG_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE)
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RETURN;
		}
		break;

	case SEQ_RETURN:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd(wk);
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：あずける動作実行
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Azukeru( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_SUBSEQ_RET,
		SEQ_MSG_BOXFULL_KEYWAIT,
		SEQ_MSG_LASTPOKE_KEYWAIT,
		SEQ_AZUKERU_CATCHPOKE,
		SEQ_AZUKERU_POINTPOKE,
		SEQ_RET,
	};

	switch( (*seq) ){
	case SEQ_INIT:
	// 手持ち最後の１体は預けられない
		if(	(BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE )
		&&	(CheckPointLastPartyPoke( wk ) == TRUE)
		){
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_07 );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_MSG_LASTPOKE_KEYWAIT;
		}
	// メールを持っているポケモンなども預けられない
		else
		{
			int msgID;

			if( CheckStatusPokeUnleavable( wk, &msgID ) )
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msgID );
				BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_MSG_LASTPOKE_KEYWAIT;
			}
			else
			{
				SelectTrayCtrl_Init( wk, wk->vpara.azukeruTrayNumber, msg_boxmes_01_20 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq) = SEQ_SUBSEQ_RET;
			}
		}
		break;

	case SEQ_SUBSEQ_RET:
		if( SelectTrayCtrl_Main(wk) == FALSE )
		{
			break;
		}

		if( wk->selectTrayWork.trayNumber == SELECT_TRAY_CANCEL )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_CLEAR );
			(*seq) = SEQ_RET;
			break;
		}

		wk->vpara.azukeruTrayNumber = wk->selectTrayWork.trayNumber;

		// つかんでるポケモンを預ける
		if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_SINGLE )
		{
			if( VParaSet_CatchPokeAzuke( wk, wk->selectTrayWork.trayNumber ) )
			{
				SetBoxModifiedFlag( wk );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_CLEAR );
				(*seq) = SEQ_AZUKERU_CATCHPOKE;
				break;
			}
		}
		// 指してるポケモンを預ける
		else
		{
			if( VParaSet_PointPokeAzuke( wk, wk->selectTrayWork.trayNumber ) )
			{
				SetBoxModifiedFlag( wk );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_CLEAR );
				(*seq) = SEQ_AZUKERU_POINTPOKE;
				break;
			}
		}
	// ボックスがいっぱいで預けられなかったらココにくる
		Snd_SePlay( SOUND_WARNING );
		VParaSet_MessageID( &wk->vpara, msg_boxmes_01_14 );
		BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
		(*seq) = SEQ_MSG_BOXFULL_KEYWAIT;
		break;

	case SEQ_MSG_BOXFULL_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE ){
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			SelectTrayCtrl_Continue( wk );
			(*seq) = SEQ_SUBSEQ_RET;
		}
		break;

	case SEQ_MSG_LASTPOKE_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
		}
		break;

	case SEQ_AZUKERU_CATCHPOKE:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_JUMPWIN_CLEAR ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_AZUKERU_CATCHPOKE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_RET;
		}
		break;

	case SEQ_AZUKERU_POINTPOKE:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_JUMPWIN_CLEAR ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_AZUKERU_POINTPOKE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_RET;
		}
		break;

	case SEQ_RET:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * 現在指している手持ちポケモンが、戦える最後の１体かどうかをチェック
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEだと最後の１体
 */
//------------------------------------------------------------------
static BOOL CheckPointLastPartyPoke( BOXAPP_WORK* wk )
{
	POKEMON_PARAM* pp;
	int i, c, members;
	BOOL fastmode;


	members = PokeParty_GetPokeCount( wk->partyData );
	for(i=0, c=0; i<members; i++)
	{
		pp = PokeParty_GetMemberPointer(wk->partyData, i);
		fastmode = PokeParaFastModeOn( pp );
		if( (PokeParaGet(pp, ID_PARA_tamago_exist, NULL) == FALSE)
		&&	(PokeParaGet(pp, ID_PARA_hp, NULL) != 0)
		){
			c++;
		}
		PokeParaFastModeOff( pp, fastmode );
		if(c >= 2)
		{
			return FALSE;
		}
	}

	if( GetPointPokeParam(&wk->vpara, ID_PARA_tamago_exist, NULL) )
	{
		return FALSE;
	}
	if( GetPointPokeParam(&wk->vpara, ID_PARA_hp, NULL) == 0 )
	{
		return FALSE;
	}


	return TRUE;
}

//------------------------------------------------------------------
/**
 * ポケモンを「にがす」ことが出来る状態かチェック
 *
 * @param   wk			[in] ワークポインタ
 * @param   msgID		[out] にがすことが出来ない時、警告メッセージのIDを入れる
 *
 * @retval  BOOL		TRUEだと「にがす」ことが出来る。FALSEだと出来ない。
 */
//------------------------------------------------------------------
static BOOL CheckReleasable( BOXAPP_WORK* wk, int* msgID )
{
	// タマゴは逃がせない
	if( GetStatusPokeParam( &wk->vpara, ID_PARA_tamago_exist, NULL ) )
	{
		*msgID = msg_boxmes_01_33;
		return FALSE;
	}

	// メールを持っていたら逃がせない
	{
		u16 item = BoxAppVPara_GetStatusPokeItemNumber(&wk->vpara);
		if( ItemMailCheck(BoxAppVPara_GetStatusPokeItemNumber(&wk->vpara)) )
		{
			*msgID = msg_boxmes_01_32;
			return FALSE;
		}
	}

	// ボールカプセルに入っていたら逃がせない
	if( GetStatusPokeParam( &wk->vpara, ID_PARA_cb_id, NULL ) != 0 )
	{
		*msgID = msg_boxmes_01_31;
		return FALSE;
	}


	// ポケモンをつかんでいない時
	if(BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_NONE)
	{
		// 手持ち最後の１体は逃がせない
		if(BoxAppVPara_GetCursorArea( &wk->vpara ) == CURSOR_AREA_PARTY)
		{
			if( CheckPointLastPartyPoke(wk) )
			{
				*msgID = msg_boxmes_01_07;
				return FALSE;
			}
		}
	}

	return TRUE;
}


//------------------------------------------------------------------
/**
 * サブシーケンス：にがす動作実行
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_OP_Nigasu( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_MENU_CTRL,
		SEQ_NIGASU,
		SEQ_WAIT_EFFECT,
		SEQ_MODOTTA_MSG,
		SEQ_NIGASHITA_MSG,
		SEQ_MSG_KEYWAIT,
		SEQ_NIGASU_END,
		SEQ_MSG_LASTPOKE_KEYWAIT,
		SEQ_RET,
	};

	enum {
		CATCHPOKE,
		TRAYPOKE,
		PARTYPOKE,
	};

	switch( (*seq) ){
	case SEQ_INIT:
		{
			int msgID;

			if( CheckReleasable(wk, &msgID) )
			{
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_03 );
				BoxMenu_SetYesNoMenu( &(wk->vpara), 1 );
				BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
				(*seq) = SEQ_MENU_CTRL;
			}
			else
			{
				Snd_SePlay( SOUND_WARNING );
				VParaSet_MessageID( &wk->vpara, msgID );
				BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq) = SEQ_MSG_LASTPOKE_KEYWAIT;
			}
		}
		break;

	case SEQ_MENU_CTRL:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		switch( BoxMenu_Ctrl( &(wk->vpara) ) ){
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_NO:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
			break;

		case BOXMENU_YES:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_NIGASU;
			break;
		}
		break;

	case SEQ_NIGASU:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			// 単語バッファにポケモン名をセットしておく
			WORDSET_RegisterPokeNickName( wk->wordset, 0, BoxAppVPara_GetStatusPokePara( &wk->vpara ) );

			// ワザチェック開始
			StartReleaseWazaCheck( wk );

			// つかんでるポケモンの場合
			if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_SINGLE )
			{
				BoxAppView_SetCommand( wk->vwk, CMD_NIGASU_CATCHPOKE );
				/*
					パラメータ更新後は掴んでるフラグで識別できなくなるので
					どこのポケモンを逃がしたかワークに保存しておく
				*/
				wk->work = CATCHPOKE;
			}
			// 指してるポケモンの場合
			else
			{
				if( BoxAppVPara_GetCursorArea( &wk->vpara ) == CURSOR_AREA_TRAY )
				{
					BoxAppView_SetCommand( wk->vwk, CMD_NIGASU_TRAYPOKE );
					wk->work = TRAYPOKE;
				}
				else
				{
					BoxAppView_SetCommand( wk->vwk, CMD_NIGASU_PARTYPOKE );
					wk->work = PARTYPOKE;
				}
			}
			(*seq) = SEQ_WAIT_EFFECT;
		}
		break;

	case SEQ_WAIT_EFFECT:
		// ワザチェックが終わらないと逃がすエフェクトも終わらないので
		// エフェクトだけ待てば良い
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			if( BoxApp_ReleaseWazaCheckOK( wk ) )
			{
				if( BoxAppVPara_GetCursorCatchPokeFlag( &wk->vpara ) == CURSOR_CATCH_SINGLE )
				{
					VParaSet_CatchPokeNigasu( wk );
				}
				else
				{
					VParaSet_PointPokeNigasu( wk );
				}
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_04 );
				(*seq) = SEQ_NIGASHITA_MSG;
			}
			else
			{
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_34 );
				(*seq) = SEQ_MODOTTA_MSG;
			}
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
		}
		break;

	case SEQ_NIGASHITA_MSG:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A | PAD_BUTTON_B ) )
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_05 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_MSG_KEYWAIT;
		}
		break;

	case SEQ_MODOTTA_MSG:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A | PAD_BUTTON_B ) )
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_35 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_MSG_KEYWAIT;
		}
		break;

	case SEQ_MSG_KEYWAIT:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A | PAD_BUTTON_B ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_NIGASU_END;
		}
		break;

	case SEQ_NIGASU_END:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			if( BoxApp_ReleaseWazaCheckOK(wk) )
			{
				if( wk->work == PARTYPOKE )
				{
					BoxAppView_SetCommand( wk->vwk, CMD_PARTYICON_CLOSEUP );
				}
				SetBoxModifiedFlag( wk );
			}
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_RET;
		}
		break;

	case SEQ_MSG_LASTPOKE_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE )
		{
			break;
		}
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
		}
		break;


	case SEQ_RET:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//=====================================================================================
// 逃がせるかどうかワザチェック（調べる量が多いのでタスクを回して少しづつ調べる）
//=====================================================================================

//------------------------------------------------------------------
/**
 * ワザチェック開始
 *
 * @param   mainWk		
 *
 */
//------------------------------------------------------------------
static void StartReleaseWazaCheck( BOXAPP_WORK* mainWk )
{
	RELEASE_WAZACHECK_WORK*  wk = &(mainWk->wazaCheckWork);
	int i, cnt;

	wk->targetPoke = mainWk->vpara.statusPoke.poke_data;

	for(i=0, cnt=0; i<NIGASU_CHECKWAZA_MAX; i++)
	{
		wk->target_waza_flag[i] = PokeHaveWaza(wk->targetPoke, NigasuCheckWazaTable[i]);
		if( wk->target_waza_flag[i] )
		{
			cnt++;
		}
	}
	// 逃がそうとしているポケモンが対象ワザを持っていないのであればチェックする必要なし
	if( cnt == 0 )
	{
		wk->done = TRUE;
		wk->ok = TRUE;
		return;
	}
	else
	{
		wk->done = FALSE;
		wk->ok = FALSE;
		wk->tray = 0;
		wk->pos = 0;
		wk->boxData = mainWk->boxData;
		wk->partyData = mainWk->partyData;
		wk->pokeCatchFlag = (BoxAppVPara_GetCursorCatchPokeFlag( &mainWk->vpara ) != CURSOR_CATCH_NONE);

		for(i=0; i<NIGASU_CHECKWAZA_MAX; i++)
		{
			wk->count[i] = 0;
		}

		TCB_Add( ReleaseWazaCheckTask, wk, 0 );
	}
}
//------------------------------------------------------------------
/**
 * ワザチェックタスク本体
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ReleaseWazaCheckTask( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		TRAY_CHECKPOKE_UNIT = 15,	///< １フレームにこれだけのポケモンを調べる
	};

	RELEASE_WAZACHECK_WORK* wk = wk_adrs;
	POKEMON_PASO_PARAM* ppp;
	int i, w;

	// ボックス全調べ
	if( wk->tray < BOX_MAX_TRAY )
	{
		int max = wk->pos + TRAY_CHECKPOKE_UNIT;

		if( max > BOX_MAX_POS )
		{
			max = BOX_MAX_POS;
		}

		for(i=wk->pos; i<max; i++)
		{
			ppp = BOXDAT_GetPokeDataAddress( wk->boxData, wk->tray, i );
			if( PokePasoParaGet( ppp, ID_PARA_poke_exist, NULL ) )
			{
				for(w=0; w<NIGASU_CHECKWAZA_MAX; w++)
				{
					if( PokeHaveWaza(ppp, NigasuCheckWazaTable[w]) )
					{
						wk->count[w]++;
					}
				}
			}
		}

		if( max == BOX_MAX_POS )
		{
			wk->pos = 0;
			wk->tray++;
		}
		else
		{
			wk->pos = max;
		}
	}
	// 手持ち＆つかみポケ調べ
	else
	{
		int max = PokeParty_GetPokeCount( wk->partyData );
		for(i=0; i<max; i++)
		{
			ppp = (POKEMON_PASO_PARAM*)PokeParty_GetMemberPointer( wk->partyData, i );
			for(w=0; w<NIGASU_CHECKWAZA_MAX; w++)
			{
				if( PokeHaveWaza(ppp, NigasuCheckWazaTable[w]) )
				{
					wk->count[w]++;
				}
			}
		}
		if( wk->pokeCatchFlag )
		{
			for(w=0; w<NIGASU_CHECKWAZA_MAX; w++)
			{
				if( PokeHaveWaza(wk->targetPoke, NigasuCheckWazaTable[w]) )
				{
					wk->count[w]++;
				}
			}
		}

		// 対象ワザを覚えているポケモンが１体、かつターゲットがそのワザを覚えているなら逃がせない
		wk->ok = TRUE;
		for(w=0; w<NIGASU_CHECKWAZA_MAX; w++)
		{
			if( (wk->count[w] == 1) && (wk->target_waza_flag[w] == TRUE) )
			{
				wk->ok = FALSE;
				break;
			}
		}

		wk->done = TRUE;
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------------------
/**
 * ポケモンが指定ワザを覚えているかチェック
 *
 * @param   ppp		
 * @param   waza		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL PokeHaveWaza( POKEMON_PASO_PARAM* ppp, u16 waza )
{
	BOOL  ret, fastMode;

	ret = FALSE;
	fastMode = PokePasoParaFastModeOn( ppp );

	if( PokePasoParaGet( ppp, ID_PARA_tamago_exist, NULL ) == FALSE )
	{
		int i;
		for(i=0; i<4; i++)
		{
			if( PokePasoParaGet( ppp, ID_PARA_waza1+i, NULL ) == waza )
			{
				ret = TRUE;
				break;
			}
		}
	}

	PokePasoParaFastModeOff( ppp, fastMode );
	return ret;
}


//------------------------------------------------------------------
/**
 * ワザチェックが終わったか判定
 *
 * @param   mainWk		
 *
 * @retval  BOOL		TRUEなら終わった
 */
//------------------------------------------------------------------
BOOL BoxApp_ReleaseWazaCheckDone( const BOXAPP_WORK* mainWk )
{
	const RELEASE_WAZACHECK_WORK*  wk = &(mainWk->wazaCheckWork);
	return wk->done;
}

//------------------------------------------------------------------
/**
 * ワザチェックの結果、逃がしても良いポケモンか判定
 *
 * @param   mainWk		
 *
 * @retval  BOOL		TRUEなら逃がしても良い
 */
//------------------------------------------------------------------
BOOL BoxApp_ReleaseWazaCheckOK( const BOXAPP_WORK* mainWk )
{
	const RELEASE_WAZACHECK_WORK*  wk = &(mainWk->wazaCheckWork);
	if( wk->done )
	{
		return wk->ok;
	}
	return FALSE;
}







//------------------------------------------------------------------
/**
 * サブシーケンス：ボックスの名前入力画面へ移行～復帰
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SubSeq_Connect_InputTrayName( BOXAPP_WORK* wk, u32* seq )
{
	switch( (*seq) ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_FADEOUT );
		(*seq)++;
		break;
	case 1:
		if( BoxAppView_WaitCommand(wk->vwk, CMD_FADEOUT) )
		{
			BoxAppView_End( wk->vwk );
			sys_DeleteHeap( HEAPID_BOX_VIEW );

			BOXDAT_GetBoxName( wk->boxData, BOXDAT_GetCureentTrayNumber(wk->boxData), wk->nameinParam->strbuf );
			wk->subProc = PROC_Create( &NameInProcData, wk->nameinParam, HEAPID_BOX_SYSTEM );
			(*seq)++;
		}
		break;
	case 2:
		if( ProcMain( wk->subProc ) )
		{
			u32 current = BOXDAT_GetCureentTrayNumber( wk->boxData );

			PROC_Delete( wk->subProc );

			// ボックスデータ更新→描画パラメータ更新→画面構築の順に
			sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BOX_VIEW, HEAPSIZE_VIEW );
			BOXDAT_SetBoxName( wk->boxData, current, wk->nameinParam->strbuf );
			SetTrayStatus( wk->boxData, &wk->vpara.tray );
			BoxAppView_Init( &(wk->vwk), &wk->vpara, wk );
			SubSeqSet( wk, SubSeq_RestartBox );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモンステータス画面へ移行～復帰
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
static void SubSeq_Connect_PokemonStatus( BOXAPP_WORK* wk, u32* seq )
{
	switch( (*seq) ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_FADEOUT );
		(*seq)++;
		break;
	case 1:
		if( BoxAppView_WaitCommand(wk->vwk, CMD_FADEOUT) )
		{
			BoxAppView_End( wk->vwk );
			sys_DeleteHeap( HEAPID_BOX_VIEW );
			SetPokemonStatusScheneParam( wk );
			wk->subProc = PROC_Create( &PokeStatusProcData, &(wk->statusParam), HEAPID_BOX_SYSTEM );
			(*seq)++;
		}
		break;
	case 2:
		if( ProcMain( wk->subProc ) )
		{
			u32 current = BOXDAT_GetCureentTrayNumber( wk->boxData );

			PROC_Delete( wk->subProc );

			// ボックスデータ更新→描画パラメータ更新→画面構築の順に
			sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BOX_VIEW, HEAPSIZE_VIEW );

			if( BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) == CURSOR_CATCH_NONE )
			{
				UpdateCursorPosByStatusScene( &(wk->vpara), wk );
			}

			BoxAppView_Init( &(wk->vwk), &wk->vpara, wk );
			SubSeqSet( wk, SubSeq_RestartBox );

			SetBoxModifiedFlag( wk );
		}
	}
}
//------------------------------------------------------------------
/**
 * ポケモンステータス画面からの復帰時、直前まで見ていたポケモンに
 * カーソル位置を合わせる
 *
 * @param   vpara		
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void UpdateCursorPosByStatusScene( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk )
{
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	switch( cursor->area ){
	case CURSOR_AREA_TRAY:
		cursor->tray_pos = wk->statusParam.pos;
		cursor->tray_xpos = cursor->tray_pos % BOX_MAX_COLUMN;
		cursor->tray_ypos = cursor->tray_pos / BOX_MAX_COLUMN;
		break;

	case CURSOR_AREA_PARTY:
		cursor->partytray_pos = wk->statusParam.pos;
		break;

	default:
		return;
	}

	CursorPointPokeUpdate( wk );
}




//------------------------------------------------------------------
/**
 * サブシーケンス：バッグ画面へ移行～復帰
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubSeq_Connect_Bag( BOXAPP_WORK* wk, u32 *seq )
{
	FS_EXTERN_OVERLAY(fld_bag);

	static const u8  bag_enable_pockets[] = {
		BAG_POKE_NORMAL, BAG_POKE_DRUG, BAG_POKE_BALL, BAG_POKE_WAZA,
		BAG_POKE_NUTS, BAG_POKE_BATTLE, BAG_POKE_EVENT, 0xff
	};
	static u32  select_itemno;


	switch( (*seq) ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_FADEOUT );
		(*seq)++;
		break;
	case 1:
		if( BoxAppView_WaitCommand(wk->vwk, CMD_FADEOUT) )
		{
			MYITEM*  myItem;

			BoxAppView_End( wk->vwk );
			sys_DeleteHeap( HEAPID_BOX_VIEW );

			myItem = SaveData_GetMyItem( wk->saveData );
			wk->subProcWork = MyItem_MakeBagData( myItem, bag_enable_pockets, HEAPID_BOX_SYSTEM );
			BAG_SysDataSet( wk->subProcWork, wk->saveData, BAG_MODE_ITEMSET, NULL );

			Overlay_Load( FS_OVERLAY_ID(fld_bag), OVERLAY_LOAD_NOT_SYNCHRONIZE);
			wk->subProc = PROC_Create( &BagProcData, wk->subProcWork, HEAPID_BOX_SYSTEM );
			(*seq)++;
		}
		break;
	case 2:
		if( ProcMain( wk->subProc ) )
		{
			select_itemno = BagSysReturnItemGet( (BAG_DATA*)(wk->subProcWork) );

			PROC_Delete( wk->subProc );
			sys_FreeMemoryEz( wk->subProcWork );
			Overlay_UnloadID( FS_OVERLAY_ID(fld_bag) );

			if( select_itemno != ITEM_DUMMY_ID )
			{
				MyItem_SubItem( SaveData_GetMyItem(wk->saveData), select_itemno, 1, HEAPID_BOX_SYSTEM );
				VParaSet_StatusPokeItemNumber( &wk->vpara, select_itemno, wk );
				SetBoxModifiedFlag( wk );
			}

			// ボックスデータ更新→描画パラメータ更新→画面構築の順に
			sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BOX_VIEW, HEAPSIZE_VIEW );
			BoxAppView_Init( &(wk->vwk), &wk->vpara, wk );
			BoxAppView_SetCommand( wk->vwk, CMD_INIT );
			(*seq)++;
		}
		break;
	case 3:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_INIT ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_FADEIN );
			(*seq)++;
		}
		break;
	case 4:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_FADEIN ) )
		{
			if( select_itemno == ITEM_DUMMY_ID )
			{
				SubSeqEnd( wk );
			}
			else
			{
				WORDSET_RegisterItemName( wk->wordset, 0, select_itemno );
				VParaSet_MessageID( &wk->vpara, msg_boxmes_01_17 );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
				(*seq)++;
			}
		}
		break;
	case 5:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) )
		{
			if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
			{
				Snd_SePlay( SOUND_DECIDE );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq)++;
			}
		}
		break;
	case 6:
		if( BoxAppView_WaitCommandAll(wk->vwk) )
		{
			SubSeqEnd(wk);
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモンのアイテムをバッグに戻す（せいりモード）
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubSeq_Restore_Item( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_CTRL_MENU,
		SEQ_RESTORE,
		SEQ_WAIT_STATUS_UPDATE,
		SEQ_WAIT_KEY,
		SEQ_RET,
	};

	static u32 itemno;

	switch( *seq ){
	case SEQ_INIT:
		itemno = BoxAppVPara_GetStatusPokeItemNumber( &wk->vpara );
		if( ItemMailCheck(itemno) )
		{
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_25 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_WAIT_KEY;
		}
		else
		{
			WORDSET_RegisterItemName( wk->wordset, 0, itemno );
			BoxMenu_SetYesNoMenu( &(wk->vpara), 0 );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_24 );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_CTRL_MENU;
		}
		break;

	case SEQ_CTRL_MENU:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		switch( BoxMenu_Ctrl( &(wk->vpara) ) ){
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_NO:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
			break;

		case BOXMENU_YES:
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_CLEAR );
			(*seq) = SEQ_RESTORE;
			break;
		}
		break;

	case SEQ_RESTORE:
		if( MyItem_AddItem( SaveData_GetMyItem(wk->saveData), itemno, 1, HEAPID_BOX_SYSTEM ) )
		{
			VParaSet_StatusPokeItemNumber( &wk->vpara, ITEM_DUMMY_ID, wk );
			BoxAppView_SetCommand( wk->vwk, CMD_ITEM_POKE_UPDATE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );

			*seq = SEQ_WAIT_STATUS_UPDATE;
		}
		else
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_15 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );

			*seq = SEQ_WAIT_KEY;
		}
		break;

	case SEQ_WAIT_STATUS_UPDATE:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_16 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			*seq = SEQ_WAIT_KEY;
		}
		break;

	case SEQ_WAIT_KEY:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) )
		{
			if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
			{
				Snd_SePlay( SOUND_DECIDE );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq) = SEQ_RET;
			}
		}
		break;

	case SEQ_RET:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモンのアイテムをバッグに戻す（どうぐせいりモード）
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubSeq_ItemMode_Restore( BOXAPP_WORK* wk, u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_CTRL_MENU,
		SEQ_RESTORE,
		SEQ_WAIT_ITEMICON_DISAPPEAR_POKE,
		SEQ_DISP_RESULT_MESSAGE,
		SEQ_WAIT_KEY,
		SEQ_RET,
	};

	static u32 itemno;

	switch( *seq ){
	case SEQ_INIT:
		itemno = BoxAppVPara_GetInfoItemNumber( &wk->vpara );
		if( ItemMailCheck(itemno) )
		{
			Snd_SePlay( SOUND_WARNING );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_25 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			(*seq) = SEQ_WAIT_KEY;
		}
		else
		{
			WORDSET_RegisterItemName( wk->wordset, 0, itemno );
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_28 );
			BoxMenu_SetYesNoMenu( &(wk->vpara), 0 );
			BoxAppView_SetCommand( wk->vwk, CMD_MENU_DISP );
			(*seq) = SEQ_CTRL_MENU;
		}
		break;

	case SEQ_CTRL_MENU:
		if( BoxAppView_WaitCommandAll( wk->vwk ) == FALSE )
		{
			break;
		}
		switch( BoxMenu_Ctrl( &(wk->vpara) ) ){
		case BOXMENU_CTRL_MOVE:
			BoxAppView_SetCommand( wk->vwk, CMD_MENUCURSOR_UPDATE );
			break;
		case BOXMENU_CTRL_CANCEL:
		case BOXMENU_NO:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RET;
			break;

		case BOXMENU_YES:
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
			(*seq) = SEQ_RESTORE;
			break;
		}
		break;

	case SEQ_RESTORE:
		if( MyItem_AddItem( SaveData_GetMyItem(wk->saveData), itemno, 1, HEAPID_BOX_SYSTEM) )
		{
			if( BoxAppVPara_GetCatchItemNumber(&wk->vpara) != ITEM_DUMMY_ID )
			{
				VParaSet_ClearCatchItem( &wk->vpara );
				*seq = SEQ_DISP_RESULT_MESSAGE;
			}
			else
			{
				VParaSet_StatusPokeItemNumber( &wk->vpara, ITEM_DUMMY_ID, wk );
				*seq = SEQ_WAIT_ITEMICON_DISAPPEAR_POKE;
			}
			BoxAppView_SetCommand( wk->vwk, CMD_ITEMICON_RESTORE );
		}
		else
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_15 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			*seq = SEQ_WAIT_KEY;
		}
		break;

	case SEQ_WAIT_ITEMICON_DISAPPEAR_POKE:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_ITEMICON_RESTORE ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_ITEM_POKE_UPDATE );
			BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
			(*seq) = SEQ_DISP_RESULT_MESSAGE;
		}
		break;

	case SEQ_DISP_RESULT_MESSAGE:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			VParaSet_MessageID( &wk->vpara, msg_boxmes_01_29 );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			*seq = SEQ_WAIT_KEY;
		}
		break;

	case SEQ_WAIT_KEY:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) )
		{
			if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) )
			{
				Snd_SePlay( SOUND_DECIDE );
				BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
				(*seq) = SEQ_RET;
			}
		}
		break;

	case SEQ_RET:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}



//------------------------------------------------------------------
/**
 * サブシーケンス：アイテムの説明表示
 *
 * @param   wk		ワークポインタ
 * @param   seq		シーケンス
 *
 */
//------------------------------------------------------------------
static void SubSeq_ItemInfo( BOXAPP_WORK* wk, u32* seq )
{
	switch( *seq ){
	case 0:
		BoxAppView_SetCommand( wk->vwk, CMD_MSG_CLEAR );
		(*seq)++;
		break;
	case 1:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_CLEAR ) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_ITEMINFO_DISP );
			(*seq)++;
		}
		break;
	case 2:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_ITEMINFO_DISP ) )
		{
			(*seq)++;
		}
		break;
	case 3:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_PLUS_KEY_MASK) )
		{
			BoxAppView_SetCommand( wk->vwk, CMD_ITEMINFO_CLEAR );
			(*seq)++;
		}
		break;
	case 4:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_ITEMINFO_CLEAR ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//======================================================================================================
// トレイ選択コントロール関連
//======================================================================================================

//------------------------------------------------------------------
/**
 * トレイ選択コントロール初期化
 *
 * @param   wk					ワークポインタ
 * @param   init_tray_num		初期表示トレイナンバー
 * @param   msg_id				選択時に表示するメッセージID
 *
 */
//------------------------------------------------------------------
static void SelectTrayCtrl_Init( BOXAPP_WORK* wk, u32 init_tray_num, u32 msg_id )
{
	wk->selectTrayWork.seq = 0;
	wk->selectTrayWork.trayNumber = init_tray_num;
	wk->selectTrayWork.msgID = msg_id;
	wk->selectTrayWork.continue_flag = FALSE;
}

static void SelectTrayCtrl_Continue( BOXAPP_WORK* wk )
{
	wk->selectTrayWork.seq = 0;
	wk->selectTrayWork.continue_flag = TRUE;
}

//------------------------------------------------------------------
/**
 * トレイ選択処理メイン
 *
 * @param   wk		ワークポインタ
 * @param   seq		関数内シーケンスナンバとして利用できる変数のアドレス
 *
 * 開始時、wk->selectBox に入ったナンバーを初期表示ボックスとする。
 * 終了時、選択されたボックスナンバーを同じく wk->selectBox に入れる。
 * Ｂキャンセルされた時は、定数 SELECT_TRAY_CANCEL が入る。
 */
//------------------------------------------------------------------
static BOOL SelectTrayCtrl_Main( BOXAPP_WORK* wk )
{
	enum {
		SEQ_JUMPWIN_DISP,
		SEQ_MSG_DISP,
		SEQ_MSG_DISP_WAIT,
		SEQ_KEYWAIT,
		SEQ_TRAYCHANGE_RETURN,
		SEQ_RETURN,
	};

	SELECT_TRAY_WORK*  subwk = &(wk->selectTrayWork);

	switch( subwk->seq ){
	case SEQ_JUMPWIN_DISP:
		if( subwk->continue_flag == TRUE )
		{
			subwk->seq = SEQ_MSG_DISP;
			break;
		}

		// あり得ないハズだが一応
		if( subwk->trayNumber == SELECT_TRAY_CANCEL ){
			subwk->trayNumber = 0;
		}
		VParaSet_JumpWin( &wk->vpara, subwk->trayNumber );
		BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_DISP );
		subwk->seq = SEQ_MSG_DISP;
		break;

	case SEQ_MSG_DISP:
		if( BoxAppView_WaitCommand(wk->vwk, CMD_JUMPWIN_DISP) )
		{
			VParaSet_MessageID( &wk->vpara, subwk->msgID );
			BoxAppView_SetCommand( wk->vwk, CMD_MSG_DISP );
			subwk->seq = SEQ_MSG_DISP_WAIT;
		}
		break;

	case SEQ_MSG_DISP_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_MSG_DISP ) == FALSE )
		{
			break;
		}
		subwk->seq = SEQ_KEYWAIT;

		/* fallthru */

	case SEQ_KEYWAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_JUMPWIN_UPDATE ) == FALSE )
		{
			break;
		}

		if( sys.trg & (PAD_KEY_LEFT|PAD_BUTTON_L) )
		{
			subwk->trayNumber--;
			if( subwk->trayNumber < 0 )
			{
				subwk->trayNumber = BOX_MAX_TRAY-1;
			}
			VParaSet_JumpWin( &wk->vpara, subwk->trayNumber );
			BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_UPDATE );
			break;
		}
		if( sys.trg & (PAD_KEY_RIGHT|PAD_BUTTON_R) )
		{
			if( ++(subwk->trayNumber) >= BOX_MAX_TRAY )
			{
				subwk->trayNumber = 0;
			}
			VParaSet_JumpWin( &wk->vpara, subwk->trayNumber );
			BoxAppView_SetCommand( wk->vwk, CMD_JUMPWIN_UPDATE );
			break;
		}

		if( sys.trg & PAD_BUTTON_A )
		{
			Snd_SePlay( SOUND_DECIDE );
			return TRUE;
		}

		if( sys.trg & PAD_BUTTON_B )
		{
			Snd_SePlay( SOUND_CANCEL );
			subwk->trayNumber = SELECT_TRAY_CANCEL;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//======================================================================================================
// サブ画面操作関連
//======================================================================================================

static int calc_reelmove_vector( int* next, int now, u32 max )
{
	int diff_fwd, diff_back;

	diff_fwd = (*next) - now;
	if( diff_fwd < 0 ){ diff_fwd += max; }

	diff_back = now - (*next);
	if( diff_back < 0 ){ diff_back += max; }

	if( diff_fwd <= diff_back )
	{
		return diff_fwd;
	}
	else
	{
		return -diff_back;
	}
}

//------------------------------------------------------------------
/**
 * カレントトレイ切り替え
 *
 * @param   wk		
 * @param   seq		
 *
 */
//------------------------------------------------------------------
static void SubSeq_ChangeTray( BOXAPP_WORK* wk, u32* seq )
{
	switch( *seq ){
	case 0:
		BOXDAT_SetCureentTrayNumber( wk->boxData, BoxAppVPara_GetTrayBoxNumber(&wk->vpara) );
		CursorPointPokeUpdate( wk );
		BoxAppView_SetCommand( wk->vwk, CMD_TRAY_CHANGE );
		(*seq)++;
		break;

	case 1:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_TRAY_CHANGE ) )
		{
			if( (BoxAppVPara_GetCursorArea(&wk->vpara) == CURSOR_AREA_TRAY)
			&&	(BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) == CURSOR_CATCH_NONE)
			){
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
				(*seq)++;
			}
			else
			{
				SubSeqEnd( wk );
			}
		}
		break;

	case 2:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_STATUS_UPDATE ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * サブLCDでのトレイ選択モード
 *
 * @param   wk		
 * @param   seq		
 *
 */
//------------------------------------------------------------------
static void SubSeq_TrayMode( BOXAPP_WORK* wk,  u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_TP_CTRL,
		SEQ_MOVEICON_WAIT,
		SEQ_SCROLL_WAIT,
		SEQ_WAIT_STATUS_UPDATE,
		SEQ_END,
	};

	switch( *seq ){
	case SEQ_INIT:
		Snd_SePlay( SOUND_SUB_BUTTON );
		VParaSet_SubLCDStae( &wk->vpara, SUBLCD_STATE_TRAY );
		VParaSet_SubLCDPos( &(wk->vpara), BoxAppVPara_GetTrayBoxNumber(&wk->vpara) );
		BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MODECHANGE );
		BoxApp_ReelCtrlInit( &(wk->reel), 0, 192, 56, 88 );
		wk->reel_move_flag = FALSE;
		wk->reel_release_flag = TRUE;
		(*seq) = SEQ_TP_CTRL;
		break;

	case SEQ_TP_CTRL:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_SUBLCD_MODECHANGE ) == FALSE){ break; }

		if( CheckButtonPush( wk ) )
		{
			if( wk->btn_id == BUTTONID_RIGHT )
			{
				if( BoxAppVPara_GetBoxMode(&wk->vpara) != BOX_MODE_ITEM )
				{
					SubSeqSet( wk, SubSeq_LimitMode );
				}
				else
				{
					Snd_SePlay( SOUND_DISABLE_BUTTON );
				}
				break;
			}
		}

		if( sys.trg & SUBLCD_CTRL_ESCAPE_KEYMASK )
		{
			Snd_SePlay( SOUND_DECIDE );
			VParaSet_SubLCDStae( &(wk->vpara), SUBLCD_STATE_NORMAL );
			VParaSet_SubLCDPos( &(wk->vpara), BoxAppVPara_GetTrayBoxNumber(&wk->vpara) );
			BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MODECHANGE );
			(*seq) = SEQ_END;
			break;
		}

		if( wk->reel_move_flag )
		{
			if( wk->reel_release_flag )
			{
				if( ++(wk->reel_timer) > 20 )
				{
					u32 pos = BoxAppVPara_GetSubLCDPos( &wk->vpara );

					VParaSet_CurrentTrayNumberSet( &wk->vpara, pos );
					BOXDAT_SetCureentTrayNumber( wk->boxData, pos );
					CursorPointPokeUpdate(wk);

					if( BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) == CURSOR_CATCH_NONE )
					{
						BoxAppView_SetCommand( wk->vwk, CMD_STATUS_CLEAR );
					}

					BoxAppView_SetCommand( wk->vwk, CMD_TRAY_CHANGE );

					wk->reel_move_flag = FALSE;
					wk->reel_timer = 0;

					(*seq) = SEQ_SCROLL_WAIT;
					break;
				}
			}
		}


		switch(BoxApp_ReelCtrlMain(&wk->reel)){
		case REEL_RESULT_START:
			wk->reel_pos = BoxAppVPara_GetSubLCDPos( &wk->vpara );
			wk->reel_move_flag = FALSE;
			wk->reel_prev_slide = 0;
			wk->reel_release_flag = FALSE;
//			OS_TPrintf("*** REEL START\n");
			break;

		case REEL_RESULT_MOVE:
			{
				int slide;

				slide = BoxApp_ReelCtrlGetMoveValue( &wk->reel );

				if( slide != wk->reel_prev_slide )
				{
					int move, pos;

					move = slide - wk->reel_prev_slide;
					pos = BoxAppVPara_GetSubLCDPos(&wk->vpara) + move;
//					OS_TPrintf("*** REEL MOVE  move:%d  pos:%d\n", move, pos);
					if( pos < 0 ){
						pos += BOX_MAX_TRAY;
					}else if( pos >= BOX_MAX_TRAY ){
						pos -= BOX_MAX_TRAY;
					}

					wk->reel_prev_slide = slide;

					VParaSet_SubLCDPos( &(wk->vpara), pos );
					VParaSet_SubLCDMove( &(wk->vpara), move );
					BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MOVEICON );
					Snd_SePlay( SOUND_SUB_MOVE_ICON );
					(*seq) = SEQ_MOVEICON_WAIT;
				}
			}
			break;
		case REEL_RESULT_RELEASE:
			{
				int trayNum, lcdPos;

				trayNum = BoxAppVPara_GetTrayBoxNumber(&wk->vpara);
				lcdPos = BoxAppVPara_GetSubLCDPos(&wk->vpara);

				wk->reel_move_flag = ( trayNum != lcdPos );
				wk->reel_timer = 0;
				wk->reel_release_flag = TRUE;
//				OS_TPrintf("*** REEL RELEASE\n");
			}
			break;
		}
		break;

	case SEQ_MOVEICON_WAIT:
		if( wk->reel_release_flag == FALSE )
		{
			if( BoxApp_ReelCtrlMain(&wk->reel) == REEL_RESULT_RELEASE )
			{
				int trayNum, lcdPos;

				trayNum = BoxAppVPara_GetTrayBoxNumber(&wk->vpara);
				lcdPos = BoxAppVPara_GetSubLCDPos(&wk->vpara);

				wk->reel_move_flag = ( trayNum != lcdPos );
				wk->reel_timer = 0;
				wk->reel_release_flag = TRUE;
//				OS_TPrintf("*** REEL RELEASE\n");
			}
		}
		if( BoxAppView_WaitCommand( wk->vwk, CMD_SUBLCD_MOVEICON ) )
		{
			(*seq) = SEQ_TP_CTRL;
		}
		break;

	case SEQ_SCROLL_WAIT:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_TRAY_CHANGE ) )
		{
			if( (BoxAppVPara_GetCursorCatchPokeFlag(&wk->vpara) == CURSOR_CATCH_NONE)
			&&	(BoxAppVPara_GetCursorPointPokeFlag(&wk->vpara))
			){
				BoxAppView_SetCommand( wk->vwk, CMD_STATUS_UPDATE );
				(*seq) = SEQ_WAIT_STATUS_UPDATE;
			}
			else
			{
				(*seq) = SEQ_TP_CTRL;
			}
		}
		break;

	case SEQ_WAIT_STATUS_UPDATE:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_STATUS_UPDATE ) )
		{
			(*seq) = SEQ_TP_CTRL;
		}
		break;

	case SEQ_END:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}

}

//------------------------------------------------------------------
/**
 * サブLCDでの絞り込みモード
 *
 * @param   wk		
 * @param   seq		
 *
 */
//------------------------------------------------------------------
static void SubSeq_LimitMode( BOXAPP_WORK* wk,  u32* seq )
{
	enum {
		SEQ_INIT,
		SEQ_TP_CTRL,
		SEQ_MOVEICON_WAIT,
		SEQ_END,
	};

	switch( *seq ){
	case SEQ_INIT:
		Snd_SePlay( SOUND_SUB_BUTTON );
		VParaSet_SubLCDStae( &wk->vpara, SUBLCD_STATE_MARK );
		VParaSet_SubLCDLimitPos( &(wk->vpara), 0 );
		VParaSet_SubLCDPos( &(wk->vpara), 0 );
		BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MODECHANGE );
		BoxApp_ReelCtrlInit( &(wk->reel), 255, 192, 56, 88 );
		wk->reel_move_flag = FALSE;
		wk->reel_release_flag = TRUE;
		(*seq) = SEQ_TP_CTRL;
		break;

	case SEQ_TP_CTRL:
		if( BoxAppView_WaitCommand( wk->vwk, CMD_SUBLCD_MODECHANGE ) == FALSE){ break; }

		if( CheckButtonPush( wk ) )
		{
			if( wk->btn_id == BUTTONID_LEFT )
			{
				SubSeqSet( wk, SubSeq_TrayMode);
				break;
			}
		}

		if( sys.trg & SUBLCD_CTRL_ESCAPE_KEYMASK )
		{
			Snd_SePlay( SOUND_DECIDE );
			VParaSet_SubLCDStae( &wk->vpara, SUBLCD_STATE_NORMAL );
			BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MODECHANGE );
			(*seq) = SEQ_END;
		}

		if( CheckLimitModeIconTouch( wk ) )
		{
			Snd_SePlay( SOUND_DECIDE );
			BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MARKICON_UPDATE );
			BoxAppView_SetCommand( wk->vwk, CMD_ICON_LIMITMODE_UPDATE );
			break;
		}

		switch(BoxApp_ReelCtrlMain(&wk->reel)){
		case REEL_RESULT_START:
//			wk->reel_pos = BoxAppVPara_GetSubLCDLimitPos(&(wk->vpara));
//			wk->reel_move_flag = FALSE;
			wk->reel_pos = BoxAppVPara_GetSubLCDPos( &wk->vpara );
			wk->reel_move_flag = FALSE;
			wk->reel_prev_slide = 0;
			wk->reel_release_flag = FALSE;
			break;
		case REEL_RESULT_MOVE:
			{
				int slide;

				slide = BoxApp_ReelCtrlGetMoveValue( &wk->reel );

				if( slide != wk->reel_prev_slide )
				{
					int move, pos;

					move = slide - wk->reel_prev_slide;
					pos = BoxAppVPara_GetSubLCDPos(&wk->vpara) + move;
					if( pos < 0 ){
						pos += LIMITMODE_ICON_MAX;
					}else if( pos >= LIMITMODE_ICON_MAX ){
						pos -= LIMITMODE_ICON_MAX;
					}

					wk->reel_prev_slide = slide;

					VParaSet_SubLCDPos( &(wk->vpara), pos );
					VParaSet_SubLCDLimitPos( &(wk->vpara), pos );
					VParaSet_SubLCDMove( &(wk->vpara), move );
					BoxAppView_SetCommand( wk->vwk, CMD_SUBLCD_MOVEICON );
					Snd_SePlay( SOUND_SUB_MOVE_ICON );
					(*seq) = SEQ_MOVEICON_WAIT;
				}
			}
			break;

		case REEL_RESULT_RELEASE:
			{
				int trayNum, lcdPos;

				trayNum = BoxAppVPara_GetTrayBoxNumber(&wk->vpara);
				lcdPos = BoxAppVPara_GetSubLCDPos(&wk->vpara);

				wk->reel_move_flag = ( trayNum != lcdPos );
				wk->reel_timer = 0;
				wk->reel_release_flag = TRUE;
			}
			break;
		}
		break;

	case SEQ_MOVEICON_WAIT:
		if( wk->reel_release_flag == FALSE )
		{
			if( BoxApp_ReelCtrlMain(&wk->reel) == REEL_RESULT_RELEASE )
			{
				int trayNum, lcdPos;

				trayNum = BoxAppVPara_GetTrayBoxNumber(&wk->vpara);
				lcdPos = BoxAppVPara_GetSubLCDPos(&wk->vpara);

				wk->reel_move_flag = ( trayNum != lcdPos );
				wk->reel_timer = 0;
				wk->reel_release_flag = TRUE;
			}
		}
		if( BoxAppView_WaitCommand( wk->vwk, CMD_SUBLCD_MOVEICON ) )
		{
			(*seq) = SEQ_TP_CTRL;
		}
		break;

	case SEQ_END:
		if( BoxAppView_WaitCommandAll( wk->vwk ) )
		{
			SubSeqEnd( wk );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * 絞り込みモードのアイコンがタッチされたかチェック
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEでタッチされた
 */
//------------------------------------------------------------------
static BOOL CheckLimitModeIconTouch( BOXAPP_WORK* wk )
{
	wk->touch_icon_id = LIMITMODE_ICON_MAX;

	BMN_Main( wk->icon_bmn );

	if( wk->touch_icon_id != LIMITMODE_ICON_MAX )
	{
		return TRUE;
	}

	return FALSE;
}
static void IconBmnCallBack( u32 btnID, u32 event, void* wk_adrs )
{
	BOXAPP_WORK* wk = (BOXAPP_WORK*)wk_adrs;

	if( wk->touch_icon_id == LIMITMODE_ICON_MAX )
	{
		if( event == BMN_EVENT_TOUCH )
		{
			u32 iconID = BoxAppVPara_GetSubLCDLimitPos( &wk->vpara );
			iconID += btnID;
			if( iconID >= LIMITMODE_ICON_MAX )
			{
				iconID -= LIMITMODE_ICON_MAX;
			}
			VParaSet_LimitModeBitFlag( &wk->vpara, iconID );
			wk->touch_icon_id = btnID;
		}
	}

}

//==============================================================================================================
//==============================================================================================================


//------------------------------------------------------------------
/**
 * ワーク構築：メイン
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void InitWork( BOXAPP_WORK* wk, BOX_PROC_PARAM* proc_param )
{
	wk->boxData = SaveData_GetBoxData( proc_param->savedata );
	wk->saveData = proc_param->savedata;
	wk->partyData = SaveData_GetTemotiPokemon( proc_param->savedata );
	wk->sysConfig = SaveData_GetConfig( proc_param->savedata );
	wk->procParam = proc_param;
	proc_param->modifiedFlag = FALSE;

	wk->msgman_box = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_boxmes_dat, HEAPID_BOX_SYSTEM );
	wk->msgman_poke = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_BOX_SYSTEM );
	wk->msgman_poke_character = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_chr_dat, HEAPID_BOX_SYSTEM );
	wk->msgman_speabi = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_tokusei_dat, HEAPID_BOX_SYSTEM );
	wk->wordset = WORDSET_Create(HEAPID_BOX_SYSTEM);
	wk->partyPokeWork = sys_AllocMemory( HEAPID_BOX_SYSTEM, PokemonParam_GetWorkSize() );
	GF_ASSERT(wk->wordset);

	wk->nameinParam = NameIn_ParamAllocMake( HEAPID_BOX_SYSTEM, NAMEIN_BOX, 0, BOX_TRAYNAME_MAXLEN, wk->sysConfig );

	if( proc_param->mode != BOX_MODE_COMPARE )
	{
		wk->bmn = BMN_Create( ButtonHitTbl, NELEMS(ButtonHitTbl), BmnCallBack, wk, HEAPID_BOX_SYSTEM );	
	}
	else
	{
		wk->bmn = BMN_Create( CompareButtonHitTbl, NELEMS(CompareButtonHitTbl), BmnCallBack, wk, HEAPID_BOX_SYSTEM );	
	}
	
	wk->icon_bmn = BMN_Create( IconHitTbl, NELEMS(IconHitTbl), IconBmnCallBack, wk, HEAPID_BOX_SYSTEM );

	wk->vpara.boxData = wk->boxData;
	wk->vpara.partyData = wk->partyData;

	wk->vpara.azukeruTrayNumber = 0;
	wk->vpara.catch_item = ITEM_DUMMY_ID;

	InitWork_system( &(wk->vpara.system), proc_param->mode );
	InitWork_statusPoke( &(wk->vpara.statusPoke) );
	InitWork_tray( wk->boxData, &(wk->vpara.tray) );
	InitWork_Compare( &(wk->vpara.compare) );

	InitWork_cursor( wk );
	InitWork_catchpoke( &(wk->vpara.catchPoke) );
	InitWork_SubLCD( &(wk->vpara.subLCD) );

}

//------------------------------------------------------------------
/**
 * ワーク破棄
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void DeleteWork( BOXAPP_WORK* wk )
{
	BMN_Delete( wk->icon_bmn );
	BMN_Delete( wk->bmn );

	if(wk->partyPokeWork)
	{
		sys_FreeMemoryEz(wk->partyPokeWork);
	}
	WORDSET_Delete( wk->wordset );
	MSGMAN_Delete( wk->msgman_box );
	MSGMAN_Delete( wk->msgman_poke );
	MSGMAN_Delete( wk->msgman_poke_character );
	MSGMAN_Delete( wk->msgman_speabi );

	NameIn_ParamDelete( wk->nameinParam );

	DeleteWork_statusPoke( &(wk->vpara.statusPoke) );
	DeleteWork_catchpoke( &(wk->vpara.catchPoke) );
	DeleteWork_tray( &(wk->vpara.tray) );
	DeleteWork_Compare( &(wk->vpara.compare) );

	sys_FreeMemoryEz( wk );

}

//------------------------------------------------------------------
/**
 * ワーク初期化：システムデータ
 *
 * @param   system		
 *
 */
//------------------------------------------------------------------
static void InitWork_system( BOXAPP_SYSTEM* system, int mode )
{
	system->boxMode = mode;				// ボックス動作モード（あずける・つれていく・せいり・どうぐ）
	system->expertModeFlag = FALSE;		// 慣れてる人モードフラグ
	system->limitModeBitFlag = 0;		// 絞り込みモードビットフラグ
}
//------------------------------------------------------------------
/**
 * ワーク初期化：カーソルデータ
 *
 * @param   system		
 * @param   cursor		
 *
 */
//------------------------------------------------------------------
static void InitWork_cursor( BOXAPP_WORK* wk )
{
	BOXAPP_VPARAM* vpara = &(wk->vpara);
	BOXAPP_CURSOR* cursor = &(vpara->cursor);

	VParaSet_CursorTrayPos( vpara, 0, 0 );

	cursor->partytray_pos = 0;
	cursor->partytray_prev_area = CURSOR_AREA_PARTY;

	switch( vpara->system.boxMode ){
	case BOX_MODE_AZUKERU:
		cursor->area = CURSOR_AREA_PARTY;
		break;
	case BOX_MODE_COMPARE:
		cursor->area = CURSOR_AREA_TRAY_TAB;
		break;
	default:
		cursor->area = CURSOR_AREA_TRAY;
	}

	cursor->poke_catch_flag = CURSOR_CATCH_NONE;

	CursorPointPokeUpdate( wk );
}
//------------------------------------------------------------------
/**
 * ワーク初期化：移動中ポケデータ
 *
 * @param   catchPoke		
 */
//------------------------------------------------------------------
static void InitWork_catchpoke( BOXAPP_CATCH_POKE* catchPoke )
{
	catchPoke->ppp = sys_AllocMemory( HEAPID_BOX_SYSTEM, BOX_MAX_POS * PokemonPasoParamSizeGet() );
	catchPoke->areaPokeCount = 0;
	catchPoke->fromPartyFlag = FALSE;
}
//------------------------------------------------------------------
/**
 * ワーク削除：移動中ポケデータ
 *
 * @param   catchPoke		
 *
 */
//------------------------------------------------------------------
static void DeleteWork_catchpoke( BOXAPP_CATCH_POKE* catchPoke )
{
	sys_FreeMemoryEz( catchPoke->ppp );
}


//------------------------------------------------------------------
/**
 * ワーク初期化：トレイデータ
 *
 * @param   box		
 * @param   tray		
 */
//------------------------------------------------------------------
static void InitWork_tray( BOX_DATA* box, BOXAPP_TRAY* tray )
{
	tray->number = BOXDAT_GetCureentTrayNumber( box );
	tray->name = STRBUF_Create(BOX_TRAYNAME_BUFSIZE, HEAPID_BOX_SYSTEM);
	SetTrayStatus( box, tray );
}
//------------------------------------------------------------------
/**
 * ワーク削除：トレイデータ
 *
 * @param   tray		
 *
 */
//------------------------------------------------------------------
static void DeleteWork_tray( BOXAPP_TRAY* tray )
{
	STRBUF_Delete( tray->name );
}



//------------------------------------------------------------------
/**
 * ワーク初期化：ステータス表示ポケモン用ワーク
 *
 * @param   statusPoke		
 *
 */
//------------------------------------------------------------------
static void InitWork_statusPoke( BOXAPP_STATUS_POKE* statusPoke )
{
	statusPoke->nickname = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_BOX_SYSTEM );
	statusPoke->monsname = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_BOX_SYSTEM );
	statusPoke->itemname = STRBUF_Create( BUFLEN_ITEM_NAME, HEAPID_BOX_SYSTEM );
	statusPoke->character = STRBUF_Create( BUFLEN_POKEMON_CHARACTER_NAME, HEAPID_BOX_SYSTEM );
	statusPoke->ability = STRBUF_Create( BUFLEN_POKEMON_ABILITY_NAME, HEAPID_BOX_SYSTEM );
}
//------------------------------------------------------------------
/**
 * ワーク削除：ステータス表示ポケモン用ワーク
 *
 * @param   statusPoke		
 *
 */
//------------------------------------------------------------------
static void DeleteWork_statusPoke( BOXAPP_STATUS_POKE* statusPoke )
{
	STRBUF_Delete(statusPoke->nickname);
	STRBUF_Delete(statusPoke->monsname);
	STRBUF_Delete(statusPoke->itemname);
	STRBUF_Delete(statusPoke->character);
	STRBUF_Delete(statusPoke->ability);
}


//------------------------------------------------------------------
/**
 * ワーク初期化：つよさくらべ用ワーク
 *
 * @param   compare		
 *
 */
//------------------------------------------------------------------
static void InitWork_Compare( BOXAPP_COMPARE* compare )
{
	int i;

	compare->updateSide = BOXAPP_COMPARE_SIDE_LEFT;
	compare->page = 0;
	compare->pageButtonPushFlag = FALSE;

	for(i=0; i<2; i++)
	{
		compare->updateSideFlag[i] = FALSE;
		compare->status[i].nickname  = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_BOX_SYSTEM );
		compare->status[i].character = STRBUF_Create( BUFLEN_POKEMON_CHARACTER_NAME, HEAPID_BOX_SYSTEM );
	}
}
//------------------------------------------------------------------
/**
 * ワーク削除：つよさくらべ用ワーク
 *
 * @param   compare		
 *
 */
//------------------------------------------------------------------
static void DeleteWork_Compare( BOXAPP_COMPARE* compare )
{
	int i;

	for(i=0; i<2; i++)
	{
		STRBUF_Delete( compare->status[i].nickname );
		STRBUF_Delete( compare->status[i].character );
	}
}







//------------------------------------------------------------------
/**
 * ワーク初期化：サブLCD状態
 *
 * @param   sub		
 *
 */
//------------------------------------------------------------------
static void InitWork_SubLCD( BOXAPP_SUBLCD* sub )
{
	sub->state = SUBLCD_STATE_NORMAL;
	sub->pos = 0;
	sub->limit_pos = 0;
	sub->move = 0;
}
//------------------------------------------------------------------
/**
 * トレイ関連描画パラメータを更新
 *
 * @param   box		
 * @param   tray		
 *
 */
//------------------------------------------------------------------
static void SetTrayStatus( const BOX_DATA* box, BOXAPP_TRAY* tray )
{
	tray->wallPaper = BOXDAT_GetWallPaperNumber( box, tray->number );
	BOXDAT_GetBoxName( box, tray->number, tray->name );
}
//------------------------------------------------------------------
/**
 * カレントの壁紙ナンバー更新
 *
 * @param   vpara		
 * @param   box			
 *
 */
//------------------------------------------------------------------
static void TrayCurrentWallPaperUpdate( BOXAPP_VPARAM* vpara, BOX_DATA* box )
{
	BOXAPP_TRAY*  tray = &(vpara->tray);
	tray->wallPaper = BOXDAT_GetWallPaperNumber( box, tray->number );
}



//------------------------------------------------------------------
/**
 * カーソル移動チェック
 *
 * @param   wk		
 *
 * @retval  BOOL		TRUEで移動あり
 */
//------------------------------------------------------------------
static BOOL CheckCursorMoveKeyInput( u32 keyflag, BOXAPP_WORK* wk )
{
	BOOL ret = FALSE;

	do{
		if( keyflag & PAD_KEY_LEFT )
		{
			ret = CursorPosMove( &(wk->vpara), -1,  0 );
			break;
		}

		if( keyflag & PAD_KEY_RIGHT )
		{
			ret = CursorPosMove( &(wk->vpara),  1,  0 );
			break;
		}

		if( keyflag & PAD_KEY_UP )
		{
			ret =  CursorPosMove( &(wk->vpara),  0, -1 );
			break;
		}

		if( keyflag & PAD_KEY_DOWN )
		{
			ret = CursorPosMove( &(wk->vpara),  0,  1 );
			break;
		}

	}while(0);

	if( ret == TRUE )
	{
		CursorPointPokeUpdate( wk );
	}

	return ret;
}

//------------------------------------------------------------------
/**
 * カーソル移動データ処理
 *
 * @param   vpara		
 * @param   x		Ｘ移動量
 * @param   y		Ｙ移動量
 *
 * @retval  BOOL		TRUEで移動あり
 */
//------------------------------------------------------------------
static BOOL CursorPosMove( BOXAPP_VPARAM* vpara, int x, int y )
{
	#define DecideButtonArea(x)	(((x) == (BOX_MAX_COLUMN-1))? CURSOR_AREA_EXIT_BUTTON : CURSOR_AREA_PARTY_BUTTON);

	BOXAPP_CURSOR* cursor = &vpara->cursor;

	switch( cursor->area ){
	case CURSOR_AREA_TRAY:
		if( x != 0)
		{
			int  xpos = cursor->tray_xpos += x;

			if( xpos < 0 )
			{
				xpos = BOX_MAX_COLUMN - 1;
			}
			else if( xpos >= BOX_MAX_COLUMN )
			{
				xpos = 0;
			}
			VParaSet_CursorTrayPos( vpara, xpos, cursor->tray_ypos );

			return TRUE;
		}
		else if( y != 0)
		{
			int ypos = cursor->tray_ypos + y;
			if( ypos < 0 )
			{
				ypos = 0;
				cursor->area = CURSOR_AREA_TRAY_TAB;
			}
			else if( ypos > TRAY_YPOS_MAX )
			{
				ypos = TRAY_YPOS_MAX;
				cursor->area = DecideButtonArea( cursor->tray_xpos );
			}
			VParaSet_CursorTrayPos( vpara, cursor->tray_xpos, ypos );
			return TRUE;
		}
		break;

	case CURSOR_AREA_TRAY_TAB:
		if( y > 0 )
		{
			cursor->area = CURSOR_AREA_TRAY;
			VParaSet_CursorTrayPos( vpara, cursor->tray_xpos, 0 );
			return TRUE;
		}
		else if( y < 0 )
		{
			cursor->area = DecideButtonArea( cursor->tray_xpos );
			return TRUE;
		}
		break;

	case CURSOR_AREA_EXIT_BUTTON:
		if( y < 0 )
		{
			cursor->area = CURSOR_AREA_TRAY;
			VParaSet_CursorTrayPos( vpara, cursor->tray_xpos, TRAY_YPOS_MAX );
			return TRUE;
		}
		else if( y > 0 )
		{
			cursor->area = CURSOR_AREA_TRAY_TAB;
			return TRUE;
		}
		else if( x != 0)
		{
			cursor->area = CURSOR_AREA_PARTY_BUTTON;
			return TRUE;
		}
		break;

	case CURSOR_AREA_PARTY_BUTTON:
		if( y < 0 )
		{
			cursor->area = CURSOR_AREA_TRAY;
			VParaSet_CursorTrayPos( vpara, cursor->tray_xpos, TRAY_YPOS_MAX );
			return TRUE;
		}
		if( y > 0 )
		{
			cursor->area = CURSOR_AREA_TRAY_TAB;
			return TRUE;
		}
		if( x != 0)
		{
			cursor->area = CURSOR_AREA_EXIT_BUTTON;
			return TRUE;
		}
		break;

	case CURSOR_AREA_PARTY:
		{
			u32  before_pos = cursor->partytray_pos;

			if( y < 0 )
			{
				if( before_pos == CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
				{
					cursor->partytray_pos = 5;
				}
				else
				{
					cursor->partytray_pos -= 2;
					if( cursor->partytray_pos < 0 )
					{
						cursor->partytray_pos = CURSOR_PARTYTRAY_CLOSEBUTTON_POS;
					}
				}
			}
			else if( y > 0 )
			{
				if( before_pos == CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
				{
					cursor->partytray_pos = 0;
				}
				else
				{
					cursor->partytray_pos += 2;
					if( cursor->partytray_pos >= CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
					{
						cursor->partytray_pos = CURSOR_PARTYTRAY_CLOSEBUTTON_POS;
					}
				}
			}
			else if( x < 0 )
			{
				if( before_pos & 1 )
				{
					cursor->partytray_pos -= 1;
				}
			}
			else if( x > 0 )
			{
				if( before_pos != CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
				{
					if( (before_pos & 1) == 0 )
					{
						cursor->partytray_pos += 1;
					}
				}
			}


			if( before_pos != cursor->partytray_pos )
			{
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;

	#undef DecideButtonArea
}
//------------------------------------------------------------------
/**
 * 範囲選択時のカーソル移動チェック
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int CheckCursorMoveKeyInput_AreaSelect( u32 keyflag, BOXAPP_WORK* wk )
{
	int ret = AREASELECT_RESULT_NONE;

	do{
		if( keyflag & PAD_KEY_LEFT )
		{
			ret = CursorPosMove_AreaSelect( &(wk->vpara), -1,  0 );
			break;
		}

		if( keyflag & PAD_KEY_RIGHT )
		{
			ret = CursorPosMove_AreaSelect( &(wk->vpara),  1,  0 );
			break;
		}

		if( keyflag & PAD_KEY_UP )
		{
			ret =  CursorPosMove_AreaSelect( &(wk->vpara),  0, -1 );
			break;
		}

		if( keyflag & PAD_KEY_DOWN )
		{
			ret = CursorPosMove_AreaSelect( &(wk->vpara),  0,  1 );
			break;
		}

		if( keyflag & PAD_BUTTON_L )
		{
			ret = AREASELECT_RESULT_SCROLL_LEFT;
			break;
		}

		if( keyflag & PAD_BUTTON_R )
		{
			ret = AREASELECT_RESULT_SCROLL_RIGHT;
			break;
		}

	}while(0);

	if( ret == AREASELECT_RESULT_UPDATE )
	{
		CursorPointPokeUpdate( wk );
	}

	return ret;
}
//------------------------------------------------------------------
/**
 * 範囲選択中のカーソル移動データ処理
 *
 * @param   vpara		
 * @param   x		Ｘ移動量
 * @param   y		Ｙ移動量
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int CursorPosMove_AreaSelect( BOXAPP_VPARAM* vpara, int x, int y )
{
	BOXAPP_CURSOR* cursor = &vpara->cursor;
	const BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;

	if( cursor->area == CURSOR_AREA_TRAY )
	{
		if( x != 0 )
		{
			int  xpos = cursor->tray_xpos + x;

			if( BoxAppVPara_GetCursorCatchPokeFlag(vpara) & CURSOR_CATCH_AREA_MASK )
			{
				int l_border, r_border;

				l_border = r_border = xpos;
				if(catchPoke->areaEndX > catchPoke->areaStartX){
					l_border -= (catchPoke->areaEndX - catchPoke->areaStartX);
				}else{
					r_border += (catchPoke->areaStartX - catchPoke->areaEndX);
				}

				if( l_border < 0 )
				{
					return AREASELECT_RESULT_SCROLL_LEFT;
				}
				if( r_border >= BOX_MAX_COLUMN )
				{
					return AREASELECT_RESULT_SCROLL_RIGHT;
				}
			}
			else
			{
				if( (xpos < 0) || (xpos >= BOX_MAX_COLUMN) )
				{
					return AREASELECT_RESULT_OVER;
				}
			}

			VParaSet_CursorTrayPos( vpara, xpos, cursor->tray_ypos );
			return AREASELECT_RESULT_UPDATE;
		}

		if( y != 0)
		{
			int ypos;

			ypos = cursor->tray_ypos + y;

			if( BoxAppVPara_GetCursorCatchPokeFlag(vpara) & CURSOR_CATCH_AREA_MASK )
			{
				int t_border, b_border;

				t_border = b_border = ypos;
				if(catchPoke->areaEndY > catchPoke->areaStartY){
					t_border -= (catchPoke->areaEndY - catchPoke->areaStartY);
				}else{
					b_border += (catchPoke->areaStartY - catchPoke->areaEndY);
				}

				if((t_border < 0)||(b_border >= BOX_MAX_RAW))
				{
					return AREASELECT_RESULT_OVER;
				}
			}
			else
			{
				if( (ypos < 0) || (ypos >= BOX_MAX_RAW ) )
				{
					return AREASELECT_RESULT_OVER;
				}
			}

			VParaSet_CursorTrayPos( vpara, cursor->tray_xpos, ypos );
			return AREASELECT_RESULT_UPDATE;
		}
	}

	GF_ASSERT(0);
	return AREASELECT_RESULT_NONE;
}

//------------------------------------------------------------------
/**
 * 手持ちポケモンボタンを押した時の移動先パラメータセット
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CursorPosSetForPartyBoxButtonOpen( BOXAPP_WORK* wk )
{
	BOXAPP_VPARAM* vpara = &wk->vpara;
	BOXAPP_CURSOR* cursor = &vpara->cursor;
	u32 cnt;

	// ポケモンをつかんでいるなら空きスペースへ
	if( BoxAppVPara_GetCursorCatchPokeFlag( vpara ) == CURSOR_CATCH_SINGLE )
	{
		cursor->partytray_pos = PokeParty_GetPokeCount( wk->partyData );

		// 空きが無ければ最後尾
		if( cursor->partytray_pos >= TEMOTI_POKEMAX )
		{
			cursor->partytray_pos = TEMOTI_POKEMAX - 1;
		}
	}
	// つかんでいないなら先頭へ
	else
	{
		cursor->partytray_pos = 0;
	}

	cursor->partytray_prev_area = cursor->area;
	cursor->area = CURSOR_AREA_PARTY;

	CursorPointPokeUpdate( wk );
}
//------------------------------------------------------------------
/**
 * 手持ちポケモントレイから抜ける時の移動先パラメータセット
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CursorPosSetForPartyBoxButtonClose( BOXAPP_WORK* wk )
{
	BOXAPP_CURSOR* cursor = &(wk->vpara.cursor);
	cursor->area = CURSOR_AREA_TRAY;
	if( cursor->partytray_prev_area != CURSOR_AREA_TRAY )
	{
		VParaSet_CursorTrayPos( &wk->vpara, 0, 0 );
	}
	CursorPointPokeUpdate( wk );
}

//------------------------------------------------------------------
/**
 * カーソル現在位置でステータス更新
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void CursorPointPokeUpdate( BOXAPP_WORK* wk )
{
	BOXAPP_VPARAM* vpara = &wk->vpara;
	BOXAPP_STATUS_POKE* stpoke = &vpara->statusPoke;
	BOXAPP_CURSOR* cursor = &vpara->cursor;
	u32 monsno;

	cursor->poke_point_flag = FALSE;

	switch( cursor->area ){
	case CURSOR_AREA_TRAY:
		cursor->point_poke = BOXDAT_GetPokeDataAddress( vpara->boxData, 
											BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos );
		break;

	case CURSOR_AREA_PARTY:
		if( cursor->partytray_pos < PokeParty_GetPokeCount( wk->partyData ) )
		{
			cursor->point_poke = PokeParty_GetMemberPointer( wk->partyData, cursor->partytray_pos );
		}
		else
		{
			cursor->point_poke = NULL;
		}
		break;

	case CURSOR_AREA_TRAY_TAB:
	case CURSOR_AREA_EXIT_BUTTON:
	case CURSOR_AREA_PARTY_BUTTON:
	default:
		cursor->point_poke = NULL;
		break;
	}



	if( cursor->point_poke )
	{
		if( PokePasoParaGet( cursor->point_poke, ID_PARA_poke_exist, NULL ) )
		{
			cursor->poke_point_flag = TRUE;
			if( !(BoxAppVPara_GetCursorCatchPokeFlag(vpara) & CUROSR_CATCH_STATUS_HOLD_MASK) )
			{
				VParaSet_StatusPoke( vpara, cursor->point_poke, wk );
			}
		}
	}

}
/*============================================================================================*/
/*  タッチパネルチェック処理                                                                  */
/*============================================================================================*/

//------------------------------------------------------------------
/**
 * ボタンが押されたかチェック
 *
 * @param   wk		ワークポインタ
 *
 * @retval  u32		押されたボタンのID（押されていなければ BUTTONID_NONE ）
 */
//------------------------------------------------------------------
static BOOL CheckButtonPush( BOXAPP_WORK* wk )
{
	wk->btn_id = BUTTONID_NONE;

	BMN_Main( wk->bmn );

	return  ( wk->btn_id != BUTTONID_NONE );
}

//------------------------------------------------------------------
/**
 * ボタン管理マネージャからのコールバック
 *
 * @param   btnID		ボタンID
 * @param   event		ボタンイベント
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void BmnCallBack( u32 btnID, u32 event, void* wk_adrs )
{
	BOXAPP_WORK* wk = (BOXAPP_WORK*)wk_adrs;

	if( ( event == BMN_EVENT_TOUCH )
	&&	( wk->btn_id == BUTTONID_NONE) 
	){
		wk->btn_id = btnID;
	}

	if( BoxAppVPara_GetBoxMode(&wk->vpara) == BOX_MODE_COMPARE )
	{
		if( btnID == BUTTONID_PAGE )
		{
			switch( event ){
			case BMN_EVENT_TOUCH:
				VParaSet_SetComparePageButtonState( &wk->vpara, TRUE );
				break;

			case BMN_EVENT_RELEASE:
			case BMN_EVENT_SLIDEOUT:
				VParaSet_SetComparePageButtonState( &wk->vpara, FALSE );
				break;
			}
		}
	}
}

/*====================================================================================*/
/*  描画パラメータセット処理                                                          */
/*====================================================================================*/
static void VParaSet_MessageID( BOXAPP_VPARAM* vpara, u32 msgID )
{
	vpara->message_id = msgID;
}

//------------------------------------------------------------------
/**
 * トレイ内カーソル位置をセット
 *
 * @param   vpara		
 * @param   x		
 * @param   y		
 *
 */
//------------------------------------------------------------------
static void VParaSet_CursorTrayPos( BOXAPP_VPARAM* vpara, u32 x, u32 y )
{
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	cursor->tray_xpos = x;
	cursor->tray_ypos = y;
	cursor->tray_pos = y * BOX_MAX_COLUMN + x;
}
//------------------------------------------------------------------
/**
 * カーソルの下にあるポケモン単体を、掴み中ポケデータにする。
 * つかんだポケモンデータ部はクリアする。
 *
 * @param   vpara		
 */
//------------------------------------------------------------------
static void VParaSet_PokeCatch( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
	{
		MI_CpuCopy32( cursor->point_poke, catchPoke->ppp, PokemonPasoParamSizeGet() );
		BOXDAT_ClearPokemon( wk->boxData, BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos );
		catchPoke->fromPartyFlag = FALSE;
	}
	else
	{
		// catchPoke->ppp は30体分とってあるので足りるハズ…
		MI_CpuCopy32( cursor->point_poke, catchPoke->ppp, PokemonParamSizeGet() );
		PokeParty_Delete( wk->partyData, cursor->partytray_pos );
		catchPoke->fromPartyFlag = TRUE;
	}

	VParaSet_StatusPokeData( vpara, catchPoke->ppp );

	catchPoke->areaStartX = catchPoke->areaEndX = cursor->tray_xpos;
	catchPoke->areaStartY = catchPoke->areaEndY = cursor->tray_ypos;

	vpara->cursor.poke_catch_flag = CURSOR_CATCH_SINGLE;
	vpara->cursor.poke_point_flag = FALSE;
}
//------------------------------------------------------------------
/**
 * 範囲選択中ポケモンを、掴み中ポケデータにする。
 * つかんだポケモンデータ部はクリアする。
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_AreaSelectPokeCatch( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	u32  x, y, left, right, top, bottom, pos, cursor_pos, idx, ppp_size;
	POKEMON_PASO_PARAM* ppp;
	BOXAPP_CATCH_POKE* catchPoke;
	void* dstp;

	catchPoke = &vpara->catchPoke;

	catchPoke->areaSpaceCatchFlag = TRUE;
	cursor_pos = BoxAppVPara_GetCursorTrayPos(vpara);

	ppp_size = PokemonPasoParamSizeGet();
	idx = 0;
	dstp = (void*)(catchPoke->ppp);
	BoxAppVPara_GetAreaSelectParam( vpara, &left, &right, &top, &bottom );
	for(y=top; y<=bottom; y++)
	{
		pos = y*BOX_MAX_COLUMN + left;
		for(x=left; x<=right; x++)
		{
			ppp = BOXDAT_GetPokeDataAddress(wk->boxData, BOXDAT_TRAYNUM_CURRENT, pos);
			if( PokePasoParaGet( ppp, ID_PARA_poke_exist, NULL ) )
			{
				MI_CpuCopy32( ppp, dstp, ppp_size );
				BOXDAT_ClearPokemon( wk->boxData, BOXDAT_TRAYNUM_CURRENT, pos );
				(u8*)dstp += ppp_size;
				catchPoke->areaPokePos[idx++] = pos;
				if(pos == cursor_pos)
				{
					catchPoke->areaSpaceCatchFlag = FALSE;
				}
			}
			pos++;
		}
	}

	catchPoke->areaPokeCount = idx;
	catchPoke->areaTopPos = top*BOX_MAX_COLUMN+left;

//areaSpaceCatchFlag
	vpara->cursor.poke_catch_flag = (vpara->cursor.poke_point_flag)? CURSOR_CATCH_AREA_POINT : CURSOR_CATCH_AREA_FREE;
	vpara->cursor.poke_point_flag = FALSE;
}


//------------------------------------------------------------------
/**
 * アイコン範囲選択パラメータ初期セット
 *
 * @param   wk			
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_StartAreaSelect( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	catchPoke->areaStartX = catchPoke->areaEndX = cursor->tray_xpos;
	catchPoke->areaStartY = catchPoke->areaEndY = cursor->tray_ypos;
}

//------------------------------------------------------------------
/**
 * アイコン範囲選択パラメータ更新
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_UpdateAreaSelect( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	catchPoke->areaEndX = cursor->tray_xpos;
	catchPoke->areaEndY = cursor->tray_ypos;
}

//------------------------------------------------------------------
/**
 * つかんでいるポケモン単体を、カーソル位置に置く。
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_PokePut( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	BOXAPP_CURSOR* cursor = &vpara->cursor;
	POKEMON_PASO_PARAM* ppp;

	if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
	{
		BOXDAT_PutPokemonPos( wk->boxData, BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos, catchPoke->ppp );
		ppp = BOXDAT_GetPokeDataAddress( wk->boxData, BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos );
	}
	else
	{
		if( catchPoke->fromPartyFlag )
		{
			PokeParty_Add( wk->partyData, (POKEMON_PARAM*)(catchPoke->ppp) );
		}
		else
		{
			PokeReplace( catchPoke->ppp, wk->partyPokeWork );
			PokeParty_Add( wk->partyData, wk->partyPokeWork );
		}
//		ppp = catchPoke->ppp;
		ppp = (POKEMON_PASO_PARAM*)PokeParty_GetMemberPointer( wk->partyData,
					PokeParty_GetPokeCount(wk->partyData)-1 );
	}

	VParaSet_StatusPokeData( vpara, ppp );
	CursorPointPokeUpdate( wk );

	vpara->cursor.poke_catch_flag = CURSOR_CATCH_NONE;
	vpara->cursor.poke_point_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * 範囲選択でつかんでいるポケモンデータを、カーソル位置に置く。
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_AreaSelectPokePut( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara )
{
	POKEMON_PASO_PARAM* ppp;
	int i, catch_top_pos, put_top_pos, put_pos, ppp_size;
	BOXAPP_CURSOR* cursor = &vpara->cursor;
	BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;

	put_top_pos = BoxAppVPara_GetAreaSelectCursorTopPos(vpara);
	catch_top_pos = catchPoke->areaTopPos;

	ppp_size = PokemonPasoParamSizeGet();
	ppp = catchPoke->ppp;
	for(i=0; i<catchPoke->areaPokeCount; i++)
	{
		put_pos = put_top_pos + (catchPoke->areaPokePos[i]-catch_top_pos);

		BOXDAT_PutPokemonPos( wk->boxData, BOXDAT_TRAYNUM_CURRENT, put_pos, ppp );

		(u8*)ppp += ppp_size;
	}

	VParaSet_StatusPokeData(vpara,
		BOXDAT_GetPokeDataAddress(wk->boxData, BOXDAT_TRAYNUM_CURRENT, BoxAppVPara_GetCursorTrayPos(vpara)));
	CursorPointPokeUpdate( wk );

	catchPoke->areaPokeCount = 0;

//	vpara->cursor.poke_point_flag = PokePasoParaGet( cursor->point_poke, ID_PARA_poke_exist, NULL );
	vpara->cursor.poke_point_flag = (vpara->cursor.poke_catch_flag==CURSOR_CATCH_AREA_POINT);
	vpara->cursor.poke_catch_flag = CURSOR_CATCH_NONE;

}
//------------------------------------------------------------------
/**
 * つかんでいるポケモンとカーソル位置のポケモンのデータを入れ替える
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_PokeChange( BOXAPP_WORK* wk, BOXAPP_VPARAM* vpara)
{
	u32  ppsize;
	void* tmpbuf;
	BOXAPP_CATCH_POKE* catchPoke;
	BOXAPP_CURSOR* cursor;

	catchPoke = &vpara->catchPoke;
	ppsize = PokemonParamSizeGet();
	tmpbuf = (u8*)(catchPoke->ppp) + ppsize;
	cursor = &vpara->cursor;

	MI_CpuCopy32( catchPoke->ppp, tmpbuf, ppsize );
	MI_CpuCopy32( cursor->point_poke, catchPoke->ppp, ppsize );

	if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
	{
		BOXDAT_PutPokemonPos( wk->boxData, BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos, tmpbuf );
		catchPoke->fromPartyFlag = FALSE;
	}
	else
	{
		if( catchPoke->fromPartyFlag == FALSE )
		{
			PokeReplace( tmpbuf, wk->partyPokeWork );
		}
		else
		{
			MI_CpuCopy32( tmpbuf, wk->partyPokeWork, ppsize );
		}
		PokeParty_SetMemberData( wk->partyData, cursor->partytray_pos, wk->partyPokeWork );
		catchPoke->fromPartyFlag = TRUE;
	}

	VParaSet_StatusPoke( vpara, catchPoke->ppp, wk );
}
//------------------------------------------------------------------
/**
 * つかんでいるポケモンをボックスに預ける
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで成功
 */
//------------------------------------------------------------------
static BOOL VParaSet_CatchPokeAzuke( BOXAPP_WORK* wk, u32 trayNum )
{
	BOXAPP_VPARAM* vpara;
	BOXAPP_CURSOR* cursor;
	BOXAPP_CATCH_POKE* catchPoke;

	vpara = &(wk->vpara);
	cursor = &vpara->cursor;
	catchPoke = &vpara->catchPoke;

	if( BOXDAT_PutPokemonBox( wk->boxData, trayNum, catchPoke->ppp ) )
	{
		vpara->cursor.poke_catch_flag = CURSOR_CATCH_NONE;
		CursorPointPokeUpdate( wk );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 指しているポケモンをボックスに預ける
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで成功
 */
//------------------------------------------------------------------
static BOOL VParaSet_PointPokeAzuke( BOXAPP_WORK* wk, u32 trayNum )
{
	BOXAPP_VPARAM* vpara;
	BOXAPP_CURSOR* cursor;

	vpara = &(wk->vpara);
	cursor = &vpara->cursor;

	if( BOXDAT_PutPokemonBox( wk->boxData, trayNum, cursor->point_poke ) )
	{
		PokeParty_Delete( wk->partyData, cursor->partytray_pos );
		CursorPointPokeUpdate( wk );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * つかんでいるポケモンデータを削除（逃がす）
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
static void VParaSet_CatchPokeNigasu( BOXAPP_WORK* wk )
{
	BOXAPP_VPARAM* vpara;
	BOXAPP_CURSOR* cursor;
	BOXAPP_CATCH_POKE* catchPoke;

	vpara = &(wk->vpara);
	cursor = &vpara->cursor;
	catchPoke = &vpara->catchPoke;

	PokePasoParaInit(catchPoke->ppp);
	cursor->poke_catch_flag = CURSOR_CATCH_NONE;

	CursorPointPokeUpdate( wk );
}
//------------------------------------------------------------------
/**
 * 指しているポケモンデータを削除（逃がす）
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
static void VParaSet_PointPokeNigasu( BOXAPP_WORK* wk )
{
	BOXAPP_VPARAM* vpara = &(wk->vpara);
	BOXAPP_CURSOR* cursor = &vpara->cursor;

	if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
	{
		BOXDAT_ClearPokemon( wk->boxData, BOXDAT_TRAYNUM_CURRENT, cursor->tray_pos );
	}
	else
	{
		PokeParty_Delete( wk->partyData, cursor->partytray_pos );
	}
	CursorPointPokeUpdate( wk );
}
//------------------------------------------------------------------
/**
 * ステータス表示用ポケモンの状態更新
 *
 * @param   vpara		
 * @param   ppp			
 * @param   wk			
 *
 */
//------------------------------------------------------------------
static void VParaSet_StatusPoke( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk )
{
	VParaSet_StatusPoke_Normal( vpara, ppp, wk );

	if( BoxAppVPara_GetBoxMode(vpara) == BOX_MODE_COMPARE )
	{
		VParaSet_StatusPoke_Compare( vpara, ppp, wk );
	}
}

//-----------------------------------------------------------
// ステータス表示用ポケモンの状態更新（通常用）
//-----------------------------------------------------------
static void VParaSet_StatusPoke_Normal( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke = &(vpara->statusPoke);
	BOOL   fastmodeFlag = PokePasoParaFastModeOn(ppp);
	POKEMON_PERSONAL_DATA*  personalData;

	stpoke->poke_data = ppp;
	stpoke->monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	stpoke->itemno = PokePasoParaGet( ppp, ID_PARA_item, NULL );
	stpoke->zukan_no = PMNumber_GetPokeNumber( PMNumber_GetMode(wk->saveData), stpoke->monsno );
	stpoke->tamago_flag = PokePasoParaGet( ppp, ID_PARA_tamago_exist, NULL );
	personalData = PokePersonalPara_Open(stpoke->monsno, HEAPID_BOX_SYSTEM);

	stpoke->level = PokePersonal_LevelCalc( personalData, stpoke->monsno, PokePasoParaGet(ppp, ID_PARA_exp, NULL) );

	stpoke->mark = PokePasoParaGet( ppp, ID_PARA_mark, NULL );

	stpoke->type1 = PokePasoParaGet( ppp, ID_PARA_type1, NULL );
	stpoke->type2 = PokePasoParaGet( ppp, ID_PARA_type2, NULL );

	if( (stpoke->tamago_flag == FALSE) && PokePasoParaGet( ppp, ID_PARA_nidoran_nickname, NULL ) )
	{
		stpoke->sex = PokePersonal_SexGet( personalData, stpoke->monsno, PokePasoParaGet(ppp, ID_PARA_personal_rnd, NULL) );
	}
	else
	{
		// ニドラン♂・♀でニックネームがついていない時は性別表示させないため
		stpoke->sex = MONS_UNKNOWN;
	}

	PokePasoParaGet( ppp, ID_PARA_nickname_buf, stpoke->nickname );

	if( stpoke->tamago_flag == FALSE )
	{
		MSGMAN_GetString( wk->msgman_poke, stpoke->monsno, stpoke->monsname );
	}
	else
	{
		STRBUF_Copy( stpoke->monsname, stpoke->nickname );
		STRBUF_Clear( stpoke->nickname );
	}

	if( stpoke->itemno != ITEM_DUMMY_ID )
	{
		GetItemName( stpoke->itemname, stpoke->itemno, HEAPID_BOX_SYSTEM );
	}
	else
	{
		MSGMAN_GetString( wk->msgman_box, msg_boxmes_01_21, stpoke->itemname );
	}

	{
		u32 num = PokePasoSeikakuGet( ppp );
		MSGMAN_GetString( wk->msgman_poke_character, num, stpoke->character );

		num = PokePasoParaGet( ppp, ID_PARA_speabino, NULL );
		MSGMAN_GetString( wk->msgman_speabi, num, stpoke->ability );
	}

	PokePersonalPara_Close( personalData );
	PokePasoParaFastModeOff( ppp, fastmodeFlag );
}
//-----------------------------------------------------------
// ステータス表示用ポケモンの状態更新（つよさくらべ用）
//-----------------------------------------------------------
static void VParaSet_StatusPoke_Compare( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke = &(vpara->statusPoke);
	BOXAPP_COMPARE_POKE_STATUS* compare_poke = &(vpara->compare.status[vpara->compare.updateSide]);
	BOOL  fastmodeFlag;

	compare_poke->poke_data = ppp;
	compare_poke->monsno = stpoke->monsno;
	compare_poke->tamago_flag = stpoke->tamago_flag;
	compare_poke->level = stpoke->level;

	if( compare_poke->tamago_flag )
	{
		STRBUF_Copy( compare_poke->nickname, stpoke->monsname );
	}
	else
	{
		STRBUF_Copy( compare_poke->nickname, stpoke->nickname );
	}
	STRBUF_Copy( compare_poke->character, stpoke->character );

	PokeReplace( ppp, wk->partyPokeWork );
	fastmodeFlag = PokeParaFastModeOn( wk->partyPokeWork );
	compare_poke->hp_max     = PokeParaGet( wk->partyPokeWork, ID_PARA_hpmax, NULL );
	compare_poke->attack     = PokeParaGet( wk->partyPokeWork, ID_PARA_pow, NULL );
	compare_poke->defence    = PokeParaGet( wk->partyPokeWork, ID_PARA_def, NULL );
	compare_poke->sp_attack  = PokeParaGet( wk->partyPokeWork, ID_PARA_spepow, NULL );
	compare_poke->sp_defence = PokeParaGet( wk->partyPokeWork, ID_PARA_spedef, NULL );
	compare_poke->agility    = PokeParaGet( wk->partyPokeWork, ID_PARA_agi, NULL );
	compare_poke->style     = PokeParaGet( wk->partyPokeWork, ID_PARA_style, NULL );
	compare_poke->beauty    = PokeParaGet( wk->partyPokeWork, ID_PARA_beautiful, NULL );
	compare_poke->cute      = PokeParaGet( wk->partyPokeWork, ID_PARA_cute, NULL );
	compare_poke->clever    = PokeParaGet( wk->partyPokeWork, ID_PARA_clever, NULL );
	compare_poke->strong    = PokeParaGet( wk->partyPokeWork, ID_PARA_strong, NULL );
	compare_poke->skill[0]  = PokeParaGet( wk->partyPokeWork, ID_PARA_waza1, NULL );
	compare_poke->skill[1]  = PokeParaGet( wk->partyPokeWork, ID_PARA_waza2, NULL );
	compare_poke->skill[2]  = PokeParaGet( wk->partyPokeWork, ID_PARA_waza3, NULL );
	compare_poke->skill[3]  = PokeParaGet( wk->partyPokeWork, ID_PARA_waza4, NULL );
	compare_poke->form_number = PokeParaGet( wk->partyPokeWork, ID_PARA_form_no, NULL );
	PokeParaFastModeOff( wk->partyPokeWork, fastmodeFlag );

	vpara->compare.updateSideFlag[vpara->compare.updateSide] = TRUE;
}

//------------------------------------------------------------------
/**
 * 強さ比べモード：更新するサイドの変更
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SwitchCompareSide( BOXAPP_VPARAM* vpara )
{
	vpara->compare.updateSide ^= 1;
}

//------------------------------------------------------------------
/**
 * 強さ比べモード：ページ切り替え
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_ChangeComparePage( BOXAPP_VPARAM* vpara )
{
	if( ++(vpara->compare.page) >= BOXAPP_COMPARE_PAGE_MAX )
	{
		vpara->compare.page = 0;
	}
}
//------------------------------------------------------------------
/**
 * 強さ比べモード：ボタン押下状態セット
 *
 * @param   vpara		
 * @param   on		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SetComparePageButtonState( BOXAPP_VPARAM* vpara, BOOL on )
{
	vpara->compare.pageButtonPushFlag = on;
}
//------------------------------------------------------------------
/**
 * ステータス表示用ポケモンのﾃﾞｰﾀｱﾄﾞﾚｽのみセットし直す
 *
 * @param   vpara		
 * @param   ppp		
 *
 */
//------------------------------------------------------------------
static void VParaSet_StatusPokeData( BOXAPP_VPARAM* vpara, POKEMON_PASO_PARAM* ppp )
{
	vpara->statusPoke.poke_data = ppp;
}
//------------------------------------------------------------------
/**
 * ステータス表示用ポケモンのマーキング状態のみセットしなおす
 * ※マーキング状態はメニュー用ワークを参照
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_StatusPokeMark( BOXAPP_VPARAM* vpara )
{
	BOXAPP_STATUS_POKE* stpoke;
	u8 mark;

	stpoke = &(vpara->statusPoke);
	mark= vpara->menu.mark;
	stpoke->mark = mark;

	// markはu8に入れる
	PokePasoParaPut( stpoke->poke_data, ID_PARA_mark, &(mark) );
}
//------------------------------------------------------------------
/**
 * ステータス表示用ポケモンのアイテムナンバーをセット
 *
 * @param   vpara		
 * @param   itemno		
 *
 */
//------------------------------------------------------------------
static void VParaSet_StatusPokeItemNumber( BOXAPP_VPARAM* vpara, u16 itemno, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke;

	stpoke = &(vpara->statusPoke);
	stpoke->itemno = itemno;

	if( stpoke->itemno != ITEM_DUMMY_ID )
	{
		GetItemName( stpoke->itemname, stpoke->itemno, HEAPID_BOX_SYSTEM );
	}
	else
	{
		MSGMAN_GetString( wk->msgman_box, msg_boxmes_01_21, stpoke->itemname );
	}

	// アイテムセット
	if( (BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY)
	&&	(BoxAppVPara_GetCursorCatchPokeFlag(vpara) == CURSOR_CATCH_NONE)
	){
		u32 pos = BoxAppVPara_GetCursorTrayPos(vpara);
		BOXDAT_PokeParaPut( wk->boxData, BOXDAT_TRAYNUM_CURRENT, pos, ID_PARA_item, &itemno );
	}
	else
	{
		PokePasoParaPut( stpoke->poke_data, ID_PARA_item, &itemno );
	}

	// アウスだったらフォルムチェンジ
	if( PokePasoParaGet( stpoke->poke_data, ID_PARA_monsno, NULL ) == MONSNO_AUSU )
	{
		PokePasoParaAusuFormChange( stpoke->poke_data );
	}
}
//------------------------------------------------------------------
/**
 * トレイナンバー１コ進める
 *
 * @param   tray		
 *
 */
//------------------------------------------------------------------
static void VParaSet_CurrentTrayInc( BOXAPP_VPARAM* vpara )
{
	BOXAPP_TRAY*  tray = &(vpara->tray);
	if( ++(tray->number) >= BOX_MAX_TRAY )
	{
		tray->number = 0;
	}
	SetTrayStatus( vpara->boxData, tray );
}
//------------------------------------------------------------------
/**
 * トレイナンバー１コ戻す
 *
 * @param   tray		
 *
 */
//------------------------------------------------------------------
static void VParaSet_CurrentTrayDec( BOXAPP_VPARAM* vpara )
{
	BOXAPP_TRAY*  tray = &(vpara->tray);
	if( tray->number )
	{
		tray->number--;
	}
	else
	{
		tray->number = BOX_MAX_TRAY - 1;
	}
	
	SetTrayStatus( vpara->boxData, tray );
}
//------------------------------------------------------------------
/**
 * トレイナンバー直接セット
 *
 * @param   box		
 * @param   tray		
 *
 */
//------------------------------------------------------------------
static void VParaSet_CurrentTrayNumberSet( BOXAPP_VPARAM* vpara, u32 number )
{
	BOXAPP_TRAY*  tray = &(vpara->tray);
	tray->number = number;
	SetTrayStatus( vpara->boxData, tray );
}
//------------------------------------------------------------------
/**
 * ボックス選択ウィンドウ用パラメータセット
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_JumpWin( BOXAPP_VPARAM* vpara, u32 center_trayno )
{
	BOXAPP_JUMPWIN* jwin = &(vpara->jumpWin);

	jwin->center_trayno = center_trayno;
}

//------------------------------------------------------------------
/**
 * アイテム「あずかる」
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_WithDrawItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke = &(vpara->statusPoke);
	u16 itemNumber = ITEM_DUMMY_ID;

	vpara->catch_item = stpoke->itemno;
	MSGMAN_GetString( wk->msgman_box, msg_boxmes_01_21, stpoke->itemname );

	VParaSet_StatusPokeItemNumber( vpara, itemNumber, wk );
}
//------------------------------------------------------------------
/**
 * つかんでいたアイテムをクリア
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_ClearCatchItem( BOXAPP_VPARAM* vpara )
{
	vpara->catch_item = ITEM_DUMMY_ID;
}
//------------------------------------------------------------------
/**
 * アイテム「もたせる」
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SetItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke = &(vpara->statusPoke);
	u16 itemNumber;

	itemNumber = vpara->catch_item;
	vpara->catch_item = ITEM_DUMMY_ID;

	VParaSet_StatusPokeItemNumber( vpara, itemNumber, wk );
}
//------------------------------------------------------------------
/**
 * アイテム「とりかえる」
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SwapItem( BOXAPP_VPARAM* vpara, BOXAPP_WORK* wk )
{
	BOXAPP_STATUS_POKE* stpoke = &(vpara->statusPoke);
	u16 itemNumber;

	itemNumber = vpara->catch_item;
	vpara->catch_item = stpoke->itemno;

	VParaSet_StatusPokeItemNumber( vpara, itemNumber, wk );}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   vpara		
 * @param   state		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SubLCDStae( BOXAPP_VPARAM* vpara, u32 state )
{
	vpara->subLCD.state = state;
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   vpara		
 * @param   pos		
 *
 */
//------------------------------------------------------------------
static void VParaSet_SubLCDPos( BOXAPP_VPARAM* vpara, u32 pos )
{
	vpara->subLCD.pos = pos;
}
static void VParaSet_SubLCDLimitPos( BOXAPP_VPARAM* vpara, u32 pos )
{
	vpara->subLCD.limit_pos = pos;
}
static void VParaSet_SubLCDMove( BOXAPP_VPARAM* vpara, int move )
{
	vpara->subLCD.move = move;
}

static void VParaSet_LimitModeBitFlag( BOXAPP_VPARAM* vpara, u32 iconID )
{
	if( iconID == LIMITMODE_ICON_ALLOFF ){
		vpara->system.limitModeBitFlag = 0;
	}else{
		vpara->system.limitModeBitFlag ^= ( 1 << (iconID-1) );
	}
}

static void VParaSet_ExpertModeChange( BOXAPP_VPARAM* vpara )
{
	vpara->system.expertModeFlag ^= 1;
}

/*====================================================================================*/
/*  描画パラメータ取得処理                                                            */
/*====================================================================================*/
MSGDATA_MANAGER* BoxApp_GetMsgManager( const BOXAPP_WORK* wk )
{
	return wk->msgman_box;
}
//------------------------------------------------------------------
/**
 * メッセージ作成用WORDSETを渡す
 *
 * @param   wk		ワークポインタ
 *
 * @retval  const WORDSET*		
 */
//------------------------------------------------------------------
const WORDSET* BoxApp_GetWordSet( const BOXAPP_WORK* wk )
{
	return wk->wordset;
}

int BoxApp_GetTalkWinType( const BOXAPP_WORK* wk )
{
	return CONFIG_GetWindowType( wk->sysConfig );
}


/*====================================================================================*/
/*  描画パラメータ取得処理                                                            */
/*====================================================================================*/
u32 BoxAppVPara_GetBoxMode( const BOXAPP_VPARAM* vpara )
{
	return vpara->system.boxMode;
}
u32 BoxAppVPara_GetCursorArea( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.area;
}
u32 BoxAppVPara_GetCursorTrayPosX( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.tray_xpos;
}
u32 BoxAppVPara_GetCursorTrayPosY( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.tray_ypos;
}
u32 BoxAppVPara_GetCursorTrayPos( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.tray_pos;
}
u32 BoxAppVPara_GetCursorPartyPos( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.partytray_pos;
}
BOOL BoxAppVPara_GetCursorPointPokeFlag( const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.poke_point_flag;
}
u32 BoxAppVPara_GetCursorCatchPokeFlag(const BOXAPP_VPARAM* vpara )
{
	return vpara->cursor.poke_catch_flag;
}

BOOL BoxAppVPara_GetCursorCatchPokeFromPartyFlag( const BOXAPP_VPARAM* vpara )
{
	if( vpara->cursor.poke_catch_flag )
	{
		return vpara->catchPoke.fromPartyFlag;
	}
	return FALSE;
}

BOOL BoxAppVPara_GetCursorStatusEnableFlag(const BOXAPP_VPARAM* vpara )
{
	const BOXAPP_CATCH_POKE* catchPoke;
	const BOXAPP_CURSOR* cursor;

	catchPoke = &vpara->catchPoke;
	cursor = &vpara->cursor;

	if(	(cursor->poke_catch_flag == CURSOR_CATCH_SINGLE)
	||	(cursor->poke_catch_flag == CURSOR_CATCH_AREA_POINT)
	){
		return TRUE;
	}

	if( vpara->cursor.poke_point_flag )
	{
		return TRUE;
	}

	return FALSE;
}

u32 BoxAppVPara_GetTrayBoxNumber(const BOXAPP_VPARAM* vpara )
{
	return vpara->tray.number;
}
/** ステータス表示用ポケモンデータ本体 */
const BOXAPP_STATUS_POKE* BoxAppVpara_GetStatusPokeData( const BOXAPP_VPARAM* vpara )
{
	return &(vpara->statusPoke);
}
/* ステータス表示ポケモンの持つアイテムナンバーを返す */
u32 BoxAppVPara_GetStatusPokeItemNumber( const BOXAPP_VPARAM* vpara )
{
	if( BoxAppVPara_GetCursorStatusEnableFlag(vpara) )
	{
		return vpara->statusPoke.itemno;
	}
	return ITEM_DUMMY_ID;
}
/** カレントボックストレイデータ本体 */
const BOXAPP_TRAY* BoxAppVpara_GetTrayData( const BOXAPP_VPARAM* vpara )
{
	return &(vpara->tray);
}
/** ボックスデータポインタ */
const BOX_DATA* BoxAppVPara_GetBoxData( const BOXAPP_VPARAM* vpara )
{
	return vpara->boxData;
}

u32 BoxAppVPara_GetMessageID( const BOXAPP_VPARAM* vpara )
{
	return vpara->message_id;
}
POKEMON_PASO_PARAM* BoxAppVPara_GetStatusPokePara( const BOXAPP_VPARAM* vpara )
{
	return vpara->statusPoke.poke_data;
}
u32 BoxAppVPara_GetStatusPokeMarkBit( const BOXAPP_VPARAM* vpara )
{
	return vpara->statusPoke.mark;
}
/** ボックス選択ウィンドウの中心トレイナンバー */
u32 BoxAppVPara_GetJumpWinCenterTrayNumber( const BOXAPP_VPARAM* vpara )
{
	return vpara->jumpWin.center_trayno;
}
s32 BoxAppVPara_GetSubLCDMove( const BOXAPP_VPARAM* vpara )
{
	return vpara->subLCD.move;
}

u32 BoxAppVPara_GetSubLCDPos( const BOXAPP_VPARAM* vpara )
{
	return vpara->subLCD.pos;
}
u32 BoxAppVPara_GetSubLCDLimitPos( const BOXAPP_VPARAM* vpara )
{
	return vpara->subLCD.limit_pos;
}

/* 絞り込みモードのビットフラグ */
u32 BoxAppVPara_GetLimitModeBitFlag( const BOXAPP_VPARAM* vpara )
{
	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_ITEM )
	{
		return vpara->system.limitModeBitFlag;
	}
	else
	{
		// どうぐ整理モードは常にアイテム所持ポケのみ有効表示させる
		return LIMITMODE_BIT_ITEM;
	}
}

BOOL BoxAppVPara_GetExpertModeFlag( const  BOXAPP_VPARAM* vpara )
{
	return vpara->system.expertModeFlag;
}
/*  範囲選択のパラメータを取得 */
void BoxAppVPara_GetAreaSelectParam( const BOXAPP_VPARAM* vpara, u32* left, u32* right, u32* top, u32* bottom )
{
	const BOXAPP_CATCH_POKE* catchPoke;

	catchPoke = &vpara->catchPoke;

	if( catchPoke->areaStartX <= catchPoke->areaEndX )
	{
		*left = catchPoke->areaStartX;
		*right = catchPoke->areaEndX;
	}
	else
	{
		*left = catchPoke->areaEndX;
		*right = catchPoke->areaStartX;
	}

	if( catchPoke->areaStartY <= catchPoke->areaEndY )
	{
		*top = catchPoke->areaStartY;
		*bottom = catchPoke->areaEndY;
	}
	else
	{
		*top = catchPoke->areaEndY;
		*bottom = catchPoke->areaStartY;
	}
}
/* 範囲選択動作中、範囲が１セル分になっているかチェック */
BOOL BoxAppVPara_CheckAreaSelectSinglePoke( const BOXAPP_VPARAM* vpara )
{
	const BOXAPP_CATCH_POKE* catchPoke;

	catchPoke = &vpara->catchPoke;

	if(	(catchPoke->areaStartX == catchPoke->areaEndX)
	&&	(catchPoke->areaStartY == catchPoke->areaEndY)
	){
		return TRUE;
	}
	return FALSE;
}
/* 範囲選択動作中の範囲トップ位置を返す */
u32 BoxAppVPara_GetAreaSelectCursorTopPos( const BOXAPP_VPARAM* vpara )
{
	const BOXAPP_CATCH_POKE* catchPoke;
	int left, top;

	catchPoke = &vpara->catchPoke;

	left = vpara->cursor.tray_xpos;
	top = vpara->cursor.tray_ypos;

	if(catchPoke->areaEndX > catchPoke->areaStartX)
	{
		left -= (catchPoke->areaEndX - catchPoke->areaStartX);
	}
	if(catchPoke->areaEndY > catchPoke->areaStartY)
	{
		top -= (catchPoke->areaEndY - catchPoke->areaStartY);
	}

	return (top*BOX_MAX_COLUMN + left);
}
/* 範囲選択ポケモンの特定の１体が、掴んだ時にボックスの何番目に居たかを範囲中先頭のポケモンからのオフセットで返す */
/* ややこしい */
u32 BoxAppVPara_GetAreaSelectIconOfsPos( const BOXAPP_VPARAM* vpara, u32 idx )
{
	const BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	return catchPoke->areaPokePos[idx] - catchPoke->areaTopPos;
}

BOOL BoxAppVPara_GetAreaSelectCatchSpaceFlag( const BOXAPP_VPARAM* vpara )
{
	const BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;
	return catchPoke->areaSpaceCatchFlag;
}

u32 BoxAppVPara_GetCatchItemNumber( const BOXAPP_VPARAM* vpara )
{
	return vpara->catch_item;
}

u32 BoxAppVPara_GetInfoItemNumber( const BOXAPP_VPARAM* vpara )
{
	u32 itemno = BoxAppVPara_GetCatchItemNumber(vpara);
	if( itemno != ITEM_DUMMY_ID )
	{
		return itemno;
	}
	return BoxAppVPara_GetStatusPokeItemNumber( vpara );
}

u32 BoxAppVPara_GetCompareUpdateSide( const BOXAPP_VPARAM* vpara )
{
	return vpara->compare.updateSide;
}

u32 BoxAppVPara_GetComparePage( const BOXAPP_VPARAM* vpara )
{
	return vpara->compare.page;
}

const BOXAPP_COMPARE_POKE_STATUS* BoxAppVPara_GetCompareStatus( const BOXAPP_VPARAM* vpara, int side )
{
	return &vpara->compare.status[side];
}

BOOL BoxAppVPara_GetCompareUpdatedSideFlag( const BOXAPP_VPARAM* vpara, int side )
{
	return vpara->compare.updateSideFlag[side];
}
BOOL BoxAppVPara_GetComparePageButtonPushFlag( const BOXAPP_VPARAM* vpara )
{
	return vpara->compare.pageButtonPushFlag;
}

BOOL BoxAppVPara_GetStatusPokeTamagoFlag( const BOXAPP_VPARAM* vpara )
{
	return vpara->statusPoke.tamago_flag;
}

//------------------------------------------------------------------
/**
 * ステータス表示されているポケモンデータでのPokeParaGet
 *
 * @param   vpara		
 * @param   paramID		
 * @param   buf		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
static u32 GetStatusPokeParam( BOXAPP_VPARAM* vpara, int paramID, void* buf )
{
	if( BoxAppVPara_GetCursorCatchPokeFlag(vpara) == CURSOR_CATCH_NONE )
	{
		if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
		{
			return PokePasoParaGet( vpara->statusPoke.poke_data, paramID, buf );
		}
	}
	else
	{
		BOXAPP_CATCH_POKE* catchPoke = &vpara->catchPoke;

		if( catchPoke->fromPartyFlag == FALSE )
		{
			return PokePasoParaGet( vpara->statusPoke.poke_data, paramID, buf );
		}
	}

	return PokeParaGet( vpara->statusPoke.poke_data, paramID, buf );
}

//------------------------------------------------------------------
/**
 * カーソルが指しているポケモンデータでのPokeParaGet
 *
 * @param   vpara		
 * @param   paramID		
 * @param   buf		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
static u32 GetPointPokeParam( BOXAPP_VPARAM* vpara, int paramID, void* buf )
{
	if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY )
	{
		return PokePasoParaGet( vpara->statusPoke.poke_data, paramID, buf );
	}
	else
	{
		return PokeParaGet( vpara->cursor.point_poke, paramID, buf );
	}
}
