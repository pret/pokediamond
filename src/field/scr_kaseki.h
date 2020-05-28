//============================================================================================
/**
 * @file	scr_kaseki.h
 * @bfief	スクリプトコマンド：カセキ操作関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_KASEKI_H
#define SCR_KASEKI_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdKasekiCount(VM_MACHINE * core);
extern BOOL EvCmdItemNoToMonsNo(VM_MACHINE * core);
extern BOOL EvCmdKasekiItemNo(VM_MACHINE * core);

//未使用
extern BOOL EvCmdItemListSetProc(VM_MACHINE * core);
extern BOOL EvCmdItemListGetResult(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_KASEKI_H */

