//==============================================================================
/**
 * @file	wazatool.c
 * @brief	�Z�G�t�F�N�g�֘A�̔ėp�c�[���̃w�b�_
 * @author	matsuda
 * @date	2005.09.02(��)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "spl.h"
#include "battle_particle.h"
#include "we_err.h"
#include "we_tool.h"
#include "wazatool.h"

#include "contest/contest.h"



//==============================================================================
//	�\���̒�`
//==============================================================================
typedef struct{
	s16 x;
	s16 y;
}POINT;



//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g����^�X�N�Ŏg���������̊m��
 *
 * @param   heap_area		�g�p����q�[�v�G���A
 * @param   size			�m�ۂ���T�C�Y
 *
 * @retval  �m�ۂ����������̐擪�A�h���X
 *
 * �m�ۂ�����������0�N���A����Ă��܂�
 */
//--------------------------------------------------------------
void * WazaTool_AllocClearMemory(int heap_area, u32 size)
{
	void *work;
	
	work = sys_AllocMemory(heap_area, size);
	MI_CpuClear8(work, size);
	return work;
}

///�Z�G�t�F�N�g�p �n�_�E�I�_���W�f�[�^
static const POINT WazaEffPos[][ 6 ] = 
{
	{	//FightType	1vs1
		//ClientNo
		{ APPEAR_X_TYPE_AA, APPEAR_Y_TYPE_AA },				//����1
		{ APPEAR_X_TYPE_BB, APPEAR_Y_TYPE_BB },				//�G1
		{ CONTEST_ATTACK_POKE_X,  CONTEST_ATTACK_POKE_Y },	//�R���e�X�g�U���p
		{ CONTEST_DEFENCE_POKE_X, CONTEST_DEFENCE_POKE_Y },	//�R���e�X�g�h��p
		{ 0,0 },
		{ 0,0 },
	},
	{	//FightType 2vs2
		{ APPEAR_X_TYPE_AA, APPEAR_Y_TYPE_AA },		//����1
		{ APPEAR_X_TYPE_BB, APPEAR_Y_TYPE_BB },		//�G1
		{ APPEAR_X_TYPE_A, APPEAR_Y_TYPE_A },		//����1
		{ APPEAR_X_TYPE_B, APPEAR_Y_TYPE_B },		//�G1
		{ APPEAR_X_TYPE_C, APPEAR_Y_TYPE_C },		//����2
		{ APPEAR_X_TYPE_D, APPEAR_Y_TYPE_D },		//�G2
	},
};

void WazaEffPosGet_Type(int fight_type, int type, s16* x, s16* y)
{
	if (x != NULL){
		*x = WazaEffPos[ fight_type ][ type ].x;
	}
	if (y != NULL){
		*y = WazaEffPos[ fight_type ][ type ].y;
	}
}

void WazaEffPosGet_ClientType(WE_SYS_PTR wsp, int client_no, s16*x, s16* y)
{
	if (WES_ContestFlag_Get(wsp) == TRUE){
		WazaEffPosGet_Type(0, client_no + 2, x, y);	
	}
	else {
		if (IsWeSysBattleMode2vs2(wsp) == TRUE){
			WazaEffPosGet_Type(1, client_no - 2, x, y);	
		}
		else {
			WazaEffPosGet_Type(0, client_no, x, y);	
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g�n�_�A�I�_���W�擾
 *
 * @param   we_sys		
 * @param   client_no	�N���C�A���gNo
 * @param   get_pos		PM_??? or EFF_???
 *
 * @retval  
 *
 * POKE_* = �X�̃|�P�����̑傫���ɂ���č��W���ς��A�G�̑傫��������Ă����
 *          ���̊G�ɂ������|�P�����̒��S�̍��W������B
 *
 * EFF_* =  �|�P�����̃I�t�Z�b�g�͊֌W�Ȃ��ŏ�ɋ��ʂ̒��S���W���擾����
 */
//--------------------------------------------------------------
s16 GetWazaEffPos(WE_SYS_PTR we_sys, int client_no, int get_pos)
{
	int client_type, fight_type;
	
	client_type = WET_ClientTypeGet(we_sys, client_no);
	
	if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
		fight_type = 1;
	}
	else {
		fight_type = 0;
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		client_type += 2;
	}
	
	switch(get_pos){
	case PM_X:
	case EFF_X:
		return WazaEffPos[fight_type][client_type].x;
	case PM_Y:
	case EFF_Y:
		return WazaEffPos[fight_type][client_type].y;
	}
	
	GF_ASSERT(0);
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   �w��N���C�A���gNo�̃|�P�����A�N�^�[�̃f�t�H���g�\�t�g�v���C�I���e�B���擾����
 * @param   client_no		�N���C�A���gNO
 * @retval  �\�t�g�v���C�I���e�B
 * 
 * DP�ł̓|�P�����̓\�t�g�E�F�A�X�v���C�g�Ȃ̂ňӖ��͂Ȃ����ǋ��G�t�F�N�g�\�[�X�������Ă���ׂ�
 * �݊��p�Ƃ��ėp�ӂ���
 */
//--------------------------------------------------------------
u32 GetPokeSoftPri(u8 client_no)
{
	return WAZAEFF_ACT_SOFTPRI;
}



//-------------------------------------
//	
//	CATS_ACT_PTR�̃p���b�gNO�擾�֐�
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	cap�̎Q�Ƃ��Ă���p���b�g�i���o�[���擾����
 *
 *	@param	cap	�A�N�^�[�f�[�^
 *
 *	@return	�p���b�gNO	0�`15
 *
 *
 */
//-----------------------------------------------------------------------------
u8 WazaTool_CapPlttNoGet( CATS_ACT_PTR cap )
{
	return GetPlttProxyOffset( CLACT_PaletteProxyGet(cap->act), NNS_G2D_VRAM_TYPE_2DMAIN );
}


//-------------------------------------
//	
//	H�u�����N�֐����p�b�N�����֐�
//
//	��X�g������Ƃ������邩���m��Ȃ����ߍ쐬
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N�֐��ݒ���p�b�N�����֐�
 *
 *	@param	func		�ݒ肷��H�u�����N����֐�
 *	@param	work		���[�N
 *
 *	@retval	WAZATOOL_HBLANK_FALSE	���s
 *	@retval	WAZATOOL_HBLANK_TRUE	����
 */
//-----------------------------------------------------------------------------
int WazaTool_HBlankSet( INTR_FUNC func, void * work )
{
	GF_ASSERT( work );
	
	if( sys_HBlankIntrSet( func, work ) ){
		return WAZATOOL_HBLANK_TRUE;
	}

	return WAZATOOL_HBLANK_FALSE;
}

//-------------------------------------
//	���G�t�F�N�g�����`�F���W
//	�@���Əc�̃x�N�g��������Ԃ��܂��B
//	�@�߂�l���|���邱�ƂŁA���̕����̃x�N�g���ɂȂ�܂��B
//	�@
//	�@��]�͎n�_�ƏI�_��n���Ă��炢�A
//	�@��]�������t�ɂȂ�l���Đݒ肵�܂��B
//	�@�ꍇ�ɂ���Ă͎n�_�̒l���ς��Ƃ�������܂��B
//	�@��j�ύX�O�@�n0 �I15 �ύX��@�n360 �I���345
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�N���C�A���g�i���o�[����X�����x�N�g�����擾����
 *
 *	@param	we_sys			�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	client_no		�N���C�A���g�i���o�[
 *
 *	@retval	1				���̕�����OK
 *	@retval	-1				�t�����̃x�N�g��
 *
 * ���퓬���̎����T�C�h����Ƃ��������ł��B
 *
 * ����]���������̊֐��ŕύX�ł��܂��B
 *
 */
//-----------------------------------------------------------------------------
int WazaTool_VecChangeX( WE_SYS_PTR we_sys, int client_no )
{
	int side;
	int out_put = 1;

	// �ēx�擾
	side = WET_SideCheck( we_sys, client_no );
		
	// �R���e�X�g���`�F�b�N
	if( WES_ContestFlag_Get( we_sys ) ){
		// �R���e�X�g�̂Ƃ�
		//	�����T�C�h��X�����t�x�N�g��
		//	����T�C�h��X�������̂܂�
		if( side == SIDE_MINE ){
			out_put = -1;
		}
	}else{
		// �퓬�̂Ƃ�
		//	�����T�C�h��X�������̂܂�
		//	����T�C�h��X�����t�x�N�g��
		if( side == SIDE_ENEMY ){
			out_put = -1;
		}
	}

	return out_put;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�N���C�A���g�i���o�[����Y�����x�N�g�����擾����
 *
 *	@param	we_sys			�Z�G�t�F�N�g�V�X�e�����[�N
 *	@param	client_no		�N���C�A���g�i���o�[
 *
 *	@retval	1				���̕�����OK
 *	@retval	-1				�t�����̃x�N�g��
 *
 * ���퓬���̎����T�C�h����Ƃ��������ł��B
 *
 */
//-----------------------------------------------------------------------------
int WazaTool_VecChangeY( WE_SYS_PTR we_sys, int client_no )
{
	int side;
	int out_put = 1;

	// �ēx�擾
	side = WET_SideCheck( we_sys, client_no );
		
	//	�����T�C�h��Y�������̂܂�
	//	����T�C�h��Y�����t�x�N�g��
	if( side == SIDE_ENEMY ){
		out_put = -1;
	}
	

	return out_put;
}

//-----------------------------------------------------------------------------
/**
 *		�����@�v�Z
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���������߂�
 *
 *	@param	a		�n�_
 *	@param	an		�I�_
 *	@param	n		�V���N��
 *
 *	@return	����
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 WazaTool_GetDiff( fx32 a, fx32 an, u32 n )
{
	fx32 ans;
	
	ans = FX_Div( (an - a), n << FX32_SHIFT );

	return ans;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����diff��a�`an�ɂȂ邽�߂ɕK�v�ȃV���N��
 *	
 *	@param	a		�n�_
 *	@param	an		�I�_
 *	@param	diff	����
 *
 *	@return	�K�v�V���N��	(��Βl�j
 *
 * �����_�ȉ��؂�グ
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetDiffSync( fx32 a, fx32 an, fx32 diff )
{
	fx32 ans;
	fx32 smal;		// ������

	ans = FX_Div( (an - a), diff );

	// �����_�ȉ��؂�グ
	smal = FX_Modf( ans, &ans );
	if( smal ){
		ans += FX32_ONE;
	}

	ans = MATH_ABS( ans );
	
	return ans >> FX32_SHIFT;
}



//----------------------------------------------------------------------------
/**
 *	@brief	���W���f�֐�
 *
 *	@param	p_wtc	�f�[�^
 *	@param	cap		�A�N�^�[
 *	@param	c_x		���S���W
 *	@param	c_y		���S���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetCapMatrix( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap, s16 c_x, s16 c_y )
{
	CATS_ObjectPosSetCap( cap, c_x + p_wtc->x, c_y + p_wtc->y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g��l���f�֐�
 *
 *	@param	p_wtc	�f�[�^
 *	@param	cap		�A�N�^�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetCapScale( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	f32 s_x, s_y;
	WazaTool_CalcScaleRateToClactScale( p_wtc, &s_x, &s_y );
	CATS_ObjectScaleSetCap( cap, s_x, s_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W���f�֐�
 *
 *	@param	p_wtc	�f�[�^
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *	@param	c_x		���S�����W
 *	@param	c_y		���S�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetSspMatrix( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp, s16 c_x, s16 c_y )
{
	SoftSpriteParaSet( ssp, SS_PARA_POS_X, c_x + p_wtc->x );
	SoftSpriteParaSet( ssp, SS_PARA_POS_Y, c_y + p_wtc->y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g��l���f�֐�
 *
 *	@param	p_wtc	�f�[�^
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetSspScale( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	SoftSpriteParaSet( ssp, SS_PARA_AFF_X, p_wtc->x );
	SoftSpriteParaSet( ssp, SS_PARA_AFF_Y, p_wtc->y );
}

//-----------------------------------------------------------------------------
/**
 *		��]
 *
 *		�p�x��
 *			0�x  ->0
 *			360�x->65535(0xffff)
 *		�ł��B
 *		FX_GET_ROTA_NUM(x)	( (x*0xffff) / 360 )
 *		���̃}�N�����g�p����΁A�擾�ł��܂��B
 *		��j
 *			FX_GET_ROTA_NUM(360) == 0xffff
 *
 *	2005/11/18 tomoya takahashi
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�v�Z������
 *
 *	@param	p_wtc	����v�Z���[�N
 *	@param	r_sx	�J�n���p�x	(0�`65535) 65535��360�x�ł��B
 *	@param	r_ex	�I�����p�x	(0�`65535) 65535��360�x�ł��B
 *	@param	r_sy	�J�n���p�x	(0�`65535) 65535��360�x�ł��B
 *	@param	r_ey	�I�����p�x	(0�`65535) 65535��360�x�ł��B
 *	@param	wx		��������
 *	@param	wy		��������
 *	@param	sync	�V���N��
 *
 *	@return	none
 *
 * X����	sin�J�[�u
 * Y����	cos�J�[�u
 *
 *			1��]�������ݒ�ł��܂���B
 *			���̊֐��Őݒ肵����work[0]����]�������񐔔{
 *			���Ă�������
 */
//-----------------------------------------------------------------------------
void WazaTool_InitRotaFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, int sync )
{
	p_wtc->work[0] = sync;
	p_wtc->work[1] = r_sx;
	p_wtc->work[2] = wx;
	p_wtc->work[3] = r_sy;
	p_wtc->work[4] = wy;
	p_wtc->work[5] = (r_ex - r_sx) / sync;
	p_wtc->work[6] = (r_ey - r_sy) / sync;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�v�Z�������@��]���x���狁�߂�
 *
 *	@param	p_wtc
 *	@param	r_sx
 *	@param	r_ex
 *	@param	r_sy
 *	@param	r_ey
 *	@param	wx
 *	@param	wy
 *	@param	speed_x 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitRotaSpeedFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, u16 speed_x )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// �ړ�������ݒ�
	if( r_sx > r_ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	//��]�ړ��f�[�^��ݒ�
	p_wtc->work[0] = WazaTool_GetDiffSync( r_sx*FX32_ONE, r_ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = r_sx;
	p_wtc->work[2] = wx;
	p_wtc->work[3] = r_sy;
	p_wtc->work[4] = wy;
	p_wtc->work[5] = sp_x;
	p_wtc->work[6] = (r_ey - r_sy) / p_wtc->work[0];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�v�Z
 *
 *	@param	p_wtc	����v�Z���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	work[0]		�v�Z��
 *	work[1]		��������]�p�x		(0�`65535) 65535��360�x�ł��B
 *	work[2]		�������U�ꕝ		fx32�^
 *	work[3]		��������]�p�x		(0�`65535) 65535��360�x�ł��B
 *	work[4]		�������U�ꕝ		fx32�^
 *	work[5]		��������]�ω���	(0�`65535) 65535��360�x�ł��B
 *	work[6]		��������]�ω���	(0�`65535) 65535��360�x�ł��B
 *
 * X����	sin�J�[�u
 * Y����	cos�J�[�u
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcRotaFx( WAZATOOL_CALCMOVE* p_wtc )
{
	fx32 x, y;
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//�p�x�ω�
		p_wtc->work[1] += p_wtc->work[5];
		p_wtc->work[3] += p_wtc->work[6];

		// 0�`65535�����[�v
		p_wtc->work[1] &= 0xffff;
		p_wtc->work[3] &= 0xffff;

		p_wtc->work[0]--;

		//�~��`��
		p_wtc->x = FX_Mul( FX_SinIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;
		p_wtc->y = FX_Mul( FX_CosIdx(p_wtc->work[3]), p_wtc->work[4] ) >> FX32_SHIFT;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f�֐�
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	c_x		���S�����W
 *	@param	c_y		���S�����W
 *	@param	cap		�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectRotaFxCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcRotaFx( p_wtc ) ){
		WazaTool_SetCapMatrix( p_wtc, cap, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f�֐�
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	c_x		���S�����W
 *	@param	c_y		���S�����W
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectRotaFxSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcRotaFx( p_wtc ) ){
		WazaTool_SetSspMatrix( p_wtc, ssp, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		���s�ړ�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 * ���ړ��X�s�[�h�ŏ�����
 *	@brief	���s�ړ��v�Z�������֐�
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	sx		�ړ��J�n�����W
 *	@param	ex		�ړ��I�������W
 *	@param	sy		�ړ��J�n�����W
 *	@param	ey		�ړ��I�������W
 *	@param	speed_x	�������X�s�[�h	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSpeed( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// �ړ�������ݒ�
	if( sx > ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	// �����ړ��f�[�^��ݒ�
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = WazaTool_GetDiffSync( sx*FX32_ONE, ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = sp_x;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, p_wtc->work[0] ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 * ���ړ��X�s�[�h�ŏ�����
 *	@brief	���s�ړ��v�Z�������֐�	�i�Œ菭���g�p�j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	sx		�ړ��J�n�����W
 *	@param	ex		�ړ��I�������W
 *	@param	sy		�ړ��J�n�����W
 *	@param	ey		�ړ��I�������W
 *	@param	speed_x	�������X�s�[�h	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSpeedFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// �ړ�������ݒ�
	if( sx > ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	// �����ړ��f�[�^��ݒ�
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = WazaTool_GetDiffSync( sx*FX32_ONE, ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = sp_x << FX32_SHIFT;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, p_wtc->work[0] );
	p_wtc->work[3] = sx * FX32_ONE;
	p_wtc->work[4] = sy * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 * ��Sync���ŏ�����
 *	@brief	���s�ړ��v�Z�������֐�
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	sx		�ړ��J�n�����W
 *	@param	ex		�ړ��I�������W
 *	@param	sy		�ړ��J�n�����W
 *	@param	ey		�ړ��I�������W
 *	@param	sync	�g�p����V���N��	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSync( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync  )
{
	GF_ASSERT(p_wtc);

	// �����ړ��f�[�^��ݒ�
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( sx*FX32_ONE, ex*FX32_ONE, sync ) >> FX32_SHIFT;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, sync ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 * ��Sync���ŏ�����
 *	@brief	���s�ړ��v�Z�������֐�	�i�Œ菭���g�p�j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	sx		�ړ��J�n�����W
 *	@param	ex		�ړ��I�������W
 *	@param	sy		�ړ��J�n�����W
 *	@param	ey		�ړ��I�������W
 *	@param	sync	�g�p����sync��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSyncFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync )
{

	GF_ASSERT(p_wtc);

	// �����ړ��f�[�^��ݒ�
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( sx*FX32_ONE, ex*FX32_ONE, sync );
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, sync );
	p_wtc->work[3] = sx*FX32_ONE;
	p_wtc->work[4] = sy*FX32_ONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���s�ړ��v�Z
 *
 *	@param	p_wtc	����v�Z���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	work[0]		�v�Z��
 *	work[1]		x�ω���
 *	work[2]		y�ω���
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcStraight( WAZATOOL_CALCMOVE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		
		p_wtc->x += p_wtc->work[1];
		p_wtc->y += p_wtc->work[2];
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���s�ړ��v�Z	�i�Œ菭���g�p�j
 *
 *	@param	p_wtc	����v�Z���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	work[0]		�v�Z��
 *	work[1]		���ω���		fx32�^
 *	work[2]		���ω���		fx32�^
 *	work[3]		�ω������l		fx32�^	�����l�͂O
 *	work[4]		�ω������l		fx32�^	�����l�͂O
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcStraightFx( WAZATOOL_CALCMOVE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		
		p_wtc->work[3] += p_wtc->work[1];
		p_wtc->work[4] += p_wtc->work[2];
		p_wtc->x	= p_wtc->work[3] >> FX32_SHIFT;
		p_wtc->y	= p_wtc->work[4] >> FX32_SHIFT;
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	cap		�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectStraightFxCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcStraightFx( p_wtc ) ){

		WazaTool_SetCapMatrix( p_wtc, cap, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectStraightFxSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcStraightFx( p_wtc ) ){

		WazaTool_SetSspMatrix( p_wtc, ssp, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		�R�Ȃ�ړ�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�R�Ȃ�ړ��������@Y����		(�Œ菭���g�p)
 *
 *	@param	p_wtc_st		���s�ړ��p�����[�^�ݒ��
 *	@param	p_wtc_rt		��]�p�����[�^�ݒ��
 *	@param	sx				�n�_�����W
 *	@param	ex				�I�_�����W
 *	@param	sy				�n�_�����W
 *	@param	ey				�I�_�����W
 *	@param	sync			�v�Z�V���N��
 *	@param	width			��܂Ȃ�̕�	Y����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitCurveYFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width )
{
	// ���s�ړ��ݒ�
	WazaTool_InitStraightSyncFx( p_wtc_st, sx, ex, sy, ey, sync );
	
	// ��]�ݒ�
	p_wtc_rt->x = 0;
	p_wtc_rt->y	= 0;
	WazaTool_InitRotaFx( p_wtc_rt, 
			0, 0,
			FX_GET_ROTA_NUM(90), FX_GET_ROTA_NUM(270),
			0, width, sync );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�R�Ȃ�ړ��������@������		(�Œ菭���g�p)
 *
 *	@param	p_wtc_st		���s�ړ��p�����[�^�ݒ��
 *	@param	p_wtc_rt		��]�p�����[�^�ݒ��
 *	@param	sx				�n�_�����W
 *	@param	ex				�I�_�����W
 *	@param	sy				�n�_�����W
 *	@param	ey				�I�_�����W
 *	@param	sync			�v�Z�V���N��
 *	@param	width			��܂Ȃ�̕�	X����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitCurveXFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width )
{
	// ���s�ړ��ݒ�
	WazaTool_InitStraightSyncFx( p_wtc_st, sx, ex, sy, ey, sync );
	
	// ��]�ݒ�
	p_wtc_rt->x = 0;
	p_wtc_rt->y	= 0;
	WazaTool_InitRotaFx( p_wtc_rt, 
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(180),
			0, 0,
			width, 0, sync );
}

//----------------------------------------------------------------------------
/**
 * �����s�ړ��Ɖ�]�̂��킹�Z
 *	@brief	�R�Ȃ�ړ��v�Z	�i�Œ菭���g�p�j
 *
 *	@param	p_wtc_st	���s�ړ��v�Z���[�N	(���C��)
 *	@param	p_wtc_rt	��]�v�Z���[�N		(�T�u)
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	��p_wtc_st��x,y���W���v�Z���ʂɂȂ�܂��B
 *	������������p_wtc_rt��x,y��0�ŏ��������Ă��������B
 *
 * p_wtc_st	���s�ړ��p
 *	x			�S�̂̂����W�v�Z����
 *	y			�S�̂̂����W�v�Z����
 *	work[0]		�v�Z��
 *	work[1]		���ω���		fx32�^
 *	work[2]		���ω���		fx32�^
 *	work[3]		�ω������l		fx32�^	�����l�͂O
 *	work[4]		�ω������l		fx32�^	�����l�͂O
 *
 * p_wtc_rt	��]�p
 *	x			��]�݂̂̌v�Z����
 *	y			��]�݂̂̌v�Z����
 *	work[0]		�v�Z��
 *	work[1]		��������]�p�x		(0�`65535) 65535��360�x�ł��B
 *	work[2]		�������U�ꕝ		fx32�^
 *	work[3]		��������]�p�x		(0�`65535) 65535��360�x�ł��B
 *	work[4]		�������U�ꕝ		fx32�^
 *	work[5]		��������]�ω���	(0�`65535) 65535��360�x�ł��B
 *	work[6]		��������]�ω���	(0�`65535) 65535��360�x�ł��B
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcCurveFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt )
{
	BOOL st_end, rt_end;
	
	GF_ASSERT(p_wtc_st);
	GF_ASSERT(p_wtc_rt);

	// ���s�ړ��v�Z
	st_end = WazaTool_CalcStraightFx( p_wtc_st );
	// �R�Ȃ�v�Z
	rt_end = WazaTool_CalcRotaFx( p_wtc_rt );

	// ���s�ړ��Ɖ�]�̉��Z
	p_wtc_st->x += p_wtc_rt->x;
	p_wtc_st->y += p_wtc_rt->y;

	// �v�Z�I���`�F�b�N
	if( (st_end == rt_end) && (st_end == FALSE) ){
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc_st	�����ړ��p
 *	@param	p_wtc_rt	��]�p
 *	@param	cap			�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectCurveFxCap( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcCurveFx( p_wtc_st, p_wtc_rt ) ){

		WazaTool_SetCapMatrix( p_wtc_st, cap, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc_st	�����ړ��f�[�^
 *	@param	p_wtc_rt	��]�f�[�^
 *	@param	ssp			�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectCurveFxSsp( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcCurveFx( p_wtc_st, p_wtc_rt ) ){
		WazaTool_SetSspMatrix( p_wtc_st, ssp, 0, 0 );
		return TRUE;
	}

	return FALSE;
}


//WAZATOOL_CALCMOVE_ONE�\���̗p�֐��S
//----------------------------------------------------------------------------
/**
 *������
 *	@brief	�P�̒l�𓙍��œ������������֐��@�i�V���N���w��j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	a		�J�n�l
 *	@param	an		�I���l
 *	@param	sync	�V���N��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSync( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, u32 sync )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( a*FX32_ONE, an*FX32_ONE, sync ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *������
 *	@brief	�P�̒l�𓙍��œ������������֐��@�i�X�s�[�h�w��j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	a		�J�n�l
 *	@param	an		�I���l
 *	@param	speed	�X�s�[�h
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSpeed( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, s16 speed )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = WazaTool_GetDiffSync( a*FX32_ONE, an*FX32_ONE, speed * FX32_ONE );
	p_wtc->work[1] = speed;
}

//----------------------------------------------------------------------------
/**
 *���Œ菭��
 *	@brief	�P�̒l�𓙍��œ������������֐��@�i�V���N���w��j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	a		�J�n�l
 *	@param	an		�I���l
 *	@param	sync	�V���N��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, u32 sync )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( a*FX32_ONE, an*FX32_ONE, sync );
	p_wtc->work[2] = a * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *���Œ菭��
 *	@brief	�P�̒l�𓙍��œ������������֐��@�i�X�s�[�h�w��j
 *
 *	@param	p_wtc	�f�[�^�ݒ��
 *	@param	a		�J�n�l
 *	@param	an		�I���l
 *	@param	speed	�X�s�[�h
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSpeedFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, fx32 speed )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = WazaTool_GetDiffSync( a*FX32_ONE, an*FX32_ONE, speed * FX32_ONE );
	p_wtc->work[1] = speed * FX32_ONE;
	p_wtc->work[2] = a * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *������
 *	@brief	1�̒l�̓����v�Z
 *
 *	@param	p_wtc	���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	work[0]		�v�Z��
 *	work[1]		�ω���	
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcMoveOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		p_wtc->num	+= p_wtc->work[1];
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *���Œ菭��
 *	@brief	1�̒l�̓����v�Z
 *
 *	@param	p_wtc	���[�N
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *	work[0]		�v�Z��
 *	work[1]		�ω���	
 *	work[2]		���܂łɕω�������
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcMoveOneFx( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		p_wtc->work[2] += p_wtc->work[1];
		p_wtc->num	= p_wtc->work[2] >> FX32_SHIFT;
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�C���g�v�Z�������֐�
 *
 *	@param	p_wtc		�v�Z�p�����[�^�i�[��
 *	@param	s_r			�J�n��]�p
 *	@param	e_r			�I����]�p
 *	@param	w			�ő�ӂ蕝
 *	@param	sync		�V���N��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitSinCosOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, u16 s_r, u16 e_r, fx32 w, u32 sync )
{
	p_wtc->work[0] = sync;
	p_wtc->work[1] = s_r;
	p_wtc->work[2] = w;
	p_wtc->work[3] = (e_r - s_r) / sync;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	sin�g�v�Z
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcSinOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//�p�x�ω�
		p_wtc->work[1] += p_wtc->work[3];

		// 0�`65535�����[�v
		p_wtc->work[1] &= 0xffff;

		p_wtc->work[0]--;

		//�~��`��
		p_wtc->num = FX_Mul( FX_SinIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	cos�g�v�Z
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcCosOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//�p�x�ω�
		p_wtc->work[1] += p_wtc->work[3];

		// 0�`65535�����[�v
		p_wtc->work[1] &= 0xffff;

		p_wtc->work[0]--;

		//�~��`��
		p_wtc->num = FX_Mul( FX_CosIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;

		return TRUE;
	}

	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�g�k������
 *
 * @param	p_wtc	
 * @param	ss				�J�n�X�P�[��
 * @param	ds				�ʏ�X�P�[��
 * @param	es				�I���X�P�[��
 * @param	sync			�t���[����
 *
 * @retval	none	
 *
 *		0x100(256) = 100%
 *
 */
//--------------------------------------------------------------
#define SCALE_RATE_PER(p1, p2)	( ((p1) * 0x100) / p2 )
void WazaTool_InitScaleRate(WAZATOOL_CALCMOVE* p_wtc, s16 ss, s16 ds, s16 es, u32 sync)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;			///< �����鎞��
	
	///< �g�嗦
	wk->work[1] = WazaTool_GetDiff(SCALE_RATE_PER(ss, ds) * FX32_ONE,
								   SCALE_RATE_PER(es, ds) * FX32_ONE, sync);

	///< ���݂̊g�嗦x,y
	wk->x = SCALE_RATE_PER(ss, ds);
	wk->y = SCALE_RATE_PER(ss, ds);
	wk->work[3] = wk->x * FX32_ONE;
	wk->work[4] = wk->y * FX32_ONE;
}


//--------------------------------------------------------------
/**
 * @brief	�g�k���s
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcScaleRate(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;

	if (wk->work[0]){
		wk->work[0]--;
		wk->work[3] += wk->work[1];
		wk->work[4] += wk->work[1];
		wk->x = (wk->work[3] >> FX32_SHIFT);
		wk->y = (wk->work[4] >> FX32_SHIFT);
		
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�g�kXY���f
 *
 * @param	p_wtc		�ėp
 * @param	sx			�J�n�X�P�[��X
 * @param	ex			�I���X�P�[��X
 * @param	sy			�J�n�X�P�[��Y
 * @param	ey			�I���X�P�[��Y
 * @param	ds			��{�l
 * @param	sync		�V���N��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_InitScaleRateEx(WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, s16 ds, u32 sync)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;			///< �����鎞��
	
	///< �g�嗦
	wk->work[1] = WazaTool_GetDiff(SCALE_RATE_PER(sx, ds) * FX32_ONE,
								   SCALE_RATE_PER(ex, ds) * FX32_ONE, sync);
	
	wk->work[2] = WazaTool_GetDiff(SCALE_RATE_PER(sy, ds) * FX32_ONE,
								   SCALE_RATE_PER(ey, ds) * FX32_ONE, sync);

	///< ���݂̊g�嗦x,y
	wk->x = SCALE_RATE_PER(sx, ds);
	wk->y = SCALE_RATE_PER(sy, ds);
	wk->work[3] = wk->x * FX32_ONE;
	wk->work[4] = wk->y * FX32_ONE;
}


//--------------------------------------------------------------
/**
 * @brief	�g�k�AXY���f
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcScaleRateEx(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;

	if (wk->work[0]){
		wk->work[0]--;
		wk->work[3] += wk->work[1];
		wk->work[4] += wk->work[2];
		wk->x = (wk->work[3] >> FX32_SHIFT);
		wk->y = (wk->work[4] >> FX32_SHIFT);
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�g�k�p�����[�^�[��ϊ�
 *
 * @param	p_wtc	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_CalcScaleRateToClactScale(WAZATOOL_CALCMOVE* p_wtc, f32* x, f32* y)
{
	*x = (1.0f * p_wtc->x) / 0x0100;
	*y = (1.0f * p_wtc->y) / 0x0100;
}


//--------------------------------------------------------------
/**
 * @brief	��{���W�A�����A�X�P�[������␳���W�����߂�
 *
 * @param	def_y		��{���W
 * @param	poke_h		����
 * @param	sy			�X�P�[���l
 *
 * @retval	s16	
 *
 */
//--------------------------------------------------------------
s16 WazaTool_CalcScaleRateToYPos(s16 def_y, int poke_h, u32 sy)
{
	fx32 pos = (80 - (poke_h * 2)) * FX32_ONE;
	fx32 tmp;
	s16  ofs;
	
	tmp = (pos - ((pos * sy) / 0x100)) / 2;
	ofs = tmp >> FX32_SHIFT;

	return ofs;
}


//--------------------------------------------------------------
/**
 * @brief	��{���W�A�����A�X�P�[������␳���W�����߂�
 *
 * @param	def_y		��{���W
 * @param	poke_h		����
 * @param	sy			�X�P�[���l
 *
 * @retval	s16
 *
 */
//--------------------------------------------------------------
s16	WazaTool_CalcScaleRateToYPosFX(s16 def_y, int poke_h, fx32 sy)
{
	fx32 pos = (80 - (poke_h * 2)) * FX32_ONE;
	fx32 def = 0x0100 * FX32_ONE;
	fx32 tmp;
	fx32 mul;
	fx32 div;
	s16  ofs;
	
	mul = FX_Mul(pos, sy);
	div = FX_Div(mul, def);
	tmp = (pos - div);
#if 1
	{
		fx32 integer;
		fx32 decimal;
		decimal = FX_Modf(tmp, &integer);
		if (decimal){
			decimal += FX32_HALF;
		}
		tmp = integer + decimal;
	}
#endif
	
	ofs = (tmp >> FX32_SHIFT) / 2;
	
	return ofs;
}

//--------------------------------------------------------------
/**
 * @brief	�\�t�g�E�F�A�X�v���C�g�ɕ␳�n�𔽉f����
 *
 * @param	ssp	
 * @param	def_y	
 * @param	poke_height	
 * @param	scale	
 * @param	mode			���[�h	EOFS_MODE �Q��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_PokeOffsetSet(SOFT_SPRITE* ssp, s16 def_y, s16 poke_height, fx32 scale, int mode)
{
	s16 ofs_y;
	s16 def;
	
	def   = def_y;
	ofs_y = WazaTool_CalcScaleRateToYPosFX(def_y, poke_height, scale);
	
	if (mode == WAZAEFF_OFS_MODE_TOP){
		ofs_y *= -1;
		def = def_y - poke_height;
	}
	
	SoftSpriteParaSet(ssp, SS_PARA_POS_Y, def + ofs_y);
}

void WazaTool_PokeOffsetSetOAM(CATS_ACT_PTR cap, s16 def_y, s16 poke_height, fx32 scale, int mode)
{
	s16 ofs_y;
	s16 def;
	s16 dx;
	s16 dy;
	
	def   = def_y;
	ofs_y = WazaTool_CalcScaleRateToYPosFX(def_y, poke_height, scale);
	
	if (mode == WAZAEFF_OFS_MODE_TOP){
		ofs_y *= -1;
		def = def_y - poke_height;
	}

	CATS_ObjectPosGetCap(cap, &dx, &dy);
	CATS_ObjectPosSetCap(cap, dx,  def + ofs_y);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�f�[�^
 *	@param	cap		�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcScaleRate( p_wtc ) ){
		WazaTool_SetCapScale( p_wtc, cap );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�f�[�^
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcScaleRate( p_wtc ) ){
		WazaTool_SetSspScale( p_wtc, ssp );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�f�[�^
 *	@param	cap		�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateExCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcScaleRateEx( p_wtc ) ){
		WazaTool_SetCapScale( p_wtc, cap );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�f�[�^
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateExSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcScaleRateEx( p_wtc ) ){
		WazaTool_SetSspScale( p_wtc, ssp );
		return TRUE;
	}

	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	���ݏ󋵂ƁA1�O�̏󋵂���U��ʒu�����߂�֐�
 *
 * @param	now			��
 * @param	befor		1�O
 * @param	p			�ӂ蕝
 *
 * @retval	static inline void	
 *
 */
//--------------------------------------------------------------
static inline void WazaTool_ShakeTool(s16* now, s32* befor, s32 p)
{
	s32 temp = *befor;
	*befor = *now;
	
	if (temp == 0){
		*now = 0;
	}
	else {
		*now = temp *= -1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�ȈՃV�F�C�N
 *
 * @param	p_wtc	
 * @param	x			x�̂ӂ蕝
 * @param	y			y�̂ӂ蕝
 * @param	sync		�h�炷�^�C�~���O
 * @param	num			�h�炷��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_InitShake(WAZATOOL_CALCMOVE* p_wtc, s16 x, s16 y, u32 sync, u32 num)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;
	wk->work[1] = sync;
	wk->work[2] = num;
	
	wk->work[3] = 0;			///< ���E���E ��1�Z�b�g
	
	wk->work[4] = x;
	wk->work[5] = y;
	
	wk->work[6] = x * -1;		///< 1�O�̏��
	wk->work[7] = y * -1;		///< 1�O�̏��

	wk->x = 0;
	wk->y = 0;	
}


//--------------------------------------------------------------
/**
 * @brief	�h�炵
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcShake(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	if (wk->work[2]){
		
		wk->work[0]++;
		if (wk->work[0] >= wk->work[1]){
			wk->work[0] = 0;
			WazaTool_ShakeTool(&wk->x, &wk->work[6], wk->work[4]);
			WazaTool_ShakeTool(&wk->y, &wk->work[7], wk->work[5]);
			if ((++wk->work[3]) >= 4){
				wk->work[3] = 0;
				wk->work[2]--;
			}
		}
		
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	c_x		���S���W
 *	@param	c_y		���S���W
 *	@param	cap		�A�N�^�[
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectShakeCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcShake( p_wtc ) ){
		WazaTool_SetCapMatrix( p_wtc, cap, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v�Z�����f
 *
 *	@param	p_wtc	�v�Z�f�[�^
 *	@param	c_x		���S�����W
 *	@param	c_y		���S�����W
 *	@param	ssp		�X�v���C�g
 *
 *	@retval	TRUE	�r��
 *	@retval	FALSE	����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectShakeSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcShake( p_wtc ) ){
		WazaTool_SetSspMatrix( p_wtc, ssp, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�c���f�[�^��p_wtz�ɐݒ肵�܂��B
 *
 *	@param	p_wtz		�c���f�[�^�i�[��
 *	@param	p_wtc		����f�[�^�i�eWazaTool_Init�`�֐��ŏ������������́j
 *	@param	p_func		����֐�
 *	@param	x			�ړ��̊�ƂȂ邘���W
 *	@param	y			�ړ��̊�ƂȂ邙���W
 *	@param	wait		�c����\�����Ă����^�C�~���O
 *	@param	zanzou_num	�c���̐�		�P�ȏ�
 *	@param	type		���W�ɔ��f�����邩�g��k���ɔ��f�����邩
 *	@param	cap_00		�c����OAM�O
 *	@param	cap_01		�c����OAM�P		�c���̐����P�ȉ��̎��@NULL
 *	@param	cap_02		�c����OAM�Q		�c���̐����Q�ȉ��̎��@NULL
 *	@param	cap_03		�c����OAM�R		�c���̐����R�ȉ��̎��@NULL
 *
 *	@return	none
 *
 * type		�c�����f�^�C�v
	WAZATOOL_ZANZOU_TYPE_MATRIX,	// �^�C�v	���W
	WAZATOOL_ZANZOU_TYPE_SCALE,		// �^�C�v	�g��k��
 * 
 */
//-----------------------------------------------------------------------------
void WazaTool_InitZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func, s16 x, s16 y, u16 wait, u8 zanzou_num, u8 type, CATS_ACT_PTR cap_00, CATS_ACT_PTR cap_01, CATS_ACT_PTR cap_02, CATS_ACT_PTR cap_03 )
{
	int i;		// ���[�v�p
	
	// �f�[�^�ݒ�
	p_wtz->x = x;
	p_wtz->y = y;
	p_wtz->move_func	= p_func;
	p_wtz->wait			= wait;
	p_wtz->count		= 0;
	p_wtz->zanzou_num	= zanzou_num;
	p_wtz->zanzou_move	= 0;
	p_wtz->type			= type;
	for( i=0; i<zanzou_num; i++ ){
		p_wtz->move_param[ i ] = *p_wtc;
	}
	p_wtz->cap[ WAZATOOL_ZANZOU_0 ] = cap_00;
	p_wtz->cap[ WAZATOOL_ZANZOU_1 ] = cap_01;
	p_wtz->cap[ WAZATOOL_ZANZOU_2 ] = cap_02;
	p_wtz->cap[ WAZATOOL_ZANZOU_3 ] = cap_03;

	// �c���̕\��OFF
	for( i=0; i<p_wtz->zanzou_num; i++ ){
		CATS_ObjectEnableCap( p_wtz->cap[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�c���̓���p�����[�^��ύX����
 *
 *	@param	p_wtz		�c���f�[�^
 *	@param	p_wtc		�ݒ蓮��f�[�^
 *	@param	p_func		�ݒ蓮��֐�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_ChangeMoveZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func )
{
	int i;

	p_wtz->move_func	= p_func;
	for( i=0; i<p_wtz->zanzou_num; i++ ){
		p_wtz->move_param[ i ] = *p_wtc;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�c���𓮍삳����
 *
 *	@param	p_wtz		�c������f�[�^
 *
 *	@retval	TRUE		�r��
 *	@retval	FALSE		����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcZanzou( WAZATOOL_ZANZOU* p_wtz )
{
	int i;
	BOOL ret[WAZATOOL_ZANZOU_MAX];
	f32 s_x, s_y;

	// �ϐ�������
	for( i=0; i<WAZATOOL_ZANZOU_MAX; i++ ){
		ret[i] = TRUE;
	}
	
	// �o�^����
	if( p_wtz->wait <= p_wtz->count ){

		// �P�̓���J�n
		CATS_ObjectEnableCap( p_wtz->cap[ p_wtz->zanzou_move ], TRUE );
		p_wtz->zanzou_move++;
		p_wtz->count = 0;
	}

	// �o�^�^�C�~���O�J�E���g����
	if( p_wtz->zanzou_move < p_wtz->zanzou_num ){
		p_wtz->count++;
	}
	
	// ���쏈��
	for( i=0; i<p_wtz->zanzou_move; i++ ){
		
		// �v�Z	
		ret[ i ] = p_wtz->move_func( &p_wtz->move_param[ i ] );

		// ���f
		if( ret[ i ] ){
			// ���쒆�͒l�̍X�V
			if( p_wtz->type == WAZATOOL_ZANZOU_TYPE_MATRIX ){
				CATS_ObjectPosSetCap( p_wtz->cap[ i ], p_wtz->x + p_wtz->move_param[ i ].x, p_wtz->y + p_wtz->move_param[ i ].y );
			}else{

				// CalcScaleRate���g�p���Ă���Ƃ���
				WazaTool_CalcScaleRateToClactScale( &p_wtz->move_param[ i ], &s_x, &s_y );
				CATS_ObjectScaleSetCap( p_wtz->cap[ i ],
						s_x, s_y);
			}
		}else{
			// ���슮��������\��OFF
			CATS_ObjectEnableCap( p_wtz->cap[ i ], FALSE );
		}
	}

	// �I���`�F�b�N
	for( i=0; i<p_wtz->zanzou_num; i++ ){

		// �܂��v�Z�r���̃I�u�W�F�N�g�����邩�`�F�b�N
		if( ret[i] == TRUE ){	
			return TRUE;
		}
	}
		
	// ret[]�̒��g���S��FALSE�Ȃ�S�v�Z����
	return FALSE;
}


//-------------------------------------
//	
//	�ėp�I�Ɏg���铮�샏�[�N��
//	�쐬����֐��S
//
//	��]�ړ��Ȃǂ͋��ʂ̓�������邱�Ƃ��������ߍ쐬
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�ړ��̃f�t�H���g�ݒ�
 *
 *	@param	p_wtc		����v�Z�f�[�^�i�[��
 *	@param	rota_num	��]��
 *	@param	sync		1��]�V���N��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_MakeDefRota( WAZATOOL_CALCMOVE* p_wtc, int rota_num, int rota_one_sync )
{
	int vec_x;
	
	WazaTool_InitRotaFx( p_wtc,
			0, FX_GET_ROTA_NUM(360),
			0, FX_GET_ROTA_NUM(360),
			WAZATOOL_DEF_ROTA_W_X,
			WAZATOOL_DEF_ROTA_W_Y,
			rota_one_sync);

	p_wtc->work[0] *= rota_num;
}


//-------------------------------------
//	
//	alpha�t�F�[�h�^�X�N
//	
//=====================================
//�t�F�[�h�^�X�N
static void WazaTool_TskAlphaFade( TCB_PTR tcb, void* work )
{
	BOOL check;
	WAZATOOL_ALPHA_FADE* wk = work;

	// �v�Z��
	check = WazaTool_CalcStraightFx( &wk->wtc );

	// �I���`�F�b�N
	if( check == FALSE ){

		wk->end_flag = TRUE;
		TCB_Delete( tcb );
	}else{

		// �}�C�i�X�͂O��
		if( wk->wtc.x < 0 ){
			wk->wtc.x = 0;
		}
		if( wk->wtc.y < 0 ){
			wk->wtc.y = 0;
		}
		
		// ���f��
		G2_ChangeBlendAlpha( wk->wtc.x, wk->wtc.y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A���t�@�t�F�[�h�^�X�N�J�n
 *
 *	@param	p_alfd	�f�[�^�i�[��
 *	@param	sev1	�Ώ̖ʂP�̊J�n�W��
 *	@param	eev1	�Ώ̖ʂP�̏I���W��
 *	@param	sev2	�Ώ̖ʂQ�̊J�n�W��
 *	@param	eev2	�Ώ̖ʂQ�̏I���W��
 *	@param	sync	�g�p�V���N��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartAlphaFade( WAZATOOL_ALPHA_FADE* p_alfd, s16 sev1, s16 eev1, s16 sev2, s16 eev2, int sync )
{
	// �ω��p�����[�^�ݒ�
	WazaTool_InitStraightSyncFx( &p_alfd->wtc, sev1, eev1, sev2, eev2, sync );

	// �I���t���O������
	p_alfd->end_flag = FALSE;

	// �^�X�N����
	TCB_Add( WazaTool_TskAlphaFade, p_alfd, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A���t�@�t�F�[�h�^�X�N�I���`�F�b�N
 *
 *	@param	p_alfd	�A���t�@�t�F�[�h�^�X�N���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_EndCheckAlphaFade( const WAZATOOL_ALPHA_FADE* p_alfd )
{
	return p_alfd->end_flag;
}

//-----------------------------------------------------------------------------
/**
 *		���X�^�[�p�V�X�e��
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	HDMA�R���g���[��
//	
//=====================================
typedef void (*pWazaTool_LSVBCFunc)( void* work );
// 1/30 ���J�o�[����V�X�e��
typedef struct _WAZATOOL_LASTER_VBLANK_CONT{
	TCB_PTR		vdma_tcb;
	TCB_PTR		vbuff_tcb;
	BOOL vblank_lst_flg;// VBlank�ōs���������s�����̃t���O
	BOOL dma_set_flg;	//���C�����[�v����V�u���������`�F�b�N����t���O
	
	pWazaTool_LSVBCFunc	vblank1;	// �R�O�t���[���̒ʏ��V�u�����N�p����
	pWazaTool_LSVBCFunc	vblank2;	// �r����V�u�����N�p����
	void * work;
} WAZATOOL_LSVBC;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ʏ�V�u�����N
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_VBlank1( TCB_PTR tcb, void* work )
{
	WAZATOOL_LSVBC* wk = work;
	
	if( wk->vblank_lst_flg ){
		// ����V�u�����N���Ԓ���DMA�ݒ���s��
		// �Q��ڂ͂����ōs���̂łP��ڂ������C�����[�v
		// �Ȃ��ł���V�u�����N���Ԓ��ɂ���Ă��炤
		wk->dma_set_flg = TRUE;

		// �ʏ��V�u�����N����
		wk->vblank1( wk->work );

	}else{
		LASTER_DmaStop();
	}
}
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r���ɓ���V�u�����N���ԗp�֐�
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_VBlank2( TCB_PTR tcb, void* work )
{
	WAZATOOL_LSVBC* wk = work;
	
	if( wk->vblank_lst_flg && wk->dma_set_flg ){

		// �r����V�u�����N����
		wk->vblank2( wk->work );
		
		wk->dma_set_flg = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[V�u�����N�V�X�e��
 *
 *	@param	p_lsvbc		���X�^�[V�u�����N�V�X�e�����[�N
 *	@param	work		�����ɓn�����[�N
 *	@param	pfunc1		�ʏ��V�u�����N
 *	@param	pfunc2		�r����V�u�����N
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Init( WAZATOOL_LSVBC* p_lsvbc, void* work, pWazaTool_LSVBCFunc pfunc1, pWazaTool_LSVBCFunc pfunc2 )
{
	GF_ASSERT( p_lsvbc );

	p_lsvbc->vblank_lst_flg	= TRUE;
	p_lsvbc->dma_set_flg	= FALSE;
	p_lsvbc->work			= work;
	p_lsvbc->vblank1		= pfunc1;
	p_lsvbc->vblank2		= pfunc2;

	// �^�X�N�o�^
	p_lsvbc->vbuff_tcb = VWaitTCB_Add( WazaTool_LSVBC_VBlank1, p_lsvbc, 0 );
	p_lsvbc->vdma_tcb = VIntrTCB_Add( WazaTool_LSVBC_VBlank2, p_lsvbc, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�pV�u�����N�Ǘ��V�X�e���j��
 *
 *	@param	p_lsvbc		�j�����郉�X�^�[V�u�����N�Ǘ��V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Delete( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );

	// VBlank�֐��j��
	if( p_lsvbc->vbuff_tcb != NULL ){
		TCB_Delete( p_lsvbc->vbuff_tcb );
	}
	if( p_lsvbc->vdma_tcb != NULL ){
		TCB_Delete( p_lsvbc->vdma_tcb );
	}
	LASTER_DmaStop();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	V�u�����N�V�X�e���̂P����~
 *
 *	@param	p_lsvbc		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Stop( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );
	p_lsvbc->vblank_lst_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	V�u�����N�V�X�e���̍ĊJ
 *
 *	@param	p_lsvbc		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Start( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );
	p_lsvbc->vblank_lst_flg = TRUE;
}


//-------------------------------------
//	
//	�o�b�t�@�����������삵�Ȃ�
//	
//=====================================
typedef struct _WAZATOOL_DEFLASTER{
	WAZATOOL_LSVBC vblank;

	// ���X�^�[�f�[�^
	LASTER_SYS_PTR lst;	// ���X�^�[�V�X�e��
	u32	buff1[ WAZATOOL_DEFLASTER_BUFF_SIZE ];	// �_�u���o�b�t�@
	u32	buff2[ WAZATOOL_DEFLASTER_BUFF_SIZE ];	// �_�u���o�b�t�@
	u32	addr;	// DMA�]����
} WAZATOOL_DEFLASTER;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	DMA�]���ݒ�
 *
 *	@param	p_lst	�f�t�H���g���X�^�[�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterDmaTransSet( WAZATOOL_DEFLASTER* wk )
{
	const void* buff;

	// �Q�Ɨp�o�b�t�@�擾
	buff = LASTER_GetReadBuff( wk->lst );

	LASTER_DmaStop();
	
	// HBlankDmaTrans�ɐݒ�
	LASTER_DmaSet( buff, (void*)wk->addr, 4, LASTER_DMA_TYPE32 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�pV�u�����N�Ǘ��V�X�e���ɓn���ʏ�V�u�����N�֐�
 *
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterNormVblank( void* work )
{
	WAZATOOL_DEFLASTER* wk = work;

	// �o�b�t�@�X�C�b�`
	LASTER_VBlank( wk->lst );

	// HDMA�o�^
	WazaTool_DefLasterDmaTransSet( wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief ���X�^�[�pV�u�����N�Ǘ��V�X�e���ɓn���r���ɌĂ΂��V�u�����N�p����
 *
 *	@param		work	���[�N
 *	
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterCenterVblank( void* work )
{
	WAZATOOL_DEFLASTER* wk = work;

	// HDMA�o�^
	WazaTool_DefLasterDmaTransSet( wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�f�t�H���g���X�^�[����������
 *
 *	@param	addr		�]���惌�W�X�^�A�h���X
 *	@param	init_num	�o�b�t�@�̏����l
 *	@param	heap		�q�[�vID
 *
 *	@return	�쐬�������X�^�[�����f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
WAZATOOL_DEFLASTER_PTR WazaTool_InitDefLaster( u32 addr, u32 init_num, int heap )
{
	WAZATOOL_DEFLASTER_PTR p_lst;
	
	p_lst = sys_AllocMemory( heap, sizeof(WAZATOOL_DEFLASTER) );
	memset( p_lst, 0, sizeof(WAZATOOL_DEFLASTER) );
	GF_ASSERT( p_lst );


	p_lst->lst			= LASTER_Init( heap, p_lst->buff1, p_lst->buff2 );
	GF_ASSERT( p_lst->lst );
	p_lst->addr			= addr;

	// �o�b�t�@�̏�����
	MI_CpuFill32( p_lst->buff1, init_num, sizeof(u32) * WAZATOOL_DEFLASTER_BUFF_SIZE );
	MI_CpuFill32( p_lst->buff2, init_num, sizeof(u32) * WAZATOOL_DEFLASTER_BUFF_SIZE );

	// V�u�����N�Ǘ��V�X�e����������
	WazaTool_LSVBC_Init( &p_lst->vblank, p_lst, WazaTool_DefLasterNormVblank, WazaTool_DefLasterCenterVblank );

	return p_lst;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�����̏I��
 *
 *	@param	p_lst	�f�t�H���g���X�^�[�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_DeleteDefLaster( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	// Vblank�Ǘ��V�X�e���j��
	WazaTool_LSVBC_Delete( &p_lst->vblank );
	
	// ���X�^�[�V�X�e���j��
	if( p_lst->lst != NULL ){
		LASTER_Delete( p_lst->lst );
	}

	sys_FreeMemoryEz( p_lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������ݗp�o�b�t�@�̎擾
 *
 *	@param	cp_lst	�f�t�H���g���X�^�[�V�X�e��
 *
 *	@return	�������ݗp�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
void* WazaTool_GetDefLasterWriteBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );

	return LASTER_GetWriteBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Q�Ɨp�o�b�t�@���擾
 *
 *	@param	cp_lst	�f�t�H���g���X�^�[�V�X�e��
 *
 *	@return	�Q�Ɨp�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
const void* WazaTool_GetDefLasterReadBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );

	return LASTER_GetReadBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�����̒�~
 *
 *	@param	p_lst	�f�t�H���g���X�^�[���[�N
 *
 *	@return	none
 *
 * V�u�����N�֐����@�\���Ȃ��Ȃ�̂ŁA
 * ��ʂɃ��X�^�[�����f����Ȃ��Ȃ�܂��B
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StopDefLaster( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Stop( &p_lst->vblank );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�����X�^�[�g
 *
 *	@param	p_lst	�f�t�H���g���X�^�[�V�X�e��
 *
 *	@return	none
 *
 * ��ʂɃ��X�^�[�����f�����悤�ɂȂ�܂��B
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartDefLaster( WAZATOOL_DEFLASTER* p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Start( &p_lst->vblank );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�f�[�^�]����A�h���X���Đݒ�
 *
 *	@param	p_lst	�f�t�H���g���X�^�[�V�X�e��
 *	@param	addr	�]����A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_SetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst, u32 addr )
{
	GF_ASSERT( p_lst );

	p_lst->addr = addr;
}


//--------------------------------------------------------------
/**
 * @brief	�f�[�^�]����A�h���X���擾
 *
 * @param	p_lst	�f�t�H���g���X�^�[�V�X�e��
 *
 * @retval	u32		�]����A�h���X
 *
 */
//--------------------------------------------------------------
u32 WazaTool_GetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	return p_lst->addr;
}

//-------------------------------------
//	
//	1/30�t���[���Ή�
//	
// ���X�^�[�X�N���[�����b�v�֐�
// SIN�J�[�u�X�N���[�������܂�
//	
//	
//=====================================
typedef struct _WAZATOOL_SCRLASTER{
	WAZATOOL_LSVBC vblank;

	// ���X�^�[�f�[�^
	LASTER_SCROLL_PTR lst;	// ���X�^�[�X�N���[���V�X�e��
} WAZATOOL_SCRLASTER;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�pV�u�����N�Ǘ��V�X�e���ɓn���ʏ�V�u�����N�֐�
 *
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_ScrLasterNormVblank( void* work )
{
	WAZATOOL_SCRLASTER* wk = work;
	
	LASTER_ScrollVBuffSwitch( wk->lst );

	LASTER_ScrollVDma( wk->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief ���X�^�[�pV�u�����N�Ǘ��V�X�e���ɓn���r���ɌĂ΂��V�u�����N�p����
 *
 *	@param		work	���[�N
 *	
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_ScrLasterCenterVblank( void* work )
{
	WAZATOOL_SCRLASTER* wk = work;
	
	LASTER_ScrollVDma( wk->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���V�X�e������
 *
 *	@param	start		�X�N���[���J�n�����W
 *	@param	end			�X�N���[���I�������W
 *	@param	add_r		sin�J�[�u�e�[�u���쐬���̊p�x�𑫂��Ă����l(0�`65535)
 *	@param	r_w			sin�J�[�u�̔��a
 *	@param	scr_sp		���X�^�[�X�N���[���X�s�[�h	����*100�����l	�}�C�i�X�L��
 *	@param	bg_no		���X�^�[��������BG�̔ԍ�
 *	@param	tsk_pri		�^�X�N�D�揇��
 *	@param	init_num	�o�b�t�@������������l
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	�쐬�������X�^�[�f�[�^
 * 
 * start <= �X�N���[���͈� <= end
 *
 * bg_no = 0�`3	���C����ʌŒ�
 *
 */
//-----------------------------------------------------------------------------
WAZATOOL_SCRLASTER_PTR WazaTool_InitScrLaster( u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 tsk_pri, u32 init_num, int heap )
{
	WAZATOOL_SCRLASTER_PTR p_lst;
	u32 addr;
	void* buff;
	const void* cbuff;
		
	p_lst = sys_AllocMemory( heap, sizeof(WAZATOOL_SCRLASTER) );
	GF_ASSERT( p_lst );
	memset( p_lst, 0, sizeof(WAZATOOL_SCRLASTER) );

	// bg_no���烌�W�X�^�̃A�h���X���擾
	addr = WazaTool_GetLasterBGDestAddr( bg_no );

	// ���X�^�[�X�N���[���V�X�e���쐬
	p_lst->lst = LASTER_ScrollInit( heap );
	LASTER_ScrollStart( p_lst->lst, start, end, add_r, r_w, scr_sp, addr, init_num, tsk_pri );
	
	// VBlank�Ǘ��V�X�e���쐬
	WazaTool_LSVBC_Init( &p_lst->vblank, p_lst, WazaTool_ScrLasterNormVblank, WazaTool_ScrLasterCenterVblank );

	return p_lst;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�X�N���[���j��
 *
 *	@param	p_lst	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_DeleteScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );
	

	// V�u�����N�Ǘ��V�X�e���j��
	WazaTool_LSVBC_Delete( &p_lst->vblank );

	// ���X�^�[�X�N���[���j��
	if( p_lst->lst ){
		LASTER_ScrollDelete( p_lst->lst );
	}

	sys_FreeMemoryEz( p_lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������ݗp�o�b�t�@���^
 *
 *	@param	cp_lst	���[�N
 *
 *	@return	�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
void* WazaTool_GetScrLasterWriteBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );
	return LASTER_GetScrollWriteBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Q�Ɨp�o�b�t�@���擾
 *
 *	@param	cp_lst	���[�N
 *
 *	@return	�o�b�t�@
 *
 *
 */
//-----------------------------------------------------------------------------
const void* WazaTool_GetScrLasterReadBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );
	return LASTER_GetScrollReadBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[���f�̒�~
 *
 *	@param	p_lst	���[�N
 *
 *	@return	none
 *
 * V�u�����N�֐����@�\���Ȃ��Ȃ�̂ŁA
 * ��ʂɃ��X�^�[�����f����Ȃ��Ȃ�܂��B
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StopScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Stop( &p_lst->vblank );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[���f�̊J�n
 *
 *	@param	p_lst	���[�N
 *
 *	@return	none
 *
 * ��ʂɃ��X�^�[�����f�����悤�ɂȂ�܂��B
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Start( &p_lst->vblank );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�^�[�̃o�b�t�@�ɐݒ肷����W�f�[�^���쐬
 *
 *	@param	x	�ݒ肘���W
 *	@param	y	�ݒ肙���W
 *
 *	@return	�o�b�t�@�ɐݒ肷��l
 *
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetLasterBuffMatrixData( u16 x, u16 y )
{
	return ( (y << 16) | x );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�i���o�[�ɑΉ������A�h���X��Ԃ�
 *
 *	@param	bg_no	BG�i���o�[
 *
 *	@return	�A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetLasterBGDestAddr( int bg_no )
{
	u32 addr;
	switch( bg_no ){
	case 0:
		addr	= LASTER_SCROLL_MBG0;
		break;
	case 1:
		addr	= LASTER_SCROLL_MBG1;
		break;
	case 2:
		addr	= LASTER_SCROLL_MBG2;
		break;
	case 3:
		addr	= LASTER_SCROLL_MBG3;
		break;
	}

	return addr;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�G�t�F�N�g��BG�ɗD�揇�ʂ�ݒ�
 *
 *	@param	we_sys		�Z�G�t�F�N�g�V�X�e��
 *	@param	pri			�D�揇�� 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_SetEffectBGPriority( WE_SYS_PTR we_sys, int pri )
{
	int eff_bg;
	
	eff_bg = BT_BGL_BGNoGet( we_sys, WES_BF_EFFECT );
	switch( eff_bg ){
	case 0:
		G2_SetBG0Priority( pri );
		break;

	case 1:
		G2_SetBG1Priority( pri );
		break;

	case 2:
		G2_SetBG2Priority( pri );
		break;

	case 3:
		G2_SetBG3Priority( pri );
		break;
	}
}


// =============================================================================
//
//
//	���c�[���H�Ƃ��H
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	2�_�̒��_�����߂�
 *
 * @param	x1				�_1��x
 * @param	y1				�_1��y
 * @param	x2				�_2��x
 * @param	y2				�_2��y
 * @param	mx				���_x
 * @param	my				���_y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_MiddlePointGet(s16 px1, s16 py1, s16 px2, s16 py2, s16* mx, s16* my)
{
	*mx = (px1 + px2) / 2;
	*my = (py1 + py2) / 2;
}


//--------------------------------------------------------------
/**
 * @brief	2�_�̒��_�����߂�
 *
 * @param	x1				�_1��x
 * @param	y1				�_1��y
 * @param	x2				�_2��x
 * @param	y2				�_2��y
 * @param	mx				���_x
 * @param	my				���_y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_MiddlePointGetFx(s16 px1, s16 py1, s16 px2, s16 py2, fx32* mx, fx32* my)
{
	*mx = ((px1 + px2) * FX32_ONE) / 2;
	*my = ((py1 + py2) * FX32_ONE) / 2;
}


//--------------------------------------------------------------
/**
 * @brief	2�_�̋��������߂�
 *
 * @param	x1				�_1��x
 * @param	y1				�_1��y
 * @param	x2				�_2��x
 * @param	y2				�_2��y
 * @param	range			����
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_RangeGetFx(s16 x1, s16 y1, s16 x2, s16 y2, fx32* range)
{
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	*range = FX_Sqrt( ((py*py)+(px*px)) * FX32_ONE );
}


//--------------------------------------------------------------
/**
 * @brief	�_�Ɠ_����p�x�����߂�
 *
 * @param	x1				�_1��x
 * @param	y1				�_1��y
 * @param	x2				�_2��x
 * @param	y2				�_2��y
 * @param	angle			�p�x
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_PointToPointAngleGet(s16 x1, s16 y1, s16 x2, s16 y2, u16* angle)
{
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	s16 tmp;
	
	*angle = FX_Atan2Idx((py * FX32_ONE), px * FX32_ONE);
	if (*angle > 0 && py < 0){
		*angle = (*angle -FX_GET_ROTA_NUM(180)) * 0xffff;
	}
	else if (*angle < 0 && py > 0){
		*angle += +FX_GET_ROTA_NUM(180);					
	}
}


//--------------------------------------------------------------
/**
 * @brief	�p�����[�^�̑����Ǘ�
 *
 * @param	p			�Ώ�
 * @param	ep			���E
 * @param	cp			�����l
 *
 * @retval	BOOL		TRUE = ���E�ɓ��B����
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_ParamCalc(int* p, int ep, s32 cp)
{
	if (cp < 0){
		if (*p + cp > ep){
			*p += cp;
			return FALSE;
		}
		else {
			*p = ep;
			return TRUE;
		}			
	}
	else {
		if (*p + cp < ep){
			*p += cp;
			return FALSE;
		}
		else {
			*p = ep;
			return TRUE;
		}			
	}
	return TRUE;
}



// ----------------------------------------------------------------------------
//
//
//	���\�t�g�t�F�[�h�֐��S
//
//
// ----------------------------------------------------------------------------
// -----------------------------------------
//
//	�� �\�t�g�t�F�[�h����\����
//
// -----------------------------------------
typedef struct _TPAL_SOFT_FADE_SYS {
	
	BOOL	active;				///< TRUE = ���쒆
	TCB_PTR	tcb;
	
	FADEREQ req;
	u16		start_pos;
	u16		col_num;
	u16		next_rgb;
	u8		start_evy;
	u8		end_evy;
	u8		evy;
	s8		param;
	s8		wait;
	s8		timer;
	
	PALETTE_FADE_PTR	pfd;	///< pfd
	
} TPAL_SOFT_FADE_SYS;


//--------------------------------------------------------------
/**
 * @brief	����TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void PSF_Tcb(TCB_PTR tcb, void* work)
{
	PAL_SFS_PTR wk = (PAL_SFS_PTR)work;
	
	if (wk->active == FALSE){ return; }
	
	if ((++wk->timer) >= wk->wait){
		wk->timer = 0;

		SoftFadePfd(wk->pfd,
					wk->req,
					wk->start_pos,
					wk->col_num,
					wk->evy,
					wk->next_rgb);
	
		if (wk->evy == wk->end_evy){
			wk->active = FALSE;
		}
		else {
			s8 temp = wk->evy + wk->param;
			
			if (wk->param > 0){
				if (temp > wk->end_evy){
					wk->evy = wk->end_evy;
				}
				else {
					wk->evy += wk->param;
				}
			}
			else {
				if (temp < wk->end_evy){
					wk->evy = wk->end_evy;
				}
				else {
					wk->evy += wk->param;
				}
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	��ԃ`�F�b�N
 *
 * @param	psp			PAL_SFS_PTR
 *
 * @retval	BOOL		TRUE = ���s��
 *
 */
//--------------------------------------------------------------
BOOL IsPaletteSoftFade(PAL_SFS_PTR psp)
{
	GF_ASSERT(psp != NULL);
	
	return psp->active;
}


//--------------------------------------------------------------
/**
 * @brief	�I������
 *
 * @param	psp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PaletteSoftFadeDelete(PAL_SFS_PTR psp)
{
	GF_ASSERT(psp != NULL);
	
	TCB_Delete(psp->tcb);
	sys_FreeMemoryEz(psp);
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	pfd				pfd
 * @param	heap_area		�q�[�v
 * @param	req				�f�[�^�ԍ�
 * @param	start_pos		�J�n�ʒu
 * @param	col_num			�I���ʒu
 * @param	wait			�E�F�C�g
 * @param	param			evy �v�Z�l (start end�ŕ�����t������̂Ő����œn���Ă�������)
 * @param	start_evy		�J�n�Z�x
 * @param	end_evy			�I���Z�x
 * @param	next_rgb		�ύX��̐F
 * @param	tcb_pri			TCB�D��x
 *
 * @retval	PAL_SFS_PTR	
 *
 */
//--------------------------------------------------------------
PAL_SFS_PTR PaletteSoftFade(PALETTE_FADE_PTR pfd, int heap_area, FADEREQ req,
							u16 start_pos, u16 col_num,
							s8 wait, s8 param,
							u8 start_evy, u8 end_evy, 
							u16 next_rgb, int tcb_pri)
{
	PAL_SFS_PTR wk = NULL;
	
	wk = sys_AllocMemory(heap_area, sizeof(TPAL_SOFT_FADE_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->pfd			= pfd;
	
	wk->req			= req;
	wk->start_pos	= start_pos;
	wk->col_num		= col_num;
	wk->next_rgb	= next_rgb;
	wk->start_evy	= start_evy;
	wk->end_evy		= end_evy;
	wk->evy			= start_evy;
	wk->wait		= wait;
	wk->timer		= wait;
	
	if (wk->start_evy < wk->end_evy){
		wk->param	= param;
	}
	else {
		wk->param	= param * -1;
	}
	
	wk->active		= TRUE;
	
	wk->tcb = TCB_Add(PSF_Tcb, wk, tcb_pri);
	
	return wk;
} 

static void PalGrayScale(u16 *pal, u16 pal_size);

static void PalGrayScale(u16 *pal, u16 pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}

void WeTool_PalGrayScale(WE_SYS_PTR wsp)
{
	PALETTE_FADE_PTR pfd;
	u16* pal;
	
	pfd = WeSysPFDGet(wsp);
	
	pal = PaletteWorkTransWorkGet(pfd, FADE_MAIN_BG);
	
	if (WES_ContestFlag_Get(wsp) == TRUE){
		PalGrayScale(pal, 16 * ACTIN_HAIKEI_PAL_NUM);
	}
	else {
		PalGrayScale(pal, 16 * 8);
	}
}

void WeTool_PalNormal(WE_SYS_PTR wsp)
{
	PALETTE_FADE_PTR pfd;
	
	pfd = WeSysPFDGet(wsp);
	
	if (WES_ContestFlag_Get(wsp) == TRUE){
		PaletteWorkCopy(pfd, FADE_MAIN_BG, 0, FADE_MAIN_BG, 0, 16 * ACTIN_HAIKEI_PAL_NUM * 2);
	}
	else {
		PaletteWorkCopy(pfd, FADE_MAIN_BG, 0, FADE_MAIN_BG, 0, 16 * 8 * 2);
	}
}
