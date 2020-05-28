/**
 *	@file	fld_mailbox.h
 *	@brief	フィールドメールボックス処理
 *	@author	Miyuki Iwasawa
 *	@date	06.03.03
 */

#ifndef __H_FLD_MAIL_BOX_H__
#define __H_FLD_MAIL_BOX_H__

/**
 *	@brief	メールボックス呼び出し＆初期化
 */
extern void MailBox_Call(void* fsys,int* end_flag);

//--------------------------------------------------------------
/**
 * @brief	メールボックスサブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		移動方向
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
extern void EventCmd_MailBoxCall( GMEVENT_CONTROL *event);

#endif	//__H_FLD_MAIL_BOX_H__
