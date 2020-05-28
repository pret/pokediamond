//============================================================================================
/**
 * @file	scr_item.h
 * @bfief	スクリプトコマンド：アイテム関連
 * @author	Tomomichi Ohta
 * @date	06.06.30
 */
//============================================================================================
#ifndef SCR_ITEM_H
#define SCR_ITEM_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddItem(VM_MACHINE * core);
extern BOOL EvCmdSubItem(VM_MACHINE * core);
extern BOOL EvCmdAddItemChk(VM_MACHINE * core);	
extern BOOL EvCmdCheckItem(VM_MACHINE * core);
extern BOOL EvCmdWazaMachineItemNoCheck( VM_MACHINE * core );
extern BOOL EvCmdGetPocketNo(VM_MACHINE * core);

//未使用
extern BOOL EvCmdAddPCBoxItem( VM_MACHINE * core );
extern BOOL EvCmdCheckPCBoxItem( VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_ITEM_H */
