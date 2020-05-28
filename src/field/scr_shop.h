//============================================================================================
/**
 * @file	scr_shop.h
 * @bfief	スクリプトコマンド：ショップ関連
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#ifndef SCR_SHOP_H
#define SCR_SHOP_H


//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdShopCall( VM_MACHINE * core );
extern BOOL EvCmdFixShopCall( VM_MACHINE * core );
extern BOOL EvCmdFixGoodsCall( VM_MACHINE * core );
extern BOOL EvCmdFixSealCall( VM_MACHINE * core );
extern BOOL EvCmdAcceShopCall( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_SHOP_H */


