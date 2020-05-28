//******************************************************************************
/**
 *
 * @file	player_event_arrowmat.h
 * @brief	プレーヤーの方向床のイベント
 * @author	k.ohno
 * @data	06.06.20
 *
 */
//******************************************************************************
#ifndef __PLAYER_EVENT_ARROWMAT_H__
#define __PLAYER_EVENT_ARROWMAT_H__



// 方向床を踏んだ場合イベント起動
extern int JikiEventCheck_ArrowMat(
    FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir);


#endif //__PLAYER_EVENT_ARROWMAT_H__

