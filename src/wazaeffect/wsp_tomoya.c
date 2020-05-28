//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		wsp_tomoya.c
 *	@brief		tomoya �̍쐬�����Z�G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2005.12.15
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
#include "wsp_sample.h"			///< xxx.c�ɑ΂���xxx.h�͕K�{
#include "wsp.h"			///< xxx.c�ɑ΂���xxx.h�͕K�{

#include "wazatool.h"			///< �Z�G�t�F�N�g�x���֐��S
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"				///< �A�[�J�C�u�p
#include "system/arc_util.h"				///< �A�[�J�C�u�p
#include "system/brightness.h"				///< �u���C�g�l�X
#include "system/wipe.h"

//-------------------------------------
//	
//	�ł񂱂�������
//	
//=====================================
#define WE098_OAM_MAX	(2)
#define WE098_ROTA_NUM	(1)		// ��]��
#define WE098_SYNC		(8)		// �V���N��
#define WE098_SYNC_ZAN	(10)	// �c���̃V���N��
#define WE098_DO_WAIT	(2)		// �c�����s�҂�
#define WE098_ALPHA_OAM	(26)	// OAM�Ɋ|���郿�l
#define WE098_ALPHA_BG	(5)		// BG�Ɋ|���郿�l
typedef struct{

	WE_SYS_PTR		we_sys;
	CATS_RES_PTR	crp;
	
	SOFT_SPRITE*		at_ssp;		// �U���|�P����
	WAZATOOL_CALCMOVE	at_wtc;		// �|�P��������f�[�^
	CATS_ACT_PTR		at_cap[ WE098_OAM_MAX ];	// �c��OAM�̃A�N�^�[�f�[�^
	WAZATOOL_ZANZOU		at_wtz;		// �c������f�[�^
	s16					at_pos_x;	// �|�P�����f�t�H���g���W
	s16					at_pos_y;	// �|�P�����f�t�H���g���W
	s16					cap_ofs_y;	// OAM�I�t�Z�b�gY

/*
	SOFT_SPRITE*		df_ssp;		// ����|�P����
	WAZATOOL_CALCMOVE	df_wtc;		// �|�P��������f�[�^
	s16					df_pos_x;	// �|�P�����f�t�H���g���W
	s16					df_pos_y;	// �|�P�����f�t�H���g���W
*/
} TWE_098_SYS;


//----------------------------------------------------------------------------
/**
 *	@brief	�ł񂱂�������	����TCB
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	�ł񂱂����������샏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We098_TCB(TCB_PTR tcb, void* work)
{
	TWE_098_SYS* wk = work;
	BOOL check[3];
	int i;		// ���[�v�p


	// ���삪���S�ɏI���܂ő҂��ďI��
	// ���암
	check[0] = WazaTool_CalcAndReflectRotaFxSsp( &wk->at_wtc, wk->at_pos_x, wk->at_pos_y, wk->at_ssp );
	check[1] = WazaTool_CalcZanzou( &wk->at_wtz );
//	check[2] = WazaTool_CalcAndReflectShakeSsp( &wk->df_wtc, wk->df_pos_x, wk->df_pos_y, wk->df_ssp );
	check[2] = FALSE;

	// �c��OAM�`��
	CATS_Draw(wk->crp);	

	// �I���`�F�b�N��
	for( i=0; i<3; i++ ){
		// �v�Z�r�������邩�`�F�b�N
		if( check[i] == TRUE ){
			// ���s
			return ;
		}
	}

	// �����W��ݒ�
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_pos_x );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_pos_y + (WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT) );
//	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_pos_x );
//	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_pos_y );


	// �I��
	WEEffect_TCB_Delete(wk->we_sys, tcb);
	sys_FreeMemoryEz(wk);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ł񂱂��������̎��s
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 * poke_oam�Ƀ|�P�����̊G���h���b�v���Ă����K�v������܂��@WE098_OAM_MAX
 *
 * we_sys����󂯎������Ȃ�
 *
 * OBJ	�w�i�A�R���ʂ̃A���t�@�u�����f�B���O���s���܂��B
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_098( WE_SYS_PTR we_sys )
{
	TWE_098_SYS* wk;
	int i;		// ���[�v�p
	int vec_x;
	WAZATOOL_CALCMOVE	at_zan_wtc;	// �c���|�P��������f�[�^
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_098_SYS));

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	
	// �|�P�����@�\�t�g�E�F�A�X�v���C�g�f�[�^�擾
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_pos_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_pos_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_SHADOW_HEIGHT );

/*	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_pos_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_pos_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );//*/
	// ���W����]��Y������ɕ␳
	wk->at_pos_y -= WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT;

	// �|�P�����@����f�[�^�쐬
	WazaTool_MakeDefRota( 
			&wk->at_wtc,
			WE098_ROTA_NUM, WE098_SYNC );

/*	WazaTool_InitShake( &wk->df_wtc,
			WE098_SHAKE_W_X,
			0,
			WE098_SHAKE_SYNC / WE098_SHAKE_NUM,
			WE098_SHAKE_NUM );//*/

	// �c������f�[�^�쐬
	WazaTool_MakeDefRota(
			&at_zan_wtc,
			WE098_ROTA_NUM, WE098_SYNC_ZAN );

	// �x�N�g�������킹��
	// �U����
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_wtc.work[2] *= vec_x;
	at_zan_wtc.work[2] *= vec_x;
	
	// �h�䑤
//	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
//	wk->df_wtc.x *= vec_x;

	// �c���f�[�^�擾
	for( i=0; i<WE098_OAM_MAX; i++ ){
		wk->at_cap[ i ] = WeSysPokeCapGet(wk->we_sys, i);
		CATS_ObjectPriSetCap( wk->at_cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->at_cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectObjModeSetCap(wk->at_cap[i], GX_OAM_MODE_XLU);
	}

	WazaTool_InitZanzou( &wk->at_wtz, &at_zan_wtc, WazaTool_CalcRotaFx,
			wk->at_pos_x, wk->at_pos_y - wk->cap_ofs_y,
			WE098_DO_WAIT,WE098_OAM_MAX, WAZATOOL_ZANZOU_TYPE_MATRIX, 
			wk->at_cap[0], wk->at_cap[1], NULL, NULL );


	// �c���̐F��ݒ�
	// �A���t�@���|����
	WET_DefaultBlendSet(wk->we_sys, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	
	WEEffect_TCB_AddPriSet(wk->we_sys, We098_TCB, wk);
}


//-------------------------------------
//	
//	�h���������΂�
//	
//=====================================
enum{
	WE065_AT_MOVE1,
	WE065_AT_ROTA1,
	WE065_AT_WAIT,
	WE065_AT_MOVE2,
	WE065_DF_MOVE,
	WE065_AT_ROTA2,
	WE065_END,
};
#define WE065_MOVE_WIDTH	(-32)
#define WE065_MOVE_SYNC		(3)
#define WE065_MOVE2_SYNC	(2)
#define WE065_SHAKE_WAIT	( 32 )
#define WE065_ROTA_DIS		(20)
#define WE065_ROTA1_SYNC	(8)
#define WE065_ROTA2_SYNC	(4)
#define WE065_MOVE_WAIT		(2)
typedef struct{

	WE_SYS_PTR		we_sys;
	
	int						seq;		// �V�[�P���X
	s16						wait;		// �E�F�C�g
	SOFT_SPRITE*			at_ssp;		// �U���|�P����
	WAZATOOL_CALCMOVE		at_wtc;		// �|�P��������f�[�^
	WAZATOOL_CALCMOVE_ONE	at_wtc_r;	// �|�P��������f�[�^��]
	s16						at_pos_x;	// �|�P�����f�t�H���g���W
	s16						at_pos_y;	// �|�P�����f�t�H���g���W

/*	
	SOFT_SPRITE*		df_ssp;		// ����|�P����
	WAZATOOL_CALCMOVE	df_wtc;		// �|�P��������f�[�^
	s16					df_pos_x;	// �|�P�����f�t�H���g���W
	s16					df_pos_y;	// �|�P�����f�t�H���g���W
*/
} TWE_065_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	�h���������΂�	����TCB
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	�h���������΂����샏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We065_TCB(TCB_PTR tcb, void* work)
{
	TWE_065_SYS* wk = work;
	
	switch( wk->seq ){
	case WE065_AT_MOVE1:
		if( WazaTool_CalcStraightFx( &wk->at_wtc ) ){
			WazaTool_SetSspMatrix( &wk->at_wtc, wk->at_ssp, wk->at_pos_x, wk->at_pos_y );
		}else{
			WazaTool_InitStraightSyncFx( &wk->at_wtc, wk->at_wtc.x, 0, 0, 0, WE065_MOVE2_SYNC );
			wk->seq ++;
		}
		break;

	case WE065_AT_ROTA1:
		if( WazaTool_CalcMoveOne( &wk->at_wtc_r ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->at_wtc_r.num );
		}else{
			WazaTool_InitMoveOneSync( &wk->at_wtc_r, wk->at_wtc_r.num, 0, WE065_ROTA2_SYNC );
			wk->seq ++;
			wk->wait = WE065_MOVE_WAIT;
		}
		break;

	case WE065_AT_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;

	case WE065_AT_MOVE2:
		if( WazaTool_CalcStraightFx( &wk->at_wtc ) ){
			WazaTool_SetSspMatrix( &wk->at_wtc, wk->at_ssp, wk->at_pos_x, wk->at_pos_y );
		}else{
			wk->seq ++;
			wk->wait = WE065_SHAKE_WAIT;
		}
		break;
		
	case WE065_DF_MOVE:
/*		if( WazaTool_CalcAndReflectShakeSsp( &wk->df_wtc, wk->df_pos_x, wk->df_pos_y, wk->df_ssp ) == FALSE ){
			wk->seq ++;
		}//*/

		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		
	case WE065_AT_ROTA2:
		if( WazaTool_CalcMoveOne( &wk->at_wtc_r ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->at_wtc_r.num );
		}else{
			wk->seq ++;
		}
		break;

	case WE065_END:			// �I��
		// �����W��ݒ�
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_pos_x );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_pos_y );

		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, 0 );
/*		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_pos_x );
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_pos_y );//*/

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�h���������΂��̎��s
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 * we_sys����󂯎������Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_065( WE_SYS_PTR we_sys )
{
	TWE_065_SYS* wk;
	int i;		// ���[�v�p
	int vec_x;
	int vec_x_df;
	
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_098_SYS));

	wk->we_sys	= we_sys;
	wk->seq = 0;	

	// �|�P�����@�\�t�g�E�F�A�X�v���C�g�f�[�^�擾
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_pos_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_pos_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

/*	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_pos_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_pos_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );//*/

	// �|�P�����@����f�[�^�쐬
	WazaTool_InitStraightSyncFx( &wk->at_wtc, 0, WE065_MOVE_WIDTH, 0, 0, WE065_MOVE_SYNC );
	WazaTool_InitMoveOneSync( &wk->at_wtc_r, 0, FX_GET_ROTA_NUM(WE065_ROTA_DIS), WE065_ROTA1_SYNC );
	
//	WazaTool_InitShake( &wk->df_wtc, WE065_SHAKE_WIDTH, 0, WE065_SHAKE_SYNC, WE065_SHAKE_NUM );
	

	// �x�N�g�������킹��
	// �U����
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_wtc.work[1] *= vec_x;
	wk->at_wtc_r.work[1] *= vec_x;

/*	// �h�䑤
	wk->df_wtc.x *= vec_x;//*/

	vec_x_df = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet(wk->we_sys) );

	// �U����]�ʒu�ݒ�
	{
		int ats = WET_SideCheck(we_sys, WeSysATNoGet(wk->we_sys));
		int dfs = WET_SideCheck(we_sys, WeSysDFNoGet(wk->we_sys));
		
		if (ats == SIDE_MINE &&	dfs == SIDE_MINE){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * -1);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
		else if (ats == SIDE_ENEMY && dfs == SIDE_ENEMY){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * +1);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
		else {		
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * vec_x_df);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We065_TCB, wk);
}

//-------------------------------------
//	
//	�X�v�[���܂�
//	
//=====================================
//�X�̃X�v�[���I�u�W�F�N�g�̓���V�[�P���X
enum{
	WE134_SPOON_OBJ_MOVE1,
	WE134_SPOON_OBJ_MOVE2,
	WE134_SPOOP_OBJ_END
};
//�S�̗̂���
enum{
	WE134_MATRIX_INIT,
	WE134_FADE_IN,
	WE134_FADE_IN_END,
	WE134_OBJ_MOVE,
	WE134_SPOON_CURVE,
	WE134_FADE_OUT,
	WE134_END
};

#define WE134_SPOON_NUM		(3)		// �c���{�{��
#define WE134_ZANZOU_NUM	(2)
#define WE134_ROTA1_S		( FX_GET_ROTA_NUM(90) )
#define WE134_ROTA1_E		( FX_GET_ROTA_NUM(270) )
#define WE134_ROTA2_E		( FX_GET_ROTA_NUM(180) )
#define WE134_ROTA_SP		( FX_GET_ROTA_NUM(10) )
#define WE134_ROTA_WIDHT	( -32 * FX32_ONE )
#define WE134_ROTA_HEIGHT	( -8 * FX32_ONE )
#define WE134_DO_WAIT		( 8 )
#define WE134_FADE_COUNT	( 10 )

#define WE134_ROTA_SP_S		( FX_GET_ROTA_NUM(0) )
#define WE134_ROTA_SP_E		( FX_GET_ROTA_NUM(360) )
#define WE134_ROTA_SP_W		( -1 * FX32_ONE )


// �X�̃X�v�[���\����
typedef struct {
	CATS_ACT_PTR	cap;
	WAZATOOL_CALCMOVE wtc;
	WAZATOOL_CALCMOVE_ONE add_sp;		// ��]�X�s�[�h�����x
	s16 def_sp_x;	// X������]�̃f�t�H���g�X�s�[�h
	s16	pos_x;
	s16 pos_y;
	int seq;
	BOOL do_flag;	// ���s�J�n�t���O
} TWE_134_SPOON;
// �X�v�[���܂��S�̃f�[�^
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	// spoon_obj
	TWE_134_SPOON	main;
	TWE_134_SPOON	sub[ WE134_ZANZOU_NUM ];
	int	seq;
	int wait;
	int count;
	int fade_count;
} TWE_134_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	�X�v�[���܂��@�c���I�u�W�F�̍쐬
 *
 *	@param	spoon		�X�v�[���c���I�u�W�F�f�[�^�i�[��
 *	@param	csp			clact_tool�V�X�e�����[�N
 *	@param	crp			clact_tool���\�[�X���[�N
 *	@param	cp_coap		�Z���A�N�^�[���
 *	@param	cp_parent	�e�X�v�[��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We_CAT_WE_134_ZanzouInit( TWE_134_SPOON* spoon, CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* cp_coap, const TWE_134_SPOON* cp_parent )
{
	//�X�v�[���A�b�h
	spoon->cap		= CATS_ObjectAdd_S(csp, crp, cp_coap);
	spoon->wtc		= cp_parent->wtc;
	spoon->add_sp	= cp_parent->add_sp;
	spoon->def_sp_x = cp_parent->def_sp_x;
	spoon->pos_x	= cp_parent->pos_x;
	spoon->pos_y	= cp_parent->pos_y;
	spoon->seq		= cp_parent->seq;
	spoon->do_flag	= FALSE;

	// �\��OFF
	CATS_ObjectEnableCap( spoon->cap, FALSE );

	CATS_ObjectPriSetCap( spoon->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( spoon->cap, WAZAEFF_ACT_BGPRI );
}

static void We_CAT_WE_134_ZanzouDelete( TWE_134_SPOON* spoon )
{
	//�X�v�[���j��
	CATS_ActorPointerDelete_S(spoon->cap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��ON/OFF�@�ݒ�
 *
 *	@param	spoon	�X�v�[���f�[�^
 *	@param	flag	�`��ON/OFF
 *
 *	@return	none
 *
 *	flag
 *		TRUE	�\��
 *		FALSE	��\��
 */
//-----------------------------------------------------------------------------
static void We_CAT_WE_134_SpoonDrawFlag( TWE_134_SPOON* spoon, BOOL flag )
{
	CATS_ObjectEnableCap( spoon->cap, flag );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v�[������
 *
 *	@param	spoon	�X�v�[�����[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL We134_SpoonMove( TWE_134_SPOON* spoon )
{
	if( spoon->do_flag == FALSE ){
		return TRUE;
	}
	
	switch( spoon->seq ){
	case WE134_SPOON_OBJ_MOVE1:
	case WE134_SPOON_OBJ_MOVE2:
		if( WazaTool_CalcRotaFx( &spoon->wtc ) ){
			// ����
			WazaTool_CalcCosOne( &spoon->add_sp );
			spoon->wtc.work[5] = spoon->def_sp_x + spoon->add_sp.num;

			CATS_ObjectPosSetCap( spoon->cap, 
					spoon->pos_x + spoon->wtc.x,
					spoon->pos_y + spoon->wtc.y	);
		}else{
			// MOVE2�ȊO�͎��̓���̏��������s��
			if( spoon->seq < WE134_SPOON_OBJ_MOVE2 ){
				// ��]�ړ�
				if( spoon->seq == WE134_SPOON_OBJ_MOVE1 ){
					WazaTool_InitRotaSpeedFx( &spoon->wtc,
							spoon->wtc.work[1], WE134_ROTA2_E,
							spoon->wtc.work[1], WE134_ROTA2_E,
							spoon->wtc.work[2], spoon->wtc.work[4],
							WE134_ROTA_SP );
				}
				// �ړ������x
				WazaTool_InitSinCosOneSyncFx( &spoon->add_sp,
						WE134_ROTA_SP_S, WE134_ROTA_SP_E,
						WE134_ROTA_SP_W, spoon->wtc.work[0]);
			}
			spoon->seq++;
		}
		break;

	case WE134_SPOOP_OBJ_END:
		return FALSE;
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�v�[���܂�	����TCB
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	�X�v�[���܂����샏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We134_TCB(TCB_PTR tcb, void* work)
{
	TWE_134_SYS* wk = work;
	int i;	// ���[�v�p
	BOOL check = FALSE;
	BOOL check_sub;
	
	switch( wk->seq ){
	case WE134_MATRIX_INIT:
		We134_SpoonMove( &wk->main );
		wk->seq++;
		break;
	case WE134_FADE_IN:
		wk->fade_count += WE134_FADE_COUNT;
		G2_ChangeBlendAlpha( (wk->fade_count / 10), 31 - (wk->fade_count / 10) );
		
		if( wk->fade_count >= 310 ){
			// ���C���I�u�W�F�̃I�u�W�F���[�h�𕁒ʂɂ���
			CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_NORMAL);

			wk->seq++;
		}
		break;

	case WE134_FADE_IN_END:
		// �c���̃��l�ɕύX
		G2_ChangeBlendAlpha( WET_DEFAULT_BLEND, WET_DEFAULT_BLEND );
		wk->seq++;
		break;

	case WE134_OBJ_MOVE:
		// ���s�J�n�`�F�b�N��
		if( wk->wait <= 0 ){
			wk->sub[ wk->count ].do_flag = TRUE;
			// �\��ON
			CATS_ObjectEnableCap( wk->sub[ wk->count ].cap, TRUE );
			
			wk->count ++;
			wk->wait = WE134_DO_WAIT;
		}
		if( wk->count < WE134_ZANZOU_NUM ){
			wk->wait --;
		}

		// ���암
		check = We134_SpoonMove( &wk->main );
		for( i=0; i<WE134_ZANZOU_NUM; i++ ){
			check_sub = We134_SpoonMove( &wk->sub[ i ] );

			// �c���͓��삪�I�������\��OFF
			if( check_sub == FALSE ){
				We_CAT_WE_134_SpoonDrawFlag( &wk->sub[ i ], FALSE );
			}
			check |= check_sub;
		}

		// �S����I��������I���
		if( check == FALSE ){
			wk->seq++;
		}
		break;

	case WE134_SPOON_CURVE:
		// �A�j���[�V����������
		CATS_ObjectUpdateCap( wk->main.cap );

		// �A�j���I���҂�
		if( CLACT_AnmActiveCheck( wk->main.cap->act ) == FALSE ){
			// ���C���I�u�W�F�𔼓����I�u�W�F���[�h�ɕύX
			CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_XLU);
			wk->seq ++;
		}
		break;

	case WE134_FADE_OUT:
		wk->fade_count -= WE134_FADE_COUNT;
		G2_ChangeBlendAlpha( (wk->fade_count / 10), 31 - (wk->fade_count / 10) );
		
		if( wk->fade_count <= 0 ){
			wk->seq++;
		}
		break;

	case WE134_END:
		// �c���f�[�^�j��
		for( i=0; i<WE134_ZANZOU_NUM; i++ ){
			We_CAT_WE_134_ZanzouDelete( &wk->sub[ i ] );			
		}

		// mainOAM�j��
		CATS_ActorPointerDelete_S(wk->main.cap);
		
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
 * @brief	�X�v�[���܂��p�^�X�N
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_134(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_134_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	int i;		// ���[�v�p
	int at_client;
	int width;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_134_SYS));

	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;
	wk->wait	= WE134_DO_WAIT;
	wk->count	= 0;
	wk->seq		= 0;

	// �|�P�����̔z�u������鉡����������
	at_client = WeSysATNoGet(we_sys); 
	width = WazaTool_VecChangeX( we_sys, at_client );
	width *= WE134_ROTA_WIDHT;

	// ���C���X�v�[���f�[�^�쐬
	wk->main.cap	= cap;
	wk->main.seq	= WE134_SPOON_OBJ_MOVE1;
	WazaTool_InitRotaSpeedFx( &wk->main.wtc, 
			WE134_ROTA1_S, WE134_ROTA1_E,
			WE134_ROTA1_S, WE134_ROTA1_E,
			width, WE134_ROTA_HEIGHT,
			WE134_ROTA_SP );
	WazaTool_InitSinCosOneSyncFx( &wk->main.add_sp,
			WE134_ROTA_SP_S, WE134_ROTA_SP_E,
			WE134_ROTA_SP_W, wk->main.wtc.work[0]);

	wk->main.def_sp_x = wk->main.wtc.work[5];
	wk->main.do_flag = TRUE;	// ���C���͂����Ȃ�ړ�
	// ���W�͍U������ݒ�
	wk->main.pos_x	= GetWazaEffPos(we_sys, at_client, PM_X);
	wk->main.pos_y	= GetWazaEffPos(we_sys, at_client, PM_Y);
	CATS_ObjectPosSetCap( wk->main.cap, wk->main.pos_x, wk->main.pos_y );
	CATS_ObjectPriSetCap( wk->main.cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->main.cap, WAZAEFF_ACT_BGPRI );
	
	// �T�u�X�v�[���f�[�^�쐬
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = wk->main.pos_x;
	coap.y = wk->main.pos_y;
	for( i=0; i<WE134_ZANZOU_NUM; i++ ){

		We_CAT_WE_134_ZanzouInit( 
				&wk->sub[ i ],			// �f�[�^�i�[��
				wk->csp, wk->crp,		// �Z���A�N�^�[�V�X�e��
				&coap,					// �Z���A�N�^�[�o�^�f�[�^
				&wk->main );			// �e�I�u�W�F
	}

	// �t�F�[�h�ݒ�
	wk->fade_count = 0;
	WET_DefaultBlendSet(wk->we_sys, 0, 31);
	CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_XLU);
	for( i=0; i<WE134_ZANZOU_NUM; i++ ){
		CATS_ObjectObjModeSetCap(wk->sub[ i ].cap, GX_OAM_MODE_XLU);
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We134_TCB, wk);
}


//-------------------------------------
//	
//	�˂�肫
//	
//=====================================
enum{
/*	WE093_AT_MOVE,
	WE093_WAIT,//*/
	WE093_DF_MOVE1,
	WE093_DF_MOVE2,
	WE093_END,
};
#define WE093_SHAKE_MOVE	(2)	// ���h�ꕝ
#define WE093_SHAKE_SYNC	(1)	
#define WE093_SHAKE_DFNUM	(6)

/*#define WE093_SHAKE_ATNUM	(2)
#define WE093_WAIT_NUM		(6)//*/

/*#define WE093_SCALE_WIDTH	(0.150f)
#define WE093_SCALE_HEIGHT	(0.30f)
#define WE093_Z_SCALE_MAX	(10.0f)//*/

#define WE093_Z_SCALE_D		( 10 )
#define WE093_Z_SCALE_XS	( 10 )
#define WE093_Z_SCALE_XE	( 12 )
#define WE093_Z_SCALE_YS	( 10 )
#define WE093_Z_SCALE_YE	( 15 )
#define WE093_Z_SCALE_OFS	( 0.10f )


#define WE093_Z_SCALE_ADD_SYNC	( 7 )
#define WE093_Z_SCALE_SUB_SYNC	( 4 )
//#define WE093_Z_ALPHA		(1)
//#define WE093_Z_BG_ALPHA	(16 - WE093_Z_ALPHA)//*/
#define WE093_Z_ALPHA		(28)
#define WE093_Z_BG_ALPHA	(15)
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;

	int seq;
	int wait;

/*	// �U��
	WAZATOOL_CALCMOVE at_wtc;
	SOFT_SPRITE*	at_ssp;
	s16	at_x;
	s16 at_y;//*/

	// �h��
	WAZATOOL_CALCMOVE df_wtc;
	WAZATOOL_CALCMOVE df_scale;
	CATS_ACT_PTR	df_cap;	// �c��OAM�̃A�N�^�[�f�[�^
	SOFT_SPRITE*	df_ssp;
	s16 df_x;
	s16 df_y;
	s16 s_ofs_switch;
	
	s16 cap_ofs_y;

} TWE_093_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	�h��|�P�����̍��W�@�g��l�ݒ�
 *
 *	@param	TWE_093_SYS* wk 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We093_DFPokeParamSet( TWE_093_SYS* wk )
{
	f32 scale_x, scale_y;

	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x + wk->df_wtc.x );
	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y + wk->df_wtc.y );
	CATS_ObjectPosSetCap( wk->df_cap, wk->df_x + wk->df_wtc.x, wk->df_y + wk->df_wtc.y - wk->cap_ofs_y );
	
	WazaTool_CalcScaleRateToClactScale( &wk->df_scale, &scale_x, &scale_y );
	scale_x += (f32)(wk->s_ofs_switch * WE093_Z_SCALE_OFS);
	CATS_ObjectScaleSetCap( wk->df_cap, scale_x, scale_y );

	wk->s_ofs_switch *= -1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O��TCB
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We093_TCB(TCB_PTR tcb, void* work)
{
	TWE_093_SYS* wk = work;
	BOOL check;
	
	switch( wk->seq ){
/*	case WE093_AT_MOVE:
		
		// poke���암
		if( WazaTool_CalcAndReflectShakeSsp( &wk->at_wtc, wk->at_x, wk->at_y, wk->at_ssp ) == FALSE ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			wk->seq++;
		}
		break;

	case WE093_WAIT:
		wk->wait++;
		if( wk->wait > WE093_WAIT_NUM ){
			wk->seq ++;
		}
		break;//*/

	case WE093_DF_MOVE1:	// �g��MAX�܂�
		WazaTool_CalcShake( &wk->df_wtc );
		check = WazaTool_CalcScaleRateEx( &wk->df_scale );

		// ���W�@�g��l�ݒ�
		We093_DFPokeParamSet( wk );
		
		if( check == FALSE ){
			// �g��v�Z
			WazaTool_InitScaleRateEx( &wk->df_scale,
					WE093_Z_SCALE_XE,WE093_Z_SCALE_XS, 
					WE093_Z_SCALE_YE,WE093_Z_SCALE_YS,
					WE093_Z_SCALE_D,
					WE093_Z_SCALE_SUB_SYNC);

			wk->seq++;
		}
		break;

	case WE093_DF_MOVE2:	// �k�������܂�
		WazaTool_CalcShake( &wk->df_wtc );
		check = WazaTool_CalcScaleRateEx( &wk->df_scale );

		// ���W�@�g��l�ݒ�
		We093_DFPokeParamSet( wk );
		
		if( check == FALSE ){
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );
			wk->seq++;
		}
		break;
		
	case WE093_END:

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;	
	}

	// �c��OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�˂�肫
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 * we_sys����󂯎������Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_093( WE_SYS_PTR we_sys )
{
	TWE_093_SYS* wk;

	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_093_SYS));

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	wk->seq		= 0;
	wk->wait	= 0;
	
	// �|�P�����@�\�t�g�E�F�A�X�v���C�g�f�[�^�擾
/*	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );//*/
	
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );

	wk->cap_ofs_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_SHADOW_HEIGHT );

	// �p���b�g�t�F�[�h
//	PaletteFadeReq();

	// �|�P�����@����f�[�^�쐬
//	WazaTool_InitShake( &wk->at_wtc, WE093_SHAKE_MOVE, 0, WE093_SHAKE_SYNC, WE093_SHAKE_ATNUM );
	WazaTool_InitShake( &wk->df_wtc, WE093_SHAKE_MOVE, 0, WE093_SHAKE_SYNC, WE093_SHAKE_DFNUM );

	// �c���f�[�^�쐬
	// �c���f�[�^�擾
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectObjModeSetCap(wk->df_cap, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap(wk->df_cap, CLACT_AFFINE_DOUBLE);
	CATS_ObjectPriSetCap( wk->df_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->df_cap, WAZAEFF_ACT_BGPRI );

	// �g��v�Z
	WazaTool_InitScaleRateEx( &wk->df_scale,
			WE093_Z_SCALE_XS, WE093_Z_SCALE_XE,
			WE093_Z_SCALE_YS, WE093_Z_SCALE_YE,
			WE093_Z_SCALE_D,
			WE093_Z_SCALE_ADD_SYNC);

	// �g�k�U�邦����̃X�C�b�`
	wk->s_ofs_switch = 1;

	// �������|����
	WET_DefaultBlendSet(wk->we_sys,
			WE093_Z_ALPHA, WE093_Z_BG_ALPHA);

	WEEffect_TCB_AddPriSet(wk->we_sys, We093_TCB, wk);
}


//-------------------------------------
//	
//	�Ƃ���
//	
//=====================================
enum{
	WE151_RASTER,
	WE151_FADE_OUT,
	WE151_FADE_WAIT,
	WE151_FADE_IN,
	WE151_END,
};
#define WE151_SIN_BUFF	(72)
#define WE151_ROTA_ADD	( FX_GET_ROTA_NUM(5) )
#define WE151_ROTA_WIDTH	(8*FX32_ONE)	// ���a

#define WE151_SCROLL_SP	(80)		// �P�ʂ͐���*100

#define WE151_MOVEY_END	(40)
#define WE151_MOVEX_END	(80)
#define WE151_MOVE_SYNC	(24)

#define WE151_ALPHA_FADE_SYNC	( 16 )

#define WE151_HEIGHT_ERR	(-8)	// ���̃T�C�Y���|�P�����̊G�̏�Ɖ����J�b�g

#define WE151_FADE_WAIT_NUM	(8)
typedef struct{
	WE_SYS_PTR	we_sys;
	int			seq;
	int			count;

	SOFT_SPRITE* at_ssp;
	s16			at_x;
	s16			at_y;

	s16		start;
	s16		end;
	
	// ���X�^�[�f�[�^
	WAZATOOL_SCRLASTER_PTR	lst;

	// �c���L�k��v�Z
	WAZATOOL_CALCMOVE	move_param;

	// �A���t�@�t�F�[�h
	WAZATOOL_ALPHA_FADE	alpha_fade;
} TWE_151_SYS;


static void We151_BuffClean( TWE_151_SYS* wk, void* buff )
{
	u32 num;
	
	// �o�b�t�@���������l�ŏ�����
	num = ((-wk->at_y & 0xffff) << 16) | (-wk->at_x & 0xffff);
	MI_CpuFill32( buff, num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[���암��
 *
 *	@param	wk	���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	�I��
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL We151_RasterMove( TWE_151_SYS* wk )
{
	u32* buff;
	int i;
	BOOL ret;
	s16 set_x, set_y;
	int in_buff;

	buff = WazaTool_GetScrLasterWriteBuff( wk->lst );
	// �o�b�t�@������
	We151_BuffClean( wk, buff );

	// �v�Z��
	// �c���L�k
	ret = WazaTool_CalcStraightFx( &wk->move_param );
	
	// �l�ݒ蕔
	// �c�L�k
	// �����s�ړ�
	for( i=wk->start; i<=wk->end; i++ ){
		set_x = buff[i] & 0xffff;
		set_y = buff[i] >> 16;

		// �c�L�k�ݒ�
		set_y -= ( (wk->end - i) * (wk->move_param.y) ) / 100;
		set_x -= ( ((wk->start + (SOFT_SPRITE_SIZE_Y/2)) - i) * (wk->move_param.x) ) / 100;

		// 1�O�̃o�b�t�@�ɓ���Ă���
		in_buff = i - 1;
		if( in_buff < 0 ){
			in_buff += 192;
		}
		// �ݒ�
		buff[in_buff] = WazaTool_GetLasterBuffMatrixData( set_x, set_y );
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ƃ���
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We151_TCB(TCB_PTR tcb, void* work)
{
	TWE_151_SYS* wk = work;

	switch( wk->seq ){
	case WE151_RASTER:
		if( We151_RasterMove( wk ) == FALSE ){
			wk->seq++;
			WET_DefaultBGEffectBlendSet( wk->we_sys, 31, 0 );
			// �A���t�@�t�F�[�h�o�^
			WazaTool_StartAlphaFade( &wk->alpha_fade,
					31, 0, 0, 31, WE151_ALPHA_FADE_SYNC);
		}
		break;
	
	case WE151_FADE_OUT:
		We151_RasterMove( wk );
		
		// �A���t�@�t�F�[�h�I���҂�
		if( WazaTool_EndCheckAlphaFade( &wk->alpha_fade ) ){
			wk->seq ++;
			
			// ���X�^�[�V�X�e���X�g�b�v
			WazaTool_StopScrLaster( wk->lst );
			wk->count = 0;
		}
		break;

	case WE151_FADE_WAIT:

		GF_BGL_ScrollSet(WeSysBGLPointerGet( wk->we_sys ), BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -wk->at_x);
		GF_BGL_ScrollSet(WeSysBGLPointerGet( wk->we_sys ), BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -wk->at_y);

		wk->count ++;
		if( wk->count > WE151_FADE_WAIT_NUM ){
			// �t�F�[�h�C���J�n
			WazaTool_StartAlphaFade( &wk->alpha_fade,
					0, 31, 31, 0, WE151_ALPHA_FADE_SYNC);
			wk->seq++;
		}
		break;

	case WE151_FADE_IN:
		// �A���t�@�t�F�[�h�I���҂�
		if( WazaTool_EndCheckAlphaFade( &wk->alpha_fade ) ){
			// �|�P�����\��
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, 0 );
		
			wk->seq++;
		}
		break;

	case WE151_END:

		// ���X�^�[�V�X�e���j��
		WazaTool_DeleteScrLaster( wk->lst );

		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );
		
		// �L�����N�^�f�[�^�N���A
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ƃ���
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_151( WE_SYS_PTR we_sys )
{
	TWE_151_SYS* wk;
	int vec_x;
	TCB_PTR tcb;
	int client_type;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_151_SYS));
	memset( wk, 0, sizeof(TWE_151_SYS) );

	wk->we_sys	= we_sys;

	// WE151�^�X�N�o�^
	tcb = WEEffect_TCB_AddPriSet(wk->we_sys, We151_TCB, wk);

	// �U�����|�P�����f�[�^�擾
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->at_y -= SoftSpriteParaGet(wk->at_ssp, SS_PARA_SHADOW_HEIGHT);

	// ������W�ɕύX
	wk->at_x -= SOFT_SPRITE_SIZE_X / 2;
	wk->at_y -= SOFT_SPRITE_SIZE_Y / 2;

	// �|�P������\��
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, 1 );

	// �x�N�g���𐮂���
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	wk->start	= wk->at_y + WE151_HEIGHT_ERR;
	wk->end		= wk->at_y + SOFT_SPRITE_SIZE_Y - WE151_HEIGHT_ERR;

	if( wk->start < 0 ){
		wk->start = 0;
	}
	if( wk->end > 192 ){
		wk->end = 192;
	}
	
	// ���X�^�[������
	wk->lst = WazaTool_InitScrLaster( 
			wk->start,					// �J�n
			wk->end,					// �I��
			WE151_ROTA_ADD,				// ��]�p�ύX�l
			WE151_ROTA_WIDTH * vec_x,	// ���a
			WE151_SCROLL_SP,			// �X�N���[���X�s�[�h
			BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT),	// BGNO
			TCB_GetPriority(tcb)+ 1,		// �^�X�N�D�揇��
			WazaTool_GetLasterBuffMatrixData( wk->at_x, wk->at_y ),
			WeSysHeapAreaGet(we_sys) );
	
	// �c���L�k��
	WazaTool_InitStraightSyncFx( &wk->move_param,
			0, WE151_MOVEX_END,
			0, WE151_MOVEY_END,
			WE151_MOVE_SYNC );

	// �c���L�k��
	wk->move_param.work[1] *= vec_x;	// �������̃x�N�g��

	// ���Ă�OBJ�̈ʒu�ɂ��BGpriority��ύX����
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysATNoGet(we_sys) );
	if( (client_type == CLIENT_TYPE_B) || (client_type == CLIENT_TYPE_C) ){
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
	}

	// 1��Ă�
	We151_TCB( tcb, wk );
}

//-------------------------------------
//	
//	�i�C�g�w�b�h
//	
//=====================================
enum{
	WE101_AT_POKE_SCALE_FADEIN,
	WE101_ATWAIT,
	WE101_AT_POKE_SCALE_DOWN,
	WE101_ATEND,
};

enum{
	WE101_DF_POKEBLACKOUT,
	WE101_DF_POKEBLACKIN,
	WE101_DF_END,
};

#define WE101_AT_SCALE_START	(14)
#define WE101_AT_SCALE_END		(10)
#define WE101_AT_SCALE_START_F	(WE101_AT_SCALE_START / (f32)WE101_AT_SCALE_END)
#define WE101_AT_SCALE_SYNC		(8)

#define WE101_AT_ALPHA_START	(0)
#define WE101_AT_ALPHA_END		(16)
#define WE101_AT_ALPHA_SYNC		(8)

#define WE101_AT_WAIT	( 32 )

#define WE101_DF_SHAKE_WIDTH	(4)
#define WE101_DF_SHAKE_SYNC		(1)
#define WE101_DF_SHAKE_NUM		(4)
#define WE101_DF_BLACK_FADE_WAIT	(0)
#define WE101_DF_BLACK_FADE_S		(0)
#define WE101_DF_BLACK_FADE_E		(16)
#define WE101_DF_BLACK_FADE_COL		(0)

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int			seq;
	int			count;
	
	// �U����CAT
	CATS_ACT_PTR			at_cap;
	WAZATOOL_CALCMOVE		at_scale;
	WAZATOOL_CALCMOVE_ONE	at_alpha;
	BOOL contest_x_flip;		// �R���e�X�g�̂Ƃ�TRUE
} TWE_101AT_SYS;

typedef struct {
	WE_SYS_PTR	we_sys;
	int			seq;
	
	// �h�䑤
	SOFT_SPRITE*		df_ssp;
	CATS_ACT_PTR		df_cap;
	BOOL				cap_move;
	WAZATOOL_CALCMOVE	df_shake;
	s16					df_x;
	s16					df_y;

	int					oam_y;
} TWE_101DF_SYS;



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�i�C�g�w�b�h
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We101AT_TCB(TCB_PTR tcb, void* work)
{
	TWE_101AT_SYS* wk = work;
	BOOL check;
	f32 s_x, s_y;

	switch( wk->seq ){
	case WE101_AT_POKE_SCALE_FADEIN:
		check = WazaTool_CalcMoveOneFx( &wk->at_alpha );
		G2_ChangeBlendAlpha( wk->at_alpha.num, 31 - wk->at_alpha.num );
		if( check == FALSE ){
			wk->seq++;
			wk->count = 0;
		}
		break;

	case WE101_ATWAIT:

		wk->count ++;
		if( wk->count > WE101_AT_WAIT ){
			wk->seq++;
		}
		break;
		
	case WE101_AT_POKE_SCALE_DOWN:
		check = WazaTool_CalcScaleRate( &wk->at_scale );

		WazaTool_CalcScaleRateToClactScale( &wk->at_scale, &s_x, &s_y );
		if( wk->contest_x_flip == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->at_cap, s_x, s_y );
//		check = WazaTool_CalcAndReflectScaleRateCap( &wk->at_scale, wk->at_cap );
		if( check == FALSE ){
			// �I�u�W�F�E�B���h�EOAM��\��
			CATS_ObjectEnableCap( wk->at_cap, FALSE );
			wk->seq++;
		}
		break;
		
	case WE101_ATEND:

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// �c��OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�i�C�g�w�b�h
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We101DF_TCB(TCB_PTR tcb, void* work)
{
	TWE_101DF_SYS* wk = work;
	BOOL check;

	switch( wk->seq ){
	case WE101_DF_POKEBLACKOUT:
		WazaTool_CalcShake( &wk->df_shake );
		WazaTool_SetSspMatrix( &wk->df_shake, wk->df_ssp, wk->df_x, wk->df_y );
		// �Qvs�Q�|�P�������Ԃ���̂���
		if( wk->cap_move == TRUE ){
			WazaTool_SetCapMatrix( &wk->df_shake, wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			// pal�t�F�[�h
			SoftSpritePalFadeSet( wk->df_ssp, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_COL );

			// �Qvs�Q�|�P�������Ԃ���̂���
			if( wk->cap_move == TRUE ){
				int plt_bit;

				// �p���b�g�t�F�[�h
				plt_bit = 1 << WazaTool_CapPlttNoGet( wk->df_cap );

				PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_OBJ, plt_bit, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_COL);
			}

			wk->seq++;
		}
		break;

	case WE101_DF_POKEBLACKIN:
		check = WazaTool_CalcShake( &wk->df_shake );
		WazaTool_SetSspMatrix( &wk->df_shake, wk->df_ssp, wk->df_x, wk->df_y );
		// �Qvs�Q�|�P�������Ԃ���̂���
		if( wk->cap_move == TRUE ){
			WazaTool_SetCapMatrix( &wk->df_shake, wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );

			// �QVS�Q�|�P�������Ԃ���̂���
			if( wk->cap_move == TRUE ){
				SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 0 );	// ssp��\��
				CATS_ObjectPosSetCap( wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
			}

			wk->seq++;
		}
		break;
		
	case WE101_DF_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�i�C�g�w�b�h
 
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_101AT( WE_SYS_PTR we_sys )
{
	TWE_101AT_SYS* wk;
	int vec_x;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_101AT_SYS));
	memset( wk, 0, sizeof(TWE_101AT_SYS) );

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);

	// �R���e�X�g���`�F�b�N
	wk->contest_x_flip = WES_ContestFlag_Get(we_sys);


	// �U�����f�[�^�쐬
	wk->at_cap = WeSysPokeCapGet(wk->we_sys, 0);
	// �g�k����
	WazaTool_InitScaleRate( &wk->at_scale, WE101_AT_SCALE_START, WE101_AT_SCALE_END, WE101_AT_SCALE_END, WE101_AT_SCALE_SYNC );
	// �A���t�@
	WazaTool_InitMoveOneSyncFx( &wk->at_alpha, WE101_AT_ALPHA_START, WE101_AT_ALPHA_END, WE101_AT_ALPHA_SYNC );
	// �A���t�@�ݒ�
	CATS_ObjectObjModeSetCap( wk->at_cap, GX_OAM_MODE_XLU );
	WET_DefaultBlendSet( wk->we_sys, 0, 31 );
	// �g�k�ݒ�
	CATS_ObjectAffineSetCap( wk->at_cap, CLACT_AFFINE_DOUBLE );
	
	if(wk->contest_x_flip == TRUE){
		CATS_ObjectScaleSetCap( wk->at_cap, -WE101_AT_SCALE_START_F, WE101_AT_SCALE_START_F );
	}else{
		CATS_ObjectScaleSetCap( wk->at_cap, WE101_AT_SCALE_START_F, WE101_AT_SCALE_START_F );
	}
	
	CATS_ObjectPriSetCap( wk->at_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->at_cap, WAZAEFF_ACT_BGPRI );

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet(wk->we_sys, We101AT_TCB, wk);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�i�C�g�w�b�h
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_101DF( WE_SYS_PTR we_sys )
{
	TWE_101DF_SYS* wk;
	int vec_x;
	int at_client;
	int df_client;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_101DF_SYS));
	memset( wk, 0, sizeof(TWE_101DF_SYS) );

	wk->we_sys	= we_sys;

	// �h�䑤�f�[�^�쐬
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	wk->oam_y = SoftSpriteParaGet(wk->df_ssp, SS_PARA_SHADOW_HEIGHT);
	// ���h��
	WazaTool_InitShake( &wk->df_shake, WE101_DF_SHAKE_WIDTH,0,WE101_DF_SHAKE_SYNC,WE101_DF_SHAKE_NUM );
		
	// �x�N�g�������킹��
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet( wk->we_sys ) );
	wk->df_shake.x += vec_x;

	// pal�t�F�[�h
	SoftSpritePalFadeSet( wk->df_ssp, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_COL );

	// Defense�}�X�N�p�Z��
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 1);

	at_client = WET_ClientTypeGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	df_client = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );

	// �U����A�Ŏ����C
	// �U����D�Ŏ����B
	// �̎�����SSP������CAP�����œ�������
	// �QVS�Q�|�P�������Ԃ���̂���
	if( ((at_client == CLIENT_TYPE_A) && (df_client == CLIENT_TYPE_C)) ||
		((at_client == CLIENT_TYPE_D) && (df_client == CLIENT_TYPE_B)) ){
		int plt_bit;
		// �p���b�g�t�F�[�h
		plt_bit = 1 << WazaTool_CapPlttNoGet( wk->df_cap );
		PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_OBJ, plt_bit, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_COL);
		wk->cap_move = TRUE;
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 1 );	// ssp��\��
	}

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet(wk->we_sys, We101DF_TCB, wk);
}

//-------------------------------------
//	
//	�����
//	
//=====================================
// ����|�P�����̕�
enum{
	WE180_INIT,
	WE180_MAIN,
	WE180_END,
};

// ���X�^�[�|�P�����̕�
enum{
	WE180_L_FADEIN,
	WE180_L_MAIN,
	WE180_L_FADE_OUT,
	WE180_L_END,
};

/*// �p���b�g�t�F�[�h
enum{
	WE180_P_FADEOUT_INIT,
	WE180_P_FADEOUT_MAIN,
	WE180_P_FADEIN_INIT,
	WE180_P_FADEIN_MAIN,
	WE180_P_FADE_END,
};//*/

#define WE180_ROTA_ADD		( FX_GET_ROTA_NUM(5) )
#define WE180_ROTA_WIDTH	( 5*FX32_ONE )
#define WE180_SCR_SP		(100)

#define WE180_FADEIN_ALPHA1_ST		( 0 )
#define WE180_FADEIN_ALPHA1_ED		( 8 )
#define WE180_FADEIN_ALPHA2_ST		( 16 )
#define WE180_FADEIN_ALPHA2_ED		( 8 )
#define WE180_FADEIN_ALPHA_SYNC		( 24 )
#define WE180_FADEOUT_ALPHA_SYNC	( 24 )//*/

#define WE180_LASTER_COUNT		(32)

/*#define WE180_PL_FADE_S			(0)
#define WE180_PL_FADE_E			(8)
#define WE180_PL_COLOR			( GX_RGB( 31,31,31 ) )
#define WE180_PL_WAIT			( 0 )
#define WE180_PL_COUNT			( 4 )//*/

typedef struct {
	WE_SYS_PTR	we_sys;
	int			seq;
	int			sub_seq;
	int			pl_fade_seq;

/*	// �U���p
	SOFT_SPRITE* at_ssp;	// ���点��X�v���C�g
	int at_pl_count;//*/
	
	// �h��p
	SOFT_SPRITE* df_ssp;
	WAZATOOL_SCRLASTER_PTR	lst;
	PALETTE_FADE_PTR	pfd;	// BG�̃p���b�g�t�F�[�h
	WAZATOOL_ALPHA_FADE alpha;	// �A���t�@�t�F�[�h
	int df_count;

	CATS_ACT_PTR		df_cap;
	
} TWE_180_SYS;

/*
static BOOL We180_PlFadeObj( TWE_180_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->pl_fade_seq ){
	case WE180_P_FADEOUT_INIT:
		SoftSpritePalFadeSet( wk->at_ssp, 
				WE180_PL_FADE_S, WE180_PL_FADE_E,
				WE180_PL_WAIT, WE180_PL_COLOR );
		wk->pl_fade_seq++;
		break;
		
	case WE180_P_FADEOUT_MAIN:
		if( SoftSpritePalFadeExist( wk->at_ssp ) == FALSE ){
			wk->pl_fade_seq++;
		}
		break;
		
	case WE180_P_FADEIN_INIT:
		SoftSpritePalFadeSet( wk->at_ssp, 
				WE180_PL_FADE_E, WE180_PL_FADE_S,
				WE180_PL_WAIT, WE180_PL_COLOR );
		wk->pl_fade_seq++;
		break;
		
	case WE180_P_FADEIN_MAIN:
		if( SoftSpritePalFadeExist( wk->at_ssp ) == FALSE ){
			wk->at_pl_count++;
			if( wk->at_pl_count > WE180_PL_COUNT ){
				wk->pl_fade_seq++;
			}else{
				wk->pl_fade_seq = WE180_P_FADEOUT_INIT;
			}
		}
		break;
		
	case WE180_P_FADE_END:
		ret = TRUE;
		break;
	}

	return ret;
}
//*/
static BOOL We180_LasterObj( TWE_180_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->sub_seq ){
	case WE180_L_FADEIN:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) == TRUE ){
			wk->sub_seq ++;
			wk->df_count = WE180_LASTER_COUNT;
		}
		break;
		
	case WE180_L_MAIN:
		wk->df_count --;
		if( wk->df_count < 0 ){
			wk->sub_seq++;

			// �t�F�[�h�A�E�g����
			WazaTool_StartAlphaFade( &wk->alpha,
					WE180_FADEIN_ALPHA1_ED, WE180_FADEIN_ALPHA1_ST, 
					 WE180_FADEIN_ALPHA2_ED, WE180_FADEIN_ALPHA2_ST,
					WE180_FADEOUT_ALPHA_SYNC );
		}
		break;
		
	case WE180_L_FADE_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) == TRUE ){
			wk->sub_seq ++;

			// ���X�^�[�j��
			WazaTool_DeleteScrLaster( wk->lst );
		}
		break;
		
	case WE180_L_END:
		ret = TRUE;
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����
 *
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We180_TCB( TCB_PTR tcb, void* work )
{
	TWE_180_SYS* wk = work;
	BOOL check;
	
	
	switch( wk->seq ){
	case WE180_INIT:
		if( CATS_ObjectEnableGetCap( wk->df_cap ) == 1 ){
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 1 );
		}
		
		We180_LasterObj( wk );
		wk->seq ++;
		break;

	case WE180_MAIN:

		// ���点��
		check = We180_LasterObj( wk );
		
		// ���X�^�[�̕����I���̂�҂�
		if( check ){
			wk->seq ++;
		}
		break;
		
	case WE180_END:

		// �G�t�F�N�gBG�D�揇�ʕύX
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );
		
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 0 );

		// �L�����N�^�f�[�^�N���A
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_180( WE_SYS_PTR we_sys )
{
	TWE_180_SYS* wk;
	int vec_x;
	s16 e_x, e_y;
	int plt_bit;
	int client_type;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_180_SYS);
	wk->we_sys	= we_sys;
	wk->pfd		= WeSysPFDGet(wk->we_sys);

	// �A���t�@�t�F�[�h
	WET_DefaultBGEffectBlendSet( wk->we_sys, WE180_FADEIN_ALPHA1_ST, WE180_FADEIN_ALPHA2_ST );
	WazaTool_StartAlphaFade( &wk->alpha,
			WE180_FADEIN_ALPHA1_ST, WE180_FADEIN_ALPHA1_ED,
			WE180_FADEIN_ALPHA2_ST, WE180_FADEIN_ALPHA2_ED,
			WE180_FADEIN_ALPHA_SYNC );


/*	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
//*/

	// �h�䑤
	// 
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	e_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	e_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	e_y -= SoftSpriteParaGet(wk->df_ssp, SS_PARA_SHADOW_HEIGHT);
	e_x -= (SOFT_SPRITE_SIZE_X / 2);
	e_y -= (SOFT_SPRITE_SIZE_Y / 2);

	// ���̃��C���[��BG�����邽�߂̏���
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 0);
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	if( (client_type == CLIENT_TYPE_D) ||
		(client_type == CLIENT_TYPE_A) ){
		CATS_ObjectEnableCap( wk->df_cap, TRUE );
		CATS_ObjectBGPriSetCap( wk->df_cap, 2 );
	}else{

		// �G�t�F�N�gBG���RD�ʂ̏�ɂ���
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
		CATS_ObjectEnableCap( wk->df_cap, FALSE );
	}

	
	// ���X�^�[
	wk->lst = WazaTool_InitScrLaster( 
			e_y,
			e_y + SOFT_SPRITE_SIZE_Y,
			WE180_ROTA_ADD,
			WE180_ROTA_WIDTH,
			WE180_SCR_SP,
			BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT),
			0,
			WazaTool_GetLasterBuffMatrixData( -e_x, -e_y ),
			WeSysHeapAreaGet(we_sys) );

	// �p���b�g�t�F�[�h
	plt_bit = 1 << (BATTLE_PAL_EFF_0);
	ColorConceChangePfd( wk->pfd, FADE_MAIN_BG, plt_bit, 8, 0x0 );

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet(wk->we_sys, We180_TCB, wk);
}

//-------------------------------------
//	
//	��т��ӂ�
//	
//=====================================
enum{
	WE118_FADEIN,
	WE118_MAIN,
	WE118_FADEOUT,
	WE118_END,
};

#define WE118_FADE_SCALE_S	(1)
#define WE118_FADE_SCALE_D	(10)
#define WE118_FADE_SCALE_E	(10)
#define WE118_FADE_SYNC		(8)

#define WE118_ROTA_S	( FX_GET_ROTA_NUM( 359 ) )
#define WE118_ROTA_E	( FX_GET_ROTA_NUM( 320 ) )
#define WE118_ROTA_S_E	( FX_GET_ROTA_NUM( 0 ) )
#define WE118_ROTA_E_E	( FX_GET_ROTA_NUM( 40 ) )
#define WE118_ROTA_NUM	( 5 )
#define WE118_ROTA_ONE_SYNC	(4)
#define WE118_ROTA_OFS_X	( -12 )
#define WE118_ROTA_OFS_Y	( 12 )

// ���W�␳
#define WE118_MATRIX_OFSX	( 40 )
#define WE118_MATRIX_OFSY	( 0 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int	seq;

	//�@��
	CATS_ACT_PTR			hand_cap;
	WAZATOOL_CALCMOVE		hand_scale;
	WAZATOOL_CALCMOVE_ONE	hand_rota;
	int hand_rota_count;
	int hand_rota_end;

	int sum_flip;
	
	// ��X�͌��̊G
} TWE_118_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	��т��ӂ�	����TCB
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	�X�v�[���܂����샏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We118_TCB(TCB_PTR tcb, void* work)
{
	TWE_118_SYS* wk = work;
	BOOL check;
	f32	s_x, s_y;
	int rota_s, rota_e;

	switch( wk->seq ){
	case WE118_FADEIN:
		// �v�Z
		check = WazaTool_CalcScaleRate( &wk->hand_scale );
		
		// �l�ݒ�
		if( check == TRUE ){
			WazaTool_CalcScaleRateToClactScale( &wk->hand_scale, &s_x, &s_y );
			CATS_ObjectScaleSetCap( wk->hand_cap, s_x * wk->sum_flip, s_y );
		}else{
			wk->seq++;
			wk->hand_rota_count = WE118_ROTA_NUM;
				
			// �t�F�[�h�A�E�g�̐ݒ���s��
			WazaTool_InitScaleRate(		// �g�k
					&wk->hand_scale,
					WE118_FADE_SCALE_E,
					WE118_FADE_SCALE_D,
					WE118_FADE_SCALE_S,		
					WE118_FADE_SYNC	);
			
		}
		break;
		
	case WE118_MAIN:
		check = WazaTool_CalcMoveOne( &wk->hand_rota );
		// ��]�e�ݒ�
		CATS_ObjectRotationSetCap( wk->hand_cap, wk->hand_rota.num );
		
		if( check == FALSE ){
			if( wk->hand_rota_count > 0 ){
				wk->hand_rota_count --;
		
				rota_s = wk->hand_rota.num;
				rota_e = wk->hand_rota_end;
				wk->hand_rota_end = wk->hand_rota.num;
				
				// ��]������
				WazaTool_InitMoveOneSync( 
						&wk->hand_rota,
						rota_s,
						rota_e,
						WE118_ROTA_ONE_SYNC
						);
			}else{
				
				wk->seq ++;
			}
		}
		break;
		
	case WE118_FADEOUT:
		// �v�Z
		check = WazaTool_CalcScaleRate( &wk->hand_scale );
		
		// �l�ݒ�
		if( check == TRUE ){
			WazaTool_CalcScaleRateToClactScale( &wk->hand_scale, &s_x, &s_y );
			CATS_ObjectScaleSetCap( wk->hand_cap, s_x * wk->sum_flip, s_y );

		}else{
		
			wk->seq++;
		}
		break;
		
	case WE118_END:
		// �I��
		// OAM�j��
		CATS_ActorPointerDelete_S(wk->hand_cap);

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	�w���ӂ�p�^�X�N
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_118(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_118_SYS* wk;
	int vec_x;
	int con_chg_x;
	s16 at_x, at_y;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_118_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �R���e�X�g�̂Ƃ��t���b�v
	if( ContestFlipCheck(wk->we_sys, WEDEF_DROP_M1 ) == TRUE ){
		wk->sum_flip = -1;
		con_chg_x = vec_x * -1;
	}else{
		wk->sum_flip = 1;
		con_chg_x = vec_x;
	}
	

	// ���W�͍U������ݒ�
	at_x	= GetWazaEffPos(we_sys, WeSysATNoGet(wk->we_sys), PM_X);
	at_y	= GetWazaEffPos(we_sys, WeSysATNoGet(wk->we_sys), PM_Y);
	
	// �蓮��p�����[�^�ݒ�
	wk->hand_cap		= cap;
	CATS_ObjectAffineSetCap( wk->hand_cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectScaleSetCap( wk->hand_cap, WE118_FADE_SCALE_S, WE118_FADE_SCALE_S );
	CATS_ObjectPosSetCap( wk->hand_cap, at_x, at_y );
	CATS_ObjectPosMoveCap( wk->hand_cap, WE118_MATRIX_OFSX * vec_x, WE118_MATRIX_OFSY );
	CATS_ObjectPriSetCap( wk->hand_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->hand_cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectAffinePosSetCap( wk->hand_cap, WE118_ROTA_OFS_X * con_chg_x, WE118_ROTA_OFS_Y );

	if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
		CATS_ObjectAnimeSeqSetCap(wk->hand_cap, 1);
	}
	else {
		CATS_ObjectAnimeSeqSetCap(wk->hand_cap, 0);
	}

		
	WazaTool_InitScaleRate(		// �g�k
			&wk->hand_scale,
			WE118_FADE_SCALE_S,		
			WE118_FADE_SCALE_D,
			WE118_FADE_SCALE_E,
			WE118_FADE_SYNC	);

	if( con_chg_x >= 0 ){
		WazaTool_InitMoveOneSync( 
				&wk->hand_rota,
				WE118_ROTA_S,
				WE118_ROTA_E,
				WE118_ROTA_ONE_SYNC
				);
		wk->hand_rota_end = WE118_ROTA_S;
	}else{

		WazaTool_InitMoveOneSync( 
				&wk->hand_rota,
				WE118_ROTA_S_E,
				WE118_ROTA_E_E,
				WE118_ROTA_ONE_SYNC
				);
		wk->hand_rota_end = WE118_ROTA_S_E;

	}

	// �^�X�N�o�^
	WEEffect_TCB_AddPriSet(wk->we_sys, We118_TCB, wk);
}

//-------------------------------------
//	
//	����݂�
//	
//=====================================
enum{
	WE132_OAM_MOVE,
	WE132_SHAKE,
	WE132_SCALE,
	WE132_END,
};
#define WE132_OAM_NUM	(4)

#define WE132_SCALE_S	( 10 )
#define WE132_SCALE_E	( 8 )
#define WE132_SCALE_D	( 10 )
#define WE132_SCALE_NUM	( 3 )
#define WE132_SCALE_SYNC	( 8 )
#define WE132_FLIP_ROTA	( FX_GET_ROTA_NUM(45) )
#define WE132_UNDER_MAT_OFS	(16)
#define WE132_GRASS_MAT_OFS	(10)		// ���̍��W�Â�ɕ\�����Ă�

#define WE132_SHAKE_WIDTH	( 4 )
#define WE132_SHAKE_NUM		( 1 )
#define WE132_SHAKE_SYNC	( 1 )

#define WE132_GRASS_ADD_WAIT	( 4 )

// ���I�u�W�F
typedef struct{
	
	CATS_ACT_PTR cap;
	
	// ��]�Ɗg��p�����[�^
	WAZATOOL_CALCMOVE		scale;
	BOOL	flip;
	int		scale_num;
	int		next_scale_s;
	int		next_scale_e;
} TWE_132_GRASS;

// 132�̃I�u�W�F
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	int	seq;
	int wait;
	int count;

	// �h�䑤
	SOFT_SPRITE*	df_ssp;
	s16				df_x;
	s16				df_y;
	WAZATOOL_CALCMOVE shake;
	

	// ���f�[�^
	TWE_132_GRASS	grass[ WE132_OAM_NUM ];
	int grass_count;
} TWE_132_SYS;

static void TWE_132_GrassInit( TWE_132_GRASS* wk, CATS_ACT_PTR cap, s16 x, s16 y, BOOL flip )
{
	// �����J
	wk->cap = cap;
	WazaTool_InitScaleRate(
			&wk->scale,
			WE132_SCALE_S,
			WE132_SCALE_D,
			WE132_SCALE_E,
			WE132_SCALE_SYNC
			);
	wk->scale_num = WE132_SCALE_NUM;
	wk->next_scale_s = WE132_SCALE_E;
	wk->next_scale_e = WE132_SCALE_S;
	wk->flip		= flip;
	
	CATS_ObjectPosSetCap( wk->cap, x, y );
	CATS_ObjectPosSetCap( wk->cap, x, y );

	// �_�u���A�t�B��
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );
	
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );

	if( flip ){
		// �t���b�v������
		CATS_ObjectScaleSetCap( wk->cap, -1, 1 );
	}

	// �`��I�t
	CATS_ObjectEnableCap( wk->cap, FALSE );
}

static void TWE_132_GrassDelete( TWE_132_GRASS* wk )
{
	// OAM�j��
	CATS_ActorPointerDelete_S(wk->cap);
}

static void TWE_132_GrassDrawOn( TWE_132_GRASS* wk )
{
	// �`��I�t
	CATS_ObjectEnableCap( wk->cap, TRUE );
		
	// �I�[�g�A�j��������
	CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
}

static BOOL TWE_132_GrassMove( TWE_132_GRASS* wk )
{
	BOOL check;
	f32	s_x, s_y;
	int tmp;

	// �v�Z��
	check = WazaTool_CalcScaleRate( &wk->scale );

	// �g�k��scale_num�񑱂���
	if( check == TRUE ){

		WazaTool_CalcScaleRateToClactScale( &wk->scale, &s_x, &s_y );
		if( wk->flip ){
			CATS_ObjectScaleSetCap( wk->cap, -s_x, 1 );
		}else{
			CATS_ObjectScaleSetCap( wk->cap, s_x, 1 );
		}
	}else{
		if( wk->scale_num > 0 ){
			wk->scale_num --;

			WazaTool_InitScaleRate(
					&wk->scale,
					wk->next_scale_s,
					WE132_SCALE_D,
					wk->next_scale_e,
					WE132_SCALE_SYNC
					);
			tmp = wk->next_scale_s;
			wk->next_scale_s	= wk->next_scale_e;
			wk->next_scale_e	= tmp;
		}else{
			
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����݂��@TCB
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We132_TCB( TCB_PTR tcb, void* work )
{
	TWE_132_SYS* wk = work;
	int i;
	BOOL check;
	
	switch( wk->seq ){
	case WE132_OAM_MOVE:
		if( wk->wait >= WE132_GRASS_ADD_WAIT ){
			// �P�o�^
			wk->wait = 0;
			TWE_132_GrassDrawOn( &wk->grass[ wk->count ] );
			wk->count++;

			if( wk->count >= WE132_OAM_NUM ){
				wk->seq ++;
			}
		}
		wk->wait ++;
		break;
		
	case WE132_SHAKE:
		// �|�P�������V�F�C�N
		if( WazaTool_CalcAndReflectShakeSsp( &wk->shake, wk->df_x, wk->df_y, wk->df_ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE132_SCALE:
		for( i = 0; i < WE132_OAM_NUM; i++ ){

			check = TWE_132_GrassMove( wk->grass + i );
		}
		if( check == FALSE ){
			wk->seq++;
		}
		break;

	case WE132_END:
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );

		for( i = 0; i < WE132_OAM_NUM; i++ ){
			TWE_132_GrassDelete( wk->grass + i );
		}

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	����݂��p�^�X�N
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_132(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_132_SYS* wk;
	int i;		// ���[�v�p
	int df_client;
	int set_y;
	int flip_flg;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_132_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �|�P�����̔z�u������鉡����������
	df_client = WeSysDFNoGet(we_sys); 

	// ���W�͖h�䑤��ݒ�
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, df_client );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	WazaTool_InitShake( 
			&wk->shake,
			WE132_SHAKE_WIDTH,
			0,
			WE132_SHAKE_SYNC,
			WE132_SHAKE_NUM
			);

	// ���I�u�W�F�쐬
	set_y = wk->df_y + WE132_UNDER_MAT_OFS;	// �|�P�����̒�ӂ̍��W�ɂ���
	flip_flg = 0;
	coap   = WeSysCoapGet(wk->we_sys);
	for( i=0; i<WE132_OAM_NUM; i++ ){
		// �O�߂͈�����cap���g�p
		if( i == 0 ){
			
			TWE_132_GrassInit( &wk->grass[ i ], cap, wk->df_x, set_y, flip_flg );
		}else{
			
			TWE_132_GrassInit( &wk->grass[ i ], CATS_ObjectAdd_S(csp, crp, &coap), wk->df_x, set_y, flip_flg );
		}

		set_y -= WE132_GRASS_MAT_OFS;
		flip_flg ^= 1;
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We132_TCB, wk);
}


//-------------------------------------
//	
//	�ق˃u�[������
//	
//=====================================
enum{
	WE155_AT_MOVE0,
	WE155_AT_MOVE0_1,
	WE155_BONE_AT_DF,
	WE155_BONE_DF_AT,
	WE155_AT_MOVE1,
	WE155_AT_MOVE2,
	WE155_END,
};

#define WE155_AT_MOVE_X		( -32 )
#define WE155_AT_MOVE_X_0	( -16 )
#define WE155_AT_MOVE_SYNC	( 4 )
#define WE155_AT_MOVE_SYNC_0	( 2 )

/*#define WE155_SHAKE_WIDTH	( 4 )
#define WE155_SHAKE_NUM		( 1 )
#define WE155_SHAKE_SYNC	( 1 )//*/

#define WE155_BONE_MOVE_ONE_SYNC	( 10 )
#define	WE155_BONE_MOVE_HEIGHT		( 32*FX32_ONE )

typedef struct{
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// �U����
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16	at_y;
	WAZATOOL_CALCMOVE at_move;
	s32 vec_x;

/*	// �h�䑤
	WAZATOOL_CALCMOVE df_move;//*/
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16	df_y;
	
	// ��
	CATS_ACT_PTR	bone_obj;
	WAZATOOL_CALCMOVE bone_param1;
	WAZATOOL_CALCMOVE bone_param2;
} TWE155_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ق˂ԁ[�߂��
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We155_TCB( TCB_PTR tcb, void* work )
{
	TWE155_SYS* wk = work;

	switch( wk->seq ){
	case WE155_AT_MOVE0:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, 0,
					0, 0,
					WE155_AT_MOVE_SYNC_0 );
			wk->seq++;
		}
		return;	// OAM�`�悵�Ȃ�����
		
	case WE155_AT_MOVE0_1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					0, WE155_AT_MOVE_X * wk->vec_x,
					0, 0,
					WE155_AT_MOVE_SYNC );
			wk->seq++;
		}
		return;	// OAM�`�悵�Ȃ�����

	case WE155_BONE_AT_DF:
		// ��������
		if( WazaTool_CalcAndReflectCurveFxCap( &wk->bone_param1, &wk->bone_param2, wk->bone_obj ) == FALSE ){

			WazaTool_InitCurveYFx( 
					&wk->bone_param1, &wk->bone_param2,
					wk->df_x, wk->at_x, 
					wk->df_y, wk->at_y,
					WE155_BONE_MOVE_ONE_SYNC,
					-WE155_BONE_MOVE_HEIGHT
					);
			wk->seq++;
		}
		break;
		
	case WE155_BONE_DF_AT:
		// �|�P�����𓮂���
//		WazaTool_CalcAndReflectShakeSsp( &wk->df_move, wk->df_x, wk->df_y, wk->df_ssp );

		// ���𓮂���
		if( WazaTool_CalcAndReflectCurveFxCap( &wk->bone_param1, &wk->bone_param2, wk->bone_obj ) == FALSE ){
/*			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );//*/

			// ���\��OFF
			CATS_ObjectEnableCap( wk->bone_obj, FALSE );
			wk->seq++;
		}
		
		break;
		
	case WE155_AT_MOVE1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, 0,
					0, 0,
					WE155_AT_MOVE_SYNC );
			wk->seq++;
		}
		break;

	case WE155_AT_MOVE2:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			wk->seq++;
		}
		break;
		
	case WE155_END:
		CATS_ActorPointerDelete_S(wk->bone_obj);

		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	���p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_155(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE155_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE155_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	WazaTool_InitStraightSyncFx( 
			&wk->at_move,
			0, WE155_AT_MOVE_X_0 * wk->vec_x,
			0, 0,
			WE155_AT_MOVE_SYNC );

	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
/*	WazaTool_InitShake( 
			&wk->df_move,
			WE155_SHAKE_WIDTH, 0,
			WE155_SHAKE_SYNC,
			WE155_SHAKE_NUM );//*/

	// ��
	wk->bone_obj = cap;
	CATS_ObjectAutoAnimeSetCap( wk->bone_obj, TRUE );
	CATS_ObjectPriSetCap( wk->bone_obj, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->bone_obj, WAZAEFF_ACT_BGPRI );
	WazaTool_InitCurveYFx( 
			&wk->bone_param1, &wk->bone_param2,
			wk->at_x, wk->df_x, 
			wk->at_y, wk->df_y,
			WE155_BONE_MOVE_ONE_SYNC,
			WE155_BONE_MOVE_HEIGHT
			);

	WEEffect_TCB_AddPriSet(wk->we_sys, We155_TCB, wk);
}

//-------------------------------------
//	
//	���܂�����
//	
//=====================================
enum{
	WE185_AT_FADE_OUT,
	WE185_DF_DAMAGE,
	WE185_AT_FADE_IN,
	WE185_END,
};
#define WE185_ROTA_NUM	( 2 )
#define WE185_ROTA_SYNC	( 16 )
#define WE185_FADE_ALPHA_S	(16)
#define WE185_FADE_ALPHA_E	(0)
#define WE185_FADE_ALPHA_SYNC	( 32 )

#define WE185_DF_SHAKE_WAIT	( 16 )

/*#define WE185_SHAKE_WIDTH	( 4 )
#define WE185_SHAKE_NUM		( 1 )
#define WE185_SHAKE_SYNC	( 1 )//*/

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	// �U����
	SOFT_SPRITE* at_ssp;
	CATS_ACT_PTR at_cap;
	s16	at_x;
	s16	at_y;
	WAZATOOL_CALCMOVE at_move;
	WAZATOOL_ALPHA_FADE	at_alpha;

	s16 cap_ofs_y;

/*	// �h�䑤
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16	df_y;
	WAZATOOL_CALCMOVE df_move;//*/

} TWE185_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���܂�����
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We185_TCB( TCB_PTR tcb, void* work )
{
	TWE185_SYS* wk = work;
	
	switch( wk->seq ){
	case WE185_AT_FADE_OUT:
		// �A���t�@�͏���ɂ����
		
		// ��]�v�Z
		if( WazaTool_CalcAndReflectRotaFxCap( &wk->at_move, wk->at_x, wk->at_y - wk->cap_ofs_y, wk->at_cap ) == FALSE ){
			wk->seq++;
			wk->wait = WE185_DF_SHAKE_WAIT;
		}
		break;
		
	case WE185_DF_DAMAGE:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;

			// �t�F�[�h�C������
			WazaTool_StartAlphaFade(
					&wk->at_alpha,
					WE185_FADE_ALPHA_E, WE185_FADE_ALPHA_S,
					16 - WE185_FADE_ALPHA_E, 16 - WE185_FADE_ALPHA_S,  
					WE185_FADE_ALPHA_SYNC
					);
		}
		break;

	case WE185_AT_FADE_IN:
		// alpah
		if( WazaTool_EndCheckAlphaFade( &wk->at_alpha ) ){
			CATS_ObjectEnableCap( wk->at_cap, TRUE );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, FALSE );
			wk->seq++;
		}
		break;

	case WE185_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}
	// OAM�`��
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���܂�����
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_185( WE_SYS_PTR we_sys )
{
	TWE185_SYS* wk;
	int vec_x;

	wk = WET_ALLOC_MEMORY(we_sys, TWE185_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_SHADOW_HEIGHT );
	wk->at_y	-= WAZATOOL_DEF_ROTA_W_Y_INT;
	wk->at_cap	= WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectObjModeSetCap( wk->at_cap, GX_OAM_MODE_XLU );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, TRUE );
	WazaTool_MakeDefRota( 
			&wk->at_move,
			WE185_ROTA_NUM,
			WE185_ROTA_SYNC	);
	WET_DefaultBlendSet( wk->we_sys,
			WE185_FADE_ALPHA_S, 16 - WE185_FADE_ALPHA_S );
	WazaTool_StartAlphaFade(
			&wk->at_alpha,
			WE185_FADE_ALPHA_S, WE185_FADE_ALPHA_E,
			16 - WE185_FADE_ALPHA_S, 16 - WE185_FADE_ALPHA_E, 
			WE185_FADE_ALPHA_SYNC
			);
	wk->at_move.work[2] *= vec_x;

/*	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	WazaTool_InitShake( 
			&wk->df_move,
			WE185_SHAKE_WIDTH, 0,
			WE185_SHAKE_SYNC,
			WE185_SHAKE_NUM );//*/

	WEEffect_TCB_AddPriSet(wk->we_sys, We185_TCB, wk);

	// OAM�`��
	CATS_Draw(wk->crp);	
}

//-------------------------------------
//	
//	�|����
//	
//=====================================
enum{
	WE184_FACE_MOVE,
	WE184_FACE_FADEOUT,
	WE184_FACE_END,
};

enum{
	WE184_MOVE,
	WE184_END,
};

enum{
	WE184_POKE_SCALE_UP,
	WE184_POKE_SCALE_DOWN,
	WE184_POKE_END,
};

/*#define WE184_SCALE_RATE_S	( 10 )
#define WE184_SCALE_RATE_E	( 15 )
#define WE184_SCALE_RATE_D	( 10 )
#define WE184_SCALE_SYNC	( 12 )
#define WE184_MOVE_WIDTH	( 64 )
#define WE184_MOVE_HEIGH	( -16 )
#define WE184_MOVE_HEIGH_MY	( -48 )
#define WE184_MOVE_SYNC		( 32 )		// �炪��������
#define WE184_MOVE_X_OFS	( 32 )	//*/

#define WE184_SCALE_RATE_S	( 10 )
#define WE184_SCALE_RATE_E	( 15 )
#define WE184_SCALE_RATE_D	( 10 )
#define WE184_SCALE_SYNC	( 12 )

#define WE184_MOVE_WIDTH	( 0 )
#define WE184_MOVE_HEIGH	( -8 )
#define WE184_MOVE_HEIGH_MY	( -24 )
#define WE184_MOVE_SYNC		( 32 )		// �炪��������
#define WE184_MOVE_X_OFS	( 32 )	//*/

#define WE184_FACE_SCALE_RATE_S	( 5 )
#define WE184_FACE_SCALE_RATE_E	( 12 )
#define WE184_FACE_SCALE_RATE_D	( 10 )

#define WE184_FADE_OUT_SYNC	( 8 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// �U����
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE at_scale;
	int poke_seq;
	
	// �|����
	CATS_ACT_PTR face_obj;
	int face_seq;
	WAZATOOL_CALCMOVE face_scale;
	WAZATOOL_CALCMOVE face_move;
	WAZATOOL_ALPHA_FADE face_alpha;
	s16	face_x;
	s16	face_y;
	
} TWE184_SYS;

static BOOL We184_PokeMove( TWE184_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->poke_seq ){
	case WE184_POKE_SCALE_UP:
		if( WazaTool_CalcScaleRate( &wk->at_scale ) ){
			// �g�k
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, wk->at_scale.y );
		}else{
			wk->poke_seq++;
			WazaTool_InitScaleRate( 
					&wk->at_scale,
					WE184_SCALE_RATE_E,
					WE184_SCALE_RATE_D,
					WE184_SCALE_RATE_S,
					WE184_SCALE_SYNC );
		}
		break;
		
	case WE184_POKE_SCALE_DOWN:
		if( WazaTool_CalcScaleRate( &wk->at_scale ) ){
			// �g�k
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, wk->at_scale.y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
			wk->poke_seq++;
		}
		break;

	case WE184_POKE_END:
		ret = TRUE;		
		break;
	}

	return ret;
}

static BOOL We184_FaceMove( TWE184_SYS* wk )
{
	BOOL ret = FALSE;
	BOOL check;
	
	switch( wk->face_seq ){
	case WE184_FACE_MOVE:
		// �v�Z��
		// �S�ē����t���[���œ���
		WazaTool_CalcAndReflectScaleRateCap( &wk->face_scale, wk->face_obj );
		check = WazaTool_CalcStraightFx( &wk->face_move );

		if( check ){

			// ���W�ړ�
			WazaTool_SetCapMatrix( &wk->face_move, wk->face_obj, wk->face_x, wk->face_y );
		}else{
			wk->face_seq++;
			WazaTool_StartAlphaFade( 
					&wk->face_alpha,
					16, 0,
					14,16,
					WE184_FADE_OUT_SYNC	);
		}
		break;

	case WE184_FACE_FADEOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->face_alpha ) ){
			CATS_ObjectEnableCap( wk->face_obj, FALSE );
			wk->face_seq++;
		}
		break;

	case WE184_FACE_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We184_TCB( TCB_PTR tcb, void* work )
{
	TWE184_SYS* wk = work;
	
	switch( wk->seq ){
	case WE184_MOVE:
		We184_PokeMove( wk );
		if( We184_FaceMove( wk ) ){
			wk->seq++;
		}
		break;
		
	case WE184_END:
		CATS_ActorPointerDelete_S(wk->face_obj);
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
 * @brief	�|����p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_184(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE184_SYS* wk;
	int vec_x;
	int vec_y;
	s16	at_x;
	s16	at_y;
	int move_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE184_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	vec_y = WazaTool_VecChangeY( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	WazaTool_InitScaleRate( 
			&wk->at_scale,
			WE184_SCALE_RATE_S,
			WE184_SCALE_RATE_D,
			WE184_SCALE_RATE_E,
			WE184_SCALE_SYNC );


	// ����
	wk->face_obj = cap;
	CATS_ObjectAutoAnimeSetCap( wk->face_obj, TRUE );
	CATS_ObjectAffineSetCap( wk->face_obj, CLACT_AFFINE_DOUBLE );
	CATS_ObjectObjModeSetCap( wk->face_obj, GX_OAM_MODE_XLU );
	CATS_ObjectPriSetCap( wk->face_obj, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->face_obj, WAZAEFF_ACT_BGPRI );
	wk->face_x	= at_x + (WE184_MOVE_X_OFS * vec_x);
	wk->face_y	= at_y;

	if( vec_y < 0 ){
		move_y = WE184_MOVE_HEIGH;
	}else{
		move_y = WE184_MOVE_HEIGH_MY;
	}

	
	WazaTool_InitStraightSyncFx( 
			&wk->face_move,
			0, WE184_MOVE_WIDTH * vec_x, 
			0, move_y * vec_y,
			WE184_MOVE_SYNC );
	WazaTool_InitScaleRate( 
			&wk->face_scale,
			WE184_FACE_SCALE_RATE_S,
			WE184_FACE_SCALE_RATE_D,
			WE184_FACE_SCALE_RATE_E,
			WE184_MOVE_SYNC );
//	WET_DefaultBlendSet(wk->we_sys, 31, 26 );

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			GX_BLEND_ALL, 31, 26 );	

	WEEffect_TCB_AddPriSet(wk->we_sys, We184_TCB, wk);
}



//-------------------------------------
//	
//	�݂�Ԃ�
//	
//=====================================
enum{
	WE193_MOVE_INIT,
	WE193_MOVE_MAIN,
	WE193_POKE_FADE_OUT,
	WE193_POKE_FADE_IN,
	WE193_END,
};

#define WE193_MOVE_WIDTH	( 80 )
#define WE193_MOVE_HEIGHT	( 80 )
#define WE193_MOVE_SYNC		( 8 )
#define WE193_MOVE_COUNT	( 6 )
#define WE193_MOVE_WAIT		( 4 )

#define WE193_FADEOUT_ALPHA_SYNC	( 16 )
#define WE193_POKE_FADE_S	( 0 )
#define WE193_POKE_FADE_E	( 10 )
#define WE193_POKE_FADE_COLOR	( GX_RGB( 31,31,31 ) )
#define WE193_POKE_FADE_WAIT	(0)

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// �h�䑤
	SOFT_SPRITE* df_ssp;
	
	// �ނ��߂���
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cap_move;
	WAZATOOL_ALPHA_FADE cap_alpha;
	s16	cap_x;
	s16	cap_y;
	int cap_count;
	int cap_wait;
	
} TWE193_SYS;

static void We193_InitCap( TWE193_SYS* wk )
{
	switch( wk->cap_count ){
	case 0:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE193_MOVE_WIDTH / 2,
				0, WE193_MOVE_HEIGHT / 2,
				WE193_MOVE_SYNC );
		break;
	case 1:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 2:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE193_MOVE_WIDTH,
				0, WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 3:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 4:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE193_MOVE_WIDTH,
				0, WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 5:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE193_MOVE_WIDTH / 2,
				0, -WE193_MOVE_HEIGHT / 2,
				WE193_MOVE_SYNC );
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

static void We193_TCB( TCB_PTR tcb, void* work )
{
	TWE193_SYS* wk = work;

	switch( wk->seq ){
	case WE193_MOVE_INIT:
		// ����������
		wk->cap_wait ++;
		if( wk->cap_wait > WE193_MOVE_WAIT ){
			We193_InitCap( wk );
			wk->seq ++;
			wk->cap_wait = 0;
		}
		break;
		
	case WE193_MOVE_MAIN:
		// �v�Z��
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){
			WazaTool_SetCapMatrix( &wk->cap_move, wk->cap, wk->cap_x, wk->cap_y );
		}else{

			wk->cap_count ++;
			if( wk->cap_count < WE193_MOVE_COUNT ){
				wk->seq = WE193_MOVE_INIT;

				// ���݈ʒu��ۑ�
				wk->cap_x += wk->cap_move.x;
				wk->cap_y += wk->cap_move.y;
			}else{
				
				wk->seq ++;
				// �t�F�[�h�A�E�g�ݒ�
				CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
				WazaTool_StartAlphaFade( 
						&wk->cap_alpha,
						16, 0,
						0, 16,
						WE193_FADEOUT_ALPHA_SYNC );
				
				// �p���b�g�t�F�[�h
				SoftSpritePalFadeSet( wk->df_ssp,
						WE193_POKE_FADE_S, WE193_POKE_FADE_E,
						WE193_POKE_FADE_WAIT,
						WE193_POKE_FADE_COLOR );
			}
		}
		break;
		
	case WE193_POKE_FADE_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			CATS_ObjectEnableCap( wk->cap, FALSE );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			wk->seq++;
			// �p���b�g�t�F�[�h
			SoftSpritePalFadeSet( wk->df_ssp,
					WE193_POKE_FADE_E, WE193_POKE_FADE_S,
					WE193_POKE_FADE_WAIT,
					WE193_POKE_FADE_COLOR );
		}
		break;
		
	case WE193_POKE_FADE_IN:
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE193_END:
		CATS_ActorPointerDelete_S(wk->cap);
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
 * @brief	�݂�Ԃ�p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_193(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE193_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE193_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );


	// ���ዾ
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosGetCap( wk->cap, &wk->cap_x, &wk->cap_y );


	WEEffect_TCB_AddPriSet(wk->we_sys, We193_TCB, wk);
}

//-------------------------------------
//	
//	���b�N�I��
//	
//=====================================
enum{
	WE199_MOVE_INIT,
	WE199_MOVE_MAIN,
	WE199_ANIME_ACT,
	WE199_FLASH_IN,
	WE199_FLASH_OUT,
	WE199_SWITCH_ACT,
	WE199_END,
};

#define WE199_MOVE_WAIT_INIT	( -16 )
#define WE199_MOVE_WIDTH	( 80 )
#define WE199_MOVE_HEIGHT	( 80 )
#define WE199_MOVE_SYNC		( 4 )
#define WE199_MOVE_COUNT	( 4 )
#define WE199_MOVE_WAIT		( 1 )

#define WE199_FLASH_SYNC	( -8 )

#define WE199_FLASH_WAIT	( 8 )

#define WE199_SWITCH_WAIT	( 4 )
#define WE199_SWITCH_COUNT	( 4 )


typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// �h�䑤
	SOFT_SPRITE* df_ssp;

	// �|�P�����t�F�[�h�p
	SOFT_SPRITE* fade_ssp[4];
	
	// ���b�N�I��
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cap_move;
	s16	cap_x;
	s16	cap_y;
	int cap_count;
	int cap_wait;
	int cap_vanish;
} TWE199_SYS;

static void We199_InitCap( TWE199_SYS* wk )
{
	switch( wk->cap_count ){
	case 0:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE199_MOVE_WIDTH,
				0, WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 1:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 2:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE199_MOVE_WIDTH,
				0, WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 3:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE199_MOVE_WIDTH/2,
				0, -WE199_MOVE_HEIGHT/2,
				WE199_MOVE_SYNC );
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

static void We199_TCB( TCB_PTR tcb, void* work )
{
	TWE199_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE199_MOVE_INIT:
		// ����������
		wk->cap_wait ++;
		if( wk->cap_wait > WE199_MOVE_WAIT ){
			We199_InitCap( wk );
			wk->seq ++;
			wk->cap_wait = 0;
		}
		break;
		
	case WE199_MOVE_MAIN:
		// �v�Z��
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){
			WazaTool_SetCapMatrix( &wk->cap_move, wk->cap, wk->cap_x, wk->cap_y );
		}else{

			wk->cap_count ++;
			if( wk->cap_count < WE199_MOVE_COUNT ){
				wk->seq = WE199_MOVE_INIT;

				// ���݈ʒu��ۑ�
				wk->cap_x += wk->cap_move.x;
				wk->cap_y += wk->cap_move.y;
			}else{
				
				wk->seq ++;
				wk->cap_wait = WE199_FLASH_WAIT;

				// �I�[�g�A�j��
				// �A�j���V�[�P���X�ύX
				CATS_ObjectAnimeSeqSetCap( wk->cap, 1 );
				CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
			}
		}
		break;

	case WE199_ANIME_ACT:
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->seq++;

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE199_FLASH_SYNC, 0, 16, 0xffff);
			for( i=0; i<4; i++ ){
				if( wk->fade_ssp[i] ){
					SoftSpritePalFadeSet( wk->fade_ssp[i], 14, 16, 0, 0xffff );
				}
			}
/*			// �u���C�g�l�X�J�n
			WIPE_SYS_Start( 
					WIPE_PATTERN_M,
					WIPE_TYPE_FADEOUT,
					WIPE_TYPE_FADEOUT,
					WIPE_FADE_WHITE,
					WE199_FLASH_SYNC,
					1, WeSysHeapAreaGet(wk->we_sys) );
//*/
		}
		break;
		
	case WE199_FLASH_IN:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;
/*
			// �u���C�g�l�X�J�n
			WIPE_SYS_Start( 
					WIPE_PATTERN_M,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_WHITE,
					WE199_FLASH_SYNC,
					1, WeSysHeapAreaGet(wk->we_sys) );
//*/
			
			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE199_FLASH_SYNC, 16, 0, 0xffff);
			for( i=0; i<4; i++ ){
				if( wk->fade_ssp[i] ){
					SoftSpritePalFadeSet( wk->fade_ssp[i], 2, 0, 0, 0xffff );
					
				}
			}
		}
		break;
		
	case WE199_FLASH_OUT:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;

			wk->cap_wait = WE199_SWITCH_WAIT;
			wk->cap_count = WE199_SWITCH_COUNT;
			wk->cap_vanish = 0;
		}
		break;

	case WE199_SWITCH_ACT:
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->cap_wait = WE199_SWITCH_WAIT;
			wk->cap_count --;
			if( wk->cap_count < 0 ){	// �񐔓_�ł�����I��
				wk->seq ++;
			}else{
				CATS_ObjectEnableCap( wk->cap, wk->cap_vanish );
				wk->cap_vanish ^= 1;
			}
		}
		break;
		
	case WE199_END:
		CATS_ActorPointerDelete_S(wk->cap);
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
 * @brief	���b�N�I���p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_199(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE199_SYS* wk;
	int i;

	wk = WET_ALLOC_MEMORY(we_sys, TWE199_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );

	for( i=0; i<4; i++ ){
		wk->fade_ssp[i] = WeSysSoftSpritePointerGet( wk->we_sys, i );
	}

	// ���ዾ
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosGetCap( wk->cap, &wk->cap_x, &wk->cap_y );
	wk->cap_x -= WE199_MOVE_WIDTH / 2;
	wk->cap_y -= WE199_MOVE_HEIGHT / 2;
	CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_y );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	wk->cap_wait = WE199_MOVE_WAIT_INIT;

	// ���ݒ�
//	WET_DefaultBlendSet(wk->we_sys, 31, 26 );

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			GX_BLEND_ALL, 31, 26 );	
	


	WEEffect_TCB_AddPriSet(wk->we_sys, We199_TCB, wk);
}

//-------------------------------------
//	
//	���܂���
//	
//=====================================
enum{
	WE204_ROTA_OUT,
	WE204_ROTA_DOWN,
	WE204_ROTA_IN,
	WE204_ROTA_END,
};
enum{
	WE204_MOVE,
	WE204_END,
};
#define WE204_ROTA_E		( FX_GET_ROTA_NUM( 15 ) )
#define WE204_ROTA_SYNC		( 3 )
#define WE204_ROTA_C_Y		( 50 )
#define WE204_DOWN_HEIGHT	( 2 )
#define WE204_DOWN_SYNC		( 2 )
#define WE204_DOWN_WAIT		( 0 )

#define WE204_MOVE_NUM		(4)

#define WE204_MATRIX_Y		( 40 )
#define WE204_MATRIXOFS_Y	( -40 )

#define WE204_ROTA_OFS_X	( 16 )

// ���[�N
typedef struct{
	int	seq;
	WE_SYS_PTR	we_sys;			
	
	// �\�t�g�X�v���C�g�f�[�^
	SOFT_SPRITE* at_ssp;
	s16 at_x;
	s16 at_y;

	// ��]�v�Z�p���[�N
	WAZATOOL_CALCMOVE_ONE	calc_rota;
	WAZATOOL_CALCMOVE		calc_move;
	int count;
	int rota_seq;
	int wait;
	int flip_flg;

} TWE204_SYS;

static void TWe204_RotaInit( TWE204_SYS* wk, BOOL flip )
{
	fx32 width;

	WazaTool_InitMoveOneSyncFx( 
			&wk->calc_rota,
			0,
			WE204_ROTA_E,
			WE204_ROTA_SYNC	);

	// ��]����
	// ��]���ݒ�
	if( flip ){
		wk->calc_rota.work[1] *= -1;
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, WE204_ROTA_OFS_X );
	}else{
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, -WE204_ROTA_OFS_X );
	}
	
	wk->rota_seq = 0;
	wk->wait = WE204_DOWN_WAIT;
}

static BOOL TWe204_RotaMove( TWE204_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->rota_seq ){
	case WE204_ROTA_OUT:

		WazaTool_CalcMoveOneFx( &wk->calc_rota );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );

		wk->wait --;
		if( wk->wait < 0 ){
			wk->rota_seq++;

			WazaTool_InitStraightSyncFx(
					&wk->calc_move,
					wk->at_x, wk->at_x,
					wk->at_y, wk->at_y + WE204_DOWN_HEIGHT,
					WE204_DOWN_SYNC
					);
		}
		break;

	case WE204_ROTA_DOWN:
		if( WazaTool_CalcMoveOneFx( &wk->calc_rota ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );
		}
		
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->calc_move, wk->at_ssp ) == FALSE ){
			wk->rota_seq++;
			WazaTool_InitMoveOneSyncFx( 
					&wk->calc_rota,
					wk->calc_rota.num,
					0,
					WE204_ROTA_SYNC	);

			WazaTool_InitStraightSyncFx(
					&wk->calc_move,
					wk->at_x, wk->at_x,
					wk->at_y + WE204_DOWN_HEIGHT, wk->at_y,
					WE204_DOWN_SYNC
					);
		}
		break;

	case WE204_ROTA_IN:

		WazaTool_CalcAndReflectStraightFxSsp( &wk->calc_move, wk->at_ssp );
		
		if( WazaTool_CalcMoveOneFx( &wk->calc_rota ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, 0 );
			wk->rota_seq++;
		}
		break;
	case WE204_ROTA_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We204_TCB( TCB_PTR tcb, void* work )
{
	TWE204_SYS* wk = work;

	switch( wk->seq ){
	case WE204_MOVE:
		if( TWe204_RotaMove( wk ) ){

			wk->count ++;
			if( wk->count < WE204_MOVE_NUM ){
				wk->flip_flg ^= 1;
				TWe204_RotaInit( wk, wk->flip_flg );
				TWe204_RotaMove( wk );
			}else{
				wk->seq++;
			}
		}
		break;

	case WE204_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���܂���
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_204( WE_SYS_PTR we_sys )
{
	TWE204_SYS* wk;
	int vec_x;

	wk = WET_ALLOC_MEMORY(we_sys, TWE204_SYS);
	wk->we_sys	= we_sys;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �U����
	if (WeSysGPWorkGet(we_sys, 0) == 0){
		wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
		wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
		wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	}
	else {
		wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
		wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
		wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	}

	// ��]���S�p�x�ݒ�
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, WE204_ROTA_C_Y );

	// ��]�f�[�^������
	if( vec_x == 1 ){
		wk->flip_flg = 0;
	}else{
		wk->flip_flg = 1;
	}
	TWe204_RotaInit( wk, wk->flip_flg );

	WEEffect_TCB_AddPriSet(wk->we_sys, We204_TCB, wk);
}


//-------------------------------------
//	
//	���΂�
//	
//=====================================
enum{
	WE207_POKE_SCALE,
	WE207_WAIT,
	WE207_END,
};
enum{
	WE207_AT_SCALE_UP,
	WE207_AT_WAIT,
	WE207_AT_SCALE_DOWN,
	WE207_AT_END,
};

#define WE207_SCALE_POKE_S		( 10 )
#define WE207_SCALE_POKE_D		( 10 )
#define WE207_SCALE_POKE_E		( 15 )
#define WE207_SCALE_POKE_SYNC	( 8 )
#define WE207_SCALE_POKE_WAIT	( 4 )



#define WE207_WAIT_NUM	( 16 )

typedef struct {
	WE_SYS_PTR	we_sys;
	int seq;
	int wait;
	
	// �U����
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE at_scale;
	int at_wait;
	int at_seq;
	int at_y;
	int at_h;
	
} TWE207_SYS;


static BOOL We207_MoveAtPoke( TWE207_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->at_seq ){
	case WE207_AT_SCALE_UP:
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) ){
			// ���ɂ��킹��
			WazaTool_PokeOffsetSet( wk->at_ssp, wk->at_y, wk->at_h, wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}else{
			wk->at_seq++;
		}
		break;

	case WE207_AT_WAIT:
		wk->at_wait --;
		if( wk->at_wait < 0 ){
			wk->at_seq++;
			WazaTool_InitScaleRate(
					&wk->at_scale,
					WE207_SCALE_POKE_E,
					WE207_SCALE_POKE_D,
					WE207_SCALE_POKE_S,
					WE207_SCALE_POKE_SYNC
					);
		}
		break;

	case WE207_AT_SCALE_DOWN:
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) ){
			// ���ɂ��킹��
			WazaTool_PokeOffsetSet( wk->at_ssp, wk->at_y, wk->at_h, wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}else{
			wk->at_seq++;
		}
		break;

	case WE207_AT_END:
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
		ret = TRUE;
		break;
	}

	return ret;
}

static void We207_TCB( TCB_PTR tcb, void* work )
{
	TWE207_SYS* wk = work;
	
	switch( wk->seq ){
	case WE207_POKE_SCALE:
		if( We207_MoveAtPoke( wk ) ){
			wk->seq++;
			wk->wait = WE207_WAIT_NUM;
		}
		break;

	case WE207_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		

	case WE207_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���܂���
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_207_MAIN( WE_SYS_PTR we_sys )
{
	TWE207_SYS* wk;
	SOFT_SPRITE* df_ssp;

	wk = WET_ALLOC_MEMORY(we_sys, TWE207_SYS);
	wk->we_sys	= we_sys;

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	WazaTool_InitScaleRate(
			&wk->at_scale,
			WE207_SCALE_POKE_S,
			WE207_SCALE_POKE_D,
			WE207_SCALE_POKE_E,
			WE207_SCALE_POKE_SYNC
			);
	wk->at_wait = WE207_SCALE_POKE_WAIT;	

	wk->at_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	WEEffect_TCB_AddPriSet(wk->we_sys, We207_TCB, wk);
}


//-------------------------------------
//	
//	���낢�܂Ȃ���
//	
//=====================================
enum{
	WE212_CAP_SCALE_OUT,
	WE212_CAP_SCALE_IN,
	WE212_CAP_ALPHA_WAIT,
	WE212_CAP_END
};

enum{
	WE212_CAP_OBJ_SCALE_OUT,
	WE212_CAP_ANIME,
	WE212_CAP_FLASH_IN,
	WE212_CAP_OBJ_ALPHA_OUT,
	WE212_END
};

enum{
	WE212_CAP_SCALE_OUT_INIT,
	WE212_CAP_SCALE_OUT_MOVE,
	WE212_CAP_SCALE_OUT_END,
};

#define WE212_SCALE_OUT_KETA	( 100 )
#define WE212_SCALE_S	( 15 * WE212_SCALE_OUT_KETA )
#define WE212_SCALE_D	( 10 )
#define WE212_SCALE_E	( 10 * WE212_SCALE_OUT_KETA )
#define WE212_SYNC_S	( 4 * WE212_SCALE_OUT_KETA )
#define WE212_SCALE_OUT_DIV	( 3 )	// 1/WE212_SCALE_OUT_DIV�Â��炵�Ă���
#define WE212_SCALDE_NUM	(2)
 
#define WE212_ALPHA_S	( 16 )
#define WE212_ALPHA_E	( 10 )

#define WE212_FADE_OUT_NUM	( 3 )

#define WE212_FLASH_WAIT	( 30 )
//#define WE212_FLASH_SYNC	( -2 )
#define WE212_FLASH_SYNC	( 8 )
#define WE212_FLASH_OUT_FLG	( -1 )
#define WE212_FLASH_IN_FLG	( -2 )
#define WE212_FLASH_MSK		( PLANEMASK_BG0|PLANEMASK_BG2|PLANEMASK_BG3 )

#define WE212_CAP_ALPHA_IN_SYNC	( 4 )
#define WE212_CAP_ALPHA_OUT_SYNC	( 8 )
#define WE212_CAP_OBJ_END_FRAME	( 4 )


typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int flash_wait;
	
	// ���낢�܂Ȃ���
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE		cap_scale;
	WAZATOOL_ALPHA_FADE		cap_alpha;
	int cap_seq;
	int cap_scalenum;

	int cap_count;
	int cap_sync;
	int cap_scale_s;
	int cap_scale_e;
	int cap_scale_out_seq;
} TWE212_SYS;

static void We212_InitCapObj( TWE212_SYS* wk )
{
	WazaTool_InitScaleRate(
			&wk->cap_scale,
			wk->cap_scale_s / WE212_SCALE_OUT_KETA,
			WE212_SCALE_D,
			wk->cap_scale_e / WE212_SCALE_OUT_KETA,
			wk->cap_sync / WE212_SCALE_OUT_KETA
			);
	WET_DefaultBlendSet(wk->we_sys, WE212_ALPHA_S, 16 - WE212_ALPHA_S );
	WazaTool_StartAlphaFade(
			&wk->cap_alpha,
			WE212_ALPHA_S,
			WE212_ALPHA_E,
			16 - WE212_ALPHA_S,
			16 - WE212_ALPHA_E,
			(wk->cap_sync / WE212_SCALE_OUT_KETA) * WE212_SCALDE_NUM	
			);
	wk->cap_seq = 0;
	wk->cap_scalenum = 0;
}

static BOOL We212_CalcCapObj( TWE212_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->cap_seq ){
	case WE212_CAP_SCALE_OUT:
		if( WazaTool_CalcAndReflectScaleRateCap( &wk->cap_scale, wk->cap ) == FALSE ){
			WazaTool_InitScaleRate(
					&wk->cap_scale,
					wk->cap_scale_e / WE212_SCALE_OUT_KETA,
					WE212_SCALE_D,
					wk->cap_scale_s / WE212_SCALE_OUT_KETA,
					wk->cap_sync / WE212_SCALE_OUT_KETA
					);
			wk->cap_seq++;
		}
		break;
		
	case WE212_CAP_SCALE_IN:
		if( WazaTool_CalcAndReflectScaleRateCap( &wk->cap_scale, wk->cap ) == FALSE ){
			wk->cap_scalenum++;
			if( wk->cap_scalenum < WE212_SCALDE_NUM ){
				wk->cap_seq = WE212_CAP_SCALE_OUT;
				WazaTool_InitScaleRate(
						&wk->cap_scale,
						wk->cap_scale_s / WE212_SCALE_OUT_KETA,
						WE212_SCALE_D,
						wk->cap_scale_e / WE212_SCALE_OUT_KETA,
						wk->cap_sync / WE212_SCALE_OUT_KETA
						);
			}else{
				wk->cap_seq++;
			}
		}
		break;
		
	case WE212_CAP_ALPHA_WAIT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->cap_seq++;
			ret = TRUE;
		}
		break;
		
	case WE212_CAP_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static BOOL We212_ScaleOut( TWE212_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->cap_scale_out_seq ){
	case WE212_CAP_SCALE_OUT_INIT:
		We212_InitCapObj( wk );
		We212_CalcCapObj( wk );
		wk->cap_scale_out_seq++;
		break;
		
	case WE212_CAP_SCALE_OUT_MOVE:
		if( We212_CalcCapObj( wk ) ){
			wk->cap_count --;
			if( wk->cap_count >= 0 ){
				wk->cap_sync -= wk->cap_sync / WE212_SCALE_OUT_DIV;
				wk->cap_scale_s -= wk->cap_scale_s / WE212_SCALE_OUT_DIV;
				wk->cap_scale_e -= wk->cap_scale_e / WE212_SCALE_OUT_DIV;
				wk->cap_scale_out_seq = WE212_CAP_SCALE_OUT_INIT;
			}else{
				wk->cap_scale_out_seq++;
				ret = TRUE;
			}
		}
		break;
		
	case WE212_CAP_SCALE_OUT_END:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We212_TCB( TCB_PTR tcb, void* work )
{
	TWE212_SYS* wk = work;
	BOOL check1, check2;
	
	switch( wk->seq ){
	case WE212_CAP_OBJ_SCALE_OUT:
		if( We212_ScaleOut( wk ) ){
			wk->seq ++;
			wk->flash_wait = WE212_FLASH_WAIT;

			CATS_ObjectAnimeSeqSetCap( wk->cap, 0 );
			CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
//			G2_ChangeBlendAlpha( 16, 0 );
			CATS_ObjectScaleSetCap( wk->cap, 1,1 );
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					0,
					16,
					16,
					0,
					WE212_CAP_ALPHA_IN_SYNC
					);
		}
		break;

	case WE212_CAP_ANIME:
		
		// �t���b�V���^�X�N�ݒ�
		if( wk->flash_wait == 0 ){

//			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE212_FLASH_SYNC, 0, 16, 0xffff);
			
			// �u���C�g�l�X�J�n	�t���b�V���A�E�g
			ChangeBrightnessRequest( 
					WE212_FLASH_SYNC,
					BRIGHTNESS_WHITE,
					BRIGHTNESS_NORMAL,
					WE212_FLASH_MSK,
					MASK_MAIN_DISPLAY );//*/

			wk->flash_wait = WE212_FLASH_OUT_FLG;
		}else{
			
			if( wk->flash_wait > 0 ){
				wk->flash_wait --;
			}
		}

		if( wk->flash_wait == WE212_FLASH_OUT_FLG ){
//			if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) ){
				
//				PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE212_FLASH_SYNC, 16, 0, 0xffff);
				
				// �u���C�g�l�X�J�n	�t���b�V���C��
				ChangeBrightnessRequest( 
						WE212_FLASH_SYNC,
						BRIGHTNESS_NORMAL,
						BRIGHTNESS_WHITE,
						WE212_FLASH_MSK,
						MASK_MAIN_DISPLAY );//*/
				wk->flash_wait = WE212_FLASH_IN_FLG;	
			}
		}
		
		// �A�j���I���҂�
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq ++;
		}
		break;

	case WE212_CAP_FLASH_IN:
//		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) ){
			wk->seq ++;
			WET_DefaultBlendSet(wk->we_sys, 16, 0 );
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					16,
					0,
					0,
					16,
					WE212_CAP_ALPHA_OUT_SYNC
					);
		}
		break;

	case WE212_CAP_OBJ_ALPHA_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			CATS_ObjectEnableCap( wk->cap, FALSE );
			wk->seq++;
		}
		break;
		
	case WE212_END:
		CATS_ActorPointerDelete_S(wk->cap);
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
 * @brief	���낢�܂Ȃ����p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_212(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE212_SYS* wk;
	SOFT_SPRITE* df_ssp;

	wk = WET_ALLOC_MEMORY(we_sys, TWE212_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// ���낢�܂Ȃ���
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	CATS_ObjectAnimeFrameSetCap( wk->cap, WE212_CAP_OBJ_END_FRAME );
	wk->cap_count = WE212_FADE_OUT_NUM;
	wk->cap_sync = WE212_SYNC_S;
	wk->cap_scale_s	= WE212_SCALE_S;
	wk->cap_scale_e	= WE212_SCALE_E;

	WEEffect_TCB_AddPriSet(wk->we_sys, We212_TCB, wk);
}


//-------------------------------------
//	
//	���񂪂���
//	
//=====================================
enum{
	WE216_SHAKE_INIT,
	WE216_SHAKE_MOVE,
	WE216_SHAKE_END,
};
#define WE216_SHAKE_Y			( 32 )
#define WE216_SHAKE_ONE_SYNC	( 6 )
#define WE216_SHAKE_NUM			( 4 )
typedef struct {
	int	seq;
	WE_SYS_PTR	we_sys;			
	
	// �\�t�g�X�v���C�g�f�[�^
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16 at_y;
	WAZATOOL_CALCMOVE	at_move;
	int at_move_count;

} TWE216_SYS;

static void We216_ShakeInit( TWE216_SYS* wk )
{
	switch( wk->at_move_count ){
	case 0:
	case 2:
		WazaTool_InitStraightSyncFx(
				&wk->at_move,
				0,0,
				0, WE216_SHAKE_Y,
				WE216_SHAKE_ONE_SYNC
				);
		break;

	case 1:
	case 3:
		WazaTool_InitStraightSyncFx(
				&wk->at_move,
				0,0,
				WE216_SHAKE_Y, 0,
				WE216_SHAKE_ONE_SYNC
				);
		break;
	}
}

static void We216_TCB( TCB_PTR tcb, void* work )
{
	TWE216_SYS* wk = work;
	
	switch( wk->seq ){
	case WE216_SHAKE_INIT:
		We216_ShakeInit( wk );
		wk->seq++;
		break;
		
	case WE216_SHAKE_MOVE:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			wk->at_move_count++;
			if( wk->at_move_count < WE216_SHAKE_NUM ){
				wk->seq = WE216_SHAKE_INIT;
			}else{
				wk->seq++;
			}
		}
		break;
		
	case WE216_SHAKE_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	���񂪂����p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_216( WE_SYS_PTR we_sys )
{
	TWE216_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE216_SYS);
	wk->we_sys	= we_sys;

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	// �㉺�^��
	wk->at_move_count = 0;

	WEEffect_TCB_AddPriSet(wk->we_sys, We216_TCB, wk);
}


//-------------------------------------
//	
//	���Ă݂Ȃ�
//	
//=====================================
enum{
	WE233_AT_ROTA_INIT,
	WE233_AT_ROTA_CALC,
	WE233_AT_MOVE_1,
	WE233_DF_MOVE_1,
	WE233_AT_MOVE_2,
	WE233_DF_MOVE_2,
	WE233_END,
};

#define WE233_ROTA_NUM	( 1 )
#define WE233_ROTA_SYNC	( 64 )
#define WE233_STRAIGHT_MOVE_X		( 32 )
#define WE233_STRAIGHT_MOVE_SYNC	( 2 )
#define WE233_STRAIGHT_MOVE1_SYNC	( 8 )

typedef struct {
	int	seq;
	WE_SYS_PTR	we_sys;			
	int vec_x;
	
	// �U���p
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16 at_y;
	WAZATOOL_CALCMOVE	at_move;

	// �h��p
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16 df_y;
	WAZATOOL_CALCMOVE	df_move;
} TWE233_SYS;

static void We233_TCB( TCB_PTR tcb, void* work )
{
	TWE233_SYS* wk = work;

	switch( wk->seq ){
	case WE233_AT_ROTA_INIT:
		// ��]���쏉����
		WazaTool_MakeDefRota( 
				&wk->at_move,
				WE233_ROTA_NUM,
				WE233_ROTA_SYNC
				);
		wk->at_move.work[2] *= wk->vec_x;
		wk->seq++;
		break;
		
	case WE233_AT_ROTA_CALC:
		if( WazaTool_CalcAndReflectRotaFxSsp( &wk->at_move, wk->at_x, wk->at_y - WAZATOOL_DEF_ROTA_W_Y_INT, wk->at_ssp ) == FALSE ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			// ���s�ړ�����
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_x, wk->at_x + WE233_STRAIGHT_MOVE_X,
					0, 0,
					WE233_STRAIGHT_MOVE_SYNC
					);
			wk->at_move.work[1] *= wk->vec_x;
			wk->seq++;

			// ���炩�ɂ��邽��
			WazaTool_CalcStraightFx( &wk->at_move );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}
		break;
		
	case WE233_AT_MOVE_1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}else{

			// �G���s�ړ�����
			WazaTool_InitStraightSyncFx( 
					&wk->df_move,
					wk->df_x, wk->df_x + (WE233_STRAIGHT_MOVE_X * wk->vec_x),
					0, 0,
					WE233_STRAIGHT_MOVE_SYNC
					);
			wk->seq++;
		}
		break;
		
	case WE233_DF_MOVE_1:
		if( WazaTool_CalcStraightFx( &wk->df_move ) ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_move.x );
		}else{

			// ���s�ړ�����
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, wk->at_x,
					0, 0,
					WE233_STRAIGHT_MOVE1_SYNC
					);
			wk->seq++;
		}
		break;

	case WE233_AT_MOVE_2:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );

			// �G���s�ړ�����
			WazaTool_InitStraightSyncFx( 
					&wk->df_move,
					wk->df_move.x, wk->df_x,
					0, 0,
					WE233_STRAIGHT_MOVE1_SYNC
					);
			wk->seq++;
		}
		break;
		
	case WE233_DF_MOVE_2:
		if( WazaTool_CalcStraightFx( &wk->df_move ) ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_move.x );
		}else{
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );

			wk->seq++;
		}
		break;
		
	case WE233_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	���Ă݂Ȃ��p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_233( WE_SYS_PTR we_sys )
{
	TWE233_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE233_SYS);
	wk->we_sys	= we_sys;

	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );

	WEEffect_TCB_AddPriSet(wk->we_sys, We233_TCB, wk);
}


//-------------------------------------
//	
//	���������
//	
//=====================================
enum{
	WE259_INIT_MOVE,
	WE259_MOVE_OBJ,
	WE259_WAIT,
	WE259_INIT_REMOVE,
	WE259_REMOVE_OBJ,
	WE259_END,
};

enum{
	WE259_SSP_SCALE_1,
	WE259_SSP_SCALE_2,
	WE259_SSP_SCALE_3,
	WE259_SSP_END,
};

#define WE259_CAP_OBJ_NUM	( 6 )

#define WE259_OBJ_SCALE_D	( 10 )
#define WE259_OBJ_SCALE_SYNC	( 2 )
#define WE259_OBJ_SCALE1_S	( 10 )
#define WE259_OBJ_SCALE1_E	( 8 )
#define WE259_OBJ_SCALE2_S	( 8 )
#define WE259_OBJ_SCALE2_E	( 15 )
#define WE259_OBJ_SCALE3_S	( 15 )
#define WE259_OBJ_SCALE3_E	( 10 )

#define WE259_OBJ_SCALE1_SX	( 10 )
#define WE259_OBJ_SCALE1_EX	( 9 )
#define WE259_OBJ_SCALE2_SX	( 9 )
#define WE259_OBJ_SCALE2_EX	( 11 )
#define WE259_OBJ_SCALE3_SX	( 11 )
#define WE259_OBJ_SCALE3_EX	( 10 )

/*#define WE259_CAP_MAT_XOFS		( 48 )
#define WE259_CAP_MAT_XOFS_SUB	( 4 )
#define WE259_CAP_MAT_YOFS_SUB	( 24 )//*/

#define WE259_CAP_MAT_R			( 48*FX32_ONE )	// ���a�T�C�Y
#define WE259_CAP_MAT_ROTA		( FX_GET_ROTA_NUM( 90 ) / (WE259_CAP_OBJ_NUM/2) )

#define WE259_CAP_WAIT_MAX	( 8 )
#define WE256_CAP_ANIME_SPEED	( FX32_ONE*2 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int count;
	int wait;

	// �U���I�u�W�F�N�g
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE	at_scale;
	int ssp_seq;

	s16 ssp_y;
	s16 poke_h;
	
	// ���������I�u�W�F�N�g
	CATS_ACT_PTR	cap[ WE259_CAP_OBJ_NUM ];
	int cap_seq[ WE259_CAP_OBJ_NUM  ];
	int cap_wait[ WE259_CAP_OBJ_NUM ];
	
} TWE259_SYS;

// �|�P�������쏀��
static void We259_SSP_Init( TWE259_SYS* wk )
{
	wk->ssp_seq = 0;

	WazaTool_InitScaleRateEx(
			&wk->at_scale,
			WE259_OBJ_SCALE1_SX,
			WE259_OBJ_SCALE1_EX,
			WE259_OBJ_SCALE1_S,
			WE259_OBJ_SCALE1_E,
			WE259_OBJ_SCALE_D,
			WE259_OBJ_SCALE_SYNC
			);
}

static BOOL We259_SSP_Move( TWE259_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->ssp_seq ){
	case WE259_SSP_SCALE_1:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){

			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->ssp_seq++;
			WazaTool_InitScaleRateEx(
					&wk->at_scale,
					WE259_OBJ_SCALE2_SX,
					WE259_OBJ_SCALE2_EX,
					WE259_OBJ_SCALE2_S,
					WE259_OBJ_SCALE2_E,
					WE259_OBJ_SCALE_D,
					WE259_OBJ_SCALE_SYNC
					);
		}
		break;
		
	case WE259_SSP_SCALE_2:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->ssp_seq++;
			WazaTool_InitScaleRateEx(
					&wk->at_scale,
					WE259_OBJ_SCALE3_SX,
					WE259_OBJ_SCALE3_EX,
					WE259_OBJ_SCALE3_S,
					WE259_OBJ_SCALE3_E,
					WE259_OBJ_SCALE_D,
					WE259_OBJ_SCALE_SYNC
					);
		}
		break;
		
	case WE259_SSP_SCALE_3:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
			wk->ssp_seq++;
			ret = TRUE;
		}
		break;
		
	case WE259_SSP_END:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We259_CAP_Init( CATS_ACT_PTR cap, int* p_cap_seq, fx32 frame )
{
	*p_cap_seq = 0;
	CATS_ObjectPriSetCap( cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectEnableCap( cap, TRUE );
	CATS_ObjectAutoAnimeSetCap( cap, TRUE );
	CATS_ObjectAutoAnimeSpeedSetCap( cap, frame );
	// �A�j���V�[�P���X�`�F���W
	CATS_ObjectAnimeSeqSetCap( cap, 0 );		
	CATS_ObjectAnimeFrameSetCap(cap, 0 );


	// 55�t���[����ɂ���߂�
	CATS_ObjectUpdateNumCap( cap, 55*FX32_ONE );
}

// �A�j���[�V����������
static BOOL We259_CAP_Move( CATS_ACT_PTR cap, int* p_cap_seq )
{
	BOOL ret = FALSE;
	
	switch( *p_cap_seq ){
	case 0:		// �I���`�F�b�N
		if( CATS_ObjectAnimeActiveCheckCap( cap ) == FALSE ){
			(*p_cap_seq)++;
			ret = TRUE;
		}
		break;

	case 1:		// �I��
		ret = TRUE;
		break;
	
	default:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We259_TCB( TCB_PTR tcb, void* work )
{
	TWE259_SYS* wk = work;
	BOOL check1, check2;
	int i;

	switch( wk->seq ){
	case WE259_INIT_MOVE:
		We259_SSP_Init( wk );
		We259_CAP_Init( wk->cap[ wk->count ], &wk->cap_seq[ wk->count ], WE256_CAP_ANIME_SPEED );
		wk->seq++;
		break;
		
	case WE259_MOVE_OBJ:
		check1 = We259_SSP_Move( wk );
		check2 = We259_CAP_Move( wk->cap[ wk->count ], &wk->cap_seq[ wk->count ] );
		if( (check1 == check2) && (check1 == TRUE) ){
			// �A�j���V�[�P���X�`�F���W
			CATS_ObjectAnimeSeqSetCap( wk->cap[ wk->count ], 1 );		
			wk->seq++;
		}
		break;

	case WE259_WAIT:
		wk->cap_wait[ wk->count ] --;
		if( wk->cap_wait[ wk->count ] < 0 ){
			wk->count ++;
			if( wk->count < WE259_CAP_OBJ_NUM ){
				wk->seq = WE259_INIT_MOVE;
			}else{
				wk->seq ++;
			}
		}
		break;

	case WE259_INIT_REMOVE:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
			We259_CAP_Init( wk->cap[ i ], &wk->cap_seq[ i ], WE256_CAP_ANIME_SPEED );
		}
		wk->seq++;
		break;
			
	case WE259_REMOVE_OBJ:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
			check1 = We259_CAP_Move( wk->cap[ i ], &wk->cap_seq[ i ] );
		}
		if( check1 == TRUE ){
			wk->seq++;
		}
		break;
		
	case WE259_END:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
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
 * @brief	���������p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_259(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE259_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	int i;
	s16 at_x;
	s16 at_y;
	s16 cap_x;
	s16 cap_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE259_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	
	// �|�P�����̍����@�Ɓ@�ʒu���擾
	wk->ssp_y = at_y;
	wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	

	// ���������
	coap   = WeSysCoapGet(wk->we_sys);
	// �c�蕪�̃I�u�W�F�N�g���쐬
	for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
		if( i==0 ){
			wk->cap[ i ] = cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(csp, crp, &coap);
		}
		CATS_ObjectEnableCap( wk->cap[i], FALSE );

		// �z�u�ʒu�ݒ�
		//     5 4
		//    3   2
		//   1     0
/*		cap_x = WE259_CAP_MAT_XOFS - (WE259_CAP_MAT_XOFS_SUB * (WE259_CAP_MAT_XOFS_SUB * (i / 2)) );
		cap_y = WE259_CAP_MAT_YOFS_SUB * (i / 2);//*/

		cap_x = FX_Mul( FX_CosIdx( WE259_CAP_MAT_ROTA*(i/2) ), WE259_CAP_MAT_R ) >> FX32_SHIFT;
		cap_y = FX_Mul( FX_SinIdx( WE259_CAP_MAT_ROTA*(i/2) ), WE259_CAP_MAT_R ) >> FX32_SHIFT;
		if( (i % 2) == 0 ){
			// ����=�E��
			cap_x = at_x + cap_x;
			CATS_ObjectFlipSetCap( wk->cap[i], TRUE );
		}else{
			// �������
			cap_x = at_x - cap_x;
		}
		cap_y = at_y - cap_y;
		CATS_ObjectPosSetCap( wk->cap[i], cap_x, cap_y );

		// wait�ݒ�
		if( i < 2 ){
			wk->cap_wait[ i ] = WE259_CAP_WAIT_MAX;
		}else{
			wk->cap_wait[ i ] = 0;
		}
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We259_TCB, wk);
}


//-------------------------------------
//	
//	�o�g���^�b�`
//	
//=====================================
enum{
	WE226_OPEN_BALL_INIT,
	WE226_OPEN_BALL,
	WE266_POKE_IN_BALL,
	WE266_CLOSE_BALL,
	WE266_MOVE_BALL,
	WE226_END,
};

#define WE226_SCALE_S	( 10 )
#define WE226_SCALE_E	( 0 )
#define WE226_SCALE_D	( 10 )
#define WE226_SCALE_SYNC	( 8 )

#define WE226_MOVE_SYNC	( 8 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	// �U���I�u�W�F�N�g
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE	at_scale;
	WAZATOOL_CALCMOVE	at_move;
	
	// �{�[���I�u�W�F�N�g
	CATS_ACT_PTR	cap;
	WAZATOOL_CALCMOVE	cap_move;
	int cap_seq;
	s16 cap_x;
	s16 cap_y;

} TWE226_SYS;

static void We226_TCB( TCB_PTR tcb, void* work )
{
	TWE226_SYS* wk = work;
	int ofs_x, ofs_y;

	switch( wk->seq ){
	case WE226_OPEN_BALL_INIT:	// �{�[�����[�Ղ񏉊���
		CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
		wk->seq++;
		break;
		
	case WE226_OPEN_BALL:	// �{�[���I�[�v��
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			CATS_ObjectAutoAnimeSetCap( wk->cap, FALSE );
			wk->seq++;
			WazaTool_InitScaleRate(
					&wk->at_scale,
					WE226_SCALE_S,
					WE226_SCALE_D,
					WE226_SCALE_E,
					WE226_SCALE_SYNC
					);
			ofs_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
			ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
			WazaTool_InitStraightSyncFx(
					&wk->at_move,
					ofs_x, wk->cap_x,
					ofs_y, wk->cap_y,
					WE226_SCALE_SYNC
					);

		}
		break;
		
	case WE266_POKE_IN_BALL:	// �|�P�������ځ[��̂Ȃ���
		WazaTool_CalcAndReflectStraightFxSsp( &wk->at_move, wk->at_ssp );
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) == FALSE ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, TRUE );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );

			CATS_ObjectAnimeSeqSetCap( wk->cap, 1 );
			CATS_ObjectAutoAnimeSpeedSetCap( wk->cap, FX32_ONE );
			CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
			wk->seq++;
		}
		break;
		
	case WE266_CLOSE_BALL:		// �{�[�����Ƃ���
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){

			CATS_ObjectAutoAnimeSetCap( wk->cap, FALSE );
			wk->seq++;
			WazaTool_InitStraightSyncFx(
					&wk->cap_move,
					0, 0,
					wk->cap_y, 0,
					WE226_MOVE_SYNC
					);
		}
		break;
		
	case WE266_MOVE_BALL:
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){

			CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_move.y );
		}else{

			wk->seq++;
		}
		break;
		
	case WE226_END:
		CATS_ActorPointerDelete_S(wk->cap);
		
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
 * @brief	�o�g���^�b�`�p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_226(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE226_SYS* wk;
	s16 at_x, at_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE226_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;


	// �U����
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, FALSE );
//	wk->cap_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
//	wk->cap_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_x = GetWazaEffPos(we_sys, WeSysATNoGet(we_sys), PM_X);
	wk->cap_y = GetWazaEffPos(we_sys, WeSysATNoGet(we_sys), PM_Y);
	
	//�{�[���I�u�W�F
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_y );


	WEEffect_TCB_AddPriSet(wk->we_sys, We226_TCB, wk);
}


//-------------------------------------
//	
//	�����݂₰
//	
//=====================================
enum{
	WE262_FADEIN_INIT,
	WE262_FADEIN,
	WE262_SCALE_OUT,
	WE262_SCALE_WAIT,
	WE262_SCALE_IN,
	WE262_FADEOUT,
	WE262_END,
};

enum{
	WE262_SCALEOUT_Y,
	WE262_SCALEOUT_YX,
	WE262_SCALEOUT_END,
};

enum{
	WE262_SCALEIN_MOVE,
	WE262_SCALEIN_XY_MOVE,
	WE262_SCALEIN_END,
};

#define WE262_ALPHA_IN_S	( 0 )
#define WE262_ALPHA_IN_E	( 8 )
#define WE262_ALPHA_SYNC	( 8 )

#define WE262_SCALE_D		( 10 )

#define WE262_SCALEOUT_SY		( 10 )
#define WE262_SCALEOUT_EY		( 20 )
#define WE262_SCALEOUT_SX		( 10 )
#define WE262_SCALEOUT_EX		( 1 )
#define WE262_SCALEOUT_YSYNC	( 8 )
#define WE262_SCALEOUT_XSYNC	( 4 )
#define WE262_SCALEOUT_WAIT		( 6 )

#define WE262_SCALEIN_SY		( 20 )
#define WE262_SCALEIN_EY		( 10 )
#define WE262_SCALEIN_SX		( 2 )
#define WE262_SCALEIN_EX		( 10 )
#define WE262_SCALEIN_SYNC	( 8 )

#define WE262_SCALEIN_MOVE_DIS	( 64 )
#define WE262_SCALEIN_MOVE_SYNC	( 8 )
#define WE262_SCALEIN_WAIT	( 6 )

#define WE262_SCALE_WAIT_NUM	( 2 )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int poke_h;
	int dy;

	// �|�P��������
	CATS_ACT_PTR	poke_cap_at;
	CATS_ACT_PTR	poke_cap_df;

	CATS_ACT_PTR	poke_cap_at_msk;
	CATS_ACT_PTR	poke_cap_df_msk;
	
	WAZATOOL_CALCMOVE	cap_scale1;
	WAZATOOL_CALCMOVE	cap_scale2;
	WAZATOOL_CALCMOVE	cap_move;
	int cap_seq;
	int cap_wait;
	
	WAZATOOL_ALPHA_FADE	cap_alpha;
	PALETTE_FADE_PTR	pfd;	// �p���b�g�t�F�[�h

	BOOL contest_at;
	BOOL contest_df;
} TWE262_SYS;

#define CLIENT_MAX_NUM	( CLIENT_TYPE_D + 1 )
static const u16 We262_MskOnOff[ CLIENT_MAX_NUM ] = {
	0, 0, 
	1, 0, 0, 1,
};

static void We262_SetPlttColorCap( TWE262_SYS* wk, CATS_ACT_PTR cap )
{
	int plt_bit;

	// �p���b�g�t�F�[�h
	plt_bit = 1 << WazaTool_CapPlttNoGet( cap );
	
	ColorConceChangePfd( wk->pfd, FADE_MAIN_OBJ, plt_bit, 8, 0x0 );
}

static void We262_ScaleOutInit( TWE262_SYS* wk )
{
	int client_type;
	f32 s_x, s_y;
	
	WazaTool_InitScaleRateEx(
			&wk->cap_scale1,
			WE262_SCALE_D,
			WE262_SCALE_D,
			WE262_SCALEOUT_SY,
			WE262_SCALEOUT_EY,
			WE262_SCALE_D,
			WE262_SCALEOUT_YSYNC
			);
	WazaTool_InitScaleRate(
			&wk->cap_scale2,
			WE262_SCALEOUT_SX,
			WE262_SCALE_D,
			WE262_SCALEOUT_EX,
			WE262_SCALEOUT_XSYNC
			);

	wk->cap_seq = 0;
	wk->cap_wait= WE262_SCALEOUT_WAIT;
	
	client_type = WET_ClientTypeGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	CATS_ObjectEnableCap( wk->poke_cap_at_msk, We262_MskOnOff[ client_type ] );
	CATS_ObjectEnableCap( wk->poke_cap_at, TRUE );

	// �g��k���̓R���e�X�g������̂ō��E���]���l����
	WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
	if( wk->contest_at == TRUE ){
		s_x = -s_x;
	}
	CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );
	
	We262_SetPlttColorCap( wk, wk->poke_cap_at );
}

static BOOL We262_ScaleOutMove( TWE262_SYS* wk )
{
	BOOL ret = FALSE;
	f32 s_x, s_y;
	
	switch( wk->cap_seq ){
	case WE262_SCALEOUT_Y:

		WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		// �g��k���̓R���e�X�g������̂ō��E���]���l����
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
		if( wk->contest_at == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );

		WazaTool_PokeOffsetSetOAM(
				wk->poke_cap_at,
				wk->dy, wk->poke_h,
				wk->cap_scale1.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->cap_seq++;
			WazaTool_InitScaleRateEx(
					&wk->cap_scale1,
					WE262_SCALEOUT_SX,
					WE262_SCALEOUT_EX,
					WE262_SCALEOUT_EY,
					WE262_SCALEOUT_EY,
					WE262_SCALE_D,
					WE262_SCALEOUT_XSYNC
					);
		}
		break;
		
	case WE262_SCALEOUT_YX:
		WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		if( WazaTool_CalcScaleRate( &wk->cap_scale2 ) ){
			
			// �l�ݒ�
			wk->cap_scale1.x = wk->cap_scale2.x;

			// �g��k���̓R���e�X�g������̂ō��E���]���l����
			WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
			if( wk->contest_at == TRUE ){
				s_x = -s_x;
			}
			CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );

			WazaTool_PokeOffsetSetOAM(
					wk->poke_cap_at,
					wk->dy, wk->poke_h,
					wk->cap_scale1.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->cap_seq++;
			// �\��OFF
			CATS_ObjectEnableCap( wk->poke_cap_at_msk, FALSE );
			CATS_ObjectEnableCap( wk->poke_cap_at, FALSE );
			ret = TRUE;
		}
		break;
		
	case WE262_SCALEOUT_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We262_ScaleInInit( TWE262_SYS* wk )
{
	s16 mat_x, mat_y;
	f32 s_x, s_y;
	int client_type;
	
	CATS_ObjectPosGetCap( wk->poke_cap_df, &mat_x, &mat_y );
	
	WazaTool_InitStraightSyncFx( 
			&wk->cap_move,
			mat_x, mat_x,
			mat_y - WE262_SCALEIN_MOVE_DIS, mat_y,
			WE262_SCALEIN_MOVE_SYNC
			);

	WazaTool_InitScaleRateEx(
			&wk->cap_scale1,
			WE262_SCALEIN_SX,
			WE262_SCALEIN_EX,
			WE262_SCALEIN_SY,
			WE262_SCALEIN_EY,
			WE262_SCALE_D,
			WE262_SCALEIN_SYNC
			);

	// �P��l��ݒ�
	WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
	if( wk->contest_df == TRUE ){
		s_x = -s_x;
	}
	CATS_ObjectScaleSetCap( wk->poke_cap_df, s_x, s_y );
	WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );

	wk->cap_seq = 0;
	wk->cap_wait = WE262_SCALEIN_WAIT;

	client_type = WET_ClientTypeGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
	CATS_ObjectEnableCap( wk->poke_cap_df_msk, We262_MskOnOff[ client_type ] );
	CATS_ObjectEnableCap( wk->poke_cap_df, TRUE );

	We262_SetPlttColorCap( wk, wk->poke_cap_df );
}

static BOOL We262_ScaleInMove( TWE262_SYS* wk )
{
	f32 s_x, s_y;
	BOOL ret = FALSE;
	BOOL check;
	
	switch( wk->cap_seq ){
	case WE262_SCALEIN_MOVE:
		wk->cap_wait--;
		WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );
		if( wk->cap_wait < 0 ){
			wk->cap_seq++;
		}
		break;
		
	case WE262_SCALEIN_XY_MOVE:
		WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );
		
		// �g��k���̓R���e�X�g������̂ō��E���]���l����
		check = WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );

		if( wk->contest_df == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->poke_cap_df, s_x, s_y );
		if( check == FALSE ){
			wk->cap_seq++;
			ret = TRUE;
		}
		break;
		
	case WE262_SCALEIN_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We262_TCB( TCB_PTR tcb, void* work )
{
	TWE262_SYS* wk = work;

	switch( wk->seq ){
	case WE262_FADEIN_INIT:
		WET_DefaultBlendSet( wk->we_sys, WE262_ALPHA_IN_S, 16 - WE262_ALPHA_IN_S );
		WazaTool_StartAlphaFade( 
				&wk->cap_alpha, 
				WE262_ALPHA_IN_S,
				WE262_ALPHA_IN_E,
				16 - WE262_ALPHA_IN_S,
				16 - WE262_ALPHA_IN_E,
				WE262_ALPHA_SYNC);
		wk->seq++;
		break;
		
	case WE262_FADEIN:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			We262_ScaleOutInit( wk );
		}
		break;
		
	case WE262_SCALE_OUT:
		if( We262_ScaleOutMove( wk ) ){
			wk->seq++;

			wk->wait = WE262_SCALE_WAIT_NUM;
		}
		break;

	case WE262_SCALE_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			We262_ScaleInInit( wk );
			wk->seq++;
		}
		break;
		
	case WE262_SCALE_IN:
		if( We262_ScaleInMove( wk ) ){
			wk->seq++;
			WazaTool_StartAlphaFade( 
					&wk->cap_alpha, 
					WE262_ALPHA_IN_E,
					WE262_ALPHA_IN_S,
					16 - WE262_ALPHA_IN_E,
					16 - WE262_ALPHA_IN_S,
					WE262_ALPHA_SYNC);
		}
		break;
		
	case WE262_FADEOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE262_END:
		// �I��
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}

	// �c��OAM�`��
	CATS_Draw(wk->crp);	
}


//----------------------------------------------------------------------------
/**
 * @brief	�����݂₰�p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_262( WE_SYS_PTR we_sys )
{
	TWE262_SYS* wk;
	SOFT_SPRITE* ssp;
	s16 at_x, at_y;
	s16 df_x, df_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE262_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	wk->pfd		= WeSysPFDGet(wk->we_sys);


	// �U����
	ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x = SoftSpriteParaGet( ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( ssp, SS_PARA_POS_Y );
	at_y -= SoftSpriteParaGet( ssp, SS_PARA_SHADOW_HEIGHT );

	// �h�䑤
	ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	df_x = SoftSpriteParaGet( ssp, SS_PARA_POS_X );
	df_y = SoftSpriteParaGet( ssp, SS_PARA_POS_Y );
	df_y -= SoftSpriteParaGet( ssp, SS_PARA_SHADOW_HEIGHT );

	// �U�����@�����@�ʒu���擾
	wk->dy = at_y;
	wk->poke_h = WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	
	//����
	// �����̉e
	wk->poke_cap_at = WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectPriSetCap( wk->poke_cap_at, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->poke_cap_at, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->poke_cap_at, at_x, at_y );
	CATS_ObjectEnableCap( wk->poke_cap_at, FALSE );
	CATS_ObjectObjModeSetCap(wk->poke_cap_at, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap( wk->poke_cap_at, CLACT_AFFINE_DOUBLE );

	// ����̉e
	wk->poke_cap_df = WeSysPokeCapGet(wk->we_sys, 1);
	CATS_ObjectPriSetCap( wk->poke_cap_df, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->poke_cap_df, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->poke_cap_df, df_x, df_y );
	CATS_ObjectEnableCap( wk->poke_cap_df, FALSE );
	CATS_ObjectObjModeSetCap(wk->poke_cap_df, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap( wk->poke_cap_df, CLACT_AFFINE_DOUBLE );
	CATS_ObjectAffinePosSetCap( wk->poke_cap_df, 0, SOFT_SPRITE_SIZE_Y / 2 );

	// �R���e�X�g�`�F�b�N
	wk->contest_at = ContestFlipCheck(wk->we_sys, WEDEF_DROP_M1 ); 
	wk->contest_df = ContestFlipCheck(wk->we_sys, WEDEF_DROP_E1 ); 

	// �}�X�N�p
	wk->poke_cap_at_msk = WeSysPokeCapGet(wk->we_sys, 2);
	wk->poke_cap_df_msk = WeSysPokeCapGet(wk->we_sys, 3);

	CATS_ObjectEnableCap( wk->poke_cap_at_msk, FALSE );
	CATS_ObjectEnableCap( wk->poke_cap_df_msk, FALSE );


	WEEffect_TCB_AddPriSet(wk->we_sys, We262_TCB, wk);
}


//-------------------------------------
//	
//	�ӂ�����
//	
//=====================================
enum{
	WE286_SCALEIN_INIT,
	WE286_SCALEIN,
	WE286_MOVE_POKE,
	WE286_SCALEOUT,
	WE286_END,
};

#define WE286_ZANZOU_NUM		( 3 )
#define WE286_ZANZOU_FUU_OAM	( 0 )	// ��OAM�̗v�f��
#define WE286_ZANZOU_SCALE_S	( 25 )
#define WE286_ZANZOU_SCALE_E	( 10 )
#define WE286_ZANZOU_SCALE_D	( 10 )
#define WE286_ZANZOU_SCALE_SYNC	( 10 )
#define WE286_ZANZOU_SCALEOUT_SYNC	( 6 )

#define WE286_ZANZOU_WAIT		( 9 )
#define WE286_ZANZOU_OUT_WAIT	( 5 )
#define WE286_SHAKE_X			( 4 )
#define WE286_SHAKE_SYNC		( 1 )
#define WE286_SHAKE_NUM			( 6 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	// �h�䑤
	SOFT_SPRITE* df_ssp;
	WAZATOOL_CALCMOVE	df_move;
	s16 df_x;
	s16 df_y;
	
	// ����c���I�u�W�F�N�g
	CATS_ACT_PTR zz_cap[ WE286_ZANZOU_NUM ];
	WAZATOOL_ZANZOU zz_sys;
	WAZATOOL_CALCMOVE	zz_move;
} TWE286_SYS;

static void We286_ZZScaleInInit( TWE286_SYS* wk )
{
	WazaTool_InitScaleRate( 
			&wk->zz_move,
			WE286_ZANZOU_SCALE_S,
            WE286_ZANZOU_SCALE_D,   
			WE286_ZANZOU_SCALE_E,
            WE286_ZANZOU_SCALE_SYNC
			);

	WazaTool_InitZanzou( 
			&wk->zz_sys,
			&wk->zz_move,
			WazaTool_CalcScaleRate,
			wk->df_x, wk->df_y,
			WE286_ZANZOU_WAIT,
			WE286_ZANZOU_NUM,
			WAZATOOL_ZANZOU_TYPE_SCALE,
			wk->zz_cap[ 2 ],		// ���̑�
			wk->zz_cap[ 1 ],		// ���̑�
			wk->zz_cap[ WE286_ZANZOU_FUU_OAM ],		// ��
			NULL
			);
}

static void We286_ZZScaleOutInit( TWE286_SYS* wk )
{
	WazaTool_InitScaleRate( 
			&wk->zz_move,
			WE286_ZANZOU_SCALE_E,
            WE286_ZANZOU_SCALE_D,   
			WE286_ZANZOU_SCALE_S,
            WE286_ZANZOU_SCALEOUT_SYNC
			);

	WazaTool_InitZanzou( 
			&wk->zz_sys,
			&wk->zz_move,
			WazaTool_CalcScaleRate,
			wk->df_x, wk->df_y,
			WE286_ZANZOU_OUT_WAIT,
			WE286_ZANZOU_NUM,
			WAZATOOL_ZANZOU_TYPE_SCALE,
			wk->zz_cap[ WE286_ZANZOU_FUU_OAM ],		// ��
			wk->zz_cap[ 1 ],		// ���̑�
			wk->zz_cap[ 2 ],		// ���̑�
			NULL
			);

	CATS_ObjectEnableCap( wk->zz_cap[ WE286_ZANZOU_FUU_OAM ], TRUE );
}

static void We286_TCB( TCB_PTR tcb, void* work )
{
	TWE286_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE286_SCALEIN_INIT:
		We286_ZZScaleInInit( wk );
		wk->seq++;
		break;

	case WE286_SCALEIN:
		if( WazaTool_CalcZanzou( &wk->zz_sys ) == FALSE ){
			CATS_ObjectEnableCap( wk->zz_cap[ WE286_ZANZOU_FUU_OAM ], TRUE );
			wk->seq++;

			// �|�P�����V�F�C�N
			WazaTool_InitShake( 
					&wk->df_move,
					WE286_SHAKE_X,
					0,
					WE286_SHAKE_SYNC,
					WE286_SHAKE_NUM
					);
		}
		break;
		
	case WE286_MOVE_POKE:
		if( WazaTool_CalcAndReflectShakeSsp( &wk->df_move, wk->df_x, wk->df_y, wk->df_ssp ) == FALSE ){
			wk->seq++;

			We286_ZZScaleOutInit( wk );
		}
		break;
		
	case WE286_SCALEOUT:
		if( WazaTool_CalcZanzou( &wk->zz_sys ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE286_END:
		for( i=0; i<WE286_ZANZOU_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->zz_cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}

	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 * @brief	�ӂ�����p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_286(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE286_SYS* wk;
	int i;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE286_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �h�䑤
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	wk->df_y -= SoftSpriteParaGet( wk->df_ssp, SS_PARA_SHADOW_HEIGHT );
	
	// �c��
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE286_ZANZOU_NUM; i++ ){
		if( i == WE286_ZANZOU_FUU_OAM ){
			wk->zz_cap[ i ] = cap;
			// �ŏ��̃A�N�^�[�͈Ⴄ�G�ɂȂ�
			CATS_ObjectAnimeSeqSetCap( wk->zz_cap[ i ], 1 );
		}else{
			wk->zz_cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
			// �ق��͔�����
			CATS_ObjectObjModeSetCap( wk->zz_cap[ i ], GX_OAM_MODE_XLU );
		}
		CATS_ObjectPriSetCap( wk->zz_cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->zz_cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectPosSetCap( wk->zz_cap[ i ], wk->df_x, wk->df_y );
		CATS_ObjectEnableCap( wk->zz_cap[ i ], FALSE );
		CATS_ObjectAffineSetCap( wk->zz_cap[ i ], CLACT_AFFINE_DOUBLE );
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We286_TCB, wk);
}


//-------------------------------------
//	
//	����˂�
//	
//=====================================
enum{
	WE288_MOVE_START,
	WE288_FADE_IN,
	WE288_FADE_OUT_WAIT,
	WE288_FADE_OUT,
	WE288_END,
};


#define WE288_CAP_NUM			( 6 )	// ������������288.s��������
#define WE288_CAP_H_SUM			( 5 )	// �㉺�͉��{���œ�������
#define WE288_CAP_H_DIS			( FX32_ONE*10 )
#define WE288_CAP_ROTA_S		( FX_GET_ROTA_NUM( 0 ) )
#define WE288_CAP_ROTA_E		( FX_GET_ROTA_NUM( 180 ) )
#define WE288_CAP_ROTA_SYNC		( 48 )
#define WE288_CAP_ROTA_WIDTH	( FX32_ONE*50 )
#define WE288_CAP_ALPHA_S		( 1 )
#define WE288_CAP_ALPHA_E		( 16 )
#define WE288_CAP_ALPHA_SYNC	( 10 )

#define WE288_CAP_ALPHAOUT_WAIT	( WE288_CAP_ROTA_SYNC - (WE288_CAP_ALPHA_SYNC*2) )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int vec_x;

	//����˂�
	CATS_ACT_PTR cap[ WE288_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ WE288_CAP_NUM ];	// ���ړ�
	WAZATOOL_ALPHA_FADE cap_alpha;	// �A���t�@�ϊ�
	s16 cap_cx;
	s16 cap_cy;
} TWE288_SYS;

static void We288_CapInit( TWE288_SYS* wk, int vec_x )
{
	int i;
	int rota_offs_one;

	rota_offs_one = FX_GET_ROTA_NUM( 360 ) / WE288_CAP_NUM;
	
	// �v�Z�f�[�^�쐬
	for( i=0; i<WE288_CAP_NUM; i++ ){
		WazaTool_InitRotaFx(
				&wk->cap_move[ i ],
				WE288_CAP_ROTA_S,
				WE288_CAP_ROTA_E,
				0,0,
				WE288_CAP_ROTA_WIDTH, 0,
				WE288_CAP_ROTA_SYNC
				);
		wk->cap_move[i].work[1] += (rota_offs_one*i);
		wk->cap_move[i].work[5] *= vec_x;
	}

}

static void We288_CapMove( TWE288_SYS* wk )
{
	int i;
	s16 ofs_y;
	u16 rota;

	for( i=0; i<WE288_CAP_NUM; i++ ){
		
		// �v�Z
		WazaTool_CalcRotaFx( &wk->cap_move[ i ] );
		
		// y�I�t�Z�b�g���W�����߂�
		rota = wk->cap_move[ i ].work[ 1 ] * WE288_CAP_H_SUM;
		ofs_y = FX_Mul( FX_SinIdx( rota ), WE288_CAP_H_DIS*wk->vec_x ) >> FX32_SHIFT;

		// ���f
		CATS_ObjectPosSetCap( wk->cap[ i ],
				wk->cap_cx + wk->cap_move[ i ].x,
				wk->cap_cy + ofs_y );

		// �p�x��BG�D�揇�ʂ�ς���
		if( (wk->cap_move[ i ].work[ 1 ] >= FX_GET_ROTA_NUM(90)) &&
			(wk->cap_move[ i ].work[ 1 ] <= FX_GET_ROTA_NUM(269)) ){
			
			CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		}else{

			CATS_ObjectBGPriSetCap( wk->cap[ i ], BT_3DPriorityGet(wk->we_sys)+1 );
		}//*/
	}
}

static void We288_TCB( TCB_PTR tcb, void* work )
{
	TWE288_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE288_MOVE_START:
		// �A���t�@�ݒ�
		WET_DefaultBlendSet( wk->we_sys,
				WE288_CAP_ALPHA_S, 16 - WE288_CAP_ALPHA_S );
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				WE288_CAP_ALPHA_S, WE288_CAP_ALPHA_E,
				16 - WE288_CAP_ALPHA_S, 16 - WE288_CAP_ALPHA_E,
				WE288_CAP_ALPHA_SYNC
				);
		// �I�u�W�F
		We288_CapInit( wk, wk->vec_x );
		We288_CapMove( wk );
		wk->seq++;
		break;
		
	case WE288_FADE_IN:
		We288_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			wk->wait = WE288_CAP_ALPHAOUT_WAIT;
		}
		break;
		
	case WE288_FADE_OUT_WAIT:
		We288_CapMove( wk );
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					WE288_CAP_ALPHA_E, WE288_CAP_ALPHA_S, 
					16 - WE288_CAP_ALPHA_E, 16 - WE288_CAP_ALPHA_S, 
					WE288_CAP_ALPHA_SYNC
					);
		}
		break;
		
	case WE288_FADE_OUT:
		We288_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;

	case WE288_END:
		for( i=0; i<WE288_CAP_NUM; i++ ){
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
 * @brief	����˂�p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_288(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE288_SYS* wk;
	int i;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE288_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �U����
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->cap_cx = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	wk->cap_cy = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// ����˂�
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE288_CAP_NUM ; i++ ){
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

	WEEffect_TCB_AddPriSet(wk->we_sys, We288_TCB, wk);
}


//-------------------------------------
//	
//	�����Ԃ�
//	
//=====================================
#define WE320_CAP_NUM	( 15 )		// ������������we_320.s���ς���
#define WE320_CAP_GRA_NUM	( 3 )	// �G�̎��
#define WE320_CAP_STR_SX	( 0 )
#define WE320_CAP_STR_EX	( 256 )
#define WE320_CAP_STR_SY	( 0 )
#define WE320_CAP_STR_EY	( -128 )
#define WE320_CAP_STR_SYNC	( 59 )

#define WE320_CAP_Y_OFS_ROTA	( FX_GET_ROTA_NUM( 2 ) )
#define WE320_CAP_Y_HEIGHT		( FX32_ONE*14 )
#define WE320_CAP_SCALE_DEF		( 1.0f )
#define WE320_CAP_SCALE_NUM		( FX32_CONST(0.17f) )

#define WE320_CAP_START_WAIT	( 6 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int vec_x;
	int vec_y;

	//����
	CATS_ACT_PTR cap[ WE320_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ WE320_CAP_NUM ];	// �΂߈ړ�
	int cap_wait;
	int cap_count;
} TWE320_SYS;

static void We320_CapObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_wtc, int vec_x, int vec_y )
{
	s16 n_x, n_y;

	CATS_ObjectPosGetCap( cap, &n_x, &n_y );
	
	WazaTool_InitStraightSyncFx( 
			p_wtc,
			n_x + (WE320_CAP_STR_SX * vec_x),
			n_x + (WE320_CAP_STR_EX * vec_x),
			n_y + (WE320_CAP_STR_SY * vec_y),
			n_y + (WE320_CAP_STR_EY * vec_y),
			WE320_CAP_STR_SYNC
			);

	CATS_ObjectEnableCap( cap, TRUE );
}

static BOOL We320_CapObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_wtc )
{
	s16 cap_x, cap_y;
	s16 ofs_y;
	fx32 scale_work;
	f32 scale;
	u16 rota;
	
	if( WazaTool_CalcAndReflectStraightFxCap( p_wtc, cap ) ){
		
		CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

		rota = cap_x * WE320_CAP_Y_OFS_ROTA;
		
		// x���W�ɂ��Y���W�̔g�Ɗg��k���l�����߂�
		// Y���W
		ofs_y = FX_Mul( FX_SinIdx( rota ), WE320_CAP_Y_HEIGHT ) >> FX32_SHIFT;
		CATS_ObjectPosSetCap( cap, cap_x, cap_y + ofs_y );

		// �g�k�l
		scale_work = FX_Mul( FX_SinIdx( rota ), WE320_CAP_SCALE_NUM );
		scale_work *= -1;
		scale = WE320_CAP_SCALE_DEF + FX_FX32_TO_F32( scale_work );
		CATS_ObjectScaleSetCap( cap, scale, scale );
		return FALSE;
	}

	return TRUE;
}

static BOOL We320_CapObjManager( TWE320_SYS* wk )
{
	int i;
	BOOL check;
	
	// ���ˊǗ�
	if( wk->cap_count < WE320_CAP_NUM ){
		wk->cap_wait++;
		if( wk->cap_wait > WE320_CAP_START_WAIT ){
			wk->cap_wait = 0;
			
			We320_CapObjStart(
					wk->cap[ wk->cap_count ], 
					&wk->cap_move[ wk->cap_count ],
					wk->vec_x, wk->vec_y );
			wk->cap_count++;
		}
	}

	// ����Ǘ�
	for( i = 0; i < wk->cap_count; i++ ){

		check = We320_CapObjMove( wk->cap[ i ], &wk->cap_move[ i ] );
	}

	// �I���`�F�b�N��
	if( wk->cap_count >= WE320_CAP_NUM ){
		if( check == TRUE ){
			return TRUE;
		}
	}

	return FALSE;
}

static void We320_TCB( TCB_PTR tcb, void* work )
{
	TWE320_SYS* wk = work;
	int i;

	if( We320_CapObjManager(wk) ){

		// �I��
		for( i=0; i<WE320_CAP_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}else{

		CATS_Draw(wk->crp);
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	���J�p�^�X�N�o�^
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_320(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE320_SYS* wk;
	int i;
	s16 at_x, at_y;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE320_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// �U����
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// ����
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE320_CAP_NUM ; i++ ){
		if( i == 0 ){
			wk->cap[ i ] =  cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
		CATS_ObjectPriSetCap( wk->cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectAffineSetCap(wk->cap[ i ], CLACT_AFFINE_DOUBLE);
		CATS_ObjectEnableCap(wk->cap[ i ], FALSE);
		CATS_ObjectPosSetCap( wk->cap[ i ], at_x, at_y );

		// �G��ύX
		CATS_ObjectAnimeSeqSetCap( wk->cap[ i ], i % WE320_CAP_GRA_NUM );
	}
	
	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->vec_y = WazaTool_VecChangeY( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	WEEffect_TCB_AddPriSet(wk->we_sys, We320_TCB, wk);
}


//-------------------------------------
//	
//	������肫
//	
//=====================================

// ������肫�@�h�䑤����
enum{
	WE326_DF_SWITCH,
	WE326_DF_WAIT,
	WE326_DF_END,
};

#define WE326_ROTA_ADD_NUM	( FX_GET_ROTA_NUM(180) / SOFT_SPRITE_SIZE_Y )
#define WE326_ROTA_NUM_0	( FX_GET_ROTA_NUM(180) )
#define WE326_ROTA_NUM_1	( FX_GET_ROTA_NUM(180) )
#define WE326_WIDTH0_NUM		( 5 )
#define WE326_WIDTH1_NUM		( -5 )
#define WE326_WIDTH2_NUM		( 10 )
#define WE326_CHANGE_NUM	( 3 )
#define WE326_CHANGE_WAIT	( 16 )
#define WE326_ROTA0_WIDTH	( 16*FX32_ONE )
#define WE326_ROTA1_WIDTH	( -16*FX32_ONE )
#define WE326_ROTA2_WIDTH	( 20*FX32_ONE )
#define WE326_WIDTH_OFS	( 1*FX32_ONE )
#define WE326_MAT_OFS	(-8)
typedef struct {
	WE_SYS_PTR we_sys;
	WAZATOOL_DEFLASTER_PTR p_laster;
	int seq;

	SOFT_SPRITE* ssp;

	int effect_y;
	int center_y;
	int rota_num;
	fx32 rota_width;
	int rota_width_ofs_flg;
	int width_a;
	int wait;
	int count;
	u32 init_num;
} TWE326_DF_SYS;

static void We326DF_ParamSet( TWE326_DF_SYS* wk )
{
	switch( wk->count ){
	case 0:
		wk->rota_num	= WE326_ROTA_NUM_0;
		wk->width_a		= WE326_WIDTH0_NUM;
		wk->rota_width	= WE326_ROTA0_WIDTH;
		wk->wait		= WE326_CHANGE_WAIT;
		break;

	case 1:
		wk->rota_num = WE326_ROTA_NUM_1;
		wk->width_a = WE326_WIDTH1_NUM;
		wk->rota_width	= WE326_ROTA1_WIDTH;
		wk->wait	= WE326_CHANGE_WAIT;
		break;

	case 2:
		wk->rota_num = WE326_ROTA_NUM_0;
		wk->width_a = WE326_WIDTH2_NUM;
		wk->rota_width	= WE326_ROTA2_WIDTH;
		wk->wait	= WE326_CHANGE_WAIT;
		wk->wait	= WE326_CHANGE_WAIT;
		break;
	}
}

static void We326DF_BuffSet( TWE326_DF_SYS* wk )
{
	u32* buff = WazaTool_GetDefLasterWriteBuff( wk->p_laster );
	int i;
	s16 ofs_x;
	s16 now_x;
	s16 now_y;
	u16 rota_num;
	int width;
	int start = wk->effect_y + WE326_MAT_OFS;
	int end = wk->effect_y + SOFT_SPRITE_SIZE_Y - WE326_MAT_OFS;
	int in_buff;

	if( start < 0 ){
		start = 0;
	}
	if( end > 192 ){
		end = 192;
	}
	
	// �k�킹�邽�߉�]���a�̕���␳����^�C�~���O��
	// ���݂ɕς���
	wk->rota_width_ofs_flg *= -1;
	
	// sin�J�[�u���쐬��wodth_a�ƍ��W�����g�p���ĉ��ړ��l�����߂�
	for( i= start; i< end; i++ ){

		if( i & 2 ){
			width = wk->rota_width + (WE326_WIDTH_OFS * wk->rota_width_ofs_flg);
		}else{
			width = wk->rota_width - (WE326_WIDTH_OFS * wk->rota_width_ofs_flg);
		}
		
		rota_num = wk->rota_num + WE326_ROTA_ADD_NUM * (i - start);
		ofs_x = FX_Mul( FX_SinIdx( rota_num ), width ) >> FX32_SHIFT;
		ofs_x += ((i - wk->center_y) * wk->width_a) / 10;

		// �l�ݒ�
		now_x = wk->init_num & 0xffff;
		now_y = wk->init_num >> 16;

		// 1�O�̃o�b�t�@�ɓ���Ă���
		in_buff = i - 1;
		if( in_buff < 0 ){
			in_buff += 192;
		}
		buff[ in_buff ] = WazaTool_GetLasterBuffMatrixData( now_x + ofs_x, now_y );
	}
}

static void We326DF_TCB( TCB_PTR tcb, void* work )
{
	TWE326_DF_SYS* wk = work;

	switch( wk->seq ){
	case WE326_DF_SWITCH:
		We326DF_ParamSet( wk );
		We326DF_BuffSet( wk );
		wk->seq++;
		break;
		
	case WE326_DF_WAIT:
		wk->wait --;
		We326DF_BuffSet( wk );
		if( wk->wait < 0 ){
			wk->count++;
			if( wk->count < WE326_CHANGE_NUM ){
				wk->seq = WE326_DF_SWITCH;
			}else{
				wk->seq++;
			}
		}
		break;
		
	case WE326_DF_END:
		SoftSpriteParaSet( wk->ssp, SS_PARA_VANISH, FALSE );
		WazaTool_StopDefLaster( wk->p_laster );
		WazaTool_DeleteDefLaster( wk->p_laster );

		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );

		// �L�����N�^�f�[�^�N���A
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�_�ʗ͂��������G�t�F�N�g
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_326DF(WE_SYS_PTR we_sys)
{
	TWE326_DF_SYS* wk;
	SOFT_SPRITE* ssp;
	s16 ssp_x, ssp_y;
	int client_type;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_DF_SYS);
	wk->we_sys	= we_sys;
	
	// �h�䑤���W���擾
	wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	ssp_y -= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);

	SoftSpriteParaSet( wk->ssp, SS_PARA_VANISH, TRUE );
	
	wk->center_y = ssp_y;
	
	ssp_x = ssp_x - (SOFT_SPRITE_SIZE_X/2);
	wk->effect_y = ssp_y - (SOFT_SPRITE_SIZE_Y/2);
	
	wk->init_num = WazaTool_GetLasterBuffMatrixData( -ssp_x, -wk->effect_y );

	// ���X�^�[�V�X�e���쐬
	wk->p_laster = WazaTool_InitDefLaster( 
			WazaTool_GetLasterBGDestAddr( BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT) ),
			wk->init_num,
			WeSysHeapAreaGet(wk->we_sys)
			);

	wk->rota_width_ofs_flg = 1;


	// ���Ă�OBJ�̈ʒu�ɂ��BGpriority��ύX����
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	if( (client_type == CLIENT_TYPE_B) || (client_type == CLIENT_TYPE_C) ){
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We326DF_TCB, wk);
}


//-------------------------------------
//	
//	�˂����܂�
//	
//=====================================
// wnd�}�X�N�`�u���C�g�l�X�t�F�[�h
enum{
	WE252_BACK_MASKFADE_START,
	WE252_BACK_MASKFADE,
	WE252_BACK_MASKFADE_AND_BRFADEOUT,
	WE252_BACK_BRIGHTNESS_FADEOUT,
	WE252_BACK_BRIGHTNESS_FADEIN,
	WE252_BACK_END,
};

#define WE252_BACK_MSKFADE_SX	( 127 )
#define WE252_BACK_MSKFADE_EX	( 0 )
#define WE252_BACK_MSKFADE_SYNC	( 8 )

#define WE252_BACK_BROUT_SYNC	( 8 )
//#define WE252_BACK_BRIN_SYNC	( 20 )
#define WE252_BACK_BRIN_SYNC	( 0 )

#define WE252_BACK_BR_WAIT		( 7 )

typedef struct {
	WE_SYS_PTR we_sys;
	int seq;
	int wait;
	WAZATOOL_CALCMOVE wnd_move;
}TWE252_BACK_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�˂����܂��̔w�i�G�t�F�N�g
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We252Back_TCB( TCB_PTR tcb, void* work )
{
	TWE252_BACK_SYS* wk = work;

	switch( wk->seq ){
	case WE252_BACK_MASKFADE_START:
		WazaTool_InitStraightSyncFx(  
				&wk->wnd_move,
				WE252_BACK_MSKFADE_SX,
				WE252_BACK_MSKFADE_EX,
				0,0,
				WE252_BACK_MSKFADE_SYNC
				);
		// �}�X�N�ݒ�
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
		WET_DefaultWndMskSet( 
				wk->we_sys,
				WET_WNDMSK_0,
				FALSE );
		G2_SetWnd0Position( 0, 0, 255, 191 );
		wk->wait = WE252_BACK_BR_WAIT;
		wk->seq++;
		break;
		
	case WE252_BACK_MASKFADE:
		wk->wait --;
		if( wk->wait < 0 ){

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE252_BACK_BRIN_SYNC, 0, 16, 0xffff);
/*			// �u���C�g�l�X�t�F�[�h
			ChangeBrightnessRequest(
					WE252_BACK_BROUT_SYNC,
					BRIGHTNESS_WHITE,
					BRIGHTNESS_NORMAL,
					(1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND)),
					MASK_MAIN_DISPLAY
					);//*/

			wk->seq++;
		}
		break;

	case WE252_BACK_MASKFADE_AND_BRFADEOUT:
		if( WazaTool_CalcStraightFx( &wk->wnd_move ) ){
			G2_SetWnd0Position( 
					127 - wk->wnd_move.x,
					0,
					128 + wk->wnd_move.x,
					191 );
		}else{
			wk->seq++;
		}
		break;
		
	case WE252_BACK_BRIGHTNESS_FADEOUT:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;

			// �E�B���h�E�}�X�NOFF
			GX_SetVisibleWnd( GX_WNDMASK_NONE );

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE252_BACK_BRIN_SYNC, 16, 0, 0xffff);
			
			// �u���C�g�l�X�t�F�[�h
/*			ChangeBrightnessRequest(
					WE252_BACK_BRIN_SYNC,
					BRIGHTNESS_NORMAL,
					BRIGHTNESS_WHITE,
					(1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND)),
					MASK_MAIN_DISPLAY
					);//*/
		}
		break;
		
	case WE252_BACK_BRIGHTNESS_FADEIN:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;
		}
		break;
			
	case WE252_BACK_END:
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�˂����܂����������G�t�F�N�g
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_252Back(WE_SYS_PTR we_sys)
{
	TWE252_BACK_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_DF_SYS);
	wk->we_sys	= we_sys;

	WEEffect_TCB_AddPriSet(wk->we_sys, We252Back_TCB, wk);
}

enum{
	WE252_CAP_START,
	WE252_CAP_ALPHAIN,
	WE252_CAP_ANM,
	WE252_CAP_ALPHAOUT,
	WE252_CAP_END,
};
#define WE252_CAP_ALPHA_S	( 0 )
#define WE252_CAP_ALPHA_E	( 16 )
#define WE252_CAP_SYNC		( 8 )
typedef struct {
	WE_SYS_PTR we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	CATS_ACT_PTR cap;
	
	WAZATOOL_ALPHA_FADE alpha;
} TWE252_CAP_DRAW;


static void WeCat252_DrawCapTcb( TCB_PTR tcb, void* work )
{
	TWE252_CAP_DRAW* wk = work;
	
	switch( wk->seq ){
	case WE252_CAP_START:
		WET_DefaultBlendSet( wk->we_sys, WE252_CAP_ALPHA_S, 16 - WE252_CAP_ALPHA_S );			
		WazaTool_StartAlphaFade(
				&wk->alpha,
				WE252_CAP_ALPHA_S, WE252_CAP_ALPHA_E,
				16 - WE252_CAP_ALPHA_S, 16 - WE252_CAP_ALPHA_E,
				WE252_CAP_SYNC
				);
		wk->seq++;
		break;
		
	case WE252_CAP_ALPHAIN:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE252_CAP_ANM:
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->alpha,
					WE252_CAP_ALPHA_E, WE252_CAP_ALPHA_S,
					16 - WE252_CAP_ALPHA_E, 16 - WE252_CAP_ALPHA_S,
					WE252_CAP_SYNC
					);
		}
		break;
		
	case WE252_CAP_ALPHAOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE252_CAP_END:
		CATS_ActorPointerDelete_S(wk->cap);
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
 * @brief	�I�[�g�A�j�����I���܂ŕ`��
 *
 *	@param	we_sys	�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	csp		�Z���A�N�^�[�c�[���V�X�e��
 *	@param	crp		�Z���A�N�^�[���\�[�X�V�X�e��
 *	@param	cap		�Z���A�N�^�[�c�[���I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_252_DrawCap(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE252_CAP_DRAW* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE252_CAP_DRAW);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;
	wk->cap		= cap;

	CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );

	WEEffect_TCB_AddPriSet(wk->we_sys, WeCat252_DrawCapTcb, wk);
}


//-------------------------------------
//	
//	�|�P������k�������Ȃ���g�k
//	
//=====================================
enum{
	WE252_POKE_SSP_SCALEUP_INIT,
	WE252_POKE_SSP_SCALEUP,
	WE252_POKE_SSP_SCALEDOWN_INIT,
	WE252_POKE_SSP_SCALEDOWN,
	WE252_POKE_SSP_SCALEEND,
};

#define NEKODAMASI_SC_SX		(10)
#define NEKODAMASI_SC_EX		(7)
#define NEKODAMASI_SC_SY		(10)
#define NEKODAMASI_SC_EY		(30)
#define NEKODAMASI_SC_D			(10)
#define NEKODAMASI_SC_NUM		(1)
#define NEKODAMASI_SC_SYNC		((4 << 16) | 3)

#define WE252_SHAKE_WIDTH	( 2 )
#define WE252_SHAKE_NUM		( 2 )
#define WE252_SHAKE_SYNC	( 1 )


typedef struct {
	WE_SYS_PTR we_sys;
	int seq;

	s16 dy;			// ���̃|�W�V����
	s16 dx;			// ���̃|�W�V����
	s16 poke_h;		// �|�P�����̍���

	// �|�P����
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE	ssp_scale;
	WAZATOOL_CALCMOVE	ssp_shak;

	int scale_sx;
	int scale_ex;
	int scale_sy;
	int scale_ey;
	int scale_d;
	int scale_num;		// �L�тďk�ނ��P�Ƃ�����
	int scale_sync;		// �L�тďk�ނɂP��̂��񂭐�
} TWE252_POKE_SSP_SCALE_UPDOWN;

static void We252SSPPokeScaleUpDownTCB( TCB_PTR tcb, void* work )
{
	TWE252_POKE_SSP_SCALE_UPDOWN* wk = work;
	BOOL check;

	switch( wk->seq ){
	case WE252_POKE_SSP_SCALEUP_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_sx,
				wk->scale_ex,
				wk->scale_sy,
				wk->scale_ey,
				wk->scale_d,
				wk->scale_sync >> 16
				);
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );

		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->seq++;
		break;
		
	case WE252_POKE_SSP_SCALEUP:
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		check = WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		
		if( check == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE252_POKE_SSP_SCALEDOWN_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_ex,
				wk->scale_sx,
				wk->scale_ey,
				wk->scale_sy,
				wk->scale_d,
				wk->scale_sync & 0xffff
				);
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->seq++;
		break;
		
	case WE252_POKE_SSP_SCALEDOWN:
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		check = WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		// �g�k�l��ݒ�
		if( check == FALSE ){
			wk->scale_num --;
			if( wk->scale_num <= 0 ){
				// �I��
				wk->seq++;
			}else{
				wk->seq = WE252_POKE_SSP_SCALEUP_INIT;
			}
		}
		break;
		
	case WE252_POKE_SSP_SCALEEND:
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->dx );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->dy );

		SoftSpriteParaSet( wk->ssp, SS_PARA_AFF_X, 0x100 );
		SoftSpriteParaSet( wk->ssp, SS_PARA_AFF_Y, 0x100 );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	POKE_SSP ��L�яk�݂�����	
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_252SSPPoke(WE_SYS_PTR we_sys)
{
	TWE252_POKE_SSP_SCALE_UPDOWN* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE252_POKE_SSP_SCALE_UPDOWN);
	wk->we_sys	= we_sys;

	wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));

	// �|�P�����擾
	wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
	wk->dy = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	wk->dx = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	
	wk->scale_sx	= NEKODAMASI_SC_SX;
	wk->scale_ex	= NEKODAMASI_SC_EX;
	wk->scale_sy	= NEKODAMASI_SC_SY;
	wk->scale_ey	= NEKODAMASI_SC_EY;
	wk->scale_d		= NEKODAMASI_SC_D;
	wk->scale_num	= NEKODAMASI_SC_NUM;
	wk->scale_sync	= NEKODAMASI_SC_SYNC;


	WazaTool_InitShake(
			&wk->ssp_shak,
			WE252_SHAKE_WIDTH, 0,
			WE252_SHAKE_SYNC,
			WE252_SHAKE_NUM
			);


	WEEffect_TCB_AddPriSet(wk->we_sys, We252SSPPokeScaleUpDownTCB, wk);
}



//-------------------------------------
//	
//	���K�z�[��
//	
//=====================================

#define MEGAHOON_POS_X_OFS	( 64 )
#define MEGAHOON_POS_Y_OFS	( -16 )
#define MEGAHOON_MOVE_X		( 48 )
#define MEGAHOON_MOVE_Y		( -16 )
#define MEGAHOON_MOVE_SYNC	( 6 )

typedef struct {
	WE_SYS_PTR we_sys;
	CATS_RES_PTR crp;

	WAZATOOL_CALCMOVE	cap_move;
	CATS_ACT_PTR cap;
} TWE224_SYS;

static void We_224TCB( TCB_PTR tcb, void* work )
{
	TWE224_SYS* wk = work;
	
	if( WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->cap ) == FALSE ){
		CATS_ActorPointerDelete_S(wk->cap);
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}
	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���K�z�[������^�X�N�o�^
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224(WE_SYS_PTR we_sys)
{
	TWE224_SYS* wk;
	int at_client;
	int vec_x, vec_y;
	int cap_x, cap_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysCrpGet( we_sys );

	// cap�擾
	at_client = WeSysATNoGet( we_sys );
	if( WET_SideCheck( we_sys, at_client ) == SIDE_MINE ){
		wk->cap = WeSysOamCapGet( we_sys, 0 );

		CATS_ActorPointerDelete_S( WeSysOamCapGet( we_sys, 1 ) );
	}else{
		wk->cap = WeSysOamCapGet( we_sys, 1 );

		CATS_ActorPointerDelete_S( WeSysOamCapGet( we_sys, 0 ) );
	}

	// �����x�N�g���擾
	vec_x = WazaTool_VecChangeX( we_sys, at_client );
	vec_y = WazaTool_VecChangeY( we_sys, at_client );

	// ���K�z�[�����W�ݒ�
	cap_x = GetWazaEffPos( we_sys, at_client, PM_X );
	cap_y = GetWazaEffPos( we_sys, at_client, PM_Y );
	cap_x += MEGAHOON_POS_X_OFS * vec_x;
	cap_y += MEGAHOON_POS_Y_OFS * vec_y;
	CATS_ObjectPosSetCap( wk->cap, cap_x, cap_y );

	// ���K�z�[������ݒ�
	WazaTool_InitStraightSyncFx(
			&wk->cap_move,
			cap_x, cap_x + (MEGAHOON_MOVE_X * vec_x),
			cap_y, cap_y + (MEGAHOON_MOVE_Y * vec_y),
			MEGAHOON_MOVE_SYNC
			);
	

	WEEffect_TCB_AddPriSet(wk->we_sys, We_224TCB, wk);
}


// �U��������
enum{
	WE224AT_SHAKE_INIT,
	WE224AT_SHAKE,
	WE224AT_MOVE1,		// �G�̂ق��Ɉړ�
	WE224AT_WAIT,		// �ҋ@
	WE224AT_MOVE2,		// �߂�
	WE224AT_END,		// �I��
};
#define WE224AT_SHAKE_X		( 4 )
#define WE224AT_SHAKE_NUM	( 4 )
#define WE224AT_SHAKE_SYNC	( 1 )

#define WE224AT_MOVE_X		( 40 )
#define WE224AT_MOVE_Y		( -7 )
#define WE224AT_SYNC		( 4 )

#define WE224AT_WAIT_NUM		( 8 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int wait;
	int vec_x;
	int vec_y;

	// �|�P����
	SOFT_SPRITE*	ssp;
	s16				ssp_x;
	s16				ssp_y;
	WAZATOOL_CALCMOVE	ssp_move;
	WAZATOOL_CALCMOVE	ssp_shake;
}TWE224AT_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�U��������
 *
 *	@param	tcb		
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We_224ATTCB( TCB_PTR tcb, void* work )
{
	TWE224AT_SYS* wk = work;

	switch( wk->seq ){
	case WE224AT_SHAKE_INIT:
		WazaTool_InitShake(
				&wk->ssp_shake,
				WE224AT_SHAKE_X,
				0,
				WE224AT_SHAKE_SYNC,
				WE224AT_SHAKE_NUM
				);
		wk->seq++;
		break;
		
	case WE224AT_SHAKE:
		if( WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shake, wk->ssp_x, wk->ssp_y, wk->ssp ) == FALSE ){
			wk->seq++;

			// �����ړ��ݒ�
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x, wk->ssp_x + (WE224AT_MOVE_X * wk->vec_x),
					wk->ssp_y, wk->ssp_y + (WE224AT_MOVE_Y * wk->vec_y),
					WE224AT_SYNC
					);
		}
		break;
		
	case WE224AT_MOVE1:		// �G�̂ق��Ɉړ�
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
			wk->wait = WE224AT_WAIT_NUM;
		}
		break;
		
	case WE224AT_WAIT:		// �ҋ@
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;

			// �����ړ��ݒ�
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x + (WE224AT_MOVE_X * wk->vec_x), wk->ssp_x, 
					wk->ssp_y + (WE224AT_MOVE_Y * wk->vec_y), wk->ssp_y, 
					WE224AT_SYNC
					);
		}
		break;
		
	case WE224AT_MOVE2:		// �߂�
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE224AT_END:		// �I��
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->ssp_x );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->ssp_y );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���K�z�[���U��������^�X�N�o�^
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224AT(WE_SYS_PTR we_sys)
{
	TWE224AT_SYS* wk;
	int at_client;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224AT_SYS);
	wk->we_sys	= we_sys;

	// �|�P�����f�[�^�쐬
	at_client = WeSysATNoGet( we_sys );
	wk->ssp = WeSysSoftSpritePointerGet( we_sys, at_client );
	wk->ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	wk->ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );

	// �����x�N�g���擾
	wk->vec_x = WazaTool_VecChangeX( we_sys, at_client );
	wk->vec_y = WazaTool_VecChangeY( we_sys, at_client );


	WEEffect_TCB_AddPriSet(wk->we_sys, We_224ATTCB, wk);
}


// �h�䑤����
enum{
	WE224DF_MOVE1_INIT,
	WE224DF_MOVE1,
	WE224DF_SHAKE,
	WE224DF_MOVE2,
	WE224DF_END,
};
#define WE224DF_SHAKE_X		( 4 )
#define WE224DF_SHAKE_NUM	( 4 )
#define WE224DF_SHAKE_SYNC	( 1 )

#define WE224DF_MOVE_X		( -40 )
#define WE224DF_MOVE_Y		( 16 )
#define WE224DF_SYNC		( 4 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int vec_x;
	int vec_y;

	// �|�P����
	SOFT_SPRITE*	ssp;
	s16				ssp_x;
	s16				ssp_y;
	WAZATOOL_CALCMOVE	ssp_move;
	WAZATOOL_CALCMOVE	ssp_shake;
}TWE224DF_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�U��������
 *
 *	@param	tcb		
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We_224DFTCB( TCB_PTR tcb, void* work )
{
	TWE224DF_SYS* wk = work;
	s16 x, y;

	switch( wk->seq ){
	case WE224DF_MOVE1_INIT:
		// �����ړ��ݒ�
		WazaTool_InitStraightSyncFx(
				&wk->ssp_move,
				wk->ssp_x, wk->ssp_x + (WE224DF_MOVE_X * wk->vec_x),
				wk->ssp_y, wk->ssp_y + (WE224DF_MOVE_Y * wk->vec_y),
				WE224DF_SYNC
				);
		wk->seq++;
		break;
		
		
	case WE224DF_MOVE1:		// �G�̂ق��Ɉړ�
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
			WazaTool_InitShake(
					&wk->ssp_shake,
					WE224DF_SHAKE_X,
					0,
					WE224DF_SHAKE_SYNC,
					WE224DF_SHAKE_NUM
					);
		}
		break;
		
	case WE224DF_SHAKE:
		x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
		y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
		if( WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shake, x, y, wk->ssp ) == FALSE ){
			wk->seq++;

			// �����ړ��ݒ�
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x + (WE224DF_MOVE_X * wk->vec_x), wk->ssp_x, 
					wk->ssp_y + (WE224DF_MOVE_Y * wk->vec_y), wk->ssp_y, 
					WE224DF_SYNC
					);

		}
		break;
		
	case WE224DF_MOVE2:		// �߂�
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE224DF_END:		// �I��
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->ssp_x );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->ssp_y );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���K�z�[���U��������^�X�N�o�^
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224DF(WE_SYS_PTR we_sys)
{
	TWE224DF_SYS* wk;
	int at_client;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224DF_SYS);
	wk->we_sys	= we_sys;

	// �|�P�����f�[�^�쐬
	at_client = WeSysDFNoGet( we_sys );
	wk->ssp = WeSysSoftSpritePointerGet( we_sys, at_client );
	wk->ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	wk->ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );

	// �����x�N�g���擾
	wk->vec_x = WazaTool_VecChangeX( we_sys, at_client );
	wk->vec_y = WazaTool_VecChangeY( we_sys, at_client );


	WEEffect_TCB_AddPriSet(wk->we_sys, We_224DFTCB, wk);
}
