//==============================================================================================
/**
 * @file	poke_test.c
 * @brief	ポケモングラフィックチェック
 * @author	sogabe
 * @date	2005.11.08
 */
//==============================================================================================

#ifdef PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/font_arc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/softsprite.h"
#include "poke_test.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "battle/graphic/batt_bg_def.h"
#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/fight.h"
#include "poketool/monsno.h"
#include "poketool/poke_tool.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/window.h"

#include "pokeanime/p_anm_sys.h"

#include "system/main.h"
#include "demo/title.h"
#include "msgdata/msg_poke_test.h"
#include "msgdata/msg_poke_anime.h"

#include "poketool/pokegra/pokegrano.dat"

extern	BOOL	PMSVLD_Load(u32 src, void * dst, u32 len);
extern	BOOL	PMSVLD_Save(u32 src, void * dst, u32 len);

#define		SAVE_BANK	(30)
#define		HEIGHT_MAX	(32)
#define		HEIGHT_MIN	(-32)
#define		SHADOW_MAX	(2)

//#define		GO_USE		//有効にするとichinose仕様

enum{
	SIDE_MAIN=0,
	SIDE_SUB,
};

enum{
	NUM_CALC_NONE=0,
	NUM_CALC_MOVE,
	NUM_CALC_CHANGE,
	NUM_CALC_END,
};

enum{
	MODE_NORMAL=0,
	MODE_ACTIVE,
	MODE_LOOP,
	MODE_STOP,
	MODE_DEFAULT_PARAM,
	MODE_DEFAULT_WAZA,
};

enum{
	VOICE_ON=0,
	VOICE_OFF,
};

//==============================================================================================
//
//	構造体
//
//==============================================================================================

#define	PGT_POKE_MAX	(600)					//ポケモンアニメーションデータのMAX
#define	PGT_END_KEY		(PAD_BUTTON_L|PAD_BUTTON_R|PAD_BUTTON_SELECT)

enum{
	SEQ_POKEMON_CHECK_INIT=0,
	SEQ_POKEMON_CHECK,
	SEQ_POKEMON_CHECK_EDIT,
	SEQ_POKEMON_ANIME,
	SEQ_POKEMON_ANIME_EDIT,
	SEQ_LOAD,
	SEQ_SAVE,
	SEQ_POKEMON_ANIME_ACT,
	SEQ_POKEMON_ANIME_ACT_B,
	SEQ_POKEMON_ANIME_ACT_F,
};

enum{
	CUR_PUT=0,
	CUR_DEL
};

typedef struct{
	u8	patno;
	u8	wait;
}PRG_ANIME;

typedef struct{
	u8					prg_anm_f;				//プログラムアニメナンバー（正面）
	u8					prg_anm_f_wait;
	PRG_ANIME			prg_anm_b[3];			//プログラムアニメナンバー（背面）
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];	//パターンアニメデータ
}POKE_ANM_DATA;

typedef struct{
	BOOL end_flag;
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win_m;
	GF_BGL_BMPWIN		*win_s;
	SOFT_SPRITE_MANAGER	*ssm;
	SOFT_SPRITE			*ss[2];
	MSGDATA_MANAGER		*man_msg;
	MSGDATA_MANAGER		*man_pam;
	MSGDATA_MANAGER		*man_poke;
	STRBUF				*msg_buf;
	POKE_ANM_SYS_PTR	pasp;
	int					seq_no;
	int					seq_no_temp;
	int					sub_seq_no;
	int					mons_no;
	int					sex;
	int					col;
	int					anm_pat;
	int					form_no;
	int					pos;
	int					yes_no_pos;
	int					put_req;
	int					main_pos;
	int					cur_pos_keta;
	int					shadow_flag;
	int					bg_flag;
	int					col_flag;
	int					bg_r;
	int					bg_g;
	int					bg_b;
	//ここ以下は、セーブしているので、位置の変更は厳禁！
	POKE_ANM_DATA		pad[PGT_POKE_MAX];
	s8					height[PGT_POKE_MAX];
	u8					shadow_size[PGT_POKE_MAX];
	s8					shadow_ofx[PGT_POKE_MAX];
}POKE_GRA_TEST;

//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================

static	void	PokeGraInit(POKE_GRA_TEST *pgt);
static	void	PokeGraTestBGCreate(POKE_GRA_TEST *pgt,GF_BGL_INI *bgl);
static	void	PokeTestMainScreenCreate(POKE_GRA_TEST *pgt);
static	void	PokeGraTestDebugPrint(POKE_GRA_TEST *pgt,int mode);
static	void	PokeGraTestVBlank(void *work);
static	void	Init3DStuff_(void);
static	u8		PokeGraTestSexGet(u16 monsno);
static	void	PokeGraTestMSG_Print(POKE_GRA_TEST *pgt);
static	void	PokeGraTestSubScreenMake(POKE_GRA_TEST *pgt);
static	void	PokeGraTestSubScreenAnmFDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col);
static	void	PokeGraTestSubScreenAnmFWaitDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col);
static	void	PokeGraTestSubScreenAnmBDataPut(POKE_GRA_TEST *pgt,int num,GF_PRINTCOLOR col);
static	void	PokeGraTestSubScreenAnmBWaitDataPut(POKE_GRA_TEST *pgt,int num,GF_PRINTCOLOR col);
static	void	PokeGraTestSubScreenPatDataPut(POKE_GRA_TEST *pgt,int pos,GF_PRINTCOLOR col);
static	void	PokeGraTestSubScreenWaitDataPut(POKE_GRA_TEST *pgt,int pos,GF_PRINTCOLOR col);
static	void	CursorMove(POKE_GRA_TEST *pgt,int side,int pos,int mode);
static	void	YesNoCursorMove(POKE_GRA_TEST *pgt,int pos,int mode);
static	BOOL	PokeNumAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeSexAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeColorAct(POKE_GRA_TEST *pgt);
static	BOOL	PokePatAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeFormAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeHeightAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeOfxAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeShadowAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeBGColorRAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeBGColorGAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeBGColorBAct(POKE_GRA_TEST *pgt);
static	BOOL	AnmFrontAct(POKE_GRA_TEST *pgt);
static	BOOL	AnmFrontWaitAct(POKE_GRA_TEST *pgt);
static	BOOL	AnmBackAct(POKE_GRA_TEST *pgt);
static	BOOL	AnmBackWaitAct(POKE_GRA_TEST *pgt);
static	BOOL	PatDataAct(POKE_GRA_TEST *pgt);
static	BOOL	WaitDataAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeGraTestLoadAct(POKE_GRA_TEST *pgt);
static	BOOL	PokeGraTestSaveAct(POKE_GRA_TEST *pgt);
static	void	PokeGraTestYesNoPut(POKE_GRA_TEST *pgt);

static	void	PokeTestPokeNumDataPut(POKE_GRA_TEST *pgt,int mode);
static	void	PokeTestPokeSexDataPut(POKE_GRA_TEST *pgt);
static	void	PokeTestPokeColorDataPut(POKE_GRA_TEST *pgt);
static	void	PokeTestPokePatDataPut(POKE_GRA_TEST *pgt);
static	void	PokeTestPokeFormDataPut(POKE_GRA_TEST *pgt,int mode);
static	void	PokeTestPokeHeightDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col);
static	void	PokeTestPokeOfxDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col);
static	void	PokeTestPokeShadowDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col);
static	void	PokeTestPokeBGColorRDataPut(POKE_GRA_TEST *pgt,int mode);
static	void	PokeTestPokeBGColorGDataPut(POKE_GRA_TEST *pgt,int mode);
static	void	PokeTestPokeBGColorBDataPut(POKE_GRA_TEST *pgt,int mode);
static	void	PokeTestBGColorSet(POKE_GRA_TEST *pgt);

static	void	PokeTestNumPut(POKE_GRA_TEST *pgt,int x,int y,int param,int keta,int pos,int mode);
static	int		PokeTestNumCalc(POKE_GRA_TEST *pgt,int *param,int keta,int min,int max,int mode);
static	int		PokeTestPokeFormMaxGet(POKE_GRA_TEST *pgt);

static	void	PokeGraTestShadowSet(POKE_GRA_TEST *pgt,int height);

//==================================================================================================
//
//	データ
//
//==================================================================================================

static	const	u16	pal[]={
		GX_RGB(31,31,31),				//0:白
		GX_RGB(13,13,13),				//1:濃い灰
		GX_RGB(24,24,24),				//2:薄い灰
		GX_RGB(15,31,15),				//3:うすみどり
		GX_RGB(31,15,15),				//4:うすあか
		GX_RGB(19,19,19),				//5:灰
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB(31,31,31),				//15:白
};

//ポケモンチェック
enum{
	POKE_NUM=0,
	POKE_SEX,
	POKE_COLOR,
	POKE_PAT,
	POKE_FORM,
	POKE_HEIGHT,
	POKE_OFX,
	POKE_SHADOW,
	POKE_BG_COLOR_R,
	POKE_BG_COLOR_G,
	POKE_BG_COLOR_B
};

//アニメーション設定
enum{
	MENU_ANM_FRONT=0,
	MENU_ANM_BACK1,
	MENU_ANM_BACK2,
	MENU_ANM_BACK3,
	MENU_ANM_FRONT_WAIT,
	MENU_ANM_BACK1_WAIT,
	MENU_ANM_BACK2_WAIT,
	MENU_ANM_BACK3_WAIT,
	MENU_PAT_01,
	MENU_PAT_02,
	MENU_PAT_03,
	MENU_PAT_04,
	MENU_PAT_05,
	MENU_PAT_06,
	MENU_PAT_07,
	MENU_PAT_08,
	MENU_PAT_09,
	MENU_PAT_10,
	MENU_WAIT_01,
	MENU_WAIT_02,
	MENU_WAIT_03,
	MENU_WAIT_04,
	MENU_WAIT_05,
	MENU_WAIT_06,
	MENU_WAIT_07,
	MENU_WAIT_08,
	MENU_WAIT_09,
	MENU_WAIT_10,
};

typedef BOOL (*PT_FUNC)(POKE_GRA_TEST *);

typedef struct
{
	u8		cursor_pos_x;	//カーソルX位置
	u8		cursor_pos_y;	//カーソルY位置
	u8		move_up;		//上キーを押したときの移動先
	u8		move_down;		//下キーを押したときの移動先
	u8		move_left;		//左キーを押したときの移動先
	u8		move_right;		//右キーを押したときの移動先
	PT_FUNC	a_button_act;	//Aボタンを押したときのアクション
}MENU_LIST_PARAM;

#define	MONS_NUM_X	(0)		//モンスターナンバー表示X位置
#define	MONS_NUM_Y	(8)		//モンスターナンバー表示Y位置
#define	MONS_NAME_X	(32)	//モンスター名表示X位置
#define	MONS_NAME_Y	(8)		//モンスター名表示Y位置
#define	MONS_SEX_X	(96)	//モンスター性別表示X位置
#define	MONS_SEX_Y	(8)		//モンスター性別表示Y位置
#define	MONS_COL_X	(128)	//モンスターカラー表示X位置
#define	MONS_COL_Y	(8)		//モンスターカラー表示Y位置
#define	MONS_PAT_X	(188)	//モンスターアニメパターンナンバー表示X位置
#define	MONS_PAT_Y	(8)		//モンスターアニメパターンナンバー表示Y位置

#define	POKE_NUM_DATA_X			(12)
#define	POKE_NUM_DATA_Y			(0)
#define	POKE_NUM_X				(POKE_NUM_DATA_X-12)
#define	POKE_NUM_Y				(0)
#define	POKE_SEX_DATA_X			(108)
#define	POKE_SEX_DATA_Y			(0)
#define	POKE_SEX_X				(POKE_SEX_DATA_X-12)
#define	POKE_SEX_Y				(0)
#define	POKE_COLOR_DATA_X		(140)
#define	POKE_COLOR_DATA_Y		(0)
#define	POKE_COLOR_X			(POKE_COLOR_DATA_X-12)
#define	POKE_COLOR_Y			(0)
#define	POKE_PAT_DATA_X			(200)
#define	POKE_PAT_DATA_Y			(0)
#define	POKE_PAT_X				(POKE_PAT_DATA_X-12)
#define	POKE_PAT_Y				(0)
#define	POKE_FORM_DATA_X		(12)
#define	POKE_FORM_DATA_Y		(16)
#define	POKE_FORM_X				(POKE_FORM_DATA_X-12)
#define	POKE_FORM_Y				(16)
#define	POKE_HEIGHT_DATA_X		(60)
#define	POKE_HEIGHT_DATA_Y		(16)
#define	POKE_HEIGHT_X			(POKE_HEIGHT_DATA_X-12)
#define	POKE_HEIGHT_Y			(16)
#define	POKE_OFX_DATA_X			(88)
#define	POKE_OFX_DATA_Y			(16)
#define	POKE_OFX_X				(POKE_OFX_DATA_X-12)
#define	POKE_OFX_Y				(16)
#define	POKE_SHADOW_DATA_X		(124)
#define	POKE_SHADOW_DATA_Y		(16)
#define	POKE_SHADOW_X			(POKE_SHADOW_DATA_X-12)
#define	POKE_SHADOW_Y			(16)
#define	POKE_BG_COLOR_R_DATA_X	(144)
#define	POKE_BG_COLOR_R_DATA_Y	(16)
#define	POKE_BG_COLOR_R_X		(POKE_BG_COLOR_R_DATA_X-12)
#define	POKE_BG_COLOR_R_Y		(16)
#define	POKE_BG_COLOR_G_DATA_X	(172)
#define	POKE_BG_COLOR_G_DATA_Y	(16)
#define	POKE_BG_COLOR_G_X		(POKE_BG_COLOR_G_DATA_X-12)
#define	POKE_BG_COLOR_G_Y		(16)
#define	POKE_BG_COLOR_B_DATA_X	(200)
#define	POKE_BG_COLOR_B_DATA_Y	(16)
#define	POKE_BG_COLOR_B_X		(POKE_BG_COLOR_B_DATA_X-12)
#define	POKE_BG_COLOR_B_Y		(16)

static	const	MENU_LIST_PARAM	mlp_m[]={
	//POKE_NUM
	{
		POKE_NUM_X,
		POKE_NUM_Y,
		POKE_FORM,
		POKE_FORM,
		POKE_PAT,
		POKE_SEX,
		PokeNumAct,
	},
	//POKE_SEX
	{
		POKE_SEX_X,
		POKE_SEX_Y,
		POKE_OFX,
		POKE_OFX,
		POKE_NUM,
		POKE_COLOR,
		PokeSexAct,
	},
	//POKE_COLOR
	{
		POKE_COLOR_X,
		POKE_COLOR_Y,
		POKE_SHADOW,
		POKE_SHADOW,
		POKE_SEX,
		POKE_PAT,
		PokeColorAct,
	},
	//POKE_PAT
	{
		POKE_PAT_X,
		POKE_PAT_Y,
		POKE_BG_COLOR_R,
		POKE_BG_COLOR_R,
		POKE_COLOR,
		POKE_NUM,
		PokePatAct,
	},
	//POKE_FORM
	{
		POKE_FORM_X,
		POKE_FORM_Y,
		POKE_NUM,
		POKE_NUM,
		POKE_BG_COLOR_B,
		POKE_HEIGHT,
		PokeFormAct,
	},
	//POKE_HEIGHT
	{
		POKE_HEIGHT_X,
		POKE_HEIGHT_Y,
		POKE_SEX,
		POKE_SEX,
		POKE_FORM,
		POKE_OFX,
		PokeHeightAct,
	},
	//POKE_OFX
	{
		POKE_OFX_X,
		POKE_OFX_Y,
		POKE_SEX,
		POKE_SEX,
		POKE_HEIGHT,
		POKE_SHADOW,
		PokeOfxAct,
	},
	//POKE_SHADOW
	{
		POKE_SHADOW_X,
		POKE_SHADOW_Y,
		POKE_COLOR,
		POKE_COLOR,
		POKE_OFX,
		POKE_BG_COLOR_R,
		PokeShadowAct,
	},
	//POKE_BG_COLOR_R
	{
		POKE_BG_COLOR_R_X,
		POKE_BG_COLOR_R_Y,
		POKE_PAT,
		POKE_PAT,
		POKE_SHADOW,
		POKE_BG_COLOR_G,
		PokeBGColorRAct,
	},
	//POKE_BG_COLOR_G
	{
		POKE_BG_COLOR_G_X,
		POKE_BG_COLOR_G_Y,
		POKE_PAT,
		POKE_PAT,
		POKE_BG_COLOR_R,
		POKE_BG_COLOR_B,
		PokeBGColorGAct,
	},
	//POKE_BG_COLOR_B
	{
		POKE_BG_COLOR_B_X,
		POKE_BG_COLOR_B_Y,
		POKE_PAT,
		POKE_PAT,
		POKE_BG_COLOR_G,
		POKE_FORM,
		PokeBGColorBAct,
	},
};

#define	CUR_POS_X1		(4)
#define	CUR_POS_X2		(48)
#define	CUR_POS_X3		(96)
#define	CUR_POS_X4		(192)

#define	CUR_POS_Y1		(0)
#define	CUR_POS_Y2		(52)
#define	CUR_POS_OFS_Y1	(13)
#define	CUR_POS_OFS_Y2	(14)

#define	NO_MOVE			(0xff)

static	const	MENU_LIST_PARAM	mlp[]={
	//MENU_ANM_FRONT
	{
		CUR_POS_X1,
		CUR_POS_Y1+CUR_POS_OFS_Y1*0,
		MENU_PAT_10,
		MENU_ANM_BACK1,
		MENU_ANM_FRONT_WAIT,
		MENU_ANM_FRONT_WAIT,
		AnmFrontAct,
	},
	//MENU_ANM_BACK1
	{
		CUR_POS_X1,
		CUR_POS_Y1+CUR_POS_OFS_Y1*1,
		MENU_ANM_FRONT,
		MENU_ANM_BACK2,
		MENU_ANM_BACK1_WAIT,
		MENU_ANM_BACK1_WAIT,
		AnmBackAct,
	},
	//MENU_ANM_BACK2
	{
		CUR_POS_X1,
		CUR_POS_Y1+CUR_POS_OFS_Y1*2,
		MENU_ANM_BACK1,
		MENU_ANM_BACK3,
		MENU_ANM_BACK2_WAIT,
		MENU_ANM_BACK2_WAIT,
		AnmBackAct,
	},
	//MENU_ANM_BACK3
	{
		CUR_POS_X1,
		CUR_POS_Y1+CUR_POS_OFS_Y1*3,
		MENU_ANM_BACK2,
		MENU_PAT_01,
		MENU_ANM_BACK3_WAIT,
		MENU_ANM_BACK3_WAIT,
		AnmBackAct,
	},
	//MENU_ANM_FRONT_WAIT
	{
		CUR_POS_X4,
		CUR_POS_Y1+CUR_POS_OFS_Y1*0,
		MENU_WAIT_10,
		MENU_ANM_BACK1_WAIT,
		MENU_ANM_FRONT,
		MENU_ANM_FRONT,
		AnmFrontWaitAct,
	},
	//MENU_ANM_BACK1_WAIT
	{
		CUR_POS_X4,
		CUR_POS_Y1+CUR_POS_OFS_Y1*1,
		MENU_ANM_FRONT_WAIT,
		MENU_ANM_BACK2_WAIT,
		MENU_ANM_BACK1,
		MENU_ANM_BACK1,
		AnmBackWaitAct,
	},
	//MENU_ANM_BACK2_WAIT
	{
		CUR_POS_X4,
		CUR_POS_Y1+CUR_POS_OFS_Y1*2,
		MENU_ANM_BACK1_WAIT,
		MENU_ANM_BACK3_WAIT,
		MENU_ANM_BACK2,
		MENU_ANM_BACK2,
		AnmBackWaitAct,
	},
	//MENU_ANM_BACK3_WAIT
	{
		CUR_POS_X4,
		CUR_POS_Y1+CUR_POS_OFS_Y1*3,
		MENU_ANM_BACK2_WAIT,
		MENU_WAIT_01,
		MENU_ANM_BACK3,
		MENU_ANM_BACK3,
		AnmBackWaitAct,
	},
	//MENU_PAT_01
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*0,
		MENU_ANM_BACK3,
		MENU_PAT_02,
		MENU_WAIT_01,
		MENU_WAIT_01,
		PatDataAct,
	},
	//MENU_PAT_02
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*1,
		MENU_PAT_01,
		MENU_PAT_03,
		MENU_WAIT_02,
		MENU_WAIT_02,
		PatDataAct,
	},
	//MENU_PAT_03
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*2,
		MENU_PAT_02,
		MENU_PAT_04,
		MENU_WAIT_03,
		MENU_WAIT_03,
		PatDataAct,
	},
	//MENU_PAT_04
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*3,
		MENU_PAT_03,
		MENU_PAT_05,
		MENU_WAIT_04,
		MENU_WAIT_04,
		PatDataAct,
	},
	//MENU_PAT_05
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*4,
		MENU_PAT_04,
		MENU_PAT_06,
		MENU_WAIT_05,
		MENU_WAIT_05,
		PatDataAct,
	},
	//MENU_PAT_06
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*5,
		MENU_PAT_05,
		MENU_PAT_07,
		MENU_WAIT_06,
		MENU_WAIT_06,
		PatDataAct,
	},
	//MENU_PAT_07
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*6,
		MENU_PAT_06,
		MENU_PAT_08,
		MENU_WAIT_07,
		MENU_WAIT_07,
		PatDataAct,
	},
	//MENU_PAT_08
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*7,
		MENU_PAT_07,
		MENU_PAT_09,
		MENU_WAIT_08,
		MENU_WAIT_08,
		PatDataAct,
	},
	//MENU_PAT_09
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*8,
		MENU_PAT_08,
		MENU_PAT_10,
		MENU_WAIT_09,
		MENU_WAIT_09,
		PatDataAct,
	},
	//MENU_PAT_10
	{
		CUR_POS_X2,
		CUR_POS_Y2+CUR_POS_OFS_Y2*9,
		MENU_PAT_09,
		MENU_ANM_FRONT,
		MENU_WAIT_10,
		MENU_WAIT_10,
		PatDataAct,
	},
	//MENU_WAIT_01
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*0,
		MENU_ANM_BACK3_WAIT,
		MENU_WAIT_02,
		MENU_PAT_01,
		MENU_PAT_01,
		WaitDataAct,
	},
	//MENU_WAIT_02
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*1,
		MENU_WAIT_01,
		MENU_WAIT_03,
		MENU_PAT_02,
		MENU_PAT_02,
		WaitDataAct,
	},
	//MENU_WAIT_03
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*2,
		MENU_WAIT_02,
		MENU_WAIT_04,
		MENU_PAT_03,
		MENU_PAT_03,
		WaitDataAct,
	},
	//MENU_WAIT_04
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*3,
		MENU_WAIT_03,
		MENU_WAIT_05,
		MENU_PAT_04,
		MENU_PAT_04,
		WaitDataAct,
	},
	//MENU_WAIT_05
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*4,
		MENU_WAIT_04,
		MENU_WAIT_06,
		MENU_PAT_05,
		MENU_PAT_05,
		WaitDataAct,
	},
	//MENU_WAIT_06
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*5,
		MENU_WAIT_05,
		MENU_WAIT_07,
		MENU_PAT_06,
		MENU_PAT_06,
		WaitDataAct,
	},
	//MENU_WAIT_07
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*6,
		MENU_WAIT_06,
		MENU_WAIT_08,
		MENU_PAT_07,
		MENU_PAT_07,
		WaitDataAct,
	},
	//MENU_WAIT_08
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*7,
		MENU_WAIT_07,
		MENU_WAIT_09,
		MENU_PAT_08,
		MENU_PAT_08,
		WaitDataAct,
	},
	//MENU_WAIT_09
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*8,
		MENU_WAIT_08,
		MENU_WAIT_10,
		MENU_PAT_09,
		MENU_PAT_09,
		WaitDataAct,
	},
	//MENU_WAIT_10
	{
		CUR_POS_X3,
		CUR_POS_Y2+CUR_POS_OFS_Y2*9,
		MENU_WAIT_09,
		MENU_ANM_FRONT_WAIT,
		MENU_PAT_10,
		MENU_PAT_10,
		WaitDataAct,
	},
};

#define	NORMAL_LETTER	(1)
#define	NORMAL_SHADOW	(2)
#define	NORMAL_GROUND	(15)

#define	ACTIVE_LETTER	(3)
#define	ACTIVE_SHADOW	(2)
#define	ACTIVE_GROUND	(15)

#define	CURSOR_LETTER	(4)
#define	CURSOR_SHADOW	(2)
#define	CURSOR_GROUND	(15)

#define	NONE_LETTER		(5)
#define	NONE_SHADOW		(2)
#define	NONE_GROUND		(15)

#define	COL_NORMAL		(GF_PRINTCOLOR_MAKE(NORMAL_LETTER,NORMAL_SHADOW,NORMAL_GROUND))
#define	COL_ACTIVE		(GF_PRINTCOLOR_MAKE(ACTIVE_LETTER,ACTIVE_SHADOW,ACTIVE_GROUND))
#define	COL_CURSOR		(GF_PRINTCOLOR_MAKE(CURSOR_LETTER,CURSOR_SHADOW,CURSOR_GROUND))
#define	COL_NONE		(GF_PRINTCOLOR_MAKE(NONE_LETTER,NONE_SHADOW,NONE_GROUND))

//==================================================================================================
//
//	関数
//
//==================================================================================================

static	void	PokeGraInit(POKE_GRA_TEST *pgt)
{
	int				i,j;

	simple_3DBGInit(HEAPID_BATTLE);
	sys_HBlankIntrStop();

	MI_CpuClearFast(pgt,sizeof(POKE_GRA_TEST));

	pgt->man_msg=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_poke_test_dat,HEAPID_BATTLE);
	pgt->man_pam=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_poke_anime_dat,HEAPID_BATTLE);
	pgt->man_poke=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_monsname_dat,HEAPID_BATTLE);
	pgt->msg_buf=STRBUF_Create(0x100,HEAPID_BATTLE);

	pgt->put_req=0;
	pgt->anm_pat=0;
	pgt->form_no=0;

	pgt->end_flag = FALSE;
	pgt->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	pgt->win_m=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,1);
	pgt->win_s=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,1);

	PokeGraTestBGCreate(pgt,pgt->bgl);

	pgt->ssm=SoftSpriteInit(HEAPID_BATTLE);
	SoftSpritePaletteTransParamSet(pgt->ssm,0,SOFT_SPRITE_COL_SIZE);	//影の分も転送するようにサイズを変更
	pgt->pasp=PokeAnm_AllocMemory(HEAPID_BATTLE,2,0);

	pgt->mons_no=1;
	pgt->sex=PokeGraTestSexGet(pgt->mons_no);
	if(pgt->sex==3){
		pgt->sex=0;
	}
	pgt->main_pos=0;
	pgt->pos=0;
	pgt->seq_no=SEQ_POKEMON_CHECK_INIT;
	pgt->seq_no_temp=0;
	pgt->sub_seq_no=0;
	pgt->bg_flag=0;
	pgt->col_flag=0;
	pgt->bg_r=0;
	pgt->bg_g=0;
	pgt->bg_b=0;

	GF_BGL_BmpWinAdd(pgt->bgl,pgt->win_m,GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(pgt->win_m,0xff);
	BmpTalkWinWrite(pgt->win_m,WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);
	GF_BGL_BmpWinAdd(pgt->bgl,pgt->win_s,GF_BGL_FRAME1_S,0x00,0x00,32,24,0x00,0x01);

	for(i=0;i<PGT_POKE_MAX;i++){
		pgt->pad[i].prg_anm_f=0;
		pgt->pad[i].prg_anm_f_wait=0;
		for(j=0;j<3;j++){
			pgt->pad[i].prg_anm_b[j].patno=0;
			pgt->pad[i].prg_anm_b[j].wait=0;
		}
		for(j=0;j<SS_ANM_SEQ_MAX;j++){
			pgt->pad[i].ssanm[j].patno=-1;
			pgt->pad[i].ssanm[j].wait=0;
		}
		pgt->height[i]=0;
		pgt->shadow_size[i]=1;
		pgt->shadow_ofx[i]=0;
	}

	pgt->height[0]=0x55;

//	PokeGraTestMSG_Print(pgt);

	PokeTestMainScreenCreate(pgt);
	
	CursorMove(pgt,SIDE_MAIN,pgt->main_pos,CUR_PUT);

	PokeGraTestSubScreenMake(pgt);
	Snd_Stop();

	OS_TPrintf("save_ram:0x%08x size:0x%08x\n",&pgt->pad[0],sizeof(POKE_ANM_DATA)*PGT_POKE_MAX);
	OS_TPrintf("height:0x%08x size:0x%08x\n",&pgt->height[0],PGT_POKE_MAX);
	OS_TPrintf("shadow:0x%08x size:0x%08x\n",&pgt->shadow_size[0],PGT_POKE_MAX);
	OS_TPrintf("shadow_ofx:0x%08x size:0x%08x\n",&pgt->shadow_ofx[0],PGT_POKE_MAX);
}

static	void	PokeTestMainScreenCreate(POKE_GRA_TEST *pgt)
{
	PokeTestPokeNumDataPut(pgt,MODE_NORMAL);
	PokeTestPokeSexDataPut(pgt);
	PokeTestPokeColorDataPut(pgt);
	PokeTestPokePatDataPut(pgt);
	PokeTestPokeFormDataPut(pgt,MODE_NORMAL);
	PokeTestPokeHeightDataPut(pgt,COL_NORMAL);
	PokeTestPokeOfxDataPut(pgt,COL_NORMAL);
	PokeTestPokeShadowDataPut(pgt,COL_NORMAL);
	PokeTestPokeBGColorRDataPut(pgt,MODE_NORMAL);
	PokeTestPokeBGColorGDataPut(pgt,MODE_NORMAL);
	PokeTestPokeBGColorBDataPut(pgt,MODE_NORMAL);
}

//============================================================================================
/**
 *	戦闘背景画面初期化＆画面生成
 */
//============================================================================================
static	void	PokeGraTestBGCreate(POKE_GRA_TEST *pgt,GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				1, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				3, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(0x01);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//サブ画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[]={
			///<FRAME1_S
			{
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
				0,0,0,FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_S, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_S );
	}

	//背景グラフィックデータロード
	{
		TalkWinGraphicNullSet(bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,0,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		ArcUtil_PalSet(ARC_BATT_BG,BATT_BG00_D_NCLR,PALTYPE_MAIN_BG,0,0,HEAPID_BATTLE);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		ArcUtil_PalSet(ARC_WINFRAME,TalkWinPalArcGet(0),PALTYPE_MAIN_BG,TALK_WIN_PAL_NO*0x20,0x20,HEAPID_BATTLE);
//		ArcUtil_PalSet(ARC_FONT,NARC_font_talk_ncrl,PALTYPE_MAIN_BG,TALK_MSG_PAL_NO*0x20,0x20,HEAPID_BATTLE);
//
		DC_FlushRange((void *)&pal,sizeof(pal));
		GX_LoadBGPltt((void *)&pal,TALK_MSG_PAL_NO*0x20,sizeof(pal));

		DC_FlushRange((void *)&pal,sizeof(pal));
		GXS_LoadBGPltt((void *)&pal,0,sizeof(pal));
	}

	GF_Disp_DispOn();

	sys_VBlankFuncChange(PokeGraTestVBlank,pgt);
}

//============================================================================================
/**
 *	メインループタスク
 */
//============================================================================================
static	void	PokeGraTestMain(POKE_GRA_TEST * pgt)
{
	u8	sex;
	int	move=NO_MOVE;

	if(pgt->put_req){
		pgt->put_req=0;
		GF_BGL_BmpWinOn(pgt->win_m);
		GF_BGL_BmpWinOn(pgt->win_s);
	}

	if((sys.trg == PAD_BUTTON_Y)&&(pgt->seq_no<SEQ_LOAD)&&(pgt->seq_no!=SEQ_POKEMON_CHECK_EDIT)){
#ifdef GO_USE
		Snd_Stop();
#else
		pgt->seq_no_temp=pgt->seq_no;
		pgt->seq_no=SEQ_LOAD;
		pgt->sub_seq_no=0;
		pgt->yes_no_pos=1;
#endif
	}

	if((sys.trg == PAD_BUTTON_X)&&(pgt->seq_no<SEQ_LOAD)&&(pgt->seq_no!=SEQ_POKEMON_CHECK_EDIT)){
#ifdef GO_USE
		Snd_SceneSet(SND_SCENE_DUMMY);
		Snd_DataSetByScene( SND_SCENE_BATTLE, SEQ_FIGHT0101, 1 );	//バトル曲再生
#else
		pgt->seq_no_temp=pgt->seq_no;
		pgt->seq_no=SEQ_SAVE;
		pgt->sub_seq_no=0;
		pgt->yes_no_pos=1;
#endif
	}

	if((pgt->seq_no!=SEQ_POKEMON_ANIME)&&
	   (pgt->seq_no!=SEQ_POKEMON_ANIME_EDIT)){
		if(sys.trg == PAD_BUTTON_B){
			pgt->shadow_flag++;
			switch(pgt->shadow_flag%3){
			case 0:
				PokeTestPokeHeightDataPut(pgt,COL_NORMAL);
				PokeTestPokeOfxDataPut(pgt,COL_NORMAL);
				PokeTestPokeShadowDataPut(pgt,COL_NORMAL);
				break;
			case 1:
				SoftSpriteSSSystemFlagSet(pgt->ssm,SS_SYSTEM_FLAG_SHADOW_OFF);
				break;
			case 2:
				PokeTestPokeHeightDataPut(pgt,COL_NONE);
				PokeTestPokeOfxDataPut(pgt,COL_NONE);
				PokeTestPokeShadowDataPut(pgt,COL_NONE);
				SoftSpriteSSSystemFlagReset(pgt->ssm,SS_SYSTEM_FLAG_SHADOW_OFF);
				break;
			}
			PokeGraTestDebugPrint(pgt,VOICE_OFF);
		}
		if(sys.trg == PAD_BUTTON_L){
#ifdef GO_USE
			if((pgt->seq_no!=SEQ_POKEMON_ANIME)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT_B)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT_F)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_EDIT)){
				PokePrgAnmDataSet(pgt->pasp,pgt->ss[0],pgt->mons_no,PARA_BACK,0,PARA_HFLIP_OFF,0);
				Snd_PMVoicePlayEx(PV_NORMAL,pgt->mons_no,-117,127,HEAPID_BASE_APP);
				pgt->seq_no_temp=pgt->seq_no;
				pgt->seq_no=SEQ_POKEMON_ANIME_ACT_B;
			}
#else
			pgt->bg_flag++;
			switch(pgt->bg_flag&3){
			case 0:
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
				break;
			case 1:
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
				break;
			case 2:
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
				break;
			case 3:
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
				break;
			}
#endif
		}
		if(sys.trg == PAD_BUTTON_R){
#ifdef GO_USE
			if((pgt->seq_no!=SEQ_POKEMON_ANIME)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT_B)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT_F)&&
			   (pgt->seq_no!=SEQ_POKEMON_ANIME_EDIT)){
				{
					SOFT_SPRITE_ANIME	ssa[10];
	
					PokePrgAnmDataSet(pgt->pasp,pgt->ss[1],pgt->mons_no,PARA_FRONT,0,PARA_HFLIP_OFF,1);
					Snd_PMVoicePlayEx(PV_NORMAL,pgt->mons_no,117,127,HEAPID_BASE_APP);
	
					PokeAnmDataSet(&ssa[0],pgt->mons_no);
					SoftSpriteAnimeDataSet(pgt->ss[1],&ssa[0]);
					SoftSpriteAnimeSet(pgt->ss[1],NULL);
					SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_Y_REQ,0);
					SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_AFF_REQ,0);
				}
				pgt->seq_no_temp=pgt->seq_no;
				pgt->seq_no=SEQ_POKEMON_ANIME_ACT_F;
			}
#else
			pgt->col_flag^=1;
			PokeTestBGColorSet(pgt);
#endif
		}
	}
	if((pgt->seq_no!=SEQ_POKEMON_ANIME)&&
	   (pgt->seq_no!=SEQ_POKEMON_ANIME_ACT)&&
	   (pgt->seq_no!=SEQ_POKEMON_ANIME_EDIT)){
		if(sys.trg == PAD_BUTTON_START){
			{
				SOFT_SPRITE_ANIME	ssa[10];

				PokePrgAnmDataSet(pgt->pasp,pgt->ss[1],pgt->mons_no,PARA_FRONT,0,PARA_HFLIP_OFF,1);
				PokePrgAnmDataSet(pgt->pasp,pgt->ss[0],pgt->mons_no,PARA_BACK,0,PARA_HFLIP_OFF,0);
				Snd_PMVoicePlay(pgt->mons_no);

				PokeAnmDataSet(&ssa[0],pgt->mons_no);
				SoftSpriteAnimeDataSet(pgt->ss[1],&ssa[0]);
				SoftSpriteAnimeSet(pgt->ss[1],NULL);
				SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_Y_REQ,0);
				SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_AFF_REQ,0);
			}
			pgt->seq_no_temp=pgt->seq_no;
			pgt->seq_no=SEQ_POKEMON_ANIME_ACT;
		}
	}

	if(pgt->col_flag&1){
		PokeTestBGColorSet(pgt);
	}

	switch(pgt->seq_no){
	case SEQ_POKEMON_CHECK_INIT:
		{
			SOFT_SPRITE_ARC	ssa;
			int				height;

			PokeGraArcDataGet(&ssa,pgt->mons_no,pgt->sex,PARA_BACK,pgt->col,NULL,0x88888888);
			height=PokeHeightGet(pgt->mons_no,pgt->sex,PARA_BACK,NULL,NULL);
			pgt->ss[0]=SoftSpriteAdd(pgt->ssm,&ssa,APPEAR_X_TYPE_AA,APPEAR_Y_TYPE_AA+height,APPEAR_Z_TYPE_AA,
									 0,NULL,NULL);
			PokeGraArcDataGet(&ssa,pgt->mons_no,pgt->sex,PARA_FRONT,pgt->col,NULL,0x88888888);
			height=PokeHeightGet(pgt->mons_no,pgt->sex,PARA_FRONT,NULL,NULL);
			pgt->ss[1]=SoftSpriteAdd(pgt->ssm,&ssa,APPEAR_X_TYPE_BB,APPEAR_Y_TYPE_BB+height,APPEAR_Z_TYPE_BB,
									 1,NULL,NULL);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_REQ,1);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_SIZE,pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OX,pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OY,SHADOW_OFS-height);
		}
		pgt->seq_no=SEQ_POKEMON_CHECK;
		break;
	//ポケモンチェック
	case SEQ_POKEMON_CHECK:
		if(sys.trg & PAD_BUTTON_SELECT){
			pgt->pos=0;
			pgt->seq_no=SEQ_POKEMON_ANIME;
			CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_PUT);
			break;
		}
		if(sys.trg==PAD_KEY_UP){
			move=mlp_m[pgt->main_pos].move_up;
		}
		else if(sys.trg == PAD_KEY_DOWN){
			move=mlp_m[pgt->main_pos].move_down;
		}
		else if(sys.trg == PAD_KEY_LEFT){
			move=mlp_m[pgt->main_pos].move_left;
		}
		else if(sys.trg == PAD_KEY_RIGHT){
			move=mlp_m[pgt->main_pos].move_right;
		}
		if(sys.trg == PAD_BUTTON_A){
			if(mlp_m[pgt->main_pos].a_button_act!=NULL){
				pgt->sub_seq_no=0;
				pgt->seq_no=SEQ_POKEMON_CHECK_EDIT;
			}
		}
		if(move!=NO_MOVE){
			CursorMove(pgt,SIDE_MAIN,move,CUR_PUT);
		}
#if 0
		if(sys.repeat & PAD_KEY_LEFT){
			if(pgt->mons_no==1){
				pgt->mons_no=MONSNO_END;
			}
			else{
				pgt->mons_no--;
			}
		}
		else if(sys.repeat & PAD_KEY_RIGHT){
			if(pgt->mons_no==MONSNO_END){
				pgt->mons_no=1;
			}
			else{
				pgt->mons_no++;
			}
		}
		if((sys.repeat & PAD_KEY_UP)&&(pgt->height[PokeGraNoTable[pgt->mons_no]]<HEIGHT_MAX)){
			pgt->height[PokeGraNoTable[pgt->mons_no]]++;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_HEIGHT,pgt->height[PokeGraNoTable[pgt->mons_no]]);
		}
		if((sys.repeat & PAD_KEY_DOWN)&&(pgt->height[PokeGraNoTable[pgt->mons_no]]>HEIGHT_MIN)){
			pgt->height[PokeGraNoTable[pgt->mons_no]]--;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_HEIGHT,pgt->height[PokeGraNoTable[pgt->mons_no]]);
		}
		if(sys.repeat & PAD_BUTTON_L){
			if(pgt->mons_no-10<1){
				pgt->mons_no=MONSNO_END+(pgt->mons_no-10);
			}
			else{
				pgt->mons_no-=10;
			}
		}
		else if(sys.repeat & PAD_BUTTON_R){
			if(pgt->mons_no+10>MONSNO_END){
				pgt->mons_no=pgt->mons_no+10-MONSNO_END;
			}
			else{
				pgt->mons_no+=10;
			}
		}
		else if(sys.repeat & PAD_BUTTON_A){
			sex=PokeGraTestSexGet(pgt->mons_no);
			if(sex==3){
				pgt->sex^=1;
			}
		}
		else if(sys.repeat & PAD_BUTTON_B){
			pgt->col^=1;
		}
		if(sys.repeat){
			if((sys.repeat & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_BUTTON_A|PAD_BUTTON_B))==0){
				pgt->sex=PokeGraTestSexGet(pgt->mons_no);
				if(pgt->sex==3){
					pgt->sex=0;
				}
			}
			PokeGraTestDebugPrint(pgt);
			PokeGraTestSubScreenMake(pgt);
		}
#endif
		break;
	case SEQ_POKEMON_CHECK_EDIT:
		if(mlp_m[pgt->main_pos].a_button_act(pgt)==TRUE){
			pgt->seq_no=SEQ_POKEMON_CHECK;
		}
		break;
	//ポケモンアニメセット
	case SEQ_POKEMON_ANIME:
		if(sys.trg==PAD_KEY_UP){
			move=mlp[pgt->pos].move_up;
		}
		else if(sys.trg == PAD_KEY_DOWN){
			move=mlp[pgt->pos].move_down;
		}
		else if(sys.trg == PAD_KEY_LEFT){
			move=mlp[pgt->pos].move_left;
		}
		else if(sys.trg == PAD_KEY_RIGHT){
			move=mlp[pgt->pos].move_right;
		}
		if(sys.trg == PAD_BUTTON_SELECT){
			CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_DEL);
			pgt->seq_no=SEQ_POKEMON_CHECK;
		}
		if(sys.trg == PAD_BUTTON_START){
			{
				P_ANM_SETTING_PARAM	pas_p;
				int					num;

				if((pgt->pos==0)||(pgt->pos==4)||(pgt->pos>7)){
					pas_p.AnimeNo=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_f;
					pas_p.Wait=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_f_wait;
					pas_p.Reverse=0;
					num=1;
					SoftSpriteAnimeDataSet(pgt->ss[num],&pgt->pad[PokeGraNoTable[pgt->mons_no]].ssanm[0]);
					SoftSpriteAnimeSet(pgt->ss[num],NULL);
					SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_Y_REQ,0);
					SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_AFF_REQ,0);
				}
				else if(pgt->pos<4){
					pas_p.AnimeNo=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_b[pgt->pos-1].patno;
					pas_p.Wait=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_b[pgt->pos-1].wait;
					pas_p.Reverse=0;
					num=0;
				}
				else if(pgt->pos<8){
					pas_p.AnimeNo=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_b[pgt->pos-5].patno;
					pas_p.Wait=pgt->pad[PokeGraNoTable[pgt->mons_no]].prg_anm_b[pgt->pos-5].wait;
					pas_p.Reverse=0;
					num=0;
				}

				PokeAnm_SetPokeAnime(pgt->pasp,pgt->ss[num],&pas_p,num);
				Snd_PMVoicePlay(pgt->mons_no);

				pgt->seq_no_temp=pgt->seq_no;
				pgt->seq_no=SEQ_POKEMON_ANIME_ACT_B+num;
	
			}
		}
		if(sys.trg == PAD_BUTTON_A){
			if(mlp[pgt->pos].a_button_act!=NULL){
				pgt->sub_seq_no=0;
				pgt->seq_no=SEQ_POKEMON_ANIME_EDIT;
			}
		}
		if(move!=NO_MOVE){
			CursorMove(pgt,SIDE_SUB,move,CUR_PUT);
		}
		if(sys.repeat & PAD_BUTTON_L){
			if(pgt->mons_no==1){
				pgt->mons_no=MONSNO_END;
			}
			else{
				pgt->mons_no--;
			}
			pgt->sex=PokeGraTestSexGet(pgt->mons_no);
			if(pgt->sex==3){
				pgt->sex=0;
			}
			PokeGraTestDebugPrint(pgt,VOICE_ON);
			PokeTestMainScreenCreate(pgt);
			PokeGraTestSubScreenMake(pgt);
			CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_PUT);
		}
		else if(sys.repeat & PAD_BUTTON_R){
			if(pgt->mons_no==MONSNO_END){
				pgt->mons_no=1;
			}
			else{
				pgt->mons_no++;
			}
			pgt->sex=PokeGraTestSexGet(pgt->mons_no);
			if(pgt->sex==3){
				pgt->sex=0;
			}
			PokeGraTestDebugPrint(pgt,VOICE_ON);
			PokeTestMainScreenCreate(pgt);
			PokeGraTestSubScreenMake(pgt);
			CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_PUT);
		}
		break;
	case SEQ_POKEMON_ANIME_EDIT:
		if(mlp[pgt->pos].a_button_act(pgt)==TRUE){
			pgt->seq_no=SEQ_POKEMON_ANIME;
		}
		break;
	//ロード
	case SEQ_LOAD:
		if(PokeGraTestLoadAct(pgt)==TRUE){
			pgt->seq_no=pgt->seq_no_temp;
			if(pgt->seq_no){
				CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_PUT);
			}
		}
		break;
	//セーブ
	case SEQ_SAVE:
		if(PokeGraTestSaveAct(pgt)==TRUE){
			pgt->seq_no=pgt->seq_no_temp;
			if(pgt->seq_no){
				CursorMove(pgt,SIDE_SUB,pgt->pos,CUR_PUT);
			}
		}
		break;
	//アニメ終了待ち
	case SEQ_POKEMON_ANIME_ACT:
		if((PokeAnm_IsFinished(pgt->pasp,0)==TRUE)&&
		   (PokeAnm_IsFinished(pgt->pasp,1)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(pgt->ss[0])==FALSE)&&
		   (SoftSpriteAnimeEndCheck(pgt->ss[1])==FALSE)){
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_Y_REQ,1);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_AFF_REQ,1);
			pgt->seq_no=pgt->seq_no_temp;
		}
		break;
	//アニメ終了待ち
	case SEQ_POKEMON_ANIME_ACT_B:
		if((PokeAnm_IsFinished(pgt->pasp,0)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(pgt->ss[0])==FALSE)){
			pgt->seq_no=pgt->seq_no_temp;
		}
		break;
	//アニメ終了待ち
	case SEQ_POKEMON_ANIME_ACT_F:
		if((PokeAnm_IsFinished(pgt->pasp,1)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(pgt->ss[1])==FALSE)){
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_Y_REQ,1);
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_AFF_REQ,1);
			pgt->seq_no=pgt->seq_no_temp;
		}
		break;
	}
#if 0
	if((sys.trg & PGT_END_KEY)==PGT_END_KEY){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_BGL_BGControlExit(pgt->bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlExit(pgt->bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlExit(pgt->bgl, GF_BGL_FRAME3_M );
		GF_BGL_BGControlExit(pgt->bgl, GF_BGL_FRAME1_S );
		GF_BGL_BmpWinFree(pgt->win_m,1);
		GF_BGL_BmpWinFree(pgt->win_s,1);
		SoftSpriteEnd(pgt->ssm);
		PokeAnm_FreeMemory(pgt->pasp);
		sys_FreeMemoryEz(pgt->msg_buf);
		sys_FreeMemoryEz(pgt->bgl);
		MSGMAN_Delete(pgt->man_msg);
		pgt->end_flag = TRUE;
		return;
	}
#endif

	SoftSpriteMain(pgt->ssm);
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
}

//============================================================================================
/**
 *	メインループタスク
 */
//============================================================================================
static	void	PokeGraTestDebugPrint(POKE_GRA_TEST *pgt,int mode)
{
	int				height;
	SOFT_SPRITE_ARC	*ssa;

	ssa=SoftSpriteArcPointerGet(pgt->ssm,0);
	PokeGraArcDataGet(ssa,pgt->mons_no,pgt->sex,PARA_BACK,pgt->col,pgt->form_no,0x88888888);
	height=PokeHeightGet(pgt->mons_no,pgt->sex,PARA_BACK,pgt->form_no,NULL)+APPEAR_Y_TYPE_AA;
	SoftSpriteParaSet(pgt->ss[0],SS_PARA_POS_Y,height);

	ssa=SoftSpriteArcPointerGet(pgt->ssm,1);
	PokeGraArcDataGet(ssa,pgt->mons_no,pgt->sex,PARA_FRONT,pgt->col,pgt->form_no,0x88888888);
	height=PokeHeightGet(pgt->mons_no,pgt->sex,PARA_FRONT,pgt->form_no,NULL);
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_POS_Y,APPEAR_Y_TYPE_BB+height);
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_ANM_PAT,pgt->anm_pat);
	PokeGraTestShadowSet(pgt,height);

//	PokeGraTestMSG_Print(pgt);

	SoftSpriteRecover(pgt->ssm);

	if(mode==VOICE_ON){
		Snd_PMVoicePlay(pgt->mons_no);
	}
}

static	void	PokeGraTestShadowSet(POKE_GRA_TEST *pgt,int height)
{
	s8		ox;
	s8		oy;
	u8		size;

	switch(pgt->shadow_flag%3){
	case 0:
	case 1:
		ox	=pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]];
		oy	=pgt->height[PokeGraNoTable[pgt->mons_no]];
		size=pgt->shadow_size[PokeGraNoTable[pgt->mons_no]];
		break;
	case 2:
		ArchiveDataLoadOfs(&ox,ARC_POKE_SHADOW_OFX,0,pgt->mons_no,1);
		ArchiveDataLoadOfs(&oy,ARC_POKE_YOFS,0,pgt->mons_no,1);
		ArchiveDataLoadOfs(&size,ARC_POKE_SHADOW,0,pgt->mons_no,1);
		break;
	}
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OY,SHADOW_OFS-height);
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OX,ox);
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_HEIGHT,oy);
	SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_SIZE,size);
}

//==============================================================================================
//
//	タイトルデバックメニューから呼ばれるように追加
//
//==============================================================================================
//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT PokeGraTestProc_Init(PROC * proc, int * seq)
{
	POKE_GRA_TEST	*pgt;
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_BATTLE,BATTLE_ALLOC_SIZE);
	pgt=PROC_AllocWork(proc,sizeof(POKE_GRA_TEST),HEAPID_BATTLE);
	PokeGraInit(pgt);
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT PokeGraTestProc_Main(PROC * proc, int * seq)
{
	POKE_GRA_TEST * pgt = PROC_GetWork(proc);
	PokeGraTestMain(pgt);
	if (pgt->end_flag) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT PokeGraTestProc_End(PROC * proc, int * seq)
{
	PROC_FreeWork(proc);
	sys_DeleteHeap(HEAPID_BATTLE);
	Main_SetNextProc(NO_OVERLAY_ID, &TitleProcData);
	//sys_MainProcChange( TitleMainProc );				//復帰先
	//ソフトリセット
	//詳細はソース先頭の「サウンドテストの例外処理について」を参照して下さい
	//OS_InitReset();
	OS_ResetSystem(0);									//ソフトリセット
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
const PROC_DATA PokeGraTestProcData = {
	PokeGraTestProc_Init,
	PokeGraTestProc_Main,
	PokeGraTestProc_End,
	NO_OVERLAY_ID
};

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	VBLankには引数が必要なので定義してあるが実際にはNULLが入っているので、アクセスは禁止！
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	PokeGraTestVBlank(void *work)
{
	POKE_GRA_TEST	*pgt=(POKE_GRA_TEST *)work;

	G2_BlendNone();
	G2S_BlendNone();

	SoftSpriteTextureTrans(pgt->ssm);

	GF_BGL_VBlankFunc(pgt->bgl);

	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief	3D初期化
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static void Init3DStuff_(void)
{
    G3X_Init();                                            // initialize the 3D graphics states
    G3X_InitMtxStack();                                    // initialize the matrix stack

    G2_SetBG0Priority(1);

    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
    G3X_AlphaBlend(TRUE);

    // 3D 面は特殊効果OFFでも他のBG面とαブレンディングが行われますが、
    // そのためにはαブレンディング対象面の指定を行う必要があります。
    // SDK には対象面のみを設定する API が存在しないので、代わりに G2_SetBlendAlpha を使います。
    // この場合 G2_SetBlendAlpha の後ろ2つの引数は無視されます。
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BD, 0, 0);

    // clear color
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 0, FALSE );

    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン性別ゲット
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	u8	PokeGraTestSexGet(u16 monsno)
{
	u8	sex;

	sex=PokePersonalParaGet(monsno,ID_PER_sex);
	switch(sex){
		case	MONS_MALE:
			return	PARA_MALE;
		case	MONS_FEMALE:
			return	PARA_FEMALE;
		case	MONS_UNKNOWN:
			return	PARA_UNK;
	}
	return	3;
}

//--------------------------------------------------------------
//	メッセージ表示位置定義
//--------------------------------------------------------------
#define	ANM_FRONT_NUM_X		(16)	//アニメーションナンバー
#define	ANM_FRONT_X			(48)	//アニメーションナンバー
#define	ANM_FRONT_WAIT_X	(208)	//アニメーションナンバー
#define	ANM_FRONT_Y			(0)		//アニメーションナンバー

#define	ANM_BACK_NUM_X		(16)	//アニメーションナンバー
#define	ANM_BACK_X			(48)	//アニメーションナンバー
#define	ANM_BACK_WAIT_X		(208)	//アニメーションナンバー
#define	ANM_BACK_Y			(13)	//アニメーションナンバー
#define	ANM_BACK_OFS_Y		(13)	//アニメーションナンバー

#define	ANM_NO_X	(16)	//アニメーションナンバー
#define	ANM_NO_Y	(52)	//アニメーションナンバー
#define	PAT_NO_X	(64)	//Patナンバー
#define	PAT_NO_Y	(52)	//Patナンバー
#define	WAIT_X		(112)	//アニメーションWait
#define	WAIT_Y		(52)	//アニメーションWait

#define	ANM_NO_OFS_Y	(14)	//アニメーションナンバー

#define	SVLD_X		(160)
#define	SVLD_Y		(80)

#define	YES_NO_X	(160)
#define	YES_NO_Y	(96)

#define	YES_NO_CUR_X	(144)
#define	YES_NO_CUR_Y	(96)

#if 0
//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestMSG_Print(POKE_GRA_TEST *pgt)
{
	MSGDATA_MANAGER		*msg_m;

	GF_BGL_BmpWinDataFill(pgt->win_m,0xff);

	//モンスターナンバー
	STRBUF_SetNumber(pgt->msg_buf, pgt->mons_no, 3, NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,MONS_NUM_X,MONS_NUM_Y,MSG_NO_PUT,NULL);

	//モンスター名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_monsname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,pgt->mons_no,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,MONS_NAME_X,MONS_NAME_Y,MSG_NO_PUT,NULL);

	//性別
	MSGMAN_GetString(pgt->man_msg,POKE_TEST_002+pgt->sex,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,MONS_SEX_X,MONS_SEX_Y,MSG_NO_PUT,NULL);

	//カラー
	MSGMAN_GetString(pgt->man_msg,POKE_TEST_005+pgt->col,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,MONS_COL_X,MONS_COL_Y,MSG_NO_PUT,NULL);

	//アニメパターンナンバー
	STRBUF_SetNumber(pgt->msg_buf, pgt->height[PokeGraNoTable[pgt->mons_no]], 3, NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,MONS_PAT_X,MONS_PAT_Y,MSG_NO_PUT,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);

	pgt->put_req=1;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	サブスクリーン表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenMake(POKE_GRA_TEST *pgt)
{
	int		i;	

	GF_BGL_BmpWinDataFill(pgt->win_s,0xff);

	PokeGraTestSubScreenAnmFDataPut(pgt,COL_NORMAL);
	PokeGraTestSubScreenAnmFWaitDataPut(pgt,COL_NORMAL);

	for(i=0;i<3;i++){
		PokeGraTestSubScreenAnmBDataPut(pgt,i,COL_NORMAL);
		PokeGraTestSubScreenAnmBWaitDataPut(pgt,i,COL_NORMAL);
	}

	for(i=0;i<SS_ANM_SEQ_MAX;i++){
		//アニメナンバー
		STRBUF_SetNumber(pgt->msg_buf,i+1,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_NO_X,ANM_NO_Y+i*ANM_NO_OFS_Y,MSG_NO_PUT,NULL);
		PokeGraTestSubScreenPatDataPut(pgt,i,COL_NORMAL);
		PokeGraTestSubScreenWaitDataPut(pgt,i,COL_NORMAL);
	}
	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeTestPokeNumDataPut(POKE_GRA_TEST *pgt,int mode)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_NUM_DATA_X,POKE_NUM_DATA_Y,12*8,16);

	PokeTestNumPut(pgt,POKE_NUM_DATA_X,POKE_NUM_DATA_Y,pgt->mons_no,3,pgt->cur_pos_keta,mode);

	MSGMAN_GetString(pgt->man_poke,pgt->mons_no,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_NUM_DATA_X+32,POKE_NUM_DATA_Y,MSG_NO_PUT,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeSexDataPut(POKE_GRA_TEST *pgt)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_SEX_DATA_X,POKE_SEX_DATA_Y,12*2,16);

	MSGMAN_GetString(pgt->man_msg,POKE_TEST_002+pgt->sex,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_SEX_DATA_X,POKE_SEX_DATA_Y,MSG_NO_PUT,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeColorDataPut(POKE_GRA_TEST *pgt)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_COLOR_DATA_X,POKE_COLOR_DATA_Y,12*4,16);

	MSGMAN_GetString(pgt->man_msg,POKE_TEST_005+pgt->col,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_COLOR_DATA_X,POKE_COLOR_DATA_Y,MSG_NO_PUT,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokePatDataPut(POKE_GRA_TEST *pgt)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_PAT_DATA_X,POKE_PAT_DATA_Y,12*1,16);

	//アニメパターンナンバー
	STRBUF_SetNumber(pgt->msg_buf, pgt->anm_pat,1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_PAT_DATA_X,POKE_PAT_DATA_Y,MSG_NO_PUT,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeFormDataPut(POKE_GRA_TEST *pgt,int mode)
{
	int	max;

	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_FORM_DATA_X,POKE_FORM_DATA_Y,12*4,16);

	PokeTestNumPut(pgt,POKE_FORM_DATA_X,POKE_FORM_DATA_Y,pgt->form_no,2,pgt->cur_pos_keta,mode);

	max=PokeTestPokeFormMaxGet(pgt);

	STRBUF_SetNumber(pgt->msg_buf,max,2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_FORM_DATA_X+20,POKE_FORM_DATA_Y,MSG_NO_PUT,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeHeightDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_HEIGHT_DATA_X,POKE_HEIGHT_DATA_Y,12*2,16);

	STRBUF_SetNumber(pgt->msg_buf,pgt->height[PokeGraNoTable[pgt->mons_no]],3,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_HEIGHT_DATA_X,POKE_HEIGHT_DATA_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeOfxDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_OFX_DATA_X,POKE_OFX_DATA_Y,12*2,16);

	STRBUF_SetNumber(pgt->msg_buf,pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]],3,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_OFX_DATA_X,POKE_OFX_DATA_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeShadowDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_SHADOW_DATA_X,POKE_SHADOW_DATA_Y,12*1,16);

	STRBUF_SetNumber(pgt->msg_buf,pgt->shadow_size[PokeGraNoTable[pgt->mons_no]],1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,POKE_SHADOW_DATA_X,POKE_SHADOW_DATA_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

static	void	PokeTestPokeBGColorRDataPut(POKE_GRA_TEST *pgt,int mode)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_BG_COLOR_R_DATA_X,POKE_BG_COLOR_R_DATA_Y,12*2,16);

	PokeTestNumPut(pgt,POKE_BG_COLOR_R_DATA_X,POKE_BG_COLOR_R_DATA_Y,pgt->bg_r,2,pgt->cur_pos_keta,mode);

	pgt->put_req=1;
}

static	void	PokeTestPokeBGColorGDataPut(POKE_GRA_TEST *pgt,int mode)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_BG_COLOR_G_DATA_X,POKE_BG_COLOR_G_DATA_Y,12*2,16);

	PokeTestNumPut(pgt,POKE_BG_COLOR_G_DATA_X,POKE_BG_COLOR_G_DATA_Y,pgt->bg_g,2,pgt->cur_pos_keta,mode);

	pgt->put_req=1;
}

static	void	PokeTestPokeBGColorBDataPut(POKE_GRA_TEST *pgt,int mode)
{
	GF_BGL_BmpWinFill(pgt->win_m,0x0f,POKE_BG_COLOR_B_DATA_X,POKE_BG_COLOR_B_DATA_Y,12*2,16);

	PokeTestNumPut(pgt,POKE_BG_COLOR_B_DATA_X,POKE_BG_COLOR_B_DATA_Y,pgt->bg_b,2,pgt->cur_pos_keta,mode);

	pgt->put_req=1;
}

static	void	PokeTestBGColorSet(POKE_GRA_TEST *pgt)
{
	u16	col;
	u16	src;
	u8	evy;

	if(pgt->col_flag&1){
		pgt->col_flag+=0x100;
		if((pgt->col_flag&0x300)==0){
			if(pgt->col_flag&0x80){
				pgt->col_flag-=2;
				if((pgt->col_flag&0x0e)==0){
					pgt->col_flag^=0x80;
				}
			}
			else{
				pgt->col_flag+=2;
				if((pgt->col_flag&0x0e)==0x0e){
					pgt->col_flag^=0x80;
				}
			}
			evy=((pgt->col_flag&0x0e)>>1)+8;
			src=0;
			SoftFade(&src,&col,1,evy,GX_RGB(pgt->bg_r,pgt->bg_g,pgt->bg_b));
		}
		else{
			return;
		}
	}
	else{
		col=GX_RGB(pgt->bg_r,pgt->bg_g,pgt->bg_b);
	}

	DC_FlushRange((void *)&col,sizeof(col));
	GX_LoadBGPltt((void *)&col,0,sizeof(col));
}

static	void	PokeTestNumPut(POKE_GRA_TEST *pgt,int x,int y,int param,int keta,int pos,int mode)
{
	int		i;
	int		data,ofs;
	int		keta_tbl[10]={
		1000000000,
		100000000,
		10000000,
		1000000,
		100000,
		10000,
		1000,
		100,
		10,
		1,
	};

	ofs=0;

	for(i=0;i<keta;i++){
		data=param/keta_tbl[10-keta+i];
		param%=keta_tbl[10-keta+i];
		STRBUF_SetNumber(pgt->msg_buf,data,1,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
		if(mode==MODE_NORMAL){
			GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,x+ofs,y,MSG_NO_PUT,COL_NORMAL,NULL);
		}
		else{
			if((keta-1)-i==pos){
				GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,x+ofs,y,MSG_NO_PUT,COL_CURSOR,NULL);
			}
			else{
				GF_STR_PrintColor(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,x+ofs,y,MSG_NO_PUT,COL_ACTIVE,NULL);
			}
		}
		ofs+=FontProc_GetPrintStrWidth(FONT_SYSTEM,pgt->msg_buf,0);
	}

	pgt->put_req=1;
}

static	int	PokeTestPokeFormMaxGet(POKE_GRA_TEST *pgt)
{
	int	ret;

	switch(pgt->mons_no){
	//ミノムッチ
	//ミノメス
	case MONSNO_MINOMUTTI:
	case MONSNO_MINOMESU:
		ret=FORMNO_MINOMUTTI_MAX;
		break;
	//シーウシ
	//シードルゴ
	case MONSNO_SIIUSI:
	case MONSNO_SIIDORUGO:
		ret=FORMNO_SII_MAX;
		break;
	//チェリシュ
	case MONSNO_THERISYU:
		ret=FORMNO_THERISYU_MAX;
		break;
	//アウス
	case MONSNO_AUSU:
		ret=POKE_WAZA_TYPE_MAX;
		break;
	//ポワルン
	case MONSNO_POWARUN:
		ret=FORMNO_POWARUN_MAX;
		break;
	//デオキシス
	case MONSNO_DEOKISISU:
		ret=FORMNO_DEOKISISU_MAX;
		break;
	//アンノーン
	case MONSNO_ANNOON:
		ret=UNK_QUE;
		break;
	default:
		ret=0;
		break;
	}
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenAnmFDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col)
{
	int	grano;
	u8	anm_no;

	grano=PokeGraNoTable[pgt->mons_no];
	anm_no=pgt->pad[grano].prg_anm_f;

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,ANM_FRONT_NUM_X,ANM_FRONT_Y,144,14);

	STRBUF_SetNumber(pgt->msg_buf,anm_no+1,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_FRONT_NUM_X,ANM_FRONT_Y,MSG_NO_PUT,col,NULL);
	MSGMAN_GetString(pgt->man_pam,MSG_POKE_ANM001+anm_no,pgt->msg_buf);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_FRONT_X,ANM_FRONT_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenAnmFWaitDataPut(POKE_GRA_TEST *pgt,GF_PRINTCOLOR col)
{
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,ANM_FRONT_WAIT_X,ANM_FRONT_Y,24,14);

	STRBUF_SetNumber(pgt->msg_buf,pgt->pad[grano].prg_anm_f_wait,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_FRONT_WAIT_X,ANM_FRONT_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenAnmBDataPut(POKE_GRA_TEST *pgt,int num,GF_PRINTCOLOR col)
{
	int	grano;
	u8	anm_no;

	grano=PokeGraNoTable[pgt->mons_no];
	anm_no=pgt->pad[grano].prg_anm_b[num].patno;

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,ANM_BACK_X,ANM_BACK_Y+ANM_BACK_OFS_Y*num,128,ANM_BACK_OFS_Y);

	STRBUF_SetNumber(pgt->msg_buf,anm_no+1,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_BACK_NUM_X,ANM_BACK_Y+ANM_BACK_OFS_Y*num,MSG_NO_PUT,col,NULL);
	MSGMAN_GetString(pgt->man_pam,MSG_POKE_ANM001+anm_no,pgt->msg_buf);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_BACK_X,ANM_BACK_Y+ANM_BACK_OFS_Y*num,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenAnmBWaitDataPut(POKE_GRA_TEST *pgt,int num,GF_PRINTCOLOR col)
{
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,ANM_BACK_WAIT_X,ANM_BACK_Y+ANM_BACK_OFS_Y*num,24,ANM_BACK_OFS_Y);

	STRBUF_SetNumber(pgt->msg_buf,pgt->pad[grano].prg_anm_b[num].wait,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);

	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,ANM_BACK_WAIT_X,ANM_BACK_Y+ANM_BACK_OFS_Y*num,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenPatDataPut(POKE_GRA_TEST *pgt,int pos,GF_PRINTCOLOR col)
{
	s8	pat;
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];
	pat=pgt->pad[grano].ssanm[pos].patno;

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,PAT_NO_X,PAT_NO_Y+pos*ANM_NO_OFS_Y,24,14);

	//Patナンバー
	if(pat<0){
		if(pat==-1){
			MSGMAN_GetString(pgt->man_msg,POKE_TEST_007,pgt->msg_buf);
		}
		else{
			MSGMAN_GetString(pgt->man_msg,POKE_TEST_014+(pat*-1-2),pgt->msg_buf);
		}
	}
	else{
		STRBUF_SetNumber(pgt->msg_buf,pat,1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	}
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,PAT_NO_X,PAT_NO_Y+pos*ANM_NO_OFS_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//--------------------------------------------------------------
/**
 * @brief	サブスクリーンデータ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	PokeGraTestSubScreenWaitDataPut(POKE_GRA_TEST *pgt,int pos,GF_PRINTCOLOR col)
{
	u8	wait;
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];
	wait=pgt->pad[grano].ssanm[pos].wait;

	GF_BGL_BmpWinFill(pgt->win_s,0x0f,WAIT_X,WAIT_Y+pos*ANM_NO_OFS_Y,24,14);

	//Wait
	STRBUF_SetNumber(pgt->msg_buf,wait,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,WAIT_X,WAIT_Y+pos*ANM_NO_OFS_Y,MSG_NO_PUT,col,NULL);

	pgt->put_req=1;
}

//==============================================================================================
//
//	メニューカーソル移動
//
//==============================================================================================
static	void	CursorMove(POKE_GRA_TEST *pgt,int side,int pos,int mode)
{
	switch(side){
	default:
	case SIDE_MAIN:
		GF_BGL_BmpWinFill(pgt->win_m,0x0f,mlp_m[pgt->main_pos].cursor_pos_x,mlp_m[pgt->main_pos].cursor_pos_y,12,16);
		if(mode==CUR_PUT){
			MSGMAN_GetString(pgt->man_msg,POKE_TEST_009,pgt->msg_buf);
			GF_STR_PrintSimple(pgt->win_m,FONT_SYSTEM,pgt->msg_buf,mlp_m[pos].cursor_pos_x,mlp_m[pos].cursor_pos_y,
							   MSG_NO_PUT,NULL);
			pgt->main_pos=pos;
		}
		break;
	case SIDE_SUB:
		GF_BGL_BmpWinFill(pgt->win_s,0x0f,mlp[pgt->pos].cursor_pos_x,mlp[pgt->pos].cursor_pos_y,12,16);
		if(mode==CUR_PUT){
			MSGMAN_GetString(pgt->man_msg,POKE_TEST_009,pgt->msg_buf);
			GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,mlp[pos].cursor_pos_x,mlp[pos].cursor_pos_y,MSG_NO_PUT,NULL);
			pgt->pos=pos;
		}
		break;
	}
	pgt->put_req=1;
}

//==============================================================================================
//
//	メニューカーソル移動
//
//==============================================================================================
static	void	YesNoCursorMove(POKE_GRA_TEST *pgt,int pos,int mode)
{
	GF_BGL_BmpWinFill(pgt->win_s,0x0f,YES_NO_CUR_X,YES_NO_CUR_Y+ANM_NO_OFS_Y*pgt->yes_no_pos,12,16);
	if(mode==CUR_PUT){
		MSGMAN_GetString(pgt->man_msg,POKE_TEST_009,pgt->msg_buf);
		GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,YES_NO_CUR_X,YES_NO_CUR_Y+ANM_NO_OFS_Y*pos,MSG_NO_PUT,NULL);
		pgt->yes_no_pos=pos;
	}
	pgt->put_req=1;
}

static	BOOL	PokeNumAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	if(sys.trg==PAD_BUTTON_X){
		PokeColorAct(pgt);
	}
	if(sys.trg==PAD_BUTTON_Y){
		PokeSexAct(pgt);
	}

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeNumDataPut(pgt,MODE_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		switch(PokeTestNumCalc(pgt,&pgt->mons_no,3,MONSNO_HUSIGIDANE,MONSNO_END,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			pgt->sex=PokeGraTestSexGet(pgt->mons_no);
			if(pgt->sex==3){
				pgt->sex=0;
			}
			pgt->form_no=0;
			PokeTestPokeSexDataPut(pgt);
			PokeTestPokeFormDataPut(pgt,MODE_NORMAL);
			if((pgt->shadow_flag%3)==2){
				PokeTestPokeHeightDataPut(pgt,COL_NONE);
				PokeTestPokeOfxDataPut(pgt,COL_NONE);
				PokeTestPokeShadowDataPut(pgt,COL_NONE);
			}
			else{
				PokeTestPokeHeightDataPut(pgt,COL_NORMAL);
				PokeTestPokeOfxDataPut(pgt,COL_NORMAL);
				PokeTestPokeShadowDataPut(pgt,COL_NORMAL);
			}
			PokeGraTestDebugPrint(pgt,VOICE_ON);
		case NUM_CALC_MOVE:
			PokeTestPokeNumDataPut(pgt,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			PokeTestPokeNumDataPut(pgt,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeSexAct(POKE_GRA_TEST *pgt)
{
	int	sex;

	sex=PokeGraTestSexGet(pgt->mons_no);
	if(sex==3){
		pgt->sex^=1;
	}
	PokeTestPokeSexDataPut(pgt);
	PokeGraTestDebugPrint(pgt,VOICE_OFF);

	return TRUE;
}

static	BOOL	PokeColorAct(POKE_GRA_TEST *pgt)
{
	pgt->col^=1;
	PokeTestPokeColorDataPut(pgt);
	PokeGraTestDebugPrint(pgt,VOICE_OFF);

	return TRUE;
}

static	BOOL	PokePatAct(POKE_GRA_TEST *pgt)
{
	pgt->anm_pat^=1;
	PokeTestPokePatDataPut(pgt);
	PokeGraTestDebugPrint(pgt,VOICE_OFF);

	return TRUE;
}

static	BOOL	PokeFormAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;
	int		max;

	if(sys.trg==PAD_BUTTON_X){
		PokeColorAct(pgt);
	}
	if(sys.trg==PAD_BUTTON_Y){
		PokeSexAct(pgt);
	}

	max=PokeTestPokeFormMaxGet(pgt);

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeFormDataPut(pgt,MODE_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		switch(PokeTestNumCalc(pgt,&pgt->form_no,2,0,max,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			PokeGraTestDebugPrint(pgt,VOICE_OFF);
		case NUM_CALC_MOVE:
			PokeTestPokeFormDataPut(pgt,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			PokeTestPokeFormDataPut(pgt,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeHeightAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	if((pgt->shadow_flag%3)==2){
		return TRUE;
	}

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeHeightDataPut(pgt,COL_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		if((sys.repeat & PAD_KEY_UP)&&(pgt->height[PokeGraNoTable[pgt->mons_no]]<HEIGHT_MAX)){
			pgt->height[PokeGraNoTable[pgt->mons_no]]++;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_HEIGHT,pgt->height[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeHeightDataPut(pgt,COL_ACTIVE);
		}
		if((sys.repeat & PAD_KEY_DOWN)&&(pgt->height[PokeGraNoTable[pgt->mons_no]]>HEIGHT_MIN)){
			pgt->height[PokeGraNoTable[pgt->mons_no]]--;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_HEIGHT,pgt->height[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeHeightDataPut(pgt,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeTestPokeHeightDataPut(pgt,COL_NORMAL);
			ret=TRUE;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeOfxAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	if((pgt->shadow_flag%3)==2){
		return TRUE;
	}

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeOfxDataPut(pgt,COL_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		if((sys.repeat & PAD_KEY_RIGHT)&&(pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]<HEIGHT_MAX)){
			pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]++;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OX,pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeOfxDataPut(pgt,COL_ACTIVE);
		}
		if((sys.repeat & PAD_KEY_LEFT)&&(pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]>HEIGHT_MIN)){
			pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]--;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_OX,pgt->shadow_ofx[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeOfxDataPut(pgt,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeTestPokeOfxDataPut(pgt,COL_NORMAL);
			ret=TRUE;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeShadowAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	if((pgt->shadow_flag%3)==2){
		return TRUE;
	}

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeShadowDataPut(pgt,COL_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		if((sys.repeat & PAD_KEY_UP)&&(pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]<3)){
			pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]++;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_SIZE,pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeShadowDataPut(pgt,COL_ACTIVE);
		}
		if((sys.repeat & PAD_KEY_DOWN)&&(pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]>0)){
			pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]--;
			SoftSpriteParaSet(pgt->ss[1],SS_PARA_SHADOW_SIZE,pgt->shadow_size[PokeGraNoTable[pgt->mons_no]]);
			PokeTestPokeShadowDataPut(pgt,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeTestPokeShadowDataPut(pgt,COL_NORMAL);
			ret=TRUE;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeBGColorRAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeBGColorRDataPut(pgt,MODE_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		switch(PokeTestNumCalc(pgt,&pgt->bg_r,2,0,31,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			PokeTestBGColorSet(pgt);
		case NUM_CALC_MOVE:
			PokeTestPokeBGColorRDataPut(pgt,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			PokeTestPokeBGColorRDataPut(pgt,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeBGColorGAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeBGColorGDataPut(pgt,MODE_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		switch(PokeTestNumCalc(pgt,&pgt->bg_g,2,0,31,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			PokeTestBGColorSet(pgt);
		case NUM_CALC_MOVE:
			PokeTestPokeBGColorGDataPut(pgt,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			PokeTestPokeBGColorGDataPut(pgt,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

static	BOOL	PokeBGColorBAct(POKE_GRA_TEST *pgt)
{
	BOOL	ret=FALSE;

	switch(pgt->sub_seq_no){
	case 0:
		PokeTestPokeBGColorBDataPut(pgt,MODE_ACTIVE);
		pgt->sub_seq_no++;
	case 1:
		switch(PokeTestNumCalc(pgt,&pgt->bg_b,2,0,31,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			PokeTestBGColorSet(pgt);
		case NUM_CALC_MOVE:
			PokeTestPokeBGColorBDataPut(pgt,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			PokeTestPokeBGColorBDataPut(pgt,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	数値編集
//
//==============================================================================================
static	int	PokeTestNumCalc(POKE_GRA_TEST *pgt,int *param,int keta,int min,int max,int mode)
{
	int ret=NUM_CALC_NONE;
	u32	calc_work[]={
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};

	if((sys.repeat & PAD_KEY_LEFT)&&(pgt->cur_pos_keta<(keta-1))){
		pgt->cur_pos_keta++;
		ret=NUM_CALC_MOVE;
	}
	else if((sys.repeat & PAD_KEY_RIGHT)&&(pgt->cur_pos_keta)){
		pgt->cur_pos_keta--;
		ret=NUM_CALC_MOVE;
	}
	else if(sys.repeat & PAD_KEY_UP){
		if(mode==MODE_LOOP){
			if((param[0]+calc_work[pgt->cur_pos_keta])>max){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[pgt->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]+calc_work[pgt->cur_pos_keta])>max){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[pgt->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.repeat & PAD_KEY_DOWN){
		if(mode==MODE_LOOP){
			if((param[0]<calc_work[pgt->cur_pos_keta])||((param[0]-calc_work[pgt->cur_pos_keta])<min)){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[pgt->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]<calc_work[pgt->cur_pos_keta])||((param[0]-calc_work[pgt->cur_pos_keta])<min)){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[pgt->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.trg & PAD_BUTTON_A){
		pgt->cur_pos_keta=0;
		ret=NUM_CALC_END;
	}

	return ret;
}


//--------------------------------------------------------------
/**
 * @brief	AnmFront編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	AnmFrontAct(POKE_GRA_TEST *pgt)
{
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenAnmFDataPut(pgt,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].prg_anm_f<POKE_ANIME_MAX-1){
				pgt->pad[grano].prg_anm_f++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].prg_anm_f>0){
				pgt->pad[grano].prg_anm_f--;
			}
		}
		else if(sys.repeat&PAD_KEY_RIGHT){
			if((pgt->pad[grano].prg_anm_f+10)<POKE_ANIME_MAX-1){
				pgt->pad[grano].prg_anm_f+=10;
			}
			else{
				pgt->pad[grano].prg_anm_f=POKE_ANIME_MAX-1;
			}
		}
		else if(sys.repeat&PAD_KEY_LEFT){
			if((pgt->pad[grano].prg_anm_f-10)>0){
				pgt->pad[grano].prg_anm_f-=10;
			}
			else{
				pgt->pad[grano].prg_anm_f=0;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenAnmFDataPut(pgt,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenAnmFDataPut(pgt,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	Wait編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	AnmFrontWaitAct(POKE_GRA_TEST *pgt)
{
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenAnmFWaitDataPut(pgt,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].prg_anm_f_wait<99){
				pgt->pad[grano].prg_anm_f_wait++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].prg_anm_f_wait>0){
				pgt->pad[grano].prg_anm_f_wait--;
			}
		}
		else if(sys.repeat&PAD_KEY_RIGHT){
			if((pgt->pad[grano].prg_anm_f_wait+10)<99){
				pgt->pad[grano].prg_anm_f_wait+=10;
			}
			else{
				pgt->pad[grano].prg_anm_f_wait=99;
			}
		}
		else if(sys.repeat&PAD_KEY_LEFT){
			if((pgt->pad[grano].prg_anm_f_wait-10)>0){
				pgt->pad[grano].prg_anm_f_wait-=10;
			}
			else{
				pgt->pad[grano].prg_anm_f_wait=0;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenAnmFWaitDataPut(pgt,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenAnmFWaitDataPut(pgt,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	AnmBack編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	AnmBackAct(POKE_GRA_TEST *pgt)
{
	int	grano;
	int	num;

	grano=PokeGraNoTable[pgt->mons_no];
	num=pgt->pos-1;

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenAnmBDataPut(pgt,num,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].prg_anm_b[num].patno<POKE_ANIME_MAX-1){
				pgt->pad[grano].prg_anm_b[num].patno++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].prg_anm_b[num].patno>0){
				pgt->pad[grano].prg_anm_b[num].patno--;
			}
		}
		else if(sys.repeat&PAD_KEY_RIGHT){
			if((pgt->pad[grano].prg_anm_b[num].patno+10)<POKE_ANIME_MAX-1){
				pgt->pad[grano].prg_anm_b[num].patno+=10;
			}
			else{
				pgt->pad[grano].prg_anm_b[num].patno=POKE_ANIME_MAX-1;
			}
		}
		else if(sys.repeat&PAD_KEY_LEFT){
			if((pgt->pad[grano].prg_anm_b[num].patno-10)>0){
				pgt->pad[grano].prg_anm_b[num].patno-=10;
			}
			else{
				pgt->pad[grano].prg_anm_b[num].patno=0;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenAnmBDataPut(pgt,num,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenAnmBDataPut(pgt,num,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	Wait編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	AnmBackWaitAct(POKE_GRA_TEST *pgt)
{
	int	grano;
	int	num;

	grano=PokeGraNoTable[pgt->mons_no];
	num=pgt->pos-1;

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenAnmBWaitDataPut(pgt,num,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].prg_anm_b[num].wait<99){
				pgt->pad[grano].prg_anm_b[num].wait++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].prg_anm_b[num].wait>0){
				pgt->pad[grano].prg_anm_b[num].wait--;
			}
		}
		else if(sys.repeat&PAD_KEY_RIGHT){
			if((pgt->pad[grano].prg_anm_b[num].wait+10)<99){
				pgt->pad[grano].prg_anm_b[num].wait+=10;
			}
			else{
				pgt->pad[grano].prg_anm_b[num].wait=99;
			}
		}
		else if(sys.repeat&PAD_KEY_LEFT){
			if((pgt->pad[grano].prg_anm_b[num].wait-10)>0){
				pgt->pad[grano].prg_anm_b[num].wait-=10;
			}
			else{
				pgt->pad[grano].prg_anm_b[num].wait=0;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenAnmBWaitDataPut(pgt,num,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenAnmBWaitDataPut(pgt,num,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	PatNo編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	PatDataAct(POKE_GRA_TEST *pgt)
{
	int	pos;
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];
	pos=pgt->pos-MENU_PAT_01;

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenPatDataPut(pgt,pos,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].ssanm[pos].patno<1){
				pgt->pad[grano].ssanm[pos].patno++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].ssanm[pos].patno>-10){
				pgt->pad[grano].ssanm[pos].patno--;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenPatDataPut(pgt,pos,COL_ACTIVE);
			if(pos==0){
				if(pgt->pad[grano].ssanm[pos].patno>=0){
					SoftSpriteParaSet(pgt->ss[1],SS_PARA_ANM_PAT,pgt->pad[grano].ssanm[pos].patno);
				}
			}
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenPatDataPut(pgt,pos,COL_NORMAL);
			if(pos==0){
				SoftSpriteParaSet(pgt->ss[1],SS_PARA_ANM_PAT,0);
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	Wait編集
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	BOOL	WaitDataAct(POKE_GRA_TEST *pgt)
{
	int	pos;
	int	grano;

	grano=PokeGraNoTable[pgt->mons_no];
	pos=pgt->pos-MENU_WAIT_01;

	switch(pgt->sub_seq_no){
	case 0:
		PokeGraTestSubScreenWaitDataPut(pgt,pos,COL_ACTIVE);
		pgt->sub_seq_no++;
		break;
	case 1:
		if(sys.repeat&PAD_KEY_UP){
			if(pgt->pad[grano].ssanm[pos].wait<99){
				pgt->pad[grano].ssanm[pos].wait++;
			}
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(pgt->pad[grano].ssanm[pos].wait>0){
				pgt->pad[grano].ssanm[pos].wait--;
			}
		}
		else if(sys.repeat&PAD_KEY_RIGHT){
			if((pgt->pad[grano].ssanm[pos].wait+10)<99){
				pgt->pad[grano].ssanm[pos].wait+=10;
			}
			else{
				pgt->pad[grano].ssanm[pos].wait=99;
			}
		}
		else if(sys.repeat&PAD_KEY_LEFT){
			if((pgt->pad[grano].ssanm[pos].wait-10)>0){
				pgt->pad[grano].ssanm[pos].wait-=10;
			}
			else{
				pgt->pad[grano].ssanm[pos].wait=0;
			}
		}
		if(sys.repeat){
			PokeGraTestSubScreenWaitDataPut(pgt,pos,COL_ACTIVE);
		}
		if(sys.trg&PAD_BUTTON_A){
			PokeGraTestSubScreenWaitDataPut(pgt,pos,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	パラメータロード
//
//==============================================================================================
static	BOOL	PokeGraTestLoadAct(POKE_GRA_TEST *pgt)
{
	int	i;

	switch(pgt->sub_seq_no){
	case 0:
		OS_TPrintf("save_ram:0x%08x size:0x%08x\n",&pgt->pad[0],sizeof(POKE_ANM_DATA)*PGT_POKE_MAX);
		OS_TPrintf("height:0x%08x size:0x%08x\n",&pgt->height[0],PGT_POKE_MAX);
		OS_TPrintf("shadow:0x%08x size:0x%08x\n",&pgt->shadow_size[0],PGT_POKE_MAX);
		OS_TPrintf("shadow_ofx:0x%08x size:0x%08x\n",&pgt->shadow_ofx[0],PGT_POKE_MAX);
		MSGMAN_GetString(pgt->man_msg,POKE_TEST_010,pgt->msg_buf);
		GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,SVLD_X,SVLD_Y,MSG_NO_PUT,NULL);
		PokeGraTestYesNoPut(pgt);
		YesNoCursorMove(pgt,pgt->yes_no_pos,CUR_PUT);
		pgt->sub_seq_no++;
		break;
	case 1:
		if((sys.trg==PAD_KEY_UP)&&(pgt->yes_no_pos==1)){
			YesNoCursorMove(pgt,0,CUR_PUT);
		}
		if((sys.trg==PAD_KEY_DOWN)&&(pgt->yes_no_pos==0)){
			YesNoCursorMove(pgt,1,CUR_PUT);
		}
		if(sys.trg==PAD_BUTTON_A){
			if(pgt->yes_no_pos==0){
				PMSVLD_Load(SAVE_BANK,&pgt->pad[0],sizeof(POKE_ANM_DATA)*PGT_POKE_MAX+PGT_POKE_MAX*3);
			}
			if(pgt->height[0]!=0x55){
				for(i=0;i<PGT_POKE_MAX;i++){
					pgt->height[i]=0;
				}
				pgt->height[0]=0x55;
			}
			for(i=0;i<PGT_POKE_MAX;i++){
				if(pgt->shadow_size[i]>3){
					pgt->shadow_size[i]=1;
				}
			}
			if(pgt->shadow_ofx[0]!=0x55){
				for(i=0;i<PGT_POKE_MAX;i++){
					pgt->shadow_ofx[i]=0;
				}
				pgt->shadow_ofx[0]=0x55;
			}
			PokeGraTestSubScreenMake(pgt);
			return TRUE;
		}
		if(sys.trg==PAD_BUTTON_B){
			PokeGraTestSubScreenMake(pgt);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	パラメータセーブ
//
//==============================================================================================
static	BOOL	PokeGraTestSaveAct(POKE_GRA_TEST *pgt)
{
	switch(pgt->sub_seq_no){
	case 0:
		OS_TPrintf("save_ram:0x%08x size:0x%08x\n",&pgt->pad[0],sizeof(POKE_ANM_DATA)*PGT_POKE_MAX);
		OS_TPrintf("height:0x%08x size:0x%08x\n",&pgt->height[0],PGT_POKE_MAX);
		OS_TPrintf("shadow:0x%08x size:0x%08x\n",&pgt->shadow_size[0],PGT_POKE_MAX);
		OS_TPrintf("shadow_ofx:0x%08x size:0x%08x\n",&pgt->shadow_ofx[0],PGT_POKE_MAX);
		MSGMAN_GetString(pgt->man_msg,POKE_TEST_011,pgt->msg_buf);
		GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,SVLD_X,SVLD_Y,MSG_NO_PUT,NULL);
		PokeGraTestYesNoPut(pgt);
		YesNoCursorMove(pgt,pgt->yes_no_pos,CUR_PUT);
		pgt->sub_seq_no++;
		break;
	case 1:
		if((sys.trg==PAD_KEY_UP)&&(pgt->yes_no_pos==1)){
			YesNoCursorMove(pgt,0,CUR_PUT);
		}
		if((sys.trg==PAD_KEY_DOWN)&&(pgt->yes_no_pos==0)){
			YesNoCursorMove(pgt,1,CUR_PUT);
		}
		if(sys.trg==PAD_BUTTON_A){
			if(pgt->yes_no_pos==0){
				PMSVLD_Save(SAVE_BANK,&pgt->pad[0],sizeof(POKE_ANM_DATA)*PGT_POKE_MAX+PGT_POKE_MAX*3);
			}
			PokeGraTestSubScreenMake(pgt);
			return TRUE;
		}
		if(sys.trg==PAD_BUTTON_B){
			PokeGraTestSubScreenMake(pgt);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	YesNo
//
//==============================================================================================
static	void	PokeGraTestYesNoPut(POKE_GRA_TEST *pgt)
{
	MSGMAN_GetString(pgt->man_msg,POKE_TEST_012,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,YES_NO_X,YES_NO_Y,MSG_NO_PUT,NULL);
	MSGMAN_GetString(pgt->man_msg,POKE_TEST_013,pgt->msg_buf);
	GF_STR_PrintSimple(pgt->win_s,FONT_SYSTEM,pgt->msg_buf,YES_NO_X,YES_NO_Y+ANM_NO_OFS_Y,MSG_NO_PUT,NULL);
	pgt->put_req=1;
}

#if 0
static CATS_ACT_PTR PokeIconCharActorSet(POKE_GRA_TEST *pgt,int mons_no)
{
	u32 char_id;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	CATS_ACT_PTR cap;
	int monsno, tbl_no;
	
	if(client_type >= CLIENT_TYPE_A){
		tbl_no = client_type - CLIENT_TYPE_A;	//0originに修正
	}
	else{
		tbl_no = client_type;	//AA or BB
	}
	
	GF_ASSERT(bip->pokeicon_cap[tbl_no] == NULL);
	
	switch(client_type){	//戦闘入力画面では敵のみ表示
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		char_id = CHARID_POKEICON_COMMAND;
		break;
	case CLIENT_TYPE_B:
		char_id = CHARID_POKEICON_B;
		break;
	case CLIENT_TYPE_D:
		char_id = CHARID_POKEICON_D;
		break;
	default:
		GF_ASSERT(0 && "設定されていません");
		return NULL;
	}

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	//キャラリソース
	CATS_LoadResourceCharArc(csp, crp, ARC_POKEICON, PokeIconCgxArcIndexGetByPP(pp),
		0, NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	
	//アクター
	obj_param = PokeIconObjParam;
	obj_param.id[CLACT_U_CHAR_RES] = char_id;
	obj_param.x = PokeIconPos[tbl_no][0];
	obj_param.y = PokeIconPos[tbl_no][1];
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	//パレット切り替え
	monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	CLACT_PaletteOffsetChgAddTransPlttNo(cap->act, PokeIconPaletteIDGet(monsno));
	
	CATS_ObjectUpdateCap(cap);
	bip->pokeicon_cap[tbl_no] = cap;
	return cap;
}
#endif

#endif //PM_DEBUG
