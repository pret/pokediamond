//============================================================================================
/**
 * @file	snd_def.h
 * @bfief	�T�E���h��`�t�@�C��
 * @author	Satoshi Nohara
 * @date	06.02.13
 */
//============================================================================================
#ifndef SND_DEF_H
#define SND_DEF_H


//============================================================================================
//
//�ZSE�̃p����`
//
//============================================================================================
//#define WAZA_SE_PAN_L			(-118)//(-128)
#define WAZA_SE_PAN_L			(-117)//(-128)
#define WAZA_SE_PAN_N			(0)
#define WAZA_SE_PAN_R			(117)//(127)


//============================================================================================
//
//�����Đ��p�^�[����`
//
//============================================================================================
#define PV_NORMAL				(0)	//�ʏ�Đ�
#define PV_HALF					(1)	//�Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j
#define PV_FLDEVENT				(2)	//�{�����|�P�����i�t�B�[���h�C�x���g�j
#define PV_W_TOOBOE				(3)	//�Z���ʉ��E�Ƃ��ڂ��p
#define PV_W_HYPER1				(4)	//�Z���ʉ��E�n�C�p�[�{�C�X�p�P
#define PV_POKEDOWN				(5)	//�|�P���������ꂽ��
#define PV_W_HYPER2				(6)	//�Z���ʉ��E�n�C�p�[�{�C�X�p�Q
#define PV_W_HOERU1				(7)	//�Z���ʉ��E�ق���P
#define PV_W_HOERU2				(8)	//�Z���ʉ��E�ق���Q
#define PV_W_NAKIGOE1			(9)	//�Z���ʉ��E�Ȃ������P
#define PV_W_NAKIGOE2			(10)//�Z���ʉ��E�Ȃ������Q
#define PV_PINCHNORMAL			(11)//�ʏ�Đ�(���C�Ȃ�)
#define PV_PINCHHALF			(12)//�Đ����ԒZ�k�i�Q�����Q�o�g���Ń|�P�����o�ꎞ�j(���C�Ȃ�)
#define PV_ZUKAN_CHORUS			(13)//�}�ӃR�[���X�Đ�(�ǉ�06.03.03)
#define PV_ZUKAN_NORMAL			(14)//�}�Ӄm�[�}���Đ�(�ǉ�06.04.21)

//��������
#define PV_VOL_MAX				(127)//
#define PV_VOL_DEFAULT			(100)//

//BGM�{�����[����`
#define BGM_VOL_MAX			(127)							//BGM�̃{�����[���ő�
#define BGM_VOL_HALF		(64)							//BGM�̃{�����[������
#define BGM_VOL_MIN			(0)								//BGM�̃{�����[���ŏ�
#define BGM_VOL_ZUKAN		(BGM_VOL_MAX / 3)				//�}�Ӊ��BGM�̃{�����[��
#define BGM_VOL_TR_CASE		(BGM_VOL_MAX / 3)				//�g���[�i�[�P�[�XBGM�̃{�����[��
#define BGM_VOL_CLIP		(BGM_VOL_MAX / 3)				//�C���[�W�N���b�v���BGM�̃{�����[��
#define BGM_VOL_PERAP		(BGM_VOL_MAX / 3)				//�y���b�v�Ɋo�������Ă��鎞�̃{�����[��

//�{�C�X�`���b�g�I����ɉ��ʂ��Z�b�g(sound_data_bgm.sarc�ŕύX������������Ή�)
#define BGM_WIFILOBBY_VOL		(90)
#define BGM_WIFILOBBY_START_VOL	(90/5)


//============================================================================================
//
//�T�E���h��`�u�������p�̒�`
//
//============================================================================================
#define SE_MSG_SKIP				(SEQ_SE_DP_SELECT)			//���b�Z�[�W�L�[����SE�i���o�[
//#define SE_MSG_SKIP			(SEQ_SE_DP_SELECT2)			//���b�Z�[�W�L�[����SE�i���o�[
	
#define SE_DECIDE				(SEQ_SE_DP_SELECT)			//����SE�i���o�[
//#define SE_DECIDE				(SEQ_SE_DP_DECIDE)			//����SE�i���o�[
//#define SE_DECIDE				(SEQ_SE_DP_PIRORIRO)		//����SE�i���o�[(�V���v���ȕ����悳����)

//#define SE_CANCEL 			(SEQ_SE_DP_DECIDE)			//�L�����Z��SE�i���o�[
#define SE_CANCEL				(SEQ_SE_DP_SELECT)			//�L�����Z��SE�i���o�[

//#define SE_WIN_OPEN			(SEQ_SE_DP_WIN_OPEN3)		//���j���[���J��
#define SE_WIN_OPEN				(SEQ_SE_DP_WIN_OPEN)		//���j���[���J��

//fieldobj_acmd.c
#define SE_JUMP					(SEQ_SE_DP_DANSA)			//���W�����vSE�i���o�[

#define SE_LANDING				(SEQ_SE_DP_SUTYA)			//�����n
	
#define SE_POISON				(SEQ_SE_DP_DOKU2)			//����

#define SE_FLD_MENU_SELECT		(SEQ_SE_DP_SELECT78)		//���t�B�[���h���j���[�I��SE�i���o�[

#define SE_DOOR_OPEN			(SEQ_SE_DP_DOOR_OPEN)		//���h�A���J����

#define SE_DOOR_CLOSE			(SEQ_SE_DP_DOOR_CLOSE2)		//���h�A��߂�

//#define SE_JIDO_DOOR_OPEN		(SEQ_SE_DP_DOOR_OPEN)		//�����h�A���J����
#define SE_JIDO_DOOR_OPEN		(SEQ_SE_DP_DOOR10)			//�����h�A���J����

//#define SE_JIDO_DOOR_CLOSE	(SEQ_SE_DP_DOOR_CLOSE2)		//�����h�A��߂�
//#define SE_JIDO_DOOR_CLOSE	(SEQ_SE_DP_DOOR10)			//�����h�A��߂�
#define SE_JIDO_DOOR_CLOSE		(0)							//�����h�A��߂�

//#define SE_KANNON_DOOR_OPEN	(SEQ_SE_DP_DOOR_OPEN)		//�h�A���J����
//#define SE_KANNON_DOOR_CLOSE	(SEQ_SE_DP_DOOR_CLOSE2)		//�h�A��߂�

#define SE_C10_LIFT				(SEQ_SE_DP_ELEBETA4)		//���`�����s�I�������̃��t�g

//���g�p�H
#define SE_UG_TRAP_ON			(SEQ_SE_DP_DOKU)			//�n���Ńg���b�v�ɂЂ�������

#define SE_MARK_GYOE			(SEQ_SE_DP_DECIDE)			//���u�I�v�}�[�N��

#define SE_TOUCH_SUB_WIN		(SEQ_SE_DP_BUTTON9)			//������ʂ̋��ʁu�͂��A�������v

//src\field\effect_uground.c
#define SE_UG_CHG_DOWN			(SEQ_SE_DP_PYUU)			//���n���ւ����
#define SE_UG_CHG_UP			(SEQ_SE_DP_PYUU2)			//���n��ւ̂ڂ�
#define SE_UG_CHG_TURN			(SEQ_SE_DP_GYURU)			//���n��Ŏ�l�������邮����

#define SE_UNION_TALK			(SEQ_SE_DP_BUTTON9)			//�����j�I���b�������ꂽ��
//#define SE_UNION_FALL			(SEQ_SE_DP_DECIDE)			//�����j�I�������Ă��鉹
#define SE_UNION_FALL			(SEQ_SE_DP_TELE2)			//�����j�I�������Ă��鉹

#define SE_BTL_SEARCHER			(SEQ_SE_DP_UG_005)			//���o�g���T�[�`���[�g�p��


//============================================================================================
//
//	060619 �����Č��ʉ�
//
//============================================================================================

//============================================================================================
//
//	����J����S��
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	���@
//--------------------------------------------------------------------------------------------
//�����n�����Ƃ��̉�
#define SE_SUTYA2							(SEQ_SE_DP_SUTYA2)

//��������Ƃ�
#define SE_SORAWOTOBU						(SEQ_SE_DP_FW019)

//�������肫
#define SE_KAIRIKI							(SEQ_SE_DP_UG_023)

//�����Ȃ��ق�
#define SE_ANAWOHORU						(SEQ_SE_DP_KAIDAN2)

//�����Ȃʂ��̃q��
#define SE_ANANUKENOHIMO					(SEQ_SE_DP_KAIDAN2)

//���e���|�[�g
#define SE_TELEPORT							(SEQ_SE_DP_TELE)

//�����b�N�N���C��(�ړ����Ă��鎞)
#define SE_ROCKCLIMB						(SEQ_SE_DP_UG_023)

//����(�����𓊂�����)
#define SE_FISHING							(SEQ_SE_DP_FW104)

//�����]�ԏ�鎞
#define SE_BICYCLE							(SEQ_SE_DP_JITENSYA)

//�����]�Ԃɏ���Ă��鎞�ɃM�A��؂�ւ���
#define SE_BICYCLE_GEAR						(SEQ_SE_DP_GEAR)			//up
#define SE_BICYCLE_GEAR2					(SEQ_SE_DP_GEAR2)			//down

//���󂢏��������
#define SE_SHALLOW_MARSH_WALK				(SEQ_SE_DP_MARSH_WALK)

//���[�����ɂ͂܂�����
#define SE_DEEP_MARSH_FALL_DOWN				(SEQ_SE_DP_ZUPO)

//���[�������甲���o������
#define SE_DEEP_MARSH_FALL_OUT				(SEQ_SE_DP_ZUPO2)

//���������������
#define SE_LONG_GRASS_WALK					(SEQ_SE_DP_KUSA)

//������������鎞
#define SE_DRIFT_SAND						(SEQ_SE_DP_SUNA)

//���]�ԃW�����v��(�R�{��)
#define SE_BICYCLE_JUMP3					(SEQ_SE_DP_DANSA4)

//���]�ԃW�����v��(�S�{��)
#define SE_BICYCLE_JUMP4					(SEQ_SE_DP_DANSA5)

//���L�b�T�L�W���@��ʂ����鉹
#define SE_KISSAKI_GYM_BREAK				(SEQ_SE_DP_FW291)

//���n�k��
#define SE_SHAKE							(SEQ_SE_DP_FW089)

//�������̔��@�ň��ݕ����o�Ă�����
#define SE_JIHANKI							(SEQ_SE_DP_JIHANKI)


//--------------------------------------------------------------------------------------------
//
//	�M���K�c�A�W�g
//
//--------------------------------------------------------------------------------------------
//���M���K�c�A�W�g�r���@���b�N���ꂽ�h�A���J������
#define SE_AZITO_DOOR_OPEN					(SEQ_SE_DP_DOOR10)

//���M���K�c�A�W�g�r���@���[�v���Ń��[�v����Ƃ��̉�
#define SE_AZITO_WARP						(SEQ_SE_DP_TELE2)


//--------------------------------------------------------------------------------------------
//
//	�����f��
//
//--------------------------------------------------------------------------------------------
//�������f���ŁA�{�[���̔�ԑ��x�����X�ɃA�b�v���Ă����J�b�g�̉�
#define SE_KOUKAN_BALL_MOVE					(SEQ_SE_DP_KOUKAN10)


//--------------------------------------------------------------------------------------------
//
//	GTC
//
//--------------------------------------------------------------------------------------------
//���u��l���������ɓ����Ă���Ƃ��̉��v
#define SE_GTC_PLAYER_IN					(SEQ_SE_DP_PYUU)

//���[���̓d�������鉹
#define SE_GTC_ON							(SEQ_SE_DP_PC_LOGIN)

//���|�P�������������Č��������Ƃ��̉�(�g���[�i�[�������Ƃ��̉�)
#define SE_GTC_APPEAR						(SEQ_SE_DP_TELE2)

//���[���̓d���𗎂Ƃ���
#define SE_GTC_OFF							(SEQ_SE_DP_PC_LOGOFF)

//����l������������o��Ƃ��̉�
#define SE_GTC_PLAYER_OUT					(SEQ_SE_DP_PYUU2)

//���������̉�
#define SE_GTC_SEARCH						(SEQ_SE_DP_Z_SEARCH)

//�������������ǌ�����Ȃ�����
#define SE_GTC_NG							(SEQ_SE_DP_BOX03)


//============================================================================================
//
//	����J����S��
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	�X���b�g�@�{��
//--------------------------------------------------------------------------------------------
//BET��
#define SE_SLOT_BET							(SEQ_SE_DP_ZUKAN02)

//���[����]�J�n��
#define SE_SLOT_REEL_START					(SEQ_SE_DP_OPEN2)

//��~��
#define SE_SLOT_REEL_STOP					(SEQ_SE_DP_UG_022)

//��~���i�s�b�s�P&2�j
//#define SE_SLOT_REEL_STOP2				(SEQ_SE_DP_SELECT)
#define SE_SLOT_REEL_STOP2					(SEQ_SE_DP_SELECT_SLOT)

//--------------------------------------------------------------------------------------------
//	�X���b�g�@���o
//--------------------------------------------------------------------------------------------
//���{�[���]���艹�iIN�j
#define SE_SLOT_BALL_FALL_DOWN				(SEQ_SE_DP_UG_020)

//���{�[���I�[�v����
#define SE_SLOT_BALL_OPEN					(SEQ_SE_DP_SLOT01)

//���s�b�s�{�[��IN
#define SE_SLOT_PIPPI_BALL_IN				(SEQ_SE_DP_SLOT02)

//������
#define SE_SLOT_MOON_LIGHT					(SEQ_SE_DP_025)


//--------------------------------------------------------------------------------------------
//
//	���@�g���b�v
//
//--------------------------------------------------------------------------------------------
//�����ɂ͂܂��ĕ�����ς��鎞
#define SE_TRAP_HOLE_DIR					(SEQ_SE_DP_BOX02)

//�������甲������
#define SE_TRAP_HOLE_FALL_OUT				(SEQ_SE_DP_DANSA)

//���₪�����Ă��鎞(�e���o��)
#define SE_TRAP_ROCK_SHADOW					(SEQ_SE_DP_FW466)

//���₪�n�ʂɗ�������
#define SE_TRAP_ROCK_FALL					(SEQ_SE_DP_FW452)

//��������΂���Ă��鎞
#define SE_TRAP_MOVE						(SEQ_SE_DP_F007)

//�����킪�����Ă��鎞
#define SE_TRAP_BUBBLE						(SEQ_SE_DP_FAWA)

//��������ʂɂ͂������
#define SE_TRAP_KEMURI						(SEQ_SE_DP_FPASA2)


//============================================================================================
//
//	�ē�����S��
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	�D�f��
//--------------------------------------------------------------------------------------------
//�������b�R���@�����@�����@���@�ʏ�
#define SE_TRAIN_START						(SEQ_SE_DP_TRAIN02)

//�������b�R���@�����@����
#define SE_TRAIN_END						(SEQ_SE_DP_TRAIN03)

//�������b�R���@�����@�`���`��
#define SE_TRAIN_BELL						(SEQ_SE_DP_TRAIN04)

//���D�@�ʏ�
#define SE_SHIP_RUN							(SEQ_SE_DP_SHIP01)

//���D�@�D�J
#define SE_SHIP_KITEKI						(SEQ_SE_DP_SHIP02)

//���V�����J����
#define SE_PIER_OPEN						(SEQ_SE_DP_SHIP03)

//--------------------------------------------------------------------------------------------
//	�G���x�[�^�[
//--------------------------------------------------------------------------------------------
//���G���x�[�^�[�@�㏸��(���~��������)
#define SE_ELEBETA_UP						(SEQ_SE_DP_ELEBETA2)
#define SE_ELEBETA_DOWN						(SEQ_SE_DP_ELEBETA2)

//���G���x�[�^�[�@������
#define SE_ELEBETA_ARRIVAL					(SEQ_SE_DP_PINPON)

//--------------------------------------------------------------------------------------------
//	�W��
//--------------------------------------------------------------------------------------------
//���i�M�T�W���@�{�^���𓥂񂾎��{���Ԃ���鉹
#define SE_NAGISA_GYM_BUTTON				(SEQ_SE_DP_GAGAGA)

//���m���Z�W���@�{�^���𓥂񂾎��{�������������鉹
//#define SE_NOMOSE_GYM_BUTTON				(SEQ_SE_DP_DENSI05)
#define SE_NOMOSE_GYM_BUTTON				(SEQ_SE_DP_FW056)

//������ړ����鉹
#define SE_TOBARI_GYM_MOVE					(SEQ_SE_DP_TV_NOISE)

//�����X�K�W���@���t�g������������
#define SE_YOSUGA_GYM_LIFT					(SEQ_SE_DP_KI_GASYAN)


//============================================================================================
//
//	��������S��
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	�t�B�[���h�Z
//--------------------------------------------------------------------------------------------
//�����܂�������(�V�C���J�A��J�A���̎��͖�Ȃ��̂ő��v)
#define SE_AMAIKAORI						(SEQ_SE_DP_FW230)

//������΂炢
#define SE_KIRIBARAI						(SEQ_SE_DP_FBRADE)


//============================================================================================
//
//	��삳��S��
//
//============================================================================================
//�������ړ��̎��ɃN���N������Ă���(���s�[�g���Ȃ̂Œ�~�������K�v�I)(�g���[�i�[�Ƃ̎����z�u�͂Ȃ�)
#define SE_YAZIRUSI_FLOOR					(SEQ_SE_DP_F209)


//============================================================================================
//
//	�S������(�ē����񂩍�������)
//
//============================================================================================
//�����킭����
#define SE_IWAKUDAKI						(SEQ_SE_DP_FW088)

//������������
#define SE_IAIGIRI							(SEQ_SE_DP_FW015)

//�������̂ڂ�
#define SE_TAKINOBORI						(SEQ_SE_DP_FW463)


//============================================================================================
//
//	�㓡����S��
//
//============================================================================================
//���^�}�S
#define SE_EGG_N01							(SEQ_SE_DP_EGG01)
#define SE_EGG_N02							(SEQ_SE_DP_BOWA3)

//���}�i�t�B�[�̃^�}�S
#define SE_EGG_S01							(SEQ_SE_DP_W278)
#define SE_EGG_S02							(SEQ_SE_DP_W080C)
#define SE_EGG_S03							(SEQ_SE_DP_W361)


#endif	/* SND_DEF_H */


