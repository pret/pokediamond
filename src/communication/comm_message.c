//=============================================================================
/**
 * @file	comm_message.c
 * @brief	エラーメッセージを表示しているクラス
 * @author	k.ohno
 * @date    2006.02.05
 */
//=============================================================================


//---------------------------------------------------------
// include 
//---------------------------------------------------------
#include "common.h"
#include "communication/communication.h"
#include "system/window.h"      //TalkWinGraphicSet
#include "system/wordset.h"				//WORDSET_ExpandStr
#include "system/fontproc.h"  // FONT_TALK
#include "system/arc_util.h"
#include "system/wipe.h"

#include "msgdata/msg_communication.h"
#include "msgdata/msg.naix"

//extern u8 MsgSpeedGet(void);
//extern u8 TalkWinNumGet(void);

//---------------------------------------------------------
// typedef
//---------------------------------------------------------
