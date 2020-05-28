
//============================================================================
/**
 *
 *@file		sub_086.s
 *@brief	戦闘シーケンス
 *			くろいまなざしシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_086:
	//まもる、みきりで外れている時は、うまくきまらん
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_MAMORU_NOHIT,MamoruNoHitUmakukimaran
	//技が外れているときは、うまくきまらん
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,KieNoHitUmakukimaran
	//すでにくろいまなざしを受けているときは、うまくきまらん
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KUROIMANAZASHI,Umakukimaran
	//みがわりを出されているときは、うまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KUROIMANAZASHI
	PSP_VALUE_WORK	VAL_BIT,SIDE_DEFENCE,ID_PSP_wkw_manazashi_client_no,BUF_PARA_ATTACK_CLIENT
	MESSAGE			KuroimanazashiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

KieNoHitUmakukimaran:
	//きえるのはずれメッセージの方が優先度が高いのでフラグを落としておく
	VALUE			VAL_NBIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_KIE_NOHIT
	BRANCH			Umakukimaran
MamoruNoHitUmakukimaran:
	//まもるのはずれメッセージの方が優先度が高いのでフラグを落としておく
	VALUE			VAL_NBIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_MAMORU_NOHIT
Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
