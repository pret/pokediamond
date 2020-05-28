//============================================================================================
/**
 * @file	scr_goods.h
 * @bfief	�X�N���v�g�R�}���h�F�O�b�Y�֘A
 * @author	Tomomichi Ohta
 * @date	06.06.30
 */
//============================================================================================
#ifndef SCR_GOODS_H
#define SCR_GOODS_H

//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdAddGoods(VM_MACHINE * core);
extern BOOL EvCmdSubGoods(VM_MACHINE * core);
extern BOOL EvCmdAddGoodsChk(VM_MACHINE * core);
extern BOOL EvCmdCheckGoods(VM_MACHINE * core);
extern BOOL EvCmdAddTrap(VM_MACHINE * core);
extern BOOL EvCmdSubTrap(VM_MACHINE * core);
extern BOOL EvCmdAddTrapChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTrap(VM_MACHINE * core);
extern BOOL EvCmdAddTreasure(VM_MACHINE * core);
extern BOOL EvCmdSubTreasure(VM_MACHINE * core);
extern BOOL EvCmdAddTreasureChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTreasure(VM_MACHINE * core);
extern BOOL EvCmdAddTama(VM_MACHINE * core);
extern BOOL EvCmdSubTama(VM_MACHINE * core);
extern BOOL EvCmdAddTamaChk(VM_MACHINE * core);
extern BOOL EvCmdCheckTama(VM_MACHINE * core);

#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_GOODS_H */

