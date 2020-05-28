//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		wsp_status.c
 *	@brief		�X�e�[�^�X�ُ�̃G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2005.12.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

// -----------------------------------------
//
//	include
//
// -----------------------------------------
#include "common.h"				///< �K�{
#include "system/lib_pack.h"	///< �K�{
#include "we_def.h"
#include "west_sp.h"			///< �K�{
#include "wsp.h"			///< xxx.c�ɑ΂���xxx.h�͕K�{

#include "wazatool.h"			///< �Z�G�t�F�N�g�x���֐��S
#include "we_tool.h"			///< 

#include "system/arc_tool.h"				///< �A�[�J�C�u�p
#include "system/arc_util.h"				///< �A�[�J�C�u�p

#define __WSP_STATUS_H_GLOBAL

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

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// ����
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work );
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int vec_x );
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale );


// �X
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work );

// ��ł�
static void SMPTM_YakedoTcb( TCB_PTR tcb, void* work );
static BOOL SMPTM_MoveYakedoObj( CATS_ACT_PTR cap, int* count, int* wait );
static void SMPTM_InitYakedoObj( CATS_ACT_PTR cap, int* count, int* wait, int num, int vec_x);

// ������
static void Konran_TCB( TCB_PTR tcb, void* work );

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


enum{
	NEMURI_SEQ_0_START,
	NEMURI_SEQ_1_WAIT,
	NEMURI_SEQ_1_START,
	NEMURI_SEQ_END_WAIT,
	NEMURI_SEQ_END,
};

typedef struct{
	WE_SYS_PTR	we_sys;
	int seq;
	int wait;
	CATS_RES_PTR crp;
	int vec_x;

	// ����f�[�^
	CATS_ACT_PTR		cap[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_move[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_scale[ NEMURI_SET_NUM ];
} TWE_ST001_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�߂ނ�G�t�F�N�g
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_001(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	TWE_ST001_SYS* wk;
	int i;
	int client_no;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST001_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;

	client_no = WeSysATNoGet(we_sys);
	wk->vec_x = WazaTool_VecChangeX( we_sys, client_no );

	// ����Z���A�N�^�[�̓o�^���s��
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = GetWazaEffPos(we_sys, client_no, PM_X);
	coap.y = GetWazaEffPos(we_sys, client_no, PM_Y);

	for( i=0; i<NEMURI_SET_NUM; i++ ){
		if( i==0 ){
			wk->cap[i] = cap;
			CATS_ObjectPosSetCap( wk->cap[i], coap.x, coap.y );
		}else{
			wk->cap[i] = CATS_ObjectAdd_S( csp, crp, &coap );
		}
		CATS_ObjectEnableCap( wk->cap[i], FALSE );
		CATS_ObjectPriSetCap( wk->cap[i], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[i], WAZAEFF_ACT_BGPRI );
	}

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet( wk->we_sys, SMPTM_NemuriTcb, wk );
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
	TWE_ST001_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case NEMURI_SEQ_0_START:
		NemuriObjStart( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0], wk->vec_x );
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
		NemuriObjStart( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1], wk->vec_x );
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
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
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
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int vec_x )
{
	s16 cap_x, cap_y;
	
	// �\�����{�p�A�t�B��
	CATS_ObjectAffineSetCap( cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectEnableCap( cap, TRUE );

	CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

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


enum{
	KOORI_SEQ_ALPHAIN_START,
	KOORI_SEQ_ALPHAIN,
	KOORI_SEQ_ANM,
	KOORI_SEQ_ALPHAOUT,
	KOORI_SEQ_END,
};

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int plt_no;
	CATS_RES_PTR crp;

	// ����f�[�^
	CATS_ACT_PTR		cap;
	WAZATOOL_ALPHA_FADE	cap_alpha;
} TWE_ST004_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�G�t�F�N�g�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_004(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_ST004_SYS* wk;
	int client_no;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST004_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;

	wk->cap = cap;
	CATS_ObjectEnableCap( wk->cap, FALSE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );

	wk->plt_no = CATS_ObjectPaletteOffsetGetCap( wk->cap );

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet( wk->we_sys,SMPTM_KooriTcb, wk );
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
	TWE_ST004_SYS* wk = work;
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

		WET_DefaultBlendSet(wk->we_sys,
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
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
}

//-----------------------------------------------------------------------------
/**
 *
 *			�₯��
 * 
 */
//-----------------------------------------------------------------------------
#define YAKEDO_OBJ_NUM			( 6 )		// ��ǂ̂̃I�u�W�F�N�g��
#define YAKEDO_OBJ_ONEGRA_NUM	( 2 )		// �����G�̃I�u�W�F��
#define YAKEDO_OBJ_ADD_WAIT		( 2 )		// �I�u�W�F�o�^�҂�
#define YAKEDO_OBJ_DRAW_SYNC	( 16 )		// �\���V���N

#define YAKEDO_OBJ_MAT_OFS_X	( 40 )
#define YAKEDO_OBJ_MAT_DIS_X	( -12 )
#define YAKEDO_OBJ_MAT_OFS_Y	( 40 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	CATS_RES_PTR crp;

	// ����f�[�^
	CATS_ACT_PTR		cap[YAKEDO_OBJ_NUM];
	int					cap_count[YAKEDO_OBJ_NUM];
	int					cap_wait[YAKEDO_OBJ_NUM];
} TWE_ST003_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�₯�ǃG�t�F�N�g�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_003(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	TWE_ST003_SYS* wk;
	int client_no;
	int i;
	int vec_x;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST003_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;


	client_no = WeSysATNoGet(wk->we_sys);
	vec_x = WazaTool_VecChangeX( we_sys, client_no );
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = GetWazaEffPos(we_sys, client_no, PM_X);
	coap.y = GetWazaEffPos(we_sys, client_no, PM_Y);

	// �A�N�^�[�̕\���D�揇�ʐ���̂��߃J�E���^���ŏI����s��
	for( i=YAKEDO_OBJ_NUM - 1; i>=0; i-- ){
		if( i==YAKEDO_OBJ_NUM - 1 ){
			wk->cap[i] = cap;
			CATS_ObjectPosSetCap( cap, coap.x, coap.y );
		}else{
			wk->cap[i] = CATS_ObjectAdd_S( csp, crp, &coap );
		}
		CATS_ObjectPriSetCap( wk->cap[i], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[i], WAZAEFF_ACT_BGPRI );
		CATS_ObjectEnableCap( wk->cap[i], FALSE );

		// �A�j���f�[�^������
		SMPTM_InitYakedoObj( wk->cap[i], &wk->cap_count[i], &wk->cap_wait[i], i, vec_x );
	}

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet( wk->we_sys,SMPTM_YakedoTcb, wk );
}

static void SMPTM_InitYakedoObj( CATS_ACT_PTR cap, int* count, int* wait, int num, int vec_x )
{
	s16 x, y;
	
	// �G��ݒ�
	CATS_ObjectAnimeSeqSetCap( cap, num / YAKEDO_OBJ_ONEGRA_NUM );

	// wait
	*wait = num * YAKEDO_OBJ_ADD_WAIT;

	// count
	*count = YAKEDO_OBJ_DRAW_SYNC;

	// ���W
	CATS_ObjectPosGetCap( cap, &x, &y );
	x += (YAKEDO_OBJ_MAT_OFS_X + (YAKEDO_OBJ_MAT_DIS_X * num)) * vec_x;
	y += YAKEDO_OBJ_MAT_OFS_Y;
	CATS_ObjectPosSetCap( cap, x, y );
}

static BOOL SMPTM_MoveYakedoObj( CATS_ACT_PTR cap, int* count, int* wait )
{
	if( *wait > 0 ){
		(*wait) --;

		if( *wait == 0 ){
			CATS_ObjectEnableCap( cap, TRUE );
		}
		
	}else{

		if( *count > 0 ){
			(*count) --;
		}else{
			CATS_ObjectEnableCap( cap, FALSE );
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�₯�Ǔ���^�X�N
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_YakedoTcb( TCB_PTR tcb, void* work )
{
	TWE_ST003_SYS* wk = work;
	int i;
	BOOL check;

	switch( wk->seq ){
	case 0:
		for( i=0; i<YAKEDO_OBJ_NUM; i++ ){
			check = SMPTM_MoveYakedoObj( wk->cap[i], &wk->cap_count[i], &wk->cap_wait[i] );
		}
		if( check ){
			wk->seq++;
		}
		break;
		
	case 1:
		for( i=0; i<YAKEDO_OBJ_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
}


//-----------------------------------------------------------------------------
/**
 *
 *		������
 *
 */
//-----------------------------------------------------------------------------
enum{
	KONRAN_MOVE_START,
	KONRAN_FADE_IN,
	KONRAN_FADE_OUT_WAIT,
	KONRAN_FADE_OUT,
	KONRAN_END,
};


#define KONRAN_CAP_NUM			( 6 )	// ������������288.s��������
#define KONRAN_CAP_ROTA_S		( FX_GET_ROTA_NUM( 0 ) )
#define KONRAN_CAP_ROTA_E		( FX_GET_ROTA_NUM( 180 ) )
#define KONRAN_CAP_ROTA_SYNC		( 48 )
#define KONRAN_CAP_ROTA_WIDTH	( FX32_ONE*50 )
#define KONRAN_CAP_ALPHA_S		( 1 )
#define KONRAN_CAP_ALPHA_E		( 16 )
#define KONRAN_CAP_ALPHA_SYNC	( 10 )

#define KONRAN_CAP_ALPHAOUT_WAIT	( KONRAN_CAP_ROTA_SYNC - (KONRAN_CAP_ALPHA_SYNC*2) )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int vec_x;

	//������
	CATS_ACT_PTR cap[ KONRAN_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ KONRAN_CAP_NUM ];	// ���ړ�
	WAZATOOL_ALPHA_FADE cap_alpha;	// �A���t�@�ϊ�
	s16 cap_cx;
	s16 cap_cy;
} TKONRAN_SYS;

static void Konran_CapInit( TKONRAN_SYS* wk, int vec_x )
{
	int i;
	int rota_offs_one;

	rota_offs_one = FX_GET_ROTA_NUM( 360 ) / KONRAN_CAP_NUM;
	
	// �v�Z�f�[�^�쐬
	for( i=0; i<KONRAN_CAP_NUM; i++ ){
		WazaTool_InitRotaFx(
				&wk->cap_move[ i ],
				KONRAN_CAP_ROTA_S,
				KONRAN_CAP_ROTA_E,
				0,0,
				KONRAN_CAP_ROTA_WIDTH, 0,
				KONRAN_CAP_ROTA_SYNC
				);
		wk->cap_move[i].work[1] += (rota_offs_one*i);
		wk->cap_move[i].work[5] *= vec_x;
	}

}

static void Konran_CapMove( TKONRAN_SYS* wk )
{
	int i;
	u16 rota;

	for( i=0; i<KONRAN_CAP_NUM; i++ ){
		
		// �v�Z
		WazaTool_CalcRotaFx( &wk->cap_move[ i ] );
		
		// ���f
		CATS_ObjectPosSetCap( wk->cap[ i ],
				wk->cap_cx + wk->cap_move[ i ].x,
				wk->cap_cy );

		// �p�x��BG�D�揇�ʂ�ς���
		if( (wk->cap_move[ i ].work[ 1 ] >= FX_GET_ROTA_NUM(90)) &&
			(wk->cap_move[ i ].work[ 1 ] <= FX_GET_ROTA_NUM(269)) ){
			
			CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		}else{

			CATS_ObjectBGPriSetCap( wk->cap[ i ], BT_3DPriorityGet(wk->we_sys)+1 );
		}//*/
	}
}

static void Konran_TCB( TCB_PTR tcb, void* work )
{
	TKONRAN_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case KONRAN_MOVE_START:
		// �A���t�@�ݒ�
		WET_DefaultBlendSet( wk->we_sys,
				KONRAN_CAP_ALPHA_S, 16 - KONRAN_CAP_ALPHA_S );
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				KONRAN_CAP_ALPHA_S, KONRAN_CAP_ALPHA_E,
				16 - KONRAN_CAP_ALPHA_S, 16 - KONRAN_CAP_ALPHA_E,
				KONRAN_CAP_ALPHA_SYNC
				);
		// �I�u�W�F
		Konran_CapInit( wk, wk->vec_x );
		Konran_CapMove( wk );
		wk->seq++;
		break;
		
	case KONRAN_FADE_IN:
		Konran_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			wk->wait = KONRAN_CAP_ALPHAOUT_WAIT;
		}
		break;
		
	case KONRAN_FADE_OUT_WAIT:
		Konran_CapMove( wk );
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					KONRAN_CAP_ALPHA_E, KONRAN_CAP_ALPHA_S, 
					16 - KONRAN_CAP_ALPHA_E, 16 - KONRAN_CAP_ALPHA_S, 
					KONRAN_CAP_ALPHA_SYNC
					);
		}
		break;
		
	case KONRAN_FADE_OUT:
		Konran_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;

	case KONRAN_END:
		for( i=0; i<KONRAN_CAP_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}

	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 * @brief	������p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_006(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TKONRAN_SYS* wk;
	int i;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TKONRAN_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �U����
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->cap_cx = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	wk->cap_cy = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// ������
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<KONRAN_CAP_NUM ; i++ ){
		if( i == 0 ){
			wk->cap[ i ] =  cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
		CATS_ObjectPriSetCap( wk->cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectObjModeSetCap( wk->cap[ i ], GX_OAM_MODE_XLU );
		CATS_ObjectAutoAnimeSetCap( wk->cap[ i ], TRUE );
	}
	
	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	WEEffect_TCB_AddPriSet(wk->we_sys, Konran_TCB, wk);
}
