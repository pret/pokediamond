//==============================================================================
/**
 * @file	visual_tool.h
 * @brief	�r�W���A������c�[���ނ̃w�b�_
 * @author	matsuda
 * @date	2005.12.10(�y)
 */
//==============================================================================
#ifndef __VISUAL_TOOL_H__
#define __VISUAL_TOOL_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�r�W���A������m�[�}����b���b�Z�[�W��ID��`
///(��VisualTalkMsgData�e�[�u���ƕ��т𓯂��ɂ��Ă������I�I)
enum{
	A_TALK_VISUAL_NULL,			///<���b�Z�[�W�w��Ȃ�
	
	A_TALK_VISUAL_HOST_01,
	A_TALK_VISUAL_HOST_PRACTICE_01,
	A_TALK_VISUAL_HOST_02,
	A_TALK_VISUAL_HOST_03,
	A_TALK_VISUAL_HOST_04,
	A_TALK_VISUAL_HOST_05,
	A_TALK_VISUAL_HOST_06,
	A_TALK_VISUAL_HOST_07,
	A_TALK_VISUAL_HOST_08,
	A_TALK_VISUAL_HOST_09,
	A_TALK_VISUAL_HOST_10,
	A_TALK_VISUAL_HOST_11,
	A_TALK_VISUAL_HOST_12,
	A_TALK_VISUAL_HOST_13,
};


///�ϋq�n�[�g�̃A�j���^�C�v
enum{
	AUDIENCE_HEART_ANMTYPE_BP,		///<�u���[�_�[�|�C���g�ɂ��n�[�g
	AUDIENCE_HEART_ANMTYPE_CLIP,	///<�N���b�v�ɂ��n�[�g
};


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void VT_SoftSpriteAdd(VISUAL_SYSTEM_PARAM *sys, int breeder_no);
extern void VT_SoftSpriteDel(VISUAL_SYSTEM_PARAM *sys, int breeder_no);
extern void VT_SoftSpriteAddAll(VISUAL_SYSTEM_PARAM *sys);
extern void VT_SoftSpriteDelAll(VISUAL_SYSTEM_PARAM *sys);
extern void VT_AudienceHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void VT_AudienceHeartResourceFree(CATS_RES_PTR crp);
extern void VT_TrainerAdd(VISUAL_PROC_WORK *vpw, int breeder_no);
extern void VT_TrainerDel(VISUAL_PROC_WORK *vpw);
extern void VT_A_TalkMessageSet(VISUAL_PROC_WORK *vpw, u32 a_talk_id, const VTAG_PARAM *tagpara);
extern int VT_TalkMessageEndCheck(VISUAL_PROC_WORK *vpw);
extern void VT_AudienceHeartActorAdd(VISUAL_PROC_WORK *vpw, int x, int y, 
	fx32 angle, int anm_type);
extern u32 VT_A_TalkIDGet_BPAppeal(int con_type);


#endif	//__VISUAL_TOOL_H__

