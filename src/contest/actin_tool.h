//==============================================================================
/**
 * @file	actin_tool.h
 * @brief	���Z�͕���Ŏg�p����c�[����
 * @author	matsuda
 * @date	2005.11.24(��)
 */
//==============================================================================
#ifndef __ACTIN_TOOL_H__
#define __ACTIN_TOOL_H__


//==============================================================================
//	�萔��`
//==============================================================================
///���Z�͕���m�[�}����b���b�Z�[�W��ID��`(��ActinTalkMsgData�e�[�u���ƕ��т𓯂��ɂ��Ă������I�I)
enum{
	A_TALK_NULL,			///<���b�Z�[�W�w��Ȃ�
	
	A_TALK_SELECT_JUDGE,
	A_TALK_SELECT_WAZA,
	A_TALK_SELECT_WAZA_FINAL,
	A_TALK_WAZA_APPEAL,
	A_TALK_JUDGE_LOOK,
	A_TALK_JUDGE_SUFFER,
	A_TALK_JUDGE_SUFFER0002,
	A_TALK_JUDGE_SUFFER0003,
	A_TALK_JUDGE_SUFFER0004,
	A_TALK_NO_JUDGE_SUFFER,
	A_TALK_VOLTAGE_UP_1,
	A_TALK_VOLTAGE_UP_2,
	A_TALK_VOLTAGE_UP_3,
	A_TALK_VOLTAGE_UP_4,
	A_TALK_VOLTAGE_UP_5,
	A_TALK_VOLTAGE_UP_6,
	A_TALK_VOLTAGE_SUB_1,
	A_TALK_VOLTAGE_SUB_10,
	A_TALK_VOLTAGE_SUB_2,
	A_TALK_VOLTAGE_SUB_3,
	A_TALK_VOLTAGE_SUB_4,
	A_TALK_VOLTAGE_SUB_5,
	A_TALK_VOLTAGE_STATE_UP_2,
	A_TALK_VOLTAGE_STATE_UP_3,
	A_TALK_VOLTAGE_STATE_UP_4,
	A_TALK_VOLTAGE_STATE_UP_5,
	A_TALK_VOLTAGE_STATE_SUB_3,
	A_TALK_VOLTAGE_STATE_SUB_2,
	A_TALK_VOLTAGE_STATE_SUB_1,
	A_TALK_VOLTAGE_STATE_SUB_0,
	A_TALK_TURN_RESULT_0,
	A_TALK_TURN_RESULT_1,
	A_TALK_TURN_RESULT_2,
	A_TALK_TURN_RESULT_3,
	A_TALK_TURN_RESULT_4,
	A_TALK_ACT_HOST_01,
	A_TALK_ACT_HOST_02,
	A_TALK_ACT_HOST_03,
	A_TALK_ACT_HOST_04,
	A_TALK_ACT_HOST_05,
	A_TALK_ACT_HOST_06,
	A_TALK_EXPLAIN_01,
	A_TALK_EXPLAIN_02,
	A_TALK_PRAC_APREFACE,
	A_TALK_PRACTICE_OPENING,
	A_TALK_SIO_WAIT,		//������@���������イ�c
};

///��b�E�B���h�E�X���C�h����
enum{
	TALKWIN_SLIDE_DIR_OUT,		///<��b�E�B���h�E�X���C�h�A�E�g
	TALKWIN_SLIDE_DIR_IN,		///<��b�E�B���h�E�X���C�h�C��
};

///�u���[�_�[�p�l�����G�t�F�N�g�^�C�v
enum{
	BRDPANEL_ALPHA_TYPE_RETIRE,		///<�u���[�_�[�p�l�����B��
	BRDPANEL_ALPHA_TYPE_RETURN,		///<�u���[�_�[�p�l�����A
};

///��b�E�B���h�E�̃X�N���[���`�惂�[�h
enum{
	TALKWIN_SCREEN_WRITE_BEFORE,	///<�X�N���[���O
	TALKWIN_SCREEN_WRITE_AFTER,		///<�X�N���[����
};

///�R�����A�N�V�����A�C�R���̃^�C�v
enum{
	JUDGE_REACTION_ICON_NOMINATION,		///<�R���w��
	JUDGE_REACTION_ICON_WEAR,			///<�w�����
	JUDGE_REACTION_ICON_VOLTAGE,		///<�{���e�[�W�A�b�v
	JUDGE_REACTION_ICON_VOLTAGE_MAX,	///<�{���e�[�W�ő�
	JUDGE_REACTION_ICON_SUFFER_BIG,		///<�R�����F���A�N�V�����ł���
	JUDGE_REACTION_ICON_SUFFER_MIDDLE,	///<�R�����F���A�N�V���������炢
	JUDGE_REACTION_ICON_SUFFER_SMALL,	///<�R�����F���A�N�V����������
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�{���e�[�W�|�C���g�A�j���p���[�N
typedef struct{
	ACTIN_PROC_WORK *apw;		///<���Z�͕���Ǘ����[�N�ւ̃|�C���^
	TCB_PTR tcb;				///<�A�j�����s�^�X�N�ւ̃|�C���^
	u8 judge_no;				///<�{���e�[�W���������Ă���R���̔ԍ�
}VOLTAGE_POINT_ANIME_WORK;

///�R���e�X�g�ŋZ�G�t�F�N�g���o���ۂ̃p�����[�^
typedef struct{
	u32 waza_kouka;
	u16 wazano;					///<�Z�ԍ�
	u8 loop;					///<�����ďo����
	u8 counter;					
	u8 natukido;				///<�Ȃ��x
}CON_WAZAEFF_PARAM;

///�u���[�_�[�p�l���F�t���b�V�����샏�[�N
typedef struct{
	PALETTE_FADE_PTR pfd;		///<�p���b�g�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR tcb;				///<�u���[�_�[�p�l���t���b�V�����C������^�X�N�ւ̃|�C���^
	s16 evy;					///<����EVY�l
	u8 breeder_no;				///<�u���[�_�[�ԍ�
	u8 req;						///<TRUE:���N�G�X�g���AFALSE:�ҋ@��
}PANEL_FLASH_WORK;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void AT_SoftSpriteAddAll(ACTIN_SYSTEM_PARAM *sys);
extern void AT_SoftSpriteDelAll(ACTIN_SYSTEM_PARAM *sys);
extern void AT_JudgeAddAll(ACTIN_SYSTEM_PARAM *sys, CONTEST_SYSTEM *consys);
extern void AT_JudgeDelAll(ACTIN_SYSTEM_PARAM *sys);
extern CATS_ACT_PTR AT_SubHeartJudgeAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no);
extern void AT_SpecialHeartSet(ACTIN_SYSTEM_PARAM *sys, int judge_no);
extern void AT_SpecialHeartDel(ACTIN_SYSTEM_PARAM *sys);
extern void AT_AppealPointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void AT_AppealPointResourceFree(CATS_RES_PTR crp);
extern void AT_AppealPointActorDelAll(ACTIN_SYSTEM_PARAM *sys);
extern void AT_AppealPointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int breeder_no, 
	int breeder_pos, int point);
extern void AT_VoltagePointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void AT_VoltagePointResourceFree(CATS_RES_PTR crp);
extern void AT_VoltagePointActorDelAll(ACTIN_SYSTEM_PARAM *sys);
extern void AT_VoltagePointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int judge_no, int point);
extern void BreederPanelColorChange(ACTIN_PROC_WORK *apw, int breeder_pos, int pal_no);
extern void BreederPanelColorChangeAll(ACTIN_PROC_WORK *apw);
extern void AT_TalkWinSlideCoverOBJSet(ACTIN_SYSTEM_PARAM *sys);
extern void AT_TalkWinSlideCoverOBJDelete(ACTIN_SYSTEM_PARAM *sys);
extern void AT_TalkWinSlideTaskSet(ACTIN_SYSTEM_PARAM *sys, u8 slide_dir, u8 *end_flag);
extern void AT_TalkWinScreenWrite(ACTIN_SYSTEM_PARAM *sys, int write_type);
extern void AT_A_TalkMessageSet(ACTIN_PROC_WORK *apw, u32 a_talk_id, const ATAG_PARAM *tagpara,
	const void *extagpara);
extern void AT_WazaKoukaTalkMessageSet(ACTIN_PROC_WORK *apw, int apno, int msg_type, 
	const ATAG_PARAM *tagpara, const void *extagpara);
extern int AT_TalkMessageEndCheck(ACTIN_PROC_WORK *apw);
extern void AT_BreederPanelFontOamCreate(ACTIN_PROC_WORK *apw, int breeder_no);
extern void AT_BreederPanelFontOamCreateAll(ACTIN_PROC_WORK *apw);
extern void AT_BreederPanelFontOamDeleteAll(ACTIN_PROC_WORK *apw);
extern void AT_BreederPanelFontOamPosUpdate(ACTIN_PROC_WORK *apw);
extern void AT_NextIconResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void AT_NextIconResourceFree(CATS_RES_PTR crp);
extern void AT_NextIconActorAnimeSet(ACTIN_SYSTEM_PARAM *sys, int breeder_pos, int next_pos);
extern void AT_NextIconActorDelAll(ACTIN_SYSTEM_PARAM *sys);
extern void AT_BrdPanelAlphaEffectSet(ACTIN_PROC_WORK *apw, int eff_type, u8 *end_flag);
extern void AT_MsgTagParaInitDataSet(ACTIN_PROC_WORK *apw, ATAG_PARAM *tagpara, int breeder_no);
extern u32 AT_MsgTagJudgeCommentCreate(int breeder_no, int app_total, ATAG_PARAM *tagpara);
extern void AT_AudienceAnimeSet(ACTIN_PROC_WORK *apw, int voltage, u8 start_wait, int se_volume, 
	int fade, u8 *end_flag);
extern void AT_JudgeReactionIconResourceLoad(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp);
extern void AT_JudgeReactionIconResourceDel(CATS_RES_PTR crp);
extern void AT_JudgeReactionIconActorAdd(ACTIN_SYSTEM_PARAM *sys);
extern void AT_JudgeReactionIconActorDel(ACTIN_SYSTEM_PARAM *sys);
extern void AT_JudgeReactionIconON(ACTIN_SYSTEM_PARAM *sys, int judge_no, int reaction_type);
extern void AT_JudgeReactionIconOFF(ACTIN_SYSTEM_PARAM *sys);
extern void AT_JudgeReactionMoveTaskSet(ACTIN_PROC_WORK *apw, int judge_no, 
	int reaction_type, u8 *end_flag);
extern BOOL AT_VoltageMoveEffectEndCheck(ACTIN_SYSTEM_PARAM *sys, int judge_no);
extern void AT_APHeartMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, 
	u8 *effect_count, PANEL_FLASH_WORK *panel_flash);
extern VOLTAGE_POINT_ANIME_WORK * AT_VoltageAnimeSet(ACTIN_PROC_WORK *apw, int judge_no);
extern void AT_VoltageAnimeDel(VOLTAGE_POINT_ANIME_WORK *vaw);
extern void AT_VoltageMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, 
	int judge_no, u8 *effect_count);
extern u32 AT_A_TalkIDGet_Host01(int con_type);
extern u32 AT_A_TalkIDGet_VoltageUp(int waza_con_type);
extern u32 AT_A_TalkIDGet_VoltageSub(int waza_con_type);
extern int AT_AudienceVolumeGet(int app_total);
extern void AT_WazaEffParamSet(CONTEST_SYSTEM *consys, int breeder_no, int wazano, 
	CON_WAZAEFF_PARAM *wazapara);
extern int AT_WazaConsecutiveCheck(ACTIN_GAME_PARAM *a_game, int breeder_no, int wazano);
extern void AT_SoftSpriteHensinPop(ACTIN_SYSTEM_PARAM *sys, int breeder_no);
PANEL_FLASH_WORK * BreederPanel_FlashTaskSet(ACTIN_PROC_WORK *apw, int breeder_no);
extern void BreederPanel_FlashTaskDelete(PANEL_FLASH_WORK *pfw);
extern void BreederPanel_FlashReqSet(PANEL_FLASH_WORK *pfw);
extern BOOL BreederPanel_FlashReqCheck(PANEL_FLASH_WORK *pfw);
extern void AT_TalkMessageWinClear(ACTIN_PROC_WORK *apw);


//==============================================================================
//	�O���f�[�^�錾
//==============================================================================
extern const u8 BreederPanelScreenPalNo[];


#endif	//__ACTIN_TOOL_H__

