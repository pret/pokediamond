//============================================================================================
/**
 * @file	scr_shop.h
 * @bfief	�X�N���v�g�R�}���h�F�V���b�v�֘A
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#ifndef SCR_SHOP_H
#define SCR_SHOP_H


//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdShopCall( VM_MACHINE * core );
extern BOOL EvCmdFixShopCall( VM_MACHINE * core );
extern BOOL EvCmdFixGoodsCall( VM_MACHINE * core );
extern BOOL EvCmdFixSealCall( VM_MACHINE * core );
extern BOOL EvCmdAcceShopCall( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_SHOP_H */


