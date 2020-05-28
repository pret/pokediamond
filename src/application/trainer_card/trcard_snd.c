//==============================================================================================
/**
 * @file	trcard_snd.c
 * @brief	�g���[�i�[�P�[�X�@�o�b�`�S�Ց���
 * @author	Satoshi Nohara
 * @date	2005.12.06
 */
//==============================================================================================
#include "common.h"
#include "system/snd_tool.h"
#include "trcard_sys.h"
#include "trcard_snd.h"

/*
	//����

	�E�o�b�`�ȊO��SE���鎞�ɁA�o�b�`�̉���S�Ď~�߂鏈�����K�v

	�E�ψ�ɂ����̂ŁA�o�b�`���Ƃɑ����̂��ꕝ������������肸��ĕ�������
*/


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define SND_BADGE_NO_USE			(0xff)

//��{����
enum{
	P_C = 0,					//C
	P_D = (64*2),				//D
	P_E = (64*4),				//E
	P_F = (64*5),				//F
	P_G = (64*7),				//G
	P_A = (64*9),				//A
	P_B = (64*11),				//B
	PCC = (64*12),				//C

	//P_DIFF_MAX = (64+32),		//�ő剹������
	P_DIFF_MAX = (64+32+512),	//�ő剹������(06.04.12)
	P_DIFF = (P_DIFF_MAX/TR_CARD_BADGE_LV_MAX),	//��������(���x�����Ŋ������l)
};


//==============================================================================================
//
//	�f�[�^
//
//==============================================================================================
//�����e�[�u��
static const u16 basic_pitch_tbl[8] = { P_C, P_D, P_E, P_F, P_G, P_A, P_B, PCC };	//��������Ȃ�


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
static void Snd_DebugBadge( SND_BADGE_WORK* wk );
static void Snd_BadgeWorkPlay_Sub1( SND_BADGE_WORK* wk );
static BOOL Snd_BadgeWorkPlay_Sub2( SND_BADGE_WORK* wk, const int no, const u8 lv );
static BOOL Snd_BadgeWorkPlay_Sub3( SND_BADGE_WORK* wk, const int no, const u8 lv );
static BOOL Snd_BadgeWorkPlay_Sub4( SND_BADGE_WORK* wk, const int no, const u8 lv );
static void Snd_BadgeWorkSort2( SND_BADGE_WORK* wk );
static void Snd_BadgeWorkSort3( SND_BADGE_WORK* wk, int num, int player, int no );
static void Snd_BadgeWorkPitch( int num, const int no, const u8 lv );


//==============================================================================================
//
//	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�g���[�i�[�P�[�X�@�o�b�W���[�N������
 *
 * @param	wk		SND_BADGE_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_DebugBadge( SND_BADGE_WORK* wk )
{
	int i,j;

	OS_Printf( "============================\n" );

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){
		OS_Printf( "i=%d, 0=%d\n", i, wk->player[i][0] );
		OS_Printf( "i=%d, 1=%d\n", i, wk->player[i][1] );
	}

}

//--------------------------------------------------------------
/**
 * @brief	�g���[�i�[�P�[�X�@�o�b�W���[�N������
 *
 * @param	wk		SND_BADGE_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BadgeWorkInit( SND_BADGE_WORK* wk )
{
	int i,j;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){
		wk->player[i][0] = i;						//"0,1,2,3"
		wk->player[i][1] = SND_BADGE_NO_USE;		//�N���A
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�g���[�i�[�P�[�X�@�o�b�W�S�Ղ�炷
 *
 * @param	wk		SND_BADGE_WORK�^�̃|�C���^
 * @param	no		�o�b�W�i���o�[(0����7)
 * @param	lv		�o�b�W���x��(0�`4)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BadgeWorkPlay( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i;

	//�g�p���ŁA���łɍĐ��I�����Ă�����̂̓N���A����I
	Snd_BadgeWorkPlay_Sub1( wk );

	//debug
	//Snd_DebugBadge( wk );

	//�n���ꂽ�o�b�`���g�p���̎��́A�����v���C���[�ōĐ�����I
	if( Snd_BadgeWorkPlay_Sub2(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub2 �Đ�!" );
		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	//�n���ꂽ�o�b�`��V�K�ɖ炷��
	if( Snd_BadgeWorkPlay_Sub3(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub3 �Đ�!" );

		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	//�v���C���[���S�Ė��܂��Ă��鎞�́A��ԌÂ��f�[�^�������āA�㏑������
	if( Snd_BadgeWorkPlay_Sub4(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub4 �Đ�!" );

		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	return;
}

//�g�p���ŁA���łɍĐ��I�����Ă�����̂̓N���A����I
static void Snd_BadgeWorkPlay_Sub1( SND_BADGE_WORK* wk )
{
	int i;

	//�v���C���[�������`�F�b�N
	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//�g�p���ɂȂ��Ă���
		if( wk->player[i][1] != SND_BADGE_NO_USE ){
		
			//�Đ��I�����Ă�����
			if( Snd_PlayerCountPlayingSeq( (PLAYER_SE_1 + wk->player[i][0]) ) == 0 ){
				wk->player[i][1] = SND_BADGE_NO_USE;		//�N���A
				//OS_Printf( "Sub1 �N���A!" );
			}
		}
	}

	//�\�[�g2(�f�[�^���l�߂�)
	Snd_BadgeWorkSort2( wk );
	return;
}

//�n���ꂽ�o�b�`���g�p���̎��́A�����v���C���[�ōĐ�����I
static BOOL Snd_BadgeWorkPlay_Sub2( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//�n���ꂽ�o�b�`���g�p���̎�
		if( wk->player[i][1] == no ){

			//�����n���h���A�v���C���[�Ŗ炷
			Snd_BadgeWorkPitch( wk->player[i][0], no, lv );

			//Snd_BadgeWorkSort( wk, i );	//�\�[�g
			Snd_BadgeWorkSort3( wk, i, wk->player[i][0], no );	//�\�[�g

			return TRUE;
		}
	}

	return FALSE;
}

//�n���ꂽ�o�b�`��V�K�ɖ炷��
static BOOL Snd_BadgeWorkPlay_Sub3( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i,player;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//�g�p���Ă��Ȃ��v���C���[��T��
		if( wk->player[i][1] == SND_BADGE_NO_USE ){

			Snd_BadgeWorkPitch( wk->player[i][0], no, lv );

			Snd_BadgeWorkSort3( wk, i, wk->player[i][0], no );	//�\�[�g
			return TRUE;
		}
	}

	return FALSE;
}

//�v���C���[���S�Ė��܂��Ă��鎞�́A��ԌÂ��f�[�^�������āA�㏑������
static BOOL Snd_BadgeWorkPlay_Sub4( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int num;

	num = (SND_BADGE_PLAYER_MAX-1);

	Snd_BadgeWorkPitch( wk->player[num][0], no, lv );

	Snd_BadgeWorkSort3( wk, num, wk->player[num][0], no );	//�\�[�g

	return TRUE;
}

//�\�[�g(�n���ꂽ�l��擪�ɂ���)
static void Snd_BadgeWorkSort3( SND_BADGE_WORK* wk, int num, int player, int no )
{
	int i;

	for( i=num; i > 0 ;i-- ){
		wk->player[i][0] = wk->player[i-1][0];
		wk->player[i][1] = wk->player[i-1][1];
	}

	//�擪�ɃZ�b�g
	wk->player[0][0] = player;
	wk->player[0][1] = no;
	return;
}

//�\�[�g2(�f�[�^���l�߂�)
static void Snd_BadgeWorkSort2( SND_BADGE_WORK* wk )
{
	int i;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		if( wk->player[i][0] == SND_BADGE_NO_USE ){
			wk->player[i][0] = wk->player[i+1][0];
			wk->player[i+1][0] = SND_BADGE_NO_USE;
		}
	}

	return;
}

//�o�b�`�ɂ�艹���𑀍삷��
//���x���ɂ�艹���̔�����������
static void Snd_BadgeWorkPitch( int num, const int no, const u8 lv )
{
	int diff = P_DIFF * (TR_CARD_BADGE_LV_MAX-lv);
	Snd_ArcPlayerStartSeqEx( (SND_HANDLE_SE_1+num), (PLAYER_SE_1+num), SEQ_SE_DP_BADGE_C );
	//Snd_PlayerSetTrackPitch( (SND_HANDLE_SE_1+num), 0xffff, (basic_pitch_tbl[no]+diff) );	//�ジ��
	Snd_PlayerSetTrackPitch( (SND_HANDLE_SE_1+num), 0xffff, (basic_pitch_tbl[no]-diff) );	//������
	return;
}


