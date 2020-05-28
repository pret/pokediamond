
//============================================================================================
/**
 * @file	fight_def.h
 * @bfief	�퓬���C���v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include	"battle/battle_common.h"
#include	"poketool/poke_tool.h"
#include	"../src/poketool/poke_tool_def.h"
#include	"battle/server.h"
#include	"battle/client.h"
#include	"system/softsprite.h"
#include	"wazaeffect/we_mana.h"
#include	"system/clact_tool.h"
#include	"battle/ground.h"
#include	"battle/battle_input.h"
#include "system/numfont.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/palanm.h"
#include "system/gra_tool.h"
#include "vs_demo.h"
#include "field/tvtopic_battle.h"		//TVWATCH_BATTLE_WORK
#include "battle/temoti_gauge.h"
#include "gflib/vram_transfer_manager.h"

#ifndef __FIGHT_DEF_H_
#define __FIGHT_DEF_H_

typedef struct _MYSTATUS MYSTATUS;
typedef struct _MYITEM MYITEM;
typedef struct _POKEPARTY POKEPARTY;
typedef struct _ZUKAN_WORK ZUKAN_WORK;
typedef struct _BOX_DATA BOX_DATA;
typedef struct PERAPVOICE PERAPVOICE;
typedef struct _CONFIG CONFIG;
typedef struct _POKETCH_DATA POKETCH_DATA;

///<�퓬�p���[�N�\���̐錾
struct battle_work
{
	GF_G3DMAN			*g3Dman;					///<3D�ʏ������}�l�[�W���[�̃|�C���^
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	MSGDATA_MANAGER		*fight_msg;					///<�퓬���b�Z�[�W�p���b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^
	MSGDATA_MANAGER		*attack_msg;				///<�퓬���b�Z�[�W�p���b�Z�[�W�f�[�^�}�l�[�W���̃|�C���^�i�A�^�b�N���b�Z�[�W�j
	WORDSET				*wordset;					///<�퓬���b�Z�[�W�p�P��o�b�t�@
	STRBUF				*msg_buf;					///<���b�Z�[�W�p�Ɋm�ۂ������[�N�ւ̃|�C���^
	TCB_PTR				update_tcb;
	TCB_PTR				pinch_tcb;					///<�s���`SE�̐���^�X�N
	TCB_PTR				msgwinmove_tcb;				///<�ŏ��̉��o�p(BG1�ʁi���b�Z�[�W�ʁj����ɃX�N���[��������j
	PALETTE_FADE_PTR	pfd;						///<�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
	u32					fight_type;
	SERVER_PARAM		*server_param;
	CLIENT_PARAM		*client_param[CLIENT_MAX];
	int					client_set_max;
	MYSTATUS			*my_status[CLIENT_MAX];		///<�v���[���[���
	MYITEM				*my_item;					///<�莝���A�C�e�����
	BAG_CURSOR			*bag_cursor;				///<�o�b�O�̃J�[�\���f�[�^
	ZUKAN_WORK			*zw;						///<�}�Ӄ��[�N
	BOX_DATA			*box;						///<�{�b�N�X�f�[�^
	POKEPARTY			*poke_party[CLIENT_MAX];	///<�莝���|�P�����̍\����
	PERAPVOICE			*poke_voice[CLIENT_MAX];	///<�|�P�����̖����f�[�^
	SOFT_SPRITE_MANAGER	*soft_sprite;
	WE_SYS_PTR			wsp;
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	POKETCH_DATA		*poketch_data;				///<�|�P�b�`�f�[�^
	TVWATCH_BATTLE_WORK * TVWatchBattleWork;		///<�e���r�F�ߊl�ԑg�p
	u16					trainer_id[CLIENT_MAX];
	u8					trainer_sex[CLIENT_MAX];
	TRAINER_DATA		trainer_data[CLIENT_MAX];	///<�g���[�i�[�f�[�^
	GROUND_WORK			ground[GROUND_MAX];			///<�n�ʃ��[�N(���@�� + �G��)
	BI_PARAM_PTR		bip;						///<�퓬���͉�ʃV�X�e�����[�N�ւ̃|�C���^
	TEMOTIGAUGE_PTR		tg[TEMOTIGAUGE_MAX];		///<�莝���Q�[�W���[�N�ւ̃|�C���^
	NUMFONT				*numfont_hp;				///<8x8�t�H���g(HP�p)
	NUMFONT				*numfont_lv;				///<8x8�t�H���g(���x���p)
	void				*msg_icon;					///<���b�Z�[�W�E�C���h�E��DS�A�C�R���p�|�C���^
	CONFIG				*config;					///<�Q�[���R���t�B�O
	FRIEND_LIST			*friendlist;				///<�Ƃ������O���[�v�f�[�^
	void				*time_icon;					///<�ʐM�ҋ@���̎��v�A�C�R���^�X�N
	

	VS_DEMO_DATA		*vdd;						///<�ΐ�J�n�O�f���p���[�N�ւ̃|�C���^
	POKE_ANM_SYS_PTR	pasp;						///<�|�P�����v���O�����A�j���V�X�e�����[�N�ւ̃|�C���^
	NNSG2dCellTransferState	*cell_trans;			///<�Z���]���}�l�[�W��
	

	EXCHR_PARAM			exchr_param[CLIENT_MAX];	///<�Z�G�t�F�N�g�p�|�P�����L�����W�J�p�����[�^

	BATTLE_TOWER_RECORD	btr;						///<�o�g���^���[���їp���[�N

	RECORD				*record;					///<�J�E���g�A�b�v�p���[�N

	u8					*bg_area;					///<�w�i�O���t�B�b�N�ޔ�̈�i�L�����j
	u16					*pal_area;					///<�w�i�O���t�B�b�N�ޔ�̈�i�p���b�g�j

	u8					sio_send_buffer[BATTLE_SIO_BUF_SIZE];	///<�ʐM���M�o�b�t�@
	u8					sio_recv_buffer[BATTLE_SIO_BUF_SIZE];	///<�ʐM��M�o�b�t�@

	u16					push_bg_palette[0x10*7];	///<BG�p���b�g�ޔ�̈�
	u16					push_obj_palette[0x10*7];	///<OBJ�p���b�g�ޔ�̈�

	u16					sio_send_read;				///<�ʐM���M�o�b�t�@�ǂݍ��݈ʒu
	u16					sio_send_write;				///<�ʐM���M�o�b�t�@�������݈ʒu

	u16					sio_send_over;				///<�ʐM���M�o�b�t�@�������ݎ��ɃI�[�o�[�����Ƃ��̃��[�N
	u16					sio_recv_read;				///<�ʐM��M�o�b�t�@�ǂݍ��݈ʒu

	u16					sio_recv_write;				///<�ʐM��M�o�b�t�@�������݈ʒu
	u16					sio_recv_over;				///<�ʐM��M�o�b�t�@�������ݎ��ɃI�[�o�[�����Ƃ��̃��[�N

	u8					*tcb_sio_send_seq_no;		///<�ʐM���MTCB�̃V�[�P���X�i���o�[�ւ̃|�C���^
	u8					*tcb_sio_recv_seq_no;		///<�ʐM��MTCB�̃V�[�P���X�i���o�[�ւ̃|�C���^

	u8					server_flag;				///<�T�[�o���N�����Ă��邩�t���O
	u8					proc_mode;					///<�퓬�V�X�e���̓��샂�[�h
	u8					fight_end_flag;				///<�퓬�I���t���O
	u8					bld_init_req		:1;		///<�u�����h�ݒ菉�����v���t���O
	u8					vram_init_req		:1;		///<VRAM�ݒ菉�����v���t���O
	u8					bl_vram_init_req	:1;		///<VRAM�ݒ菉�����v���t���O�i�o�b�O�����X�g��ʁj
	u8					pinch_se_flag		:2;		///<�s���`SE�t���O
	u8					pinch_se_wait		:3;		///<�s���`SE�E�G�C�g

	int					ground_id;					///<�n�`ID
	int					bg_id;						///<�w�iID
	int					place_id;					///<�n�於ID
	u32					battle_status_flag;			///<�퓬���ʃt���O
	int					time_zone;					///<���ԑ�

	int					safari_ball;				///<�T�t�@���{�[���̐�

	u8					appear_flag[CLIENT_MAX];	///<�J��o�����|�P������SelMonsNo���r�b�g�Ŋi�[

	u32					regulation_flag;			///<���M�����[�V�����t���O

	u8					win_lose_flag;				///<���s�t���O
	u8					demo_seq_no;				///<�ߊl�f���p�V�[�P���X�i���o�[
	u16					ball_count;					///<�{�[���𓊂�����

	int					shinka_place_mode;			///<�ꏊ�i�����iSHINKA_PLACE�`�j	
	int					contest_see_flag;			///<�R���e�X�g���������ǂ����̃t���O
	int					weather;					///<�t�B�[���h�V��
	int					mizuki_flag;				///<�~�Y�L�ɂ��������ǂ����̃t���O
	u32					seed_temp;					///<�����̎�̑ޔ����[�N
	int					bg1_scroll;					///<BG1Y�X�N���[���p���[�N
	int					get_pokemon_client;			///<�ߊl�����|�P������ClientNo

	int					command_select_flag;		///<�R�}���h�Z���N�g�Ń{�^���̃X���C�h�C���̏I�����ŗ��Ƃ��t���O

	u8					no_reshuffle_client;		///<����ւ��ł��Ȃ�ClientNo���r�b�g�ŊǗ��i�ʐM�p�j
	u8					dummy[3];
};

#endif __FIGHT_DEF_H_
