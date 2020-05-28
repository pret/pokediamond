
//============================================================================
/**
 *
 *@file		sub_163.s
 *@brief	�퓬�V�[�P���X
 *			�������V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_163:
	//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_IEKI,Umakukimaran
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	//�����}���`�^�C�v�́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_IEKI
	MESSAGE			IekiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
