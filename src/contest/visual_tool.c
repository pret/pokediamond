//==============================================================================
/**
 * @file	visual_tool.c
 * @brief	ビジュアル部門ツール類
 * @author	matsuda
 * @date	2005.12.10(土)
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
//	定数定義
//==============================================================================
///観客ハートの角度加算値(FX32)
#define AUDIENCE_HEART_ADD_ANGLE		(6 << FX32_SHIFT)
///観客ハートのふり幅
#define AUDIENCE_HEART_FURIHABA			(8)
///観客ハートのY座標加算値(下位8ビット少数)
#define AUDIENCE_HEART_ADD_Y			(0x0100)
///観客ハートの終了までのフレーム数
#define AUDIENCE_HEART_END_FRAME		(60)


//==============================================================================
//	構造体定義
//==============================================================================
///観客ハート動作用ワーク
typedef struct{
	u8 *count_work;			///<動作中のハートの数をカウントするための共通ワークへのポインタ
	CATS_ACT_PTR cap;		///<ハートアクターへのポインタ
	s32 x;					///<下位８ビット小数
	s32 y;					///<下位８ビット小数
	fx32 angle;				///<角度(下位８ビット小数)
	u8 seq;					///<シーケンス番号
	u16 frame;				///<生成されてからのフレーム数をカウント
}AUDIENCE_HEART_WORK;


//==============================================================================
//	アクターヘッダ
//==============================================================================
///観客ハートアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S AudienceHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, V_AUDIENCE_HEART_SOFTPRI, PALOFS_SUB_AUDIENCE_HEART,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		V_CHARID_AUDIENCE_HEART,	//キャラ
		V_PLTTID_OBJ_COMMON_SUB,	//パレット
		V_CELLID_AUDIENCE_HEART,	//セル
		V_CELLANMID_AUDIENCE_HEART,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	V_AUDIENCE_HEART_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

//==============================================================================
//	データ
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ビジュアル部門ノーマル会話メッセージデータ ※A_TALK_VISUAL_???の定義と並びを同じにしておく事！！
static const VISUAL_MESSAGE_PARAM VisualTalkMsgData[] = {
	{0,									VTAG_NONE},	//ダミー

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
//	プロトタイプ宣言
//==============================================================================
static void AudienceHeartMoveTask(TCB_PTR tcb, void *work);



//--------------------------------------------------------------
/**
 * @brief   ソフトウェアスプライト(ポケモン)を生成する
 *
 * @param   sys				ビジュアルシステムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
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
	
	//表示OFF
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_VANISH, TRUE);
//	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_DRAW_STOP, TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を生成する
 *
 * @param   sys		ビジュアルシステムワークへのポインタ
 * @param   pp		全ブリーダーのポケモンパラメータが入っている配列へのポインタ
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
 * @brief   ソフトウェアスプライト(ポケモン)を削除する
 *
 * @param   sys				ビジュアルシステムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
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
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を削除する
 * @param   sys		ビジュアルシステムワークへのポインタ
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
 * @brief   観客ハートのリソースロードする
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void VT_AudienceHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし
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
 * @brief   観客ハートのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void VT_AudienceHeartResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, V_CHARID_AUDIENCE_HEART);
	CATS_FreeResourceCell(crp, V_CELLID_AUDIENCE_HEART);
	CATS_FreeResourceCellAnm(crp, V_CELLANMID_AUDIENCE_HEART);
}

//--------------------------------------------------------------
/**
 * @brief   観客ハートのアクターを生成する
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   x			表示座標X
 * @param   y			表示座標Y
 * @param   angle		初期角度(FX32)
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
 * @brief   観客ハートのアクター動作タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		観客ハート動作用ワークへのポインタ
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
 * @brief   トレーナーを生成
 * @param   vpw				ビジュアル部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
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
 * @brief   トレーナーを削除
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
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
 * @brief   メッセージタグ展開
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
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
		GF_ASSERT(0 && "認識できないタグです\n");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージセット
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   msg_id		メッセージID
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
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
 * @brief   ノーマル会話用のメッセージセット
 *
 * @param   vpw				演技力部門管理ワークへのポインタ
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
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
 * @brief   会話メッセージフォントが表示しきっているかチェック
 * @param   dpw		ビジュアル部門管理ワークへのポインタ
 * @retval  0=終了
 */
//--------------------------------------------------------------
int VT_TalkMessageEndCheck(VISUAL_PROC_WORK *vpw)
{
	return GF_MSG_PrintEndCheck(vpw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   BP評価時に出すメッセージのIDを取得する
 * @param   con_type		CONTYPE_???
 * @retval  A_TALK用メッセージID
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


