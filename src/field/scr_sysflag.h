//============================================================================================
/**
 * @file	scr_sysflag.h
 * @bfief	スクリプトコマンド：SYSFLAG操作関連
 * @author	Tomomichi Ohta
 * @date	06.06.30
 */
//============================================================================================
#ifndef SCR_SYSFLAG_H
#define SCR_SYSFLAG_H

//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdSysFlagZukanGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagZukanSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagShoesGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagShoesSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagBadgeGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagBadgeSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagBadgeCount( VM_MACHINE * core );
extern BOOL EvCmdSysFlagBagGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagBagSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagPairGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagPairSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagPairReset( VM_MACHINE * core );
extern BOOL EvCmdSysFlagOneStepGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagOneStepSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagOneStepReset( VM_MACHINE * core );
extern BOOL EvCmdSysFlagGameClearGet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagGameClearSet( VM_MACHINE * core );
extern BOOL EvCmdSysFlagKairiki( VM_MACHINE * core );
extern BOOL EvCmdSysFlagFlash(VM_MACHINE * core);
extern BOOL EvCmdSysFlagKiribarai(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_SYSFLAG_H */


