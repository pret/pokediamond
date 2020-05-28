//============================================================================================
/**
 * @file	b_bag_anm.h
 * @brief	�퓬�p�o�b�O��� �{�^������
 * @author	Hiroyuki Nakamura
 * @date	05.03.15
 */
//============================================================================================
#ifndef B_BAG_ANM_H
#define B_BAG_ANM_H
#undef GLOBAL
#ifdef B_BAG_ANM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	BBAG_BTNANM_PAGE1 = 0,
	BBAG_BTNANM_PAGE2,
	BBAG_BTNANM_PAGE3,
	BBAG_BTNANM_PAGE4,
	BBAG_BTNANM_LAST,
	BBAG_BTNANM_RET1,

	BBAG_BTNANM_ITEM1,
	BBAG_BTNANM_ITEM2,
	BBAG_BTNANM_ITEM3,
	BBAG_BTNANM_ITEM4,
	BBAG_BTNANM_ITEM5,
	BBAG_BTNANM_ITEM6,
	BBAG_BTNANM_UP,
	BBAG_BTNANM_DOWN,
	BBAG_BTNANM_RET2,

	BBAG_BTNANM_USE,
	BBAG_BTNANM_RET3,
/*
	BBAG_BTNANM_PAGE1 = 0,
	BBAG_BTNANM_PAGE2,
	BBAG_BTNANM_PAGE3,
	BBAG_BTNANM_PAGE4,
	BBAG_BTNANM_PAGE5,
	BBAG_BTNANM_LAST,
	BBAG_BTNANM_RET1,

	BBAG_BTNANM_ITEM1,
	BBAG_BTNANM_ITEM2,
	BBAG_BTNANM_ITEM3,
	BBAG_BTNANM_ITEM4,
	BBAG_BTNANM_ITEM5,
	BBAG_BTNANM_ITEM6,
	BBAG_BTNANM_NEXT,
	BBAG_BTNANM_RET2,

	BBAG_BTNANM_USE,
	BBAG_BTNANM_RET3,
*/
};

// �{�^���A�j�����[�h
enum {
//	BBAG_BTNANM_MODE_CHG = 0,	// �������玟��
	BBAG_BTNANM_MODE_END = 0,	// �ĉ����\
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================


GLOBAL void BattleBag_ButtonScreenMake( BBAG_WORK * wk, u16 * scrn );

GLOBAL void BattleBag_ButtonAnmInit( BBAG_WORK * wk, u8 id, u8 mode );

GLOBAL void BattleBag_ButtonAnmMain( BBAG_WORK * wk );

GLOBAL void BattleBag_ButtonPageScreenInit( BBAG_WORK * wk, u8 page );


#undef GLOBAL
#endif	// B_BAG_ANM_H
