//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imageclip_data.c
 *	@brief		�C���[�W�N���b�v�Z�[�u�f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.02.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "include/savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "include/savedata/savedata.h"
#include "include/gflib/system.h"
#include "include/gflib/assert.h"
#include <string.h>

#define	__IMAGECLIP_DATA_H_GLOBAL
#include "include/savedata/imageclip_data.h"


#include "include/gflib/strbuf_family.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_SAVEDATA_DATAINIT_FLAG	( 0x1234 )		// �������f�[�^�i�[���̃t���O
#define IMC_SAVEDATA_DATASET_FLAG	( 0x2345 )		// �Z�[�u�f�[�^�i�[���̃t���O

enum{
	IMC_ACCE_9_GET_NUM = 9,
	IMC_ACCE_1_GET_NUM = 1,
	
	IMC_ACCE_9_ARRY_IN = 8,		// 9�p�z��u32�ɓ���f�[�^�̐�
	IMC_ACCE_1_ARRY_IN = 32,	// 1�p�z��u32�ɓ���f�[�^�̐�
	IMC_BG_ARRY_IN	   = 4,		// BG�p�z��u32�ɓ���f�[�^�̐�
	IMC_ACCE_9_ARRY_BIT = 4,	// 9�p�z���1�f�[�^�Ɏg���r�b�g��
	IMC_ACCE_1_ARRY_BIT = 1,	// 1�p�z���1�f�[�^�Ɏg���r�b�g��
	IMC_BG_ARRY_BIT		= 8,	// BG�p�z���1�f�[�^�Ɏg���r�b�g��
	
	IMC_ACCE_9_ARRY_NUM	= 8,	// 9���Ă�A�N�Z�T���̃t���O�z��
	IMC_ACCE_1_ARRY_NUM = 2,	// 1���Ă�A�N�Z�T���̃t���O�z��
	IMC_BG_ARRY_NUM = 6,		// BG�̃t���O�z��
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	�|�P�����f�[�^
//=====================================
typedef struct _IMC_SAVEDATA_POKEMON{
	u32 personal_rnd;				///<�|�P�����̌�����
	u32 idno;						///<IDNo	���A�|�P�����p
	u16	monsno;						///<�����X�^�[�i���o�[
	u16 nickname[ IMC_SAVEDATA_NICKNAME_STR_NUM ];	///<�j�b�N�l�[��
	u16 oyaname[ IMC_SAVEDATA_OYANAME_STR_NUM ];	///<�j�b�N�l�[��
	s8 poke_pri;					///<�|�P�����D�揇��
	u8 poke_x;						///<�|�P���������W
	u8 poke_y;						///<�|�P���������W
	u8 form_id;					///<�`��A�g���r���[�g
	u8 oya_sex;						///<�e����
} ;

//-------------------------------------
//	�A�N�Z�T���f�[�^�\����
//=====================================
typedef struct _IMC_SAVEDATA_ACCESSORIE{
	u8 accessory_no;	///<�A�N�Z�T���i���o�[
	u8 accessory_x;		///<�A�N�Z�T�������W
	u8 accessory_y;		///<�A�N�Z�T�������W
	s8 accessory_pri;	///<�A�N�Z�T���\���D��
} ;



//-------------------------------------
//	�e���r�Ǘp�Z�[�u�f�[�^���[�N
//=====================================
typedef struct _IMC_TELEVISION_SAVEDATA{
	u32 init_flag;					///<�������ް����̃t���O
	IMC_SAVEDATA_POKEMON	pokemon;///<�|�P�����f�[�^
	u32 accessory_set_msk;			///<�i�[�A�N�Z�T���[�}�X�N
	PMS_DATA title;					///<�N���b�v�^�C�g��
	IMC_SAVEDATA_ACCESSORIE acce[ IMC_SAVEDATA_TELEVISION_ACCE_NUM ];	///<�A�N�Z�T��
	u8 bg_id;								///<bg�i���o�[	
	u8 country;	// ���R�[�h
} ;

//-------------------------------------
//	�R���e�X�g�p�Z�[�u�f�[�^���[�N
//=====================================
typedef struct _IMC_CONTEST_SAVEDATA{
	u32 init_flag;					///<�������ް����̃t���O
	u32 rank_code;					///<�R���e�X�g�����N�R�[�h
	IMC_SAVEDATA_POKEMON	pokemon;///<�|�P�����f�[�^
	u32 accessory_set_msk;			///<�i�[�A�N�Z�T���[�}�X�N
	IMC_SAVEDATA_ACCESSORIE acce[ IMC_SAVEDATA_CONTEST_ACCE_NUM ];	///<�A�N�Z�T��
	u8 bg_id;						///<bg�i���o�[	
} ;

//-------------------------------------
//	�A�C�e���ێ��Z�[�u�f�[�^���[�N
//=====================================
typedef struct _IMC_ITEM_SAVEDATA{
	u32 acce_9[ IMC_ACCE_9_ARRY_NUM ];		// 9���Ă�A�N�Z�T���@�擾�t���O
	u32 acce_1[ IMC_ACCE_1_ARRY_NUM ];		// 1���Ă�A�N�Z�T���@�擾�t���O
	u32 bg[ IMC_BG_ARRY_NUM ];				// BG�擾���ԃf�[�^
} ;


//-------------------------------------
//	�Z�[�u�f�[�^
//=====================================
struct _IMC_SAVEDATA{
	IMC_TELEVISION_SAVEDATA imc_television_savedata[ IMC_SAVEDATA_TELEVISION_SAVENUM ];	///<save�f�[�^
	IMC_CONTEST_SAVEDATA	imc_contest_savedata[ IMC_SAVEDATA_CONTEST_SAVENUM ];		///<save�f�[�^

	IMC_ITEM_SAVEDATA	imc_item_savedata;	///<�A�C�e���Z�[�u�f�[�^
};


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v���[�N�����Ă��Ȃ����`�F�b�N
 *
 *	@param	init_flag		�������f�[�^�t���O
 *
 *	@retval	TRUE	������	
 *	@retval FALSE	���Ă���
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_savedata( u32 init_flag )
{
	if( (init_flag == IMC_SAVEDATA_DATAINIT_FLAG) ||
		(init_flag == IMC_SAVEDATA_DATASET_FLAG) ){

		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�Ǘp�Z�[�u�f�[�^�̐������`�F�b�N
 *	
 *	@param	wk	�Z�[�u�f�[�^
 *
 *	@retval	TRUE	������	
 *	@retval FALSE	���Ă���
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_television_savedata( const IMC_TELEVISION_SAVEDATA* wk )
{
	return correct_savedata( wk->init_flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�Z�[�u�f�[�^�̐������`�F�b�N
 *	
 *	@param	wk	�Z�[�u�f�[�^
 *
 *	@retval	TRUE	������	
 *	@retval FALSE	���Ă���
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_contest_savedata( const IMC_CONTEST_SAVEDATA* wk )
{
	return correct_savedata( wk->init_flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�Ǘp�Z�[�u�f�[�^�̏�����
 *	
 *	@param	wk	�Z�[�u�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_television_savedata( IMC_TELEVISION_SAVEDATA* wk )
{
	memset( wk, 0, sizeof(IMC_TELEVISION_SAVEDATA) );
	wk->init_flag = IMC_SAVEDATA_DATAINIT_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�Z�[�u�f�[�^�̏�����
 *	
 *	@param	wk	�Z�[�u�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_contest_savedata( IMC_CONTEST_SAVEDATA* wk )
{
	memset( wk, 0, sizeof(IMC_CONTEST_SAVEDATA) );
	wk->init_flag = IMC_SAVEDATA_DATAINIT_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������[�N����f�[�^���擾
 *
 *	@param	ip		�|�P�����p�����[�^
 *	@param	x		�����W�擾��
 *	@param	y		�����W�擾��
 *	@param	pri		�\���D�揇��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void get_poke_mat( IMC_POKE* ip, u8* x, u8* y, s8* pri )
{
	int gx, gy;
	int gpri;

	IMC_POKE_MatrixGet( ip, &gx, &gy );
	gpri = IMC_POKE_DrawPriorityGet( ip );
	GF_ASSERT( gx < 256 );
	GF_ASSERT( gy < 256 );
	GF_ASSERT( gpri > -128 );

	*x = gx;
	*y = gy;
	*pri = gpri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����f�[�^�̊i�[
 *
 *	@param	p_pokemon	�C���[�W�N���b�v�|�P�����Z�[�u���[�N
 *	@param	pp			�|�P�����p�����[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	pri			�D�揇��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetPokeData_Local_Core( IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp, u8 x, u8 y, s8 pri )
{
	p_pokemon->monsno   = PokeParaGet(pp, ID_PARA_monsno, NULL);
	PokeParaGet(pp, ID_PARA_nickname, p_pokemon->nickname);
//	PokeParaGet(pp, ID_PARA_oyaname, p_pokemon->oyaname);
	p_pokemon->personal_rnd = PokeParaGet(pp, ID_PARA_personal_rnd, NULL );
	p_pokemon->idno = PokeParaGet(pp, ID_PARA_id_no, NULL);
	p_pokemon->form_id = PokeParaGet(pp, ID_PARA_form_no, NULL);
//	p_pokemon->oya_sex = PokeParaGet(pp, ID_PARA_oyasex, NULL);
	p_pokemon->poke_x = x;
	p_pokemon->poke_y = y;
	p_pokemon->poke_pri = pri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����f�[�^�̊i�[
 *
 *	@param	p_pokemon	�C���[�W�N���b�v�|�P�����Z�[�u���[�N
 *	@param	pp			�|�P�����p�����[�^
 *	@param	ip			�C���[�W�N���b�v�|�P�����f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetPokeData_Local( IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp, IMC_POKE* ip )
{
	u8 x, y;
	s8 pri;
	get_poke_mat( ip, &x, &y, &pri );
	ImcSaveData_SetPokeData_Local_Core( p_pokemon, pp, x, y, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�f�[�^�ݒ�
 *
 *	@param	p_pokemon		�|�P�����f�[�^
 *	@param	pbuff			�g���[�i�[���o�b�t�@
 *	@param	sex				����
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetTrData_Local( IMC_SAVEDATA_POKEMON* p_pokemon, const STRBUF* pbuff, int sex )
{
	STRBUF_GetStringCode( pbuff, p_pokemon->oyaname, IMC_SAVEDATA_OYANAME_STR_NUM );
	p_pokemon->oya_sex = sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����p�����[�^�̍쐬
 *	@param	p_pokemon		�C���[�W�N���b�v�|�P�����Z�[�u�f�[�^
 *	@param	pp				�|�P�����p�����[�^�i�[��
 */
//-----------------------------------------------------------------------------
static inline void imcsacedata_GetPokePara_Local( const IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp )
{
	PokeParaSet( pp, p_pokemon->monsno, 0, 0, RND_SET, p_pokemon->personal_rnd, ID_SET, p_pokemon->idno );
	PokeParaPut( pp, ID_PARA_nickname, p_pokemon->nickname );
//	PokeParaPut( pp, ID_PARA_oyaname, p_pokemon->oyaname );
	PokeParaPut( pp, ID_PARA_form_no, &p_pokemon->form_id );
//	PokeParaPut( pp, ID_PARA_oyasex, &p_pokemon->oya_sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���f�[�^�i�[
 *
 *	@param	p_acce		�A�N�Z�T�����[�N
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	pri			�D�揇��
 */
//-----------------------------------------------------------------------------
static void imcsavedata_SetAcce_Local( IMC_SAVEDATA_ACCESSORIE* p_acce, u8 acce_no, u8 x, u8 y, u8 pri )
{
	p_acce->accessory_no	= acce_no;
	p_acce->accessory_x		= x;
	p_acce->accessory_y		= y;
	p_acce->accessory_pri	= pri;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����ݒ�
 *
 *	@param	p_arry		�A�N�Z�T���z��
 *	@param	set_data	�ݒ萔
 *	@param	idx			�C���f�b�N�X
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imcsavedata_Acce9Set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// idx���傫����
	GF_ASSERT( idx < IMC_ACCE_GET_9_NUM );
	arry_idx = idx / IMC_ACCE_9_ARRY_IN;
	
	bit_idx = idx % IMC_ACCE_9_ARRY_IN;
	bit_idx *= IMC_ACCE_9_ARRY_BIT;

	// �̈�N���[��
	p_arry[ arry_idx ] &= ~(0xf << bit_idx);
	// �ݒ�
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����擾
 *
 *	@param	p_arry		�A�N�Z�T���z��
 *	@param	idx			�C���f�b�N�X	
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_Acce9Get( const u32* p_arry, u8 idx )
{
	u8 now;
	u8 arry_idx;
	u8 bit_idx;
	
	// idx���傫����
	GF_ASSERT( idx < IMC_ACCE_GET_9_NUM );

	arry_idx = idx / IMC_ACCE_9_ARRY_IN;
	bit_idx = idx % IMC_ACCE_9_ARRY_IN;
	bit_idx *= IMC_ACCE_9_ARRY_BIT;
	now = (p_arry[ arry_idx ] >> bit_idx) & 0xf;
	
	return now;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1bit�t���O�z��̃t���O�ݒ�
 *
 *	@param	p_arry		�z��|�C���^
 *	@param	set_data	�ݒ萔�@0 or 1
 *	@param	idx			�C���f�b�N�X 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcsavedata_1bitArry_set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// �l���傫����
	GF_ASSERT( set_data < 2 );

	arry_idx = idx / IMC_ACCE_1_ARRY_IN;
	bit_idx = idx % IMC_ACCE_1_ARRY_IN;
	bit_idx *= IMC_ACCE_1_ARRY_BIT;

	// �̈�N���[��
	p_arry[ arry_idx ] &= ~(0x1 << bit_idx);
	// �ݒ�
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	1�r�b�g�t���O�z��̒l�擾�֐�
 *
 *	@param	p_arry	1�r�b�g�z��
 *	@param	idx		�C���f�b�N�X
 *
 *	@return	�l
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_1bitArry_get( const u32* p_arry, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	arry_idx = idx / IMC_ACCE_1_ARRY_IN;
	bit_idx = idx % IMC_ACCE_1_ARRY_IN;
	bit_idx *= IMC_ACCE_1_ARRY_BIT;

	return (p_arry[ arry_idx ] >> bit_idx) & 0x1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�z��̃t���O�ݒ�
 *
 *	@param	p_arry		�z��|�C���^
 *	@param	set_data	�ݒ萔
 *	@param	idx			�C���f�b�N�X 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcsavedata_BGArry_set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// �l���傫����
	GF_ASSERT( set_data <= IMC_BG_RIGHT_MAX );

	arry_idx = idx / IMC_BG_ARRY_IN;
	bit_idx = idx % IMC_BG_ARRY_IN;
	bit_idx *= IMC_BG_ARRY_BIT;

	// �̈�N���[��
	p_arry[ arry_idx ] &= ~(0xff << bit_idx);
	// �ݒ�
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�t���O�z��̒l�擾�֐�
 *
 *	@param	p_arry	BG�z��
 *	@param	idx		�C���f�b�N�X
 *
 *	@return	�l
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_BGArry_get( const u32* p_arry, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	arry_idx = idx / IMC_BG_ARRY_IN;
	bit_idx = idx % IMC_BG_ARRY_IN;
	bit_idx *= IMC_BG_ARRY_BIT;

	return (p_arry[ arry_idx ] >> bit_idx) & 0xff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ێ����Ă���f�[�^�����擾
 *
 *	@param	p_arry		BG�z��
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_BGArry_FlagOnDataNumGet( const u32* p_arry )
{
	int i;
	int count;

	count = 0;
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

		if( imcsavedata_BGArry_get( p_arry, i ) != IMC_BG_RIGHT_MAX ){
			count ++;
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃A�N�Z�T����9�ێ�����A�N�Z�T�����`�F�b�N
 *
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *
 *	@retval	TRUE	9�ێ��o����
 *	@retval	FALSE	1�ێ��ł���
 */
//-----------------------------------------------------------------------------
static inline BOOL imcsavedata_AcceNo_9Check( u32 acce_no )
{
	if( acce_no < IMC_ACCE_GET_1_START ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���i���o�[��1�ێ��A�N�Z�T������̐����ɕύX
 *
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *
 *	@return	1�ێ��A�N�Z�T������̐�
 */
//-----------------------------------------------------------------------------
static inline u8 imcsavedata_AcceNo_1Get( u32 acce_no )
{
	GF_ASSERT( acce_no >= IMC_ACCE_GET_1_START );

	return acce_no - IMC_ACCE_GET_1_START;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�C�e���Z�[�u�̈�̏�����
 *
 *	@param	wk	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_item_savedata( IMC_ITEM_SAVEDATA* wk )
{
	int i;
	memset( wk, 0, sizeof(IMC_ITEM_SAVEDATA) );

	// BG�̗̈�͍ŏ��ɍő吔���i�[���Ă���
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		imcsavedata_BGArry_set( wk->bg, IMC_BG_RIGHT_MAX, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����i���o�[����@�|�P�����̍��W���擾
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_ImcPokeObjContestMatGet( POKEMON_PARAM* pp, u8* x, u8* y )
{
	u8 height = PokeParaHeightGet( pp, PARA_FRONT );

	*x = IMC_POKE_INIT_X - (IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT);

	// 1�܂��N���b�v���̂��Ђ傤�ɂ���
	*y = (IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT) - ((SOFT_SPRITE_SIZE_Y/2) - height) + IMC_POKE_MAT_CONTEST_Y_OFS;
	// 2���̌�A�Z�[�u���̂��Ђ傤�ɂ���	�e���r�p�ƃR���e�X�g�p�̃Z�[�u���̊���W�����킹�邽��
	*y += (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v���[�N�̏�����
 *
 *	@param	iw	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_Init(IMC_SAVEDATA * iw)
{
	int i;

	for( i=0; i<IMC_SAVEDATA_TELEVISION_SAVENUM; i++ ){
		clean_television_savedata( &iw->imc_television_savedata[ i ] );
	}
	for( i=0; i<IMC_SAVEDATA_CONTEST_SAVENUM; i++ ){
		clean_contest_savedata( &iw->imc_contest_savedata[ i ] );
	}
	clean_item_savedata( &iw->imc_item_savedata );
}


//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�Z�[�u�f�[�^���[�N�T�C�Y�̎擾
 *
 *	@param	none
 *
 *	@return	���[�N�T�C�Y
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetWorkSize(void)
{
	return sizeof(IMC_SAVEDATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�p���[�N�̐�������
 *
 *	@param	heapID		�q�[�vID
 *
 *	@return	���������C���[�W�N���b�v���[�N�̃|�C���^
 */
//-----------------------------------------------------------------------------
IMC_SAVEDATA * ImcSaveData_AllocWork(u32 heapID)
{
	IMC_SAVEDATA * iw;
	iw = sys_AllocMemory(heapID, sizeof(IMC_SAVEDATA));
	ImcSaveData_Init(iw);
	return iw;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�p���[�N�T�C�Y�擾
 *
 *	@param	none
 *
 *	@return	���[�N�T�C�Y
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetTelevisionWorkSize(void)
{
	return sizeof(IMC_TELEVISION_SAVEDATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p���[�N�T�C�Y�擾
 *
 *	@param	none
 *
 *	@return	���[�N�T�C�Y
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetContestWorkSize(void)
{
	return sizeof(IMC_CONTEST_SAVEDATA);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�p���[�N�쐬
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
IMC_TELEVISION_SAVEDATA* ImcSaveData_TelevisionAllocWork(u32 heapID)
{
	IMC_TELEVISION_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_TELEVISION_SAVEDATA));
	clean_television_savedata( iow );
	return iow;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p���[�N�쐬
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
IMC_CONTEST_SAVEDATA* ImcSaveData_ContestAllocWork(u32 heapID)
{
	IMC_CONTEST_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_CONTEST_SAVEDATA));
	clean_contest_savedata( iow );
	return iow;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�C�e���p���[�N�쐬
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
IMC_ITEM_SAVEDATA* ImcSaveData_ItemAllocWork(u32 heapID)
{
	IMC_ITEM_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_ITEM_SAVEDATA));
	clean_item_savedata( iow );
	
	return iow;
}


//-----------------------------------------------------------------------------
//	���[�N�f�[�^�ǂݏ���
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�f�[�^�̃e���r�W����1���擾����
 *
 *	@param	iw		�C���[�W�N���b�v���[�N
 *	@param	no		�擾�C���f�b�N�X
 *
 *	@return	�e���r�W����1�̃f�[�^
 */
//-----------------------------------------------------------------------------
IMC_TELEVISION_SAVEDATA* ImcSaveData_GetTelevisionSaveData(IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_SAVENUM );		///<�z��ő吔�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( &iw->imc_television_savedata[ no ] ) );
	
	return &iw->imc_television_savedata[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�Z�[�u�f�[�^��1���擾����
 *
 *	@param	iw		�C���[�W�N���b�v���[�N
 *	@param	no		�擾�C���f�b�N�X
 *
 *	@return	�R���e�X�g�p�Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
IMC_CONTEST_SAVEDATA* ImcSaveData_GetContestSaveData(IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_SAVENUM );		///<�z��ő吔�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( &iw->imc_contest_savedata[ no ] ) );
	
	return &iw->imc_contest_savedata[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^����A�C�e���ێ��Z�[�u���[�N���擾
 *
 *	@param	iw		�C���[�W�N���b�v���[�N
 *
 *	@return	�A�C�e���Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
IMC_ITEM_SAVEDATA* ImcSaveData_GetItemSaveData(IMC_SAVEDATA* iw)
{
	return &iw->imc_item_savedata;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃e���r�Ǘp�Z�[�u�f�[�^�̈�ɃZ�[�u���Ă��邩
 *
 *	@param	iw	�C���[�W�N���b�v���[�N
 *	@param	no	�`�F�b�N����C���f�b�N�X
 *
 *	@retval	TRUE	�Z�[�u�ς�
 *	@retval	FALSE	�Z�[��������
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionSaveData(const IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_SAVENUM );		///<�z��ő吔�`�F�b�N

	return ImcSaveData_CheckTelevisionData( &iw->imc_television_savedata[ no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃e���r�Ǘp�Z�[�u�f�[�^�̈�ɃZ�[�u���Ă��邩
 *
 *	@param	iw	�C���[�W�N���b�v���[�N
 *	@param	no	�`�F�b�N����C���f�b�N�X
 *
 *	@retval	TRUE	�Z�[�u�ς�
 *	@retval	FALSE	�Z�[��������
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestSaveData(const IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_SAVENUM );		///<�z��ő吔�`�F�b�N

	return ImcSaveData_CheckContestData( &iw->imc_contest_savedata[ no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ǉ��ł��邩�`�F�b�N
 *
 *	@param	p_iow		�Z�[�u�f�[�^���[�N
 *	@param	acce_no		�A�N�Z�T�����[�N
 *	@param	num			�A�N�Z�T����
 *
 *	@retval	TRUE	�ǉ��\
 *	@retval	FALSE	�ǉ��s�\
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckAcceAdd( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u32 get;
	BOOL ret = TRUE;

	// �ێ����擾
	get = ImcSaveData_GetAcceFlag( p_iow, acce_no );
	
	// 9���Ă邩1���Ă邩�`�F�b�N
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9
		get += num;
		if( get > 9 ){
			ret = FALSE;
		}
	}else{
		// 1
		get += num;
		if( get > 1 ){
			ret = FALSE;
		}
	}
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����Ă��邩�`�F�b�N
 *
 *	@param	p_iow		�Z�[�u�f�[�^���[�N
 *	@param	acce_no		�A�N�Z�T���i���o�[ 
 *
 *	@retval	TRUE	�ێ�
 *	@retval	FALSE	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckAcceGet( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no )
{
	u32 get;

	// �ێ����擾
	get = ImcSaveData_GetAcceFlag( p_iow, acce_no );

	if( get > 0 ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�w�i��ێ����Ă��邩���`�F�b�N
 *
 *	@param	p_iow		�Z�[�u�f�[�^���[�N
 *	@param	bg_no		BG�i���o�[
 *	
 *	@retval	TRUE	�ێ�
 *	@retval	FALSE	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckBgGet( const IMC_ITEM_SAVEDATA* p_iow, u32 bg_no )
{
	u32 get;

	// �ێ����Ԏ擾
	get = ImcSaveData_GetBGFlag( p_iow, bg_no );

	if( get != IMC_BG_RIGHT_MAX ){
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���t���O�������Ă��邩�`�F�b�N
 *
 *	@param	cp_iow		�A�C�e���Z�[�u���[�N
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 acce_no )
{
	u32 num;
	
	// �A�N�Z�T����
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9���Ă邩1���Ă邩�`�F�b�N
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9��
		num = imcsavedata_Acce9Get( cp_iow->acce_9, acce_no );
	}else{
		// 1��
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// �A�N�Z�T��No��1�ێ��A�N�Z�T������̐��ɕύX
		num = imcsavedata_1bitArry_get( cp_iow->acce_1, acce_no );
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ێ��t���O�擾
 *
 *	@param	cp_iow	�A�C�e���Z�[�u�f�[�^
 *	@param	bg_no	BG�i���o�[
 *	
 *	@return	�ێ���������
 *	@retval	IMC_BG_RIGHT_MAX�̂Ƃ��͂܂��ێ����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetBGFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 bg_no )
{
	BOOL get;
	
	// �w�i��
	GF_ASSERT( bg_no < IMC_BG_RIGHT_MAX );
	get = imcsavedata_BGArry_get( cp_iow->bg, bg_no );

	return get;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���@�w�i�@�S�ẴA�C�e���ێ�����Ԃ�
 *
 *	@param	cp_iow	�A�C�e���Z�[�u�f�[�^
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	u32 count;

	count = ImcSaveData_GetAcceAllNum( cp_iow );
	count += ImcSaveData_GetBGAllNum( cp_iow );
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���@�S�ẴA�C�e���ێ�����Ԃ�
 *
 *	@param	cp_iow	�A�C�e���Z�[�u�f�[�^
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	int i;	
	int count;
	count = 0;
	for( i=0; i<IMC_ACCE_MAX; i++ ){
		count += ImcSaveData_GetAcceFlag( cp_iow, i );
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�@�S�ẴA�C�e���ێ�����Ԃ�
 *
 *	@param	cp_iow	�A�C�e���Z�[�u�f�[�^
 *
 *	@return	�ێ���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	int i;
	int count = 0;
	
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

		if( ImcSaveData_GetBGFlag( cp_iow, i ) != IMC_BG_RIGHT_MAX ){
			count ++;
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����Z�b�g
 *
 *	@param	p_iow		�A�C�e���Z�[�u�̈�
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *	@param	num			�ݒ萔
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	// �A�N�Z�T����
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9���Ă邩1���Ă邩�`�F�b�N
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9�ȏ�ɂ��Ȃ�
		if( num > IMC_ACCE_9_GET_NUM ){
			num = IMC_ACCE_9_GET_NUM;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, num, acce_no );
	}else{
		// 1�ȏ�ɂ��Ȃ�
		if( num > IMC_ACCE_1_GET_NUM ){
			num = IMC_ACCE_1_GET_NUM;
		}
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// �A�N�Z�T��No��1�ێ��A�N�Z�T������̐��ɕύX
		imcsavedata_1bitArry_set( p_iow->acce_1, num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����̑����Z
 *
 *	@param	p_iow		�A�C�e���Z�[�u�̈�
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *	@param	num			�����l
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ImcSaveData_AddAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u8 now_num;
	
	// �A�N�Z�T����
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9���Ă邩1���Ă邩�`�F�b�N
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		now_num = imcsavedata_Acce9Get( p_iow->acce_9, acce_no );
		// 9�ȏ�ɂ��Ȃ�
		now_num += num;
		if( now_num > IMC_ACCE_9_GET_NUM ){
			now_num = IMC_ACCE_9_GET_NUM;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, now_num, acce_no );
	}else{
		now_num = imcsavedata_1bitArry_get( p_iow->acce_1, acce_no );
		// 1�ȏ�ɂ��Ȃ�
		now_num += num;
		if( now_num > IMC_ACCE_1_GET_NUM ){
			now_num = IMC_ACCE_1_GET_NUM;
		}
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// �A�N�Z�T��No��1�ێ��A�N�Z�T������̐��ɕύX
		imcsavedata_1bitArry_set( p_iow->acce_1, now_num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ����̈����Z
 *
 *	@param	p_iow		�A�C�e���Z�[�u�̈�
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *	@param	num			�����l
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SubAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u8 now_num;
	
	// �A�N�Z�T����
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9���Ă邩1���Ă邩�`�F�b�N
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		now_num = imcsavedata_Acce9Get( p_iow->acce_9, acce_no );
		if( now_num > num){
			now_num -= num;
		}else{
			now_num = 0;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, now_num, acce_no );
	}else{
		now_num = 0;
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// �A�N�Z�T��No��1�ێ��A�N�Z�T������̐��ɕύX
		imcsavedata_1bitArry_set( p_iow->acce_1, now_num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	BG�ێ��t���O�ݒ�
 *
 *	@param	p_iow		�A�C�e���Z�[�u�̈惏�[�N
 *	@param	bg_no		BG�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetBGFlag( IMC_ITEM_SAVEDATA* p_iow, u32 bg_no )
{
	u8 get_no;
	
	// �w�i��
	GF_ASSERT( bg_no < IMC_BG_RIGHT_MAX );

	// ���łɕێ����Ă��Ȃ����`�F�b�N
	if( imcsavedata_BGArry_get( p_iow->bg, bg_no ) == IMC_BG_RIGHT_MAX ){

		// �ݒ肷��ێ��������Ԃ��擾
		get_no = imcsavedata_BGArry_FlagOnDataNumGet( p_iow->bg );

		// �ݒ�
		imcsavedata_BGArry_set( p_iow->bg, get_no, bg_no );
	}
	
}





//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^�ɒl��ݒ�ς݂��`�F�b�N
 *
 *	@param	iow	�C���[�W�N���b�v���[�N
 *
 *	@retval	TRUE	�Z�[�u�ς�
 *	@retval	FALSE	�Z�[��������
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionData(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	if( iow->init_flag == IMC_SAVEDATA_DATASET_FLAG ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�����t���O��ݒ肷��
 *
 *	@param	iw	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetComplateFlagTelevisionData(IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	iow->init_flag = IMC_SAVEDATA_DATASET_FLAG;
	iow->country = CasetteLanguage;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^������������
 *
 *	@param	iw		�C���[�W�N���b�v���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_ClaenTelevisionData(IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	// ���[�N�̏�����
	clean_television_savedata( iow );
}
	
//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����f�[�^��o�^����
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pp		�|�P�����p�����[�^
 *	@param	ip		�C���[�W�N���b�v�|�P�����f�[�^
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionPokeData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	// �|�P�����f�[�^�i�[
	ImcSaveData_SetPokeData_Local( &iow->pokemon, pp, ip );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���f�[�^�ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N	
 *	@param	ao		�A�N�Z�T���[�f�[�^
 *	@param	no		�A�N�Z�T���[�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionAcceData(IMC_TELEVISION_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no)
{
	NNSG2dSVec2 mat = SWSP_GetSpritePos( ao->drawObj );
	int pri = SWSP_GetSpritePriority( ao->drawObj );
	
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<�z��ő吔�`�F�b�N
	GF_ASSERT( mat.x < 256 );		// u8�ɓ���悤��
	GF_ASSERT( mat.y < 256 );		// u8�ɓ���悤��
	GF_ASSERT( pri > -128 );		// u8�ɓ���悤��
	GF_ASSERT( !(iow->accessory_set_msk & (1 << no)) );	///<���d�o�^�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	
	//�@�f�[�^�ݒ�
	imcsavedata_SetAcce_Local( &iow->acce[ no ],
			ao->accessorie_no,
			mat.x,
			mat.y,
			pri);

	// �}�X�N�ݒ�
	iow->accessory_set_msk |= 1 << no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGID�̐ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	bg		BGID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionBgId(IMC_TELEVISION_SAVEDATA* iow, u8 bg)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	iow->bg_id = bg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�N���b�v�̃^�C�g���i�[
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	str		�^�C�g�����P��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTitle( IMC_TELEVISION_SAVEDATA* iow, const PMS_DATA* str )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Copy( &iow->title, str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�^�C�g���P��ݒ�
 *
 *	@param	iow		���[�N
 *	@param	word	�ȈՒP��ID
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTitlePmsWord( IMC_TELEVISION_SAVEDATA* iow, PMS_WORD word )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Clear( &iow->title );
	PMSDAT_SetWord( &iow->title, 0, word );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�ǃN���b�v�f�[�^�R�s�[�֐�
 *
 *	@param	iow			���[�N
 *	@param	set_iow		�ݒ肷��f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_CopyTelevision( IMC_TELEVISION_SAVEDATA* iow, const IMC_TELEVISION_SAVEDATA* set_iow )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	memcpy( iow, set_iow, sizeof(IMC_TELEVISION_SAVEDATA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�f�[�^�ݒ�
 *
 *	@param	iow		���[�N
 *	@param	pbuff	�g���[�i�[���f�[�^
 *	@param	sex		����
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTrData( IMC_TELEVISION_SAVEDATA* iow, const STRBUF* pbuff, int sex )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_SetTrData_Local( &iow->pokemon, pbuff, sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����̃C���f�b�N�X�̃A�N�Z�T�����o�^����Ă��邩�`�F�b�N
 *
 *	@param	iow		�P�Z�[�u�f�[�^
 *	@param	no		�A�N�Z�T���i�[�z��C���f�b�N�X
 *
 *	@retval	TRUE	�o�^�ς�
 *	@retval	FALSE	���o�^
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionAcceDataSet(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<�z��ő吔�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	return iow->accessory_set_msk & (1 << no);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�Ǘp���[�N����|�P�����Z�[�u�f�[�^�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�|�P�����Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_POKEMON* ImcSaveData_GetTelevisionPokemon(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return &iow->pokemon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�ǃ��[�N����A�N�Z�T���Z�[�u�f�[�^�擾
 *
 *	@param	iow		���[�N
 *	@param	no		�A�N�Z�T���i���o�[
 *
 *	@return	�A�N�Z�T���Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetTelevisionAcce(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return &iow->acce[no];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�����X�^�[�i���o�[
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetTelevisionPokeMonsNo(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeMonsNo(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����j�b�N�l�[���擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	������i�[�o�b�t�@�@�v�f���@IMC_SAVEDATA_STRBUF_NUM�K�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokeNickName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_GetUtilPokeNickName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̐e�l�[���擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	������i�[�o�b�t�@�@�v�f���@IMC_SAVEDATA_STRBUF_NUM�K�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokeOyaName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_GetUtilPokeOyaName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���ʎ擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�e����
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeOyaSex(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeOyaSex(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����������擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeRnd(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeRnd( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P����ID�i���o�[�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	IDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeIDNo(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeIDNo( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��i���o�[�̎擾
 *
 *	@param	iow
 *
 *	@return	�`��i���o�[
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeFormID(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeFormID( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�D�揇�ʎ擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetTelevisionPokePri(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokePri(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\�������W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	X���W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionPokeX(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeX( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�����W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionPokeY(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeY( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����p�����[�^���擾����
 *
 *	@param	iow		�C���[�W�N���b�v�Z�[�u�f�[�^
 *	@param	pp		�|�P�����p�����[�^
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokePara(const IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	imcsacedata_GetPokePara_Local( &iow->pokemon, pp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���i���o�[�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *	
 *	@return	�A�N�Z�T���i���o�[
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceNo(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilAcceNo( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T��X���W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *	
 *	@return	�A�N�Z�T���\�������W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceMatX(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilAcceMatX( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T�������W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *
 *	@return	�A�N�Z�T���\�������W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceMatY(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatY( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���\���D�揇�ʎ擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *
 *	@return	�A�N�Z�T���\���D�揇��
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetTelevisionAccePri(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	return ImcSaveData_GetUtilAccePri( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGID���擾
 *	
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	BGID
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionBgId(const IMC_TELEVISION_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	return iow->bg_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�^�C�g�����擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	�i�[��o�b�t�@
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionTitle( const IMC_TELEVISION_SAVEDATA* iow, PMS_DATA* pbuff )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Copy(pbuff, &iow->title);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�^�C�g���@�ȈՉ�b�P��
 *
 *	@param	iow		�Z�[�u���[�N
 *
 *	@return	�P��ID
 */
//-----------------------------------------------------------------------------
PMS_WORD ImcSaveData_GetTelevisionTitlePmsWord( const IMC_TELEVISION_SAVEDATA* iow )
{
	PMS_WORD work = PMSDAT_GetWordNumber( &iow->title, 0 );
	return work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���R�[�h�擾
 *
 *	@param	iow 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetCountryCode( const IMC_TELEVISION_SAVEDATA* iow )
{
	//�������`�F�b�N
	GF_ASSERT( correct_television_savedata( iow ) );

	return iow->country;
}
	

//-----------------------------------------------------------------------------
//	IMC_CONTEST_SAVEDATA����֐�
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�ɃR���e�X�g�Z�[�u�f�[�^���i�[����Ă��邩�`�F�b�N
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@retval	TRUE	�Z�[�u�ς�
 *	@retval	FALSE	�Z�[��������
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestData(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	if( iow->init_flag == IMC_SAVEDATA_DATASET_FLAG ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�����t���O��ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetComplateFlagContestData(IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	iow->init_flag = IMC_SAVEDATA_DATASET_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^������������
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_ClaenContestData(IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	// ���[�N�̏�����
	clean_contest_savedata( iow );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p���[�N�|�P�����f�[�^�̐ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pp		�|�P�����p�����[�^
 *	@param	ip		�C���[�W�N���b�v�|�P�������[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestPokeData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	// �|�P�����f�[�^�i�[
	ImcSaveData_SetPokeData_Local( &iow->pokemon, pp, ip );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�A�N�Z�T���f�[�^�̐ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	ao		�A�N�Z�T���f�[�^
 *	@param	no		�i�[���[�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestAcceData(IMC_CONTEST_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no)
{
	NNSG2dSVec2 mat = SWSP_GetSpritePos( ao->drawObj );
	int pri = SWSP_GetSpritePriority( ao->drawObj );
	
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<�z��ő吔�`�F�b�N
	GF_ASSERT( mat.x < 256 );		// u8�ɓ���悤��
	GF_ASSERT( mat.y < 256 );		// u8�ɓ���悤��
	GF_ASSERT( pri > -128 );		// u8�ɓ���悤��
	GF_ASSERT( !(iow->accessory_set_msk & (1 << no)) );	///<���d�o�^�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	
	//�@�f�[�^�ݒ�
	imcsavedata_SetAcce_Local( &iow->acce[ no ],
			ao->accessorie_no,
			mat.x,
			mat.y,
			pri);

	// �}�X�N�ݒ�
	iow->accessory_set_msk |= 1 << no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�pBGID�ݒ�
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	bg		BGID
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestBgId(IMC_CONTEST_SAVEDATA* iow, u8 bg)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	iow->bg_id = bg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p���[�N�@�R���e�X�g�����N�i�[
 *
 *	@param	iow			�C���[�W�N���b�v���[�N
 *	@param	rank_code	�����N�R�[�h
 *	
 *	@return	none
 *	
 *	rank_code
		///�R���e�X�g�����N�F�m�[�}�������N
		CONRANK_NORMAL		(0)
		///�R���e�X�g�����N�F�X�[�p�[�����N
		CONRANK_SUPER		(1)
		///�R���e�X�g�����N�F�n�C�p�[�����N
		CONRANK_HYPER		(2)
		///�R���e�X�g�����N�F�}�X�^�[�����N
		CONRANK_MASTER		(3)
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestRank(IMC_CONTEST_SAVEDATA* iow, u32 rank_code)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	iow->rank_code = rank_code;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g���[�N�̃f�[�^���R�s�[�ݒ�
 *
 *	@param	iow			���[�N
 *	@param	set_iow		�ݒ胏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_CopyContest( IMC_CONTEST_SAVEDATA* iow, const IMC_CONTEST_SAVEDATA* set_iow )
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	memcpy( iow, set_iow, sizeof(IMC_CONTEST_SAVEDATA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����f�[�^�ݒ�
 *
 *	@param	iow		�Z�[�u�f�[�^
 *	@param	pp		�|�P�����p�����[�^
 *	@param	pri		�D�揇��
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestPokeData_Easy( IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, s8 pri )
{
	u8 x;
	u8 y;

	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	// �|�P�����p�����[�^����|�P�����T�C�Y�擾
	ImcSaveData_ImcPokeObjContestMatGet( pp, &x, &y );

	// �|�P�����f�[�^�i�[
	ImcSaveData_SetPokeData_Local_Core( &iow->pokemon, pp, x, y, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���f�[�^�ݒ�
 *
 *	@param	iow			�Z�[�u���[�N
 *	@param	acce_idx	�A�N�Z�T���z��C���f�b�N�X
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	pri			�D�揇��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestAcceData_Easy( IMC_CONTEST_SAVEDATA* iow, u32 acce_idx, u8 acce_no, u8 x, u8 y, s8 pri )
{
	GF_ASSERT( acce_idx < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<�z��ő吔�`�F�b�N
	GF_ASSERT( acce_no < IMC_ACCE_MAX );		///<�A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( x < 256 );		// u8�ɓ���悤��
	GF_ASSERT( y < 256 );		// u8�ɓ���悤��
	GF_ASSERT( pri > -128 );		// u8�ɓ���悤��
	GF_ASSERT( !(iow->accessory_set_msk & (1 << acce_idx)) );	///<���d�o�^�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	// �A�N�Z�T���̗D�揇�ʂ��A�����I�Ƀ|�P����������������
	if( iow->pokemon.poke_pri >= pri ){
		pri = iow->pokemon.poke_pri + 1;
	}
	
	//�@�f�[�^�ݒ�
	imcsavedata_SetAcce_Local( &iow->acce[ acce_idx ],
			acce_no,
			x,
			y,
			pri);

	// �}�X�N�ݒ�
	iow->accessory_set_msk |= 1 << acce_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����̃C���f�b�N�X�̃A�N�Z�T�����o�^����Ă��邩�`�F�b�N
 *
 *	@param	iow		�P�Z�[�u�f�[�^
 *	@param	no		�A�N�Z�T���i�[�z��C���f�b�N�X
 *
 *	@retval	TRUE	�o�^�ς�
 *	@retval	FALSE	���o�^
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestAcceDataSet(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<�z��ő吔�`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	if( (iow->accessory_set_msk & (1 << no)) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�@�g���[�i�[�f�[�^
 *	
 *	@param	iow		���[�N
 *	@param	pbuff	�g���[�i�[��
 *	@param	sex		����
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestTrData( IMC_CONTEST_SAVEDATA* iow, const STRBUF* pbuff, int sex )
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_SetTrData_Local( &iow->pokemon, pbuff, sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p���[�N����|�P�����Z�[�u�f�[�^�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�|�P�����Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_POKEMON* ImcSaveData_GetContestPokemon(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return &iow->pokemon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g���[�N����A�N�Z�T���Z�[�u�f�[�^�擾
 *
 *	@param	iow		���[�N
 *	@param	no		���[�N�i���o�[
 *
 *	@return	�A�N�Z�T���Z�[�u�f�[�^
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetContestAcce(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	return &iow->acce[ no ];
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����i���o�[
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�|�P�����i���o�[
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetContestPokeMonsNo(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeMonsNo(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����j�b�N�l�[��
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	������i�[�o�b�t�@�@�v�f���@IMC_SAVEDATA_STRBUF_NUM�K�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokeNickName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_GetUtilPokeNickName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�|�P�����e���O�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	���O�i�[�̈�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokeOyaName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_GetUtilPokeOyaName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���ʎ擾
 *
 *	@param	iow	���[�N
 *
 *	@return	�e����
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeOyaSex(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeOyaSex(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�|�P�����ő̗������擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�ő̗���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeRnd(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeRnd( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�|�P����IDNo�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�|�P����IDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeIDNo(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeIDNo( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�`��i���o�[�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�`��i���o�[
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeFormID(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeFormID( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�|�P�����\���D�揇��	�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�\���D�揇��
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetContestPokePri(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokePri(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�|�P���������W	�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestPokeX(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeX( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�|�P���������W	�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestPokeY(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeY( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����p�����[�^���쐬����
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pp		�|�P�����p�����[�^�i�[��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokePara(const IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	imcsacedata_GetPokePara_Local( &iow->pokemon, pp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p	�A�N�Z�T���i���o�[�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *
 *	@return	�A�N�Z�T���i���o�[
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceNo(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceNo( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�A�N�Z�T�������W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceMatX(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatX( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�A�N�Z�T�������W�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���[�C���f�b�N�X
 *
 *	@return	�A�N�Z�T�������W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceMatY(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatY( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�A�N�Z�T���\���D�揇��	�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	no		�A�N�Z�T���C���f�b�N�X
 *
 *	@return	�\���D�揇��
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetContestAccePri(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1�f�[�^�����A�N�Z�T���ő吔�`�F�b�N
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<�A�N�Z�T���f�[�^�i�[�ς݃`�F�b�N
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAccePri( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@BGID�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	BGID
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestBgId(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return iow->bg_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�����N�R�[�h�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *
 *	@return	�����N�R�[�h
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestRank(const IMC_CONTEST_SAVEDATA* iow)
{
	//�������`�F�b�N
	GF_ASSERT( correct_contest_savedata( iow ) );
	return iow->rank_code;
}



//-------------------------------------
//	�|�P�����f�[�^�擾
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������X�^�[�i���o�[�擾
 *
 *	@param* iow		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetUtilPokeMonsNo(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����j�b�N�l�[���擾
 *
 *	@param	iow		���[�N
 *	@param	pbuff	������i�[�o�b�t�@�@�v�f���@IMC_SAVEDATA_STRBUF_NUM�K�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokeNickName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff)
{
	STRBUF_SetStringCode(pbuff, iow->nickname);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����e���O�擾
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pbuff	���O�i�[�̈�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokeOyaName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff)
{
	STRBUF_SetStringCode(pbuff, iow->oyaname);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ő̗������擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�ő̗���
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeRnd(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->personal_rnd;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P����IDNo�擾
 *
 *	@param	iow		���[�N	
 *
 *	@return	�|�P����IDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeIDNo(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->idno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��i���o�[�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�`��i���o�[
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeFormID(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->form_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���ʎ擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�e����
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeOyaSex(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->oya_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����\���D�揇��	�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�\���D�揇��
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetUtilPokePri(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_pri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������W	�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilPokeX(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������W	�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�����W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilPokeY(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����p�����[�^���쐬����
 *
 *	@param	iow		�C���[�W�N���b�v���[�N
 *	@param	pp		�|�P�����p�����[�^�i�[��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokePara(const IMC_SAVEDATA_POKEMON* iow, POKEMON_PARAM* pp)
{
	imcsacedata_GetPokePara_Local( iow, pp );
}


//-------------------------------------
//	�A�N�Z�T���f�[�^�擾
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���i���o�[�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�A�N�Z�T���i���o�[
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceNo(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T��X���W�擾
 *
 *	@param	iow		���[�N
 *	
 *	@return	�A�N�Z�T���\�������W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceMatX(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T�������W�擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�A�N�Z�T���\�������W
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceMatY(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���\���D�揇�ʎ擾
 *
 *	@param	iow		���[�N
 *
 *	@return	�A�N�Z�T���\���D�揇��
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetUtilAccePri(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_pri;
}

//-------------------------------------
//	���R�[�h����
//=====================================
// �Z�[�u���邩�`�F�b�N�֐�
static BOOL imcSaveData_RecordMixSaveCheck( IMC_SAVEDATA* iw, const IMC_TELEVISION_SAVEDATA* cp_src )
{
	int i;
	const void* cp_checkdata;
	u32 hash_0, hash_1;
	MATHCRC32Table hash_tbl;
	BOOL ret_val = TRUE;
	
	// �Z�[�u�f�[�^���i�[����Ă��郏�[�N���`�F�b�N
	if( ImcSaveData_CheckTelevisionData( cp_src ) == TRUE ){

		MATH_CRC32InitTable( &hash_tbl );
		hash_0 = MATH_CalcCRC32( &hash_tbl, cp_src, sizeof(IMC_TELEVISION_SAVEDATA) );

		// �ێ����Ă��郏�[�N�̒��ɓ����f�[�^���Ȃ����`�F�b�N
		for( i=0; i<IMC_SAVEDATA_TELEVISION_SAVENUM; i++ ){
			cp_checkdata = ImcSaveData_GetTelevisionSaveData( iw, i );
			MATH_CRC32InitTable( &hash_tbl );
			hash_1 = MATH_CalcCRC32( &hash_tbl, cp_checkdata, sizeof(IMC_TELEVISION_SAVEDATA) );

			// �n�b�V���l����v�����Ƃ��A
			// �f�[�^�X�V���Ȃ�
			if( hash_1 == hash_0 ){
				ret_val = FALSE;
				break;
			}
		}
	}else{
		ret_val = FALSE;
	}
	return ret_val;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���R�[�h����
 *
 *	@param	datanum		���R�[�h�f�[�^�ő吔
 *	@param	myid		������ID
 *	@param	iw			�Z�[�u�f�[�^
 *	@param	cpp_arry	�f�[�^�z��
 */
//-----------------------------------------------------------------------------
void ImcSaveData_RecordMix( u8 datanum, int myid, IMC_SAVEDATA* iw, const void** cpp_arry )
{
	int data_num;	// ���f�[�^��
	IMC_TELEVISION_SAVEDATA* p_dest;
	const IMC_TELEVISION_SAVEDATA* cp_src;
	int i;
	int count;
	
	// ���f�[�^���`�F�b�N
	data_num = 0;
	for( i=0; i<datanum; i++ ){

		// �����̓p�X
		if( i==myid ){
			continue;
		}
		
		if( cpp_arry[ i ] != NULL ){
			cp_src = cpp_arry[ i ];
			// �f�[�^�L��
			if( imcSaveData_RecordMixSaveCheck( iw, cp_src ) == TRUE ){
				data_num ++;
			}
		}
	}

	// �����o�����Ŋi�[���Ă���
	// ���������f�[�^��data_num�Â��炷	
	for( i=IMC_SAVEDATA_TELEVISION_SAVENUM - 1; i>=IMC_SAVEDATA_TELEVISION_OTHER_S; i-- ){
		
		// �ړ���̃o�b�t�@������Ȃ�R�s�[
		if( i+data_num < IMC_SAVEDATA_TELEVISION_SAVENUM ){
			p_dest = ImcSaveData_GetTelevisionSaveData( iw, i+data_num );
			cp_src = ImcSaveData_GetTelevisionSaveData( iw, i );
			ImcSaveData_CopyTelevision( p_dest, cp_src );
		}
	}

	// IMC_SAVEDATA_TELEVISION_OTHER_S�̃Z�[�u�f�[�^����
	// ���Ƀf�[�^��ݒ肵�Ă���
	count = IMC_SAVEDATA_TELEVISION_OTHER_S;	// �Z�[�u��o�b�t�@����
	for( i=0; i<datanum; i++ ){

		// �����̓p�X
		if( i==myid ){
			continue;
		}
		
		if( cpp_arry[ i ] != NULL ){
			cp_src = cpp_arry[ i ];
			// �f�[�^�L��
			if( imcSaveData_RecordMixSaveCheck( iw, cp_src ) == TRUE ){
				p_dest = ImcSaveData_GetTelevisionSaveData( iw, count );
				count ++;
				ImcSaveData_CopyTelevision( p_dest, cp_src );
			}
		}
	}
}



//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������ԃf�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	�C���[�W�N���b�v���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
IMC_SAVEDATA * SaveData_GetImcSaveData(SAVEDATA * sv)
{
	IMC_SAVEDATA * is = NULL;
	is = SaveData_Get(sv, GMDATA_ID_IMAGECLIPDATA);
	return is;
}

//----------------------------------------------------------
//	�f�o�b�O�p
//----------------------------------------------------------
#ifdef PM_DEBUG
void Debug_ImcSaveData_Make(IMC_SAVEDATA * iw, int option)
{
	int i;
	IMC_ITEM_SAVEDATA* p_item;

	p_item = ImcSaveData_GetItemSaveData( iw );
	
	// �A�C�e���f�[�^��S�Ēǉ�
	for( i=0; i<IMC_ACCE_MAX; i++ ){

		if( i < IMC_ACCE_GET_1_START ){
			ImcSaveData_SetAcceFlag( p_item, i, IMC_ACCE_9_GET_NUM );
		}else{
			ImcSaveData_SetAcceFlag( p_item, i, IMC_ACCE_1_GET_NUM );
		}
	}
	// BG
/*	for( i=IMC_BG_RIGHT_MAX; i>0; i-- ){
		ImcSaveData_SetBGFlag( p_item, i - 1 );
	}//*/
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		ImcSaveData_SetBGFlag( p_item, i );
	}
}

void Debug_ImcSaveData_SetItemData(IMC_ITEM_SAVEDATA* iow)
{
	int i;

	// �A�C�e���f�[�^��S�Ēǉ�
	for( i=0; i<IMC_ACCE_MAX; i++ ){

		if( i < IMC_ACCE_GET_1_START ){
			ImcSaveData_SetAcceFlag( iow, i, IMC_ACCE_9_GET_NUM );
		}else{
			ImcSaveData_SetAcceFlag( iow, i, IMC_ACCE_1_GET_NUM );
		}
	}
	// BG
/*	for( i=IMC_BG_RIGHT_MAX; i>0; i-- ){
		ImcSaveData_SetBGFlag( iow, i - 1 );
	}//*/
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		ImcSaveData_SetBGFlag( iow, i );
	}
}

static void debug_PokeDataSet( IMC_SAVEDATA_POKEMON* p_poke, POKEMON_PARAM* p_pp )
{
	p_poke->monsno = PokeParaGet(p_pp, ID_PARA_monsno, NULL);
	PokeParaGet(p_pp, ID_PARA_nickname, p_poke->nickname);
	PokeParaGet(p_pp, ID_PARA_oyaname, p_poke->oyaname);
	p_poke->personal_rnd = PokeParaGet(p_pp, ID_PARA_personal_rnd, NULL );
	p_poke->idno = PokeParaGet(p_pp, ID_PARA_id_no, NULL);
	p_poke->form_id = PokeParaGet(p_pp, ID_PARA_form_no, NULL);
	p_poke->oya_sex = PokeParaGet(p_pp, ID_PARA_oyasex, NULL);
	p_poke->poke_x		= IMC_RBOX_END_SX + (IMC_RBOX_AREA_WIDTH/2);
	p_poke->poke_y		= IMC_RBOX_END_SY + (IMC_RBOX_AREA_HEIGHT/2);
	p_poke->poke_pri	= 5;
}
static void debug_AcceDataSet( IMC_SAVEDATA_ACCESSORIE* p_acce, u32 rnd )
{
	int acce_no;
	int x, y;
	int pri;

	// �o���邾���|�P�����̍��W�ɂ��킹��
	acce_no = (rnd * 555) % IMC_ACCE_MAX;
	x = (IMC_RBOX_END_SX + (IMC_RBOX_AREA_WIDTH/2) - 40) + ((rnd * 9) % 80);
	y = (IMC_RBOX_END_SY + (IMC_RBOX_AREA_HEIGHT/2) - 40) + ((rnd * 2) % 80);
	pri = (rnd * 15) % 20;
	imcsavedata_SetAcce_Local( p_acce, acce_no, x, y, pri );
}

void Debug_ImcSaveData_MakeTelevisionDummyData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num )
{
	int i;
	
	// ������
	ImcSaveData_ClaenTelevisionData( iow );

	// �|�P�����o�^
	debug_PokeDataSet( &iow->pokemon, p_pp );

	// �A�N�Z�T���f�[�^�ݒ�
	for( i=0; i<acce_num; i++ ){
		debug_AcceDataSet( &iow->acce[i], iow->pokemon.personal_rnd * (i+1) );
		iow->accessory_set_msk |= 1 << i;
	}
	iow->bg_id = 0;

	// �Z�[�u����
	ImcSaveData_SetComplateFlagTelevisionData( iow );
}

void Debug_ImcSaveData_MakeContestDummyData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num, u32 rank_code )
{
	int i;
	
	// ������
	ImcSaveData_ClaenContestData( iow );

	// �|�P�����o�^
	debug_PokeDataSet( &iow->pokemon, p_pp );

	// �A�N�Z�T���f�[�^�ݒ�
	for( i=0; i<acce_num; i++ ){
		debug_AcceDataSet( &iow->acce[i], iow->pokemon.personal_rnd * (i+1) );
		iow->accessory_set_msk |= 1 << i;
	}

	iow->rank_code = rank_code;
	iow->bg_id = 0;

	// �Z�[�u����
	ImcSaveData_SetComplateFlagContestData( iow );
}


#endif

