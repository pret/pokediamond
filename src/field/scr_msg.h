//============================================================================================
/**
 * @file	scr_msg.h
 * @bfief	�X�N���v�g�Ŏg�p���郁�b�Z�[�W����
 * @author	Satoshi Nohara
 * @date	06.05.02
 */
//============================================================================================
#ifndef __SCR_MSG_H__
#define __SCR_MSG_H__


//==============================================================================
//	�\���̒�`
//==============================================================================
///ScrTalkMsg�֐��̊g���p�����[�^
typedef struct{
	u8 msg_speed;		///<���b�Z�[�W���x
	u8 auto_flag;		///<��������ݒ�(MSG_AUTO_???)
	u8 font;			///<�t�H���g
}SCR_TALK_EX_PARAM;

//============================================================================================
//
//	extern�錾
//
//============================================================================================
extern void ScrTalk_InitExParam( SCR_TALK_EX_PARAM* ex_param, VM_MACHINE* core );

extern void ScrTalkMsg( VM_MACHINE * core, const MSGDATA_MANAGER * msgman, u16 msg_id, u8 skip,
	SCR_TALK_EX_PARAM *ex_param );

extern void TalkMsgPMSParam(VM_MACHINE * core,u16 stype,u16 sid,u16 word0,s16 word1,u8 skip);

extern void TalkMsgAllPut(VM_MACHINE * core, const MSGDATA_MANAGER * msgman, int msg_id );

extern void TalkMsgExtraWordSet( VM_MACHINE * core, WORDSET* wordset,u8 msg_id, u8 skip );

#endif


