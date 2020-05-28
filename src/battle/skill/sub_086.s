
//============================================================================
/**
 *
 *@file		sub_086.s
 *@brief	�퓬�V�[�P���X
 *			���낢�܂Ȃ����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_086:
	//�܂���A�݂���ŊO��Ă��鎞�́A���܂����܂��
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_MAMORU_NOHIT,MamoruNoHitUmakukimaran
	//�Z���O��Ă���Ƃ��́A���܂����܂��
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,KieNoHitUmakukimaran
	//���łɂ��낢�܂Ȃ������󂯂Ă���Ƃ��́A���܂����܂��
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KUROIMANAZASHI,Umakukimaran
	//�݂������o����Ă���Ƃ��́A���܂����܂��
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KUROIMANAZASHI
	PSP_VALUE_WORK	VAL_BIT,SIDE_DEFENCE,ID_PSP_wkw_manazashi_client_no,BUF_PARA_ATTACK_CLIENT
	MESSAGE			KuroimanazashiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

KieNoHitUmakukimaran:
	//������̂͂��ꃁ�b�Z�[�W�̕����D��x�������̂Ńt���O�𗎂Ƃ��Ă���
	VALUE			VAL_NBIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_KIE_NOHIT
	BRANCH			Umakukimaran
MamoruNoHitUmakukimaran:
	//�܂���̂͂��ꃁ�b�Z�[�W�̕����D��x�������̂Ńt���O�𗎂Ƃ��Ă���
	VALUE			VAL_NBIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_MAMORU_NOHIT
Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
