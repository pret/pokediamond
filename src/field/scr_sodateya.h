//============================================================================================
/**
 * @file	scr_sodateya.h
 * @bfief	�X�N���v�g�R�}���h�F�����Ă�֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_SODATEYA_H
#define SCR_SODATEYA_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdGetSodateyaName( VM_MACHINE * core );
extern BOOL EvCmdGetSodateyaZiisan( VM_MACHINE * core );
extern BOOL EvCmdDelSodateyaEgg( VM_MACHINE * core );
extern BOOL EvCmdGetSodateyaEgg( VM_MACHINE * core );
extern BOOL EvCmdHikitoriPoke( VM_MACHINE * core );
extern BOOL EvCmdHikitoriRyoukin( VM_MACHINE * core );

extern BOOL EvCmdSodatePokeLevelStr( VM_MACHINE * core );
extern BOOL EvCmdMsgAzukeSet( VM_MACHINE * core );
extern BOOL EvCmdSetSodateyaPoke( VM_MACHINE * core );
extern BOOL EvCmdHikitoriListNameSet( VM_MACHINE * core );
extern BOOL EvCmdGetSodateyaAishou( VM_MACHINE * core );
extern BOOL EvCmdGetSodateyaTamagoCheck( VM_MACHINE * core );

/*���g�p*/
extern BOOL EvCmdHikitoriList( VM_MACHINE * core );
extern BOOL EvCmdMsgSodateyaAishou( VM_MACHINE * core );
extern BOOL EvCmdMsgExpandBuf( VM_MACHINE * core );
extern BOOL EvCmdSodateyaPokeList( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_SODATEYA_H */
