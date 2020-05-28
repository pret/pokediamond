//============================================================================================
/**
 * @file	safari_enc.h
 * @brief	サファリエンカウント関連
 * @author	saitou
 *
 */
//============================================================================================

#ifndef __SAFARI_ENC_H__
#define __SAFARI_ENC_H__

extern void SafariEnc_SetSafariEnc(	const int inRandomSeed, const BOOL inBookGet,
									const int inZoneID,
									int *outSafEncMonsNo1, int *outSafEncMonsNo2);

#ifdef PM_DEBUG
extern void SafariEnc_DebugGetSafariTbl(const int inRandomSeed, const BOOL inBookGet,
										const u8 inArea,
										int *outSaf, int *outSafEncMonsNo);
#endif

#endif //__SAFARI_ENC_H__

