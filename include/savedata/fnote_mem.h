//============================================================================================
/**
 * @file	fnote_mem.h
 * @brief	�`���m�[�g�@�f�[�^�Ǘ�����
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#ifndef F_NOTE_MEM_H
#define F_NOTE_MEM_H
#undef GLOBAL
#ifdef F_NOTE_MEM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
// ����
#define	FNOTE_TYPE_START		( 0 )	// �J�n
#define	FNOTE_TYPE_ACTION		( 1 )	// �s��
#define	FNOTE_TYPE_POKEMON		( 2 )	// �|�P����
#define	FNOTE_TYPE_TRAINER		( 3 )	// �g���[�i�[
#define	FNOTE_TYPE_SIO			( 4 )	// �ʐM

// �f�[�^ID
#define	FNOTE_ID_MYHOUSE		( 1 )		// �s���F����
#define	FNOTE_ID_LABO			( 2 )		// �s���F������
#define	FNOTE_ID_POKECENTER		( 3 )		// �s���F�|�P�����Z���^�[
#define	FNOTE_ID_FDSHOP_BUY		( 4 )		// �s���F�V���b�v�E����
#define	FNOTE_ID_FDSHOP_BUY2	( 5 )		// �s���F�V���b�v�E�����i�����j
#define	FNOTE_ID_FDSHOP_SALE	( 6 )		// �s���F�V���b�v�E����
#define	FNOTE_ID_FDSHOP_SALE2	( 7 )		// �s���F�V���b�v�E����i�����j
#define	FNOTE_ID_FDSHOP_TRADE	( 8 )		// �s���F�V���b�v�E����
#define	FNOTE_ID_GYMBEFORE		( 9 )		// �s���F�W���i���[�_�[��|���O�j
#define	FNOTE_ID_GYMAFTER		( 10 )		// �s���F�W���i���[�_�[��|������j
#define	FNOTE_ID_SITENNOU		( 11 )		// �s���F�l�V��
#define	FNOTE_ID_CHAMPION		( 12 )		// �s���F�`�����s�I��
#define	FNOTE_ID_CITY			( 13 )		// �s���F�X
#define	FNOTE_ID_DUNGEON		( 14 )		// �s���F�_���W����
#define	FNOTE_ID_BUILD			( 15 )		// �s���F����
#define	FNOTE_ID_GAMECORNER		( 16 )		// �s���F�Q�[���R�[�i�[
#define	FNOTE_ID_SAFARIZONE		( 17 )		// �s���F�T�t�@���]�[��
#define	FNOTE_ID_ITEMGET		( 18 )		// �s���F�A�C�e���擾
/** �|�P�������X�g�Ɠ������тɂ��邱�ƁI **/
#define	FNOTE_ID_IAIGIRI		( 19 )		// �s���F�Z�E����������
#define	FNOTE_ID_SORAWOTOBU		( 20 )		// �s���F�Z�E������Ƃ�
#define	FNOTE_ID_NAMINORI		( 21 )		// �s���F�Z�E�Ȃ݂̂�
#define	FNOTE_ID_KAIRIKI		( 22 )		// �s���F�Z�E�����肫
#define	FNOTE_ID_KIRIBARAI		( 23 )		// �s���F�Z�E����΂炢
#define	FNOTE_ID_IWAKUDAKI		( 24 )		// �s���F�Z�E���킭����
#define	FNOTE_ID_TAKINOBORI		( 25 )		// �s���F�Z�E�����̂ڂ�
#define	FNOTE_ID_ROCKCLIMB		( 26 )		// �s���F�Z�E���b�N�N���C��
#define	FNOTE_ID_FLASH			( 27 )		// �s���F�Z�E�t���b�V��
#define	FNOTE_ID_TELEPORT		( 28 )		// �s���F�Z�E�e���|�[�g
#define	FNOTE_ID_ANAWOHORU		( 29 )		// �s���F�Z�E���Ȃ��ق�
#define	FNOTE_ID_AMAIKAORI		( 30 )		// �s���F�Z�E���܂�������
#define	FNOTE_ID_OSYABERI		( 31 )		// �s���F�Z�E������ׂ�i�_�~�[�j
#define	FNOTE_ID_MIRUKUNOMI		( 32 )		// �s���F�Z�E�~���N�̂�
#define	FNOTE_ID_TAMAGOUMI		( 33 )		// �s���F�Z�E�^�}�S����

#define	FNOTE_ID_UG_FOSSIL		( 34 )		// �s���F�n���E���Ό@��
#define	FNOTE_ID_UG_BASE		( 35 )		// �s���F�n���E�閧��n

#define	FNOTE_ID_POKEGET		( 1 )		// �|�P�����F�ߊl
#define	FNOTE_ID_POKEDOWN		( 2 )		// �|�P�����F�|����

#define	FNOTE_ID_SB_SINGLE		( 1 )		// �ʐM�F�ʐM�ΐ�E�V���O��
#define	FNOTE_ID_SB_DOUBLE		( 2 )		// �ʐM�F�ʐM�ΐ�E�_�u��
#define	FNOTE_ID_SB_MULTI		( 3 )		// �ʐM�F�ʐM�ΐ�E�}���`
#define	FNOTE_ID_SB_MIX1		( 4 )		// �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1
#define	FNOTE_ID_SB_MIX2		( 5 )		// �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2
#define	FNOTE_ID_U_GREETING		( 6 )		// �ʐM�F���j�I�����[���E���A
#define	FNOTE_ID_U_POKECHG		( 7 )		// �ʐM�F���j�I�����[���E����
#define	FNOTE_ID_U_PICTURE		( 8 )		// �ʐM�F���j�I�����[���E���G����
#define	FNOTE_ID_U_MLTCHG		( 9 )		// �ʐM�F���j�I�����[���E�����l����
#define	FNOTE_ID_U_TRANSCEIVER	( 10 )		// �ʐM�F���j�I�����[���E�g�����V�[�o�[
#define	FNOTE_ID_U_BATTLE		( 11 )		// �ʐM�F���j�I�����[���E�ΐ�
#define	FNOTE_ID_RECORD			( 12 )		// �ʐM�F���R�[�h�R�[�i�[
#define	FNOTE_ID_CONTEST		( 13 )		// �ʐM�F�R���e�X�g
#define	FNOTE_ID_PORUTO			( 14 )		// �ʐM�F�|���g�쐬
#define	FNOTE_ID_GTC			( 15 )		// �ʐM�FGTC
#define	FNOTE_ID_BTLTOWER		( 16 )		// �ʐM�F�o�g���^���[

// ���s
#define	FNOTE_RESULT_WIN		( 0 )	// ����
#define	FNOTE_RESULT_LOSE		( 1 )	// ����
#define	FNOTE_RESULT_DRAW		( 2 )	// ��������

// �Z�C���f�b�N�X
#define	FNOTE_IAIGIRI			( FNOTE_ID_IAIGIRI-FNOTE_ID_IAIGIRI )		// ����������
#define	FNOTE_SORAWOTOBU		( FNOTE_ID_SORAWOTOBU-FNOTE_ID_IAIGIRI )	// ������Ƃ�
#define	FNOTE_NAMINORI			( FNOTE_ID_NAMINORI-FNOTE_ID_IAIGIRI )		// �Ȃ݂̂�
#define	FNOTE_KAIRIKI			( FNOTE_ID_KAIRIKI-FNOTE_ID_IAIGIRI )		// �����肫
#define	FNOTE_KIRIBARAI			( FNOTE_ID_KIRIBARAI-FNOTE_ID_IAIGIRI )		// ����΂炢
#define	FNOTE_IWAKUDAKI			( FNOTE_ID_IWAKUDAKI-FNOTE_ID_IAIGIRI )		// ���킭����
#define	FNOTE_TAKINOBORI		( FNOTE_ID_TAKINOBORI-FNOTE_ID_IAIGIRI )	// �����̂ڂ�
#define	FNOTE_ROCKCLIMB			( FNOTE_ID_ROCKCLIMB-FNOTE_ID_IAIGIRI )		// ���b�N�N���C��
#define	FNOTE_FLASH				( FNOTE_ID_FLASH-FNOTE_ID_IAIGIRI )			// �t���b�V��
#define	FNOTE_TELEPORT			( FNOTE_ID_TELEPORT-FNOTE_ID_IAIGIRI )		// �e���|�[�g
#define	FNOTE_ANAWOHORU			( FNOTE_ID_ANAWOHORU-FNOTE_ID_IAIGIRI )		// ���Ȃ��ق�
#define	FNOTE_AMAIKAORI			( FNOTE_ID_AMAIKAORI-FNOTE_ID_IAIGIRI )		// ���܂�������
#define	FNOTE_OSYABERI			( FNOTE_ID_OSYABERI-FNOTE_ID_IAIGIRI )		// ������ׂ�i�_�~�[�j
#define	FNOTE_MIRUKUNOMI		( FNOTE_ID_MIRUKUNOMI-FNOTE_ID_IAIGIRI )	// �~���N�̂�
#define	FNOTE_TAMAGOUMI			( FNOTE_ID_TAMAGOUMI-FNOTE_ID_IAIGIRI )		// �^�}�S����


#ifndef	__ASM_NO_DEF_	// ������ȍ~�́A�A�Z���u���ł͖���
#include "system/savedata_def.h"
#include "system/buflen.h"
#include "savedata/mystatus.h"
#include "savedata/playtime.h"


typedef struct _FNOTE_DATA FNOTE_DATA;

// �J�n�f�[�^
typedef struct {
	u32	year:7;		// �N
	u32	month:4;	// ��
	u32	week:3;		// �j��
	u32	day:5;		// ��
	u32	start:13;	// �J�n�ʒu
}FNOTE_WK_START;

// �s�����[�N
typedef struct {
	u8	id;			// ��zID
	u16	map;		// �}�b�vID
	u16	trainer;	// �g���[�i�[ID
	u16	item;		// �A�C�e��ID
}FNOTE_WK_ACTION;

// �|�P�������[�N
typedef struct {
	u8	id;			// ��zID
	u8	type:2;		// �\���^�C�v
	u8	time:4;		// ����
	u8	sex:2;		// ����
	u16	mons;		// �|�P����ID
}FNOTE_WK_POKE;

// �g���[�i�[���[�N
typedef struct {
	u16	id:1;		// ��zID
	u16	trid:15;	// �g���[�i�[ID
	u16	map;		// �}�b�vID
}FNOTE_WK_TRAINER;

// �ʐM���[�N
typedef struct {
	u8	id;									// ��zID
	u8	result:4;							// ���s
	u8	sex1:1;								// �ʐM����P�̐���
	u8	sex2:1;								// �ʐM����Q�̐���
	u8	poke_sex:2;							// �|�P�����̐���
	u16	name1[BUFLEN_PERSON_NAME];			// �ʐM����P�̖��O
	u16	name2[BUFLEN_PERSON_NAME];			// �ʐM����Q�̖��O
	u16	nickname[BUFLEN_POKEMON_NAME];		// �|�P�����̃j�b�N�l�[��
}FNOTE_WK_SIO;


#define	FNOTE_PAGE_MAX		( 10 )		///< �`���m�[�g�y�[�WMAX
#define	FNOTE_ACTION_MAX	( 4 )		///< �`���m�[�g�s�����[�N��
#define	FNOTE_SIO_MAX		( 2 )		///< �`���m�[�g�ʐM���[�N��



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �`���m�[�g�p���[�N�̃T�C�Y�擾
 *
 * @param	none
 *
 * @return	���[�N�T�C�Y
 */
//--------------------------------------------------------------------------------------------
GLOBAL int FNOTE_GetWorkSize(void);

//--------------------------------------------------------------------------------------------
/**
 * �`���m�[�g�p���[�N�������i�S�́j
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_InitAll( FNOTE_DATA * dat );

//--------------------------------------------------------------------------------------------
/**
 * �Z�[�u�f�[�^����`���m�[�g�̃|�C���^���擾
 *
 * @param	sv		�Z�[�u�f�[�^
 *
 * @return	�`���m�[�g�f�[�^
 */
//--------------------------------------------------------------------------------------------
GLOBAL FNOTE_DATA * SaveData_GetFNote( SAVEDATA * sv );

//--------------------------------------------------------------------------------------------
/**
 * �Z�[�u�y�[�W�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	flg		�Z�[�u���t���O ( TRUE = ���� )
 *
 * @retval	"flg = TRUE : �Z�[�u�y�[�W"
 * @retval	"flg = FALSE : NULL"
 */
//--------------------------------------------------------------------------------------------
GLOBAL FNOTE_DATA * FNOTE_SavePageGet( FNOTE_DATA * dat, BOOL flg );

//--------------------------------------------------------------------------------------------
/**
 * �Q�[���J�n���̖`���m�[�g�\���`�F�b�N
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	flg		�Z�[�u���t���O ( TRUE = ���� )
 *
 * @retval	"TRUE = �\��"
 * @retval	"FALSE = �\�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------
GLOBAL BOOL FNOTE_GameStartOpenCheck( FNOTE_DATA * dat, BOOL flg );

//--------------------------------------------------------------------------------------------
/**
 * ��z�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 * @param	type	�L�^�^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_DataSave( FNOTE_DATA * dat, void * wk, u8 type );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ ���t�E�J�n�ꏊ ]
 *
 * @param	start	�J�n�ꏊ
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 *
 * @li	���t��RTC����擾
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_StartDataMake( u16 start, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionHouseDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F������ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionLaboDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�|�P�����Z���^�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_PokemonCenterDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopBuyDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E�����i�����j ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopBuy2DataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopSaleDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E����i�����j ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopSale2DataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopTradeDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�W���i���[�_�[��|���O�j ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionGymBeforeDataMake( u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�W���i���[�_�[��|������j ]
 *
 * @param	map		�}�b�vID
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionGymAfterDataMake( u16 map, u16 trainer, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�l�V�� ]
 *
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionSitenouDataMake( u16 trainer, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�`�����s�I�� ]
 *
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionChampionDataMake( u16 trainer, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�X ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionCityDataMake( u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�_���W���� ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionDungeonDataMake( u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F���� ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionBuildDataMake( u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�Q�[���R�[�i�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionGameCornerDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�T�t�@���]�[�� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionSafariDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�A�C�e���擾 ]
 *
 * @param	item	�A�C�e��ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionItemDataMake( u16 item, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�Z ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionSkillDataMake( u8 waza, u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�n���E���Ό@�� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionUGFossilDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�n���E�閧��n ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionUGBaseDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �|�P�����F�ߊl ]
 *
 * @param	ptime	�v���C����
 * @param	mons	�|�P����ID
 * @param	sex		����
 * @param	time	���ԑ�
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_PokemonGetDataMake(
					const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �|�P�����F�|�� ]
 *
 * @param	ptyme	�v���C����
 * @param	mons	�|�P����ID
 * @param	sex		����
 * @param	time	���ԑ�
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_PokemonDownDataMake(
					const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �g���[�i�[ ]
 *
 * @param	map		�}�b�vID
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_TrainerDataMake( u16 map, u16 trainer, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�V���O�� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioSingleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�_�u�� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioDoubleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�}���` ]
 *
 * @param	name1	�ΐ푊��P�̖��O
 * @param	name2	�ΐ푊��Q�̖��O
 * @param	sex1	�ΐ푊��P�̐���
 * @param	sex2	�ΐ푊��Q�̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioMultiBtlDataMake(
				 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1 ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioMixBtl1DataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2 ]
 *
 * @param	name1	�ΐ푊��P�̖��O
 * @param	name2	�ΐ푊��Q�̖��O
 * @param	sex1	�ΐ푊��P�̐���
 * @param	sex2	�ΐ푊��Q�̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioMixBtl2DataMake(
				 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���A ]
 *
 * @param	name	����̖��O
 * @param	sex		����̐���
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionGreetDataMake( STRCODE * name, u8 sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���� ]
 *
 * @param	name		��������̖��O
 * @param	sex			��������̐���
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionChangeDataMake(
				STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���G���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionPictureDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�����l���� ]
 *
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionMltChgDataMake( STRCODE * nickname, u8 poke_sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�g�����V�[�o�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionTransceiverDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�ΐ� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionBattleDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���R�[�h�R�[�i�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioRecordDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�R���e�X�g ]
 *
 * @param	result	����
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioContestDataMake( u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�|���g�쐬 ]
 *
 * @param	name	����̖��O
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioPorutoDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�FGTC ]
 *
 * @param	name		��������̖��O
 * @param	sex			��������̐���
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioGTCDataMake(
				STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�o�g���^���[ ]
 *
 * @param	name	����̖��O
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioBattleTowerDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ��z�f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 * @param	type	�L�^�^�C�v
 * @param	page	�擾�y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_DataGet( FNOTE_DATA * dat, void * wk, u8 type, u8 page );


//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F����A�������A�����A�_���W��������o�� ]
 *
 * @param	my		�v���[���[�f�[�^
 * @param	dat		�`���m�[�g�̃Z�[�u�f�[�^
 * @param	now		���݂̃}�b�v
 * @param	before	�O�ɂ����}�b�v
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_DataMakeSaveMapChg(
				MYSTATUS * my, FNOTE_DATA * dat, u32 now, u32 before, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ����Ȍ����̕\���^�C�v�擾
 *
 * @param	name	���OID
 *
 * @return	�\���^�C�v
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 FNOTE_ExBuildPutTypeGet( u32 name );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F�X�ɓ��� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	map		���݂̃}�b�v
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_DataMakeSaveCity( FNOTE_DATA * dat, u32 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F�W�����[�_�[�A�`�����s�I���A�l�V�� & �g���[�i�[�F�g���[�i�[ ]
 *
 * @param	dat			�`���m�[�g�̃Z�[�u�f�[�^
 * @param	map			�]�[��ID
 * @param	trainer		�g���[�i�[ID
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_DataMakeSaveTrainer( FNOTE_DATA * dat, u16 map, u16 trainer, u32 heap );


#endif	__ASM_NO_DEF_

#undef GLOBAL
#endif	/* F_NOTE_MEM_H */
