//============================================================================================
/**
 * @file	box_reel.h
 * @brief	�{�b�N�X�����ʁ@�T�u��ʃ��[���Z���N�^�̓��씻��
 * @author	taya
 * @date	2005.11.16
 */
//============================================================================================
#ifndef __BOX_REEL_H__
#define __BOX_REEL_H__


enum {
	REEL_RESULT_NULL,	///< �����Ȃ�
	REEL_RESULT_START,	///< ����J�n
	REEL_RESULT_MOVE,	///< ������
	REEL_RESULT_RELEASE,///< ����I��
};

typedef struct _BOX_REEL_CTRL{
	u32		seq;
	u32		touch_x;
	u32		touch_y;
	u32		center_x;
	u32		center_y;
	u32		last_x;
	u32		last_y;

	BOOL	hit_flag;

	u16		touch_angle;
	int		sign;

	TP_HIT_TBL   inside;
	TP_HIT_TBL   outside;

	int  (*func)(struct _BOX_REEL_CTRL*, BOOL, BOOL);

}BOX_REEL_CTRL;


extern void BoxApp_ReelCtrlInit( BOX_REEL_CTRL* ctrl, int cx, int cy, int r_in, int r_out );
extern int BoxApp_ReelCtrlMain( BOX_REEL_CTRL* ctrl );
extern int BoxApp_ReelCtrlGetMoveValue( const BOX_REEL_CTRL* ctrl );
extern void BoxApp_ReelCtrlNotifyMoveStart( BOX_REEL_CTRL* ctrl );
extern int BoxApp_ReelCtrlReset( BOX_REEL_CTRL* ctrl );


#endif
