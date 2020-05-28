//=============================================================================
/**
 * @file	field_subproc.h	
 * @brief	フィールドからよばれるサブプロセス
 * @author	GAME FREAK inc.
 */
//=============================================================================
#ifndef	__FIELD_SUBPROC_H__
#define	__FIELD_SUBPROC_H__

#include "field_common.h"
#include "system/procsys.h"
#include "field_event.h"
#include "application/trainer_card.h"
#include "application/poru_tool.h"
#include "application/box.h"
#include "application/wifi_p2pmatch.h"
#include "field/itemuse.h"
#include "field/field_skill.h"
#include "application/slot.h"

//==============================================================================
//	include
//==============================================================================


typedef enum {
	EVBAG_MODE_NORMAL_ONLY = 0,
	EVBAG_MODE_KINOMI_ONLY,
}EVBAG_MODE;

//==============================================================================
//==============================================================================

//通信交換イベント呼び出し
extern void EventCmd_UnionTrade(GMEVENT_CONTROL * event);

extern void * FieldBag_SetProc( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk );
extern void FieldBag_SubProcSet( FIELDSYS_WORK * fsys, void * buf );
extern void * FieldPokeList_SetProc( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk, u8 pos );
extern void FieldPokeStatus_SetProc( FIELDSYS_WORK * fsys, void * psd );
extern void FieldTrCard_SetProc( FIELDSYS_WORK * fsys, TR_CARD_DATA *tcd );
extern void FieldNutsTag_SetProc( FIELDSYS_WORK * fsys, void * buf );
extern void FieldFantasyNote_SetProc( FIELDSYS_WORK * fsys, void * buf );
extern void * FieldConfig_SetProc( FIELDSYS_WORK * fsys );

extern void * DebugFieldBox_SetProc( FIELDSYS_WORK * fsys );
extern void FieldBox_SetProc( FIELDSYS_WORK * fsys, BOX_PROC_PARAM* param );

void EventCmd_ImcClipTvStart(GMEVENT_CONTROL * event, u16* result, SAVEDATA* p_save, u16 pos, u16 reference );
extern BOOL FieldImageClip_SetProc( FIELDSYS_WORK * fsys, void* buff );
extern BOOL FieldImageClipViewer_SetProc( FIELDSYS_WORK * fsys, void* buff );
extern BOOL FieldZukan_SetProc( FIELDSYS_WORK * fsys, void* p_pearent );
extern void NameInput_SetProc( FIELDSYS_WORK * fsys, void *param );
extern void * TradeList_SetProc( FIELDSYS_WORK * fsys );
extern void OekakiBoard_SetProc( FIELDSYS_WORK *fsys );
extern void * RecordCorner_SetProc( FIELDSYS_WORK *fsys );
extern void WifiNoteEntry_SetProc( FIELDSYS_WORK *fsys, SAVEDATA* pSaveData );
extern void WifiNote_SetProc( FIELDSYS_WORK *fsys, SAVEDATA* pSaveData );
extern BOOL WifiP2PMatch_SetProc( FIELDSYS_WORK *fsys,WIFIP2PMATCH_PROC_PARAM* pParam );
//WiFi地球儀呼び出し
extern void Field_WifiEarth_SetProc(FIELDSYS_WORK * fsys);

extern void EventCmd_NameIn(GMEVENT_CONTROL * event, int mode, int info, int wordmax, int pos, const STRCODE* str, u16* ret_work);


extern void * FieldBagEvent_SetProc( FIELDSYS_WORK * fsys, EVBAG_MODE mode );
extern u16 FieldBagEvent_GetSelectedItem(void * param);

//ポケモン選択呼出し
extern void * FieldPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys);
extern void * FieldPokeListEventNpcTrade_SetProc(int heap, FIELDSYS_WORK * fsys);
extern int FieldPokeListEvent_GetSelect(void * wk);
extern int FieldPokeListEvent_GetMode(void * wk);
extern void * UnionPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys);
extern void * ContestPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, 
	int con_type, int con_rank, int sio_flag, int pos);

extern void * EventCmd_PokeListSelect(GMEVENT_CONTROL * event, int heapID);

//そだてやポケモン選択呼出し
extern void * SodateyaPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos);

//ポケモンステータス画面呼び出し
extern void * ContestPokeStatusEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos);
extern int FieldPokeStatusEvent_GetPos(void * wk);

//わざ忘れ選択呼出し
extern void * FieldWazaListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, u8 pos);
extern int FieldWazaListEvent_GetSelect(void * wk);

//技教え・思い出し
#include "application/waza_oshie.h"
extern void WazaOshie_ProcSet( FIELDSYS_WORK * fsys , WAZAOSHIE_DATA * wk );

//メール呼び出し
#include "savedata/mail_def.h"
#include "application/mail/mail_param.h"
/**
 *	@brief	メール作成画面フィールドメニュー呼び出し
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :内部確保したパラメータワークへのポインタ
 *						　　呼び出し側が明示的に解放する必要あり
 */
extern MAIL_PARAM * FieldMailCreate_InitCall( FIELDSYS_WORK * fsys ,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID);

/**
 *	@brief	メール描画画面フィールドメニュー呼び出し
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :内部確保したパラメータワークへのポインタ
 *						　　呼び出し側が明示的に解放する必要あり
 */
extern MAIL_PARAM * FieldMailView_InitCall( FIELDSYS_WORK * fsys,
		MAILBLOCK_ID blockID,u8 dataID,int heapID);
/**
 *	@brief	メール描画画面フィールドメニュー呼び出し(ポケモンメール)
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :内部確保したパラメータワークへのポインタ
 *						　　呼び出し側が明示的に解放する必要あり
 *
 */
extern MAIL_PARAM * FieldMailViewPoke_InitCall( FIELDSYS_WORK * fsys,
		POKEMON_PARAM* poke,int heapID);

/**
 *	@brief	ポルトケース呼び出し
 */
extern PORUTO_PARAM* FieldPorutoCase_InitCall(FIELDSYS_WORK* fsys,int heapID);
/**
 *	@brief	フィールド タワーアプリ呼び出し
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	work	void*:ワークの引継ぎ
 *
 *	@retval	0:成功
 *	@retval else	失敗
 */
#include "application\btwr_app.h"
extern void BTowerApp_SetProc(FIELDSYS_WORK *fsys,BTOWER_APP_PARAM * ap);

//==============================================================================
// 簡易会話入力画面
//==============================================================================
#include "application\pms_input.h"
extern void FieldProc_SetPmsInput( FIELDSYS_WORK* fsys, PMSI_PARAM* param );

//イベントコマンド：簡易会話単語入力呼び出し
extern void EventCmd_PMSInput(GMEVENT_CONTROL * event, u16 * result, u16 * pms1, u16 * pms2);

//==============================================================================
// 開始ポケモン選択画面画面
//==============================================================================
#include "demo/ev_poke_select.h"
extern void Field_EVPokeSelect_SetProc( FIELDSYS_WORK * fsys, EV_POKESELECT_PEARENT_DATA* p_pearent );

// -----------------------------------------
//
//	カスタムボール画面
//
// -----------------------------------------
extern BOOL Field_CustomBall_SetProc( FIELDSYS_WORK * fsys, void* buff );

// 自分サイン入力画面
extern void Field_MySign_SetProc( FIELDSYS_WORK *fsys );

// 世界交換呼び出し
extern void Field_WorldTrade_SetProc( FIELDSYS_WORK *fsys, int connect );

// WIFIバトルタワー接続画面呼び出し
extern void* Field_WifiBattleTowerConnect_SetProc( FIELDSYS_WORK *fsys, int mode, int connect );



//==============================================================================
// 交換リスト～交換デモ～
//==============================================================================
extern BOOL GMEVENT_UnionTradeList(GMEVENT_CONTROL * event);


//==============================================================================
// 殿堂入りデモ
//==============================================================================
#include "demo\demo_dendou.h"
extern void Field_DendouDemo_SetProc( FIELDSYS_WORK * fsys, DEMO_DENDOU_PARAM* param );

//==============================================================================
//	殿堂入り確認
//==============================================================================
extern void * Field_DendouPC_Call( FIELDSYS_WORK* fsys );


//==============================================================================
// エンディングデモ
//==============================================================================
#include "demo\demo_ending.h"
extern void Field_EndingDemo_SetProc( FIELDSYS_WORK * fsys, ENDING_PROC_PARAM* param );

//==============================================================================
//	タマゴうまれるデモ
//==============================================================================
void Field_EggDemo_Call(FIELDSYS_WORK * fsys);

//==============================================================================
//	スロット
//==============================================================================
extern BOOL FieldSlot_SetProc( FIELDSYS_WORK *fsys, SLOT_PARAM *slotparam );

extern void EventCmd_SlotMachine(GMEVENT_CONTROL * event, int id);


//==============================================================================
//	アクセサリーショップ
//==============================================================================
extern void EventCmd_AcceShop(GMEVENT_CONTROL * event);

//==============================================================================
//	表彰状
//==============================================================================
extern void* Syoujyou_SetProc( FIELDSYS_WORK * fsys, int heapID, int type );

//==============================================================================
// タウンマップ関連
//==============================================================================
extern void * FieldMenuTMap_SetProc( FIELDSYS_WORK * fsys );


#endif	//__FIELD_SUBPROC_H__
