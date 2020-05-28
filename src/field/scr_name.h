//============================================================================================
/**
 * @file	scr_name.h
 * @bfief	スクリプトコマンド：名前関連
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#ifndef SCR_NAME_H
#define SCR_NAME_H


//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdPlayerName(VM_MACHINE * core );
extern BOOL EvCmdRivalName(VM_MACHINE * core ); 
extern BOOL EvCmdSupportName(VM_MACHINE * core );
extern BOOL EvCmdPokemonName(VM_MACHINE * core );
extern BOOL EvCmdItemName(VM_MACHINE * core );
extern BOOL EvCmdPocketName(VM_MACHINE * core );
extern BOOL EvCmdItemWazaName(VM_MACHINE * core );
extern BOOL EvCmdWazaName(VM_MACHINE * core );
extern BOOL EvCmdNumberName(VM_MACHINE * core );
extern BOOL EvCmdNumberNameEx(VM_MACHINE * core );
extern BOOL EvCmdNickName(VM_MACHINE * core );
extern BOOL EvCmdNickNamePC(VM_MACHINE * core );
extern BOOL EvCmdPoketchName(VM_MACHINE * core );
extern BOOL EvCmdTrTypeName(VM_MACHINE * core );
extern BOOL EvCmdMyTrTypeName(VM_MACHINE * core );
extern BOOL EvCmdPokemonNameExtra(VM_MACHINE * core );
extern STRBUF * PokeNameGetAlloc( u16 id, u32 heap );
extern BOOL EvCmdFirstPokemonName(VM_MACHINE * core );
extern BOOL EvCmdRivalPokemonName(VM_MACHINE * core );
extern BOOL EvCmdSupportPokemonName(VM_MACHINE * core );
extern BOOL EvCmdGoodsName(VM_MACHINE * core );
extern BOOL EvCmdTrapName(VM_MACHINE * core );
extern BOOL EvCmdTamaName(VM_MACHINE * core );
extern BOOL EvCmdZoneName(VM_MACHINE * core );
extern BOOL EvCmdNutsName(VM_MACHINE * core);
extern BOOL EvCmdSeikakuName(VM_MACHINE * core);
extern BOOL EvCmdAcceName(VM_MACHINE * core );
extern BOOL EvCmdMonumantName(VM_MACHINE * core ) ;
extern BOOL EvCmdTemotiWazaName( VM_MACHINE * core );
extern BOOL EvCmdRibbonName(VM_MACHINE * core);
extern BOOL EvCmdSealName(VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_NAME_H */


