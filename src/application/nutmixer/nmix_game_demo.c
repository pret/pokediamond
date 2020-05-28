//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_demo.c
 *	@brief		�؂̎��~�L�T�[�@�������G�t�F�N�g�����Ȃǂ̏���
 *	@author		tomoya takahashi
 *	@data		2006.05.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "system/procsys.h"
#include "nutmixer_def.h"
#include "src/application/nuts_tag/ntag_gra.naix"
#include "itemtool/nuts.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "nutmixer.naix"
#include "nmix_game_snd_def.h"

#define __NMIX_GAME_DEMO_H_GLOBAL
#include "nmix_game_demo.h"

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
 *		�����ėp�I�Ȃ��̂������ɏ���
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���S�ʒu��STR���獶�[���W�����߂�
 *
 *	@param	c_x		���S��
 *	@param	str		������
 *	@param	font	�t�H���g�^�C�v
 *
 *	@return	���[���W
 */
//-----------------------------------------------------------------------------
static int NMixDemo_GetStrLeftX_CenterKey( int c_x, const STRBUF* str, FONT_TYPE font )
{
	u32 str_width;
	str_width = FontProc_GetPrintStrWidth( font, str, 0 );
	str_width /= 2;
	c_x -= str_width;
	return c_x;
}


//----------------------------------------------------------------------------
/**
 *	@brief	SWSP�@�L�����N�^���\�[�X�ǂݍ���
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR_PTR NMix_Demo_SwspCharLoad( SWSP_SYS_PTR swsp_sys, u32 data_idx, u32 heapid )
{
	SWSP_CHARDATA char_ent;
	void * buff;
	NNSG2dCharacterData* p_chardata;
	SWSP_CHAR_PTR obj;
	
	
	buff = ArcUtil_CharDataGet( 
			ARC_NUTMIXER_GRA, data_idx, FALSE,
			&p_chardata, heapid );

	// �L�����N�^�f�[�^�]��
	char_ent.s_sys		= swsp_sys;
	char_ent.res_file	= p_chardata;
	obj =SWSP_CharLoad( &char_ent );

	sys_FreeMemoryEz( buff );
	return obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	SWSP�@�p���b�g���\�[�X�ǂݍ���
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT_PTR NMix_Demo_SwspPlttLoad( SWSP_SYS_PTR swsp_sys, u32 data_idx, u32 heapid )
{
	SWSP_PLTTDATA pltt_ent;
	void * buff;
	NNSG2dPaletteData* p_plttdata;
	SWSP_PLTT_PTR obj;
	
	
	// �p���b�g�f�[�^�ǂݍ���
	buff = ArcUtil_PalDataGet( 
			ARC_NUTMIXER_GRA, data_idx,
			&p_plttdata, heapid );
	// �L�����N�^�f�[�^�]��
	pltt_ent.s_sys		= swsp_sys;
	pltt_ent.res_file	= p_plttdata;
	pltt_ent.load_num	= 1;
	obj =SWSP_PlttLoad( &pltt_ent );

	sys_FreeMemoryEz( buff );
	return obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�o�^
 *
 *	@param	swsp_sys	�\�t�g�E�F�A�X�v���C�g
 *	@param	p_char	�L�����N�^
 *	@param	p_pltt	�p���b�g
 *	@param	x		�����W
 *	@param	y		�����W	
 *	@param	pri		�D�揇��
 *
 *	@return	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ_PTR NMix_Demo_SwspObjAdd( SWSP_SYS_PTR swsp_sys, SWSP_CHAR_PTR p_char, SWSP_PLTT_PTR p_pltt, int x, int y, int pri )
{
	SWSP_ADDDATA add;
	SWSP_OBJ_PTR obj;

	add.s_sys	= swsp_sys;
	add.p_char	= p_char;
	add.p_pltt	= p_pltt;

	// �o�^�f�[�^�i�[
	add.m_x = x;
	add.m_y = y;
	add.rota = 0;
	add.alpha = 31;
	add.pri = pri;
	add.pltt_offs = 0; 

	obj = SWSP_Add( &add );

	// ��荇������\��
	SWSP_SetSpriteDraw( obj, FALSE );

	return obj;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�Z�b�g�ȂǍ쐬
 *
 *	@param	p_sys		���[�N
 *	@param	work_num	���[�N��
 *	@param	res_num		���\�[�X��
 *	@param	heapID		�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_Init( NMIXGAME_CLACT_SYS* p_sys, int work_num, int res_num, int heapID )
{
	int i;
	
	// �Z���A�N�^�[�Z�b�g�쐬
	p_sys->cas = CLACT_U_SetEasyInit( work_num, &p_sys->renddata, heapID );

	// ���\�[�X�}�l�[�W���쐬
	for( i=0; i<4; i++ ){
		p_sys->resMan[i] = CLACT_U_ResManagerInit( res_num, i, heapID );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����j��
 *
 *	@param	p_sys	�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_Delete( NMIXGAME_CLACT_SYS* p_sys )
{
	int i;
	
	CLACT_DestSet( p_sys->cas );
	p_sys->cas = NULL;
	
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerDelete( p_sys->resMan[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�P���ȃ��\�[�X�ǂݍ���
 *
 *	@param	p_sys		�Ǘ��V�X�e��
 *	@param	p_work		�f�[�^�i�[��
 *	@param	arc_file	�A�[�J�C�u�t�@�C��
 *	@param	pltt_idx	�p���b�g
 *	@param	pltt_num	�p���b�g�ǂݍ��ݐ�
 *	@param	char_idx	�L�����N�^
 *	@param	cel_idx		�Z��
 *	@param	anm_idx		�A�j��
 *	@param	cont_id		�Ǘ�ID
 *	@param	heap		�q�[�v
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResLoadEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap )
{
	BOOL result;
	
	// �L�����N�^
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			arc_file, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap, ALLOC_BOTTOM );

	// �p���b�g
	p_work->resobj[1] = CLACT_U_ResManagerResAddArcPltt_AllocType( p_sys->resMan[1],
			arc_file, pltt_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, pltt_num, heap, ALLOC_BOTTOM );
	p_work->pltt_copy = FALSE;

	// �Z��
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			arc_file, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, heap );

	// �A�j��
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			arc_file, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, heap );


	// Vram�]��
	result = CLACT_U_CharManagerSetCharModeAdjustAreaCont( p_work->resobj[0] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );
	result = CLACT_U_PlttManagerSetCleanArea( p_work->resobj[1] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[1] );

	// �w�b�_�[�쐬
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, cont_id, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief		�p���b�g�R�s�[
 *
 *	@param	p_sys		�A�N�^�[�V�X�e��
 *	@param	p_work		���[�N
 *	@param	arc_file	�A�[�J�C�u
 *	@param	pltt_obj	�p���b�g�I�u�W�F
 *	@param	char_idx	�L����
 *	@param	cel_idx		�Z��
 *	@param	anm_idx		�A�j��
 *	@param	cont_id		�Ǘ�ID
 *	@param	heap		�q�[�v
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResLoadEasy_PlttCopy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, CLACT_U_RES_OBJ_PTR pltt_obj, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap )
{
	BOOL result;
	u32 pltt_contid;
	
	// �L�����N�^
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			arc_file, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap, ALLOC_BOTTOM );

	// �p���b�g
	p_work->resobj[1] = pltt_obj;
	p_work->pltt_copy = TRUE;
	pltt_contid = CLACT_U_ResManagerGetResObjID( pltt_obj );

	// �Z��
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			arc_file, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, heap );

	// �A�j��
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			arc_file, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, heap );


	// Vram�]��
	result = CLACT_U_CharManagerSetCharModeAdjustAreaCont( p_work->resobj[0] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );

	// �w�b�_�[�쐬
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, pltt_contid, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�P�����\�[�X�j��
 *
 *	@param	p_sys	�V�X�e�����[�N
 *	@param	p_work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResDeleteEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work )
{
	int i;
	CLACT_U_CharManagerDelete( p_work->resobj[0] );

	if( p_work->pltt_copy == FALSE ){
		CLACT_U_PlttManagerDelete( p_work->resobj[1] );
	}

	// ���\�[�X���S�j��
	for( i=0; i<4; i++ ){

		if( i != 1 ){
			CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
		}else{

			// �p���b�g�̂Ƃ������R�s�[�I�u�W�F�`�F�b�N
			if( p_work->pltt_copy == FALSE ){
				CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	p_work		���\�[�X���[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	z			�����W
 *	@param	pri			�D�揇��
 *	@param	heap		�q�[�v
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR NMIXGAME_CLACT_Add( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri, int heap )
{
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;

	add.ClActSet	= p_sys->cas;
	add.ClActHeader	= &p_work->head;
	add.mat.x		= x;
	add.mat.y		= y;
	add.mat.z		= z;
	add.pri			= pri;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;

	act = CLACT_AddSimple( &add );
	GF_ASSERT( act );
	return act;
} 



//-----------------------------------------------------------------------------
/**
 *			�ėp�v�Z�V�X�e��
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���쏉����
 *
 *	@param	p_work			���샏�[�N
 *	@param	s_x				�J�nx���W
 *	@param	e_x				�I��x���W
 *	@param	count_max		�J�E���g�ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_MoveReq( NMIX_DEMO_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_MoveMain( NMIX_DEMO_MOVE_WORK* p_work )
{
	int w_x;

	// ���ݍ��W�擾
	w_x = p_work->dis_x * p_work->count;
	w_x = w_x / p_work->count_max;

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���쏉����
 *
 *	@param	p_work			���샏�[�N
 *	@param	s_x				�J�nx���W
 *	@param	e_x				�I��x���W
 *	@param	count_max		�J�E���g�ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_MoveReqFx( NMIX_DEMO_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_MoveMainFx( NMIX_DEMO_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// ���ݍ��W�擾
	w_x = FX_Mul( p_work->dis_x, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������ėp�@������
 *
 *	@param	p_work	���[�N
 *	@param	s_x		�J�n���W
 *	@param	e_x		�I�����W
 *	@param	s_s		�J�n���x
 *	@param	count_max �����l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_AddMoveReqFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max )
{
	fx32 t_x_t;	// �^�C���̂Q��
	fx32 vot;	// �����x���^�C��
	fx32 dis;
	fx32 a;

	dis = e_x - s_x;
	
	// �����l�����߂�
	// a = 2(x - vot)/(t*t)
	t_x_t = (count_max * count_max) << FX32_SHIFT;
	vot = FX_Mul( s_s, count_max * FX32_ONE );
	vot = dis - vot;
	vot = FX_Mul( vot, 2*FX32_ONE );
	a = FX_Div( vot, t_x_t );

	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->s_s = s_s;
	p_work->s_a = a;
	p_work->count = 0;
	p_work->count_max = count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_AddMoveMainFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work )
{
	fx32 dis;
	fx32 t_x_t;
	fx32 calc_work;
	fx32 vot;
	
	// �������x�^��
	// dis = vot + 1/2( a*(t*t) )
	vot = FX_Mul( p_work->s_s, p_work->count << FX32_SHIFT );
	t_x_t = (p_work->count * p_work->count) << FX32_SHIFT;
	calc_work = FX_Mul( p_work->s_a, t_x_t );
	calc_work = FX_Div( calc_work, 2*FX32_ONE );	// 1/2(a*(t*t))
	dis = vot + calc_work;	///<�ړ�����

	p_work->x = p_work->s_x + dis;


	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�x�N�g���쐬
 *	@param	x
 *	@param	y
 *	@param	z 
 *	@return	�x�N�g��
 */
//-----------------------------------------------------------------------------
VecFx32 NMIX_DEMO_MakeVec( fx32 x, fx32 y, fx32 z )
{
	VecFx32 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}






//-----------------------------------------------------------------------------
/**
 *					�؂̎��Ȃׂɓ�������
*/
//-----------------------------------------------------------------------------

#define NMIX_DEMO_NUTS_IN_RESMAN_ID	( 1000 )
// �I�u�W�F�N�g�V�[�P���X
enum{
	NMIX_DEMO_NUTSIN_OBJ_SEQ_WAIT,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_POCHAN,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_END,
};

// �؂̎������e�[�u��
typedef struct{
	fx32 eff_ssx;	// �����x��
	fx32 eff_ssy;	// �����x��
	s16 eff_sx;		// �J�n�����W 
	s16 eff_ex;		// �I�������W
	
	s16 eff_sy;		// �J�n�����W
	s16 eff_ey;		// �I�������W
	u8 eff_count_max;	// �J�E���g�l
	u8 wait;		// ���˃E�G�C�g
} NMIX_DEMO_NUTS_IN_PARAM;

static const NMIX_DEMO_NUTS_IN_PARAM NMIX_DEMO_NutsInMoveParam[ NUTMIXER_MEMBER_MAX ] = {
	{
		FX32_CONST( 0 ),	// �����x��
		FX32_CONST( 0 ),	// �����x��
		64,		// �J�n�����W 
		96,		// �I�������W
		-32,	// �J�n�����W
		88,		// �I�������W
		32,	// �J�E���g�l
		10,	// ���˃E�G�C�g
	},
	{
		FX32_CONST( 0 ),	// �����x��
		FX32_CONST( 0 ),	// �����x��
		280,	// �J�n�����W 
		156,	// �I�������W
		192,	// �J�n�����W
		128,	// �I�������W
		32,	// �J�E���g�l
		32,	// ���˃E�G�C�g
	},
	{
		FX32_CONST( 0 ),	// �����x��
		FX32_CONST( 0 ),	// �����x��
		-32,	// �J�n�����W 
		128,	// �I�������W
		32,		// �J�n�����W
		96,		// �I�������W
		32,	// �J�E���g�l
		32,	// ���˃E�G�C�g
	},
	{
		FX32_CONST( 0 ),	// �����x��
		FX32_CONST( 0 ),	// �����x��
		128,	// �J�n�����W 
		116,	// �I�������W
		-32,	// �J�n�����W
		96,		// �I�������W
		32,	// �J�E���g�l
		32,	// ���˃E�G�C�g
	},
};

// �؂̎��O���t�B�b�N�f�[�^IDX�擾�}�N��
#define	NMIXGAMEDEMO_NUTSIN_PL_GET(x)		( NARC_ntag_gra_kinomi_001_NCLR + ((x)-NUTS_START_ITEMNUM) )
#define	NMIXGAMEDEMO_NUTSIN_CH_GET(x)		( NARC_ntag_gra_kinomi_001_NCGR + ((x)-NUTS_START_ITEMNUM) )

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�̏�����
 *
 *	@param	p_work		���[�N
 *	@param	nuts_num	�؂̎���
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Init( NMIX_DEMO_NUTS_IN* p_work, int nuts_num )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_NUTS_IN) );
	p_work->nuts_num = nuts_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�̔j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Delete( NMIX_DEMO_NUTS_IN* p_work )
{
	// ���\�[�X�j�����Ă��܂���B
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_NUTS_IN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�t�@�C���ǂݍ���
 *
 *	@param	p_work					���[�N
 *	@param	p_get_ko_before_data	�Q�[���J�n�O�ʐM�f�[�^
 *	@param	p_clact					�A�N�^�[�V�X�e��
 *	@param	p_def_oam_res			�f�t�H���gOAM���\�[�X
 *	@param	heapID					�q�[�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_GraphicLoad( NMIX_DEMO_NUTS_IN* p_work, NUTMIX_COMM_BEFORE_KO* p_get_ko_before_data, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	int load_num;
	
	// �ʐM����̖؂̎��f�[�^��ǂݍ���	���g�̓A�C�e���i���o�[
	load_num = 0;
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		
		// 0�ȊO�Ȃ�؂̎��f�[�^
		if( p_get_ko_before_data->before[i].nut_type != 0 ){
			
//			OS_Printf( "���̂� %d cont_id %d\n", p_get_ko_before_data->before[i].nut_type, NMIX_DEMO_NUTS_IN_RESMAN_ID + i );
			
			// �ǂݍ��ݏ���
			NMIXGAME_CLACT_ResLoadEasy( p_clact, 
					&p_work->res_work[ load_num ], ARC_NTAG_GRA,
					NMIXGAMEDEMO_NUTSIN_PL_GET( p_get_ko_before_data->before[i].nut_type ), 1,
					NMIXGAMEDEMO_NUTSIN_CH_GET( p_get_ko_before_data->before[i].nut_type ),
					NARC_ntag_gra_kinomi_001_NCER, NARC_ntag_gra_kinomi_001_NANR,
					NMIX_DEMO_NUTS_IN_RESMAN_ID + i, heapID );

			// �A�N�^�[�̍쐬����
			p_work->clact[ load_num ] = NMIXGAME_CLACT_Add( p_clact,
					&p_work->res_work[ load_num ] ,0,0,0,0, heapID );
			CLACT_SetDrawFlag( p_work->clact[ load_num ], FALSE );
			// ���Ƀ|�`�������g��
			p_work->pochan[ load_num ] = NMIXGAME_CLACT_Add( p_clact,
					&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_START ], 
					0,0,0,0, heapID );
			CLACT_SetDrawFlag( p_work->pochan[ load_num ], FALSE );
			CLACT_AnmChg( p_work->pochan[ load_num ], 1 );
			load_num ++;
		}

		// �S���ǂݍ��񂾂��`�F�b�N
		if( p_work->nuts_num == load_num ){
//			OS_Printf( "load_num %d i[%d] \n", load_num, i );
			break;
		}
	}

	p_work->res_load = TRUE;
} 

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�j��
 *
 *	@param	p_work	���[�N
 *	@param	p_clact	�Z���A�N�^�[�V�X�e��
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_GraphicRelease( NMIX_DEMO_NUTS_IN* p_work, NMIXGAME_CLACT_SYS* p_clact )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<p_work->nuts_num; i++ ){
		CLACT_Delete( p_work->clact[i] );
		CLACT_Delete( p_work->pochan[i] );
		NMIXGAME_CLACT_ResDeleteEasy( p_clact, &p_work->res_work[i] );
	}
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�؂̎������G�t�F�N�g�J�n
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Start( NMIX_DEMO_NUTS_IN* p_work )
{
	int i;
	VecFx32 matrix;
	
	GF_ASSERT( p_work->move_flg == FALSE );

	for( i=0; i<p_work->nuts_num; i++ ){
		// �����p�����[�^������
		NMIX_DEMO_AddMoveReqFx( &p_work->move_x[i], 
				NMIX_DEMO_NutsInMoveParam[i].eff_sx * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ex * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ssx,
				NMIX_DEMO_NutsInMoveParam[i].eff_count_max );	

		NMIX_DEMO_AddMoveReqFx( &p_work->move_y[i], 
				NMIX_DEMO_NutsInMoveParam[i].eff_sy * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ey * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ssy,
				NMIX_DEMO_NutsInMoveParam[ i].eff_count_max );	

		// �A�N�^�[�ɍ��W�ݒ�
		matrix = NMIX_DEMO_MakeVec( p_work->move_x[i].x,
				p_work->move_y[i].x, 0 );
		CLACT_SetMatrix( p_work->clact[i], &matrix );

		p_work->obj_seq[i] = 0;
		p_work->obj_wait[i] = NMIX_DEMO_NutsInMoveParam[i].wait;
	}

	// ���ˑ���������
	p_work->start_count = 0;
	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�؂̎������G�t�F�N�g���C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	NMIX_DEMO_NUTS_RET_FALSE,	// �r��
 * 	@retval	NMIX_DEMO_NUTS_RET_TRUE,	// �I��
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_00,	// 0����
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_01,	// 1����
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_02,	// 2����
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_03,	// 3����
 */
//-----------------------------------------------------------------------------
u32 NMixGameDemo_NutsIn_Main( NMIX_DEMO_NUTS_IN* p_work )
{
	int i;
	BOOL result;
	VecFx32	matrix;
	u32 ret = NMIX_DEMO_NUTS_RET_FALSE;

	if( p_work->move_flg == FALSE ){
		return NMIX_DEMO_NUTS_RET_TRUE;
	}

	// ���˕���
	if( p_work->start_count < p_work->nuts_num ){

		p_work->obj_wait[ p_work->start_count ]--;
		if( p_work->obj_wait[ p_work->start_count ] <= 0 ){
			// ����
			p_work->obj_seq[ p_work->start_count ] = NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE;
			CLACT_SetDrawFlag( p_work->clact[p_work->start_count], TRUE );

			// �߂�l
			ret = NMIX_DEMO_NUTS_RET_NUTS_00 + p_work->start_count;
			p_work->start_count ++;
		}
	}
	
	// ��������
	for( i=0; i<p_work->nuts_num; i++ ){
		switch( p_work->obj_seq[ i ] ){
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_WAIT:
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE:
			result = NMIX_DEMO_AddMoveMainFx( &p_work->move_x[i] );	
			NMIX_DEMO_AddMoveMainFx( &p_work->move_y[i] );

			matrix = NMIX_DEMO_MakeVec( p_work->move_x[i].x,
					p_work->move_y[i].x, 0 );
			CLACT_SetMatrix( p_work->clact[i], &matrix );
			if( result == TRUE ){
				CLACT_SetMatrix( p_work->pochan[i], &matrix );
				CLACT_SetDrawFlag( p_work->pochan[i], TRUE );
				CLACT_SetAnmFlag( p_work->pochan[i], TRUE );
				CLACT_SetDrawFlag( p_work->clact[i], FALSE );

				// �|�`�������J�n
				Snd_SePlay( NMIXGAME_SE_NUTS_SOOP_IN );
				
				p_work->obj_seq[ i ]++;
			}
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_POCHAN:
			// �A�j���I���҂�
			if( CLACT_AnmActiveCheck( p_work->pochan[i] ) == FALSE ){
				CLACT_SetDrawFlag( p_work->pochan[i], FALSE );
				p_work->obj_seq[i]++;
			}
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_END:
			break;

		default:
			GF_ASSERT( 0 );
			break;
		}
	}

	// �I���`�F�b�N
	if( p_work->obj_seq[ p_work->nuts_num - 1 ] == NMIX_DEMO_NUTSIN_OBJ_SEQ_END ){
		p_work->move_flg = FALSE;
		return NMIX_DEMO_NUTS_RET_TRUE;
	}
	return ret;
}




//-----------------------------------------------------------------------------
/**
 *		���ʐ���
 */
//-----------------------------------------------------------------------------
#define NMIX_SUBWIN_FONTBMP_X	( 4 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_FONTBMP_Y	( 19 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_FONTBMP_CX	( 23 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_FONTBMP_CY	( 4 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_FONT_COLOR		( 0 )		// �g�p�J���[�p���b�g
#define NMIX_SUBWIN_FONT_CG_OFS		( 1 )
#define NMIX_SUBWIN_FONT_STR_COLOR	( 1 )		// �t�H���g�p�J���[�p���b�g
#define NMIX_SUBWIN_FONTBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define NMIX_SUBWIN_BACK_COLOR		( 2 )	// �w�i�J���[�p���b�g
#define NMIX_SUBWIN_BACK_COLOR_NUM	( 2 )	// �w�i�J���[�p���b�g�g�p��

#define NMIX_SUBWIN_PLNAME_FONTBMP_X	( 6 )		// �����ʃr�b�g�}�b�v�ʒu
#define NMIX_SUBWIN_PLNAME_FONTBMP_Y	( 13 )		// �����ʃr�b�g�}�b�v�ʒu
#define NMIX_SUBWIN_PLNAME_FONTBMP_CX	( 20 )		// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_PLNAME_FONTBMP_CY	( 8 )		// �����ʃr�b�g�}�b�vsize
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX	( 5 )	// �g�@�\���J�n��
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY	( 13 )	// �g�@�\���J�n��
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COX	( 12 )	// �g�@�\���@�I�t�Z�b�g
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COY	( 5 )	// �g�@�\���@�I�t�Z�b�g
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_CX		( 10 )		// �g�@�T�C�Y
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_CY		( 4 )		// �g�@�T�C�Y
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM	( 2 )
#define NMIX_SUBWIN_BACK_PLNAME_FONT_OFSX	( 32 )	// �����̘g���ォ�璆�S�܂ł̃I�t�Z�b�g
#define NMIX_SUBWIN_BACK_PLNAME_FONT_OFSY	( 8 )	// �����̘g���ォ�璆�S�܂ł̃I�t�Z�b�g


static void NMixSubWin_BmpInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID );
static void NMixSubWin_BmpRelease( NMIX_DEMO_SUB_WIN* p_work );
static void NMixSubWin_BackGroundInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID );
static void NMixSubWin_BackGroundRelease( NMIX_DEMO_SUB_WIN* p_work );
static void NmixSubWIn_BmpTextSet( GF_BGL_BMPWIN* p_bmp, STRBUF* str, int x, int y );



//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʐ��䃏�[�N�̏�����
 *
 *	@param	p_work				���[�N
 *	@param	pp_trainer_name		�g���[�i�[���z��ւ̃|�C���^
 *	@param	comm_count			�ʐM���萔
 *	@param	p_msg_data			���b�Z�[�W�f�[�^
 *	@param	p_comm_data			�ʐM�f�[�^
 *	@param	wnd_type			�E�B���h�E�^�C�v
 *	@param	heapID				�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_Init( NMIX_DEMO_SUB_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_SUB_WIN) );
	p_work->p_msg_data = p_msg_data;
	p_work->comm_count = comm_count;
	p_work->heapID = heapID;
	p_work->p_comm_data = p_comm_data;
	p_work->wnd_type = wnd_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�f�[�^�j��
 *	
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_Delete( NMIX_DEMO_SUB_WIN* p_work )
{
	// ���\�[�X�j�����Ă��܂���
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_SUB_WIN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	3D���\�[�X�ǂݍ��ݏ���
 *
 *	@param	p_work		���[�N
 *	@param	p_bgl		BGL
 *	@param	heapID		�q�[�vID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_GraphicLoad( NMIX_DEMO_SUB_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID )
{
	GF_ASSERT( p_work->res_load == FALSE );

	// BGL�ݒ�
	p_work->p_bgl = p_bgl;
	
	// �r�b�g�}�b�v�E�B���h�E������
	NMixSubWin_BmpInit( p_work, heapID );

	// �w�i�ݒ�
	NMixSubWin_BackGroundInit( p_work, heapID );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_GraphicRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	
	// �r�b�g�}�b�v�E�B���h�E�j��
	NMixSubWin_BmpRelease( p_work );

	// �w�i�j��
	NMixSubWin_BackGroundRelease( p_work );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�E�t���e�L�X�g�o�^
 *
 *	@param	p_work	���[�N
 *	@param	msgidx	�\�����郁�b�Z�[�W
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinNutsOn( NMIX_DEMO_SUB_WIN* p_work, int nuts_id )
{
	// �؂̎�������쐬
	WORDSET_RegisterItemName( p_work->p_msg_data->wset, 0, nuts_id );
	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->nuts_in );
	
	// �r�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	NmixSubWIn_BmpTextSet( p_work->p_bmp, p_work->p_msg_data->tmp, 0, 0 );
	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_ON, NMIX_SUBWIN_FONT_CG_OFS, NMIX_SUBWIN_FONT_COLOR );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�ʕ\��OFF
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinNutsOff( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_BGL_BmpWinOff( p_work->p_bmp );
	// ���b�Z�[�W�X�N���[�����N���[��
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME0_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̂܂܁@���҂����������`��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinWaitMsgOn( NMIX_DEMO_SUB_WIN* p_work )
{
	// �r�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	NmixSubWIn_BmpTextSet( p_work->p_bmp, p_work->p_msg_data->wait, 0, 0 );
	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_ON, NMIX_SUBWIN_FONT_CG_OFS, NMIX_SUBWIN_FONT_COLOR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�e�v���C���[�̖��O�ݒ�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_PlayerNameOn( NMIX_DEMO_SUB_WIN* p_work )
{
	int i;
	int x;
	int y;
	int x_draw;
	int y_draw;
	int netid;
	int name_draw_x, name_draw_y;

	// 1�l�v���C�̂Ƃ��́A�o���Ȃ�
	if( p_work->comm_count == 1 ){
		return ;
	}
	
	// �w�i�X�N���[���f�[�^�ɘg������
	for( i=0; i<p_work->comm_count; i++ ){

		x = i % NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM;
		y = (i / NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM);

		x_draw = x * NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COX;
		y_draw = y * NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COY;
		x *= NMIX_SUBWIN_BACK_PLNAME_WAKU_CX;
		y *= NMIX_SUBWIN_BACK_PLNAME_WAKU_CY;

		// �X�N���[���f�[�^��������
		GF_BGL_ScrWriteExpand( p_work->p_bgl, GF_BGL_FRAME1_S,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX + x_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY + y_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY,
				p_work->p_playername_scrn->rawData, 
				x, y,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX * 2,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY * 2 );

		// �p���b�g�����킹��
		GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_S,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX + x_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY + y_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY,
				NMIX_SUBWIN_BACK_COLOR );


		// BMP�ɖ��O������
		netid = p_work->p_comm_data->playno_netid[ i ];
		WORDSET_RegisterPlayerName( p_work->p_msg_data->wset, 0, p_work->p_comm_data->p_mystate[netid] );
		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->tr_name );


		name_draw_x = NMixDemo_GetStrLeftX_CenterKey( (x_draw*8) + NMIX_SUBWIN_BACK_PLNAME_FONT_OFSX, p_work->p_msg_data->tmp, FONT_TALK );	// ���[���W�����߂�
		name_draw_y = (y_draw*8) + NMIX_SUBWIN_BACK_PLNAME_FONT_OFSY;
		NmixSubWIn_BmpTextSet( p_work->p_bmp_plname, p_work->p_msg_data->tmp, 
				name_draw_x, name_draw_y );
	}

	GF_BGL_BmpWinOnVReq( p_work->p_bmp_plname );
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_S );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E������
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BmpInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID )
{
	// �w�i�̐ݒ�ƃr�b�g�}�b�v�E�B���h�E�ݒ�
	p_work->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );
	p_work->p_bmp_plname = GF_BGL_BmpWinAllocGet( heapID, 1 );
	
	// �r�b�g�}�b�v�E�B���h�E�o�^
	GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp,
			GF_BGL_FRAME0_S, 
			NMIX_SUBWIN_FONTBMP_X,
			NMIX_SUBWIN_FONTBMP_Y,
			NMIX_SUBWIN_FONTBMP_CX, 
			NMIX_SUBWIN_FONTBMP_CY, 
			NMIX_SUBWIN_FONT_STR_COLOR,
			TALK_WIN_CGX_SIZ + 1 );

	// �r�b�g�}�b�v�E�B���h�E�o�^
	GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp_plname,
			GF_BGL_FRAME0_S, 
			NMIX_SUBWIN_PLNAME_FONTBMP_X,
			NMIX_SUBWIN_PLNAME_FONTBMP_Y,
			NMIX_SUBWIN_PLNAME_FONTBMP_CX, 
			NMIX_SUBWIN_PLNAME_FONTBMP_CY, 
			NMIX_SUBWIN_FONT_STR_COLOR,
			TALK_WIN_CGX_SIZ + 1 );

	// �N���[��
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	GF_BGL_BmpWinDataFill( p_work->p_bmp_plname, 0 );

	// �g��`��
	TalkWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME0_S,
			NMIX_SUBWIN_FONT_CG_OFS,
			NMIX_SUBWIN_FONT_COLOR,
			p_work->wnd_type, heapID );

	// ��b�t�H���g�p���b�g�ǂݍ���
	TalkFontPaletteLoad( PALTYPE_SUB_BG, 
			NMIX_SUBWIN_FONT_STR_COLOR * 32, heapID );

	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_OFF,
			NMIX_SUBWIN_FONT_CG_OFS,
			NMIX_SUBWIN_FONT_COLOR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�j��
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BmpRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_BGL_BmpWinDel( p_work->p_bmp );
	GF_BGL_BmpWinFree( p_work->p_bmp, 1 );
	GF_BGL_BmpWinDel( p_work->p_bmp_plname );
	GF_BGL_BmpWinFree( p_work->p_bmp_plname, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief		�w�i������
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BackGroundInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID )
{
	int scrn_idx;
	
	// �x�[�X�w�i
	ArcUtil_PalSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_m_NCLR, 
			PALTYPE_SUB_BG, NMIX_SUBWIN_BACK_COLOR*32,
			NMIX_SUBWIN_BACK_COLOR_NUM*32, heapID );
	ArcUtil_BgCharSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_m_NCGR,
			p_work->p_bgl, GF_BGL_FRAME1_S, 0, 0, FALSE, heapID );

	// �X�N���[���f�[�^�ǂݍ���
	if( p_work->comm_count == 1 ){
		scrn_idx = NARC_nutmixer_cook_m1_NSCR;
	}else{
		scrn_idx = NARC_nutmixer_cook_m2_NSCR;
	}
	p_work->p_bg_scrn_buf = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			scrn_idx, FALSE, &p_work->p_bg_scrn, heapID );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_work->p_bgl, GF_BGL_FRAME1_S,
			p_work->p_bg_scrn->rawData, 0, 0,
			p_work->p_bg_scrn->screenWidth / 8,
			p_work->p_bg_scrn->screenHeight / 8 );

	// �p���b�g�����킹��
	GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_S,
			0, 0, 
			p_work->p_bg_scrn->screenWidth / 8,
			p_work->p_bg_scrn->screenHeight / 8,
			NMIX_SUBWIN_BACK_COLOR+1 );


	// �v���C���[���w�i��ǂݍ���
	p_work->p_playername_scrn_buf = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			NARC_nutmixer_cook_m2a_NSCR, FALSE, 
			&p_work->p_playername_scrn, heapID );
	
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief		�w�i�j��
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BackGroundRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	sys_FreeMemoryEz( p_work->p_bg_scrn_buf );
	sys_FreeMemoryEz( p_work->p_playername_scrn_buf );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�Ƀe�L�X�g�ݒ�
 *
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	str			������
 *	@param	x			�����W
 *	@param	y			�����W
 */
//-----------------------------------------------------------------------------
static void NmixSubWIn_BmpTextSet( GF_BGL_BMPWIN* p_bmp, STRBUF* str, int x, int y )
{
	// �����񏑂�����
	GF_STR_PrintColor( p_bmp, FONT_TALK, str, x, y, 0, NMIX_SUBWIN_FONTBMP_PRICOLOR, NULL );
}





//-----------------------------------------------------------------------------
/**
 *		�J�E���g�_�E��
 */
//-----------------------------------------------------------------------------

#define NMIX_GAMEDEMO_COUNTDOWN_X	( 128*FX32_ONE )
#define NMIX_GAMEDEMO_COUNTDOWN_Y	( 96*FX32_ONE )

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E�����[�N������
 *
 *	@param	p_work		���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Init( NMIX_DEMO_COUNTDOWN* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_COUNTDOWN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E�����[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Delete( NMIX_DEMO_COUNTDOWN* p_work )
{
	// ���\�[�X�j�����Ă��܂���
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_COUNTDOWN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E�����\�[�X�ǂݍ���
 *
 *	@param	p_work			���[�N
 *	@param	p_clact			�Z���A�N�^�[
 *	@param	p_def_oam_res	�f�t�H���gOAM���\�[�X
 *	@param	heapID			�q�[�vID 
 *	@param	res_no			���\�[�X�i���o�[
 *	@param	anm_idx			�A�j���C���f�b�N�X
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_GraphicLoad( NMIX_DEMO_COUNTDOWN* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID, u32 res_no, u32 anm_idx )
{
	// ���Ƀ|�`�������g��
	p_work->clact = NMIXGAME_CLACT_Add( p_clact,
			&p_def_oam_res[ res_no ], 
			NMIX_GAMEDEMO_COUNTDOWN_X, NMIX_GAMEDEMO_COUNTDOWN_Y,
			0, 0, heapID );
	CLACT_SetDrawFlag( p_work->clact, FALSE );
	CLACT_AnmChg( p_work->clact, anm_idx );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E�����\�[�X�j��
 *	
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_GraphicRelease( NMIX_DEMO_COUNTDOWN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	CLACT_Delete( p_work->clact );
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E���J�n
 *
 *	@param	p_work ���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Start( NMIX_DEMO_COUNTDOWN* p_work )
{
	CLACT_SetDrawFlag( p_work->clact, TRUE );
	CLACT_SetAnmFlag( p_work->clact, TRUE );
}
void NMixGameDemo_CountDown_Start_Pen( NMIX_DEMO_COUNTDOWN* p_work )
{
	VecFx32 matrix;
	
	CLACT_SetDrawFlag( p_work->clact, TRUE );
	CLACT_SetAnmFlag( p_work->clact, TRUE );

	matrix.x = 168 * FX32_ONE;
	matrix.y = 60 * FX32_ONE;

	CLACT_SetMatrix( p_work->clact, &matrix );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���g�_�E�����C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_CountDown_Main( NMIX_DEMO_COUNTDOWN* p_work )
{
	if( CLACT_AnmActiveCheck( p_work->clact ) == FALSE ){
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *		��O���t�B�b�N�`��Ǘ��V�X�e��
 */
//-----------------------------------------------------------------------------
// ���A�j��
static const u8 FireAnmSync[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	4,
	3,
	2
};
static const fx32 FireScaleMin[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	FX32_CONST(0.98f),
	FX32_CONST(0.95f),
	FX32_CONST(0.92f),
};
static const fx32 FireScaleMax[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	FX32_CONST(1.0f),
	FX32_CONST(1.0f),
	FX32_CONST(1.0f),
};


//----------------------------------------------------------------------------
/**
 *	@brief	���[�N��������
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_Init( NMIX_DEMO_NABE_GRA* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_NABE_GRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j��
 *
 *	@param	p_work 
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_Delete( NMIX_DEMO_NABE_GRA* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_NABE_GRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_work		���[�N
 *	@param	wsp_sys		�\�t�g�E�F�A�X�v���C�g�V�X�e��
 *	@param	heapID		�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicLoad( NMIX_DEMO_NABE_GRA* p_work, SWSP_SYS_PTR	swsp_sys, u32 heapID )
{
	int i;
	static const u8 NabeCharTbl[] = {
		NARC_nutmixer_cook_s_fire_NCBR,
		NARC_nutmixer_cook_s_nabe1_NCBR,
		NARC_nutmixer_cook_s_nabe2_NCBR,
		NARC_nutmixer_cook_s_soop1_NCBR,
		NARC_nutmixer_cook_s_soop2_NCBR,
		NARC_nutmixer_cook_s_soop3_NCBR,
	};
	static const u8 NabePlttTbl[] = {
		NARC_nutmixer_cook_s_fire1_NCLR,
		NARC_nutmixer_cook_s_fire2_NCLR,
		NARC_nutmixer_cook_s_fire3_NCLR,
		NARC_nutmixer_cook_s_nabe1_NCLR,
		NARC_nutmixer_cook_s_nabe2_NCLR,
		NARC_nutmixer_cook_s_soop1_NCLR,
		NARC_nutmixer_cook_s_soop2_NCLR,
		NARC_nutmixer_cook_s_soop3_NCLR,
	};
	static const u8 NabeObjCharTbl[] = {
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_NABE_UP,
		NMIX_DEMO_NABE_CHAR_NABE_DOWN,
		NMIX_DEMO_NABE_CHAR_SOOP_0,
		NMIX_DEMO_NABE_CHAR_SOOP_1,
		NMIX_DEMO_NABE_CHAR_SOOP_2,
	};
	static const u8 NabeObjPriTbl[] = {
		3,
		2,
		1,
		7,
		0,
		6,
		5,
		4,
	};
	static const u8 NabeObjMatX[] = {
		0,
		0,
		0,
		0,
		0,
		64,
		64,
		64,
	};
	static const u8 NabeObjMatY[] = {
		0,
		0,
		0,
		0,
		0,
		32,
		32,
		32,
	};
	
	GF_ASSERT( p_work->res_load == FALSE );
	// �L�����N�^�f�[�^�ǂݍ���
	for( i=0; i<NMIX_DEMO_NABE_CHAR_NUM; i++ ){
		p_work->swsp_char[ i ] = NMix_Demo_SwspCharLoad( swsp_sys, NabeCharTbl[i], heapID );
	}
	// �p���b�g�f�[�^�ǂݍ���
	for( i=0; i<NMIX_DEMO_NABE_PLTT_NUM; i++ ){
		p_work->swsp_pltt[ i ] = NMix_Demo_SwspPlttLoad( swsp_sys, NabePlttTbl[i], heapID );
	}

	// �I�u�W�F�N�g�o�^
	for( i=0; i<NMIX_DEMO_NABE_OBJ_NUM; i++ ){
		p_work->swsp_obj[ i ] = NMix_Demo_SwspObjAdd( swsp_sys,
				p_work->swsp_char[ NabeObjCharTbl[ i ] ],
				p_work->swsp_pltt[ i ],
				NabeObjMatX[i], NabeObjMatY[i],
				NabeObjPriTbl[ i ] );
		// ���S���W
		SWSP_SetSpriteCenterPos( p_work->swsp_obj[ i ], 128 - NabeObjMatX[i], 96 - NabeObjMatY[i] );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicRelease( NMIX_DEMO_NABE_GRA* p_work )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<NMIX_DEMO_NABE_OBJ_NUM; i++ ){
		// �I�u�W�F�N�g�j��
		SWSP_Delete( p_work->swsp_obj[ i ] );
	}
	
	// Vram����j��
	for( i=0; i<NMIX_DEMO_NABE_CHAR_NUM; i++ ){
		SWSP_CharDelete( p_work->swsp_char[ i ] );
	}
	for( i=0; i<NMIX_DEMO_NABE_PLTT_NUM; i++ ){
		SWSP_PlttDelete( p_work->swsp_pltt[ i ] );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�\��ONOFF
 *
 *	@param	p_work	���[�N
 *	@param	obj_id	�I�u�W�F�N�gID
 *	@param	flg		�t���O
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, BOOL flg )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	SWSP_SetSpriteDraw( p_work->swsp_obj[ obj_id ], flg );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�\��ONOFF	�擾
 *
 *	@param	p_work		���[�N
 *	@param	obj_id		�I�u�W�F�N�gID
 *
 *	@retval	TRUE	�\��
 *	@retval	FALSE	��\��
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_NabeGra_GraphicGetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	return SWSP_GetSpriteDraw( p_work->swsp_obj[ obj_id ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v��]�p�x�̐ݒ�
 *
 *	@param	p_work		���[�N
 *	@param	rota		��]�p�x
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetSoopRota( NMIX_DEMO_NABE_GRA* p_work, u16 rota )
{
	int i;
	
	// �X�[�v�n�S�Ă�OBJ�ɐݒ�
	for( i=NMIX_DEMO_NABE_OBJ_SOOP_0; i<=NMIX_DEMO_NABE_OBJ_SOOP_2; i++ ){
		SWSP_SetSpriteRotZ( p_work->swsp_obj[ i ], rota );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�@�g�嗦�ݒ�
 *
 *	@param	p_work		���[�N
 *	@param	scale		�g�嗦
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetSoopScale( NMIX_DEMO_NABE_GRA* p_work, fx32 scale )
{
	int i;
	// �X�[�v�n�S�Ă�OBJ�ɐݒ�
	for( i=NMIX_DEMO_NABE_OBJ_SOOP_0; i<=NMIX_DEMO_NABE_OBJ_SOOP_2; i++ ){
		SWSP_SetSpriteScale( p_work->swsp_obj[ i ], scale, scale );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��O���ӂ������l�ݒ�
 *
 *	@param	p_work	���[�N
 *	@param	obj_id	�I�u�W�F�N�gID
 *	@param	alpha	���l
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetAlpha( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, u32 alpha )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	SWSP_SetSpriteAlpha( p_work->swsp_obj[ obj_id ], alpha );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�@�C���[�A�j���@�J�n
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_FireAnmStart( NMIX_DEMO_NABE_GRA* p_work )
{
	p_work->fire_anm_seq = 1;
	p_work->way_switch = 0;

	// �������l�ɂ���	
	NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
			FX32_ONE,
			FireScaleMin[ 0 ],
			FireAnmSync[ 0 ] );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�@�C���[�A�j���@���C��
 *	
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------	
void NMixGameDemo_NabeGra_FireAnm( NMIX_DEMO_NABE_GRA* p_work, int soop_type )
{
	BOOL result;
	int i;
	switch( p_work->fire_anm_seq ){
	case 0:
		// �p�����[�^������
		if( p_work->way_switch == 0 ){
			// �傫���Ȃ�
			NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
					FireScaleMin[ soop_type ],
					FireScaleMax[ soop_type ],
					FireAnmSync[ soop_type ] );
		}else{
			// �������Ȃ�
			NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
					FireScaleMax[ soop_type ],
					FireScaleMin[ soop_type ],
					FireAnmSync[ soop_type ] );
		}
		p_work->fire_anm_seq++;

	case 1:
		// �P�񓮂���
		result = NMIX_DEMO_MoveMainFx( &p_work->fire_anm );
		// �ΑS�Ă�OBJ�ɐݒ�
		for( i=NMIX_DEMO_NABE_OBJ_FIRE_0; i<=NMIX_DEMO_NABE_OBJ_FIRE_2; i++ ){
			SWSP_SetSpriteScale( p_work->swsp_obj[ i ], p_work->fire_anm.x, p_work->fire_anm.x );
		}
		if( result == TRUE ){
			p_work->fire_anm_seq = 0;
		}
		break;

	default:
		GF_ASSERT( 0 );
		break;
	}
}





//-----------------------------------------------------------------------------
/**
 *		���̐l�̈ʒu�@�`��@�Ǘ��V�X�e��
 */
//-----------------------------------------------------------------------------
#define NMIX_DEMO_OTHER_MARK_BG_PRI	( 2 )
//----------------------------------------------------------------------------
/**
 *	@brief	���[�N������
 *	@param	p_work 
 *	@param	cp_commdata		�ʐM�f�[�^
 *	@param	comm_count		�ʐM�l��
 *	@param	p_comm_work		�ʐM���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Init( NMIX_DEMO_OTHER_MARK* p_work, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, NUTMIX_COMMPACK_WORK* p_comm_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_OTHER_MARK) );
	p_work->cp_commdata = cp_commdata;
	p_work->comm_count = comm_count;
	p_work->p_comm_work	= p_comm_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j��
 *	
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Delete( NMIX_DEMO_OTHER_MARK* p_work )	
{
	// ���\�[�X�j�����Ă��Ȃ�
	GF_ASSERT( p_work->res_load == FALSE );

	memset( p_work, 0, sizeof(NMIX_DEMO_OTHER_MARK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�ǂݍ���
 *
 *	@param	p_work			���[�N
 *	@param	p_clact			�A�N�^�[�V�X�e��
 *	@param	p_def_oam_res	��{���\�[�X
 *	@param	heapID			�q�[�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_GraphicLoad( NMIX_DEMO_OTHER_MARK* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	VecFx32 mat;
	
	mat.x = 128 * FX32_ONE;
	mat.y = 96 * FX32_ONE;
	
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_work->clact[i] = NMIXGAME_CLACT_Add( p_clact,
				&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_COMMON ], 
				128, 96,
				0, NMIX_DEMO_OTHER_MARK_BG_PRI, heapID );
		CLACT_SetDrawFlag( p_work->clact[i], FALSE );
		CLACT_AnmChg( p_work->clact[i], 4 + i );
		CLACT_SetMatrix( p_work->clact[i], &mat );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N���\�[�X�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_GraphicRelease( NMIX_DEMO_OTHER_MARK* p_work )
{
	int i;

	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		CLACT_Delete( p_work->clact[i] );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	MARK�ʒu����
 *
 *	@param	p_work			���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Main( NMIX_DEMO_OTHER_MARK* p_work )
{
	int i;
	int net_id;
	VecFx32 matrix;
	const NUTMIX_OYA* p_oya = &p_work->cp_commdata->get_game_data[ COMM_PARENT_ID ].oya;
	
	//	�Ή�����ʒu�ɐݒu
	for( i=0; i<p_work->comm_count; i++ ){
		net_id = p_work->cp_commdata->playno_netid[ i ];
		matrix.x = p_oya->x[ net_id ] * FX32_ONE;
		matrix.y = p_oya->y[ net_id ] * FX32_ONE;
		CLACT_SetMatrix( p_work->clact[i], &matrix );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	p_work
 *	@param	flg 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_DrawFlag( NMIX_DEMO_OTHER_MARK* p_work, BOOL flg )
{
	int i;
	int net_id;
	
	// ������ID�ȊO��netid �\��ON
	for( i=0; i<p_work->comm_count; i++ ){
		net_id = p_work->cp_commdata->playno_netid[ i ];
		if( NMIX_CommPack_CommGetCurrentID( p_work->p_comm_work ) != net_id ){
			CLACT_SetDrawFlag( p_work->clact[ i ], flg );
		}
	}
}



//-----------------------------------------------------------------------------
/**
 *		���C����ʁ@�r�b�g�}�b�v�E�B���h�E
 */
//-----------------------------------------------------------------------------

#define NMIX_MAINWIN_FONT_COLOR		( 0 )		// �g�p�J���[�p���b�g
#define NMIX_MAINWIN_MENUFONT_COLOR		( 1 )		// �g�p�J���[�p���b�g
#define NMIX_MAINWIN_FONT_CG_OFS	( 1 )
#define NMIX_MAINWIN_SYSTEM_FONT_CG_OFS	( 1+TALK_WIN_CGX_SIZ )
#define NMIX_MAINWIN_STR_COLOR		( 2 )		// �t�H���g�p�J���[�p���b�g
#define NMIX_MAINWIN_SYSTEMSTR_COLOR		( 3 )		// �t�H���g�p�J���[�p���b�g
#define NMIX_MAINWIN_BMP_PRICOLOR		( GF_PRINTCOLOR_MAKE(1,2,15) )
#define NMIX_MAINWIN_BMP_SYSTEMPRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define NMIX_MAINWIN_COMMBMP_X	( 10 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_COMMBMP_Y	( 11 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_COMMBMP_CX	( 16 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_COMMBMP_CY	( 4 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_COMMBMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// �L�����N�^�I�t�Z�b�g

#define NMIX_MAINWIN_RESULT0_BMP_X	( 2 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT0_BMP_Y	( 1 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT0_BMP_CX	( 28 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT0_BMP_CY	( 15 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT0_BMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// �L�����N�^�I�t�Z�b�g

#define NMIX_MAINWIN_RESULT1_BMP_X	( 2 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT1_BMP_Y	( 18 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT1_BMP_CX	( 28 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT1_BMP_CY	( 5 )			// �����ʃr�b�g�}�b�vsize
#define NMIX_MAINWIN_RESULT1_BMP_COFS ( NMIX_MAINWIN_RESULT0_BMP_COFS+ (NMIX_MAINWIN_RESULT0_BMP_CX * NMIX_MAINWIN_RESULT0_BMP_CY) )			// �L�����N�^�I�t�Z�b�g


// ���ʕ\���ʒu
#define NMIX_MAINWIN_RESULT_TITLE_X	( 56 )		// �S�̃^�C�g��
#define NMIX_MAINWIN_RESULT_TITLE_Y	( 0 )		// �S�̃^�C�g��
#define NMIX_MAINWIN_RESULT_PORUTO_TITLE_X	( 0 )	// �|���g�^�C�g��
#define NMIX_MAINWIN_RESULT_PORUTO_TITLE_Y	( 0 )	// �|���g�^�C�g��
#define NMIX_MAINWIN_RESULT_NEMU_TITLE_X	( 0 )	// ���j���[�^�C�g��
#define NMIX_MAINWIN_RESULT_NEMU_NUM_X		( 160 )	// ���j���[�l

#define NMIX_MAINWIN_RESULT_COOKTIME_KETA	( 2 )	// �������Ԍ�
#define NMIX_MAINWIN_RESULT_KOBOSI_KETA	( 4 )		// ���ڂ�
#define NMIX_MAINWIN_RESULT_KOGASI_KETA	( 4 )		// ����
#define NMIX_MAINWIN_RESULT_TEAMWORK_KETA	( 4 )		// �`�[�����[�N
#define NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y	( 24 )	// �������ԃ^�C�g��
#define NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y	( 48 )	// ���ڂ�����
#define NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y	( 68 )	// ����������
#define NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y ( 88 )// TEAMWORK�_��

#define NMIX_MAINWIN_RESULT_PORUTO_KETA		( 2 )	//�|���g�f�[�^��
#define NMIX_MAINWIN_RESULT_PORUTO_NUM_X	( 16 )	// �|���g�f�[�^
#define NMIX_MAINWIN_RESULT_PORUTO_NUM_Y	( 24 )	//�|���g�f�[�^

#define NMIX_MAINWIN_COMMBACK_COLOR	( 4 )

// �e�L�X�g�\���ʏ���
#define NMIX_MAINWIN_TEXT_BMP_X		( 2 )
#define NMIX_MAINWIN_TEXT_BMP_Y		( 2 )
#define NMIX_MAINWIN_TEXT_BMP_CX	( 27 )
#define NMIX_MAINWIN_TEXT_BMP_CY	( 5 )
#define NMIX_MAINWIN_TEXT_BMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// �L�����N�^�I�t�Z�b�g


// �����ɂ������Ⴄ
// YESNO�E�B���h�E
#define NMIX_MAINWIN_YESNO_WND_X		( 24 )
#define NMIX_MAINWIN_YESNO_WND_Y		( 8 )
#define NMIX_MAINWIN_YESNO_BMP_COFS ( NMIX_MAINWIN_TEXT_BMP_COFS + (NMIX_MAINWIN_TEXT_BMP_CX * NMIX_MAINWIN_TEXT_BMP_CY) )			// �L�����N�^�I�t�Z�b�g
#define NMIX_MAINWIN_YESNO_PLT			( 5 )
 
// �G�t�F�N�g
#define NMIX_MAINWIN_COMM_EFF_DRAW_TIME	( 30 )	
#define NMIX_MAINWIN_COMM_EFF_TCB_PRI	( 1024 )


static void NMixMainWin_BmpInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID );
static void NMixMainWin_BmpRelease( NMIX_DEMO_MAIN_WIN* p_work );
static void NMixMainWin_BackGroundInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID );
//----------------------------------------------------------------------------
/**
 *	@brief	���C���E�B���h�E�@������
 *
 *	@param	p_work			���[�N
 *	@param	comm_coun		�ʐM���萔
 *	@param	p_msg_data		���b�Z�[�W�f�[�^
 *	@param	p_comm_data		�ʐM�f�[�^
 *	@param	wnd_type		�E�B���h�E�^�C�v
 *	@param	heapID			�q�[�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_Init( NMIX_DEMO_MAIN_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_MAIN_WIN) );
	p_work->p_msg_data = p_msg_data;
	p_work->comm_count = comm_count;
	p_work->heapID = heapID;
	p_work->p_comm_data = p_comm_data;
	p_work->wnd_type = wnd_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C���E�B���h�E�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_Delete( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ���\�[�X�j�����Ă��܂���
	GF_ASSERT( p_work->res_load == FALSE );

	// �^�X�N�j��
	NMixGameDemo_StopComment( p_work );

	
	memset( p_work, 0, sizeof(NMIX_DEMO_MAIN_WIN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C����ʁ@BG���\�[�X�ǂݍ���
 *	
 *	@param	p_work		���[�N
 *	@param	p_bgl		BGL
 *	@param	heapID		�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_GraphicLoad( NMIX_DEMO_MAIN_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID )
{
	GF_ASSERT( p_work->res_load == FALSE );

	// BGL�ݒ�
	p_work->p_bgl = p_bgl;
	
	// �r�b�g�}�b�v�E�B���h�E������
	NMixMainWin_BmpInit( p_work, heapID );

	// �w�i�ݒ�
	NMixMainWin_BackGroundInit( p_work, heapID );

	// ��\���ɂ���
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�����BG�@���\�[�X�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_GraphicRelease( NMIX_DEMO_MAIN_WIN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	
	// �r�b�g�}�b�v�E�B���h�E�j��
	NMixMainWin_BmpRelease( p_work );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E������
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BmpInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID )
{
	int i;
	static u16 bitmap_param[ NMIX_DEMO_MAINWIN_NUM ][ 6 ] = {
		{ 
			NMIX_MAINWIN_COMMBMP_X,
			NMIX_MAINWIN_COMMBMP_Y,
			NMIX_MAINWIN_COMMBMP_CX,
			NMIX_MAINWIN_COMMBMP_CY,
			NMIX_MAINWIN_STR_COLOR,
			NMIX_MAINWIN_COMMBMP_COFS,
		},
		{
			NMIX_MAINWIN_RESULT0_BMP_X,
			NMIX_MAINWIN_RESULT0_BMP_Y,
			NMIX_MAINWIN_RESULT0_BMP_CX,
			NMIX_MAINWIN_RESULT0_BMP_CY,
			NMIX_MAINWIN_SYSTEMSTR_COLOR,
			NMIX_MAINWIN_RESULT0_BMP_COFS,
		},
		{
			NMIX_MAINWIN_RESULT1_BMP_X,
			NMIX_MAINWIN_RESULT1_BMP_Y,
			NMIX_MAINWIN_RESULT1_BMP_CX,
			NMIX_MAINWIN_RESULT1_BMP_CY,
			NMIX_MAINWIN_SYSTEMSTR_COLOR,
			NMIX_MAINWIN_RESULT1_BMP_COFS,
		},
		{
			NMIX_MAINWIN_TEXT_BMP_X,
			NMIX_MAINWIN_TEXT_BMP_Y,
			NMIX_MAINWIN_TEXT_BMP_CX,
			NMIX_MAINWIN_TEXT_BMP_CY,
			NMIX_MAINWIN_STR_COLOR,
			NMIX_MAINWIN_TEXT_BMP_COFS,
		},
	};

	// �g�̊G�ȂǓǂݍ���
	// ��b�g
	TalkWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME2_M,
			NMIX_MAINWIN_FONT_CG_OFS,
			NMIX_MAINWIN_FONT_COLOR,
			p_work->wnd_type, heapID );
	// ��b�t�H���g�p���b�g�ǂݍ���
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 
			NMIX_MAINWIN_STR_COLOR * 32, heapID );

	// ���j���[�g
	MenuWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME2_M,
			NMIX_MAINWIN_SYSTEM_FONT_CG_OFS,
			NMIX_MAINWIN_MENUFONT_COLOR,
			MENU_TYPE_SYSTEM, heapID );
	// �V�X�e���t�H���g�p���b�g�ǂݍ���
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 
			NMIX_MAINWIN_SYSTEMSTR_COLOR * 32, heapID );
	
	// �r�b�g�}�b�v�E�B���h�E�������m��
	for( i=0; i<NMIX_DEMO_MAINWIN_NUM; i++ ){
		p_work->p_bmp[i] = GF_BGL_BmpWinAllocGet( heapID, 1 );

		GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp[i],
				GF_BGL_FRAME2_M,
				bitmap_param[i][0],
				bitmap_param[i][1],
				bitmap_param[i][2],
				bitmap_param[i][3],
				bitmap_param[i][4],
				bitmap_param[i][5] );

		GF_BGL_BmpWinDataFill( p_work->p_bmp[i], 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�j��
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BmpRelease( NMIX_DEMO_MAIN_WIN* p_work )
{
	int i;

	for( i=0; i<NMIX_DEMO_MAINWIN_NUM; i++ ){
		GF_BGL_BmpWinDel( p_work->p_bmp[i] );
		GF_BGL_BmpWinFree( p_work->p_bmp[i], 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		�w�i������
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BackGroundInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// �w�i�ݒ�
	ArcUtil_PalSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_s_window_NCLR, 
			PALTYPE_MAIN_BG, NMIX_MAINWIN_COMMBACK_COLOR*32,
			1*32, heapID );
	ArcUtil_BgCharSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_s_window_NCGR,
			p_work->p_bgl, GF_BGL_FRAME1_M, 0, 0, FALSE, heapID );

	buff = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			NARC_nutmixer_cook_s_window_NSCR, FALSE, &p_scrn, heapID );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_work->p_bgl, GF_BGL_FRAME1_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8,
			p_scrn->screenHeight / 8 );

	// �p���b�g�����킹��
	GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_M,
			0, 0, 
			p_scrn->screenWidth / 8,
			p_scrn->screenHeight / 8,
			NMIX_MAINWIN_COMMBACK_COLOR );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_M );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�I�����b�Z�[�W�\��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_EndMsgPirntOn( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ������`��
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME], 0 );

	// ������`��
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME],
			FONT_TALK, p_work->p_msg_data->end, 0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );
	// �]��
	GF_BGL_BmpWinOn( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );

	// �\���ݒ�
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����b�Z�[�W��\��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_EndMsgPrintOff( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ��\���ɂ��ďI���
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

	// �]��
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );
}


//----------------------------------------------------------------------------
/**	
 *	@brief	�G�t�F�N�g���C���^�X�N
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_MainComment( TCB_PTR tcb, void* p_work )
{
	NMIX_DEMO_MAIN_WIN* p_demo = p_work;
	
	p_demo->move_count ++;
	
	if( p_demo->move_count >= NMIX_MAINWIN_COMM_EFF_DRAW_TIME ){
		// ��\���ɂ��ďI���
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		TCB_Delete( tcb );
		p_demo->move_tcb = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�����g�`��G�t�F�N�g�J�n
 *
 *	@param	p_work		���[�N
 *	@param	comm_type	�R�����g�^�C�v
 *
 *	comm_type
		NMIX_STMSG_SPEED_KOGERU00,
		NMIX_STMSG_SPEED_HAYAI00,
		NMIX_STMSG_SPEED_KOGERU01,
		NMIX_STMSG_SPEED_HAYAI01,
		NMIX_STMSG_SPEED_KOGERU02,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_StartComment( NMIX_DEMO_MAIN_WIN* p_work, u32 comm_type )
{
	// �\�����łȂ����`�F�b�N
	GF_ASSERT( p_work->move_tcb == NULL );

	p_work->move_tcb = TCB_Add( NMixGameDemo_MainComment, p_work, NMIX_MAINWIN_COMM_EFF_TCB_PRI );
	p_work->move_count = 0;


	// ������`��
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME], 0 );

	// ������`��
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME],
			FONT_TALK, p_work->p_msg_data->spd[ comm_type ], 0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );
	// �]��
	GF_BGL_BmpWinOn( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );

	// �\���ݒ�
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���`�F�b�N
 *	
 *	@param	cp_work 
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_EndCheckComment( const NMIX_DEMO_MAIN_WIN* cp_work )
{
	if( cp_work->move_tcb == NULL ){
		return TRUE;
	}
	return FALSE;
}
	
//----------------------------------------------------------------------------
/**
 *	@brief	�R�����g�G�t�F�N�g�@��~
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_StopComment( NMIX_DEMO_MAIN_WIN* p_work )
{
	if( p_work->move_tcb == NULL ){
		return ;
	}
	// ��\���ɂ��ďI���
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	
	TCB_Delete( p_work->move_tcb );
	p_work->move_tcb = NULL;
}

// �V�[��0
static void NMixGameDemo_MainWin_ResultSeen0( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ���b�Z�[�W�X�N���[�����N���[��
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME2_M );
	
	// ������`��
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN], 15 );

	// ���ʔ��\
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->result, 
			NMIX_MAINWIN_RESULT_TITLE_X, NMIX_MAINWIN_RESULT_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// �g�̕`��
	BmpMenuWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN], WINDOW_TRANS_ON, NMIX_MAINWIN_SYSTEM_FONT_CG_OFS, NMIX_MAINWIN_MENUFONT_COLOR );

	// �������Ⴂ�E�B���h�E
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB], 15 );

	// �o�����|���b�N
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_PORUTO_TI ], 
			NMIX_MAINWIN_RESULT_PORUTO_TITLE_X, NMIX_MAINWIN_RESULT_PORUTO_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// �g�̕`��
	BmpMenuWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB], WINDOW_TRANS_ON, NMIX_MAINWIN_SYSTEM_FONT_CG_OFS, NMIX_MAINWIN_MENUFONT_COLOR );

	// �\��
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}

#ifdef PM_DEBUG
extern u32 D_Tomoya_MazeMaze_TeamWork;
#endif

// �V�[��1
static void NMixGameDemo_MainWin_ResultSeen1( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ��������
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_COOK_TIME_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// ���ۂ̎���
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0, 
			p_work->p_comm_data->get_result_data.min,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// ��
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 1, 
			p_work->p_comm_data->get_result_data.second,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// �b
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
			p_work->p_comm_data->get_result_data.dec,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// �R���}
	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_COOK_TIME] );	// �W�J
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// ���ڂ�����
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_KOBOSI_NUM_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// ���ۂ̉�
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0, 
			p_work->p_comm_data->get_result_data.kobore_num,
			NMIX_MAINWIN_RESULT_KOBOSI_KETA,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_KOBOSI_NUM] );	// �W�J
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// �ł�������
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_KOGASI_NUM_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, 
			NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// ���ۂ̉�
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0,
			p_work->p_comm_data->get_result_data.kogasi_num, 
			NMIX_MAINWIN_RESULT_KOGASI_KETA,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_KOGASI_NUM] );	// �W�J
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// ���������l���ł���Ă�����TEAMWORK�_��\��
#ifdef PM_DEBUG
	D_Tomoya_MazeMaze_TeamWork = p_work->p_comm_data->get_result_data.match_num;
#endif
/*	if( p_work->comm_count > 1 ){
		// TEAMWORK�_��
		GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
				FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_TEAMWORK_TI ], 
				NMIX_MAINWIN_RESULT_NEMU_TITLE_X, 
				NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y,
				0,
				NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
		
		// ���ۂ̉�
		WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0,
				p_work->p_comm_data->get_result_data.match_num,
				NMIX_MAINWIN_RESULT_TEAMWORK_KETA,
				NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_TEAMWORK] );	// �W�J
		
		GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
				FONT_SYSTEM, p_work->p_msg_data->tmp, 
				NMIX_MAINWIN_RESULT_NEMU_NUM_X,
				NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y,
				0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	}//*/
	
	// �\��
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
}

// �V�[��2
static void NMixGameDemo_MainWin_ResultSeen2( NMIX_DEMO_MAIN_WIN* p_work )
{
	// �|���b�N��	���x�� ��
	WORDSET_RegisterPorutoName( p_work->p_msg_data->wset, 3, 
			p_work->p_comm_data->get_result_data.poruto_type );	
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 1,
			p_work->p_comm_data->get_result_data.poruto_lv,
			NMIX_MAINWIN_RESULT_PORUTO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
			p_work->comm_count,
			NMIX_MAINWIN_RESULT_PORUTO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
	if( sys.cont & PAD_BUTTON_A ){
		WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
				99,
				NMIX_MAINWIN_RESULT_PORUTO_KETA,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	}
#endif

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_PORUTO] );	// �W�J

	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_PORUTO_NUM_X, 
			NMIX_MAINWIN_RESULT_PORUTO_NUM_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// �\��
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����ʕ\��
 *
 *	@param	p_work		���[�N
 *	@param	seen		�V�[��
		NMIX_DEMO_MINWIN_RESULT_SEEN0,
		NMIX_DEMO_MINWIN_RESULT_SEEN1,
		NMIX_DEMO_MINWIN_RESULT_SEEN2,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_ResultOn( NMIX_DEMO_MAIN_WIN* p_work, u32 seen )
{

	switch( seen ){
	case NMIX_DEMO_MINWIN_RESULT_SEEN0:
		NMixGameDemo_MainWin_ResultSeen0( p_work );
		break;
		
	case NMIX_DEMO_MINWIN_RESULT_SEEN1:
		NMixGameDemo_MainWin_ResultSeen1( p_work );
		break;
		
	case NMIX_DEMO_MINWIN_RESULT_SEEN2:
		NMixGameDemo_MainWin_ResultSeen2( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ʕ\����off
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_ResultOff( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ���b�Z�[�W�X�N���[�����N���[��
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME2_M );
	
	// �\��
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�e�L�X�g�\��
 *
 *	@param	p_work		���[�N
 *	@param	text_no		�e�L�X�g�^�C�v
			NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO,
			NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI,
			NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI,
			NMIX_DEMO_MAINWIN_TEXT_BAG,
			NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU,
			NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE,
			NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_TextOn( NMIX_DEMO_MAIN_WIN* p_work, u32 text_no )
{
	STRBUF* str;
	int my_netid;
	
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT], 15 );

	switch( text_no ){
	case NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO:
		WORDSET_RegisterPlayerName( p_work->p_msg_data->wset, 0,
				 p_work->p_comm_data->p_mystate[ p_work->p_comm_data->my_netid ] );
		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->casein );	// �W�J
		str = p_work->p_msg_data->tmp;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI:
		str = p_work->p_msg_data->replay;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI:
		str = p_work->p_msg_data->poruto_ippai;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_BAG:
		str = p_work->p_msg_data->bag_erabu;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU:
		str = p_work->p_msg_data->exit;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE:
		str = p_work->p_msg_data->nuts_none;
		break;

	case NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI:
		str = p_work->p_msg_data->wait;
		break;
	}
	
	// �����̕\��
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT],
			FONT_TALK, str, 
			0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );

	// �g�̕`��
	BmpTalkWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT], WINDOW_TRANS_ON, NMIX_MAINWIN_FONT_CG_OFS, NMIX_MAINWIN_FONT_COLOR );
	
	// �\��
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT] );
}



//-----------------------------------------------------------------------------
/**
 *		�X�[�v�G�t�F�N�g�Ǘ�
 */
//-----------------------------------------------------------------------------
enum{
	NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,	// �A�j�����I��莟�������
	NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,		// �I�����N�G�X�g��������ď�����
	NMIX_DEMO_SOOP_EFF_MOVETYPE_NUM
};

//-------------------------------------
//	�����p�����[�^
//=====================================
typedef struct {
	fx32 rnd_scale_min;	// �g�k�ŏ�
	fx32 rnd_scale_max;	// �g�k�ő�
	fx32 rnd_scale_ss;	// �g�k�����x
	fx32 move_ss;		// �����x
	u8 rnd_dis_s_min;	// �����J�n�ŏ�
	u8 rnd_dis_s_max;	// �����J�n�ő�
	u8 rnd_dis_min;		// ���������ŏ�
	u8 rnd_dis_max;		// ���������ő�
	u8 move_sync;		// �����V���N��
	u8 res_id;			// �f�t�H���g���\�[�X���Ԗڂ�
	u8 res_anm;			// �A�j���[�V�������Ԗڂ�
	u8 move_type;		// �����^�C�v

	u8 scale_use;		// �g�k�g�p�t���O
	u8 soop_move;		// �X�[�v����
	u8 pri;				// priority
} NMIX_DEMO_SOOP_EFF_PARAM;

// �����p�����[�^
// �Ō�̃X�[�v�^�C�v�ɂ́A���ڂ�邪�Ȃ��̂�-1���Ă��܂�
#define EFF_SOOP_DATA_NUM	( (NMIX_SOOPTYPE_SOOP_NUM*3) - 1 )	// �f�[�^����
static const NMIX_DEMO_SOOP_EFF_PARAM EffSoopMoveParam[ EFF_SOOP_DATA_NUM ] = {
	{	// �X�[�v�`��0	��
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		0,					// ���������ŏ�
		0,					// ���������ő�
		32,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_SOUP,	// ���\�[�X���Ԗڂ�
		1,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},
	{	// �X�[�v�`��0	������
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.0f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		0,					// �J�n�����ŏ�
		8,					// �J�n�����ő�
		0,					// ���������ŏ�
		24,					// ���������ő�
		16,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_SOUP,	// ���\�[�X���Ԗڂ�
		2,					// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,	// �����^�C�v
		TRUE,				// �g�k�g�p�t���O
		TRUE,				// �X�[�v�Ɠ������ē�����
		10,					// �\�t�g�D�揇��
	},
	{	// �X�[�v�`��0	���ڂ��
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(2.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		32,					// ���������ŏ�
		64,					// ���������ő�
		16,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_SOUP,	// ���\�[�X���Ԗڂ�
		0,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},

	{	// �X�[�v�`��1	��
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		0,					// ���������ŏ�
		0,					// ���������ő�
		32,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_CREAM,	// ���\�[�X���Ԗڂ�
		1,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},
	{	// �X�[�v�`��1	������
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.0f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		0,					// �J�n�����ŏ�
		8,					// �J�n�����ő�
		0,					// ���������ŏ�
		24,					// ���������ő�
		16,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_CREAM,	// ���\�[�X���Ԗڂ�
		2,					// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,	// �����^�C�v
		TRUE,				// �g�k�g�p�t���O
		TRUE,				// �X�[�v�Ɠ������ē�����
		10,					// �\�t�g�D�揇��
	},
	{	// �X�[�v�`��1	���ڂ��
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(4.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		32,					// ���������ŏ�
		64,					// ���������ő�
		16,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_CREAM,	// ���\�[�X���Ԗڂ�
		0,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},
	

	{	// �X�[�v�`��2	��
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		0,					// ���������ŏ�
		0,					// ���������ő�
		32,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_SOBORO,	// ���\�[�X���Ԗڂ�
		0,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},
	{	// �X�[�v�`��2	����
		FX32_CONST(0.50f),	// �����ŋ��߂�g��l�ŏ�
		FX32_CONST(1.50f),	// �����ŋ��߂�g��l�ő�
		FX32_CONST(0.0f),	// �g�叉���x
		FX32_CONST(0.0f),	// ���������x
		32,					// �J�n�����ŏ�
		64,					// �J�n�����ő�
		0,					// ���������ŏ�
		0,					// ���������ő�
		32,					// �����V���N
		NMIX_GAME_DEF_OAM_RES_SOBORO,	// ���\�[�X���Ԗڂ�
		1,						// �A�j���i���o�[
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// �����^�C�v
		FALSE,				// �g�k�g�p�t���O
		FALSE,				// �X�[�v�Ɠ������ē�����
		5,					// �\�t�g�D�揇��
	},
};

#define NMIX_DEMO_SOOP_EFFECT_PRI	( 100 )		// �\�t�gpriority
#define NMIX_DEMO_SOOP_EFFECT_BG_PRI	( 2 )	// �n�[�hpri
#define NMIX_DEMO_SOOP_END_EFF_SYNC	( 8 )	// �����I���G�t�F�N�g�V���N��



static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetClaenObj( NMIX_DEMO_SOOP_EFFECT* p_work );
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetOldObj( NMIX_DEMO_SOOP_EFFECT* p_work );
static void NmixGameDemo_SoopEffect_DeleteObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );
static void NmixGameDemo_SoopEffect_MainObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );
static void NmixGameDemo_SoopEffect_MoveSoopObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, NUTMIX_GAME_COMM_PACK* p_comm_pack );
static void NmixGameDemo_SoopEffect_AddObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, int move_type, fx32 s_x, fx32 e_x, fx32 ss_x, fx32 s_y, fx32 e_y, fx32 ss_y, fx32 scale_x, fx32 scale_e, fx32 scale_ss, BOOL scale_use, int move_sync, NMIXGAME_CLACT_RES_WORK* p_res, int anm_idx, NMIXGAME_CLACT_SYS* p_clact, u32 heapID, BOOL soop_move, u8 pri );
static void NmixGameDemo_SoopEffect_EndEffectObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );


//----------------------------------------------------------------------------
/**
 *	@brief	�G�t�F�N�g������
 *	
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Init( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_SOOP_EFFECT) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�G�t�F�N�g���[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Delete( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );

	memset( p_work, 0, sizeof(NMIX_DEMO_SOOP_EFFECT) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_work				���[�N
 *	@param	p_clact				�Z���A�N�^�[
 *	@param	p_def_oam_res		�f�t�H���g���\�[�X
 *	@param	heapID				�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_GraphicLoad( NMIX_DEMO_SOOP_EFFECT* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	p_work->p_clact = p_clact;
	p_work->p_def_oam_res = p_def_oam_res;
	p_work->heapID	= heapID;

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_GraphicRelease( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;
	
	// �o�^����Ă���OAM��j������
	for(  i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact != NULL ){
			NmixGameDemo_SoopEffect_DeleteObj( &p_work->eff_obj[i] );
		}
	}
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C���֐�
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Main( NMIX_DEMO_SOOP_EFFECT* p_work, NUTMIX_GAME_COMM_PACK* p_comm_pack )
{
	int i;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact ){
			NmixGameDemo_SoopEffect_MainObj( &p_work->eff_obj[i] );

			// �X�[�v�ƈꏏ�Ɉړ�����
			if( p_work->eff_obj[i].soop_move ){
				NmixGameDemo_SoopEffect_MoveSoopObj( &p_work->eff_obj[i], p_comm_pack );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�G�t�F�N�g�o�^
 *
 *	@param	p_work			���[�N
 *	@param	soop_type		�X�[�v�^�C�v
 *	@param	eff_type		�G�t�F�N�g�^�C�v
 *
 *	eff_type
		NMIX_DEMO_SOOP_EFF_TYPE_KOGE,
		NMIX_DMEO_SOOP_EFF_TYPE_KOBORE,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Add( NMIX_DEMO_SOOP_EFFECT* p_work, int soop_type, int eff_type )
{
	NMIX_DEMO_SOOP_EFF_OBJ* p_obj;
	u16 rnd_rota;
	fx32 s_x, e_x, s_y, e_y, e_scale, ss_x, ss_y;
	NMIX_DEMO_SOOP_EFF_PARAM move_param = EffSoopMoveParam[ soop_type*3+eff_type ];
	int move_s_dis, move_dis;


	// �󂢂Ă���I�u�W�F�m��
	p_obj = NmixGameDemo_SoopEffect_GetClaenObj( p_work );
	if( p_obj == NULL ){
		// ��Ԑ̂ɓo�^���ꂽ�I�u�W�F�N�g���擾
		p_obj = NmixGameDemo_SoopEffect_GetOldObj( p_work );
		GF_ASSERT( p_obj );
		NmixGameDemo_SoopEffect_DeleteObj( p_obj );	// �I�u�W�F�N�g�j��
	}
	
	// �������g�p���ăp�����[�^���쐬����
	// �������������߂�
	rnd_rota = gf_mtRand();

	// �J�n��������
	move_s_dis = move_param.rnd_dis_s_min + (gf_mtRand() % move_param.rnd_dis_s_max);
	move_dis = move_param.rnd_dis_min + (gf_mtRand() % move_param.rnd_dis_max);

	move_dis += move_s_dis;	// �J�n�ʒu�𑫂�
	
	// ��������J�n�������W�����߂�
	s_x = FX_Mul( FX_SinIdx( rnd_rota ),  move_s_dis*FX32_ONE );
	s_y = FX_Mul( FX_CosIdx( rnd_rota ),  move_s_dis*FX32_ONE );
	// ��������I���������W�����߂�
	e_x = FX_Mul( FX_SinIdx( rnd_rota ),  move_dis*FX32_ONE );
	e_y = FX_Mul( FX_CosIdx( rnd_rota ),  move_dis*FX32_ONE );
	// �������珉���x���������߂�
	ss_x = FX_Mul( FX_SinIdx( rnd_rota ), move_param.move_ss );
	ss_y = FX_Mul( FX_CosIdx( rnd_rota ), move_param.move_ss );

	// �J�n�I�����W�𒆐S����̋����ɂ���
	s_x += 128 * FX32_ONE;
	e_x += 128 * FX32_ONE;
	s_y += 96 * FX32_ONE;
	e_y += 96 * FX32_ONE;

	// �g�k�����߂�
	e_scale = move_param.rnd_scale_min + (gf_mtRand() % move_param.rnd_scale_max);
	
	// �����f�[�^�o�^
	NmixGameDemo_SoopEffect_AddObj(
			p_obj, move_param.move_type,
			s_x, e_x, ss_x, s_y, e_y, ss_y,
			FX32_CONST( 0.10f ), e_scale, move_param.rnd_scale_ss, move_param.scale_use,
			move_param.move_sync,
			&p_work->p_def_oam_res[ move_param.res_id ],
			move_param.res_anm, p_work->p_clact, p_work->heapID,
			move_param.soop_move,
			move_param.pri );

	// �o�^����
	p_obj->add_time = p_work->add_count;
	p_work->add_count ++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����N�G�X�g���o���A�I���҂��G�t�F�N�g������
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_DelReq( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;	
	
	// �I�����N�G�X�g���o���A�I���G�t�F�N�g�ݒ�
	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		
		if( p_work->eff_obj[i].clact != NULL ){
			NmixGameDemo_SoopEffect_EndEffectObj( &p_work->eff_obj[i] );
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	�N���[���I�u�W�F�N�g�擾
 *
 *	@param	p_work	���[�N
 *
 *	@return	�I�u�W�FPTR		NULL�F�Ȃ�
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetClaenObj( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact == NULL ){
			return &p_work->eff_obj[i];
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��Ԑ̂ɓo�^���ꂽ�I�u�W�F�N�g���擾
 *
 *	@param	p_work	���[�N
 *
 *	@return	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetOldObj( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;
	NMIX_DEMO_SOOP_EFF_OBJ* p_obj = NULL;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact != NULL ){

			if( p_obj == NULL ){
				p_obj = &p_work->eff_obj[i];
			}else{
				if( p_obj->add_time > p_work->eff_obj[i].add_time ){
					p_obj = &p_work->eff_obj[i];
				}
			}
		}
	}
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�j������
 *
 *	@param	p_obj	���[�N
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_DeleteObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	GF_ASSERT( p_obj->clact );

	CLACT_Delete( p_obj->clact );
	memset( p_obj, 0, sizeof(NMIX_DEMO_SOOP_EFF_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g���C������
 *
 *	@param	p_obj	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_MainObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	BOOL result;
	
	if( p_obj->move_end == FALSE ){
		// ��������
		p_obj->move_end = NMIX_DEMO_AddMoveMainFx( &p_obj->move_x );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_y );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_scale );

		// ���W�ݒ�
		p_obj->matrix.x = p_obj->move_x.x;
		p_obj->matrix.y = p_obj->move_y.x;
		CLACT_SetMatrix( p_obj->clact, &p_obj->matrix );

		if( p_obj->scale_use ){
			p_obj->scale.x = p_obj->move_scale.x;
			p_obj->scale.y = p_obj->move_scale.x;
			p_obj->scale.z = p_obj->move_scale.x;
			CLACT_SetScale( p_obj->clact, &p_obj->scale );
		}
	}

	if( p_obj->anm_end == FALSE ){
		// �A�j���I���Ɠ����I�������m
		if( CLACT_AnmActiveCheck( p_obj->clact ) == FALSE ){
			p_obj->anm_end = TRUE;
		}
	}

	if( p_obj->move_type == NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END ){
		
		if( (p_obj->move_end == TRUE) && (p_obj->anm_end == TRUE) ){
			// �j��
			NmixGameDemo_SoopEffect_DeleteObj( p_obj );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�ꏏ�ɃI�u�W�F�N�g����]������
 *
 *	@param	p_obj		�I�u�W�F�N�g
 *	@param	p_comm_pack	�ʐM�p�b�N
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_MoveSoopObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, NUTMIX_GAME_COMM_PACK* p_comm_pack )
{
	VecFx32 matrix;
	u32 dist;
	u16 def_rota;
	u16 calc_rota;
	fx32 calc_x, calc_y;
	
	// �S�A�j���I���㓮��
	if( (p_obj->move_end == TRUE) && (p_obj->anm_end == TRUE) ){
		if( p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_way == 0 ){
			p_obj->obj_rota += p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_sp;
		}else{
			p_obj->obj_rota -= p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_sp;
		}

		calc_x = p_obj->matrix.x - (NMIX_SOOP_ROTA_CX * FX32_ONE);
		calc_y = p_obj->matrix.y - (NMIX_SOOP_ROTA_CY * FX32_ONE);

		dist = GetVectorDistance( 	
				calc_x >> FX32_SHIFT,
				calc_y >> FX32_SHIFT,
				0, 0 );

		def_rota = FX_Atan2Idx(
				calc_y,
				calc_x );

		calc_rota = def_rota + p_obj->obj_rota;

		// �A�N�^�[���W��ݒ�
		matrix.x = FX_Mul( FX_CosIdx( calc_rota ), dist * FX32_ONE );
		matrix.y = FX_Mul( FX_SinIdx( calc_rota ), dist * FX32_ONE );

		matrix.x += (NMIX_SOOP_ROTA_CX*FX32_ONE);
		matrix.y += (NMIX_SOOP_ROTA_CY*FX32_ONE);

		// ��]����W��ݒ�
		CLACT_SetMatrix( p_obj->clact, &matrix );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�o�^
 *
 *	@param	p_obj			�I�u�W�F�N�g
 *	@param	move_type		�^�C�v
 *	@param	s_x				�J�n�����W
 *	@param	e_x				�I�������W
 *	@param	ss_x			�����x��
 *	@param	s_y				�J�n�����W
 *	@param	e_y				�I�������W
 *	@param	ss_y			�����x��
 *	@param	scale_x			�g�k�J�n
 *	@param	scale_e			�g�k�Ō�
 *	@param	scale_ss		�g�k�����x
 *	@param	scale_use		�g�k���g�p���邩
 *	@param	move_sync		�����V���N��
 *	@param	p_res			���\�[�X
 *	@param	anm_idx			�A�j���i���o�[
 *	@param	p_clact			�A�N�^�[
 *	@param	heapID			�q�[�vID
 *	@param	soop_move		�X�[�v����
 *	@param	pri				�\�t�gpriority
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_AddObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, int move_type, fx32 s_x, fx32 e_x, fx32 ss_x, fx32 s_y, fx32 e_y, fx32 ss_y, fx32 scale_x, fx32 scale_e, fx32 scale_ss, BOOL scale_use, int move_sync, NMIXGAME_CLACT_RES_WORK* p_res, int anm_idx, NMIXGAME_CLACT_SYS* p_clact, u32 heapID, BOOL soop_move, u8 pri )
{
	p_obj->move_type = move_type;
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_x,
			s_x, e_x, ss_x, move_sync );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_y,
			s_y, e_y, ss_y, move_sync );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_scale,
			scale_x, scale_e, scale_ss, move_sync );

	p_obj->matrix.x = s_x;
	p_obj->matrix.y = s_y;
	p_obj->scale.x = scale_x;
	p_obj->scale.y = scale_x;
	p_obj->scale.z = scale_x;
	p_obj->scale_use = scale_use;
	p_obj->soop_move = soop_move;

	// �A�N�^�[�o�^
	p_obj->clact = NMIXGAME_CLACT_Add( p_clact, p_res, s_x, s_y, 0, pri, heapID );
	GF_ASSERT( p_obj->clact );	// �o�^���s
	if( p_obj->scale_use ){
		// �g�k
		CLACT_SetScaleAffine( p_obj->clact, &p_obj->scale, CLACT_AFFINE_DOUBLE );
	}
	// �A�j��
	CLACT_AnmChg( p_obj->clact, anm_idx );
	// AUTO�A�j��
	CLACT_SetAnmFlag( p_obj->clact, TRUE );
	// BG�D�揇��
	CLACT_BGPriorityChg( p_obj->clact, NMIX_DEMO_SOOP_EFFECT_BG_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���G�t�F�N�g�ݒ�
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_EndEffectObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	// �A�j���^�C�v�`�F�b�N
	// �I�����N�G�X�g�`�����`�F�b�N
	if( p_obj->move_type != NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ ){
		return ;
	}
	
	// �g�k�A�j�����ďI���
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_scale,
			p_obj->move_scale.x, FX32_CONST(0.050f), 0, NMIX_DEMO_SOOP_END_EFF_SYNC );

	// �A�j���I���㎩��
	p_obj->move_type = NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END;
	p_obj->scale_use = TRUE;

	CLACT_SetAffineParam( p_obj->clact, CLACT_AFFINE_DOUBLE );

}


//-----------------------------------------------------------------------------
/**
 *		���G�t�F�N�g�Ǘ�
 */
//-----------------------------------------------------------------------------

#define NMIX_DEMO_YAZIRUSI_OAM_CONT_ID	( 7000 )	// �Ǘ�ID
#define NMIX_DEMO_YAZIRUSI_OAM_CL_NUM	( 2 )		// �J���[�{��
#define NMIX_DEMO_YAZIRUSI_OAM_SET_X	( 128 * FX32_ONE )
#define NMIX_DEMO_YAZIRUSI_OAM_SET_Y	( 96 * FX32_ONE )

#define NMIX_DEMO_YAZIRUSI_NORMAL_ANMNUM	( 3 )	// �_�ŉ�
#define NMIX_DEMO_YAZIRUSI_NORMAL_TIMING	( 8 )	// �_�Ń^�C�~���O


static void NmixGameDemo_Yazirusi_NormalAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_NormalAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_ReverseAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_ReverseAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );


//----------------------------------------------------------------------------
/**
 *	@brief	���G�t�F�N�g������
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Init( NMIX_DEMO_YAZIRUSI* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_YAZIRUSI) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���G�t�F�N�g�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Delete( NMIX_DEMO_YAZIRUSI* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_YAZIRUSI) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_work		���[�N
 *	@param	p_clact		�Z���A�N�^�[
 *	@param	heapID		�q�[�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_GraphicLoad( NMIX_DEMO_YAZIRUSI* p_work, NMIXGAME_CLACT_SYS* p_clact, u32 heapID )
{
	int i;
	
	GF_ASSERT( p_work->res_load == FALSE );


	p_work->p_clact = p_clact;
	
	// ���\�[�X�ǂݍ���
	NMIXGAME_CLACT_ResLoadEasy( p_clact,
			&p_work->oam_res, ARC_NUTMIXER_GRA,
			NARC_nutmixer_cook_s_yazi_NCLR,
			NMIX_DEMO_YAZIRUSI_OAM_CL_NUM,
			NARC_nutmixer_cook_s_yazi_NCGR, 
			NARC_nutmixer_cook_s_yaj_NCER, 
			NARC_nutmixer_cook_s_yaj_NANR, 
			NMIX_DEMO_YAZIRUSI_OAM_CONT_ID, heapID );

	// �I�u�W�F�N�g�o�^
	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		p_work->yazirusi[i].clact = NMIXGAME_CLACT_Add( p_clact,
				&p_work->oam_res,
				NMIX_DEMO_YAZIRUSI_OAM_SET_X,
				NMIX_DEMO_YAZIRUSI_OAM_SET_Y, 0,
				0, heapID );

		// �A�j���`�F���W
		if( i >= NMIX_DEMO_YAZIRUSI_LEFT ){

			CLACT_AnmChg( p_work->yazirusi[i].clact, 1 );
		}

		CLACT_SetDrawFlag( p_work->yazirusi[i].clact, FALSE );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�j��
 *
 *	@param	p_work		���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_GraphicRelease( NMIX_DEMO_YAZIRUSI* p_work )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		// �I�u�W�F�N�g�j��
		CLACT_Delete( p_work->yazirusi[i].clact );
	}
	
	// ���\�[�X�j��
	NMIXGAME_CLACT_ResDeleteEasy( p_work->p_clact, &p_work->oam_res );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��󃁃C������
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Main( NMIX_DEMO_YAZIRUSI* p_work )
{
	int i;
	
	// �e�X�̓���������
	// �E���́A�R��_�ł��ďI���
	// �t��]�́A�I��肪�N���܂ŁA�_�ł���
	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		if( (i == NMIX_DEMO_YAZIRUSI_LEFT) || (i == NMIX_DEMO_YAZIRUSI_RIGHT) ){
			NmixGameDemo_Yazirusi_NormalAnm( &p_work->yazirusi[i] );
		}else{
			NmixGameDemo_Yazirusi_ReverseAnm( &p_work->yazirusi[i] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������N�G�X�g
 *
 *	@param	p_work		���[�N
 *	@param	eff_type	�G�t�F�N�g�^�C�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Add( NMIX_DEMO_YAZIRUSI* p_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );

	// �����J�n
	if( (eff_type == NMIX_DEMO_YAZIRUSI_LEFT) || (eff_type == NMIX_DEMO_YAZIRUSI_RIGHT) ){
		NmixGameDemo_Yazirusi_NormalAnmStart( &p_work->yazirusi[eff_type] );
	}else{
		NmixGameDemo_Yazirusi_ReverseAnmStart( &p_work->yazirusi[eff_type] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���������I��
 *
 *	@param	p_work		���[�N
 *	@param	eff_type	�G�t�F�N�g�^�C�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Stop( NMIX_DEMO_YAZIRUSI* p_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );
	
	// �����I��
	p_work->yazirusi[ eff_type ].move = FALSE;

	// ��\����
	CLACT_SetDrawFlag( p_work->yazirusi[ eff_type ].clact, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���G�t�F�N�g���I����Ă��邩�`�F�b�N
 *
 *	@param	cp_work		���[�N
 *	@param	eff_type	�^�C�v
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_Yazirusi_EndCheck( const NMIX_DEMO_YAZIRUSI* cp_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );
	
	// �����I��
	if( cp_work->yazirusi[ eff_type ].move == FALSE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʏ�A�j���J�n
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_NormalAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	p_obj->count = 0;
	p_obj->count_num = NMIX_DEMO_YAZIRUSI_NORMAL_ANMNUM;
	p_obj->move = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�m�[�}���A�j��
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_NormalAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	if( p_obj->move == FALSE ){
		return ;
	}
	
	NmixGameDemo_Yazirusi_ReverseAnm( p_obj );

	// 0�ɂȂ����񐔂𐔂���
	if( p_obj->count == 0 ){
		p_obj->count_num --;
		if( p_obj->count_num <= 0 ){

			// �����I��
			p_obj->move = FALSE;
			// �`��OFF
			CLACT_SetDrawFlag( p_obj->clact, FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t��]�p�����J�n
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_ReverseAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	p_obj->count = 0;
	p_obj->move = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t��]�@�p�A�j�����C��
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_ReverseAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	if( p_obj->move == FALSE ){
		return ;
	}
	
	if( p_obj->count == 0 ){
		// �\��
		CLACT_SetDrawFlag( p_obj->clact, TRUE );
	}else if( p_obj->count == NMIX_DEMO_YAZIRUSI_NORMAL_TIMING ){
		// ��\��
		CLACT_SetDrawFlag( p_obj->clact, FALSE );
	}else if( p_obj->count == (NMIX_DEMO_YAZIRUSI_NORMAL_TIMING * 2) ){
		p_obj->count = 0;
		return ;
	}
	p_obj->count ++;
}



//-----------------------------------------------------------------------------
/**
 *		���L���L���@
 */
//-----------------------------------------------------------------------------
#define NMIX_DEMO_HOSI_SOFT_PRI	( 5 )
#define NMIX_DEMO_HOSI_BG_PRI	( 2 )

#define NMIX_DEMO_HOSI_MOVE_SYNC	( 16 )	// �����V���N��
#define NMIX_DEMO_HOSI_MOVE_DIST	( FX32_CONST( 16 ) )	// �ړ�����
#define NMIX_DEMO_HOSI_MOVE_SS		( FX32_CONST( 1 ) )		// �����x
#define NMIX_DEMO_HOSI_MOVE_ADDNUM	( 2 )	// 1��̓o�^��



static NMIX_DEMO_HOSI_KIRAKIRA_OBJ* NMixGameDemo_HosiKirakiraCleanObj_Get( NMIX_DEMO_HOSI_KIRAKIRA* p_work );

static void NMixGameDemo_HosiKiraKiraObjMain( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj );
static void NMixGameDemo_HosiKiraKiraObjDel( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj );
static void NMixGameDemo_HosiKirakiraObjAdd( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj, int anm_idx, fx32 x, fx32 y, fx32 e_x, fx32 e_y, fx32 ss_x, fx32 ss_y );



//----------------------------------------------------------------------------
/**
 *	@brief	�L���L��������
 *
 *	@param	p_work		���[�N
 *	@param	comm_count	�ʐM���萔
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Init( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int comm_count )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_HOSI_KIRAKIRA) );
	p_work->comm_count = comm_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L���L���@�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Delete( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	// ���\�[�X�j�����Ă��܂���B
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_HOSI_KIRAKIRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ��ݏ���
 *
 *	@param	p_work				���[�N
 *	@param	p_clact				�A�N�^�[�V�X�e��
 *	@param	p_def_oam_res		�f�t�H���g�肻�[��
 *	@param	heapID				�q�[�vID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_GraphicLoad( NMIX_DEMO_HOSI_KIRAKIRA* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	
	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		p_work->eff_obj[i].clact = NMIXGAME_CLACT_Add( p_clact,
				&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_COMMON ], 
				0, 0,
				0, NMIX_DEMO_HOSI_SOFT_PRI, heapID );
		CLACT_SetDrawFlag( p_work->eff_obj[i].clact, FALSE );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_GraphicRelease( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		CLACT_Delete( p_work->eff_obj[i].clact );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L���L�����C������
 *
 *	@param	p_work ���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Main( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		NMixGameDemo_HosiKiraKiraObjMain( &p_work->eff_obj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L���L���I�u�W�F�N�g���o��
 *
 *	@param	p_work	���[�N
 *	@param	x		�����W
 *	@param	y		�����W
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Add( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int x, int y )
{
	NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj;
	u32 rota;
	fx32 e_x, e_y;
	fx32 ss_x, ss_y;
	int i;


	// �o�^���W�Ȃǂ����߂�
	rota = FX_Atan2Idx( x - NMIX_SOOP_ROTA_CX, y - NMIX_SOOP_ROTA_CY );

	// ��]�ʒu����ړ����������߂�
	e_x = FX_Mul( FX_CosIdx( rota ), NMIX_DEMO_HOSI_MOVE_DIST );
	e_y = FX_Mul( FX_SinIdx( rota ), NMIX_DEMO_HOSI_MOVE_DIST );
	ss_x = FX_Mul( FX_CosIdx( rota ), NMIX_DEMO_HOSI_MOVE_SS );
	ss_y = FX_Mul( FX_SinIdx( rota ), NMIX_DEMO_HOSI_MOVE_SS );

	// �󂢂Ă���I�u�W�F�擾
	p_obj = NMixGameDemo_HosiKirakiraCleanObj_Get( p_work );
	if( p_obj ){
		NMixGameDemo_HosiKirakiraObjAdd( p_obj, p_work->eff_count,
				x*FX32_ONE, y*FX32_ONE,
				(NMIX_SOOP_ROTA_CX*FX32_ONE) + e_x, 
				(NMIX_SOOP_ROTA_CY*FX32_ONE) + e_y, 
				ss_x, ss_y );
	}
	p_obj = NMixGameDemo_HosiKirakiraCleanObj_Get( p_work );
	if( p_obj ){
		NMixGameDemo_HosiKirakiraObjAdd( p_obj, p_work->eff_count,
				x*FX32_ONE, y*FX32_ONE,
				(NMIX_SOOP_ROTA_CX*FX32_ONE) - e_x, 
				(NMIX_SOOP_ROTA_CY*FX32_ONE) - e_y, 
				-ss_x, -ss_y );
	}

	// �G�t�F�N�g�J�E���g
	p_work->eff_count = (p_work->eff_count + 1) % p_work->comm_count;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�󂢂Ă���I�u�W�F�N�g�擾
 *
 *	@param	p_work	���[�N
 *
 *	@return	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_HOSI_KIRAKIRA_OBJ* NMixGameDemo_HosiKirakiraCleanObj_Get( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){

		if( p_work->eff_obj[i].move_flg == FALSE ){
			return &p_work->eff_obj[i];
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�������C��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKiraKiraObjMain( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj )
{
	BOOL result;

	if( p_obj->move_flg == FALSE  ){
		return ;
	}
	
	if( p_obj->move_end == FALSE ){
		// ��������
		p_obj->move_end = NMIX_DEMO_AddMoveMainFx( &p_obj->move_x );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_y );

		// ���W�ݒ�
		p_obj->matrix.x = p_obj->move_x.x;
		p_obj->matrix.y = p_obj->move_y.x;
		CLACT_SetMatrix( p_obj->clact, &p_obj->matrix );
	}

	if( p_obj->move_end == TRUE ){
		// �j��
		NMixGameDemo_HosiKiraKiraObjDel( p_obj );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�����j��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKiraKiraObjDel( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj )
{
	if( p_obj->move_flg == FALSE  ){
		return ;
	}
	// �A�N�^�[���\����
	CLACT_SetDrawFlag( p_obj->clact, FALSE );
	p_obj->move_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�o�^
 *
 *	@param	p_obj		�I�u�W�F�N�g
 *	@param	anm_idx		�A�j���C���f�b�N�X
 *	@param	x			�J�n�����W
 *	@param	y			�J�n�����W
 *	@param	e_x			�I�������W
 *	@param	e_y			�I�������W
 *	@param	ss_x		�����x��
 *	@param	ss_y		�����x��
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKirakiraObjAdd( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj, int anm_idx, fx32 x, fx32 y, fx32 e_x, fx32 e_y, fx32 ss_x, fx32 ss_y )
{
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_x,
			x, e_x, ss_x, NMIX_DEMO_HOSI_MOVE_SYNC );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_y,
			y, e_y, ss_y, NMIX_DEMO_HOSI_MOVE_SYNC );
	p_obj->matrix.x = x;
	p_obj->matrix.y = y;

	// �\��
	CLACT_SetDrawFlag( p_obj->clact, TRUE );
	// �A�j��
	CLACT_AnmChg( p_obj->clact, anm_idx );
	CLACT_AnmReStart( p_obj->clact );
	// AUTO�A�j��
	CLACT_SetAnmFlag( p_obj->clact, TRUE );
	// BG�D�揇��
	CLACT_BGPriorityChg( p_obj->clact, NMIX_DEMO_HOSI_BG_PRI );

	// �����J�n
	p_obj->move_flg = TRUE;
	p_obj->move_end = FALSE;
}


//-----------------------------------------------------------------------------
/**
 *			�|���g�\��
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�\��������
 *
 *	@param	p_work		���[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	poruto_type	�|���g�^�C�v
 *	@param	heapID		�q�[�v
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Init( NMIX_DEMO_PORUTO_DRAW* p_work, int x, int y, int poruto_type, int heapID )
{
	p_work->poruto_man = PoruOam_SysInit( heapID, 1, 1, PORUOAM_DRAW_MAIN, PORUOAM_CGXOFS_ADJUST );

	// �|���g�o�^
	p_work->p_obj = PoruOam_Add( p_work->poruto_man, poruto_type, x, y, 0, 0, 0, PORUOAM_VT_MAIN );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Delete( NMIX_DEMO_PORUTO_DRAW* p_work )
{
	PoruOam_Del( p_work->poruto_man, p_work->p_obj );
	PoruOam_SysRelease( p_work->poruto_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�`�揈��
 *
 *	@param	p_work ���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Draw( NMIX_DEMO_PORUTO_DRAW* p_work )
{
	PoruOam_DrawMain( p_work->poruto_man );
}


//-----------------------------------------------------------------------------
/**
 *			YES�@NO�@�E�B���h�E
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E�@������
 *
 *	@param	p_work			���[�N
 *	@param	comm_count		�ʐM����
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Init( NMIX_DEMO_YESNO_WND* p_work, int heap, GF_BGL_INI* p_bgl )
{
	p_work->yes_no = TOUCH_SW_AllocWork( heap );
	p_work->p_bgl = p_bgl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Delete( NMIX_DEMO_YESNO_WND* p_work )
{
	TOUCH_SW_FreeWork( p_work->yes_no );
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E�J�n
 *
 *	@param	p_work ���[�N
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Start( NMIX_DEMO_YESNO_WND* p_work )
{
	TOUCH_SW_PARAM param;

	param.p_bgl  = p_work->p_bgl;
	param.bg_frame = GF_BGL_FRAME2_M;
	param.char_offs = NMIX_MAINWIN_YESNO_BMP_COFS;
	param.pltt_offs = NMIX_MAINWIN_YESNO_PLT;
	param.x		= NMIX_MAINWIN_YESNO_WND_X;
	param.y		= NMIX_MAINWIN_YESNO_WND_Y;
	
	TOUCH_SW_Init( p_work->yes_no, &param );
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E���C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// �����Ȃ�
 *	@retval	TOUCH_SW_RET_YES	// �͂�
 *	@retval	TOUCH_SW_RET_NO		// ������
 */
//-----------------------------------------------------------------------------
u32 NMixGameDemo_YesNoWnd_Main( NMIX_DEMO_YESNO_WND* p_work )
{
	u32 ret;
	ret = TOUCH_SW_Main( p_work->yes_no );

	if( ret != TOUCH_SW_RET_NORMAL ){
		TOUCH_SW_Reset( p_work->yes_no );
	}
	return ret;
}

