//============================================================================================
/**
 * @file	fd_shop.h
 * @brief	�t�����h���B�V���b�v����
 * @author	Hiroyuki Nakamura
 * @date	2004.12.15
 */
//============================================================================================
#ifndef FD_SHOP_H
#define FD_SHOP_H
#undef GLOBAL
#ifdef FD_SHOP_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	SHOP_TYPE_ITEM	( 0 )		// �A�C�e���V���b�v
#define	SHOP_TYPE_GOODS	( 1 )		// �O�b�Y�V���b�v
#define	SHOP_TYPE_SEAL	( 2 )		// �V�[���V���b�v


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
GLOBAL void ShopInit(
				GMEVENT_CONTROL * event, FIELDSYS_WORK * repw, u16 * item, u8 type, BOOL dp_flg );


#undef GLOBAL
#endif	/* FD_SHOP_H */
