//=============================================================================
/**
 * @file	myitem.c
 * @brief	�莝���A�C�e������p
 * @author	tamada
 * @author	hiroyuki nakamura
 * @date	2005.10.13
 */
//=============================================================================

#include "common.h"
#include "gflib/system.h"

#include "system/gamedata.h"

#include "itemtool/myitem.h"
#include "itemtool/item.h"

#include "system/savedata.h"		//SaveData_Get & GMDATA_ID_TEMOTI_ITEM

#include "system/procsys.h"
#include "application/bag.h"


//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	�莝���A�C�e���\���̂̒�`
 */
//------------------------------------------------------------------
struct _MYITEM {
	MINEITEM MyNormalItem[ BAG_NORMAL_ITEM_MAX ];	// �莝���̕��ʂ̓���
	MINEITEM MyEventItem[ BAG_EVENT_ITEM_MAX ];		// �莝���̑�؂ȓ���
	MINEITEM MySkillItem[ BAG_WAZA_ITEM_MAX ];		// �莝���̋Z�}�V��
	MINEITEM MySealItem[ BAG_SEAL_ITEM_MAX ];		// �莝���̃V�[��
	MINEITEM MyDrugItem[ BAG_DRUG_ITEM_MAX ];		// �莝���̖�
	MINEITEM MyNutsItem[ BAG_NUTS_ITEM_MAX ];		// �莝���̖؂̎�
	MINEITEM MyBallItem[ BAG_BALL_ITEM_MAX ];		// �莝���̃����X�^�[�{�[��
	MINEITEM MyBattleItem[ BAG_BATTLE_ITEM_MAX ];	// �莝���̐퓬�p�A�C�e��
	u32	cnv_button;									// �֗��{�^��
};

// �t�B�[���h�̃o�b�O�̃J�[�\���ʒu
typedef struct {
	u8	scr[8];
	u8	pos[8];
	u16	pocket;
	u16	dummy;
}FLDBAG_CURSOR;

// �퓬�̃o�b�O�̃J�[�\���ʒu
typedef struct {
	u8	scr[5];
	u8	pos[5];
	u16	item;
	u16	page;
	u16	pocket;		// �|�P�b�g�y�[�W�̈ʒu
}BTLBAG_CURSOR;

// �o�b�O�̃J�[�\���ʒu�f�[�^
struct _BAG_CURSOR {
	FLDBAG_CURSOR	fld;
	BTLBAG_CURSOR	btl;
};



#define	ITEM_CHECK_ERR	( 0xffffffff )		// �`�F�b�N�G���[

#define	ITEM_MAX_NORMAL			( 999 )		// �ʏ�̃A�C�e���������ő�
#define	ITEM_MAX_WAZAMACHINE	( 99 )		// �Z�}�V���̏������ő�

static u32 MyItemDataGet( MYITEM * myitem, u16 id, MINEITEM ** item, u32 * max, u32 heap );



//=============================================================================
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int MyItem_GetWorkSize(void)
{
	return sizeof(MYITEM);
}

//------------------------------------------------------------------
/**
 * @brief	�莝���A�C�e�����[�N�𐶐�����
 * @param	myitem	�莝���A�C�e���\���̂ւ̃|�C���^
 * @return	MYITEM�ւ̃|�C���^
 */
//------------------------------------------------------------------
MYITEM * MyItem_AllocWork(int heapID)
{
	MYITEM * item;
	item = sys_AllocMemory(heapID, sizeof(MYITEM));
	MyItem_Init(item);
	return item;
}

//------------------------------------------------------------------
/**
 * @brief	����������
 * @param	item	MYITEM�ւ̃|�C���^
 */
//------------------------------------------------------------------
void MyItem_Init(MYITEM * item)
{
	MI_CpuClear16(item, sizeof(MYITEM));
}

//------------------------------------------------------------------
/**
 * @brief	MYITEM�̃R�s�[
 * @param	from	�R�s�[���ւ̃|�C���^
 * @param	to		�R�s�[��ւ̃|�C���^
 */
//------------------------------------------------------------------
void MyItem_Copy(const MYITEM * from, MYITEM * to)
{
	MI_CpuCopy8(from, to, sizeof(MYITEM));
}

//------------------------------------------------------------------
/**
 * @brief	�֗��{�^���Ɋ��蓖�Ă��Ă���A�C�e���擾
 * @param	myitem	MYITEM�ւ̃|�C���^
 * @return	�A�C�e���ԍ�
 */
//------------------------------------------------------------------
u32 MyItem_CnvButtonItemGet( const MYITEM * myitem )
{
	return myitem->cnv_button;
}

//------------------------------------------------------------------
/**
 * @brief	�֗��{�^���ɃA�C�e���Z�b�g
 * @param	myitem	MYITEM�ւ̃|�C���^
 * @param	setitem	�Z�b�g����A�C�e��
 * @return	�A�C�e���ԍ�
 */
//------------------------------------------------------------------
void MyItem_CnvButtonItemSet( MYITEM * myitem, u32 setitem )
{
	myitem->cnv_button = setitem;
}

//------------------------------------------------------------------
/**
 * @brief	MYITEM�ƍő吔�擾
 * @param	id		�A�C�e���ԍ�
 * @param	item	MYITEM�擾�ꏊ
 * @param	max		�ő吔�擾�ꏊ
 * @param	heap		�q�[�vID
 * @return	�|�P�b�g�ԍ�
 */
//------------------------------------------------------------------
static u32 MyItemDataGet( MYITEM * myitem, u16 id, MINEITEM ** item, u32 * max, u32 heap )
{
	u32	pocket = ItemParamGet( id, ITEM_PRM_POCKET, heap );

	switch( pocket ){
	case BAG_POKE_EVENT:	// ��؂ȕ�
		*item = myitem->MyEventItem;
		*max = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// ����
		*item = myitem->MyNormalItem;
		*max = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// �؂̎�
		*item = myitem->MyNutsItem;
		*max = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// ��
		*item = myitem->MyDrugItem;
		*max = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// �{�[��
		*item = myitem->MyBallItem;
		*max = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// �퓬�p
		*item = myitem->MyBattleItem;
		*max = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// �V�[��
		*item = myitem->MySealItem;
		*max = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// �Z�}�V��
		*item = myitem->MySkillItem;
		*max = BAG_WAZA_ITEM_MAX;
		break;
	}
	return pocket;
}


//------------------------------------------------------------------
/**
 * @brief	������A�C�e�����`�F�b�N
 * @param	item		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	siz			�莝���A�C�e���\���̂̃T�C�Y�i���j
 * @param	id			�w�肷��A�C�e���̃i���o�[
 * @param	num			������A�C�e���̌�
 * @param	max			�A�C�e���ő吔
 * @retval	���� = �A�C�e���ʒu
 * @retval	���s = NULL
 */
//------------------------------------------------------------------
static MINEITEM * AddItemSearch( MINEITEM * item, u32 siz, u16 id, u16 num, u16 max )
{
	u32	i;
	u32	pos = ITEM_CHECK_ERR;

	for( i=0; i<siz; i++ ){
		if( item[i].id == id ){
			if( ( item[i].no + num ) > max ){
				return NULL;
			}
			return &item[i];
		}
		if( pos == ITEM_CHECK_ERR ){
			if( item[i].id == 0 && item[i].no == 0 ){
				pos = i;
			}
		}
	}

	if( pos == ITEM_CHECK_ERR ){
		return NULL;
	}
	return &item[pos];
}

//------------------------------------------------------------------
/**
 * @brief	�A�C�e����������ꏊ���擾
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	���� = �A�C�e���ʒu
 * @retval	���s = NULL
 */
//------------------------------------------------------------------
static MINEITEM * AddItemPosGet( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * add;
	u32	max;
	u32	pocket;

	pocket = MyItemDataGet( myitem, item_no, &add, &max, heap );
	if( pocket == BAG_POKE_WAZA ){
		return AddItemSearch( add, max, item_no, num, ITEM_MAX_WAZAMACHINE );
	}
	return AddItemSearch( add, max, item_no, num, ITEM_MAX_NORMAL );
}

//------------------------------------------------------------------
/**
 * @brief	�莝���ɃA�C�e�����������邩�`�F�b�N
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	����
 * @retval	FALSE	���s
 */
//------------------------------------------------------------------
BOOL MyItem_AddCheck( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	if( AddItemPosGet( myitem, item_no, num, heap ) == NULL ){
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�莝���ɃA�C�e����������
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	����
 * @retval	FALSE	���s
 */
//------------------------------------------------------------------
BOOL MyItem_AddItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * add = AddItemPosGet( myitem, item_no, num, heap );

	if( add == NULL ){ return FALSE; }

	add->id = item_no;
	add->no += num;

	{
		u32	pocket;
		u32	max;
		pocket = MyItemDataGet( myitem, item_no, &add, &max, heap );
		if( pocket == BAG_POKE_NUTS || pocket == BAG_POKE_WAZA ){
			MyItem_SortNumber( add, max );
		}
	}

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	��菜���A�C�e�����`�F�b�N
 * @param	item		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	siz			�莝���A�C�e���\���̂̃T�C�Y�i���j
 * @param	id			�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @retval	���� = �A�C�e���ʒu
 * @retval	���s = NULL
 */
//------------------------------------------------------------------
static MINEITEM * SubItemSearch( MINEITEM * item, u32 siz, u16 id, u16 num )
{
	u32	i;

	for( i=0; i<siz; i++ ){
		if( item[i].id == id ){
			if( item[i].no >= num ){
				return &item[i];
			}else{
				return NULL;
			}
		}
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�A�C�e������菜���ꏊ���擾
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	���� = �A�C�e���ʒu
 * @retval	���s = NULL
 */
//------------------------------------------------------------------
static MINEITEM * SubItemPosGet( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub;
	u32	max;

	MyItemDataGet( myitem, item_no, &sub, &max, heap );
	return SubItemSearch( sub, max, item_no, num );

/*
	switch( ItemParamGet( item_no, ITEM_PRM_POCKET, heap ) ){
	case BAG_POKE_EVENT:	// ��؂ȕ�
		sub = SubItemSearch( myitem->MyEventItem, BAG_EVENT_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_NORMAL:	// ����
		sub = SubItemSearch( myitem->MyNormalItem, BAG_NORMAL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_NUTS:		// �؂̎�
		sub = SubItemSearch( myitem->MyNutsItem, BAG_NUTS_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_DRUG:		// ��
		sub = SubItemSearch( myitem->MyDrugItem, BAG_DRUG_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_BALL:		// �{�[��
		sub = SubItemSearch( myitem->MyBallItem, BAG_BALL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_BATTLE:	// �퓬�p
		sub = SubItemSearch( myitem->MyBattleItem, BAG_BATTLE_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_SEAL:		// �V�[��
		sub = SubItemSearch( myitem->MySealItem, BAG_SEAL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_WAZA:		// �Z�}�V��
		sub = SubItemSearch( myitem->MySkillItem, BAG_WAZA_ITEM_MAX, item_no, num );
		break;
	default:
		return NULL;
	}

	return sub;
*/

}

//------------------------------------------------------------------
/**
 * @brief	�莝������A�C�e������菜��
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	����
 * @retval	FALSE	���s
 */
//------------------------------------------------------------------
BOOL MyItem_SubItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub = SubItemPosGet( myitem, item_no, num, heap );

	if( sub == NULL ){ return FALSE; }

	sub->no -= num;
	if( sub->no == 0 ){
		sub->id = 0;
	}

	{
		u32	max;

		MyItemDataGet( myitem, item_no, &sub, &max, heap );
		MyItem_SortSpace( sub, max );
	}

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�莝������A�C�e������菜���i�|�P�b�g�w��j
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	max			������
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	����
 * @retval	FALSE	���s
 */
//------------------------------------------------------------------
BOOL MyItem_SubItemDirect( MINEITEM * myitem, u32 max, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub = SubItemSearch( myitem, max, item_no, num );

	if( sub == NULL ){ return FALSE; }

	sub->no -= num;
	if( sub->no == 0 ){
		sub->id = 0;
	}

	MyItem_SortSpace( myitem, max );

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�莝���A�C�e�����ł̑��݃`�F�b�N
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	���݂���
 * @retval	FALSE	���݂��Ȃ�
 */
//------------------------------------------------------------------
BOOL MyItem_CheckItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	if( SubItemPosGet( myitem, item_no, num, heap ) == NULL ){
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�b�g�ɃA�C�e�������݂��邩�`�F�b�N
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	pocket		�|�P�b�g�ԍ�
 * @retval	TRUE	���݂���
 * @retval	FALSE	���݂��Ȃ�
 */
//------------------------------------------------------------------
BOOL MyItem_CheckItemPocket( MYITEM * myitem, u32 pocket )
{
	MINEITEM * item;
	u32	max;
	u32	i;

	switch( pocket ){
	case BAG_POKE_EVENT:	// ��؂ȕ�
		item = myitem->MyEventItem;
		max  = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// ����
		item = myitem->MyNormalItem;
		max  = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// �؂̎�
		item = myitem->MyNutsItem;
		max  = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// ��
		item = myitem->MyDrugItem;
		max  = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// �{�[��
		item = myitem->MyBallItem;
		max  = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// �퓬�p
		item = myitem->MyBattleItem;
		max  = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// �V�[��
		item = myitem->MySealItem;
		max  = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// �Z�}�V��
		item = myitem->MySkillItem;
		max  = BAG_WAZA_ITEM_MAX;
		break;
	default:
		return FALSE;
	}

	for( i=0; i<max; i++ ){
		if( item[i].id != 0 ){ return TRUE; }
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�莝���̌��`�F�b�N
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	heap		�q�[�vID
 * @return	�莝����
 */
//------------------------------------------------------------------
u16 MyItem_GetItemNum( MYITEM * myitem, u16 item_no, u32 heap )
{
	MINEITEM * sub = SubItemPosGet( myitem, item_no, 1, heap );

	if( sub == NULL ){
		return 0;
	}
	return sub->no;
}

//------------------------------------------------------------------
/**
 * @brief	�莝���̌��`�F�b�N�i�|�P�b�g�w��j
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	max			������
 * @param	item_no		�w�肷��A�C�e���̃i���o�[
 * @param	num			�A�C�e���̌�
 * @param	heap		�q�[�vID
 * @retval	TRUE	����
 * @retval	FALSE	���s
 */
//------------------------------------------------------------------
u16 MyItem_GetItemNumDirect( MINEITEM * myitem, u32 max, u16 item_no, u32 heap )
{
	MINEITEM * sub = SubItemSearch( myitem, max, item_no, 1 );

	if( sub == NULL ){ return 0; }

	return sub->no;
}

//------------------------------------------------------------------
/**
 * @brief	�w����̃A�C�e�������ւ�
 * @param	p1		����ւ���f�[�^1
 * @param	p2		����ւ���f�[�^2
 * @return	none
 */
//------------------------------------------------------------------
static void ChengeItem( MINEITEM * p1, MINEITEM * p2 )
{
	MINEITEM	copy;

	copy = *p1;
	*p1  = *p2;
	*p2  = copy;
}

//------------------------------------------------------------------
/**
 * @brief	�A�C�e���\�[�g�i�X�y�[�X���߂�j
 * @param	item	�A�C�e���f�[�^
 * @param	max		�ő�l
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_SortSpace( MINEITEM * item, const u32 max )
{
	u32	i, j;

	for( i=0; i<max-1; i++ ){
		for( j=i+1; j<max; j++ ){
			if( item[i].no == 0 ){
				ChengeItem( &item[i], &item[j] );
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�A�C�e���\�[�g�i�ԍ����j
 * @param	p	�|�P�b�g�f�[�^
 * @param	max		�ő�l
 * @return	none
 */	
//------------------------------------------------------------------
void MyItem_SortNumber( MINEITEM * item, const u32 max )
{
	u32	i, j;

	for( i=0; i<max-1; i++ ){
		for( j=i+1; j<max; j++ ){
			if( item[i].no == 0 || ( item[j].no != 0 && item[i].id > item[j].id ) ){
				ChengeItem( &item[i], &item[j] );
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�o�b�O�̃f�[�^�쐬
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	list		�|�P�b�g���X�g
 * @param	heap		�q�[�vID
 */
//------------------------------------------------------------------
void * MyItem_MakeBagData( MYITEM * myitem, const u8 * list, u32 heap )
{
	BAG_DATA * bag;
	int i;

	bag = BagSystemDataAlloc( heap );
	for( i=0; list[i] != 0xff; i++ ){
		switch( list[i] ){
		case BAG_POKE_EVENT:
			BagPocketDataMake( bag, myitem->MyEventItem, BAG_POKE_EVENT, i );
			break;
		case BAG_POKE_NORMAL:
			BagPocketDataMake( bag, myitem->MyNormalItem, BAG_POKE_NORMAL, i );
			break;
		case BAG_POKE_NUTS:
			BagPocketDataMake( bag, myitem->MyNutsItem, BAG_POKE_NUTS, i );
			break;
		case BAG_POKE_DRUG:
			BagPocketDataMake( bag, myitem->MyDrugItem, BAG_POKE_DRUG, i );
			break;
		case BAG_POKE_BALL:
			BagPocketDataMake( bag, myitem->MyBallItem, BAG_POKE_BALL, i );
			break;
		case BAG_POKE_BATTLE:
			BagPocketDataMake( bag, myitem->MyBattleItem, BAG_POKE_BATTLE, i );
			break;
		case BAG_POKE_SEAL:
			BagPocketDataMake( bag, myitem->MySealItem, BAG_POKE_SEAL, i );
			break;
		case BAG_POKE_WAZA:
			BagPocketDataMake( bag, myitem->MySkillItem, BAG_POKE_WAZA, i );
			break;
		}
	}
	return bag;
}


//------------------------------------------------------------------
/**
 * @brief	�w��|�P�b�g�̎w��ʒu�̃A�C�e�����擾
 * @param	myitem		�莝���A�C�e���\���̂ւ̃|�C���^
 * @param	pocket		�|�P�b�gID
 * @param	pos			�ʒu
 * @return	�A�C�e���f�[�^
 */
//------------------------------------------------------------------
MINEITEM * MyItem_PosItemGet( MYITEM * myitem, u16 pocket, u16 pos )
{
	MINEITEM * item;
	u16	max;

	switch( pocket ){
	case BAG_POKE_EVENT:	// ��؂ȕ�
		item = myitem->MyEventItem;
		max  = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// ����
		item = myitem->MyNormalItem;
		max  = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// �؂̎�
		item = myitem->MyNutsItem;
		max  = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// ��
		item = myitem->MyDrugItem;
		max  = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// �{�[��
		item = myitem->MyBallItem;
		max  = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// �퓬�p
		item = myitem->MyBattleItem;
		max  = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// �V�[��
		item = myitem->MySealItem;
		max  = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// �Z�}�V��
		item = myitem->MySkillItem;
		max  = BAG_WAZA_ITEM_MAX;
		break;
	}

	if( pos >= max ){ return NULL; }

	return &item[pos];
}


//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^����莝���A�C�e���ւ̃|�C���^���擾����
 * @param	sv	�Z�[�u�f�[�^�ւ̃|�C���^
 * @return	�Z�[�u�f�[�^����MYITEM�ւ̃|�C���^
 */
//------------------------------------------------------------------
MYITEM * SaveData_GetMyItem(SAVEDATA * sv)
{
	MYITEM * myitem;
	myitem = (MYITEM *)SaveData_Get(sv, GMDATA_ID_TEMOTI_ITEM);
	return myitem;
}

//------------------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F�K���Ɏ莝���𐶐�����
 * @param	myitem	�莝���A�C�e���\���̂ւ̃|�C���^
 */
//------------------------------------------------------------------
static const MINEITEM DebugItem[] = {
	{ ITEM_MASUTAABOORU,	111 },
	{ ITEM_MONSUTAABOORU,	222 },
	{ ITEM_SUUPAABOORU,		333 },
	{ ITEM_HAIPAABOORU,		444 },
	{ ITEM_PUREMIABOORU,	555 },
	{ ITEM_DAIBUBOORU,		666 },
	{ ITEM_TAIMAABOORU,		777 },
	{ ITEM_RIPIITOBOORU,	888 },
	{ ITEM_NESUTOBOORU,		999 },
	{ ITEM_GOOZYASUBOORU,	100 },
	{ ITEM_KIZUGUSURI,		123 },
	{ ITEM_NEMUKEZAMASI,	456 },
	{ ITEM_TAUNMAPPU,		1 },
	{ ITEM_TANKENSETTO,		1 },
	{ ITEM_ZITENSYA,		1 },
	{ ITEM_NANDEMONAOSI,	18 },
	{ ITEM_PIIPIIRIKABAA,	18 },
	{ ITEM_PIIPIIMAKKUSU,	18 },
	{ ITEM_DOKUKESI,		18 },		// �ǂ�����
	{ ITEM_YAKEDONAOSI,		19 },		// �₯�ǂȂ���
	{ ITEM_KOORINAOSI,		20 },		// ������Ȃ���
	{ ITEM_MAHINAOSI,		22 },		// �܂ЂȂ���
	{ ITEM_EFEKUTOGAADO,	54 },		// �G�t�F�N�g�K�[�h
	{ ITEM_KURITHIKATTAA,	55 },		// �N���e�B�J�b�^�[
	{ ITEM_PURASUPAWAA,		56 },		// �v���X�p���[
	{ ITEM_DHIFENDAA,		57 },		// �f�B�t�F���_�[
	{ ITEM_SUPIIDAA,		58 },		// �X�s�[�_�[
	{ ITEM_YOKUATAARU,		59 },		// ���N�A�^�[��
	{ ITEM_SUPESYARUAPPU,	60 },		// �X�y�V�����A�b�v
	{ ITEM_SUPESYARUGAADO,	61 },		// �X�y�V�����K�[�h
	{ ITEM_PIPPININGYOU,	62 },		// �s�b�s�ɂ񂬂傤
	{ ITEM_ENEKONOSIPPO,	63 },		// �G�l�R�̃V�b�|
	{ ITEM_GENKINOKAKERA,	28 },		// ���񂫂̂�����
	{ ITEM_KAIHUKUNOKUSURI,	28 },		// ���񂫂̂�����
	{ ITEM_PIIPIIEIDO,	28 },
	{ ITEM_PIIPIIEIDAA,	28 },
	{ ITEM_DAAKUBOORU,	13 },		// �_�[�N�{�[��
	{ ITEM_HIIRUBOORU,  14 },		// �q�[���{�[��
	{ ITEM_KUIKKUBOORU,	15 },		// �N�C�b�N�{�[��
	{ ITEM_PURESYASUBOORU,	16 },	// �v���V�A�{�[��
	{ ITEM_TOMODATITETYOU,  1},  // �Ƃ������蒠
};

void Debug_MyItem_MakeBag(MYITEM * myitem, int heapID)
{
	u32	i;

	memset( myitem->MyEventItem, 0, sizeof(MINEITEM) * BAG_EVENT_ITEM_MAX );
	memset( myitem->MyNormalItem, 0, sizeof(MINEITEM) * BAG_NORMAL_ITEM_MAX );
	memset( myitem->MyNutsItem, 0, sizeof(MINEITEM) * BAG_NUTS_ITEM_MAX );
	memset( myitem->MyDrugItem, 0, sizeof(MINEITEM) * BAG_DRUG_ITEM_MAX );
	memset( myitem->MyBallItem, 0, sizeof(MINEITEM) * BAG_BALL_ITEM_MAX );
	memset( myitem->MyBattleItem, 0, sizeof(MINEITEM) * BAG_BATTLE_ITEM_MAX );
	memset( myitem->MySealItem, 0, sizeof(MINEITEM) * BAG_SEAL_ITEM_MAX );
	memset( myitem->MySkillItem, 0, sizeof(MINEITEM) * BAG_WAZA_ITEM_MAX );

	for( i=0; i<NELEMS(DebugItem); i++ ){
		MyItem_AddItem( myitem, DebugItem[i].id, DebugItem[i].no, heapID );
	}
}


//------------------------------------------------------------------
/**
 * @brief	�o�b�O�̃J�[�\���ʒu�f�[�^�m��
 * @param	heapID	�q�[�vID
 * @return	�J�[�\���ʒu�f�[�^
 */
//------------------------------------------------------------------
BAG_CURSOR * MyItem_BagCursorAlloc( u32 heapID )
{
	BAG_CURSOR * cursor;

	cursor = sys_AllocMemory( heapID, sizeof(BAG_CURSOR) );
	MI_CpuClear16( cursor, sizeof(BAG_CURSOR) );
	return cursor;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�o�b�O�̃J�[�\���ʒu�擾
 * @param	wk		�J�[�\���f�[�^
 * @param	pocket	�|�P�b�gID
 * @param	pos		�J�[�\���ʒu�擾�ꏊ
 * @param	scr		�X�N���[���J�E���^�擾�ꏊ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr )
{
	*pos = wk->fld.pos[pocket];
	*scr = wk->fld.scr[pocket];
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�o�b�O�̃|�P�b�g�ʒu�擾
 * @param	wk		�J�[�\���f�[�^
 * @return	none
 */
//------------------------------------------------------------------
u16 MyItem_FieldBagPocketGet( BAG_CURSOR * wk )
{
	return wk->fld.pocket;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�o�b�O�̃J�[�\���ʒu�Z�b�g
 * @param	wk		�J�[�\���f�[�^
 * @param	pocket	�|�P�b�gID
 * @param	pos		�J�[�\���ʒu
 * @param	scr		�X�N���[���J�E���^
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr )
{
	wk->fld.pos[pocket] = pos;
	wk->fld.scr[pocket] = scr;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�o�b�O�̃|�P�b�g�ʒu�Z�b�g
 * @param	wk		�J�[�\���f�[�^
 * @param	pocket	�|�P�b�gID
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagPocketSet( BAG_CURSOR * wk, u16 pocket )
{
	wk->fld.pocket = pocket;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̃J�[�\���ʒu�擾
 * @param	wk		�J�[�\���f�[�^
 * @param	pocket	�|�P�b�gID
 * @param	pos		�J�[�\���ʒu�擾�ꏊ
 * @param	scr		�X�N���[���J�E���^�擾�ꏊ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr )
{
	*pos = wk->btl.pos[pocket];
	*scr = wk->btl.scr[pocket];
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̍Ō�Ɏg��������擾
 * @param	wk		�J�[�\���f�[�^
 * @return	�Ō�Ɏg��������
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagLastItemGet( BAG_CURSOR * wk )
{
	return wk->btl.item;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̍Ō�Ɏg��������̃|�P�b�g�擾
 * @param	wk		�J�[�\���f�[�^
 * @return	�Ō�Ɏg��������̃|�P�b�g
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagLastPageGet( BAG_CURSOR * wk )
{
	return wk->btl.page;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̃|�P�b�g�y�[�W�̃J�[�\���ʒu�擾
 * @param	wk		�J�[�\���f�[�^
 * @return	�Ō�Ɏg��������
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagPocketPagePosGet( BAG_CURSOR * wk )
{
	return wk->btl.pocket;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̃J�[�\���ʒu�Z�b�g
 * @param	wk		�J�[�\���f�[�^
 * @param	pocket	�|�P�b�gID
 * @param	pos		�J�[�\���ʒu
 * @param	scr		�X�N���[���J�E���^
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr )
{
	wk->btl.pos[pocket] = pos;
	wk->btl.scr[pocket] = scr;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̃J�[�\���ʒu������
 * @param	wk		�J�[�\���f�[�^
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorPosInit( BAG_CURSOR * wk )
{
	u32	i;

	for( i=0; i<5; i++ ){
		MyItem_BattleBagCursorSet( wk, i, 0, 0 );
	}
	MyItem_BattleBagPocketPagePosSet( wk, 0 );
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̍Ō�Ɏg����������Z�b�g
 * @param	wk		�J�[�\���f�[�^
 * @param	item	�Ō�Ɏg�����A�C�e��
 * @param	page	�Ō�Ɏg�����A�C�e���̃y�[�W
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagLastItemSet( BAG_CURSOR * wk, u16 item, u16 page )
{
	wk->btl.item = item;
	wk->btl.page = page;
}

//------------------------------------------------------------------
/**
 * @brief	�퓬�o�b�O�̃|�P�b�g�y�[�W�̃J�[�\���ʒu�Z�b�g
 * @param	wk		�J�[�\���f�[�^
 * @return	�Ō�Ɏg��������
 */
//------------------------------------------------------------------
void MyItem_BattleBagPocketPagePosSet( BAG_CURSOR * wk, u16 pocket )
{
	wk->btl.pocket = pocket;
}

// �O���Q�ƃC���f�b�N�X����鎞�̂ݗL��(�Q�[�����͖���)
#ifdef CREATE_INDEX
void *Index_Get_Myitem_Offset(MYITEM *item, int type)
{
  switch(type){
  case BAG_POKE_NORMAL: return item->MyNormalItem; break;
  case BAG_POKE_EVENT: return item->MyEventItem; break;
  case BAG_POKE_WAZA: return item->MySkillItem; break;
  case BAG_POKE_SEAL: return item->MySealItem; break;
  case BAG_POKE_DRUG: return item->MyDrugItem; break;
  case BAG_POKE_NUTS: return item->MyNutsItem; break;
  case BAG_POKE_BALL: return item->MyBallItem; break;
  case BAG_POKE_BATTLE: return item->MyBattleItem; break;
  }
}
#endif
