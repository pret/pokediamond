//==============================================================================
/**
 * @file	egg_main.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.05.22(月)
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
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"

#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"

#include "include/poketool/pokeicon.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"

#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"

#include "battle/battle_common.h"
#include "system/wipe.h"
#include "demo/egg/data/particle/egg_demo_setup.h"

#include "system/pm_overlay.h"

#include "demo/egg/egg.h"
#include "pokeanime/p_anm_sys.h"

static BOOL EggMain_DemoMain(EGG_MAIN_WORK* emwk);
static BOOL EggMain_DemoSpMain(EGG_MAIN_WORK* emwk);

static BOOL (* const EggDemoTable[])(EGG_MAIN_WORK* emwk) = {
	EggMain_DemoMain,
	EggMain_DemoSpMain,
};

static BOOL EggMain_Demo01(EGG_MAIN_WORK* emwk);
static BOOL EggMain_Demo02(EGG_MAIN_WORK* emwk);
static BOOL EggMain_Demo03(EGG_MAIN_WORK* emwk);
static BOOL EggMain_Demo04(EGG_MAIN_WORK* emwk);
static BOOL EggMain_Demo05(EGG_MAIN_WORK* emwk);

static BOOL EggMain_DemoSP01(EGG_MAIN_WORK* emwk);

//--------------------------------------------------------------
/**
 * @brief	デモ実行
 *
 * @param	emwk	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL EggMain_Executed(EGG_MAIN_WORK* emwk)
{
	BOOL active;
	
	active = EggDemoTable[ emwk->mode ]( emwk );
	
	return active;
}


//--------------------------------------------------------------
/**
 * @brief	デモメイン
 *
 * @param	emwk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL EggMain_DemoMain(EGG_MAIN_WORK* emwk)
{
	BOOL active = TRUE;
	
	switch(emwk->seq){
	case EMD_SEQ_INIT:
		///< 初期化
		EggDisp_BG_ResourceLoad(emwk->sys.bgl, emwk->sys.pfd);
		EggDisp_SubBG_ResourceLoad(emwk->sys.bgl, emwk->sys.pfd);
		
		EggDisp_BMP_WindowResLoad(emwk->sys.bgl, emwk->sys.pfd, emwk->sys.win_type);
		EggDisp_BMP_WindowAdd(emwk->sys.bgl, &emwk->sys.win[0], GF_BGL_FRAME1_M,
							  EGG_DEMO_TALK_WIN_X, EGG_DEMO_TALK_WIN_Y,
							  EGG_DEMO_TALK_WIN_W, EGG_DEMO_TALK_WIN_H,
							  EGG_DEMO_TALK_WIN_S, EDPAL_FONT);

		///< OAM
		EggOAM_ResourceLoad(emwk);
		EggOAM_Add(emwk);
		
		///< SSP
		EggPoke_Add(emwk);
		EggPoke_Vanish(emwk, 1);
		
		///< パーティクル
		{
			EGG_PARTICLE_PARAM param;
			
			param.heap_id = HEAPID_EGG_DEMO;
			param.spa_id  = SPA_EGG_DEMO_NORMAL;
			emwk->sys.egg_pt  = EggParticle_Init(&param);
		}
		emwk->seq++;
		break;
		
	case EMD_SEQ_FADE_IN:
		///< フェードイン
		EggDisp_WipeFadeIn();
		emwk->seq++;
	
	case EMD_SEQ_FADE_IN_WAIT:
		///< フェード待ち
		if (WIPE_SYS_EndCheck() == TRUE){
			Snd_Stop();								// 全停止
			Snd_DataSetByScene( SND_SCENE_EGG, SEQ_SHINKA, 1 );	///< タマゴ孵化
			emwk->seq++;
		}
		break;
		
	case EMD_SEQ_DEMO_1:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_Demo01(emwk);
			
			if (end == FALSE){
				emwk->seq++;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_2:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_Demo02(emwk);
			
			if (end == FALSE){
				emwk->seq++;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_3:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_Demo03(emwk);
			
			if (end == FALSE){
				emwk->seq++;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_4:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_Demo04(emwk);
			
			if (end == FALSE){
				emwk->seq++;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_5:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_Demo05(emwk);
			
			if (end == FALSE){
				EggPoke_Anm(emwk);
				{
					int poke_no;
					poke_no = PokeParaGet(emwk->epwk->param.pp, ID_PARA_monsno, NULL);
					Snd_PMVoicePlay(poke_no);								
					emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 0,
																 emwk->epwk->param.pp,
																 emwk->sys.msg_speed);
				}
				emwk->seq++;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_MSG_1:
		///< メッセージ
		if (Snd_PMVoicePlayCheck() != 0){ break; }
	//	EggPoke_Anm(emwk);
	//	emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 0,
	//												 emwk->epwk->param.pp,
	//												 emwk->sys.msg_speed);
		Snd_MePlay( SEQ_FANFA5 );
		emwk->seq++;
			
	case EMD_SEQ_DEMO_MSG_2:
		///< メッセージ
		if (Snd_MePlayCheckBgmPlay() != FALSE){ break; }
		emwk->seq++;
				
	case EMD_SEQ_DEMO_MSG_2_2:
		///< メッセージ
		if (GF_MSG_PrintEndCheck(emwk->sys.msg_index) != 0){ break; }
		
		emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 1,
													 emwk->epwk->param.pp,
													 emwk->sys.msg_speed);
		emwk->seq++;
		
	case EMD_SEQ_DEMO_MSG_3:
		///< メッセージ
		if (GF_MSG_PrintEndCheck(emwk->sys.msg_index) != 0){ break; }		
		if (PokeAnm_IsFinished(emwk->sys.pas, 0) != TRUE){ break; }
		if (SoftSpriteAnimeEndCheck(emwk->ssp_poke) != FALSE){ break; }
		
		EggDisp_SelWindowAdd(emwk,
							 emwk->sys.bgl, &emwk->sys.win[1],
							 GF_BGL_FRAME1_M,
							 EGG_DEMO_YN_WIN_X, EGG_DEMO_YN_WIN_Y,
							 EGG_DEMO_YN_WIN_W, EGG_DEMO_YN_WIN_H,
							 EGG_DEMO_YN_WIN_S, EDPAL_FONT);
		emwk->seq++;
		break;
	
	case EMD_SEQ_DEMO_SEL_1:
		{
			u32 ret = BmpMenuMain(emwk->sys.bmw);
			
			switch(ret){
			case BMPMENU_CANCEL:
				emwk->epwk->is_name_set = FALSE;
				emwk->seq++;
				break;
				
			case BMPMENU_NULL:
				break;
			
			default:
				if (ret == 0){
					emwk->epwk->is_name_set = TRUE;
				}
				else {
					emwk->epwk->is_name_set = FALSE;
				}
				emwk->seq++;
				break;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_SEL_2:
		EggDisp_SelWindowDel(emwk);
		emwk->seq++;
		break;
		
	case EMD_SEQ_DEMO_SEL_3:
		emwk->seq++;
		break;
	
	case EMD_SEQ_FADE_OUT:
		///< フェードアウト
		EggDisp_WipeFadeOut();
		emwk->seq++;
	
	case EMD_SEQ_FADE_OUT_WAIT:
		///< フェードアウト待ち
		if (WIPE_SYS_EndCheck() == TRUE){
			//Snd_BgmStop( SEQ_SHINKA, 0 );			///< ふか曲を止める
			emwk->seq++;
		}
		break;
	
	case EMD_SEQ_END:
	default:
		///< おしまい
		EggPoke_Del(emwk);
		EggOAM_Delete(emwk);
		EggDisp_BMP_WindowDel(&emwk->sys.win[0]);
		EggParticle_PtcExit(emwk->sys.egg_pt->ptc);
		EggParticle_End(emwk->sys.egg_pt);
		active = FALSE;
		break;
	}
	
	CATS_Draw(emwk->sys.crp);
	
	return active;
}




static BOOL EggMain_DemoSpMain(EGG_MAIN_WORK* emwk)
{
	BOOL active = TRUE;
	
	switch(emwk->seq){
	case EMD_SEQ_INIT:
		///< 初期化
		EggDisp_BG_ResourceLoad(emwk->sys.bgl, emwk->sys.pfd);
		EggDisp_SubBG_ResourceLoad(emwk->sys.bgl, emwk->sys.pfd);
		
		EggDisp_BMP_WindowResLoad(emwk->sys.bgl, emwk->sys.pfd, emwk->sys.win_type);
		EggDisp_BMP_WindowAdd(emwk->sys.bgl, &emwk->sys.win[0], GF_BGL_FRAME1_M,
							  EGG_DEMO_TALK_WIN_X, EGG_DEMO_TALK_WIN_Y,
							  EGG_DEMO_TALK_WIN_W, EGG_DEMO_TALK_WIN_H,
							  EGG_DEMO_TALK_WIN_S, EDPAL_FONT);

		///< OAM
		EggOAM_ResourceLoad(emwk);
		EggOAM_Add(emwk);
		CATS_ObjectEnableCap(emwk->egg, CATS_ENABLE_FALSE);
		
		///< SSP
		EggPoke_Add(emwk);
		EggPoke_Vanish(emwk, 1);
		
		///< パーティクル
		{
			EGG_PARTICLE_PARAM param;
			
			param.heap_id = HEAPID_EGG_DEMO;
			param.spa_id  = SPA_EGG_DEMO_SPECIAL;
			emwk->sys.egg_pt  = EggParticle_Init(&param);
		}
		emwk->seq++;
		break;
		
	case EMD_SEQ_FADE_IN:
		///< フェードイン
		EggDisp_WipeFadeIn();
		emwk->seq++;
	
	case EMD_SEQ_FADE_IN_WAIT:
		///< フェード待ち
		if (WIPE_SYS_EndCheck() == TRUE){
			Snd_DataSetByScene( SND_SCENE_EGG, SEQ_SHINKA, 1 );	///< タマゴ孵化
			emwk->seq++;
		}
		break;
		
	case EMD_SEQ_DEMO_1:
		///< デモ
		{
			BOOL end;
			
			end = EggMain_DemoSP01(emwk);
			
			if (end == FALSE){
				EggPoke_Anm(emwk);
				{
					int poke_no;
					poke_no = PokeParaGet(emwk->epwk->param.pp, ID_PARA_monsno, NULL);
					Snd_PMVoicePlay(poke_no);								
					emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 0,
																 emwk->epwk->param.pp,
																 emwk->sys.msg_speed);
				}
				emwk->seq = EMD_SEQ_DEMO_MSG_1;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_2:
	case EMD_SEQ_DEMO_3:
	case EMD_SEQ_DEMO_4:
	case EMD_SEQ_DEMO_5:
		GF_ASSERT(0);
		break;
		
	case EMD_SEQ_DEMO_MSG_1:
		///< メッセージ
		if (Snd_PMVoicePlayCheck() != 0){ break; }
	//	EggPoke_Anm(emwk);
	//	emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 0,
	//												 emwk->epwk->param.pp,
	//												 emwk->sys.msg_speed);
		Snd_MePlay( SEQ_FANFA5 );
		emwk->seq++;
			
	case EMD_SEQ_DEMO_MSG_2:
		///< メッセージ
		if (Snd_MePlayCheckBgmPlay() != FALSE){ break; }
		
		emwk->seq++;
		
	case EMD_SEQ_DEMO_MSG_2_2:
		///< メッセージ
		if (GF_MSG_PrintEndCheck(emwk->sys.msg_index) != 0){ break; }
		
		emwk->sys.msg_index = EggDisp_BMP_MessageSet(&emwk->sys.win[0], 1,
													 emwk->epwk->param.pp,
													 emwk->sys.msg_speed);
		emwk->seq++;
			
	case EMD_SEQ_DEMO_MSG_3:
		///< メッセージ
		if (GF_MSG_PrintEndCheck(emwk->sys.msg_index) != 0){ break; }		
		if (PokeAnm_IsFinished(emwk->sys.pas, 0) != TRUE){ break; }
		if (SoftSpriteAnimeEndCheck(emwk->ssp_poke) != FALSE){ break; }
		
		EggDisp_SelWindowAdd(emwk,
							 emwk->sys.bgl, &emwk->sys.win[1],
							 GF_BGL_FRAME1_M,
							 EGG_DEMO_YN_WIN_X, EGG_DEMO_YN_WIN_Y,
							 EGG_DEMO_YN_WIN_W, EGG_DEMO_YN_WIN_H,
							 EGG_DEMO_YN_WIN_S, EDPAL_FONT);
		emwk->seq++;
		break;
	
	case EMD_SEQ_DEMO_SEL_1:
		{
			u32 ret = BmpMenuMain(emwk->sys.bmw);
			
			switch(ret){
			case BMPMENU_CANCEL:
				emwk->epwk->is_name_set = FALSE;
				emwk->seq++;
				break;
				
			case BMPMENU_NULL:
				break;
			
			default:
				if (ret == 0){
					emwk->epwk->is_name_set = TRUE;
				}
				else {
					emwk->epwk->is_name_set = FALSE;
				}
				emwk->seq++;
				break;
			}
		}
		break;
		
	case EMD_SEQ_DEMO_SEL_2:
		EggDisp_SelWindowDel(emwk);
		emwk->seq++;
		break;
		
	case EMD_SEQ_DEMO_SEL_3:
		emwk->seq++;
		break;
	
	case EMD_SEQ_FADE_OUT:
		///< フェードアウト
		EggDisp_WipeFadeOut();
		emwk->seq++;
	
	case EMD_SEQ_FADE_OUT_WAIT:
		///< フェードアウト待ち
		if (WIPE_SYS_EndCheck() == TRUE){
			//Snd_BgmStop( SEQ_SHINKA, 0 );			// ふか曲を止める
			emwk->seq++;
		}
		break;
	
	case EMD_SEQ_END:
	default:
		///< おしまい
		EggPoke_Del(emwk);
		EggOAM_Delete(emwk);
		EggDisp_BMP_WindowDel(&emwk->sys.win[0]);
		EggParticle_PtcExit(emwk->sys.egg_pt->ptc);
		EggParticle_End(emwk->sys.egg_pt);
		active = FALSE;
		break;
	}
	
	CATS_Draw(emwk->sys.crp);
	
	return active;
}







///< 通常たまご
static BOOL EggMain_Demo01(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
		CATS_ObjectAnimeFrameSetCap(emwk->egg, 0);
		emwk->sub_seq++;
		break;
	
	case 1:
		if ((++emwk->sub_cnt) >= EGG_DEMO_PT_WAIT_0){
			
			Snd_SePlay( SE_EGG_N01 );
			
			emwk->sub_seq++;
		}
		break;
		
	default:
		emwk->sub_seq = 0;
		emwk->sub_cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}

///< ピキピキひび割れ
static BOOL EggMain_Demo02(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
		if (EggParticle_Main(emwk->sys.egg_pt) == TRUE){ break; }
		
		CATS_ObjectAnimeFrameSetCap(emwk->egg, 1);
		emwk->sub_seq++;
		break;
	
	case 1:
		{
			int end;
			
			end = EggOam_DemoMoveEx(emwk, EGG_MOVE_SHAKE_1);
			
			if (end == EGG_DEMO_MOVE_END){
			
				Snd_SePlay( SE_EGG_N01 );
			
				CATS_ObjectAnimeFrameSetCap(emwk->egg, 2);
				emwk->sub_seq++;
				emwk->sub_cnt = 0;
			}
				
		}
		break;
		
	default:
		{
			int end;
			
			end = EggOam_DemoMoveEx(emwk, EGG_MOVE_SHAKE_1);
			
			if (end == EGG_DEMO_MOVE_END){
				CATS_ObjectAnimeFrameSetCap(emwk->egg, 2);
				emwk->sub_seq = 0;
				emwk->sub_cnt = 0;
				return FALSE;
			}
				
		}
		break;
	}
	
	return TRUE;
}

///< 殻小
static BOOL EggMain_Demo03(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
//		CATS_ObjectAnimeFrameSetCap(emwk->egg, 3);
		emwk->sub_seq++;
		break;
	
	case 1:
		{
			int end;
			
			end = EggOam_DemoMoveEx(emwk, EGG_MOVE_SHAKE_2);
			
			if (end == EGG_DEMO_MOVE_PARTICLE){
			
				Snd_SePlay( SE_EGG_N01 );
			
				CATS_ObjectAnimeFrameSetCap(emwk->egg, 3);
				EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_NORMAL_KARA_BURN01);
			}
			if (end == EGG_DEMO_MOVE_END){
				emwk->sub_cnt = 0;
				emwk->sub_seq++;
			}
				
		}
		break;
		
	default:
		emwk->sub_seq = 0;
		emwk->sub_cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}


///< 殻中
static BOOL EggMain_Demo04(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
		if (EggParticle_Main(emwk->sys.egg_pt) == TRUE){ break; }
		
//		CATS_ObjectAnimeFrameSetCap(emwk->egg, 4);
		emwk->sub_seq++;
		break;
	
	case 1:
		{
			int end;
			
			end = EggOam_DemoMoveEx(emwk, EGG_MOVE_SHAKE_3);
			
			if (end == EGG_DEMO_MOVE_PARTICLE){
				
				Snd_SePlay( SE_EGG_N01 );			
				
				CATS_ObjectAnimeFrameSetCap(emwk->egg, 4);
				EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_NORMAL_KARA_BURN02);
			}
			if (end == EGG_DEMO_MOVE_END){
				emwk->sub_cnt = 0;
				emwk->sub_seq++;
			}
				
		}
		break;
		
	default:
		emwk->sub_seq = 0;
		emwk->sub_cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}

///< ぼぎゃーん
static BOOL EggMain_Demo05(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
		if (EggParticle_Main(emwk->sys.egg_pt) == TRUE){ break; }
		
		CATS_ObjectAnimeFrameSetCap(emwk->egg, 4);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		emwk->sub_seq++;
		break;
	
	case 1:
		{
			int end;
			
			end = EggOam_DemoMoveEx(emwk, EGG_MOVE_SHAKE_4);
			
			if (end == EGG_DEMO_MOVE_PARTICLE){
				CATS_ObjectAnimeFrameSetCap(emwk->egg, 5);
			
				Snd_SePlay( SE_EGG_N02 );
			
				EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_NORMAL_KARA_BURN03);
				EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_NORMAL_KIRA_BURN01);
			}
			if (end == EGG_DEMO_MOVE_END){
				CATS_ObjectEnableCap(emwk->egg, CATS_ENABLE_FALSE);
				emwk->sub_cnt = 0;
				emwk->sub_seq++;
			}
				
		}
		break;
	
	case 2:
		if ((++emwk->sub_cnt) >= 10){
			emwk->sub_cnt = 0;
			
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_BG,  0xFFFF, 0,  0, 16, 0xFFFF);
			
			{					
				NNSG2dImagePaletteProxy* palette;
				int pal_no;
				
				palette = CLACT_PaletteProxyGet(emwk->wnd_t->act);
				pal_no  = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
				
				PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF ^ (1 << pal_no), 0,  0, 16, 0xFFFF);
			}
			
			SoftSpritePalFadeSet(emwk->ssp_poke, 0, 16, 0, 0xFFFF);
			emwk->sub_seq++;
		}
		break;
	
	case 3:
		{
			s16 x, y;
			int check = 0;
			
			CATS_ObjectPosGetCap(emwk->wnd_t, &x, &y);
			if (y > -48){
				CATS_ObjectPosMoveCap(emwk->wnd_t, 0, -4);
			}
			else {
				check++;
			}
			
			CATS_ObjectPosGetCap(emwk->wnd_b, &x, &y);	
			if (y < 192){
				CATS_ObjectPosMoveCap(emwk->wnd_b, 0, +4);
			}
			else {
				check++;
			}
			
			if (PaletteFadeCheck(emwk->sys.pfd) != 0
			||  check != 2
			||	SoftSpritePalFadeExist(emwk->ssp_poke) != FALSE){ break; }
			
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON);
			EggPoke_Vanish(emwk, 0);
			CATS_ObjectEnableCap(emwk->egg,	  CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(emwk->wnd_t, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(emwk->wnd_b, CATS_ENABLE_FALSE);
		
			emwk->sub_seq++;
		}
		break;
	
	case 4:
		if ((++emwk->sub_cnt) >= EGG_DEMO_PT_WAIT_0){
			emwk->sub_cnt = 0;
	
			SoftSpritePalFadeSet(emwk->ssp_poke, 16, 0, 0, 0xFFFF);
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_BG,  0xFFFF, 0,  16, 0, 0xFFFF);
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF, 0,  16, 0, 0xFFFF);
	
			emwk->sub_seq++;
		}
		break;
	
	case 5:
		if (PaletteFadeCheck(emwk->sys.pfd) != 0
		||	SoftSpritePalFadeExist(emwk->ssp_poke) != FALSE){ break; }
		
		emwk->sub_seq++;
		break;	

	default:
		if (EggParticle_Main(emwk->sys.egg_pt) == TRUE){ break; }
		emwk->sub_seq = 0;
		emwk->sub_cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}


static BOOL EggMain_DemoSP01(EGG_MAIN_WORK* emwk)
{
	switch(emwk->sub_seq){
	case 0:
		EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_SPECIAL_TAMAGO_MANA01);
		EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_SPECIAL_TAMAGO_MANA02);
		EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_SPECIAL_TAMAGO_MANA03);
		EggParticle_SprSet(emwk->sys.egg_pt, EGG_DEMO_SPECIAL_TAMAGO_MANA04);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		emwk->sub_seq++;
		break;
	
	case 1:
	
		switch(emwk->sub_cnt){
		case 25:
			Snd_SePlay( SE_EGG_S01 );
			break;
		case 80:
			Snd_SePlay( SE_EGG_S02 );
			break;
		case 142:
			Snd_SePlay( SE_EGG_S03 );
			break;
		};
		if ((++emwk->sub_cnt) >= EGG_DEMO_SP_PT_WAIT_0){
			emwk->sub_cnt = 0;
			
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_BG,  0xFFFF, 0,  0, 16, 0xFFFF);
			
			{					
				NNSG2dImagePaletteProxy* palette;
				int pal_no;
				
				palette = CLACT_PaletteProxyGet(emwk->wnd_t->act);
				pal_no  = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
				
				PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF ^ (1 << pal_no), 0,  0, 16, 0xFFFF);
			}
			
			SoftSpritePalFadeSet(emwk->ssp_poke, 0, 16, 0, 0xFFFF);
			emwk->sub_seq++;
		}
		break;
	
	case 2:
		{
			s16 x, y;
			int check = 0;
			
			CATS_ObjectPosGetCap(emwk->wnd_t, &x, &y);
			if (y > -48){
				CATS_ObjectPosMoveCap(emwk->wnd_t, 0, -4);
			}
			else {
				check++;
			}
			
			CATS_ObjectPosGetCap(emwk->wnd_b, &x, &y);	
			if (y < 192){
				CATS_ObjectPosMoveCap(emwk->wnd_b, 0, +4);
			}
			else {
				check++;
			}
			
			if (PaletteFadeCheck(emwk->sys.pfd) != 0
			||  check != 2
			||	SoftSpritePalFadeExist(emwk->ssp_poke) != FALSE){ break; }
			EggPoke_Vanish(emwk, 0);
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON);
			CATS_ObjectEnableCap(emwk->egg,	  CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(emwk->wnd_t, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(emwk->wnd_b, CATS_ENABLE_FALSE);
		
			emwk->sub_seq++;
		}
		break;
	
	case 3:
		if ((++emwk->sub_cnt) >= EGG_DEMO_PT_WAIT_0){
			emwk->sub_cnt = 0;
	
			SoftSpritePalFadeSet(emwk->ssp_poke, 16, 0, 0, 0xFFFF);
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_BG,  0xFFFF, 0,  16, 0, 0xFFFF);
			PaletteFadeReq(emwk->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF, 0,  16, 0, 0xFFFF);
	
			emwk->sub_seq++;
		}
		break;
	
	case 4:
		if (PaletteFadeCheck(emwk->sys.pfd) != 0
		||	SoftSpritePalFadeExist(emwk->ssp_poke) != FALSE){ break; }
		
		emwk->sub_seq++;
		break;	

	default:
		emwk->sub_seq = 0;
		emwk->sub_cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}


