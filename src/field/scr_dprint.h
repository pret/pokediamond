//============================================================================================
/**
 * @file	scr_dprint.h
 * @bfief	スクリプトコマンド：デバッグ表示関連
 * @author	Tomomichi Ohta
 * @date	06.07.08
 */
//============================================================================================
#ifndef SCR_DPRINT_H
#define SCR_DPRINT_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdDebugPrintWork(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintFlag(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintWorkStationed(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintFlagStationed(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */

#endif	/* SCR_DPRINT_H */
