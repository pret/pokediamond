//==============================================================================================
/**
 * @file	ev_win.h
 * @brief	�C�x���g�E�B���h�E
 * @author	Satoshi Nohara
 * @date	2005.07.29
 */
//==============================================================================================
#ifndef EV_WIN_H
#define EV_WIN_H


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define EV_WIN_B_CANCEL			(0xfffe)		//B�L�����Z��
//#define EV_WIN_LIST_END		(0xfffd)		//���ڂ̏I���R�[�h
#define EV_WIN_NOTHING			(0xeeee)		//�������̒l
#define	EV_WIN_LIST_LABEL		(0xfa)			//���X�g�g�p���Ƀ��x�����w�肷���`(�X�N���v�g�p)
#define	EV_WIN_TALK_MSG_NONE	(0xff)			//���X�g�g�p���̉�b���b�Z�[�W�Ȃ�

//----------------------------------------------------------------------------------------------
//	�t���A��`
//
//	�EWK_ELEVATOR_FLOOR�ɑ�������l
//	�E�J�[�\���ʒu�ɑΉ����Ă���̂Œ���
//	�E�K�i���o�[�̕�����̓X�N���v�g�ŃZ�b�g����
//----------------------------------------------------------------------------------------------
#define FLOOR_NOTHING			(0xffff)		//TCB�폜����l

#define FLOOR_C05R0103_2F		(0)
#define FLOOR_C05R0103_1F		(1)

#define FLOOR_C05R0803_2F		(0)
#define FLOOR_C05R0803_1F		(1)

#define FLOOR_C07FS0101_8F		(0)
#define FLOOR_C07FS0101_4F		(1)
#define FLOOR_C07FS0101_3F		(2)
#define FLOOR_C07FS0101_2F		(3)

#define FLOOR_T07R0103_2F		(0)
#define FLOOR_T07R0103_1F		(1)

#define FLOOR_C08R0802_2F		(0)
#define FLOOR_C08R0802_1F		(1)

#define FLOOR_C07R0206_5F		(0)
#define FLOOR_C07R0206_4F		(1)
#define FLOOR_C07R0206_3F		(2)
#define FLOOR_C07R0206_2F		(3)
#define FLOOR_C07R0206_1F		(4)

#define FLOOR_C01R0208_4F		(0)
#define FLOOR_C01R0208_3F		(1)
#define FLOOR_C01R0208_2F		(2)
#define FLOOR_C01R0208_1F		(3)

//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_


#include "common.h"
#include "gflib/msg_print.h"					//STRCODE
#include "system/msgdata.h"						//MSGDATA_MANAGER


//==============================================================================================
//
//	�C�x���g�E�B���h�E���[�N�ւ̕s���S�^�|�C���^
//
//==============================================================================================
typedef	struct _EV_WIN_WORK EV_WIN_WORK;


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@������
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	"EV_WIN_WORK�^�̃A�h���X�ANULL�͎��s"
 */
//--------------------------------------------------------------
extern EV_WIN_WORK* CmdEvBmpMenu_Init(FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPMENU�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPMENU�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenu_Start( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�c���@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	x_max		���������ڍő吔(�K��1�ȏ�)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max );

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@������
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	"EV_WIN_WORK�^�̃A�h���X�ANULL�͎��s"
 */
//--------------------------------------------------------------
extern EV_WIN_WORK* CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPLIST�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpList_Start( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@�����I��
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void EvBmpMenu_Del( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@�t���A�\��
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset);

//--------------------------------------------------------------
/**
 * ����ڑ��悩��A���݂̃t���A�i���o�[���擾
 *
 * @param   zone_id		�]�[��ID
 *
 * @retval  "�t���A�i���o�["
 */
//--------------------------------------------------------------
extern u16 ElevatorNowFloorGet( int zone_id );




//--------------------------------------------------------------------------------------------
/**
 * �������E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_GoldWinDel�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_GoldWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * �������E�B���h�E�폜
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_GoldWinDel( GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * �������`��
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_GoldWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_CoinWinDel�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_CoinWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�폜
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_CoinWinDel( GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���`��
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_CoinWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_CoinWinDel(���L�Ŏg����)�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_BtlPointWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�`��
 *
 * @param	fsys
 * @param	wk
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_BtlPointWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );


#endif	__ASM_NO_DEF_


#endif	/* EV_WIN_H */


