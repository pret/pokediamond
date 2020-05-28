//============================================================================================
/**
 * @file	scr_trainer.h
 * @bfief	�X�N���v�g�R�}���h�F�g���[�i�[�֘A
 * @author	Satoshi Nohara
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_TRAINER_H
#define SCR_TRAINER_H


//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdEyeTrainerMoveSet( VM_MACHINE * core );
extern BOOL EvCmdEyeTrainerMoveCheck( VM_MACHINE * core );
extern BOOL EvCmdEyeTrainerTypeGet( VM_MACHINE * core );
extern BOOL EvCmdEyeTrainerIdGet( VM_MACHINE * core );
extern BOOL EvCmdTrainerIdGet( VM_MACHINE * core );
extern BOOL EvCmdTrainerBattleSet( VM_MACHINE * core );
extern BOOL EvCmdTrainerMultiBattleSet( VM_MACHINE * core );
extern BOOL EvCmdTrainerTalkTypeGet( VM_MACHINE * core );
extern BOOL EvCmdRevengeTrainerTalkTypeGet( VM_MACHINE * core );
extern BOOL EvCmdTrainerTypeGet( VM_MACHINE * core );
extern BOOL EvCmdTrainerBgmSet( VM_MACHINE * core );
extern BOOL EvCmdTrainerLose( VM_MACHINE * core );
extern BOOL EvCmdTrainerLoseCheck( VM_MACHINE * core );
extern BOOL EvCmdSeacretPokeRetryCheck( VM_MACHINE * core );
extern BOOL EvCmdHaifuPokeRetryCheck( VM_MACHINE * core );
extern BOOL EvCmd2vs2BattleCheck( VM_MACHINE * core );
extern BOOL EvCmdDebugBattleSet( VM_MACHINE * core );
extern BOOL EvCmdDebugTrainerFlagSet( VM_MACHINE * core );
extern BOOL EvCmdDebugTrainerFlagOnJump( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_TRAINER_H */



