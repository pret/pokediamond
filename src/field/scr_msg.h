//============================================================================================
/**
 * @file	scr_msg.h
 * @bfief	スクリプトで使用するメッセージ処理
 * @author	Satoshi Nohara
 * @date	06.05.02
 */
//============================================================================================
#ifndef __SCR_MSG_H__
#define __SCR_MSG_H__


//==============================================================================
//	構造体定義
//==============================================================================
///ScrTalkMsg関数の拡張パラメータ
typedef struct{
	u8 msg_speed;		///<メッセージ速度
	u8 auto_flag;		///<自動送り設定(MSG_AUTO_???)
	u8 font;			///<フォント
}SCR_TALK_EX_PARAM;

//============================================================================================
//
//	extern宣言
//
//============================================================================================
extern void ScrTalk_InitExParam( SCR_TALK_EX_PARAM* ex_param, VM_MACHINE* core );

extern void ScrTalkMsg( VM_MACHINE * core, const MSGDATA_MANAGER * msgman, u16 msg_id, u8 skip,
	SCR_TALK_EX_PARAM *ex_param );

extern void TalkMsgPMSParam(VM_MACHINE * core,u16 stype,u16 sid,u16 word0,s16 word1,u8 skip);

extern void TalkMsgAllPut(VM_MACHINE * core, const MSGDATA_MANAGER * msgman, int msg_id );

extern void TalkMsgExtraWordSet( VM_MACHINE * core, WORDSET* wordset,u8 msg_id, u8 skip );

#endif


