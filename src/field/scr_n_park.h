//============================================================================================
/**
 * @file	scr_n_park.h
 * @bfief	スクリプトコマンド：自然公園関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_N_PARK_H
#define SCR_N_PARK_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdNaturalParkWalkCountClear(VM_MACHINE * core);
extern BOOL EvCmdNaturalParkWalkCountGet(VM_MACHINE * core);
extern BOOL EvCmdNaturalParkAccessoryNoGet(VM_MACHINE * core);
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_N_PARK_H */

