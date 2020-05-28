//============================================================================================
/**
 * @file	scr_sound.h
 * @bfief	スクリプトコマンド：サウンド関連
 * @author	Satoshi Nohara
 * @date	06.06.26
 */
//============================================================================================
#ifndef SCR_SOUND_H
#define SCR_SOUND_H


//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdBgmPlayCheck(VM_MACHINE * core );
extern BOOL EvCmdBgmPlay(VM_MACHINE * core );
extern BOOL EvCmdBgmStop(VM_MACHINE * core );
extern BOOL EvCmdBgmNowMapPlay(VM_MACHINE * core );
extern BOOL EvCmdBgmSpecialSet(VM_MACHINE * core );
extern BOOL EvCmdBgmFadeOut( VM_MACHINE * core );
extern BOOL EvWaitBgmFade( VM_MACHINE * core );
extern BOOL EvCmdBgmFadeIn( VM_MACHINE * core );
extern BOOL EvCmdBgmPlayerPause( VM_MACHINE * core );
extern BOOL EvCmdPlayerFieldDemoBgmPlay( VM_MACHINE * core );
extern BOOL EvCmdCtrlBgmFlagSet( VM_MACHINE * core );
extern BOOL EvCmdSePlay( VM_MACHINE * core );
extern BOOL EvCmdSeStop( VM_MACHINE * core );
extern BOOL EvCmdSeWait(VM_MACHINE * core);
extern BOOL EvCmdVoicePlay( VM_MACHINE * core );
extern BOOL EvCmdVoicePlayWait( VM_MACHINE * core );
extern BOOL EvCmdMePlay(VM_MACHINE * core );
extern BOOL EvCmdMeWait(VM_MACHINE * core );
extern BOOL EvCmdPerapDataCheck( VM_MACHINE * core );
extern BOOL EvCmdPerapRecStart( VM_MACHINE * core );
extern BOOL EvCmdPerapRecStop( VM_MACHINE * core );
extern BOOL EvCmdPerapSave( VM_MACHINE * core );
extern BOOL EvCmdSndClimaxDataLoad( VM_MACHINE * core );
extern BOOL EvCmdSndInitialVolSet( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_SOUND_H */



