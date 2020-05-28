//============================================================================================
/**
 * @file	scr_goods.h
 * @bfief	スクリプトコマンド：グッズ関連
 * @author	Tomomichi Ohta
 * @date	06.06.30
 */
//============================================================================================
#ifndef SCR_GOODS_H
#define SCR_GOODS_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddGoods(VM_MACHINE * core);
extern BOOL EvCmdSubGoods(VM_MACHINE * core);
extern BOOL EvCmdAddGoodsChk(VM_MACHINE * core);
extern BOOL EvCmdCheckGoods(VM_MACHINE * core);
extern BOOL EvCmdAddTrap(VM_MACHINE * core);
extern BOOL EvCmdSubTrap(VM_MACHINE * core);
extern BOOL EvCmdAddTrapChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTrap(VM_MACHINE * core);
extern BOOL EvCmdAddTreasure(VM_MACHINE * core);
extern BOOL EvCmdSubTreasure(VM_MACHINE * core);
extern BOOL EvCmdAddTreasureChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTreasure(VM_MACHINE * core);
extern BOOL EvCmdAddTama(VM_MACHINE * core);
extern BOOL EvCmdSubTama(VM_MACHINE * core);
extern BOOL EvCmdAddTamaChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTama(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_GOODS_H */

