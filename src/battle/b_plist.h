//============================================================================================
/**
 * @file	b_plist.h
 * @brief	�퓬�p�|�P�������X�g��ʁ@�O�����J�w�b�_�t�@�C��
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#ifndef B_PLIST_H
#define B_PLIST_H
#undef GLOBAL
#ifdef B_PLIST_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	BPL_SEL_EXIT		( 6 )	// �L�����Z��
#define	BPL_SEL_WP_CANCEL	( 4 )	// �Z�Y��L�����Z���i�V�����o����Z�ʒu�j

// ���X�g������`
enum {
	BPL_MODE_NORMAL = 0,	// �ʏ�̃|�P�����I��
	BPL_MODE_NO_CANCEL,		// �L�����Z���s��
	BPL_MODE_ITEMUSE,		// �A�C�e���g�p
	BPL_MODE_WAZASET,		// �Z�Y��
};

// �y�[�W��`
enum {
	BPLIST_PAGE_SELECT = 0,		// �|�P�����I���y�[�W
	BPLIST_PAGE_POKE_CHG,		// �|�P��������ւ��y�[�W
	BPLIST_PAGE_MAIN,			// �X�e�[�^�X���C���y�[�W	
	BPLIST_PAGE_WAZA_SEL,		// �X�e�[�^�X�Z�I���y�[�W
	BPLIST_PAGE_SKILL,			// �X�e�[�^�X�Z�ڍ׃y�[�W
	BPLIST_PAGE_PP_RCV,			// PP�񕜋Z�I���y�[�W
	BPLIST_PAGE_WAZASET_BS,		// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
	BPLIST_PAGE_WAZASET_BI,		// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
	BPLIST_PAGE_WAZASET_CS,		// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�I���j
	BPLIST_PAGE_WAZASET_CI,		// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�ڍׁj
};

// ���X�g�f�[�^
typedef struct {
	POKEPARTY * pp;		// �|�P�����f�[�^
	void * myitem;		// �A�C�e���f�[�^

	BATTLE_WORK * bw;		// �퓬�p���[�N

	u32	heap;			// �q�[�vID

//	u8	fight_type;		// �V���O���^�_�u���^�}���`
	u8	multi_pos;		// �}���`�̗��ʒu
	u8	sel_poke;		// �I�����ꂽ�|�P���� or �߂�
	u8	double_sel;		// �_�u���o�g���ł��łɑI������Ă���|�P����
	u8	ret_mode;		// �I�����ꂽ����

	u8	fight_poke1;	// �퓬�ɏo�Ă���|�P�����P
	u8	fight_poke2;	// �퓬�ɏo�Ă���|�P�����Q

	u32	skill_item_use[2];	// �Z�Ŏg�p�s��

	u16	hp_rcv;			// HP�񕜗�

	u16	item;			// �A�C�e��
	u16	chg_waza;		// ���ꂩ���֎~�Z�E�V�����o����Z

	s32 client_no;						// �N���C�A���gNo
	u8	list_row[POKEMON_TEMOTI_MAX];	// ���X�g���E

	u8	cursor_flg;		// �J�[�\���\���t���O

	u8	bag_page;		// �o�b�O�̃y�[�W

	u8	sel_wp;			// �I�����ꂽ�Z�ʒu

	u8	mode;			// ���X�g���[�h
	u8	end_flg;		// �I���t���O

}BPLIST_DATA;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�|�P�������X�g�^�X�N�ǉ�
 *
 * @param	dat		���X�g�f�[�^
 *
 * @return none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_TaskAdd( BPLIST_DATA * dat );


#undef GLOBAL
#endif	/* B_PLIST_H */
