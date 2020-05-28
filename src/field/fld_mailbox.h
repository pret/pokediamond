/**
 *	@file	fld_mailbox.h
 *	@brief	�t�B�[���h���[���{�b�N�X����
 *	@author	Miyuki Iwasawa
 *	@date	06.03.03
 */

#ifndef __H_FLD_MAIL_BOX_H__
#define __H_FLD_MAIL_BOX_H__

/**
 *	@brief	���[���{�b�N�X�Ăяo����������
 */
extern void MailBox_Call(void* fsys,int* end_flag);

//--------------------------------------------------------------
/**
 * @brief	���[���{�b�N�X�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		�ړ�����
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
extern void EventCmd_MailBoxCall( GMEVENT_CONTROL *event);

#endif	//__H_FLD_MAIL_BOX_H__
