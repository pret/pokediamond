//============================================================================================
/**
 * @file	scr_dprint.h
 * @bfief	�X�N���v�g�R�}���h�F�f�o�b�O�\���֘A
 * @author	Tomomichi Ohta
 * @date	06.07.08
 */
//============================================================================================
#ifndef SCR_DPRINT_H
#define SCR_DPRINT_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdDebugPrintWork(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintFlag(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintWorkStationed(VM_MACHINE * core);
extern BOOL EvCmdDebugPrintFlagStationed(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */

#endif	/* SCR_DPRINT_H */
