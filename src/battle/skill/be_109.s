//============================================================================
/**
 *
 *@file		be_109.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			109　通常は「すばやさ」が１段階下がり「こうげき」「ぼうぎょ」が１段階上がるのだが、
 *				 ゴーストタイプのポケモンがこの技を使用すると、ＨＰを減らすかわりに、攻撃側のポケモンのＨＰを１／２減らします。
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_109:
	//ポケモンのタイプがゴーストタイプなら、ゴーストタイプののろいを起動
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_type1,GHOST_TYPE,GhostNoroi
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_type2,GHOST_TYPE,GhostNoroi
NormalNoroi:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NORMAL_NOROI|ADD_STATUS_ATTACK
	SEQ_END

GhostNoroi:
	//技によってタイプがゴーストに変わっている場合があるので、DefenceClientのチェックをする
	IF_WORK			IF_FLAG_NE,BUF_PARA_ATTACK_CLIENT,BUF_PARA_DEFENCE_CLIENT,GhostNoroiStart
	DIR_CLIENT_GET	SIDE_ATTACK
GhostNoroiStart:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GHOST_NOROI|ADD_STATUS_WAZAKOUKA
	//ゴーストの技エフェクトをセット
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	SEQ_END
