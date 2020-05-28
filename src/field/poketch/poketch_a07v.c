//============================================================================================
/**
 * @file	poketch_a07v.c
 * @bfief	ポケッチ（アプリNo07: なつき度チェッカー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"

#include "system\lib_pack.h"
#include "poketool\pokeicon.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a07.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define POKEICON_CHAR_SIZE		(4*4*2)
#define POKEICON_CHAR_BYTESIZE	(POKEICON_CHAR_SIZE*0x20)
#define EFFECT_CHAR_OFS			(POKEICON_CHAR_SIZE*TEMOTI_POKEMAX)


enum {
	POKEICON_R = 16,
	POKEICON_R_FX32 = (POKEICON_R<<FX32_SHIFT),

	POKEICON_TOUCH_RANGE = 8,
	POKEICON_REACTION_RANGE = 48,
	POKEICON_REACTION_EX_RANGE = 64,

	AREA_L_LIMIT = (-10 * FX32_ONE),
	AREA_R_LIMIT = (217 << FX32_SHIFT),
	AREA_T_LIMIT = (-22 * FX32_ONE),
	AREA_B_LIMIT = (183 << FX32_SHIFT),

	EV_MAX_TIME = 16,

	ICONCTRL_RESET_TIMER = 6,

	
};

enum {
	OAMPRI_HEART,
	OAMPRI_ICON,
	OAMPRI_SHADOW,
};

enum {
	EFFANM_HEART1,
	EFFANM_HEART2,
	EFFANM_HEART3,
	EFFANM_SHADOW,
};

enum {
	PALPOS_EFFECT,
	PALPOS_ICON,	// アイコンはポケモンアイコンと同じだけ本数を使う
};

#ifdef PM_DEBUG
#define  RINGBUF_DEPTH		(64)
#endif



//==============================================================
// Work
//==============================================================
typedef  void (*pIconMoveFunc)(VIEWWORK*, int);


typedef struct {
	PACT*		act;
	PACT*		eff_act;

	VecFx32		vec;		// 移動量
	VecFx32		pos;		// 当たり判定位置
	VecFx32		add_pos;	// 当たり判定とは別に加算する

	u8  move_seq;
	u8  reaction_type;
	u8  reaction_level;
	u8  ref_timer;
	u8  reverse_NG;
	u8  touch_flag;
	u8  prev_pushed_flag;

	union {
		u32  work;
		u16  work_h[2];
		u8   work_q[4];
	};


}ICON_MOVE_PARAM;


struct _POKETCH_A07_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT_CLANM_PACK    icon_clpack;
	PACT_CLANM_PACK    eff_clpack;

/*
	PACT*              act[ TEMOTI_POKEMAX ];
	VecFx32            pos[ TEMOTI_POKEMAX ];
	VecFx32            vec[ TEMOTI_POKEMAX ];
*/

	VecFx32            next_pos[ TEMOTI_POKEMAX ];
	VecFx32            tmp;


	TCB_PTR				tcb;

	pIconMoveFunc		move_func[TEMOTI_POKEMAX];
	int					move_work[TEMOTI_POKEMAX];

	u32					icon_ctrl_seq;
	u32					icon_ctrl_timer;
	u32					touch_icon;
	u32					prev_touch_icon;
	u32					touch_count;
	BOOL				icon_touch_flag;
	BOOL				start_icon_touch_flag;

	u32					reset_icon_count;

	u32					icon_move_order[ TEMOTI_POKEMAX ];
	fx32				icon_move_ratio[ TEMOTI_POKEMAX ];

	ICON_MOVE_PARAM		icon[ TEMOTI_POKEMAX ];


	u32					tp_x;
	u32					tp_y;

};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void SetupPokeActor( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void ResetIconVector( VecFx32* vec );
static inline void UpdateIconDirection( ICON_MOVE_PARAM* icon );
static void SetupMoveTask( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void IconCtrlWorkInit( VIEWWORK* vwk );
static void ChangeIconCtrlSeq( VIEWWORK* vwk, int seq );
static void IconCtrlTask(TCB_PTR tcb, void* wk_ptr);
static u32 check_touch_icon( VIEWWORK* vwk );
static BOOL check_tp_range( u32 tp_x, u32 tp_y, u32 area_r, const VecFx32* pos );
static void set_icon_move_order( VIEWWORK* vwk );
static void IconCtrl_Start(VIEWWORK* vwk, const VIEWPARAM* vpara);
static void IconCtrl_TouchTrg(VIEWWORK* vwk, const VIEWPARAM* vpara);
static void IconCtrl_TouchCont(VIEWWORK* vwk, const VIEWPARAM* vpara);
static void IconCtrl_Release(VIEWWORK* vwk, const VIEWPARAM* vpara);
static void IconCtrl_Reset(VIEWWORK* vwk, const VIEWPARAM* vpara);
static void IconMoveFunc_Default( VIEWWORK* vwk, int p );
static void IconMoveFunc_Touch( VIEWWORK* vwk, int p );
static void debug_print( const char* fmt, ... );
static void IconBallMovePreProc( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void SetIconMoveSeq( VIEWWORK* vwk, int p, int seq );
static void SetIconMoveReset( VIEWWORK* vwk );
static BOOL WaitIconMoveReset( VIEWWORK* vwk );
static void disp_heart_actor( VIEWWORK* vwk, int p );
static void disp_shadow_actor( VIEWWORK* vwk, int p );
static void vanish_effect_actor( VIEWWORK* vwk, int p );
static void speed_adjust( fx32 max, u32 ratio, VecFx32* vec );
static BOOL is_speed_zero( const VecFx32* vec );
static void Bmv_Default( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void Bmv_ReactionLike( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void Bmv_ReactionHate( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void Bmv_Touch_Like( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void Bmv_Touch_Hate( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void Bmv_Reset( VIEWWORK* vwk, const VIEWPARAM* vpara, int p );
static void IconBallMoveProc( VIEWWORK* vwk, const VIEWPARAM* vpara );
static inline BOOL check_vector_zero( const VecFx32* vector );
static inline void reverse_vector( VecFx32* vector );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A07_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		int i;

		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();
		wk->tcb = NULL;

		for(i=0; i<TEMOTI_POKEMAX; i++)
		{
			wk->icon[i].act = NULL;
			wk->icon[i].eff_act = NULL;
		}

		PACT_TOOL_LoadCellDatas( &wk->icon_clpack, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );

		PACT_TOOL_LoadCellDatas( &wk->eff_clpack, ARC_POKETCH_IMG,
			NARC_poketch_natsuki_ncer,NARC_poketch_natsuki_nanr, POKETCH_APP_VIEW_HEAPID );


		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		確保したワークアドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A07_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		int i;
		for(i=0; i<TEMOTI_POKEMAX; i++)
		{
			if(wk->icon[i].act != NULL)
			{
				PACT_Del(wk->actsys, wk->icon[i].act);
			}
			if(wk->icon[i].eff_act != NULL)
			{
				PACT_Del(wk->actsys, wk->icon[i].eff_act);
			}
		}
		PACT_TOOL_UnloadCellDatas( &wk->icon_clpack );
		PACT_TOOL_UnloadCellDatas( &wk->eff_clpack );

		if(wk->tcb != NULL)
		{
			TCB_Delete(wk->tcb);
		}

		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ 0, NULL, 0 },
};


//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd		コマンド
 * @param   view_wk_adrs	ワーク領域アドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A07_SetViewCommand(VIEWWORK* wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store,
		POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単発）
 *
 * @param   cmd			コマンド
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A07_WaitViewCommand(VIEWWORK* wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A07_WaitViewCommandAll(VIEWWORK* wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}



//------------------------------------------------------------------
/**
 * コマンド削除
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK* cwk)
{
	VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_ptr)
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_simple_ncgr, vwk->bgl,
		USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, 0, 0, 0, 32, 24, USE_PALNO );
	PoketchView_SetBaseColorPalette(USE_PALNO,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	SetupPokeActor( vwk, vwk->vpara );

	SetupMoveTask( vwk, vwk->vpara );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

}

static void SetupPokeActor( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	static const struct {
		u16 x;
		u16 y;
	}IconDefaultPos[] = {
		{  48,  44 }, { 176,  44 },
		{  48,  92 }, { 176,  92 },
		{  48, 140 }, { 176, 140 },
	};

	ARCHANDLE* arcHandle;

	PoketchViewTool_SetupPokeIconPalette( PALPOS_ICON );
	ArcUtil_ObjCharSet( ARC_POKETCH_IMG, NARC_poketch_natsuki_ncgr, OBJTYPE_SUB, EFFECT_CHAR_OFS*0x20, 0, TRUE, HEAPID_POKETCH_APP );

	arcHandle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_POKETCH_APP );
	if( arcHandle )
	{
		PACT_ADD_PARAM   actparam;
		NNSG2dCharacterData* charData;
		void* charBuf;
		int i;

		actparam.anmseq = 0;
		actparam.flip = PACT_FLIP_OFF;
		actparam.bgpri = BGPRI2;
		actparam.affine_flag = TRUE;


		for(i=0; i<vpara->poke_count; i++)
		{
			charBuf = ArchiveDataLoadAllocByHandle( arcHandle, vpara->poke_param[i].imgArcIdx, HEAPID_POKETCH_APP );
			NNS_G2dGetUnpackedCharacterData( charBuf, &charData );
			DC_FlushRange( charData->pRawData, POKEICON_CHAR_BYTESIZE );
			GXS_LoadOBJ( charData->pRawData, POKEICON_CHAR_BYTESIZE*i, POKEICON_CHAR_BYTESIZE );
			sys_FreeMemoryEz(charBuf);

			actparam.pos.x = FX32INT(IconDefaultPos[i].x);
			actparam.pos.y = FX32INT(IconDefaultPos[i].y);

			actparam.oampri = OAMPRI_ICON;
			vwk->icon[i].act = PACT_Add( vwk->actsys, &actparam, &vwk->icon_clpack );
			PACT_SetCharOffset( vwk->icon[i].act, POKEICON_CHAR_SIZE*i );
			PACT_SetPalOffset( vwk->icon[i].act,
				PALPOS_ICON + PokeIconPalNumGet(vpara->poke_param[i].monsno, vpara->poke_param[i].form, FALSE ) );

			actparam.oampri = OAMPRI_HEART;
			vwk->icon[i].eff_act = PACT_Add( vwk->actsys, &actparam, &vwk->eff_clpack );
			if( vwk->icon[i].eff_act )
			{
				PACT_SetVanish( vwk->icon[i].eff_act, TRUE );
				PACT_SetCharOffset( vwk->icon[i].eff_act, EFFECT_CHAR_OFS );
				PACT_SetPalOffset( vwk->icon[i].eff_act, PALPOS_EFFECT );
			}
			else
			{
				GF_ASSERT(0);
			}

			vwk->icon[i].reverse_NG = PokePersonalParaGet( vpara->poke_param[i].monsno, ID_PER_reverse );
			vwk->icon[i].touch_flag = FALSE;
			vwk->icon[i].prev_pushed_flag = FALSE;

			VEC_Set( &vwk->icon[i].pos, actparam.pos.x, actparam.pos.y, 0 );
			VEC_Set( &vwk->icon[i].add_pos, 0, 0, 0 );
		}


		ArchiveDataHandleClose( arcHandle );
	}
}

//------------------------------------------------------------------
/**
 * アイコン移動量をリセット（ランダム）
 *
 * @param   vec		
 *
 */
//------------------------------------------------------------------
static void ResetIconVector( VecFx32* vec )
{
	fx32 vx, vy;

	vx = ((-32) + (gf_mtRand()& 63)) * FX32_ONE;
	vy = ((-32) + (gf_mtRand()& 63)) * FX32_ONE;

	VEC_Set( vec, vx, vy, 0 );
	VEC_Normalize( vec, vec );

	vec->x /= EV_MAX_TIME;
	vec->y /= EV_MAX_TIME;
}


static inline void UpdateIconDirection( ICON_MOVE_PARAM* icon )
{
	if( icon->reverse_NG )
	{
		PACT_ChangeAnmSeq( icon->act, POKEICON_ANM_NORMAL_L );
	}
	else
	{
		PACT_ChangeAnmSeq( icon->act, (icon->vec.x > 0)? POKEICON_ANM_NORMAL_R : POKEICON_ANM_NORMAL_L );
	}
}


static void SetupMoveTask( VIEWWORK* vwk, const VIEWPARAM* vpara )
{

	int i;
	for(i=0; i<vpara->poke_count; i++)
	{
		// 移動用vectorを作っておく
		ResetIconVector( &vwk->icon[i].vec );
		UpdateIconDirection( &vwk->icon[i] );
	}

	IconCtrlWorkInit( vwk );
	vwk->tcb = TCB_Add( IconCtrlTask, vwk, POKETCH_APP_TASKPRI );

}
//------------------------------------------------------------------
/**
 * コマンド：終了処理
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdQuit(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}


enum {
	ICONCTRL_START,
	ICONCTRL_TOUCH_TRG,
	ICONCTRL_TOUCH_CONT,
	ICONCTRL_RELEASE,
	ICONCTRL_RESET,
};


static void IconCtrlWorkInit( VIEWWORK* vwk )
{
	int i;

	vwk->icon_ctrl_seq = ICONCTRL_START;

	for(i=0; i<vwk->vpara->poke_count; i++)
	{
		vwk->icon[i].move_seq = 0;
		vwk->icon[i].ref_timer = 0;
	}

	vwk->touch_icon = vwk->vpara->poke_count;
	vwk->prev_touch_icon = vwk->touch_icon;
}

static void ChangeIconCtrlSeq( VIEWWORK* vwk, int seq )
{
	vwk->icon_ctrl_seq = seq;
	vwk->icon_ctrl_timer = 0;
}

//------------------------------------------------------------------
/**
 * アイコンコントロールタスク：初期時
 *
 * @param   tcb		
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
static void IconCtrlTask(TCB_PTR tcb, void* wk_ptr)
{
	static void (* const func[])(VIEWWORK*, const VIEWPARAM*) = {
		IconCtrl_Start,
		IconCtrl_TouchTrg,
		IconCtrl_TouchCont,
		IconCtrl_Release,
		IconCtrl_Reset,
	};
	VIEWWORK* vwk = wk_ptr;
	const VIEWPARAM* vpara = vwk->vpara;
	int i;

	if( vpara->tp_cont )
	{
		vwk->tp_x = vpara->tp_x;
		vwk->tp_y = vpara->tp_y - 8;	// １キャラ下げて描いてる分をここで吸収

		vwk->touch_icon = check_touch_icon( vwk );
		vwk->icon_touch_flag = (vwk->touch_icon < vpara->poke_count );

		if( vwk->icon_touch_flag && (vwk->touch_icon != vwk->prev_touch_icon) )
		{
			PoketchVoicePlay( vpara->poke_param[ vwk->touch_icon ].monsno );
		}
		vwk->prev_touch_icon = vwk->touch_icon;
	}
	else
	{
		vwk->icon_touch_flag = FALSE;
		vwk->prev_touch_icon = vpara->poke_count;
	}

	func[ vwk->icon_ctrl_seq ]( vwk, vpara );

	IconBallMovePreProc( vwk, vpara );

	if( vwk->icon_ctrl_seq != ICONCTRL_RESET )
	{
		IconBallMoveProc( vwk, vpara );
	}
}


static u32 check_touch_icon( VIEWWORK* vwk )
{
	int i;
	int x, y;

	for(i=0; i<vwk->vpara->poke_count; i++)
	{
		x = vwk->icon[i].pos.x >> FX32_SHIFT;
		y = vwk->icon[i].pos.y >> FX32_SHIFT;
		x = (vwk->tp_x - x) * (vwk->tp_x - x);
		y = (vwk->tp_y - y) * (vwk->tp_y - y);

		if( (x+y) < (POKEICON_R*POKEICON_R) )
		{
			return i;
		}
	}

	return vwk->vpara->poke_count;
}

// タッチされている位置の有効範囲内にいるか？
static BOOL check_tp_range( u32 tp_x, u32 tp_y, u32 area_r, const VecFx32* pos )
{
	int x, y;
	int area;

	tp_x <<= FX32_SHIFT;
	tp_y <<= FX32_SHIFT;

	x = tp_x - pos->x;
	y = tp_y - pos->y;

	x = (x >> FX32_SHIFT) * x;
	y = (y >> FX32_SHIFT) * y;

	area = (s64)(area_r * area_r) << FX32_SHIFT;

	if( area > (x+y) )
	{
		return TRUE;
	}

	return FALSE;
}


static void set_icon_move_order( VIEWWORK* vwk )
{
	int i;
	for(i=0; i<vwk->vpara->poke_count; i++)
	{
		vwk->icon_move_order[i] = i;
	}
}


static void IconCtrl_Start(VIEWWORK* vwk, const VIEWPARAM* vpara)
{
	if( vpara->tp_trg )
	{
		vwk->start_icon_touch_flag = vwk->icon_touch_flag;
		ChangeIconCtrlSeq( vwk, ICONCTRL_TOUCH_TRG );
	}
}

static void IconCtrl_TouchTrg(VIEWWORK* vwk, const VIEWPARAM* vpara)
{
	if( vpara->tp_cont )
	{
		vwk->icon_ctrl_timer++;
		if( vwk->icon_ctrl_timer > ICONCTRL_RESET_TIMER )
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_TOUCH_CONT );
		}
	}
	else
	{
		if( vwk->start_icon_touch_flag )
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_START );
		}
		else
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_RELEASE );
		}
	}
}

static void IconCtrl_TouchCont(VIEWWORK* vwk, const VIEWPARAM* vpara)
{
	if( vpara->tp_cont == FALSE)
	{
		ChangeIconCtrlSeq( vwk, ICONCTRL_START );
	}
}

static void IconCtrl_Release(VIEWWORK* vwk, const VIEWPARAM* vpara)
{
	if( vpara->tp_trg == FALSE )
	{
		vwk->icon_ctrl_timer++;
		if( vwk->icon_ctrl_timer > ICONCTRL_RESET_TIMER )
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_START );
		}
	}
	else
	{
		if( vwk->icon_touch_flag )
		{
			vwk->start_icon_touch_flag = TRUE;
			ChangeIconCtrlSeq( vwk, ICONCTRL_TOUCH_TRG  );
		}
		else
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_RESET  );
		}
	}
}

static void IconCtrl_Reset(VIEWWORK* vwk, const VIEWPARAM* vpara)
{
	if( vwk->icon_ctrl_timer == 0 )
	{
		SetIconMoveReset( vwk );
		vwk->icon_ctrl_timer++;
	}
	else
	{
		if( WaitIconMoveReset( vwk ) )
		{
			ChangeIconCtrlSeq( vwk, ICONCTRL_START  );
		}
	}
}






static void IconMoveFunc_Default( VIEWWORK* vwk, int p )
{
	VEC_Add( &vwk->icon[p].pos, &vwk->icon[p].vec, &vwk->icon[p].pos );

	if( ( vwk->icon[p].pos.x > AREA_R_LIMIT )
	||	( vwk->icon[p].pos.x < AREA_L_LIMIT )
	){
		vwk->icon[p].vec.x *= -1;
		UpdateIconDirection( &vwk->icon[p] );
	}
	if( ( vwk->icon[p].pos.y > AREA_B_LIMIT )
	||	( vwk->icon[p].pos.y < AREA_T_LIMIT )
	){
		vwk->icon[p].vec.y *= -1;
	}

	PACT_SetPos( vwk->icon[p].act, vwk->icon[p].pos.x, vwk->icon[p].pos.y );
}

static void IconMoveFunc_Touch( VIEWWORK* vwk, int p )
{
	
}






static void debug_print( const char* fmt, ... )
{
	if( sys.cont & PAD_BUTTON_B )
	{
		va_list vlist;

		va_start(vlist, fmt);
		OS_TVPrintf( fmt, vlist );
		va_end(vlist);
	}
}




//==============================================================================================
// ビリヤード球みたいな動き
//==============================================================================================
enum {
	BMV_DEFAULT,
	BMV_REACTION_LIKE,
	BMV_REACTION_HATE,
	BMV_TOUCH_LIKE,
	BMV_TOUCH_HATE,
	BMV_RESET,
};



enum {
	DEFAULT_MAX_SPEED = (FX32_ONE * 3) / EV_MAX_TIME,
	REACTION_MAX_SPEED = (FX32_ONE * 6) / EV_MAX_TIME,
};

static void IconBallMovePreProc( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	static  void (* const func_tbl[])(VIEWWORK* vwk, const VIEWPARAM* vpara, int) = {
		Bmv_Default,
		Bmv_ReactionLike,
		Bmv_ReactionHate,
		Bmv_Touch_Like,
		Bmv_Touch_Hate,
		Bmv_Reset,
	};
	int i;
	for(i=0; i<vpara->poke_count; i++)
	{
		if( vwk->icon[i].ref_timer )
		{
			vwk->icon[i].ref_timer--;
			debug_print("icon[%d] REF[%d]\n", i, vwk->icon[i].ref_timer);
		}
		else
		{
			func_tbl[ vwk->icon[i].move_seq ]( vwk, vpara, i );
		}
	}
	
	debug_print("------------\n");
}
//------------------------------------------------------------------
/**
 * アイコン動作セット
 *
 * @param   vwk		
 * @param   p		
 * @param   func		
 *
 */
//------------------------------------------------------------------
static void SetIconMoveSeq( VIEWWORK* vwk, int p, int seq )
{
	/* 前処理 */
	switch( vwk->icon[p].move_seq ){
	case BMV_TOUCH_LIKE:
		vanish_effect_actor( vwk, p );
		break;
	}

	vwk->icon[p].move_seq = seq;
	vwk->icon[p].work = 0;
	VEC_Set( &vwk->icon[p].add_pos, 0, 0, 0 );


	/* 後処理 */
	switch( vwk->icon[p].move_seq ){
	case BMV_TOUCH_LIKE:
		disp_heart_actor( vwk, p );
		break;
	}

}

static void SetIconMoveReset( VIEWWORK* vwk )
{
	int i;

	for(i=0; i<vwk->vpara->poke_count; i++)
	{
		SetIconMoveSeq( vwk, i, BMV_RESET );
		vwk->icon[i].ref_timer = 0;
	}

	vwk->reset_icon_count = vwk->vpara->poke_count;
}


static BOOL WaitIconMoveReset( VIEWWORK* vwk )
{
	return (vwk->reset_icon_count == 0);
}




static void disp_heart_actor( VIEWWORK* vwk, int p )
{
	if( vwk->vpara->poke_param[p].reaction_type == REACTION_LIKE )
	{
		PACT_SetOamPri( vwk->actsys, vwk->icon[p].eff_act, OAMPRI_HEART );
		PACT_ChangeAnmSeq( vwk->icon[p].eff_act, EFFANM_HEART1 + (vwk->vpara->poke_param[p].reaction_level-1) );
		PACT_SetVanish( vwk->icon[p].eff_act, FALSE );
	}
}

static void disp_shadow_actor( VIEWWORK* vwk, int p )
{
	PACT_SetOamPri( vwk->actsys, vwk->icon[p].eff_act, OAMPRI_SHADOW );
	PACT_ChangeAnmSeq( vwk->icon[p].eff_act, EFFANM_SHADOW );
	PACT_SetVanish( vwk->icon[p].eff_act, FALSE );
}

static void vanish_effect_actor( VIEWWORK* vwk, int p )
{
	PACT_SetVanish( vwk->icon[p].eff_act, TRUE );
}


static void speed_adjust( fx32 max, u32 ratio, VecFx32* vec )
{
	fx32 speed = VEC_Mag(vec);

	if( speed > max )
	{
		VecFx32 norm_vec;

//		OS_TPrintf("sp %d, ", speed);
		speed = (speed * ratio) / 100;

//		OS_TPrintf("  %d, ", speed);

		VEC_Normalize( vec, &norm_vec );
		VEC_Set( vec, 0, 0, 0 );
		VEC_MultAdd( speed, &norm_vec, vec, vec );

	//-------------------------------
//		speed = VEC_Mag( vec );
//		OS_TPrintf("  %d\n", speed);

	}
}

static BOOL is_speed_zero( const VecFx32* vec )
{
	return ( (vec->x == 0) && (vec->y == 0) );
}

static void Bmv_Default( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	debug_print(" icon[%d] Default\n", p );
	if( vpara->tp_cont == FALSE )
	{
		speed_adjust( DEFAULT_MAX_SPEED, 96, &vwk->icon[p].vec );
	}
	else
	{
		if( vwk->icon_touch_flag == FALSE )
		{
			if( check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_REACTION_RANGE, &vwk->icon[p].pos) )
			{
				if( vpara->poke_param[p].reaction_type != REACTION_HATE )
				{
					SetIconMoveSeq( vwk, p, BMV_REACTION_LIKE );
					Bmv_ReactionLike( vwk, vpara, p );
				}
				else
				{
					SetIconMoveSeq( vwk, p, BMV_REACTION_HATE );
					Bmv_ReactionHate( vwk, vpara, p );
				}
			}
		}

		else if( vwk->touch_icon == p )
		{
			if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_TOUCH_RANGE, &vwk->icon[p].pos))
			{
				if( vpara->poke_param[p].reaction_type != REACTION_HATE )
				{
					SetIconMoveSeq( vwk, p, BMV_TOUCH_LIKE );
				}
				else
				{
					SetIconMoveSeq( vwk, p, BMV_TOUCH_HATE );
				}
			}

		}

	}
}
static void Bmv_ReactionLike( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	debug_print(" icon[%d] ReaLike\n", p );

	if(	vpara->tp_cont 
	&&	check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_REACTION_EX_RANGE, &vwk->icon[p].pos)
	){
		static const u8 ratio [] = {
			100, 150, 175, 200 
		};

		if( (vwk->icon_touch_flag == FALSE)
		||	(vwk->touch_icon == p )
		){

			if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_TOUCH_RANGE, &vwk->icon[p].pos))
			{
				SetIconMoveSeq( vwk, p, BMV_TOUCH_LIKE );
			}
			else
			{
				VecFx32 tpp;


				VEC_Set(&tpp, vwk->tp_x<<FX32_SHIFT, vwk->tp_y<<FX32_SHIFT, 0);
				VEC_Subtract( &tpp, &vwk->icon[p].pos, &tpp );
				VEC_Normalize( &tpp, &tpp );
				tpp.x = (tpp.x * ratio[ vpara->poke_param[p].reaction_level] ) / 100;
				tpp.y = (tpp.y * ratio[ vpara->poke_param[p].reaction_level] ) / 100;
				tpp.x /= EV_MAX_TIME;
				tpp.y /= EV_MAX_TIME;
				vwk->icon[p].vec = tpp;
	//			VEC_Add( &tpp, &vwk->icon[p].vec, &vwk->icon[p].vec );
	//			VEC_Normalize( &vwk->icon[p].vec, &vwk->icon[p].vec );
	//			VEC_MultAdd( ratio[vpara->poke_param[p].reaction_level], &tpp, &vwk->icon[p].vec, &vwk->icon[p].vec );
			}
		}
	}
	else
	{
		SetIconMoveSeq( vwk, p, BMV_DEFAULT );
	}
}
static void Bmv_ReactionHate( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	debug_print(" icon[%d] ReaHate\n", p );

	if(	vpara->tp_cont 
	&&	check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_REACTION_EX_RANGE, &vwk->icon[p].pos)
	){
		static const u8 ratio [] = {
			100, 150, 175, 200 
		};
		VecFx32 tpp;

		VEC_Set(&tpp, vwk->tp_x<<FX32_SHIFT, vwk->tp_y<<FX32_SHIFT, 0);
		VEC_Subtract( &vwk->icon[p].pos, &tpp, &tpp );
		VEC_Normalize( &tpp, &tpp );
		tpp.x = (tpp.x * ratio[ vpara->poke_param[p].reaction_level] ) / 100;
		tpp.y = (tpp.y * ratio[ vpara->poke_param[p].reaction_level] ) / 100;
		tpp.x /= EV_MAX_TIME;
		tpp.y /= EV_MAX_TIME;
		vwk->icon[p].vec = tpp;
	}
	else
	{
		SetIconMoveSeq( vwk, p, BMV_DEFAULT );
	}
}


static void Bmv_Touch_Like( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	debug_print(" icon[%d] TcgLike\n", p );

	// タッチパネル接触有り
	if(vpara->tp_cont)
	{
		VecFx32 tpp;

		VEC_Set(&tpp, vwk->tp_x<<FX32_SHIFT, vwk->tp_y<<FX32_SHIFT, 0);

		// まだタッチポイントに触れている範囲
		if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_TOUCH_RANGE, &vwk->icon[p].pos))
		{
			VEC_Subtract( &tpp, &vwk->icon[p].pos, &tpp );

			if( VEC_Mag(&tpp) > REACTION_MAX_SPEED )
			{
				VecFx32 dmy;
				VEC_Normalize(&tpp, &tpp);
				tpp.x *= ( REACTION_MAX_SPEED >> FX32_SHIFT );
				tpp.y *= ( REACTION_MAX_SPEED >> FX32_SHIFT );
			}
			tpp.x /= EV_MAX_TIME;
			tpp.y /= EV_MAX_TIME;
			vwk->icon[p].vec = tpp;

			return;
		}
		// まだ反応できる範囲
		else if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_REACTION_EX_RANGE, &vwk->icon[p].pos))
		{
			SetIconMoveSeq( vwk, p, BMV_REACTION_LIKE );
			return;
		}
	}

//	ResetIconVector( &vwk->icon[p].vec );
	SetIconMoveSeq( vwk, p, BMV_DEFAULT );
}
static void Bmv_Touch_Hate( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	debug_print(" icon[%d] TchHate\n", p );

	// タッチパネル接触有り
	if(vpara->tp_cont)
	{
		VecFx32 tpp;

		VEC_Set(&tpp, vwk->tp_x<<FX32_SHIFT, vwk->tp_y<<FX32_SHIFT, 0);

		// まだタッチポイントに触れている範囲
		if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_TOUCH_RANGE, &vwk->icon[p].pos))
		{
			VEC_Set( &vwk->icon[p].vec, 0, 0, 0 );
			return;
		}
		// まだ反応できる範囲
		else if(check_tp_range(vwk->tp_x, vwk->tp_y, POKEICON_REACTION_EX_RANGE, &vwk->icon[p].pos))
		{
			SetIconMoveSeq( vwk, p, BMV_REACTION_HATE );
			return;
		}
	}
	else
	{
		if( is_speed_zero( &vwk->icon[p].vec ) )
		{
			ResetIconVector( &vwk->icon[p].vec );
		}
	}

	SetIconMoveSeq( vwk, p, BMV_DEFAULT );
}

static void Bmv_Reset( VIEWWORK* vwk, const VIEWPARAM* vpara, int p )
{
	enum {
		JUMP_HEIGHT = -20,
	};
	ICON_MOVE_PARAM* icon = &vwk->icon[p];

	debug_print(" icon[%d] Reset!!\n", p );

	switch(icon->work_q[0]){
	case 0:
		VEC_Set( &icon->vec, 0, 0, 0 );
		disp_shadow_actor( vwk, p );
		PoketchSePlay( POKETCH_SE_NATSUKI_JUMP );
		icon->work_q[0]++;
		/* fallthru */
	case 1:
		icon->work_q[1] += 8;

		if( icon->work_q[2] == 0 )
		{
			if( icon->work_q[1] > 140 )
			{
				vanish_effect_actor( vwk, p );
				icon->work_q[2] = 1;
			}
		}
		if( icon->work_q[1] > 180 )
		{
			icon->work_q[1] = 180;
			icon->work_q[2] = 2;
		}

		VEC_Set( &icon->add_pos, 0, JUMP_HEIGHT*Sin360(icon->work_q[1]), 0 );
		VEC_Add( &icon->pos, &icon->add_pos, &vwk->tmp );
		PACT_SetPos( icon->act, vwk->tmp.x, vwk->tmp.y );
		PACT_SetPos( icon->eff_act, icon->pos.x, icon->pos.y + (8<<FX32_SHIFT));

		if( icon->work_q[2] == 2 )
		{
			ResetIconVector( &icon->vec );
			SetIconMoveSeq( vwk, p, BMV_DEFAULT );
			vwk->reset_icon_count--;
		}
		break;
	}
}



static void IconBallMoveProc( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	enum {
		EVTYPE_NONE = 0,
		EVTYPE_HIT_ICON,
		EVTYPE_HIT_LEFT,
		EVTYPE_HIT_RIGHT,
		EVTYPE_HIT_TOP,
		EVTYPE_HIT_BOTTOM,
	};


	VecFx32 relative_pos;
	fx32 ev_time, ev_all_time;
	fx32 icon_distance;
	int ev_pos1, ev_pos2, ev_type, i, j;

	VecFx32  norm_pos, relative_vec;
	fx32     relative_speed, ov_time;

	ev_all_time = EV_MAX_TIME << FX32_SHIFT;

	do {
		ev_time = ev_all_time;
		ev_type = EVTYPE_NONE;


		// 何も接触イベントが発生しなかった場合の次フレーム位置
		for(i=0; i<vpara->poke_count; i++)
		{
			VEC_MultAdd( ev_time, &vwk->icon[i].vec, &vwk->icon[i].pos, &vwk->next_pos[i] );
		}

		// 壁への接触判定
		for(i=0; i<vpara->poke_count; i++)
		{
			// 左壁
			if( (vwk->next_pos[i].x < AREA_L_LIMIT) && (vwk->icon[i].vec.x != 0) )
			{
				fx32 ov_time = ev_time - ((vwk->next_pos[i].x - AREA_L_LIMIT) / vwk->icon[i].vec.x);
				if( ov_time < ev_time )
				{
					ev_type = EVTYPE_HIT_LEFT;
					ev_pos1 = i;
					ev_time = ov_time;
				}
			}
			// 右壁
			if( (vwk->next_pos[i].x > AREA_R_LIMIT) && (vwk->icon[i].vec.x != 0) )
			{
				fx32 ov_time = ev_time - ((vwk->next_pos[i].x - AREA_R_LIMIT) / vwk->icon[i].vec.x);
				if( ov_time < ev_time )
				{
					ev_type = EVTYPE_HIT_RIGHT;
					ev_pos1 = i;
					ev_time = ov_time;
				}
			}
			// 上壁
			if( (vwk->next_pos[i].y < AREA_T_LIMIT) && (vwk->icon[i].vec.y != 0) )
			{
				fx32 ov_time = ev_time - ((vwk->next_pos[i].y - AREA_T_LIMIT) / vwk->icon[i].vec.y);
				if( ov_time < ev_time )
				{
					ev_type = EVTYPE_HIT_TOP;
					ev_pos1 = i;
					ev_time = ov_time;
				}
			}
			// 下壁
			if( (vwk->next_pos[i].y > AREA_B_LIMIT) && (vwk->icon[i].vec.y != 0) )
			{
				fx32 ov_time = ev_time - ((vwk->next_pos[i].y - AREA_B_LIMIT) / vwk->icon[i].vec.y);
				if( ov_time < ev_time )
				{
					ev_type = EVTYPE_HIT_BOTTOM;
					ev_pos1 = i;
					ev_time = ov_time;
				}
			}
		}

		// アイコン同士の接触
		for(j=0; j<vpara->poke_count; j++)
		{
			for(i=0; i<j; i++)
			{
				// 相対位置を計算
				VEC_Subtract( &vwk->next_pos[i], &vwk->next_pos[j], &relative_pos );

				// アイコンの中心間距離を計算（２Ｒ以下なら衝突してる）
				icon_distance = VEC_Mag( &relative_pos );
				if( icon_distance < (2*POKEICON_R_FX32) )
				{
					// 相対位置の単位ベクトル
					VEC_Normalize( &relative_pos, &norm_pos );

					// 相対速度
					VEC_Subtract( &vwk->icon[i].vec, &vwk->icon[j].vec, &relative_vec );

					// アイコン中心同士を結んだ座標軸での相対速度
					relative_speed = VEC_DotProduct( &relative_vec, &norm_pos );
					// 接触の瞬間から動いた時間
					ov_time = ev_time - ((2*POKEICON_R_FX32 - icon_distance) / -relative_speed);
					if( ov_time < ev_time )
					{
						ev_type = EVTYPE_HIT_ICON;
						ev_pos1 = i;
						ev_pos2 = j;
						ev_time = ov_time;
					}
				}
			}
		}

		// 次の接触イベント発生まで位置を更新
		//（計算誤差により次イベントまでの時間が完全にゼロになることがあるので、強制的に最小値を入れる）
		if( ev_time <= 0 )
		{
			break;
//			ev_time = 1;
		}
		for(i=0; i<vpara->poke_count; i++)
		{
			VEC_MultAdd( ev_time, &vwk->icon[i].vec, &vwk->icon[i].pos, &vwk->icon[i].pos );
		}

		// 接触イベント処理
		switch( ev_type ){
		case EVTYPE_HIT_ICON:
			{
				if( vwk->icon[ev_pos1].move_seq == BMV_TOUCH_LIKE )
				{
					VecFx32* vec = &vwk->icon[ev_pos2].vec;
					if( check_vector_zero(vec) || vwk->icon[ev_pos2].prev_pushed_flag )
					{
						// 相対位置
						VEC_Subtract( &vwk->icon[ev_pos2].pos, &vwk->icon[ev_pos1].pos, &relative_pos );
						VEC_Normalize( &relative_pos, &norm_pos );
						vec->x = FX_Mul(norm_pos.x, FX32_CONST(0.1f));
						vec->y = FX_Mul(norm_pos.y, FX32_CONST(0.1f));
						vwk->icon[ev_pos2].prev_pushed_flag = TRUE;
						if( ((ev_pos1==1)&&(ev_pos2==2)) || ((ev_pos2==1)&&(ev_pos1==2)) ){ OS_TPrintf("PTN A  x:%d, y:%d\n", vec->x, vec->y); }
					}
					else
					{
						reverse_vector( vec );
						if( ((ev_pos1==1)&&(ev_pos2==2)) || ((ev_pos2==1)&&(ev_pos1==2)) ){ OS_TPrintf("PTN B\n"); }
					}
					vwk->icon[ev_pos2].ref_timer = 20;
				}
				else if( vwk->icon[ev_pos2].move_seq == BMV_TOUCH_LIKE )
				{
					VecFx32* vec = &vwk->icon[ev_pos1].vec;
					if( check_vector_zero(vec) || vwk->icon[ev_pos1].prev_pushed_flag )
					{
						VEC_Subtract( &vwk->icon[ev_pos1].pos, &vwk->icon[ev_pos2].pos, &relative_pos );
						VEC_Normalize( &relative_pos, &norm_pos );
						vec->x = FX_Mul(norm_pos.x, FX32_CONST(0.1f));
						vec->y = FX_Mul(norm_pos.y, FX32_CONST(0.1f));
						vwk->icon[ev_pos1].prev_pushed_flag = TRUE;
						if( ((ev_pos1==1)&&(ev_pos2==2)) || ((ev_pos2==1)&&(ev_pos1==2)) ){ OS_TPrintf("PTN C  x:%d y:%d\n", vec->x, vec->y); }
					}
					else
					{
						reverse_vector(vec);
						if( ((ev_pos1==1)&&(ev_pos2==2)) || ((ev_pos2==1)&&(ev_pos1==2)) ){ OS_TPrintf("PTN D\n"); }
					}
					vwk->icon[ev_pos1].ref_timer = 20;
				}
				else
				{
					// 相対位置
					VEC_Subtract( &vwk->icon[ev_pos1].pos, &vwk->icon[ev_pos2].pos, &relative_pos );
					// 中心距離
					icon_distance = VEC_Mag( &relative_pos );
					// 相対位置の単位ベクトル
					VEC_Normalize( &relative_pos, &norm_pos );
					// 相対速度
					VEC_Subtract( &vwk->icon[ev_pos1].vec, &vwk->icon[ev_pos2].vec, &relative_vec );
					// アイコン中心同士を結んだ座標軸での相対速度
					relative_speed = VEC_DotProduct( &relative_vec, &norm_pos );
					// 反射計算
					VEC_MultAdd(-relative_speed, &norm_pos, &vwk->icon[ev_pos1].vec, &vwk->icon[ev_pos1].vec);
					VEC_MultAdd( relative_speed, &norm_pos, &vwk->icon[ev_pos2].vec, &vwk->icon[ev_pos2].vec);
					vwk->icon[ev_pos1].ref_timer = 20;
					vwk->icon[ev_pos2].ref_timer = 20;
					vwk->icon[ev_pos1].prev_pushed_flag = FALSE;
					vwk->icon[ev_pos2].prev_pushed_flag = FALSE;
					if( ((ev_pos1==1)&&(ev_pos2==2)) || ((ev_pos2==1)&&(ev_pos1==2)) ){ OS_TPrintf("PTN E\n"); }
				}
			}
			break;


		case EVTYPE_HIT_LEFT:
		case EVTYPE_HIT_RIGHT:
			vwk->icon[ev_pos1].vec.x *= -1;
			vwk->icon[ev_pos1].prev_pushed_flag = FALSE;
			break;

		case EVTYPE_HIT_TOP:
		case EVTYPE_HIT_BOTTOM:
			vwk->icon[ev_pos1].vec.y *= -1;
			vwk->icon[ev_pos1].prev_pushed_flag = FALSE;
			break;
		}

		ev_all_time -= ev_time;

	}while( ev_type != EVTYPE_NONE );


	for(i=0; i<vpara->poke_count; i++)
	{
		if( vwk->icon[i].move_seq < BMV_TOUCH_LIKE )
		{
			UpdateIconDirection( &vwk->icon[i] );
		}
		VEC_Add( &vwk->icon[i].pos, &vwk->icon[i].add_pos, &vwk->tmp );
		PACT_SetPos(vwk->icon[i].act, vwk->tmp.x, vwk->tmp.y);
		PACT_SetPos(vwk->icon[i].eff_act, vwk->icon[i].pos.x, vwk->icon[i].pos.y + (8<<FX32_SHIFT));
	}

}


static inline BOOL check_vector_zero( const VecFx32* vector )
{
	return ((vector->x == 0) && (vector->y ==0));
}

static inline void reverse_vector( VecFx32* vector )
{
	vector->x *= -1;
	vector->y *= -1;
}

