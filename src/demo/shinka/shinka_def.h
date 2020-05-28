
#include	"system/softsprite.h"
#include	"battle/battle_common.h"
#include	"system/particle.h"
#include	"application/p_status.h"

// -----------------------------------------
//
//	���p�[�e�B�N���o�^�p���[�N
//
// -----------------------------------------
typedef struct {
	
	int heap_id;
	
	int spa_id;
//	int	spr_id;
	
} SHINKA_PARTICLE_PARAM;


// -----------------------------------------
//
//	���p�[�e�B�N���Ǘ�
//
// -----------------------------------------
typedef struct  {
	
	SHINKA_PARTICLE_PARAM	param;
	
	EMIT_PTR			emit;
	PTC_PTR				ptc;
	
} SHINKA_PARTICLE_SYS;


///<�i���f���p���[�N�\���̐錾
struct shinka_work
{
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	MSGDATA_MANAGER		*msg_man;
	WORDSET				*wordset;					///<�퓬���b�Z�[�W�p�P��o�b�t�@
	STRBUF				*msg_buf;					///<���b�Z�[�W�p�Ɋm�ۂ������[�N�ւ̃|�C���^
	PALETTE_FADE_PTR	pfd;						///<�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
	SOFT_SPRITE_MANAGER	*ssm;
	SOFT_SPRITE			*ss[2];
	POKEPARTY			*ppt;
	POKEMON_PARAM		*pp;
	CONFIG				*config;
	SHINKA_PARTICLE_SYS	*shinka_pt;
	GF_G3DMAN			*g3Dman;
	PROC				*proc;
	PSTATUS_DATA		*psd;
	void				*work_p;
	POKE_ANM_SYS_PTR	pasp;
	ZUKAN_WORK			*zw;
	MYITEM				*my_item;
	RECORD				*record;
	POKETCH_DATA		*poketch_data;
	void				*msg_icon;
	int					heapID;
	u16					before_mons_no;
	u16					after_mons_no;
	u8					seq_no;
	u8					msg_index;
	u8					wait;
	u8					end_flag;

	int					waza_cnt;					///<�Z�o���e�[�u���̃C���f�b�N�X

	u16					waza_no;					///<�o����Z�i���o�[
	u8					waza_pos;					///<�Z��Y��鎞�̃|�W�V����
	u8					dummy;

	u8					morph_flag;
	u8					morph_speed;
	
	u8					wx1;
	u8					wy1;
	u8					wx2;
	u8					wy2;

	int					shinka_cond;
	int					shinka_status_flag;
};
