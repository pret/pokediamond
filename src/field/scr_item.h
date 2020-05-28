//============================================================================================
/**
 * @file	scr_item.h
 * @bfief	�X�N���v�g�R�}���h�F�A�C�e���֘A
 * @author	Tomomichi Ohta
 * @date	06.06.30
 */
//============================================================================================
#ifndef SCR_ITEM_H
#define SCR_ITEM_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddItem(VM_MACHINE * core);
extern BOOL EvCmdSubItem(VM_MACHINE * core);
extern BOOL EvCmdAddItemChk(VM_MACHINE * core);	
extern BOOL EvCmdCheckItem(VM_MACHINE * core);
extern BOOL EvCmdWazaMachineItemNoCheck( VM_MACHINE * core );
extern BOOL EvCmdGetPocketNo(VM_MACHINE * core);

//���g�p
extern BOOL EvCmdAddPCBoxItem( VM_MACHINE * core );
extern BOOL EvCmdCheckPCBoxItem( VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_ITEM_H */
