//==============================================================================
/**
 * @file	visual_tool.c
 * @brief	�r�W���A������c�[����
 * @author	matsuda
 * @date	2005.12.10(�y)
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
#include "msgdata/msg_cmsg_visual.h"

#include "visual.h"
#include "visual_tool.h"
#include "con_tool.h"
#include "visual_id.h"
#include "visual_tcb_pri.h"
#include "savedata/config.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�ϋq�n�[�g�̊p�x���Z�l(FX32)
#define AUDIENCE_HEART_ADD_ANGLE		(6 << FX32_SHIFT)
///�ϋq�n�[�g�̂ӂ蕝
#define AUDIENCE_HEART_FURIHABA			(8)
///�ϋq�n�[�g��Y���W���Z�l(����8�r�b�g����)
#define AUDIENCE_HEART_ADD_Y			(0x0100)
///�ϋq�n�[�g�̏I���܂ł̃t���[����
#define AUDIENCE_HEART_END_FRAME		(60)


//==============================================================================
//	�\���̒�`
//==============================================================================
///�ϋq�n�[�g����p���[�N
typedef struct{
	u8 *count_work;			///<���쒆�̃n�[�g�̐����J�E���g���邽�߂̋��ʃ��[�N�ւ̃|�C���^
	CATS_ACT_PTR cap;		///<�n�[�g�A�N�^�[�ւ̃|�C���^
	s32 x;					///<���ʂW�r�b�g����
	s32 y;					///<���ʂW�r�b�g����
	fx32 angle;				///<�p�x(���ʂW�r�b�g����)
	u8 seq;					///<�V�[�P���X�ԍ�
	u16 frame;				///<��������Ă���̃t���[�������J�E���g
}AUDIENCE_HEART_WORK;


//==============================================================================
//	�A�N�^�[�w�b�_
//==============================================================================
///�ϋq�n�[�g�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S AudienceHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, V_AUDIENCE_HEART_SOFTPRI, PALOFS_SUB_AUDIENCE_HEART,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		V_CHARID_AUDIENCE_HEART,	//�L����
		V_PLTTID_OBJ_COMMON_SUB,	//�p���b�g
		V_CELLID_AUDIENCE_HEART,	//�Z��
		V_CELLANMID_AUDIENCE_HEART,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	V_AUDIENCE_HEART_BGPRI,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

//==============================================================================
//	�f�[�^
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�r�W���A������m�[�}����b���b�Z�[�W�f�[�^ ��A_TALK_VISUAL_???�̒�`�ƕ��т𓯂��ɂ��Ă������I�I
static const VISUAL_MESSAGE_PARAM VisualTalkMsgData[] = {
	{0,									VTAG_NONE},	//�_�~�[

	{msg_con_visual_host_01,			VTAG_NONE},
	{msg_con_v_prac_02,					VTAG_NONE},
	{msg_con_visual_host_02,			VTAG_OYA_NICK},
	{msg_con_visual_host_03,			VTAG_OYA_NICK},
	{msg_con_visual_host_04,			VTAG_OYA_NICK},
	{msg_con_visual_host_05,			VTAG_OYA_NICK},
	{msg_con_visual_host_06,			VTAG_NONE},
	{msg_con_visual_host_07,			VTAG_NONE},
	{msg_con_visual_host_08,			VTAG_NONE},
	{msg_con_visual_host_09,			VTAG_NONE},
	{msg_con_visual_host_10,			VTAG_NONE},
	{msg_con_visual_host_11,			VTAG_NONE},
	{msg_con_visual_host_12,			VTAG_NONE},
	{msg_con_visual_host_13,			VTAG_NONE},
};


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void AudienceHeartMoveTask(TCB_PTR tcb, void *work);



//--------------------------------------------------------------
/**
 * @brief   �\�t�g�E�F�A�X�v���C�g(�|�P����)�𐶐�����
 *
 * @param   sys				�r�W���A���V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void VT_SoftSpriteAdd(VISUAL_SYSTEM_PARAM *sys, int breeder_no)
{
	GF_ASSERT(sys->exchr_param[breeder_no].exchr_buffer == NULL);
	GF_ASSERT(sys->ss[breeder_no] == NULL);
	
	sys->exchr_param[breeder_no].exchr_buffer = sys_AllocMemory(HEAPID_VISUAL, EXCHR_BUFFER_SIZE);
	
	sys->ss[breeder_no] = ConTool_BreederPokemonAdd(sys->soft_sprite, breeder_no, 
		sys->c_game->pp[breeder_no], 
		PARA_FRONT, &sys->exchr_param[breeder_no], HEAPID_VISUAL, 
		VISUAL_APPEAR_X, VISUAL_APPEAR_Y, VISUAL_POKEPOS_Z);
	
	//�\��OFF
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_VANISH, TRUE);
//	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_DRAW_STOP, TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)�𐶐�����
 *
 * @param   sys		�r�W���A���V�X�e�����[�N�ւ̃|�C���^
 * @param   pp		�S�u���[�_�[�̃|�P�����p�����[�^�������Ă���z��ւ̃|�C���^
 */
//--------------------------------------------------------------
void VT_SoftSpriteAddAll(VISUAL_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		VT_SoftSpriteAdd(sys, i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �\�t�g�E�F�A�X�v���C�g(�|�P����)���폜����
 *
 * @param   sys				�r�W���A���V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void VT_SoftSpriteDel(VISUAL_SYSTEM_PARAM *sys, int breeder_no)
{
	if(sys->ss[breeder_no] == NULL){
		GF_ASSERT(sys->exchr_param[breeder_no].exchr_buffer == NULL);
		return;
	}
	
	SoftSpriteDel(sys->ss[breeder_no]);
	sys_FreeMemoryEz(sys->exchr_param[breeder_no].exchr_buffer);
	
	sys->ss[breeder_no] = NULL;
	sys->exchr_param[breeder_no].exchr_buffer = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ẵu���[�_�[�̃\�t�g�E�F�A�X�v���C�g(�|�P����)���폜����
 * @param   sys		�r�W���A���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void VT_SoftSpriteDelAll(VISUAL_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		VT_SoftSpriteDel(sys, i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�n�[�g�̃��\�[�X���[�h����
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void VT_AudienceHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g���g�p����̂Ń��[�h�Ȃ�
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		AUDIENCE_HEART_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, V_CHARID_AUDIENCE_HEART);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		AUDIENCE_HEART_NCER_BIN, 1, 
		V_CELLID_AUDIENCE_HEART);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		AUDIENCE_HEART_NANR_BIN, 1, V_CELLANMID_AUDIENCE_HEART);
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�n�[�g�̃��\�[�X���������
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void VT_AudienceHeartResourceFree(CATS_RES_PTR crp)
{
	//�p���b�g�͏풓�p���b�g�Ȃ̂ō폜�Ȃ�
	CATS_FreeResourceChar(crp, V_CHARID_AUDIENCE_HEART);
	CATS_FreeResourceCell(crp, V_CELLID_AUDIENCE_HEART);
	CATS_FreeResourceCellAnm(crp, V_CELLANMID_AUDIENCE_HEART);
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�n�[�g�̃A�N�^�[�𐶐�����
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   x			�\�����WX
 * @param   y			�\�����WY
 * @param   angle		�����p�x(FX32)
 * @param   anm_type	AUDIENCE_HEART_ANMTYPE_???
 */
//--------------------------------------------------------------
void VT_AudienceHeartActorAdd(VISUAL_PROC_WORK *vpw, int x, int y, fx32 angle, int anm_type)
{
	AUDIENCE_HEART_WORK *heart;
	
	heart = sys_AllocMemory(HEAPID_VISUAL, sizeof(AUDIENCE_HEART_WORK));
	MI_CpuClear8(heart, sizeof(AUDIENCE_HEART_WORK));
	
	heart->cap = CATS_ObjectAdd_S(vpw->sys.csp, vpw->sys.crp, &AudienceHeartObjParam);
	CATS_ObjectPosSetCap_SubSurface(heart->cap, x, y, VISUAL_SUB_ACTOR_DISTANCE);
	if(anm_type == AUDIENCE_HEART_ANMTYPE_CLIP){
		CATS_ObjectAnimeSeqSetCap(heart->cap, 1);
	}
	CATS_ObjectUpdate(heart->cap->act);
	
	heart->x = x << 8;
	heart->y = y << 8;
	heart->count_work = &vpw->heart_count;
	vpw->heart_count++;
	TCB_Add(AudienceHeartMoveTask, heart, TCBPRI_VISUAL_EFFECT);
	
	Snd_SePlay(VSE_AUDIENCE_HEART);
}

//--------------------------------------------------------------
/**
 * @brief   �ϋq�n�[�g�̃A�N�^�[����^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�ϋq�n�[�g����p���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void AudienceHeartMoveTask(TCB_PTR tcb, void *work)
{
	AUDIENCE_HEART_WORK *heart = work;
	s32 offset_x;
	
	switch(heart->seq){
	case 0:
		offset_x = Sin360FX(heart->angle) * AUDIENCE_HEART_FURIHABA / FX32_ONE;
		heart->angle += AUDIENCE_HEART_ADD_ANGLE;
		heart->y -= AUDIENCE_HEART_ADD_Y;
		
		CATS_ObjectPosSetCap_SubSurface(heart->cap, heart->x / 0x0100 + offset_x, 
			heart->y / 0x0100, VISUAL_SUB_ACTOR_DISTANCE);
		
		heart->frame++;
		if(heart->frame >= AUDIENCE_HEART_END_FRAME || heart->y <= (-32*0x0100)){
			heart->seq++;
		}
		break;
	default:
		CATS_ActorPointerDelete_S(heart->cap);
		(*(heart->count_work))--;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief   �g���[�i�[�𐶐�
 * @param   vpw				�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 */
//--------------------------------------------------------------
void VT_TrainerAdd(VISUAL_PROC_WORK *vpw, int breeder_no)
{
	SOFT_SPRITE_ARC	ssa;
	
	GF_ASSERT(vpw->sys.trainer_ss == NULL);
	
	TrTypeGraArcDataGet(&ssa, vpw->consys->c_game.bd[breeder_no].trainer_type);
	vpw->sys.trainer_ss = SoftSpriteAdd(vpw->sys.soft_sprite, &ssa, 
		VISUAL_TRAINER_APPEAR_X, VISUAL_TRAINER_APPEAR_Y, VISUAL_TRAINER_APPEAR_Z,
		3, NULL, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   �g���[�i�[���폜
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void VT_TrainerDel(VISUAL_PROC_WORK *vpw)
{
	if(vpw->sys.trainer_ss == NULL){
		return;
	}
	SoftSpriteDel(vpw->sys.trainer_ss);
	vpw->sys.trainer_ss = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�^�O�W�J
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
static void VT_MessageTagExpand(VISUAL_PROC_WORK *vpw, int msg_tag, const VTAG_PARAM *tagpara)
{
	if(msg_tag != VTAG_NONE){
		GF_ASSERT(tagpara != NULL);
	}
	
	switch(msg_tag){
	case VTAG_NONE:
		break;
	
	case VTAG_OYA_NICK:
		WORDSET_RegisterWord(vpw->sys.wordset, 0, 
			vpw->consys->c_game.breeder_name_str[tagpara->mine_brd], 
			vpw->consys->c_game.player_sex[tagpara->mine_brd], TRUE, PM_LANG);
		WORDSET_RegisterPokeNickName(vpw->sys.wordset, 1, 
			PPPPointerGet(vpw->sys.c_game->pp[tagpara->mine_brd]));
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
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   msg_id		���b�Z�[�WID
 * @param   msg_tag		�^�O�R�[�h
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
static void VT_TalkMessageSet(VISUAL_PROC_WORK *vpw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const VTAG_PARAM *tagpara)
{
	STRBUF *message_src;
	int wait;
	
//	BattleMSG_TagExpand(bw,mp);
//	BattleMSG_MsgExpand(bw,msg_m,mp);
	if(vpw->consys->sio_flag == FALSE){
		wait = CONFIG_GetMsgPrintSpeed(vpw->consys->config);
	}
	else{
		wait = CONTEST_SIO_MSG_SPEED;
	}
	
	message_src = MSGMAN_AllocString(msg_man, msg_id);
	VT_MessageTagExpand(vpw, msg_tag, tagpara);
	WORDSET_ExpandStr(vpw->sys.wordset, vpw->sys.msg_buf, message_src);

	GF_BGL_BmpWinDataFill(&vpw->sys.win[VISUAL_BMPWIN_TALK], 0xff);
	vpw->sys.talk_msg_index = GF_STR_PrintSimple(&vpw->sys.win[VISUAL_BMPWIN_TALK], 
		FONT_TALK, vpw->sys.msg_buf, 0, 0, wait, NULL);

	STRBUF_Delete(message_src);
}

//--------------------------------------------------------------
/**
 * @brief   �m�[�}����b�p�̃��b�Z�[�W�Z�b�g
 *
 * @param   vpw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara		�^�O�W�J����ꍇ�A�Q�Ƃ����p�����[�^��
 *                      (�^�O�ɂ���Ă͕K�v�Ȃ��̂ŁA���̏ꍇ�ANULL�ł�OK)
 */
//--------------------------------------------------------------
void VT_A_TalkMessageSet(VISUAL_PROC_WORK *vpw, u32 a_talk_id, const VTAG_PARAM *tagpara)
{
	u32 msg_id, msg_tag;
	
	GF_ASSERT(a_talk_id < NELEMS(VisualTalkMsgData));
	
	msg_id = VisualTalkMsgData[a_talk_id].msg_id;
	msg_tag = VisualTalkMsgData[a_talk_id].msg_tag;
	VT_TalkMessageSet(vpw, vpw->sys.visual_msg, msg_id, msg_tag, tagpara);
}

//--------------------------------------------------------------
/**
 * @brief   ��b���b�Z�[�W�t�H���g���\���������Ă��邩�`�F�b�N
 * @param   dpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @retval  0=�I��
 */
//--------------------------------------------------------------
int VT_TalkMessageEndCheck(VISUAL_PROC_WORK *vpw)
{
	return GF_MSG_PrintEndCheck(vpw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   BP�]�����ɏo�����b�Z�[�W��ID���擾����
 * @param   con_type		CONTYPE_???
 * @retval  A_TALK�p���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 VT_A_TalkIDGet_BPAppeal(int con_type)
{
	const u16 BPMsgID[] = {
		A_TALK_VISUAL_HOST_08,
		A_TALK_VISUAL_HOST_09,
		A_TALK_VISUAL_HOST_10,
		A_TALK_VISUAL_HOST_11,
		A_TALK_VISUAL_HOST_12,
	};
	
	return BPMsgID[con_type];
}


