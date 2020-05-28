#ifndef B_BAG_H
#define B_BAG_H
#undef GLOBAL
#ifdef B_BAG_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


enum {
	BBAG_MODE_NORMAL = 0,	// �ʏ탂�[�h
	BBAG_MODE_GETDEMO,		// �ߊl�f�����[�h
};

enum {
	BBAG_POKE_HPRCV = 0,	// HP�񕜃|�P�b�g
	BBAG_POKE_STRCV,		// ��ԉ񕜃|�P�b�g
	BBAG_POKE_BALL,			// �{�[���|�P�b�g
	BBAG_POKE_BATTLE,		// �퓬�p�|�P�b�g
	BBAG_POKE_MAX
};


typedef struct {
	BATTLE_WORK * bw;	// �퓬�p���[�N

	MYSTATUS * myst;	// �v���[���[�f�[�^
	MYITEM * myitem;	// �A�C�e���f�[�^

	u32	heap;			// �q�[�vID
	s32 client_no;		// �N���C�A���gNo

	u32	mode;			// ���䃂�[�h

	u32	skill_item_use;	// �Z�Ŏg�p�s��

	u16	ret_item;		// �g�p�����A�C�e��
	u8	ret_page;		// �g�p�����A�C�e���̃|�P�b�g

	u8	used_poke;		// �O��g�p�����A�C�e���̃|�P�b�g
	u16	used_item;		// �O��g�p�����A�C�e��

	u8	enc_double;		// �쐶2vs2�Ń{�[�����������Ȃ��ꍇ�͂P
	u8	waza_vanish;	// ���肪�u������Ƃԁv�ȂǂŌ����Ȃ��ꍇ�͂P
	u8	waza_migawari;	// ���肪�u�݂����v���g�p���Ă���ꍇ�͂P

	u8	cursor_flg;		// �J�[�\���\���t���O

	u8	end_flg;		// �I���t���O

	u8	item_pos[5];	// �A�C�e���ʒu
	u8	item_scr[5];	// �A�C�e���X�N���[���J�E���^
}BBAG_DATA;


extern void BattleBag_TaskAdd( BBAG_DATA * dat );






#undef GLOBAL
#endif	/* B_BAG_H */
