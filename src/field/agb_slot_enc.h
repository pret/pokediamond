//============================================================================================
/**
 * @file	agb_slot_enc.h
 * @brief	ＡＧＢスロットバージョン別エンカウント関連
 * @author	saitou
 *
 */
//============================================================================================
#ifndef __AGB_SLOT_ENC_H__
#define __AGB_SLOT_ENC_H__

#include "encount_dat.h"

extern void AgbSlotEnc_SetAgbSlotEnc(	const ENCOUNT_DATA *inEncData,
										const BOOL inBookGet,
										int *outAgbEncMonsNo1, int *outAgbEncMonsNo2);

#endif //__AGB_SLOT_ENC_H__
