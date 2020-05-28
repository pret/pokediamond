//=============================================================================
/**
 * @file	myitem.h
 * @brief	�莝���A�C�e������p�w�b�_
 * @author	tamada
 * @author	hiroyuki nakamura
 * @date	2005.10.13
 */
//=============================================================================
#ifndef	__MYITEM_H__
#define	__MYITEM_H__

#include "system/savedata_def.h"
#include "application/bag_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�莝���A�C�e���^��`
 */
//----------------------------------------------------------
typedef struct _MYITEM MYITEM;

// �o�b�O�̃J�[�\���ʒu
typedef struct _BAG_CURSOR	BAG_CURSOR;

//------------------------------------------------------------------------
//	�A�C�e���f�[�^
//------------------------------------------------------------------------
typedef	struct {
	u16	id;		// �A�C�e���ԍ�
	u16	no;		// ��
}MINEITEM;

#define	BAG_NORMAL_ITEM_MAX		( 165 )		// ����|�P�b�g�ő吔
#define	BAG_EVENT_ITEM_MAX		( 50 )		// ��؂ȕ��|�P�b�g�ő吔
#define	BAG_WAZA_ITEM_MAX		( 100 )		// �Z�}�V���|�P�b�g�ő吔
#define	BAG_SEAL_ITEM_MAX		( 12 )		// �V�[���|�P�b�g�ő吔
#define	BAG_DRUG_ITEM_MAX		( 40 )		// ��|�P�b�g�ő吔
#define	BAG_NUTS_ITEM_MAX		( 64 )		// �؂̎��|�P�b�g�ő吔
#define	BAG_BALL_ITEM_MAX		( 15 )		// �����X�^�[�{�[���|�P�b�g�ő吔
#define	BAG_BATTLE_ITEM_MAX		( 30 )		// �퓬�p�A�C�e���|�P�b�g�ő吔

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int MyItem_GetWorkSize(void);
extern MYITEM * MyItem_AllocWork(int heapID);
extern void MyItem_Copy(const MYITEM * from, MYITEM * to);

//----------------------------------------------------------
//	MYITEM����̂��߂̊֐�
//----------------------------------------------------------
extern void MyItem_Init(MYITEM * item);
extern BOOL MyItem_AddCheck( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_AddItem(MYITEM * myitem, u16 item_no, u16 num, u32 heap);
extern BOOL MyItem_SubItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_SubItemDirect( MINEITEM * myitem, u32 max, u16 item_no, u16 num, u32 heap );
extern BOOL MyItem_CheckItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap );
extern u16 MyItem_GetItemNum( MYITEM * myitem, u16 item_no, u32 heap );
extern u16 MyItem_GetItemNumDirect( MINEITEM * myitem, u32 max, u16 item_no, u32 heap );
extern void MyItem_SortSpace( MINEITEM * item, const u32 max );
extern void MyItem_SortNumber( MINEITEM * item, const u32 max );
extern BOOL MyItem_CheckItemPocket( MYITEM * myitem, u32 pocket );
extern MINEITEM * MyItem_PosItemGet( MYITEM * myitem, u16 pocket, u16 pos );
extern void MyItem_BattlePocketItemMake( MYITEM * myitem, MINEITEM * make[], u32 heap );
extern u32 MyItem_CnvButtonItemGet( const MYITEM * myitem );
extern void MyItem_CnvButtonItemSet( MYITEM * myitem, u32 item );


//----------------------------------------------------------
//	�o�b�O�쐬�֐�
//----------------------------------------------------------
extern void * MyItem_MakeBagData( MYITEM * myitem, const u8 * list, u32 heap );

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern MYITEM * SaveData_GetMyItem(SAVEDATA * sv);

//------------------------------------------------------------------
//	�o�b�O�̃J�[�\���ʒu�f�[�^
//------------------------------------------------------------------
extern BAG_CURSOR * MyItem_BagCursorAlloc( u32 heapID );

extern void MyItem_FieldBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr );
extern u16 MyItem_FieldBagPocketGet( BAG_CURSOR * wk );
extern void MyItem_FieldBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr );
extern void MyItem_FieldBagPocketSet( BAG_CURSOR * wk, u16 pocket );

extern void MyItem_BattleBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr );
extern u16 MyItem_BattleBagLastItemGet( BAG_CURSOR * wk );
extern u16 MyItem_BattleBagLastPageGet( BAG_CURSOR * wk );
extern u16 MyItem_BattleBagPocketPagePosGet( BAG_CURSOR * wk );
extern void MyItem_BattleBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr );
extern void MyItem_BattleBagLastItemSet( BAG_CURSOR * wk, u16 item, u16 page );
extern void MyItem_BattleBagPocketPagePosSet( BAG_CURSOR * wk, u16 pocket );
extern void MyItem_BattleBagCursorPosInit( BAG_CURSOR * wk );


//	�f�o�b�O�p�K���Ɏ莝���A�C�e�������֐�
extern void Debug_MyItem_MakeBag(MYITEM * myitem, int heapID);

#ifdef CREATE_INDEX
extern void *Index_Get_Myitem_Offset(MYITEM *item, int type);
#endif
#endif	/* __MYITEM_H__ */
