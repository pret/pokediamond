//============================================================================================
/**
 * @file	scr_gold.h
 * @bfief	スクリプトコマンド：お金関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_GOLD_H
#define SCR_GOLD_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddGold(VM_MACHINE * core);
extern BOOL EvCmdSubGold(VM_MACHINE * core);
extern BOOL EvCmdCompGold(VM_MACHINE * core);
extern BOOL EvCmdGoldWinWrite(VM_MACHINE * core);	
extern BOOL EvCmdGoldWinDel(VM_MACHINE * core);
extern BOOL EvCmdGoldWrite(VM_MACHINE * core);	
extern BOOL EvCmdSubMyGold( VM_MACHINE * core );
extern BOOL EvCmdCompMyGold( VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_GOLD_H */

