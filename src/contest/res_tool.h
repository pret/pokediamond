//==============================================================================
/**
 * @file	res_tool.h
 * @brief	���ʔ��\��ʃc�[���ނ̃w�b�_
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#ifndef __RES_TOOL_H__
#define __RES_TOOL_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�_���X����m�[�}����b���b�Z�[�W��ID��`
///(��DanceTalkMsgData�e�[�u���ƕ��т𓯂��ɂ��Ă������I�I)
enum{
	A_TALK_CONRES_NULL,			///<���b�Z�[�W�w��Ȃ�

	A_TALK_HOST_01,
	A_TALK_HOST_02,
	A_TALK_HOST_03,
	A_TALK_HOST_04,
	A_TALK_HOST_05,
	A_TALK_HOST_06,
};

//--------------------------------------------------------------
//	RT_WndOpenEffStart�֐��̈����Ɏg�p
//--------------------------------------------------------------
enum{
	RT_WNDEFF_OPEN,			///<�E�B���h�E�J��
	RT_WNDEFF_CLOSE,		///<�E�B���h�E����
};

//--------------------------------------------------------------
//	PokeSlideEffectStart�֐��̈����Ɏg�p
//--------------------------------------------------------------
enum{
	RT_POKESLIDE_IN,		///<�|�P�����o��
	RT_POKESLIDE_OUT,		///<�|�P�����ޏ�
};

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void RT_SoftSpriteAddAll(CONRES_PROC_WORK *cpw);
extern void RT_SoftSpriteDelAll(CONRES_SYSTEM_PARAM *sys);
extern void RT_A_TalkMessageSet(CONRES_PROC_WORK *cpw, u32 a_talk_id, const CRTAG_PARAM *tagpara);
extern int RT_TalkMessageEndCheck(CONRES_PROC_WORK *cpw);
extern void RT_Announce_BGSet(CONRES_PROC_WORK *rpw);
extern void RT_Announce_BGDel(CONRES_PROC_WORK *rpw);
extern void RT_Announce_OBJSet(CONRES_PROC_WORK *rpw);
extern void RT_Announce_OBJDel(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGSet(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGDel(CONRES_PROC_WORK *rpw);
extern void RT_Result_OBJSet(CONRES_PROC_WORK *rpw);
extern void RT_Result_OBJDel(CONRES_PROC_WORK *rpw);
extern void RT_PokeIconSetAll(CONRES_PROC_WORK *rpw);
extern void RT_PokeIconDelAll(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiResouceLoad(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiResouceFree(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconSetAll(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconDelAll(CONRES_PROC_WORK *rpw);
extern void RT_WndOpenEffStart(CONRES_PROC_WORK *rpw, int open_close, u8 *end_flag);
extern void PokeSlideEffectStart(CONRES_PROC_WORK *rpw, int breeder_no, int in_out, u8 *end_flag);
extern void RT_ConfettiCreateTaskSet(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiEndFlagSet(CONRES_PROC_WORK *rpw);
extern void RT_CalcPoint(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconAppearSet(CONRES_PROC_WORK *rpw, int breeder_no, int ranking);
extern void RT_MeterResouceLoad(CONRES_PROC_WORK *rpw);
extern void RT_MeterResouceFree(CONRES_PROC_WORK *rpw);
extern void RT_MeterActorDotCreate(CONRES_PROC_WORK *rpw, int breeder_no, int con_game, 
	int dot, int breeder_pos);
extern void RT_MeterActorDeleteAll(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGSet_Sub(CONRES_PROC_WORK *rpw);
extern void RT_CalcRevicePoint(CONTEST_SYSTEM *consys, int con_game, s16 ret_revise[]);


#endif	//__RES_TOOL_H__

