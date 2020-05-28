//==============================================================================
/**
 * @file	res_tool.c
 * @brief	���ʔ��\��ʃc�[����
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "msgdata/msg.naix"

#include "con_result.h"
#include "con_tool.h"
#include "res_tool.h"
#include "res_id.h"
#include "res_tcb_pri.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/fontoam.h"
#include "msgdata/msg_con_tally.h"

#include "adv_tool.h"

#include "system/window.h"
#include "poketool/pokeicon.h"

#include "visual.h"
#include "visual_tool.h"
#include "savedata/config.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�E�B���h�E���J���ő�h�b�g��
#define WNDOPEN_EFF_OPEN_Y_DOT		(12*8)
///�E�B���h�E���J�����x(����8�r�b�g����)
#define WNDOPEN_EFF_ADD_Y			(0x0400)

///�|�P�����X���C�h�F�ړ����xX(����8�r�b�g����)
#define POKESLIDE_ADD_X		(0x0800)

///���ӂԂ�����������
#define CONFETTI_INIT_CREATE_NUM	(8)
///���ӂԂ����������ő吔
#define CONFETTI_CREATE_MAX		(48)
///���ӂԂ������Ԋu
#define CONFETTI_CREATE_WAIT	(6)

///���ӂԂ��F�����J�n���WY
#define CONFETTI_START_Y		(-16)	//(192/2 - WNDOPEN_EFF_OPEN_Y_DOT/2 - 16)
///���ӂԂ��F�����J�n���WY�����_���l
#define CONFETTI_START_Y_RND	(96-32)
///���ӂԂ��F�I�����WY
#define CONFETTI_END_Y			(192+16)	//(192/2 + WNDOPEN_EFF_OPEN_Y_DOT/2 + 16)
///���ӂԂ��FX�����Œ�ړ����x(����8�r�b�g����)
#define CONFETTI_ADD_X			(0x0030)
///���ӂԂ��FX���������_���ړ����x
#define CONFETTI_RND_X			(0x0100)
///���ӂԂ��FY�����ړ����x
#define CONFETTI_ADD_Y			(0x0200)
///���ӂԂ��FSin�J�[�u�Œ�p�x���Z�l(����8�r�b�g����)
#define CONFETTI_ADD_ANGLE		(0x0000)
///���ӂԂ��FSin�J�[�u�p�x���Z�����_���l
#define CONFETTI_RND_ANGLE		(0x0300)
///���ӂԂ��FSin�J�[�u�ӂ蕝
#define CONFETTI_FURIHABA_X		(16)
///���ӂԂ��FSin�J�[�u�ӂ蕝�����_���l
#define CONFETTI_FURIHABA_X_RND	(24)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�A�N�e�B�u���[�h�v�Z�䗦(����100�{�A�ȉ�����)�F�r�W���A��
#define CONRESULT_GAME_PERCENT_ACTIVE_VISUAL	(70 * 100)
///�A�N�e�B�u���[�h�v�Z�䗦(����100�{�A�ȉ�����)�F�_���X
#define CONRESULT_GAME_PERCENT_ACTIVE_DANCE		(30 * 100)

///�`���[�����[�h�v�Z�䗦(����100�{�A�ȉ�����)�F�r�W���A��
#define CONRESULT_GAME_PERCENT_CHARM_VISUAL		(60 * 100)
///�`���[�����[�h�v�Z�䗦(����100�{�A�ȉ�����)�F���Z
#define CONRESULT_GAME_PERCENT_CHARM_ACTIN		(40 * 100)

///�O�����h���[�h�v�Z�䗦(����100�{�A�ȉ�����)�F�r�W���A��
#define CONRESULT_GAME_PERCENT_GRAND_VISUAL		(3333)	//(50 * 100)
///�O�����h���[�h�v�Z�䗦(����100�{�A�ȉ�����)�F�_���X
#define CONRESULT_GAME_PERCENT_GRAND_DANCE		(3333)	//(20 * 100)
///�O�����h���[�h�v�Z�䗦(����100�{�A�ȉ�����)�F���Z
#define CONRESULT_GAME_PERCENT_GRAND_ACTIN		(3333)	//(30 * 100)


//==============================================================================
//	�\���̒�`
//==============================================================================
///�E�B���h�E�@�\�̊J�����G�t�F�N�g�p���[�N
typedef struct{
	CONRES_PROC_WORK *rpw;		///<���ʔ��\�Ǘ����[�N�ւ̃|�C���^
	u8 *end_flag;				///<�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^

	s32 y1;						///<�E�B���h�E���WY(�㑤)�F����8�r�b�g����
	s32 y2;						///<�E�B���h�E���WY(����)�F����8�r�b�g����
	
	u8 seq;						///<�V�[�P���X�ԍ�
}WNDOPEN_EFF_WORK;

///�|�P�����X���C�h�o��G�t�F�N�g�p���[�N
typedef struct{
	SOFT_SPRITE *ss;		///<�Ώۂ̃|�P�����\�t�g�E�F�A�X�v���C�g�ւ̃|�C���^
	u8 *end_flag;			///<�I���t���O���Z�b�g���郏�[�N�ւ̃|�C���^

	s32 x;					///<���WX(����8�r�b�g����)
	s32 y;					///<���WY(����8�r�b�g����)

	u8 seq;					///<�V�[�P���X�ԍ�
}POKESLIDE_EFF_WORK;

///���ӂԂ������Ǘ��^�X�N�p���[�N
typedef struct{
	CONRES_PROC_WORK *rpw;
	s16 wait;
}CONFETTI_CREATE_WORK;

///���ӂԂ��A�N�^�[����p���[�N
typedef struct{
	CONRES_PROC_WORK *rpw;		///<���ʔ��\�Ǘ����[�N�ւ̃|�C���^
	CATS_ACT_PTR cap;			///<���ӂԂ��A�N�^�[�ւ̃|�C���^
	s32 x;						///<�\�����WX(����8�r�b�g����)
	s32 y;						///<�\�����WY(����8�r�b�g����)
	s16 dx;						///<�\���I�t�Z�b�g���WX
	s16 furihaba;				///<Sin�J�[�u�ӂ蕝
	s32 add_x;					///<���WX���Z�l(����8�r�b�g����)
	s32 add_angle;				///<�p�x���Z�l(����8�r�b�g����)
	s32 angle;					///<���݊p�x(����8�r�b�g����)
}CONFETTI_WORK;

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void RT_MessageTagExpand(CONRES_PROC_WORK *rpw, int msg_tag, const CRTAG_PARAM *tagpara);
static void RT_TalkMessageSet(CONRES_PROC_WORK *rpw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const CRTAG_PARAM *tagpara);
void RT_SoftSpriteAddAll(CONRES_PROC_WORK *rpw);
void RT_SoftSpriteDelAll(CONRES_SYSTEM_PARAM *sys);
void RT_A_TalkMessageSet(CONRES_PROC_WORK *rpw, u32 a_talk_id, const CRTAG_PARAM *tagpara);
int RT_TalkMessageEndCheck(CONRES_PROC_WORK *rpw);
void RT_PokeIconSetAll(CONRES_PROC_WORK *rpw);
void RT_PokeIconDelAll(CONRES_PROC_WORK *rpw);
static void PokeIconUpdate(TCB_PTR tcb, void *work);
void RT_ConfettiResouceLoad(CONRES_PROC_WORK *rpw);
void RT_ConfettiResouceFree(CONRES_PROC_WORK *rpw);
void RT_RankingIconSetAll(CONRES_PROC_WORK *rpw);
void RT_RankingIconDelAll(CONRES_PROC_WORK *rpw);
static void WndEffOpenTask(TCB_PTR tcb, void *work);
static void WndEffCloseTask(TCB_PTR tcb, void *work);
static void PokeSlideEffect_In(TCB_PTR tcb, void *work);
static void PokeSlideEffect_Out(TCB_PTR tcb, void *work);
static void ConfettiCreateTaskMain(TCB_PTR tcb, void *work);
static void RT_ConfettiActorAdd(CONRES_PROC_WORK *rpw);
static void ConfettiActorMain(TCB_PTR tcb, void *work);

//==============================================================================
//	�f�[�^
//==============================================================================
///�|�P�����\�����W
ALIGN4 static const s16 ConresPokePos[BREEDER_MAX][3] = {	//X, Y, Z
	{44, 70, CONRES_POKEPOS_Z_MAIN},
	{44+56, 70, CONRES_POKEPOS_Z_SUB},
	{44+56*2, 70, CONRES_POKEPOS_Z_SUB},
	{44+56*3, 70, CONRES_POKEPOS_Z_SUB},
};

///�|�P�����A�C�R���\�����W
static const struct{
	s16 x;
	s16 y;
}PokeIconPos[] = {
	{8*3+4, 8*2+4 + 32*0},
	{8*3+4, 8*2+4 + 32*1},
	{8*3+4, 8*2+4 + 32*2},
	{8*3+4, 8*2+4 + 32*3},
};

///���ʃA�C�R���\�����W
static const struct{
	s16 x;
	s16 y;
}RankingIconPos[] = {
	{0x1d*8, 8*2-3 + 32*0},
	{0x1d*8, 8*2-3 + 32*1},
	{0x1d*8, 8*2-3 + 32*2},
	{0x1d*8, 8*2-3 + 32*3},
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�_���X����m�[�}����b���b�Z�[�W�f�[�^	��A_TALK_CONRES_???�̒�`�ƕ��т𓯂��ɂ��Ă������I�I
static const CONRES_MESSAGE_PARAM ConresTalkMsgData[] = {
	{0,									CRTAG_NONE},	//�_�~�[
	{msg_con_tally_host_01,				CRTAG_NONE},
	{msg_con_tally_host_02,				CRTAG_NONE},
	{msg_con_tally_host_03,				CRTAG_NONE},
	{msg_con_tally_host_04,				CRTAG_NONE},
	{msg_con_tally_host_05,				CRTAG_NUM_OYA_NICK},
	{msg_con_tally_host_06,				CRTAG_NONE},
};


//==============================================================================
//	�A�N�^�[�w�b�_
//==============================================================================
///�|�P�����A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S PokeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, R_POKEICON_SOFTPRI, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		R_CHARID_POKEICON_0,				//�L����
		R_PLTTID_POKEICON,				//�p���b�g
		R_CELLID_POKEICON,				//�Z��
		R_CELLANMID_POKEICON,				//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	R_POKEICON_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���ӂԂ��F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S ConfettiObjParam = {
	0, 0, 0,		//x, y, z
	0, R_CONFETTI_SOFTPRI, R_PALOFS_CONFETTI,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		R_CHARID_CONFETTI,				//�L����
		R_PLTTID_OBJ_COMMON,				//�p���b�g
		R_CELLID_CONFETTI,				//�Z��
		R_CELLANMID_CONFETTI,				//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	R_CONFETTI_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���ʃA�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S RankingIconObjParam = {
	0, 0, 0,		//x, y, z
	0, R_RANKING_SOFTPRI, R_PALOFS_RANKING,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		R_CHARID_RANKING,				//�L����
		R_PLTTID_OBJ_COMMON,				//�p���b�g
		R_CELLID_RANKING,				//�Z��
		R_CELLANMID_RANKING,				//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	R_RANKING_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���[�^�[�F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S MeterObjParam = {
	0, 0, 0,		//x, y, z
	0, R_METER_SOFTPRI, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		R_CHARID_METER,				//�L����
		R_PLTTID_METER,				//�p���b�g
		R_CELLID_METER,				//�Z��
		R_CELLANMID_METER,				//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	R_METER_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};




//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)�𐶐�����
 *
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_SoftSpriteAddAll(CONRES_PROC_WORK *rpw)
{
	int i, breeder_no;
	
	for(i = 0; i < BREEDER_MAX; i++){
		breeder_no = rpw->r_game.breeder_sort[i];
		
		GF_ASSERT(rpw->sys.exchr_param[breeder_no].exchr_buffer == NULL);
		
		rpw->sys.exchr_param[breeder_no].exchr_buffer = 
			sys_AllocMemory(HEAPID_CONRES, EXCHR_BUFFER_SIZE);
		rpw->sys.ss[breeder_no] = 
			ConTool_BreederPokemonAdd(rpw->sys.soft_sprite, i, rpw->sys.c_game->pp[breeder_no], 
			PARA_FRONT, &rpw->sys.exchr_param[breeder_no], HEAPID_CONRES, 
			ConresPokePos[i][0], ConresPokePos[i][1], ConresPokePos[i][2]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)���폜����
 * @param   sys		�_���X�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_SoftSpriteDelAll(CONRES_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		SoftSpriteDel(sys->ss[i]);
		sys_FreeMemoryEz(sys->exchr_param[i].exchr_buffer);
		sys->exchr_param[i].exchr_buffer = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�^�O�W�J
 *
 * @param   rpw			���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
static void RT_MessageTagExpand(CONRES_PROC_WORK *rpw, int msg_tag, const CRTAG_PARAM *tagpara)
{
	u32 str_id;
	
	if(msg_tag != CRTAG_NONE){
		GF_ASSERT(tagpara != NULL);
	}
	
	switch(msg_tag){
	case CRTAG_NONE:
		break;
	
	case CRTAG_RANK:
		str_id = ConTool_GetRankMsgID(rpw->consys->c_game.rank, rpw->consys->c_game.mode,
			rpw->consys->sio_flag);
		WORDSET_RegisterContestRank(rpw->sys.wordset, 0, str_id);
		break;
	case CRTAG_OYA_NICK:
		WORDSET_RegisterWord(rpw->sys.wordset, 0, 
			rpw->consys->c_game.breeder_name_str[tagpara->mine_brd], 
			rpw->consys->c_game.player_sex[tagpara->mine_brd], TRUE, PM_LANG);
		WORDSET_RegisterPokeNickName(rpw->sys.wordset, 1, 
			PPPPointerGet(rpw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case CRTAG_NUM_OYA_NICK:
		WORDSET_RegisterNumber(rpw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterWord(rpw->sys.wordset, 1, 
			rpw->consys->c_game.breeder_name_str[tagpara->mine_brd], 
			rpw->consys->c_game.player_sex[tagpara->mine_brd], TRUE, PM_LANG);
		WORDSET_RegisterPokeNickName(rpw->sys.wordset, 2, 
			PPPPointerGet(rpw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	
	default:
		GF_ASSERT(0 && "�F���ł��Ȃ��^�O�ł�\n");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�Z�b�g
 *
 * @param   rpw			���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   msg_id		���b�Z�[�WID
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
static void RT_TalkMessageSet(CONRES_PROC_WORK *rpw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const CRTAG_PARAM *tagpara)
{
	STRBUF *message_src;
	int wait;
	
//	BattleMSG_TagExpand(bw,mp);
//	BattleMSG_MsgExpand(bw,msg_m,mp);
	if(rpw->consys->sio_flag == FALSE){
		wait = CONFIG_GetMsgPrintSpeed(rpw->consys->config);
	}
	else{
		wait = CONTEST_SIO_MSG_SPEED;
	}
	
	message_src = MSGMAN_AllocString(msg_man, msg_id);
	RT_MessageTagExpand(rpw, msg_tag, tagpara);
	WORDSET_ExpandStr(rpw->sys.wordset, rpw->sys.msg_buf, message_src);

	GF_BGL_BmpWinDataFill(&rpw->sys.win[CONRES_BMPWIN_TALK], 0xff);
	rpw->sys.talk_msg_index = GF_STR_PrintSimple(&rpw->sys.win[CONRES_BMPWIN_TALK], 
		FONT_TALK, rpw->sys.msg_buf, 0, 0, wait, NULL);

	STRBUF_Delete(message_src);
}

//--------------------------------------------------------------
/**
 * @brief   �m�[�}����b�p�̃��b�Z�[�W�Z�b�g
 *
 * @param   rpw				���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara			�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                  	    (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
void RT_A_TalkMessageSet(CONRES_PROC_WORK *rpw, u32 a_talk_id, const CRTAG_PARAM *tagpara)
{
	u32 msg_id, msg_tag;
	
	GF_ASSERT(a_talk_id < NELEMS(ConresTalkMsgData));
	
	msg_id = ConresTalkMsgData[a_talk_id].msg_id;
	msg_tag = ConresTalkMsgData[a_talk_id].msg_tag;
	RT_TalkMessageSet(rpw, rpw->sys.conres_msg, msg_id, msg_tag, tagpara);
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�t�H���g���\���������Ă��邩�`�F�b�N
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @retval  0=�I��
 */
//--------------------------------------------------------------
int RT_TalkMessageEndCheck(CONRES_PROC_WORK *rpw)
{
	return GF_MSG_PrintEndCheck(rpw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   ��I��ʁF��{BG�f�[�^���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Announce_BGSet(CONRES_PROC_WORK *rpw)
{
	WINTYPE win_type;
	
	//�L�����N�^
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_BG_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_BG_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	GF_BGL_ScrClear(rpw->sys.bgl, CONRES_FRAME_WIN);

	//�p���b�g
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_BG_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0, 0);
	//�t�H���g�p�p���b�g
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, RES_BMPWIN_TALK_COLOR * 16);


	//��b�E�B���h�E
	win_type = CONFIG_GetWindowType(rpw->consys->config);
	TalkWinGraphicSet(rpw->sys.bgl, CONRES_FRAME_WIN, CONRES_TALKWIN_CGX_OFFSET, 
		CONRES_TALKWIN_BACK_COLOR, win_type, HEAPID_CONRES);
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, CONRES_TALKWIN_PALNO * 16);

#if 0
	//�ǂ񂿂傤
	ArcUtil_BgCharSet(ARC_CONTEST_BG, DONTYOU_ANIM_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_EFF, 0, 0, 1, HEAPID_CONRES);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_DANCE_DONCHOU_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_EFF, 0, 0, 1, HEAPID_CONRES);
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, DONTYOU_ANIM_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, DONTYOU_PALNO * 16);
#else
	GF_BGL_ScrClear(rpw->sys.bgl, CONRES_FRAME_EFF);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ��I��ʁF��{BG�f�[�^�̍폜����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Announce_BGDel(CONRES_PROC_WORK *rpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   ��I��ʁF��{BG�f�[�^���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Announce_OBJSet(CONRES_PROC_WORK *rpw)
{
	ADV_FlowerResourceLoad(rpw->sys.csp, rpw->sys.crp, rpw->sys.pfd,
		R_CHARID_FLOWER, R_PLTTID_FLOWER, R_CELLID_FLOWER, R_CELLANMID_FLOWER);
	ADV_FlowerActorAddAll(&rpw->sys.flower, rpw->sys.csp, rpw->sys.crp, 
		R_CHARID_FLOWER, R_PLTTID_FLOWER, R_CELLID_FLOWER, R_CELLANMID_FLOWER, 
		0, R_FLOWER_SOFTPRI, R_FLOWER_BGPRI, TCBPRI_CONRES_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   ��I��ʁF��{BG�f�[�^�̍폜����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Announce_OBJDel(CONRES_PROC_WORK *rpw)
{
	ADV_FlowerActorDelAll(&rpw->sys.flower);
	ADV_FlowerResourceFree(rpw->sys.crp, R_CHARID_FLOWER, R_PLTTID_FLOWER, 
		R_CELLID_FLOWER, R_CELLANMID_FLOWER);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\��ʁF��{BG�f�[�^���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Result_BGSet(CONRES_PROC_WORK *rpw)
{
	WINTYPE win_type;
	
	//�L�����N�^
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_KEKKA_BG_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_KEKKA00_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_KEKKA01_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_EFF, 0, 0, 1, HEAPID_CONRES);
	GF_BGL_ScrClear(rpw->sys.bgl, CONRES_FRAME_WIN);

	//�p���b�g
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CONTEST_KEKKA_BG_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0, 0);
	//�t�H���g�p�p���b�g
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, RES_BMPWIN_TALK_COLOR * 16);


	//��b�E�B���h�E
	win_type = CONFIG_GetWindowType(rpw->consys->config);
	TalkWinGraphicSet(rpw->sys.bgl, CONRES_FRAME_WIN, CONRES_TALKWIN_CGX_OFFSET, 
		CONRES_TALKWIN_BACK_COLOR, win_type, HEAPID_CONRES);
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, CONRES_TALKWIN_PALNO * 16);

	//�j�b�N�l�[�����e�� �`��
	{
		STRBUF *nickname_buf;
		int i, breeder_no;
		
		nickname_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_CONRES);

		for(i = 0; i < BREEDER_MAX; i++){
			breeder_no = rpw->r_game.breeder_sort[i];
			PokeParaGet(rpw->sys.c_game->pp[breeder_no], ID_PARA_nickname_buf, nickname_buf);

			GF_BGL_BmpWinDataFill(&rpw->sys.win[CONRES_BMPWIN_NICK_0 + i], 0x00);
			GF_BGL_BmpWinDataFill(&rpw->sys.win[CONRES_BMPWIN_OYA_0 + i], 0x00);

			GF_STR_PrintColor(&rpw->sys.win[CONRES_BMPWIN_NICK_0 + i], 
				FONT_SYSTEM, nickname_buf, 0, RES_BMPWIN_NAME_DOT_OFFSET, 
				MSG_ALLPUT, RES_BMPWIN_NAME_GF_COLOR, NULL);
			GF_STR_PrintColor(&rpw->sys.win[CONRES_BMPWIN_OYA_0 + i], 
				FONT_SYSTEM, rpw->consys->c_game.breeder_name_str[breeder_no], 0, 
				RES_BMPWIN_NAME_DOT_OFFSET, 
				MSG_ALLPUT, RES_BMPWIN_NAME_GF_COLOR, NULL);
		}

		STRBUF_Delete(nickname_buf);
	}

	//���W�X�^�ݒ�
	GX_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);
	G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | 
		GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
	G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | 
		GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
	G2_SetWndOutsidePlane((GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | 
		GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ) ^ CONRES_GX_WND_EFF, 
		TRUE);
	G2_SetWnd0Position(0, 0, 255, 0);
	G2_SetWnd1Position(0, 0, 255, 0);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�T�u��ʁF��{BG�f�[�^���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Result_BGSet_Sub(CONRES_PROC_WORK *rpw)
{
	//�F��S�Đ^�����ɂ��Ă���(��ʂ������Ȃ��悤��)
	PaletteWork_Clear(rpw->sys.pfd, FADE_SUB_BG, FADEBUF_ALL, 0x0000, 0, 16*16);
	PaletteWork_Clear(rpw->sys.pfd, FADE_SUB_OBJ, FADEBUF_ALL, 0x0000, 0, 16*16);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\��ʁF��{BG�f�[�^�̍폜����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Result_BGDel(CONRES_PROC_WORK *rpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\��ʁF��{BG�f�[�^���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Result_OBJSet(CONRES_PROC_WORK *rpw)
{
	//�풓OBJ�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(rpw->sys.pfd, FADE_MAIN_OBJ, rpw->sys.csp, rpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_KEKKA_OBJ_NCLR, 0, 
		R_CONRES_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, R_PLTTID_OBJ_COMMON);

	RT_ConfettiResouceLoad(rpw);

	RT_PokeIconSetAll(rpw);
	RT_RankingIconSetAll(rpw);
	RT_MeterResouceLoad(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\��ʁF��{BG�f�[�^�̍폜����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_Result_OBJDel(CONRES_PROC_WORK *rpw)
{
	RT_PokeIconDelAll(rpw);
	RT_RankingIconDelAll(rpw);
	RT_MeterActorDeleteAll(rpw);

	RT_ConfettiResouceFree(rpw);
	RT_MeterResouceFree(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R����S�ăZ�b�g
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_PokeIconSetAll(CONRES_PROC_WORK *rpw)
{
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	int breeder_no, i;
	
	//�p���b�g
	CATS_LoadResourcePlttWorkArc(rpw->sys.pfd, FADE_MAIN_OBJ, rpw->sys.csp, rpw->sys.crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, POKEICON_PAL_MAX, 
		NNS_G2D_VRAM_TYPE_2DMAIN, R_PLTTID_POKEICON);
	//�Z��
	CATS_LoadResourceCellArc(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
		PokeIcon64kCellArcIndexGet(), 0, R_CELLID_POKEICON);
	//�Z���A�j��
	CATS_LoadResourceCellAnmArc(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
		PokeIcon64kCellAnmArcIndexGet(), 0, R_CELLANMID_POKEICON);
	
	//�A�N�^�[����
	obj_param = PokeIconObjParam;
	for(i = 0; i < BREEDER_MAX; i++){
		//�L�������\�[�X
		CATS_LoadResourceCharArcModeAdjustAreaCont(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
			PokeIconCgxArcIndexGetByPP(rpw->consys->c_game.pp[i]),
			0, NNS_G2D_VRAM_TYPE_2DMAIN, R_CHARID_POKEICON_0 + i);

		obj_param.id[CLACT_U_CHAR_RES] = R_CHARID_POKEICON_0 + i;
		rpw->sys.pokeicon_cap[i] = CATS_ObjectAdd_S(rpw->sys.csp, rpw->sys.crp, &obj_param);
		CATS_ObjectAnimeSeqSetCap(rpw->sys.pokeicon_cap[i], POKEICON_ANM_HPMAX);
		
		//�p���b�g�؂�ւ�
	//	monsno = PokeParaGet(rpw->consys->c_game.pp[i], ID_PARA_monsno, NULL);
	//	egg = PokeParaGet(rpw->consys->c_game.pp[i], ID_PARA_tamago_flag, NULL);
		CLACT_PaletteOffsetChgAddTransPlttNo(rpw->sys.pokeicon_cap[i]->act, 
			PokeIconPalNumGetByPP(rpw->consys->c_game.pp[i]));
		
		CATS_ObjectUpdateCap(rpw->sys.pokeicon_cap[i]);
	}
	
	//���W�Z�b�g
	for(i = 0; i < BREEDER_MAX; i++){
		breeder_no = rpw->r_game.breeder_sort[i];
		CATS_ObjectPosSetCap(rpw->sys.pokeicon_cap[breeder_no], 
			PokeIconPos[i].x, PokeIconPos[i].y);
	}
	
	//�A�j���X�V�p�^�X�N����
	rpw->sys.pokeicon_tcb = TCB_Add(PokeIconUpdate, rpw, TCBPRI_POKEICON_UPDATE);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R����S�č폜
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_PokeIconDelAll(CONRES_PROC_WORK *rpw)
{
	int i;
	
	CATS_FreeResourceCell(rpw->sys.crp, R_CELLID_POKEICON);
	CATS_FreeResourceCellAnm(rpw->sys.crp, R_CELLANMID_POKEICON);
	CATS_FreeResourcePltt(rpw->sys.crp, R_PLTTID_POKEICON);

	for(i = 0; i < BREEDER_MAX; i++){
		CATS_FreeResourceChar(rpw->sys.crp, R_CHARID_POKEICON_0 + i);
		CATS_ActorPointerDelete_S(rpw->sys.pokeicon_cap[i]);
	}
	
	TCB_Delete(rpw->sys.pokeicon_tcb);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���A�j���X�V�^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void PokeIconUpdate(TCB_PTR tcb, void *work)
{
	CONRES_PROC_WORK *rpw = work;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		CATS_ObjectUpdateCap(rpw->sys.pokeicon_cap[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ��̃��\�[�X���Z�b�g
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_ConfettiResouceLoad(CONRES_PROC_WORK *rpw)
{
	CATS_LoadResourceCharArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, CONFETTI_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, R_CHARID_CONFETTI);
	CATS_LoadResourceCellArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		CONFETTI_NCER_BIN, 1, R_CELLID_CONFETTI);
	CATS_LoadResourceCellAnmArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		CONFETTI_NANR_BIN, 1, R_CELLANMID_CONFETTI);
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ��̃��\�[�X���
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_ConfettiResouceFree(CONRES_PROC_WORK *rpw)
{
	CATS_FreeResourceChar(rpw->sys.crp, R_CHARID_CONFETTI);
	CATS_FreeResourceCell(rpw->sys.crp, R_CELLID_CONFETTI);
	CATS_FreeResourceCellAnm(rpw->sys.crp, R_CELLANMID_CONFETTI);
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ������Ǘ��^�X�N�𐶐�����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_ConfettiCreateTaskSet(CONRES_PROC_WORK *rpw)
{
	CONFETTI_CREATE_WORK *ccw;
	int i;
	
	ccw = sys_AllocMemory(HEAPID_CONRES, sizeof(CONFETTI_CREATE_WORK));
	MI_CpuClear8(ccw, sizeof(CONFETTI_CREATE_WORK));
	
	ccw->rpw = rpw;
	
	for(i = 0; i < CONFETTI_INIT_CREATE_NUM; i++){
		RT_ConfettiActorAdd(rpw);
	}
	TCB_Add(ConfettiCreateTaskMain, ccw, TCBPRI_CONRES_CONFETTI_SYS);
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ��S�I���t���O���Z�b�g����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_ConfettiEndFlagSet(CONRES_PROC_WORK *rpw)
{
	rpw->confetti_end = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ������Ǘ��^�X�N���C������
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���ӂԂ�����
 */
//--------------------------------------------------------------
static void ConfettiCreateTaskMain(TCB_PTR tcb, void *work)
{
	CONFETTI_CREATE_WORK *ccw = work;
	
	if(ccw->rpw->confetti_end == TRUE){
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	
	if(ccw->rpw->confetti_count < CONFETTI_CREATE_MAX){
		ccw->wait++;
		if(ccw->wait > CONFETTI_CREATE_WAIT){
			ccw->wait = 0;
			RT_ConfettiActorAdd(ccw->rpw);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ��A�N�^�[����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void RT_ConfettiActorAdd(CONRES_PROC_WORK *rpw)
{
	CATS_ACT_PTR cap;
	CONFETTI_WORK *confetti;
	s32 x, y;
	
	confetti = sys_AllocMemory(HEAPID_CONRES, sizeof(CONFETTI_WORK));
	MI_CpuClear8(confetti, sizeof(CONFETTI_WORK));
	
	confetti->rpw = rpw;
	
	confetti->cap = CATS_ObjectAdd_S(rpw->sys.csp, rpw->sys.crp, &ConfettiObjParam);
	
	x = (contest_rand(rpw->consys) & 0xff) + 20;
	y = CONFETTI_START_Y + (contest_rand(rpw->consys) % CONFETTI_START_Y_RND);
	confetti->x = x * 0x100;
	confetti->y = y * 0x100;
	CATS_ObjectPosSetCap(confetti->cap, x, y);
	
	confetti->add_x = (contest_rand(rpw->consys) % CONFETTI_RND_X) + CONFETTI_ADD_X;
	confetti->add_angle = (contest_rand(rpw->consys) % CONFETTI_RND_ANGLE) + CONFETTI_ADD_ANGLE;
	confetti->furihaba = 
		(contest_rand(rpw->consys) % CONFETTI_FURIHABA_X_RND) + CONFETTI_FURIHABA_X;
	
	CATS_ObjectUpdateCap(confetti->cap);
	
	TCB_Add(ConfettiActorMain, confetti, TCBPRI_CONRES_CONFETTI_ACTOR);
	rpw->confetti_count++;
}

//--------------------------------------------------------------
/**
 * @brief   ���ӂԂ��A�N�^�[���C������
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���ӂԂ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConfettiActorMain(TCB_PTR tcb, void *work)
{
	CONFETTI_WORK *confetti = work;
	
	if(confetti->rpw->confetti_end == TRUE 
			|| ((confetti->y / 0x100) > CONFETTI_END_Y)
			|| (((confetti->x+confetti->dx) / 0x100) < -16)){
		confetti->rpw->confetti_count--;
		CATS_ActorPointerDelete_S(confetti->cap);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	
	confetti->angle += confetti->add_angle;
	if(confetti->angle >= (360<<8)){
		confetti->angle -= 360<<8;
	}
	confetti->dx = FX_Mul(Sin360(confetti->angle / 0x100), confetti->furihaba << FX32_SHIFT) / FX32_ONE;
	confetti->x -= confetti->add_x;
	confetti->y += CONFETTI_ADD_Y;
	CATS_ObjectPosSetCap(confetti->cap, 
		(confetti->x / 0x0100) + confetti->dx, confetti->y / 0x0100);

	CATS_ObjectUpdateCap(confetti->cap);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʃA�C�R����S�ăZ�b�g
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_RankingIconSetAll(CONRES_PROC_WORK *rpw)
{
	CATS_LoadResourceCharArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, RANKING_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, R_CHARID_RANKING);
	CATS_LoadResourceCellArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		RANKING_NCER_BIN, 1, R_CELLID_RANKING);
	CATS_LoadResourceCellAnmArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		RANKING_NANR_BIN, 1, R_CELLANMID_RANKING);
	
	{
		int i, breeder_no;
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->sys.ranking_cap[i] = CATS_ObjectAdd_S(
				rpw->sys.csp, rpw->sys.crp, &RankingIconObjParam);
			CATS_ObjectUpdateCap(rpw->sys.ranking_cap[i]);
			//�\��OFF
			CATS_ObjectEnableCap(rpw->sys.ranking_cap[i], CATS_ENABLE_FALSE);
		}
		//���W�Z�b�g
		for(i = 0; i < BREEDER_MAX; i++){
			breeder_no = rpw->r_game.breeder_sort[i];
			CATS_ObjectPosSetCap(rpw->sys.ranking_cap[breeder_no], 
				RankingIconPos[i].x, RankingIconPos[i].y);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ʃA�C�R����S�č폜
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_RankingIconDelAll(CONRES_PROC_WORK *rpw)
{
	CATS_FreeResourceChar(rpw->sys.crp, R_CHARID_RANKING);
	CATS_FreeResourceCell(rpw->sys.crp, R_CELLID_RANKING);
	CATS_FreeResourceCellAnm(rpw->sys.crp, R_CELLANMID_RANKING);
	
	{
		int i;
		for(i = 0; i < BREEDER_MAX; i++){
			CATS_ActorPointerDelete_S(rpw->sys.ranking_cap[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ʃA�C�R����o��(�\��)������
 *
 * @param   rpw				���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   ranking			����
 */
//--------------------------------------------------------------
void RT_RankingIconAppearSet(CONRES_PROC_WORK *rpw, int breeder_no, int ranking)
{
	CATS_ObjectAnimeSeqSetCap(rpw->sys.ranking_cap[breeder_no], ranking);
	CATS_ObjectEnableCap(rpw->sys.ranking_cap[breeder_no], CATS_ENABLE_TRUE);
	Snd_SePlay(RSE_RANKING_ANNOUNCE);
}

//--------------------------------------------------------------
/**
 * @brief   ���[�^�[�̃��\�[�X���Z�b�g
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_MeterResouceLoad(CONRES_PROC_WORK *rpw)
{
	CATS_LoadResourcePlttWorkArc(rpw->sys.pfd, FADE_MAIN_OBJ, rpw->sys.csp, rpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_KEKKA_METER_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, R_PLTTID_METER);
	CATS_LoadResourceCharArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		CON_KEKKA_METER_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, R_CHARID_METER);
	CATS_LoadResourceCellArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		CON_KEKKA_METER_NCER_BIN, 1, R_CELLID_METER);
	CATS_LoadResourceCellAnmArc(rpw->sys.csp, rpw->sys.crp, ARC_CONTEST_OBJ, 
		CON_KEKKA_METER_NANR_BIN, 1, R_CELLANMID_METER);
}

//--------------------------------------------------------------
/**
 * @brief   ���[�^�[�̃��\�[�X���
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_MeterResouceFree(CONRES_PROC_WORK *rpw)
{
	CATS_FreeResourcePltt(rpw->sys.crp, R_PLTTID_METER);
	CATS_FreeResourceChar(rpw->sys.crp, R_CHARID_METER);
	CATS_FreeResourceCell(rpw->sys.crp, R_CELLID_METER);
	CATS_FreeResourceCellAnm(rpw->sys.crp, R_CELLANMID_METER);
}

///���[�^�[�̊J�n���WX
#define RES_METER_START_X		(48)
///���[�^�[�̊J�n���WY
#define RES_METER_START_Y		(32)
///���[�^�[�̍��WY�̎��̃u���[�_�[�܂ł̊Ԋu�h�b�g��
#define RES_METER_SPACE_Y		(32)

///�e���[�^�[�̊J�n�A�j���V�[�P���X�ԍ�
enum{
	RES_METER_START_ANIM_SPACE = 0,		///<��
	RES_METER_START_ANIM_VISUAL = 1,	///<�r�W���A���p���[�^�[�J�n�V�[�P���X�ԍ�
	RES_METER_START_ANIM_DANCE = 0x11,	///<�_���X�p���[�^�[�J�n�V�[�P���X�ԍ�
	RES_METER_START_ANIM_ACTIN = 0x21,	///<���Z�p���[�^�[�J�n�V�[�P���X�ԍ�
};

//--------------------------------------------------------------
/**
 * @brief   �w��h�b�g�������[�^�[�A�N�^�[�𐶐�����
 *
 * @param   rpw				���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   con_game		CONGAME_???
 * @param   dot				�\���h�b�g��
 * @param   breeder_pos		�u���[�_�[�\���ʒu
 */
//--------------------------------------------------------------
void RT_MeterActorDotCreate(CONRES_PROC_WORK *rpw, int breeder_no, int con_game, int dot, int breeder_pos)
{
	int start_dot;
	CATS_ACT_PTR *cap_array;
	int start_anime;
	int x, y, act_num, i, no, calc_dot;
	
	switch(con_game){
	case CONGAME_VISUAL:
		start_dot = 0;
		start_anime = RES_METER_START_ANIM_VISUAL;
		cap_array = rpw->sys.visual_meter_cap[breeder_no];
		break;
	case CONGAME_DANCE:
		start_dot = rpw->r_game.visual_dot[breeder_no];
		start_anime = RES_METER_START_ANIM_DANCE;
		cap_array = rpw->sys.dance_meter_cap[breeder_no];
		break;
	case CONGAME_ACTIN:
		start_dot = rpw->r_game.visual_dot[breeder_no] + rpw->r_game.dance_dot[breeder_no];
		start_anime = RES_METER_START_ANIM_ACTIN;
		cap_array = rpw->sys.actin_meter_cap[breeder_no];
		break;
	default:
		GF_ASSERT(0);
		return;
	}
	
	//���W�J�n�ʒu
	x = RES_METER_START_X + start_dot;
	y = RES_METER_START_Y + RES_METER_SPACE_Y * breeder_pos;
	
	//�K�v�ȃA�N�^�[�����Z�o
	act_num = dot / RES_METER_ACT_SIZE_X;
	if(dot % RES_METER_ACT_SIZE_X != 0){
		act_num++;
	}
	GF_ASSERT(act_num <= RES_METER_CAP_MAX);
	
	//����Ȃ��A�N�^�[���𐶐�
	for(i = 0; i < act_num; i++){
		if(cap_array[i] == NULL){
			cap_array[i] = CATS_ObjectAdd_S(rpw->sys.csp, rpw->sys.crp, &MeterObjParam);
		}
	}
	
	//�h�b�g���ɍ��킹�ăA�j��
	no = 0;
	for(calc_dot = dot; calc_dot >= RES_METER_ACT_SIZE_X; calc_dot -= RES_METER_ACT_SIZE_X){
		CATS_ObjectAnimeSeqSetCap(cap_array[no], start_anime + RES_METER_ACT_SIZE_X - 1);
		no++;
	}
	if(calc_dot > 0 && no < act_num){
		CATS_ObjectAnimeSeqSetCap(cap_array[no], start_anime + calc_dot - 1);
	}
	
	//OBJUpdate
	for(i = 0; i < act_num; i++){
		CATS_ObjectPosSetCap(cap_array[i], x + i * RES_METER_ACT_SIZE_X, y);
		CATS_ObjectUpdateCap(cap_array[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���[�^�[�A�N�^�[��S�č폜����
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_MeterActorDeleteAll(CONRES_PROC_WORK *rpw)
{
	int i, breeder_no;
	
	for(breeder_no = 0; breeder_no < BREEDER_MAX; breeder_no++){
		for(i = 0; i < RES_METER_CAP_MAX; i++){
			if(rpw->sys.visual_meter_cap[breeder_no][i] != NULL){
				CATS_ActorPointerDelete_S(rpw->sys.visual_meter_cap[breeder_no][i]);
			}
			if(rpw->sys.dance_meter_cap[breeder_no][i] != NULL){
				CATS_ActorPointerDelete_S(rpw->sys.dance_meter_cap[breeder_no][i]);
			}
			if(rpw->sys.actin_meter_cap[breeder_no][i] != NULL){
				CATS_ActorPointerDelete_S(rpw->sys.actin_meter_cap[breeder_no][i]);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �E�B���h�E�@�\�̊J�����G�t�F�N�g�J�n
 *
 * @param   open_close		RT_WNDEFF_OPEN or RT_WNDEFF_CLOSE
 * @param   end_flag		�G�t�F�N�g�I����A���̃��[�N��TRUE���Z�b�g����܂�
 */
//--------------------------------------------------------------
void RT_WndOpenEffStart(CONRES_PROC_WORK *rpw, int open_close, u8 *end_flag)
{
	WNDOPEN_EFF_WORK *wew;
	
	*end_flag = FALSE;
	
	wew = sys_AllocMemory(HEAPID_CONRES, sizeof(WNDOPEN_EFF_WORK));
	MI_CpuClear8(wew, sizeof(WNDOPEN_EFF_WORK));
	
	wew->rpw = rpw;
	wew->end_flag = end_flag;
	
	if(open_close == RT_WNDEFF_OPEN){
		wew->y1 = (192/2) << 8;
		wew->y2 = (192/2) << 8;
		TCB_Add(WndEffOpenTask, wew, TCBPRI_CONRES_WNDOPEN);
	}
	else{
		wew->y1 = ((192/2) - WNDOPEN_EFF_OPEN_Y_DOT/2) << 8;
		wew->y2 = ((192/2) + WNDOPEN_EFF_OPEN_Y_DOT/2) << 8;
		TCB_Add(WndEffCloseTask, wew, TCBPRI_CONRES_WNDOPEN);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �E�B���h�E�@�\�F�I�[�v���G�t�F�N�g���s
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		WNDOPEN_EFF_WORK�\����
 */
//--------------------------------------------------------------
static void WndEffOpenTask(TCB_PTR tcb, void *work)
{
	WNDOPEN_EFF_WORK *wew = work;
	
	switch(wew->seq){
	case 0:
		wew->y1 -= WNDOPEN_EFF_ADD_Y;
		wew->y2 += WNDOPEN_EFF_ADD_Y;
		if(wew->y1 <= ((192/2)<<8) - ((WNDOPEN_EFF_OPEN_Y_DOT/2)<<8)){
			wew->y1 = (192/2 - WNDOPEN_EFF_OPEN_Y_DOT/2) << 8;
			wew->y2 = (192/2 + WNDOPEN_EFF_OPEN_Y_DOT/2) << 8;
			wew->seq++;
		}
		//left=0, right=255�ł��ƉE�[��1�h�b�g�c��̂�2���g���Ė�����͂�
		wew->rpw->wnd0_x1 = 0;
		wew->rpw->wnd0_y1 = wew->y1 >> 8;
		wew->rpw->wnd0_x2 = 255;
		wew->rpw->wnd0_y2 = wew->y2 >> 8;
		wew->rpw->wnd1_x1 = 1;
		wew->rpw->wnd1_y1 = wew->y1 >> 8;
		wew->rpw->wnd1_x2 = 0;
		wew->rpw->wnd1_y2 = wew->y2 >> 8;
		break;
	default:
		*(wew->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �E�B���h�E�@�\�F�N���[�Y�G�t�F�N�g���s
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		WNDOPEN_EFF_WORK�\����
 */
//--------------------------------------------------------------
static void WndEffCloseTask(TCB_PTR tcb, void *work)
{
	WNDOPEN_EFF_WORK *wew = work;
	
	switch(wew->seq){
	case 0:
		wew->y1 += WNDOPEN_EFF_ADD_Y;
		wew->y2 -= WNDOPEN_EFF_ADD_Y;
		if(wew->y1 >= ((192/2)<<8)){
			wew->y1 = (192/2) << 8;
			wew->y2 = (192/2) << 8;
			wew->seq++;
		}
		//left=0, right=255�ł��ƉE�[��1�h�b�g�c��̂�2���g���Ė�����͂�
		wew->rpw->wnd0_x1 = 0;
		wew->rpw->wnd0_y1 = wew->y1 >> 8;
		wew->rpw->wnd0_x2 = 255;
		wew->rpw->wnd0_y2 = wew->y2 >> 8;
		wew->rpw->wnd1_x1 = 1;
		wew->rpw->wnd1_y1 = wew->y1 >> 8;
		wew->rpw->wnd1_x2 = 0;
		wew->rpw->wnd1_y2 = wew->y2 >> 8;
		break;
	default:
		*(wew->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����X���C�h�o��G�t�F�N�g�J�n
 *
 * @param   rpw				���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   in_out			RT_POKESLIDE_IN or RT_POKESLIDE_OUT
 * @param   end_flag		�G�t�F�N�g�I����A���̃��[�N��TRUE���Z�b�g����܂�
 */
//--------------------------------------------------------------
void PokeSlideEffectStart(CONRES_PROC_WORK *rpw, int breeder_no, int in_out, u8 *end_flag)
{
	POKESLIDE_EFF_WORK *pew;
	
	*end_flag = FALSE;
	
	pew = sys_AllocMemory(HEAPID_CONRES, sizeof(POKESLIDE_EFF_WORK));
	MI_CpuClear8(pew, sizeof(POKESLIDE_EFF_WORK));
	
	pew->ss = rpw->sys.ss[breeder_no];
	pew->end_flag = end_flag;
	
	if(in_out == RT_POKESLIDE_IN){
		pew->x = (256 + SOFT_SPRITE_SIZE_X/2) << 8;
		pew->y = (192/2) << 8;
		TCB_Add(PokeSlideEffect_In, pew, TCBPRI_CONRES_EFFECT);
	}
	else{
		pew->x = (256/2) << 8;
		pew->y = (192/2) << 8;
		TCB_Add(PokeSlideEffect_Out, pew, TCBPRI_CONRES_EFFECT);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����X���C�h�o��F��ʊO����o��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		POKESLIDE_EFF_WORK�\����
 */
//--------------------------------------------------------------
static void PokeSlideEffect_In(TCB_PTR tcb, void *work)
{
	POKESLIDE_EFF_WORK *pew = work;
	
	switch(pew->seq){
	case 0:
		SoftSpriteParaSet(pew->ss, SS_PARA_VANISH, FALSE);
		pew->seq++;
		//break;
	case 1:
		pew->x -= POKESLIDE_ADD_X;
		if(pew->x <= (256/2) << 8){
			pew->x = (256/2) << 8;
			pew->seq++;
		}
		SoftSpriteParaSet(pew->ss, SS_PARA_POS_X, pew->x >> 8);
		SoftSpriteParaSet(pew->ss, SS_PARA_POS_Y, pew->y >> 8);
		break;
	default:
		*(pew->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����X���C�h�o��F��ʓ������ʊO��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		POKESLIDE_EFF_WORK�\����
 */
//--------------------------------------------------------------
static void PokeSlideEffect_Out(TCB_PTR tcb, void *work)
{
	POKESLIDE_EFF_WORK *pew = work;
	
	switch(pew->seq){
	case 0:
		pew->seq++;
		//break;
	case 1:
		pew->x -= POKESLIDE_ADD_X;
		if(pew->x <= -(SOFT_SPRITE_SIZE_X / 2) * 0x100){
			//pew->x = -(SOFT_SPRITE_SIZE_X / 2) * 0x100;
			pew->seq++;
		}
		SoftSpriteParaSet(pew->ss, SS_PARA_POS_X, pew->x / 0x0100);
		SoftSpriteParaSet(pew->ss, SS_PARA_POS_Y, pew->y >> 8);
		break;
	default:
		SoftSpriteParaSet(pew->ss, SS_PARA_VANISH, TRUE);

		*(pew->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�����Ă���R���e�X�g���[�h����A�Q���������Z�̎��v�Z�䗦���擾����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   con_game	CONGAME_???
 *
 * @retval  �v�Z�䗦(����100�{�A�ȉ�����)
 */
//--------------------------------------------------------------
static int RT_CalcGamePercentGet(CONTEST_SYSTEM *consys, int con_game)
{
	switch(consys->c_game.mode){
	case CONMODE_CHARM:
		switch(con_game){
		case CONGAME_VISUAL:
			return CONRESULT_GAME_PERCENT_CHARM_VISUAL;
		case CONGAME_ACTIN:
			return CONRESULT_GAME_PERCENT_CHARM_ACTIN;
		default:
			//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
			return 0;
		}
		break;
	case CONMODE_ACTIVE:
		switch(con_game){
		case CONGAME_VISUAL:
			return CONRESULT_GAME_PERCENT_ACTIVE_VISUAL;
		case CONGAME_DANCE:
			return CONRESULT_GAME_PERCENT_ACTIVE_DANCE;
		default:
			//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
			return 0;
		}
		break;
	case CONMODE_GRAND:
		switch(con_game){
		case CONGAME_VISUAL:
			return CONRESULT_GAME_PERCENT_GRAND_VISUAL;
		case CONGAME_DANCE:
			return CONRESULT_GAME_PERCENT_GRAND_DANCE;
		case CONGAME_ACTIN:
			return CONRESULT_GAME_PERCENT_GRAND_ACTIN;
		default:
			//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
			return 0;
		}
		break;
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_VISUAL_TUTORIAL:
		if(con_game == CONGAME_VISUAL){
			return 10000;
		}
		//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
		return 0;
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_DANCE_TUTORIAL:
		if(con_game == CONGAME_DANCE){
			return 10000;
		}
		//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
		return 0;
	case CONMODE_ACTIN_PRACTICE:
	case CONMODE_ACTIN_TUTORIAL:
		if(con_game == CONGAME_ACTIN){
			return 10000;
		}
		//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
		return 0;
	default:
		//GF_ASSERT(0 && "�p�ӂ���Ă��Ȃ��v�Z��");
		return 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Q�����Ă���R���e�X�g���[�h����A�Q���������Z�̎��ő�h�b�g�����擾����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   con_game	CONGAME_???
 *
 * @retval  �ő�h�b�g��
 */
//--------------------------------------------------------------
static int RT_CalcGameDotGet(CONTEST_SYSTEM *consys, int con_game)
{
	int percent, dot;
	
	percent = RT_CalcGamePercentGet(consys, con_game);
	dot = RES_METER_DOT_MAX * percent;
	dot = (dot + 5000) / 10000;		//�l�̌ܓ����Đ�����
	return dot;
}

//--------------------------------------------------------------
/**
 * @brief   �e����̓��_�C���l���擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   con_game	CONGAME_???
 * @param   ret_revise	���_�C���l�����(BREEDER_MAX���̔z��)
 *
 * �����Z����ł��g�p���܂��B
 */
//--------------------------------------------------------------
void RT_CalcRevicePoint(CONTEST_SYSTEM *consys, int con_game, s16 ret_revise[])
{
	int total_point[BREEDER_MAX];
	int revise_point[BREEDER_MAX];
	int percent, bairitu, i, top_breeder;
	
	//�����܂ł̓��_�����߂�
	for(i = 0; i < BREEDER_MAX; i++){
		switch(con_game){
		case CONGAME_VISUAL:
			total_point[i] = 
				ConTool_HeartNumGet_BP(consys, i) + ConTool_HeartNumGet_Clip(consys, i);
			break;
		case CONGAME_DANCE:
			total_point[i] = consys->c_game.score[i].dance;
			break;
		case CONGAME_ACTIN:
			total_point[i] = consys->c_game.score[i].actin;
			break;
		default:
			GF_ASSERT(0);
			return;
		}
	}
	
	//���_�g�b�v�̃u���[�_�[�����߂�
	top_breeder = 0;
	for(i = 1; i < BREEDER_MAX; i++){
		if(total_point[top_breeder] < total_point[i]){
			top_breeder = i;
		}
	}
	
	//�{���擾
	percent = RT_CalcGamePercentGet(consys, con_game);
	bairitu = percent / total_point[top_breeder];
	
	//�C���l
	for(i = 0; i < BREEDER_MAX; i++){
		revise_point[i] = total_point[i] * bairitu;
		revise_point[i] = (revise_point[i] + 50) / 100;	//�l�̌ܓ�
	}
	
	//���ʑ��
	for(i = 0; i < BREEDER_MAX; i++){
		switch(con_game){
		case CONGAME_VISUAL:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("�u���[�_�[%d �r�W���A���C���l��%d\n", i, ret_revise[i]);
			break;
		case CONGAME_DANCE:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("�u���[�_�[%d �_���X�C���l��%d\n", i, ret_revise[i]);
			break;
		case CONGAME_ACTIN:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("�u���[�_�[%d ���Z�C���l��%d\n", i, ret_revise[i]);
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �����܂ł̑S�ẴQ�[���̓��_���v�Z�A���[�^�[�̃h�b�g�����Z�o
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void RT_CalcPoint(CONRES_PROC_WORK *rpw)
{
	int i;
	
	//�e����̏C���l�v�Z
	switch(rpw->consys->c_game.mode){
	case CONMODE_CHARM:
		RT_CalcRevicePoint(rpw->consys, CONGAME_VISUAL, rpw->r_game.visual_revise);
		RT_CalcRevicePoint(rpw->consys, CONGAME_ACTIN, rpw->r_game.actin_revise);
		break;
	case CONMODE_ACTIVE:
		RT_CalcRevicePoint(rpw->consys, CONGAME_VISUAL, rpw->r_game.visual_revise);
		RT_CalcRevicePoint(rpw->consys, CONGAME_DANCE, rpw->r_game.dance_revise);
		break;
	case CONMODE_GRAND:
		RT_CalcRevicePoint(rpw->consys, CONGAME_VISUAL, rpw->r_game.visual_revise);
		RT_CalcRevicePoint(rpw->consys, CONGAME_DANCE, rpw->r_game.dance_revise);
		RT_CalcRevicePoint(rpw->consys, CONGAME_ACTIN, rpw->r_game.actin_revise);
		break;
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_VISUAL_TUTORIAL:
		RT_CalcRevicePoint(rpw->consys, CONGAME_VISUAL, rpw->r_game.visual_revise);
		break;
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_DANCE_TUTORIAL:
		RT_CalcRevicePoint(rpw->consys, CONGAME_DANCE, rpw->r_game.dance_revise);
		break;
	case CONMODE_ACTIN_PRACTICE:
	case CONMODE_ACTIN_TUTORIAL:
		RT_CalcRevicePoint(rpw->consys, CONGAME_ACTIN, rpw->r_game.actin_revise);
		break;
	}
	
	//�����C���l
	for(i = 0; i < BREEDER_MAX; i++){
		rpw->r_game.total_revise[i] = rpw->r_game.visual_revise[i] 
			+ rpw->r_game.dance_revise[i] + rpw->r_game.actin_revise[i];
		OS_TPrintf("�u���[�_�[%d �����C���l��%d\n", i, rpw->r_game.total_revise[i]);
	}
	
#if 1
	//1�ʂ̓��_����Ɋe�u���[�_�[�������[�^�[�̊e����̃p�[�Z���e�[�W���擾
	{
		s32 top_breeder_point, top_breeder;
		
		//�r�W���A��
		top_breeder = 0;
		for(i = 1;i < BREEDER_MAX; i++){
			if(rpw->r_game.visual_revise[top_breeder] < rpw->r_game.visual_revise[i]){
				top_breeder = i;
			}
		}
		top_breeder_point = rpw->r_game.visual_revise[top_breeder];
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.visual_percent[i] = 
				RES_METER_PERCENT_MAX * rpw->r_game.visual_revise[i] / top_breeder_point;
			OS_TPrintf("�u���[�_�[%d �r�W���A�����[�^�[�����p�[�Z���g = %d\n", i, rpw->r_game.visual_percent[i]);
		}

		//�_���X
		top_breeder = 0;
		for(i = 1;i < BREEDER_MAX; i++){
			if(rpw->r_game.dance_revise[top_breeder] < rpw->r_game.dance_revise[i]){
				top_breeder = i;
			}
		}
		top_breeder_point = rpw->r_game.dance_revise[top_breeder];
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.dance_percent[i] = 
				RES_METER_PERCENT_MAX * rpw->r_game.dance_revise[i] / top_breeder_point;
			OS_TPrintf("�u���[�_�[%d �_���X���[�^�[�����p�[�Z���g = %d\n", i, rpw->r_game.dance_percent[i]);
		}

		//���Z
		top_breeder = 0;
		for(i = 1;i < BREEDER_MAX; i++){
			if(rpw->r_game.actin_revise[top_breeder] < rpw->r_game.actin_revise[i]){
				top_breeder = i;
			}
		}
		top_breeder_point = rpw->r_game.actin_revise[top_breeder];
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.actin_percent[i] = 
				RES_METER_PERCENT_MAX * rpw->r_game.actin_revise[i] / top_breeder_point;
			OS_TPrintf("�u���[�_�[%d ���Z���[�^�[�����p�[�Z���g = %d\n", i, rpw->r_game.actin_percent[i]);
		}
	}
	
	//�e����̃Q�[�W�h�b�g�����擾
	{
		int max_dot;
		
		//�r�W���A��
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_VISUAL);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.visual_dot[i] = max_dot * rpw->r_game.visual_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("�u���[�_�[%d �r�W���A�������h�b�g�� = %d\n", i, rpw->r_game.visual_dot[i]);
		}

		//�_���X
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_DANCE);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.dance_dot[i] = max_dot * rpw->r_game.dance_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("�u���[�_�[%d �_���X�����h�b�g�� = %d\n", i, rpw->r_game.dance_dot[i]);
		}

		//���Z
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_ACTIN);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.actin_dot[i] = max_dot * rpw->r_game.actin_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("�u���[�_�[%d ���Z�����h�b�g�� = %d\n", i, rpw->r_game.actin_dot[i]);
		}
		
		//����
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.gauge_dot[i] = rpw->r_game.visual_dot[i] + rpw->r_game.dance_dot[i]
				+ rpw->r_game.actin_dot[i];
		}
	}

	//�����h�b�g�����珇�ʂ�����
	{
		s32 random[BREEDER_MAX];
		s32 ranking[BREEDER_MAX];	//���ʏ��Ƀu���[�_�[No������܂�
		s32 total[BREEDER_MAX];
		int i, j, t;
		
		for(i = 0; i < BREEDER_MAX; i++){
			ranking[i] = i;
			total[i] = rpw->r_game.gauge_dot[i];
			//���_�������������ꍇ�̔�r�p�Ɋe�u���[�_�[���Ƀ����_���l������
			random[i] = contest_rand(rpw->consys);
		}

		//�����C���l���Ƀ\�[�g���s
		for(i = 0; i < BREEDER_MAX - 1; i++){
			for(j = BREEDER_MAX - 1; j > i; j--){
				if(total[j-1] < total[j] || (total[j-1]==total[j] && random[j-1] < random[j])){
					//�����C���l����ւ�
					t = total[j];
					total[j] = total[j-1];
					total[j-1] = t;
					//�u���[�_�[�ԍ����ꂩ��
					t = ranking[j];
					ranking[j] = ranking[j-1];
					ranking[j-1] = t;
					//�����_���l����ւ�
					t = random[j];
					random[j] = random[j-1];
					random[j-1] = t;
				}
			}
		}
		
		//���ʌ��ʑ��
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.ranking[i] = ranking[i];
			rpw->consys->c_game.score[ranking[i]].final_ranking = i;
			OS_TPrintf("���� %d�� = �u���[�_�[�ԍ�%d\n", i, ranking[i]);
		}
	}
#else
	//�����C���l���珇�ʂ�����
	{
		s32 random[BREEDER_MAX];
		s32 ranking[BREEDER_MAX];	//���ʏ��Ƀu���[�_�[No������܂�
		s32 total[BREEDER_MAX];
		int i, j, t;
		
		for(i = 0; i < BREEDER_MAX; i++){
			ranking[i] = i;
			total[i] = rpw->r_game.total_revise[i];
			//���_�������������ꍇ�̔�r�p�Ɋe�u���[�_�[���Ƀ����_���l������
			random[i] = contest_rand(rpw->consys);
		}

		//�����C���l���Ƀ\�[�g���s
		for(i = 0; i < BREEDER_MAX - 1; i++){
			for(j = BREEDER_MAX - 1; j > i; j--){
				if(total[j-1] < total[j] || (total[j-1]==total[j] && random[j-1] < random[j])){
					//�����C���l����ւ�
					t = total[j];
					total[j] = total[j-1];
					total[j-1] = t;
					//�u���[�_�[�ԍ����ꂩ��
					t = ranking[j];
					ranking[j] = ranking[j-1];
					ranking[j-1] = t;
					//�����_���l����ւ�
					t = random[j];
					random[j] = random[j-1];
					random[j-1] = t;
				}
			}
		}
		
		//���ʌ��ʑ��
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.ranking[i] = ranking[i];
			rpw->consys->c_game.score[ranking[i]].final_ranking = i;
			OS_TPrintf("���� %d�� = �u���[�_�[�ԍ�%d\n", i, ranking[i]);
		}
	}

	//1�ʂ̓��_����Ɋe�u���[�_�[�������[�^�[�̃p�[�Z���e�[�W���擾
	{
		s32 top_breeder_point;
		
		top_breeder_point = rpw->r_game.total_revise[rpw->r_game.ranking[0]];
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.total_percent[i] = 
				RES_METER_PERCENT_MAX * rpw->r_game.total_revise[i] / top_breeder_point;
			if(rpw->r_game.total_percent[i] == RES_METER_PERCENT_MAX 
					&& i != rpw->r_game.ranking[0]){
				//1�ʂł��Ȃ��̂ɁARES_METER_PERCENT_MAX%�̃Q�[�W�����Ȃ�Ό��Z����
				rpw->r_game.total_percent[i]--;
			}
			OS_TPrintf("�u���[�_�[%d �������[�^�[�����p�[�Z���g = %d\n", i, rpw->r_game.total_percent[i]);
		}
	}
	
	//�擾�����Q�[�W�̃p�[�Z���e�[�W�����ɑ����Q�[�W�h�b�g�����擾
	{
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.gauge_dot[i] = RES_METER_DOT_MAX 
				* rpw->r_game.total_percent[i] / RES_METER_PERCENT_MAX;
			OS_TPrintf("�u���[�_�[%d �������[�^�[�h�b�g�� = %d\n", i, rpw->r_game.gauge_dot[i]);
		}
	}
	
	//�����Q�[�W�h�b�g������A�u���[�_�[���ɓ��_�z���ɉ��������[�^�[�̃h�b�g�����擾
	{
		s32 check_total, hosei_dot;
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.visual_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.visual_revise[i] / rpw->r_game.total_revise[i];
			rpw->r_game.dance_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.dance_revise[i] / rpw->r_game.total_revise[i];
			rpw->r_game.actin_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.actin_revise[i] / rpw->r_game.total_revise[i];
			
			//���喈�ɕ��������Q�[�W�h�b�g�̍��v�������Q�[�W�h�b�g���ɑ���Ȃ��ꍇ��
			//��ԉ҂��ł��鏊�ŕ␳
			check_total = rpw->r_game.visual_dot[i] 
				+ rpw->r_game.dance_dot[i] + rpw->r_game.actin_dot[i];
			hosei_dot = rpw->r_game.gauge_dot[i] - check_total;
			if(hosei_dot > 0){
				if(rpw->r_game.visual_dot[i] > rpw->r_game.dance_dot[i] 
						&& rpw->r_game.visual_dot[i] > rpw->r_game.actin_dot[i]
						&& rpw->r_game.visual_dot[i] > 0){
					rpw->r_game.visual_dot[i] += hosei_dot;
					OS_TPrintf("�u���[�_�[%d �r�W���A���h�b�g�ɑ΂��ĕ␳��%d\n", i, hosei_dot);
				}
				else if(rpw->r_game.dance_dot[i] > rpw->r_game.visual_dot[i] 
						&& rpw->r_game.dance_dot[i] > rpw->r_game.actin_dot[i]
						&& rpw->r_game.dance_dot[i] > 0){
					rpw->r_game.dance_dot[i] += hosei_dot;
					OS_TPrintf("�u���[�_�[%d �_���X�h�b�g�ɑ΂��ĕ␳��%d\n", i, hosei_dot);
				}
				else if(rpw->r_game.actin_dot[i] > rpw->r_game.visual_dot[i] 
						&& rpw->r_game.actin_dot[i] > rpw->r_game.dance_dot[i]
						&& rpw->r_game.actin_dot[i] > 0){
					rpw->r_game.actin_dot[i] += hosei_dot;
					OS_TPrintf("�u���[�_�[%d ���Z�h�b�g�ɑ΂��ĕ␳��%d\n", i, hosei_dot);
				}
			}
			OS_TPrintf("�u���[�_�[%d �r�W���A�������h�b�g��=%d\n", i, rpw->r_game.visual_dot[i]);
			OS_TPrintf("�u���[�_�[%d �_���X�����h�b�g��=%d\n", i, rpw->r_game.dance_dot[i]);
			OS_TPrintf("�u���[�_�[%d ���Z�����h�b�g��=%d\n", i, rpw->r_game.actin_dot[i]);
		}
	}
#endif
}

