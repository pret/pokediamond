//============================================================================================
/**
 * @file	scr_poke.h
 * @bfief	�X�N���v�g�R�}���h�F�|�P��������֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_POKE_H
#define SCR_POKE_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddPokemon(VM_MACHINE * core);
extern BOOL EvCmdTemotiMonsNo(VM_MACHINE * core);
extern BOOL EvCmdMonsOwnChk(VM_MACHINE * core);
extern BOOL EvCmdAddTamago(VM_MACHINE * core);
extern BOOL EvCmdChgPokeWaza( VM_MACHINE * core );
extern BOOL EvCmdChkPokeWaza( VM_MACHINE * core );
extern BOOL EvCmdChkPokeWazaGroup( VM_MACHINE * core );
extern BOOL EvCmdApprovePoisonDead(VM_MACHINE * core);
extern BOOL EvCmdPokeLevelChk(VM_MACHINE * core);
extern BOOL EvCmdPokeLevelGet(VM_MACHINE * core);
extern BOOL EvCmdChkPokeSeikakuAll(VM_MACHINE * core);
extern BOOL EvCmdGetPokeSeikaku(VM_MACHINE * core);
extern BOOL EvCmdGetNatsuki( VM_MACHINE * core );
extern BOOL EvCmdAddNatsuki( VM_MACHINE * core );
extern BOOL EvCmdSubNatsuki( VM_MACHINE * core );
extern BOOL EvCmdTemotiPokeContestStatusGet( VM_MACHINE * core );
extern BOOL EvCmdFrontPokemon(VM_MACHINE * core);
extern BOOL EvCmdTemotiPokeType(VM_MACHINE * core);
extern BOOL EvCmdGetPokeCount( VM_MACHINE * core );
extern BOOL EvCmdGetPokeCount2( VM_MACHINE * core );
extern BOOL EvCmdGetPokeCount3( VM_MACHINE * core );
extern BOOL EvCmdGetPokeCount4( VM_MACHINE * core );
extern BOOL EvCmdGetTamagoCount( VM_MACHINE * core );
extern BOOL EvCmdChkTemotiPokerus( VM_MACHINE * core );
extern BOOL EvCmdTemotiPokeSexGet( VM_MACHINE * core );
extern BOOL EvCmdWazaCount( VM_MACHINE * core );
extern BOOL EvCmdWazaDel( VM_MACHINE * core );
extern BOOL EvCmdTemotiWazaNo( VM_MACHINE * core );
extern BOOL EvCmdPokeMailChk(VM_MACHINE * core);
extern BOOL EvCmdPokeMailDel(VM_MACHINE * core);
extern BOOL EvCmdTemotiPokeChk( VM_MACHINE * core );
extern BOOL EvCmdChkRibbonCount(VM_MACHINE * core);
extern BOOL EvCmdChkRibbonCountAll(VM_MACHINE * core);
extern BOOL EvCmdChkRibbon(VM_MACHINE * core);
extern BOOL EvCmdSetRibbon(VM_MACHINE * core);
extern BOOL EvCmdDameTamagoChkAll(VM_MACHINE * core);

//���g�p
extern  EvCmdGetTemotiPokeNum( VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */

#endif	/* SCR_POKE_H */
