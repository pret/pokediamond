//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_data.c
 *	@brief		�؂̎��~�L�T�[�@�f�[�^�Ǘ���
 *	@author		tomoya takahashi
 *	@data		2006.05.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "include/gflib/calctool.h"
#include "include/itemtool/nuts.h"

#define __NMIX_GAME_DATA_H_GLOBAL
#include "nmix_game_data.h"

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
 *		�ėp�v�Z
 */
//-----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/**
 *	@brief	��]�p�x���v�Z����		�X�s�[�h�ɕύX
 *
 *	@param	x			���݂����W
 *	@param	y			���݂����W
 *	@param	last_x		�O�̂����W
 *	@param	last_y		�O�̂����W
 *	@param	center_x	���S�����W
 *	@param	center_y	���S�����W
 *
 *	@return	��]�����p�x
 */
//-----------------------------------------------------------------------------
s32	NMIX_DATA_CalcRota( int x, int y, int last_x, int last_y, int center_x, int center_y )
{
	int last_rota;
	int now_rota;
	s32 zettai;
	s32 rota_num;

	// ���S����̋����ɕϊ�
	x -= center_x;
	y -= center_y;
	last_x -= center_x;
	last_y -= center_y;

#if 0
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( y, x );

	rota_num = now_rota - last_rota;

	// ��Βl�����߂�
	if( rota_num < 0 ){
		zettai = -rota_num;
	}else{
		zettai = rota_num;
	}

	// 180�ȏ�ɂȂ邱�Ƃ͍l���ɂ������̏ꍇ��,�O���R�U�O�Ƃ��čl����
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360�Ƃ����l���ɂȂ邩��x�N�g����ς���K�v������
	}

	// �ݒ�
	if( rota_num < 0 ){
		rota_num = -zettai;
	}else{
		rota_num = zettai;
	}
#endif
	rota_num = CalcTool_CircleVectorDistance( last_x, last_y, x, y, 0 );
	rota_num = NMIX_SOOP_SPEED_GET( rota_num );
	return rota_num;
}




//-----------------------------------------------------------------------------
/**
 *
 *		�q�f�[�^
 *
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�q�f�[�^������
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoInit( NMIX_DATA_KO* p_data )
{
	memset( p_data, 0, sizeof(NMIX_DATA_KO) );

	// ���W�ɃZ���^�[���W�����Ă���
	p_data->x = 128;
	p_data->y = 96;
	p_data->last_x = 128;
	p_data->last_y = 96;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�q�f�[�^�@���W
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoMain( NMIX_DATA_KO* p_data )
{
	s32 rota;

#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_cont = 1;	//�^�b�`�p�l���������ςȂ�
		sys.tp_x = 64 + gf_mtRand() % 128;
		sys.tp_y = 64 + gf_mtRand() % 96;
#endif	// DEBUG_NUTMIXER_AUTO
	
	
	// �G���Ă���Ƃ��݂̂������W��ύX
	if( sys.tp_cont ){
		p_data->x = sys.tp_x;
		p_data->y = sys.tp_y;

		// �ēx�^�b�`�̎��́A���X�g���������W�ɂ���
		if( p_data->last_touch_flg == FALSE ){
			p_data->last_x = p_data->x;
			p_data->last_y = p_data->y;
		}
	}
	// ���̍��W�ƈȑO�̍��W�����]�p�����߂�
	p_data->rota = NMIX_DATA_CalcRota( p_data->x, p_data->y, 
			p_data->last_x, p_data->last_y,
			NMIX_SOOP_ROTA_CX, NMIX_SOOP_ROTA_CY );

	p_data->last_x = p_data->x;
	p_data->last_y = p_data->y;

	p_data->last_touch_flg = sys.tp_cont;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�q�ʐM�f�[�^�@�쐬
 *
 *	@param	p_commdata	�ʐM�f�[�^
 *	@param	p_data		���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoMake( NUTMIX_ONE* p_commdata, NMIX_DATA_KO* p_data )
{
	p_commdata->x = p_data->x;
	p_commdata->y = p_data->y;
#if 0
	if( p_data->rota < 0 ){
		p_commdata->rota = (-p_data->rota) & 0xffff;
		p_commdata->rota_way = 1;
	}else{
		p_commdata->rota = p_data->rota & 0xffff;
		p_commdata->rota_way = 0;
	}
#else

	if( p_data->rota < 0 ){
		p_commdata->rota = (-p_data->rota);
		p_commdata->rota_way = 1;
	}else{
		p_commdata->rota = p_data->rota;
		p_commdata->rota_way = 0;
	}
#endif
}





//-----------------------------------------------------------------------------
/**
 *				�e�̂ݕK�v�Ȃ���
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	�X�[�v�^�C�v�ɑΉ�������]���f��
//	NMIX_DATA_SOOP_ROTA_PAR_MAX��100�l�Ƃ����l
//=====================================
//#define NMIX_DATA_SOOP_ROTA_PAR_MAX	( 512 )
#define NMIX_DATA_SOOP_ROTA_PAR_MAX	( 204 )
static const u8	NMIX_DATA_SoopRotaPar[ NMIX_SOOPTYPE_SOOP_NUM ] ={
	8,	// �X�[�v
	7,	// �N���[��
	7,	// �\�{��
};

//-------------------------------------
//	�^�C�v�ʁ@���x�����x
//=====================================
static const u16 NMIX_DATA_SoopRotaSub[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	64,	   // �X�[�v
	72,	   // �N���[��
	80,	   // �\�{��
};

// ���̍��W���X�[�v�����`�F�b�N
#define NMIX_DEMO_SOOPIN_MIN_DIST	( 16 )	// �Œ�ł����S����16�����ɂ���K�v������
#define NMIX_DEMO_SOOPIN_MAX_OFS	( 8 )	// ���̃X�[�v���{���̒l���O�܂Ń^�b�`�p�l����������
#define NMIX_DEMO_SOOPIN_DEF_SIZE	( 64 )	// ���̃X�[�v�T�C�Y���a

#define NMIX_DEMO_SOOPIN_OK		( 0 )
#define NMIX_DEMO_SOOPIN_MIN	( 1 )	/// ���S����̋���������Ȃ�
#define NMIX_DEMO_SOOPIN_MAX	( 2 )	/// ���S���痣�ꂷ��


// ��]���x�v�Z�p
#define NMIX_DEMO_ROTACALC_SOOPIN_MIN_DIV	( 2 )	// ���S�ɋ߂��Ƃ��ɉ�]���x���犄��l

//----------------------------------------------------------------------------
/**
 *	@brief	���̍��W���X�[�v�����`�F�b�N
 *
 *	@param	p_data		���[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@retval	NMIX_DEMO_SOOPIN_OK		( 0 )
 *	@retval NMIX_DEMO_SOOPIN_MIN	( 1 )
 *  @retval	NMIX_DEMO_SOOPIN_MAX	( 2 )
 */
//-----------------------------------------------------------------------------
static u32 NMixData_SoopRota_PlayerInSoop( NMIX_DATA_SOOP* p_data, int x, int y )
{
	fx32 scale;
	u32 speed;
	u32 soop_dist;
	u32 center_dist;

	// ���S����̋��������߂�
	center_dist = GetVectorDistance( 
				x, y,
				NMIX_SOOP_ROTA_CX, NMIX_SOOP_ROTA_CY );

	// �X�s�[�h����X�[�v�̔��a�����߂�
	if( p_data->sp_rota >= 0 ){
		speed = p_data->sp_rota;
	}else{
		speed = -p_data->sp_rota;
	}
	scale = NMIX_DATA_SoopSpeedGraScale( speed, p_data->soop_type );
	soop_dist = FX_Mul( scale, NMIX_DEMO_SOOPIN_DEF_SIZE * FX32_ONE ) >> FX32_SHIFT;

	soop_dist += NMIX_DEMO_SOOPIN_MAX_OFS;

	if( (center_dist < NMIX_DEMO_SOOPIN_MIN_DIST) ){
		return NMIX_DEMO_SOOPIN_MIN;
	}else if( (center_dist > soop_dist) ){
		return NMIX_DEMO_SOOPIN_MAX;
	}
	return NMIX_DEMO_SOOPIN_OK;
}
 
//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v��]����
 *
 *	@param	p_data			���[�N
 *	@param	cp_commdata		�ʐM�f�[�^
 *	@param	comm_count		�ʐM����̐�
 *	@param	rota_way		��]���Ăق�������
 *
 *	@return	���݂̉�]�p�x
 */
//-----------------------------------------------------------------------------
u16 NMIX_DATA_SoopRota( NMIX_DATA_SOOP* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 rota_way )
{
	int i;
	s32 rota_ave;	// �F�̉�]�p�x�̕���
	s32 comm_count_s;
	int net_id;
	fx32 par;
	s32 last_rota;
	u16 rota;
	u32 soop_in_result;	// �X�[�v�͈͓��`�F�b�N����

	// �FOK�Ȃ����A�ɂ���ŏ�����
	p_data->ok_area = TRUE;

	// �F�̉�]�p�x�̕��ς����߂�
	rota_ave = 0;
	for( i=0; i<comm_count; i++ ){
		net_id = cp_commdata->playno_netid[ i ];

		// ���̃v���C���[�́A�X�[�v���̈ʒu�ɂ��邩�`�F�b�N
		soop_in_result = NMixData_SoopRota_PlayerInSoop( p_data, 
				cp_commdata->get_game_data[ net_id ].one.x,
				cp_commdata->get_game_data[ net_id ].one.y );

	  	
		switch( soop_in_result ){
		case NMIX_DEMO_SOOPIN_OK:
			rota = cp_commdata->get_game_data[ net_id ].one.rota;
			break;
		case NMIX_DEMO_SOOPIN_MIN:
			rota = cp_commdata->get_game_data[ net_id ].one.rota / NMIX_DEMO_ROTACALC_SOOPIN_MIN_DIV;
			p_data->ok_area = FALSE;
			break;
		case NMIX_DEMO_SOOPIN_MAX:
			rota = 0;
			p_data->ok_area = FALSE;
			break;
		}
		if( cp_commdata->get_game_data[ net_id ].one.rota_way == 0 ){
			rota_ave += rota;
		}else{
			rota_ave -= rota;
		}
	}

	comm_count_s = comm_count;
	rota_ave = rota_ave / comm_count_s;
	
	// �X�[�v�^�C�v���f������X�s�[�h����
	par = FX_Div( NMIX_DATA_SoopRotaPar[ p_data->soop_type ]*FX32_ONE, NMIX_DATA_SOOP_ROTA_PAR_MAX*FX32_ONE );
	rota_ave = FX_Mul( rota_ave*FX32_ONE, par ) >> FX32_SHIFT;

	// �F�̉�]�p�x�����]�X�s�[�h���v�Z
	p_data->sp_rota += rota_ave;


	// �����l�𑫂�����
	if( p_data->sp_rota > 0 ){
		p_data->sp_rota -= NMIX_DATA_SoopRotaSub[ p_data->soop_type ];
		if( p_data->sp_rota < 0 ){
			p_data->sp_rota = 0;
		}
	}else if( p_data->sp_rota < 0 ){
		p_data->sp_rota += NMIX_DATA_SoopRotaSub[ p_data->soop_type ];
		if( p_data->sp_rota > 0 ){
			p_data->sp_rota = 0;
		}
	}

	// sp_rota�̒l��+- NMIX_SOOP_MAX_ROTA�ȓ��ɂȂ�悤�ɂ���
	if( p_data->sp_rota > NMIX_SOOP_MAX_ROTA ){
		p_data->sp_rota = NMIX_SOOP_MAX_ROTA;
	}else if( p_data->sp_rota < -NMIX_SOOP_MAX_ROTA ){
		p_data->sp_rota = -NMIX_SOOP_MAX_ROTA;
	}

	// �O�̉�]�p�x�ۑ�
	last_rota = p_data->now_rota;

	// ��]
	p_data->now_rota += CalcTool_CircleVectroDistRotaGet( NMIX_SOOP_ROTA_GET_R, NMIX_SOOP_SPEED_RESET( p_data->sp_rota ) );

	// ��]�񐔂�ݒ�
	// ��]�����������Ă��邩�`�F�b�N
	if( ((rota_way == 0) && (p_data->sp_rota >= 0)) ||
		((rota_way == 1) && (p_data->sp_rota < 0)) ){

		if( rota_way == 0 ){
			if( (last_rota & 0xffff) > (p_data->now_rota & 0xffff) ){
				p_data->rota_count ++;
			}
		}else{
			if( (last_rota & 0xffff) < (p_data->now_rota & 0xffff) ){
				p_data->rota_count ++;
			}
		}
	}

	return p_data->now_rota & 0xffff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̉�]�p�x���擾����
 *
 *	@param	cp_data		���[�N
 *
 *	@return	��]�p�x
 */
//-----------------------------------------------------------------------------
u16 NMIX_DATA_SoopGetRota( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->now_rota & 0xffff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̃X�[�v�^�C�v�ŉ���]������
 *
 *	@param	cp_data		���[�N
 *
 *	@return	��]�J�E���g
 */
//-----------------------------------------------------------------------------
u32 NMIX_DATA_SoopGetRotaCount( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->rota_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�^�C�v�ݒ�
 *
 *	@param	p_data	���[�N
 *	@param	type	�X�[�v�^�C�v
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_SoopSetType( NMIX_DATA_SOOP* p_data, int type )
{
	GF_ASSERT( type < NMIX_SOOPTYPE_SOOP_NUM );
	p_data->soop_type = type;
	p_data->rota_count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̉�]�X�s�[�h�擾
 *
 *	@param	cp_data		���[�N
 *
 *	@return	��]�X�s�[�h
 */
//-----------------------------------------------------------------------------
s32 NMIX_DATA_SoopGetRotaSpeed( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->sp_rota;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�X�s�[�h�Ɋ֌W����̂��̌v�Z
 *	
 *	@param	p_data		���[�N
 *	@param	speed		�X�s�[�h
 *	@param	soop_type	�X�[�v�^�C�v
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_SoopSpeedMain( NMIX_DATA_SOOP_SPEED* p_data, s32 speed, int soop_type )
{
	p_data->kobosi_eff = FALSE;
	p_data->koge_eff = 0;

	// ��]�X�s�[�h���炱�ڂ�邩�A�����邩�`�F�b�N����
	if( NMIX_DATA_SoopSpeedKobore( speed, soop_type ) ){
		// ���ڂ��
		p_data->speed_over_count ++;

		if( p_data->speed_over_count >= NMIX_SOOP_KOBORE_RETIME ){
			if( p_data->kobosi_count < NMIX_SOOP_SCORE_MAX ){
				p_data->kobosi_count ++;
			}
			p_data->kobosi_eff = TRUE;
			p_data->speed_over_count = 0;
		}

		// ���ł�����n�߂Ă̂���
		p_data->first_koge_eff = FALSE;
	}else if( NMIX_DATA_SoopSpeedKoge( speed, soop_type ) ){
		// ������
		p_data->speed_none_count ++;

		if( p_data->speed_none_count >= NMIX_SOOP_KOGE_RETIME ){
			p_data->speed_none_count = 0;

			// ���߂ďł�����A���o��
			if( p_data->first_koge_eff == FALSE ){
				p_data->koge_eff = NMIX_GAME_COMM_KOGE_KEMURI_REQ;
				p_data->first_koge_eff = TRUE;
			}else{
				p_data->koge_eff = NMIX_GAME_COMM_KOGE_KOGE_REQ;

				if( p_data->koge_count < NMIX_SOOP_SCORE_MAX ){
					p_data->koge_count ++;
				}
			}
		}
	}else{
		// ���ł�����n�߂Ă̂���
		p_data->first_koge_eff = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ڂ�邩�`�F�b�N
 *
 *	@param	speed		�X�s�[�h
 *	@param	soop_type	�^�C�v
 *
 *	@retval	TRUE	���ڂ��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopSpeedKobore( s32 speed, int soop_type )
{
	int zettai = MATH_IAbs( speed );

	// �X�[�v�^�C�v�@�ŏI�`�Ԃ͂��ڂ�Ȃ�
	if( soop_type == NMIX_SOOPTYPE_SOOP_2 ){
		return FALSE;
	}

	if( zettai >= NMIX_SOOP_KOBORE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����邩�`�F�b�N
 *
 *	@param	speed		�X�s�[�h
 *	@param	soop_type	�^�C�v
 *
 *	@retval	TRUE	������
 *	@retval FALSE	�����Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopSpeedKoge( s32 speed, int soop_type )
{
	int zettai = MATH_IAbs( speed );

		
	if( zettai <= NMIX_SOOP_KOGE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�s�[�h����g�嗦�����߂�
 *
 *	@param	speed		�X�s�[�h
 *	@param	soop_type	�^�C�v
 *
 *	@retval	�g�嗦
 */
//-----------------------------------------------------------------------------
fx32 NMIX_DATA_SoopSpeedGraScale( u16 speed, int soop_type )
{
	fx32 work;
	fx32 scale;
	s32 speed_work;

	// �X�s�[�h���炱����󂢂��������āA
	// ���ڂ�鋫�E���ő�g��l�ɂȂ�悤�ɋ��߂�
	speed_work = speed - NMIX_SOOP_KOGE;
	if( speed_work < 0 ){
		speed_work = 0;
	}

	work = FX_Mul( NMIX_SOOP_MAX_SCALE, speed_work * FX32_ONE );
	scale = FX_Div( work, (NMIX_SOOP_MAX_ROTA - NMIX_SOOP_KOGE) * FX32_ONE );
	return scale + FX32_ONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	��]�����`�F���W�@������
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_RotaWayCont_Init( NMIX_DATA_ROTA_WAY_CONT* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DATA_ROTA_WAY_CONT) );
	p_work->left_par = 2;
	p_work->rota_way_count  = -1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]�����Ǘ��@���C��
 *
 *	@param	p_work		���[�N
 *	@param	soop_type	�X�[�v�^�C�v
 *	@param	speed		���݉�]�X�s�[�h
 *	@param	team_work	TEAMWORK���_�v�Z����
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_RotaWayCont_Main( NMIX_DATA_ROTA_WAY_CONT* p_work, int soop_type, s32 speed, BOOL team_work )
{
	int next_req;
	u32 rnd;
	u32 way_rnd;
	// ���̉�]�����`�F�b�N�܂ł̃J�E���g�l
	static u8 NextCheckCount[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		{ 30*5 },
		{ 30*4 },
		{ 30*3 },
	};

	p_work->rota_way_chg = FALSE;

	// ���ύX�`�F�b�N���邩�`�F�b�N
	// �t�����ɉ���Ă���Ƃ�
	// TEAMWORK���_�v�Z���͕ύX���Ȃ�
	if( (NMIX_DATA_RotaWayReverseCheck( p_work, speed ) == TRUE) ||
		(team_work == TRUE) ){
		return ;
	}
	
	// ���̃`�F�b�N�܂ł̶������O�Ȃ�����ύX
	if( p_work->rota_way_count < 0 ){
		rnd = gf_mtRand();
		way_rnd = (rnd % 5);
		if( way_rnd <= p_work->left_par ){
			// ��
			next_req = 1;
			p_work->rota_way_chg = TRUE;
		}else{
			// �E
			next_req = 0;
			p_work->rota_way_chg = TRUE;
		}

		// �P�O�ƈꏏ�̂Ƃ�
		if( next_req == p_work->rota_way_req ){
			// ���E�`�F�b�N	
			if( p_work->rota_way_req == 1 ){
				if( (p_work->left_par - 1) >= 0 ){
					p_work->left_par --;
				}
			}else{
				if( (p_work->left_par + 1) < 5 ){
					p_work->left_par ++;
				}
			}
		}else{
			p_work->rota_way_req = next_req;
			p_work->left_par = 2;
		}

		OS_Printf( "rnd %d left_par %d\n", rnd, p_work->left_par );

		// ���̃G�t�F�N�g�܂ł̎���
		p_work->rota_way_count = NextCheckCount[ soop_type ] + (rnd % (2*30));
	}

	p_work->rota_way_count --;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�����ɐi��ł��邩�`�F�b�N
 *
 *	@param	cp_work		���[�N
 *	@param	speed		���݃X�s�[�h
 *
 *	@retval	TRUE	�t����
 *	@retval	FALSE	�ǂ�����
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_RotaWayReverseCheck( const NMIX_DATA_ROTA_WAY_CONT* cp_work, s32 speed )
{
	if( ((speed < 0) && (cp_work->rota_way_req == 0)) ||
		((speed > 0) && (cp_work->rota_way_req == 1)) ){
		return TRUE;
	}
	return FALSE;
}	



#define NMIX_DATA_SOOP_ALPHA_ROTA_TIMING	( 5 )	// ���Ƃ��̉�]�Ƃ����Ƃ���܂ł�����A����������
#define NMIX_DATA_SOOP_ALPHA_TIME_TIMING	( 2*30 )	// ���Ƃ��̎��ԂƂ����Ƃ���܂ł����烿��������
//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�^�C�v�ύX�Ǘ�
 *
 *	@param	p_work		���[�N
 *	@param	soop_rota_count		��]�J�E���g]
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopAdd_Main( NMIX_DATA_SOOP_ADD* p_work, NMIX_DATA_SOOP* p_soop )
{
	static const u8 SoopAddRotaCountTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		16, 16, 16
	};
	int time_alpha = 31;
	int count_alpha = 31;
	int soop_rota_count = NMIX_DATA_SoopGetRotaCount( p_soop );
	int last_time;
	int last_count;

	// �X�[�v�^�C�v�ύX
	if( (p_work->next_time == NMIX_DATA_SOOPADD_NEXT_TIME) || 
		(soop_rota_count >= SoopAddRotaCountTbl[ p_work->soop_type ]) ){
		p_work->soop_type ++;
		p_work->next_time = 0;
		soop_rota_count = 0;	// ���̃��l���߂悤

		if( p_work->soop_type >= NMIX_SOOPTYPE_SOOP_NUM ){
			return TRUE;
		}

		// �X�[�v�^�C�v��ݒ�
		NMIX_DATA_SoopSetType( p_soop, p_work->soop_type );
	}
	
	// ���l�����߂�
	last_time = (NMIX_DATA_SOOPADD_NEXT_TIME - p_work->next_time);
	if( last_time <= NMIX_DATA_SOOP_ALPHA_TIME_TIMING ){
		time_alpha = 31 * last_time;
		time_alpha = time_alpha / NMIX_DATA_SOOP_ALPHA_TIME_TIMING;
	}
	last_count = (SoopAddRotaCountTbl[ p_work->soop_type ] - soop_rota_count);
	if( last_count <= NMIX_DATA_SOOP_ALPHA_ROTA_TIMING ){
		count_alpha = 31 * last_count;
		count_alpha = count_alpha / NMIX_DATA_SOOP_ALPHA_ROTA_TIMING;
	}

	// ���l�̏������ق������
	if( time_alpha < count_alpha ){
		p_work->rota_alpha = time_alpha;
	}else{
		p_work->rota_alpha = count_alpha;
	}
	p_work->next_time ++;

	return FALSE;
}

#define NMIX_DATA_TEAMWORK_CHECK_ROTA	( 600 )
//----------------------------------------------------------------------------
/**
 *	@brief	TEAMWORK�@����
 *
 *	@param	p_work			���[�N
 *	@param	cp_comm_pack	�ʐM�f�[�^
 *	@param	comm_count		����
 *	@param	speed			�X�s�[�h
 *	@param	soop_type		�X�[�v�^�C�v
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_TeamWork_Main( NMIX_DATA_TEAMWORK* p_work, const NUTMIX_GAME_COMM_PACK* cp_comm_pack, int comm_count, s32 speed, int soop_type, BOOL ok_area, BOOL reverse )
{
	u32 dist;
	const NUTMIX_OYA* cp_oya = &cp_comm_pack->get_game_data[ COMM_PARENT_ID ].oya;
	const NUTMIX_ONE* cp_oya_one;
	int i;
	int net_id;
	

	p_work->team_work_req = FALSE;

	// ��������A���ڂꂽ�肵�Ȃ����`�F�b�N
	if( (NMIX_DATA_SoopSpeedKoge( speed, soop_type ) == TRUE) ||
		(NMIX_DATA_SoopSpeedKobore( speed, soop_type ) == TRUE) ||
		(ok_area == FALSE) ){
		p_work->team_work_time_add_wait = 0;
		p_work->team_work_time_add_flg = FALSE;
		return ;
	}
	

	// 1�p�Ȃ�łȂ�
	if( comm_count <= 1 ){
		p_work->team_work_time_add_wait = 0;
		p_work->team_work_time_add_flg = FALSE;
		return ;
	}

	// �t��]���Ă�����łȂ�
	if( reverse == TRUE ){
		return ;
	}

	// �����ƒ��Ԃ��~�܂��Ă�����łȂ�
	for( i=0; i<comm_count; i++ ){
		net_id = cp_comm_pack->playno_netid[ i ];
		cp_oya_one = &cp_comm_pack->get_game_data[ net_id ].one;

		if( cp_oya_one->rota <= NMIX_DATA_TEAMWORK_CHECK_ROTA ){
			return ;
		}
	}

	// �F���e�̃G���A�ɓ����Ă��邩�`�F�b�N����
	for( i=1; i<comm_count; i++ ){

		net_id = cp_comm_pack->playno_netid[ i ];
		
		dist = GetVectorDistance( 
				cp_oya->x[ 0 ], cp_oya->y[ 0 ],
				cp_oya->x[ net_id ], cp_oya->y[ net_id ] );

		if( dist > NMIX_DATA_TEAMWORK_AREA ){
			p_work->team_work_time_add_wait = 0;
			p_work->team_work_time_add_flg = FALSE;
			return ;	// �G���A�O�Ȃ̂Ŕ�����
		}
	}


	// TEAMWORK���_�@�����Z�J�n�E�G�C�g
	if( p_work->team_work_time_add_wait < NMIX_DATA_TEAMWORK_EFF_ADD_WAIT ){
		p_work->team_work_time_add_wait ++;
	}else{
		// �ŏ���1��ڂ͂����Ȃ�
		// �^�C���̊Ԋu�ŃG�t�F�N�g���o��
		if( (p_work->team_work_time % NMIX_DATA_TEAMWORK_EFF_TIMING) == 0 ){
			p_work->team_work_req = TRUE;
		}

		// �^�C���J�E���g
		p_work->team_work_time ++;
		p_work->team_work_time_add_flg = TRUE;
	}


}

//----------------------------------------------------------------------------
/**
 *	@brief	�e����������
 *	
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaInit( NMIX_DATA_OYA* p_data )
{
	memset( p_data, 0, sizeof(NMIX_DATA_OYA) );
	NMIX_DATA_RotaWayCont_Init( &p_data->rota_waycont );
	p_data->soop_add.rota_alpha = 31;
	// ��]�����ύX�`�F�b�N���P����s���Ă���
	NMIX_DATA_RotaWayCont_Main( &p_data->rota_waycont, 0, 0, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���C������
 *
 *	@param	p_data	���[�N
 *	@param	cp_commdata	�ʐM�f�[�^
 *	@param	comm_count	�ʐM���萔
 *
 *	@retval	TRUE	�Q�[���I��
 *	@retval	FALSE	�Q�[���r��
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_OyaMain( NMIX_DATA_OYA* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count )
{
	s32 speed;
	BOOL result;

	// �X�[�v�^�C�v�ύX
	result = NMIX_DATA_SoopAdd_Main( &p_data->soop_add, &p_data->soop_cont );

	// �����X�[�v�^�C�v�ȏ�ɂȂ�����Q�[���I��
	if( result == TRUE ){
		return TRUE;
	}
	
	// �X�[�v��]����
	NMIX_DATA_SoopRota( &p_data->soop_cont, cp_commdata, comm_count, p_data->rota_waycont.rota_way_req );

	// �X�s�[�h�擾
	speed = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );

	// �X�[�v�X�s�[�h�ɂ��F�X�ȃp�����[�^�ݒ�
	NMIX_DATA_SoopSpeedMain( &p_data->soop_speed_data, speed, p_data->soop_add.soop_type );

	// TEAMWORK�^�C���ݒ�
	NMIX_DATA_TeamWork_Main( &p_data->team_work, cp_commdata, comm_count, speed, p_data->soop_add.soop_type, p_data->soop_cont.ok_area, NMIX_DATA_RotaWayReverseCheck( &p_data->rota_waycont, speed ) );

	// ��]�����ύX�`�F�b�N
	NMIX_DATA_RotaWayCont_Main( &p_data->rota_waycont, p_data->soop_add.soop_type, speed, p_data->team_work.team_work_time_add_flg );
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�ʐM�f�[�^�쐬
 *
 *	@param	p_data			���[�N
 *	@param	p_comm_pack		�ʐM�R�}���hPACKAGE
 *	@param	comm_count		�ʐM�l��
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	int i;
	NUTMIX_OYA* p_oya = &p_comm_pack->send_game_data.oya;
	s32	sp_rota;
	
	// �ʐM�f�[�^�ݒu
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_oya->x[ i ] = p_comm_pack->get_game_data[ i ].one.x;
		p_oya->y[ i ] = p_comm_pack->get_game_data[ i ].one.y;
	}
	
	sp_rota = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );
	if( sp_rota >= 0 ){	// �O�̎��͉E���Ȃ��Ǝ󂯎�葤������
		p_oya->rota_sp = sp_rota & 0xffff;
		p_oya->rota_way = 0;
	}else{
		p_oya->rota_sp = (-sp_rota) & 0xffff;
		p_oya->rota_way = 1;
	}
	p_oya->rota		= NMIX_DATA_SoopGetRota( &p_data->soop_cont );

	p_oya->koge_req = p_data->soop_speed_data.koge_eff;
	p_oya->kobore_req = p_data->soop_speed_data.kobosi_eff;

	// ��]���N�G�X�g�����ݒ�
	p_oya->now_rota_req = p_data->rota_waycont.rota_way_req;
	p_oya->rota_req_eff = p_data->rota_waycont.rota_way_chg;

	// ���̃X�[�v�`��ƃ��l
	if( p_data->soop_add.soop_type < NMIX_SOOPTYPE_SOOP_NUM ){
		p_oya->mix_type = p_data->soop_add.soop_type;
	}else{
		p_oya->mix_type = NMIX_SOOPTYPE_SOOP_2;
	}

	p_oya->alpha_num = p_data->soop_add.rota_alpha;

	// �L���L���G�t�F�N�g
	p_oya->kirakira_eff = p_data->team_work.team_work_req;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�f�[�^�쐬
 *
 *	@param	p_data			�f�[�^
 *	@param	p_oya			�e�f�[�^�i�[��
 *	@param	comm_count		�ʐM���萔
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake_Init( NMIX_DATA_OYA* p_data, NUTMIX_OYA* p_oya, int comm_count )
{
	int i;
	s32	sp_rota;

	// �ʐM�f�[�^�ݒu
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_oya->x[ i ] = 128;
		p_oya->y[ i ] = 96;
	}
	
	
	sp_rota = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );
	if( sp_rota >= 0 ){	// �O�̎��͉E���Ȃ��Ǝ󂯎�葤������
		p_oya->rota_sp = sp_rota & 0xffff;
		p_oya->rota_way = 0;
	}else{
		p_oya->rota_sp = (-sp_rota) & 0xffff;
		p_oya->rota_way = 1;
	}
	p_oya->rota		= NMIX_DATA_SoopGetRota( &p_data->soop_cont );

	p_oya->koge_req = p_data->soop_speed_data.koge_eff;
	p_oya->kobore_req = p_data->soop_speed_data.kobosi_eff;

	// ��]���N�G�X�g�����ݒ�
	p_oya->now_rota_req = p_data->rota_waycont.rota_way_req;
	p_oya->rota_req_eff = p_data->rota_waycont.rota_way_chg;

	// ���̃X�[�v�`��ƃ��l
	p_oya->mix_type = p_data->soop_add.soop_type;
	p_oya->alpha_num = p_data->soop_add.rota_alpha;

	// �L���L���G�t�F�N�g
	p_oya->kirakira_eff = p_data->team_work.team_work_req;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������Ԍv�Z
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCookCountAdd( NMIX_DATA_OYA* p_data )
{
	// �������ԃJ�E���g
	p_data->cook_time ++;
}


static const u8 playnum_teamwork_score[ NUTMIXER_MEMBER_MAX ] = {	// TEAMWORK�v���C���_
	0, 1, 5, 10
};
enum{
	NMIX_PORUTO_PARA_KARAI,	// ����́A�؂̎��̕��̒萔�ɂ����Ă��܂�
	NMIX_PORUTO_PARA_SIBUI,	// include/itemtool/nuts.h
	NMIX_PORUTO_PARA_AMAI,	// include/savedata/poruto_def.h
	NMIX_PORUTO_PARA_NIGAI,	// �ɂ͂����Ă��܂���
	NMIX_PORUTO_PARA_SUPPAI,
	NMIX_PORUTO_PARA_NUM,
};

// TEAMWORK���_�J�E���g�^�C�~���O
#define NMIX_TEAMWORK_SCORE_TIMING	( 6 )
#define NMIX_TEAMWORK_SCORE_DIV		( 10 )

#define NMIX_TEAMWORK_SCORE_SUB_MAX	( 10 )
#define NMIX_MAROYAKA_LIMIT	( 15 )

static int teamWorkScoreGet( u32 time, u32 comm_count )
{
	int score;
	score = ((time / NMIX_TEAMWORK_SCORE_TIMING)*playnum_teamwork_score[ comm_count -1 ]) / NMIX_TEAMWORK_SCORE_DIV;	// �b�P�ʂ� * (0.2)

	if( score > NMIX_SOOP_SCORE_MAX ){
		score = NMIX_SOOP_SCORE_MAX;
	}
	return score;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�f�[�^�쐬
 *
 *	@param	p_data			���[�N
 *	@param	p_poruto		�|���g�f�[�^�i�[��
 *	@param	cp_commdata		�ʐM�f�[�^
 *	@param	comm_count		�ʐM���萔
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCalcPorutoData( NMIX_DATA_OYA* p_data, PORUTO_DATA* p_poruto, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 heapID )
{
	NUTSDATA* p_nut;	// �؂̎��f�[�^
	int i, j;
	const NUTMIX_GAME_BGFORE* cp_before = cp_commdata->get_oya_ko_before_data.before;
	s32 param[ NMIX_PORUTO_PARA_NUM ] = {0,0,0,0,0};		// �h�@�a�@�Á@��@�_
	s32 umami = 0;
	s32 param_result[ NMIX_PORUTO_PARA_NUM ];		// �h�@�a�@�Á@��@�_�@
	s32 umami_result;
	int equal_count;	// �؂̎���������
	int equal_count_max;// �����؂̎��̐��ő吔
	BOOL black_poru_flg;	// ���߃|���g�t���O
	int sub_idx;
	int sub_num;
	int minus_count;
	int cook_time_para;	// �������Ԃ���Z�o���銮���l�@1=100�̒l
	int calc_work;
	u8 poruto_param[ NMIX_PORUTO_PARA_NUM ];
	int netid, netid_j;

	// �@�F�̖؂̎��f�[�^�擾
	equal_count_max = 0;
	for( i=0; i<comm_count; i++ ){
		netid = cp_commdata->playno_netid[ i ];
		p_nut = Nuts_DataLoadItem( cp_before[ netid ].nut_type, heapID );
		// �����؂̎����J�E���g
		equal_count = 0;
		for( j=0; j<comm_count; j++ ){
			netid_j = cp_commdata->playno_netid[ j ];
			if( cp_before[ netid ].nut_type == cp_before[ netid_j ].nut_type ){
				equal_count ++;
			}
		}
		if( equal_count > equal_count_max ){
			equal_count_max = equal_count;
		}
		// �p�����[�^�����Z
		OS_Printf( "��player_%d  ", i );
		for( j=0; j<NMIX_PORUTO_PARA_NUM; j++ ){
			param[ j ] += Nuts_ParamGet( p_nut, NUTS_PRM_KARAI+j );
			OS_Printf( "%d  ", Nuts_ParamGet( p_nut, NUTS_PRM_KARAI+j ) );
		}
		umami += Nuts_ParamGet( p_nut, NUTS_PRM_UMAI );
		OS_Printf( "%d  \n", Nuts_ParamGet( p_nut, NUTS_PRM_UMAI ) );

		sys_FreeMemoryEz( p_nut );
	}

	// �l���̔������@�����|���g�̂Ƃ��́A���߃|���g
	if( (equal_count_max >= 2) && ( comm_count > 1 ) ){
		black_poru_flg = TRUE;
	}else{
		black_poru_flg = FALSE;
	}

	// �F���܂݂́A���� �Ɓ@�v���C�l�������Z
	umami_result = (umami / comm_count) - comm_count;

	
	// �A�ł��������[���v�Z
	// �B�����Ƀ}�C�i�X�̐����v�Z
	minus_count = 0;
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// �_���ς��܂�
		sub_idx = (i + 1) % NMIX_PORUTO_PARA_NUM;	// �h���ɕύX
		param_result[ i ] = param[ i ] - param[ sub_idx ];
		if( param_result[i] < 0 ){
			minus_count ++;
		}
	}

	OS_Printf( "�h%d�@�a%d�@��%d�@��%d�@�_%d\n", param_result[0],
			param_result[1], param_result[2], param_result[3], 
			param_result[4]);

	// �C�}�C�i�X�����@�݂�Ȉ���
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// �_���ς��܂�
		param_result[ i ] -= minus_count;
	}
	
	// �}�C�i�X��4�ȏ�Ȃ�܂����|���g
	if( minus_count >= 4 ){
		black_poru_flg = TRUE;
	}


	// �������ԁ@�����l�쐬
	cook_time_para = (NMIX_DATA_SOOP_COOK_MAX_TIME*1000) / p_data->cook_time;
	if( (cook_time_para % 10) >= 5 ){	// �����_��3�ʎl�̌ܓ�
		cook_time_para += 10;
	}
	cook_time_para /= 10;	// �����_��Q�ʂ܂łɂ���

	// �������Ԋ����l
	OS_Printf( "�������Ԋ����l %d / 100 \n", cook_time_para );

	OS_Printf( "�}�C�i�X�l�����Z��@�h%d�@�a%d�@��%d�@��%d�@�_%d\n", param_result[0],
			param_result[1], param_result[2], param_result[3], 
			param_result[4]);

	OS_Printf( "�ł�������%d�@���ڂ�����%d\n", p_data->soop_speed_data.koge_count, p_data->soop_speed_data.kobosi_count );
	
	// �D�Q�[���̌v�Z���ʂ�ǉ�
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// �_���ς��܂�
		// ���������l�ݒ�
		calc_work = param_result[ i ] * cook_time_para;
		if( (calc_work % 100) >= 50 ){	// �����_�ȉ��l�̌ܓ�
			calc_work += 100;
		}
		calc_work = calc_work / 100;	// ���������l�����������ɂ���
		param_result[ i ] = calc_work - (p_data->soop_speed_data.koge_count + p_data->soop_speed_data.kobosi_count);	// ���������l���炱�ڂ������@�ł������������炷

		// �}�C�i�X�ɂȂ�����0�ɂ���
		if( param_result[ i ] < 0 ){
			param_result[ i ] = 0;
		}
	}

	OS_Printf( "TEAMWORK %d\n", p_data->team_work.team_work_time / NMIX_TEAMWORK_SCORE_TIMING );

	// ���܂݂���@TEAMWORK�^�C��������
	if( comm_count > 1 ){
		sub_num = teamWorkScoreGet( p_data->team_work.team_work_time, comm_count );

		if( sub_num > NMIX_TEAMWORK_SCORE_SUB_MAX ){
			sub_num = NMIX_TEAMWORK_SCORE_SUB_MAX;
		}
		umami_result -= sub_num;
	}
	if( umami_result < NMIX_MAROYAKA_LIMIT ){
		umami_result = NMIX_MAROYAKA_LIMIT;
	}

	OS_Printf( "���܂� %d  ���ʂ��܂� %d \n", (umami / comm_count), umami_result );

	// �|���g�쐬�p�z��ɐݒ�
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// �_���ς��܂�
		poruto_param[ i ] = param_result[ i ];
	}

	OS_Printf( "�h%d�@�a%d�@��%d�@��%d�@�_%d\n", poruto_param[0],
			poruto_param[1], poruto_param[2], poruto_param[3], 
			poruto_param[4]);

	
	// �E�|���g�쐬
	p_data->poruto_type = PorutoData_CalcParam( p_poruto, poruto_param, umami_result, black_poru_flg );

	// �|���g�̃^�C�v�ƃ��x���ƕۑ�
	p_data->poruto_lv	= PorutoData_GetLevel( p_poruto );

	OS_Printf( "poruto_type %d\n", p_data->poruto_type);
}



//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����ʒʐM�f�[�^���M
 *
 *	@param	p_data			�f�[�^
 *	@param	p_comm_pack		�ʐM���[�N
 *	@param	comm_count		�ʐM���� 
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake_Result( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	NUTMIX_COMM_RESULT* p_result = &p_comm_pack->send_oya_result_data;
	int time_set;
	
	p_result->kobore_num = p_data->soop_speed_data.kobosi_count;
	p_result->kogasi_num = p_data->soop_speed_data.koge_count;
	p_result->match_num	 = teamWorkScoreGet( p_data->team_work.team_work_time, comm_count );
	p_result->poruto_type	= p_data->poruto_type;
	p_result->poruto_lv		= p_data->poruto_lv;

	time_set = p_data->cook_time;
	p_result->min			= time_set / (60*30);	// ��
	time_set -= p_result->min * (60*30);
	p_result->second		= time_set / (30);		// �b
	time_set -= p_result->second * 30;
	p_result->dec			= (100*time_set)/30;	// 30��100�ɂȂ�悤�ɒl�ݒ�

	OS_Printf( "cook_time %d\n", p_data->cook_time );
}



#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
void NMIX_DATA_OyaCommDataMake_Result_MaxDebug( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	NUTMIX_COMM_RESULT* p_result = &p_comm_pack->send_oya_result_data;
	
	p_result->kobore_num = NMIX_SOOP_SCORE_MAX;
	p_result->kogasi_num = NMIX_SOOP_SCORE_MAX;
	p_result->match_num	 = NMIX_SOOP_SCORE_MAX;
	p_result->poruto_type	= PORUTO_FLAVOR_BI_SO;
	p_result->poruto_lv		= 99;

	p_result->min			= 99;	// ��
	p_result->second		= 99;		// �b
	p_result->dec			= 99;
}
#endif // NMIX_DEBUG_DUMMY_RESULT_ON
