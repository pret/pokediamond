//==============================================================================
/**
 * @file	ball_effect_tool.h
 * @brief	ä»íPÇ»ê‡ñæÇèëÇ≠
 * @author	goto
 * @date	2006.05.01(åé)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
#ifndef __BALL_EFFECT_TOOL_H__
#define __BALL_EFFECT_TOOL_H__


#define CB_SEAL_TYPE_A		(0)
#define CB_SEAL_TYPE_B		(1)


#define SEAL_DEF_POS_X			(190)
#define SEAL_DEF_POS_Y			(70)
#define CB_RELEASE_RANGE		(60)
#define CB_RELEASE_RANGE_LINE	(20)
#define CB_WAIT_TABLE			(CB_RELEASE_RANGE / CB_RELEASE_RANGE_LINE)


#include "field/field_common.h"

#include "savedata/custom_ball.h"

#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"
#include "system/touch_subwindow.h"

#include "include/application/imageClip/imc_hand.h"
#include "system\font_arc.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_ball_custom.h"
#include "include/msgdata/msg_bc_seal_name.h"

#include "touchpanel_system.h"
#include "touchpanel.h"
#include "gflib/button_man.h"
#include "wazaeffect/ball_effect.h"
#include "include/poketool/poke_tool.h"


extern int BET_PtoP(s16 x1, s16 y1, s16 x2, s16 y2);
extern int BET_Seal_RangeGet(CB_SEAL* seal);
extern int BET_Seal_RangeWaitGet(CB_SEAL* seal);

#endif


