//============================================================================================
/**
 * @file	scr_coin.h
 * @bfief	スクリプトコマンド：コイン関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_COIN_H
#define SCR_COIN_H


//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdCoinWinWrite(VM_MACHINE * core);
extern BOOL EvCmdCoinWinDel(VM_MACHINE * core);
extern BOOL EvCmdCoinWrite(VM_MACHINE * core);
extern BOOL EvCmdCheckCoin( VM_MACHINE * core );
extern BOOL EvCmdAddCoin( VM_MACHINE * core );
extern BOOL EvCmdSubCoin( VM_MACHINE * core );
extern BOOL EvCmdSubWkCoin( VM_MACHINE * core );
extern BOOL EvCmdCompCoin( VM_MACHINE * core );
extern BOOL EvCmdCompWkCoin( VM_MACHINE * core );
extern BOOL EvCmdAddCoinChk(VM_MACHINE * core);
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_COIN_H */


