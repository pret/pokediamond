//==============================================================================================
/**
 * @file	fld_bgm.c
 * @brief	�t�B�[���h�T�E���h����
 * @author	Satoshi Nohara
 * @date	2005.10.14
 */
//==============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "system/snd_tool.h"
#include "system/gamedata.h"		//POKE_NUM_MAX
#include "system/pm_rtc.h"			//GF_RTC_IsNightTime
#include "mapdefine.h"				//ZONE_ID_C01
#include "zonedata.h"				//ZoneData_GetBGMID
#include "player.h"					//HERO_FORM_SWIM
#include "sway_grass_enc.h"
#include "fld_bgm.h"
#include "field/situation_local.h"

#include "battle/battle_common.h"	//���C���N���[�h�ɕK�v
#include "poketool/tr_tool.h"
#include "battle/trtype_def.h"

#include "tr_bgm.dat"
#include "sysflag.h"


//==============================================================================================
//
//	�ϐ�
//
//==============================================================================================


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void Snd_GameOverSet();
void Snd_RestartSet( FIELDSYS_WORK* fsys );

//�t�B�[���hBGM�i���o�[�擾
u16 Snd_FieldBgmNoGet( FIELDSYS_WORK* fsys, int zone_id );

//�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
u16 Snd_FieldBgmNoGetNonBasicBank( FIELDSYS_WORK* fsys, int zone_id );

//"�]�[�����܂�����p"�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
BOOL Snd_FadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//"�}�b�v�J�ڐ�p"�@�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
static BOOL Snd_MapChangeFadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//ev_mapchange.c�p�̊֐�
BOOL Snd_MapChangeFadeOutNextPlaySub( FIELDSYS_WORK* fsys, int zone_id, int mode );

//���[�J���֐�
static void Snd_BgmFadeOutTimeGet( FIELDSYS_WORK* fsys, int mode, int* frame, int* next_wait );

//BGM�i���o�[�擾
u16 Snd_EyeBgmGet( int tr_id );
u16 Snd_BattleBgmGet( u32 fight_type, int tr_id );
u16 Snd_ZoneDataBgmNoGet( int zone_id );


//==============================================================================================
//
//	�֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[���ɂ��鏈��(field_encount.c����Ă΂��)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_GameOverSet()
{
	//�S�Ă̍Đ����̃V�[�P���X���~
	Snd_Stop();

	//�S�Ẵ|�[�Y�t���O�N���A
	Snd_PauseClearAll();

	//�t�B�[���h�V�[������t�B�[���h�V�[���̃��[�h������̂ŁA
	//��x�V�[�����N���A���Ă���A�t�B�[���h�f�[�^���[�h�֐i��
	Snd_SceneSet( SND_SCENE_DUMMY );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[��ɍĊJ���鎞�̏���(field_encount.c����Ă΂��)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 *
 * ���g�p�I
 */
//--------------------------------------------------------------
void Snd_RestartSet( FIELDSYS_WORK* fsys )
{
	u16 bgm_no;

	//�t�B�[���h�V�[������t�B�[���h�V�[���̃��[�h������̂ŁA
	//��x�V�[�����N���A���Ă���A�t�B�[���h�f�[�^���[�h�֐i��
	Snd_SceneSet( SND_SCENE_DUMMY );

	//�t�B�[���h�f�[�^���[�h
	bgm_no = Snd_FieldBgmNoGet( fsys, fsys->location->zone_id );
	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );

	//�t�F�[�h�C��
	Snd_BgmFadeIn(BGM_VOL_MAX, BGM_FADEIN_RESTART_TIME, BGM_FADEIN_START_VOL_MIN);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM�w��Z�b�g
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	bgm_no	BGM�i���o�[
 *
 * @retval	none
 *
 * �}�b�v�������BGM�w�肪�Z�b�g�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
void Snd_FieldBgmSetSpecial( FIELDSYS_WORK* fsys, u16 bgm_no )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	*situation_bgm		= bgm_no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM�w��Q�b�g
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	"BGM�i���o�["
 *
 * �}�b�v�������BGM�w�肪�Z�b�g�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmGetSpecial( FIELDSYS_WORK* fsys )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	return (*situation_bgm);
}

//--------------------------------------------------------------
/**
 * @brief	BGM�w��N���A
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 *
 * �}�b�v�������BGM�w�肪�N���A�����
 * ���]��BGM�̐���ȂǂɎg�p
 */
//--------------------------------------------------------------
void Snd_FieldBgmClearSpecial( FIELDSYS_WORK* fsys )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	*situation_bgm		= 0;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�i���o�[�擾
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 *
 * @retval	"�t�B�[���hBGM�i���o�["
 *
 * �}�b�v�Ǘ��\�͒��ڌ��Ȃ��ŁA���̊֐���ʂ���BGM�i���o�[�擾����
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmNoGet( FIELDSYS_WORK* fsys, int zone_id )
{
	PLAYER_STATE_PTR player;
	int status;
	u16 bgm_no,ret;

	player = fsys->player;
	status = Player_FormGet(player);

	//�g��蒆���`�F�b�N
	if( status == HERO_FORM_SWIM ){
		return SEQ_NAMINORI;
	}

	//��ꑐ�����`�F�b�N
	if( SwayGrass_CheckValid(fsys->SwayGrass) == TRUE ){
		return SEQ_KUSAGASA;
	}

	//�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
	bgm_no = Snd_FieldBgmNoGetNonBasicBank( fsys, zone_id );

	/*
	INIT_CHANGE�ŁABmgSpecialSet���Ăяo���āA
	�C�x���g�Ȑ؂�ւ��𔽉f�����悤�Ǝv�������A
	���̃]�[���̋ȃt�F�[�h�C�����A
	���̃]�[����INIT_CHANGE����ɂ��邽�ߏo���Ȃ��I
	�Ȃ̂ŁA���̃]�[��ID�͎擾�ł��Ă���̂ŁA
	�����ŃC�x���g�t���O�����ăC�x���g�Ȃɐ؂�ւ���I(06.06.17)
	*/

	//����BGM�w�肪�Z�b�g����Ă�����(���]�ԂȂ�)
	if( Snd_FieldBgmGetSpecial(fsys) != 0 ){
		bgm_no = Snd_FieldBgmGetSpecial( fsys );
	}

	return bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 *
 * @retval	"�t�B�[���hBGM�i���o�["
 *
 * �}�b�v�J�ڂ̎��́ABASIC_BANK�ɂȂ���̂��܂߂����Ȃ�
 * �}�b�v�J�ڂ̎��́A����w��̓`�F�b�N����K�v���Ȃ�
 * �}�b�v�J�ڂ̎��́A���]�ԁA�Ȃ݂̂�͈����p�����Ƃ͂Ȃ�
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmNoGetNonBasicBank( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no,ret;

	//�}�b�v�Ǘ��\����BGM�i���o�[��Ԃ�
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
		bgm_no = ZoneData_GetDayBGMID( zone_id );
	}else{
		bgm_no = ZoneData_GetNightBGMID( zone_id );
	}

	//�C�x���gBGM�؂�ւ�
	ret = SysFlag_EventBgmGet( SaveData_GetEventWork(fsys->savedata), zone_id );
	if( ret != 0 ){
		bgm_no = ret;
	}

	return bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	"�]�[�����܂�����p"�@�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	seq_no	�V�[�P���X�i���o�[
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �t�B�[���h�ȊO�́A���̊֐����g�p���ĉ������I
 * ��Snd_BgmFadeOutNextPlaySet(...);
 *
 * �]�[�����܂�����p�ł��B���H�A���̃]�[�����܂������Ɏg�p���܂��B
 * �}�b�v�J�ڂɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode )
{
	PLAYER_STATE_PTR player;
	int frame,next_wait,status;

	player = fsys->player;
	status = Player_FormGet(player);

	//�t�B�[���hBGM���Œ�ɂ���t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return 0;		//�������Ȃ�
	}

	//�ύX����BGM�i���o�[���A����BGM�i���o�[�Ɠ������`�F�b�N
	if( seq_no == Snd_NowBgmNoGet(fsys) ){
		return 0;		//�������Ȃ�
	}

	//�C�x���g�ŁA�A�����BGM��PLAYER_BGM�Ŗ炵�Ȃ���A�}�b�v�J�ڂ���ƁA
	//PLAYER_FIELD���|�[�Y��Ԃ̂܂܂ɂȂ��Ă���I
	//�]�[���؂�ւ����̓|�[�Y��S�ăN���A���Ă����Ȃ��͂��I
	
	//�S�Ẵ|�[�Y�t���O�N���A
	Snd_PauseClearAll();

	//�����̏o���肩�A�]�[�����܂��������ɂ���āA�t�F�[�h�A�E�g���Ԃ�ς���I
	Snd_BgmFadeOutTimeGet( fsys, mode, &frame, &next_wait );

	if( (status == HERO_FORM_CYCLE_R) || (status == HERO_FORM_CYCLE_D) ){
		//���]�Ԃɏ���Ă��鎞�̓t�F�[�h�A�E�g���t�F�[�h�C��(�o���N���̂܂܌p��)
		Snd_FadeOutNextFadeInSet(SND_SCENE_FIELD, seq_no, frame, next_wait, 
									BGM_FADEIN_CYCLE_TIME, SND_BANK_CONTINUE, NULL);
	}else{
		//�ʏ�̓t�F�[�h�A�E�g���J�n(�o���N���̂܂܌p��)
		Snd_FadeOutNextPlaySet(SND_SCENE_FIELD, seq_no, frame, next_wait, SND_BANK_CONTINUE, NULL);
	}

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	"�}�b�v�J�ڐ�p"�@�t�F�[�h�A�E�g �� BGM�Đ�(�t�B�[���h��p)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	seq_no	�V�[�P���X�i���o�[
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �}�b�v�J�ڐ�p�ł��B�����A�_���W�����ɓ��鎞�Ɏg�p���܂��B
 * ���H�A���̃]�[�����܂������ɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
static BOOL Snd_MapChangeFadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode )
{
	int frame,next_wait;

	/*

	//�}�b�v�`�F���W�̃R�}���h���ŁA
	//
	//�P�ABGM���ύX����邩�`�F�b�N
	//�Q�A�ύX����鎞�́A
	//�R�A�t�F�[�h�A�E�g
	//�S�A�t�F�[�h�A�E�g�҂�
	//�����܂ł�
	//�P�A����BGM�����[�h���čĐ�
	//�ɕ�����ƃ^�C�~���O�����₷�������B
	//�����A���̓^�C�~���O�����Ă���B

	//���ƁAFLAG_CHANGE�ŃT�E���h���[�N�̃��N�G�X�gBGM��BGM�i���o�[�����āA
	//����ɒl�������Ă�����A����BGM��点��悤�ɂ��Ă����Ƃ悢�����B
	//Snd_FieldBgmNoGet�ŁA�C�x���g�̃`�F�b�N���������A�X�N���v�g�őS�Ă�����悤�ɂȂ�̂ŁB
	
	*/

	//�t�B�[���hBGM���Œ�ɂ���t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return 0;		//�������Ȃ�
	}

	//�ύX����BGM�i���o�[���A����BGM�i���o�[�Ɠ������`�F�b�N
	if( seq_no == Snd_NowBgmNoGet(fsys) ){
		return 0;		//�������Ȃ�
	}

	//�C�x���g�ŁA�A�����BGM��PLAYER_BGM�Ŗ炵�Ȃ���A�}�b�v�J�ڂ���ƁA
	//PLAYER_FIELD���|�[�Y��Ԃ̂܂܂ɂȂ��Ă���I
	//�]�[���؂�ւ����̓|�[�Y��S�ăN���A���Ă����Ȃ��͂��I
	
	//�S�Ẵ|�[�Y�t���O�N���A
	Snd_PauseClearAll();

	//�����̏o���肩�A�]�[�����܂��������ɂ���āA�t�F�[�h�A�E�g���Ԃ�ς���I
	Snd_BgmFadeOutTimeGet( fsys, mode, &frame, &next_wait );

	//�t�F�[�h�A�E�g���J�n(�o���N�؂�ւ���)
	Snd_FadeOutNextPlaySet(SND_SCENE_FIELD, seq_no, frame, next_wait, SND_BANK_CHANGE, NULL);
	
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	"�}�b�v�J�ڐ�p"�@ev_mapchange.c�p�̊֐�
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id	�]�[��ID
 * @param	mode	���[�h(fld_bgm.h�Q��)
 *
 * @retval	"0=�������Ȃ��A1=�J�n"
 *
 * �}�b�v�J�ڐ�p�ł��B�����A�_���W�����ɓ��鎞�Ɏg�p���܂��B
 * ���H�A���̃]�[�����܂������ɂ͎g�p�ł��܂���B
 */
//--------------------------------------------------------------
BOOL Snd_MapChangeFadeOutNextPlaySub( FIELDSYS_WORK* fsys, int zone_id, int mode )
{
	u16 bgm_no = Snd_FieldBgmNoGet( fsys, zone_id );
	Snd_ZoneBgmSet( Snd_ZoneDataBgmNoGet(zone_id) );				//�]�[���̋Ȃ��Z�b�g
	return Snd_MapChangeFadeOutNextPlayCall( fsys, bgm_no, mode );
}


//==============================================================================================
//
//	���[�J���֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�t�F�[�h�A�E�g���Ԏ擾
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	mode		���[�h(fld_bgm.h�Q��)
 * @param	frame		�t�F�[�h�A�E�g�t���[�������i�[����|�C���^
 * @param	next_wait	����BGM��炷�܂ł̃t���[�������i�[����|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_BgmFadeOutTimeGet( FIELDSYS_WORK* fsys, int mode, int* frame, int* next_wait )
{
	//�}�b�v�Ǘ��\�ŁA�]�[���̃^�C�v(�������A�t�B�[���h���A���A���Ȃ�)��
	//���ʂł���悤�ɂȂ�����A�����̃��[�h�͂���Ȃ������H

	//�����̏o���肩�A�]�[�����܂��������ɂ���āA�t�F�[�h�A�E�g���Ԃ�ς���I
	
	switch( mode ){

	//�����̏o����
	case BGM_FADE_ROOM_MODE:
		*frame		= BGM_FADE_ROOM_TIME;
		*next_wait	= 0;
		break;

	//�t�B�[���h�̐؂�ւ�
	case BGM_FADE_FIELD_MODE:
		*frame		= BGM_FADE_FIELD_TIME;
		*next_wait	= 0;
		break;

	//���A�̏o����
	case BGM_FADE_CAVE_MODE:
		*frame		= BGM_FADE_CAVE_TIME;
		*next_wait	= BGM_NEXT_WAIT_CAVE_TIME;
		break;

	//���̑�
	case BGM_FADE_OTHERS_MODE:
		*frame		= BGM_FADE_OTHERS_TIME;
		*next_wait	= 0;
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�g���[�i�[����BGM�擾(�X�N���v�g����Ă΂��)
 *
 * @param	tr_id	�g���[�i�[ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
u16 Snd_EyeBgmGet( int tr_id )
{
	u8 type;
	u16 bgm,i;

	type = (u8)TT_TrainerDataParaGet( tr_id, ID_TD_tr_type );

	bgm = SEQ_EYE_KID;	//�ی�

	for( i=0; i < TRTYPE_BGM_TBL_MAX ;i++ ){

		if( trtype_bgm_tbl[i][0] == type ){
			bgm = trtype_bgm_tbl[i][1];
			break;
		}
	}

	return bgm;
}

//--------------------------------------------------------------
/**
 * @brief	�퓬BGM�擾
 *
 * @param	fight_type	�퓬��ʃt���O
 * @param	tr_id		�g���[�i�[ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
u16 Snd_BattleBgmGet( u32 fight_type, int tr_id )
{
	u8 type;
	u16 bgm = SEQ_BA_POKE;

	//�쐶�n�q�T�t�@��   k.ohno �ʐM�ΐ�Ŏ~�܂�̂ŏC��

    //�g���[�i�[
	if(fight_type == FIGHT_TYPE_TRAINER){

		type = (u8)TT_TrainerDataParaGet( tr_id, ID_TD_tr_type );

		switch( type ){

		//�W��
		case TRTYPE_LEADER1:
		case TRTYPE_LEADER2:
		case TRTYPE_LEADER3:
		case TRTYPE_LEADER4:
		case TRTYPE_LEADER5:
		case TRTYPE_LEADER6:
		case TRTYPE_LEADER7:
		case TRTYPE_LEADER8:
			bgm = SEQ_BA_GYM;
			break;

		//�M���K�c
		case TRTYPE_GINGAM:
		case TRTYPE_GINGAW:
			bgm = SEQ_BA_GINGA;
			break;

		//�M���K�c�{�X
		case TRTYPE_GINGALEADER1:
		case TRTYPE_GINGALEADER2:
		case TRTYPE_GINGALEADER3:
			bgm = SEQ_BA_AKAGI;
			break;

		//�g���[�i�[
		default:
			bgm = SEQ_BA_TRAIN;
			break;
		}
	}

	return bgm;
}

//--------------------------------------------------------------
/**
 * @brief	�]�[���f�[�^��BGM�i���o�[�擾
 *
 * @param	zone_id	�]�[��ID
 *
 * @retval	"BGM�i���o�["
 */
//--------------------------------------------------------------
u16 Snd_ZoneDataBgmNoGet( int zone_id )
{
	u16 bgm_no;

	//�}�b�v�Ǘ��\����BGM�i���o�[��Ԃ�
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
		bgm_no = ZoneData_GetDayBGMID( zone_id );
	}else{
		bgm_no = ZoneData_GetNightBGMID( zone_id );
	}

	return bgm_no;
}


//==============================================================================================
//
//	�}�b�v�J�ڗp(�܂������͎g�p�s�I)
//
//	ev_mapchange.c
//	map_jump.c
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ځF�]�[���؂�ւ��鎞�Ƀt�F�[�h�A�E�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_EvMapChangeBgmFadeCheck( FIELDSYS_WORK* fsys, int zone_id )
{
	//�t�B�[���hBGM���Œ�ɂ���t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return;
	}

	//�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
	if( Snd_NowBgmNoGet() != Snd_FieldBgmNoGetNonBasicBank(fsys,zone_id) ){
		Snd_BgmFadeOut( 0, BGM_FADE_MAPJUMP_TIME );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ځF�]�[���؂�ւ��鎞��BGM�Đ�
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_EvMapChangeBgmPlay( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no;

	//�t�B�[���hBGM���Œ�ɂ���t���O�`�F�b�N(�Z�[�u�͂��Ȃ�)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return;
	}

	Snd_SceneSet( SND_SCENE_DUMMY );

	//�t�B�[���hBGM�i���o�[�擾(BASIC_BANK������)
	bgm_no = Snd_FieldBgmNoGetNonBasicBank( fsys, zone_id );

	Snd_ZoneBgmSet( bgm_no );		//�]�[���ȃZ�b�g

	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
	return;
}


//==============================================================================================
//
//	�t�B�[���h�������p
//
//	fieldmap.c
//	fld_menu.c(�i����̕��A�Ɏg�p)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�������F�T�E���h�f�[�^�Z�b�g
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	zone_id		�]�[��ID
 *
 * @retval	none
 *
 * �V�[�����ύX����Ȃ����͉������Ȃ��I
 */
//--------------------------------------------------------------
void Snd_FieldMapInitBgmPlay( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no;

	bgm_no = Snd_FieldBgmNoGet( fsys, zone_id );	//���]��BGM�ŕ��A���邱�Ƃ����肦��I

	Snd_ZoneBgmSet( Snd_FieldBgmNoGetNonBasicBank(fsys,zone_id) );	//�]�[���ȃZ�b�g

	//�T�E���h�f�[�^�Z�b�g(�V�[�����ύX����Ȃ����͉������Ȃ�)
	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
	return;
}


