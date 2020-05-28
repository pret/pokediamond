//==============================================================================
/**
 * @file	temoti_gauge.c
 * @brief	�莝���Q�[�W
 * @author	matsuda
 * @date	2006.06.14(��)
 */
//==============================================================================
#include "common.h"
#include "graphic/batt_obj_def.h"
#include "system/arc_tool.h"
#include "battle/battle_id.h"
#include "battle/battle_tcb_pri.h"
#include "battle/fight_tool.h"
#include "temoti_gauge.h"
#include "battle_snd_def.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�莝���Q�[�W�̃A�j���V�[�P���X�ԍ�
enum{
	TGANM_BALL_ALIVE_ENEMY,		///<�|�P����������(�����Ă���)�F�G��
	TGANM_BALL_NG_ENEMY,		///<�|�P����������(�X�e�[�^�X�ُ�)�F�G��
	TGANM_BALL_DEAD_ENEMY,		///<�|�P����������(�C��)�F�G��
	TGANM_BALL_ALIVE_MINE,		///<�|�P����������(�����Ă���)�F���@��
	TGANM_BALL_NG_MINE,			///<�|�P����������(�X�e�[�^�X�ُ�)�F���@��
	TGANM_BALL_DEAD_MINE,		///<�|�P����������(�C��)�F���@��
	TGANM_BALL_NONE,			///<�|�P���������Ȃ�(���@�A�G����)
	TGANM_ARROW_ENEMY,			///<���(�G��)
	TGANM_ARROW_MINE,			///<���(���@��)
};

//--------------------------------------------------------------
//	���
//--------------------------------------------------------------
///���o��J�n���WX(���@��)
#define ARROW_MINE_START_X			(256 + 96)
///��󓞒����WX(���@��)
#define ARROW_MINE_END_X			(256 - 32)
///�����WY(���@��)
#define ARROW_MINE_Y				(128)

///���o��J�n���WX(�G��)
#define ARROW_ENEMY_START_X			(-96)
///��󓞒����WX(�G��)
#define ARROW_ENEMY_END_X			(32)
///�����WY(�G��)
#define ARROW_ENEMY_Y				(56)

///���IN���x(����8�r�b�g����)
#define ARROW_IN_SPEED				(0x0e00)
///���OUT���x(����8�r�b�g����)
#define ARROW_OUT_SPEED				(0x0400)

//--------------------------------------------------------------
//	�{�[��
//--------------------------------------------------------------
///�{�[���o��J�n���WX(���@��)
#define BALL_MINE_START_X			(256 + 20)
///�{�[���������WX(���@��)
#define BALL_MINE_END_X				(256 - 128 + 20 + 14)
///�{�[�����WY(���@��)
#define BALL_MINE_Y					(ARROW_MINE_Y - 6)

///�{�[���o��J�n���WX(�G��)
#define BALL_ENEMY_START_X			(-20)
///�{�[���������WX(�G��)
#define BALL_ENEMY_END_X			(128 - 20 - 14)
///�{�[�����WY(�G��)
#define BALL_ENEMY_Y				(ARROW_ENEMY_Y - 6)

///�{�[��IN���x(����8�r�b�g����)
#define BALL_IN_SPEED				(ARROW_IN_SPEED)
///�{�[��OUT���x(����8�r�b�g����)
#define BALL_OUT_SPEED				(0x0c00)

///�G���J�E���gIN���A1�ڂ̃{�[����IN�J�n����܂ł̃E�F�C�g
#define BALL_ENCOUNT_FAST_IN_WAIT	(5)
///�G���J�E���gIN���A�{�[������̓����n�߂�܂ł̃E�F�C�g
#define BALL_ENCOUNT_IN_WAIT		(3)
///�{�[�������X���W�z�u�Ԋu
#define BALL_SPACE_X				(16)
///�{�[�����G���J�E���gIN���A�l�܂�����ԂɂȂ鎞��X���W�z�u�Ԋu
#define BALL_OVER_SPACE_X				(15)
///�{�[�����G���J�E���gIN���A�l�܂�����ԂɂȂ鎞��X���W�I�t�Z�b�g���W
#define BALL_OVER_LEN				(6)

///�{�[����]���x(���@��)
#define BALL_MINE_ROTATION		(-0x2800)
///�{�[����]���x(�G��)
#define BALL_ENEMY_ROTATION		(-BALL_MINE_ROTATION)

///�{�[���̃R�����̓�����n�߂�܂ł̃E�F�C�g
#define BALL_KORON_WAIT			(0)
///�{�[���̃R�����̓���̎��̈ړ����x(����8�r�b�g����)
#define BALL_KORON_SPEED		(0x0600)
///�R��������O�̎΂ߌ����Œ�~���Ă���A�j���̃t���[���ԍ�(���@��)
#define BALL_NANAME_ANM_FRAME_MINE	(1)
///�R��������O�̎΂ߌ����Œ�~���Ă���A�j���̃t���[���ԍ�(�G��)
#define BALL_NANAME_ANM_FRAME_ENEMY	(1)

//--------------------------------------------------------------
//	������
//--------------------------------------------------------------
///���������x(����8�r�b�g����)
#define ARROW_ALPHA_OUT_SP			(0x0100)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�G���J�E���g�A�E�g�̎��A�J�X�^���{�[���̃��[�h�œ������K�N�K�N�ɂȂ�̂ŁA�����n�߂�܂�
///�����E�F�C�g������(�J�X�^���{�[���̃��[�h���I������瓮���n�߂邮�炢�ɂ��Ă���)
#define ARROW_SCROLL_OUT_START_WAIT		(4)
#define BALL_OUT_ENCOUNT_START_WAIT		(ARROW_SCROLL_OUT_START_WAIT)


//==============================================================================
//	�\���̒�`
//==============================================================================
///��󃏁[�N
typedef struct{
	CATS_ACT_PTR cap;
	TCB_PTR tcb;
	ARROW_OUT_TYPE out_type;
	TEMOTI_SIDE side;
	BALL_POS_TYPE pos_type;
	s32 x;			///<X���W(����8�r�b�g����)
	s16 alpha;		///<�����������W�X�^�l(����8�r�b�g����)
	u8 seq;
	u8 start_wait;
}TG_ARROW_WORK;

///�{�[�����[�N
typedef struct{
	CATS_ACT_PTR cap;
	TCB_PTR tcb;
	TEMOTI_SIDE side;
	BALL_POS_TYPE pos_type;
	BALL_OUT_TYPE out_type;
	s8 *in_count;
	s16 *arrow_alpha;		///<��󂪊Ǘ����Ă��锼���������W�X�^�l�ւ̃|�C���^
	s32 x;
	s32 end_x;
	s32 over_end_x;
	s16 wait;
	u16 se_id;
	u8 seq;
	u8 pos;
	u8 flip_anmseq;
	u8 start_wait;
}TG_BALL_WORK;

///�莝���Q�[�W���[�N
typedef struct _TEMOTIGAUGE_WORK{
	TG_ARROW_WORK	arrow;
	TG_BALL_WORK	ball[POKEMON_TEMOTI_MAX];
	s8 in_count;
}TEMOTIGAUGE_WORK;


//==============================================================================
//	�f�[�^
//==============================================================================
///�莝���Q�[�W���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S TemotiGaugeArrowObjParam = {
	0, 0, 0,		//x, y, z
	0, 10, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_TEMOTI_GAUGE,	//�L����
		PLTTID_TEMOTI_GAUGE,	//�p���b�g
		CELLID_TEMOTI_GAUGE,	//�Z��
		CELLANMID_TEMOTI_GAUGE,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	0,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�莝���Q�[�W�{�[���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S TemotiGaugeBallObjParam = {
	0, 0, 0,		//x, y, z
	0, 8, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_TEMOTI_GAUGE,	//�L����
		PLTTID_TEMOTI_GAUGE,	//�p���b�g
		CELLID_TEMOTI_GAUGE,	//�Z��
		CELLANMID_TEMOTI_GAUGE,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	0,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};


//==============================================================================
//	�f�[�^
//==============================================================================
///���@�����ʒuY
ALIGN4 static const u16 ArrowMinePosY[] = {
	ARROW_MINE_Y - 36,		//BALL_POS_HIGH
	ARROW_MINE_Y,			//BALL_POS_MIDDLE
	ARROW_MINE_Y,			//BALL_POS_LOW
};

///�G�����ʒuY
ALIGN4 static const u16 ArrowEnemyPosY[] = {
	ARROW_ENEMY_Y - 36,		//BALL_POS_HIGH
	ARROW_ENEMY_Y,			//BALL_POS_MIDDLE
	ARROW_ENEMY_Y,			//BALL_POS_LOW
};

///���@���{�[���ʒuY
ALIGN4 static const u16 BallMinePosY[] = {
	BALL_MINE_Y - 36,		//BALL_POS_HIGH
	BALL_MINE_Y,			//BALL_POS_MIDDLE
	BALL_MINE_Y,			//BALL_POS_LOW
};

///�G���{�[���ʒuY
ALIGN4 static const u16 BallEnemyPosY[] = {
	BALL_ENEMY_Y - 36,		//BALL_POS_HIGH
	BALL_ENEMY_Y,			//BALL_POS_MIDDLE
	BALL_ENEMY_Y,			//BALL_POS_LOW
};


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void TEMOTI_ArrowIn(TG_ARROW_WORK *arrow, TEMOTI_SIDE side, BALL_POS_TYPE pos_type,
	CATS_SYS_PTR csp, CATS_RES_PTR crp);
static void TEMOTI_ArrowOut(TG_ARROW_WORK *arrow, ARROW_OUT_TYPE out_type);
static void TEMOTI_BallIn(TG_BALL_WORK *ball, s8 *in_count, TEMOTI_SIDE side, 
	BALL_IN_TYPE ball_in_type, BALL_POS_TYPE pos_type,
	int pos, int anmseq, CATS_SYS_PTR csp, CATS_RES_PTR crp);
static void TEMOTI_BallOut(TG_BALL_WORK *ball, int pos, BALL_OUT_TYPE out_type, s16 *alpha);
static void ArrowTask_In(TCB_PTR tcb, void *work);
static void ArrowTask_Out(TCB_PTR tcb, void *work);
static void BallTask_EncountIn(TCB_PTR tcb, void *work);
static void BallTask_ChangeIn(TCB_PTR tcb, void *work);
static void BallTask_EncountOut(TCB_PTR tcb, void *work);
static void BallTask_ChangeOut(TCB_PTR tcb, void *work);
static int BallStatusAnimeSeqGet(int status, TEMOTI_SIDE side);
static int BallStatusFlipAnimeSeqGet(int anm_seq);
static TEMOTIGAUGE_PTR TEMOTI_SystemWorkAlloc(void);
static void TEMOTI_SystemWorkFree(TEMOTIGAUGE_PTR tb);



//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�W�̃��\�[�X�����[�h����
 *
 * @param   csp			
 * @param   crp			
 * @param   pfd			
 */
//--------------------------------------------------------------
void TEMOTI_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAUGE_M_BALL_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_TEMOTI_GAUGE);
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_TEMOTI_GAUGE);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NCER_BIN, 1, CELLID_TEMOTI_GAUGE);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NANR_BIN, 1, CELLANMID_TEMOTI_GAUGE);
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�W�̃��\�[�X���������
 *
 * @param   crp			
 */
//--------------------------------------------------------------
void TEMOTI_ResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_TEMOTI_GAUGE);
	CATS_FreeResourcePltt(crp, PLTTID_TEMOTI_GAUGE);
	CATS_FreeResourceCell(crp, CELLID_TEMOTI_GAUGE);
	CATS_FreeResourceCellAnm(crp, CELLANMID_TEMOTI_GAUGE);
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�W���[�N��Alloc����
 *
 * @retval  �莝���Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static TEMOTIGAUGE_PTR TEMOTI_SystemWorkAlloc(void)
{
	TEMOTIGAUGE_WORK *tg;
	
	tg = sys_AllocMemory(HEAPID_BATTLE, sizeof(TEMOTIGAUGE_WORK));
	MI_CpuClear8(tg, sizeof(TEMOTIGAUGE_WORK));
	return tg;
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�W���[�N��Free����
 *
 * @param   tb		�莝���Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void TEMOTI_SystemWorkFree(TEMOTIGAUGE_PTR tb)
{
	GF_ASSERT(tb->arrow.tcb == NULL);
	
	sys_FreeMemoryEz(tb);
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�WIN�G�t�F�N�g���N������
 *
 * @param   status[]	�|�P�����̃X�e�[�^�X���(POKEMON_TEMOTI_MAX���̔z��)
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 *
 * @retval  �莝���Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
TEMOTIGAUGE_PTR TEMOTI_InEffectSet(u8 status[], TEMOTI_SIDE side, BALL_IN_TYPE ball_in_type,
	BALL_POS_TYPE pos_type, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	TEMOTIGAUGE_PTR tg;
	int i, anmseq;
	
	tg = TEMOTI_SystemWorkAlloc();
	TEMOTI_ArrowIn(&tg->arrow, side, pos_type, csp, crp);
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		anmseq = BallStatusAnimeSeqGet(status[i], side);
		TEMOTI_BallIn(&tg->ball[i], &tg->in_count, side, ball_in_type, pos_type,
			i, anmseq, csp, crp);
	}
	return tg;
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�WIN�G�t�F�N�g�̏I���m�F
 *
 * @param   tg		�莝���Q�[�W���[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�I���A�@FALSE:�G�t�F�N�g��
 */
//--------------------------------------------------------------
BOOL TEMOTI_InEffectEndCheck(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	if(tg->arrow.tcb == NULL){
		for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
			if(tg->ball[i].tcb != NULL){
				break;
			}
		}
		if(i == POKEMON_TEMOTI_MAX){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�WOUT�G�t�F�N�g���N������
 *
 * @p
 * @param   status[]	�|�P�����̃X�e�[�^�X���(POKEMON_TEMOTI_MAX���̔z��)
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 *
 * @retval  �莝���Q�[�W���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void TEMOTI_OutEffectSet(TEMOTIGAUGE_PTR tg, 
	ARROW_OUT_TYPE arrow_out_type, BALL_OUT_TYPE ball_out_type)
{
	int i;
	
	GF_ASSERT(tg != NULL);
	
	TEMOTI_ArrowOut(&tg->arrow, arrow_out_type);
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		TEMOTI_BallOut(&tg->ball[i], i, ball_out_type, &tg->arrow.alpha);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�WIN�G�t�F�N�g�̏I���m�F
 *
 * @param   tg		�莝���Q�[�W���[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�I���A�@FALSE:�G�t�F�N�g��
 */
//--------------------------------------------------------------
BOOL TEMOTI_OutEffectEndCheck(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	if(tg->arrow.tcb == NULL){
		for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
			if(tg->ball[i].tcb != NULL){
				break;
			}
		}
		if(i == POKEMON_TEMOTI_MAX){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �莝���Q�[�W�̃G�t�F�N�g�������
 *
 * @param   tg		�莝���Q�[�W���[�N�ւ̃|�C���^
 *
 * �A�N�^�[�̍폜�A�莝���Q�[�W���[�N���g�̉�����s���܂�
 */
//--------------------------------------------------------------
void TEMOTI_EffectFree(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	CATS_ActorPointerDelete_S(tg->arrow.cap);
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		CATS_ActorPointerDelete_S(tg->ball[i].cap);
	}
	
	TEMOTI_SystemWorkFree(tg);
}


//==============================================================================
//
//	���o��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���o��G�t�F�N�g���N������
 *
 * @param   arrow			��󃏁[�N�ւ̃|�C���^
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 */
//--------------------------------------------------------------
static void TEMOTI_ArrowIn(TG_ARROW_WORK *arrow, TEMOTI_SIDE side, BALL_POS_TYPE pos_type,
	CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	GF_ASSERT(arrow->cap == NULL && arrow->tcb == NULL);
	
	MI_CpuClear8(arrow, sizeof(TG_ARROW_WORK));
	
	//�A�N�^�[����
	arrow->cap = CATS_ObjectAdd_S(csp, crp, &TemotiGaugeArrowObjParam);
	if(side == TEMOTI_MINE){
		CATS_ObjectPosSetCap(arrow->cap, ARROW_MINE_START_X, ArrowMinePosY[pos_type]);
		CLACT_AnmChg(arrow->cap->act, TGANM_ARROW_MINE);
	}
	else{
		CATS_ObjectPosSetCap(arrow->cap, ARROW_ENEMY_START_X, ArrowEnemyPosY[pos_type]);
		CLACT_AnmChg(arrow->cap->act, TGANM_ARROW_ENEMY);
	}
	CATS_ObjectUpdate(arrow->cap->act);

	//���[�N�ݒ�
	arrow->side = side;
	arrow->pos_type = pos_type;
	
	//�^�X�N����
	arrow->seq = 0;
	arrow->tcb = TCB_Add(ArrowTask_In, arrow, TCBPRI_TEMOTIGAUGE_ARROW);
	
	Snd_SePlay(BSE_TB_START);
}

//--------------------------------------------------------------
/**
 * @brief   ��󓮍�^�X�N�F���IN
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ArrowTask_In(TCB_PTR tcb, void *work)
{
	TG_ARROW_WORK *arrow = work;
	
	switch(arrow->seq){
	case 0:	//���[�N������
		{
			s16 x, y;
			CATS_ObjectPosGetCap(arrow->cap, &x, &y);
			arrow->x = x << 8;
		}
		arrow->seq++;
		//break;
	case 1:
		if(arrow->side == TEMOTI_MINE){
			arrow->x -= ARROW_IN_SPEED;
			if(arrow->x <= ARROW_MINE_END_X << 8){
				arrow->x = ARROW_MINE_END_X << 8;
				arrow->seq++;
			}
			CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowMinePosY[arrow->pos_type]);
		}
		else{
			arrow->x += ARROW_IN_SPEED;
			if(arrow->x >= ARROW_ENEMY_END_X << 8){
				arrow->x = ARROW_ENEMY_END_X << 8;
				arrow->seq++;
			}
			CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowEnemyPosY[arrow->pos_type]);
		}
		break;
	default:
		TCB_Delete(tcb);
		arrow->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	���ޏ�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ޏ�G�t�F�N�g���N������
 *
 * @param   arrow			��󃏁[�N�ւ̃|�C���^
 * @param   out_type		�ޏꓮ��w��
 */
//--------------------------------------------------------------
static void TEMOTI_ArrowOut(TG_ARROW_WORK *arrow, ARROW_OUT_TYPE out_type)
{
	GF_ASSERT(arrow->cap != NULL && arrow->tcb == NULL);
	
	//�^�X�N����
	arrow->seq = 0;
	arrow->out_type = out_type;
	if(out_type == ARROW_OUT_TYPE_SCROLL){
		arrow->start_wait = ARROW_SCROLL_OUT_START_WAIT;
	}
	else{
		arrow->start_wait = 0;
	}
	arrow->tcb = TCB_Add(ArrowTask_Out, arrow, TCBPRI_TEMOTIGAUGE_ARROW);
}

//--------------------------------------------------------------
/**
 * @brief   ��󓮍�^�X�N�F���OUT
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ArrowTask_Out(TCB_PTR tcb, void *work)
{
	TG_ARROW_WORK *arrow = work;
	
	switch(arrow->seq){
	case 0:	//���[�N������
		{
			s16 x, y;
			CATS_ObjectPosGetCap(arrow->cap, &x, &y);
			arrow->x = x << 8;
		}

		CATS_ObjectObjModeSetCap(arrow->cap, GX_OAM_MODE_XLU);	//������OBJ���[�h

		//���������W�X�^�ݒ�
		arrow->alpha = 16 << 8;
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, 
			GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 
			| GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD,
			(arrow->alpha >> 8), 16 - (arrow->alpha >> 8));

		arrow->seq++;
		//break;
	case 1:
		if(arrow->start_wait > 0){
			arrow->start_wait--;
			break;
		}
		arrow->seq++;
		//break;
	case 2:
		if(arrow->out_type == ARROW_OUT_TYPE_SCROLL){
			if(arrow->side == TEMOTI_MINE){
				arrow->x -= ARROW_OUT_SPEED;
				CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowMinePosY[arrow->pos_type]);
			}
			else{
				arrow->x += ARROW_OUT_SPEED;
				CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowEnemyPosY[arrow->pos_type]);
			}
		}
		
		//������
		arrow->alpha -= ARROW_ALPHA_OUT_SP;
		if(arrow->alpha <= 0){
			arrow->alpha = 0;
			CATS_ObjectEnable(arrow->cap->act, CATS_ENABLE_FALSE);
			arrow->seq++;
		}
		G2_ChangeBlendAlpha(arrow->alpha >> 8, 16 - (arrow->alpha >> 8));
		break;
	default:
		BattleDefaultBlendSet();
		
		TCB_Delete(tcb);
		arrow->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	�{�[���o��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �{�[���o��G�t�F�N�g���N������
 *
 * @param   arrow			��󃏁[�N�ւ̃|�C���^
 * @param   in_count		�{�[���S�Ăŋ��ʂŎg�p����J�E���^���[�N�ւ̃|�C���^
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 * @param   ball_in_type	�{�[���o�ꓮ��^�C�v
 * @param   pos				���ڂ̃{�[����
 * @param   anmseq			�A�j���V�[�P���X�ԍ�
 */
//--------------------------------------------------------------
static void TEMOTI_BallIn(TG_BALL_WORK *ball, s8 *in_count, TEMOTI_SIDE side, 
	BALL_IN_TYPE ball_in_type, BALL_POS_TYPE pos_type,
	int pos, int anmseq, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	GF_ASSERT(ball->cap == NULL && ball->tcb == NULL);
	
	MI_CpuClear8(ball, sizeof(TG_BALL_WORK));
	
	//�A�N�^�[����
	ball->cap = CATS_ObjectAdd_S(csp, crp, &TemotiGaugeBallObjParam);
	if(side == TEMOTI_MINE){
		CATS_ObjectPosSetCap(ball->cap, BALL_MINE_START_X, BallMinePosY[pos_type]);
	}
	else{
		CATS_ObjectPosSetCap(ball->cap, BALL_ENEMY_START_X, BallEnemyPosY[pos_type]);
	}
	CLACT_AnmChg(ball->cap->act, anmseq);
//	CATS_ObjectAffineSetCap(ball->cap, CLACT_AFFINE_NORMAL);
	CATS_ObjectUpdate(ball->cap->act);

	//���[�N�ݒ�
	ball->side = side;
	ball->pos = pos;
	ball->pos_type = pos_type;
	ball->flip_anmseq = BallStatusFlipAnimeSeqGet(anmseq);
	ball->in_count = in_count;
	ball->se_id = (anmseq == TGANM_BALL_NONE ? BSE_TB_KARA : BSE_TB_KON);
	
	if(side == TEMOTI_MINE){
		ball->end_x = BALL_MINE_END_X + pos * BALL_SPACE_X;
		ball->over_end_x = BALL_MINE_END_X + pos * BALL_OVER_SPACE_X - BALL_OVER_LEN;
	}
	else{
		ball->end_x = BALL_ENEMY_END_X - pos * BALL_SPACE_X;
		ball->over_end_x = BALL_ENEMY_END_X - pos * BALL_OVER_SPACE_X + BALL_OVER_LEN;
	}
	
	//�^�X�N����
	ball->seq = 0;
	if(ball_in_type == BALL_IN_TYPE_ENCOUNT){
		ball->wait = BALL_ENCOUNT_IN_WAIT * pos + BALL_ENCOUNT_FAST_IN_WAIT;
		ball->tcb = TCB_Add(BallTask_EncountIn, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
	else{
		ball->wait = 0;//BALL_ENCOUNT_IN_WAIT * pos;
		ball->tcb = TCB_Add(BallTask_ChangeIn, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{�[������^�X�N�F�G���J�E���g���̉��IN
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BallTask_EncountIn(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	switch(ball->seq){
	case 0:	//���[�N������
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		ball->seq++;
		//break;
	case 1:
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_IN_SPEED;
			if(ball->x <= ball->over_end_x << 8){
				ball->x = ball->over_end_x << 8;
				Snd_SePlay(ball->se_id);
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_IN_SPEED;
			if(ball->x >= ball->over_end_x << 8){
				ball->x = ball->over_end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	case 3:
//		if(ball->side == TEMOTI_MINE){
//			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_MINE);
//		}
//		else{
//			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_ENEMY);
//		}
		
		(*(ball->in_count))++;
		ball->seq++;
		//break;
	case 4:
		if(*(ball->in_count) != POKEMON_TEMOTI_MAX){
			CATS_ObjectUpdate(ball->cap->act);
			break;
		}

		if(ball->side == TEMOTI_MINE){
			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_MINE);
		}
		else{
			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_ENEMY);
		}
		ball->wait = 0;
		ball->seq++;
		//break;
	case 5:
		ball->wait++;
		if(ball->wait < BALL_KORON_WAIT){
			break;
		}
		CLACT_AnmChg(ball->cap->act, ball->flip_anmseq);
		ball->wait = 0;
		ball->seq++;
		//break;
	case 6:
		if(ball->side == TEMOTI_MINE){
			ball->x += BALL_KORON_SPEED;
			if(ball->x >= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x -= BALL_KORON_SPEED;
			if(ball->x <= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	default:
		//CLACT_AnmChg(ball->cap->act, anmseq);
		CLACT_AnmFrameSet(ball->cap->act, 0);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{�[������^�X�N�F����ւ����̉��IN
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BallTask_ChangeIn(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	switch(ball->seq){
	case 0:	//���[�N������
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		CLACT_AnmFrameSet(ball->cap->act, 0);
		ball->seq++;
		//break;
	case 1:
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_IN_SPEED;
			if(ball->x <= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_IN_SPEED;
			if(ball->x >= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		break;
	default:
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	�{�[���ޏ�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �{�[���ޏ�G�t�F�N�g���N������
 *
 * @param   ball			��󃏁[�N�ւ̃|�C���^
 * @param   pos				�{�[���莝���ʒu
 * @param   out_type		�ޏꓮ��w��
 * @param   alpha			��󂪊Ǘ����Ă��锼�������W�X�^�l�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void TEMOTI_BallOut(TG_BALL_WORK *ball, int pos, BALL_OUT_TYPE out_type, s16 *alpha)
{
	GF_ASSERT(ball->cap != NULL && ball->tcb == NULL);
	
	//�^�X�N����
	ball->seq = 0;
	if(out_type == BALL_OUT_TYPE_ENCOUNT){
		ball->arrow_alpha = alpha;
		ball->wait = BALL_ENCOUNT_IN_WAIT * pos;
		ball->start_wait = BALL_OUT_ENCOUNT_START_WAIT;
		ball->tcb = TCB_Add(BallTask_EncountOut, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
	else{
		ball->arrow_alpha = alpha;
		ball->wait = 0;
		ball->start_wait = 0;
		ball->tcb = TCB_Add(BallTask_ChangeOut, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{�[������^�X�N�F���OUT
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BallTask_EncountOut(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	if((*(ball->arrow_alpha)) == 0){
		ball->seq = 100;	//�I����
	}
	
	switch(ball->seq){
	case 0:	//���[�N������
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		CATS_ObjectObjModeSetCap(ball->cap, GX_OAM_MODE_XLU);	//������OBJ���[�h
		ball->seq++;
		//break;
	case 1:
		if(ball->start_wait > 0){
			ball->start_wait--;
			break;
		}
		
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_OUT_SPEED;
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_OUT_SPEED;
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		
		if(ball->x < -16*0x100 || ball->x > ((256+16) << 8)){
			ball->seq++;
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	case 100:
	default:
		CATS_ObjectEnable(ball->cap->act, CATS_ENABLE_FALSE);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �{�[������^�X�N�F���OUT(����ւ���)
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		��󃏁[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BallTask_ChangeOut(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	if((*(ball->arrow_alpha)) == 0){
		ball->seq = 100;	//�I����
	}
	
	switch(ball->seq){
	case 0:	//���[�N������
		CATS_ObjectObjModeSetCap(ball->cap, GX_OAM_MODE_XLU);	//������OBJ���[�h
		ball->seq++;
		//break;
	case 1:		//�������I���҂�
		break;
	case 100:
	default:
		CATS_ObjectEnable(ball->cap->act, CATS_ENABLE_FALSE);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �X�e�[�^�X��񂩂�A�{�[���̃A�j���V�[�P���X�ԍ����擾����
 * @param   status		�X�e�[�^�X���
 * @retval  �A�j���V�[�P���X�ԍ�
 */
//--------------------------------------------------------------
static int BallStatusAnimeSeqGet(int status, TEMOTI_SIDE side)
{
	int anm_seq;
	
	switch(status){
	case COMSEL_STATUS_NONE:
	default:
		anm_seq = TGANM_BALL_NONE;
		break;
	case COMSEL_STATUS_ALIVE:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_ALIVE_MINE : TGANM_BALL_ALIVE_ENEMY;
		break;
	case COMSEL_STATUS_DEAD:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_DEAD_MINE : TGANM_BALL_DEAD_ENEMY;
		break;
	case COMSEL_STATUS_NG:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_NG_MINE : TGANM_BALL_NG_ENEMY;
		break;
	}
	return anm_seq;
}

//--------------------------------------------------------------
/**
 * @brief   �{�[���̃A�j���V�[�P���X����A���΍Đ��̃A�j���V�[�P���X�ԍ����擾����
 * @param   anm_seq		�A�j���V�[�P���X
 * @retval  ���΍Đ��̃A�j���V�[�P���X
 */
//--------------------------------------------------------------
static int BallStatusFlipAnimeSeqGet(int anm_seq)
{
	switch(anm_seq){
	case TGANM_BALL_NONE:
	default:
		return anm_seq;
	
	case TGANM_BALL_ALIVE_MINE:
		return TGANM_BALL_ALIVE_ENEMY;
	case TGANM_BALL_ALIVE_ENEMY:
		return TGANM_BALL_ALIVE_MINE;
	
	case TGANM_BALL_DEAD_MINE:
		return TGANM_BALL_DEAD_ENEMY;
	case TGANM_BALL_DEAD_ENEMY:
		return TGANM_BALL_DEAD_MINE;
	
	case TGANM_BALL_NG_MINE:
		return TGANM_BALL_NG_ENEMY;
	case TGANM_BALL_NG_ENEMY:
		return TGANM_BALL_NG_MINE;
	}
}

