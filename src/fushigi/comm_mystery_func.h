#ifndef __COMM_MYSTERY_FUNC_H__
#define __COMM_MYSTERY_FUNC_H__

#include "savedata/fushigi_data.h"


#define RGB(r, g, b)		(((b)&31)<<10|((g)&31)<<5|((r)&31))


enum {
  COMMMYSTERYFUNC_ERROR_NONE = 0,
  COMMMYSTERYFUNC_ERROR_VERSION,	// 配布バージョンに含まれていなかった
  COMMMYSTERYFUNC_ERROR_HAVE,		// すでにもらっていた
  COMMMYSTERYFUNC_ERROR_FULLGIFT,	// 配達員が一杯
  COMMMYSTERYFUNC_ERROR_FULLCARD,	// カードが一杯
  COMMMYSTERYFUNC_ERROR_GROUNDCHILD,	// これは孫配信
  COMMMYSTERYFUNC_ERROR_MAX
};



//--------------------------------------------------------------------------------------------
/**
 * VRAM初期化
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void CommMysteryFunc_VramBankSet(void);

//--------------------------------------------------------------------------------------------
/**
 * @brief	BG初期化
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void CommMysteryFunc_BgInit( GF_BGL_INI * ini );

//------------------------------------------------------------------
/**
 * @brief	おくりものをもらえるかチェック
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
extern int CommMysteryFunc_CheckGetGift(SAVEDATA *sv, GIFT_COMM_PACK *gcp);

#endif	// __COMM_MYSTERY_FUNC_H__
/*  */
