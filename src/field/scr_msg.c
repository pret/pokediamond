//============================================================================================
/**
 * @file	scr_msg.c
 * @bfief	スクリプトで使用するメッセージ処理
 * @author	Satoshi Nohara
 * @date	06.05.02
 */
//============================================================================================
#include "common.h"
#include "gflib/msg_print.h"
#include "gflib/strbuf_family.h"	//許可制

#include "system/lib_pack.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pmfprint.h"

#include "fieldsys.h"
#include "script.h"										//
#include "fieldmap.h"
#include "talk_msg.h"

#include "scr_msg.h"


//-------------------------------------------------------------
/**
 *
 */
//-------------------------------------------------------------
enum {
	TALK_FONT_DEFAULT = FONT_TALK,
};



//-------------------------------------------------------------
/**
 *	メッセージ出力パラメータ
 */
//-------------------------------------------------------------
typedef struct {
	STRBUF*   msgBuf;
	STRBUF*   tmpBuf;
	WORDSET*  wordSet;
	GF_BGL_BMPWIN*  bmpWin;

	u8*    win_open_flag;
	u8*    print_task_index;
}SCR_MSG_PARAM;




//==============================================================
// Prototype
//==============================================================
static u8 GetConfigMsgSpeed( VM_MACHINE* core );
static void ReadMsgParam( FIELDSYS_WORK* fsys, SCR_MSG_PARAM* param );
static void ReadMsgParamExWord( FIELDSYS_WORK* fsys,WORDSET* wordset,SCR_MSG_PARAM* param );
static void AddBitmapWin( FIELDSYS_WORK* fsys, SCR_MSG_PARAM* param );
static void LoadPrintString( SCR_MSG_PARAM* param, const MSGDATA_MANAGER* msgman, u32 msgID );
static void CreatePrintStringByPmsParam( SCR_MSG_PARAM* param, u16 stype, u16 sid, PMS_WORD word0, PMS_WORD word1 );
static void ScrTalkMsgCore( SCR_MSG_PARAM* msg_param, int font, int speed, int skip_flag, int auto_flag );
static void ScrPutMsgCore( SCR_MSG_PARAM* msg_param, int font );




//------------------------------------------------------------------
/**
 * メッセージ出力の拡張パラメータをデフォルト値で初期化する
 *（この後、必要な個所のみを変更すれば良い）
 *
 * @param   ex_param		
 * @param   core		
 *
 */
//------------------------------------------------------------------
void ScrTalk_InitExParam( SCR_TALK_EX_PARAM* ex_param, VM_MACHINE* core )
{
	ex_param->msg_speed = GetConfigMsgSpeed( core );
	ex_param->auto_flag = MSG_AUTO_OFF;
	ex_param->font = TALK_FONT_DEFAULT;
}


//--------------------------------------------------------------
/**
 *	会話メッセージウィンドウ出力
 *
 * @param	core		VM_MACHINE型のポインタ
 * @param	msg_id		メッセージID
 * @param	skip		メッセージスキップフラグ
 * @param   ex_param	拡張パラメータ(不要な場合はNULL)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void ScrTalkMsg( VM_MACHINE * core, const MSGDATA_MANAGER * msgman, u16 msg_id, u8 skip,  SCR_TALK_EX_PARAM *ex_param )
{
	SCR_MSG_PARAM  param;
	u8 msg_speed;
	u8 auto_flag;
	u8 font;

	ReadMsgParam( core->fsys, &param );
	AddBitmapWin( core->fsys, &param );
	LoadPrintString( &param, msgman, msg_id );

	if(ex_param == NULL)
	{
		msg_speed = GetConfigMsgSpeed( core );
		auto_flag = MSG_AUTO_OFF;
		font = TALK_FONT_DEFAULT;
	}
	else
	{
		msg_speed = ex_param->msg_speed;
		auto_flag = ex_param->auto_flag;
		font = ex_param->font;
	}

	ScrTalkMsgCore( &param, font, msg_speed, skip, auto_flag );
}

//--------------------------------------------------------------
/**
 *	会話ウィンドウ出力（一括表示）
 *
 * @param	core		VM_MACHINE型のポインタ
 * @param	msgman		メッセージマネージャー
 * @param	msg_id		メッセージID
 * @param	skip		メッセージスキップフラグ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void TalkMsgAllPut(VM_MACHINE * core, const MSGDATA_MANAGER * msgman, int msg_id)
{
	SCR_MSG_PARAM  param;

	ReadMsgParam( core->fsys, &param );
	AddBitmapWin( core->fsys, &param );
	LoadPrintString( &param, msgman, msg_id );

	ScrPutMsgCore( &param, TALK_FONT_DEFAULT );
}

//--------------------------------------------------------------
/**
 * パラメータから簡易会話データを生成、メッセージ出力する
 *
 * @param	core		VM_MACHINE型のポインタ
 * @param	stype		
 * @param	sid
 * @param	word0
 * @param	word1
 * @param	skip
 *
 * @retval	none
 */
//--------------------------------------------------------------
void TalkMsgPMSParam( VM_MACHINE * core, u16 stype, u16 sid, u16 word0, s16 word1, u8 skip )
{
	SCR_MSG_PARAM	param;
	PMS_DATA		pms;

	ReadMsgParam( core->fsys, &param );
	AddBitmapWin( core->fsys, &param );

	CreatePrintStringByPmsParam( &param, stype, sid, word0, word1 );

	if(skip != 0xFF)
	{
		ScrTalkMsgCore( &param, TALK_FONT_DEFAULT, GetConfigMsgSpeed(core), skip, MSG_AUTO_OFF );
	}
	else
	{
		// skip == 0xff だったら 一括表示する
		ScrPutMsgCore( &param, TALK_FONT_DEFAULT );
	}
}

//--------------------------------------------------------------
/**
 *
 * @brief	自前で作成したWORDSETを使用してタグ展開
 * @param	core		VM_MACHINE型のポインタ
 * @param	msg_id		メッセージID
 * @param	skip		メッセージスキップフラグ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void TalkMsgExtraWordSet( VM_MACHINE * core, WORDSET* wordset, u8 msg_id, u8 skip )
{
	SCR_MSG_PARAM	param;

	ReadMsgParamExWord( core->fsys, wordset,&param );
	AddBitmapWin( core->fsys, &param );
	LoadPrintString( &param, core->msgman, msg_id );

	ScrTalkMsgCore( &param, TALK_FONT_DEFAULT, GetConfigMsgSpeed(core), skip, MSG_AUTO_OFF );
}
























//------------------------------------------------------------------
/**
 * プレイヤーCONFIGデータからメッセージ速度を取得
 *
 * @param   core		
 *
 * @retval  u8		メッセージ速度
 */
//------------------------------------------------------------------
static u8 GetConfigMsgSpeed( VM_MACHINE* core )
{
	return CONFIG_GetMsgPrintSpeed( SaveData_GetConfig(core->fsys->savedata) );
}

//------------------------------------------------------------------
/**
 * スクリプトワークから文字出力に必要な共通パラメータを読み出す
 *
 * @param   fsys		
 * @param   param		読み出したパラメータの保存先構造体
 *
 */
//------------------------------------------------------------------
static void ReadMsgParam( FIELDSYS_WORK* fsys, SCR_MSG_PARAM* param )
{
	param->msgBuf = *((STRBUF**)(GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGBUF )));
	param->tmpBuf = *((STRBUF**)(GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TMPBUF )));
	param->wordSet = *((WORDSET**)(GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET )));
	param->bmpWin = GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_MSGWINDAT);

	param->win_open_flag = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_OPEN_FLAG );
	param->print_task_index = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGINDEX );
}
//------------------------------------------------------------------
/**
 * スクリプトワークから文字出力に必要な共通パラメータを読み出す
 * (WORDSETを自前のものを使うバージョン)
 *
 * @param   fsys
 * @param	WORDSET*	自前で作成したWORDSETへのポインタ
 * @param   param		読み出したパラメータの保存先構造体
 *
 */
//------------------------------------------------------------------
static void ReadMsgParamExWord( FIELDSYS_WORK* fsys,WORDSET* wordset,SCR_MSG_PARAM* param )
{
	param->msgBuf = *((STRBUF**)(GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGBUF )));
	param->tmpBuf = *((STRBUF**)(GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TMPBUF )));
	param->wordSet = wordset;
	param->bmpWin = GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_MSGWINDAT);

	param->win_open_flag = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_OPEN_FLAG );
	param->print_task_index = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGINDEX );
}

//------------------------------------------------------------------
/**
 * 会話ウィンドウ登録・表示
 *
 * @param   fsys		
 * @param   param		
 *
 */
//------------------------------------------------------------------
static void AddBitmapWin( FIELDSYS_WORK* fsys, SCR_MSG_PARAM* param )
{
	if( *(param->win_open_flag) == 0 )
	{
		FldTalkBmpAdd( fsys->bgl, param->bmpWin, FLD_MBGFRM_FONT );
		FieldTalkWinPut( param->bmpWin, SaveData_GetConfig(fsys->savedata) );
		*(param->win_open_flag) = 1;
	}
	GF_BGL_BmpWinDataFill( param->bmpWin, FBMP_COL_WHITE );
}

//------------------------------------------------------------------
/**
 * 出力文字列をパラメータ内部バッファに読み込み
 *
 * @param   param		
 * @param   msgman		
 * @param   msgID		
 *
 */
//------------------------------------------------------------------
static void LoadPrintString( SCR_MSG_PARAM* param, const MSGDATA_MANAGER* msgman, u32 msgID )
{
	MSGMAN_GetString( msgman, msgID, param->tmpBuf );
	WORDSET_ExpandStr( param->wordSet, param->msgBuf, param->tmpBuf );
}

//------------------------------------------------------------------
/**
 * 簡易会話データから文字列を生成し、パラメータ内部バッファに読み込み
 *
 * @param   param		
 * @param   stype		
 * @param   sid		
 * @param   word0		
 * @param   word1		
 *
 */
//------------------------------------------------------------------
static void CreatePrintStringByPmsParam( SCR_MSG_PARAM* param, u16 stype, u16 sid, PMS_WORD word0, PMS_WORD word1 )
{
	PMS_DATA     pms;
	STRBUF* tmpBuf;

	// 簡易会話データ生成
	PMSDAT_Clear(&pms);
	PMSDAT_SetSentence( &pms, stype, sid );
	PMSDAT_SetWord( &pms, 0, word0 );
	PMSDAT_SetWord( &pms, 1, word1 );

	tmpBuf = PMSDAT_ToString( &pms, HEAPID_EVENT );
	STRBUF_Copy( param->msgBuf, tmpBuf );
	STRBUF_Delete( tmpBuf );
}


//------------------------------------------------------------------
/**
 * 会話ウィンドウにメッセージを流す処理を開始
 *
 * @param   msg_param		
 * @param   font		
 * @param   speed		
 * @param   skip_flag		
 * @param   auto_flag		
 *
 */
//------------------------------------------------------------------
static void ScrTalkMsgCore( SCR_MSG_PARAM* msg_param, int font, int speed, int skip_flag, int auto_flag )
{
	*(msg_param->print_task_index) = FieldTalkMsgStartEx( msg_param->bmpWin, msg_param->msgBuf, 
					font, speed, skip_flag, auto_flag );
}

//------------------------------------------------------------------
/**
 * 会話ウィンドウにメッセージを一括表示する
 *
 * @param   msg_param		
 * @param   font		
 *
 */
//------------------------------------------------------------------
static void ScrPutMsgCore( SCR_MSG_PARAM* msg_param, int font )
{
	*(msg_param->print_task_index) = GF_STR_PrintSimple(
										msg_param->bmpWin, font, msg_param->msgBuf,
										0, 0, MSG_ALLPUT, NULL );
}
