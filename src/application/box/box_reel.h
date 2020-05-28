//============================================================================================
/**
 * @file	box_reel.h
 * @brief	ボックス操作画面　サブ画面リールセレクタの動作判定
 * @author	taya
 * @date	2005.11.16
 */
//============================================================================================
#ifndef __BOX_REEL_H__
#define __BOX_REEL_H__


enum {
	REEL_RESULT_NULL,	///< 何もない
	REEL_RESULT_START,	///< 測定開始
	REEL_RESULT_MOVE,	///< 動いた
	REEL_RESULT_RELEASE,///< 測定終了
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
