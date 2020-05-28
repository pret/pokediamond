//============================================================================================
/**
 * @file	tv_define.h
 * @date	2006.05.11
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__TV_DEFINE_H__
#define	__TV_DEFINE_H__

//----------------------------------------------------------
/**
 * @brief
 */
//----------------------------------------------------------
typedef enum {
	TV_PROGRAM_BATTLE_TRAINER = 1,
	TV_PROGRAM_TRAINER_RESEARCH,
	TV_PROGRAM_BATTLE_WATCH,
	TV_PROGRAM_TRAINERS_EVERYDAY,
	TV_PROGRAM_SINOU_NEWS_NET,
	TV_PROGRAM_RECORD_GON,
	TV_PROGRAM_SINOU_NOW,
	TV_PROGRAM_TREND,

	TV_PROGRAM_ID_MAX,
}TV_PROGRAM_ID;

//----------------------------------------------------------
/**
 * @brief	TV�g�s�b�N�F�Ď��^�^�C�v��`
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_WATCH_POKE_GET_SUCCESS = 1,	///<�|�P�����ߊl�����I	3	�|�P�����ߊl�I����
	TVTOPIC_WATCH_POKE_GET_FAILURE,		///<�|�P�����ߊl���s	3	�{�[�������P�ȏ�œ|���A������
	TVTOPIC_WATCH_FISHING,				///<���E��ނ�I	3	�|�P��������グ���Ƃ�
	TVTOPIC_WATCH_CHANGE_GROUP,			///<�O���[�v��芷���I	4	�ʂ̃O���[�v�ɏ�芷�����Ƃ�
	TVTOPIC_WATCH_SEE_RARE_POKEMON,		///<���A�|�P���������I	3	���A�|�P�����Ƃ̃G���J�E���g��
	TVTOPIC_WATCH_GET_HIDE_ITEM,		///<�B��������I	4	�B��������������Ƃ�
	TVTOPIC_WATCH_SHOPPING,				///<�������`�F�b�N	4	��x��10�ȏ�̓���𔃂����Ƃ�
	TVTOPIC_WATCH_BORN_EGG,				///<�^�}�S���z�����I	4	�^�}�S���z�������Ƃ�
	TVTOPIC_WATCH_CHECK_SODATEYA,		///<��ĉ��`�F�b�N		��ĉ��ɗa�����Ƃ�
	TVTOPIC_WATCH_CHANGE_NICKNAME,		///<�������f	4	�j�b�N�l�[����ύX�����Ƃ�
	TVTOPIC_WATCH_POISON_DEAD,			///<�łłЂ񎀁c�c		�t�B�[���h�Ń|�P�������m���ɂȂ����Ƃ�
	TVTOPIC_WATCH_WIN_LOT,				///<�|�P�����������I�I		�|�P���������ɓ��������Ƃ�
	TVTOPIC_WATCH_DIG_FOSSIL,			///<���Ό@��	���Ό@�����������
	TVTOPIC_WATCH_DENDOU,				///<�a������I	�͂��߂ēa�����肵���Ƃ�
	TVTOPIC_WATCH_SAFARI,				///<�T�t�@���Q�[��	�T�t�@���Q�[�����I���������Ƃ�
	TVTOPIC_WATCH_OSU_MESU,				///<�I�X�����I���X�����I	�p�\�R�����甲�����Ƃ��̎莝���ɂ��
	TVTOPIC_WATCH_KANPOU,				///<�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
	TVTOPIC_WATCH_NUTS_HARVEST,			///<�L��I		�؂̎�������������n�����Ƃ��i���n���A�؂�HP���W�A�X�������Ƃ��j
	TVTOPIC_WATCH_NUTS_POOR,			///<�s��E�E�E	�؂̎����P�������n�ł��Ȃ������Ƃ�
	TVTOPIC_WATCH_MAKE_NEW_GROUP,		///<�V�O���[�v�a���I	�V�����O���[�v��������Ƃ�
	TVTOPIC_WATCH_SET_CUSTOMBALL,		///<�J�X�^���{�[���쐬�I	�J�X�^���J�v�Z�����|�P�����ɃZ�b�g�����Ƃ�
	TVTOPIC_WATCH_GET_FLAG,				///<����������I		�l�̊��������A�����I
	TVTOPIC_WATCH_LOSE_FLAG,			///<�������ꂽ�I		�����̊��������A��ꂽ�I
	TVTOPIC_WATCH_RIBBON,				///<���{��		

	TVTOPIC_WATCH_MAX,
}TVTOPIC_WATCH_TYPE;


//----------------------------------------------------------
/**
 * @brief	TV�g�s�b�N�F�M�l�X�^�^�C�v��`
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_RECORD_BTOWER = 1,		///<�o�g���^���[�A���L�^�X�V	�o�g���^���[�A���L�^���X�V�����Ƃ�
	TVTOPIC_RECORD_BFACTORY,		///<�t�@�N�g���[�A���L�^�X�V	�t�@�N�g���[�A���L�^���X�V�����Ƃ�
	TVTOPIC_RECORD_OOKISA,			///<�傫������L�^�X�V	�傫������ŋL�^���X�V�����Ƃ�
	TVTOPIC_RECORD_SLOT,			///<�X���b�g�B�l	�X���b�g�ň�薇���ȏ���҂����Ƃ�
	TVTOPIC_RECORD_RIBBON,			///<���{���R���N�^�[	���{������薇���ȏ�l�����ɍ쐬
	TVTOPIC_RECORD_NUTS_MASTER,		///<�؂̎���Ă̖��l	���n���A�؂�HP��10�������Ƃ�
	TVTOPIC_RECORD_POKE_SEARCHER,	///<�h�ꑐ���l		�h�ꑐ�G���J�E���g���I�������Ƃ��A������10�ȏ�
	TVTOPIC_RECORD_TRAP_REMOVER,	///<���i�������l	�n���ɓ������Ƃ��A��������̃��i������������쐬
	TVTOPIC_RECORD_FLAG_GET,		///<�n�^�g�����l		

	TVTOPIC_RECORD_MAX,
}TVTOPIC_RECORD_TYPE;

//----------------------------------------------------------
/**
 * @brief	TV�g�s�b�N�F����^�^�C�v��`
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_INTERVIEW_GYM_BADGE = 1,///<�W�����e�I	1	�W���̂���V�e�B	�W�����[�_�[��|��������
	TVTOPIC_INTERVIEW_BTOWER,		///<����I�o�g���^���[	1	�o�g���^���[	����I����
	TVTOPIC_INTERVIEW_BFACTORY,		///<����I�t�@�N�g���[	1	�o�g���t�@�N�g���[	����I����
	TVTOPIC_INTERVIEW_POKEMON,		///<���Ȃ��̃|�P����	1	�|�P������D���N���u	
	TVTOPIC_INTERVIEW_ITEM,			///<�������߂̂ǂ����I	2	�t�����h���B�V���b�v	
	TVTOPIC_INTERVIEW_POKETCH,		///<���C�ɓ���̃|�P�b�`	2	�J���p�j�[	
	TVTOPIC_INTERVIEW_CONTEST,		///<����I�R���e�X�g		�R���e�X�g���	�R���e�X�g�I����
	TVTOPIC_INTERVIEW_TATOE,		///<�|�P�����ɗႦ����H	2	��D���N���u	
	TVTOPIC_INTERVIEW_CLIP,			///<�|�P�����N���b�v�I	2	�N���b�v�����ꏊ	�N���b�v�����������
	TVTOPIC_INTERVIEW_CHARACTOR,	///<���i�f�f�I	2		
	TVTOPIC_INTERVIEW_PORUTO,		///<�|���g����		�|���g�����ꏊ	�|���g���������
	TVTOPIC_INTERVIEW_KOUKAN,		///<���������|�P����	1		
	TVTOPIC_INTERVIEW_TUREARUKI,	///<�A������𖞋i�I		���R�����Q�[�g	�A�������

	TVTOPIC_INTERVIEW_TYPE_MAX,
}TVTOPIC_INTERVIEW_TYPE;


//----------------------------------------------------------
/**
 * @brief	TV�g�s�b�N�F�C�x���g�^�^�C�v��`
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_EVENT_RANDOMGROUP = 1,		///<�O���[�v�Љ�
	TVTOPIC_EVENT_WEATHER,				///<�V�C�\��
	TVTOPIC_EVENT_TOWNGUIDE,			///<�V���I�E���̊X���̊X
	TVTOPIC_EVENT_BARGAIN,				///<�V���b�v��������
	TVTOPIC_EVENT_POKEMON_OUTBREAK,		///<��ʔ����I
	TVTOPIC_EVENT_POKEMON_ENCOUNT,		///<�|�P�����o�v���I
	TVTOPIC_EVENT_POKEMON_AISHOU,		///<�|�P���������`�����l��
	TVTOPIC_EVENT_POSTMAN,				///<�z�B�������
	TVTOPIC_EVENT_NUTS_INFOMATION,		///<���݂̂��傤�ق�
	TVTOPIC_EVENT_WAZAMACHINE,			///<�킴�}�V�����傤�ق�
	TVTOPIC_EVENT_POKEMON_ITEM,			///<�ǂ����������Ă�쐶�|�P����
	TVTOPIC_EVENT_POKEMON_CHARACTOR,	///<���������f�f
	TVTOPIC_EVENT_SLOT_INFO,			///<�X���b�g�̏o�ʏ��
	TVTOPIC_EVENT_TV_SHOPPING,			///<�s�u�V���b�s���O
	TVTOPIC_EVENT_TV_MOVE_POKEMON,		///<�ړ��|�P�����ڌ����I
	TVTOPIC_EVENT_TV_TAMAGO_INFO,		///<�^�}�S������
	TVTOPIC_EVENT_TV_CLIP_INFO,			///<�|�P�����t�@�b�V�����`�F�b�N

	TVTOPIC_EVENT_TYPE_MAX,
}TVTOPIC_EVENT_TYPE;

//----------------------------------------------------------
/**
 * @brief	CM�^�C�v��`
 */
//----------------------------------------------------------
typedef enum {
	CM_TYPE_POKECEN = 1,		///<�|�P�����Z���^�[	�ŏ�����
	CM_TYPE_FRIENDLYSHOP,		///<�t�����h���B�V���b�v	�ŏ�����
	CM_TYPE_TV_STATION,			///<�s�u��	�ŏ�����
	CM_TYPE_TRAINERSCHOOL,		///<�g���[�i�[�X�N�[��	�ŏ�����
	CM_TYPE_POKETCH,			///<�|�P�b�`	�ŏ�����
	CM_TYPE_POKETCH_SOFT,		///<�|�P�b�`�\�t�g	
	CM_TYPE_FLOWER_SHOP,		///<�ԉ�	�\�m�I����
	CM_TYPE_BICYCLE_SHOP,		///<���]�ԉ�	�n�N�^�C����
	CM_TYPE_CONTEST,			///<���e��	
	CM_TYPE_NATURE_PARK,		///<�R���e�X�g�b�l	�n�N�^�C����
	CM_TYPE_DEPART,				///<���R����	���X�K����
	CM_TYPE_BEAUTY_SALON,		///<�g�o���f�p�[�g	���X�K����
	CM_TYPE_SODATEYA,			///<��ĉ�	���X�K����
	CM_TYPE_HOTEL,				///<�z�e��	���X�K����
	CM_TYPE_SAFARI,				///<�厼��	���X�K����
	CM_TYPE_C09,				///<�L�b�T�L�V�e�B	�W���o�b�W�T��
	CM_TYPE_C08,				///<�i�M�T�s��	�W���o�b�W�T��
	CM_TYPE_GTC,				///<�f�s�b	�f�s�b�I�[�v��
	CM_TYPE_POKEPARK,			///<�|�P�����p�[�N	�V���I�E�}�ӃR���v
	CM_TYPE_SHIP_C09,			///<�L�b�T�L�V�e�B�̑D	�V���I�E�}�ӃR���v
	CM_TYPE_BATTLEZONE,			///<�o�g���]�[��	�V���I�E�}�ӃR���v
	CM_TYPE_CLUB,				///<������̌���	�V���I�E�}�ӃR���v
	CM_TYPE_GINGA1,				///<�M���K�c�P	
	CM_TYPE_GINGA2,				///<�M���K�c�Q	
	CM_TYPE_PC_COMM,			///<�|�P�����Z���^�[�ʐM��	�}�ӎ擾��
	CM_TYPE_PC_WIFI,			///<�|�P�����Z���^�[Wi-Fi��	�}�ӎ擾��
	CM_TYPE_BTOWER,				///<�o�g���^���[	�o�g���^���[�I�[�v����
	CM_TYPE_WIFI_BTOWER,		///< Wi-Fi�o�g���^���[	Wi-Fi�o�g���^���[�I�[�v����
	CM_TYPE_SHIP,				///<��蕨�b�l�i�D�j	�D�ɏ���悤�ɂȂ��Ă���

	CM_TYPE_MAX,
}CM_TYPE;

#endif	/*	__TV_DEFINE_H__ */

