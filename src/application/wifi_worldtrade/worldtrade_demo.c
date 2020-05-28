//============================================================================================
/**
 * @file	worldtrade_status.c
 * @bfief	���E�����|�P���������f���Ăяo��
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
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
//static void InitWork( WORLDTRADE_WORK *wk );
//static void FreeWork( WORLDTRADE_WORK *wk );
static MYSTATUS *MakePartnerStatusData( Dpw_Tr_Data *dtd );
static POKEMON_PARAM *RecvPokemonParamPointerGet( WORLDTRADE_WORK *wk, int mode );
static void EvoPokemonUpdate( WORLDTRADE_WORK *wk );




//============================================================================================
//	PROC��`
//============================================================================================
static const PROC_DATA  TradeDemoProcData = {
	TradeDemoProc_Init,
	TradeDemoProc_Main,
	TradeDemoProc_Quit,
	FS_OVERLAY_ID(demo_trade),
};



//============================================================================================
//	��`
//============================================================================================
enum{
	DEMO_MODE_DEMO=0,
	DEMO_MODE_SHINKA,
};

//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

//==============================================================================
/**
 * $brief   ���E�����������ʏ�����
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Demo_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ���[�N������
//	InitWork( wk );

	wk->demoPokePara = PokemonParam_AllocWork( HEAPID_WORLDTRADE );


	// ���[�h���ƂɃp�����[�^���i�[����
	switch(wk->sub_process_mode){

	// �a����
	case MODE_UPLOAD:
		wk->tradeDemoParam.sendPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
										(POKEMON_PARAM*)wk->UploadPokemonData.postData.data);
		wk->tradeDemoParam.recvPoke = wk->tradeDemoParam.sendPoke;
		wk->partnerStatus = MakePartnerStatusData( &wk->UploadPokemonData );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_SEND_ONLY;
		break;

	// �󂯎��
	case MODE_DOWNLOAD:
		wk->tradeDemoParam.recvPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
										(POKEMON_PARAM*)wk->UploadPokemonData.postData.data);

		wk->tradeDemoParam.sendPoke = wk->tradeDemoParam.recvPoke;
		// �����MYSTATUS�������̂ŁA�ł������ł���������
		wk->partnerStatus = MakePartnerStatusData( &wk->UploadPokemonData );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_RECV_ONLY;
		break;

	// �󂯎��|�P��������������Ă���
	case MODE_DOWNLOAD_EX:
			wk->tradeDemoParam.recvPoke = PPPPointerGet((POKEMON_PARAM*)wk->UploadPokemonData.postData.data);

			WorldTradeData_GetPokemonData( wk->param->worldtrade_data, wk->demoPokePara );
			wk->tradeDemoParam.sendPoke = PPPPointerGet(wk->demoPokePara);
			
			// �����MYSTATUS�������̂ŁA�ł������ł���������
			wk->partnerStatus 			= MakePartnerStatusData( &wk->UploadPokemonData );
			wk->tradeDemoParam.partner  = wk->partnerStatus;

			wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
			wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_FULL;
		break;

	// ��������
	case MODE_EXCHANGE:
		WorldTradeData_GetPokemonData( wk->param->worldtrade_data, wk->demoPokePara );
		wk->tradeDemoParam.sendPoke = PPPPointerGet(wk->demoPokePara);
		wk->tradeDemoParam.recvPoke = (POKEMON_PASO_PARAM*)PPPPointerGet(
											(POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data);
		// �����MYSTATUS�������̂ŁA�ł������ł���������
		wk->partnerStatus = MakePartnerStatusData( &wk->DownloadPokemonData[wk->TouchTrainerPos] );
		wk->tradeDemoParam.partner  = wk->partnerStatus;

		wk->tradeDemoParam.bgType   = DEMO_TRADE_BGTYPE_WIFI;
		wk->tradeDemoParam.seqFlag  = DEMO_TRADE_SEQ_FULL;

		break;
	}

	wk->tradeDemoParam.config   = wk->param->config;

	// subPROC����
	wk->proc = PROC_Create( &TradeDemoProcData, &wk->tradeDemoParam, HEAPID_WORLDTRADE );

	wk->subprocflag = 1;

	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   ���E�����������ʃ��C��
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

			// �i���`�F�b�N
			if(wk->sub_process_mode==MODE_EXCHANGE){
				// �����Ō�������
				POKEMON_PARAM *pp = RecvPokemonParamPointerGet( wk, wk->sub_process_mode );
				int item     = PokeParaGet( pp, ID_PARA_item, NULL );
				int shinkano;
				int shinka_cond;
				OS_Printf( "�i���`�F�b�N %d\n",PokeParaGet(pp,ID_PARA_monsno,NULL));

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
					// �i�������Ȃ炻�̂܂܏I��
					WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
					ret = SEQ_FADEOUT;
				
				}
			}else if(wk->sub_process_mode==MODE_DOWNLOAD || wk->sub_process_mode==MODE_DOWNLOAD_EX){
				// �����̃|�P������������������������Ă�?
				POKEMON_PARAM *pp     = RecvPokemonParamPointerGet( wk, wk->sub_process_mode );
				POKEMON_PARAM *backup = PokemonParam_AllocWork(HEAPID_WORLDTRADE);
				WorldTradeData_GetPokemonData( wk->param->worldtrade_data, backup );
				if(PokeParaGet(pp,ID_PARA_monsno,NULL)!=PokeParaGet(backup,ID_PARA_monsno,NULL)
					|| PokeParaGet(pp,ID_PARA_personal_rnd,NULL)!=PokeParaGet(backup,ID_PARA_personal_rnd,NULL)){

					int item     = PokeParaGet( pp, ID_PARA_item, NULL );
					int shinkano;
					int shinka_cond;
					OS_Printf( "�i���`�F�b�N %d\n",PokeParaGet(pp,ID_PARA_monsno,NULL));

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
						// �i�������Ȃ炻�̂܂܏I��
						WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
						ret = SEQ_FADEOUT;
				
					}
					// ��r�p�Ɏg�����|�P�����f�[�^�����
				}else{
					// �����̃|�P����������������̂ł���΂��̂܂�
					WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
					ret = SEQ_FADEOUT;
				}
				sys_FreeMemoryEz(backup);
							
			}else{
				// �i�������Ȃ炻�̂܂܏I��
				WorldTrade_SubProcessChange( wk, WORLDTRADE_TITLE, 0 );
				ret = SEQ_FADEOUT;
			}
		}

		break;
	case DEMO_MODE_SHINKA:
		// �i���I���҂�
		if(ShinkaEndCheck(wk->shinkaWork)){
			ShinkaEnd( wk->shinkaWork );

			// �i�����POKEMON_PARAM���������i�[�����ꏊ�ɔ��f������
			EvoPokemonUpdate( wk );

			// �n�[�h�E�F�A�E�C���h�E������
			GX_SetVisibleWnd(GX_WNDMASK_NONE);

			// �Z�[�u��
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
 * $brief   ���E�����������ʏI��
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
	// �{�b�N�X��ʂɖ߂�
	WorldTrade_SubProcessUpdate( wk );

	return SEQ_INIT;
}


//------------------------------------------------------------------
/**
 * @brief   wifi�̑��肩���MYSTATUS����Ȃ��̂ŁA�Œ���̏��̂ݍ��
 *
 * @param   dtd			�T�[�o�[����Ⴄ�����f�[�^
 *
 * @retval  MYSTATUS *	
 */
//------------------------------------------------------------------
static MYSTATUS *MakePartnerStatusData( Dpw_Tr_Data *dtd )
{
	MYSTATUS *status = MyStatus_AllocWork( HEAPID_WORLDTRADE );
	
	MyStatus_Init( status );
	
	// �g���[�i�[���i�[
	MyStatus_SetMyName(status, dtd->name );

	// ROM�E���[�W�����R�[�h�i�[
	MyStatus_SetRomCode( status,    dtd->versionCode );
	MyStatus_SetRegionCode( status, dtd->langCode );
	
	
	return status;
}


//------------------------------------------------------------------
/**
 * @brief   ���������|�P�����̃|�C���^��Ԃ��֐�
 *
 * @param   wk		
 * @param   mode	
 *
 * @retval  POKEMON_PARAM *		
 */
//------------------------------------------------------------------
static POKEMON_PARAM *RecvPokemonParamPointerGet( WORLDTRADE_WORK *wk, int mode )
{
	// �\���I�����ƁA�󓮓I�����̃|�P�����̃|�C���^
	if( mode == MODE_EXCHANGE){
		return (POKEMON_PARAM*)wk->DownloadPokemonData[wk->TouchTrainerPos].postData.data;
	}else if( mode == MODE_DOWNLOAD_EX ){
		return (POKEMON_PARAM*)wk->UploadPokemonData.postData.data;
	}else if( mode == MODE_DOWNLOAD ){
		return (POKEMON_PARAM*)wk->UploadPokemonData.postData.data;
	}

	GF_ASSERT_MSG(0,"�n�����[�h���Ԉ���Ă���");
	return NULL;
}

//------------------------------------------------------------------
/**
 * @brief   �i���|�P������������x���������ꂽ�ꏊ�Ɋi�[���Ȃ���
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
		// �Ă����̎�
		PokeCopyPPtoPP( pp, PokeParty_GetMemberPointer( wk->param->myparty, wk->EvoPokeInfo.pos ) );
	}else{
		int boxno=0, boxpos=0;
		// �{�b�N�X�̎�
		// �{�b�N�X�Ɋi�[�����|�P��������U����
		BOXDAT_ClearPokemon( wk->param->mybox, wk->EvoPokeInfo.boxno, wk->EvoPokeInfo.pos );

		// �i�[���Ȃ���
		BOXDAT_GetEmptyTrayNumberAndPos( wk->param->mybox, &boxno, &boxpos );
		BOXDAT_PutPokemonBox( wk->param->mybox, boxno, PPPPointerGet(pp) );
		
	}
}
