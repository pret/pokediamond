//==============================================================================
/**
 * @file	actin_tool.c
 * @brief	���Z�͕���Ŏg�p����c�[����
 * @author	matsuda
 * @date	2005.11.24(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "con_tool.h"
#include "actin_id.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_cmsg_acting.h"

#include "system/snd_tool.h"
#include "application/app_tool.h"
#include "savedata/config.h"

#include "battle/wazano_def.h"
#include "battle/battle_server.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�u���[�_�[�p�l���̃h�b�g��X
#define BREEDER_PANEL_DOT_LEN_X		(10 * 8)
///�u���[�_�[�p�l���̃h�b�g��Y
#define BREEDER_PANEL_DOT_LEN_Y		(BREEDER_PANEL_Y_LEN * 8)

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
///�p�l����BMP�G���A�𖄂ߐs�����ꍇ�Ɏg�p����J���[�ԍ�
#define BMPWIN_PANEL_FILL_COLOR			(2)

///��b�E�B���h�E�J�o�[�̃X�N���[���ʒu(�X�N���[���O)
#define WINSLIDE_SCRN_POS_BEFORE		(32 * 0x12 + 0x15)
///��b�E�B���h�E�J�o�[�̃X�N���[���ʒu(�X�N���[����)
#define WINSLIDE_SCRN_POS_AFTER			(32 * 0x12 + 0x1e)
///��b�E�B���h�E�X���C�h���x(����8�r�b�g����)
#define TALKWIN_SLIDE_SPEED		(0x0400)
///��b�E�B���h�E�̃X���C�h����(�h�b�g�P��)
#define TALKWIN_SLIDE_DOT_LEN	(9 * 8 + FRAME_WIN_DEFAULT_X)

///�u���[�_�[�p�l���̃��X�s�[�h(����8�r�b�g����)
#define BRDPANEL_ALPHA_SP		(0x0800)	//(0x0500)

///�ϋq�A�j���̃E�F�C�g
#define AUDIENCE_ANIME_WAIT		(2)
///�ϋq�A�j���̌J��Ԃ���
#define AUDIENCE_ANIME_LOOP		2	//(8)
///�ϋq�t�F�[�h��EVY�ő�l
#define AUDIENCE_FADE_MAX_EVY		(EVY_MAX)
///�ϋq�t�F�[�h��EVY���Z�l
#define AUDIENCE_FADE_ADD_EVY		(2)
///�ϋq�t�F�[�h��EVY�̃J���[�J�n�ʒu
#define AUDIENCE_FADE_COLOR_POS		(0 * 16 + 1)
///�ϋq�t�F�[�h�̃J���[�J�n�ʒu����̕ύX�J���[��
#define AUDIENCE_FADE_COLOR_NUM		(2)
///�ϋq�t�F�[�h�̕ύX��̃J���[
#define AUDIENCE_FADE_RGB			(0x237e)

///�A�s�[���A�C�R���G�t�F�N�g�F�g�k���̏����l
#define APICON_EFF_INIT_SCALE		(0.1f)
///�A�s�[���A�C�R���G�t�F�N�g�F�g�k���̍ő�l
#define APICON_EFF_MAX_SCALE		(1.5f)
///�A�s�[���A�C�R���G�t�F�N�g�F�ʏ�̊g�k��
#define APICON_EFF_NORMAL_SCALE		(1.0f)
///�A�s�[���A�C�R���G�t�F�N�g�F���Z�g�k��
#define APICON_EFF_ADD_SCALE		(0.3f)
///�A�s�[���A�C�R���G�t�F�N�g�F��]���x
#define APICON_EFF_ADD_ROTATION		(0)//(0x2000)

///�R������A�w���F�ړ���(����8�r�b�g����)
#define JUDGE_NOMINATION_ADD_Y		(0x0180)
///�R������A�w���F�ړ��J��Ԃ���
#define JUDGE_NOMINATION_LOOP		(2)

///�R������A���F�ړ���X(����8�r�b�g����)
#define JUDGE_WEAR_ADD_X			(0x0200)
///�R������A���F�ړ��J��Ԃ���
#define JUDGE_WEAR_LOOP				(4)

///�R������A�W�����v�F�w���̃W�����v��
#define JUDGE_JUMP_NOMINATION_POWER			(0x0200)
///�R������A�W�����v�F�{���e�[�W���̃W�����v��
#define JUDGE_JUMP_VOLTAGE_UP_POWER			(0x0300)
///�R������A�W�����v�F�{���e�[�WMAX���̃W�����v��
#define JUDGE_JUMP_VOLTAGE_MAX_UP_POWER		(0x0400)
///�R������A�W�����v�F�R�����A�ł���
#define JUDGE_JUMP_SUFFER_BIG				(0x0480)
///�R������A�W�����v�F�R�����A�����炢
#define JUDGE_JUMP_SUFFER_MIDDLE			(0x0280)
///�R������A�W�����v�F�R�����A������
#define JUDGE_JUMP_SUFFER_SMALL				(0x0100)
///�R������A�W�����v�F�d��
#define JUDGE_JUMP_GRAVITY			(0x0100 / 2)

///�{���e�[�W�ړ��F�ŏ��̈ړ��ɂ�����t���[����
#define VOLTAGE_MOVE_FIRST_FRAME		(10)//(15)
///�{���e�[�W�ړ��F�Ō�̈ړ��ɂ�����t���[����
#define VOLTAGE_MOVE_END_FRAME			(6)	//(10)
///�{���e�[�W�ړ��F�ŏ��̈ړ����I�������ɔ�������E�F�C�g
#define VOLTAGE_MOVE_FIRST_WAIT			(3)//(4)
///�{���e�[�W�ړ��F�Ō�̈ړ����I�������ɔ�������E�F�C�g
#define VOLTAGE_MOVE_END_WAIT			(2)//(4)
///�{���e�[�W�ړ��F�A�N�^�[�A�j���̉�]�p���Z�l
#define VOLTAGE_MOVE_ADD_ROTATION		(0x2000)

///AP�n�[�g�������o���܂ł̃E�F�C�g(2�ڂ̈ȍ~�̃n�[�g�����ɃX���C�h����X�s�[�h�ɉe������)
#define APHEART_START_WAIT			(3)
///���t���[���̂ӂ蕝���Z�l
#define APHEART_SUB_FURIHABA		(0x0300)//(0x0200)
///�ӂ蕝�����̒l�ȉ��ɂȂ�����I��
#define APHEART_END_FURIHABA		(0x0200)
///��]���x
#define APHEART_ADD_ANGLE			(0x800)//(0xb00)
///���t���[���̉�]���x���Z�l
#define APHEART_ADD_FRAME_ANGLE		(0)

///�{���e�[�W�ړ��F�G�t�F�N�g�J�n�܂ł̃E�F�C�g
#define VOLMOVE_START_WAIT		(12)
///�{���e�[�W�ړ��F�ӂ蕝X
#define VOLMOVE_FURIHABA_X		(12 << FX32_SHIFT)
///�{���e�[�W�ړ��F�ӂ蕝Y
#define VOLMOVE_FURIHABA_Y		(6 << FX32_SHIFT)
///�{���e�[�W�ړ��F�p�x���Z�l
#define VOLMOVE_ADD_ANGLE		(0x800)
///�{���e�[�W�ړ��F�����ړ����xX(����8�r�b�g����)�@���̑��x�����Y���x�����肳���
#define VOLMOVE_STRAIGHT_SP_X	(0x0300)
///�{���e�[�W�ړ��F���~�ړ�����t���[����
#define VOLMOVE_DOWNMOVE_FRAME	(80)
///�{���e�[�W�ړ��F���~���̑��xY(����8�r�b�g����)
#define VOLMOVE_DOWNMOVE_SP_Y	(0x0080)

///�u���[�_�[�p�l���F�t���b�V���̊J�nEVY�l(����8�r�b�g����)
#define PANEL_FLASH_START_EVY		(10 << 8)
///�u���[�_�[�p�l���F�t���b�V����EVY���Z�l(����8�r�b�g����)
#define PANEL_FLASH_SUB_EVY		(0x280)
///�u���[�_�[�p�l���F�t���b�V���̃J���[�R�[�h
#define PANEL_FLASH_RGB			(0x7fff)
///�u���[�_�[�p�l���F�t���b�V���̊J�n�J���[�ʒu
#define PANEL_FLASH_START_POS	(1)
///�u���[�_�[�p�l���F�t���b�V���̑ΏۃJ���[��
#define PANEL_FLASH_COLOR_NUM	(4)


//==============================================================================
//	�\���̒�`
//==============================================================================
///��b�E�B���h�E�X���C�h�^�X�N�Ŏg�p���郏�[�N
typedef struct{
	ACTIN_SYSTEM_PARAM *sys;
	u8 *end_flag;	///<�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^
	
	s32 x;		///<����8�r�b�g����
	u8 seq;
	u8 slide_dir;	///<�X���C�h����
}TALKWIN_SLIDE_WORK;

///�u���[�_�[�p�l�����G�t�F�N�g�^�X�N�Ŏg�p���郏�[�N
typedef struct{
	ACTIN_PROC_WORK *apw;
	u8 *end_flag;	///<�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^
	
	s16 eva;
	s16 evb;
	u8 seq;
	u8 eff_type;
}BRDPANEL_ALPHA_WORK;

///�ϋq�A�j�����[�N
typedef struct{
	ACTIN_PROC_WORK *apw;
	int se_volume;		///<����SE�̃{�����[��
	u8 seq;				///<�V�[�P���X
	u8 anm_no;			///<���ݎ��s���̃A�j���p�^�[��
	u8 loop;			///<�A�j���J��Ԃ��񐔃J�E���g
	u8 voltage;			///<�{���e�[�W�l
	u8 wait;			///<�A�j���E�F�C�g
	u8 start_wait;		///<�J�n�܂ł̃E�F�C�g
	u8 fade;			///<�t�F�[�h�̗L��
	s8 evy;				///<�t�F�[�h��EVY�l
	u8 *end_flag;		///<�I�����A�����ɏI���t���O(TRUE)���Z�b�g����
}AUDIENCE_ANIME_WORK;

///�A�s�[���|�C���g�A�C�R���o��G�t�F�N�g�p�̃��[�N
typedef struct{
	CATS_ACT_PTR cap;
	f32 sx;
	f32 sy;
	u8 seq;
	u8 wait;
}APPEAL_POINT_APPEAR_WORK;

///AP�n�[�g��]�ړ�����p���[�N
typedef struct{
	ACTIN_PROC_WORK *apw;	///<���Z�͕���Ǘ����[�N�ւ̃|�C���^
	PANEL_FLASH_WORK *panel_flash;	///<�p�l���t���b�V�����샏�[�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�ΏۂƂȂ�n�[�g�̃A�N�^�[�|�C���^
	u8 *effect_count;		///<�G�t�F�N�g�J�E���^���[�N�ւ̃|�C���^
	u32 furihaba;			///<�ӂ蕝(����8�r�b�g����)
	u32 add_angle;			///<�p�x���Z�l
	s32 slide_x;			///<�X���C�h���̌��ݍ��WX(����8�r�b�g����)
	u16 slide_add_x;		///<���ɃX���C�h���Ă������̑��xX(����8�r�b�g����)
	u16 angle;				///<���݂̊p�x(����100�{)
	u8 seq;					///<�V�[�P���X�ԍ�
	u8 center_x;			///<Sin�J�[�u���S���WX
	u8 center_y;			///<Sin�J�[�u���S���WY
	u8 start_x;				///<Sin�J�[�u�J�n�ʒuX
	u8 start_y;				///<Sin�J�[�u�J�n�ʒuY
}APHEART_MOVE_WORK;

///�R�����A�N�V��������p���[�N
typedef struct{
	ACTIN_PROC_WORK *apw;		///<���Z�͕���Ǘ����[�N�ւ̃|�C���^
	u8 *end_flag;				///<�G�t�F�N�g�I�����ɂ����ɏI���̕Ԏ��Ƃ���TRUE������
	u8 judge_no;				///<�R��No
	s8 wait;					///<�ėp�E�F�C�g
	u8 seq;						///<�V�[�P���XNo
	
	s16 start_x;				///<�R���������WX
	s16 start_y;				///<�R���������WY
	s32 x;						///<���ݍ��WX(����8�r�b�g����)
	s32 y;						///<���ݍ��WY(����8�r�b�g����)
	u8 loop;
	union{
		struct{
			u8 dummy;
		}nom;
		struct{
			u8 dummy;
		}wear;
		struct{
			s32 x;
			s32 y;
			s16 up_power;		///<�W�����v��
			s16 backup_up_power;		///<�W�����v��
		}jump;
	};
}JUDGE_REACTION_MOVE_WORK;

///�{���e�[�W�ړ��G�t�F�N�g�p���[�N
typedef struct{
	ACTIN_SYSTEM_PARAM *sys;
	CATS_ACT_PTR cap;				///<�{���e�[�W���o�̃A�N�^�[�|�C���^
	CATS_ACT_PTR voltage_cap;		///<�{���e�[�W�|�C���g�̃A�N�^�[�|�C���^
	fx32 theta;			///<�p�x(����8�r�b�g����)
	s32 x;				///<���ݍ��WX(����8�r�b�g����)
	s32 y;				///<���ݍ��WY(����8�r�b�g����)
	s32 temp_x;
	s32 temp_y;
	s32 move_end_x;		///<�ړ��p�̓r����~�|�C���gX
	s32 move_end_y;		///<�ړ��p�̓r����~�|�C���gY
	s16 add_x;			///<X���Z�l(����8�r�b�g����)
	s16 add_y;			///<Y���Z�l(����8�r�b�g����)
	
	u8 end_x;			///<�I�_���WX
	u8 end_y;			///<�I�_���WY
	
	u8 seq;				///<�V�[�P���X�ԍ�
	u8 wait;			///<�E�F�C�g�J�E���g
	
	//����Ȃ������A�ȃf�[�^
	u8 judge_no;		///<�R��NO
	u8 point;			///<�{���e�[�W�|�C���g
}VOLTAGE_MOVE_WORK;

///�{���e�[�W�|�C���g,�p�l���ړ��p���[�N
typedef struct{
	ACTIN_PROC_WORK *apw;	///<���Z�͕���Ǘ����[�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�ΏۂƂȂ�n�[�g�̃A�N�^�[�|�C���^
	u8 *effect_count;		///<�G�t�F�N�g�J�E���^���[�N�ւ̃|�C���^
	u16 angle;				///<���݂̊p�x(����100�{)
	u8 seq;					///<�V�[�P���X�ԍ�
	u8 center_x;			///<�p�l�����S���WX
	u8 center_y;			///<�p�l�����S���WY
	s32 add_x;				///<X�ړ����Z�l
	s32 add_y;				///<Y�ړ����Z�l
	s32 x;					///<����X���W(����8�r�b�g����)
	s32 y;					///<����X���W(����8�r�b�g����)
	s16 wait;
}VOLPANEL_MOVE_WORK;

//==============================================================================
//	�f�[�^
//==============================================================================
///�R���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S JudgeObjParam = {
	JUDGE_POS_X_0, JUDGE_POS_Y_0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		0,	//�L����
		0,	//�p���b�g
		0,	//�Z��
		0,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTIN_BGPRI_JUDGE,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�R���{�b�N�X�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S JudgeBoxObjParam = {
	JUDGE_BOX_POS_X_0, JUDGE_BOX_POS_Y_0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE_BOX, PALOFS_JUDGE_BOX_LEFT,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_JUDGE_BOX,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_JUDGE_BOX,	//�Z��
		CELLANMID_JUDGE_BOX,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTIN_BGPRI_JUDGE,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���ʐR�����ɂ���n�[�g�̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S SpecialHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_SPECIAL_HEART, PALOFS_SPECIAL_HEART,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_SPECIAL_HEART,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_SPECIAL_HEART,	//�Z��
		CELLANMID_SPECIAL_HEART,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTIN_BGPRI_JUDGE,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�A�s�[���|�C���g�n�[�g�̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S AppealPointObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_APPEAL_POINT, PALOFS_APPEAL_POINT,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_APPEAL_POINT,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_APPEAL_POINT,	//�Z��
		CELLANMID_APPEAL_POINT,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_APPEAL_POINT,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�{���e�[�W�|�C���g�n�[�g�̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S VoltagePointObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_VOLTAGE_POINT, PALOFS_VOLTAGE_POINT,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_VOLTAGE_POINT,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_VOLTAGE_POINT,	//�Z��
		CELLANMID_VOLTAGE_POINT,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_VOLTAGE_POINT,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�{���e�[�W���o�̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S VoltageEffectObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_VOLTAGE_EFF, PALOFS_VOLTAGE_EFF,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_VOLTAGE_EFF,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_VOLTAGE_EFF,	//�Z��
		CELLANMID_VOLTAGE_EFF,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTIN_BGPRI_VOLTAGE_EFF,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���A�C�R���̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S NextIconObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_NEXT_ICON, PALOFS_NEXT_ICON,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_NEXT_ICON,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_NEXT_ICON,	//�Z��
		CELLANMID_NEXT_ICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_NEXT_ICON,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///��b�E�B���h�E�J�o�[�̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S WinCoverObjParam = {
	0, 0, 0,		//x, y, z
	0, 10, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_WIN_COVER_0,	//�L����
		PLTTID_WIN_COVER,	//�p���b�g
		CELLID_WIN_COVER,	//�Z��
		CELLANMID_WIN_COVER,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	0,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�R�����A�N�V�����A�C�R���̃A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S JudgeReactionObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE_REACTION, PALOFS_JUDGE_REACTION,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_JUDGE_REACTION,	//�L����
		PLTTID_OBJ_COMMON,	//�p���b�g
		CELLID_JUDGE_REACTION,	//�Z��
		CELLANMID_JUDGE_REACTION,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTIN_BGPRI_JUDGE_REACTION,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�A�s�[���|�C���g�A�C�R�����o�����W(��ԍ����̍��W)
ALIGN4 static const s16 AppealPointPos[BREEDER_MAX][2] = {	//X, Y
	{5, 5*8 + 3},
	{5, 11*8 + 3},
	{5, 17*8 + 3},
	{5, 23*8 + 3},
};

///�{���e�[�W�|�C���g�A�C�R�����o�����W(��ԍ����̍��W)
ALIGN4 static const s16 VoltagePointPos[JUDGE_MAX][2] = {	//X, Y
	{10*8 + 8 + 32*0, 1*8 + 4},
	{10*8 + 8 + 32*1, 1*8 + 4},
	{10*8 + 8 + 32*2, 1*8 + 4},
};
///�{���e�[�W�Ɨׂ̃{���e�[�W�̌���X
#define VOLTAGE_SPACE_X		(5)

///�R�����A�N�V�����A�C�R���̕\�����W
static const struct{
	s16 x;
	s16 y;
}JudgeReactionIconPos[] = {
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 0, JUDGE_BOX_POS_Y_0 - 12},
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 1, JUDGE_BOX_POS_Y_0 - 12},
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 2, JUDGE_BOX_POS_Y_0 - 12},
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///���Z�͕���m�[�}����b���b�Z�[�W�f�[�^	��A_TALK_???�̒�`�ƕ��т𓯂��ɂ��Ă������I�I
static const ACTIN_MESSAGE_PARAM ActinTalkMsgData[] = {
	{0,									ATAG_NONE,		FALSE},	//�_�~�[

	{CAMSG_TALK_SELECT_JUDGE,			ATAG_NUM,		TRUE},
	{CAMSG_TALK_SELECT_WAZA,			ATAG_NUM,		TRUE},
	{CAMSG_TALK_SELECT_WAZA0002,		ATAG_NUM,		TRUE},
	{CAMSG_TALK_WAZA_APPEAL,			ATAG_MINE_JUDGE_WAZA,	FALSE},
	{CAMSG_TALK_JUDGE_LOOK,				ATAG_NONE,		FALSE},		///<�\���ʒu�ύX
	{CAMSG_TALK_JUDGE_SUFFER,			ATAG_JUDGE,		FALSE},	//�폜
	{CAMSG_TALK_JUDGE_SUFFER0002,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_JUDGE_SUFFER0003,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_JUDGE_SUFFER0004,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_NO_JUDGE_SUFFER,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_VOLTAGE_UP_1,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_2,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_3,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_4,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_5,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_6,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_1,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_10,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_2,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_3,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_4,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_5,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_2,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_3,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_4,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_5,		ATAG_NUM,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_3,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_2,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_1,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_0,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_0,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_1,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_2,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_3,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_4,			ATAG_MINE,		FALSE},
	{msg_con_act_host_01,				ATAG_NONE,		FALSE},
	{msg_con_act_host_02,				ATAG_NONE,		FALSE},
	{msg_con_act_host_03,				ATAG_NONE,		FALSE},
	{msg_con_act_host_04,				ATAG_NONE,		FALSE},
	{msg_con_act_host_05,				ATAG_NONE,		FALSE},
	{msg_con_act_host_06,				ATAG_NONE,		FALSE},
	{msg_con_a_explain_01,				ATAG_NONE,		FALSE},
	{msg_con_a_explain_02,				ATAG_NONE,		FALSE},
	{msg_con_a_prac_apreface,			ATAG_NONE,		FALSE},
	{msg_con_a_prac_01,					ATAG_NONE,		FALSE},
	{msg_con_a_caution_01,				ATAG_NONE,		TRUE},	//������@���������イ�c
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�ϋq�̊����̃{�����[��
ALIGN4 static const int AudienceVolume[] = {
	0, ACTIN_AUDIENCE_VOLUME - 30, ACTIN_AUDIENCE_VOLUME, ACTIN_AUDIENCE_VOLUME + 30,
};
///�{�����[�����x���ő�
#define AUDIENCE_VOLUME_LEVEL_MAX		(NELEMS(AudienceVolume))
///���_���Ƀ{�����[���̃��x�����グ�Ă�����
#define AUDIENCE_VOLUME_LEVEL_POINT		(50)


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void TalkWinSlideInOutMain(TCB_PTR tcb, void *work);
void AT_BreederPanelFontOamCreate(ACTIN_PROC_WORK *apw, int breeder_no);
void AT_BreederPanelFontOamCreateAll(ACTIN_PROC_WORK *apw);
void AT_BreederPanelFontOamDeleteAll(ACTIN_PROC_WORK *apw);
void AT_BreederPanelFontOamPosUpdate(ACTIN_PROC_WORK *apw);
void AT_BrdPanelAlphaEffectSet(ACTIN_PROC_WORK *apw, int eff_type, u8 *end_flag);
static void BrdPanelAlphaEffMain(TCB_PTR tcb, void *work);
static void BrdPanelAlphaSet_VTask(TCB_PTR tcb, void *work);
static void AudienceAnimeMain(TCB_PTR tcb, void *work);
static void AppealPointAppearEffectSet(CATS_ACT_PTR cap);
static void AppealPointAppear(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Nomination(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Wear(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Jump(TCB_PTR tcb, void *work);
static void APHeartMoveTask(TCB_PTR tcb, void *work);
static void VoltageAnimeUpdateTask(TCB_PTR tcb, void *work);
static void VoltageMoveTask(TCB_PTR tcb, void *work);
static void BreederPanel_FlashMain(TCB_PTR tcb, void *work);

//==============================================================================
//	�f�[�^
//==============================================================================
///�e�u���[�_�[�̃p�l���p���b�g�ԍ�
ALIGN4 const u8 BreederPanelScreenPalNo[] = {6, 7, 0xa, 0xb};


//--------------------------------------------------------------
/**
 * @brief   ���Z�͉�ʂ̃f�t�H���g�u�����h�ݒ���s��
 *
 * �Z�G�t�F�N�g��������Ă΂��֐��ł�
 */
//--------------------------------------------------------------
void ActinExTool_DefaultBlendSet(void)
{
	G2_BlendNone();
}

#if 0	//�u���[�_�[����OBJ�ŕ\������悤�ɂȂ���
//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�����p�l���ɕ`�悷��
 *
 * @param   apw				���Z�͊Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�Ώۂ̃u���[�_�[�ԍ�
 * @param   put_pos			�`�悷��p�l���̈ʒu
 * @param   bmp_pal			BMP�̃p���b�g�ԍ�
 */
//--------------------------------------------------------------
void BreederParamBmpWrite(ACTIN_PROC_WORK *apw, int breeder_no, int put_pos, int bmp_pal)
{
	STRBUF *oyaname_buf, *nickname_buf;
	
	nickname_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_ACTIN);
	oyaname_buf = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_ACTIN);

	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_nickname_buf, nickname_buf);
	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_oyaname_buf, oyaname_buf);

	GF_BGL_BmpWinSet_Pal(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], bmp_pal);
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], 
		BMPWIN_PANEL_FILL_COLOR);
	
	GF_STR_PrintColor(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], FONT_SYSTEM, 
		nickname_buf, 0, 0, 
		MSG_NO_PUT, MSGCOLOR_BREEDERPARAM, NULL);
	GF_STR_PrintColor(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], FONT_SYSTEM, 
		oyaname_buf, 0, 16, 
		MSG_NO_PUT, MSGCOLOR_BREEDERPARAM, NULL);

	STRBUF_Delete(oyaname_buf);
	STRBUF_Delete(nickname_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̏����p�l���ɕ`�悷��
 * @param   apw				���Z�͊Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BreederParamBmpWriteAll(ACTIN_PROC_WORK *apw)
{
	int i, pal;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(apw->a_game.breeder_sort[i] == apw->consys->c_game.my_breeder_no){
			pal = MYBREEDER_PANEL_SCREEN_PAL;
		}
		else{
			pal = BREEDER_PANEL_SCREEN_PAL;
		}
		BreederParamBmpWrite(apw, apw->a_game.breeder_sort[i], i, pal);
	}
	//���S�ĕ`�悵�Ă���E�B���h�EON��
	for(i = 0; i < BREEDER_MAX; i++){
		GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + i]);
	}
}
#endif

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���̃J���[(�X�N���[��)��ύX����
 *
 * @param   apw				���Z�͊Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_pos		����������p�l���̈ʒu
 * @param   pal_no			�V���ɃZ�b�g����p���b�g�ԍ�
 */
//--------------------------------------------------------------
void BreederPanelColorChange(ACTIN_PROC_WORK *apw, int breeder_pos, int pal_no)
{
	u16 *scrbuf;
	int x, y;
	
	scrbuf = GF_BGL_ScreenAdrsGet(apw->sys.bgl, ACTIN_FRAME_BRDPANEL);
	scrbuf = &scrbuf[32 * (breeder_pos * BREEDER_PANEL_Y_LEN) + BREEDER_PANEL_SCREEN_START_POS];
	for(y = 0; y < BREEDER_PANEL_Y_LEN; y++){
		for(x = 0; x < BREEDER_PANEL_X_LEN; x++){
			scrbuf[y * 32 + x] = (scrbuf[y * 32 + x] & 0x0fff) | (pal_no << 12);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�u���[�_�[�p�l���̃J���[(�X�N���[��)��ύX����
 * @param   apw		���Z�͊Ǘ����[�N�ւ̃|�C���^
 *
 * breeder_sort�ɏ]���ď����������s���܂�
 */
//--------------------------------------------------------------
void BreederPanelColorChangeAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		BreederPanelColorChange(apw, i, BreederPanelScreenPalNo[apw->a_game.breeder_sort[i]]);
	}
	GF_BGL_LoadScreenV_Req(apw->sys.bgl, ACTIN_FRAME_BRDPANEL);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���̃t���b�V������^�X�N�𐶐�����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 *
 * @retval  ���������t���b�V�����샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
PANEL_FLASH_WORK * BreederPanel_FlashTaskSet(ACTIN_PROC_WORK *apw, int breeder_no)
{
	PANEL_FLASH_WORK *pfw;
	
	pfw = sys_AllocMemory(HEAPID_ACTIN, sizeof(PANEL_FLASH_WORK));
	MI_CpuClear8(pfw, sizeof(PANEL_FLASH_WORK));
	
	pfw->pfd = apw->sys.pfd;
	pfw->breeder_no = breeder_no;
	pfw->tcb = TCB_Add(BreederPanel_FlashMain, pfw, TCBPRI_ACTIN_BRDPANEL_FLASH);
	return pfw;
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���̃t���b�V������^�X�N���폜����
 * @param   pfw		�t���b�V�����샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BreederPanel_FlashTaskDelete(PANEL_FLASH_WORK *pfw)
{
	GF_ASSERT(pfw->req == FALSE);
	TCB_Delete(pfw->tcb);
	sys_FreeMemoryEz(pfw);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���̃t���b�V�����N�G�X�g��ݒ肷��
 * @param   pfw		�t���b�V�����샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BreederPanel_FlashReqSet(PANEL_FLASH_WORK *pfw)
{
	pfw->req = TRUE;
	pfw->evy = PANEL_FLASH_START_EVY;
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���Ƀt���b�V�����N�G�X�g���������Ă��邩�`�F�b�N
 * @param   pfw		�t���b�V�����샏�[�N�ւ̃|�C���^
 * @retval  TRUE:���N�G�X�g�������AFALSE:�ҋ@��
 */
//--------------------------------------------------------------
BOOL BreederPanel_FlashReqCheck(PANEL_FLASH_WORK *pfw)
{
	return pfw->req;
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���F�t���b�V�����상�C���^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�t���b�V�����샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BreederPanel_FlashMain(TCB_PTR tcb, void *work)
{
	PANEL_FLASH_WORK *pfw = work;
	
	if(pfw->req == FALSE){
		return;
	}
	
	SoftFadePfd(pfw->pfd, FADE_MAIN_BG, 
		BreederPanelScreenPalNo[pfw->breeder_no] * 16 + PANEL_FLASH_START_POS,
		PANEL_FLASH_COLOR_NUM, pfw->evy >> 8, PANEL_FLASH_RGB);
	if(pfw->evy == 0){
		pfw->req = FALSE;
		return;
	}
	pfw->evy -= PANEL_FLASH_SUB_EVY;
	if(pfw->evy < 0){
		pfw->evy = 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ϐg�Ȃǂ̋Z�G�t�F�N�g��A�\�t�g�E�F�A�X�v���C�g�̕`���Ԃ𕜋A����ׂɁA��蒼��
 *
 * @param   sys				���Z�̓V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void AT_SoftSpriteHensinPop(ACTIN_SYSTEM_PARAM *sys, int breeder_no)
{
	SoftSpriteDel(sys->ss[breeder_no]);

	GF_ASSERT(sys->exchr_param[breeder_no].exchr_buffer != NULL);
	MI_CpuClear8(sys->exchr_param[breeder_no].exchr_buffer, EXCHR_BUFFER_SIZE);
	
	sys->ss[breeder_no] = ConTool_BreederPokemonAdd(sys->soft_sprite, breeder_no, 
		sys->c_game->pp[breeder_no], PARA_BACK, &sys->exchr_param[breeder_no], HEAPID_ACTIN, 
		ACTIN_POKEPOS_X-32*breeder_no, ACTIN_POKEPOS_Y-32*breeder_no, ACTIN_POKEPOS_Z);
	//�\��OFF
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_VANISH, TRUE);
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_DRAW_STOP, TRUE);
	//���]�Z�b�g
	{
		u32 monsno;
		monsno = PokeParaGet(sys->c_game->pp[breeder_no], ID_PARA_monsno, NULL);
		if(ContestPokeFlipCheck(monsno) == TRUE){
			SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_H_FLIP, TRUE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)�𐶐�����
 *
 * @param   sys		���Z�̓V�X�e�����[�N�ւ̃|�C���^
 * @param   pp		�S�u���[�_�[�̃|�P�����p�����[�^�������Ă���z��ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_SoftSpriteAddAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		GF_ASSERT(sys->exchr_param[i].exchr_buffer == NULL);
		sys->exchr_param[i].exchr_buffer = sys_AllocMemory(HEAPID_ACTIN, EXCHR_BUFFER_SIZE);
		
		sys->ss[i] = ConTool_BreederPokemonAdd(sys->soft_sprite, i, sys->c_game->pp[i], 
			PARA_BACK, &sys->exchr_param[i], HEAPID_ACTIN, 
			ACTIN_POKEPOS_X-32*i, ACTIN_POKEPOS_Y-32*i, ACTIN_POKEPOS_Z);
		//�\��OFF
		SoftSpriteParaSet(sys->ss[i], SS_PARA_VANISH, TRUE);
		SoftSpriteParaSet(sys->ss[i], SS_PARA_DRAW_STOP, TRUE);
		//���]�Z�b�g
		{
			u32 monsno;
			monsno = PokeParaGet(sys->c_game->pp[i], ID_PARA_monsno, NULL);
			if(ContestPokeFlipCheck(monsno) == TRUE){
				SoftSpriteParaSet(sys->ss[i], SS_PARA_H_FLIP, TRUE);
			}
		}
	}
	
	GF_ASSERT(sys->transparent_exchr_param.exchr_buffer == NULL);
	sys->transparent_exchr_param.exchr_buffer = sys_AllocMemory(HEAPID_ACTIN, EXCHR_BUFFER_SIZE);
	sys->transparent_exchr_param.pal_index = sys->exchr_param[0].pal_index;	//�_�~�[
	sys->transparent_exchr_param.arcID = sys->exchr_param[0].arcID;	//�_�~�[
	//�o�b�t�@�N���A
	MI_CpuClear32(sys->transparent_exchr_param.exchr_buffer, EXCHR_BUFFER_SIZE);
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)���폜����
 * @param   sys		���Z�̓V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_SoftSpriteDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		SoftSpriteDel(sys->ss[i]);
		sys_FreeMemoryEz(sys->exchr_param[i].exchr_buffer);
		sys->exchr_param[i].exchr_buffer = NULL;
	}
	sys_FreeMemoryEz(sys->transparent_exchr_param.exchr_buffer);
	sys->transparent_exchr_param.exchr_buffer = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �R���A�N�^�[�̐����ƃ��\�[�X�o�^
 *
 * @param   pfd			�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   csp			csp
 * @param   crp			crp
 * @param   judge		�R���f�[�^�ւ̃|�C���^
 * @param   judge_no	�R��NO
 *
 * @retval  ���������R���A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_JudgeAdd(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	const JUDGE_DATA *judge, int judge_no)
{
	CATS_ACT_PTR judge_cap;
	TCATS_OBJECT_ADD_PARAM_S judge_head;
	
#if WAIT_FIX	//OBJ�R�[�h�ɂ���Ďg�p����G��ύX����H
	switch(judge->obj_code){
	case 0:
		break;
	default:
		break;
	}
#else
	u32 char_id, pal_id, cell_id, anm_id;
	
	switch(judge_no){
	case 0:
		char_id = CON_GORGGEOUSM_NCGR_BIN;
		pal_id = CON_GORGGEOUSM_NCLR;
		cell_id = CON_GORGGEOUSM_NCER_BIN;
		anm_id = CON_GORGGEOUSM_NANR_BIN;
		break;
	case 1:
		char_id = CON_GENTLEMAN_NCGR_BIN;
		pal_id = CON_GENTLEMAN_NCLR;
		cell_id = CON_GENTLEMAN_NCER_BIN;
		anm_id = CON_GENTLEMAN_NANR_BIN;
		break;
	default:
		char_id = CON_IDOL_NCGR_BIN;
		pal_id = CON_IDOL_NCLR;
		cell_id = CON_IDOL_NCER_BIN;
		anm_id = CON_IDOL_NANR_BIN;
		break;
	}
	
	//-- ���\�[�X���[�h --//
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_0 + judge_no);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_CONTEST_OBJ, pal_id, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_JUDGE_0 + judge_no);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_0 + judge_no);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_0 + judge_no);
	
	//-- �A�N�^�[���� --//
	judge_head = JudgeObjParam;
	judge_head.id[CLACT_U_CHAR_RES] = CHARID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_PLTT_RES] = PLTTID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_CELL_RES] = CELLID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_CELLANM_RES] = CELLANMID_JUDGE_0 + judge_no;
	judge_head.x = JUDGE_POS_X_0 + JUDGE_POS_X_SPACE * judge_no;
	judge_head.y = JUDGE_POS_Y_0 + JUDGE_POS_Y_SPACE * judge_no;
	judge_cap = CATS_ObjectAdd_S(csp, crp, &judge_head);
	CATS_ObjectUpdate(judge_cap->act);
#endif

	return judge_cap;
}

//--------------------------------------------------------------
/**
 * @brief   �R���A�N�^�[�����\�[�X�폜
 *
 * @param   crp				crp
 * @param   judge_cap		�R���A�N�^�[�ւ̃|�C���^
 * @param   judge_no		�R��No
 */
//--------------------------------------------------------------
static void AT_JudgeDel(CATS_RES_PTR crp, CATS_ACT_PTR judge_cap, int judge_no)
{
#if WAIT_FIX	//���K��ADD���@���܂��킩��Ȃ��̂ŁA�폜���킩��Ȃ�
	;
#else
	//-- �A�N�^�[�폜 --//
	CATS_ActorPointerDelete_S(judge_cap);

	//-- ���\�[�X�폜 --//
	CATS_FreeResourceChar(crp, CHARID_JUDGE_0 + judge_no);
	CATS_FreeResourcePltt(crp, PLTTID_JUDGE_0 + judge_no);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_0 + judge_no);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_0 + judge_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �R���{�b�N�X�̃��\�[�X�o�^
 *
 * @param   pfd			�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   csp			csp
 * @param   crp			crp
 *
 * �S�Ă̐R���{�b�N�X�œ������\�[�X���g���܂킷�悤�ɂȂ��Ă��܂��B
 */
//--------------------------------------------------------------
static void AT_JudgeBoxResourceLoad(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	u32 char_id, cell_id, anm_id;
	
	char_id = JUDGE_BOX_NCGR_BIN;
	cell_id = JUDGE_BOX_NCER_BIN;
	anm_id = JUDGE_BOX_NANR_BIN;
	
	//-- ���\�[�X���[�h --//
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_BOX);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_BOX);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_BOX);
}

//--------------------------------------------------------------
/**
 * @brief   �R���{�b�N�X�A�N�^�[�̐���
 *
 * @param   csp			csp
 * @param   crp			crp
 * @param   judge_no	�R��NO
 *
 * @retval  ���������R���{�b�N�X�A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_JudgeBoxActorAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no)
{
	CATS_ACT_PTR box_cap;
	TCATS_OBJECT_ADD_PARAM_S box_head;
	const int judge_palofs[] = {
		PALOFS_JUDGE_BOX_LEFT, PALOFS_JUDGE_BOX_CENTER, PALOFS_JUDGE_BOX_RIGHT,
	};
	
	//-- �A�N�^�[���� --//
	box_head = JudgeBoxObjParam;
	box_head.x = JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * judge_no;
	box_head.y = JUDGE_BOX_POS_Y_0 + JUDGE_BOX_POS_Y_SPACE * judge_no;
	box_head.pal = 	judge_palofs[judge_no];
	box_cap = CATS_ObjectAdd_S(csp, crp, &box_head);
	CATS_ObjectUpdate(box_cap->act);

	return box_cap;
}

//--------------------------------------------------------------
/**
 * @brief   �R���{�b�N�X�A�N�^�[�폜
 *
 * @param   box_cap			�R���{�b�N�X�A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void AT_JudgeBoxActorDel(CATS_ACT_PTR box_cap)
{
	CATS_ActorPointerDelete_S(box_cap);
}

//--------------------------------------------------------------
/**
 * @brief   �R���{�b�N�X���\�[�X�폜
 *
 * @param   crp				crp
 */
//--------------------------------------------------------------
static void AT_JudgeBoxResourceDel(CATS_RES_PTR crp)
{
	//-- ���\�[�X�폜 --//
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, CHARID_JUDGE_BOX);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_BOX);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_BOX);
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ă̐R���ƐR���{�b�N�X�̃A�N�^�[�ƃ��\�[�X��o�^����
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_JudgeAddAll(ACTIN_SYSTEM_PARAM *sys, CONTEST_SYSTEM *consys)
{
	int i;
	
	//�R���{�b�N�X�̃��\�[�X�ǂݍ���
	AT_JudgeBoxResourceLoad(sys->pfd, sys->csp, sys->crp);

	for(i = 0; i < JUDGE_MAX; i++){
		sys->judge_box_cap[i] = AT_JudgeBoxActorAdd(sys->csp, sys->crp, i);
		sys->judge_cap[i] = 
			AT_JudgeAdd(sys->pfd, sys->csp, sys->crp, &consys->c_game.jd[i], i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ă̐R���ƐR���{�b�N�X�̃A�N�^�[�ƃ��\�[�X�̍폜���s��
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_JudgeDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < JUDGE_MAX; i++){
		AT_JudgeDel(sys->crp, sys->judge_cap[i], i);
		AT_JudgeBoxActorDel(sys->judge_box_cap[i]);
	}
	AT_JudgeBoxResourceDel(sys->crp);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R���̃��\�[�X�o�^
 *
 * @param   pfd			�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   csp			csp
 * @param   crp			crp
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconResourceLoad(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	u32 char_id, cell_id, anm_id;
	
	char_id = EXCLAMATION_NCGR_BIN;
	cell_id = EXCLAMATION_NCER_BIN;
	anm_id = EXCLAMATION_NANR_BIN;
	
	//-- ���\�[�X���[�h --//
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_REACTION);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_REACTION);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_REACTION);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R�����\�[�X�폜
 *
 * @param   crp				crp
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconResourceDel(CATS_RES_PTR crp)
{
	//-- ���\�[�X�폜 --//
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, CHARID_JUDGE_REACTION);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_REACTION);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_REACTION);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R���A�N�^�[�̐���
 * @param   sys			���Z�̓V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconActorAdd(ACTIN_SYSTEM_PARAM *sys)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S act_head;
	
	//-- �A�N�^�[���� --//
	act_head = JudgeReactionObjParam;
	cap = CATS_ObjectAdd_S(sys->csp, sys->crp, &act_head);
	
	CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);

	CATS_ObjectUpdate(cap->act);
	
	sys->judge_reaction_icon_cap = cap;
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R���A�N�^�[�폜
 *
 * @param   box_cap			�R�����A�N�V�����A�C�R���A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconActorDel(ACTIN_SYSTEM_PARAM *sys)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);
	
	CATS_ActorPointerDelete_S(sys->judge_reaction_icon_cap);
	sys->judge_reaction_icon_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R����\��ON����
 *
 * @param   sys				���Z�̓V�X�e�����[�N�ւ̃|�C���^
 * @param   judge_no		�R��No
 * @param   reaction_type	���A�N�V�����^�C�v(JUDGE_REACTION_ICON_???)
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconON(ACTIN_SYSTEM_PARAM *sys, int judge_no, int reaction_type)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);

	CATS_ObjectPosSetCap(sys->judge_reaction_icon_cap, 
		JudgeReactionIconPos[judge_no].x, JudgeReactionIconPos[judge_no].y);
	CATS_ObjectAnimeSeqSetCap(sys->judge_reaction_icon_cap, reaction_type);
	CATS_ObjectEnableCap(sys->judge_reaction_icon_cap, CATS_ENABLE_TRUE);
	
	switch(reaction_type){
	case JUDGE_REACTION_ICON_NOMINATION:
		Snd_SePlay(ASE_ICON_NOMINATION);
		break;
	case JUDGE_REACTION_ICON_WEAR:
		Snd_SePlay(ASE_ICON_WEAR);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE:
		Snd_SePlay(ASE_ICON_VOLTAGE);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE_MAX:
		Snd_SePlay(ASE_ICON_VOLTAGE_MAX);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V�����A�C�R����\��OFF����
 * @param   sys		���Z�̓V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconOFF(ACTIN_SYSTEM_PARAM *sys)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);

	CATS_ObjectEnableCap(sys->judge_reaction_icon_cap, CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   �R�������A�N�V�������삳����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   judge_no		�R��No
 * @param   reaction_type	���A�N�V�����^�C�v(JUDGE_REACTION_ICON_???)
 * @param   end_flag		�I����������TRUE������
 */
//--------------------------------------------------------------
void AT_JudgeReactionMoveTaskSet(ACTIN_PROC_WORK *apw, int judge_no, 
	int reaction_type, u8 *end_flag)
{
	JUDGE_REACTION_MOVE_WORK *jrmw;
	
	jrmw = sys_AllocMemory(HEAPID_ACTIN, sizeof(JUDGE_REACTION_MOVE_WORK));
	MI_CpuClear8(jrmw, sizeof(JUDGE_REACTION_MOVE_WORK));
	
	*end_flag = FALSE;
	jrmw->end_flag = end_flag;
	jrmw->apw = apw;
	jrmw->judge_no = judge_no;
	
	CATS_ObjectPosGetCap(apw->sys.judge_cap[judge_no], &jrmw->start_x, &jrmw->start_y);
	
	switch(reaction_type){
	case JUDGE_REACTION_ICON_NOMINATION:
	default:
		//TCB_Add(JudgeReactionMove_Nomination, jrmw, TCBPRI_ACTIN_EFFECT);
		jrmw->loop = 1;
		jrmw->jump.up_power = -JUDGE_JUMP_NOMINATION_POWER;
		jrmw->jump.backup_up_power = -JUDGE_JUMP_NOMINATION_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_WEAR:
		TCB_Add(JudgeReactionMove_Wear, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE:
		jrmw->jump.up_power = -JUDGE_JUMP_VOLTAGE_UP_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE_MAX:
		jrmw->jump.up_power = -JUDGE_JUMP_VOLTAGE_MAX_UP_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_BIG:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_BIG;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_MIDDLE:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_MIDDLE;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_SMALL:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_SMALL;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V��������F�w��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R�����A�N�V�������샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Nomination(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
	case 3:
		jrmw->y -= JUDGE_NOMINATION_ADD_Y;
		jrmw->loop++;
		if(jrmw->loop > JUDGE_NOMINATION_LOOP){
			jrmw->loop = 0;
			jrmw->seq++;
		}
		break;
	case 2:
	case 4:
		jrmw->y += JUDGE_NOMINATION_ADD_Y;
		jrmw->loop++;
		if(jrmw->loop > JUDGE_NOMINATION_LOOP){
			jrmw->loop = 0;
			jrmw->y = jrmw->start_y * 0x0100;
			jrmw->seq++;
		}
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
		jrmw->x / 0x0100, jrmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V��������F���
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R�����A�N�V�������샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Wear(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
		if(jrmw->loop & 1){
			jrmw->x = jrmw->start_x * 0x0100 + JUDGE_WEAR_ADD_X;
		}
		else{
			jrmw->x = jrmw->start_x * 0x0100 - JUDGE_WEAR_ADD_X;
		}

		jrmw->loop++;
		if(jrmw->loop > JUDGE_WEAR_LOOP){
			jrmw->x = jrmw->start_x * 0x0100;
			jrmw->loop = 0;
			jrmw->seq++;
		}
		break;
	case 2:
		jrmw->wait++;
		if(jrmw->wait > 15){
			jrmw->wait = 0;
			jrmw->seq++;
		}
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
		jrmw->x / 0x0100, jrmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   �R�����A�N�V��������F�W�����v(�{���e�[�W�A�{���e�[�WMAX)
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R�����A�N�V�������샏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Jump(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
		jrmw->y += jrmw->jump.up_power;
		jrmw->jump.up_power += JUDGE_JUMP_GRAVITY;
		if(jrmw->y >= jrmw->start_y * 0x0100){
			jrmw->y = jrmw->start_y * 0x0100;
			if(jrmw->loop > 0){
				jrmw->jump.up_power = jrmw->jump.backup_up_power;
				jrmw->loop--;
				jrmw->seq--;
			}
			else{
				jrmw->seq++;
			}
		}
		CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
			jrmw->x / 0x0100, jrmw->y / 0x0100);
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ʐR�����ɂ���n�[�g�A�N�^�[�𐶐�����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   judge_no		����R������NO
 */
//--------------------------------------------------------------
void AT_SpecialHeartSet(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	GF_ASSERT(sys->special_heart_cap == NULL);
	
	//���\�[�X�ǂݍ���
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_SPECIAL_HEART);
	CATS_LoadResourceCellArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NCER_BIN, 1, 
		CELLID_SPECIAL_HEART);
	CATS_LoadResourceCellAnmArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NANR_BIN, 1, CELLANMID_SPECIAL_HEART);
	
	//�A�N�^�[����
	sys->special_heart_cap = CATS_ObjectAdd_S(sys->csp, sys->crp, &SpecialHeartObjParam);
	CATS_ObjectUpdate(sys->special_heart_cap->act);
	CATS_ObjectPosSetCap(sys->special_heart_cap, 
		SPECIAL_HEART_POS_X + SPECIAL_HEART_POS_X_SPACE * judge_no, SPECIAL_HEART_POS_Y);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʐR�����ɂ���n�[�g���폜����
 *
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_SpecialHeartDel(ACTIN_SYSTEM_PARAM *sys)
{
	//-- ���\�[�X�폜 --//
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(sys->crp, CHARID_SPECIAL_HEART);
	CATS_FreeResourceCell(sys->crp, CELLID_SPECIAL_HEART);
	CATS_FreeResourceCellAnm(sys->crp, CELLANMID_SPECIAL_HEART);
	
	//-- �A�N�^�[�폜 --//
	CATS_ActorPointerDelete_S(sys->special_heart_cap);
	sys->special_heart_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���|�C���g�̃��\�[�X���[�h����
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_AppealPointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_APPEAL_POINT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCER_BIN, 1, 
		CELLID_APPEAL_POINT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NANR_BIN, 1, CELLANMID_APPEAL_POINT);
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���|�C���g�̃��\�[�X���������
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_AppealPointResourceFree(CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, CHARID_APPEAL_POINT);
	CATS_FreeResourceCell(crp, CELLID_APPEAL_POINT);
	CATS_FreeResourceCellAnm(crp, CELLANMID_APPEAL_POINT);
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���A�C�R�����폜����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[No
 * @param   act_pos			�A�N�^�[���[�N�ʒu
 */
//--------------------------------------------------------------
static inline void AppealPointActorDel(ACTIN_SYSTEM_PARAM *sys, int breeder_no, int act_pos)
{
	if(sys->appeal_point_cap[breeder_no][act_pos] != NULL){
		CATS_ActorPointerDelete_S(sys->appeal_point_cap[breeder_no][act_pos]);
		sys->appeal_point_cap[breeder_no][act_pos] = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���u���[�_�[�����A�s�[���|�C���g�A�C�R����S�č폜����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[NO
 */
//--------------------------------------------------------------
static void AT_AppealPointActorBreederDel(ACTIN_SYSTEM_PARAM *sys, int breeder_no)
{
	int i;
	
	for(i = 0; i < APPEAL_POINT_ICON_MAX; i++){
		AppealPointActorDel(sys, breeder_no, i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�ẴA�s�[���|�C���g�A�C�R�����폜����
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_AppealPointActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int breeder;
	
	for(breeder = 0; breeder < BREEDER_MAX; breeder++){
		AT_AppealPointActorBreederDel(sys, breeder);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���|�C���g�A�C�R���𐶐�����
 *
 * @param   csp		
 * @param   crp		
 * @param   x		�\�����WX
 * @param   y		�\�����WY
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_AppealPointActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR app_cap;
	
	//�A�N�^�[����
	app_cap = CATS_ObjectAdd_S(csp, crp, &AppealPointObjParam);
	CATS_ObjectUpdate(app_cap->act);
	CATS_ObjectPosSetCap(app_cap, x, y);
	
	return app_cap;
}

//--------------------------------------------------------------
/**
 * @brief   ���̃u���[�_�[�����A�s�[���|�C���g�A�C�R������������S�č폜���A
 *          ���|�C���g���A�C�R������蒼��
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   breeder_pos		�u���[�_�[�ʒu
 * @param   point			�\������A�s�[���|�C���g
 */
//--------------------------------------------------------------
void AT_AppealPointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int breeder_no, 
	int breeder_pos, int point)
{
	int icon_num, i, icon_pos, anm_seq;
	
	icon_num = point / APPEAL_ICON_ONE_POINT;
//	GF_ASSERT(icon_num <= APPEAL_POINT_ICON_MAX);
	if(icon_num > APPEAL_POINT_ICON_MAX * APPEAL_POINT_ICON_LOOP){
		icon_num = APPEAL_POINT_ICON_MAX * APPEAL_POINT_ICON_LOOP;
		OS_TPrintf("---�A�s�[���|�C���g�A�C�R���̕\�������ő吔�𒴂��Ă��܂��I�I---\n");
	}
	
	//�K�v�ȃA�C�R���̐��ȏ�̃A�C�R�����o�Ă���ꍇ�͂������폜����
	for(i = icon_num; i < APPEAL_POINT_ICON_MAX; i++){
		AppealPointActorDel(sys, breeder_no, i);
	}
	
	//���|�C���g���܂ł̃A�C�R�������
	for(i = icon_num-1; i > -1; i--){
		icon_pos = i % APPEAL_POINT_ICON_MAX;
		anm_seq = i / APPEAL_POINT_ICON_MAX;
		
		if(sys->appeal_point_cap[breeder_no][icon_pos] == NULL){
			sys->appeal_point_cap[breeder_no][icon_pos] = AT_AppealPointActorSet(sys->csp, 
				sys->crp, AppealPointPos[breeder_pos][0] + icon_pos*8, 
				AppealPointPos[breeder_pos][1]);
			CATS_ObjectAnimeSeqSetCap(sys->appeal_point_cap[breeder_no][icon_pos], anm_seq);
			AppealPointAppearEffectSet(sys->appeal_point_cap[breeder_no][icon_pos]);
		}
		else if(CATS_ObjectAnimeSeqGetCap(sys->appeal_point_cap[breeder_no][icon_pos]) < anm_seq){
			CATS_ObjectAnimeSeqSetCap(sys->appeal_point_cap[breeder_no][icon_pos], anm_seq);
			AppealPointAppearEffectSet(sys->appeal_point_cap[breeder_no][icon_pos]);
		}
	}
	
	//SE�Đ�
	Snd_SePlay(ASE_AP_UP);
	Snd_PlayerSetTrackPitchBySeqNo(ASE_AP_UP, 0xffff, SND_HALF_PITCH * (icon_num - 1));
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���A�C�R���o��G�t�F�N�g�^�X�N�𐶐�����
 * @param   cap		�A�s�[���A�C�R���̃|�C���^
 */
//--------------------------------------------------------------
static void AppealPointAppearEffectSet(CATS_ACT_PTR cap)
{
	APPEAL_POINT_APPEAR_WORK *apaw;
	
	apaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(APPEAL_POINT_APPEAR_WORK));
	MI_CpuClear8(apaw, sizeof(APPEAL_POINT_APPEAR_WORK));
	apaw->cap = cap;
	CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
	TCB_Add(AppealPointAppear, apaw, TCBPRI_ACTIN_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �A�s�[���A�C�R���o��G�t�F�N�g���C���^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		APPEAL_POINT_APPEAR_WORK�\����
 */
//--------------------------------------------------------------
static void AppealPointAppear(TCB_PTR tcb, void *work)
{
	APPEAL_POINT_APPEAR_WORK *apaw = work;
	
	switch(apaw->seq){
	case 0:
		CATS_ObjectAffineSetCap(apaw->cap, CLACT_AFFINE_DOUBLE);
		apaw->sx = APICON_EFF_INIT_SCALE;
		apaw->sy = APICON_EFF_INIT_SCALE;
		CATS_ObjectEnableCap(apaw->cap, CATS_ENABLE_TRUE);
//		CATS_ObjectScaleSetCap(apaw->cap, 1.4f, 1.4f);
		apaw->seq++;
		//break;
	case 1:
		apaw->sx += APICON_EFF_ADD_SCALE;
		apaw->sy += APICON_EFF_ADD_SCALE;
		CATS_ObjectScaleSetCap(apaw->cap, apaw->sx, apaw->sy);
		CATS_ObjectRotationAddCap(apaw->cap, APICON_EFF_ADD_ROTATION);
		if(apaw->sx >= APICON_EFF_MAX_SCALE){
			apaw->seq++;
		}
		break;
	case 2:
		apaw->sx -= APICON_EFF_ADD_SCALE;
		apaw->sy -= APICON_EFF_ADD_SCALE;
		CATS_ObjectScaleSetCap(apaw->cap, apaw->sx, apaw->sy);
		CATS_ObjectRotationAddCap(apaw->cap, APICON_EFF_ADD_ROTATION);
		if(apaw->sx <= APICON_EFF_NORMAL_SCALE){
			CATS_ObjectScaleSetCap(apaw->cap, APICON_EFF_NORMAL_SCALE, APICON_EFF_NORMAL_SCALE);
			CATS_ObjectRotationSetCap(apaw->cap, 0);
			apaw->seq++;
		}
		break;
	default:
		CATS_ObjectAffineSetCap(apaw->cap, CLACT_AFFINE_NONE);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�̃��\�[�X���[�h����
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_VoltagePointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_VOLTAGE_POINT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NCER_BIN, 1, 
		CELLID_VOLTAGE_POINT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NANR_BIN, 1, CELLANMID_VOLTAGE_POINT);

	//�{���e�[�W���o
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_VOLTAGE_EFF);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NCER_BIN, 1, 
		CELLID_VOLTAGE_EFF);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NANR_BIN, 1, CELLANMID_VOLTAGE_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�̃��\�[�X���������
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_VoltagePointResourceFree(CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, CHARID_VOLTAGE_POINT);
	CATS_FreeResourceCell(crp, CELLID_VOLTAGE_POINT);
	CATS_FreeResourceCellAnm(crp, CELLANMID_VOLTAGE_POINT);

	//�{���e�[�W���o
	CATS_FreeResourceChar(crp, CHARID_VOLTAGE_EFF);
	CATS_FreeResourceCell(crp, CELLID_VOLTAGE_EFF);
	CATS_FreeResourceCellAnm(crp, CELLANMID_VOLTAGE_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�A�C�R���̒P�ƍ폜
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   judge_no		�R��No
 * @param   icon_pos		�A�C�R���̈ʒu
 */
//--------------------------------------------------------------
static inline void AT_VoltagePointActorDel(ACTIN_SYSTEM_PARAM *sys, int judge_no, int icon_pos)
{
	CATS_ActorPointerDelete_S(sys->voltage_point_cap[judge_no][icon_pos]);
	sys->voltage_point_cap[judge_no][icon_pos] = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���R�������{���e�[�W�|�C���g�A�C�R����S�č폜����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   judge_no		�R��No
 */
//--------------------------------------------------------------
static void AT_VoltagePointActorJudgeDel(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			AT_VoltagePointActorDel(sys, judge_no, i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵ{���e�[�W�|�C���g�A�C�R�����폜����
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_VoltagePointActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int judge;
	
	for(judge = 0; judge < JUDGE_MAX; judge++){
		AT_VoltagePointActorJudgeDel(sys, judge);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�A�C�R���𐶐�����
 *
 * @param   csp		
 * @param   crp		
 * @param   x		�\�����WX
 * @param   y		�\�����WY
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_VoltagePointActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR app_cap;
	
	//�A�N�^�[����
	app_cap = CATS_ObjectAdd_S(csp, crp, &VoltagePointObjParam);
	CATS_ObjectUpdate(app_cap->act);
	CATS_ObjectPosSetCap(app_cap, x, y);
	
	return app_cap;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���o�A�C�R���𐶐�����
 *
 * @param   csp		
 * @param   crp		
 * @param   x		�\�����WX
 * @param   y		�\�����WY
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_VoltageEffectActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR cap;
	
	//�A�N�^�[����
	cap = CATS_ObjectAdd_S(csp, crp, &VoltageEffectObjParam);
	CATS_ObjectUpdate(cap->act);
	CATS_ObjectPosSetCap(cap, x, y);
	
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���o�F���C���^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		VOLTAGE_MOVE_WORK�\����
 */
//--------------------------------------------------------------
static void VoltagePointActorMove(TCB_PTR tcb, void *work)
{
	VOLTAGE_MOVE_WORK *vmw = work;
	
	switch(vmw->seq){
	case 0:
		CATS_ObjectAffineSetCap(vmw->cap, CLACT_AFFINE_NORMAL);
		
		vmw->move_end_x = vmw->x + (32<<8);
		vmw->move_end_y = vmw->y + (72<<8);
		vmw->add_x = (vmw->move_end_x - vmw->x) / VOLTAGE_MOVE_FIRST_FRAME;
		vmw->add_y = (vmw->move_end_y - vmw->y) / VOLTAGE_MOVE_FIRST_FRAME;
		vmw->seq++;
		//break;
	case 1:
		vmw->x += vmw->add_x;
		vmw->y += vmw->add_y;
		if((vmw->add_x > 0 && vmw->x >= vmw->move_end_x)
				|| (vmw->add_x < 0 && vmw->x <= vmw->move_end_x)){
			vmw->seq++;
		}
		break;
	case 2:
		vmw->wait++;
		if(vmw->wait > VOLTAGE_MOVE_FIRST_WAIT){
			vmw->wait = 0;
			vmw->seq++;
		}
		break;
	case 3:
		vmw->move_end_x = vmw->end_x << 8;
		vmw->move_end_y = vmw->end_y << 8;
		vmw->add_x = (vmw->move_end_x - vmw->x) / VOLTAGE_MOVE_END_FRAME;
		vmw->add_y = (vmw->move_end_y - vmw->y) / VOLTAGE_MOVE_END_FRAME;
		vmw->seq++;
		//break;
	case 4:
		vmw->x += vmw->add_x;
		vmw->y += vmw->add_y;
		if((vmw->add_x > 0 && vmw->x >= vmw->move_end_x)
				|| (vmw->add_x < 0 && vmw->x <= vmw->move_end_x)){
			vmw->x = vmw->end_x << 8;
			vmw->y = vmw->end_y << 8;
			vmw->seq++;
		}
		break;
	case 5:
		vmw->wait++;
		if(vmw->wait > VOLTAGE_MOVE_END_WAIT){
			vmw->wait = 0;
			vmw->seq++;
		}
		break;
	default:
		CATS_ActorPointerDelete_S(vmw->cap);

		CATS_ObjectEnableCap(vmw->voltage_cap, CATS_ENABLE_TRUE);
		
		Snd_SePlay(ASE_VOLTAGE_UP);

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	
	CATS_ObjectRotationAddCap(vmw->cap, VOLTAGE_MOVE_ADD_ROTATION);
	CATS_ObjectPosSetCap(vmw->cap, vmw->x / 0x0100, vmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�ړ��G�t�F�N�g���I�����Ă��邩�m�F
 *
 * @param   sys				���Z�̓V�X�e�����[�N�ւ̃|�C���^
 * @param   judge_no		�R���ԍ�
 *
 * @retval  TRUE:�I���B�@FALSE:���쒆�̃G�t�F�N�g������
 */
//--------------------------------------------------------------
BOOL AT_VoltageMoveEffectEndCheck(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			if(CATS_ObjectEnableGetCap(sys->voltage_point_cap[judge_no][i]) == CATS_ENABLE_FALSE){
				return FALSE;
			}
		}
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���|�C���g���܂ł̃{���e�[�W�A�C�R�����쐬����
 * 			���ɐ�������Ă���A�C�R�������|�C���g���ɒB���Ă��Ȃ���Βǉ��ō��A
 *          �t�ɑ�����������Ă���Ȃ�΁A���̕��͍폜����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   judge_no		�R���ԍ�
 * @param   point			�\������{���e�[�W�|�C���g
 */
//--------------------------------------------------------------
void AT_VoltagePointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int judge_no, int point)
{
	int icon_num, i;
	VOLTAGE_MOVE_WORK *vmw;
	
	icon_num = point / VOLTAGE_ONE_POINT;
	GF_ASSERT(icon_num <= VOLTAGE_MAX);
	
	//���|�C���g���̃A�C�R�������
	for(i = 0; i < icon_num; i++){
		if(sys->voltage_point_cap[judge_no][i] == NULL){
			sys->voltage_point_cap[judge_no][i] = AT_VoltagePointActorSet(sys->csp, sys->crp, 
				VoltagePointPos[judge_no][0] + i*VOLTAGE_SPACE_X, 
				VoltagePointPos[judge_no][1]);
			CATS_ObjectEnableCap(sys->voltage_point_cap[judge_no][i], CATS_ENABLE_FALSE);

			//�{���e�[�W���o����
			vmw = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLTAGE_MOVE_WORK));
			MI_CpuClear8(vmw, sizeof(VOLTAGE_MOVE_WORK));
			vmw->sys = sys;
			vmw->voltage_cap = sys->voltage_point_cap[judge_no][i];
			vmw->cap = AT_VoltageEffectActorSet(sys->csp, sys->crp, 
				JudgeReactionIconPos[judge_no].x, JudgeReactionIconPos[judge_no].y);
			vmw->x = JudgeReactionIconPos[judge_no].x << 8;
			vmw->y = JudgeReactionIconPos[judge_no].y << 8;
			vmw->end_x = VoltagePointPos[judge_no][0] + i*VOLTAGE_SPACE_X;
			vmw->end_y = VoltagePointPos[judge_no][1];
			vmw->judge_no = judge_no;
			vmw->point = point;
			TCB_Add(VoltagePointActorMove, vmw, TCBPRI_ACTIN_EFFECT);
		}
	}
	//���|�C���g����葽���A�C�R��������Ă���ꍇ�͍폜����
	for( ; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			AT_VoltagePointActorDel(sys, judge_no, i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�B���h�E�A�X���C�h���̃J�o�[OBJ�𐶐�
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_TalkWinSlideCoverOBJSet(ACTIN_SYSTEM_PARAM *sys)
{
	int scr_x;
	u16 *scrnbuf;
	int i, obj_palno;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	csp = sys->csp;
	crp = sys->crp;
	
	scr_x = GF_BGL_ScrollGetX(sys->bgl, ACTIN_FRAME_WIN);
	scrnbuf = GF_BGL_ScreenAdrsGet(sys->bgl, ACTIN_FRAME_WIN);
	if(scr_x == 0){
		scrnbuf = &scrnbuf[WINSLIDE_SCRN_POS_BEFORE];
	}
	else{
		scrnbuf = &scrnbuf[WINSLIDE_SCRN_POS_AFTER];
	}
	
	//���\�[�X�o�^
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_0);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_1);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_2);
	obj_palno = CATS_LoadResourcePlttWorkArc(sys->pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_CONTEST_OBJ, CONTEST_OBJ_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_WIN_COVER);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCER_BIN, 1, 
		CELLID_WIN_COVER);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		SPACE_64K_8X16_NANR_BIN, 1, CELLANMID_WIN_COVER);

	//�A�N�^�[����
	{
		TCATS_OBJECT_ADD_PARAM_S head;
		
		head = WinCoverObjParam;
		for(i = 0; i < WINCOVER_ACT_MAX; i++){
			GF_ASSERT(sys->wincover_cap[i] == NULL);
			sys->wincover_cap[i] = CATS_ObjectAdd_S(csp, crp, &head);
			CATS_ObjectPosSetCap(sys->wincover_cap[i], 0x1f * 8 + 4, 0x13 * 8 + i * 16);
			head.id[CLACT_U_CHAR_RES]++;
		}
	}
	
	//�X�N���[���Ŏg�p���Ă���L�����N�^��ǂݎ����OBJ��VRAM�փR�s�[����
	{
		void *obj_vram;
		NNSG2dImageProxy * image;
		u8 *bgchar;
		u8 *bgchar_vram;
		int k = 0;
		
		obj_vram = G2_GetOBJCharPtr();
		bgchar_vram = GF_BGL_CgxGet(ACTIN_FRAME_WIN);
		for(i = 0; i < WINCOVER_ACT_MAX; i++){
			image = CLACT_ImageProxyGet(sys->wincover_cap[i]->act);
			
			bgchar = &bgchar_vram[32 * (scrnbuf[k * 32] & 1023)];
			MI_CpuCopy16(bgchar, (void*)((u32)obj_vram 
				+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
			k++;

			bgchar = &bgchar_vram[32 * (scrnbuf[k * 32] & 1023)];
			MI_CpuCopy16(bgchar, (void*)((u32)obj_vram 
				+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN] + 0x20), 0x20);
			k++;
		}
	}
	
	//�X�N���[���Ŏg�p���Ă���p���b�g��ǂݎ����OBJ�p���b�g�փR�s�[����
	{
		int palno;
		
		palno = (*scrnbuf) >> 12;
		PaletteWorkCopy(sys->pfd, FADE_MAIN_BG, palno * 16, 
			FADE_MAIN_OBJ, obj_palno * 16, 0x20);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�B���h�E�A�X���C�h���̃J�o�[OBJ�폜
 * @param   sys		���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_TalkWinSlideCoverOBJDelete(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	CATS_RES_PTR crp;
	
	crp = sys->crp;
	
	//�A�N�^�[�폜
	for(i = 0; i < WINCOVER_ACT_MAX; i++){
		CATS_ActorPointerDelete_S(sys->wincover_cap[i]);
		sys->wincover_cap[i] = NULL;
	}
	
	//���\�[�X�폜
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_0);
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_1);
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_2);
	CATS_FreeResourcePltt(crp, PLTTID_WIN_COVER);
	CATS_FreeResourceCell(crp, CELLID_WIN_COVER);
	CATS_FreeResourceCellAnm(crp, CELLANMID_WIN_COVER);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�B���h�E�̃X�N���[�����X���C�h�p�ɕ`��
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   write_type		TALKWIN_SCREEN_WRITE_???
 */
//--------------------------------------------------------------
void AT_TalkWinScreenWrite(ACTIN_SYSTEM_PARAM *sys, int write_type)
{
	u16 *scrnbuf_before, *scrnbuf_after, *scrnbuf;
	int i;
	
	scrnbuf = GF_BGL_ScreenAdrsGet(sys->bgl, ACTIN_FRAME_WIN);
	scrnbuf_before = &scrnbuf[WINSLIDE_SCRN_POS_BEFORE];
	scrnbuf_after = &scrnbuf[WINSLIDE_SCRN_POS_AFTER];
	
	if(write_type == TALKWIN_SCREEN_WRITE_BEFORE){
		for(i = 0; i < 6; i++){
			scrnbuf_before[i * 32] = scrnbuf_before[i * 32 - 1];
		}
	}
	else{
		for(i = 0; i < 6; i++){
			scrnbuf_before[i * 32] = scrnbuf_after[i * 32];
		}
	}
	
	GF_BGL_LoadScreenV_Req(sys->bgl, ACTIN_FRAME_WIN);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�B���h�E�X���C�h����^�X�N�𐶐�����
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 * @param   slide_dir		�X���C�h����(TALKWIN_SLIDE_DIR_???)
 * @param   end_flag		�X���C�h�̏I����m�点�郏�[�N�ւ̃|�C���^(�I����TRUE���Z�b�g����܂�)
 */
//--------------------------------------------------------------
void AT_TalkWinSlideTaskSet(ACTIN_SYSTEM_PARAM *sys, u8 slide_dir, u8 *end_flag)
{
	TALKWIN_SLIDE_WORK *tsw;
	
	*end_flag = FALSE;

	tsw = sys_AllocMemory(HEAPID_ACTIN, sizeof(TALKWIN_SLIDE_WORK));
	MI_CpuClear8(tsw, sizeof(TALKWIN_SLIDE_WORK));
	
	tsw->sys = sys;
	tsw->slide_dir = slide_dir;
	tsw->end_flag = end_flag;
	
	tsw->x = GF_BGL_ScrollGetX(sys->bgl, ACTIN_FRAME_WIN) << 8;
	
	AT_TalkWinSlideCoverOBJSet(sys);
	
	if(slide_dir == TALKWIN_SLIDE_DIR_OUT){
		AT_TalkWinScreenWrite(sys, TALKWIN_SCREEN_WRITE_BEFORE);
	}
	
	TCB_Add(TalkWinSlideInOutMain, tsw, TCBPRI_ACTIN_TALKWIN_SLIDE);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�B���h�E�X���C�h����^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		TALKWIN_SLIDE_WORK�\����
 */
//--------------------------------------------------------------
static void TalkWinSlideInOutMain(TCB_PTR tcb, void *work)
{
	TALKWIN_SLIDE_WORK *tsw = work;
	
	switch(tsw->seq){
	case 0:
		if(tsw->slide_dir == TALKWIN_SLIDE_DIR_OUT){
			tsw->x += TALKWIN_SLIDE_SPEED;
			if((tsw->x >> 8) >= TALKWIN_SLIDE_DOT_LEN){
				tsw->x = TALKWIN_SLIDE_DOT_LEN << 8;
				tsw->seq++;
			}
		}
		else{
			tsw->x -= TALKWIN_SLIDE_SPEED;
			if(tsw->x <= (FRAME_WIN_DEFAULT_X << 8)){
				tsw->x = FRAME_WIN_DEFAULT_X << 8;
				tsw->seq++;
			}
		}
		GF_BGL_ScrollReq(tsw->sys->bgl, ACTIN_FRAME_WIN, GF_BGL_SCROLL_X_SET, tsw->x >> 8);
		break;
	default:
		if(tsw->slide_dir == TALKWIN_SLIDE_DIR_IN){
			AT_TalkWinScreenWrite(tsw->sys, TALKWIN_SCREEN_WRITE_AFTER);
		}
		AT_TalkWinSlideCoverOBJDelete(tsw->sys);
		*(tsw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l���̏�ɏ�������Ă���OBJ�ɑ΂��āA������OBJ���[�h���Z�b�g����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   on_off		�m�[�}���FGX_OAM_MODE_NORMAL�A�������FGX_OAM_MODE_XLU
 * @param   enable		TRUE:�\���B�@FALSE:��\��
 */
//--------------------------------------------------------------
static void AT_PanelObjBrdModeSet(ACTIN_PROC_WORK *apw, GXOamMode obj_mode, int enable)
{
	int i, k;
	int cap_enable, fontoam_enable;
	
	if(enable == TRUE){
		cap_enable = CATS_ENABLE_TRUE;
		fontoam_enable = TRUE;
	}
	else{
		cap_enable = CATS_ENABLE_FALSE;
		fontoam_enable = FALSE;
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		//�A�s�[���|�C���g
		for(k = 0; k < APPEAL_POINT_ICON_MAX; k++){
			if(apw->sys.appeal_point_cap[i][k] != NULL){
				CATS_ObjectObjModeSetCap(apw->sys.appeal_point_cap[i][k], obj_mode);
				CATS_ObjectEnableCap(apw->sys.appeal_point_cap[i][k], cap_enable);
			}
		}
		//���A�C�R��
		if(apw->sys.nexticon_cap[i] != NULL){
			CATS_ObjectObjModeSetCap(apw->sys.nexticon_cap[i], obj_mode);
			CATS_ObjectEnableCap(apw->sys.nexticon_cap[i], cap_enable);
		}
		//�j�b�N�l�[���ƃu���[�_�[��
		FONTOAM_ObjModeSet(apw->sys.fontact_oya[i].fontoam, obj_mode);
		FONTOAM_ObjModeSet(apw->sys.fontact_nickname[i].fontoam, obj_mode);
		FONTOAM_SetDrawFlag(apw->sys.fontact_oya[i].fontoam, fontoam_enable);
		FONTOAM_SetDrawFlag(apw->sys.fontact_nickname[i].fontoam, fontoam_enable);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l�����G�t�F�N�g�����s����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   eff_type	�G�t�F�N�g�^�C�v(BRDPANEL_ALPHA_TYPE_???)
 * @param   end_flag	�G�t�F�N�g�̏I����m�点�郏�[�N�ւ̃|�C���^(�I����TRUE���Z�b�g����܂�)
 */
//--------------------------------------------------------------
void AT_BrdPanelAlphaEffectSet(ACTIN_PROC_WORK *apw, int eff_type, u8 *end_flag)
{
	BRDPANEL_ALPHA_WORK *baw;
	
	*end_flag = FALSE;
	
	baw = sys_AllocMemory(HEAPID_ACTIN, sizeof(BRDPANEL_ALPHA_WORK));
	MI_CpuClear8(baw, sizeof(BRDPANEL_ALPHA_WORK));
	
	baw->apw = apw;
	baw->eff_type = eff_type;
	baw->end_flag = end_flag;
	
	TCB_Add(BrdPanelAlphaEffMain, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l�����G�t�F�N�g���C���^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BRDPANEL_ALPHA_WORK�\����
 */
//--------------------------------------------------------------
static void BrdPanelAlphaEffMain(TCB_PTR tcb, void *work)
{
	BRDPANEL_ALPHA_WORK *baw = work;
	
	switch(baw->seq){
	case 0:	//OBJ�̒��オ�������������Ώۂ̃u���[�_�[�p�l���ʂȂ̂ŁA�����ɔ����������
			//OBJ�̕����ςȈׁA�ʁX�ɔ������ŏ����Ă���
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
			baw->eva = 16 << 8;
			baw->evb = 0;
			G2_SetBlendAlpha(0, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 16, 0);
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_XLU, TRUE);
		}
		else{
			baw->eva = 0;
			baw->evb = 16 << 8;
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 0, 16);
			
			ActinBG_BrdPanelSet(baw->apw, EFF_BG_TYPE_BRDPANEL, TRUE);
		}
		
		VWaitTCB_Add(BrdPanelAlphaSet_VTask, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK);
		baw->seq++;
		break;
	case 1:
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE && baw->eva == 0){
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_NORMAL, FALSE);
			baw->seq++;
		}
		else if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETURN && baw->evb == 0){
			baw->seq++;
		}
		break;

	case 2:	//2�i�K��
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
			baw->eva = 16 << 8;
			baw->evb = 0;
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 16, 0);
		}
		else{
			baw->eva = 0;
			baw->evb = 16 << 8;
			G2_SetBlendAlpha(0, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, 0, 16);
			
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_XLU, TRUE);
		}
		
		VWaitTCB_Add(BrdPanelAlphaSet_VTask, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK);
		baw->seq++;
		break;
	case 3:
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE && baw->eva == 0){
			ActinBG_BrdPanelSet(baw->apw, EFF_BG_TYPE_EFFECT, TRUE);
			baw->seq++;
		}
		else if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETURN && baw->evb == 0){
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_NORMAL, TRUE);
			baw->seq++;
		}
		break;

	default:
		ActinExTool_DefaultBlendSet();
		
		*(baw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�p�l�����G�t�F�N�g��Vblank���]���^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BRDPANEL_ALPHA_WORK�\����
 */
//--------------------------------------------------------------
static void BrdPanelAlphaSet_VTask(TCB_PTR tcb, void *work)
{
	BRDPANEL_ALPHA_WORK *baw = work;
	int end = 0;
	
	if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
		baw->eva -= BRDPANEL_ALPHA_SP;
		baw->evb += BRDPANEL_ALPHA_SP;
		if(baw->eva <= 0){
			baw->eva = 0;
			end++;
		}
		if(baw->evb >= (16 << 8)){
			baw->evb = 16 << 8;
		}
	}
	else{
		baw->eva += BRDPANEL_ALPHA_SP;
		baw->evb -= BRDPANEL_ALPHA_SP;
		if(baw->eva >= (16 << 8)){
			baw->eva = 16 << 8;
			end++;
		}
		if(baw->evb <= 0){
			baw->evb = 0;
		}
	}
	
	G2_ChangeBlendAlpha(baw->eva >> 8, baw->evb >> 8);
	if(end > 0){
		TCB_Delete(tcb);
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�^�O�W�J
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
static void AT_MessageTagExpand(ACTIN_PROC_WORK *apw, int msg_tag, const ATAG_PARAM *tagpara,
	const void *extagpara)
{
	GF_ASSERT(msg_tag < ATAG_MINE || tagpara != NULL);	//ATAG_MINE�ȏ�̏ꍇ��tagpara�K�{
	
	if(tagpara != NULL){
		OS_TPrintf("mine=%d, enemy=%d, wazano=%d, num=%d, judge_no=%d\n",
			tagpara->mine_brd, tagpara->enemy_brd, tagpara->wazano, tagpara->num, 
			tagpara->judge_no);
	}

	switch(msg_tag){
	case ATAG_NONE:
		break;
	case ATAG_NOW:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[apw->advance.now_breeder]));
		break;

	case ATAG_MINE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_ENEMY:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_WAZA:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		break;
	case ATAG_NUM:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_JUDGE:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		break;
	case ATAG_MINE_ENEMY:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_MINE_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_MINE_NUM:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_MINE_JUDGE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterJudgeName(apw->sys.wordset, 1, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		break;

	case ATAG_ENEMY_MINE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_ENEMY_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_ENEMY_NUM:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_ENEMY_JUDGE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_WAZA_MINE:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_WAZA_ENEMY:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_WAZA_NUM:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_WAZA_JUDGE:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_NUM_MINE:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_NUM_ENEMY:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_NUM_WAZA:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_NUM_JUDGE:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_JUDGE_MINE:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_JUDGE_ENEMY:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_JUDGE_WAZA:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_JUDGE_NUM:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;

	case ATAG_MINE_JUDGE_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterJudgeName(apw->sys.wordset, 1, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterWazaName(apw->sys.wordset, 2, tagpara->wazano);
		break;
	
	case ATAG_EXCODE_JUDGESUFFER:
		{
			const JUDGE_SUFFER_REVIEW *jsr = extagpara;
			int i;
			
			WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
				apw->sys.c_game->jd[jsr->judge_no].name_id);
			for(i = 0; i < BREEDER_MAX; i++){
				if(jsr->suffer_breeder[i] == BREEDER_MAX){
					break;
				}
				WORDSET_RegisterPokeNickName(apw->sys.wordset, 1 + i, 
					PPPPointerGet(apw->sys.c_game->pp[jsr->suffer_breeder[i]]));
			}
		}
		break;
		
	default:
		GF_ASSERT(0 && "�F���ł��Ȃ��^�O�ł�\n");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�E�B���h�E���N���A����
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_TalkMessageWinClear(ACTIN_PROC_WORK *apw)
{
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_TALK], 0xff);
	GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_TALK]);
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�Z�b�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   msg_id		���b�Z�[�WID
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 * @param   extagpara	�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 * @param   all_put		TRUE:���b�Z�[�W�ꊇ�\��
 */
//--------------------------------------------------------------
static void AT_TalkMessageSet(ACTIN_PROC_WORK *apw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const ATAG_PARAM *tagpara, const void *extagpara, int all_put)
{
	STRBUF *message_src;
	u32 wait;
	
//	BattleMSG_TagExpand(bw,mp);
//	BattleMSG_MsgExpand(bw,msg_m,mp);

	if(all_put == TRUE){
		wait = MSG_ALLPUT;
	}
	else{
		if(apw->consys->sio_flag == FALSE){
			wait = CONFIG_GetMsgPrintSpeed(apw->consys->config);
		}
		else{
			wait = CONTEST_SIO_MSG_SPEED;
		}
	}
	
	message_src = MSGMAN_AllocString(msg_man, msg_id);
	AT_MessageTagExpand(apw, msg_tag, tagpara, extagpara);
	WORDSET_ExpandStr(apw->sys.wordset, apw->sys.msg_buf, message_src);
	
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_TALK], 0xff);
	apw->sys.talk_msg_index = GF_STR_PrintSimple(&apw->sys.win[ACTIN_BMPWIN_TALK], 
		FONT_TALK, apw->sys.msg_buf, 0, 0, wait, NULL);
	if(wait == MSG_ALLPUT){
		apw->sys.talk_msg_index = 0xff;
		GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_TALK]);
	}
	
	if(GF_BGL_ScrollGetX(apw->sys.bgl, ACTIN_FRAME_WIN) == FRAME_WIN_DEFAULT_X){
		//GF_BGL_BmpWinDataFill�Řg�܂œh��Ԃ����̂ōĕ`��
//		AT_TalkWinScreenWrite(&apw->sys, TALKWIN_SCREEN_WRITE_AFTER);
	}
	
	STRBUF_Delete(message_src);
}

//--------------------------------------------------------------
/**
 * @brief   �m�[�}����b�p�̃��b�Z�[�W�Z�b�g
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
void AT_A_TalkMessageSet(ACTIN_PROC_WORK *apw, u32 a_talk_id, const ATAG_PARAM *tagpara,
	const void *extagpara)
{
	u32 msg_id, msg_tag, all_put;
	
	GF_ASSERT(a_talk_id < NELEMS(ActinTalkMsgData));
	
	msg_id = ActinTalkMsgData[a_talk_id].msg_id;
	msg_tag = ActinTalkMsgData[a_talk_id].msg_tag;
	all_put = ActinTalkMsgData[a_talk_id].all_put;
	AT_TalkMessageSet(apw, apw->sys.actin_msg, msg_id, msg_tag, tagpara, extagpara, all_put);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʗp�̉�b���b�Z�[�W�Z�b�g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   apno		�A�s�[���ԍ�
 * @param   msg_type	���b�Z�[�W�^�C�v(KOUKA_MSGID_???)
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
void AT_WazaKoukaTalkMessageSet(ACTIN_PROC_WORK *apw, int apno, int msg_type, 
	const ATAG_PARAM *tagpara, const void *extagpara)
{
	u32 msg_id, msg_tag;
	
	ConTool_GetKoukaMsgID(apno, msg_type, &msg_id, &msg_tag);
	AT_TalkMessageSet(apw, apw->sys.wazakouka_msg, msg_id, msg_tag, tagpara, extagpara, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�t�H���g���\���������Ă��邩�`�F�b�N
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @retval  0=�I��
 */
//--------------------------------------------------------------
int AT_TalkMessageEndCheck(ACTIN_PROC_WORK *apw)
{
	if(apw->sys.talk_msg_index == 0xff){
		return 0;	//�ꊇ�\��
	}
	return GF_MSG_PrintEndCheck(apw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[���̃t�H���gOAM�𐶐�����
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamCreate(ACTIN_PROC_WORK *apw, int breeder_no)
{
//	STRBUF *oyaname_buf;
	STRBUF *nickname_buf;
	GF_PRINTCOLOR color;
	
	nickname_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_ACTIN);
//	oyaname_buf = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_ACTIN);

	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_nickname_buf, nickname_buf);
//	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_oyaname_buf, oyaname_buf);

	if(breeder_no == apw->consys->c_game.my_breeder_no){
		color = MSGCOLOR_BREEDERPARAM_MINE;
	}
	else{
		color = MSGCOLOR_BREEDERPARAM;
	}
	
	ADV_FontOamCreate(HEAPID_ACTIN, apw->sys.bgl, apw->sys.crp, apw->sys.fontoam_sys,
		&apw->sys.fontact_nickname[breeder_no], nickname_buf, 
		FONT_SYSTEM, color, 0, PLTTID_FONTACT, 
		0, 0, FALSE, ACTIN_BGPRI_BREEDER_PARAM, ACTIN_SOFTPRI_BREEDER_PARAM);
	ADV_FontOamCreate(HEAPID_ACTIN, apw->sys.bgl, apw->sys.crp, apw->sys.fontoam_sys,
		&apw->sys.fontact_oya[breeder_no], 
		apw->consys->c_game.breeder_name_str[breeder_no],//oyaname_buf, 
		FONT_SYSTEM, color, 0, PLTTID_FONTACT, 
		0, 0, FALSE, ACTIN_BGPRI_BREEDER_PARAM, ACTIN_SOFTPRI_BREEDER_PARAM);

	STRBUF_Delete(nickname_buf);
//	STRBUF_Delete(oyaname_buf);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[���̃t�H���gOAM��S�Đ�������
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamCreateAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		AT_BreederPanelFontOamCreate(apw, i);
	}
	AT_BreederPanelFontOamPosUpdate(apw);
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[���̃t�H���gOAM��S�č폜����
 * @param   sys		�_���X�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamDeleteAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		ADV_FontOamDelete(&apw->sys.fontact_nickname[i]);
		ADV_FontOamDelete(&apw->sys.fontact_oya[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[���̃t�H���gOAM�̍��W���u���[�_�[�\�[�g�ɍ��킹�čX�V����
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamPosUpdate(ACTIN_PROC_WORK *apw)
{
	int pos, breeder_no;
	
	for(pos = 0; pos < BREEDER_MAX; pos++){
		breeder_no = apw->a_game.breeder_sort[pos];
		ADV_FontOamPosSet(&apw->sys.fontact_nickname[breeder_no], 
			BREEDER_PANEL_NICK_X, BREEDER_PANEL_NICK_Y + BREEDER_PANEL_NICK_Y_SPACE * pos,
			FALSE);
		ADV_FontOamPosSet(&apw->sys.fontact_oya[breeder_no], 
			BREEDER_PANEL_OYA_X, BREEDER_PANEL_OYA_Y + BREEDER_PANEL_OYA_Y_SPACE * pos, 
			FALSE);
	}
}


//--------------------------------------------------------------
/**
 * @brief   ���A�C�R���̃��\�[�X���[�h����
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_NextIconResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		NEXT_ICON_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_NEXT_ICON);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, NEXT_ICON_NCER_BIN, 1, CELLID_NEXT_ICON);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, NEXT_ICON_NANR_BIN, 
		1, CELLANMID_NEXT_ICON);
}

//--------------------------------------------------------------
/**
 * @brief   ���A�C�R���̃��\�[�X���������
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_NextIconResourceFree(CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, CHARID_NEXT_ICON);
	CATS_FreeResourceCell(crp, CELLID_NEXT_ICON);
	CATS_FreeResourceCellAnm(crp, CELLANMID_NEXT_ICON);
}

//--------------------------------------------------------------
/**
 * @brief   ���A�C�R���̃A�N�^�[�����ƃA�j���ݒ���s��
 *
 * @param   sys				���Z�̓V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_pos		�\��������u���[�_�[�ʒu
 * @param   next_pos		���̃^�[�����ԖځA�ƕ\�������邩
 *
 * ����breeder_pos�̈ʒu�ɃA�N�^�[����������Ă���ꍇ�̓A�j���̐ݒ肾���s���܂�
 */
//--------------------------------------------------------------
void AT_NextIconActorAnimeSet(ACTIN_SYSTEM_PARAM *sys, int breeder_pos, int next_pos)
{
	//�A�N�^�[����������Ă��Ȃ��ꍇ�͐���
	if(sys->nexticon_cap[breeder_pos] == NULL){
		sys->nexticon_cap[breeder_pos] = CATS_ObjectAdd_S(sys->csp, sys->crp, &NextIconObjParam);
	}
	
	//�A�j���ݒ�
	CATS_ObjectAnimeSeqSetCap(sys->nexticon_cap[breeder_pos], next_pos);
	
	//���W�ݒ�
	CATS_ObjectPosSetCap(sys->nexticon_cap[breeder_pos], 
		NEXT_ICON_POS_X, NEXT_ICON_POS_Y + breeder_pos * NEXT_ICON_POS_Y_SPACE);

	CATS_ObjectUpdate(sys->nexticon_cap[breeder_pos]->act);
}

//--------------------------------------------------------------
/**
 * @brief   ���ݏ�ɏo�Ă��鎟�A�C�R���A�N�^�[��S�č폜
 *
 * @param   sys				���Z�̓V�X�e���\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_NextIconActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(sys->nexticon_cap[i] != NULL){
			CATS_ActorPointerDelete_S(sys->nexticon_cap[i]);
			sys->nexticon_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�^�O�W�J�p�����[�^�Ɋe�u���[�_�[���̏����l�f�[�^���Z�b�g����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   tagpara			�^�O�p�����[�^�����
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void AT_MsgTagParaInitDataSet(ACTIN_PROC_WORK *apw, ATAG_PARAM *tagpara, int breeder_no)
{
	MI_CpuClear8(tagpara, sizeof(ATAG_PARAM));
	tagpara->mine_brd = breeder_no;
	tagpara->wazano = apw->a_game.waza_no[breeder_no];
	tagpara->judge_no = apw->a_game.judge_no[breeder_no];
}

//--------------------------------------------------------------
/**
 * @brief   ���vAP�l����R���̃R�����g���x���̃��b�Z�[�WID�ƃ^�O���擾����
 *
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   app_total		���vAP
 * @param   tagpara			�^�O�����
 *
 * @retval  A_TALK_???
 */
//--------------------------------------------------------------
u32 AT_MsgTagJudgeCommentCreate(int breeder_no, int app_total, ATAG_PARAM *tagpara)
{
	int a_talk_id;
	
	tagpara->mine_brd = breeder_no;
	if(app_total <= JUDGE_COMMENT_LEVEL_0){
		a_talk_id = A_TALK_TURN_RESULT_0;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_1){
		a_talk_id = A_TALK_TURN_RESULT_1;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_2){
		a_talk_id = A_TALK_TURN_RESULT_2;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_3){
		a_talk_id = A_TALK_TURN_RESULT_3;
	}
	else{
		a_talk_id = A_TALK_TURN_RESULT_4;
	}
	return a_talk_id;
}

//--------------------------------------------------------------
/**
 * @brief   ���݂܂ł̓��_����ϋq�̊����̃{�����[�����擾����
 * @param   app_total		���݂܂ł̓��_
 * @retval  �����̃{�����[��
 */
//--------------------------------------------------------------
int AT_AudienceVolumeGet(int app_total)
{
	int volume_level;
	int volume;
	
	volume_level = app_total / AUDIENCE_VOLUME_LEVEL_POINT;
	if(volume_level >= AUDIENCE_VOLUME_LEVEL_MAX){
		volume_level = AUDIENCE_VOLUME_LEVEL_MAX - 1;
	}
	
	volume = AudienceVolume[volume_level];
	GF_ASSERT(volume >= 0);
	GF_ASSERT(volume <= 127);
	return volume;
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�A�j�������s����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   voltage			�{���e�[�W�l
 * @param   start_wait		�J�n�E�F�C�g
 * @param   se_volume		����SE�̃{�����[��
 * @param   fade			TRUE:�t�F�[�h���s��
 * @param   end_flag		�G�t�F�N�g�I�����ɁA�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AT_AudienceAnimeSet(ACTIN_PROC_WORK *apw, int voltage, u8 start_wait, int se_volume, int fade,
	u8 *end_flag)
{
	AUDIENCE_ANIME_WORK *aaw;
	
	*end_flag = FALSE;
	
	aaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(AUDIENCE_ANIME_WORK));
	MI_CpuClear8(aaw, sizeof(AUDIENCE_ANIME_WORK));
	aaw->apw = apw;
	aaw->end_flag = end_flag;
	aaw->start_wait = start_wait;
	aaw->voltage = voltage;
	aaw->se_volume = se_volume;
	aaw->fade = fade;
	TCB_Add(AudienceAnimeMain, aaw, TCBPRI_ACTIN_AUDIENCE_ANIME);
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�A�j�����s�^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AUDIENCE_ANIME_WORK�\����
 */
//--------------------------------------------------------------
static void AudienceAnimeMain(TCB_PTR tcb, void *work)
{
	AUDIENCE_ANIME_WORK *aaw = work;
	
	switch(aaw->seq){
	case 0:
		if(aaw->start_wait > 0){
			aaw->start_wait--;
			break;
		}
		Snd_SePlay(ASE_AUDIENCE);
		Snd_PlayerSetInitialVolumeBySeqNo(ASE_AUDIENCE, aaw->se_volume);
		aaw->seq++;
		//break;
	case 1:
		{
			u32 scr_id;
			
			if(aaw->anm_no == 0){
				scr_id = CON_BG2_NSCR_BIN;
			}
			else{
				scr_id = CON_BG_NSCR_BIN;
			}
			ArcUtil_ScrnSet(ARC_CONTEST_BG, scr_id, aaw->apw->sys.bgl, 
				ACTIN_FRAME_AUDIENCE, 0, 0, 1, HEAPID_ACTIN);
		}
		
		aaw->seq++;
		break;
	case 2:
		aaw->wait++;
		if(aaw->wait > AUDIENCE_ANIME_WAIT){
			aaw->wait = 0;
			aaw->anm_no ^= 1;
			aaw->seq--;
			
			if(aaw->anm_no == 0){
				aaw->loop++;
				if(aaw->loop > AUDIENCE_ANIME_LOOP){
					aaw->seq = 0xff;
					break;
				}
			}
		}
		
		if(aaw->fade == TRUE){
			int evy_max;
			evy_max = aaw->voltage * AUDIENCE_FADE_MAX_EVY / VOLTAGE_POINT_FULL;
			if(aaw->evy < evy_max){
				aaw->evy += AUDIENCE_FADE_ADD_EVY;
				if(aaw->evy > evy_max){
					aaw->evy = evy_max;
				}
				SoftFadePfd(aaw->apw->sys.pfd, FADE_MAIN_BG, AUDIENCE_FADE_COLOR_POS, 
					AUDIENCE_FADE_COLOR_NUM, aaw->evy, AUDIENCE_FADE_RGB);
			}
		}
		
		break;
	default:
		if(aaw->fade == TRUE){
			if(aaw->evy != 0){
				aaw->evy -= AUDIENCE_FADE_ADD_EVY;
				if(aaw->evy < 0){
					aaw->evy = 0;
				}
				SoftFadePfd(aaw->apw->sys.pfd, FADE_MAIN_BG, AUDIENCE_FADE_COLOR_POS, 
					AUDIENCE_FADE_COLOR_NUM, aaw->evy, AUDIENCE_FADE_RGB);
				break;
			}
		}

		*(aaw->end_flag) = TRUE;
		
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �e�u���[�_�[�p�l�����AP�n�[�g���p�l���ɋz�����܂�Ă����G�t�F�N�g���N������
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   breeder_pos		�u���[�_�[�ʒu
 * @param   effect_count	�G�t�F�N�g�J�E���^�ւ̃|�C���^
 * @param   panel_flash		�u���[�_�[�p�l���t���b�V�����샏�[�N�ւ̃|�C���^
 *
 * effect_count = �G�t�F�N�g����������閈�ɃC���N�������g����A�G�t�F�N�g���I�����邽�т�
 * �f�N�������g����܂��B���̊֐��ďo����A�G�t�F�N�g�J�E���^��0�ɂȂ�����S�ẴG�t�F�N�g��
 * �I�������A�Ɣ��肷�鎖���o���܂��B
 */
//--------------------------------------------------------------
void AT_APHeartMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, u8 *effect_count,
	PANEL_FLASH_WORK *panel_flash)
{
	APHEART_MOVE_WORK *heart_move;
	s32 center_x, center_y;
	s16 start_x, start_y, x, y;
	int i;
	u32 furihaba;
	u16 angle;
	
	*effect_count = 0;
	
	center_x = BREEDER_PANEL_DOT_LEN_X / 2;
	center_y = BREEDER_PANEL_DOT_LEN_Y / 2 + breeder_pos * BREEDER_PANEL_DOT_LEN_Y;
	
	furihaba = 0;
	angle = 0;
	
	for(i = 0; i < APPEAL_POINT_ICON_MAX; i++){
		if(apw->sys.appeal_point_cap[breeder_no][i] == NULL){
			continue;
		}
		
		if(*effect_count == 0){
			//�ӂ蕝�擾
			CATS_ObjectPosGetCap(apw->sys.appeal_point_cap[breeder_no][i], 
				&start_x, &start_y);
			furihaba = APP_StraightDistance(
				MATH_IAbs(start_x - center_x), MATH_IAbs(start_y - center_y)) * 0x100;

			//�p�x�擾
			{
				f32 len_x, len_start_y;
				len_x = start_x - center_x;
				len_start_y = start_y - center_y;
				angle = FX_Atan2Idx(FX_F32_TO_FX32(len_start_y), FX_F32_TO_FX32(len_x));
				//65535��MAX�̊p�x���A360�x*100�{�����p�x��MAX�̂��̂ɕϊ�����
				angle = (360*100) * angle / 65535;
			}
		}
		
		heart_move = sys_AllocMemory(HEAPID_ACTIN, sizeof(APHEART_MOVE_WORK));
		MI_CpuClear8(heart_move, sizeof(APHEART_MOVE_WORK));
		
		heart_move->panel_flash = panel_flash;
		
		heart_move->cap = apw->sys.appeal_point_cap[breeder_no][i];
		
		heart_move->furihaba = furihaba;
		heart_move->angle = angle;
		
		heart_move->add_angle = APHEART_ADD_ANGLE;
		heart_move->center_x = center_x;
		heart_move->center_y = center_y;
		heart_move->effect_count = effect_count;
		heart_move->start_x = start_x;
		heart_move->start_y = start_y;
		
		CATS_ObjectPosGetCap(apw->sys.appeal_point_cap[breeder_no][i], &x, &y);
		heart_move->slide_add_x = (MATH_IAbs(start_x - x) << 8) 
			/ (APHEART_START_WAIT * (*effect_count));
		heart_move->slide_x = x << 8;
		
		TCB_Add(APHeartMoveTask, heart_move, TCBPRI_ACTIN_EFFECT);
		
		(*effect_count)++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   AP�n�[�g��]�ړ��^�X�N���C��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		AP�n�[�g��]�ړ��p���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void APHeartMoveTask(TCB_PTR tcb, void *work)
{
	APHEART_MOVE_WORK *heart_move = work;
	int offset_x, offset_y, furihaba;
	s16 x, y;
	
	switch(heart_move->seq){
	case 0:		//�J�n�ʒu�܂ŃX���C�h�ړ�
		heart_move->slide_x -= heart_move->slide_add_x;
		if(heart_move->slide_x <= (heart_move->start_x << 8)){
			heart_move->slide_x = heart_move->start_x << 8;
			heart_move->seq++;
		}
		CATS_ObjectPosGetCap(heart_move->cap, &x, &y);
		x = heart_move->slide_x >> 8;
		CATS_ObjectPosSetCap(heart_move->cap, x, y);
		break;
		
	case 1:		//Sin�J�[�u
		heart_move->angle += heart_move->add_angle;
		heart_move->add_angle += APHEART_ADD_FRAME_ANGLE;
		if(heart_move->angle >= 360*100){
			heart_move->angle -= 360*100;
		}
		
		if(heart_move->furihaba > APHEART_SUB_FURIHABA){
			heart_move->furihaba -= APHEART_SUB_FURIHABA;
		}
		else{
			heart_move->furihaba = 0;
		}
		if(heart_move->furihaba <= APHEART_END_FURIHABA){
			heart_move->seq++;
		}
		furihaba = heart_move->furihaba / 0x100;
		offset_x = FX_Mul(Cos360(heart_move->angle / 100), furihaba << FX32_SHIFT) / FX32_ONE;
		offset_y = FX_Mul(Sin360(heart_move->angle / 100), furihaba << FX32_SHIFT) / FX32_ONE;
		CATS_ObjectPosSetCap(heart_move->cap, 
			heart_move->center_x + offset_x, heart_move->center_y + offset_y);
		break;

	default:
		CATS_ObjectEnableCap(heart_move->cap, CATS_ENABLE_FALSE);
		Snd_SePlay(ASE_APHEART_PANEL_IN);
		BreederPanel_FlashReqSet(heart_move->panel_flash);
		
		(*(heart_move->effect_count))--;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�̃A�j�����s�^�X�N�𐶐�����
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   judge_no		�R��NO
 *
 * @retval  ���������{���e�[�W�A�j�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
VOLTAGE_POINT_ANIME_WORK * AT_VoltageAnimeSet(ACTIN_PROC_WORK *apw, int judge_no)
{
	VOLTAGE_POINT_ANIME_WORK *vaw;
	
	vaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLTAGE_POINT_ANIME_WORK));
	MI_CpuClear8(vaw, sizeof(VOLTAGE_POINT_ANIME_WORK));
	
	vaw->apw = apw;
	vaw->judge_no = judge_no;
	
	vaw->tcb = TCB_Add(VoltageAnimeUpdateTask, vaw, TCBPRI_ACTIN_EFFECT);
	return vaw;
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�A�j���^�X�N���폜����
 * @param   vaw		�{���e�[�W�A�j�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
void AT_VoltageAnimeDel(VOLTAGE_POINT_ANIME_WORK *vaw)
{
	TCB_Delete(vaw->tcb);
	sys_FreeMemoryEz(vaw);
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�A�j�����s�^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�{���e�[�W�|�C���g�A�j�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VoltageAnimeUpdateTask(TCB_PTR tcb, void *work)
{
	VOLTAGE_POINT_ANIME_WORK *vaw = work;
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(vaw->apw->sys.voltage_point_cap[vaw->judge_no][i] == NULL){
			continue;
		}
		CATS_ObjectUpdateCap(vaw->apw->sys.voltage_point_cap[vaw->judge_no][i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�A�p�l���ړ��G�t�F�N�g�N��
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[No
 * @param   breeder_pos		�u���[�_�[�ʒu
 * @param   judge_no		�R��NO
 * @param   effect_count	�G�t�F�N�g�J�E���^�ւ̃|�C���^
 *
 * effect_count = �G�t�F�N�g����������閈�ɃC���N�������g����A�G�t�F�N�g���I�����邽�т�
 * �f�N�������g����܂��B���̊֐��ďo����A�G�t�F�N�g�J�E���^��0�ɂȂ�����S�ẴG�t�F�N�g��
 * �I�������A�Ɣ��肷�鎖���o���܂��B
 */
//--------------------------------------------------------------
void AT_VoltageMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, int judge_no, u8 *effect_count)
{
	VOLPANEL_MOVE_WORK *vol_move;
	int i;
	int center_x, center_y;
	
	*effect_count = 0;
	
	center_x = BREEDER_PANEL_DOT_LEN_X / 2;
	center_y = BREEDER_PANEL_DOT_LEN_Y / 2 + breeder_pos * BREEDER_PANEL_DOT_LEN_Y;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(apw->sys.voltage_point_cap[judge_no][i] == NULL){
			continue;
		}
		
		vol_move = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLPANEL_MOVE_WORK));
		MI_CpuClear8(vol_move, sizeof(VOLPANEL_MOVE_WORK));
		
		vol_move->apw = apw;
		vol_move->cap = apw->sys.voltage_point_cap[judge_no][i];
		vol_move->effect_count = effect_count;
		
		vol_move->center_x = center_x;
		vol_move->center_y = center_y;
		
		vol_move->wait = VOLMOVE_START_WAIT * (*effect_count);
		
		TCB_Add(VoltageMoveTask, vol_move, TCBPRI_ACTIN_EFFECT);
		
		(*effect_count)++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�|�C���g�A�p�l���ړ����s�^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�{���e�[�W�|�C���g�A�p�l���ړ��p���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VoltageMoveTask(TCB_PTR tcb, void *work)
{
	VOLPANEL_MOVE_WORK *vol_move = work;
	s16 x, y;
	int offset_x, offset_y;
	
	switch(vol_move->seq){
	case 0:
		if(vol_move->wait > 0){
			vol_move->wait--;
			break;
		}

		//��]�̊J�n�ʒu��Cos��MAX�ʒu�ɍ����悤�ɍ��W�␳
		CATS_ObjectPosGetCap(vol_move->cap, &x, &y);
		y += VOLMOVE_FURIHABA_Y >> FX32_SHIFT;
		vol_move->x = x << 8;
		vol_move->y = y << 8;
		
		Snd_SePlay(ASE_VOLTAGE_EFF_START);
		vol_move->seq++;
		//break;
	case 1:
		vol_move->angle += VOLMOVE_ADD_ANGLE;
		if(vol_move->angle >= 360*100){
			vol_move->angle -= 360*100;
		}
		offset_x = FX_Mul(Sin360(vol_move->angle / 100), VOLMOVE_FURIHABA_X) / FX32_ONE;
		offset_y = FX_Mul(Cos360(vol_move->angle / 100), VOLMOVE_FURIHABA_Y) / FX32_ONE;
		
		vol_move->y += VOLMOVE_DOWNMOVE_SP_Y;
		
		CATS_ObjectPosSetCap(vol_move->cap, (vol_move->x >> 8) + offset_x,
			(vol_move->y >> 8) + offset_y);
		
		vol_move->wait++;
		if(vol_move->wait > VOLMOVE_DOWNMOVE_FRAME){
			vol_move->wait = 0;
			CATS_ObjectPosGetCap(vol_move->cap, &x, &y);
			vol_move->x = x << 8;
			vol_move->y = y << 8;
			{//���i�ړ����x�擾
				s32 len_x, len_y, frame;
				
				len_x = (MATH_IAbs(x - vol_move->center_x) << 8);
				len_y = (MATH_IAbs(y - vol_move->center_y) << 8);
				frame = len_x / VOLMOVE_STRAIGHT_SP_X;
				vol_move->add_x = VOLMOVE_STRAIGHT_SP_X;
				vol_move->add_y = len_y / frame;
				if(vol_move->center_y < y){
					vol_move->add_y = -vol_move->add_y;
				}
			}
			Snd_SePlay(ASE_VOLTAGE_STRAIGHT_MOVE);
			vol_move->seq++;
		}
		break;
	case 2:
		vol_move->x -= vol_move->add_x;
		vol_move->y += vol_move->add_y;
		if(vol_move->x <= (vol_move->center_x << 8)){
			vol_move->x = vol_move->center_x << 8;
			vol_move->seq++;
		}
		CATS_ObjectPosSetCap(vol_move->cap, vol_move->x >> 8, vol_move->y >> 8);
		break;
	default:
		CATS_ObjectEnableCap(vol_move->cap, CATS_ENABLE_FALSE);
		Snd_SePlay(ASE_VOLTAGE_PANEL_IN);
		
		(*(vol_move->effect_count))--;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���J�n���ɕ\������A_Talk�p���b�Z�[�WID���擾����
 * @param   con_type		CONTYPE_???
 * @retval  A_TALK�p���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_Host01(int con_type)
{
	const u16 HostMsgID[] = {
		A_TALK_ACT_HOST_06,
		A_TALK_ACT_HOST_05,
		A_TALK_ACT_HOST_01,
		A_TALK_ACT_HOST_03,
		A_TALK_ACT_HOST_04,
	};
	
	return HostMsgID[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W�㏸���ɕ\������A_Talk�p���b�Z�[�WID���擾����
 * @param   waza_con_type		�Z��CONTYPE_???
 * @retval  A_TALK�p���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_VoltageUp(int waza_con_type)
{
	const u16 VoltageUpMsgID[] = {
		A_TALK_VOLTAGE_UP_2,
		A_TALK_VOLTAGE_UP_3,
		A_TALK_VOLTAGE_UP_4,
		A_TALK_VOLTAGE_UP_5,
		A_TALK_VOLTAGE_UP_6,
	};
	
	return VoltageUpMsgID[waza_con_type];
}

//--------------------------------------------------------------
/**
 * @brief   �{���e�[�W���~���ɕ\������A_Talk�p���b�Z�[�WID���擾����
 * @param   waza_con_type		�Z��CONTYPE_???
 * @retval  A_TALK�p���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_VoltageSub(int waza_con_type)
{
	const u16 VoltageDownMsgID[] = {
		A_TALK_VOLTAGE_SUB_10,
		A_TALK_VOLTAGE_SUB_2,
		A_TALK_VOLTAGE_SUB_3,
		A_TALK_VOLTAGE_SUB_4,
		A_TALK_VOLTAGE_SUB_5,
	};
	
	return VoltageDownMsgID[waza_con_type];
}

//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g�����ׂ̈̃p�����[�^�擾
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   wazano			�Z�ԍ�
 * @param   wazapara		�p�����[�^�����
 */
//--------------------------------------------------------------
void AT_WazaEffParamSet(CONTEST_SYSTEM *consys, int breeder_no, int wazano, 
	CON_WAZAEFF_PARAM *wazapara)
{
	MI_CpuClear8(wazapara, sizeof(CON_WAZAEFF_PARAM));
	
	wazapara->wazano = wazano;
	
	switch(wazano){
	case WAZANO_SOORAABIIMU:
	case WAZANO_KAMAITATI:
	case WAZANO_ROKETTOZUTUKI:
	case WAZANO_GODDOBAADO:
		wazapara->loop = 1;
		break;
	case WAZANO_ONGAESI:
		wazapara->natukido = 255;	//�З�Max��Ԃ̂��o��
		break;
	case WAZANO_YATUATARI:
		wazapara->natukido = 0;	//�З�Max��Ԃ̂��o��
		break;
	case WAZANO_NOROI:	//�̂낢
		{
			int type1, type2;
			
			type1 = PokeParaGet(consys->c_game.pp[breeder_no], ID_PARA_type1, NULL);
			type2 = PokeParaGet(consys->c_game.pp[breeder_no], ID_PARA_type2, NULL);
			if(type1 == GHOST_TYPE || type2 == GHOST_TYPE){
				wazapara->counter = 1;
			}
			else{
				wazapara->counter = 0;
			}
		}
		break;
	case WAZANO_OUMUGAESI:
		wazapara->wazano = WAZANO_HATAKU;
		break;
	case WAZANO_SIZENNOTIKARA:
		wazapara->wazano = WAZANO_TORAIATAKKU;
		break;
	case WAZANO_KAWARAWARI:
		wazapara->counter = 1;
		break;
	case WAZANO_SYADOODAIBU:
		wazapara->loop = 1;
		wazapara->waza_kouka = WAZAKOUKA_KIE;
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z�����̃^�[���I���o���邩�`�F�b�N(�A���g�p�̊m�F)
 *
 * @param   a_game			���Z�͕���Q�[�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   wazano			�`�F�b�N����Z�ԍ�
 *
 * @retval  TRUE:�Z�͏o����
 * @retval  FALSE:�o���Ȃ�
 */
//--------------------------------------------------------------
int AT_WazaConsecutiveCheck(ACTIN_GAME_PARAM *a_game, int breeder_no, int wazano)
{
	if(wazano == 0){
		return FALSE;
	}
	
	if((wazano == a_game->waza_history[breeder_no])
			&& (a_game->wazapara.save[breeder_no].waza_repeat != wazano)){
		return FALSE;
	}
	return TRUE;
}

