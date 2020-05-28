//=============================================================================
/**
 * @file	comm_command_contest.h
 * @brief	�ʐM�̃R�}���h�ꗗ  �R���e�X�g�p
 * @author	matsuda
 * @date    2005.12.15(��)
 */
//=============================================================================

#ifndef __COMM_COMMAND_CONTEST_H__
#define __COMM_COMMAND_CONTEST_H__

#include "communication/comm_command.h"
#include "poketool/poke_tool.h"


/// �o�g����p�ʐM�R�}���h�̒�`�B
enum CommCommandBattle_e {
  CC_EXIT_CONTEST = CS_COMMAND_MAX, ///<�R���e�X�g���I�����t�B�[���h�ɖ߂鎖�𑗐M

	CC_TIMING_DATA,				///<�������p
	CC_NORMAL_DATA,				///<�ʏ�f�[�^���M
	CC_DANCE_DATA,				///<�_���X�p�f�[�^���M
	CC_FAST_PARAM,				///<����f�[�^����M
	CC_POKEPARA_DATA,			///<�|�P�����p�����[�^
	CC_POKEPARA_ALL_DATA,		///<�|�P�����p�����[�^(�S����)
	CC_BREEDER_DATA,			///<�u���[�_�[�f�[�^
	CC_JUDGE_DATA,				///<�R���f�[�^
	CC_NAME_DATA,				///<�u���[�_�[��
	CC_IMC_DATA,				///<�N���b�v�f�[�^
	CC_IMC_ALL_DATA,			///<�N���b�v�f�[�^(�S����)
	CC_IMC_LOCAL,				///<�C���[�W�N���b�v��ʗp�f�[�^���M
	CC_IMC_FORCE_END,			///<�C���[�W�N���b�v��ʗp�F�����I���t���O���M
	CC_PERAP_DATA,				///<�؃��b�v�f�[�^
	CC_ETC_DATA,				///<�Œ蒷�ׂ̍����f�[�^�Q
	
  //------------------------------------------------�����܂�
  CC_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������
};

extern void CommCommandContestInitialize(void* pWork);


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern BOOL CommContestSendFastParam(CONTEST_SYSTEM *consys);
extern BOOL CommContestSendPokePara(CONTEST_SYSTEM *consys, int breeder_no, 
	const POKEMON_PARAM *pp);
extern BOOL CommContestSendPokeParaAll(CONTEST_SYSTEM *consys, POKEMON_PARAM **pp);
extern BOOL CommContestSendBreederData(CONTEST_SYSTEM *consys, int breeder_no, const BREEDER_DATA *bd);
extern BOOL CommContestSendJudgeData(CONTEST_SYSTEM *consys, int breeder_no, const JUDGE_DATA *jd);
extern BOOL CommContestSendNameData(CONTEST_SYSTEM *consys, int breeder_no, const STRBUF *name);
extern BOOL CommContestSendClipData(CONTEST_SYSTEM *consys, int breeder_no, const IMC_CONTEST_SAVEDATA *imc_data);
extern BOOL CommContestSendClipDataAll(CONTEST_SYSTEM *consys, IMC_CONTEST_SAVEDATA **imc_data);
extern BOOL CommContestSendImcLocal(CON_IMC_LOCAL *imc_local, u32 counter);
extern BOOL CommContestSendPerap(CONTEST_SYSTEM *consys, int breeder_no, void *perap_voice);
extern BOOL CommContestSendEtcData(CONTEST_SYSTEM *consys, int breeder_no, const CON_ETC_SIO_DATA *etc_data);
extern BOOL CommContestSendImcForceEnd(CON_IMC_LOCAL *imc_local, int force_end);


#endif// __COMM_COMMAND_CONTEST_H__

