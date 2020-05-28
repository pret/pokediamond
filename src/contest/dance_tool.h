//==============================================================================
/**
 * @file	dance_tool.h
 * @brief	�r�W���A������c�[���ނ̃w�b�_
 * @author	matsuda
 * @date	2005.12.10(�y)
 */
//==============================================================================
#ifndef __DANCE_TOOL_H__
#define __DANCE_TOOL_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�|�P�����풓�A�j���F���N�G�X�g��`
typedef enum{
	PDA_REQ_AFF_SET,			///<�g�k�A�j���ғ�
	PDA_REQ_AFF_STOP,			///<�g�k�A�j������~
	PDA_REQ_AFF_STOP_REQ,		///<�g�k�A�j����~���N�G�X�g(�ʏ�T�C�Y�ɖ߂������~)
	PDA_REQ_MOVE_SET,			///<�ړ��A�j���ғ�
	PDA_REQ_MOVE_STOP,			///<�ړ��A�j������~
	PDA_REQ_MOVE_STOP_REQ,		///<�ړ��A�j����~���N�G�X�g(�ʏ�ʒu�ɖ߂������~)
}PDA_REQ;

///�_���X����m�[�}����b���b�Z�[�W��ID��`
///(��DanceTalkMsgData�e�[�u���ƕ��т𓯂��ɂ��Ă������I�I)
enum{
	A_TALK_DANCE_NULL,			///<���b�Z�[�W�w��Ȃ�

	A_TALK_BEGIN_HOST_01,
	A_TALK_BEGIN_HOST_PRACTICE_01,
	A_TALK_END_HOST_01,
	A_TALK_BEGIN_HOST_02,
	A_TALK_BEGIN_HOST_03,
	A_TALK_AFTER_01,
	A_TALK_PRAC_DPREFACE,
};

///���A�N�^�[�̃A�j���V�[�P���X
enum{
	DANCE_STAR_ANMSEQ_BIG,		//�傫����
	DANCE_STAR_ANMSEQ_SMALL,	//��������
};

//--------------------------------------------------------------
//	���C�g
//--------------------------------------------------------------
///�|�P�����ɓ��Ă郉�C�g�̐F�F�m�[�}��
#define IMC_LIGHT_COLOR_NORMAL		(0x7fff)
///�|�P�����ɓ��Ă郉�C�g�̐F�F��
#define IMC_LIGHT_COLOR_BLACK		(0x254a)


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void DT_SoftSpriteAddAll(DANCE_PROC_WORK *dpw);
extern void DT_SoftSpriteDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_HeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_HeartResourceFree(CATS_RES_PTR crp);
extern s16 DT_RotationPosGetX(int rotation_pos);
extern s16 DT_RotationPosGetY(int rotation_pos);
extern s16 DT_RotationPosGetZ(int rotation_pos);
extern void DT_MusicBarAnimeUpdate(DANCE_SYSTEM_PARAM *sys, int len);
extern void DT_MusicBarAnimeUpdateFrame(DANCE_SYSTEM_PARAM *sys, int now_frame, int end_frame);
extern void DT_OnpuResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_OnpuResourceFree(CATS_RES_PTR crp);
extern void DT_OnpuActorDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_ReviewPanelResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_ReviewPanelResourceFree(CATS_RES_PTR crp);
extern void DT_ReviewPanelActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_ReviewPanelActorDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_MyCursorResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_MyCursorResourceFree(CATS_RES_PTR crp);
extern void DT_MyCursorActorSet(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_MyCursorActorDel(DANCE_SYSTEM_PARAM *sys);
extern void DT_FumenColorSet(DANCE_SYSTEM_PARAM *sys, FUMENCOLOR_TYPE color_type);
extern void DT_PokeAffineUpdateZ(SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork);
extern void DT_PokeAffineUpdateZAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_ReviewFontOamCreateAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_ReviewFontOamDeleteAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_MyCursorTaskSet(DANCE_PROC_WORK *dpw);
extern void DT_MyCursorTaskDel(DANCE_PROC_WORK *dpw);
extern void DT_ReviewPanelTaskSet(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int review_type, int breeder_no, u8 rotation_pos);
extern void DT_DancingParamRecieve(DANCE_PROC_WORK *dpw, const DANCING_PARAM *dancing_param);
extern void DT_DanceMoveTaskSet(DANCE_PROC_WORK *dpw);
extern void DT_DanceMoveTaskDel(DANCE_PROC_WORK *dpw);
extern void DT_MainDancerRecordInit(DANCE_PROC_WORK *dpw);
extern void DT_ReviewPanelTaskDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_PokemonDefaultAnimeTaskDelAll(DANCE_PROC_WORK *dpw);
extern void DT_PokemonDefaultAnimeReq(DANCE_PROC_WORK *dpw, int breeder_no, PDA_REQ req);
extern int DT_PokemonDefaultAnimeStopCheckAff(DANCE_PROC_WORK *dpw, int breeder_no);
extern int DT_PokemonDefaultAnimeStopCheckMove(DANCE_PROC_WORK *dpw, int breeder_no);
extern void DT_PokemonDefaultAnimeTaskSet(DANCE_PROC_WORK *dpw, int breeder_no, int rotation_pos);
extern BOOL DT_DanceMoveStepNoneAllCheck(DANCE_PROC_WORK *dpw);
extern void DT_A_TalkMessageSet(DANCE_PROC_WORK *dpw, u32 a_talk_id, const DTAG_PARAM *tagpara);
extern int DT_TalkMessageEndCheck(DANCE_PROC_WORK *dpw);
extern void DT_PrinResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_PrinResourceFree(CATS_RES_PTR crp);
extern void DT_PrinCreate(DANCE_PROC_WORK *dpw, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_PrinFree(DANCE_PROC_WORK *dpw);
extern void PrinReq_FrameUpdate(PRIN_WORK *pw, u32 now_frame, u32 end_frame);
extern void PrinReq_OutMove(PRIN_WORK *pw);
extern void PrinReq_InMove(PRIN_WORK *pw);
extern int DT_DanceNumGet(int con_rank);
extern void DT_PanelMessagePut(DANCE_PROC_WORK *dpw, u32 a_talk_id, const DTAG_PARAM *tagpara);
extern void DT_PanelMessageClear(DANCE_PROC_WORK *dpw);
extern s64 DT_ReadyEndFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, 
	int now_count);
extern s64 DT_RotationEndFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, 
	int now_count);
extern s64 DT_DancingStartFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, 
	int now_count);
extern void DT_ShadowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_ShadowResourceFree(CATS_RES_PTR crp);
extern void DT_ShadowActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_ShadowActorDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_ShadowHomingFlagSet(SHADOW_WORK *shadow, int flag, int jump_flag);
extern void DT_SpotLightResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_SpotLightResourceFree(CATS_RES_PTR crp);
extern void DT_SpotLightActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_SpotLightActorDelAll(DANCE_SYSTEM_PARAM *sys);
extern void DT_StarResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void DT_StarResourceFree(CATS_RES_PTR crp);
extern BOOL DT_StarActorSet(DANCE_PROC_WORK *dpw, int breeder_no, int anm_seq);
extern void DT_ShadowEnableSet(DANCE_SYSTEM_PARAM *sys, int enable);
extern void DT_PokeAppealMove(DANCE_PROC_WORK *dpw, int breeder_no, u8 *end_flag);
extern void DT_BGAlphaDefaultDataSet(DANCE_PROC_WORK *dpw);
extern void DT_BGAlphaEffectSet(DANCE_PROC_WORK *dpw, int bgalpha_type);
extern void DT_BGAlphaDefaultBlendModeSet(void);
extern void DT_BGAlphaEffectSet_MainDancerHistory(DANCE_PROC_WORK *dpw, u32 frame);
extern void DT_FumenFlashTaskSet(DANCE_PROC_WORK *dpw);
extern void DT_FumenFlashTaskDel(DANCE_PROC_WORK *dpw);
extern void DT_FumenFlashEffectSet(DANCE_PROC_WORK *dpw, int dancer_type);
extern void DT_EmitterCreate(DANCE_PROC_WORK *dpw, u32 res_no, 
	s32 x, s32 y, s32 z, fx32 gen_num);
extern void DT_MiddlePaletteFadeReq(DANCE_PROC_WORK *dpw, u32 fade_bit, u32 frame, 
	int start_evy, int end_evy, u16 next_rgb);
extern BOOL DT_MiddlePaletteFadeCheck(DANCE_PROC_WORK *dpw);
extern void DT_MiddlePaletteOccSet(DANCE_PROC_WORK *dpw, int occ);
extern void DT_DancerLightEffectSet(DANCE_PROC_WORK *dpw, int main_dancer_breeder_no, 
	int dancer_type);
extern void DT_DancerLightEffectOff(DANCE_PROC_WORK *dpw);
extern void DT_DancerLightEffectAllOn(DANCE_PROC_WORK *dpw);
extern void DT_DancerLightFadeReq(DANCE_PROC_WORK *dpw, int breeder_no, 
	GXRgb start_color, GXRgb next_color, int end_evy, int frame, u8 *end_flag);
extern void DT_DancerLightRankingSet(DANCE_PROC_WORK *dpw);
extern BOOL DanceJump_PokeCheck(u32 monsno);


#endif	//__DANCE_TOOL_H__

