
//============================================================================
/**
 *
 *@file		sub_079.s
 *@brief	戦闘シーケンス
 *			ロックオンシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_079:
	//命中率で外れている時は、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	PSP_VALUE		VAL_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_LOCKON
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,LOCKON_COUNT*2
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_lockon_client_no,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	MESSAGE			LockOnM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_078_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

