//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_poke_obj.c
 *	@brief		�C���[�W�N���b�v�@�|�P�����f�[�^	
 *	@author		tomoya takahashi 
 *	@data		2005.09.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "system/arc_util.h"
#include "include/poketool/monsno.h"

#define __IMC_POKE_OBJ_H_GLOBAL
#include "include/application/imageClip/imc_poke_obj.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
/*
#define IMC_POKE_IN_SIZE_SML	(20)
#define IMC_POKE_IN_SIZE_MDL	(10)
#define IMC_POKE_IN_SIZE_BIG	(5)

#define IMC_POKE_IN_SML	(0)
#define IMC_POKE_IN_MDL	(1)
#define IMC_POKE_IN_BIG	(2)
#define IMC_POKE_IN_SIZE_NUM	( 3 )//*/


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static int GetInSize_SizeX( char* buff, int pokegra_x );
static void GetInSize_Draw( char* buff );

static void SetPokeHitTbl( RECT_HIT_TBL* p_tbl, int x, int y, int size_hx, int size_hy );

//-----------------------------------------------------------------------------
/**
*	�������O���[�o���ϐ�
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����̃L�����N�^�f�[�^��`��V�X�e���ɓo�^
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	arc_data		�A�[�J�C�u�f�[�^
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_CharSet( IMC_DRAW_DATA* drawData, SOFT_SPRITE_ARC* arc_data )
{
	// �L�����N�^�f�[�^��o�^
	void* buff;
	NNSG2dCharacterData* p_char;
	
	buff = ArcUtil_Load( arc_data->arc_no, arc_data->index_chr, FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_TOP );
	p_char = IMC_DRAW_SetCharData( drawData, buff, IMC_DRAW_POKE_CHAR_ID );

	SoftSpriteChrMask( (u8*)p_char->pRawData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�@�|�P�����f�[�^�쐬
 *
 *	@param	poke			�C���[�W�N���b�v�@�|�P�����f�[�^
 *	@param	sprite_man		�\�t�g�E�F�A�X�v���C�g�}�l�[�W��
 *	@param	poke_para		�|�P�����p�����[�^�\����
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_Init( IMC_POKE* poke, SOFT_SPRITE_MANAGER* sprite_man, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap )
{
	int monsno = PokeParaGet( poke_para, ID_PARA_monsno, NULL );

	// �|�P�����O���t�B�b�N�擾
	PokeGraArcDataGetPP(arc_data, poke_para, PARA_FRONT);
	
	// �\���ݒ�
	poke->sprite = SoftSpriteAdd( 
			sprite_man,
			arc_data,
			IMC_POKE_INIT_X,IMC_POKE_INIT_Y, 
			IMC_POKE_DEFAULT_PRI, 0, NULL, NULL);


	// �f�[�^�쐬
	{
		int x, y;
		IMC_POKE_SizeGet( poke, &x, &y );
		x /= 2;
		y /= 2;
		poke->hit_tbl.rect.top		= IMC_POKE_INIT_Y - y;
		poke->hit_tbl.rect.bottom	= IMC_POKE_INIT_Y + y;
		poke->hit_tbl.rect.left		= IMC_POKE_INIT_X - x;
		poke->hit_tbl.rect.right	= IMC_POKE_INIT_X + x;

		SetPokeHitTbl( &poke->hit_tbl, IMC_POKE_INIT_X, IMC_POKE_INIT_Y, x, y );
	}

	// �H������ŗǂ��T�C�Y�ݒ�
	{
		u8 height = PokeParaHeightGet( poke_para, PARA_FRONT );
		// �L�����N�^�f�[�^��o�^
		void* buff;
		NNSG2dCharacterData* p_char;
		
		buff = ArcUtil_Load( arc_data->arc_no, arc_data->index_chr, FALSE, heap, ALLOC_TOP );
		NNS_G2dGetUnpackedCharacterData( buff, &p_char );

		SoftSpriteChrMask( (u8*)p_char->pRawData );	
		
		poke->ins_x = GetInSize_SizeX( p_char->pRawData, p_char->W*8 );
		poke->ins_y = height;

//		GetInSize_Draw( p_char->pRawData );

		sys_FreeMemoryEz( buff );
	}

	// �|�P�����f�[�^�ێ�
	poke->poke_para = poke_para;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�@�|�P�����f�[�^�j��
 *
 *	@param	poke			�C���[�W�N���b�v�@�|�P�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_Delete( IMC_POKE* poke )
{
	SoftSpriteDel( poke->sprite );
	memset( poke, 0, sizeof( IMC_POKE ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʂ�ݒ�
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	priority	�D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_DrawPrioritySet( IMC_POKE* poke, int priority )
{
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_Z, priority );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʂ��擾
 *
 *	@param	poke		�|�P�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_POKE_DrawPriorityGet( IMC_POKE* poke )
{
	return SoftSpriteParaGet( poke->sprite, SS_PARA_POS_Z );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W��ݒ�
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_MatrixSet( IMC_POKE* poke, int x, int y )
{
	int size_x, size_y;
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_X, x );
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_Y, y );

	size_y /= 2;
	size_x /= 2;
	
	SetPokeHitTbl( &poke->hit_tbl, x, y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����ƃ^�b�`�p�l���̓����蔻��
 *
 *	@param	poke	�|�P�����f�[�^
 *
 *	@retval	TRUE	������
 *	@retval	FALSE	������Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHit( IMC_POKE* poke )
{
	return GF_TP_SingleHitCont( &poke->hit_tbl );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����Ǝw����W�̓����蔻��
 *
 *	@param	poke	�|�P�����f�[�^
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@retval	TRUE	������
 *	@retval	FALSE	������Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitSelf( IMC_POKE* poke, int x, int y )
{
	
	return GF_TP_SingleHitSelf( &poke->hit_tbl, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������W���擾
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_MatrixGet( IMC_POKE* poke, int* x, int* y )
{
	*x = SoftSpriteParaGet( poke->sprite, SS_PARA_POS_X );
	*y = SoftSpriteParaGet( poke->sprite, SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����T�C�Y���擾
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_SizeGet( IMC_POKE* poke, int* x, int* y )
{
	*x = SOFT_SPRITE_SIZE_X;
	*y = SOFT_SPRITE_SIZE_Y;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	offs_x		���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y		���ォ��̃I�t�Z�b�g�����W
 *	@param	char_data	�L�����N�^�f�[�^	
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitEx( IMC_POKE* poke, int* offs_x, int* offs_y, NNSG2dCharacterData* char_data )
{
	int check;		// �`�F�b�N�p
	int size_x, size_y;	// �T�C�Y	
	int x, y;		// ���݂̒��S���W
	
	// �܂������蔻��𕁒ʂɍs��
	check = IMC_POKE_TPHit( poke );
	if( check == FALSE ){
		return FALSE;
	}

	// ������W�擾
	IMC_POKE_MatrixGet( poke, &x, &y );
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	x -= (size_x / 2);
	y -= (size_y / 2);

	// �I�t�Z�b�g�l���擾
	*offs_x = sys.tp_x - x;
	*offs_y = sys.tp_y - y;


	// ���̈ʒu�̃L�����N�^�f�[�^���`�F�b�N
	// �����F�łȂ������`�F�b�N
	check = IMC_DRAW_CharCheck( char_data, *offs_x, *offs_y, 0 );

	// color�i���o�[���O�Ȃ�Ԃ�
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��	���W�w��
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	x			���ォ��̃I�t�Z�b�g�����W
 *	@param	y			���ォ��̃I�t�Z�b�g�����W
 *	@param	char_data	�L�����N�^�f�[�^	
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitExSelf( IMC_POKE* poke, int x, int y, NNSG2dCharacterData* char_data )
{
	int check;		// �`�F�b�N�p
	int size_x, size_y;	// �T�C�Y	
	int cx, cy;		// ���݂̒��S���W
	
	// �܂������蔻��𕁒ʂɍs��
	check = IMC_POKE_TPHitSelf( poke, x, y );
	if( check == FALSE ){
		return FALSE;
	}

	// ������W�擾
	IMC_POKE_MatrixGet( poke, &cx, &cy );
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	cx -= (size_x / 2);
	cy -= (size_y / 2);

	// �I�t�Z�b�g�l���擾
	x -= cx;
	y -= cy;

	// ���̈ʒu�̃L�����N�^�f�[�^���`�F�b�N
	// �����F�łȂ������`�F�b�N
	check = IMC_DRAW_CharCheck( char_data, x, y, 0 );

	// color�i���o�[���O�Ȃ�Ԃ�
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����̐H������ł悢�T�C�Y���擾
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	ins_x		�H������ł悢�T�C�Y�擾�̈�
 *	@param	ins_y		�H������ł悢�T�C�Y�擾�̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_InSizeGet( IMC_POKE* poke, int* ins_x, int* ins_y )
{
	*ins_x = poke->ins_x;
	*ins_y = poke->ins_y;
}




//-----------------------------------------------------------------------------
/**
*	�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����L�����N�^�f�[�^���獶�[����ŏ��̓_�̑傫�������߂�
 *
 *	@param	buff	�o�b�t�@
 *
 *	@return	���[����|�P�����܂ł̃T�C�Y
 */
//-----------------------------------------------------------------------------
#define IMC_POKE_CHAR_FMT_BIT	(4)	// 1�s�N�Z���̃r�b�g��
#define IMC_POKE_CHAR_FMT_NUM	(2)	// 1byte�ɓ��鐔
static int GetInSize_SizeX( char* buff, int pokegra_x )
{
	int i, j;
	int c_idx;
	int ofs_idx;
	u8 msk;

	for( i=0; i<SOFT_SPRITE_SIZE_X; i++ ){
		
		for( j=0; j<SOFT_SPRITE_SIZE_Y; j++ ){
			c_idx = ((j * pokegra_x) + i)/IMC_POKE_CHAR_FMT_NUM;
			ofs_idx = ((j * pokegra_x) + i)%IMC_POKE_CHAR_FMT_NUM;
			msk = 0xf << (IMC_POKE_CHAR_FMT_BIT * ofs_idx);
			if( (buff[ c_idx ] & msk) != 0 ){
				return i;
			}
		}
	}
	return SOFT_SPRITE_SIZE_X;
}

static void GetInSize_Draw( char* buff )
{
	int i, j;
	int c_idx;
	int ofs_idx;
	u8 msk;

	for( i=0; i<SOFT_SPRITE_SIZE_Y; i++ ){
		
		for( j=0; j<SOFT_SPRITE_SIZE_X; j++ ){
			c_idx = ((j * SOFT_SPRITE_SIZE_X) + i)/IMC_POKE_CHAR_FMT_NUM;
			ofs_idx = ((j * SOFT_SPRITE_SIZE_X) + i)%IMC_POKE_CHAR_FMT_NUM;
			msk = 0xf << (IMC_POKE_CHAR_FMT_BIT * ofs_idx);
			OS_Printf( "%02d", (buff[ c_idx ] & msk) >> IMC_POKE_CHAR_FMT_BIT );
		}
		OS_Printf( "\n" );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�����蔻��e�[�u���Ƀf�[�^�ݒ�
 *	
 *	@param	p_tbl		�e�[�u�����[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	size_hx		�n�[�t�T�C�Y��
 *	@param	size_hy		�n�[�t�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void SetPokeHitTbl( RECT_HIT_TBL* p_tbl, int x, int y, int size_hx, int size_hy )
{
	if( (y - size_hy) >= 0 ){
		p_tbl->rect.top		= y - size_hy;
	}else{
		p_tbl->rect.top		= 0;
	}
	if( (y + size_hy) <= 191 ){
		p_tbl->rect.bottom	= y + size_hy;
	}else{
		p_tbl->rect.bottom	= 191;
	}
	if( (x - size_hx) >= 0 ){
		p_tbl->rect.left	= x - size_hx;
	}else{
		p_tbl->rect.left	=0; 
	}
	if( (x + size_hx) <= 255 ){
		p_tbl->rect.right	= x + size_hx;
	}else{
		p_tbl->rect.right	= 255;
	}
}


#ifdef PM_DEBUG
//#include "include/application/imageClip/imc_subwin.h"
#include "include/msgdata/msg_debug_tomoya.h"
void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData );

static int DEBUG_poke	 = 0;
void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData )
{
	SOFT_SPRITE_ARC		arc;
	POKEMON_PARAM*		p_pp;
	BOOL chenge = FALSE;

	// �ύX����
	if( sys.trg & PAD_BUTTON_START ){
		DEBUG_poke = (1+DEBUG_poke) % MONSNO_END;
		chenge = TRUE;
	}
	if( sys.trg & PAD_BUTTON_SELECT ){
		DEBUG_poke--;
		if( DEBUG_poke < 0 ){
			DEBUG_poke += MONSNO_END;
		}
		chenge = TRUE;
	}

	// �ύX
	if( chenge ){	
		p_pp = PokemonParam_AllocWork( heap );
		
		// �|�P�����f�[�^�쐬
		PokeParaSet( p_pp, DEBUG_poke, 10, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0 );
		IMC_POKE_Delete( poke );
		IMC_POKE_Init( poke, drawData->SSM_drawSys, p_pp, &arc, heap );

		// �����蔻��p�L�����N�^���[�N�j��
		RESM_DeleteResID( drawData->SWSP_charRes, IMC_DRAW_POKE_CHAR_ID );
		IMC_POKE_CharSet( drawData, &arc );
		sys_FreeMemoryEz( p_pp );
	}
}

#endif
