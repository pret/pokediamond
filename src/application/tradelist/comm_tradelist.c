//=============================================================================
/**
 * @file	comm_tradelist.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *          フィールド用です
 *          comm_command_field.h の enum と同じ並びである必要があります
 * @author	Akito Mori
 * @date    2005.12.21
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/gra_tool.h"
#include "system/bmp_menu.h"


#include "../../field/comm_command_field.h"

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "system/mystatus.h"

#include "tradelist_def.h"


