
//============================================================================================
/**
 * @file	fight.h
 * @bfief	�퓬���C���v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __FIGHT_H_
#define __FIGHT_H_

#include "battle/battle_common.h"
#include "system/procsys.h"

#define	TALK_WIN_CGX_START	(1)			///<��b�E�C���h�E�L�����ǂݍ��ݐ�
#define	TALK_WIN_PAL_NO		(10)		///<��b�E�C���h�E�p���b�g�i���o�[
#define	TALK_MSG_PAL_NO		(11)		///<��b�E�C���h�E�����b�Z�[�W�p���b�g�i���o�[
#define	TALK_MSG_START		(TALK_WIN_CGX_SIZ+1)	///<��b�E�C���h�E�����b�Z�[�W�L�����X�^�[�g�ʒu
#define	TALK_WIN_NO			(0)			///<��b�E�C���h�ENo
#define	TALK_WIN_X			(0x02)		///<��b�E�C���h�E����X�ʒu
#define	TALK_WIN_Y			(0x13)		///<��b�E�C���h�E����X�ʒu
#define	TALK_WIN_SIZE_X		(27)		///<��b�E�C���h�EX�T�C�Y
#define	TALK_WIN_SIZE_Y		(4)			///<��b�E�C���h�EY�T�C�Y
#define	TALK_PAL_BIT		(0x0c00)	///<��b�E�C���h�E�p���b�g�r�b�g

//���x���A�b�v�X�e�[�^�X�E�C���h�E
#define	MENU_WIN_CGX_START	(1)			///<���j���[�E�C���h�E�L�����ǂݍ��ݐ�
#define	MENU_WIN_PAL_NO		(8)			///<���j���[�E�C���h�E�p���b�g�i���o�[
#define	MENU_MSG_PAL_NO		(11)		///<���j���[�E�C���h�E�����b�Z�[�W�p���b�g�i���o�[
#define	MENU_MSG_START		(MENU_WIN_CGX_SIZ+1)	   ///<���j���[�E�C���h�E�����b�Z�[�W�L�����X�^�[�g�ʒu
#define	MENU_WIN_NO			(1)			///<���j���[�E�C���h�ENo
#define	MENU_WIN_X			(0x11)		///<���j���[�E�C���h�E����X�ʒu
#define	MENU_WIN_Y			(0x07)		///<���j���[�E�C���h�E����X�ʒu
#define	MENU_WIN_SIZE_X		(14)		///<���j���[�E�C���h�EX�T�C�Y
#define	MENU_WIN_SIZE_Y		(12)		///<���j���[�E�C���h�EY�T�C�Y

#define	TAG_WIN_NO			(2)			///<�^�O�E�C���h�ENo
#define	TAG_WIN_X			(0x11)		///<���j���[�E�C���h�E����X�ʒu
#define	TAG_WIN_Y			(0x01)		///<���j���[�E�C���h�E����X�ʒu
#define	TAG_WIN_SIZE_X		(14)		///<���j���[�E�C���h�EX�T�C�Y
#define	TAG_WIN_SIZE_Y		(4)			///<���j���[�E�C���h�EY�T�C�Y



//�퓬�V�X�e���u�[�g�p�����[�^
typedef struct
{
	u8	client_no;
	u8	client_type;
}FIGHT_SYSTEM_BOOT_PARAM;

extern	BOOL	BattleSystemProc(PROC *proc,int *seq);
extern	void	FightScreenTransition(BATTLE_WORK *bw);
extern	void	FightScreenEnd(BATTLE_WORK *bw);
extern	void	FightScreenRecover(BATTLE_WORK *bw);
extern	void	FightScreenPokemonGetEnd(BATTLE_WORK *bw);
extern	void	FightScreenPokemonGet(BATTLE_WORK *bw);

#endif __FIGHT_H_
