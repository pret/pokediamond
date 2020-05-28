//============================================================================
/**
 *
 *@file		be_272.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			272　２ターン技攻撃+まもりを破る（フェイントと一緒でまもる確率は維持したまま）
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_272:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//2体に当たるときは、KEEPがおちた状態で回ってくるので、それを回避
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_272_NEXT
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SHADOW_DIVE
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_272_NEXT:
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SHADOW_DIVE
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka_temp,WAZAKOUKA_SHADOW_DIVE
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//これが必要かは微妙
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_272_END
SeqWazaAfter:
	//フェイントと同様にまもるをやぶるので、追加効果を設定
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_FEINT|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
BE_272_END:
	//姿を消す系のため技のフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
