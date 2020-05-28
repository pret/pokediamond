//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		comm_command_nutmixer_func.h
 *	@brief		�ʐM�R�[���o�b�N�֐�
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "nmix_game.h"
#include "communication/communication.h"
#include "comm_command_nutmixer.h"
#include "nmix_gameseq.h"

#define __COMM_COMMAND_NUTMIXER_FUNC_H_GLOBAL
#include "comm_command_nutmixer_func.h"


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
//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		�ʐM�������֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM�̏�����
 */
//-----------------------------------------------------------------------------
void CommCommandNutMixerInitialize( NMIX_GAMEWORK* pWork, MYSTATUS* p_mystate )
{
	int playno;
	int i;

	// �ʐM��ԃ`�F�b�N
	if( pWork->commpack_flg == NUTMIX_COMM_PACK_COMM ){
		// �ʐM�l���擾
		pWork->comm_count = CommGetConnectNum();
	}else{
		// ��ʐM
		pWork->comm_count = 1;
	}
	OS_Printf( "comm_count = %d\n", pWork->comm_count );

	// �ʐM�p�b�N�V�X�e�������J�n
	pWork->comm_work = NMIX_CommPack_CommandInitialize( 
			NutMixer_CommCommandTclGet(),
			NutMixer_CommCommandTblNumGet(),
			pWork,
			pWork->commpack_flg,
			pWork->heapID );


	memset( pWork->game_comm_pack.playno_netid, NUTMIXER_MEMBER_MAX, sizeof(u8) * NUTMIXER_MEMBER_MAX );
	
	if( pWork->commpack_flg == NUTMIX_COMM_PACK_COMM ){
		// �v���C���[�i���o�[�[���l�b�gID�擾�z����쐬
		// �v���C���[�X�e�[�^�X�擾
		playno = 0;
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){

			pWork->game_comm_pack.p_mystate[ i ] = CommInfoGetMyStatus( i );
			if( pWork->game_comm_pack.p_mystate[ i ] != NULL ){
				pWork->game_comm_pack.playno_netid[ playno ] = i;
				playno ++;
			}
		}
	}else{
		pWork->game_comm_pack.playno_netid[ 0 ] = 0;
		pWork->game_comm_pack.p_mystate[ 0 ] = p_mystate;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM�̔j��
 */
//-----------------------------------------------------------------------------
void CommCommandNutMixerDest( NMIX_GAMEWORK* pWork )
{
	// �ʐM�p�b�N�V�X�e���j��
	NMIX_CommPack_CommDelete( pWork->comm_work );
	pWork->comm_work = NULL;
}

//-----------------------------------------------------------------------------
/**
 *		�Q�[������
 *		�����p
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���J�n����		�q��M
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameSysStart( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	OS_Printf( "�e->�q �Q�[���J�n�O�����J�n\n" );
	// �Q�[���O�����J�n
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_BEFORE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���������@�I��	�q��M
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameEnd( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	OS_Printf( "�e->�q �Q�[���I��\n" );
	// �Q�[���������@�I����
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_GAMEEND );
}

//-----------------------------------------------------------------------------
/**
 *		�f�[�^��M�p
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�e����Q�[���J�n�O�����󂯎��
 *
 *	@param	netID		�ڑ�ID
 *	@param	size		�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		���[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameBeforeDataKo( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// �o�b�t�@�Ɋi�[
	memcpy( &p_game->game_comm_pack.get_ko_before_data, pBuff, size );

	// �e�f�[�^��ݒ�
	p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya = p_game->game_comm_pack.get_ko_before_data.oya;

	OS_Printf( "�e->�q�@�X�[�v���l %d\n �����G�t�F�N�g %d \n", p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya.alpha_num, p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya.rota_req_eff);


	OS_Printf( "�e�[���q �Q�[���J�n�O���擾 0[%d] 1[%d] 2[%d] 3[%d] \n", 
			p_game->game_comm_pack.get_ko_before_data.before[0].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[1].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[2].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[3].nut_type );

	// �Q�[���������J�n
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_RES_LOAD );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�q����؂̎��f�[�^���擾
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameBeforeData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;
	int i;
	int in_count;


	// �e�̂Ƃ��󂯎��	
	// �e�́A�S�Ď󂯎������A�q�ɖ؂̎�����]��
	if( NMIX_CommPack_CommGetCurrentID( p_game->comm_work ) == COMM_PARENT_ID ){
		// �o�b�t�@�Ɋi�[
		memcpy( &p_game->game_comm_pack.get_before_data[ netID ], pBuff, size );
		p_game->game_comm_pack.get_before_data_flg[ netID ] = TRUE;

		// �q�ɑ���f�[�^�ɂ��ǉ�
		p_game->game_comm_pack.get_oya_ko_before_data.before[ netID ] = p_game->game_comm_pack.get_before_data[ netID ];

		OS_Printf( "�q�[���e �Q�[���J�n�O���擾 netID[ %d ] nuts_data[ %d ]\n", netID, p_game->game_comm_pack.get_before_data[ netID ] );

		// �ʐM����S�����痈�����`�F�b�N
		in_count = 0;
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
			if( p_game->game_comm_pack.get_before_data_flg[ i ] == TRUE ){
				in_count ++;
			}
		}

		// �S�����炫����A�Q�[���J�n�O���]��
		if( in_count >= p_game->comm_count ){
			OS_Printf( "�q�ɃQ�[���J�n�O���]�� in_c=%d  comm_c=%d\n", in_count, p_game->comm_count );

			// 1��e�̏������f�[�^���n��
			NMIX_DATA_OyaCommDataMake_Init( &p_game->oya_data,
					&p_game->game_comm_pack.get_oya_ko_before_data.oya, p_game->comm_count );	// �ʐM�f�[�^�ݒ�


			// �f�[�^�]��
			NMIX_CommPack_CommSendData( CNM_MIXER_GAME_BEFOREDATA_KO,
					&p_game->game_comm_pack.get_oya_ko_before_data,
					CommNutMixerGetGameBeforeKoSize(),
					p_game->comm_work );
		}
	}

	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���f�[�^���擾			�e����q��
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// �o�b�t�@�Ɋi�[
	memcpy( &p_game->game_comm_pack.get_game_data[ netID ], pBuff, size );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����ʃf�[�^���擾
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameResultData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// �o�b�t�@�Ɋi�[
	memcpy( &p_game->game_comm_pack.get_result_data, pBuff, size );

	OS_Printf( "�e�[���q �Q�[�����ʏ��擾\n" );

	// ���ʕ\���Ɉȍ~
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_RESULT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�f�[�^��M
 *
 *	@param	netID		�ڑ��ԍ�
 *	@param	size		�o�b�t�@�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerPorutoData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// �o�b�t�@�Ɋi�[
	memcpy( p_game->game_comm_pack.p_get_ko_poruto, pBuff, size );
	OS_Printf( "�e�[���q �|���g�f�[�^�擾\n" );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e����@�Q�[�����Â��邩���󂯎��
 *
 *	@param	netID		�ڑ�ID
 *	@param	size		�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		���[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameNextDataKo( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// �o�b�t�@�Ɋi�[
	memcpy( &p_game->game_comm_pack.get_game_next, pBuff, size );

	OS_Printf( "�e�[���q �Q�[���I�� %d \n", p_game->game_comm_pack.get_game_next );

	
	// �Q�[���������S�@�I����
	NMIX_SetMainSeq( p_game, NMIX_GAME_MIANSEQ_RES_RELEASE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�q����Q�[�����Â��������󂯎��
 *
 *	@param	netID		�ڑ�ID
 *	@param	size		�T�C�Y
 *	@param	pBuff		�o�b�t�@
 *	@param	pWork		���[�N
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameNextData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;
	int i;
	int in_count;
	u8 send;

	// �e�̂Ƃ��󂯎��	
	// �e�́A�S�Ď󂯎������A�q�ɖ؂̎�����]��
	if( NMIX_CommPack_CommGetCurrentID( p_game->comm_work ) == COMM_PARENT_ID ){
		// �o�b�t�@�Ɋi�[
		memcpy( &p_game->game_comm_pack.game_next[ netID ], pBuff, size );
		p_game->game_comm_pack.get_next_data_flg[ netID ] = TRUE;

		OS_Printf( "�q�[���e �Q�[���I���f�[�^ netID[ %d ] next_data[ %d ]\n", netID, p_game->game_comm_pack.game_next[ netID ] );

		// �ʐM����S�����痈�����`�F�b�N
		in_count = 0;
		send = 1;	// �ŏ��ɑ����������Ă����@�F��1�Ȃ�1 ��l�ł�0�Ȃ�0�Ȃ̂�
					// ���Ń`�F�b�N���Ă���
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
			if( p_game->game_comm_pack.get_next_data_flg[ i ] == TRUE ){
				send &= p_game->game_comm_pack.game_next[ i ];
				in_count ++;
			}
		}
		// �S�����炫����A�Q�[���I���f�[�^�]��
		if( in_count >= p_game->comm_count ){
			OS_Printf( "�q�ɃQ�[���I���f�[�^�]�� in_c=%d  comm_c=%d\n", in_count, p_game->comm_count );

			// �f�[�^�]��
			NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT_KO,
					&send,
					CommNutMixerGetOneSize(),
					p_game->comm_work );
		}
	}
}


//-----------------------------------------------------------------------------
/**
 *			�T�C�Y�擾�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	0�T�C�Y
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetZeroSize( void )
{
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1�T�C�Y
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetOneSize( void )
{
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���O�ʐM�f�[�^�q���󂯎��T�C�Y�擾
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameBeforeKoSize( void )
{
	return sizeof(NUTMIX_COMM_BEFORE_KO);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���O�T�C�Y�ʐM�f�[�^�T�C�Y�擾
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameBeforeSize( void )
{
	return sizeof(NUTMIX_GAME_BGFORE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���f�[�^�T�C�Y�擾
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameSize( void )
{
	return sizeof(NUTMIX_COMM_DATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����ʃf�[�^�T�C�Y�擾
 *	@return	�T�C�Y
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameResultSize( void )
{
	return sizeof(NUTMIX_COMM_RESULT);
}


