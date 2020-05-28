//============================================================================================
/**
 * @file	scr_kaseki.h
 * @bfief	�X�N���v�g�R�}���h�F�J�Z�L����֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_KASEKI_H
#define SCR_KASEKI_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdKasekiCount(VM_MACHINE * core);
extern BOOL EvCmdItemNoToMonsNo(VM_MACHINE * core);
extern BOOL EvCmdKasekiItemNo(VM_MACHINE * core);

//���g�p
extern BOOL EvCmdItemListSetProc(VM_MACHINE * core);
extern BOOL EvCmdItemListGetResult(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_KASEKI_H */

