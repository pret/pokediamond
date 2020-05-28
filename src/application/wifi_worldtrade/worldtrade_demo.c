//============================================================================================
/**
 * @file	worldtrade_status.c
 * @bfief	世界交換ポケモン交換デモ呼び出し
 * @author	Akito Mori
 * @date	06.05.10
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/touchpanel.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"
#include "itemtool/itemsym.h"

#include "field/poketch_data.h"	//add by soga 2006.07.26

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "libdpw/dpw_tr.h"




//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
//static void InitWork( WORLDTRADE_WORK *wk );
//static void FreeWork( WORLDTRADE_WORK *wk );
static MYSTATUS *MakePartnerStatusData( Dpw_Tr_Data *dtd );
static POKEMON_PARAM *RecvPokemonParamPointerGet( WORLDTRADE_WORK *wk, int mode );
static void EvoPokemonUpdate( WORLDTRADE_WORK *wk );




//============================================================================================
//	PROC定義
//============================================================================================
static const PROC_DATA  TradeDemoProcData = {
	TradeDemoProc_Init,
	TradeDemoProc_Main,
	TradeDemoProc_Quit,
	FS_OVERLAY_ID(demo_trade),
};



//============================================================================================
//	定義
//============================================================================================
enum{
	DEMO_MODE_DEMO=0,
	DEMO_MODE_SHINKA,
};

//============================================================================================
//	プロセス関数
//============================================================================================

//==============================================================================
/**
 * $brief   世界交換入り口画面初期化
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Demo_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ワーク初期化
//	InitWork( wk );

	wk->demoPokePara = PokemonParam_AllocWork( HEAPID_WORLDTRADE );


	// モードごとにパラメータを格納する
	switch(wk->sub_process_mode){

	// 預ける
	case MODE_UPLOAD:
		wk->tradeDemoParam.sendPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
										(POKEMON_PARAM*)wk->UploadPokemonData.postData.data);
		wk->tradeDemoParam.recvPoke = wk->tradeDemoParam.sendPoke;
		wk->partnerStatus = MakePartnerStatusData( &wk->UploadPokemonData );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_SEND_ONLY;
		break;

	// 受け取る
	case MODE_DOWNLOAD:
		wk->tradeDemoParam.recvPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
										(POKEMON_PARAM*)wk->UploadPokemonData.postData.data);

		wk->tradeDemoParam.sendPoke = wk->tradeDemoParam.recvPoke;
		// 相手のMYSTATUSが無いので、できる限りでっちあげる
		wk->partnerStatus = MakePartnerStatusData( &wk->UploadPokemonData );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_RECV_ONLY;
		break;

	// 受け取るポケモンが交換されていた
	case MODE_DOWNLOAD_EX:
			wk->tradeDemoParam.recvPoke = PPPPointerGet((POKEMON_PARAM*)wk->UploadPokemonData.postData.data);

			WorldTradeData_GetPokemonData( wk->param->worldtrade_data, wk->demoPokePara );
			wk->tradeDemoParam.sendPoke = PPPPointerGet(wk->demoPokePara);
			
			// 相手のMYSTATUSが無いので、できる限りでっちあげる
			wk->partnerStatus 			= MakePartnerStatusData( &wk->UploadPokemonData );
			wk->tradeDemoParam.partner  = wk->partnerStatus;

			wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
			wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_FULL;
		break;

	// 交換する
	case MODE_EXCHANGE:
		WorldTradeData_GetPokemonData( wk->param->worldtrade_data, wk->demoPokePara );
		wk->tradeDemoParam.sendPoke = PPPPointerGet(wk->demoPokePara);
		wk->tradeDemoParam.recvPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
											(POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data);
		// 相手のMYSTATUSが無いので、できる限りでっちあげる
		wk->partnerStatus = MakePartnerStatusData( &wk->DownloadPokemonData[wk->TouchTrainerPos] );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_FULL;

		break;
	}

	wk->tradeDemoParam.config   = wk->param->config;

	// subPROC生成
	wk->proc = PROC_Create( &TradeDemoProcData, &wk->tradeDemoParam, HEAPID_WORLDTRADE );

	wk->subprocflag = 1;

	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   世界交換入り口画面メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Demo_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret=SEQ_MAIN;

	switch(wk->subprocess_seq){
	case DEMO_MODE_DEMO:
		if( ProcMain( wk->proc ) ){

			PROC_Delete( wk->proc );

			// 進化チェック
			if(wk->sub_process_mode==MODE_EXCHANGE){
				// 自分で交換した
				POKEMON_PARAM *pp = RecvPokemonParamPointerGet( wk, wk->sub_process_mode );
				int item     = PokeParaGet( pp, ID_PARA_item, NULL );
				int shinkano;
				int shinka_cond;
				OS_Printf( "進化チェック %d\n",PokeParaGet(pp,ID_PARA_monsno,NULL));

				shinkano=PokeShinkaCheck( NULL, pp, TUUSHIN_SHINKA, item, &shinka_cond );
				if(shinkano!=0){
					wk->shinkaWork = ShinkaInit( NULL,//ppt
												pp,
												shinkano,
												wk->param->config,
												wk->param->contestflag,
												wk->param->zukanwork,
												wk->param->myitem,//my_item
												wk->param->record,//record
												SaveData_GetPoketchData(wk->param->savedata),	//poketch_data
												shinka_cond,//shinka_cond
												SHINKA_STATUS_FLAG_SIO_MODE,
												HEAPID_WORLDTRADE);
					wk->subprocess_seq = DEMO_MODE_SHINKA;
				}else{
					// 進化無しならそのまま終了
					WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
					ret = SEQ_FADEOUT;
				
				}
			}else if(wk->sub_process_mode==MODE_DOWNLOAD || wk->sub_process_mode==MODE_DOWNLOAD_EX){
				// 自分のポケモンを引き取ったら交換されてた?
				POKEMON_PARAM *pp     = RecvPokemonParamPointerGet( wk, wk->sub_process_mode );
				POKEMON_PARAM *backup = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, backup );
				if(PokeParaGet(pp,ID_PARA_monsno,NULL)!=PokeParaGet(backup,ID_PARA_monsno,NULL)
					|| PokeParaGet(pp,ID_PARA_personal_rnd,NULL)!=PokeParaGet(backup,ID_PARA_personal_rnd,NULL)){

					int item     = PokeParaGet( pp, ID_PARA_item, NULL );
					int shinkano;
					int shinka_cond;
					OS_Printf( "進化チェック %d\n",PokeParaGet(pp,ID_PARA_monsno,NULL));

					shinkano=PokeShinkaCheck( NULL, pp, TUUSHIN_SHINKA, item, &shinka_cond );
					if(shinkano!=0){
						wk->shinkaWork = ShinkaInit( NULL,//ppt
												pp,
												shinkano,
												wk->param->config,
												wk->param->contestflag,
												wk->param->zukanwork,
												wk->param->myitem,//my_item
												wk->param->record,//record
												SaveData_GetPoketchData(wk->param->savedata),	//poketch_data
												shinka_cond,//shinka_cond
												SHINKA_STATUS_FLAG_SIO_MODE,
												HEAPID_WORLDTRADE);
						wk->subprocess_seq = DEMO_MODE_SHINKA;
					}else{
						// 進化無しならそのまま終了
						WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
						ret = SEQ_FADEOUT;
				
					}
					// 比較用に使ったポケモンデータを解放
				}else{
					// 自分のポケモンを引き取ったのであればそのまま
					WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
					ret = SEQ_FADEOUT;
				}
				sys_FreeMemoryEz(backup);
							
			}else{
				// 進化無しならそのまま終了
				WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
				ret = SEQ_FADEOUT;
			}
		}

		break;
	case DEMO_MODE_SHINKA:
		// 進化終了待ち
		if(ShinkaEndCheck(wk->shinkaWork)){
			ShinkaEnd( wk->shinkaWork );

			// 進化後のPOKEMON_PARAMをさっき格納した場所に反映させる
			EvoPokemonUpdate( wk );

			// ハードウェアウインドウを解除
			GX_SetVisibleWnd(GX_WNDMASK_NONE);

			// セーブへ
//			WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
			WorldTrade_SubProcessChange( wk, WORLDTRADE_UPLOAD, MODE_POKEMON_EVO_SAVE );
			ret = SEQ_FADEOUT;
		}
		break;
	}

	return ret;
}


//==============================================================================
/**
 * $brief   世界交換入り口画面終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Demo_End(WORLDTRADE_WORK *wk, int seq)
{
//	FreeWork( wk );

	sys_FreeMemoryEz(wk->demoPokePara);
	sys_FreeMemoryEz(wk->partnerStatus);
	// ボックス画面に戻る
	WorldTrade_SubProcessUpdate( wk );

	return SEQ_INIT;
}


//------------------------------------------------------------------
/**
 * @brief   wifiの相手からはMYSTATUSを貰わないので、最低限の情報のみ作る
 *
 * @param   dtd			サーバーから貰う交換データ
 *
 * @retval  MYSTATUS *	
 */
//------------------------------------------------------------------
static MYSTATUS *MakePartnerStatusData( Dpw_Tr_Data *dtd )
{
	MYSTATUS *status = MyStatus_AllocWork( HEAPID_WORLDTRADE );
	
	MyStatus_Init( status );
	
	// トレーナー名格納
	MyStatus_SetMyName(status, dtd->name );

	// ROM・リージョンコード格納
	MyStatus_SetRomCode( status,    dtd->versionCode );
	MyStatus_SetRegionCode( status, dtd->langCode );
	
	
	return status;
}


//------------------------------------------------------------------
/**
 * @brief   交換したポケモンのポインタを返す関数
 *
 * @param   wk		
 * @param   mode	
 *
 * @retval  POKEMON_PARAM *		
 */
//------------------------------------------------------------------
static POKEMON_PARAM *RecvPokemonParamPointerGet( WORLDTRADE_WORK *wk, int mode )
{
	// 能動的交換と、受動的交換のポケモンのポインタ
	if( mode == MODE_EXCHANGE){
		return (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data;
	}else if( mode == MODE_DOWNLOAD_EX ){
		return (POKEMON_PARAM*)wk->UploadPokemonData.postData.data;
	}else if( mode == MODE_DOWNLOAD ){
		return (POKEMON_PARAM*)wk->UploadPokemonData.postData.data;
	}

	GF_ASSERT_MSG(0,"渡すモードを間違っている");
	return NULL;
}

//------------------------------------------------------------------
/**
 * @brief   進化ポケモンをもう一度さっきいれた場所に格納しなおす
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EvoPokemonUpdate( WORLDTRADE_WORK *wk )
{
	POKEMON_PARAM *pp = RecvPokemonParamPointerGet( wk, wk->sub_process_mode );
	
	if(wk->EvoPokeInfo.boxno==18){
		// てもちの時
		PokeCopyPPtoPP( pp, PokeParty_GetMemberPointer( wk->param->myparty, wk->EvoPokeInfo.pos ) );
	}else{
		int boxno=0, boxpos=0;
		// ボックスの時
		// ボックスに格納したポケモンを一旦消す
		BOXDAT_ClearPokemon( wk->param->mybox, wk->EvoPokeInfo.boxno, wk->EvoPokeInfo.pos );

		// 格納しなおす
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );
		
	}
}
