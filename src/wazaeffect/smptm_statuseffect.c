//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		smptm_statuseffect.c
 *	@brief		�T���v���@�X�e�[�^�X�@�G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2005.12.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "system/lib_pack.h"
#include "battle/battle_common.h"

#include "wazatool.h"
#include "we_tool.h"

#define __SMPTM_STATUSEFFECT_H_GLOBAL
#include "smptm_statuseffect.h"

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

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�X�e�[�^�X�G�t�F�N�g�V�X�e��
//	
//=====================================
typedef struct {
	CATS_SYS_PTR	csp;	///< �Z���A�N�^�[�Ǘ�
	CATS_RES_PTR	crp;	///< ���\�[�X�f�[�^
	PALETTE_FADE_PTR pfd;	///< �p���b�g�t�F�[�h���[�N
	
	int				heap;
	int				status;			///< ���s�X�e�[�^�X�G�t�F�N�g
	SOFT_SPRITE*	ssp;	//< �\�t�g�E�F�A�X�v���C�g
	u8				client_type;///< �N���C�A���g�^�C�v
	BOOL*			p_end;			///< �I�����o�t���O

	BOOL			sub_call_flg;	///< �T�u�R�[���̏I���`�F�b�N�t���O
} SMPTM_SYS;
typedef void (*pSMPTM_Func)( SMPTM_SYS* p_smptm );


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void SMPTM_SysTcb( TCB_PTR tcb, void* work );

static void SMPTM_ClactInit( SMPTM_SYS* p_smptm, int set_num, int char_num, int pltt_num, int cell_num, int cellanm_num );
static void SMPTM_ClactDelete( SMPTM_SYS* p_smptm );

static void SMPTM_ClactResLoad( SMPTM_SYS* p_smptm, const char** cpp_path, int pltt_num, int id );


static void SMPTM_None( SMPTM_SYS* p_smptm );

// ����
static void SMPTM_NemuriMove( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriGraphicInit( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriGraphicDelete( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work );
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int client_type );
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale );

// �X
static void SMPTM_KooriMove( SMPTM_SYS* p_smptm );
static void SMPTM_KooriGraphicInit( SMPTM_SYS* p_smptm );
static void SMPTM_KooriGraphicDelete( SMPTM_SYS* p_smptm );
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work );

//-------------------------------------
//	
//	�֐��e�[�u��
//	
//=====================================
const static pSMPTM_Func pSMPTM_SubCallFunc[] = {
	SMPTM_None,
	SMPTM_NemuriMove,
	SMPTM_None,
	SMPTM_NemuriMove,
	SMPTM_KooriMove,
	SMPTM_NemuriMove,
};

const static pSMPTM_Func pSMPTM_GraphicInitFunc[] = {
	SMPTM_None,
	SMPTM_NemuriGraphicInit,
	SMPTM_None,
	SMPTM_NemuriGraphicInit,
	SMPTM_KooriGraphicInit,
	SMPTM_NemuriGraphicInit,
};

const static pSMPTM_Func pSMPTM_GraphicDeleteFunc[] = {
	SMPTM_None,
	SMPTM_NemuriGraphicDelete,
	SMPTM_None,
	SMPTM_NemuriGraphicDelete,
	SMPTM_KooriGraphicDelete,
	SMPTM_NemuriGraphicDelete,
};

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�e�[�^�X�@�G�t�F�N�g�@�J�n
 *
 *	@param	status			�X�e�[�^�X
 *	@param	client_type		�N���C�A���g�^�C�v
 *	@param	p_end			�I���`�F�b�N�t���O
 *	@param	gra				�O���t�B�b�N�p�����[�^
 *	@param	heap			�g�p�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void STATUSEFF_SampStart( int status, int client_type, BOOL* p_end, const SMPTM_GRAPHIC_PARAM* cp_gra, int heap )
{
	SMPTM_SYS* wk;
//	GF_ASSERT( status <= STATUS_MAHI );

	wk = sys_AllocMemory( heap, sizeof(SMPTM_SYS) );	
	memset( wk, 0, sizeof(SMPTM_SYS) );

	wk->status		= status;
	wk->client_type	= client_type;
	wk->p_end		= p_end;
	*wk->p_end		= FALSE;
	wk->heap		= heap;
	wk->csp			= cp_gra->csp;
	wk->ssp			= cp_gra->ss;
	wk->pfd			= cp_gra->pfd;

	// �O���t�B�b�N�f�[�^�������֐��R�[��
	pSMPTM_GraphicInitFunc[ wk->status ]( wk );

	// �G�t�F�N�g�J�n�R�[��
	wk->sub_call_flg = TRUE;
	pSMPTM_SubCallFunc[ wk->status ]( wk );
	

	// �I�����m�^�X�N�o�^
	TCB_Add( SMPTM_SysTcb, wk, 64 );
}

static void SMPTM_SysTcb( TCB_PTR tcb, void* work )
{
	SMPTM_SYS* wk = work;

	if( wk->sub_call_flg == FALSE ){

		// �O���t�B�b�N�f�[�^�j��
		pSMPTM_GraphicDeleteFunc[ wk->status ]( wk );

		*wk->p_end = TRUE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[������
 *
 *	@param	p_smptm			�V�X�e�����[�N
 *	@param	set_num			�A�N�^�[�ő吔
 *	@param	char_num		�L�����N�^��
 *	@param	pltt_num		�p���b�g��
 *	@param	cell_num		�Z����
 *	@param	cellanm_num		�Z���A�j����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactInit( SMPTM_SYS* p_smptm, int set_num, int char_num, int pltt_num, int cell_num, int cellanm_num )
{
	TCATS_RESOURCE_NUM_LIST res_man_ini;
	
	// �V�X�e�����[�N�쐬
	p_smptm->crp = CATS_ResourceCreate( p_smptm->csp );
	// �Z���A�N�^�[�Z�b�g�쐬
	CATS_ClactSetInit( p_smptm->csp, p_smptm->crp, set_num );
		
	// ���\�[�X�}�l�[�W���쐬
	res_man_ini.resource_num.char_num = char_num;
	res_man_ini.resource_num.pltt_num = pltt_num;
	res_man_ini.resource_num.cell_num = cell_num;
	res_man_ini.resource_num.cell_anm_num = cellanm_num;
	res_man_ini.resource_num.mcell_num = 0;
	res_man_ini.resource_num.mcell_anm_num = 0;
	CATS_ResourceManagerInit( p_smptm->csp, p_smptm->crp, &res_man_ini );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[���\�[�X�ǂݍ���
 *
 *	@param	p_smptm			���[�N
 *	@param	cpp_path		�p�X�̃e�[�u��	(char pltt cell cellanm)
 *	@param	pltt_num		�p���b�g��	�ǂݍ��݂���
 *	@param	id				�Ǘ�ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactResLoad( SMPTM_SYS* p_smptm, const char** cpp_path, int pltt_num, int id )
{
	// �L�����N�^�ǂݍ���
	CATS_LoadResourceChar(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[0],
			NNS_G2D_VRAM_TYPE_2DMAIN,
			id
			);

	// �p���b�g�ǂݍ���
	CATS_LoadResourcePlttWork(
			p_smptm->pfd,
			FADE_MAIN_OBJ,
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[1],
			pltt_num,
			NNS_G2D_VRAM_TYPE_2DMAIN,
			id
			);

	// �Z���ǂݍ���
	CATS_LoadResourceCell(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[2],
			id
			);

	// �Z���A�j���ǂݍ���
	CATS_LoadResourceCellAnm(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[3],
			id
			);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_smptm		�G�t�F�N�g���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactDelete( SMPTM_SYS* p_smptm )
{
	CATS_ResourceDestructor_S(p_smptm->csp, p_smptm->crp);
	p_smptm->crp = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����Ȃ��G�t�F�N�g
 *
 *	@param	p_smptm	�X�e�[�^�X�G�t�F�N�g���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_None( SMPTM_SYS* p_smptm )
{
	p_smptm->sub_call_flg = FALSE;
}


//-----------------------------------------------------------------------------
/**
 *
 *			����G�t�F�N�g
 * 
 */
//-----------------------------------------------------------------------------

#define NEMURI_SET_NUM	(2)
#define NEMURI_CHAR_NUM	(1)
#define NEMURI_PLTT_NUM	(1)
#define NEMURI_CELL_NUM	(1)
#define NEMURI_CELLANM_NUM	(1)
#define NEMURI_LOAD_PLTT	(1)
#define NEMURI_RES_ID		(0)

#define NEMURI_EFF_SYNC	( 32 )
#define NEMURI_MOVE_H	( -32 )
#define NEMURI_MOVE_W	( 16 )

#define NEMURI_SCALE_S	( 2 )
#define NEMURI_SCALE_D	( 10 )
#define NEMURI_SCALE_E	( 10 )

#define NEMURI_1_WAIT	( 8 )


const static char* pNemuriPath[] = {
	"data/smptm_nemuri.NCGR",
	"data/smptm_nemuri.NCLR",
	"data/smptm_nemuri.NCER",
	"data/smptm_nemuri.NANR",
};


enum{
	NEMURI_SEQ_0_START,
	NEMURI_SEQ_1_WAIT,
	NEMURI_SEQ_1_START,
	NEMURI_SEQ_END_WAIT,
	NEMURI_SEQ_END,
};

typedef struct{
	SMPTM_SYS* p_smptm;
	int seq;
	int wait;

	// ����f�[�^
	CATS_ACT_PTR		cap[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_move[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_scale[ NEMURI_SET_NUM ];
} SMPTM_NEMURI_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�߂ނ�G�t�F�N�g
 *
 *	@param	p_smptm	�X�e�[�^�X�G�t�F�N�g���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriMove( SMPTM_SYS* p_smptm )
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	SMPTM_NEMURI_SYS* wk;
	int i;

	
	wk = sys_AllocMemory( p_smptm->heap, sizeof(SMPTM_NEMURI_SYS) );
	memset( wk, 0, sizeof(SMPTM_NEMURI_SYS) );
	memset( &coap, 0, sizeof(TCATS_OBJECT_ADD_PARAM_S) );

	wk->p_smptm = p_smptm;

	// ����Z���A�N�^�[�̓o�^���s��
	coap.x = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_X );
	coap.y = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_Y );
	coap.z = 0;
	coap.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;
	coap.id[ 4 ] = CLACT_U_HEADER_DATA_NONE;
	coap.id[ 5 ] = CLACT_U_HEADER_DATA_NONE;

	for( i=0; i<NEMURI_SET_NUM; i++ ){
		wk->cap[i] = CATS_ObjectAdd_S( p_smptm->csp, p_smptm->crp, &coap );
		CATS_ObjectEnableCap( wk->cap[i], FALSE );
	}

	// �^�X�N�o�^
	TCB_Add( SMPTM_NemuriTcb, wk, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����O���t�B�b�N�f�[�^�쐬
 *	
 *	@param	p_smptm	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriGraphicInit( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactInit( p_smptm, NEMURI_SET_NUM, NEMURI_CHAR_NUM, NEMURI_PLTT_NUM, NEMURI_CELL_NUM, NEMURI_CELLANM_NUM );

	SMPTM_ClactResLoad( p_smptm, pNemuriPath, NEMURI_LOAD_PLTT, NEMURI_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����O���t�B�b�N�f�[�^�j��
 *
 *	@param	p_smptm 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriGraphicDelete( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactDelete( p_smptm );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����TCB
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work )
{
	SMPTM_NEMURI_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case NEMURI_SEQ_0_START:
		NemuriObjStart( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0], wk->p_smptm->client_type );
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		wk->seq++;
		wk->wait = NEMURI_1_WAIT;
		break;
		
	case NEMURI_SEQ_1_WAIT:
		wk->wait --;
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		
	case NEMURI_SEQ_1_START:
		NemuriObjStart( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1], wk->p_smptm->client_type );
		NemuriObjMove( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1] );
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		

		wk->seq++;
		break;
		
	case NEMURI_SEQ_END_WAIT:
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		if( NemuriObjMove( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1] ) ){
			wk->seq++;
		}
		break;
		
	case NEMURI_SEQ_END:
		for( i=0; i<NEMURI_SET_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		// �I��
		wk->p_smptm->sub_call_flg = FALSE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
		return;
	}

	CATS_Draw(wk->p_smptm->crp);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����G�t�F�N�g�J�n
 *
 *	@param	cap			�A�N�^�[
 *	@param	p_move		�ړ��f�[�^�i�[��
 *	@param	p_scale		�g�k�f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int client_type )
{
	int vec_x;
	s16 cap_x, cap_y;
	
	// �\�����{�p�A�t�B��
	CATS_ObjectAffineSetCap( cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectEnableCap( cap, TRUE );

	CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

	
	switch(client_type){
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		vec_x = 1;
		break;
	
	case CLIENT_TYPE_BB:
	case CLIENT_TYPE_B:
	case CLIENT_TYPE_D:
		vec_x = -1;
		break;
	}

	// �����ړ��ݒ�
	WazaTool_InitStraightSyncFx( 
			p_move,
			cap_x, cap_x + (NEMURI_MOVE_W * vec_x),
			cap_y, cap_y + (NEMURI_MOVE_H),
			NEMURI_EFF_SYNC
			);

	// �g�k
	WazaTool_InitScaleRate(
			p_scale,
			NEMURI_SCALE_S,
			NEMURI_SCALE_D,
			NEMURI_SCALE_E,
			NEMURI_EFF_SYNC
			);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����I�u�W�F�N�g����
 *
 *	@param	cap			�A�N�^�[
 *	@param	p_move		�ړ�����
 *	@param	p_scale		�g�k
 *
 *	@retval	TRUE	
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale )
{
	BOOL check;

	// ���씽�f��
	WazaTool_CalcAndReflectStraightFxCap( p_move, cap );
	check = WazaTool_CalcAndReflectScaleRateCap( p_scale, cap );

	if( check ){
		return FALSE;
	}

	// �\��OFF
	CATS_ObjectEnableCap( cap, FALSE );
	return TRUE;
}


//-----------------------------------------------------------------------------
/**
 *
 *				������
 * 
 */
//-----------------------------------------------------------------------------

#define KOORI_SET_NUM	(1)
#define KOORI_CHAR_NUM	(1)
#define KOORI_PLTT_NUM	(1)
#define KOORI_CELL_NUM	(1)
#define KOORI_CELLANM_NUM	(1)
#define KOORI_LOAD_PLTT		(3)
#define KOORI_RES_ID		(0)

#define KOORI_ALPHA_S	( 0 )
#define KOORI_ALPHA_E	( 16 )
#define KOORI_ALPHA_DEF	( 20 )
#define KOORI_ALPHAIN_SYNC	( 10 )
#define KOORI_ALPHAOUT_SYNC	( 8 )

const static char* pKooriPath[] = {
	"data/smptm_koori.NCGR",
	"data/smptm_koori.NCLR",
	"data/smptm_koori.NCER",
	"data/smptm_koori.NANR",
};


enum{
	KOORI_SEQ_ALPHAIN_START,
	KOORI_SEQ_ALPHAIN,
	KOORI_SEQ_ANM,
	KOORI_SEQ_ALPHAOUT,
	KOORI_SEQ_END,
};

typedef struct{
	SMPTM_SYS* p_smptm;
	int seq;
	int plt_no;

	// ����f�[�^
	CATS_ACT_PTR		cap;
	WAZATOOL_ALPHA_FADE	cap_alpha;
} SMPTM_KOORI_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�G�t�F�N�g�^�X�N�o�^
 *
 *	@param	p_smptm 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriMove( SMPTM_SYS* p_smptm )
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	SMPTM_KOORI_SYS* wk;

	
	wk = sys_AllocMemory( p_smptm->heap, sizeof(SMPTM_KOORI_SYS) );
	memset( wk, 0, sizeof(SMPTM_KOORI_SYS) );
	memset( &coap, 0, sizeof(TCATS_OBJECT_ADD_PARAM_S) );

	wk->p_smptm = p_smptm;

	// ����Z���A�N�^�[�̓o�^���s��
	coap.x = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_X );
	coap.y = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_Y );
	coap.z = 0;
	coap.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;
	coap.id[ 4 ] = CLACT_U_HEADER_DATA_NONE;
	coap.id[ 5 ] = CLACT_U_HEADER_DATA_NONE;

	wk->cap = CATS_ObjectAdd_S( p_smptm->csp, p_smptm->crp, &coap );
	CATS_ObjectEnableCap( wk->cap, FALSE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );

	wk->plt_no = CATS_ObjectPaletteOffsetGetCap( wk->cap );

	// �^�X�N�o�^
	TCB_Add( SMPTM_KooriTcb, wk, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�O���t�B�b�N�f�[�^������
 *
 *	@param	p_smptm		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriGraphicInit( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactInit( p_smptm, KOORI_SET_NUM, KOORI_CHAR_NUM, KOORI_PLTT_NUM, KOORI_CELL_NUM, KOORI_CELLANM_NUM );

	SMPTM_ClactResLoad( p_smptm, pKooriPath, KOORI_LOAD_PLTT, KOORI_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�O���t�B�b�N�f�[�^�j��
 *
 *	@param	p_smptm		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriGraphicDelete( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactDelete( p_smptm );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X����^�X�N
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work )
{
	SMPTM_KOORI_SYS* wk = work;
	int frame;

	switch( wk->seq ){
	case KOORI_SEQ_ALPHAIN_START:
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				KOORI_ALPHA_S, KOORI_ALPHA_E,
				KOORI_ALPHA_DEF - KOORI_ALPHA_S, KOORI_ALPHA_DEF - KOORI_ALPHA_E,
				KOORI_ALPHAIN_SYNC
				);
		CATS_ObjectEnableCap( wk->cap, TRUE );

		// �����͌�ŃR���e�X�g�p�ɂ���K�v������
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
				( 1 << BATTLE_BGNO_BACKGROUND ) | GX_BLEND_PLANEMASK_BG0,
				KOORI_ALPHA_S, KOORI_ALPHA_DEF - KOORI_ALPHA_S);	

		wk->seq++;
		break;
		
	case KOORI_SEQ_ALPHAIN:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;

			CATS_ObjectAutoAnimeSetCap( wk->cap, CATS_ANM_AUTO_ON );
			CATS_ObjectAutoAnimeSpeedSetCap( wk->cap, FX32_ONE );
		}
		break;
		
	case KOORI_SEQ_ANM:
		// �����Ńp���b�g�i���o�[��ݒ肷��
		frame = CATS_ObjectAnimeFrameGetCap( wk->cap );
		frame %= 3;
		CATS_ObjectPaletteOffsetSetCap( wk->cap, wk->plt_no + frame );
		
		
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq++;

			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					KOORI_ALPHA_E, KOORI_ALPHA_S,
					KOORI_ALPHA_DEF - KOORI_ALPHA_E, KOORI_ALPHA_DEF - KOORI_ALPHA_S,
					KOORI_ALPHAOUT_SYNC
					);
		}
		break;
		
	case KOORI_SEQ_ALPHAOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;

			CATS_ObjectEnableCap( wk->cap, FALSE );
		}
		break;
		
	case KOORI_SEQ_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// �I��
		wk->p_smptm->sub_call_flg = FALSE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
		return;
	}

	CATS_Draw(wk->p_smptm->crp);
}


//-----------------------------------------------------------------------------
/**
 *
 *				��
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�œ���J�n�֐�
 *
 *	@param	p_smptm		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_DokuMove( SMPTM_SYS* p_smptm )
{
	
}


#if 0
// �f�o�b�O
typedef struct{
	WE_SYS_PTR we_sys;
	BOOL end;
} DEBUG_SMPTM_SYS;

static void Debug_smptmTcb( TCB_PTR tcb, void* work )
{
	DEBUG_SMPTM_SYS* wk = work;

	if( wk->end ){
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}
}

void Debug_SmpTm( WE_SYS_PTR we_sys )
{
	DEBUG_SMPTM_SYS* wk;
	SMPTM_GRAPHIC_PARAM gra;
	int i;
	
	wk = WET_ALLOC_MEMORY(we_sys, DEBUG_SMPTM_SYS);
	wk->we_sys = we_sys;
	
	gra.csp = WeSysCspGet(we_sys);
	gra.ss = WeSysSoftSpritePointerGet( we_sys, WeSysATNoGet(we_sys) );
	gra.pfd = WeSysPFDGet( we_sys );
	
	STATUSEFF_SampStart( STATUS_KOORI, 
			WeSysClientTypeGet(we_sys, WeSysATNoGet(we_sys)),
			&wk->end,
			&gra,
			WeSysHeapAreaGet(we_sys) );


	WEEffect_TCB_AddPriSet(wk->we_sys, Debug_smptmTcb, wk);
}
#endif

