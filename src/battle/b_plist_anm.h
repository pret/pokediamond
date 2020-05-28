//============================================================================================
/**
 * @file	b_plist_anm.h
 * @brief	�퓬�p�|�P�������X�g��� �{�^������
 * @author	Hiroyuki Nakamura
 * @date	05.03.16
 */
//============================================================================================
#ifndef B_PLIST_ANM_H
#define B_PLIST_ANM_H
#undef GLOBAL
#ifdef B_PLIST_ANM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	BPL_BUTTON_POKE1 = 0,	// �|�P�����P
	BPL_BUTTON_POKE2,		// �|�P�����Q
	BPL_BUTTON_POKE3,		// �|�P�����R
	BPL_BUTTON_POKE4,		// �|�P�����S
	BPL_BUTTON_POKE5,		// �|�P�����T
	BPL_BUTTON_POKE6,		// �|�P�����U
	BPL_BUTTON_RET,			// �߂�
	BPL_BUTTON_POKE_CHG,	// ����ւ�
	BPL_BUTTON_STATUS1,		// ����������i���z�u�j
	BPL_BUTTON_STATUS2,		// ����������i�E�z�u�j
	BPL_BUTTON_WAZASEL1,	// �Z������
	BPL_BUTTON_WAZASEL2,	// �Z������i�P�Ɓj
	BPL_BUTTON_UP,			// �؂�ւ��i��j
	BPL_BUTTON_DOWN,		// �؂�ւ��i���j
	BPL_BUTTON_WAZA1,		// �Z�P
	BPL_BUTTON_WAZA2,		// �Z�Q
	BPL_BUTTON_WAZA3,		// �Z�R
	BPL_BUTTON_WAZA4,		// �Z�S
	BPL_BUTTON_CONTEST,		// �R���e�X�g�Z<->�키�Z

	BPL_BUTTON_WAZARCV1,	// �Z�񕜂P
	BPL_BUTTON_WAZARCV2,	// �Z�񕜂Q
	BPL_BUTTON_WAZARCV3,	// �Z�񕜂R
	BPL_BUTTON_WAZARCV4,	// �Z�񕜂S

	BPL_BUTTON_WAZADEL1,	// �Z�Y��P
	BPL_BUTTON_WAZADEL2,	// �Z�Y��Q
	BPL_BUTTON_WAZADEL3,	// �Z�Y��R
	BPL_BUTTON_WAZADEL4,	// �Z�Y��S
	BPL_BUTTON_WAZADEL5,	// �Z�Y��T

	BPL_BUTTON_WAZADEL_B,	// �Y�ꂳ����i�퓬�j
	BPL_BUTTON_WAZADEL_C,	// �Y�ꂳ����i�R���e�X�g�j

	BPL_BUTTON_WAZAPOS1,	// �Z�؂�ւ��P
	BPL_BUTTON_WAZAPOS2,	// �Z�؂�ւ��Q
	BPL_BUTTON_WAZAPOS3,	// �Z�؂�ւ��R
	BPL_BUTTON_WAZAPOS4,	// �Z�؂�ւ��S
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

GLOBAL void BattlePokeList_ButtonScreenMake( BPLIST_WORK * wk, u16 * scrn );

GLOBAL void BattlePokeList_ButtonScreenMake2( BPLIST_WORK * wk, u16 * scrn );

GLOBAL void BattlePokeList_ButtonAnmInit( BPLIST_WORK * wk, u8 id );


GLOBAL void BattlePokeList_ButtonAnmMain( BPLIST_WORK * wk );


GLOBAL void BattlePokeList_ButtonPageScreenInit( BPLIST_WORK * wk, u8 page );
GLOBAL void BattlePokeList_ButtonPalSet( BPLIST_WORK * wk, u8 page );

GLOBAL void BPL_HPRcvButtonPut( BPLIST_WORK * wk );



#undef GLOBAL
#endif	// B_PLIST_ANM_H
