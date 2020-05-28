//============================================================================================
/**
 * @file	scr_gold.h
 * @bfief	�X�N���v�g�R�}���h�F�����֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_GOLD_H
#define SCR_GOLD_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddGold(VM_MACHINE * core);
extern BOOL EvCmdSubGold(VM_MACHINE * core);
extern BOOL EvCmdCompGold(VM_MACHINE * core);
extern BOOL EvCmdGoldWinWrite(VM_MACHINE * core);	
extern BOOL EvCmdGoldWinDel(VM_MACHINE * core);
extern BOOL EvCmdGoldWrite(VM_MACHINE * core);	
extern BOOL EvCmdSubMyGold( VM_MACHINE * core );
extern BOOL EvCmdCompMyGold( VM_MACHINE * core );

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_GOLD_H */

