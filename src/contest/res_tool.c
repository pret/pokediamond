//==============================================================================
/**
 * @file	res_tool.c
 * @brief	結果発表画面ツール類
 * @author	matsuda
 * @date	2006.03.17(金)
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
//	定数定義
//==============================================================================
///ウィンドウを開く最大ドット数
#define WNDOPEN_EFF_OPEN_Y_DOT		(12*8)
///ウィンドウを開く速度(下位8ビット小数)
#define WNDOPEN_EFF_ADD_Y			(0x0400)

///ポケモンスライド：移動速度X(下位8ビット小数)
#define POKESLIDE_ADD_X		(0x0800)

///紙ふぶき初期生成数
#define CONFETTI_INIT_CREATE_NUM	(8)
///紙ふぶき同時生成最大数
#define CONFETTI_CREATE_MAX		(48)
///紙ふぶき生成間隔
#define CONFETTI_CREATE_WAIT	(6)

///紙ふぶき：生成開始座標Y
#define CONFETTI_START_Y		(-16)	//(192/2 - WNDOPEN_EFF_OPEN_Y_DOT/2 - 16)
///紙ふぶき：生成開始座標Yランダム値
#define CONFETTI_START_Y_RND	(96-32)
///紙ふぶき：終了座標Y
#define CONFETTI_END_Y			(192+16)	//(192/2 + WNDOPEN_EFF_OPEN_Y_DOT/2 + 16)
///紙ふぶき：X方向最低移動速度(下位8ビット小数)
#define CONFETTI_ADD_X			(0x0030)
///紙ふぶき：X方向ランダム移動速度
#define CONFETTI_RND_X			(0x0100)
///紙ふぶき：Y方向移動速度
#define CONFETTI_ADD_Y			(0x0200)
///紙ふぶき：Sinカーブ最低角度加算値(下位8ビット小数)
#define CONFETTI_ADD_ANGLE		(0x0000)
///紙ふぶき：Sinカーブ角度加算ランダム値
#define CONFETTI_RND_ANGLE		(0x0300)
///紙ふぶき：Sinカーブふり幅
#define CONFETTI_FURIHABA_X		(16)
///紙ふぶき：Sinカーブふり幅ランダム値
#define CONFETTI_FURIHABA_X_RND	(24)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///アクティブモード計算比率(整数100倍、以下小数)：ビジュアル
#define CONRESULT_GAME_PERCENT_ACTIVE_VISUAL	(70 * 100)
///アクティブモード計算比率(整数100倍、以下小数)：ダンス
#define CONRESULT_GAME_PERCENT_ACTIVE_DANCE		(30 * 100)

///チャームモード計算比率(整数100倍、以下小数)：ビジュアル
#define CONRESULT_GAME_PERCENT_CHARM_VISUAL		(60 * 100)
///チャームモード計算比率(整数100倍、以下小数)：演技
#define CONRESULT_GAME_PERCENT_CHARM_ACTIN		(40 * 100)

///グランドモード計算比率(整数100倍、以下小数)：ビジュアル
#define CONRESULT_GAME_PERCENT_GRAND_VISUAL		(3333)	//(50 * 100)
///グランドモード計算比率(整数100倍、以下小数)：ダンス
#define CONRESULT_GAME_PERCENT_GRAND_DANCE		(3333)	//(20 * 100)
///グランドモード計算比率(整数100倍、以下小数)：演技
#define CONRESULT_GAME_PERCENT_GRAND_ACTIN		(3333)	//(30 * 100)


//==============================================================================
//	構造体定義
//==============================================================================
///ウィンドウ機能の開け閉じエフェクト用ワーク
typedef struct{
	CONRES_PROC_WORK *rpw;		///<結果発表管理ワークへのポインタ
	u8 *end_flag;				///<終了フラグをセットするワークへのポインタ

	s32 y1;						///<ウィンドウ座標Y(上側)：下位8ビット小数
	s32 y2;						///<ウィンドウ座標Y(下側)：下位8ビット小数
	
	u8 seq;						///<シーケンス番号
}WNDOPEN_EFF_WORK;

///ポケモンスライド登場エフェクト用ワーク
typedef struct{
	SOFT_SPRITE *ss;		///<対象のポケモンソフトウェアスプライトへのポインタ
	u8 *end_flag;			///<終了フラグをセットするワークへのポインタ

	s32 x;					///<座標X(下位8ビット小数)
	s32 y;					///<座標Y(下位8ビット小数)

	u8 seq;					///<シーケンス番号
}POKESLIDE_EFF_WORK;

///紙ふぶき生成管理タスク用ワーク
typedef struct{
	CONRES_PROC_WORK *rpw;
	s16 wait;
}CONFETTI_CREATE_WORK;

///紙ふぶきアクター動作用ワーク
typedef struct{
	CONRES_PROC_WORK *rpw;		///<結果発表管理ワークへのポインタ
	CATS_ACT_PTR cap;			///<紙ふぶきアクターへのポインタ
	s32 x;						///<表示座標X(下位8ビット小数)
	s32 y;						///<表示座標Y(下位8ビット小数)
	s16 dx;						///<表示オフセット座標X
	s16 furihaba;				///<Sinカーブふり幅
	s32 add_x;					///<座標X加算値(下位8ビット小数)
	s32 add_angle;				///<角度加算値(下位8ビット小数)
	s32 angle;					///<現在角度(下位8ビット小数)
}CONFETTI_WORK;

//==============================================================================
//	プロトタイプ宣言
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
//	データ
//==============================================================================
///ポケモン表示座標
ALIGN4 static const s16 ConresPokePos[BREEDER_MAX][3] = {	//X, Y, Z
	{44, 70, CONRES_POKEPOS_Z_MAIN},
	{44+56, 70, CONRES_POKEPOS_Z_SUB},
	{44+56*2, 70, CONRES_POKEPOS_Z_SUB},
	{44+56*3, 70, CONRES_POKEPOS_Z_SUB},
};

///ポケモンアイコン表示座標
static const struct{
	s16 x;
	s16 y;
}PokeIconPos[] = {
	{8*3+4, 8*2+4 + 32*0},
	{8*3+4, 8*2+4 + 32*1},
	{8*3+4, 8*2+4 + 32*2},
	{8*3+4, 8*2+4 + 32*3},
};

///順位アイコン表示座標
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
///ダンス部門ノーマル会話メッセージデータ	※A_TALK_CONRES_???の定義と並びを同じにしておく事！！
static const CONRES_MESSAGE_PARAM ConresTalkMsgData[] = {
	{0,									CRTAG_NONE},	//ダミー
	{msg_con_tally_host_01,				CRTAG_NONE},
	{msg_con_tally_host_02,				CRTAG_NONE},
	{msg_con_tally_host_03,				CRTAG_NONE},
	{msg_con_tally_host_04,				CRTAG_NONE},
	{msg_con_tally_host_05,				CRTAG_NUM_OYA_NICK},
	{msg_con_tally_host_06,				CRTAG_NONE},
};


//==============================================================================
//	アクターヘッダ
//==============================================================================
///ポケモンアイコン：アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S PokeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, R_POKEICON_SOFTPRI, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		R_CHARID_POKEICON_0,				//キャラ
		R_PLTTID_POKEICON,				//パレット
		R_CELLID_POKEICON,				//セル
		R_CELLANMID_POKEICON,				//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	R_POKEICON_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///紙ふぶき：アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ConfettiObjParam = {
	0, 0, 0,		//x, y, z
	0, R_CONFETTI_SOFTPRI, R_PALOFS_CONFETTI,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		R_CHARID_CONFETTI,				//キャラ
		R_PLTTID_OBJ_COMMON,				//パレット
		R_CELLID_CONFETTI,				//セル
		R_CELLANMID_CONFETTI,				//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	R_CONFETTI_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///順位アイコン：アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S RankingIconObjParam = {
	0, 0, 0,		//x, y, z
	0, R_RANKING_SOFTPRI, R_PALOFS_RANKING,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		R_CHARID_RANKING,				//キャラ
		R_PLTTID_OBJ_COMMON,				//パレット
		R_CELLID_RANKING,				//セル
		R_CELLANMID_RANKING,				//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	R_RANKING_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///メーター：アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S MeterObjParam = {
	0, 0, 0,		//x, y, z
	0, R_METER_SOFTPRI, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		R_CHARID_METER,				//キャラ
		R_PLTTID_METER,				//パレット
		R_CELLID_METER,				//セル
		R_CELLANMID_METER,				//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	R_METER_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};




//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を生成する
 *
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を削除する
 * @param   sys		ダンスシステムワークへのポインタ
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
 * @brief   メッセージタグ展開
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
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
		GF_ASSERT(0 && "認識できないタグです\n");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージセット
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   msg_id		メッセージID
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
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
 * @brief   ノーマル会話用のメッセージセット
 *
 * @param   rpw				結果発表管理ワークへのポインタ
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara			タグ展開する場合、参照されるパラメータ類
 *                  	    (タグによっては必要ないので、その場合、NULLでもOK)
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
 * @brief   会話メッセージフォントが表示しきっているかチェック
 * @param   rpw		結果発表管理ワークへのポインタ
 * @retval  0=終了
 */
//--------------------------------------------------------------
int RT_TalkMessageEndCheck(CONRES_PROC_WORK *rpw)
{
	return GF_MSG_PrintEndCheck(rpw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   披露画面：基本BGデータをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Announce_BGSet(CONRES_PROC_WORK *rpw)
{
	WINTYPE win_type;
	
	//キャラクタ
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_BG_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	//スクリーン
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_BG_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	GF_BGL_ScrClear(rpw->sys.bgl, CONRES_FRAME_WIN);

	//パレット
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_BG_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0, 0);
	//フォント用パレット
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, RES_BMPWIN_TALK_COLOR * 16);


	//会話ウィンドウ
	win_type = CONFIG_GetWindowType(rpw->consys->config);
	TalkWinGraphicSet(rpw->sys.bgl, CONRES_FRAME_WIN, CONRES_TALKWIN_CGX_OFFSET, 
		CONRES_TALKWIN_BACK_COLOR, win_type, HEAPID_CONRES);
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, CONRES_TALKWIN_PALNO * 16);

#if 0
	//どんちょう
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
 * @brief   披露画面：基本BGデータの削除処理
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Announce_BGDel(CONRES_PROC_WORK *rpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   披露画面：基本BGデータをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   披露画面：基本BGデータの削除処理
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   結果発表画面：基本BGデータをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Result_BGSet(CONRES_PROC_WORK *rpw)
{
	WINTYPE win_type;
	
	//キャラクタ
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_KEKKA_BG_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	//スクリーン
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_KEKKA00_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_BACKGROUND, 0, 0, 1, HEAPID_CONRES);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_KEKKA01_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_EFF, 0, 0, 1, HEAPID_CONRES);
	GF_BGL_ScrClear(rpw->sys.bgl, CONRES_FRAME_WIN);

	//パレット
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CONTEST_KEKKA_BG_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0, 0);
	//フォント用パレット
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, RES_BMPWIN_TALK_COLOR * 16);


	//会話ウィンドウ
	win_type = CONFIG_GetWindowType(rpw->consys->config);
	TalkWinGraphicSet(rpw->sys.bgl, CONRES_FRAME_WIN, CONRES_TALKWIN_CGX_OFFSET, 
		CONRES_TALKWIN_BACK_COLOR, win_type, HEAPID_CONRES);
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_CONRES, FADE_MAIN_BG, 0x20, CONRES_TALKWIN_PALNO * 16);

	//ニックネーム＆親名 描画
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

	//レジスタ設定
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
 * @brief   結果発表サブ画面：基本BGデータをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Result_BGSet_Sub(CONRES_PROC_WORK *rpw)
{
	//色を全て真っ黒にしておく(画面が見えないように)
	PaletteWork_Clear(rpw->sys.pfd, FADE_SUB_BG, FADEBUF_ALL, 0x0000, 0, 16*16);
	PaletteWork_Clear(rpw->sys.pfd, FADE_SUB_OBJ, FADEBUF_ALL, 0x0000, 0, 16*16);
}

//--------------------------------------------------------------
/**
 * @brief   結果発表画面：基本BGデータの削除処理
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Result_BGDel(CONRES_PROC_WORK *rpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   結果発表画面：基本BGデータをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_Result_OBJSet(CONRES_PROC_WORK *rpw)
{
	//常駐OBJパレットロード
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
 * @brief   結果発表画面：基本BGデータの削除処理
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   ポケモンアイコンを全てセット
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_PokeIconSetAll(CONRES_PROC_WORK *rpw)
{
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	int breeder_no, i;
	
	//パレット
	CATS_LoadResourcePlttWorkArc(rpw->sys.pfd, FADE_MAIN_OBJ, rpw->sys.csp, rpw->sys.crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, POKEICON_PAL_MAX, 
		NNS_G2D_VRAM_TYPE_2DMAIN, R_PLTTID_POKEICON);
	//セル
	CATS_LoadResourceCellArc(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
		PokeIcon64kCellArcIndexGet(), 0, R_CELLID_POKEICON);
	//セルアニメ
	CATS_LoadResourceCellAnmArc(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
		PokeIcon64kCellAnmArcIndexGet(), 0, R_CELLANMID_POKEICON);
	
	//アクター生成
	obj_param = PokeIconObjParam;
	for(i = 0; i < BREEDER_MAX; i++){
		//キャラリソース
		CATS_LoadResourceCharArcModeAdjustAreaCont(rpw->sys.csp, rpw->sys.crp, ARC_POKEICON, 
			PokeIconCgxArcIndexGetByPP(rpw->consys->c_game.pp[i]),
			0, NNS_G2D_VRAM_TYPE_2DMAIN, R_CHARID_POKEICON_0 + i);

		obj_param.id[CLACT_U_CHAR_RES] = R_CHARID_POKEICON_0 + i;
		rpw->sys.pokeicon_cap[i] = CATS_ObjectAdd_S(rpw->sys.csp, rpw->sys.crp, &obj_param);
		CATS_ObjectAnimeSeqSetCap(rpw->sys.pokeicon_cap[i], POKEICON_ANM_HPMAX);
		
		//パレット切り替え
	//	monsno = PokeParaGet(rpw->consys->c_game.pp[i], ID_PARA_monsno, NULL);
	//	egg = PokeParaGet(rpw->consys->c_game.pp[i], ID_PARA_tamago_flag, NULL);
		CLACT_PaletteOffsetChgAddTransPlttNo(rpw->sys.pokeicon_cap[i]->act, 
			PokeIconPalNumGetByPP(rpw->consys->c_game.pp[i]));
		
		CATS_ObjectUpdateCap(rpw->sys.pokeicon_cap[i]);
	}
	
	//座標セット
	for(i = 0; i < BREEDER_MAX; i++){
		breeder_no = rpw->r_game.breeder_sort[i];
		CATS_ObjectPosSetCap(rpw->sys.pokeicon_cap[breeder_no], 
			PokeIconPos[i].x, PokeIconPos[i].y);
	}
	
	//アニメ更新用タスク生成
	rpw->sys.pokeicon_tcb = TCB_Add(PokeIconUpdate, rpw, TCBPRI_POKEICON_UPDATE);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンアイコンを全て削除
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   ポケモンアイコンアニメ更新タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		結果発表管理ワークへのポインタ
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
 * @brief   紙ふぶきのリソースをセット
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   紙ふぶきのリソース解放
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   紙ふぶき生成管理タスクを生成する
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   紙ふぶき全終了フラグをセットする
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_ConfettiEndFlagSet(CONRES_PROC_WORK *rpw)
{
	rpw->confetti_end = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   紙ふぶき生成管理タスクメイン動作
 * @param   tcb			TCBへのポインタ
 * @param   work		紙ふぶき生成
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
 * @brief   紙ふぶきアクター生成
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   紙ふぶきアクターメイン動作
 * @param   tcb			TCBへのポインタ
 * @param   work		紙ふぶきワークへのポインタ
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
 * @brief   順位アイコンを全てセット
 * @param   rpw		結果発表管理ワークへのポインタ
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
			//表示OFF
			CATS_ObjectEnableCap(rpw->sys.ranking_cap[i], CATS_ENABLE_FALSE);
		}
		//座標セット
		for(i = 0; i < BREEDER_MAX; i++){
			breeder_no = rpw->r_game.breeder_sort[i];
			CATS_ObjectPosSetCap(rpw->sys.ranking_cap[breeder_no], 
				RankingIconPos[i].x, RankingIconPos[i].y);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   順位アイコンを全て削除
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   順位アイコンを登場(表示)させる
 *
 * @param   rpw				結果発表管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   ranking			順位
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
 * @brief   メーターのリソースをセット
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   メーターのリソース解放
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_MeterResouceFree(CONRES_PROC_WORK *rpw)
{
	CATS_FreeResourcePltt(rpw->sys.crp, R_PLTTID_METER);
	CATS_FreeResourceChar(rpw->sys.crp, R_CHARID_METER);
	CATS_FreeResourceCell(rpw->sys.crp, R_CELLID_METER);
	CATS_FreeResourceCellAnm(rpw->sys.crp, R_CELLANMID_METER);
}

///メーターの開始座標X
#define RES_METER_START_X		(48)
///メーターの開始座標Y
#define RES_METER_START_Y		(32)
///メーターの座標Yの次のブリーダーまでの間隔ドット数
#define RES_METER_SPACE_Y		(32)

///各メーターの開始アニメシーケンス番号
enum{
	RES_METER_START_ANIM_SPACE = 0,		///<空白
	RES_METER_START_ANIM_VISUAL = 1,	///<ビジュアル用メーター開始シーケンス番号
	RES_METER_START_ANIM_DANCE = 0x11,	///<ダンス用メーター開始シーケンス番号
	RES_METER_START_ANIM_ACTIN = 0x21,	///<演技用メーター開始シーケンス番号
};

//--------------------------------------------------------------
/**
 * @brief   指定ドット数分メーターアクターを生成する
 *
 * @param   rpw				結果発表管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   con_game		CONGAME_???
 * @param   dot				表示ドット数
 * @param   breeder_pos		ブリーダー表示位置
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
	
	//座標開始位置
	x = RES_METER_START_X + start_dot;
	y = RES_METER_START_Y + RES_METER_SPACE_Y * breeder_pos;
	
	//必要なアクター数を算出
	act_num = dot / RES_METER_ACT_SIZE_X;
	if(dot % RES_METER_ACT_SIZE_X != 0){
		act_num++;
	}
	GF_ASSERT(act_num <= RES_METER_CAP_MAX);
	
	//足りないアクター分を生成
	for(i = 0; i < act_num; i++){
		if(cap_array[i] == NULL){
			cap_array[i] = CATS_ObjectAdd_S(rpw->sys.csp, rpw->sys.crp, &MeterObjParam);
		}
	}
	
	//ドット数に合わせてアニメ
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
 * @brief   メーターアクターを全て削除する
 * @param   rpw		結果発表管理ワークへのポインタ
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
 * @brief   ウィンドウ機能の開け閉じエフェクト開始
 *
 * @param   open_close		RT_WNDEFF_OPEN or RT_WNDEFF_CLOSE
 * @param   end_flag		エフェクト終了後、このワークにTRUEがセットされます
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
 * @brief   ウィンドウ機能：オープンエフェクト実行
 * @param   tcb			TCBへのポインタ
 * @param   work		WNDOPEN_EFF_WORK構造体
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
		//left=0, right=255でやると右端が1ドット残るので2枚使って無理矢理囲む
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
 * @brief   ウィンドウ機能：クローズエフェクト実行
 * @param   tcb			TCBへのポインタ
 * @param   work		WNDOPEN_EFF_WORK構造体
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
		//left=0, right=255でやると右端が1ドット残るので2枚使って無理矢理囲む
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
 * @brief   ポケモンスライド登場エフェクト開始
 *
 * @param   rpw				結果発表管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   in_out			RT_POKESLIDE_IN or RT_POKESLIDE_OUT
 * @param   end_flag		エフェクト終了後、このワークにTRUEがセットされます
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
 * @brief   ポケモンスライド登場：画面外から登場
 * @param   tcb			TCBへのポインタ
 * @param   work		POKESLIDE_EFF_WORK構造体
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
 * @brief   ポケモンスライド登場：画面内から画面外へ
 * @param   tcb			TCBへのポインタ
 * @param   work		POKESLIDE_EFF_WORK構造体
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
 * @brief   参加しているコンテストモードから、参加した競技の持つ計算比率を取得する
 *
 * @param   consys		コンテストシステムワークへのポインタ
 * @param   con_game	CONGAME_???
 *
 * @retval  計算比率(整数100倍、以下小数)
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
			//GF_ASSERT(0 && "用意されていない計算式");
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
			//GF_ASSERT(0 && "用意されていない計算式");
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
			//GF_ASSERT(0 && "用意されていない計算式");
			return 0;
		}
		break;
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_VISUAL_TUTORIAL:
		if(con_game == CONGAME_VISUAL){
			return 10000;
		}
		//GF_ASSERT(0 && "用意されていない計算式");
		return 0;
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_DANCE_TUTORIAL:
		if(con_game == CONGAME_DANCE){
			return 10000;
		}
		//GF_ASSERT(0 && "用意されていない計算式");
		return 0;
	case CONMODE_ACTIN_PRACTICE:
	case CONMODE_ACTIN_TUTORIAL:
		if(con_game == CONGAME_ACTIN){
			return 10000;
		}
		//GF_ASSERT(0 && "用意されていない計算式");
		return 0;
	default:
		//GF_ASSERT(0 && "用意されていない計算式");
		return 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   参加しているコンテストモードから、参加した競技の持つ最大ドット数を取得する
 *
 * @param   consys		コンテストシステムワークへのポインタ
 * @param   con_game	CONGAME_???
 *
 * @retval  最大ドット数
 */
//--------------------------------------------------------------
static int RT_CalcGameDotGet(CONTEST_SYSTEM *consys, int con_game)
{
	int percent, dot;
	
	percent = RT_CalcGamePercentGet(consys, con_game);
	dot = RES_METER_DOT_MAX * percent;
	dot = (dot + 5000) / 10000;		//四捨五入して整数化
	return dot;
}

//--------------------------------------------------------------
/**
 * @brief   各部門の得点修正値を取得
 *
 * @param   consys		コンテストシステムワークへのポインタ
 * @param   con_game	CONGAME_???
 * @param   ret_revise	得点修正値代入先(BREEDER_MAX分の配列)
 *
 * ※演技部門でも使用します。
 */
//--------------------------------------------------------------
void RT_CalcRevicePoint(CONTEST_SYSTEM *consys, int con_game, s16 ret_revise[])
{
	int total_point[BREEDER_MAX];
	int revise_point[BREEDER_MAX];
	int percent, bairitu, i, top_breeder;
	
	//ここまでの得点を求める
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
	
	//得点トップのブリーダーを求める
	top_breeder = 0;
	for(i = 1; i < BREEDER_MAX; i++){
		if(total_point[top_breeder] < total_point[i]){
			top_breeder = i;
		}
	}
	
	//倍率取得
	percent = RT_CalcGamePercentGet(consys, con_game);
	bairitu = percent / total_point[top_breeder];
	
	//修正値
	for(i = 0; i < BREEDER_MAX; i++){
		revise_point[i] = total_point[i] * bairitu;
		revise_point[i] = (revise_point[i] + 50) / 100;	//四捨五入
	}
	
	//結果代入
	for(i = 0; i < BREEDER_MAX; i++){
		switch(con_game){
		case CONGAME_VISUAL:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("ブリーダー%d ビジュアル修正値＝%d\n", i, ret_revise[i]);
			break;
		case CONGAME_DANCE:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("ブリーダー%d ダンス修正値＝%d\n", i, ret_revise[i]);
			break;
		case CONGAME_ACTIN:
			ret_revise[i] = revise_point[i];
			OS_TPrintf("ブリーダー%d 演技修正値＝%d\n", i, ret_revise[i]);
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ここまでの全てのゲームの得点を計算、メーターのドット数を算出
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void RT_CalcPoint(CONRES_PROC_WORK *rpw)
{
	int i;
	
	//各部門の修正値計算
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
	
	//総合修正値
	for(i = 0; i < BREEDER_MAX; i++){
		rpw->r_game.total_revise[i] = rpw->r_game.visual_revise[i] 
			+ rpw->r_game.dance_revise[i] + rpw->r_game.actin_revise[i];
		OS_TPrintf("ブリーダー%d 総合修正値＝%d\n", i, rpw->r_game.total_revise[i]);
	}
	
#if 1
	//1位の得点を基準に各ブリーダーが持つメーターの各部門のパーセンテージを取得
	{
		s32 top_breeder_point, top_breeder;
		
		//ビジュアル
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
			OS_TPrintf("ブリーダー%d ビジュアルメーター所持パーセント = %d\n", i, rpw->r_game.visual_percent[i]);
		}

		//ダンス
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
			OS_TPrintf("ブリーダー%d ダンスメーター所持パーセント = %d\n", i, rpw->r_game.dance_percent[i]);
		}

		//演技
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
			OS_TPrintf("ブリーダー%d 演技メーター所持パーセント = %d\n", i, rpw->r_game.actin_percent[i]);
		}
	}
	
	//各部門のゲージドット数を取得
	{
		int max_dot;
		
		//ビジュアル
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_VISUAL);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.visual_dot[i] = max_dot * rpw->r_game.visual_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("ブリーダー%d ビジュアル所持ドット数 = %d\n", i, rpw->r_game.visual_dot[i]);
		}

		//ダンス
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_DANCE);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.dance_dot[i] = max_dot * rpw->r_game.dance_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("ブリーダー%d ダンス所持ドット数 = %d\n", i, rpw->r_game.dance_dot[i]);
		}

		//演技
		max_dot = RT_CalcGameDotGet(rpw->consys, CONGAME_ACTIN);
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.actin_dot[i] = max_dot * rpw->r_game.actin_percent[i] 
				/ RES_METER_PERCENT_MAX;
			OS_TPrintf("ブリーダー%d 演技所持ドット数 = %d\n", i, rpw->r_game.actin_dot[i]);
		}
		
		//総合
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.gauge_dot[i] = rpw->r_game.visual_dot[i] + rpw->r_game.dance_dot[i]
				+ rpw->r_game.actin_dot[i];
		}
	}

	//総合ドット数から順位を決定
	{
		s32 random[BREEDER_MAX];
		s32 ranking[BREEDER_MAX];	//順位順にブリーダーNoが入ります
		s32 total[BREEDER_MAX];
		int i, j, t;
		
		for(i = 0; i < BREEDER_MAX; i++){
			ranking[i] = i;
			total[i] = rpw->r_game.gauge_dot[i];
			//得点が同じだった場合の比較用に各ブリーダー毎にランダム値を持つ
			random[i] = contest_rand(rpw->consys);
		}

		//総合修正値順にソート実行
		for(i = 0; i < BREEDER_MAX - 1; i++){
			for(j = BREEDER_MAX - 1; j > i; j--){
				if(total[j-1] < total[j] || (total[j-1]==total[j] && random[j-1] < random[j])){
					//総合修正値入れ替え
					t = total[j];
					total[j] = total[j-1];
					total[j-1] = t;
					//ブリーダー番号入れかえ
					t = ranking[j];
					ranking[j] = ranking[j-1];
					ranking[j-1] = t;
					//ランダム値入れ替え
					t = random[j];
					random[j] = random[j-1];
					random[j-1] = t;
				}
			}
		}
		
		//順位結果代入
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.ranking[i] = ranking[i];
			rpw->consys->c_game.score[ranking[i]].final_ranking = i;
			OS_TPrintf("順位 %d位 = ブリーダー番号%d\n", i, ranking[i]);
		}
	}
#else
	//総合修正値から順位を決定
	{
		s32 random[BREEDER_MAX];
		s32 ranking[BREEDER_MAX];	//順位順にブリーダーNoが入ります
		s32 total[BREEDER_MAX];
		int i, j, t;
		
		for(i = 0; i < BREEDER_MAX; i++){
			ranking[i] = i;
			total[i] = rpw->r_game.total_revise[i];
			//得点が同じだった場合の比較用に各ブリーダー毎にランダム値を持つ
			random[i] = contest_rand(rpw->consys);
		}

		//総合修正値順にソート実行
		for(i = 0; i < BREEDER_MAX - 1; i++){
			for(j = BREEDER_MAX - 1; j > i; j--){
				if(total[j-1] < total[j] || (total[j-1]==total[j] && random[j-1] < random[j])){
					//総合修正値入れ替え
					t = total[j];
					total[j] = total[j-1];
					total[j-1] = t;
					//ブリーダー番号入れかえ
					t = ranking[j];
					ranking[j] = ranking[j-1];
					ranking[j-1] = t;
					//ランダム値入れ替え
					t = random[j];
					random[j] = random[j-1];
					random[j-1] = t;
				}
			}
		}
		
		//順位結果代入
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.ranking[i] = ranking[i];
			rpw->consys->c_game.score[ranking[i]].final_ranking = i;
			OS_TPrintf("順位 %d位 = ブリーダー番号%d\n", i, ranking[i]);
		}
	}

	//1位の得点を基準に各ブリーダーが持つメーターのパーセンテージを取得
	{
		s32 top_breeder_point;
		
		top_breeder_point = rpw->r_game.total_revise[rpw->r_game.ranking[0]];
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.total_percent[i] = 
				RES_METER_PERCENT_MAX * rpw->r_game.total_revise[i] / top_breeder_point;
			if(rpw->r_game.total_percent[i] == RES_METER_PERCENT_MAX 
					&& i != rpw->r_game.ranking[0]){
				//1位でもないのに、RES_METER_PERCENT_MAX%のゲージ所持ならば減算する
				rpw->r_game.total_percent[i]--;
			}
			OS_TPrintf("ブリーダー%d 総合メーター所持パーセント = %d\n", i, rpw->r_game.total_percent[i]);
		}
	}
	
	//取得したゲージのパーセンテージを元に総合ゲージドット数を取得
	{
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.gauge_dot[i] = RES_METER_DOT_MAX 
				* rpw->r_game.total_percent[i] / RES_METER_PERCENT_MAX;
			OS_TPrintf("ブリーダー%d 総合メータードット数 = %d\n", i, rpw->r_game.gauge_dot[i]);
		}
	}
	
	//総合ゲージドット数から、ブリーダー毎に得点配分に応じたメーターのドット数を取得
	{
		s32 check_total, hosei_dot;
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.visual_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.visual_revise[i] / rpw->r_game.total_revise[i];
			rpw->r_game.dance_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.dance_revise[i] / rpw->r_game.total_revise[i];
			rpw->r_game.actin_dot[i] = rpw->r_game.gauge_dot[i] 
				* rpw->r_game.actin_revise[i] / rpw->r_game.total_revise[i];
			
			//部門毎に分割したゲージドットの合計が総合ゲージドット数に足りない場合は
			//一番稼いでいる所で補正
			check_total = rpw->r_game.visual_dot[i] 
				+ rpw->r_game.dance_dot[i] + rpw->r_game.actin_dot[i];
			hosei_dot = rpw->r_game.gauge_dot[i] - check_total;
			if(hosei_dot > 0){
				if(rpw->r_game.visual_dot[i] > rpw->r_game.dance_dot[i] 
						&& rpw->r_game.visual_dot[i] > rpw->r_game.actin_dot[i]
						&& rpw->r_game.visual_dot[i] > 0){
					rpw->r_game.visual_dot[i] += hosei_dot;
					OS_TPrintf("ブリーダー%d ビジュアルドットに対して補正＝%d\n", i, hosei_dot);
				}
				else if(rpw->r_game.dance_dot[i] > rpw->r_game.visual_dot[i] 
						&& rpw->r_game.dance_dot[i] > rpw->r_game.actin_dot[i]
						&& rpw->r_game.dance_dot[i] > 0){
					rpw->r_game.dance_dot[i] += hosei_dot;
					OS_TPrintf("ブリーダー%d ダンスドットに対して補正＝%d\n", i, hosei_dot);
				}
				else if(rpw->r_game.actin_dot[i] > rpw->r_game.visual_dot[i] 
						&& rpw->r_game.actin_dot[i] > rpw->r_game.dance_dot[i]
						&& rpw->r_game.actin_dot[i] > 0){
					rpw->r_game.actin_dot[i] += hosei_dot;
					OS_TPrintf("ブリーダー%d 演技ドットに対して補正＝%d\n", i, hosei_dot);
				}
			}
			OS_TPrintf("ブリーダー%d ビジュアル所持ドット数=%d\n", i, rpw->r_game.visual_dot[i]);
			OS_TPrintf("ブリーダー%d ダンス所持ドット数=%d\n", i, rpw->r_game.dance_dot[i]);
			OS_TPrintf("ブリーダー%d 演技所持ドット数=%d\n", i, rpw->r_game.actin_dot[i]);
		}
	}
#endif
}

