//============================================================================================
/**
 * @file	ev_check.h
 * @brief	イベント発動チェックシステム
 * @author	Sousuke Tamada
 * @date	01.03.29
 *
 * 05.07.04 Hiroyuki Nakamura
 */
//============================================================================================
#ifndef __EV_CHECK_H__
#define __EV_CHECK_H__

#include "field_common.h"



//=========================================================================
//	定義
//=========================================================================

/* イベントチェックリクエスト構造体 */
typedef struct {
	u16	TalkCheck:1;
	u16	StepCheck:1;
	u16	MenuOpen:1;
	u16	CnvButton:1;
	u16	MatCheck:1;
	u16	PushCheck:1;
	u16	MoveCheck:1;
	u16	FloatCheck:1;

	u16	DebugMenu:1;
	u16	DebugBattle:1;
	u16	DebugHook:1;
	u16 DebugKeyPush:1;
	u16	:4;

	u8	Site;
	s8	PushSite;
	u16 trg;
	u16 cont;
}EV_REQUEST;


//=========================================================================
//	関数プロトタイプ
//=========================================================================

//イベント起動チェックのリクエストセット
extern void SetRequest( EV_REQUEST * req, FIELDSYS_WORK * repw, u16 trg, u16 cont );

//イベント起動チェックメイン
extern int CheckRequest(const EV_REQUEST * req, FIELDSYS_WORK * repw);
// 炭鉱時のイベント起動検査
extern BOOL CheckRequestUG( EV_REQUEST * req, FIELDSYS_WORK * repw );
// 対戦時のイベント起動検査
extern BOOL CheckRequestVSRoom( EV_REQUEST * req, FIELDSYS_WORK * repw );
// ユニオンルームでのイベント起動チェック
extern BOOL CheckRequestUnion(const EV_REQUEST * req, FIELDSYS_WORK * repw);
//バトルタワー専用イベント起動チェック
extern int CheckRequestBTower(const EV_REQUEST * req, FIELDSYS_WORK * repw);


#endif	/*__EV_CHECK_H__*/

