//==============================================================================
/**
 * @file	egg_disp.c
 * @brief	画面周りのシステム
 * @author	goto
 * @date	2006.05.20(土)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"

#include "system/bmp_menu.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"
#include "include/system/wordset.h"

#include "msgdata/msg.naix"

#include "demo/egg/data/egg_data_def.h"
#include "demo/egg/data/particle/egg_demo_setup.h"
#include "src/field/poketch/poketch_arc.h"

#include "battle/battle_common.h"
#include "wazaeffect/wazatool.h"
#include "wazaeffect/we_def.h"

#include "system/wipe.h"

#include "shinka_def.h"

#define SHINKA_DEMO_NEAR		(FX32_ONE)			///< カメラ
#define SHINKA_DEMO_FAR			(FX32_ONE * 900)

// =============================================================================
//
//
//	プロトタイプ宣言
//
//
// =============================================================================
void				ShinkaDisp_SystemInit(void);
void				ShinkaDisp_DefaultBlendSet(void);
GF_G3DMAN			*ShinkaDisp_3D_Init(int heapID);
void				ShinkaDisp_3DSetUp(void);
void				ShinkaDisp_3DVramInit(void);
void				ShinkaDisp_ParticleMain(void);
SHINKA_PARTICLE_SYS	*ShinkaParticle_Init(SHINKA_PARTICLE_PARAM* param);
void				ShinkaParticle_SprSet(SHINKA_PARTICLE_SYS* sps, int no);
BOOL				ShinkaParticle_Main(SHINKA_PARTICLE_SYS* sps);
void				ShinkaParticle_End(SHINKA_PARTICLE_SYS* sps);

static	u32			sAllocTex(u32 size, BOOL is4x4comp);
static	u32			sAllocTexPalette(u32 size, BOOL is4pltt);
static	PTC_PTR		ShinkaParticle_SystemSet(int heap_id);
static	PTC_PTR		ShinkaParticle_PtcInit(int heap_id, int arc_id, int data_no);
static	void		ShinkaParticle_PtcExit(PTC_PTR ptc);
static	void		ShinkaParticle_CallBack(EMIT_PTR emit);

// =============================================================================
//
//
//	□ 描画システム関連
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	システム初期化
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_SystemInit(void)
{
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);	
}

//--------------------------------------------------------------
/**
 * @brief	基本α設定
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_DefaultBlendSet(void)
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					 GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3, 11, 7);
	G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					  GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 |
					  GX_BLEND_PLANEMASK_BG3, 7, 8);
}

//--------------------------------------------------------------
/**
 * @brief	3D初期化
 *
 * @param	none	
 *
 * @retval	GF_G3DMAN*	
 *
 */
//--------------------------------------------------------------
GF_G3DMAN* ShinkaDisp_3D_Init(int heapID)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(heapID,
							GF_G3DMAN_LNK,
							GF_G3DTEX_256K, 
							GF_G3DMAN_LNK,
							GF_G3DPLT_32K,
							ShinkaDisp_3DSetUp);
	
	return g3Dman;	
}

//--------------------------------------------------------------
/**
 * @brief	3Dセットアップ
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_3DSetUp(void)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );
	G3X_AlphaBlend( TRUE );
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

    G3_ViewPort(0, 0, 255, 191);
}

//--------------------------------------------------------------
/**
 * @brief	3DVram初期化
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_3DVramInit(void)
{
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	tex_key		= NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key	= NNS_GfdAllocPlttVram(0x20 *(CLIENT_MAX+1), 0, 0);
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	
	tex_addrs	= NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs	= NNS_GfdGetPlttKeyAddr(pltt_key);
	
	OS_TPrintf("ポケモン用に確保した テクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("ポケモン用に確保した 　パレットVramの先頭アドレス＝%d\n", pltt_addrs);

	Particle_SystemWorkInit();		
}

//--------------------------------------------------------------
/**
 * @brief	パーティクルメイン
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_ParticleMain(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;

	GF_G3X_Reset();

	draw_num = Particle_DrawAll();

	if(draw_num > 0){
		GF_G3X_Reset();
		NNS_G2dSetupSoftwareSpriteCamera();
	}

	Particle_CalcAll();
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
}

#if 0
//--------------------------------------------------------------
/**
 * @brief	ワイプフェードイン
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_WipeFadeIn(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
				   WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
				   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_EGG_DEMO);
}

//--------------------------------------------------------------
/**
 * @brief	ワイプフェードアウト
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaDisp_WipeFadeOut(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
			   	   WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
			   	   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_EGG_DEMO);
}
#endif

// =============================================================================
//
//
//	□ パーティクル
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	領域確保
 *
 * @param	size	
 * @param	is4x4comp	
 *
 * @retval	static u32	
 *
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
	NNSGfdTexKey key;
	u32 address;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	Particle_LnkTexKeySet(key);		//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("テクスチャVramアドレス＝%#x\n", address);
	return address;
}


//--------------------------------------------------------------
/**
 * @brief	領域確保
 *
 * @param	size	
 * @param	is4pltt	
 *
 * @retval	static u32	
 *
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	Particle_PlttLnkTexKeySet(key);	//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_Printf("パレットVramアドレス＝%#x\n", address);
	return address;
}


//--------------------------------------------------------------
/**
 * @brief	システムセット
 *
 * @param	heap_id	
 *
 * @retval	static PTC_PTR	
 *
 */
//--------------------------------------------------------------
static PTC_PTR ShinkaParticle_SystemSet(int heap_id)
{
	PTC_PTR ptc;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	
	heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE);
	ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, PARTICLE_LIB_HEAP_SIZE, 
		TRUE, heap_id);
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr != NULL){
		GFC_SetCameraClip(SHINKA_DEMO_NEAR, SHINKA_DEMO_FAR, camera_ptr);
	}
	return ptc;
}


//--------------------------------------------------------------
/**
 * @brief	PTC初期化
 *
 * @param	heap_id	
 * @param	arc_id	
 * @param	data_no	
 *
 * @retval	static PTC_PTR	
 *
 */
//--------------------------------------------------------------
static PTC_PTR ShinkaParticle_PtcInit(int heap_id, int arc_id, int data_no)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = ShinkaParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
	
	return ptc;
}


//--------------------------------------------------------------
/**
 * @brief	PTC終了
 *
 * @param	ptc	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaParticle_PtcExit(PTC_PTR ptc)
{
	void *heap;

	heap = Particle_HeapPtrGet(ptc);
	Particle_SystemExit(ptc);
	sys_FreeMemoryEz(heap);
}


//--------------------------------------------------------------
/**
 * @brief	コールバック
 *
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ShinkaParticle_CallBack(EMIT_PTR emit)
{
	VecFx32 pos = { 0, 0, 0 };

	VEC_Set(&pos, 0, PT_LCD_PTP_CHG(8), 0);	

	SPL_SetEmitterPosition(emit, &pos);
}


//--------------------------------------------------------------
/**
 * @brief	パーティクルシステム初期化
 *
 * @param	param	
 *
 * @retval	SHINKA_PARTICLE_SYS*	
 *
 */
//--------------------------------------------------------------
SHINKA_PARTICLE_SYS* ShinkaParticle_Init(SHINKA_PARTICLE_PARAM* param)
{
	int i;
	int ball_id;
	int spa_max;
	int set_id;
	SHINKA_PARTICLE_SYS* wk;
	
	wk = sys_AllocMemory(param->heap_id, sizeof(SHINKA_PARTICLE_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->param = *param;
	
	wk->ptc = ShinkaParticle_PtcInit(wk->param.heap_id, ARC_SHINKA_DEMO, wk->param.spa_id);
	
	Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);
	
	return wk;	
}

//--------------------------------------------------------------
/**
 * @brief	SPA登録
 *
 * @param	sps	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaParticle_SprSet(SHINKA_PARTICLE_SYS* sps, int no)
{
	int i;
	int ball_id;
	int spa_max;
	int set_id;
	
	SHINKA_PARTICLE_SYS* wk = sps;
	
	Particle_CreateEmitterCallback(wk->ptc, no, ShinkaParticle_CallBack, wk);

	Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	sps	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL ShinkaParticle_Main(SHINKA_PARTICLE_SYS* sps)
{
	SHINKA_PARTICLE_SYS* wk = sps;
	
	if (Particle_GetEmitterNum(wk->ptc) == 0){
		return FALSE;
	}
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	終了
 *
 * @param	sps	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ShinkaParticle_End(SHINKA_PARTICLE_SYS* sps)
{
	ShinkaParticle_PtcExit(sps->ptc);
	sys_FreeMemoryEz(sps);
}

