
//============================================================================================
/**
 * @file	scio.c
 * @bfief	戦闘サーバ、クライアント間データ送受信関数
 * @author	HisashiSogabe
 * @date	05.07.19
 */
//============================================================================================

#include "common.h"

#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/client.h"
#include "battle/fight.h"
#include "battle/scio.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/tokusyu_def.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"

#include "scio_def.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_battle.h"

#include "fight_def.h"		///<BattleWorkへの依存度が高いので、許可
#include "server_def.h"		///<ServerParamへの依存度が高いので、許可
#include "client_def.h"		///<ClientParamへの依存度が高いので、許可

//============================================================================================
/**
 * 定数宣言
 */
//============================================================================================

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================

void	SCIO_EncountEffectSet(BATTLE_WORK *bw,int send_client);
void	SCIO_PokemonEncountSet(BATTLE_WORK *bw,int send_client);
void	SCIO_PokemonEncountAppearSet(BATTLE_WORK *bw,int send_client);
void	SCIO_PokemonAppearSet(BATTLE_WORK *bw,int send_client,int ballID,int flag);
void	SCIO_PokemonReturnSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_PokemonInhaleSet(BATTLE_WORK *bw,int send_client,int ballID);
void	SCIO_PokemonDeleteSet(BATTLE_WORK *bw,int send_client);
void	SCIO_TrainerEncountSet(BATTLE_WORK *bw,int send_client);
void	SCIO_TrainerThrowSet(BATTLE_WORK *bw,int send_client,int type);
void	SCIO_TrainerOutSet(BATTLE_WORK *bw,int send_client);
void	SCIO_TrainerInSet(BATTLE_WORK *bw,int send_client,int pos);
void	SCIO_HPGaugeInSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int wait);
void	SCIO_HPGaugeOutSet(BATTLE_WORK *bw,int send_client);
void	SCIO_CommandSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
void	SCIO_CommandSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
void	SCIO_WazaSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_WazaSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
void	SCIO_DirSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int range,int send_client);
void	SCIO_DirSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
void	SCIO_ItemSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_ItemSelectReturnSet(BATTLE_WORK *bw,int send_client,ITEM_SELECT_RETURN_PARAM isrp);
void	SCIO_PokemonSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int list_mode,int chg_waza,int double_sel);
void	SCIO_PokemonSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
void	SCIO_YesNoSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int msg_id,int flag,int waza_no,int nickname);
void	SCIO_YesNoSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
void	SCIO_AttackMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	SCIO_MessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,MESSAGE_PARAM *mp);
void	SCIO_WazaEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no);
void	SCIO_WazaEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no,int attack,int defence);
void	SCIO_PokemonBlinkSet(BATTLE_WORK *bw,int send_client,u32 waza_status_flag);
void	SCIO_HPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_EXPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int now_exp);
void	SCIO_KizetsuEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_SePlaySet(BATTLE_WORK *bw,SERVER_PARAM *sp,int se_no,int send_client);
void	SCIO_FadeOutSet(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	SCIO_PokemonVanishOnOff(BATTLE_WORK *bw,int send_client,int sw);
void	SCIO_HPGaugeStatusSet(BATTLE_WORK *bw,int send_client,int status);
void	SCIO_TrainerMessageSet(BATTLE_WORK *bw,int send_client,int type);
void	SCIO_StatusEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int status);
void	SCIO_StatusEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int status);
void	SCIO_ModosuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
void	SCIO_KuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
void	SCIO_EncountMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_EncountKuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_LevelUpEffectSet(BATTLE_WORK *bw,int send_client);

void	SCIO_AlertMessageSet(BATTLE_WORK *bw,int send_client,MESSAGE_PARAM mp);
void	SCIO_AlertMessageEndSet(BATTLE_WORK *bw,int send_client);
void	SCIO_HPGaugeRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_TrainerBGSlideInSet(BATTLE_WORK *bw,int send_client);
void	SCIO_GaugeAnimeStop(BATTLE_WORK *bw,int send_client);
void	SCIO_PokemonRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int waza_no);
void	SCIO_WazaWasureSet(BATTLE_WORK *bw,int send_client,int waza_no,int sel_mons_no);
void	SCIO_MosaicSet(BATTLE_WORK *bw,int send_client,int mosaic,int wait);
void	SCIO_FormChgSet(BATTLE_WORK *bw,int send_client);
void	SCIO_BGChgSet(BATTLE_WORK *bw,int send_client);
void	SCIO_SubBGWallPut(BATTLE_WORK *bw,int send_client);
void	SCIO_BallGaugeEncountSet(BATTLE_WORK *bw,int send_client);
void	SCIO_BallGaugeEncountOut(BATTLE_WORK *bw,int send_client);
void	SCIO_BallGaugeSet(BATTLE_WORK *bw,int send_client);
void	SCIO_BallGaugeOut(BATTLE_WORK *bw,int send_client);
void	SCIO_BallGaugeResourceLoad(BATTLE_WORK *bw);
void	SCIO_BallGaugeResourceDelete(BATTLE_WORK *bw);
void	SCIO_IncRecord(BATTLE_WORK *bw,int send_client,int flag,int id);
void	SCIO_SioWaitMessage(BATTLE_WORK *bw,int send_client);
void	SCIO_ChrPop(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_SStoOAMCall(BATTLE_WORK *bw,int send_client);
void	SCIO_OAMtoSSCall(BATTLE_WORK *bw,int send_client);
void	SCIO_WinLoseMessage(BATTLE_WORK *bw);
void	SCIO_EscapeMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	SCIO_GiveUpMessage(BATTLE_WORK *bw);
void	SCIO_MigawariChrSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_WazaKoukaSESet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
void	SCIO_BGMPlay(BATTLE_WORK *bw,int send_client,int bgm_no);

void	SCIO_WinLoseFlagSet(BATTLE_WORK *bw);
void	SCIO_BlinkMessage(BATTLE_WORK *bw);

void	SCIO_ServerQueClear(BATTLE_WORK *bw,int send_client,int index);

void	SCIO_CommRecvData(BATTLE_WORK *bw,void *data);

void	SCIO_EffectDataSet(BATTLE_WORK *bw,SERVER_PARAM *sp,WAZA_EFFECT_PARAM *wep,int flag,int data,int attack,int defence,u16 waza_no);

void	ScioBattleRecvData(BATTLE_WORK *bw);
static	void	ScioBattleSendData(BATTLE_WORK *bw,int access,int para,void *data,u8 size);
static	void	SCIO_Interface(BATTLE_WORK *bw,int access,int para,void *data,u8 size);
static	void	SCIO_BallGaugeParamMake(BATTLE_WORK *bw,SERVER_PARAM *sp,BALL_GAUGE_PARAM *bgp,int command_code,int client_no);

//--------------------------------------------------------------
/**
 * @brief   バトルコマンド送信処理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static	void ScioBattleSendData(BATTLE_WORK *bw,int access,int para,void *data,u8 size)
{
	int				i;
	SIO_SEND_DATA	ssd;
	u8				*src;
	u8				*dest;
	u16				*write;
	u16				*over;

	dest=BattleWorkSioRecvBufGet(bw);
	write=BattleWorkSioRecvWriteGet(bw);
	over=BattleWorkSioRecvOverGet(bw);

	//今回のQueへの書き込みでバッファオーバーするかチェック
	if(write[0]+sizeof(SIO_SEND_DATA)+size+1>BATTLE_SIO_BUF_SIZE){
	//オーバーした場合は、overバッファにその旨を格納
	//writeバッファを先頭に戻す
		over[0]=write[0];
		write[0]=0;
	}

	ssd.access=access;
	ssd.para=para;
	ssd.size=size;

	src=(u8 *)&ssd;

	for(i=0;i<sizeof(SIO_SEND_DATA);i++){
		dest[write[0]]=src[i];
		write[0]++;
	}

	src=(u8 *)data;

	for(i=0;i<size;i++){
		dest[write[0]]=src[i];
		write[0]++;
	}
}

//============================================================================================
/**
 *
 *	受信したデータを各バッファにコピー
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	size		データサイズ
 * @param[in]	data		受信したデータ
 *
 */
//============================================================================================
static	BOOL	SCIO_RecvData(BATTLE_WORK *bw,void *data)
{
	u8	*src=(u8 *)data;
	u8	access;
	u8	para;
	int	size;
	int	i;
	BOOL	ret=FALSE;

	access=src[SIO_BUF_ACCESS];
	para=src[SIO_BUF_PARA];
	size=src[SIO_BUF_SIZE_LOW]|(src[SIO_BUF_SIZE_HIGH]<<8);

	src+=sizeof(SIO_SEND_DATA);

	if(access==SCIO_SERVER){
		if(bw->server_param->server_buffer[para][0]==0){
			for(i=0;i<size;i++){
				bw->server_param->server_buffer[para][i]=src[i];
			}
			ret=TRUE;
		}
	}
	else if(access==SCIO_CLIENT){
		if(bw->client_param[para]->client_buffer[0]==0){
			for(i=0;i<size;i++){
				bw->client_param[para]->client_buffer[i]=src[i];
			}
			ret=TRUE;
		}
	}
	else if(access==SCIO_SERVER_QUE){
		{
			int	index;
			int	id;

			index=src[0];
			id=src[1];

			if(BattleWorkServerFlagGet(bw)){
				ST_ServerQueReset(bw->server_param,id,para,index);
			}
		}
		ret=TRUE;
	}
	else{
		OS_Printf("SCIO_RecvData:ここにくるのは、おかしい\n");
	}

	return	ret;
}

//--------------------------------------------------------------
/**
 * @brief   バトルコマンド受信TCB
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void	ScioBattleRecvData(BATTLE_WORK *bw)
{
	u8				*src;
	u16				*read;
	u16				*write;
	u16				*over;
	int				size;

	src=BattleWorkSioRecvBufGet(bw);
	read=BattleWorkSioRecvReadGet(bw);
	write=BattleWorkSioRecvWriteGet(bw);
	over=BattleWorkSioRecvOverGet(bw);

	//バッファの読み込み位置と書き込み位置が同じときはデータがないので、受信しない
	if(read[0]==write[0]){
		return;
	}
	//バッファの読み込み位置とオーバーバッファが同じときは先頭に戻す
	if(read[0]==over[0]){
		read[0]=0;
		over[0]=0;
	}
	if(SCIO_RecvData(bw,(void *)&src[read[0]])==TRUE){
		size=sizeof(SIO_SEND_DATA)+(src[read[0]+SIO_BUF_SIZE_LOW]|(src[read[0]+SIO_BUF_SIZE_HIGH]<<8));
		read[0]+=size;
	}
}

//============================================================================================
/**
 *
 *	データ送受信処理
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	access	サーバ、クライアントどちら向けのデータなのか SCIO_SERVER：サーバ向け
 *																	 SCIO_CLIENT:クライアント向け
 *																	 SCIO_SERVER_QUE:サーバキュー向け
 *
 * @param[in]	para	accessの値によって意味が変化 SCIO_SERVER：応答するクライアントナンバー
 *													 SCIO_CLIENT:データを送るクライアントナンバー
 *													 SCIO_SERVER_QUE:サーバキューから削除する対象のクライアントナンバー
 * @param[in]	data	送るデータのワークのポインタ
 * @param[in]	size	送るデータのサイズ
 *
 *	dataの中身
 *	accessがSCIO_CLIENTの時は、
 *	data[0]:命令コードインデックス
 *	data[1]～:命令コードインデックスごとの引数データ
 */
//============================================================================================
static	void	SCIO_Interface(BATTLE_WORK *bw,int access,int para,void *data,u8 size)
{
	int	i;
	u8	*send=(u8 *)data;

	//実際は通信対戦の時の処理を作成
	if(bw->fight_type&FIGHT_TYPE_SIO){
		if(access==SCIO_CLIENT){
			{
				int	id;

				for(id=0;id<CommGetConnectNum();id++){
					ST_ServerQueSet(bw->server_param,id,para,send[0]);
				}
			}
		}
		CommCommandBattleSendData(bw,access,para,data,size);
	}
	else{
		if(access==SCIO_CLIENT){
			ST_ServerQueSet(bw->server_param,0,para,send[0]);
		}
		ScioBattleSendData(bw,access,para,data,size);
#if 0
		if(access==SCIO_SERVER){
			for(i=0;i<size;i++){
				bw->server_param->server_buffer[para][i]=send[i];
			}
		}
		else if(access==SCIO_CLIENT){
			ST_ServerQueSet(bw->server_param,0,para,send[0]);
			for(i=0;i<size;i++){
				bw->client_param[para]->client_buffer[i]=send[i];
			}
		}
		else if(access==SCIO_SERVER_QUE){
			ST_ServerQueReset(bw->server_param,0,para,send[0]);
		}
		else{
			OS_Printf("SCIO_Interface:ここにくるのは、おかしい\n");
		}
#endif
	}
}

//============================================================================================
/**
 *
 *	エンカウントエフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_EncountEffectSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_ENCOUNT_EFFECT;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	ポケモンエンカウントセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_PokemonEncountSet(BATTLE_WORK *bw,int send_client)
{
	POKEMON_ENCOUNT_PARAM	pep;
	int						i;

	pep.command_code=CL_POKEMON_ENCOUNT;
	pep.sex			=bw->server_param->psp[send_client].sex;
	pep.rare		=bw->server_param->psp[send_client].rare;
	pep.monsno		=bw->server_param->psp[send_client].monsno;
	pep.personal_rnd=bw->server_param->psp[send_client].personal_rnd;
	pep.voice		=ST_ServerPokeVoiceEffNoGet(bw->server_param,send_client,BattleWorkClientTypeGet(bw, send_client), TRUE);
	pep.form_no	=bw->server_param->psp[send_client].form_no;

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		pep.wazano[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_waza1+i,		NULL);
		pep.pp[i]=		ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp1+i,		NULL);
		pep.ppmax[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp_max1+i,	NULL);
	}
	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_nickname,&pep.nickname);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&pep,sizeof(POKEMON_ENCOUNT_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン出現セット（エンカウント時専用）
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_PokemonEncountAppearSet(BATTLE_WORK *bw,int send_client)
{
	POKEMON_APPEAR_PARAM	pap;
	int						i;

	pap.command_code	=CL_POKEMON_ENCOUNT_APPEAR;
	pap.sex				=bw->server_param->psp[send_client].sex;
	pap.rare			=bw->server_param->psp[send_client].rare;
	pap.monsno			=bw->server_param->psp[send_client].monsno;
	pap.personal_rnd	=bw->server_param->psp[send_client].personal_rnd;
	pap.voice			=ST_ServerPokeVoiceEffNoGet(bw->server_param,send_client,BattleWorkClientTypeGet(bw, send_client), TRUE);
	pap.sel_mons_no		=bw->server_param->sel_mons_no[send_client];
	pap.form_no			=bw->server_param->psp[send_client].form_no;
	pap.ballID			=bw->server_param->psp[send_client].get_ball;
	pap.pair_sel_mons_no=bw->server_param->sel_mons_no[BattleWorkPartnerClientNoGet(bw,send_client)];

	//繰り出したフラグをセット
	BattleWorkAppearFlagSet(bw,send_client,pap.sel_mons_no);

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		pap.wazano[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_waza1+i,		NULL);
		pap.pp[i]=		ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp1+i,		NULL);
		pap.ppmax[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp_max1+i,	NULL);
	}
	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_nickname,&pap.nickname);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&pap,sizeof(POKEMON_APPEAR_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン出現セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	ballID		出現するボール（NULLだと捕獲したボール）
 * @param[in]	flag		0:繰り出しor1:捕獲失敗フラグ
 *
 */
//============================================================================================
void	SCIO_PokemonAppearSet(BATTLE_WORK *bw,int send_client,int ballID,int flag)
{
	POKEMON_APPEAR_PARAM	pap;
	int						i;

	pap.command_code=CL_POKEMON_APPEAR;
	
	if(bw->server_param->psp[send_client].condition2&CONDITION2_HENSHIN){
		pap.sex			=bw->server_param->psp[send_client].wkw.henshin_sex;
		pap.personal_rnd=bw->server_param->psp[send_client].wkw.henshin_rnd;
	}
	else{
		pap.sex			=bw->server_param->psp[send_client].sex;
		pap.personal_rnd=bw->server_param->psp[send_client].personal_rnd;
	}

	pap.rare		=bw->server_param->psp[send_client].rare;
	pap.monsno		=bw->server_param->psp[send_client].monsno;
	pap.voice		=ST_ServerPokeVoiceEffNoGet(bw->server_param,send_client,BattleWorkClientTypeGet(bw, send_client), FALSE);
	pap.sel_mons_no	=bw->server_param->sel_mons_no[send_client];
	pap.form_no		=bw->server_param->psp[send_client].form_no;
	if(ballID){
		pap.ballID	=ballID;
	}
	else{
		pap.ballID	=bw->server_param->psp[send_client].get_ball;
	}
	pap.flag		=flag;
	pap.migawari_flag=((bw->server_param->psp[send_client].condition2&CONDITION2_MIGAWARI)!=0);

	//繰り出したフラグをセット
	BattleWorkAppearFlagSet(bw,send_client,pap.sel_mons_no);


	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		pap.wazano[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_waza1+i,		NULL);
		pap.pp[i]=		ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp1+i,		NULL);
		pap.ppmax[i]=	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_pp_max1+i,	NULL);
	}
	ST_ServerPokemonServerParamGet(bw->server_param,send_client,ID_PSP_nickname,&pap.nickname);

	for(i=0;i<CLIENT_MAX;i++){
		pap.wep_mons_no[i]		=bw->server_param->psp[i].monsno;
		pap.wep_rare[i]			=bw->server_param->psp[i].rare;
		pap.wep_form_no[i]		=bw->server_param->psp[i].form_no;
		if(bw->server_param->psp[i].condition2&CONDITION2_HENSHIN){
			pap.wep_sex[i]			=bw->server_param->psp[i].wkw.henshin_sex;
			pap.wep_personal_rnd[i]	=bw->server_param->psp[i].wkw.henshin_rnd;
		}
		else{
			pap.wep_sex[i]			=bw->server_param->psp[i].sex;
			pap.wep_personal_rnd[i]	=bw->server_param->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&pap,sizeof(POKEMON_APPEAR_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン引っ込めるセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_PokemonReturnSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	POKEMON_RETURN_PARAM	prp;
	int						dir;
	int						form_no;
	int						i;

	if(bw->client_param[send_client]->client_type&CLIENT_ENEMY_FLAG){
		dir=PARA_FRONT;
	}
	else{
		dir=PARA_BACK;
	}

	form_no=bw->server_param->psp[send_client].form_no;

	prp.command_code=CL_POKEMON_RETURN;
	if(bw->server_param->psp[send_client].condition2&CONDITION2_HENSHIN){
		prp.height=PokeHeightGet(bw->server_param->psp[send_client].monsno,
								 bw->server_param->psp[send_client].wkw.henshin_sex,dir,form_no,
								 bw->server_param->psp[send_client].wkw.henshin_rnd);
	}
	else{
		prp.height=PokeHeightGet(bw->server_param->psp[send_client].monsno,
								 bw->server_param->psp[send_client].sex,dir,form_no,
								 bw->server_param->psp[send_client].personal_rnd);
	}
	prp.ballID=bw->server_param->psp[send_client].get_ball;
	prp.migawari_flag=((bw->server_param->psp[send_client].condition2&CONDITION2_MIGAWARI)!=0);

	for(i=0;i<CLIENT_MAX;i++){
		prp.mons_no[i]		=sp->psp[i].monsno;
		prp.rare[i]			=sp->psp[i].rare;
		prp.form_no[i]		=sp->psp[i].form_no;
		if(sp->psp[i].condition2&CONDITION2_HENSHIN){
			prp.sex[i]			=sp->psp[i].wkw.henshin_sex;
			prp.personal_rnd[i]	=sp->psp[i].wkw.henshin_rnd;
		}
		else{
			prp.sex[i]			=sp->psp[i].sex;
			prp.personal_rnd[i]	=sp->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&prp,sizeof(POKEMON_RETURN_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン吸い込みセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_PokemonInhaleSet(BATTLE_WORK *bw,int send_client,int ballID)
{
	POKEMON_INHALE_PARAM	pip;
	int						dir;
	int						form_no;

	if(bw->client_param[send_client]->client_type&CLIENT_ENEMY_FLAG){
		dir=PARA_FRONT;
	}
	else{
		dir=PARA_BACK;
	}

	form_no=bw->server_param->psp[send_client].form_no;

	pip.command_code=CL_POKEMON_INHALE;
	if(bw->server_param->psp[send_client].condition2&CONDITION2_HENSHIN){
		pip.height=PokeHeightGet(bw->server_param->psp[send_client].monsno,
								 bw->server_param->psp[send_client].wkw.henshin_sex,dir,form_no,
								 bw->server_param->psp[send_client].wkw.henshin_rnd);
	}
	else{
		pip.height=PokeHeightGet(bw->server_param->psp[send_client].monsno,
								 bw->server_param->psp[send_client].sex,dir,form_no,
								 bw->server_param->psp[send_client].personal_rnd);
	}
	
	pip.ballID=ballID;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&pip,sizeof(POKEMON_INHALE_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモンを削除
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_PokemonDeleteSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_POKEMON_DELETE;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	トレーナーエンカウントセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_TrainerEncountSet(BATTLE_WORK *bw,int send_client)
{
	TRAINER_ENCOUNT_PARAM	tep;

	tep.command_code=CL_TRAINER_ENCOUNT;
	tep.trtype=bw->trainer_data[send_client].tr_type;
	tep.tr_sex=bw->trainer_sex[send_client];

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&tep,sizeof(TRAINER_ENCOUNT_PARAM));
}

//============================================================================================
/**
 *
 *	トレーナー投げるエフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	type		エフェクトタイプ
 *
 */
//============================================================================================
void	SCIO_TrainerThrowSet(BATTLE_WORK *bw,int send_client,int type)
{
	TRAINER_THROW_PARAM	ttp;

	ttp.command_code	=CL_TRAINER_THROW;
	ttp.type			=type;
	ttp.pair_sel_mons_no=bw->server_param->sel_mons_no[BattleWorkPartnerClientNoGet(bw,send_client)];

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&ttp,sizeof(TRAINER_THROW_PARAM));
}

//============================================================================================
/**
 *
 *	トレーナー画面外エフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_TrainerOutSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_TRAINER_OUT;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	トレーナー画面内エフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_TrainerInSet(BATTLE_WORK *bw,int send_client,int pos)
{
	TRAINER_IN_PARAM	tip;

	tip.command_code=CL_TRAINER_IN;
	tip.trtype=bw->trainer_data[send_client].tr_type;
	tip.tr_sex=bw->trainer_sex[send_client];
	tip.pos=pos;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&tip,sizeof(TRAINER_IN_PARAM));
}

//============================================================================================
/**
 *
 *	HPゲージ画面内エフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_HPGaugeInSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int wait)
{
	HP_GAUGE_IN_PARAM	hgip;
	POKEMON_PARAM		*pp;
	int					monsno;
	int					level;

	pp=BattleWorkPokemonParamGet(bw,send_client,sp->sel_mons_no[send_client]);
	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);

	hgip.command_code=CL_HP_GAUGE_IN;
	hgip.level=sp->psp[send_client].level;
	hgip.hp=sp->psp[send_client].hp;
	hgip.hpmax=sp->psp[send_client].hpmax;
	hgip.sel_mons_no=sp->sel_mons_no[send_client];
	hgip.status=ST_ServerConditionNoGet(sp,send_client);
	if(((sp->psp[send_client].monsno==MONSNO_NIDORAN_F)||(sp->psp[send_client].monsno==MONSNO_NIDORAN_M))&&
	    (sp->psp[send_client].nickname_flag==0)){
		hgip.sex=PARA_UNK;
	}
	else{
		hgip.sex=sp->psp[send_client].sex;
	}
	hgip.now_exp=sp->psp[send_client].exp-PokeLevelExpGet(monsno,level);
	hgip.max_exp=PokeLevelExpGet(monsno,level+1)-PokeLevelExpGet(monsno,level);
	hgip.get_mark=FT_ZukanFlagCheckGet(bw,sp->psp[send_client].monsno);

	hgip.safari_ball=BattleWorkSafariBallCountGet(bw);

	hgip.wait=wait;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&hgip,sizeof(HP_GAUGE_IN_PARAM));
}

//============================================================================================
/**
 *
 *	HPゲージ画面外エフェクトセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_HPGaugeOutSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_HP_GAUGE_OUT;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	コマンド選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_CommandSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no)
{
	COMMAND_SELECT_PARAM	csp;
	int						i;
	int						client_no;
	int						cli1,cli2;
	int						monsno;
	int						pos;
	POKEPARTY				*poke_party;
	POKEMON_PARAM			*pp;
	u32						fight_type;
	int						scsc_flag;

	MI_CpuClearFast(&csp, sizeof(COMMAND_SELECT_PARAM));

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(BattleWorkServerParamGet(bw),send_client);

	scsc_flag=0;
	for(i=0;i<BattleWorkClientSetMaxGet(bw);i++){
		if(ST_ServerCommandSelectCheck(sp,i)==FALSE){
			scsc_flag|=No2Bit(i);
		}
	}

	csp.command_code=CL_COMMAND_SELECT;
	csp.sel_mons_no=sel_mons_no;
	csp.no_reshuffle_client=sp->no_reshuffle_client|scsc_flag;

	fight_type=BattleWorkFightTypeGet(bw);

	if((fight_type&FIGHT_TYPE_2vs2)&&
	  ((fight_type&FIGHT_TYPE_MULTI)==0)){
		client_no=send_client&1;
	}
	else{
		client_no=send_client;
	}

	//自分側
	poke_party=BattleWorkPokePartyGet(bw,client_no);
	pos=0;
	for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
		pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[client_no][i]);
		monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
		if((monsno)&&(monsno!=MONSNO_TAMAGO)){
			if(PokeParaGet(pp,ID_PARA_hp,NULL)){
				if(PokeParaGet(pp,ID_PARA_condition,NULL)){
					csp.status[0][pos]=COMSEL_STATUS_NG;
				}
				else{
					csp.status[0][pos]=COMSEL_STATUS_ALIVE;
				}
			}
			else{
				csp.status[0][pos]=COMSEL_STATUS_DEAD;
			}
			if(fight_type&FIGHT_TYPE_NO_EXP){
				csp.motivation[pos]=0;
			}
			else{
				csp.motivation[pos]=PokeParaNextLevelExpRatioGet(pp);
			}
			pos++;
		}
	}

	//相手側
	if(((fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))==(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))||
	   ((fight_type&FIGHT_TYPE_TAG))||
	   ((fight_type==FIGHT_TYPE_AI_MULTI))||
	   ((fight_type==FIGHT_TYPE_BATTLE_TOWER_AI_MULTI))){
		if(BattleWorkMineEnemyCheck(bw,send_client)){
			client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
		}
		else{
			client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		}
		poke_party=BattleWorkPokePartyGet(bw,client_no);
		pos=0;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[client_no][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						csp.status[1][pos]=COMSEL_STATUS_NG;
					}
					else{
						csp.status[1][pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					csp.status[1][pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
		if(BattleWorkMineEnemyCheck(bw,send_client)){
			client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
		}
		else{
			client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
		}
		poke_party=BattleWorkPokePartyGet(bw,client_no);
		pos=3;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[client_no][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						csp.status[1][pos]=COMSEL_STATUS_NG;
					}
					else{
						csp.status[1][pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					csp.status[1][pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
	}
	else{
		client_no=BattleWorkEnemyClientNoGet(bw,send_client,BWECNG_SIDE_LEFT);
		poke_party=BattleWorkPokePartyGet(bw,client_no);
		pos=0;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[client_no][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						csp.status[1][pos]=COMSEL_STATUS_NG;
					}
					else{
						csp.status[1][pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					csp.status[1][pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
	}

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		csp.wazano[i]=	ST_ServerPokemonServerParamGet(sp,send_client,ID_PSP_waza1+i,	NULL);
		csp.pp[i]=		ST_ServerPokemonServerParamGet(sp,send_client,ID_PSP_pp1+i,		NULL);
		csp.ppmax[i]=	ST_ServerPokemonServerParamGet(sp,send_client,ID_PSP_pp_max1+i,	NULL);
	}

	csp.icon_hp=sp->psp[send_client].hp;
	csp.icon_hpmax=sp->psp[send_client].hpmax;
	if(csp.icon_hp){
		if(sp->psp[send_client].condition){
			csp.icon_status=COMSEL_STATUS_NG;
		}
		else{
			csp.icon_status=COMSEL_STATUS_ALIVE;
		}
	}
	else{
		csp.icon_status=COMSEL_STATUS_DEAD;
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&csp,sizeof(COMMAND_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	コマンド選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	data		送るデータ
 *
 */
//============================================================================================
void	SCIO_CommandSelectReturnSet(BATTLE_WORK *bw,int send_client,int data)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&data,4);
}

//============================================================================================
/**
 *
 *	技選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_WazaSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	WAZA_SELECT_PARAM	wsp;
	int					i;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(BattleWorkServerParamGet(bw),send_client);

	wsp.command_code=CL_WAZA_SELECT;
	wsp.sel_mons_no=sp->sel_mons_no[send_client];
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		wsp.wazano[i]=sp->psp[send_client].waza[i];
		wsp.pp[i]=sp->psp[send_client].pp[i];
		wsp.ppmax[i]=WT_PPMaxGet(sp->psp[send_client].waza[i],sp->psp[send_client].pp_count[i]);
	}

	wsp.wazabit=ST_ServerWaruagakiCheck(bw,sp,send_client,0,SSWC_ALL);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wsp,sizeof(WAZA_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	技選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	data		送るデータ
 *
 */
//============================================================================================
void	SCIO_WazaSelectReturnSet(BATTLE_WORK *bw,int send_client,int data)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&data,4);
}

//============================================================================================
/**
 *
 *	攻撃対象選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_DirSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int range,int send_client)
{
	DIR_SELECT_PARAM	dsp;
	int					i;
	u32					fight_type;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(sp,send_client);

	fight_type=BattleWorkFightTypeGet(bw);

	dsp.command_code=CL_DIR_SELECT;
	dsp.range=range;

	if(((fight_type&FIGHT_TYPE_2vs2)==0)||
		(fight_type&FIGHT_TYPE_MULTI)||
	   ((fight_type&FIGHT_TYPE_2vs2)&&(send_client>=2))){
		dsp.flag=1;
	}
	else{
		dsp.flag=0;
	}


	for(i=0;i<CLIENT_MAX;i++){
		if(sp->psp[i].hp){
			dsp.dspp[i].hp=sp->psp[i].hp;
			dsp.dspp[i].hpmax=sp->psp[i].hpmax;
			dsp.dspp[i].exist=1;
			if(((sp->psp[i].monsno==MONSNO_NIDORAN_F)||(sp->psp[i].monsno==MONSNO_NIDORAN_M))&&
			    (sp->psp[i].nickname_flag==0)){
				dsp.dspp[i].sex=PARA_UNK;
			}
			else{
				dsp.dspp[i].sex=sp->psp[i].sex;
			}
			dsp.dspp[i].sel_mons_no=sp->sel_mons_no[i];
			if(sp->psp[i].condition){
				dsp.dspp[i].status=COMSEL_STATUS_NG;
			}
			else{
				dsp.dspp[i].status=COMSEL_STATUS_ALIVE;
			}
		}
		else{
			dsp.dspp[i].exist=0;
			dsp.dspp[i].status=COMSEL_STATUS_DEAD;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&dsp,sizeof(DIR_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	攻撃対象選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_DirSelectReturnSet(BATTLE_WORK *bw,int send_client,int data)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&data,4);
}

//============================================================================================
/**
 *
 *	道具選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_ItemSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	ITEM_SELECT_PARAM	isp;
	int					i,j;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(sp,send_client);

	isp.command_code=CL_ITEM_SELECT;
	for(i=0;i<CLIENT_MAX;i++){
		isp.sel_mons_no[i]=sp->sel_mons_no[i];
		for(j=0;j<POKEMON_TEMOTI_MAX;j++){
			isp.list_row[i][j]=sp->list_row[i][j];
		}
		isp.shutout_flag[i]=sp->psp[i].wkw.shutout_count;
	}

	if(BattleWorkFightTypeGet(bw)==FIGHT_TYPE_2vs2_YASEI){
		if(((sp->no_reshuffle_client&No2Bit(CLIENT_NO_ENEMY))==0)&&
		   ((sp->no_reshuffle_client&No2Bit(CLIENT_NO_ENEMY2))==0)){
			isp.enc_double=1;
			isp.waza_vanish=0;
			isp.waza_migawari=0;
		}
		else if((sp->no_reshuffle_client&No2Bit(CLIENT_NO_ENEMY))==0){
			isp.enc_double=0;
			if(sp->psp[CLIENT_NO_ENEMY].waza_kouka&WAZAKOUKA_KIE){
				isp.waza_vanish=1;
				isp.waza_migawari=0;
			}
			else if(sp->psp[CLIENT_NO_ENEMY].condition2&CONDITION2_MIGAWARI){
				isp.waza_vanish=0;
				isp.waza_migawari=1;
			}
			else{
				isp.waza_vanish=0;
				isp.waza_migawari=0;
			}
		}
		else{
			isp.enc_double=0;
			if(sp->psp[CLIENT_NO_ENEMY2].waza_kouka&WAZAKOUKA_KIE){
				isp.waza_vanish=1;
				isp.waza_migawari=0;
			}
			else if(sp->psp[CLIENT_NO_ENEMY2].condition2&CONDITION2_MIGAWARI){
				isp.waza_vanish=0;
				isp.waza_migawari=1;
			}
			else{
				isp.waza_vanish=0;
				isp.waza_migawari=0;
			}
		}
	}
	else if(BattleWorkFightTypeGet(bw)==FIGHT_TYPE_1vs1_YASEI){
		isp.enc_double=0;
		if(sp->psp[CLIENT_NO_ENEMY].waza_kouka&WAZAKOUKA_KIE){
			isp.waza_vanish=1;
			isp.waza_migawari=0;
		}
		else if(sp->psp[CLIENT_NO_ENEMY].condition2&CONDITION2_MIGAWARI){
			isp.waza_vanish=0;
			isp.waza_migawari=1;
		}
		else{
			isp.waza_vanish=0;
			isp.waza_migawari=0;
		}
	}
	else{
		isp.enc_double=0;
		isp.waza_vanish=0;
		isp.waza_migawari=0;
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&isp,sizeof(ITEM_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	道具選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	data		送るデータ
 *
 */
//============================================================================================
void	SCIO_ItemSelectReturnSet(BATTLE_WORK *bw,int send_client,ITEM_SELECT_RETURN_PARAM isrp)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&isrp,sizeof(ITEM_SELECT_RETURN_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	list_mode	ポケモンリストのモード
 * @param[in]	chg_waza	入れ替えできない技ナンバーなどを指定
 * @param[in]	double_sel	2vs2時に1体目が選択したポケモンのSelPosNo（選択なしは、６）
 *
 */
//============================================================================================
void	SCIO_PokemonSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int list_mode,int chg_waza,int double_sel)
{
	POKEMON_SELECT_PARAM	psp;
	int						i,j;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(sp,send_client);

	psp.command_code=CL_POKEMON_SELECT;
	psp.client_no=send_client;
	psp.list_mode=list_mode;
	psp.chg_waza=chg_waza;
	psp.double_sel=double_sel;
	psp.no_reshuffle_client=sp->no_reshuffle_client;

	for(i=0;i<CLIENT_MAX;i++){
		psp.sel_mons_no[i]=sp->sel_mons_no[i];
		for(j=0;j<POKEMON_TEMOTI_MAX;j++){
			psp.list_row[i][j]=sp->list_row[i][j];
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&psp,sizeof(POKEMON_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモン選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	data		送るデータ
 *
 */
//============================================================================================
void	SCIO_PokemonSelectReturnSet(BATTLE_WORK *bw,int send_client,int data)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&data,4);
}

//============================================================================================
/**
 *
 *	Yes/No選択セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	msg_id		選択をさせるメッセージID
 * @param[in]	flag		選択をさせるタイプ
 * @param[in]	waza_no		技あきらめタイプの時の技ナンバー
 * @param[in]	nickname	ニックネームつける時の対象ポケモン
 */
//============================================================================================
void	SCIO_YesNoSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int msg_id,int flag,int waza_no,int nickname)
{
	YES_NO_SELECT_PARAM	ynsp;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(sp,send_client);

	ynsp.command_code=CL_YES_NO_SELECT;
	ynsp.msg_id=msg_id;
	ynsp.flag=flag;
	ynsp.waza_no=waza_no;
	ynsp.nickname=nickname;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&ynsp,sizeof(YES_NO_SELECT_PARAM));
}

//============================================================================================
/**
 *
 *	Yes/No選択結果セット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	data		送るデータ
 *
 */
//============================================================================================
void	SCIO_YesNoSelectReturnSet(BATTLE_WORK *bw,int send_client,int data)
{
	SCIO_Interface(bw,SCIO_SERVER,send_client,&data,4);
}

//============================================================================================
/**
 *
 *	アタックメッセージセット
 *
 * @param[in]	bw	戦闘システムワークのポインタ
 * @param[in]	sp	サーバ用ワークのポインタ
 *
 */
//============================================================================================
void	SCIO_AttackMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ATTACK_MESSAGE_PARAM	amp;

	amp.command_code=CL_ATTACK_MESSAGE;
	amp.sel_mons_no=sp->sel_mons_no[sp->attack_client];
	amp.waza_no=sp->waza_no_now;

	SCIO_Interface(bw,SCIO_CLIENT,sp->attack_client,&amp,sizeof(ATTACK_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	メッセージセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	sp		サーバ用ワークのポインタ
 * @param[in]	mp		メッセージパラメータ構造体
 */
//============================================================================================
void	SCIO_MessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,MESSAGE_PARAM *mp)
{
	mp->command_code=CL_MESSAGE;
	SCIO_Interface(bw,SCIO_CLIENT,sp->attack_client,mp,sizeof(MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	技エフェクトセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	sp		サーバ用ワークのポインタ
 * @param[in]	waza_no	エフェクトを出す技ナンバー
 *
 */
//============================================================================================
void	SCIO_WazaEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no)
{
	WAZA_EFFECT_PARAM	wep;

	SCIO_EffectDataSet(bw,sp,&wep,EFFTYPE_WAZA,NULL,sp->attack_client,sp->defence_client,waza_no);

	SCIO_Interface(bw,SCIO_CLIENT,sp->attack_client,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	技エフェクトセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	sp		サーバ用ワークのポインタ
 * @param[in]	waza_no	エフェクトを出す技ナンバー
 *
 */
//============================================================================================
void	SCIO_WazaEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no,int attack,int defence)
{
	WAZA_EFFECT_PARAM	wep;

	SCIO_EffectDataSet(bw,sp,&wep,EFFTYPE_WAZA,NULL,attack,defence,waza_no);

	SCIO_Interface(bw,SCIO_CLIENT,attack,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	ポケモンダメージブリンクアクションセット
 *
 * @param[in]	bw					戦闘システムワークのポインタ
 * @param[in]	send_client			データを送るクライアント
 * @param[in]	waza_status_flag	技ヒットの効果
 *
 */
//============================================================================================
void	SCIO_PokemonBlinkSet(BATTLE_WORK *bw,int send_client,u32 waza_status_flag)
{
	int	command_code=CL_POKEMON_BLINK;
	
	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	HPゲージ計算をセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバ用ワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_HPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	HP_GAUGE_CALC_PARAM	hgcp;
	POKEMON_PARAM		*pp;
	int					monsno;
	int					level;

	pp=BattleWorkPokemonParamGet(bw,send_client,sp->sel_mons_no[send_client]);
	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);

	hgcp.command_code=CL_HP_GAUGE_CALC;
	hgcp.level=sp->psp[send_client].level;
	hgcp.hp=sp->psp[send_client].hp;
	hgcp.hpmax=sp->psp[send_client].hpmax;
	hgcp.damage=sp->hp_calc_work;
	if(((sp->psp[send_client].monsno==MONSNO_NIDORAN_F)||(sp->psp[send_client].monsno==MONSNO_NIDORAN_M))&&
	    (sp->psp[send_client].nickname_flag==0)){
		hgcp.sex=PARA_UNK;
	}
	else{
		hgcp.sex=sp->psp[send_client].sex;
	}
	hgcp.now_exp=sp->psp[send_client].exp-PokeLevelExpGet(monsno,level);
	hgcp.max_exp=PokeLevelExpGet(monsno,level+1)-PokeLevelExpGet(monsno,level);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&hgcp,sizeof(HP_GAUGE_CALC_PARAM));
}

//============================================================================================
/**
 *
 *	EXPゲージ計算をセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバ用ワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_EXPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int now_exp)
{
	EXP_GAUGE_CALC_PARAM	egcp;
	POKEMON_PARAM			*pp;
	int						monsno;
	int						level;

	pp=BattleWorkPokemonParamGet(bw,send_client,sp->sel_mons_no[send_client]);
	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);

	egcp.command_code=CL_EXP_GAUGE_CALC;
	egcp.now_exp=now_exp;
	egcp.next_exp=sp->psp[send_client].exp-PokeLevelExpGet(monsno,level);
	egcp.max_exp=PokeLevelExpGet(monsno,level+1)-PokeLevelExpGet(monsno,level);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&egcp,sizeof(EXP_GAUGE_CALC_PARAM));
}

//============================================================================================
/**
 *
 *	気絶エフェクトをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバ用ワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_KizetsuEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	KIZETSU_EFFECT_PARAM	kep;
	int						i;

	kep.command_code=CL_KIZETSU_EFFECT;
	kep.monsno		=sp->psp[send_client].monsno;
	kep.form_no		=sp->psp[send_client].form_no;
	kep.migawari_flag=((sp->psp[send_client].condition2&CONDITION2_MIGAWARI)!=0);
	kep.henshin_flag=((sp->psp[send_client].condition2&CONDITION2_HENSHIN)!=0);

	if(sp->psp[send_client].condition2&CONDITION2_HENSHIN){
		kep.sex			=sp->psp[send_client].wkw.henshin_sex;
		kep.personal_rnd=sp->psp[send_client].wkw.henshin_rnd;
	}
	else{
		kep.sex			=sp->psp[send_client].sex;
		kep.personal_rnd=sp->psp[send_client].personal_rnd;
	}

	for(i=0;i<CLIENT_MAX;i++){
		kep.wep_mons_no[i]			=sp->psp[i].monsno;
		kep.wep_rare[i]				=sp->psp[i].rare;
		kep.wep_form_no[i]			=sp->psp[i].form_no;
		if(sp->psp[i].condition2&CONDITION2_HENSHIN){
			kep.wep_sex[i]			=sp->psp[i].wkw.henshin_sex;
			kep.wep_personal_rnd[i]	=sp->psp[i].wkw.henshin_rnd;
		}
		else{
			kep.wep_sex[i]			=sp->psp[i].sex;
			kep.wep_personal_rnd[i]	=sp->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&kep,sizeof(KIZETSU_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	SEをコール
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバ用ワークのポインタ
 * @param[in]	se_no		鳴らすSENo
 * @param[in]	send_client	鳴らす対象クライアント
 *
 */
//============================================================================================
void	SCIO_SePlaySet(BATTLE_WORK *bw,SERVER_PARAM *sp,int se_no,int send_client)
{
	SE_PLAY_PARAM	spp;

	spp.command_code=CL_SE_PLAY;
	spp.se_no=se_no;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&spp,sizeof(SE_PLAY_PARAM));
}

//============================================================================================
/**
 *
 *	画面フェードアウトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	sp		サーバ用ワークのポインタ
 *
 */
//============================================================================================
void	SCIO_FadeOutSet(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	command_code=CL_FADE_OUT;

	SCIO_Interface(bw,SCIO_CLIENT,0,&command_code,4);
}

//============================================================================================
/**
 *
 *	ポケモンバニッシュフラグのON/OFF
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	バニッシュ対象クライアント
 * @param[in]	sw			バニッシュのON/OFFスイッチ
 *
 */
//============================================================================================
void	SCIO_PokemonVanishOnOff(BATTLE_WORK *bw,int send_client,int sw)
{
	POKEMON_VANISH_ON_OFF	pvoo;
	int						i;

	pvoo.command_code=CL_POKEMON_VANISH_ON_OFF;
	pvoo.sw=sw;
	pvoo.migawari_flag=((bw->server_param->psp[send_client].condition2&CONDITION2_MIGAWARI)!=0);

	for(i=0;i<CLIENT_MAX;i++){
		pvoo.wep_mons_no[i]			=bw->server_param->psp[i].monsno;
		pvoo.wep_rare[i]			=bw->server_param->psp[i].rare;
		pvoo.wep_form_no[i]			=bw->server_param->psp[i].form_no;
		if(bw->server_param->psp[i].condition2&CONDITION2_HENSHIN){
			pvoo.wep_sex[i]			=bw->server_param->psp[i].wkw.henshin_sex;
			pvoo.wep_personal_rnd[i]=bw->server_param->psp[i].wkw.henshin_rnd;
		}
		else{
			pvoo.wep_sex[i]			=bw->server_param->psp[i].sex;
			pvoo.wep_personal_rnd[i]=bw->server_param->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&pvoo,sizeof(POKEMON_VANISH_ON_OFF));
}

//============================================================================================
/**
 *
 *	HPゲージに状態異常アイコンをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 * @param[in]	status		状態異常ステータス
 *
 */
//============================================================================================
void	SCIO_HPGaugeStatusSet(BATTLE_WORK *bw,int send_client,int status)
{
	HP_GAUGE_STATUS_SET_PARAM	hgssp;

	hgssp.command_code=CL_HP_GAUGE_STATUS_SET;
	hgssp.status=status;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&hgssp,sizeof(HP_GAUGE_STATUS_SET_PARAM));
}

//============================================================================================
/**
 *
 *	トレーナーメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	メッセージ表示対象クライアント
 * @param[in]	type		メッセージタイプ
 *
 */
//============================================================================================
void	SCIO_TrainerMessageSet(BATTLE_WORK *bw,int send_client,int type)
{
	TRAINER_MESSAGE_PARAM	tmp;

	tmp.command_code=CL_TRAINER_MESSAGE;
	tmp.type=type;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&tmp,sizeof(TRAINER_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	状態異常エフェクトをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 * @param[in]	status		状態異常の種類
 *
 */
//============================================================================================
void	SCIO_StatusEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int status)
{
	WAZA_EFFECT_PARAM	wep;

	SCIO_EffectDataSet(bw,sp,&wep,EFFTYPE_STATUS,status,send_client,send_client,NULL);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	状態異常エフェクトをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	cl1			セット対象クライアント
 * @param[in]	cl2			セット対象クライアント
 * @param[in]	status		状態異常の種類
 *
 */
//============================================================================================
void	SCIO_StatusEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int status)
{
	WAZA_EFFECT_PARAM	wep;

	SCIO_EffectDataSet(bw,sp,&wep,EFFTYPE_STATUS,status,cl1,cl2,NULL);

	SCIO_Interface(bw,SCIO_CLIENT,cl1,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	戻すメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_ModosuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no)
{
	MODOSU_MESSAGE_PARAM	mmp;

	mmp.command_code=CL_MODOSU_MESSAGE;
	mmp.sel_mons_no=sel_mons_no;
	mmp.rate=(sp->hp_temp-sp->psp[CLIENT_NO_ENEMY].hp)*100/sp->hp_temp;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&mmp,sizeof(MODOSU_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	繰り出すメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_KuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no)
{
	KURIDASU_MESSAGE_PARAM	kmp;

	kmp.command_code=CL_KURIDASU_MESSAGE;
	kmp.sel_mons_no=sel_mons_no;
	if(sp->psp[CLIENT_NO_ENEMY].hp==0){
		kmp.rate=1000;
	}
	else{
		kmp.rate=sp->psp[CLIENT_NO_ENEMY].hp*1000/sp->psp[CLIENT_NO_ENEMY].hpmax;
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&kmp,sizeof(KURIDASU_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	エンカウントメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_EncountMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	int	command_code=CL_ENCOUNT_MESSAGE;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	エンカウント時の繰り出すメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_EncountKuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	ENCOUNT_KURIDASU_MESSAGE_PARAM	ekmp;
	int	client_no;

	ekmp.command_code=CL_ENCOUNT_KURIDASU_MESSAGE;

	for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
		ekmp.sel_mons_no[client_no]=sp->sel_mons_no[client_no];
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&ekmp,sizeof(ENCOUNT_KURIDASU_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	レベルアップエフェクトをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_LevelUpEffectSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_LEVEL_UP_EFFECT;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	アラートメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 * @param[in]	msg_id		アラートメッセージID
 *
 */
//============================================================================================
void	SCIO_AlertMessageSet(BATTLE_WORK *bw,int send_client,MESSAGE_PARAM mp)
{
	ALERT_MESSAGE_PARAM	amp;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(BattleWorkServerParamGet(bw),send_client);

	amp.command_code=CL_ALERT_MESSAGE;
	amp.mp=mp;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&amp,sizeof(ALERT_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	アラートメッセージ表示終了をセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 *
 */
//============================================================================================
void	SCIO_AlertMessageEndSet(BATTLE_WORK *bw,int send_client)
{
	int	command;

	command=1;
	SCIO_Interface(bw,SCIO_SERVER,send_client,&command,4);
}

//============================================================================================
/**
 *
 *	HPゲージ再描画
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_HPGaugeRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	HP_GAUGE_REFRESH_PARAM	hgrp;
	POKEMON_PARAM			*pp;
	int						monsno;
	int						level;

	pp=BattleWorkPokemonParamGet(bw,send_client,sp->sel_mons_no[send_client]);
	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);

	hgrp.command_code=CL_HP_GAUGE_REFRESH;
	hgrp.level=sp->psp[send_client].level;
	hgrp.hp=sp->psp[send_client].hp;
	hgrp.hpmax=sp->psp[send_client].hpmax;
	hgrp.sel_mons_no=sp->sel_mons_no[send_client];
	hgrp.status=ST_ServerConditionNoGet(sp,send_client);
	if(((sp->psp[send_client].monsno==MONSNO_NIDORAN_F)||(sp->psp[send_client].monsno==MONSNO_NIDORAN_M))&&
	    (sp->psp[send_client].nickname_flag==0)){
		hgrp.sex=PARA_UNK;
	}
	else{
		hgrp.sex=sp->psp[send_client].sex;
	}
	hgrp.now_exp=sp->psp[send_client].exp-PokeLevelExpGet(monsno,level);
	hgrp.max_exp=PokeLevelExpGet(monsno,level+1)-PokeLevelExpGet(monsno,level);
	hgrp.get_mark=FT_ZukanFlagCheckGet(bw,sp->psp[send_client].monsno);
	hgrp.safari_ball=BattleWorkSafariBallCountGet(bw);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&hgrp,sizeof(HP_GAUGE_REFRESH_PARAM));
}

//============================================================================================
/**
 *
 *	必要なデータをコピー
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	セット対象クライアント
 * @param[in]	sel_mons_no	セット対象ポケモン位置
 *
 */
//============================================================================================
void	SCIO_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	PSP_TO_PP_COPY_PARAM	ptpcp;
	int						i;

	ptpcp.command_code=CL_PSP_TO_PSP_COPY;
	ptpcp.sel_mons_no=sp->sel_mons_no[send_client];
	ptpcp.monomane_bit=sp->psp[send_client].wkw.monomane_bit;
	ptpcp.hp=sp->psp[send_client].hp;
	ptpcp.item=sp->psp[send_client].item;
	ptpcp.hatakiotosu=sp->scw[BattleWorkMineEnemyCheck(bw,send_client)].hatakiotosu_item;
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		ptpcp.waza[i]=sp->psp[send_client].waza[i];
		ptpcp.pp[i]=sp->psp[send_client].pp[i];
	}
	if(ptpcp.hp){
		//どくどくカウンタはリセット
		ptpcp.condition=(sp->psp[send_client].condition&CONDITION_DOKUDOKU_CNT_OFF);
		ptpcp.condition2=sp->psp[send_client].condition2;
	}
	else{
		ptpcp.condition=0;
		ptpcp.condition2=0;
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&ptpcp,sizeof(PSP_TO_PP_COPY_PARAM));
}

//============================================================================================
/**
 *
 *	タッチパネルにトレーナーBGをSlideInさせる
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	キュークリアの対象クライアント
 * @param[in]	index		キュークリアの対象命令コード
 *
 */
//============================================================================================
void	SCIO_TrainerBGSlideInSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_TRAINER_BG_SLIDEIN;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	HPゲージのアニメーションを止める
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	キュークリアの対象クライアント
 * @param[in]	index		キュークリアの対象命令コード
 *
 */
//============================================================================================
void	SCIO_GaugeAnimeStop(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_GAUGE_ANIME_STOP;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	ポケモンの状態異常を直す（いやしのすずなど）
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	対象クライアント
 * @param[in]	index		対象の技ナンバー
 *
 */
//============================================================================================
void	SCIO_PokemonRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int waza_no)
{
	POKEMON_REFRESH_PARAM	prs;

	prs.command_code=CL_POKEMON_REFRESH;
	prs.waza_no=waza_no;
	prs.speabi=sp->psp[send_client].speabino;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&prs,sizeof(POKEMON_REFRESH_PARAM));
}

//============================================================================================
/**
 *
 *	技忘れ処理を呼び出す
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	waza_no		覚えた技ナンバー
 * @param[in]	sel_mons_no	技忘れをするSelPosNo
 *
 */
//============================================================================================
void	SCIO_WazaWasureSet(BATTLE_WORK *bw,int send_client,int waza_no,int sel_mons_no)
{
	WAZA_WASURE_PARAM	wwp;

	//クライアントからの返答バッファをクリア
	ST_ServerBufferClear(BattleWorkServerParamGet(bw),send_client);

	wwp.command_code=CL_WAZA_WASURE;
	wwp.waza_no=waza_no;
	wwp.sel_mons_no=sel_mons_no;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wwp,sizeof(POKEMON_REFRESH_PARAM));
}

//============================================================================================
/**
 *
 *	ソフトウエアスプライトにモザイクをかける
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	mosaic		モザイク段階
 * @param[in]	wait		モザイクをかけるスピード
 *
 */
//============================================================================================
void	SCIO_MosaicSet(BATTLE_WORK *bw,int send_client,int mosaic,int wait)
{
	MOSAIC_SET_PARAM	msp;

	msp.command_code=CL_MOSAIC_SET;
	msp.mosaic=mosaic;
	msp.wait=wait;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&msp,sizeof(MOSAIC_SET_PARAM));
}

//============================================================================================
/**
 *
 *	フォルムナンバーをチェンジ
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 * @param[in]	form_no		チェンジするフォルムナンバー
 *
 */
//============================================================================================
void	SCIO_FormChgSet(BATTLE_WORK *bw,int send_client)
{
	FORM_CHG_PARAM	fcp;

	fcp.command_code=CL_FORM_CHG;
	fcp.mons_no		=bw->server_param->psp[send_client].monsno;
	fcp.rare		=bw->server_param->psp[send_client].rare;

	if(bw->server_param->psp[send_client].condition2&CONDITION2_HENSHIN){
		fcp.sex			=bw->server_param->psp[send_client].wkw.henshin_sex;
		fcp.personal_rnd=bw->server_param->psp[send_client].wkw.henshin_rnd;
	}
	else{
		fcp.sex			=bw->server_param->psp[send_client].sex;
		fcp.personal_rnd=bw->server_param->psp[send_client].personal_rnd;
	}

	fcp.form_no	=bw->server_param->psp[send_client].form_no;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&fcp,sizeof(FORM_CHG_PARAM));
}

//============================================================================================
/**
 *
 *	地形OBJをBGにチェンジ
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_BGChgSet(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_BG_CHG;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	サブ画面の背景壁紙を表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_SubBGWallPut(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_SUBBG_WALL_PUT;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	ボールゲージを表示（エンカウント時）
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_BallGaugeEncountSet(BATTLE_WORK *bw,int send_client)
{
	BALL_GAUGE_PARAM	bgp;

	SCIO_BallGaugeParamMake(bw,bw->server_param,&bgp,CL_BALL_GAUGE_ENCOUNT_SET,send_client);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&bgp,sizeof(BALL_GAUGE_PARAM));
}

//============================================================================================
/**
 *
 *	ボールゲージを消す（エンカウント時）
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_BallGaugeEncountOut(BATTLE_WORK *bw,int send_client)
{
	BALL_GAUGE_PARAM	bgp;

	SCIO_BallGaugeParamMake(bw,bw->server_param,&bgp,CL_BALL_GAUGE_ENCOUNT_OUT,send_client);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&bgp,sizeof(BALL_GAUGE_PARAM));
}

//============================================================================================
/**
 *
 *	ボールゲージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_BallGaugeSet(BATTLE_WORK *bw,int send_client)
{
	BALL_GAUGE_PARAM	bgp;

	SCIO_BallGaugeParamMake(bw,bw->server_param,&bgp,CL_BALL_GAUGE_SET,send_client);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&bgp,sizeof(BALL_GAUGE_PARAM));
}

//============================================================================================
/**
 *
 *	ボールゲージを消す
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	データを送るクライアント
 *
 */
//============================================================================================
void	SCIO_BallGaugeOut(BATTLE_WORK *bw,int send_client)
{
	BALL_GAUGE_PARAM	bgp;

	SCIO_BallGaugeParamMake(bw,bw->server_param,&bgp,CL_BALL_GAUGE_OUT,send_client);

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&bgp,sizeof(BALL_GAUGE_PARAM));
}

//============================================================================================
/**
 *
 *	ボールゲージのリソースをロード
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_BallGaugeResourceLoad(BATTLE_WORK *bw)
{
	int	command_code=CL_BALL_GAUGE_RESOURCE_LOAD;

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&command_code,4);
}

//============================================================================================
/**
 *
 *	ボールゲージのリソースを消去
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_BallGaugeResourceDelete(BATTLE_WORK *bw)
{
	int	command_code=CL_BALL_GAUGE_RESOURCE_DELETE;

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&command_code,4);
}

//============================================================================================
/**
 *
 *	カウントアップワークのインクリメント
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	カウントアップするClientNo
 * @param[in]	flag		カウントアップする制御フラグ
 * @param[in]	id			カウントアップするワークID
 *
 */
//============================================================================================
void	SCIO_IncRecord(BATTLE_WORK *bw,int send_client,int flag,int id)
{
	INC_RECORD_PARAM	irp;

	irp.command_code=CL_INC_RECORD;
	irp.flag=flag;
	irp.id=id;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&irp,sizeof(INC_RECORD_PARAM));
}

//============================================================================================
/**
 *
 *	通信待機メッセージの表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	カウントアップするClientNo
 * @param[in]	flag		カウントアップする制御フラグ
 * @param[in]	id			カウントアップするワークID
 *
 */
//============================================================================================
void	SCIO_SioWaitMessage(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_SIO_WAIT_MESSAGE;

	//通信対戦の時のみ有効
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO){
		SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
	}
}

//============================================================================================
/**
 *
 *	退避していたキャラを復帰
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	復帰するClientNo
 *
 */
//============================================================================================
void	SCIO_ChrPop(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	int					i;
	WAZA_EFFECT_PARAM	wep;		//使うパラメータは同じなので、これを使用

	wep.command_code=CL_CHR_POP;

	for(i=0;i<CLIENT_MAX;i++){
		wep.mons_no[i]		=sp->psp[i].monsno;
		wep.rare[i]			=sp->psp[i].rare;
		wep.form_no[i]		=sp->psp[i].form_no;
		if(sp->psp[i].condition2&CONDITION2_HENSHIN){
			wep.sex[i]			=sp->psp[i].wkw.henshin_sex;
			wep.personal_rnd[i]	=sp->psp[i].wkw.henshin_rnd;
		}
		else{
			wep.sex[i]			=sp->psp[i].sex;
			wep.personal_rnd[i]	=sp->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	ソフトスプライトをOAMに変換
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	復帰するClientNo
 *
 */
//============================================================================================
void	SCIO_SStoOAMCall(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_SS_TO_OAM_CALL;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	OAMをソフトスプライトに戻す
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	復帰するClientNo
 *
 */
//============================================================================================
void	SCIO_OAMtoSSCall(BATTLE_WORK *bw,int send_client)
{
	int	command_code=CL_OAM_TO_SS_CALL;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&command_code,4);
}

//============================================================================================
/**
 *
 *	通信対戦時の勝敗メッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_WinLoseMessage(BATTLE_WORK *bw)
{
	int	command_code=CL_WIN_LOSE_MESSAGE;

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&command_code,4);
}

//============================================================================================
/**
 *
 *	通信対戦時のにげるメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_EscapeMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ESCAPE_MESSAGE_PARAM	emp;
	int						client_no;

	emp.command_code=CL_ESCAPE_MESSAGE;
	emp.escape_flag=0;

	for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
		if(sp->client_act_work[client_no][ACT_PARA_ACT_NO]==SERVER_ESCAPE_COMMAND_NO){
			emp.escape_flag|=No2Bit(client_no);
		}
	}

//	GF_ASSERT(emp.escape_flag!=0);

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&emp,sizeof(ESCAPE_MESSAGE_PARAM));
}

//============================================================================================
/**
 *
 *	バトルタワーのリタイアメッセージを表示
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_GiveUpMessage(BATTLE_WORK *bw)
{
	int	command_code=CL_GIVEUP_MESSAGE;

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&command_code,4);
}

//============================================================================================
/**
 *
 *	みがわりキャラをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	復帰するClientNo
 *
 */
//============================================================================================
void	SCIO_MigawariChrSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	int					i;
	WAZA_EFFECT_PARAM	wep;		//使うパラメータは同じなので、これを使用

	wep.command_code=CL_MIGAWARI_CHR_SET;

	for(i=0;i<CLIENT_MAX;i++){
		wep.mons_no[i]		=sp->psp[i].monsno;
		wep.rare[i]			=sp->psp[i].rare;
		wep.form_no[i]		=sp->psp[i].form_no;
		if(sp->psp[i].condition2&CONDITION2_HENSHIN){
			wep.sex[i]			=sp->psp[i].wkw.henshin_sex;
			wep.personal_rnd[i]	=sp->psp[i].wkw.henshin_rnd;
		}
		else{
			wep.sex[i]			=sp->psp[i].sex;
			wep.personal_rnd[i]	=sp->psp[i].personal_rnd;
		}
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wep,sizeof(WAZA_EFFECT_PARAM));
}

//============================================================================================
/**
 *
 *	技効果SEをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	sp			サーバシステムワークのポインタ
 * @param[in]	send_client	復帰するClientNo
 *
 */
//============================================================================================
void	SCIO_WazaKoukaSESet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client)
{
	WAZAKOUKA_SE_PARAM	wsp;

	wsp.command_code=CL_WAZAKOUKA_SE;

	if(sp->waza_status_flag&WAZA_STATUS_FLAG_BATSUGUN){
		wsp.kouka=WAZA_HIT_BATSUGUN;
	}
	else if(sp->waza_status_flag&WAZA_STATUS_FLAG_IMAHITOTSU){
		wsp.kouka=WAZA_HIT_IMAHITOTSU;
	}
	else{
		wsp.kouka=WAZA_HIT_NORMAL;
	}

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&wsp,sizeof(WAZAKOUKA_SE_PARAM));
}

//============================================================================================
/**
 *
 *	曲をセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	送信するClientNo
 * @param[in]	bgm_no		曲ナンバー
 *
 */
//============================================================================================
void	SCIO_BGMPlay(BATTLE_WORK *bw,int send_client,int bgm_no)
{
	BGM_PLAY_PARAM	bpp;

	bpp.command_code=CL_BGM_PLAY;
	bpp.bgm_no=bgm_no;

	SCIO_Interface(bw,SCIO_CLIENT,send_client,&bpp,sizeof(BGM_PLAY_PARAM));
}

//============================================================================================
/**
 *
 *	win_lose_flagをセット
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_WinLoseFlagSet(BATTLE_WORK *bw)
{
	WIN_LOSE_SET_PARAM	wlsp;

	wlsp.command_code=CL_WIN_LOSE_SET;
	wlsp.win_lose_flag=BattleWorkWinLoseGet(bw);

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&wlsp,sizeof(WIN_LOSE_SET_PARAM));
}

//============================================================================================
/**
 *
 *	メッセージウインドウをクリア
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 *
 */
//============================================================================================
void	SCIO_BlankMessage(BATTLE_WORK *bw)
{
	int	command_code=CL_BLANK_MESSAGE;

	SCIO_Interface(bw,SCIO_CLIENT,CLIENT_NO_MINE,&command_code,4);
}

//============================================================================================
/**
 *
 *	サーバキュークリア
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	send_client	キュークリアの対象クライアント
 * @param[in]	index		キュークリアの対象命令コード
 *
 */
//============================================================================================
void	SCIO_ServerQueClear(BATTLE_WORK *bw,int send_client,int index)
{
	SERVER_QUE_CLEAR_PARAM	sqcp;

	sqcp.index=index;
	sqcp.id=CommGetCurrentID();

	SCIO_Interface(bw,SCIO_SERVER_QUE,send_client,&sqcp,sizeof(SERVER_QUE_CLEAR_PARAM));
}

//============================================================================================
/**
 *
 *	通信で受信したデータを各バッファにコピー
 *
 * @param[in]	bw			戦闘システムワークのポインタ
 * @param[in]	size		データサイズ
 * @param[in]	data		受信したデータ
 *
 */
//============================================================================================
void	SCIO_CommRecvData(BATTLE_WORK *bw,void *data)
{
	u8	*src=(u8 *)data;
	u8	access;
	u8	para;
	int	size;
	int	i;

	access=src[SIO_BUF_ACCESS];
	para=src[SIO_BUF_PARA];
	size=src[SIO_BUF_SIZE_LOW]|(src[SIO_BUF_SIZE_HIGH]<<8);

	src+=sizeof(SIO_SEND_DATA);

	if(access==SCIO_SERVER){
		for(i=0;i<size;i++){
			bw->server_param->server_buffer[para][i]=src[i];
		}
	}
	else if(access==SCIO_CLIENT){
		for(i=0;i<size;i++){
			bw->client_param[para]->client_buffer[i]=src[i];
		}
	}
	else if(access==SCIO_SERVER_QUE){
		{
			int	index;
			int	id;

			index=src[0];
			id=src[1];

			if(BattleWorkServerFlagGet(bw)){
				ST_ServerQueReset(bw->server_param,id,para,index);
			}
		}
	}
	else{
		OS_Printf("SCIO_CommRecvData:ここにくるのは、おかしい\n");
	}
}

//============================================================================================
/**
 *
 *	エフェクトデータセット（技エフェクト＆ステータスエフェクト）
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 * @param[in]	sp		サーバ用ワークのポインタ
 * @param[in]	flag	エフェクトのタイプ
 * @param[in]	data	エフェクト用データ
 *
 */
//============================================================================================
void	SCIO_EffectDataSet(BATTLE_WORK *bw,SERVER_PARAM *sp,WAZA_EFFECT_PARAM *wep,int flag,int data,int attack,int defence,u16 waza_no)
{
	int					i;

	wep->command_code=CL_WAZA_EFFECT;
	wep->waza_no=waza_no;
	wep->at_client_no=attack;						///< 攻撃側のクライアント番号
	wep->df_client_no=defence;						///< 防御側のクライアント番号
	wep->flag=flag;
	wep->data=data;
	wep->ground_id=BattleWorkGroundIDGet(bw);

	if(sp!=NULL){
		wep->waza_eff_damage=sp->damage;	///< 技で受けるダメージ(回復の時は[ - ])
		if(sp->damage_power){
			wep->waza_eff_power=sp->damage_power;		///< 出ている技の威力
		}
		else{
//			wep->waza_eff_power=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage);
			wep->waza_eff_power=sp->AIWT.wtd[waza_no].damage;
		}
		wep->waza_eff_natuki=sp->psp[attack].friend;		///< なつき度
		if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
			wep->waza_eff_weather=sp->field_condition;		///< 天候
		}
		else{
			wep->waza_eff_weather=0;						///< 天候
		}
		wep->waza_eff_cnt=sp->waza_eff_cnt;				///< 技エフェクトのカウンタ(空を飛ぶとか)
		wep->migawari_flag=((sp->psp[attack].condition2&CONDITION2_MIGAWARI)!=0);
		wep->henshin_flag=((sp->psp[attack].condition2&CONDITION2_HENSHIN)!=0);
	
		for(i=0;i<CLIENT_MAX;i++){
			wep->mons_no[i]=sp->psp[i].monsno;
			wep->rare[i]=sp->psp[i].rare;
			wep->form_no[i]=sp->psp[i].form_no;
			wep->waza_kouka[i]=sp->psp[i].waza_kouka;
			if(sp->psp[i].condition2&CONDITION2_HENSHIN){
				wep->sex[i]=sp->psp[i].wkw.henshin_sex;
				wep->personal_rnd[i]=sp->psp[i].wkw.henshin_rnd;
			}
			else{
				wep->sex[i]=sp->psp[i].sex;
				wep->personal_rnd[i]=sp->psp[i].personal_rnd;
			}
		}
	}
}

//============================================================================================
/**
 *
 *	ボールゲージ構造体生成
 *
 * @param[in]	bw				戦闘システムワークのポインタ
 * @param[in]	bgp				生成するBALL_GAUGE_PARAM構造体のポインタ
 * @param[in]	command_code	ボールゲージの種類
 * @param[in]	client_no		生成対象のClientNo
 *
 */
//============================================================================================
static	void	SCIO_BallGaugeParamMake(BATTLE_WORK *bw,SERVER_PARAM *sp,BALL_GAUGE_PARAM *bgp,int command_code,int client_no)
{
	int					i;
	int					cli1,cli2;
	int					monsno;
	int					pos;
	u32					fight_type;
	POKEPARTY			*poke_party;
	POKEMON_PARAM		*pp;

	MI_CpuClearFast(bgp, sizeof(BALL_GAUGE_PARAM));

	fight_type=BattleWorkFightTypeGet(bw);

	bgp->command_code=command_code;

	if(((fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))==(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))||
	   ((fight_type&FIGHT_TYPE_TAG)&&(BattleWorkMineEnemyCheck(bw,client_no)))||
	   ((fight_type==FIGHT_TYPE_AI_MULTI)&&(BattleWorkMineEnemyCheck(bw,client_no)))||
	   ((fight_type==FIGHT_TYPE_BATTLE_TOWER_AI_MULTI))){
		if((BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_A)||
		   (BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_B)){
			cli1=client_no;
			cli2=BattleWorkPartnerClientNoGet(bw,client_no);
		}
		else{
			cli1=BattleWorkPartnerClientNoGet(bw,client_no);
			cli2=client_no;
		}
		poke_party=BattleWorkPokePartyGet(bw,cli1);
		pos=0;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
//			pp=PokeParty_GetMemberPointer(poke_party,i);
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[cli1][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						bgp->status[pos]=COMSEL_STATUS_NG;
					}
					else{
						bgp->status[pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					bgp->status[pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
		poke_party=BattleWorkPokePartyGet(bw,cli2);
		pos=3;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
//			pp=PokeParty_GetMemberPointer(poke_party,i);
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[cli2][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						bgp->status[pos]=COMSEL_STATUS_NG;
					}
					else{
						bgp->status[pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					bgp->status[pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
	}
	else{
		if((fight_type&FIGHT_TYPE_2vs2)&&
		  ((fight_type&FIGHT_TYPE_MULTI)==0)){
			client_no=client_no&1;
		}
		else{
			client_no=client_no;
		}

		poke_party=BattleWorkPokePartyGet(bw,client_no);
		pos=0;
		for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
//			pp=PokeParty_GetMemberPointer(poke_party,i);
			pp=PokeParty_GetMemberPointer(poke_party,sp->list_row[client_no][i]);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno)&&(monsno!=MONSNO_TAMAGO)){
				if(PokeParaGet(pp,ID_PARA_hp,NULL)){
					if(PokeParaGet(pp,ID_PARA_condition,NULL)){
						bgp->status[pos]=COMSEL_STATUS_NG;
					}
					else{
						bgp->status[pos]=COMSEL_STATUS_ALIVE;
					}
				}
				else{
					bgp->status[pos]=COMSEL_STATUS_DEAD;
				}
				pos++;
			}
		}
	}
}

