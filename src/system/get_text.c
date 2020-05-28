//=============================================================================
/**
 * @file	get_text.c	
 * @bfief	メッセージエディタコンバータが出力したデータからテキストデータを取得
 * @author	GAME FREAK inc.  taya
 */
//=============================================================================
#include "common.h"
#include "system/get_text.h"

//------------------------------------------------------------------
/**
 * 文字列IDから文字列アドレスを返す
 *
 * @param   msg_data		文字列データ先頭アドレス
 * @param   msg_id			文字列ID
 *
 * @retval  const u8*		
 *
 *	引数の msg_data は、メッセージコンバータが出力したバイナリファイルの先頭です
 *
 */
//------------------------------------------------------------------
const STRCODE* GetMessageData(const u8* msg_data, u32 msg_id)
{
	const u32 *ptr;
	u32  msg_max;

	ptr = (const u32*)msg_data;

	msg_max = *ptr++;
	if(msg_id >= msg_max)
	{
		SDK_ASSERT(0);
		return NULL;
	}

	ptr += msg_id;
	msg_data = (const u8*)ptr;
	msg_data += *ptr;

	return (STRCODE*)msg_data;
}
