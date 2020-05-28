//==============================================================================
/**
 * @file	dance_tool.c
 * @brief	ダンス部門ツール類
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

#include "dance.h"
#include "dance_tool.h"
#include "con_tool.h"
#include "dance_id.h"
#include "dance_tcb_pri.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg_cmsg_dance.h"
#include "system/fontoam.h"

#include "adv_tool.h"
#include "system/window.h"
#include "savedata/config.h"

#include "system/particle.h"
#include "../particledata/particledata.h"
#include "../particledata/particledata.naix"

#include "include/application/imageClip/imc_playsys.h"
#include "poketool/monsno.h"


//==============================================================================
//	定数定義
//==============================================================================
///評価パネルの上のフォントOAMのカラー設定
#define REVIEW_PRINTCOLOR	(GF_PRINTCOLOR_MAKE(0xb, 0xc, 0))

//--------------------------------------------------------------
//	ダンスアニメ移動データ
//--------------------------------------------------------------
///ダンスアニメ：バックダンサーの場合は移動量を補正する。メインダンサーの何%に制限するか
///100だとメインダンサーと同じ
#define MOVE_BACKDANCER_REVISION		(40)

///ダンスアニメ：Finishの時は移動量を補正する。通常の何%UPにするか
///100だと通常と同じ
#define MOVE_FINISHDANCE_REVISION		(200)
///ダンスアニメ：ポイント1点につき何パーセントUPにするか(下位8ビット小数)
#define MOVE_POINT_REVISION				(2 << 8)
///ダンスアニメ：ポイントで増えるパーセントの最大値
#define MOVE_POINT_REVISION_MAX			(100 << 8)

///ダンスアニメ、ジャンプ：ジャンプ力
#define MOVE_JUMP_UP_POWER		(0x0500)

///ダンスアニメ、前進：行きの移動にかけるフレーム数の割合(50%で行き戻り同じ速度)
#define MOVE_ADVANCE_GO_FRAME_PARCENT		(30)
///ダンスアニメ、前進：戻りの移動にかけるフレーム数の割合(50%で行き戻り同じ速度)
#define MOVE_ADVANCE_BACK_FRAME_PARCENT		(100 - MOVE_ADVANCE_GO_FRAME_PARCENT)
///ダンスアニメ、前進：前に移動するドット量
#define MOVE_ADVANCE_Y_LEN			(16)

///ダンスアニメ、左右移動：行きの移動にかけるフレーム数の割合(50%で行き戻り同じ速度)
#define MOVE_LR_GO_FRAME_PARCENT		(MOVE_ADVANCE_GO_FRAME_PARCENT)
///ダンスアニメ、左右移動：戻りの移動にかけるフレーム数の割合(50%で行き戻り同じ速度)
#define MOVE_LR_BACK_FRAME_PARCENT		(MOVE_ADVANCE_BACK_FRAME_PARCENT)
///ダンスアニメ、左右移動：左右に移動するドット量
#define MOVE_LR_X_LEN			(16)
///ダンスアニメ、左右移動：1フレーム毎に足しこむ角度(0-360)
#define MOVE_LR_ADD_THETA		(5)
///ダンスアニメ、左右移動：1フレーム毎に足しこむ角度(0-360)
#define MOVE_LR_ADD_THETA_BACK	(MOVE_LR_ADD_THETA)

//--------------------------------------------------------------
//	ポケモン常駐アニメ
//--------------------------------------------------------------
///ポケモン常駐アニメ：拡縮加減算最大値
#define PDA_AFF_ADD_Z_MAX	(0x2000)
///ポケモン常駐アニメ：座標移動、ふり幅X(メインダンサー)
#define PDA_MOVE_FURIHABA_X_MAIN	(3)
///ポケモン常駐アニメ：座標移動、ふり幅X(バックダンサー)
#define PDA_MOVE_FURIHABA_X_BACK	(3)

//--------------------------------------------------------------
//	プリン
//--------------------------------------------------------------
///プリンの表示座標Y
#define PRIN_POS_Y			(0x12 * 8)
///プリンのSinカーブふり幅Y
#define PRIN_FURIHABA_Y		(10)

//--------------------------------------------------------------
//	星
//--------------------------------------------------------------
///星のX移動量基本値
#define STAR_ADD_X_BASE		(0x0000)
///星のX移動量ランダム幅
#define STAR_ADD_X_RND		(0x500)
///星のY移動量基本値
#define STAR_ADD_Y_BASE		(0x400)
///星のY移動量ランダム幅
#define STAR_ADD_Y_RND		(0xf00)
///星に発生する重力
#define STAR_GRAVITY		(0x200)
///星の生存フレーム
#define STAR_LIFE_FRAME		(10)	//(15)

//--------------------------------------------------------------
//	ポケモンアピールアニメ
//--------------------------------------------------------------
///アピールアニメ：ジャンプ力
#define PAA_UP_POWER		(0x500)
///アピールアニメ：重力
#define PAA_GRAVITY			(0x200)
///アピールアニメ：繰り返し回数
#define PAA_JUMP_LOOP		(1)

///アピールアニメ左右：ふり幅
#define PAA_LR_FURIHABA			(4)
///アピールアニメ左右：角度加算値(FX32)
#define PAA_LR_ADD_ANGLE		(50 << FX32_SHIFT)
///アピールアニメ左右：繰り返し回数
#define PAA_LR_SIN_LOOP			(5)

//--------------------------------------------------------------
//	ダンス実行時の半透明BG
//--------------------------------------------------------------
#if 0	//パレットフェードに変更 2006.05.08(月)
///ダンス実行半透明BGのクリアとして使用するキャラクタNo
#define DANCE_BGALPHA_SPACE_CHARNO		(0)
///ダンス実行半透明BGで使用するキャラクタNo
#define DANCE_BGALPHA_CHARNO			(1)
///ダンス実行半透明BGのスクリーン埋め尽くしコード
#define DANCE_BGALPHA_SCREEN_CODE		((DANCE_ALPHA_BG_PALNO << 12) | DANCE_BGALPHA_CHARNO)
///ダンス実行半透明BGの縦の長さ(キャラクタ単位)
#define DANCE_BGALPHA_SCREEN_SIZE_Y		(192/8)	//(0x13)

///ダンス実行半透明BGのカラーデータ(DANCE_BGALPHA_TYPE順)
ALIGN4 static const u16 DanceBGAlphaColorData[] = {
	0x7fff, 0x001f, 0x7c00, 0x03e0, 0x27ff, 0x0000,
};

///ダンス実行半透明BGのキャラクタ埋め尽くし用データ(DANCE_BGALPHA_TYPE順)
ALIGN4 static const u8 DanceBGAlphaCharCode[] = {
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
};

///ダンス実行半透明BGのEVY値(DANCE_BGALPHA_TYPE順)
ALIGN4 static const struct{
	u8 ev1;
	u8 ev2;
}DanceBGAlphaEvy[] = {
	{3, 28},		//DANCE_BGALPHA_TYPE_NULL
	{3, 28},		//DANCE_BGALPHA_TYPE_UP
	{3, 28},		//DANCE_BGALPHA_TYPE_DOWN
	{3, 28},		//DANCE_BGALPHA_TYPE_LEFT
	{3, 28},		//DANCE_BGALPHA_TYPE_RIGHT
	{0, 15},		//DANCE_BGALPHA_TYPE_FAILED
};
#else
///ダンス実行フェードBGの変更データ
ALIGN4 static const struct{
	u16 next_rgb;	///<変更後のカラー
	u16 evy;		///<EVY値(0-16)
}DanceBGFadeData[] = {
	{0x0000, 0},		//DANCE_BGALPHA_TYPE_NULL
	{0x001f, 7},		//DANCE_BGALPHA_TYPE_UP
	{0x7c00, 7},		//DANCE_BGALPHA_TYPE_DOWN
	{0x03e0, 7},		//DANCE_BGALPHA_TYPE_LEFT
	{0x27ff, 8},		//DANCE_BGALPHA_TYPE_RIGHT
	{0x0000, 7},		//DANCE_BGALPHA_TYPE_FAILED
};
#endif

//--------------------------------------------------------------
//	譜面フラッシュ
//--------------------------------------------------------------
///譜面フラッシュ：開始EVY値(下位8ビット小数)
#define FUMEN_FLASH_START_EVY		(10 << 8)
///譜面フラッシュ：EVY減算値
#define FUMEN_FLASH_SUB_EVY			(0x0100)
///譜面フラッシュ：カラー
#define FUMEN_FLASH_COLOR			(0x7fff)

//--------------------------------------------------------------
//	エミッタリソース番号
//--------------------------------------------------------------
///ダンス成功：下位
#define EMIT_NO_SUCCEED_LOW_0			(CON_DANCE_029_BALL_BURN)
#define EMIT_NO_SUCCEED_LOW_1			(CON_DANCE_029_HIT_MARK)

///ダンス成功：上位
#define EMIT_NO_SUCCEED_HIGH_0			(CON_DANCE_030_BALL_BURN)
#define EMIT_NO_SUCCEED_HIGH_1			(CON_DANCE_030_HIT_MARK)
#define EMIT_NO_SUCCEED_HIGH_2			(CON_DANCE_030_NEEDLE_BEAM)

///決めダンス：得点低
#define EMIT_NO_FINISH_LOW_0			(CON_DANCE_036_BALL_BURN)
#define EMIT_NO_FINISH_LOW_1			(CON_DANCE_036_HIT_MARK)
#define EMIT_NO_FINISH_LOW_2			(CON_DANCE_036_KEMURI_BOMB)

///決めダンス：得点高
#define EMIT_NO_FINISH_HIGH_0			(CON_DANCE_038_HIT_MARK1)
#define EMIT_NO_FINISH_HIGH_1			(CON_DANCE_038_HIT_MARK2)
#define EMIT_NO_FINISH_HIGH_2			(CON_DANCE_038_HIT_MARK3)
#define EMIT_NO_FINISH_HIGH_3			(CON_DANCE_038_HIT_MARK4)
#define EMIT_NO_FINISH_HIGH_4			(CON_DANCE_038_HIT_MARK5)

//--------------------------------------------------------------
//	パーティクル
//--------------------------------------------------------------
///譜面パーティクル：この回数以上、連続が続いていると上位エフェクトを表示
#define FUMEN_PARTICLE_SUCCESSION_CHANGE_NUM	(6)

///フィニッシュパーティクルレベル
enum{
	FINISH_PARTICLE_LV1,
	FINISH_PARTICLE_LV2,
};

///譜面パーティクル表示レベル
enum{
	FUMEN_PARTICLE_LV1,
	FUMEN_PARTICLE_LV2,
};

//--------------------------------------------------------------
//	ライト
//--------------------------------------------------------------
///フェード：得点合計のライトのフェードにかけるフレーム数
#define FADE_RANKING_FRAME		(30)

///得点合計順に付けるライトのEVY値(得点が高い順)
ALIGN4 static const u8 RankingFadeEvy[] = {
	0, 4, 8, 12, //16, 12, 8, 4,
};


//==============================================================================
//	構造体定義
//==============================================================================
///ポケモンのアピールアニメワーク
typedef struct{
	DANCE_PROC_WORK *dpw;		///<ダンス部門管理ワークへのポインタ
	CONTEST_IMC_WORK *imcwork;	///<対象のポケモンのイメージクリップワークへのポインタ
	SHADOW_WORK *shadow;		///<対象の影へのポインタ
	u8 *end_flag;				///<終了フラグをセットするワークへのポインタ
	u8 seq;						///<シーケンス番号
	
	u8 loop;
	
	s32 up_power;				///<ジャンプ力
	s32 y;
	s32 start_y;
	
	//ジャンプ禁止の時の左右アピールで使用するワーク
	fx32 angle;
	s32 x;
	s32 start_x;
}POKE_APPEAL_ANIME;

///ライトのフェードワーク
typedef struct{
	IMC_PLAYERSYS_PTR imc_ptr;	///<対象のポケモンのイメージクリップへのポインタ
	u8 *end_flag;				///<終了フラグをセットするワークへのポインタ
	GXRgb start_color;			///<開始カラー
	GXRgb next_color;			///<変更後のカラー
	u16 add_evy;				///<EVY加算値(下位8ビット小数)
	u16 now_evy;				///<現在のEVY値(下位8ビット小数)
	u8 end_evy;					///<終了EVY値
}LIGHT_FADE_WORK;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void ReviewPanelTaskMain(TCB_PTR tcb, void *work);
static void MyCursorTaskMain(TCB_PTR tcb, void *work);
static void DT_DanceMoveReq(DANCE_PROC_WORK *dpw, int breeder_no, int rotation_pos, 
	int dance_step, int finish, int point);
static void DT_DanceMove(TCB_PTR tcb, void *work);
void DT_PokemonDefaultAnimeTaskDelAll(DANCE_PROC_WORK *dpw);
void DT_PokemonDefaultAnimeReq(DANCE_PROC_WORK *dpw, int breeder_no, PDA_REQ req);
int DT_PokemonDefaultAnimeStopCheckAff(DANCE_PROC_WORK *dpw, int breeder_no);
int DT_PokemonDefaultAnimeStopCheckMove(DANCE_PROC_WORK *dpw, int breeder_no);
static void PokemonDefaultAnime(TCB_PTR tcb, void *work);
static void PokemonDefaultAnime_Affine(POKE_DEF_ANM_WORK *pda);
static void PokemonDefaultAnime_Move(POKE_DEF_ANM_WORK *pda);
static void PrinMainTask(TCB_PTR tcb, void *work);
static BOOL Move_Jump(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, SHADOW_WORK *shadow, u32 effect_frame);
static BOOL Move_Advance(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, int advance_back, u32 effect_frame);
static BOOL Move_LeftRight(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, int left_type, u32 effect_frame);
static void ShadowMainTask(TCB_PTR tcb, void *work);
static int DT_GetPokeAffZ(int z);
static void StarMoveTask(TCB_PTR tcb, void *work);
static void PokeAppealMoveTask(TCB_PTR tcb, void *work);
void DT_BGAlphaEffectSet_DancingParam(DANCE_PROC_WORK *dpw, const DANCING_PARAM *dancing_param);
static void FumenFlashMainTask(TCB_PTR tcb, void *work);
static void EmitCall_PosSet(EMIT_PTR emit);
static void DT_ParticleFumenSet(DANCE_PROC_WORK *dpw, int hit_beat, int level);
static void DT_ParticleFinishSet(DANCE_PROC_WORK *dpw, int level);
void DT_MiddlePaletteFadeReq(DANCE_PROC_WORK *dpw, u32 fade_bit, u32 frame, 
	int start_evy, int end_evy, u16 next_rgb);
static void FinishRecoverAlphaSet(TCB_PTR tcb, void *work);
static void DancerLightFadeMain(TCB_PTR tcb, void *work);
static void PokeAppealMoveTaskLR(TCB_PTR tcb, void *work);


//==============================================================================
//	データ
//==============================================================================
///ポケモン表示座標
ALIGN4 static const s16 DancePokePos[BREEDER_MAX][3] = {	//X, Y, Z
	{128, 96, DANCE_POKEPOS_Z_MAIN},
	{48, 40, DANCE_POKEPOS_Z_SUB},
	{128, 40, DANCE_POKEPOS_Z_SUB},
	{256-48, 40, DANCE_POKEPOS_Z_SUB},
};

///評価パネル表示座標
ALIGN4 static const s16 ReviewPanelPos[BREEDER_MAX][2] = {	//X, Y
	{128, 88},
	{48, 32},
	{128, 32},
	{256-48, 32},
};

///音符の表示座標Y(ブリーダーローテーションの位置順)
ALIGN4 static const u8 OnpuPosY[] = {
	0x16*8, 0x15*8, 0x16*8, 0x17*8,
};

//--------------------------------------------------------------
//	アクターヘッダ
//--------------------------------------------------------------
///曲進行バー(8x8)のアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S MusicBar8ObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_MUSIC_BAR, PALOFS_MUSIC_BAR,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_MUSIC_BAR8,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_MUSIC_BAR8,	//セル
		D_CELLANMID_MUSIC_BAR8,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_MUSIC_BAR,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///音符のアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S OnpuObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_ONPU, PALOFS_ONPU_B,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_ONPU_B,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_ONPU,	//セル
		D_CELLANMID_ONPU,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_ONPU,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///評価パネルのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ReviewPanelObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_REVIEW, PALOFS_REVIEW,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_REVIEW,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_REVIEW,	//セル
		D_CELLANMID_REVIEW,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_REVIEW,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///自分カーソルのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S MyCursorObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_MY_CURSOR, PALOFS_MY_CURSOR,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_MY_CURSOR,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_MY_CURSOR,	//セル
		D_CELLANMID_MY_CURSOR,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_MY_CURSOR,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///プリンのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S PrinObjParam = {
	0, PRIN_POS_Y, 0,		//x, y, z
	0, DANCE_PRIN, PALOFS_PRIN,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_PRIN,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_PRIN,	//セル
		D_CELLANMID_PRIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_PRIN,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///影のアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ShadowObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_SHADOW, PALOFS_SHADOW,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_SHADOW,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_SHADOW,	//セル
		D_CELLANMID_SHADOW,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_SHADOW,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///星のアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S StarObjParam = {
	0, 0, 0,		//x, y, z
	0, DANCE_SOFTPRI_STAR, PALOFS_STAR,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		D_CHARID_STAR,	//キャラ
		D_PLTTID_OBJ_COMMON,	//パレット
		D_CELLID_STAR,	//セル
		D_CELLANMID_STAR,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	DANCE_BGPRI_STAR,			//BGプライオリティ
	0,			//Vram転送フラグ
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///譜面の色データ
ALIGN4 static const u16 FumenColor[][2] = {
	{0x463f, 0x2958},		//FUMENCOLOR_MAIN
	{0x67f8, 0x2b49},		//FUMENCOLOR_BACK
	{0x7fff, 0x6739},		//FUMENCOLOR_NULL
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ダンス部門ノーマル会話メッセージデータ	※A_TALK_DANCE_???の定義と並びを同じにしておく事！！
static const DANCE_MESSAGE_PARAM DanceTalkMsgData[] = {
	{0,									DTAG_NONE},	//ダミー
	{msg_con_dance_begin_host_01,		DTAG_RANK_NUM_OYA_NICK},
	{msg_con_d_prac_01,					DTAG_NICK},
	{msg_con_dance_end_host_01,			DTAG_NONE},
	{msg_con_dance_begin_host_02,		DTAG_NUM},
	{msg_con_dance_begin_host_03,		DTAG_NUM},
	{msg_con_d_t_after_01,				DTAG_OYA_NICK},
	{msg_con_a_prac_dpreface,			DTAG_NONE},
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
//譜面パーティクルのX座標位置(裏拍含む)
ALIGN4 static const s32 FumenParticlePosX[DANCE_BEAT + 1] = {
	//左側
	-30200,			//0
	-28412,			//0裏
	-26625,			//1
	-24837,			//1裏
	-23050,			//2
	-21262,			//2裏
	-19475,			//3
	-17887,			//3裏
	-15900,			//4
	-14112,			//4裏
	-12325,			//5
	-10537,			//5裏
	-8750,			//6
	-6962,			//6裏
	-5175,			//7
	-3387,			//7裏
	//右側
	-1600,			//8
	187,			//8裏
	1975,			//9
	3762,			//9裏
	5550,			//10
	7337,			//10裏
	9125,			//11
	10912,			//11裏
	12700,			//12
	14487,			//12裏
	16275,			//13
	18062,			//13裏
	19850,			//14
	21637,			//14裏
	23425,			//15
	25212,			//15裏

	27000,			//16
};




//--------------------------------------------------------------
/**
 * @brief   ローテーション位置の座標Xを取得する
 * @param   rotation_pos		ローテーション位置(DANCE_ROTATION_POS_???)
 * @retval  座標X
 */
//--------------------------------------------------------------
s16 DT_RotationPosGetX(int rotation_pos)
{
	return DancePokePos[rotation_pos][0];
}

//--------------------------------------------------------------
/**
 * @brief   ローテーション位置の座標Yを取得する
 * @param   rotation_pos		ローテーション位置(DANCE_ROTATION_POS_???)
 * @retval  座標Y
 */
//--------------------------------------------------------------
s16 DT_RotationPosGetY(int rotation_pos)
{
	return DancePokePos[rotation_pos][1];
}

//--------------------------------------------------------------
/**
 * @brief   ローテーション位置の座標Zを取得する
 * @param   rotation_pos		ローテーション位置(DANCE_ROTATION_POS_???)
 * @retval  座標Y
 */
//--------------------------------------------------------------
s16 DT_RotationPosGetZ(int rotation_pos)
{
	return DancePokePos[rotation_pos][2];
}


//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を生成する
 *
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_SoftSpriteAddAll(DANCE_PROC_WORK *dpw)
{
	int i;
	IMC_PLAYERSYS_INIT imc_init;
	int height;
	
	for(i = 0; i < BREEDER_MAX; i++){
		GF_ASSERT(dpw->sys.exchr_param[i].exchr_buffer == NULL);
//		dpw->sys.exchr_param[i].exchr_buffer = sys_AllocMemory(HEAPID_DANCE, EXCHR_BUFFER_SIZE);
	}
	
	MI_CpuClear8(&imc_init, sizeof(IMC_PLAYERSYS_INIT));
	imc_init.heap_id = HEAPID_DANCE;
	for(i = 0; i < BREEDER_MAX; i++){
		int breeder_no;
		breeder_no = dpw->d_game.breeder_rotation[i];
		height = PokeParaHeightGet(dpw->consys->c_game.pp[breeder_no], PARA_FRONT);
	#if 0
		dpw->sys.ss[breeder_no] = 
			ConTool_BreederPokemonAdd(dpw->sys.soft_sprite, breeder_no, dpw->sys.c_game->pp[breeder_no], 
			PARA_FRONT, &dpw->sys.exchr_param[breeder_no], HEAPID_DANCE, 
			DancePokePos[i][0], DancePokePos[i][1], DancePokePos[i][2]);
	#else
		imc_init.x = DancePokePos[i][0];
		imc_init.y = DancePokePos[i][1] + height;
		dpw->sys.imcwork[breeder_no].x = imc_init.x;
		dpw->sys.imcwork[breeder_no].y = imc_init.y;
		dpw->sys.imcwork[breeder_no].z = DancePokePos[i][2];
		dpw->sys.imcwork[breeder_no].imc_ptr = IMC_ContestPlayerInit_NoBG(&imc_init, 
			dpw->consys->c_game.imc_data[breeder_no]);
		
		IMC_Player_SetPokeMatrix(dpw->sys.imcwork[breeder_no].imc_ptr, 
			dpw->sys.imcwork[breeder_no].x, dpw->sys.imcwork[breeder_no].y);
	
		//バックダンサーはアクセサリー非表示
		if(i > 0){
			IMC_Player_SetAcceDrawFlag(dpw->sys.imcwork[breeder_no].imc_ptr, FALSE);
			IMC_Player_AddPriority(dpw->sys.imcwork[breeder_no].imc_ptr, DANCE_BACK_IMC_ADD_PRI);
		}
	#endif
	}
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を削除する
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_SoftSpriteDelAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		IMC_PlayerEnd(sys->imcwork[i].imc_ptr);
//		SoftSpriteDel(sys->ss[i]);
//		sys_FreeMemoryEz(sys->exchr_param[i].exchr_buffer);
		sys->exchr_param[i].exchr_buffer = NULL;
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
void DT_HeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
#if 0
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_APPEAL_POINT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCER_BIN, 1, 
		CELLID_APPEAL_POINT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NANR_BIN, 1, CELLANMID_APPEAL_POINT);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   観客ハートのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_HeartResourceFree(CATS_RES_PTR crp)
{
#if 0
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_APPEAL_POINT);
	CATS_FreeResourceCell(crp, CELLID_APPEAL_POINT);
	CATS_FreeResourceCellAnm(crp, CELLANMID_APPEAL_POINT);
#endif
}



//--------------------------------------------------------------
/**
 * @brief   曲進行バーアクターのアニメを更新する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 * @param   len		バーの長さ(ドット単位)
 */
//--------------------------------------------------------------
void DT_MusicBarAnimeUpdate(DANCE_SYSTEM_PARAM *sys, int len)
{
	int i, full, amari;

	if(len > MUSIC_BAR_LEN){
		len = MUSIC_BAR_LEN;
	}
	
	full = len / MUSIC_BAR_ONE_LEN;
	amari = len % MUSIC_BAR_ONE_LEN;
	
	{
		u16 *scrn_buf;
		
		scrn_buf = GF_BGL_ScreenAdrsGet(sys->bgl, DANCE_FRAME_BACKGROUND);
		scrn_buf = &scrn_buf[32 * 0x13];
		
		//全て埋まっているゲージを描画
		for(i = 0; i < full; i++){
			if(i % 8 == 0){
				scrn_buf[i] = MUSIC_BAR_FAST_SCRN_CODE_FULL;
			}
			else{
				scrn_buf[i] = 
					(i & 1) ? MUSIC_BAR_SECOND_SCRN_CODE_FULL : MUSIC_BAR_THERD_SCRN_CODE_FULL;
			}
		}
		//ゲージの先っぽを描画
		if(i < MUSIC_BAR_NUM){
			if(i % 8 == 0){
				scrn_buf[i] = MUSIC_BAR_FAST_SCRN_CODE_BASE + amari;
			}
			else{
				scrn_buf[i] = 
					((i & 1) ? MUSIC_BAR_SECOND_SCRN_CODE_BASE : MUSIC_BAR_THERD_SCRN_CODE_BASE)
					+ amari;
			}
			i++;
		}
		//残りの空白
		for( ; i < MUSIC_BAR_NUM; i++){
			if(i % 8 == 0){
				scrn_buf[i] = MUSIC_BAR_FAST_SCRN_CODE_BASE;
			}
			else{
				scrn_buf[i] = 
					(i & 1) ? MUSIC_BAR_SECOND_SCRN_CODE_BASE : MUSIC_BAR_THERD_SCRN_CODE_BASE;
			}
		}
		
		GF_BGL_LoadScreenV_Req(sys->bgl, DANCE_FRAME_BACKGROUND);
	}
}

//--------------------------------------------------------------
/**
 * @brief   曲進行バーアクターのアニメを更新する(経過フレームと終了フレームから計算)
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   now_frame		現在のフレーム
 * @param   end_frame		最終フレーム
 */
//--------------------------------------------------------------
void DT_MusicBarAnimeUpdateFrame(DANCE_SYSTEM_PARAM *sys, int now_frame, int end_frame)
{
	int len;
	
	len = now_frame * MUSIC_BAR_LEN / end_frame;
	DT_MusicBarAnimeUpdate(sys, len);
}

//--------------------------------------------------------------
/**
 * @brief   音符のリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_OnpuResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_B_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_ONPU_B);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_G_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_ONPU_G);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_R_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_ONPU_R);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_Y_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_ONPU_Y);
	
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_B_NCER_BIN, 1, 
		D_CELLID_ONPU);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		ONPU_B_NANR_BIN, 1, D_CELLANMID_ONPU);
}

//--------------------------------------------------------------
/**
 * @brief   音符のリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_OnpuResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_ONPU_B);
	CATS_FreeResourceChar(crp, D_CHARID_ONPU_G);
	CATS_FreeResourceChar(crp, D_CHARID_ONPU_R);
	CATS_FreeResourceChar(crp, D_CHARID_ONPU_Y);
	
	CATS_FreeResourceCell(crp, D_CELLID_ONPU);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_ONPU);
}

//--------------------------------------------------------------
/**
 * @brief   音符アクターを生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 * @param   anm_type		ONPU_ANMTYPE_???
 * @param   step_type		DANCE_STEP_???
 * @param   x				表示座標X
 * @param   y				表示座標Y
 * @param   rotation_pos	ローテーション位置
 *
 * @retval  セットした音符アクター配列の添え字箇所
 */
//--------------------------------------------------------------
static int DT_OnpuActorSet(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int anm_type, int step_type, int x, int y, int rotation_pos)
{
	CATS_ACT_PTR onpu_cap;
	int i;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = OnpuObjParam;
	if(anm_type == ONPU_ANMTYPE_HISTORY){
		obj_param.pri += 10;	//自分の音符が表示された時、履歴が下になるように下げておく
	}
	else{	//ローテーションの位置によってプライオリティ変更
		switch(rotation_pos){
		case 0:
		default:
			break;
		case 1:
			obj_param.pri += 3;
			break;
		case 2:
			obj_param.pri += 2;
			break;
		case 3:
			obj_param.pri += 1;
			break;
		}
	}
	
	switch(step_type){
	case DANCE_STEP_LEFT:
		obj_param.id[CLACT_U_CHAR_RES] = D_CHARID_ONPU_G;
		obj_param.pal = PALOFS_ONPU_G;
		break;
	case DANCE_STEP_RIGHT:
		obj_param.id[CLACT_U_CHAR_RES] = D_CHARID_ONPU_Y;
		obj_param.pal = PALOFS_ONPU_Y;
		break;
	case DANCE_STEP_JUMP:
		obj_param.id[CLACT_U_CHAR_RES] = D_CHARID_ONPU_R;
		obj_param.pal = PALOFS_ONPU_R;
		break;
	case DANCE_STEP_ADVANCE:
	default:
		obj_param.id[CLACT_U_CHAR_RES] = D_CHARID_ONPU_B;
		obj_param.pal = PALOFS_ONPU_B;
		break;
	}
	
	onpu_cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	CATS_ObjectAnimeSeqSetCap(onpu_cap, anm_type);
	CATS_ObjectUpdate(onpu_cap->act);
	CATS_ObjectPosSetCap_SubSurface(onpu_cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
	CATS_ObjectAutoAnimeSetCap(onpu_cap, CATS_ANM_AUTO_ON);	//オートアニメーションフラグ
	
	//空いている場所にポインタをセット
	for(i = 0; i < ONPU_ACTOR_MAX; i++){
		if(sys->onpu_cap[i] == NULL){
			sys->onpu_cap[i] = onpu_cap;
			return i;
		}
	}
	GF_ASSERT(0 && "音符アクターをセットする配列ワークに空きがありません！\n");
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   音符アクターを全て削除する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_OnpuActorDelAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < ONPU_ACTOR_MAX; i++){
		if(sys->onpu_cap[i] != NULL){
			CATS_ActorPointerDelete_S(sys->onpu_cap[i]);
			sys->onpu_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルのリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_ReviewPanelResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		WIN_EXCELLENT_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_REVIEW);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		WIN_EXCELLENT_NCER_BIN, 1, 
		D_CELLID_REVIEW);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		WIN_EXCELLENT_NANR_BIN, 1, D_CELLANMID_REVIEW);
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_ReviewPanelResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_REVIEW);
	CATS_FreeResourceCell(crp, D_CELLID_REVIEW);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_REVIEW);
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルアクターを生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 * @param   review_type		レビュータイプ(REVIEW_TYPE_???)
 * @param   breeder_no		ブリーダー番号
 * @param   breeder_rotation	現在のブリーダーローテーションへのポインタ
 *
 * @retval  セットした評価パネルアクター配列の添え字箇所
 */
//--------------------------------------------------------------
void DT_ReviewPanelActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	CATS_ACT_PTR review_cap;
	int i;
	
	for(i = 0; i < REVIEW_ACTOR_MAX; i++){
		sys->review_cap[i] = CATS_ObjectAdd_S(csp, crp, &ReviewPanelObjParam);
		CATS_ObjectEnableCap(sys->review_cap[i], CATS_ENABLE_FALSE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルアクターを全て削除する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_ReviewPanelActorDelAll(DANCE_SYSTEM_PARAM *sys)
{
	int i, breeder;
	
	for(i = 0; i < REVIEW_ACTOR_MAX; i++){
		CATS_ActorPointerDelete_S(sys->review_cap[i]);
		sys->review_cap[i] = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   評価パネル上のフォントOAMを全て生成する
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_ReviewFontOamCreateAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;
	STRBUF *excellent_src, *good_src, *failed_src;

	excellent_src = MSGMAN_AllocString(sys->dance_msg, CDMSG_EXCELLENT);
	good_src = MSGMAN_AllocString(sys->dance_msg, CDMSG_GOOD);
	failed_src = MSGMAN_AllocString(sys->dance_msg, CDMSG_FAILED);
	
	for(i = 0; i < REVIEW_ACTOR_MAX; i++){
		ADV_FontOamCreate(HEAPID_DANCE, sys->bgl, sys->crp, sys->fontoam_sys,
			&sys->fontact[REVIEW_TYPE_EXCELLENT][i],
			excellent_src, FONT_SYSTEM, REVIEW_PRINTCOLOR, 0, D_PLTTID_OBJ_COMMON, 
			0, 0, TRUE, DANCE_BGPRI_REVIEW, DANCE_SOFTPRI_REVIEW_FONT);
		FONTOAM_SetDrawFlag(sys->fontact[REVIEW_TYPE_EXCELLENT][i].fontoam, FALSE);
		
		ADV_FontOamCreate(HEAPID_DANCE, sys->bgl, sys->crp, sys->fontoam_sys,
			&sys->fontact[REVIEW_TYPE_GOOD][i],
			good_src, FONT_SYSTEM, REVIEW_PRINTCOLOR, 0, D_PLTTID_OBJ_COMMON, 
			0, 0, TRUE, DANCE_BGPRI_REVIEW, DANCE_SOFTPRI_REVIEW_FONT);
		FONTOAM_SetDrawFlag(sys->fontact[REVIEW_TYPE_GOOD][i].fontoam, FALSE);

		ADV_FontOamCreate(HEAPID_DANCE, sys->bgl, sys->crp, sys->fontoam_sys,
			&sys->fontact[REVIEW_TYPE_FAILED][i],
			failed_src, FONT_SYSTEM, REVIEW_PRINTCOLOR, 0, D_PLTTID_OBJ_COMMON, 
			0, 0, TRUE, DANCE_BGPRI_REVIEW, DANCE_SOFTPRI_REVIEW_FONT);
		FONTOAM_SetDrawFlag(sys->fontact[REVIEW_TYPE_FAILED][i].fontoam, FALSE);
	}

	STRBUF_Delete(excellent_src);
	STRBUF_Delete(good_src);
	STRBUF_Delete(failed_src);
}

//--------------------------------------------------------------
/**
 * @brief   評価パネル上のフォントOAMを全て削除する
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_ReviewFontOamDeleteAll(DANCE_SYSTEM_PARAM *sys)
{
	int i, s;
	
	for(s = 0; s < REVIEW_TYPE_MAX; s++){
		for(i = 0; i < REVIEW_ACTOR_MAX; i++){
			ADV_FontOamDelete(&sys->fontact[s][i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルアクターのタスクを生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 * @param   review_type		レビュータイプ(REVIEW_TYPE_???)
 * @param   breeder_no		ブリーダー番号
 * @param   breeder_rotation	ブリーダーのローテーション位置
 */
//--------------------------------------------------------------
void DT_ReviewPanelTaskSet(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int review_type, int breeder_no, u8 rotation_pos)
{
	CATS_ACT_PTR review_cap;
	int i, x, y, cap_pos;
	REVIEW_PANEL_TASK_WORK *rptw;
	
	cap_pos = rotation_pos == 0 ? rotation_pos : (rotation_pos-1);

//	rptw = sys_AllocMemory(HEAPID_DANCE, sizeof(REVIEW_PANEL_TASK_WORK));
	rptw = &sys->rptw[cap_pos];
	if(rptw->tcb != NULL){
		TCB_Delete(rptw->tcb);
		OS_TPrintf("既に生成中のレビューパネルをキャンセルして新しく作り直しました\n");
	}
	MI_CpuClear8(rptw, sizeof(REVIEW_PANEL_TASK_WORK));
	
	x = ReviewPanelPos[rotation_pos][0];
	y = ReviewPanelPos[rotation_pos][1];
	
	rptw->cap = sys->review_cap[cap_pos];
	CATS_ObjectAnimeSeqSetCap(rptw->cap, review_type);
	CATS_ObjectPosSetCap_SubSurface(rptw->cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
	CATS_ObjectUpdate(rptw->cap->act);
	CATS_ObjectEnableCap(rptw->cap, CATS_ENABLE_TRUE);
	
	for(i = 0; i < REVIEW_TYPE_MAX; i++){
		FONTOAM_SetDrawFlag(sys->fontact[i][cap_pos].fontoam, FALSE);
	}
	rptw->fontact = &sys->fontact[review_type][cap_pos];
	ADV_FontOamPosSet(rptw->fontact, x, y, TRUE);
	FONTOAM_SetDrawFlag(rptw->fontact->fontoam, TRUE);
	
//	CATS_ObjectAffineSetCap(rptw->cap, CLACT_AFFINE_NORMAL);
//	CATS_ObjectScaleSetCap(rptw->cap, 0, 0);
	
	rptw->tcb = TCB_Add(ReviewPanelTaskMain, rptw, TCBPRI_DANCE_REVIEWPANEL);
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルエフェクトメインタスク
 * @param   tcb			TCBプライオリティ
 * @param   work		REVIEW_PANEL_TASK_WORK構造体
 */
//--------------------------------------------------------------
static void ReviewPanelTaskMain(TCB_PTR tcb, void *work)
{
	REVIEW_PANEL_TASK_WORK *rptw = work;
	int x, y;
	
	switch(rptw->seq){
	case 0:
		FONTOAM_GetMat(rptw->fontact->fontoam, &x, &y);
		y += REVIEW_PANEL_SPEED_Y;
		FONTOAM_SetMat(rptw->fontact->fontoam, x, y);
		CATS_ObjectPosMoveCap(rptw->cap, 0, REVIEW_PANEL_SPEED_Y);
		
//		CATS_ObjectScaleAddCap(rptw->cap, 0.25, 0.25);
		
		rptw->work++;
		if(rptw->work > 4){
			rptw->work = 0;
//			FONTOAM_SetDrawFlag(rptw->fontact->fontoam, TRUE);
			rptw->seq++;
		}
		break;
	case 1:
		rptw->work++;
		if(rptw->work > 14){
			rptw->seq++;
		}
		break;
	default:
		FONTOAM_SetDrawFlag(rptw->fontact->fontoam, FALSE);
		CATS_ObjectEnableCap(rptw->cap, CATS_ENABLE_FALSE);
		
//		CATS_ObjectAffineSetCap(rptw->cap, CLACT_AFFINE_NONE);

		rptw->tcb = NULL;
		//sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   評価パネルタスクを全て削除します
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_ReviewPanelTaskDelAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;

	for(i = 0; i < REVIEW_ACTOR_MAX; i++){
		if(sys->rptw[i].tcb != NULL){
			TCB_Delete(sys->rptw[i].tcb);
			sys->rptw[i].tcb = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルのリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_MyCursorResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		MY_CURSOR_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_MY_CURSOR);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		MY_CURSOR_NCER_BIN, 1, 
		D_CELLID_MY_CURSOR);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		MY_CURSOR_NANR_BIN, 1, D_CELLANMID_MY_CURSOR);
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_MyCursorResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_MY_CURSOR);
	CATS_FreeResourceCell(crp, D_CELLID_MY_CURSOR);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_MY_CURSOR);
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルアクターを生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_MyCursorActorSet(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	CATS_ACT_PTR my_cursor_cap;
	
	my_cursor_cap = CATS_ObjectAdd_S(csp, crp, &MyCursorObjParam);
	CATS_ObjectUpdate(my_cursor_cap->act);
	
	sys->my_cursor_cap = my_cursor_cap;
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルアクターを削除する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_MyCursorActorDel(DANCE_SYSTEM_PARAM *sys)
{
	int i, breeder;
	
	if(sys->my_cursor_cap != NULL){
		CATS_ActorPointerDelete_S(sys->my_cursor_cap);
		sys->my_cursor_cap = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルアクター動作タスクを生成する
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_MyCursorTaskSet(DANCE_PROC_WORK *dpw)
{
	dpw->sys.my_cursor_tcb = TCB_Add(MyCursorTaskMain, dpw, TCBPRI_DANCE_MY_CURSOR);
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルアクター動作タスクを削除する
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_MyCursorTaskDel(DANCE_PROC_WORK *dpw)
{
	TCB_Delete(dpw->sys.my_cursor_tcb);
}

//--------------------------------------------------------------
/**
 * @brief   自分カーソルタスクメイン動作
 * @param   tcb			TCBへのポインタ
 * @param   work		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void MyCursorTaskMain(TCB_PTR tcb, void *work)
{
	DANCE_PROC_WORK *dpw = work;
	int x, y, my_breeder_no;
	
	my_breeder_no = dpw->consys->c_game.my_breeder_no;
//	x = SoftSpriteParaGet(dpw->sys.ss[my_breeder_no], SS_PARA_POS_X);
//	y = SoftSpriteParaGet(dpw->sys.ss[my_breeder_no], SS_PARA_POS_Y);
	x = dpw->sys.imcwork[my_breeder_no].x;
	y = dpw->sys.imcwork[my_breeder_no].y;
	
	CATS_ObjectPosSetCap_SubSurface(dpw->sys.my_cursor_cap, x, y - 8*5, DANCE_SUB_ACTOR_DISTANCE);
}

//--------------------------------------------------------------
/**
 * @brief   影のリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_ShadowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		SHADOW_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_SHADOW);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		SHADOW_NCER_BIN, 1, D_CELLID_SHADOW);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		SHADOW_NANR_BIN, 1, D_CELLANMID_SHADOW);
}

//--------------------------------------------------------------
/**
 * @brief   影のリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_ShadowResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_SHADOW);
	CATS_FreeResourceCell(crp, D_CELLID_SHADOW);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_SHADOW);
}

//--------------------------------------------------------------
/**
 * @brief   影アクターを全て生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_ShadowActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		sys->shadow[i].cap = CATS_ObjectAdd_S(csp, crp, &ShadowObjParam);
		CATS_ObjectUpdate(sys->shadow[i].cap->act);
		
		//拡縮ON
		CATS_ObjectAffineSetCap(sys->shadow[i].cap, CLACT_AFFINE_NORMAL);
		
		sys->shadow[i].breeder_no = i;
		sys->shadow[i].imcwork = &sys->imcwork[i];
		sys->shadow[i].height = PokeParaHeightGet(sys->c_game->pp[i], PARA_FRONT);
		DT_ShadowHomingFlagSet(&sys->shadow[i], TRUE, TRUE);
		sys->shadow[i].tcb = TCB_Add(ShadowMainTask, &sys->shadow[i], TCBPRI_DANCE_SHADOW);
	}
	
	DT_ShadowEnableSet(sys, CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   影アクターを全て削除する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_ShadowActorDelAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		CATS_ActorPointerDelete_S(sys->shadow[i].cap);
		TCB_Delete(sys->shadow[i].tcb);
		sys->shadow[i].cap = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   影アクターの表示・非表示設定
 *
 * @param   sys			ダンスシステムワークへのポインタ
 * @param   enable		CATS_ENABLE_TRUE or CATS_ENABLE_FALSE
 */
//--------------------------------------------------------------
void DT_ShadowEnableSet(DANCE_SYSTEM_PARAM *sys, int enable)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		CATS_ObjectEnableCap(sys->shadow[i].cap, enable);
	}
}

//--------------------------------------------------------------
/**
 * @brief   影動作メインタスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		影ワークへのポインタ
 */
//--------------------------------------------------------------
static void ShadowMainTask(TCB_PTR tcb, void *work)
{
	SHADOW_WORK *shadow = work;
	int x, y, z, offset_y;
	f32 f_aff;
	
	x = shadow->imcwork->x;
	y = shadow->imcwork->y;// + SOFT_SPRITE_SIZE_Y/2 - shadow->height;
	z = shadow->imcwork->z;
	
	//Zの位置によって拡縮
	{
		int set_aff;
		
		set_aff = DT_GetPokeAffZ(z);
		offset_y = (SOFT_SPRITE_SIZE_Y / 2 - shadow->height) * set_aff / 0x100;
		y += offset_y;
		f_aff = (100 * set_aff / 0x100);
		f_aff /= 100.0f;
	}
	
	if(shadow->homing_jump == FALSE){
		s16 get_x, get_y;
		CATS_ObjectPosGetCap_SubSurface(shadow->cap, &get_x, &get_y, DANCE_SUB_ACTOR_DISTANCE);
		y = get_y;
//		offset_y
	}

	CATS_ObjectPosSetCap_SubSurface(shadow->cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
	CATS_ObjectScaleSetCap(shadow->cap, f_aff, f_aff);
}

//--------------------------------------------------------------
/**
 * @brief   影：追尾フラグのセット
 *
 * @param   shadow		影ワークへのポインタ
 * @param   flag		TRUE:追尾ON、FALSE:追尾OFF
 */
//--------------------------------------------------------------
void DT_ShadowHomingFlagSet(SHADOW_WORK *shadow, int flag, int jump_flag)
{
	shadow->homing = flag;
	shadow->homing_jump = jump_flag;
}

//--------------------------------------------------------------
/**
 * @brief   スポットライトのリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_SpotLightResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		SPOTLIGHT_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_SPOTLIGHT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		SPOTLIGHT_NCER_BIN, 1, 
		D_CELLID_SPOTLIGHT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		SPOTLIGHT_NANR_BIN, 1, D_CELLANMID_SPOTLIGHT);
}

//--------------------------------------------------------------
/**
 * @brief   スポットライトのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_SpotLightResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_SPOTLIGHT);
	CATS_FreeResourceCell(crp, D_CELLID_SPOTLIGHT);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_SPOTLIGHT);
}

//--------------------------------------------------------------
/**
 * @brief   スポットライトアクターを全て生成する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_SpotLightActorSetAll(DANCE_SYSTEM_PARAM *sys, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
#if 0
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		sys->spotlight[i].cap = CATS_ObjectAdd_S(csp, crp, &ShadowObjParam);
		CATS_ObjectUpdate(sys->spotlight[i].cap->act);
		
		//拡縮ON
		CATS_ObjectAffineSetCap(sys->spotlight[i].cap, CLACT_AFFINE_NORMAL);
		
		sys->spotlight[i].breeder_no = i;
		sys->spotlight[i].imcwork = &sys->imcwork[i];
		sys->spotlight[i].height = PokeParaHeightGet(sys->c_game->pp[i], PARA_FRONT);
		DT_ShadowHomingFlagSet(&sys->spotlight[i], TRUE, TRUE);
		sys->spotlight[i].tcb = TCB_Add(ShadowMainTask, &sys->spotlight[i], TCBPRI_DANCE_SHADOW);
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   スポットライトアクターを全て削除する
 *
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_SpotLightActorDelAll(DANCE_SYSTEM_PARAM *sys)
{
#if 0
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		CATS_ActorPointerDelete_S(sys->spotlight[i].cap);
		TCB_Delete(sys->spotlight[i].tcb);
		sys->spotlight[i].cap = NULL;
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   星のリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_StarResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_STAR);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR_NCER_BIN, 1, 
		D_CELLID_STAR);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR_NANR_BIN, 1, D_CELLANMID_STAR);
}

//--------------------------------------------------------------
/**
 * @brief   星のリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_StarResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_STAR);
	CATS_FreeResourceCell(crp, D_CELLID_STAR);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_STAR);
}

//--------------------------------------------------------------
/**
 * @brief   星アクターを生成する
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   breeder_no	ブリーダー番号
 * @param   anm_seq		アニメシーケンス(DANCE_STAR_ANMSEQ_???)
 *
 * @retval  TRUE:生成成功。　FALSE:生成失敗
 */
//--------------------------------------------------------------
BOOL DT_StarActorSet(DANCE_PROC_WORK *dpw, int breeder_no, int anm_seq)
{
	CATS_ACT_PTR cap;
	u32 number, denom;
	STAR_WORK *star;
	int i, x, y;
	
	star = dpw->sys.star[breeder_no];
	for(i = 0; i < STAR_EFF_MAX; i++){
		if(star->tcb == NULL){
			break;
		}
		star++;
	}
	if(i == STAR_EFF_MAX){
		return FALSE;
	}
	
	//アクター生成
	cap = CATS_ObjectAdd_S(dpw->sys.csp, dpw->sys.crp, &StarObjParam);
	if(cap == NULL){
		return FALSE;
	}
	x = dpw->sys.imcwork[breeder_no].x;
	y = dpw->sys.imcwork[breeder_no].y;
	CATS_ObjectAnimeSeqSetCap(cap, anm_seq);
	CATS_ObjectPosSetCap_SubSurface(cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
	CLACT_SetAnmFlag(cap->act, 1);	//オートアニメ
	CATS_ObjectUpdate(cap->act);

	//動作パラメータ設定
	number = contest_rand(dpw->consys);
	denom = STAR_ADD_X_RND;
	CP_SetDiv32_32(number, denom);
	
	MI_CpuClear8(star, sizeof(STAR_WORK));
	star->cap = cap;
	star->x = x << 8;
	star->y = y << 8;
	
	star->add_x = CP_GetDivRemainder32() + STAR_ADD_X_BASE;
	if(star->add_x & 1){
		star->add_x = -star->add_x;
	}

	number = contest_rand(dpw->consys);
	denom = STAR_ADD_Y_RND;
	CP_SetDivImm32_32(number, denom);	//上のCP_SetDivのモードを引き継いでいます！！
	
	star->up_power = -(STAR_ADD_Y_BASE + CP_GetDivRemainder32());
	
	star->tcb = TCB_Add(StarMoveTask, star, TCBPRI_DANCE_EFFECT_BASE_PRI);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   星アクターメイン動作タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		星動作ワークへのポインタ
 */
//--------------------------------------------------------------
static void StarMoveTask(TCB_PTR tcb, void *work)
{
	STAR_WORK *star = work;
	s32 x, y;
	
	star->x += star->add_x;
	star->y += star->up_power;
	star->up_power += STAR_GRAVITY;
	star->life_frame++;
	
	if(star->life_frame > STAR_LIFE_FRAME
			|| (star->x > ((256+16) << 8)) || (star->x < ((-256-16) * 0x100))
			|| (star->y > ((192+16) << 8))){
		CATS_ActorPointerDelete_S(star->cap);
		TCB_Delete(tcb);
		star->cap = NULL;
		star->tcb = NULL;
		return;
	}
	
	CP_SetDiv32_32(star->x, 0x100);
	x = CP_GetDivResult32();
	CP_SetDivImm32_32(star->y, 0x100);	//上のモードを引き継いでいます！！
	y = CP_GetDivResult32();
	CATS_ObjectPosSetCap_SubSurface(star->cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
}

//--------------------------------------------------------------
/**
 * @brief   星出現エフェクトをセットする
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   breeder_no			ブリーダー番号
 * @param   review_type			REVIEW_TYPE_???
 * @param   rotation_pos		ローテーション位置
 */
//--------------------------------------------------------------
static void DT_StarEffectSet(DANCE_PROC_WORK *dpw, int breeder_no, int review_type, 
	int rotation_pos)
{
	int i, anm_seq, ret, point, star_num;
	
	if(review_type == REVIEW_TYPE_FAILED || dpw->d_game.dance_point[breeder_no] == 0){
		return;
	}

	point = dpw->d_game.dance_point[breeder_no];
	CP_SetDiv32_32(point, STAR_LVUP_POINT);
	
	if(rotation_pos == 0){
		anm_seq = DANCE_STAR_ANMSEQ_BIG;
	}
	else{
		anm_seq = DANCE_STAR_ANMSEQ_SMALL;
	}

	star_num = CP_GetDivResult32();
	if(star_num > STAR_EFF_MAX){
		star_num = STAR_EFF_MAX;
	}
	
	for(i = 0; i < star_num; i++){
		ret = DT_StarActorSet(dpw, breeder_no, anm_seq);
		if(ret == FALSE){
			OS_TPrintf("これ以上、星は表示出来ません！ブリーダー番号＝%d\n", breeder_no);
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサー位置の譜面の色を、指定したタイプの色に変更する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   color_type		カラータイプ(FUMENCOLOR_???)
 */
//--------------------------------------------------------------
void DT_FumenColorSet(DANCE_SYSTEM_PARAM *sys, FUMENCOLOR_TYPE color_type)
{
//	PaletteWorkSet(sys->pfd, FumenColor[color_type], FADE_MAIN_BG, FUMEN_MAIN_COLOR_POS,
//		FUMEN_MAIN_COLOR_NUM * 2);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンのZ位置から拡縮率を取得する
 * @param   z		Z位置
 * @retval  拡縮率(0x100で等倍)
 */
//--------------------------------------------------------------
static int DT_GetPokeAffZ(int z)
{
	int set_aff;
	
	if(z == DANCE_POKEPOS_Z_SUB){
		set_aff = DANCE_POKEAFF_BACK;
	}
	else if(z == DANCE_POKEPOS_Z_MAIN){
		set_aff = DANCE_POKEAFF_MAIN;
	}
	else{
		set_aff = (z - DANCE_POKEPOS_Z_SUB) * (DANCE_POKEAFF_MAIN - DANCE_POKEAFF_BACK) 
					/ (DANCE_POKEPOS_Z_MAIN - DANCE_POKEPOS_Z_SUB);
		set_aff += DANCE_POKEAFF_BACK;
	}
	return set_aff;
}

//--------------------------------------------------------------
/**
 * @brief   現在のZ位置を基準にポケモンの拡縮率の設定を行います
 *
 * @param   ss				対象のポケモン(ソフトウェアスプライト)へのポインタ
 * @param   imcwork			対象のポケモン(イメージクリップ)へのポインタ
 */
//--------------------------------------------------------------
void DT_PokeAffineUpdateZ(SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork)
{
	s32 now_z, set_aff;
	
//	now_z = SoftSpriteParaGet(ss, SS_PARA_POS_Z);
	now_z = imcwork->z;
	
	set_aff = DT_GetPokeAffZ(now_z);
	
//	SoftSpriteParaSet(ss, SS_PARA_AFF_X, set_aff);
//	SoftSpriteParaSet(ss, SS_PARA_AFF_Y, set_aff);
	{
		fx32 aff_fx;
		if(set_aff == 0x100){
			aff_fx = FX32_ONE;
		}
		else{
			aff_fx = FX32_ONE * set_aff / 0x100;
		}
		IMC_Player_SetScale(imcwork->imc_ptr, aff_fx, aff_fx, FX32_ONE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーに対して、現在のZ位置を基準にポケモンの拡縮率の設定を行います
 *
 * @param   sys				ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DT_PokeAffineUpdateZAll(DANCE_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		DT_PokeAffineUpdateZ(sys->ss[i], &sys->imcwork[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   渡されたダンス実行パラメータから適切な位置に音符を表示する
 *
 * @param   sys				ダンスシステムワークへのポインタ
 * @param   my_breeder_no	自分のブリーダー番号(＝ダンス実行パラメータのブリーダー番号ではない)
 * @param   param			ダンス実行パラメータへのポインタ
 *
 * @retval  TRUE：音符生成。　FALSE：生成する必要なし
 */
//--------------------------------------------------------------
static BOOL OnpuFrameSet(DANCE_PROC_WORK *dpw, int my_breeder_no, const DANCING_PARAM *param)
{
	int anm_type;
	int x, y, half_beat_x;
	
	anm_type = (param->breeder_no == my_breeder_no) ? ONPU_ANMTYPE_MINE : ONPU_ANMTYPE_ENEMY;
	
#if 0
	if(mine_data == TRUE){	//自分のデータ
		if(param->main_back == DANCER_MAIN){	//自分がメインダンサーの場合のダンスデータ
			x = 256 / DANCE_BEAT * param->hit_beat;
		}
		else{		//自分がバックダンサーの場合のダンスデータ
			x = (256 / DANCE_BEAT * param->hit_beat) + (256 / 2);
		}
	}
	else{//自分以外のダンスデータ
		if(param->main_back == DANCER_MAIN){
			x = (256 / DANCE_BEAT * param->hit_beat) - (256 / 2);
		}
		else{
			//自分以外のダンスデータで、それがメインダンサーのデータではないなら表示の必要なし
			return FALSE;
		}
	}
#else
	x = 256 / DANCE_BEAT * param->hit_beat;
#endif
	y = OnpuPosY[param->rotation_pos];
	
	//既に同じ位置に音符が生成されていないかチェック
	{
		s16 check_x, check_y;
		int i;
		
		for(i = 0; i < ONPU_ACTOR_MAX; i++){
			if(dpw->sys.onpu_cap[i] != NULL){
				CATS_ObjectPosGetCap_SubSurface(dpw->sys.onpu_cap[i], &check_x, &check_y, DANCE_SUB_ACTOR_DISTANCE);
				if(check_x == x && check_y == y && 
						CATS_ObjectAnimeSeqGetCap(dpw->sys.onpu_cap[i]) != ONPU_ANMTYPE_HISTORY){
					return FALSE;
				}
			}
		}
	}
	DT_OnpuActorSet(&dpw->sys, dpw->sys.csp, dpw->sys.crp, anm_type, param->dance_step, x, y,
		param->rotation_pos);
	
	//敵のメインダンサーのダンスデータの場合は自分の場所に履歴音符を置く
	//2重置きチェックは上の音符の場所で行われているので履歴音符までやる必要はない
	if(param->rotation_pos == 0 && anm_type == ONPU_ANMTYPE_ENEMY){
		x += 256/2;
		y = OnpuPosY[dpw->d_game.breeder_rotation[dpw->consys->c_game.my_breeder_no]];
		DT_OnpuActorSet(&dpw->sys, dpw->sys.csp, dpw->sys.crp, 
			ONPU_ANMTYPE_HISTORY, param->dance_step, x, y,
			dpw->d_game.breeder_rotation[dpw->consys->c_game.my_breeder_no]);
	}
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータを受信した時の処理
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   dancing_param		ダンス実行パラメータへのポインタ
 */
//--------------------------------------------------------------
void DT_DancingParamRecieve(DANCE_PROC_WORK *dpw, const DANCING_PARAM *dancing_param)
{
	int i, dancer_breeder, point;
	
	dancer_breeder = dancing_param->breeder_no;

	//受信データ計算処理(サーバーのみ実行)
	if(dpw->consys->c_game.my_breeder_no == dpw->consys->c_game.server_no){
		;
	}
	
	//受信データ計算処理(全クライアント実行)
	//得点加算
	{
		switch(dancing_param->lag_type){
		case DANCE_LAG_EXCELLENT_A:
			point = DANCE_POINT_EXCELLENT_A;
			break;
		case DANCE_LAG_EXCELLENT_B:
			point = DANCE_POINT_EXCELLENT_B;
			break;
		case DANCE_LAG_GOOD_A:
			point = DANCE_POINT_GOOD_A;
			break;
		case DANCE_LAG_GOOD_B:
			point = DANCE_POINT_GOOD_B;
			break;
		default:
			point = 0;
			break;
		}
		dpw->d_game.dance_point[dancer_breeder] += point;
		OS_TPrintf("%d番のブリーダー%d点獲得。合計=%d\n", dancer_breeder, point, 
			dpw->d_game.dance_point[dancer_breeder]);
	}

	if(dancing_param->rotation_pos == 0){	//メインダンサーの場合、履歴を取る
		for(i = 0; i < DANCING_RECORD_MAX; i++){
			if(dpw->maindancer_record[i].occ == FALSE){
				dpw->maindancer_record[i] = *dancing_param;
				break;
			}
			else if(dpw->maindancer_record[i].hit_beat == dancing_param->hit_beat){
				OS_TPrintf("同じ小節のダンスデータなので無視\n");
				break;
			}
		}
		//GF_ASSERT(i < DANCING_RECORD_MAX);	//メインダンス履歴オーバー
		if(i >= DANCING_RECORD_MAX){
			OS_TPrintf("ダンス履歴バッファがオーバーしたのでデータが受け取れませんでした！！！\n");
		}
	}

	//カウンター
	if(dancing_param->review_type == REVIEW_TYPE_EXCELLENT){
		dpw->sys.excellent_count[dancing_param->breeder_no]++;
		dpw->sys.now_excellent_count[dancing_param->breeder_no]++;
	}
	else{
		dpw->sys.excellent_count[dancing_param->breeder_no] = 0;
		dpw->sys.now_excellent_count[dancing_param->breeder_no] = 0;
	}
	if(dancing_param->review_type != REVIEW_TYPE_FAILED){
		dpw->sys.succession_count[dancing_param->breeder_no]++;
	}
	else{
		dpw->sys.now_failed_count[dancing_param->breeder_no]++;
		dpw->sys.succession_count[dancing_param->breeder_no] = 0;
	}
	if(dancing_param->rotation_pos > 0){
		switch(dancing_param->review_type){
		case REVIEW_TYPE_EXCELLENT:
			dpw->sys.now_back_excellent_all_count++;
			break;
		case REVIEW_TYPE_GOOD:
			dpw->sys.now_back_good_all_count++;
			break;
		case REVIEW_TYPE_FAILED:
			dpw->sys.now_back_failed_all_count++;
			break;
		}
	}

	//エフェクト処理(全クライアント実行)
	DT_ReviewPanelTaskSet(&dpw->sys, dpw->sys.csp, dpw->sys.crp, dancing_param->review_type,
		dancing_param->breeder_no, dancing_param->rotation_pos);
	//音符表示
	OnpuFrameSet(dpw, dpw->consys->c_game.my_breeder_no, dancing_param);
	//アニメリクエスト
	DT_DanceMoveReq(dpw, dancing_param->breeder_no, dancing_param->rotation_pos, 
		dancing_param->dance_step, dancing_param->finish, dpw->d_game.dance_point[dancer_breeder]);
	//星表示
	DT_StarEffectSet(dpw, dancing_param->breeder_no, dancing_param->review_type, 
		dancing_param->rotation_pos);
	//半透明BG
	DT_BGAlphaEffectSet_DancingParam(dpw, dancing_param);
	//パーティクル
	if(dancing_param->breeder_no == dpw->consys->c_game.my_breeder_no){
		if(dancing_param->review_type == REVIEW_TYPE_EXCELLENT){
			DT_ParticleFumenSet(dpw, dancing_param->hit_beat, FUMEN_PARTICLE_LV2);
		}
		else if(dancing_param->review_type == REVIEW_TYPE_GOOD){
			DT_ParticleFumenSet(dpw, dancing_param->hit_beat, FUMEN_PARTICLE_LV1);
		}
	}
	if(dancing_param->rotation_pos == 0 && dancing_param->finish == TRUE){
		//メインダンサー：フィニッシュパーティクル
		if(dpw->sys.now_excellent_count[dancing_param->breeder_no] == dpw->d_game.touch_count){
			DT_ParticleFinishSet(dpw, FINISH_PARTICLE_LV2);
		}
		else if(dpw->sys.now_failed_count[dancing_param->breeder_no] == 0){
			DT_ParticleFinishSet(dpw, FINISH_PARTICLE_LV1);
		}
	}
	else if(dancing_param->rotation_pos > 0 && dancing_param->finish == TRUE){
		//バックダンサー：フィニッシュパーティクル
		if(dpw->d_game.touch_count * (BREEDER_MAX - 1) == 
				dpw->sys.now_back_excellent_all_count 
				+ dpw->sys.now_back_good_all_count 
				+ dpw->sys.now_back_failed_all_count){
			if(dpw->d_game.touch_count * (BREEDER_MAX - 1) 
					== dpw->sys.now_back_excellent_all_count){
				DT_ParticleFinishSet(dpw, FINISH_PARTICLE_LV2);
			}
			else if(dpw->sys.now_back_failed_all_count == 0){
				DT_ParticleFinishSet(dpw, FINISH_PARTICLE_LV1);
			}
		}
	}
	
#if 0
	//SE再生：ボタン
	switch(dancing_param->dance_step){
	case DANCE_STEP_JUMP:
		Snd_SePlay(DSE_BUTTON_JUMP);
		break;
	case DANCE_STEP_ADVANCE:
		Snd_SePlay(DSE_BUTTON_ADVANCE);
		break;
	case DANCE_STEP_LEFT:
		Snd_SePlay(DSE_BUTTON_LEFT);
		break;
	case DANCE_STEP_RIGHT:
		Snd_SePlay(DSE_BUTTON_RIGHT);
		break;
	}
#endif

#ifndef DEBUG_DANCE_SE_PLAY

#ifdef DEBUG_DANCE_SE_PLAY_POKE_MOVE
	//SE再生：ポケモンアニメ
	if(dancing_param->finish == TRUE){
		Snd_SePlay(DSE_STEP_FINISH);
	}
	else{
		Snd_SePlay(DSE_STEP_NORMAL);
	}
#endif

	//SE再生：エクセレント連続評価
	if(dpw->sys.my_dancing_rotation_pos == 0 || 
			(dpw->sys.my_dancing_rotation_pos > 0 
			&& (dancing_param->rotation_pos == 0 
			|| dancing_param->breeder_no == dpw->consys->c_game.my_breeder_no))){
		switch(dancing_param->review_type){
		case REVIEW_TYPE_EXCELLENT:
			if(dpw->sys.now_excellent_count[dancing_param->breeder_no] == dpw->d_game.touch_count){
				Snd_SePlay(DSE_EXCELLENT_3);
			}
			else if(dpw->sys.now_excellent_count[dancing_param->breeder_no] 
					== dpw->d_game.touch_count - 1){
				Snd_SePlay(DSE_EXCELLENT_2);
			}
			else{
				Snd_SePlay(DSE_EXCELLENT_1);
			}
			break;
		case REVIEW_TYPE_GOOD:
			Snd_SePlay(DSE_GOOD);
			break;
		case REVIEW_TYPE_FAILED:
			if(dancing_param->button_failed == TRUE){
				Snd_SePlay(DSE_FAILED_BUTTON);
			}
			else{
				Snd_SePlay(DSE_FAILED);
			}
			break;
		}
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ダンスアニメーションをリクエストする
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @param   rotation_pos	ローテーション位置
 * @param   dance_step		ステップタイプ(DANCE_STEP_???)
 * @param   finish			TRUE:最後の決めダンス
 * @param   point			得点
 */
//--------------------------------------------------------------
static void DT_DanceMoveReq(DANCE_PROC_WORK *dpw, int breeder_no, int rotation_pos, 
	int dance_step, int finish, int point)
{
	int i, set_work;
	DANCE_MOVE_WORK *move;
	
	move = &dpw->move[breeder_no];
	set_work = -1;
	for(i = move->work_pos; i < DANCE_STEP_REQUEST_MAX; i++){
		if(move->dance_step[i] == DANCE_STEP_NONE){
			set_work = i;
			break;
		}
	}
	if(set_work == -1){
		for(i = 0; i < move->work_pos; i++){
			if(move->dance_step[i] == DANCE_STEP_NONE){
				set_work = i;
				break;
			}
		}
	}
	
	if(set_work == -1){
		//OS_TPrintf("*****ダンスアニメ予約バッファが既にいっぱいです！\n****");
		GF_ASSERT(0 && "ダンスアニメバッファが既にいっぱいです！");
		return;
	}
	
	move->dance_step[set_work] = dance_step;
	move->rotation_pos = rotation_pos;
	move->finish = finish;
	move->point = point;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンダンスエフェクト実行タスクを生成する
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_DanceMoveTaskSet(DANCE_PROC_WORK *dpw)
{
	dpw->move_tcb = TCB_Add(DT_DanceMove, dpw, TCBPRI_DANCE_MOVE);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンダンスエフェクト実行タスクを削除する
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_DanceMoveTaskDel(DANCE_PROC_WORK *dpw)
{
	TCB_Delete(dpw->move_tcb);
	dpw->move_tcb = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのダンスエフェクトが終了しているか確認
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 *
 * @retval  TRUE:全員のダンスエフェクトが終了している
 * @retval  FALSE:1匹以上がまだダンス中
 */
//--------------------------------------------------------------
BOOL DT_DanceMoveStepNoneAllCheck(DANCE_PROC_WORK *dpw)
{
	DANCE_MOVE_WORK *move;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		move = &dpw->move[i];
		if(move->dance_step[move->work_pos] != DANCE_STEP_NONE){
			return FALSE;
		}
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンダンスエフェクト実行タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DT_DanceMove(TCB_PTR tcb, void *work)
{
	DANCE_PROC_WORK *dpw = work;
	DANCE_MOVE_WORK *move;
	int dance_step, end, i;
	u32 effect_frame;
	
	for(i = 0; i < BREEDER_MAX; i++){
		move = &dpw->move[i];
		dance_step = move->dance_step[move->work_pos];
		end = FALSE;
		
		if(dance_step == DANCE_STEP_NONE){
			continue;	//アニメリクエストがかかっていないので飛ばす
		}
		
		//ダンスエフェクト中は常駐アニメ停止
		DT_PokemonDefaultAnimeReq(dpw, i, PDA_REQ_MOVE_STOP);
		
		effect_frame = dpw->d_game.one_tempo_frame / ONE_TEMPO_CALC_DECIMAL;
		effect_frame--;
		switch(dance_step){
		case DANCE_STEP_JUMP:
			if(dpw->sys.jump_up[i] == TRUE){
				end = Move_Jump(&move->eff, dpw->sys.ss[i], &dpw->sys.imcwork[i], 
					move->rotation_pos, move->finish, move->point, &dpw->sys.shadow[i], 
					effect_frame);
			}
			else{
				end = Move_Advance(&move->eff, dpw->sys.ss[i], &dpw->sys.imcwork[i], 
					move->rotation_pos, move->finish, move->point, FALSE, effect_frame);
			}
			break;
		case DANCE_STEP_ADVANCE:
			end = Move_Advance(&move->eff, dpw->sys.ss[i], &dpw->sys.imcwork[i], 
				move->rotation_pos, move->finish, move->point, TRUE, effect_frame);
			break;
		case DANCE_STEP_LEFT:
			end = Move_LeftRight(&move->eff, dpw->sys.ss[i], &dpw->sys.imcwork[i], 
				move->rotation_pos, move->finish, move->point, TRUE, effect_frame);
			break;
		case DANCE_STEP_RIGHT:
			end = Move_LeftRight(&move->eff, dpw->sys.ss[i], &dpw->sys.imcwork[i], 
				move->rotation_pos, move->finish, move->point, FALSE, effect_frame);
			break;
		default:
			GF_ASSERT(0 && "用意されていないステップタイプです\n");
			break;
		}
		
		//実行中のアニメが終了していたら、次のアニメを指すようにワーク位置移動
		if(end == TRUE){
			move->dance_step[move->work_pos] = DANCE_STEP_NONE;
			move->work_pos++;
			if(move->work_pos >= DANCE_STEP_REQUEST_MAX){
				move->work_pos = 0;
			}
			MI_CpuClear8(&move->eff, sizeof(MOVE_EFF_WORK));
	
			//常駐アニメ再開
			DT_PokemonDefaultAnimeReq(dpw, i, PDA_REQ_MOVE_SET);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンソフトウェアスプライトに移動後の座標をセット
 *          バックダンサーの場合は移動量補正も行います
 *
 * @param   eff				ダンスアニメエフェクト動作ワークへのポインタ
 * @param   ss				対象のポケモンのソフトウェアスプライトへのポインタ
 * @param   rotation_pos	ローテーション位置
 * @param   point			ここまでの得点
 * @param   finish			TRUE:フィニッシュ
 */
//--------------------------------------------------------------
static inline void Move_PosSet(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int point, int finish)
{
	s32 offset_x, offset_y, set_x, set_y;
	s32 revision, point_revision;
	
	if(rotation_pos == 0){
		revision = 100;
	}
	else{
		revision = MOVE_BACKDANCER_REVISION;
	}
	
	if(1){//finish == FALSE){
		point_revision = MOVE_POINT_REVISION * point;
		if(point_revision > MOVE_POINT_REVISION_MAX){
			point_revision = MOVE_POINT_REVISION_MAX;
		}
		
		revision += point_revision >> 8;
	}
	
	offset_x = eff->x - eff->start_x;
	offset_y = eff->y - eff->start_y;

	offset_x = offset_x * revision / 100;
	offset_y = offset_y * revision / 100;
	
	set_x = eff->start_x + offset_x;
	set_y = eff->start_y + offset_y;
	
//	SoftSpriteParaSet(ss, SS_PARA_POS_X, set_x / 0x0100);
//	SoftSpriteParaSet(ss, SS_PARA_POS_Y, set_y / 0x0100);
	imcwork->x = set_x / 0x100;
	imcwork->y = set_y / 0x100;
	IMC_Player_SetPokeMatrix(imcwork->imc_ptr, imcwork->x, imcwork->y);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン動作：ジャンプ
 * @param   eff		ダンスアニメエフェクト動作ワークへのポインタ
 * @param   ss		対象のポケモンのソフトウェアスプライトへのポインタ
 * @param   imcwork	対象のポケモンのイメージクリップへのポインタ
 * @param   finish			TRUE:最後の決めダンス
 * @param   point			ここまでの得点
 * @param   shadow			影へのポインタ
 * @param   effect_frame	エフェクトにかけるフレーム数
 * @retval  TRUE:終了。　FALSE:継続中
 */
//--------------------------------------------------------------
static BOOL Move_Jump(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, SHADOW_WORK *shadow, u32 effect_frame)
{
	BOOL end = FALSE;
	
	switch(eff->seq){
	case 0:
//		eff->start_x = SoftSpriteParaGet(ss, SS_PARA_POS_X) * 0x0100;
//		eff->start_y = SoftSpriteParaGet(ss, SS_PARA_POS_Y) * 0x0100;
		eff->start_x = imcwork->x * 0x100;
		eff->start_y = imcwork->y * 0x100;
		eff->x = eff->start_x;
		eff->y = eff->start_y;
		
		{
			int gravity;
			
			gravity = MOVE_JUMP_UP_POWER / (effect_frame / 2);
			if(finish == TRUE){
				eff->jump.up_power = -MOVE_JUMP_UP_POWER * MOVE_FINISHDANCE_REVISION / 100;
				eff->jump.gravity = gravity * MOVE_FINISHDANCE_REVISION / 100;
			}
			else{
				eff->jump.up_power = -MOVE_JUMP_UP_POWER;
				eff->jump.gravity = gravity;
			}
		}
		
		DT_ShadowHomingFlagSet(shadow, TRUE, FALSE);
		eff->seq++;
		//break;
	case 1:
		eff->y += eff->jump.up_power;
		eff->jump.up_power += eff->jump.gravity;
		if(eff->y >= eff->start_y){
			eff->y = eff->start_y;
			DT_ShadowHomingFlagSet(shadow, TRUE, TRUE);
			end = TRUE;
			eff->seq++;
		}
		break;
	default:
		return TRUE;
	}
	
	Move_PosSet(eff, ss, imcwork, rotation_pos, point, finish);
	return end;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン動作：前進
 * @param   eff		ダンスアニメエフェクト動作ワークへのポインタ
 * @param   ss		対象のポケモンのソフトウェアスプライトへのポインタ
 * @param   imcwork	対象のポケモンのイメージクリップへのポインタ
 * @param   finish			TRUE:最後の決めダンス
 * @param   point			ここまでの得点
 * @param   advance_back	TRUE:前進。　FALSE:後退
 * @param   effect_frame	エフェクトにかけるフレーム数
 * @retval  TRUE:終了。　FALSE:継続中
 */
//--------------------------------------------------------------
static BOOL Move_Advance(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, int advance_back, u32 effect_frame)
{
	BOOL end = FALSE;
	s32 end_y;
	
	switch(eff->seq){
	case 0:
//		eff->start_x = SoftSpriteParaGet(ss, SS_PARA_POS_X) * 0x0100;
//		eff->start_y = SoftSpriteParaGet(ss, SS_PARA_POS_Y) * 0x0100;
		eff->start_x = imcwork->x * 0x100;
		eff->start_y = imcwork->y * 0x100;
		eff->x = eff->start_x;
		eff->y = eff->start_y;
		
		{
			int go_frame, back_frame;
			
			go_frame = effect_frame * MOVE_ADVANCE_GO_FRAME_PARCENT / 100;
			back_frame = effect_frame - go_frame;
			eff->advance.add_go_x = MOVE_ADVANCE_Y_LEN * 0x100 / go_frame;
			eff->advance.add_back_x = MOVE_ADVANCE_Y_LEN * 0x100 / back_frame;
			if(advance_back == FALSE){
				eff->advance.add_go_x *= -1;
				eff->advance.add_back_x *= -1;
			}
		}
		
		eff->seq++;
		//break;
	case 1:
		if(finish == TRUE){
			eff->y += eff->advance.add_go_x * MOVE_FINISHDANCE_REVISION / 100;
			end_y = MOVE_ADVANCE_Y_LEN * MOVE_FINISHDANCE_REVISION / 100;
		}
		else{
			eff->y += eff->advance.add_go_x;
			end_y = MOVE_ADVANCE_Y_LEN;
		}
		
		if(abs(eff->y - eff->start_y) >= end_y * 0x0100){
			if(advance_back == TRUE){
				eff->y = eff->start_y + end_y * 0x0100;
			}
			else{
				eff->y = eff->start_y - end_y * 0x0100;
			}
			eff->seq++;
		}
		break;
	case 2:
		if(finish == TRUE){
			eff->y -= eff->advance.add_back_x * MOVE_FINISHDANCE_REVISION / 100;
		}
		else{
			eff->y -= eff->advance.add_back_x;
		}
		
		if((advance_back == TRUE && eff->y <= eff->start_y)
				|| (advance_back == FALSE && eff->y >= eff->start_y)){
			eff->y = eff->start_y;
			eff->seq++;
			end = TRUE;
		}
		break;
	default:
		return TRUE;
	}

	Move_PosSet(eff, ss, imcwork, rotation_pos, point, finish);
	return end;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン動作：左右移動
 * @param   eff		ダンスアニメエフェクト動作ワークへのポインタ
 * @param   ss		対象のポケモンのソフトウェアスプライトへのポインタ
 * @param   imcwork	対象のポケモンのイメージクリップへのポインタ
 * @param   finish			TRUE:最後の決めダンス
 * @param   point			ここまでの得点
 * @param   left_type		TRUE:左移動、FALSE:右移動
 * @param   effect_frame	エフェクトにかけるフレーム数
 * @retval  TRUE:終了。　FALSE:継続中
 */
//--------------------------------------------------------------
static BOOL Move_LeftRight(MOVE_EFF_WORK *eff, SOFT_SPRITE *ss, CONTEST_IMC_WORK *imcwork,
	int rotation_pos, int finish, int point, int left_type, u32 effect_frame)
{
	BOOL end = FALSE;
	s32 end_x;
//	int add_theta, back_theta, eff->add_x, back_x;

	
	switch(eff->seq){
	case 0:
//		eff->start_x = SoftSpriteParaGet(ss, SS_PARA_POS_X) * 0x0100;
//		eff->start_y = SoftSpriteParaGet(ss, SS_PARA_POS_Y) * 0x0100;
		eff->start_x = imcwork->x * 0x100;
		eff->start_y = imcwork->y * 0x100;
		eff->x = eff->start_x;
		eff->y = eff->start_y;
		
		{
			int go_frame, back_frame;
			
			go_frame = effect_frame * MOVE_LR_GO_FRAME_PARCENT / 100;
			back_frame = effect_frame - go_frame;
			
			eff->lr.add_theta = (65536/360 * MOVE_LR_ADD_THETA * 0x100) / go_frame;
			eff->lr.back_theta = -(65536/360 * MOVE_LR_ADD_THETA_BACK * 0x100) / back_frame;
			eff->lr.add_x = MOVE_LR_X_LEN * 0x100 / go_frame;
			eff->lr.back_x = -(MOVE_LR_X_LEN * 0x100 / back_frame);
			if(left_type == TRUE){
				eff->lr.add_theta *= -1;
				eff->lr.back_theta *= -1;
				eff->lr.add_x *= -1;
				eff->lr.back_x *= -1;
			}
		}
		
		eff->seq++;
		//break;
	case 1:
		if(finish == TRUE){
			eff->x += eff->lr.add_x * MOVE_FINISHDANCE_REVISION / 100;
			end_x = MOVE_LR_X_LEN * MOVE_FINISHDANCE_REVISION / 100;
			eff->lr.theta += eff->lr.add_theta * MOVE_FINISHDANCE_REVISION / 100;
		}
		else{
			eff->x += eff->lr.add_x;
			end_x = MOVE_LR_X_LEN;
			eff->lr.theta += eff->lr.add_theta;
		}
		
		if(abs(eff->x - eff->start_x) >= end_x * 0x0100){
			if(left_type == TRUE){
				eff->x = eff->start_x - end_x * 0x0100;
			}
			else{
				eff->x = eff->start_x + end_x * 0x0100;
			}
			eff->y = eff->start_y;
			eff->seq++;
		}
		break;
	case 2:
		if(finish == TRUE){
			eff->x += eff->lr.back_x * MOVE_FINISHDANCE_REVISION / 100;
			eff->lr.theta += eff->lr.back_theta * MOVE_FINISHDANCE_REVISION / 100;
		}
		else{
			eff->x += eff->lr.back_x;
			eff->lr.theta += eff->lr.back_theta;
		}
		
		if((left_type == TRUE && eff->x >= eff->start_x) 
				|| (left_type == FALSE && eff->x <= eff->start_x)){
			eff->x = eff->start_x;
			eff->lr.theta = 0;
			eff->seq++;
			end = TRUE;
		}
		break;
	default:
		return TRUE;
	}

	IMC_Player_SetRota(imcwork->imc_ptr, eff->lr.theta / 0x100);
	Move_PosSet(eff, ss, imcwork, rotation_pos, point, finish);
	return end;
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサー履歴初期化
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_MainDancerRecordInit(DANCE_PROC_WORK *dpw)
{
	int i;
	
	for(i = 0; i < DANCING_RECORD_MAX; i++){
		dpw->maindancer_record[i].occ = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメタスクを生成する
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @param   rotation_pos	ローテーション位置
 */
//--------------------------------------------------------------
void DT_PokemonDefaultAnimeTaskSet(DANCE_PROC_WORK *dpw, int breeder_no, int rotation_pos)
{
	GF_ASSERT(dpw->pda[breeder_no].tcb == NULL);
	
	MI_CpuClear8(&dpw->pda[breeder_no], sizeof(POKE_DEF_ANM_WORK));
	dpw->pda[breeder_no].dpw = dpw;
	dpw->pda[breeder_no].breeder_no = breeder_no;
	dpw->pda[breeder_no].rotation_pos = rotation_pos;
	dpw->pda[breeder_no].ss = dpw->sys.ss[breeder_no];
	dpw->pda[breeder_no].imcwork = &dpw->sys.imcwork[breeder_no];
	dpw->pda[breeder_no].move_start_req = 1;
	dpw->pda[breeder_no].move_init = 1;
	
	dpw->pda[breeder_no].tcb = TCB_Add(PokemonDefaultAnime, &dpw->pda[breeder_no], 
		TCBPRI_DANCE_DEFANM);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメタスクを全て削除する
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_PokemonDefaultAnimeTaskDelAll(DANCE_PROC_WORK *dpw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(dpw->pda[i].tcb != NULL){
			TCB_Delete(dpw->pda[i].tcb);
			dpw->pda[i].tcb = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：リクエスト設定
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @param   req				リクエスト番号(PDA_REQ_???)
 */
//--------------------------------------------------------------
void DT_PokemonDefaultAnimeReq(DANCE_PROC_WORK *dpw, int breeder_no, PDA_REQ req)
{
	if(dpw->pda[breeder_no].tcb == NULL){
		return;
	}
	
	switch(req){
	case PDA_REQ_AFF_SET:
		dpw->pda[breeder_no].aff_stop = 0;
		dpw->pda[breeder_no].aff_stop_req = 0;
		break;
	case PDA_REQ_AFF_STOP:
		dpw->pda[breeder_no].aff_stop = 1;
		break;
	case PDA_REQ_AFF_STOP_REQ:
		dpw->pda[breeder_no].aff_stop_req = 1;
		break;
	case PDA_REQ_MOVE_SET:
		dpw->pda[breeder_no].move_stop = 0;
		dpw->pda[breeder_no].move_stop_req = 0;
		dpw->pda[breeder_no].move_start_req = 1;
		break;
	case PDA_REQ_MOVE_STOP:
		if(dpw->pda[breeder_no].move_stop == 0){
			dpw->pda[breeder_no].move_stop = 1;
			if(dpw->pda[breeder_no].move_start_req == 0){
				dpw->pda[breeder_no].move_stop_sin = dpw->pda[breeder_no].move_sin;
			}
		}
		break;
	case PDA_REQ_MOVE_STOP_REQ:
		dpw->pda[breeder_no].move_stop_req = 1;
		break;
	default:
		GF_ASSERT(0 && "指定リクエストは用意されていません");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：拡縮アニメが停止状態かチェック
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @retval  TRUE:停止状態。　FASE:稼動状態
 */
//--------------------------------------------------------------
int DT_PokemonDefaultAnimeStopCheckAff(DANCE_PROC_WORK *dpw, int breeder_no)
{
	if(dpw->pda[breeder_no].tcb == NULL){
		return TRUE;
	}
	if(dpw->pda[breeder_no].aff_stop == 1 || dpw->pda[breeder_no].rotation_pos == 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：移動アニメが停止状態かチェック
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @retval  TRUE:停止状態。　FASE:稼動状態
 */
//--------------------------------------------------------------
int DT_PokemonDefaultAnimeStopCheckMove(DANCE_PROC_WORK *dpw, int breeder_no)
{
	if(dpw->pda[breeder_no].tcb == NULL){
		return TRUE;
	}
	if(dpw->pda[breeder_no].move_stop == 1){
		return TRUE;
	}
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：実行タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		常駐アニメ用ワーク
 */
//--------------------------------------------------------------
static void PokemonDefaultAnime(TCB_PTR tcb, void *work)
{
	POKE_DEF_ANM_WORK *pda = work;
	
	PokemonDefaultAnime_Affine(pda);
	
	PokemonDefaultAnime_Move(pda);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：拡縮
 * @param   pda		常駐アニメ用ワークへのポインタ
 * @param   add_aff	拡縮率加算値
 */
//--------------------------------------------------------------
static void PokemonDefaultAnime_Affine(POKE_DEF_ANM_WORK *pda)
{
	u64 aff_frame, add_aff;
	u32 old_aff_z;
	int aff_dir, old_aff_dir;;
	
	if(pda->aff_stop == 1 || pda->rotation_pos == 0){
		return;
	}
	
	aff_frame = pda->dpw->music_vcount;
	aff_frame *= ONE_TEMPO_CALC_DECIMAL;
	aff_frame %= pda->dpw->d_game.one_tempo_frame;
	
	add_aff = aff_frame * PDA_AFF_ADD_Z_MAX / (pda->dpw->d_game.one_tempo_frame / 2);
	aff_dir = TRUE;
	if(aff_frame >= (pda->dpw->d_game.one_tempo_frame / 2)){
		add_aff = PDA_AFF_ADD_Z_MAX - (add_aff - PDA_AFF_ADD_Z_MAX);
		aff_dir = FALSE;
	}

	old_aff_z = pda->aff_z;
	old_aff_dir = pda->aff_dir;
	pda->aff_z = DANCE_POKEPOS_Z_SUB * 0x100 + add_aff;
	pda->aff_dir = aff_dir;

	if(pda->aff_stop_req == 1){
		if(pda->aff_z == DANCE_POKEPOS_Z_SUB * 0x100 || old_aff_dir == FALSE && aff_dir == TRUE){
			pda->aff_z = DANCE_POKEPOS_Z_SUB * 0x100;
			pda->aff_stop_req = 0;
			pda->aff_stop = 1;
		}
	}

//	SoftSpriteParaSet(pda->ss, SS_PARA_POS_Z, pda->aff_z / 0x0100);
	pda->imcwork->z = pda->aff_z / 0x0100;
	DT_PokeAffineUpdateZ(pda->ss, pda->imcwork);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン常駐アニメ：移動アニメ
 * @param   pda			常駐アニメ用ワークへのポインタ
 * @param   offset_x
 */
//--------------------------------------------------------------
static void PokemonDefaultAnime_Move(POKE_DEF_ANM_WORK *pda)
{
	u32 old_sin;
	s32 offset_x, furihaba_x;
	u64 calc_frame, move_sin;
	
	old_sin = pda->move_sin;
	
	calc_frame = pda->dpw->music_vcount;
	calc_frame *= ONE_TEMPO_CALC_DECIMAL;
	calc_frame %= pda->dpw->d_game.one_tempo_frame * 2;

	move_sin = calc_frame * 360 / (pda->dpw->d_game.one_tempo_frame * 2);
	move_sin <<= 8;
	pda->move_sin = move_sin;
	
	if(pda->move_stop > 0){
		return;
	}
	
	if(pda->move_init == 1){
		old_sin = move_sin;
		pda->move_init = 0;
	}
	
	if(pda->move_start_req == 1){
		u32 now;	//360度を越えて0に戻る時に、比較しやすいように360+nowにする
		u32 stop, old;
		if(old_sin > move_sin){
			now = old_sin + move_sin;
		}
		else{
			now = move_sin;
		}
		stop = pda->move_stop_sin;
		old = old_sin;
		if(pda->move_stop_sin == move_sin || (old <= stop && stop <= now)){
			pda->move_start_req = 0;
		}
		else{
			return;
		}
	}
	
	if(pda->move_stop_req == 1){
		if(move_sin == 0 || old_sin > move_sin){
			move_sin = 0;
			pda->move_stop_req = 0;
			pda->move_stop = 1;
			pda->move_stop_sin = move_sin;
		}
	}

	furihaba_x = pda->rotation_pos == 0 ? PDA_MOVE_FURIHABA_X_MAIN : PDA_MOVE_FURIHABA_X_BACK;
	offset_x = Cos360(pda->move_sin >> 8) * furihaba_x / FX32_ONE;//>> FX32_SHIFT;
	
//	SoftSpriteParaSet(pda->ss, SS_PARA_POS_X, offset_x + DancePokePos[pda->rotation_pos][0]);
	pda->imcwork->x = offset_x + DancePokePos[pda->rotation_pos][0] - furihaba_x;
	IMC_Player_SetPokeMatrix(pda->imcwork->imc_ptr, pda->imcwork->x, pda->imcwork->y);
}

//--------------------------------------------------------------
/**
 * @brief   メッセージタグ展開
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
static void DT_MessageTagExpand(DANCE_PROC_WORK *dpw, int msg_tag, const DTAG_PARAM *tagpara)
{
	u32 str_id;
	
	if(msg_tag != DTAG_NONE){
		GF_ASSERT(tagpara != NULL);
	}
	
	switch(msg_tag){
	case DTAG_NONE:
		break;
	
	case DTAG_NICK:
		WORDSET_RegisterPokeNickName(dpw->sys.wordset, 0, 
			PPPPointerGet(dpw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case DTAG_RANK:
		str_id = ConTool_GetRankMsgID(dpw->consys->c_game.rank, dpw->consys->c_game.mode, 
			dpw->consys->sio_flag);
		WORDSET_RegisterContestRank(dpw->sys.wordset, 0, str_id);
		break;
	case DTAG_NUM:
		WORDSET_RegisterNumber(dpw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case DTAG_OYA_NICK:
		WORDSET_RegisterWord(dpw->sys.wordset, 0, 
			dpw->consys->c_game.breeder_name_str[tagpara->mine_brd], 
			dpw->consys->c_game.player_sex[tagpara->mine_brd], TRUE, PM_LANG);
		WORDSET_RegisterPokeNickName(dpw->sys.wordset, 1, 
			PPPPointerGet(dpw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case DTAG_NICK_NUM:
		WORDSET_RegisterPokeNickName(dpw->sys.wordset, 0, 
			PPPPointerGet(dpw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterNumber(dpw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case DTAG_RANK_NUM_OYA_NICK:
		str_id = ConTool_GetRankMsgID(dpw->consys->c_game.rank, dpw->consys->c_game.mode,
			dpw->consys->sio_flag);
		WORDSET_RegisterContestRank(dpw->sys.wordset, 0, str_id);

		WORDSET_RegisterNumber(dpw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);

		WORDSET_RegisterWord(dpw->sys.wordset, 2, 
			dpw->consys->c_game.breeder_name_str[tagpara->mine_brd], 
			dpw->consys->c_game.player_sex[tagpara->mine_brd], TRUE, PM_LANG);
		WORDSET_RegisterPokeNickName(dpw->sys.wordset, 3, 
			PPPPointerGet(dpw->sys.c_game->pp[tagpara->mine_brd]));
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
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   msg_id		メッセージID
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
static void DT_TalkMessageSet(DANCE_PROC_WORK *dpw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const DTAG_PARAM *tagpara)
{
	STRBUF *message_src;
	int wait;
	
//	BattleMSG_TagExpand(bw,mp);
//	BattleMSG_MsgExpand(bw,msg_m,mp);

	if(dpw->consys->sio_flag == FALSE){
		wait = CONFIG_GetMsgPrintSpeed(dpw->consys->config);
	}
	else{
		wait = CONTEST_SIO_MSG_SPEED;
	}
	message_src = MSGMAN_AllocString(msg_man, msg_id);
	DT_MessageTagExpand(dpw, msg_tag, tagpara);
	WORDSET_ExpandStr(dpw->sys.wordset, dpw->sys.msg_buf, message_src);

	GF_BGL_BmpWinDataFill(&dpw->sys.win[DANCE_BMPWIN_TALK], 0xff);
	dpw->sys.talk_msg_index = GF_STR_PrintSimple(&dpw->sys.win[DANCE_BMPWIN_TALK], 
		FONT_TALK, dpw->sys.msg_buf, 0, 0, wait, NULL);

	STRBUF_Delete(message_src);
}

//--------------------------------------------------------------
/**
 * @brief   ノーマル会話用のメッセージセット
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara			タグ展開する場合、参照されるパラメータ類
 *                  	    (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
void DT_A_TalkMessageSet(DANCE_PROC_WORK *dpw, u32 a_talk_id, const DTAG_PARAM *tagpara)
{
	u32 msg_id, msg_tag;
	
	GF_ASSERT(a_talk_id < NELEMS(DanceTalkMsgData));
	
	msg_id = DanceTalkMsgData[a_talk_id].msg_id;
	msg_tag = DanceTalkMsgData[a_talk_id].msg_tag;
	DT_TalkMessageSet(dpw, dpw->sys.dance_msg, msg_id, msg_tag, tagpara);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージフォントが表示しきっているかチェック
 * @param   dpw		ダンス部門管理ワークへのポインタ
 * @retval  0=終了
 */
//--------------------------------------------------------------
int DT_TalkMessageEndCheck(DANCE_PROC_WORK *dpw)
{
	return GF_MSG_PrintEndCheck(dpw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   プリンのリソースをセットする
 *
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_PrinResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		PRIN_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, D_CHARID_PRIN);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		PRIN_NCER_BIN, 1, 
		D_CELLID_PRIN);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		PRIN_NANR_BIN, 1, D_CELLANMID_PRIN);
}

//--------------------------------------------------------------
/**
 * @brief   プリンのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_PrinResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, D_CHARID_PRIN);
	CATS_FreeResourceCell(crp, D_CELLID_PRIN);
	CATS_FreeResourceCellAnm(crp, D_CELLANMID_PRIN);
}

//--------------------------------------------------------------
/**
 * @brief   プリンアクターを生成する
 *
 * @param   dpw
 * @param   csp		
 * @param   crp		
 */
//--------------------------------------------------------------
void DT_PrinCreate(DANCE_PROC_WORK *dpw, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	PRIN_WORK *pw;
	
	GF_ASSERT(dpw->sys.prin_sys == NULL);
	
	pw = sys_AllocMemory(HEAPID_DANCE, sizeof(PRIN_WORK));
	MI_CpuClear8(pw, sizeof(PRIN_WORK));

	dpw->sys.prin_sys = pw;
	pw->dpw = dpw;
	
	pw->cap = CATS_ObjectAdd_S(dpw->sys.csp, dpw->sys.crp, &PrinObjParam);
	CATS_ObjectUpdate(pw->cap->act);
	CATS_ObjectEnableCap(pw->cap, CATS_ENABLE_FALSE);
	
	pw->tcb = TCB_Add(PrinMainTask, pw, TCBPRI_PRIN_MAIN);
}

//--------------------------------------------------------------
/**
 * @brief   プリンアクターを削除する
 *
 * @param   dpw
 */
//--------------------------------------------------------------
void DT_PrinFree(DANCE_PROC_WORK *dpw)
{
	TCB_Delete(dpw->sys.prin_sys->tcb);
	CATS_ActorPointerDelete_S(dpw->sys.prin_sys->cap);
	
	sys_FreeMemoryEz(dpw->sys.prin_sys);
	dpw->sys.prin_sys = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   プリン動作メインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		プリン動作ワーク
 */
//--------------------------------------------------------------
static void PrinMainTask(TCB_PTR tcb, void *work)
{
	PRIN_WORK *pw = work;
	enum{
		SEQ_INIT,
		SEQ_WAIT,
		SEQ_FRAME_UPDATE,
	};
	
	switch(pw->seq){
	case SEQ_INIT:
		pw->seq++;
		break;
	case SEQ_WAIT:
		break;
	case SEQ_FRAME_UPDATE:
		break;
	}
	
	CATS_ObjectUpdate(pw->cap->act);
}

//--------------------------------------------------------------
/**
 * @brief   プリンの位置、アニメを更新する(経過フレームと終了フレームから計算)
 *
 * @param   pw				プリン動作ワークへのポインタ
 * @param   now_frame		現在のフレーム
 * @param   end_frame		最終フレーム
 */
//--------------------------------------------------------------
void PrinReq_FrameUpdate(PRIN_WORK *pw, u32 now_frame, u32 end_frame)
{
	u32 len, one_len, len_decimal, one_len_offset;
	int x, y, one_percent;
	
	len = now_frame * MUSIC_BAR_LEN / end_frame;	//現在のメータードット位置
	
	one_len = (MUSIC_BAR_LEN * ONE_TEMPO_CALC_DECIMAL) / TEMPO_BASE_ONPU;		//1拍のドット数
	len_decimal = len * ONE_TEMPO_CALC_DECIMAL;
	one_len_offset = (len * ONE_TEMPO_CALC_DECIMAL) % one_len;
	//山なりはSin180度で表現するので現在のオフセットをMax180段階のパーセンテージに変換する
	one_percent = 180 * one_len_offset / one_len;
	
	
	x = len;
	y = PRIN_POS_Y;
	y -= Sin360(one_percent) * PRIN_FURIHABA_Y / FX32_ONE;
	CATS_ObjectPosSetCap_SubSurface(pw->cap, x, y, DANCE_SUB_ACTOR_DISTANCE);
	CATS_ObjectEnableCap(pw->cap, CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   プリン動作リクエスト：画面外へ移動
 * @param   pw		プリン動作ワークへのポインタ
 */
//--------------------------------------------------------------
void PrinReq_OutMove(PRIN_WORK *pw)
{
	CATS_ObjectEnableCap(pw->cap, CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   プリン動作リクエスト：画面内に登場させる
 * @param   pw		プリン動作ワークへのポインタ
 */
//--------------------------------------------------------------
void PrinReq_InMove(PRIN_WORK *pw)
{
	CATS_ObjectEnableCap(pw->cap, CATS_ENABLE_TRUE);
	CATS_ObjectPosSetCap_SubSurface(pw->cap, 0, PRIN_POS_Y, DANCE_SUB_ACTOR_DISTANCE);
}

//--------------------------------------------------------------
/**
 * @brief   ダンスする回数を取得する
 * @param   con_rank		CONRANK_???
 * @retval  ダンスする回数
 */
//--------------------------------------------------------------
int DT_DanceNumGet(int con_rank)
{
	const u8 DanceNum[] = {3,3,4,4};
	
	GF_ASSERT(NELEMS(DanceNum) - 1 == CONRANK_MASTER);
	return DanceNum[con_rank];
}

//--------------------------------------------------------------
/**
 * @brief   看板メッセージ表示
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara			タグ展開する場合、参照されるパラメータ類
 *                  	    (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
void DT_PanelMessagePut(DANCE_PROC_WORK *dpw, u32 a_talk_id, const DTAG_PARAM *tagpara)
{
	u32 msg_id, msg_tag;
	STRBUF *message_src;
	
	GF_ASSERT(a_talk_id < NELEMS(DanceTalkMsgData));
	
	if(dpw->bord_msg_flag == TRUE){
		return;
	}
	
	//ウィンドウ描画
	BmpTalkWinWrite(&dpw->sys.win[DANCE_BMPWIN_PANEL], WINDOW_TRANS_OFF,
		DANCE_TALKWIN_CGX_OFFSET, DANCE_TALKWIN_PALNO);
	GF_BGL_LoadScreenV_Req(dpw->sys.bgl, DANCE_FRAME_WIN);
	
	//A_TALKのIDとタグID取得
	msg_id = DanceTalkMsgData[a_talk_id].msg_id;
	msg_tag = DanceTalkMsgData[a_talk_id].msg_tag;

	//メッセージ描画
	message_src = MSGMAN_AllocString(dpw->sys.dance_msg, msg_id);
	DT_MessageTagExpand(dpw, msg_tag, tagpara);
	WORDSET_ExpandStr(dpw->sys.wordset, dpw->sys.msg_buf, message_src);

	GF_BGL_BmpWinDataFill(&dpw->sys.win[DANCE_BMPWIN_PANEL], 0xff);
	GF_STR_PrintSimple(&dpw->sys.win[DANCE_BMPWIN_PANEL], 
		FONT_TALK, dpw->sys.msg_buf, 0, 0, MSG_ALLPUT, NULL);

	STRBUF_Delete(message_src);
	
	dpw->bord_msg_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   看板メッセージをクリアする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_PanelMessageClear(DANCE_PROC_WORK *dpw)
{
	BmpTalkWinClear(&dpw->sys.win[DANCE_BMPWIN_PANEL], WINDOW_TRANS_OFF);
	GF_BGL_LoadScreenV_Req(dpw->sys.bgl, DANCE_FRAME_WIN);
	dpw->bord_msg_flag = FALSE;
}


//--------------------------------------------------------------
/**
 * @brief   準備終了まで後、何フレーム残されているかチェック
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   musicdata			曲データ
 * @param   now_count			何番目のダンサーか
 *
 * @retval  準備終了までの残りフレーム数(マイナスの場合は既に準備フレームは過ぎている)
 */
//--------------------------------------------------------------
s64 DT_ReadyEndFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, int now_count)
{
	s64 frame;
	
	frame = (dpw->d_game.all_tempo_frame * musicdata->loop) * now_count;
	frame += ((dpw->d_game.ready_frame + dpw->d_game.rotation_frame) 
		* now_count + dpw->d_game.ready_frame) / ONE_TEMPO_CALC_DECIMAL;
	
	return frame - dpw->music_vcount;
}

//--------------------------------------------------------------
/**
 * @brief   ローテーション終了まで後、何フレーム残されているかチェック
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   musicdata			曲データ
 * @param   now_count			何番目のダンサーか
 *
 * @retval  ローテーション終了までの残りフレーム数(マイナスの場合は既に過ぎている)
 */
//--------------------------------------------------------------
s64 DT_RotationEndFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, 
	int now_count)
{
	s64 frame;
	
	frame = (dpw->d_game.all_tempo_frame * musicdata->loop) * (now_count + 1);
	frame += ((dpw->d_game.ready_frame + dpw->d_game.rotation_frame) 
		* now_count + dpw->d_game.ready_frame + dpw->d_game.rotation_frame)
		/ ONE_TEMPO_CALC_DECIMAL;
	
	return frame - dpw->music_vcount;
}

//--------------------------------------------------------------
/**
 * @brief   ダンス開始まで後、何フレーム残されているかチェック
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   musicdata			曲データ
 * @param   now_count			何番目のダンサーか
 *
 * @retval  ダンス開始までの残りフレーム数(マイナスの時は既にダンスが始まっている)
 */
//--------------------------------------------------------------
s64 DT_DancingStartFrameCheck(DANCE_PROC_WORK *dpw, const DANCE_MUSIC_DATA *musicdata, 
	int now_count)
{
	s64 frame;
	
	frame = DT_ReadyEndFrameCheck(dpw, musicdata, now_count);
	return frame;
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンのアピールアニメ
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   imcwork			対象のポケモンのイメージクリップへのポインタ
 * @param   end_flag		終了後、ここにTRUEが入ります
 */
//--------------------------------------------------------------
void DT_PokeAppealMove(DANCE_PROC_WORK *dpw, int breeder_no, u8 *end_flag)
{
	POKE_APPEAL_ANIME *paa;
	
	*end_flag = FALSE;
	
	paa = sys_AllocMemory(HEAPID_DANCE, sizeof(POKE_APPEAL_ANIME));
	MI_CpuClear8(paa, sizeof(POKE_APPEAL_ANIME));
	
	paa->dpw = dpw;
	paa->imcwork = &dpw->sys.imcwork[breeder_no];
	paa->shadow = &dpw->sys.shadow[breeder_no];
	paa->end_flag = end_flag;
	
	if(dpw->sys.jump_up[breeder_no] == TRUE){
		TCB_Add(PokeAppealMoveTask, paa, TCBPRI_DANCE_EFFECT_BASE_PRI);
	}
	else{
		TCB_Add(PokeAppealMoveTaskLR, paa, TCBPRI_DANCE_EFFECT_BASE_PRI);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンアピールアニメメインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		ポケモンアピールアニメワークへのポインタ
 */
//--------------------------------------------------------------
static void PokeAppealMoveTask(TCB_PTR tcb, void *work)
{
	POKE_APPEAL_ANIME *paa = work;
	
	switch(paa->seq){
	case 0:
		DT_ShadowHomingFlagSet(paa->shadow, TRUE, FALSE);
		paa->start_y = paa->imcwork->y * 0x100;
		paa->y = paa->start_y;
		paa->up_power = PAA_UP_POWER;
		paa->seq++;
		//break;
	case 1:
		paa->y -= paa->up_power;
		paa->up_power -= PAA_GRAVITY;
		if(paa->y >= paa->start_y){
			paa->y = paa->start_y;
			paa->loop++;
			if(paa->loop > PAA_JUMP_LOOP){
				paa->seq++;
			}
			else{
				paa->seq = 0;
			}
		}
		paa->imcwork->y = paa->y / 0x100;
		IMC_Player_SetPokeMatrix(paa->imcwork->imc_ptr, paa->imcwork->x, paa->imcwork->y);
		break;
	default:
		*(paa->end_flag) = TRUE;
		DT_ShadowHomingFlagSet(paa->shadow, TRUE, TRUE);
		
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンアピールアニメメインタスク(ジャンプじゃないversion)
 * @param   tcb			TCBへのポインタ
 * @param   work		ポケモンアピールアニメワークへのポインタ
 */
//--------------------------------------------------------------
static void PokeAppealMoveTaskLR(TCB_PTR tcb, void *work)
{
	POKE_APPEAL_ANIME *paa = work;
	s32 offset_x;
	fx32 before_angle;
	
	switch(paa->seq){
	case 0:
		paa->start_x = paa->imcwork->x * 0x100;
		paa->x = paa->start_x;
		paa->seq++;
		//break;
	case 1:
		offset_x = Sin360FX(paa->angle) * PAA_LR_FURIHABA / FX32_ONE;
		before_angle = paa->angle;
		paa->angle += PAA_LR_ADD_ANGLE;
		
		if((paa->angle >> FX32_SHIFT) >= 360){
			paa->loop++;
			if(paa->loop > PAA_LR_SIN_LOOP){
				paa->x = paa->start_x;
				offset_x = 0;
				paa->seq++;
			}
		}
		
		paa->imcwork->x = paa->x / 0x100 + offset_x;
		IMC_Player_SetPokeMatrix(paa->imcwork->imc_ptr, paa->imcwork->x, paa->imcwork->y);
		break;
	default:
		*(paa->end_flag) = TRUE;
		
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行半透明BGのデフォルトデータ設定
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_BGAlphaDefaultDataSet(DANCE_PROC_WORK *dpw)
{
#if 0	//パレットフェードに変更 2006.05.08(月)
	u8 *char_adrs;
	u16 *scrn_adrs;
	
	char_adrs = GF_BGL_CgxGet(DANCE_FRAME_EFF);
	MI_CpuFill8(&char_adrs[DANCE_BGALPHA_SPACE_CHARNO * 0x20], 0, 0x20);
	MI_CpuFill8(&char_adrs[DANCE_BGALPHA_CHARNO * 0x20], 
		DanceBGAlphaCharCode[DANCE_BGALPHA_TYPE_NULL], 0x20);
	
	scrn_adrs = GF_BGL_ScreenAdrsGet(dpw->sys.bgl, DANCE_FRAME_EFF);
	MI_CpuFill16(scrn_adrs, DANCE_BGALPHA_SCREEN_CODE, 32 * DANCE_BGALPHA_SCREEN_SIZE_Y * 2);
	//譜面部分は半透明BGがかからないようにクリアしておく
	MI_CpuFill16(&scrn_adrs[32 * DANCE_BGALPHA_SCREEN_SIZE_Y], 
		DANCE_BGALPHA_SPACE_CHARNO, 0x800 - (32 * DANCE_BGALPHA_SCREEN_SIZE_Y * 2));
	
	PaletteWorkSet(dpw->sys.pfd, DanceBGAlphaColorData, FADE_MAIN_BG, 
		DANCE_ALPHA_BG_PALNO * 16, sizeof(DanceBGAlphaColorData));
	
	GF_BGL_LoadScreenV_Req(dpw->sys.bgl, DANCE_FRAME_EFF);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行半透明BGのデフォルトBLENDレジスタ設定を行う
 */
//--------------------------------------------------------------
void DT_BGAlphaDefaultBlendModeSet(void)
{
#if 0	//パレットフェードに変更 2006.05.08(月)
	G2_SetBlendAlpha(DANCE_BGALPHA_PLANE_1, DANCE_BGALPHA_PLANE_2, 
		DanceBGAlphaEvy[DANCE_BGALPHA_TYPE_NULL].ev1, 
		DanceBGAlphaEvy[DANCE_BGALPHA_TYPE_NULL].ev2);
#else
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0, 0);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行半透明BGのエフェクト切り替え
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   bgalpha_type		DANCE_BGALPHA_TYPE_???
 */
//--------------------------------------------------------------
void DT_BGAlphaEffectSet(DANCE_PROC_WORK *dpw, int bgalpha_type)
{
#if 0	//パレットフェードに変更 2006.05.08(月)
	u8 *char_adrs;
	
	char_adrs = GF_BGL_CgxGet(DANCE_FRAME_EFF);
	MI_CpuFill8(&char_adrs[DANCE_BGALPHA_CHARNO * 0x20], 
		DanceBGAlphaCharCode[bgalpha_type], 0x20);
	G2_ChangeBlendAlpha(DanceBGAlphaEvy[bgalpha_type].ev1, DanceBGAlphaEvy[bgalpha_type].ev2);
#else
//	ColorConceChangePfd(dpw->sys.pfd, FADE_MAIN_BG, DANCE_DISP_BG_FADE_BIT, 
//		DanceBGFadeData[bgalpha_type].evy, DanceBGFadeData[bgalpha_type].next_rgb);
	u16 *def_wk;
	
	def_wk = PaletteWorkDefaultWorkGet(dpw->sys.pfd, FADE_MAIN_BG);
	ColorConceChange(def_wk, dpw->middle_fade.buf, DANCE_DISP_BG_FADE_BIT, 
		DanceBGFadeData[bgalpha_type].evy, DanceBGFadeData[bgalpha_type].next_rgb);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行半透明BGのエフェクトセット(DANCING_PARAMを引数として取るVer)
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   dancing_param		ダンスパラメータ
 */
//--------------------------------------------------------------
void DT_BGAlphaEffectSet_DancingParam(DANCE_PROC_WORK *dpw, const DANCING_PARAM *dancing_param)
{
	int bgalpha_type;
	
	if(dancing_param->rotation_pos != 0){
		return;
	}
	
	switch(dancing_param->review_type){
	case REVIEW_TYPE_EXCELLENT:
	case REVIEW_TYPE_GOOD:
		switch(dancing_param->dance_step){
		case DANCE_STEP_JUMP:
			bgalpha_type = DANCE_BGALPHA_TYPE_UP;
			break;
		case DANCE_STEP_ADVANCE:
			bgalpha_type = DANCE_BGALPHA_TYPE_DOWN;
			break;
		case DANCE_STEP_LEFT:
			bgalpha_type = DANCE_BGALPHA_TYPE_LEFT;
			break;
		case DANCE_STEP_RIGHT:
			bgalpha_type = DANCE_BGALPHA_TYPE_RIGHT;
			break;
		}
		break;
	case REVIEW_TYPE_FAILED:
	default:
		bgalpha_type = DANCE_BGALPHA_TYPE_FAILED;
		break;
	}
	
	DT_BGAlphaEffectSet(dpw, bgalpha_type);
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサーのダンス履歴を参照してダンス実行半透明BGエフェクトをセットする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 * @param   frame   現在のダンスフレーム
 */
//--------------------------------------------------------------
void DT_BGAlphaEffectSet_MainDancerHistory(DANCE_PROC_WORK *dpw, u32 frame)
{
	int i;
	u32 check_frame;
	u32 half_tempo_frame;
	
	half_tempo_frame = dpw->d_game.one_tempo_frame >> 1;
	
	for(i = 0; i < DANCING_RECORD_MAX; i++){
		if(dpw->maindancer_record[i].occ == TRUE){
			check_frame = (dpw->maindancer_record[i].hit_beat + DANCE_BEAT / 2) 
				* half_tempo_frame;
			CP_SetDiv32_32(check_frame, ONE_TEMPO_CALC_DECIMAL);
			check_frame = CP_GetDivResult32();
			if(check_frame == frame){
				DT_BGAlphaEffectSet_DancingParam(dpw, &dpw->maindancer_record[i]);
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   譜面をフラッシュタスクを生成する
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_FumenFlashTaskSet(DANCE_PROC_WORK *dpw)
{
	FUMEN_FLASH_WORK *ffw;
	
	GF_ASSERT(dpw->sys.fumen_flash.tcb == NULL);
	
	ffw = &dpw->sys.fumen_flash;
	ffw->dpw = dpw;
	
	ffw->tcb = TCB_Add(FumenFlashMainTask, ffw, TCBPRI_DANCE_EFFECT_BASE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   譜面フラッシュタスクを削除する
 *
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_FumenFlashTaskDel(DANCE_PROC_WORK *dpw)
{
	if(dpw->sys.fumen_flash.tcb == NULL){
		return;
	}
	TCB_Delete(dpw->sys.fumen_flash.tcb);
	dpw->sys.fumen_flash.tcb = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   譜面フラッシュ：エフェクトリクエスト
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   dancer_type		DANCER_MAIN or DANCER_BACK
 */
//--------------------------------------------------------------
void DT_FumenFlashEffectSet(DANCE_PROC_WORK *dpw, int dancer_type)
{
	FUMEN_FLASH_WORK *ffw;

	ffw = &dpw->sys.fumen_flash;
	GF_ASSERT(ffw->tcb != NULL);
	
	if(dancer_type == DANCER_MAIN){
		ffw->color_pos = FUMEN_PALNO_MAIN * 16;
	}
	else{
		ffw->color_pos = FUMEN_PALNO_BACK * 16;
	}
	ffw->occ = TRUE;
	ffw->evy = FUMEN_FLASH_START_EVY;
	
	Snd_SePlay(DSE_MY_TURN);
}

//--------------------------------------------------------------
/**
 * @brief   譜面フラッシュ：メイン動作タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		譜面フラッシュワークへのポインタ
 */
//--------------------------------------------------------------
static void FumenFlashMainTask(TCB_PTR tcb, void *work)
{
	FUMEN_FLASH_WORK *ffw = work;
	
	if(ffw->occ == FALSE){
		return;
	}
	
#if 1
//	SoftFadePfd(ffw->dpw->sys.pfd, FADE_MAIN_BG, ffw->color_pos, 16, 
//		ffw->evy >> 8, FUMEN_FLASH_COLOR);
	{
		u16 *def_wk;
		def_wk = PaletteWorkDefaultWorkGet(ffw->dpw->sys.pfd, FADE_MAIN_BG);
		SoftFade(&def_wk[ffw->color_pos], &ffw->dpw->middle_fade.buf[ffw->color_pos], 
			16, ffw->evy >> 8, FUMEN_FLASH_COLOR);
	}
#else	//ダンス実行半透明BGがパレットフェードになったので、フェードが行われた後の転送用パレットを
		//元データとして使用するように変更 2006.05.08(月)
	{
		u16 *trans_work;
		trans_work = PaletteWorkTransWorkGet(ffw->dpw->sys.pfd, FADE_MAIN_BG);
		SoftFade(&trans_work[ffw->color_pos], &trans_work[ffw->color_pos], 16, 
			ffw->evy >> 8, FUMEN_FLASH_COLOR);
	}
#endif

	if(ffw->evy == 0){
		ffw->occ = FALSE;
	}
	else if(ffw->evy > FUMEN_FLASH_SUB_EVY){
		ffw->evy -= FUMEN_FLASH_SUB_EVY;
	}
	else{
		ffw->evy = 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   エミッタ登録
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   res_no		リソース番号
 * @param   x			座標X
 * @param   y			座標Y
 * @param   z			座標Z
 * @param   gen_num		放出レート
 */
//--------------------------------------------------------------
void DT_EmitterCreate(DANCE_PROC_WORK *dpw, u32 res_no, 
	s32 x, s32 y, s32 z, fx32 gen_num)
{
	dpw->particle_temp.x = x;
	dpw->particle_temp.y = y;
	dpw->particle_temp.z = z;
	dpw->particle_temp.gen_num = gen_num;
	
	Particle_CreateEmitterCallback(dpw->ptc, res_no, EmitCall_PosSet, dpw);
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの座標を設定する
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
static void EmitCall_PosSet(EMIT_PTR emit)
{
	DANCE_PROC_WORK *dpw;
	DANCE_PARTICLE_TEMP_WORK *ptw;
	
	dpw = Particle_GetTempPtr();
	ptw = &dpw->particle_temp;
	
	SPL_SetEmitterPositionX(emit, ptw->x);
	SPL_SetEmitterPositionY(emit, ptw->y);
	SPL_SetEmitterPositionZ(emit, ptw->z);
	
	SplSub_SetEmitterGenerationRatio(emit, ptw->gen_num);
}

//--------------------------------------------------------------
/**
 * @brief   譜面パーティクルセット
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   hit_beat			表示する小節位置
 * @param   level				表示レベル
 */
//--------------------------------------------------------------
static void DT_ParticleFumenSet(DANCE_PROC_WORK *dpw, int hit_beat, int level)
{
	s32 x;
	
	GF_ASSERT(hit_beat < NELEMS(FumenParticlePosX));
	x = FumenParticlePosX[hit_beat];
	
	if(level == FUMEN_PARTICLE_LV1){
		DT_EmitterCreate(dpw, EMIT_NO_SUCCEED_LOW_0, x, DANCE_PARTICLE_FUMEN_CENTER_Y, 
			DANCE_PARTICLE_DEFAULT_Z, FX32_ONE);
		DT_EmitterCreate(dpw, EMIT_NO_SUCCEED_LOW_1, x, DANCE_PARTICLE_FUMEN_CENTER_Y, 
			DANCE_PARTICLE_DEFAULT_Z, FX32_ONE);
	}
	else{
		DT_EmitterCreate(dpw, EMIT_NO_SUCCEED_HIGH_0, x, DANCE_PARTICLE_FUMEN_CENTER_Y, 
			DANCE_PARTICLE_DEFAULT_Z, FX32_ONE);
		DT_EmitterCreate(dpw, EMIT_NO_SUCCEED_HIGH_1, x, DANCE_PARTICLE_FUMEN_CENTER_Y, 
			DANCE_PARTICLE_DEFAULT_Z, FX32_ONE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   決めダンスパーティクルセット
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   level			FINISH_PARTICLE_LV???
 */
//--------------------------------------------------------------
static void DT_ParticleFinishSet(DANCE_PROC_WORK *dpw, int level)
{
	fx32 gen_num = FX32_ONE;
	
	if(level == FINISH_PARTICLE_LV1){
//		gen_num += point * FINISH_PARTICLE_POINT_RATE;
//		if(gen_num > FINISH_PARTICLE_POINT_RATE_MAX){
//			gen_num = FINISH_PARTICLE_POINT_RATE_MAX;
//		}
		//左
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_0, 
			DANCE_PARTICLE_FINISH_LEFT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_1, 
			DANCE_PARTICLE_FINISH_LEFT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_2, 
			DANCE_PARTICLE_FINISH_LEFT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		//右
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_0, 
			DANCE_PARTICLE_FINISH_RIGHT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_1, 
			DANCE_PARTICLE_FINISH_RIGHT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_LOW_2, 
			DANCE_PARTICLE_FINISH_RIGHT_LV1, DANCE_PARTICLE_FINISH_Y_LV1, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
	}
	else{
//		gen_num += (point - FINISH_PARTICLE_CHANGE_POINT) * FINISH_PARTICLE_POINT_RATE;
//		if(gen_num > FINISH_PARTICLE_POINT_RATE_MAX){
//			gen_num = FINISH_PARTICLE_POINT_RATE_MAX;
//		}
		//左
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_0, 
			DANCE_PARTICLE_FINISH_LEFT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_1, 
			DANCE_PARTICLE_FINISH_LEFT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_2, 
			DANCE_PARTICLE_FINISH_LEFT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_3, 
			DANCE_PARTICLE_FINISH_LEFT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_4, 
			DANCE_PARTICLE_FINISH_LEFT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		//右
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_0, 
			DANCE_PARTICLE_FINISH_RIGHT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_1, 
			DANCE_PARTICLE_FINISH_RIGHT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_2, 
			DANCE_PARTICLE_FINISH_RIGHT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_3, 
			DANCE_PARTICLE_FINISH_RIGHT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
		DT_EmitterCreate(dpw, EMIT_NO_FINISH_HIGH_4, 
			DANCE_PARTICLE_FINISH_RIGHT_LV2, DANCE_PARTICLE_FINISH_Y_LV2, 
			DANCE_PARTICLE_DEFAULT_Z, gen_num);
	}
	
	//フラッシュフェード
//	ChangeBrightnessRequest(4, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE, 
//		PLANEMASK_ALL, MASK_MAIN_DISPLAY);

	DT_MiddlePaletteFadeReq(dpw, DANCE_DISP_BG_FADE_BIT, 8, 16, 0, 0x7fff);
	PaletteFadeReq(dpw->sys.pfd, PF_BIT_MAIN_OBJ, DANCE_DISP_OBJ_FADE_BIT, -1, 
		16, 0, 0x7fff);
	
	//3D面も含めて白くする
	G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD, 16);
	TCB_Add(FinishRecoverAlphaSet, dpw, 1000);
	
	Snd_SePlay(DSE_FINISH_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   フィニッシュのフラッシュ演出で行ったハードフェードを元に戻す
 * @param   tcb			TCBへのポインタ
 * @param   work		演技力部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void FinishRecoverAlphaSet(TCB_PTR tcb, void *work)
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0, 0);
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   パレット中間バッファに対してパレットフェードリクエストを行う
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   fade_bit		フェードビット
 * @param   frame			何フレームでフェードするか
 * @param   start_evy		開始EVY値
 * @param   end_evy			終了EVY値
 * @param   next_rgb		変更後のカラー
 */
//--------------------------------------------------------------
void DT_MiddlePaletteFadeReq(DANCE_PROC_WORK *dpw, u32 fade_bit, u32 frame, 
	int start_evy, int end_evy, u16 next_rgb)
{
	DANCE_MIDDLE_FADE *mf;
	
	mf = &dpw->middle_fade;
	mf->now_evy = start_evy << 8;
	mf->end_evy = end_evy << 8;
	mf->next_rgb = next_rgb;
	mf->fade_bit = fade_bit;
	mf->add_evy = ((end_evy - start_evy) * 0x100) / frame;
	mf->req = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   パレット中間バッファがフェード実行中か調べる
 * @param   dpw		ダンス部門管理ワークへのポインタ
 * @retval  TRUE:実行中。　FALSE:実行していない
 */
//--------------------------------------------------------------
BOOL DT_MiddlePaletteFadeCheck(DANCE_PROC_WORK *dpw)
{
	if(dpw->middle_fade.req == TRUE){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   中間バッファ有効フラグをセットする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 * @param   occ		TRUE:有効。　FALSE:無効。
 */
//--------------------------------------------------------------
void DT_MiddlePaletteOccSet(DANCE_PROC_WORK *dpw, int occ)
{
	dpw->middle_fade.occ = occ;
}

//--------------------------------------------------------------
/**
 * @brief   ライト演出を当てる
 *
 * @param   dpw						ダンス部門管理ワークへのポインタ
 * @param   main_dancer_breeder_no	メインダンサーのブリーダー番号
 * @param   dancer_type				ダンサータイプ(DANCER_MAIN or DANCER_BACK)
 */
//--------------------------------------------------------------
void DT_DancerLightEffectSet(DANCE_PROC_WORK *dpw, int main_dancer_breeder_no, int dancer_type)
{
	int i;
	GXRgb main_color, back_color;
	
	if(dancer_type == DANCER_MAIN){
		main_color = IMC_LIGHT_COLOR_NORMAL;
		back_color = IMC_LIGHT_COLOR_BLACK;
	}
	else{
		main_color = IMC_LIGHT_COLOR_BLACK;
		back_color = IMC_LIGHT_COLOR_NORMAL;
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(i == main_dancer_breeder_no){
			IMC_Player_SetColor(dpw->sys.imcwork[i].imc_ptr, main_color);
		}
		else{
			IMC_Player_SetColor(dpw->sys.imcwork[i].imc_ptr, back_color);
		}
	}
	
	Snd_SePlay(DSE_LIGHT_ON);
}

//--------------------------------------------------------------
/**
 * @brief   全員のライト演出をOFFする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_DancerLightEffectOff(DANCE_PROC_WORK *dpw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		IMC_Player_SetColor(dpw->sys.imcwork[i].imc_ptr, IMC_LIGHT_COLOR_NORMAL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   全員のライト演出をONする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_DancerLightEffectAllOn(DANCE_PROC_WORK *dpw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		IMC_Player_SetColor(dpw->sys.imcwork[i].imc_ptr, IMC_LIGHT_COLOR_BLACK);
	}
}

//--------------------------------------------------------------
/**
 * @brief   得点合計順にライトをつける
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DT_DancerLightRankingSet(DANCE_PROC_WORK *dpw)
{
	int i, j, t;
	s16 a[BREEDER_MAX];
	u8 b[BREEDER_MAX];
	u8 evy[BREEDER_MAX];
	
	//ソート用にテンポラリ領域にAP値とブリーダー番号を入れる
	for(i = 0; i < BREEDER_MAX; i++){
		a[i] = dpw->d_game.dance_point[i];
		b[i] = i;
	}
	
	//稼いだポイント順にソート実行
	for(i = 0; i < BREEDER_MAX - 1; i++){
		for(j = BREEDER_MAX - 1; j > i; j--){
			if(a[j-1] < a[j]){
				//得点入れ替え
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
				//ブリーダー番号入れかえ
				t = b[j];
				b[j] = b[j-1];
				b[j-1] = t;
			}
		}
	}

	//フェードレベル
	evy[0] = RankingFadeEvy[0];
	for(i = 1; i < BREEDER_MAX; i++){
		evy[i] = RankingFadeEvy[i];
		if(a[i] == a[i - 1]){	//前のブリーダーと得点が同じならフェードレベルも同じにする
			evy[i] = evy[i - 1];
		}
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		OS_TPrintf("ブリーダー%d＝得点：%d, evy = %d\n", b[i], a[i], evy[i]);
		DT_DancerLightFadeReq(dpw, b[i], IMC_LIGHT_COLOR_NORMAL, IMC_LIGHT_COLOR_BLACK,
			evy[i], FADE_RANKING_FRAME, NULL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ライトのフェードタスクを生成する
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   start_color		フェード開始カラー
 * @param   next_color		フェード終了カラー
 * @param   end_evy			EVY終了値
 * @param   frame			何フレームで終了させるか
 * @param   end_flag		エフェクト終了後、このワークにTRUEをセットします(NULLなら何もしない)
 */
//--------------------------------------------------------------
void DT_DancerLightFadeReq(DANCE_PROC_WORK *dpw, int breeder_no, 
	GXRgb start_color, GXRgb next_color, int end_evy, int frame, u8 *end_flag)
{
	LIGHT_FADE_WORK *lf;
	
	lf = sys_AllocMemory(HEAPID_DANCE, sizeof(LIGHT_FADE_WORK));
	MI_CpuClear8(lf, sizeof(LIGHT_FADE_WORK));
	
	lf->imc_ptr = dpw->sys.imcwork[breeder_no].imc_ptr;
	lf->start_color = start_color;
	lf->next_color = next_color;
	lf->end_evy = end_evy;
	lf->add_evy = (end_evy << 8) / frame;
	lf->end_flag = end_flag;
	if(end_flag != NULL){
		*end_flag = FALSE;
	}
	
	IMC_Player_SetColor(lf->imc_ptr, start_color);
	
	TCB_Add(DancerLightFadeMain, lf, TCBPRI_DANCE_EFFECT_BASE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   ライトのフェードメインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		ライトフェードワークへのポインタ
 */
//--------------------------------------------------------------
static void DancerLightFadeMain(TCB_PTR tcb, void *work)
{
	LIGHT_FADE_WORK *lf = work;
	u16 dest_color;
	int set_evy;
	
	lf->now_evy += lf->add_evy;
	set_evy = lf->now_evy >> 8;
	if(set_evy > lf->end_evy){
		set_evy = lf->end_evy;
	}
	
	SoftFade(&lf->start_color, &dest_color, 1, set_evy, lf->next_color);
	
	IMC_Player_SetColor(lf->imc_ptr, dest_color);
	
	if(set_evy >= lf->end_evy){
		if(lf->end_flag != NULL){
			*(lf->end_flag) = TRUE;
		}
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ジャンプしていいポケモンかチェック
 *
 * @param   monsno		ポケモン番号
 *
 * @retval  TRUE:ジャンプOK　　FALSE:ジャンプ禁止
 */
//--------------------------------------------------------------
BOOL DanceJump_PokeCheck(u32 monsno)
{
	switch(monsno){
	case MONSNO_DHIGUDA:
	case MONSNO_DAGUTORIO:
		return FALSE;
	}
	return TRUE;
}

