
//============================================================================================
/**
 * @file	shinka.c
 * @bfief	進化デモプログラム
 * @author	HisashiSogabe
 * @date	06.04.08
 */
//============================================================================================

#include "common.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/bmp_menu.h"
#include "system/softsprite.h"
#include "system/brightness.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"
#include "system/buflen.h"

#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/shinka.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "pokeanime/p_anm_sys.h"
#include "itemtool/myitem.h"
#include "itemtool/itemsym.h"

#include "shinka_def.h"
#include "shinka_disp.h"

#include "battle/graphic/batt_bg_def.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_fightmsg_dp.h"

#include "demo/egg/data/egg_data_def.h"
#include "demo/shinka/data/particle/shinka_demo_setup.h"
#include "src/field/poketch/poketch_arc.h"
#include "field/poketch_data.h"

#include "gflib/mmap_get.h"
#include "gflib/heapsys.h"
#include "system/window.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/font_arc.h"
#include "system/pmfprint.h"
#include "system/msg_ds_icon.h"

#include "savedata/zukanwork.h"
#include "savedata/mail_util.h"
#include "savedata/custom_ball.h"

#include "communication/communication.h"

#include "shinka_snd_def.h"

#define	SHINKA_BMP_WIN_MAX	(1)		///<進化デモで使用するBMPWINのMAX

#define	SHINKA_BEFORE		(0)
#define	SHINKA_AFTER		(1)

#define	MORPH_TIME			(128)

#define	SHINKA_BG			(PF_BIT_NORMAL_ALL)

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================

SHINKA_WORK		*ShinkaInit(POKEPARTY *ppt,POKEMON_PARAM *pp,int after_mons_no,
							CONFIG *config,int contest_see_flag,ZUKAN_WORK *zw,MYITEM *my_item,
							RECORD *record,POKETCH_DATA *poketch_data,
							int shinka_cond,int shinka_status_flag,int heapID);
static	void	ShinkaMain(TCB_PTR tcb,void *work);
BOOL			ShinkaEndCheck(SHINKA_WORK *sw);
void			ShinkaEnd(SHINKA_WORK *sw);

static	void	ShinkaSequence(SHINKA_WORK *sw);
static	void	ShinkaAfterAct(SHINKA_WORK *sw);

static	void	ShinkaBGCreate(SHINKA_WORK *sw,GF_BGL_INI *bgl);
static	void	ShinkaBGEnd(GF_BGL_INI *bgl);
static	void	ShinkaOBJCreate(SHINKA_WORK *sw);
static	void	ShinkaVBlank(void *work);

static	u8		ShinkaMSG_Print(SHINKA_WORK *sw,int msg_id);
static	BOOL	ShinkaMSG_CallBack(MSG_PRINT_HEADER *mph,u16 value);

static	void	ShinkaWazaWasureProcSet(SHINKA_WORK *sw);

//============================================================================================
//	BMPWINデータ
//============================================================================================
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME2_M, 23, 13, 7, 4, MENU_MSG_PAL_NO, MENU_MSG_START
};

// 技覚え用ステータス画面ページ
static const u8 PST_PageTbl_WazaSet[] = {
	PST_PAGE_B_SKILL,		// 「たたかうわざ」
	PST_PAGE_C_SKILL,		// 「コンテストわざ」
	PST_PAGE_MAX
};

//--------------------------------------------------------------
/**
 * @brief	戦闘進化デモ初期化
 *
 * @param[in]	pp				進化前ポケモンのPOKEMON_PARAM構造体ポインタ
 * @param[in]	after_mons_no	進化後ポケモンナンバー
 * @param[in]	config			ゲームコンフィグワークへのポインタ
 * @param[in]	heapID			使用ヒープID
 */
//--------------------------------------------------------------
SHINKA_WORK		*ShinkaInit(POKEPARTY *ppt,POKEMON_PARAM *pp,int after_mons_no,
							CONFIG *config,int contest_see_flag,ZUKAN_WORK *zw,MYITEM *my_item,
							RECORD *record,POKETCH_DATA *poketch_data,
							int shinka_cond,int shinka_status_flag,int heapID)
{
	SHINKA_WORK	*sw;
	SOFT_SPRITE_ARC	ssa;
	int			i;

	sw=(SHINKA_WORK *)sys_AllocMemory(heapID,sizeof(SHINKA_WORK));

	MI_CpuClearFast(sw,sizeof(SHINKA_WORK));
	MI_CpuFill16((void*)GF_MMAP_MainBgPlttAddr(),	0x0000,GF_MMAP_MainBgPlttSize());
	MI_CpuFill16((void*)GF_MMAP_SubBgPlttAddr(),	0x0000,GF_MMAP_SubBgPlttSize());

	sw->ppt=ppt;
	sw->pp=pp;
	sw->before_mons_no=PokeParaGet(pp,ID_PARA_monsno,NULL);
	sw->after_mons_no=after_mons_no;
	sw->heapID=heapID;

	sw->pfd=PaletteFadeInit(heapID);
	PaletteTrans_AutoSet(sw->pfd, TRUE);
	PaletteFadeWorkAllocSet(sw->pfd,FADE_MAIN_BG,	0x200,heapID);
	PaletteFadeWorkAllocSet(sw->pfd,FADE_SUB_BG,	0x200,heapID);
	PaletteFadeWorkAllocSet(sw->pfd,FADE_MAIN_OBJ,	BATTLE_MAIN_OBJPAL_SIZE,heapID);
	PaletteFadeWorkAllocSet(sw->pfd,FADE_SUB_OBJ,	0x200,heapID);

	sw->bgl=GF_BGL_BglIniAlloc(heapID);
	sw->win=GF_BGL_BmpWinAllocGet(heapID,SHINKA_BMP_WIN_MAX);

	//コンフィグコピー
	sw->config=config;

	sw->g3Dman=ShinkaDisp_3D_Init(heapID);
	ShinkaDisp_SystemInit();						///< システム初期化
	ShinkaDisp_DefaultBlendSet();					///< Blend設定
	ShinkaDisp_3DVramInit();						///< 3D設定

	ShinkaBGCreate(sw,sw->bgl);

	GF_BGL_BmpWinAdd(sw->bgl,sw->win,GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(sw->win,0xff);
	BmpTalkWinWrite(sw->win,WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	sw->ssm=SoftSpriteInit(heapID);
	sw->pasp=PokeAnm_AllocMemory(heapID,1,0);

	sw->end_flag=0;
	sw->wait=2;

	//メッセージマネージャ作成
	sw->msg_man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_fightmsg_dp_dat,heapID);
	//単語バッファ作成
	sw->wordset=WORDSET_Create(heapID);
	sw->msg_buf=STRBUF_Create(BATTLE_MESSAGE_BUF_SIZE,heapID);

	//技忘れ用ステータス画面ワーク作成
	sw->psd=sys_AllocMemory(heapID,sizeof(PSTATUS_DATA));
	MI_CpuClearFast(sw->psd,sizeof(PSTATUS_DATA));
	sw->psd->ev_contest=contest_see_flag;

	//図鑑ワークコピー
	sw->zw=zw;

	//アイテムワークコピー
	sw->my_item=my_item;

	//レコードワークコピー
	sw->record=record;

	//ポケッチワークコピー
	sw->poketch_data=poketch_data;

	//進化条件ワークコピー
	sw->shinka_cond=shinka_cond;

	//進化ステータスフラグコピー
	sw->shinka_status_flag=shinka_status_flag;

	ShinkaOBJCreate(sw);

	PaletteFadeReq(sw->pfd,SHINKA_BG,0xffff,1,16,0,0x0000);
	SoftSpritePalFadeSetAll(sw->ssm,16,0,0,0x0000);

	sw->msg_icon=MSG_DsIconFlashAdd(sw->pfd,MSG_DSI_MAINDISP,0x0b,heapID);
	MSG_DsIconFlashReq(sw->msg_icon,MSG_DSI_REQ_STOP);

	TCB_Add(ShinkaMain,sw,0);

	//メッセージスキップON
	MsgPrintSkipFlagSet(MSG_SKIP_ON);

	//通信アイコンの起動(通信してない場合はでません）
	WirelessIconEasy();

	return sw;
}

//--------------------------------------------------------------
/**
 * @brief	戦闘進化デモ
 */
//--------------------------------------------------------------
static	void	ShinkaMain(TCB_PTR tcb,void *work)
{
	SHINKA_WORK	*sw=(SHINKA_WORK *)work;

	ShinkaSequence(sw);

	SoftSpriteMain(sw->ssm);
	ShinkaDisp_ParticleMain();

	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	
	if(sw->end_flag){
		TCB_Delete(tcb);
	}
}

//--------------------------------------------------------------
/**
 * @brief	戦闘進化デモ終了まち
 *
 * @param[in]	sw	進化デモワーク構造体
 *
 * @retval	FALSE:デモ中 TRUE:デモ終了
 */
//--------------------------------------------------------------
BOOL	ShinkaEndCheck(SHINKA_WORK *sw)
{
	return (sw->end_flag==1);
}

//--------------------------------------------------------------
/**
 * @brief	戦闘進化デモ終了処理
 *
 * @param[in]	sw	進化デモワーク構造体
 */
//--------------------------------------------------------------
void	ShinkaEnd(SHINKA_WORK *sw)
{
	int	i;

	WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);
	WIPE_SetBrightness(WIPE_DISP_SUB, WIPE_FADE_BLACK);

	sys_VBlankFuncChange(NULL,NULL);

	GF_BGL_BmpWinFree(sw->win,SHINKA_BMP_WIN_MAX);

	//パレットフェードシステム削除
	PaletteFadeWorkAllocFree(sw->pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(sw->pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(sw->pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(sw->pfd, FADE_SUB_OBJ);
	PaletteFadeFree(sw->pfd);

	SoftSpriteEnd(sw->ssm);
	PokeAnm_FreeMemory(sw->pasp);
	GF_G3D_Exit(sw->g3Dman);

	ShinkaBGEnd(sw->bgl);

	//メッセージマネージャの削除
	MSGMAN_Delete(sw->msg_man);

	//単語バッファ削除
	WORDSET_Delete(sw->wordset);
	sys_FreeMemoryEz(sw->msg_buf);

	//技忘れ用ステータス画面ワーク削除
	sys_FreeMemoryEz(sw->psd);

	//DSアイコンパレットアニメ削除
	MSG_DsIconFlashDelete(sw->msg_icon);

	sys_FreeMemoryEz(sw->bgl);

	sys_FreeMemoryEz(sw);

	//メッセージスキップOFF
	MsgPrintSkipFlagSet(MSG_SKIP_OFF);
}

//--------------------------------------------------------------
/**
 * @brief	戦闘進化デモ
 */
//--------------------------------------------------------------
enum{
	SEQ_SHINKA_START_WAIT=0,
	SEQ_SHINKA_START,
	SEQ_SHINKA_BEFORE_MSG_INIT_BATTLE_MODE,
	SEQ_SHINKA_BEFORE_MSG_WAIT_BATTLE_MODE,
	SEQ_SHINKA_BEFORE_MSG_INIT,
	SEQ_SHINKA_BEFORE_MSG_WAIT,
	SEQ_SHINKA_BGM_WAIT,
	SEQ_SHINKA_FADE_WAIT,
	SEQ_SHINKA_MORPH,
	SEQ_SHINKA_WHITE_OUT,
	SEQ_SHINKA_WHITE_OUT_AFTER,
	SEQ_SHINKA_AFTER_MSG_INIT,
	SEQ_SHINKA_AFTER_MSG_WAIT,
	SEQ_SHINKA_WAZAOBOE_CHECK,
	SEQ_SHINKA_WAZAWASURE_MSG1,
	SEQ_SHINKA_WAZAWASURE_MSG1_WAIT,
	SEQ_SHINKA_WAZAWASURE_MSG2,
	SEQ_SHINKA_WAZAWASURE_MSG2_WAIT,
	SEQ_SHINKA_WAZAWASURE_MSG3,
	SEQ_SHINKA_WAZAWASURE_MSG3_WAIT,
	SEQ_SHINKA_WAZAWASURE_YES_NO_INIT,
	SEQ_SHINKA_WAZAWASURE_YES_NO,
	SEQ_SHINKA_WAZAWASURE_SELECT_INIT,
	SEQ_SHINKA_WAZAWASURE_SELECT,
	SEQ_SHINKA_WAZAWASURE_SELECT_WAIT,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG1,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG1_WAIT,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG2,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG2_WAIT,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG3,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG3_WAIT,
	SEQ_SHINKA_WAZAWASURE_ACT_MSG4,
	SEQ_SHINKA_WAZAAKIRAME_MSG1,
	SEQ_SHINKA_WAZAAKIRAME_MSG1_WAIT,
	SEQ_SHINKA_WAZAAKIRAME_YES_NO,
	SEQ_SHINKA_WAZAAKIRAME,
	SEQ_SHINKA_WAZAAKIRAME_ACT,
	SEQ_SHINKA_WAZAOBOE_MSG_INDEX_WAIT,
	SEQ_SHINKA_WAZAOBOE_MSG_WAIT,
	SEQ_SHINKA_END_INIT,
	SEQ_SHINKA_END,

	SEQ_SHINKA_CANCEL_INIT,
	SEQ_SHINKA_CANCEL,
	SEQ_SHINKA_CANCEL_MSG,
	SEQ_SHINKA_CANCEL_MSG_WAIT,
	SEQ_SHINKA_CANCEL_END,
};

static void ShinkaSequence(SHINKA_WORK *sw)
{
	if(sw->morph_flag){
		if((sw->morph_flag&1)==0){
			SoftSpriteParaCalc(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_X,sw->morph_speed*-1);
			SoftSpriteParaCalc(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_Y,sw->morph_speed*-1);
			SoftSpriteParaCalc(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X,sw->morph_speed);
			SoftSpriteParaCalc(sw->ss[SHINKA_AFTER],SS_PARA_AFF_Y,sw->morph_speed);
			if(SoftSpriteParaGet(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_X)==0){
				sw->morph_flag^=1;
			}
		}
		else{
			SoftSpriteParaCalc(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_X,sw->morph_speed);
			SoftSpriteParaCalc(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_Y,sw->morph_speed);
			SoftSpriteParaCalc(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X,sw->morph_speed*-1);
			SoftSpriteParaCalc(sw->ss[SHINKA_AFTER],SS_PARA_AFF_Y,sw->morph_speed*-1);
			if(SoftSpriteParaGet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X)==0){
				sw->morph_flag^=1;
				if(sw->morph_speed<0x40){
					sw->morph_speed*=2;
				}
			}
		}
	}

	//進化キャンセルチェック
	if((sw->shinka_status_flag&SHINKA_STATUS_FLAG_CANCEL_ON)&&
	   (sw->seq_no==SEQ_SHINKA_MORPH)&&
	   (sys.trg & PAD_BUTTON_B)){
		PaletteFadeReq(sw->pfd,SHINKA_BG,(TALK_PAL_BIT^0xffff),0,0,16,0x7fff);
		sw->seq_no=SEQ_SHINKA_CANCEL_INIT;
	}

	switch(sw->seq_no){
	case SEQ_SHINKA_START_WAIT:
		if(--sw->wait==0){
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_START:
		WIPE_ResetBrightness(WIPE_DISP_MAIN);
		WIPE_ResetBrightness(WIPE_DISP_SUB);
		MSG_DsIconFlashReq(sw->msg_icon,MSG_DSI_REQ_START);
		if(sw->shinka_status_flag&SHINKA_STATUS_FLAG_BATTLE_MODE){
			sw->seq_no=SEQ_SHINKA_BEFORE_MSG_INIT_BATTLE_MODE;
		}
		else{
			sw->seq_no=SEQ_SHINKA_BEFORE_MSG_INIT;
		}
		break;
	case SEQ_SHINKA_BEFORE_MSG_INIT_BATTLE_MODE:
		if(PaletteFadeCheck(sw->pfd)==0){
			sw->msg_index=ShinkaMSG_Print(sw,battle_ShinkaBeforeMsg1);
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_BEFORE_MSG_WAIT_BATTLE_MODE:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			sw->seq_no=SEQ_SHINKA_BEFORE_MSG_INIT;
		}
		break;
	case SEQ_SHINKA_BEFORE_MSG_INIT:
		if(PaletteFadeCheck(sw->pfd)==0){
			{
				SOFT_SPRITE_ANIME	ssa[10];

				PokePrgAnmDataSet(sw->pasp,sw->ss[0],sw->before_mons_no,PARA_FRONT,0,PARA_HFLIP_OFF,0);
				PokeAnmDataSet(&ssa[0],sw->before_mons_no);
				SoftSpriteAnimeDataSet(sw->ss[0],&ssa[0]);
				SoftSpriteAnimeSet(sw->ss[0],NULL);
			}
			Snd_PMVoicePlay(sw->before_mons_no);
			WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
			if(sw->shinka_status_flag&SHINKA_STATUS_FLAG_BATTLE_MODE){
				sw->msg_index=ShinkaMSG_Print(sw,battle_ShinkaBeforeMsg2);
			}
			else{
				sw->msg_index=ShinkaMSG_Print(sw,ShinkaBeforeMsg);
			}
			sw->seq_no=SEQ_SHINKA_BEFORE_MSG_WAIT;
		}
		break;
	case SEQ_SHINKA_BEFORE_MSG_WAIT:
		if((GF_MSG_PrintEndCheck(sw->msg_index)==0)&&
		   (Snd_PMVoicePlayCheck()==0)&&
		   (PokeAnm_IsFinished(sw->pasp,0)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(sw->ss[0])==FALSE)){
			MSG_DsIconFlashReq(sw->msg_icon,MSG_DSI_REQ_STOP);
			Snd_BgmPlayBasicData( SEQ_SHINKA );	//特殊
			sw->wait=20;
			sw->seq_no=SEQ_SHINKA_BGM_WAIT;
		}
		break;
	case SEQ_SHINKA_BGM_WAIT:
		if(--sw->wait==0){
			{
				SHINKA_PARTICLE_PARAM	param;

				param.heap_id=sw->heapID;
				param.spa_id=SPA_SHINKA_DEMO;

				sw->shinka_pt=ShinkaParticle_Init(&param);
				ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM001_A);
				SoftSpritePalFadeSet(sw->ss[SHINKA_BEFORE],0,16,4,0x7fff);
				SoftSpritePalFadeSet(sw->ss[SHINKA_AFTER],0,16,4,0x7fff);
				//パーティクルを生成した時点で残りメモリが0x8000をきっていたらアサートを出す（技忘れ対策）
				GF_ASSERT(sys_GetHeapFreeSize(sw->heapID)>0x8000);
				Snd_SePlay( SHINKA_SE_QUEEN );
			}
			sw->wait=40;
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_FADE_WAIT:
		if(sw->wy1<0x28){
			sw->wy1+=2;
			sw->wy2-=2;
		}
//		if(ShinkaParticle_Main(sw->shinka_pt)==FALSE){
		if(--sw->wait==0){
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_A);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_B);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_G);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_H);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_I);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_K);
			Snd_SePlay( SHINKA_SE_KIIN );
			sw->morph_flag=0x10;
			sw->morph_speed=8;
//			sw->wait=114;
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_MORPH:
		if(ShinkaParticle_Main(sw->shinka_pt)==FALSE){
//		if(--sw->wait==0){
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_C);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_D);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_E);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_F);
			ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM002_J);
			PaletteFadeReq(sw->pfd,SHINKA_BG,(TALK_PAL_BIT^0xffff),2,0,16,0x7fff);
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_X,AFF_APPEAR_X_S);
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X,AFF_APPEAR_X_B);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_Y,AFF_APPEAR_Y_B);
			Snd_SePlay( SHINKA_SE_SYUU );
			sw->morph_flag=0;
			sw->wait=8;
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_WHITE_OUT:
		if(sw->wy1){
			sw->wy1-=2;
			sw->wy2+=2;
		}
		if(PaletteFadeCheck(sw->pfd)==0){
			if(--sw->wait==0){
				ShinkaParticle_SprSet(sw->shinka_pt, SHINKA_DEMO_000_DM003_A);
				PaletteFadeReq(sw->pfd,SHINKA_BG,(TALK_PAL_BIT^0xffff),4,16,0,0x7fff);
				SoftSpritePalFadeSetAll(sw->ssm,16,0,3,0x7fff);
				Snd_SePlay( SHINKA_SE_BAAN );
				sw->seq_no++;
			}
		}
		break;
	case SEQ_SHINKA_WHITE_OUT_AFTER:
		if((PaletteFadeCheck(sw->pfd)==0)&&(ShinkaParticle_Main(sw->shinka_pt)==FALSE)){
			{
				SOFT_SPRITE_ANIME	ssa[10];

				PokePrgAnmDataSet(sw->pasp,sw->ss[1],sw->after_mons_no,PARA_FRONT,0,PARA_HFLIP_OFF,0);
				PokeAnmDataSet(&ssa[0],sw->after_mons_no);
				SoftSpriteAnimeDataSet(sw->ss[1],&ssa[0]);
				SoftSpriteAnimeSet(sw->ss[1],NULL);
			}
			//Snd_BgmStop(SEQ_SHINKA,0);			//060803　停止処理を外しました
			Snd_PMVoicePlay(sw->after_mons_no);
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_AFTER_MSG_INIT:
		if((Snd_PMVoicePlayCheck()==0)&&
		   (PokeAnm_IsFinished(sw->pasp,0)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(sw->ss[1])==FALSE)){
				//特殊能力セット
				PokeParaPut(sw->pp,ID_PARA_monsno,(u8 *)&sw->after_mons_no);
				PokeParaSpeabiSet(sw->pp);
				PokeParaCalc(sw->pp);
				WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
				WORDSET_RegisterPokeMonsName(sw->wordset,STR_TEMP_BUF1,PPPPointerGet(sw->pp));
				sw->msg_index=ShinkaMSG_Print(sw,ShinkaAfterMsg);
				sw->wait=40;
				sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_AFTER_MSG_WAIT:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			if(--sw->wait==0){

				//図鑑登録
				ZukanWork_SetPokeGet(sw->zw,sw->pp);
				//各種カウントアップ
				RECORD_Inc(sw->record,RECID_POKE_EVOLUTION);
				RECORD_Score_Add(sw->record,SCORE_ID_ZUKAN_ENTRY);
				//ポケッチデータ登録
				PoketchData_PokeHistory_Add(sw->poketch_data,PPPPointerGet(sw->pp));

				if(PokeParaGet(sw->pp,ID_PARA_nickname_flag,NULL)==0){
					PokeParaPut(sw->pp,ID_PARA_default_name,NULL);
				}
				sw->seq_no++;
			}
		}
		break;
	case SEQ_SHINKA_WAZAOBOE_CHECK:
		{
			u16	wazano;

			switch(PokeWazaOboeCheck(sw->pp,&sw->waza_cnt,&wazano)){
			case SAME_WAZA_SET:
				//同じ技は覚えられないので、再度チェックのループに回す
				break;
			case NO_WAZA_OBOE:
				sw->seq_no=SEQ_SHINKA_END_INIT;
				break;
			case NO_WAZA_SET:
				sw->waza_no=wazano;
				sw->seq_no=SEQ_SHINKA_WAZAWASURE_MSG1;
				break;
			default:
				WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
				WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF1,wazano);
				sw->msg_index=ShinkaMSG_Print(sw,WazaOboeMsg);
				sw->wait=MSG_WAIT;
				sw->seq_no=SEQ_SHINKA_WAZAOBOE_MSG_INDEX_WAIT;
				break;
			}
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_MSG1:
		WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
		WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF1,sw->waza_no);
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaOboeMsg1);
		sw->wait=MSG_WAIT;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_MSG2:
		WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaOboeMsg2);
		sw->wait=MSG_WAIT;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_MSG3:
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaWasureMsg1);
		sw->wait=1;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_MSG1_WAIT:
	case SEQ_SHINKA_WAZAWASURE_MSG2_WAIT:
	case SEQ_SHINKA_WAZAWASURE_MSG3_WAIT:
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG1_WAIT:
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG2_WAIT:
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG3_WAIT:
	case SEQ_SHINKA_WAZAAKIRAME_MSG1_WAIT:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			if(--sw->wait==0){
				sw->seq_no++;
			}
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_YES_NO_INIT:
		sw->work_p=BmpYesNoSelectInit(sw->bgl,&YesNoBmpWin,MENU_WIN_CGX_START,MENU_WIN_PAL_NO,sw->heapID);
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_YES_NO:
		switch(BmpYesNoSelectMain(sw->work_p,sw->heapID)){
		case 0:					//はいを選択
			sw->seq_no=SEQ_SHINKA_WAZAWASURE_SELECT_INIT;
			PaletteFadeReq(sw->pfd,SHINKA_BG,0xffff,1,0,16,0x0000);
			SoftSpritePalFadeSetAll(sw->ssm,0,16,0,0x0000);
			break;
		case BMPMENU_CANCEL:	//いいえorキャンセル
			sw->seq_no=SEQ_SHINKA_WAZAAKIRAME_MSG1;
			break;
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_SELECT_INIT:
		if(PaletteFadeCheck(sw->pfd)==0){
			WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);
			WIPE_SetBrightness(WIPE_DISP_SUB, WIPE_FADE_BLACK);
			ShinkaBGEnd(sw->bgl);
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_VANISH,1);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_VANISH,1);
			sw->psd->ppd	=sw->pp;
			sw->psd->cfg	=sw->config;
			sw->psd->ppt	=PST_PP_TYPE_POKEPARAM;
			sw->psd->pos	=0;
			sw->psd->max	=1;
			sw->psd->waza	=sw->waza_no;
			sw->psd->mode	=PST_MODE_WAZAADD;
			sw->psd->perap	=NULL;
			PokeStatus_PageSet( sw->psd, PST_PageTbl_WazaSet );
			ShinkaWazaWasureProcSet(sw);
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_SELECT:
		if(ProcMain(sw->proc)){
			PROC_Delete(sw->proc);
			ShinkaBGCreate(sw,sw->bgl);
			BmpTalkWinWrite(sw->win,WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_VANISH,0);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_VANISH,0);
			SoftSpriteRecoverSS(sw->ss[SHINKA_BEFORE]);
			SoftSpriteRecoverSS(sw->ss[SHINKA_AFTER]);
			PaletteFadeReq(sw->pfd,SHINKA_BG,0xffff,1,16,0,0x0000);
			SoftSpritePalFadeSetAll(sw->ssm,16,0,0,0x0000);
			//通信アイコンの起動(通信してない場合はでません）
			WirelessIconEasy();

			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_SELECT_WAIT:
		WIPE_ResetBrightness(WIPE_DISP_MAIN);
		WIPE_ResetBrightness(WIPE_DISP_SUB);
		if(PaletteFadeCheck(sw->pfd)==0){
			if(sw->psd->ret_sel==4){
				sw->seq_no=SEQ_SHINKA_WAZAAKIRAME_MSG1;
			}
			else{
				sw->waza_pos=sw->psd->ret_sel;
				sw->seq_no=SEQ_SHINKA_WAZAWASURE_ACT_MSG1;
			}
		}
		break;
	case SEQ_SHINKA_WAZAAKIRAME_MSG1:
		WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF0,sw->waza_no);
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaAkirameMsg1);
		sw->wait=1;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAAKIRAME_YES_NO:
		sw->work_p=BmpYesNoSelectInit(sw->bgl,&YesNoBmpWin,MENU_WIN_CGX_START,MENU_WIN_PAL_NO,sw->heapID);
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAAKIRAME:
		switch(BmpYesNoSelectMain(sw->work_p,sw->heapID)){
		case 0:					//はいを選択
			WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
			WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF1,sw->waza_no);
			sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaAkirameMsg2);
			sw->wait=MSG_WAIT;
			sw->seq_no=SEQ_SHINKA_WAZAAKIRAME_ACT;
			break;
		case BMPMENU_CANCEL:	//いいえorキャンセル
			sw->seq_no=SEQ_SHINKA_WAZAWASURE_MSG1;
			break;
		}
		break;
		break;
	case SEQ_SHINKA_WAZAAKIRAME_ACT:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			if(--sw->wait==0){
				sw->seq_no=SEQ_SHINKA_WAZAOBOE_CHECK;
			}
		}
		break;
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG1:
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaWasureMsg3);
		sw->wait=MSG_WAIT;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG2:
		WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
		WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF1,PokeParaGet(sw->pp,ID_PARA_waza1+sw->waza_pos,NULL));
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaWasureMsg4);
		sw->wait=MSG_WAIT;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG3:
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaOboeMsg3);
		sw->wait=MSG_WAIT;
		sw->seq_no++;
		break;
	case SEQ_SHINKA_WAZAWASURE_ACT_MSG4:
		WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
		WORDSET_RegisterWazaName(sw->wordset,STR_TEMP_BUF1,sw->waza_no);
		sw->msg_index=ShinkaMSG_Print(sw,sinkademo_WazaOboeMsg4);
		sw->wait=0;
		PokeParaPut(sw->pp,ID_PARA_pp_count1+sw->waza_pos,&sw->wait);	//pp_countをクリア
		PokeWazaSetPos(sw->pp,sw->waza_no,sw->waza_pos);
		sw->wait=MSG_WAIT;
		sw->seq_no=SEQ_SHINKA_WAZAOBOE_MSG_INDEX_WAIT;
		break;
	case SEQ_SHINKA_WAZAOBOE_MSG_INDEX_WAIT:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_WAZAOBOE_MSG_WAIT:
		if(Snd_MePlayCheckBgmPlay()==FALSE){
			if(--sw->wait==0){
				sw->seq_no=SEQ_SHINKA_WAZAOBOE_CHECK;
			}
		}
		break;
	case SEQ_SHINKA_END_INIT:
		PaletteFadeReq(sw->pfd,SHINKA_BG,0xffff,1,0,16,0x0000);
		SoftSpritePalFadeSetAll(sw->ssm,0,16,0,0x0000);
		sw->seq_no++;
		break;
	case SEQ_SHINKA_END:
		if(PaletteFadeCheck(sw->pfd)==0){
			ShinkaParticle_End(sw->shinka_pt);
			ShinkaAfterAct(sw);
			sw->end_flag=1;
		}
		break;
	case SEQ_SHINKA_CANCEL_INIT:
		if(PaletteFadeCheck(sw->pfd)==0){
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_X,AFF_APPEAR_X_B);
			SoftSpriteParaSet(sw->ss[SHINKA_BEFORE],SS_PARA_AFF_Y,AFF_APPEAR_Y_B);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X,AFF_APPEAR_X_S);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
			SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_VANISH,1);
			PaletteFadeReq(sw->pfd,SHINKA_BG,(TALK_PAL_BIT^0xffff),0,16,0,0x7fff);
			SoftSpritePalFadeSetAll(sw->ssm,16,0,0,0x7fff);
			sw->wx1=0;
			sw->wy1=0;
			sw->wx2=0xff;
			sw->wy2=0xa0;
			sw->morph_flag=0;
			Snd_BgmStop(SEQ_SHINKA,0);
			ShinkaParticle_End(sw->shinka_pt);
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_CANCEL:
		if(PaletteFadeCheck(sw->pfd)==0){
			{
				SOFT_SPRITE_ANIME	ssa[10];

				PokePrgAnmDataSet(sw->pasp,sw->ss[0],sw->before_mons_no,PARA_FRONT,0,PARA_HFLIP_OFF,0);
				PokeAnmDataSet(&ssa[0],sw->before_mons_no);
				SoftSpriteAnimeDataSet(sw->ss[0],&ssa[0]);
				SoftSpriteAnimeSet(sw->ss[0],NULL);
			}
			Snd_PMVoicePlay(sw->before_mons_no);
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_CANCEL_MSG:
		if((Snd_PMVoicePlayCheck()==0)&&
		   (PokeAnm_IsFinished(sw->pasp,0)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(sw->ss[0])==FALSE)){
			WORDSET_RegisterPokeNickName(sw->wordset,STR_TEMP_BUF0,PPPPointerGet(sw->pp));
			sw->msg_index=ShinkaMSG_Print(sw,ShinkaCancelMsg);
			sw->wait=20;
			sw->seq_no++;
		}
		break;
	case SEQ_SHINKA_CANCEL_MSG_WAIT:
		if(GF_MSG_PrintEndCheck(sw->msg_index)==0){
			if(--sw->wait==0){
				PaletteFadeReq(sw->pfd,SHINKA_BG,0xffff,1,0,16,0x0000);
				SoftSpritePalFadeSetAll(sw->ssm,0,16,0,0x0000);
				sw->seq_no++;
			}
		}
		break;
	case SEQ_SHINKA_CANCEL_END:
		if(PaletteFadeCheck(sw->pfd)==0){
			sw->end_flag=1;
		}
		break;
	}
}

//============================================================================================
/**
 *	進化後の後処理
 */
//============================================================================================
static	void	ShinkaAfterAct(SHINKA_WORK *sw)
{
	int	i;

	switch(sw->shinka_cond){
	//ヌケニン進化
	case SHINKA_SPECIAL_LEVELUP:
	case SHINKA_SPECIAL_NUKENIN:
		//モンスターボールを1個所持していて、手持ちに空きがあれば、殻を残す
		if(MyItem_GetItemNum(sw->my_item,ITEM_MONSUTAABOORU,sw->heapID)&&
		  (PokeParty_GetPokeCount(sw->ppt)<POKEMON_TEMOTI_MAX)){
			{
				POKEMON_PARAM	*pp;
				int				work;
				MAIL_DATA		*mail_data;
				CB_CORE			cb_core;

				pp=PokemonParam_AllocWork(sw->heapID);
				PokeCopyPPtoPP(sw->pp,pp);

				//モンスターナンバーをヌケニンに
				work=MONSNO_NUKENIN;
				PokeParaPut(pp,ID_PARA_monsno,&work);

				//取得ボールをモンスターボールに
				work=ITEM_MONSUTAABOORU;
				PokeParaPut(pp,ID_PARA_get_ball,&work);

				work=0;

				//装備アイテムをなくす
				PokeParaPut(pp,ID_PARA_item,&work);
				//ポケモンにつけるマークを消す
				PokeParaPut(pp,ID_PARA_mark,&work);

				//リボン系をクリア
				for(i=ID_PARA_sinou_champ_ribbon;i<ID_PARA_sinou_amari_ribbon+1;i++){
					PokeParaPut(pp,i,&work);
				}

				for(i=ID_PARA_stylemedal_normal;i<ID_PARA_world_ribbon+1;i++){
					PokeParaPut(pp,i,&work);
				}

				for(i=ID_PARA_trial_stylemedal_normal;i<ID_PARA_amari_ribbon+1;i++){
					PokeParaPut(pp,i,&work);
				}

				//ニックネームをデフォルト名に
				PokeParaPut(pp,ID_PARA_default_name,NULL);
				PokeParaPut(pp,ID_PARA_nickname_flag,&work);


				//状態異常を直す
				PokeParaPut(pp,ID_PARA_condition,&work);

				//メールデータ
				mail_data=MailData_CreateWork(sw->heapID);
				PokeParaPut(pp,ID_PARA_mail_data,mail_data);
				sys_FreeMemoryEz(mail_data);

				//カスタムボールID
				PokeParaPut(pp,ID_PARA_cb_id,&work);

				//カスタムボールデータ
				MI_CpuClearFast(&cb_core, sizeof(CB_CORE));
				PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);

				//特性セット
				PokeParaSpeabiSet(pp);
				PokeParaCalc(pp);
				PokeParty_Add(sw->ppt,pp);

				//図鑑登録
				ZukanWork_SetPokeGet(sw->zw,pp);
				//各種カウントアップ
				RECORD_Inc(sw->record,RECID_POKE_EVOLUTION);
				RECORD_Score_Add(sw->record,SCORE_ID_ZUKAN_ENTRY);
				//ポケッチデータ登録
				PoketchData_PokeHistory_Add(sw->poketch_data,PPPPointerGet(pp));

				sys_FreeMemoryEz(pp);

				MyItem_SubItem(sw->my_item,ITEM_MONSUTAABOORU,1,sw->heapID);
			}
		}
		break;
	//装備アイテムを消す系
	case SHINKA_TUUSHIN_ITEM:
	case SHINKA_SOUBI_NOON:
	case SHINKA_SOUBI_NIGHT:
		i=0;
		PokeParaPut(sw->pp,ID_PARA_item,&i);
		break;
	}
}

//============================================================================================
/**
 *	進化デモ背景画面初期化＆画面生成
 */
//============================================================================================
static	void	ShinkaBGCreate(SHINKA_WORK *sw,GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
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
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
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
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			{	///< BG
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S, &TextBgCntDat[0], GF_BGL_MODE_TEXT);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME0_S);
	}

	//メイン画面背景グラフィックデータロード
	{
		WINTYPE	win_type;
		int arc_index = ARC_EGGDEMO_GRA;
		int chr_index = EGG_DATA_EGG_BG01_NCGR_BIN;
		int scr_index = EGG_DATA_EGG_BG01_NSCR_BIN;
		int pal_index = EGG_DATA_EGG_BG01_NCLR;
		int frame	  = GF_BGL_FRAME3_M;

		win_type=CONFIG_GetWindowType(sw->config);

		TalkWinGraphicNullSet(bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,sw->heapID);

		ArcUtil_BgCharSet(arc_index, chr_index, bgl, frame, 0, 0, 1, sw->heapID);
		ArcUtil_ScrnSet(arc_index, scr_index, bgl, frame, 0, 0, 1, sw->heapID);
		PaletteWorkSet_Arc(sw->pfd, arc_index, pal_index, sw->heapID, FADE_MAIN_BG, 0x20 * 2, 0);
		PaletteWorkSet_Arc(sw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), sw->heapID, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);
		PaletteWorkSet_Arc(sw->pfd, ARC_FONT, NARC_font_talk_ncrl, sw->heapID, 
			FADE_MAIN_BG, 0x20, 0x0b*0x10);
		MenuWinCgxSet(sw->bgl,GF_BGL_FRAME2_M,MENU_WIN_CGX_START,MENU_TYPE_SYSTEM,sw->heapID);
		PaletteWorkSet_Arc(sw->pfd, ARC_WINFRAME, MenuWinPalArcGet(), sw->heapID, FADE_MAIN_BG, 0x20, MENU_WIN_PAL_NO*0x10);
	}
	//サブ画面背景グラフィックデータロード
	{
		int arc_index = ARC_POKETCH_IMG;
		int chr_index = NARC_poketch_before_lz_ncgr;
		int scr_index = NARC_poketch_before_lz_nscr;
		int pal_index = NARC_poketch_before_nclr;
		int frame	  = GF_BGL_FRAME0_S;
		
		ArcUtil_BgCharSet(arc_index, chr_index, bgl, frame, 0, 0, 1, sw->heapID);
						  
		ArcUtil_ScrnSet(arc_index, scr_index, bgl, frame, 0, 0, 1, sw->heapID);
						
		PaletteWorkSet_Arc(sw->pfd, arc_index, pal_index, sw->heapID, FADE_SUB_BG, 0x20 * 1, 0);
	}

	GX_SetVisibleWnd(GX_WNDMASK_W0);
	GXS_SetVisibleWnd(GX_WNDMASK_NONE);

	G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|
						  GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|GX_WND_PLANEMASK_OBJ,
						  NULL);

	G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_OBJ,NULL);

	sw->wx1=0;
	sw->wy1=0;
	sw->wx2=0xff;
	sw->wy2=0xa0;

	GF_Disp_DispOn();

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	sys_VBlankFuncChange(ShinkaVBlank,sw);
}

static	void	ShinkaBGEnd(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S);
}

static	void	ShinkaOBJCreate(SHINKA_WORK *sw)
{
	SOFT_SPRITE_ARC	ssa;
	POKEMON_PARAM	*pp;

	PokeGraArcDataGetPP(&ssa,sw->pp,PARA_FRONT);
	sw->ss[SHINKA_BEFORE]=SoftSpriteAdd(sw->ssm,&ssa,128,80,0,0,NULL,NULL);
	pp=PokemonParam_AllocWork(sw->heapID);
	PokeCopyPPtoPP(sw->pp,pp);
	PokeParaPut(pp,ID_PARA_monsno,(u8 *)&sw->after_mons_no);
	PokeParaCalc(pp);
	PokeGraArcDataGetPP(&ssa,pp,PARA_FRONT);
	sys_FreeMemoryEz(pp);
	sw->ss[SHINKA_AFTER]=SoftSpriteAdd(sw->ssm,&ssa,128,80,0,0,NULL,NULL);
	SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_X,AFF_APPEAR_X_S);
	SoftSpriteParaSet(sw->ss[SHINKA_AFTER],SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
}

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
static	void	ShinkaVBlank(void *work)
{
	SHINKA_WORK* sw=(SHINKA_WORK*)work;

	G2_SetWnd0Position(sw->wx1,sw->wy1,sw->wx2,sw->wy2);
	
	SoftSpriteTextureTrans(sw->ssm);

	DoVramTransferManager();					///< Vram転送マネージャー実行
	PaletteFadeTrans(sw->pfd);
	
	GF_BGL_VBlankFunc(sw->bgl);
	
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

//============================================================================================
/**
 *	進化メッセージ表示関数
 *
 * @param[in]	sw			進化デモシステム構造体へのポインタ
 * @param[in]	msg_id		表示するメッセージID
 * @param[in]	wait		メッセージ表示ウエイト
 *
 */
//============================================================================================
static	u8	ShinkaMSG_Print(SHINKA_WORK *sw,int msg_id)
{
	STRBUF	*src_buf;

	src_buf=MSGMAN_AllocString(sw->msg_man,msg_id);
	WORDSET_ExpandStr(sw->wordset,sw->msg_buf,src_buf);
	sys_FreeMemoryEz(src_buf);

	GF_BGL_BmpWinDataFill(sw->win,0xff);

	return GF_STR_PrintSimple(sw->win,FONT_TALK,sw->msg_buf,0,0,CONFIG_GetMsgPrintSpeed(sw->config),ShinkaMSG_CallBack);
}

//============================================================================================
/**
 *	進化メッセージコールバック関数
 */
//============================================================================================
static	BOOL	ShinkaMSG_CallBack(MSG_PRINT_HEADER *mph,u16 value)
{
	BOOL	ret;

	ret=FALSE;

	switch(value){
	//SE終了待ち
	case 1:
		ret=Snd_SePlayCheckAll();
		break;
	//ME終了待ち
	case 2:
		ret=Snd_MePlayCheckBgmPlay();
		break;
	case 3:
		Snd_MePlay( SEQ_FANFA5 );
		break;
	case 4:
		Snd_SePlay( SEQ_SE_DP_KON );
		break;
	case 5:
		Snd_MePlay( SEQ_FANFA1 );
		break;
	default:
		break;
	}

	return ret;
}

//============================================================================================
/**
 *	進化技忘れProcセット関数
 *
 * @param[in]	sw			進化デモシステム構造体へのポインタ
 */
//============================================================================================
static	void	ShinkaWazaWasureProcSet(SHINKA_WORK *sw)
{
	sw->proc=PROC_Create(&PokeStatusProcData,sw->psd,sw->heapID);
}

