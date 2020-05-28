//============================================================================================
/**
 * @file	scr_coin.h
 * @bfief	�X�N���v�g�R�}���h�F�R�C���֘A
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_COIN_H
#define SCR_COIN_H


//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdCoinWinWrite(VM_MACHINE * core);
extern BOOL EvCmdCoinWinDel(VM_MACHINE * core);
extern BOOL EvCmdCoinWrite(VM_MACHINE * core);
extern BOOL EvCmdCheckCoin( VM_MACHINE * core );
extern BOOL EvCmdAddCoin( VM_MACHINE * core );
extern BOOL EvCmdSubCoin( VM_MACHINE * core );
extern BOOL EvCmdSubWkCoin( VM_MACHINE * core );
extern BOOL EvCmdCompCoin( VM_MACHINE * core );
extern BOOL EvCmdCompWkCoin( VM_MACHINE * core );
extern BOOL EvCmdAddCoinChk(VM_MACHINE * core);
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_COIN_H */


