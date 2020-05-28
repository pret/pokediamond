//============================================================================================
/**
 * @file	scr_wazalist.h
 * @bfief	�X�N���v�g�R�}���h�F�킴�I����ʊ֘A
 * @author	Tomomichi Ohta
 * @date	06.07.08
 */
//============================================================================================
#ifndef SCR_WAZALIST_H
#define SCR_WAZALIST_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

extern BOOL EvCmdWazaListSetProc( VM_MACHINE * core );
extern BOOL EvCmdWazaListGetResult(VM_MACHINE * core);
extern BOOL EvCmdOshieWazaCount(VM_MACHINE * core);
extern BOOL EvCmdRemaindWazaCount(VM_MACHINE * core);
extern BOOL EvCmdOshieWazaListSetProc(VM_MACHINE * core);
extern BOOL EvCmdRemaindWazaListSetProc(VM_MACHINE * core);
extern BOOL EvCmdOshieWazaListGetResult(VM_MACHINE * core);
extern BOOL EvCmdRemaindWazaListGetResult(VM_MACHINE * core);
extern BOOL EvCmdNormalWazaListSetProc(VM_MACHINE * core);
extern BOOL EvCmdNormalWazaListGetResult(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */

#endif	/* SCR_POKE_H */
